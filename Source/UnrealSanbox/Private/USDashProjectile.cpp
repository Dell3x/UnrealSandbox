// Fill out your copyright notice in the Description page of Project Settings.


#include "USDashProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"



// Sets default values
AUSDashProjectile::AUSDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MoveComp->InitialSpeed = 6000.0f;

}

// Called when the game starts or when spawned
void AUSDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &AUSDashProjectile::Explode, DetonateDelay);
}

void AUSDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();

	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &AUSDashProjectile::TeleportInstigator, TeleportDelay);

	// Skip base implementation as it will destroy actor
	//Super::Explode_Implementation();
}


void AUSDashProjectile::TeleportInstigator()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedTeleport);

	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		// Keep instigator rotation or it may end up jarring
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}

	Destroy();

}

void AUSDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(APawn* ProjectileInstigator = GetInstigator())
	{
		SphereComp->IgnoreActorWhenMoving(ProjectileInstigator,true);
		ProjectileInstigator->MoveIgnoreActorAdd(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile has no instigator set!"));
	}
}

