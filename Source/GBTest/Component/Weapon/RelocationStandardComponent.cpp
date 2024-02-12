#include "./RelocationStandardComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../../Character/GameCharacter.h"
#include "../Socium/SociumBaseComponent.h"


URelocationStandardComponent::URelocationStandardComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	this->SetComponentTickInterval(0.2);
	this->SetComponentTickEnabled(false);
}

void URelocationStandardComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	if (AGameCharacter* character = this->GetCharacter()) {
		this->Cooldown = std::max(0.f, this->Cooldown - DeltaTime);
		if (Cooldown < 0.01) {
			AGameCharacter* target = character->GetGameSociumComponent()->GetPersonRay(ERelations::Enemy, data.Radius, data.MaxLength);
			if (target != currentTarget) {
				DetachToCharacter(currentTarget);
				AttachToCharacter(target);
				currentTarget = target;
			}
		}
		else if (currentTarget) {
			DetachToCharacter(currentTarget);
			currentTarget = nullptr;
		}
	}
}

void URelocationStandardComponent::AttachToCharacter(AGameCharacter* target) {
	if (AGameCharacter* character = this->GetCharacter()) {
		if (IsValid(target)) {
			target->GetGameRelocationComponent()->OnTargettingRelocation.Broadcast(character);
		}
	}
}

void URelocationStandardComponent::DetachToCharacter(AGameCharacter* target) {
	if (AGameCharacter* character = this->GetCharacter()) {
		if (IsValid(target)) {
			target->GetGameRelocationComponent()->OnTargettingEndRelocation.Broadcast(character);
		}
	}
}

void URelocationStandardComponent::Shoot() {
	if (IsValid(currentTarget) && Cooldown < 0.01) {
		if (AGameCharacter* character = this->GetCharacter()) {
			character->GetGameInputComponent()->Binding(nullptr);

			TObjectPtr<AController> controller = character->Controller;

			character->GetGameWeaponMainComponent()->ShootEnd();
			character->GetGameWeaponAddComponent()->ShootEnd();

			UCameraComponent* camera = character->GetFollowCamera();
			character->SetPlayerController(nullptr);
			character->SetFollowCamera(nullptr);
			if (camera) {
				camera->UnregisterComponent();
				camera->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
				camera->Rename(TEXT("Follow_Camera"), currentTarget);
				camera->AttachToComponent(currentTarget->GetCameraBoom(), FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
				camera->ReregisterComponent();
			}
			currentTarget->SetFollowCamera(camera);
		
			
			currentTarget->SetPlayerController(controller);


			
			currentTarget->GetGameInputComponent()->Binding(Cast<UEnhancedInputComponent>(controller->InputComponent));


			currentTarget->GetGameRelocationComponent()->Activation();

			character->GetGameSociumComponent()->ChangeGroup(ESocialGroup::Associate);
			currentTarget->GetGameSociumComponent()->ChangeGroup(ESocialGroup::Player);

			Deactivation();
		}
	}
}

void URelocationStandardComponent::Activation() {
	this->SetComponentTickEnabled(true);
	this->Cooldown = data.Cooldown;
}

void URelocationStandardComponent::Deactivation() {
	DetachToCharacter(currentTarget);
	currentTarget = nullptr;
	this->SetComponentTickEnabled(false);
}
