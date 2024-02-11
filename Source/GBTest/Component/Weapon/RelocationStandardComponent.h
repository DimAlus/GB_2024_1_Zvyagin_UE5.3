#pragma once

#include "CoreMinimal.h"
#include "./WeaponBaseComponent.h"
#include "RelocationStandardComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterEventSignature, AGameCharacter*, character);


/**
 * 
 */
UCLASS()
class GBTEST_API URelocationStandardComponent : public UWeaponBaseComponent
{
	GENERATED_BODY()
public:
	URelocationStandardComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	AGameCharacter* currentTarget;

	void AttachToCharacter(AGameCharacter* target);
	void DetachToCharacter(AGameCharacter* target);

public:
	virtual void Shoot() override;
	virtual void Activation();
	virtual void Deactivation();


	/** Call if other character targetted to this */
	UPROPERTY(BlueprintAssignable)
	FCharacterEventSignature OnTargettingRelocation;

	/** Call if other character ends targeting to this */
	UPROPERTY(BlueprintAssignable)
	FCharacterEventSignature OnTargettingEndRelocation;
};
