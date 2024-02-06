#include "./SociumBaseComponent.h"
#include "../../Character/GameCharacter.h"
#include "../../Service/SocialService.h"

USociumBaseComponent::USociumBaseComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void USociumBaseComponent::DestroyComponent(bool bPromoteChildren) {
	if (AGameCharacter* character = this->GetCharacter()) {
		USocialService::GetService().RemoveFromGroup(character, CurrentGroup);
	}
}

void USociumBaseComponent::Initialize(FSociumComponentInitializer& initializer) {
	this->data = initializer;
}

AGameCharacter* USociumBaseComponent::GetCharacter() {
	AGameCharacter* character = Cast<AGameCharacter>(this->GetOwner());
	if (character) {
		return character;
	}
	UE_LOG(LogTemplateComponents, Error, TEXT("'%s' Failed to find an Owner of Socium Component! Owner: '%s'"), *GetNameSafe(this), *GetOwner()->GetName());
	return nullptr;
}


void USociumBaseComponent::BeginPlay() {
	Super::BeginPlay();
	if (AGameCharacter* character = this->GetCharacter()) {
		USocialService::GetService().AddToGroup(character, data.DefaultGroup);
		CurrentGroup = data.DefaultGroup;
	}
}

void USociumBaseComponent::ChangeGroup(const ESocialGroup& NewGroup) {
	if (AGameCharacter* character = this->GetCharacter()) {
		if (NewGroup != CurrentGroup) {
			USocialService::GetService().ChangeGroup(character, CurrentGroup, NewGroup);
			CurrentGroup = NewGroup;
		}
	}
}
