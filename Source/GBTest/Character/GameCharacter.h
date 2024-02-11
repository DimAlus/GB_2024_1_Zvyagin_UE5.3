#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AIController.h"
#include "GameplayTask.h"

#include "../Lib/Typing.h"
#include "../Component/Input/InpitBaseComponent.h"
#include "../Component/Camera/CameraBaseComponent.h"
#include "../Component/Movement/MovementBaseComponent.h"
#include "../Component/Socium/SociumBaseComponent.h"
#include "../Component/Weapon/RelocationStandardComponent.h"
#include "../Component/Health/HealthBaseComponent.h"
#include "../Component/Weapon/WeaponBaseComponent.h"

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

	UFUNCTION()
	UActorComponent* CreateComponent(TSubclassOf<UActorComponent> cls, UObject* ownerObj = nullptr);

	virtual void Destroyed() override;
protected:
	UFUNCTION()
	void InitializeComponents();
	UFUNCTION()
	void InitializePlayer();
	UFUNCTION(BlueprintNativeEvent)
	void InitializeAfter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<AAIController> AIGameControllerClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FName AIControllerFolder;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FName ControllerFolder;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FName CharacterFolder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	AAIController* AIController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	AController* PlayerController;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UInpitBaseComponent* GameInputComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<UInpitBaseComponent> InputComponentClass = UInpitBaseComponent::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FInputComponentInitializer InputComponentInitializer;

	/** CameraComponent **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraBaseComponent* GameCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<UCameraBaseComponent> CameraComponentClass = UCameraBaseComponent::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FCameraComponentInitializer CameraComponentInitializer;

	/** MovementComponent **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMovementBaseComponent* GameMovementComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<UMovementBaseComponent> MovementComponentClass = UMovementBaseComponent::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FMovementComponentInitializer MovementComponentInitializer;

	/** SociumComponent **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USociumBaseComponent* GameSociumComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<USociumBaseComponent> SociumComponentClass = USociumBaseComponent::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FSociumComponentInitializer SociumComponentInitializer;

	/** HealthComponent **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHealthBaseComponent* GameHealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<UHealthBaseComponent> HealthComponentClass = UHealthBaseComponent::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FHealthComponentInitializer HealthComponentInitializer;
			


	/** RelocationComponent **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	URelocationStandardComponent* GameRelocationComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<URelocationStandardComponent> RelocationComponentClass = URelocationStandardComponent::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FWeaponComponentInitializer RelocationComponentInitializer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FIconInitializer RelocationIconInitializer;

	/** MainWeaponComponent **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWeaponBaseComponent* GameWeaponMainComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<UWeaponBaseComponent> WeaponMainComponentClass = UWeaponBaseComponent::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FWeaponComponentInitializer WeaponMainComponentInitializer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FIconInitializer WeaponMainIconInitializer;

	/** AddWeaponComponent **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWeaponBaseComponent* GameWeaponAddComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	TSubclassOf<UWeaponBaseComponent> WeaponAddComponentClass = UWeaponBaseComponent::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FWeaponComponentInitializer WeaponAddComponentInitializer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components Initialization")
	FIconInitializer WeaponAddIconInitializer;
protected:	
	// To add mapping context
	virtual void BeginPlay();

public:
	UFUNCTION()
	void SetPlayerController(AController* newController);

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE void SetFollowCamera(UCameraComponent* newCamera) { this->FollowCamera = newCamera; }
	/** Returns MappingContext subobject **/
	FORCEINLINE class UInputMappingContext* GetMappingContext() const { return DefaultMappingContext; }
	/** Returns InputComponent subobject **/
	FORCEINLINE class UInpitBaseComponent* GetGameInputComponent() const { return GameInputComponent; }
	/** Returns InputComponent subobject **/
	FORCEINLINE class UCameraBaseComponent* GetGameCameraComponent() const { return GameCameraComponent; }
	/** Returns InputComponent subobject **/
	FORCEINLINE class UMovementBaseComponent* GetGameMovementComponent() const { return GameMovementComponent; }
	/** Returns InputComponent subobject **/
	FORCEINLINE class USociumBaseComponent* GetGameSociumComponent() const { return GameSociumComponent; }
	/** Returns HealthComponent subobject **/
	FORCEINLINE class UHealthBaseComponent* GetGameHealthComponent() const { return GameHealthComponent; }
	/** Returns InputComponent subobject **/
	FORCEINLINE class URelocationStandardComponent* GetGameRelocationComponent() const { return GameRelocationComponent; }
	/** Returns HealthComponent subobject **/
	FORCEINLINE class UWeaponBaseComponent* GetGameWeaponMainComponent() const { return GameWeaponMainComponent; }
	/** Returns HealthComponent subobject **/
	FORCEINLINE class UWeaponBaseComponent* GetGameWeaponAddComponent() const { return GameWeaponAddComponent; }

};

