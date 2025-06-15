// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "USGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "USItemChest.generated.h"

UCLASS()
class UNREALSANBOX_API AUSItemChest : public AActor, public IUSGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
public:

	UPROPERTY(EditAnywhere)
	float TargetPitch = 110;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

	
	// Sets default values for this actor's properties
	AUSItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
