#include "./ProjectileBase.h"
#include "../Character/GameCharacter.h"
#include "../Service/SocialService.h"

AProjectileBase::AProjectileBase() {
	PrimaryActorTick.bCanEverTick = true;
	//this->OnActorBeginOverlap.Add(FScriptDelegate&BeginOverlap));
	
}

void AProjectileBase::InitializeProjectile(FProjectileInitializer& initializer, AGameCharacter* projectileOwner, FVector direction) {
	this->data = initializer;
	if (IsValid(projectileOwner)) {
		this->CurrentTime = data.DespawnTime;
		this->StartLocation = this->GetActorLocation();
		this->ProjectileOwner = projectileOwner;
		this->CountTouches = data.CountTouch;
		this->OwnerGroup = projectileOwner->GetGameSociumComponent()->GetSocialGroup();
		direction.Normalize();
		this->Velocity = direction * data.Speed;
	}
	Inited = true;
	InitializeAfter();
}

void AProjectileBase::BeginPlay() {
	Super::BeginPlay();
	this->OnActorBeginOverlap.AddDynamic(this, &AProjectileBase::BeginOverlap);
	///SetActorTickEnabled(true);
}

void AProjectileBase::InitializeAfter_Implementation() {
}


void AProjectileBase::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) {
	if (Inited) {
		this->OnBeginOverlap(OverlappedActor, OtherActor);
	}
}

void AProjectileBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (Inited) {
		AddActorWorldOffset(Velocity * DeltaTime);
		Velocity += FVector::DownVector * 9.8 * DeltaTime * data.Gravity;

		if ((CurrentTime -= DeltaTime) < 0) {
			this->Destroy();
		}

	}
}

void AProjectileBase::OnBeginOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor) {
	if (AGameCharacter* other = Cast<AGameCharacter>(OtherActor)) {
		if (other != ProjectileOwner) {
			ERelations relations = USocialService::GetService().GetRelations(OwnerGroup, other->GetGameSociumComponent()->GetSocialGroup());
			if (data.TargetRelations.Contains(relations)) {
				other->GetGameHealthComponent()->TakeDamage(other, ETypeDamage::Damage, GetDamage(other));
			}
		}
	}
	if (OtherActor != ProjectileOwner) {
		if (data.DestroyOnTouch && --CountTouches <= 0) {
			Destroy();
		}
	}
}

float AProjectileBase::GetDamage_Implementation(AGameCharacter* other) {
	return data.Damage;
}

