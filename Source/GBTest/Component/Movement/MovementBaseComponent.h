// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Navigation/PathFollowingComponent.h"

#include "../../Lib/Typing.h"

#include "MovementBaseComponent.generated.h"

class AGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GBTEST_API UMovementBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMovementBaseComponent();

	UFUNCTION()
	virtual void Initialize(FMovementComponentInitializer& initializer);

	UFUNCTION()
	AGameCharacter* GetCharacter();

protected:
	UPROPERTY()
	FMovementComponentInitializer data;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Move(FVector2D direction);
	UFUNCTION(BlueprintCallable)
	virtual void Jump();
	UFUNCTION(BlueprintCallable)
	virtual void JumpStop();
	UFUNCTION(BlueprintCallable)
	virtual void Look(const FRotator& direction);

	UFUNCTION()
	virtual EPathFollowingRequestResult::Type AiMoveTo(FVector moveTo);
};
