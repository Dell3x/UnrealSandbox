// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "USProjectileBase.h"
#include "USMagicProjectile.generated.h"

UCLASS()
class UNREALSANBOX_API AUSMagicProjectile : public AUSProjectileBase 
{
	GENERATED_BODY()

public:
	AUSMagicProjectile();
	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
