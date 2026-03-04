#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GABaseCharacter.generated.h"

// Forward declarations
class UAbilitySystemComponent;
class UGAHealthSet;
class UGameplayAbility;
class UGAHealthHUDWidget;

UCLASS()
class MYCPPPROJECT_API AGABaseCharacter
    : public ACharacter
    , public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    AGABaseCharacter();

    // GAS interface
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    // Виклик аптечки (можна викликати з Blueprint)
    UFUNCTION(BlueprintCallable, Category = "GAS|Medkit")
    void UseMedkit();

protected:
    virtual void BeginPlay() override;

    // Ability System Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
    UAbilitySystemComponent* AbilitySystemComponent = nullptr;

    // Health Attribute Set
    UPROPERTY()
    UGAHealthSet* HealthSet = nullptr;

    // Яку ability видати персонажу як "аптечку" (в Editor ставиш BP_GA_Medkit)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Abilities")
    TSubclassOf<UGameplayAbility> MedkitAbilityClass;

    void InitializeAttributes();

    // HUD клас (який будемо ставити в BP)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|UI")
    TSubclassOf<UGAHealthHUDWidget> HealthHUDClass;

    // Інстанс віджета
    UPROPERTY(VisibleInstanceOnly, Category = "GAS|UI")
    UGAHealthHUDWidget* HealthHUDInstance = nullptr;
};