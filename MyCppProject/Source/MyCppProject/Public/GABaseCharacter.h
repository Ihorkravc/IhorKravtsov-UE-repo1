#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GABaseCharacter.generated.h"

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

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable, Category = "GAS|Medkit")
    void UseMedkit();

    UFUNCTION(BlueprintCallable, Category = "GAS|Medkit")
    void AddMedkit(int32 Amount = 1);

    UFUNCTION(BlueprintCallable, Category = "GAS|Setup")
    void SetInitialHealth(float NewHealth);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
    UAbilitySystemComponent* AbilitySystemComponent = nullptr;

    UPROPERTY()
    UGAHealthSet* HealthSet = nullptr;

    // ? Лічильник аптечок (реплікується)
    UPROPERTY(ReplicatedUsing = OnRep_MedkitCharges, BlueprintReadOnly, Category = "GAS|Medkit")
    int32 MedkitCharges = 0;

    // ? Ліміт аптечок (до 5)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Medkit")
    int32 MaxMedkitCharges = 5;

    UFUNCTION()
    void OnRep_MedkitCharges();

    // Ability, яка застосовує GE_Heal
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Abilities")
    TSubclassOf<UGameplayAbility> MedkitAbilityClass;

    // UI
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|UI")
    TSubclassOf<UGAHealthHUDWidget> HealthHUDClass;

    UPROPERTY(VisibleInstanceOnly, Category = "GAS|UI")
    UGAHealthHUDWidget* HealthHUDInstance = nullptr;

    void InitializeAttributes();
    void UpdateMedkitHUD();

    // RPC (щоб клієнт міг просити сервер)
    UFUNCTION(Server, Reliable)
    void ServerUseMedkit();

    UFUNCTION(Server, Reliable)
    void ServerAddMedkit(int32 Amount);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};