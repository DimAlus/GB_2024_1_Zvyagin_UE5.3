// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InputAction.h"

#include "Typing.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateComponents, Log, All);

UCLASS()
class GBTEST_API UTyping : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FInputComponentInitializer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ScrollAction;
};


USTRUCT(BlueprintType)
struct FCameraComponentInitializer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Zoom)
	FVector2D ZoomLimits;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Zoom)
	float ZoomPerScroll;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Zoom)
	float ZoomMaxSpeed; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Zoom)
	float ZoomLenSlow;

};


USTRUCT(BlueprintType)
struct FMovementComponentInitializer {
	GENERATED_BODY()
public:


};