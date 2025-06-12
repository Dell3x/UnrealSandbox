// Fill out your copyright notice in the Description page of Project Settings.


#include "USExplosiveBarrel.h"

// Sets default values
AUSExplosiveBarrel::AUSExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComp"));
    MeshComp->SetSimulatePhysics(true);
    RootComponent = MeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	RadialForceComp->SetupAttachment(MeshComp);
	
	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->Radius = 750.0f;
	RadialForceComp->ImpulseStrength = 2500.0f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

}

// Called when the game starts or when spawned
void AUSExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUSExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUSExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MeshComp->OnComponentHit.AddDynamic(this, &AUSExplosiveBarrel::OnCollisionHit);
}

void AUSExplosiveBarrel::OnCollisionHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector3d NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
}


