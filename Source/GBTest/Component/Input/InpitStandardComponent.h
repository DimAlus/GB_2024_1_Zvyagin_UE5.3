#pragma once

#include "CoreMinimal.h"
#include "./InpitBaseComponent.h"
#include "InpitStandardComponent.generated.h"

/**
 * 
 */
UCLASS()
class GBTEST_API UInpitStandardComponent : public UInpitBaseComponent
{
	GENERATED_BODY()
public:
	UInpitStandardComponent();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Binding(UEnhancedInputComponent* inputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void JumpStart(const FInputActionValue& Value);
	UFUNCTION()
	void JumpEnd(const FInputActionValue& Value);
	UFUNCTION()
	void Scroll(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void Relocate(const FInputActionValue& Value);
};
