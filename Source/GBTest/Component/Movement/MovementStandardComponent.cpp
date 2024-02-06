#include "./MovementStandardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Character/GameCharacter.h"
#include "../../Service/SocialService.h"

UMovementStandardComponent::UMovementStandardComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UMovementStandardComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	// Set Max speed by direction movement and look
	if (AGameCharacter* character = this->GetCharacter()) {
		UCharacterMovementComponent* movement = character->GetCharacterMovement();

		float velocityYaw = movement->Velocity.Rotation().Yaw;
		float characterYaw = character->GetActorRotation().Yaw;
		float difference = std::max(velocityYaw, characterYaw) - std::min(velocityYaw, characterYaw);
		if (difference > 180) {
			difference -= 360;
		}
		difference = abs(difference);

		if (difference > data.MinBackAngle) {
			movement->MaxWalkSpeed = data.MaxBackSpeed;
		}
		else {
			movement->MaxWalkSpeed = data.MaxWalkSpeed;
		}
	}
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

void UMovementStandardComponent::Look(const FRotator& direction) {
	if (AGameCharacter* character = this->GetCharacter()) {
		character->SetActorRotation(FRotator(0, direction.Yaw, 0));
	}
}