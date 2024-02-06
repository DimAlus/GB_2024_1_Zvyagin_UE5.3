// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./CameraBaseComponent.h"
#include "CameraStandardComponent.generated.h"

/**
 * 
 */
UCLASS()
class GBTEST_API UCameraStandardComponent : public UCameraBaseComponent
{
	GENERATED_BODY()
public:
	UCameraStandardComponent();

	virtual void Initialize(FCameraComponentInitializer& initializer) override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	UPROPERTY()
	float ZoomBoost; // Ускорение
	UPROPERTY()
	float ZoomSpeed; // Текущая скорость 
	UPROPERTY()
	float ZoomLen; // Текущая позиция зума
	UPROPERTY()
	float ZoomTargetLen; // Целевая позиция зума
	UPROPERTY()
	float ZoomLimDelta;

	UPROPERTY()
	bool ZoomIsSlowing = false;
	UPROPERTY()
	float ZoomSlowing;

public:

	virtual void LookTo(const FVector2D& lookAxisVector) override;
	virtual void ZoomAt(float zoom) override;
	virtual void ZoomTo(float zoom) override;
	virtual void ZoomAtPer(float persents) override;
	virtual void ZoomToPer(float persents) override;
	virtual void ZoomIncr(int direction) override;

	virtual FVector GetCameraPosition() override;
	virtual FVector GetCameraLookVector() override;
};
