#include "GABaseCharacter.h"
#include "GAHealthHUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "GAHealthSet.h"
#include "GameplayAbilitySpec.h" // для FGameplayAbilitySpec
#include "Engine/Engine.h" 

AGABaseCharacter::AGABaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

    HealthSet = CreateDefaultSubobject<UGAHealthSet>(TEXT("HealthSet"));
    if (AbilitySystemComponent && HealthSet)
    {
        AbilitySystemComponent->AddAttributeSetSubobject(HealthSet);
    }
}

UAbilitySystemComponent* AGABaseCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AGABaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    // 1) Ініціалізація GAS
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
    }

    // 2) Видаємо аптечку як ability (тільки сервер)
    if (HasAuthority() && AbilitySystemComponent && MedkitAbilityClass)
    {
        AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(MedkitAbilityClass, 1, 0));
    }

    // 3) Ініціалізуємо атрибути
    InitializeAttributes();

  
    if (IsLocallyControlled() && HealthHUDClass)
    {
        HealthHUDInstance = CreateWidget<UGAHealthHUDWidget>(GetWorld(), HealthHUDClass);
        if (HealthHUDInstance)
        {
            HealthHUDInstance->AddToViewport();
            HealthHUDInstance->InitWithASC(AbilitySystemComponent);
        }
    }
}

void AGABaseCharacter::InitializeAttributes()
{
    if (HealthSet)
    {
        HealthSet->SetMaxHealth(100.f);
        HealthSet->SetHealth(50.f);
       // HealthSet->SetHealth(HealthSet->GetMaxHealth());
    }
}

void AGABaseCharacter::UseMedkit()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("UseMedkit CALLED"));
    }

    if (!AbilitySystemComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("ASC is NULL"));
        return;
    }

    if (!MedkitAbilityClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("MedkitAbilityClass is NULL"));
        return;
    }

    const bool bHasSpec =
        (AbilitySystemComponent->FindAbilitySpecFromClass(MedkitAbilityClass) != nullptr);

    const float Before =
        AbilitySystemComponent->GetNumericAttribute(UGAHealthSet::GetHealthAttribute());

    const bool bActivated =
        AbilitySystemComponent->TryActivateAbilityByClass(MedkitAbilityClass);

    const float After =
        AbilitySystemComponent->GetNumericAttribute(UGAHealthSet::GetHealthAttribute());

    UE_LOG(LogTemp, Warning, TEXT("HasSpec=%d Activated=%d Health: %f -> %f"),
        (int32)bHasSpec, (int32)bActivated, Before, After);
}