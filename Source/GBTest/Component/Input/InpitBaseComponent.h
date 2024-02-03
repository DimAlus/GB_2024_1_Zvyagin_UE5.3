#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

#include "../../Lib/Typing.h"

#include "InpitBaseComponent.generated.h"

class AGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GBTEST_API UInpitBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInpitBaseComponent();

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Initialize(FInputComponentInitializer& initializer);

	// Binding all actions
	UFUNCTION()
	virtual void Binding(UEnhancedInputComponent* inputComponent);
protected:
	UFUNCTION()
	AGameCharacter* GetCharacter();

	// Debinding all actions
	UFUNCTION()
	virtual void Debinding();
protected:
	UPROPERTY()
	UEnhancedInputComponent* CurrentInputComponent;
	UPROPERTY()
	FInputComponentInitializer data;
	UPROPERTY()
	TArray<uint32> bingingHandles;

};
