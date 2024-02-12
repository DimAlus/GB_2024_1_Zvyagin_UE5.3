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

ESocialGroup USociumBaseComponent::GetSocialGroup() {
	return CurrentGroup;
}

void USociumBaseComponent::RemoveFromSociety() {
	if (AGameCharacter* character = this->GetCharacter()) {
		USocialService::GetService().RemoveFromGroup(character, CurrentGroup);
		
	}

}

void USociumBaseComponent::ChangeGroup(const ESocialGroup& NewGroup) {
	if (AGameCharacter* character = this->GetCharacter()) {
		if (NewGroup != CurrentGroup) {
			USocialService::GetService().ChangeGroup(character, CurrentGroup, NewGroup);
			CurrentGroup = NewGroup;
			OnChangeSocialGroup.Broadcast(NewGroup);
		}
	}
}

TArray<AGameCharacter*> USociumBaseComponent::GetPersons(ERelations relations, float radius, int count) {
	if (AGameCharacter* character = this->GetCharacter()) {
		return USocialService::GetService().GetCharacterAround(
			CurrentGroup,
			{ relations },
			character->GetActorLocation(),
			radius,
			count,
			{ character }
		);
	}
	return TArray<AGameCharacter*>();
}

AGameCharacter* USociumBaseComponent::GetPerson(ERelations relations, float radius) {
	TArray<AGameCharacter*> characters = this->GetPersons(relations, radius, 1);
	if (characters.Num() > 0)
		return characters[0];
	return nullptr;
}

TArray<AGameCharacter*> USociumBaseComponent::GetPersonsRay(ERelations relations, float radius, float maxLength, int count) {
	if (AGameCharacter* character = this->GetCharacter()) {
		FVector pos = character->GetGameCameraComponent()->GetCameraPosition();
		FVector rot = character->GetGameCameraComponent()->GetCameraLookVector();
		return USocialService::GetService().GetCharacterByRay(
			CurrentGroup,
			{ relations },
			pos,
			rot,
			radius,
			maxLength,
			count,
			{ character }
		);
	}
	return TArray<AGameCharacter*>();
}

AGameCharacter* USociumBaseComponent::GetPersonRay(ERelations relations, float radius, float maxLength) {
	TArray<AGameCharacter*> characters = this->GetPersonsRay(relations, radius, maxLength, 1);
	if (characters.Num() > 0)
		return characters[0];
	return nullptr;
}
