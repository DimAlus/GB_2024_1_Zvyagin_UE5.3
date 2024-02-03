#include "./MovementBaseComponent.h"
#include "../../Character/GameCharacter.h"

UMovementBaseComponent::UMovementBaseComponent(){
	PrimaryComponentTick.bCanEverTick = false;
}

void UMovementBaseComponent::Initialize(FMovementComponentInitializer& initializer) {
	this->data = initializer;
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

