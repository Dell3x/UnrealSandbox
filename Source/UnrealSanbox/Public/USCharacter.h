// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "USInteractionComponent.h"
#include "GameFramework/Character.h"
#include "USCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class UNREALSANBOX_API AUSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUSCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere)
	UUSInteractionComponent* InteractionComp;
	
	// Called when the game starts or when spawne
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Jump();
	
	void PrimaryAttack();
	
	void PrimaryInteract();

public:			
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
