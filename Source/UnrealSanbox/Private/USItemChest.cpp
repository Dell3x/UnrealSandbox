// Fill out your copyright notice in the Description page of Project Settings.


#include "USItemChest.h"

// Sets default values
AUSItemChest::AUSItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	RootComponent = StaticMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("LidMesh"));
	LidMesh->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void AUSItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUSItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUSItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}
