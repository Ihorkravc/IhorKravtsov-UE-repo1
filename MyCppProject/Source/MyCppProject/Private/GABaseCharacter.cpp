#include "GABaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Net/UnrealNetwork.h"

#include "GAHealthSet.h"
#include "GAHealthHUDWidget.h"
#include "Blueprint/UserWidget.h"

AGABaseCharacter::AGABaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    HealthSet = CreateDefaultSubobject<UGAHealthSet>(TEXT("HealthSet"));
}

UAbilitySystemComponent* AGABaseCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AGABaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
    }

    InitializeAttributes();

    // HUD тільки локальному гравцю
    if (IsLocallyControlled() && HealthHUDClass && AbilitySystemComponent)
    {
        HealthHUDInstance = CreateWidget<UGAHealthHUDWidget>(GetWorld(), HealthHUDClass);
        if (HealthHUDInstance)
        {
            HealthHUDInstance->AddToViewport();
            HealthHUDInstance->InitWithASC(AbilitySystemComponent);
            UpdateMedkitHUD(); // ✅ стартове оновлення
        }
    }
}

void AGABaseCharacter::InitializeAttributes()
{
    if (HealthSet)
    {
        HealthSet->SetMaxHealth(100.f);
        HealthSet->SetHealth(50.f);
    }
}

void AGABaseCharacter::UpdateMedkitHUD()
{
    if (HealthHUDInstance)
    {
        // ✅ Викликаємо ПУБЛІЧНИЙ міст, а не BlueprintEvent напряму
        HealthHUDInstance->UpdateMedkit(MedkitCharges, MaxMedkitCharges);
    }
}

void AGABaseCharacter::UseMedkit()
{
    // клієнт -> сервер
    if (!HasAuthority())
    {
        ServerUseMedkit();
        return;
    }

    if (!AbilitySystemComponent || !MedkitAbilityClass)
        return;

    if (MedkitCharges <= 0)
        return;

    // Має бути видана ability (її будемо видавати коли підібрав аптечку)
    FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromClass(MedkitAbilityClass);
    if (!Spec)
        return;

    const bool bActivated = AbilitySystemComponent->TryActivateAbilityByClass(MedkitAbilityClass);

    if (bActivated)
    {
        MedkitCharges = FMath::Clamp(MedkitCharges - 1, 0, MaxMedkitCharges);
        UpdateMedkitHUD(); // ✅ сервер теж може оновити для локального (в синглі)
    }
}

void AGABaseCharacter::AddMedkit(int32 Amount)
{
    if (!HasAuthority())
    {
        ServerAddMedkit(Amount);
        return;
    }

    if (Amount <= 0)
        return;

    MedkitCharges = FMath::Clamp(MedkitCharges + Amount, 0, MaxMedkitCharges);

    // Видаємо ability тільки коли аптечки реально є
    if (AbilitySystemComponent && MedkitAbilityClass)
    {
        const bool bHasSpec = (AbilitySystemComponent->FindAbilitySpecFromClass(MedkitAbilityClass) != nullptr);
        if (!bHasSpec)
        {
            AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(MedkitAbilityClass, 1, 0));
        }
    }

    UpdateMedkitHUD();
}

void AGABaseCharacter::OnRep_MedkitCharges()
{
    // Викликається на клієнтах при зміні
    UpdateMedkitHUD();
}

void AGABaseCharacter::ServerUseMedkit_Implementation()
{
    UseMedkit();
}

void AGABaseCharacter::ServerAddMedkit_Implementation(int32 Amount)
{
    AddMedkit(Amount);
}

void AGABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGABaseCharacter, MedkitCharges);
}