// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerControllerDefault.generated.h"

/**
 * 
 */
UCLASS()
class GBTEST_API APlayerControllerDefault : public APlayerController
{
	GENERATED_BODY()

public:
	void SetCamera(USpringArmComponent* newCamera);
	
};
