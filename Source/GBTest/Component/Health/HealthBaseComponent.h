#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../../Lib/Typing.h"

#include "HealthBaseComponent.generated.h"

class AGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GBTEST_API UHealthBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthBaseComponent();

	UFUNCTION()
	virtual void Initialize(FHealthComponentInitializer& initializer);

	UFUNCTION()
	AGameCharacter* GetCharacter();

protected:
	UPROPERTY()
	FHealthComponentInitializer data;
		
public:
	UFUNCTION(BlueprintCallable)
	virtual float GetHealth();

	UFUNCTION(BlueprintCallable)
	virtual float GetHealthPercents();

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(AGameCharacter* otherCharacter, ETypeDamage typeDamage, float power);
};
