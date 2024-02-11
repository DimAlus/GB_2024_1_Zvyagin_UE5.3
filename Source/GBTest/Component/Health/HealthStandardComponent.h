// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./HealthBaseComponent.h"
#include "HealthStandardComponent.generated.h"

/**
 * 
 */
UCLASS()
class GBTEST_API UHealthStandardComponent : public UHealthBaseComponent
{
	GENERATED_BODY()

public:
	virtual void Initialize(FHealthComponentInitializer& initializer) override;

protected:
	float CurrentHealth;

public:
	virtual float GetHealth() override;
	virtual void TakeDamage(AGameCharacter* otherCharacter, ETypeDamage typeDamage, float power) override;
};
