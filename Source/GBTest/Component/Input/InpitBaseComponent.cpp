#include "./InpitBaseComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../../Character/GameCharacter.h"

UInpitBaseComponent::UInpitBaseComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UInpitBaseComponent::BeginPlay() {
	Super::BeginPlay();

	if (AGameCharacter* character = this->GetCharacter()) {

		if (character->Controller && character->Controller->IsPlayerController()) {
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(character->Controller->InputComponent)) {
				this->Binding(EnhancedInputComponent);
			}
			else {
				UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
			}
		}

		//Add Input Mapping Context
		if (APlayerController* PlayerController = Cast<APlayerController>(character->Controller)) {
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
				Subsystem->AddMappingContext(character->GetMappingContext(), 0);
			}
		}
	}
}

void UInpitBaseComponent::Initialize(FInputComponentInitializer& initializer) {
	UEnhancedInputComponent* inputComponent = this->CurrentInputComponent;
	if (IsValid(inputComponent)) {
		this->Debinding();
		this->data = initializer;
		this->Binding(inputComponent);
	}
	else {
		this->data = initializer;
	}
}

void UInpitBaseComponent::Debinding() {
	if (IsValid(this->CurrentInputComponent)) {
		for (int i = 0; i < bingingHandles.Num(); i++)
			this->CurrentInputComponent->RemoveBindingByHandle(bingingHandles[i]);
	}
	this->bingingHandles.Reset();
	this->CurrentInputComponent = nullptr;
}

AGameCharacter* UInpitBaseComponent::GetCharacter(){
	AGameCharacter* character = Cast<AGameCharacter>(this->GetOwner());
	if (character) {
		return character;
	}
	UE_LOG(LogTemplateComponents, Error, TEXT("'%s' Failed to find an Owner of Input Component! Owner: '%s'"), *GetNameSafe(this), *GetOwner()->GetName());
	return nullptr;
}

void UInpitBaseComponent::Binding(UEnhancedInputComponent* inputComponent) {
	if (IsValid(this->CurrentInputComponent)) {
		this->Debinding();
	}
	this->CurrentInputComponent = inputComponent;
}
