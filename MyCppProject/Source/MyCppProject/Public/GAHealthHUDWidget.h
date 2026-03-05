#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GAHealthHUDWidget.generated.h"

class UAbilitySystemComponent;

UCLASS()
class MYCPPPROJECT_API UGAHealthHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "GAS|UI")
    void InitWithASC(UAbilitySystemComponent* InASC);

    // ✅ Публічна функція, яку можна викликати з Character
    UFUNCTION(BlueprintCallable, Category = "GAS|UI")
    void UpdateMedkit(int32 NewCharges, int32 InMaxCharges);

protected:
    virtual void NativeDestruct() override;

    UPROPERTY()
    UAbilitySystemComponent* ASC = nullptr;

    FDelegateHandle HealthChangedHandle;
    FDelegateHandle MaxHealthChangedHandle;

    void BindToAttributes();
    void UnbindFromAttributes();
    void BroadcastCurrentValues();

    UFUNCTION(BlueprintImplementableEvent, Category = "GAS|UI")
    void OnHealthChanged(float NewHealth, float NewMaxHealth);

    // ⚠️ Лишаємо protected: (це ок), але більше НЕ викликаємо напряму з персонажа
    UFUNCTION(BlueprintImplementableEvent, Category = "GAS|UI")
    void OnMedkitChanged(int32 NewCharges, int32 MaxCharges);
};