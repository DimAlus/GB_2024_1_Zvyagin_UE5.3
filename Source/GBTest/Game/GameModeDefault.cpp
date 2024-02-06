// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModeDefault.h"
#include "../Character/GameCharacter.h"
#include "../Service/SocialService.h"
#include "UObject/ConstructorHelpers.h"

AGameModeDefault::AGameModeDefault()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Character/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AGameModeDefault::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	USocialService::GetService().ClearService();
}
