#include "./MovementBaseComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Character/GameCharacter.h"


UMovementBaseComponent::UMovementBaseComponent(){
	PrimaryComponentTick.bCanEverTick = false;
}

void UMovementBaseComponent::Initialize(FMovementComponentInitializer& initializer) {
	this->data = initializer;
	if (AGameCharacter* character = this->GetCharacter()) {
		UCharacterMovementComponent* movement = character->GetCharacterMovement();
		movement->JumpZVelocity = data.JumpZVelocity;
		movement->AirControl = data.AirControl;
		movement->MaxWalkSpeed = data.MaxWalkSpeed;
		movement->MinAnalogWalkSpeed = data.MinAnalogWalkSpeed;
		movement->BrakingDecelerationWalking = data.BrakingDecelerationWalking;
		movement->BrakingDecelerationFalling = 0.f;
	}
}

AGameCharacter* UMovementBaseComponent::GetCharacter() {
	AGameCharacter* character = Cast<AGameCharacter>(this->GetOwner());
	if (character) {
		return character;
	}
	UE_LOG(LogTemplateComponents, Error, TEXT("'%s' Failed to find an Owner of Movement Component! Owner: '%s'"), *GetNameSafe(this), *GetOwner()->GetName());
	return nullptr;
}

void UMovementBaseComponent::Move(FVector2D direction) {
	// Abstract Function
}

void UMovementBaseComponent::Jump() {
	// Abstract Function
}

void UMovementBaseComponent::JumpStop() {
	// Abstract Function
}

void UMovementBaseComponent::Look(const FRotator& direction) {
	// Abstract Function
}

EPathFollowingRequestResult::Type UMovementBaseComponent::AiMoveTo(FVector moveTo) {
	return EPathFollowingRequestResult::Type::Failed;
}

