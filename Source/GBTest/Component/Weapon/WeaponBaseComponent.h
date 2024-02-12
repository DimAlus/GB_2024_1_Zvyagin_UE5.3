// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../../Lib/Typing.h"

#include "WeaponBaseComponent.generated.h"

class AGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GBTEST_API UWeaponBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponBaseComponent();

	UFUNCTION()
	virtual void Initialize(FWeaponComponentInitializer& initializer);

	UFUNCTION()
	AGameCharacter* GetCharacter();

protected:
	UPROPERTY()
	FWeaponComponentInitializer data;

	bool IsShooting = false;
	float Cooldown;
public:


	UFUNCTION(BlueprintCallable)
	virtual float GetCooldown();

	UFUNCTION(BlueprintCallable)
	virtual float GetCooldownPers();

	UFUNCTION(BlueprintCallable)
	virtual float GetCooldownMax();

	UFUNCTION(BlueprintCallable)
	virtual bool CanShoot();

	UFUNCTION(BlueprintCallable)
	virtual bool CanShootTo(FVector location);

	UFUNCTION(BlueprintCallable)
	virtual void ShootTo(FVector location);

	UFUNCTION(BlueprintCallable)
	virtual void Shoot();

	UFUNCTION(BlueprintCallable)
	virtual void ShootStart();

	UFUNCTION(BlueprintCallable)
	virtual void ShootEnd();

	UFUNCTION(BlueprintCallable)
	virtual void Recharge();
};
