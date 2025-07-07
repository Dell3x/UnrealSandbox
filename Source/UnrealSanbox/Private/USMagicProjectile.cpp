// Fill out your copyright notice in the Description page of Project Settings.


#include "USMagicProjectile.h"

#include "Particles/ParticleSystemComponent.h"

// Sets default values
AUSMagicProjectile::AUSMagicProjectile()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(FName("SphereComp"));
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(FName("ParticleComp"));
	ParticleComp->SetupAttachment(SphereComp);

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileComp"));
	ProjectileComp->InitialSpeed = 1000.0f;
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->bInitialVelocityInLocalSpace = true;
}

void AUSMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
    
	// if (APawn* ProjectileInstigator = GetInstigator())
	// {
	// 	SphereComp->IgnoreActorWhenMoving(ProjectileInstigator,true);
	// 	ProjectileInstigator->MoveIgnoreActorAdd(this);
	// }
}


// Called when the game starts or when spawned
void AUSMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUSMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
