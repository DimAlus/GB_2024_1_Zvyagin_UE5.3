#include "./HealthBaseComponent.h"
#include "../../Character/GameCharacter.h"

UHealthBaseComponent::UHealthBaseComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthBaseComponent::Initialize(FHealthComponentInitializer& initializer) {
	this->data = initializer;
}

AGameCharacter* UHealthBaseComponent::GetCharacter() {
	AGameCharacter* character = Cast<AGameCharacter>(this->GetOwner());
	if (character) {
		return character;
	}
	UE_LOG(LogTemplateComponents, Error, TEXT("'%s' Failed to find an Owner of Movement Component! Owner: '%s'"), *GetNameSafe(this), *GetOwner()->GetName());
	return nullptr;
}

float UHealthBaseComponent::GetHealth() {
	return 0.0f;
}

float UHealthBaseComponent::GetHealthPercents() {
	return GetHealth() / GetMaxHealth();
}

float UHealthBaseComponent::GetMaxHealth() {
	return data.MaxHealth;
}
