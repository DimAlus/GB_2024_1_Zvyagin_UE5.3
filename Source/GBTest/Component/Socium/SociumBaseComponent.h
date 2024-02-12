#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../../Lib/Typing.h"

#include "SociumBaseComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSocialGroupChangeSignature, ESocialGroup, NewGroup);

class AGameCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GBTEST_API USociumBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USociumBaseComponent();
	virtual void DestroyComponent(bool bPromoteChildren) override;

	UFUNCTION()
	virtual void Initialize(FSociumComponentInitializer& initializer);

	UFUNCTION()
	AGameCharacter* GetCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	FSociumComponentInitializer data;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESocialGroup CurrentGroup;

public:
	UFUNCTION()
	ESocialGroup GetSocialGroup();

	UFUNCTION()
	virtual void RemoveFromSociety();

	UFUNCTION()
	virtual void ChangeGroup(const ESocialGroup& NewGroup);

	UFUNCTION(BlueprintCallable)
	virtual TArray<AGameCharacter*> GetPersons(ERelations relations, float radius, int count);
	UFUNCTION(BlueprintCallable)
	virtual AGameCharacter* GetPerson(ERelations relations, float radius);

	UFUNCTION(BlueprintCallable)
	virtual TArray<AGameCharacter*> GetPersonsRay(ERelations relations, float radius, float maxLength, int count);
	UFUNCTION(BlueprintCallable)
	virtual AGameCharacter* GetPersonRay(ERelations relations, float radius, float maxLength);


	/** Call if other character ends targeting to this */
	UPROPERTY(BlueprintAssignable)
	FSocialGroupChangeSignature OnChangeSocialGroup;
};
