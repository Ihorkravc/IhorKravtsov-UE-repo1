// Fill out your copyright notice in the Description page of Project Settings.



#pragma once

#include "CoreMinimal.h"
#include "GAAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GAHealthSet.generated.h"

UCLASS()
class MYCPPPROJECT_API UGAHealthSet : public UGAAttributeSet
{
    GENERATED_BODY()

public:
    UGAHealthSet();

    // Атрибут здоров'я
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float Health;

    // Атрибут максимального здоров'я
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth;
};