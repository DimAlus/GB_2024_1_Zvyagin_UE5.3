// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeDefault.generated.h"

UCLASS(minimalapi)
class AGameModeDefault : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameModeDefault();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};



