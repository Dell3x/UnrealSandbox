// Fill out your copyright notice in the Description page of Project Settings.


#include "USInteractionComponent.h"

#include "USGameplayInterface.h"

// Sets default values for this component's properties
UUSInteractionComponent::UUSInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUSInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUSInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUSInteractionComponent::PrimaryInteraction()
{
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * InteractRange);
	
	// FHitResult HitResult;
	// bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation, End, QueryParams);

	TArray<FHitResult> Hits;
	float Radius = 30.0f;
	
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits,EyeLocation,End, FQuat::Identity,QueryParams,Shape);
	
	FColor CollisionColor = bBlockingHit ? FColor::Green: FColor::Red;

	for (auto Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 16, CollisionColor, false, 2.0f);
			if (HitActor->Implements<UUSGameplayInterface>())
			{
				APawn* Mypawn = Cast<APawn>(HitActor);
				IUSGameplayInterface::Execute_Interact(HitActor, Mypawn);
				break;
			}
		}
	}
	
	DrawDebugLine(GetWorld(), EyeLocation, End, CollisionColor, false, 2.0f, 0,2.0f);
}
