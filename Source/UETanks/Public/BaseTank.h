// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseTank.generated.h"

UCLASS()
class UETANKS_API ABaseTank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Mesh properties
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TankBodyMeshComponent;
	
	//Movement properties
	UPROPERTY(VisibleAnywhere, Category="Movement")
	UPawnMovementComponent* TankMovementComponent;

	//Movement properties
	UPROPERTY(EditAnywhere, Category = "Aiming")
	float AimSpeed;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement Methods
	void MoveTankVertical(float VerticalMoveDirection);
	void MoveTankHorizontal(float HorizontalMoveDirection);
	

	//Aiming
	void AimHeadVertical(float VerticalLookDirection);
	void AimHeadHorizontal(float HorizontalLookDirection);

	//Firing
	void OnFireWeapon();
};

