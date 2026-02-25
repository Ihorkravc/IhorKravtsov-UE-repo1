// Fill out your copyright notice in the Description page of Project Settings.

#include "GAHealthSet.h"
#include "Net/UnrealNetwork.h"

UGAHealthSet::UGAHealthSet()
{
    // ²ν³φ³ΰλ³ηΰφ³ÿ ηνΰχενό
    Health = 100.f;
    MaxHealth = 100.f;
}

void UGAHealthSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGAHealthSet, Health, OldHealth);
}

void UGAHealthSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UGAHealthSet, MaxHealth, OldMaxHealth);
}

void UGAHealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UGAHealthSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UGAHealthSet, MaxHealth, COND_None, REPNOTIFY_Always);
}



