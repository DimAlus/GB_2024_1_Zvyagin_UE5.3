#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

#include "../Lib/Typing.h"

#include "ProjectileBase.generated.h"

class AGameCharacter;

UCLASS()
class GBTEST_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();

	UFUNCTION()
	virtual void InitializeProjectile(FProjectileInitializer& initializer, AGameCharacter* projectileOwner, FVector direction);

protected:

	virtual void BeginPlay();

	UFUNCTION(BlueprintNativeEvent)
	void InitializeAfter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FProjectileInitializer data;

	bool Inited = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AGameCharacter* ProjectileOwner;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESocialGroup OwnerGroup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int CountTouches;

	UFUNCTION(BlueprintNativeEvent)
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	virtual void Tick(float DeltaTime) override;

	void OnBeginOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor);


	UFUNCTION(BlueprintNativeEvent)
	float GetDamage(AGameCharacter* other);
};
