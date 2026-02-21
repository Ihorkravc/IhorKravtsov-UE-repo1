// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include"AbilitySystemInterface.h"
#include "GABaseCharacter.generated.h"

UCLASS()
class MYCPPPROJECT_API AGABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Gas component
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
    
	UAbilitySystemComponent* AbilitySystemComponent;
	
	//AtributeSet
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")	
	class UGAAttributeSet* AttributeSet;

	
	//IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

};
