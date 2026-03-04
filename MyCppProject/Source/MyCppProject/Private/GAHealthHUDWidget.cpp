#include "GAHealthHUDWidget.h"
#include "AbilitySystemComponent.h"
#include "GAHealthSet.h"
#include "TimerManager.h"
#include "Engine/World.h"

void UGAHealthHUDWidget::InitWithASC(UAbilitySystemComponent* InASC)
{
    UnbindFromAttributes();

    ASC = InASC;
    if (!ASC)
    {
        return;
    }

    BindToAttributes();

    // ? Стартове оновлення — на наступний тик, коли ProgressBar точно існує
    if (UWorld* W = GetWorld())
    {
        W->GetTimerManager().SetTimerForNextTick(
            FTimerDelegate::CreateUObject(this, &UGAHealthHUDWidget::BroadcastCurrentValues)
        );
    }
}

void UGAHealthHUDWidget::BindToAttributes()
{
    if (!ASC) return;

    HealthChangedHandle =
        ASC->GetGameplayAttributeValueChangeDelegate(UGAHealthSet::GetHealthAttribute())
        .AddLambda([this](const FOnAttributeChangeData& Data)
            {
                BroadcastCurrentValues();
            });

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