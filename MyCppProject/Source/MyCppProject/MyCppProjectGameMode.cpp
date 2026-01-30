// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyCppProjectGameMode.h"
#include "MyCppProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyCppProjectGameMode::AMyCppProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
