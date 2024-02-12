#include "./SocialService.h"
#include "math.h"
#include "../Character/GameCharacter.h"

USocialService::USocialService() {
	// ToDo: Move to DataTable
	RelationsData = {
		{ ESocialGroup::Player, {} },
		{ ESocialGroup::Associate, {} },
		{ ESocialGroup::Enemy, {} }
	};
	RelationsData[ESocialGroup::Player].Add({ ESocialGroup::Player, ERelations::Friend });
	RelationsData[ESocialGroup::Player].Add({ ESocialGroup::Associate, ERelations::Friend });
	RelationsData[ESocialGroup::Player].Add({ ESocialGroup::Enemy, ERelations::Enemy });

	RelationsData[ESocialGroup::Associate].Add({ ESocialGroup::Player, ERelations::Friend });
	RelationsData[ESocialGroup::Associate].Add({ ESocialGroup::Associate, ERelations::Friend });
	RelationsData[ESocialGroup::Associate].Add({ ESocialGroup::Enemy, ERelations::Enemy });

	RelationsData[ESocialGroup::Enemy].Add({ ESocialGroup::Player, ERelations::Enemy });
	RelationsData[ESocialGroup::Enemy].Add({ ESocialGroup::Associate, ERelations::Enemy });
	RelationsData[ESocialGroup::Enemy].Add({ ESocialGroup::Enemy, ERelations::Friend });
}

USocialService& USocialService::GetService()
{
	static USocialService* service;
	if (!service) {
		service = NewObject<USocialService>(
			(UObject*)GetTransientPackage(), 
			FName("SocialService"), 
			EObjectFlags::RF_MarkAsRootSet
		);
	}
	return *service;
}

void USocialService::AddToGroup(AGameCharacter* character, ESocialGroup group) {
	if (!Society.Contains(group)) {
		Society.Add(group, {});
	}
	Society[group].Add(character);
	//Society[group].Set.Add(character);
}

void USocialService::ChangeGroup(AGameCharacter* character, ESocialGroup groupFrom, ESocialGroup groupTo) {
	RemoveFromGroup(character, groupFrom);
	AddToGroup(character, groupTo);
}

void USocialService::RemoveFromGroup(AGameCharacter* character, ESocialGroup group) {
	if (!Society.Contains(group)) {
		Society.Add(group, {});
	}
	Society[group].Remove(character);
}

ERelations USocialService::GetRelations(ESocialGroup gr1, ESocialGroup gr2) {
	if (this->RelationsData.Contains(gr1) &&
		this->RelationsData[gr1].Contains(gr2)) {
		return this->RelationsData[gr1][gr2];
	}
	return ERelations::Neutral;
}

void USocialService::ClearService() {
	Society.Reset();
}

AGameCharacter* USocialService::GetCharacterByRayFirst(ESocialGroup myGroup, TSet<ERelations> relations, const FVector& position, const FVector& guide, float radius, float maxLength, TSet<AGameCharacter*> ignore) {
	const TArray<AGameCharacter*>& characters = GetCharacterByRay(myGroup, relations, position, guide, radius, maxLength, 1, ignore);
	if (characters.Num() > 0) {
		return characters[0];
	}
	return nullptr;
}


TArray<AGameCharacter*> USocialService::GetCharacterByRay(ESocialGroup myGroup, TSet<ERelations> relations, const FVector& position, const FVector& guide, float radius, float maxLength, int count, TSet<AGameCharacter*> ignore) {
	TArray<AGameCharacter*> characters;
	TSortedMap<float, AGameCharacter*> elements;
	if (guide.Length() == 0) {
		return characters;
	}
	for (auto& myRelations : this->RelationsData[myGroup]) {
		if (relations.Contains(myRelations.Value)) {
			if (!this->Society.Contains(myRelations.Key))
				continue;
			for (AGameCharacter* target : this->Society[myRelations.Key]) {
				// if not valid or ignored
				if (!IsValid(target) || ignore.Contains(target)) {
					continue;
				}
				FVector targetRelativeLoc = target->GetActorLocation() - position;
				// if target is back of ray
				if (targetRelativeLoc.Length() > maxLength || VectorsAngle(guide, targetRelativeLoc) > PI / 2) {
					continue;
				}
				// Length between line and point is |targetRelativeLoc X guide| / len(guide)
				float len = guide.Cross(targetRelativeLoc).Length() / guide.Length();
				if (len < radius) {
					elements.Add(len, target);
					// elements.Add(targetRelativeLoc.Length(), target);
				}
			}
		}
	}
	int maxVal = std::min(count, elements.Num());
	for (auto& elem : elements) {
		if (maxVal-- == 0)
			break;
		characters.Add(elem.Value);
	}
	return characters;
}

AGameCharacter* USocialService::GetCharacterAroundFirst(ESocialGroup myGroup, TSet<ERelations> relations, const FVector& position, float maxLength, TSet<AGameCharacter*> ignore) {
	const TArray<AGameCharacter*>& characters = GetCharacterAround(myGroup, relations, position, maxLength, 1, ignore);
	if (characters.Num() > 0) {
		return characters[0];
	}
	return nullptr;
}

TArray<AGameCharacter*> USocialService::GetCharacterAround(ESocialGroup myGroup, TSet<ERelations> relations, const FVector& position, float maxLength, int count, TSet<AGameCharacter*> ignore) {
	TArray<AGameCharacter*> characters;
	TSortedMap<float, AGameCharacter*> elements;
	for (auto& myRelations : this->RelationsData[myGroup]) {
		if (relations.Contains(myRelations.Value)) {
			if (!this->Society.Contains(myRelations.Key))
				continue;
			for (AGameCharacter* target : this->Society[myRelations.Key]) {
				// if not valid or ignored
				if (!(IsValid(target) && !ignore.Contains(target))) {
					continue;
				}
				float len = (target->GetActorLocation() - position).Length();
				if (len <= maxLength) {
					elements.Add(len, target);
				}
			}
		}
	}
	int maxVal = std::min(count, elements.Num());
	for (auto& elem : elements) {
		if (maxVal-- == 0)
			break;
		characters.Add(elem.Value);
	}
	return characters;
}
