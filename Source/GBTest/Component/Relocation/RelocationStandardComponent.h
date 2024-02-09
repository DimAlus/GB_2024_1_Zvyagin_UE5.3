#pragma once

#include "CoreMinimal.h"
#include "./RelocationBaseComponent.h"
#include "RelocationStandardComponent.generated.h"


/**
 * 
 */
UCLASS()
class GBTEST_API URelocationStandardComponent : public URelocationBaseComponent
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
	virtual void Relocate() override;
	virtual void Activation() override;
	virtual void Deactivation() override;

};
