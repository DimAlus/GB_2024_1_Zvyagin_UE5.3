// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"

#include "../Lib/Typing.h"
#include "../Component/Input/InpitBaseComponent.h"
#include "../Component/Camera/CameraBaseComponent.h"
#include "../Component/Movement/MovementBaseComponent.h"

#include "GameCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGameCharacter();
	

protected:
	UFUNCTION()
	UActorComponent* CreateComponent(TSubclassOf<UActorComponent> cls);
	UFUNCTION()
	void InitializeComponents();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** InputComponent **/
	UPROPERTY()
	UInpitBaseComponent* GameInputComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<UInpitBaseComponent> InputComponentClass = UInpitBaseComponent::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FInputComponentInitializer InputComponentInitializer;

	/** CameraComponent **/
	UPROPERTY()
	UCameraBaseComponent* GameCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<UCameraBaseComponent> CameraComponentClass = UCameraBaseComponent::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FCameraComponentInitializer CameraComponentInitializer;

	/** MovementComponent **/
	UPROPERTY()
	UMovementBaseComponent* GameMovementComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<UMovementBaseComponent> MovementComponentClass = UMovementBaseComponent::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FMovementComponentInitializer MovementComponentInitializer;

			

protected:	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	/** Returns MappingContext subobject **/
	FORCEINLINE class UInputMappingContext* GetMappingContext() const { return DefaultMappingContext; }
	/** Returns InputComponent subobject **/
	FORCEINLINE class UInpitBaseComponent* GetGameInputComponent() const { return GameInputComponent; }
	/** Returns InputComponent subobject **/
	FORCEINLINE class UCameraBaseComponent* GetGameCameraComponent() const { return GameCameraComponent; }
	/** Returns InputComponent subobject **/
	FORCEINLINE class UMovementBaseComponent* GetGameMovementComponent() const { return GameMovementComponent; }
};

