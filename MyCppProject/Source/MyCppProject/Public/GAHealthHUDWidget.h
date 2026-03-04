#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Delegates/Delegate.h"
#include "GAHealthHUDWidget.generated.h"

class UAbilitySystemComponent;

UCLASS()
class MYCPPPROJECT_API UGAHealthHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "GAS|UI")
    void InitWithASC(UAbilitySystemComponent* InASC);

protected:
    virtual void NativeDestruct() override;

    UPROPERTY()
    UAbilitySystemComponent* ASC = nullptr;

    FDelegateHandle HealthChangedHandle;
    FDelegateHandle MaxHealthChangedHandle;

    void BindToAttributes();
    void UnbindFromAttributes();

    UFUNCTION()
    void BroadcastCurrentValues();

    UFUNCTION(BlueprintImplementableEvent, Category = "GAS|UI")
    void OnHealthChanged(float NewHealth, float NewMaxHealth);
};