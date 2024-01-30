// Copyright Epic Games, Inc. All Rights Reserved.

#include "GBTestGameMode.h"
#include "../Character/GBTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGBTestGameMode::AGBTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
