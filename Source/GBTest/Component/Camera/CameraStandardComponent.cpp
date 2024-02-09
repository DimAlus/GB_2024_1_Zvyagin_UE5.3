#include "./CameraStandardComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "../../Character/GameCharacter.h"

UCameraStandardComponent::UCameraStandardComponent() : UCameraBaseComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UCameraStandardComponent::Initialize(FCameraComponentInitializer& initializer) {
	Super::Initialize(initializer);
	this->SetComponentTickEnabled(false);

	// Zoom
	if (this->data.ZoomLenSlow == 0) {
		this->data.ZoomLenSlow = 100;
		UE_LOG(LogTemplateComponents, Error, TEXT("'%s' Failed to initialize Camera Component! ZoomLenSlow = 0"), *GetNameSafe(this));
	}
	this->ZoomBoost = this->data.ZoomMaxSpeed * this->data.ZoomMaxSpeed / this->data.ZoomLenSlow / 2;
	this->ZoomTargetLen = this->ZoomLen = (this->data.ZoomLimits.X + this->data.ZoomLimits.Y) / 2;
	if (this->data.ZoomMaxSpeed == 0) {
		this->ZoomBoost = this->data.ZoomLenSlow;
		UE_LOG(LogTemplateComponents, Error, TEXT("'%s' Failed to initialize Camera Component! ZoomMaxSpeed = 0"), *GetNameSafe(this));
	}
	ZoomLimDelta = data.ZoomLimits.Y - data.ZoomLimits.X;
}

void UCameraStandardComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bool StopTick = false;
	if (AGameCharacter* character = this->GetCharacter()) {

		// Changing Zoom Logic
		float zoomDelta = this->ZoomTargetLen - this->ZoomLen;
		if (abs(zoomDelta) > 0.1 || abs(ZoomSpeed) > 1) {
			float zoomBoosting;
			if (ZoomIsSlowing) {
				zoomBoosting = ZoomSlowing;
				if (zoomDelta * ZoomSlowing < 0) {
					zoomBoosting = 0;
					StopTick = true;
				}
			}
			else {
				// Расстояние, которое пройдет камера, постоянно замедляясь
				float zoomSlowLen = ZoomSpeed * ZoomSpeed / 2 / ZoomBoost;
				// Если при постоянном замедлении он достигнет целевого значения и он движется в нужном направлении
				if (zoomSlowLen > abs(zoomDelta) && ZoomSpeed * zoomDelta > 0) {
					ZoomIsSlowing = true;
					zoomBoosting = ZoomSlowing = -ZoomSpeed * ZoomSpeed / zoomDelta / 2;
				}
				else {
					zoomBoosting = ZoomBoost * FMath::Sign(zoomDelta);
				}
			}
			ZoomSpeed = FMath::Clamp(ZoomSpeed + zoomBoosting * DeltaTime, -data.ZoomMaxSpeed, data.ZoomMaxSpeed);
			this->ZoomLen += ZoomSpeed * DeltaTime;
			character->GetCameraBoom()->TargetArmLength = this->ZoomLen;
		}
		else {
			StopTick = true;
		}
	}
	else {
		StopTick = true;
	}
	if (StopTick) {
		this->ZoomSpeed = 0;
		this->ZoomIsSlowing = false;
		this->SetComponentTickEnabled(false);
	}

}

void UCameraStandardComponent::LookTo(const FVector2D& lookAxisVector) {
	if (AGameCharacter* character = this->GetCharacter()) {
		if (character->Controller != nullptr)
		{
			// add yaw and pitch input to controller
			character->AddControllerYawInput(lookAxisVector.X);
			character->AddControllerPitchInput(lookAxisVector.Y);
			character->GetGameMovementComponent()->Look(character->Controller->GetControlRotation());
		}
	}
}

void UCameraStandardComponent::ZoomAt(float zoom) {
	this->ZoomTo(ZoomTargetLen - zoom);
}

void UCameraStandardComponent::ZoomTo(float zoom) {
	if (AGameCharacter* character = this->GetCharacter()) {
		if (USpringArmComponent* camera = character->GetCameraBoom()) {
			this->ZoomIsSlowing = false;
			this->ZoomTargetLen = FMath::Clamp(zoom, data.ZoomLimits.X, data.ZoomLimits.Y);
			this->ZoomLen = camera->TargetArmLength;
			if (abs(ZoomTargetLen - ZoomLen) > 0.1) {
				this->SetComponentTickEnabled(true);
			}
		}
	}
}

void UCameraStandardComponent::ZoomAtPer(float persents) {
	this->ZoomTo(ZoomTargetLen - persents * ZoomLimDelta);
}

void UCameraStandardComponent::ZoomToPer(float persents) {
	this->ZoomTo(data.ZoomLimits.X + persents * ZoomLimDelta);
}

void UCameraStandardComponent::ZoomIncr(int direction) {
	this->ZoomTo(
		ZoomTargetLen +
		data.ZoomPerScroll * ZoomLimDelta *
		-FMath::Sign(direction)
	);
}

FVector UCameraStandardComponent::GetCameraPosition() {
	FVector result;
	if (AGameCharacter* character = this->GetCharacter()) {
		if (USpringArmComponent* camera = character->GetCameraBoom())
			result = camera->GetRelativeLocation();
		result += character->GetActorLocation();
	}
	return result;
}

FVector UCameraStandardComponent::GetCameraLookVector() {
	if (AGameCharacter* character = this->GetCharacter()) {
		if (character->Controller) {
			return character->Controller->GetControlRotation().Vector();
		}
	}
	return FVector();
}
