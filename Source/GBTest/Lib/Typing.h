// Fill out your copyright notice in the Description page of Project Settings.
#pragma once


#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InputAction.h"
#include "Styling/SlateBrush.h"

#include "Typing.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateComponents, Log, All);

class AGameCharacter;
class AProjectileBase;

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

UENUM(BlueprintType)
enum class ETypeDamage : uint8 {
	Damage UMETA(DisplayName = "Damege")
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Shoot1Action { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* Shoot2Action { nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* RelocateAction { nullptr };
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


USTRUCT(BlueprintType)
struct FHealthComponentInitializer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
	float HealthRegeneration = 0.f;
};



USTRUCT(BlueprintType)
struct FProjectileInitializer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	float Speed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	float Gravity = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	float DespawnTime = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	bool isRadial = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	float Radius = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	bool DestroyOnTouch = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	int CountTouch = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
	TSet<ERelations> TargetRelations = {};

};


USTRUCT(BlueprintType)
struct FWeaponComponentInitializer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	float Cooldown = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	float Radius = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	float MaxLength = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	FVector ProjectileSpawnLocation = {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	FProjectileInitializer ProjectileInitializer = {};

};



USTRUCT(BlueprintType)
struct FIconInitializer {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Icon)
	FSlateBrush ForeTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Icon)
	FSlateBrush BackTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Icon)
	FText HelpText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Icon)
	bool IsProgress;
};
