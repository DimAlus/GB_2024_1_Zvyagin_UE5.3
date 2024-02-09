#include "./RelocationBaseComponent.h"
#include "../../Character/GameCharacter.h"

URelocationBaseComponent::URelocationBaseComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void URelocationBaseComponent::Initialize(FRelocationComponentInitializer& initializer) {
	this->data = initializer;
}

AGameCharacter* URelocationBaseComponent::GetCharacter() {
	AGameCharacter* character = Cast<AGameCharacter>(this->GetOwner());
	if (character) {
		return character;
	}
	UE_LOG(LogTemplateComponents, Error, TEXT("'%s' Failed to find an Owner of Movement Component! Owner: '%s'"), *GetNameSafe(this), *GetOwner()->GetName());
	return nullptr;
}

void URelocationBaseComponent::Relocate() {
	// Abstract Function
}

void URelocationBaseComponent::Activation() {
	// Abstract Function
}

void URelocationBaseComponent::Deactivation() {
	// Abstract Function
}
