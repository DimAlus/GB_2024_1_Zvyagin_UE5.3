#include "./MovementStandardComponent.h"
#include "../../Character/GameCharacter.h"

UMovementStandardComponent::UMovementStandardComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UMovementStandardComponent::Move(FVector2D direction) {
	if (AGameCharacter* character = this->GetCharacter()) {
		if (character->Controller != nullptr)
		{
			// find out which way is forward
			const FRotator Rotation = character->Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			// get right vector 
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement 
			character->AddMovementInput(ForwardDirection, direction.Y);
			character->AddMovementInput(RightDirection, direction.X);
		}
	}
}

void UMovementStandardComponent::Jump() {
	if (AGameCharacter* character = this->GetCharacter()) {
		character->Jump();
	}
}

void UMovementStandardComponent::JumpStop() {
}
