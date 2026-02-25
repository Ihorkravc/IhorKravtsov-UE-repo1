// Fill out your copyright notice in the Description page of Project Settings.


#include "GAHealthHUDWidget.h"
#include "AbilitySystemComponent.h"
#include "GAHealthSet.h"

void UGAHealthHUDWidget::InitWithASC(UAbilitySystemComponent* InASC)
{
    // якщо вже були прив'язані - відв'яжемось
    UnbindFromAttributes();

    ASC = InASC;
    if (!ASC)
    {
        return;
    }

    BindToAttributes();
    BroadcastCurrentValues(); // одразу покажемо стартові значення
}

void UGAHealthHUDWidget::BindToAttributes()
{
    if (!ASC) return;

    // Health changed
    HealthChangedHandle =
        ASC->GetGameplayAttributeValueChangeDelegate(UGAHealthSet::GetHealthAttribute())
        .AddLambda([this](const FOnAttributeChangeData& Data)
            {
                BroadcastCurrentValues();
            });

    // MaxHealth changed
    MaxHealthChangedHandle =
        ASC->GetGameplayAttributeValueChangeDelegate(UGAHealthSet::GetMaxHealthAttribute())
        .AddLambda([this](const FOnAttributeChangeData& Data)
            {
                BroadcastCurrentValues();
            });
}

void UGAHealthHUDWidget::UnbindFromAttributes()
{
    if (!ASC) return;

    if (HealthChangedHandle.IsValid())
    {
        ASC->GetGameplayAttributeValueChangeDelegate(UGAHealthSet::GetHealthAttribute())
            .Remove(HealthChangedHandle);
        HealthChangedHandle.Reset();
    }

    if (MaxHealthChangedHandle.IsValid())
    {
        ASC->GetGameplayAttributeValueChangeDelegate(UGAHealthSet::GetMaxHealthAttribute())
            .Remove(MaxHealthChangedHandle);
        MaxHealthChangedHandle.Reset();
    }
}

void UGAHealthHUDWidget::BroadcastCurrentValues()
{
    if (!ASC) return;

    const float Health = ASC->GetNumericAttribute(UGAHealthSet::GetHealthAttribute());
    const float MaxHealth = ASC->GetNumericAttribute(UGAHealthSet::GetMaxHealthAttribute());

    OnHealthChanged(Health, MaxHealth);
}

void UGAHealthHUDWidget::NativeDestruct()
{
    UnbindFromAttributes();
    ASC = nullptr;

    Super::NativeDestruct();
}
