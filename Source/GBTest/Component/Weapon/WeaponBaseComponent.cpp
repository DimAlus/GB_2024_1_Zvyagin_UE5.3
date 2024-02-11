#include "./WeaponBaseComponent.h"
#include "../../Character/GameCharacter.h"

UWeaponBaseComponent::UWeaponBaseComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponBaseComponent::Initialize(FWeaponComponentInitializer& initializer) {
	this->data = initializer;
}

AGameCharacter* UWeaponBaseComponent::GetCharacter() {
	AGameCharacter* character = Cast<AGameCharacter>(this->GetOwner());
	if (character) {
		return character;
	}
	UE_LOG(LogTemplateComponents, Error, TEXT("'%s' Failed to find an Owner of Movement Component! Owner: '%s'"), *GetNameSafe(this), *GetOwner()->GetName());
	return nullptr;
}

float UWeaponBaseComponent::GetCooldown() {
	return Cooldown;
}

float UWeaponBaseComponent::GetCooldownPers() {
	return GetCooldown() / GetCooldownMax();
}

float UWeaponBaseComponent::GetCooldownMax() {
	return data.Cooldown;
}

bool UWeaponBaseComponent::CanShoot() {
	return Cooldown < 0.1;
}

bool UWeaponBaseComponent::CanShootTo(FVector location) {
	return false;
}

void UWeaponBaseComponent::ShootTo(FVector location) {
	// Abstract Function
}

void UWeaponBaseComponent::Shoot() {
	// Abstract Function
}

void UWeaponBaseComponent::Recharge() {
	// Abstract Function
}
