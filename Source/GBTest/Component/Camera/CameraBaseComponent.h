#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../../Lib/Typing.h"

#include "CameraBaseComponent.generated.h"

class AGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GBTEST_API UCameraBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraBaseComponent();

	UFUNCTION()
	virtual void Initialize(FCameraComponentInitializer& initializer);
protected:
	UFUNCTION()
	AGameCharacter* GetCharacter();

protected:
	UPROPERTY()
	FCameraComponentInitializer data;
public:
	UFUNCTION()
	virtual void LookTo(const FVector2D& lookAxisVector);
	UFUNCTION()
	virtual void ZoomAt(float zoom);
	UFUNCTION()
	virtual void ZoomTo(float zoom);
	UFUNCTION()
	virtual void ZoomAtPer(float persents);
	UFUNCTION()
	virtual void ZoomToPer(float persents);
	UFUNCTION()
	virtual void ZoomIncr(int direction);


	UFUNCTION()
	virtual FVector GetCameraPosition();
	UFUNCTION()
	virtual FVector GetCameraLookVector();
};
