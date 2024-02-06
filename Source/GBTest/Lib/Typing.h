// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InputAction.h"

#include "Typing.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateComponents, Log, All);

class AGameCharacter;

UCLASS()
class GBTEST_API UTyping : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};

float VectorsAngle(const FVector& v1, const FVector& v2);



UENUM(BlueprintType)
enum class ESocialGroup : uint8 {
	Player UMETA(DisplayName = "Player"),
	Enemy UMETA(DisplayName = "Enemy"),
	Associate UMETA(DisplayName = "Associate")
};

UENUM(BlueprintType)
enum class ERelations : uint8 {
	Friend UMETA(DisplayName = "Friend"),
	Enemy UMETA(DisplayName = "Enemy"),
	Neutral UMETA(DisplayName = "Neutral")
};


USTRUCT(BlueprintType)
struct FInputComponentInitializer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* ScrollAction { nullptr };
};


USTRUCT(BlueprintType)
struct FCameraComponentInitializer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Zoom)
	FVector2D ZoomLimits { 200, 1000 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Zoom)
	float ZoomPerScroll { 0.2f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Zoom)
	float ZoomMaxSpeed { 1000 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Zoom)
	float ZoomLenSlow { 200 };

};


USTRUCT(BlueprintType)
struct FMovementComponentInitializer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Jump)
	float JumpZVelocity = 700.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Jump)
	float AirControl = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxWalkSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxRunSpeed = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxBackSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxRunAngle = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MinBackAngle = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MinAnalogWalkSpeed = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float BrakingDecelerationWalking = 2000.f;
};


USTRUCT(BlueprintType)
struct FSociumComponentInitializer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Socium)
	ESocialGroup DefaultGroup = ESocialGroup::Enemy;
};


// Map of ESocialGroup: ERelations structure
USTRUCT(BlueprintType)
struct FMap_SG_Rel {
	GENERATED_BODY()
public:
	FMap_SG_Rel() {};
	FMap_SG_Rel(TMap<ESocialGroup, ERelations> val) : Map(val) {};
	TMap<ESocialGroup, ERelations> Map;
};

// Set of AGameCharacter structure
USTRUCT(BlueprintType)
struct FSetChar {
	GENERATED_BODY()
public:
	FSetChar() {};
	FSetChar(TSet<AGameCharacter*> val) : Set(val) {};
	TSet<AGameCharacter*> Set;
};