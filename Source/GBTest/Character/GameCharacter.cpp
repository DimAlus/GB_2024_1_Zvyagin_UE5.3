// Copyright Epic Games, Inc. All Rights Reserved.

#include "./GameCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);
//#define CAMERA_TEST

//////////////////////////////////////////////////////////////////////////
// AGameCharacter

AGameCharacter::AGameCharacter()
{
	AIControllerClass = nullptr;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them

#ifdef CAMERA_TEST
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
#endif // CAMERA_TEST

}

UActorComponent* AGameCharacter::CreateComponent(TSubclassOf<UActorComponent> cls, UObject* ownerObj) {
	if (!ownerObj) {
		ownerObj = this;
	}
	UActorComponent* component = NewObject<UActorComponent>(ownerObj, cls);
	check(component);
	return component;
}

void AGameCharacter::Destroyed() {
	if (IsValid(AIController)) {
		AIController->Destroy();
	}
}

void AGameCharacter::InitializeComponents() {
	this->SetFolderPath(CharacterFolder);

	AIController = GetWorld()->SpawnActor<AAIController>(AIGameControllerClass);
	AIController->SetFolderPath(AIControllerFolder);

	if (this->Controller) {
		PlayerController = Controller;
		Controller->SetFolderPath(ControllerFolder);
	}
	else {
		AIController->Possess(this);
		//this->PossessedBy(AIController);
	}

#ifndef CAMERA_TEST

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = Cast<USpringArmComponent>(this->CreateComponent(USpringArmComponent::StaticClass()));
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->SetRelativeLocation(FVector(0, 0, 100));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->RegisterComponent();

	if (PlayerController) {
		// Create a follow camera
		FollowCamera = Cast<UCameraComponent>(this->CreateComponent(UCameraComponent::StaticClass(), CameraBoom));
		FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
		FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
		FollowCamera->RegisterComponent();
		//FollowCamera->AttachToComponent(CameraBoom, );
	}
#endif // CAMERA_TEST

	this->GameInputComponent = Cast<UInpitBaseComponent>(this->CreateComponent(this->InputComponentClass));
	this->GameInputComponent->RegisterComponent();
	this->GameInputComponent->Initialize(this->InputComponentInitializer);

	this->GameCameraComponent = Cast<UCameraBaseComponent>(this->CreateComponent(this->CameraComponentClass));
	this->GameCameraComponent->RegisterComponent();
	this->GameCameraComponent->Initialize(this->CameraComponentInitializer);

	this->GameMovementComponent = Cast<UMovementBaseComponent>(this->CreateComponent(this->MovementComponentClass));
	this->GameMovementComponent->RegisterComponent();
	this->GameMovementComponent->Initialize(this->MovementComponentInitializer);

	this->GameSociumComponent = Cast<USociumBaseComponent>(this->CreateComponent(this->SociumComponentClass));
	this->GameSociumComponent->RegisterComponent();
	this->GameSociumComponent->Initialize(this->SociumComponentInitializer);

	this->GameHealthComponent = Cast<UHealthBaseComponent>(this->CreateComponent(this->HealthComponentClass));
	this->GameHealthComponent->RegisterComponent();
	this->GameHealthComponent->Initialize(this->HealthComponentInitializer);


	this->GameRelocationComponent = Cast<URelocationStandardComponent>(this->CreateComponent(this->RelocationComponentClass));
	this->GameRelocationComponent->RegisterComponent();
	this->GameRelocationComponent->Initialize(this->RelocationComponentInitializer);
	this->GameRelocationComponent->Deactivation();

	this->GameWeaponMainComponent = Cast<UWeaponBaseComponent>(this->CreateComponent(this->WeaponMainComponentClass));
	this->GameWeaponMainComponent->RegisterComponent();
	this->GameWeaponMainComponent->Initialize(this->WeaponMainComponentInitializer);

	this->GameWeaponAddComponent = Cast<UWeaponBaseComponent>(this->CreateComponent(this->WeaponAddComponentClass));
	this->GameWeaponAddComponent->RegisterComponent();
	this->GameWeaponAddComponent->Initialize(this->WeaponAddComponentInitializer);
}

void AGameCharacter::InitializePlayer() {
	this->GameSociumComponent->ChangeGroup(ESocialGroup::Player);
	this->GameRelocationComponent->Activation();
}

void AGameCharacter::InitializeAfter_Implementation() {
}

void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	this->InitializeComponents();
	if (PlayerController) {
		this->InitializePlayer();
	}
	InitializeAfter();
}

void AGameCharacter::SetPlayerController(AController* newController) {
	if (IsValid(newController)) {
		AIController->UnPossess();
		newController->Possess(this);
		PossessedBy(newController);
	}
	else {
		AIController->Possess(this);
		PossessedBy(AIController);
	}
}
