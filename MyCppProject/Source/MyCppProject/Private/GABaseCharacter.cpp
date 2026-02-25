// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.

#include "GABaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GAHealthSet.h"

#include "GameplayAbilitySpec.h" // для FGameplayAbilitySpec

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
}

void AGABaseCharacter::InitializeAttributes()
{
    if (HealthSet)
    {
        // тимчасово: стартові значення
        HealthSet->SetMaxHealth(100.f);
        HealthSet->SetHealth(HealthSet->GetMaxHealth());
    }
}

void AGABaseCharacter::UseMedkit()
{
    if (AbilitySystemComponent && MedkitAbilityClass)
    {
        AbilitySystemComponent->TryActivateAbilityByClass(MedkitAbilityClass);
    }
}