// Fill out your copyright notice in the Description page of Project Settings.


#include "GABaseCharacter.h"
#include "GAAttributeSet.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystemComponent.h"

// Sets default values
AGABaseCharacter::AGABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Створюємо AbilitySystemComponent
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true); // для мультиплеєру
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	// Створюємо AttributeSet

	UPROPERTY()
	UGAAttributeSet* AttributeSetBase;
	
	AttributeSetBase = CreateDefaultSubobject<UGAAttributeSet>(TEXT("AttributeSetBase"));

}

// Called when the game starts or when spawned
void AGABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AGABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
