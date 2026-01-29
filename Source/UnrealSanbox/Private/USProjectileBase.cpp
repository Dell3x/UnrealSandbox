	// Fill out your copyright notice in the Description page of Project Settings.


#include "USProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUSProjectileBase::AUSProjectileBase()
{
 	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");

	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &AUSProjectileBase::OnActorHit);

	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 8000;

}


void AUSProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

// _Implementation from it being marked as BlueprintNativeEvent
void AUSProjectileBase::Explode_Implementation()
{
	// Check to make sure we aren't already being 'destroyed'
	// Adding ensure to see if we encounter this situation at all
	if (ensure(!IsPendingKillPending()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		EffectComp->DeactivateSystem();
		MoveComp->StopMovementImmediately();
		SetActorEnableCollision(false);

		Destroy();
	}
}


void AUSProjectileBase::PostInitializeComponents()
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

