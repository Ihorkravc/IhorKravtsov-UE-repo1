#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GABaseCharacter.generated.h"

// Forward declarations
class UAbilitySystemComponent;
class UGAHealthSet;
class UGameplayAbility;

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

    // ¬иклик аптечки (можна викликати з Blueprint)
    UFUNCTION(BlueprintCallable, Category = "GAS|Medkit")
    void UseMedkit();

protected:
    virtual void BeginPlay() override;

    // Ability System Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
    UAbilitySystemComponent* AbilitySystemComponent;

    // Health Attribute Set
    UPROPERTY()
    UGAHealthSet* HealthSet;

    // яку ability видати персонажу €к "аптечку" (в Editor ставиш BP_GA_Medkit)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Abilities")
    TSubclassOf<UGameplayAbility> MedkitAbilityClass;

    void InitializeAttributes();
};