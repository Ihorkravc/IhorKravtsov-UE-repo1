// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GAHealthHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYCPPPROJECT_API UGAHealthHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // ¬икличемо п≥сл€ CreateWidget, щоб прив'€зати UI до ASC
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

    // “€гнемо поточн≥ значенн€ ≥ кидаЇмо в BP-≥вент
    void BroadcastCurrentValues();

    // –еал≥зуЇш у WBP (Update progress bar/text)
    UFUNCTION(BlueprintImplementableEvent, Category = "GAS|UI")
    void OnHealthChanged(float NewHealth, float NewMaxHealth);
};

