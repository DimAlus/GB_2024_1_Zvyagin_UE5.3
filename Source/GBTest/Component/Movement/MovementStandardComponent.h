// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./MovementBaseComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "MovementStandardComponent.generated.h"

/**
 * 
 */
UCLASS()
class GBTEST_API UMovementStandardComponent : public UMovementBaseComponent
{
	GENERATED_BODY()

public:
	UMovementStandardComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:

	virtual void Move(FVector2D direction) override;
	virtual void Jump() override;
	virtual void JumpStop() override;
	virtual void Look(const FRotator& direction) override;

	virtual EPathFollowingRequestResult::Type AiMoveTo(FVector moveTo) override;
};
