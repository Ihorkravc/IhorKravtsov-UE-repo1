// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAGameplayAbility.h"
#include "GAAbility_Medkit.generated.h"

/**
 * 
 */
UCLASS()
class MYCPPPROJECT_API UGAAbility_Medkit : public UGAGameplayAbility
{
	GENERATED_BODY()

public:
    UGAAbility_Medkit();

protected:
    // —юди ми в BP п≥дставимо GE_Heal
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Medkit")
    TSubclassOf<UGameplayEffect> HealEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Medkit")
    float EffectLevel = 1.f;

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData
    ) override;
};
