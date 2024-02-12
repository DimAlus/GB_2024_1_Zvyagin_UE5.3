#include "./WeaponProjectileComponent.h"
#include "../../Character/GameCharacter.h"
#include "../../Projectile/ProjectileBase.h"

UWeaponProjectileComponent::UWeaponProjectileComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Cooldown = std::max(0.f, Cooldown - DeltaTime);	
	if (IsShooting) {
		Shoot();
	}
}

bool UWeaponProjectileComponent::CanShootTo(FVector location) {
	return CanShoot();
}

void UWeaponProjectileComponent::ShootTo(FVector location) {
	if (CanShoot()) {
		if (AGameCharacter* character = this->GetCharacter()) {
			this->Cooldown = data.Cooldown;

			FVector posProj = character->GetActorLocation() + data.ProjectileSpawnLocation;

			AProjectileBase* proj = GetWorld()->SpawnActor<AProjectileBase>(
				data.ProjectileClass,
				posProj,
				(location - posProj).Rotation()
			);
			if (proj) {

				proj->InitializeProjectile(data.ProjectileInitializer, character, location - posProj);
			}
		}
	}
}

void UWeaponProjectileComponent::Shoot() {
	if (CanShoot()) {

		if (AGameCharacter* character = this->GetCharacter()) {
			FVector pos = character->GetGameCameraComponent()->GetCameraPosition();
			FVector rot = character->GetGameCameraComponent()->GetCameraLookVector();
			/*
			FCollisionQueryParams params;
			params.AddIgnoredActor(character);
			FHitResult result;
			GetWorld()->LineTraceSingleByChannel(result, pos, pos + rot * 10000, ECollisionChannel::ECC_Pawn, params);

			FVector end = result.Location;*/
			this->Cooldown = data.Cooldown;

			FVector posProj = character->GetActorLocation() + data.ProjectileSpawnLocation;
			/*FVector rotProj = rot;
			if (result.IsValidBlockingHit()) {
				rotProj = end - posProj;
			}*/
			FVector endProj = pos + rot * 2000;
			FVector rotProj = endProj - posProj;
			
			AProjectileBase* proj = GetWorld()->SpawnActor<AProjectileBase>(
				data.ProjectileClass,
				posProj,
				rotProj.Rotation()
			);
			if (proj) {

				proj->InitializeProjectile(data.ProjectileInitializer, character, rotProj);
			}
		}
	}
}
