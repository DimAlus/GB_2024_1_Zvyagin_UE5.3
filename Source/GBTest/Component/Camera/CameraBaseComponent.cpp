#include "./CameraBaseComponent.h"
#include "../../Character/GameCharacter.h"

UCameraBaseComponent::UCameraBaseComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UCameraBaseComponent::Initialize(FCameraComponentInitializer& initializer) {
	this->data = initializer;
}

AGameCharacter* UCameraBaseComponent::GetCharacter() {
	AGameCharacter* character = Cast<AGameCharacter>(this->GetOwner());
	if (character) {
		return character;
	}
	UE_LOG(LogTemplateComponents, Error, TEXT("'%s' Failed to find an Owner of Camera Component! Owner: '%s'"), *GetNameSafe(this), *GetOwner()->GetName());
	return nullptr;
}

void UCameraBaseComponent::LookTo(const FVector2D& lookAxisVector) {
	// Abstract Function
}

void UCameraBaseComponent::ZoomAt(float zoom) {
	// Abstract Function
}

void UCameraBaseComponent::ZoomTo(float zoom) {
	// Abstract Function
}

void UCameraBaseComponent::ZoomAtPer(float persents) {
	// Abstract Function
}

void UCameraBaseComponent::ZoomToPer(float persents) {
	// Abstract Function
}

void UCameraBaseComponent::ZoomIncr(int direction) {
	// Abstract Function
}

FVector UCameraBaseComponent::GetCameraPosition() {
	return FVector();
}

FVector UCameraBaseComponent::GetCameraLookVector() {
	return FVector();
}

