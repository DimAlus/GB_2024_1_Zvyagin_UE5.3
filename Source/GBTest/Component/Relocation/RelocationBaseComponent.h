#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../../Lib/Typing.h"

#include "RelocationBaseComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterEventSignature, AGameCharacter*, character);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GBTEST_API URelocationBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URelocationBaseComponent();

	UFUNCTION()
	virtual void Initialize(FRelocationComponentInitializer& initializer);

	UFUNCTION()
	AGameCharacter* GetCharacter();

protected:
	UPROPERTY()
	FRelocationComponentInitializer data;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Cooldown = 10.f;
public:
	UFUNCTION(BlueprintCallable)
	virtual void Relocate();

	UFUNCTION(BlueprintCallable)
	virtual void Activation();

	UFUNCTION(BlueprintCallable)
	virtual void Deactivation();

	/** Call if other character targetted to this */
	UPROPERTY(BlueprintAssignable)
	FCharacterEventSignature OnTargettingRelocation;

	/** Call if other character ends targeting to this */
	UPROPERTY(BlueprintAssignable)
	FCharacterEventSignature OnTargettingEndRelocation;
};
