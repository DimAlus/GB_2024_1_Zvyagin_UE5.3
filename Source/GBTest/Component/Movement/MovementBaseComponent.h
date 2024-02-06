// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../../Lib/Typing.h"

#include "MovementBaseComponent.generated.h"

class AGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GBTEST_API UMovementBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementBaseComponent();

	UFUNCTION()
	virtual void Initialize(FMovementComponentInitializer& initializer);

	UFUNCTION()
	AGameCharacter* GetCharacter();

protected:
	UPROPERTY()
	FMovementComponentInitializer data;

public:
	UFUNCTION()
	virtual void Move(FVector2D direction);
	UFUNCTION()
	virtual void Jump();
	UFUNCTION()
	virtual void JumpStop();
	UFUNCTION()
	virtual void Look(const FRotator& direction);

};
