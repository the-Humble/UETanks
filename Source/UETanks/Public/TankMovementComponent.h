// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = Movement, meta = (BlueprintSpawnableComponent))
class UETANKS_API UTankMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

	//Begin UActorComponent Interface
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	//End UActorComponent Interface

	//Begin UMovementComponent Interface
	virtual float GetMaxSpeed() const override { return MaxMoveSpeed; }

public:

	//Max Speed at which the tank can move in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TankMovement)
	float MaxMoveSpeed;

	//Rate at which a tank accelerates in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TankMovement)
	float Acceleration;

	//Rate at which the tank decelerates in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TankMovement)
	float Deceleration;

	//Speed at which the tank rotates before moving again
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TankMovement)
	float RotateSpeed;

protected:

	//Rotates Tank to match ionput direction
	void RotateTank(FVector TargetDirection, float DeltaTime);
	
	/** Update Velocity based on input. Also applies gravity. */
	virtual void ApplyControlInputToVelocity(float DeltaTime);

	/** Prevent Pawn from leaving the world bounds (if that restriction is enabled in WorldSettings) */
	virtual bool LimitWorldBounds();

	/** Set to true when a position correction is applied. Used to avoid recalculating velocity when this occurs. */
	UPROPERTY(Transient)
	uint32 bPositionCorrected:1;
};
