// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "USProjectileBase.h"
#include "USDashProjectile.generated.h"


UCLASS()
class UNREALSANBOX_API AUSDashProjectile : public AUSProjectileBase
{
	GENERATED_BODY()
	
public:	

	AUSDashProjectile();
	virtual void PostInitializeComponents() override;


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay;

	FTimerHandle TimerHandle_DelayedDetonate;
	FTimerHandle TimerHandle_DelayedTeleport;

	// Base class using BlueprintNativeEvent, we must override the _Implementation not the Explode()
	virtual void Explode_Implementation() override;

	void TeleportInstigator();

	virtual void BeginPlay() override;

};
