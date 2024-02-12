// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../Lib/Typing.h"

#include "SocialService.generated.h"

class AGameCharacter;

/** Service for organization social interative
 * 
 */
UCLASS()
class GBTEST_API USocialService : public UObject
{
	GENERATED_BODY()
private:
	USocialService();
	/*UPROPERTY()
	TMap<ESocialGroup, FSetChar> Society;

	UPROPERTY()
	TMap<ESocialGroup, FMap_SG_Rel> RelationsData;*/
	TMap<ESocialGroup, TSet<AGameCharacter*>> Society;
	TMap<ESocialGroup, TMap<ESocialGroup, ERelations>> RelationsData;
public:
	static USocialService& GetService();

	void AddToGroup(AGameCharacter* character, ESocialGroup group);
	void ChangeGroup(AGameCharacter* character, ESocialGroup groupFrom, ESocialGroup groupTo);
	void RemoveFromGroup(AGameCharacter* character, ESocialGroup group);

	ERelations GetRelations(ESocialGroup gr1, ESocialGroup gr2);

	void ClearService();
	
	/**
	 * Function find First AGameCharacter* at cylindric Ray
	 *
	 * @param myGroup - Group of character, who find others
	 * @param relations - Set of relationship that should be with the current character
	 * @param position - Position for start Ray
	 * @param guide - The guid of the ray
	 * @param radius - radius of the ray
	 * @param maxLength - max length from position for founds characters
	 * @param ignore - set ignore characters
	 */
	UFUNCTION()
	AGameCharacter* GetCharacterByRayFirst(ESocialGroup myGroup, TSet<ERelations> relations, const FVector& position, const FVector& guide, float radius, float maxLength, TSet<AGameCharacter*> ignore = {});
	
	/**
	 * Function find all AGameCharacter* at cylindric Ray
	 *
	 * @param myGroup - Group of character, who find others
	 * @param relations - Set of relationship that should be with the current character
	 * @param position - Position for start Ray
	 * @param guide - The guid of the ray
	 * @param radius - radius of the ray
	 * @param maxLength - max length from position for founds characters
	 * @param count - count founds characters
	 * @param ignore - set ignore characters
	 */
	UFUNCTION()
	TArray<AGameCharacter*> GetCharacterByRay(ESocialGroup myGroup, TSet<ERelations> relations, const FVector& position, const FVector& guide, float radius, float maxLength, int count, TSet<AGameCharacter*> ignore = {});

	/**
	 * Function find First AGameCharacter* around point
	 *
	 * @param myGroup - Group of character, who find others
	 * @param relations - Set of relationship that should be with the current character
	 * @param position - Position of finder
	 * @param maxLength - max length from position for founds characters
	 * @param ignore - set ignore characters
	 */
	UFUNCTION()
	AGameCharacter* GetCharacterAroundFirst(ESocialGroup myGroup, TSet<ERelations> relations, const FVector& position, float maxLength, TSet<AGameCharacter*> ignore = {});

	/**
	 * Function find all AGameCharacter* around point
	 *
	 * @param myGroup - Group of character, who find others
	 * @param relations - Set of relationship that should be with the current character
	 * @param position - Position of finder
	 * @param maxLength - max length from position for founds characters
	 * @param count - count founds characters
	 * @param ignore - set ignore characters
	 */
	UFUNCTION()
	TArray<AGameCharacter*> GetCharacterAround(ESocialGroup myGroup, TSet<ERelations> relations, const FVector& position, float maxLength, int count, TSet<AGameCharacter*> ignore = {});

};
