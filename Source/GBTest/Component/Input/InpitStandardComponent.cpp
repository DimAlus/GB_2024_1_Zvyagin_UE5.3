#include "./InpitStandardComponent.h"
#include "../../Character/GameCharacter.h"

UInpitStandardComponent::UInpitStandardComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UInpitStandardComponent::BeginPlay() {
	Super::BeginPlay();
}

void UInpitStandardComponent::Binding(UEnhancedInputComponent* inputComponent) {
	Super::Binding(inputComponent);
	// Jumping
	bingingHandles.Add(
		inputComponent->BindAction(
			this->data.JumpAction, ETriggerEvent::Started, this, &UInpitStandardComponent::JumpStart
		).GetHandle()
	);
	bingingHandles.Add(
		inputComponent->BindAction(
			this->data.JumpAction, ETriggerEvent::Completed, this, &UInpitStandardComponent::JumpEnd
		).GetHandle()
	);

	// Moving
	bingingHandles.Add(
		inputComponent->BindAction(
			this->data.MoveAction, ETriggerEvent::Triggered, this, &UInpitStandardComponent::Move
		).GetHandle()
	);

	// Looking
	bingingHandles.Add(
		inputComponent->BindAction(
			this->data.LookAction, ETriggerEvent::Triggered, this, &UInpitStandardComponent::Look
		).GetHandle()
	);

	// Scrolling
	bingingHandles.Add(
		inputComponent->BindAction(
			this->data.ScrollAction, ETriggerEvent::Triggered, this, &UInpitStandardComponent::Scroll
		).GetHandle()
	);
}

void UInpitStandardComponent::Move(const FInputActionValue& Value) {
	if (AGameCharacter* character = this->GetCharacter()) {
		// input is a Vector2D
		FVector2D MovementVector = Value.Get<FVector2D>();
		character->GetGameMovementComponent()->Move(MovementVector);
	}
}

void UInpitStandardComponent::JumpStart(const FInputActionValue& Value) {
	if (AGameCharacter* character = this->GetCharacter()) {
		character->GetGameMovementComponent()->Jump();
	}
}

void UInpitStandardComponent::JumpEnd(const FInputActionValue& Value) {
	if (AGameCharacter* character = this->GetCharacter()) {
		character->GetGameMovementComponent()->JumpStop();
	}
}

void UInpitStandardComponent::Scroll(const FInputActionValue& Value) {
	if (AGameCharacter* character = this->GetCharacter()) {
		float direction = Value.Get<float>();
		character->GetGameCameraComponent()->ZoomIncr(direction);
	}
}

void UInpitStandardComponent::Look(const FInputActionValue& Value) {
	if (AGameCharacter* character = this->GetCharacter()) {
		// input is a Vector2D
		FVector2D LookAxisVector = Value.Get<FVector2D>();
		character->GetGameCameraComponent()->LookTo(LookAxisVector);
	}
}
