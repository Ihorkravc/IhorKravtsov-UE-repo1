// Fill out your copyright notice in the Description page of Project Settings.


#include "GAAbility_Medkit.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"

UGAAbility_Medkit::UGAAbility_Medkit()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGAAbility_Medkit::ActivateAbility(
    const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    // поки не працюЇ кул давн Ч можна прибрати прибрати CommitAbility.
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid() || !HealEffect)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();

    FGameplayEffectContextHandle Ctx = ASC->MakeEffectContext();
    Ctx.AddSourceObject(GetAvatarActorFromActorInfo());

    FGameplayEffectSpecHandle Spec = ASC->MakeOutgoingSpec(HealEffect, EffectLevel, Ctx);
    if (Spec.IsValid())
    {
        ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
