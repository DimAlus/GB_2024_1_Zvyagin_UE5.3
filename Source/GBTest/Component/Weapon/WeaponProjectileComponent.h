#pragma once

#include "CoreMinimal.h"
#include "./WeaponBaseComponent.h"
#include "WeaponProjectileComponent.generated.h"

/**
 * 
 */
UCLASS()
class GBTEST_API UWeaponProjectileComponent : public UWeaponBaseComponent
{
	GENERATED_BODY()

public:
	UWeaponProjectileComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool CanShootTo(FVector location) override;

	virtual void ShootTo(FVector location) override;

	virtual void Shoot() override;
};
