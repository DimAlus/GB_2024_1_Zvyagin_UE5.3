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
	if (IsValid(this->CurrentInputComponent)) {
		// Jumping
		bingingHandles.Add(
			this->CurrentInputComponent->BindAction(
				this->data.JumpAction, ETriggerEvent::Started, this, &UInpitStandardComponent::JumpStart
			).GetHandle()
		);
		bingingHandles.Add(
			this->CurrentInputComponent->BindAction(
				this->data.JumpAction, ETriggerEvent::Completed, this, &UInpitStandardComponent::JumpEnd
			).GetHandle()
		);

		// Moving
		bingingHandles.Add(
			this->CurrentInputComponent->BindAction(
				this->data.MoveAction, ETriggerEvent::Triggered, this, &UInpitStandardComponent::Move
			).GetHandle()
		);

		// Looking
		bingingHandles.Add(
			this->CurrentInputComponent->BindAction(
				this->data.LookAction, ETriggerEvent::Triggered, this, &UInpitStandardComponent::Look
			).GetHandle()
		);

		// Scrolling
		bingingHandles.Add(
			this->CurrentInputComponent->BindAction(
				this->data.ScrollAction, ETriggerEvent::Triggered, this, &UInpitStandardComponent::Scroll
			).GetHandle()
		);

		// Shoot1
		bingingHandles.Add(
			this->CurrentInputComponent->BindAction(
				this->data.Shoot1Action, ETriggerEvent::Started, this, &UInpitStandardComponent::Shoot1Start
			).GetHandle()
		);
		bingingHandles.Add(
			this->CurrentInputComponent->BindAction(
				this->data.Shoot1Action, ETriggerEvent::Completed, this, &UInpitStandardComponent::Shoot1End
			).GetHandle()
		);

		// Shoot2
		bingingHandles.Add(
			this->CurrentInputComponent->BindAction(
				this->data.Shoot2Action, ETriggerEvent::Started, this, &UInpitStandardComponent::Shoot2Start
			).GetHandle()
		);
		bingingHandles.Add(
			this->CurrentInputComponent->BindAction(
				this->data.Shoot2Action, ETriggerEvent::Completed, this, &UInpitStandardComponent::Shoot2End
			).GetHandle()
		);

		// Relocation
		bingingHandles.Add(
			this->CurrentInputComponent->BindAction(
				this->data.RelocateAction, ETriggerEvent::Started, this, &UInpitStandardComponent::Relocate
			).GetHandle()
		);
	}
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

void UInpitStandardComponent::Shoot1Start(const FInputActionValue& Value) {
	if (AGameCharacter* character = this->GetCharacter()) {
		character->GetGameWeaponMainComponent()->ShootStart();
	}
}

void UInpitStandardComponent::Shoot1End(const FInputActionValue& Value) {
	if (AGameCharacter* character = this->GetCharacter()) {
		character->GetGameWeaponMainComponent()->ShootEnd();
	}
}

void UInpitStandardComponent::Shoot2Start(const FInputActionValue& Value) {
	if (AGameCharacter* character = this->GetCharacter()) {
		character->GetGameWeaponAddComponent()->ShootStart();
	}
}

void UInpitStandardComponent::Shoot2End(const FInputActionValue& Value) {
	if (AGameCharacter* character = this->GetCharacter()) {
		character->GetGameWeaponAddComponent()->ShootEnd();
	}
}

void UInpitStandardComponent::Relocate(const FInputActionValue& Value) {
	if (AGameCharacter* character = this->GetCharacter()) {
		character->GetGameRelocationComponent()->Shoot();
	}
}
