// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"

#include "DrawDebugHelpers.h"

void UTankMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{

	if (ShouldSkipUpdate(DeltaTime))
	{
		return;
	}
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent)
	{
		return;
	}
	const AController* Controller = PawnOwner->GetController();
	if (Controller && Controller->IsLocalController())
	{
		// apply input for local players but also for AI that's not following a navigation path at the moment
		if (Controller->IsLocalPlayerController() == true || Controller->IsFollowingAPath() == false || bUseAccelerationForPaths)
		{
			ApplyControlInputToVelocity(DeltaTime);
		}
		// if it's not player controller, but we do have a controller, then it's AI
		// (that's not following a path) and we need to limit the speed
		else if (IsExceedingMaxSpeed(MaxMoveSpeed) == true)
		{
			Velocity = Velocity.GetUnsafeNormal() * MaxMoveSpeed;
		}

		LimitWorldBounds();
		bPositionCorrected = false;

		// Move actor
		FVector Delta = Velocity * DeltaTime;

		if (!Delta.IsNearlyZero(1e-6f))
		{
			const FVector OldLocation = UpdatedComponent->GetComponentLocation();
			const FQuat Rotation = UpdatedComponent->GetComponentQuat();

			FHitResult Hit(1.f);
			SafeMoveUpdatedComponent(Delta, Rotation, true, Hit);

			if (Hit.IsValidBlockingHit())
			{
				HandleImpact(Hit, DeltaTime, Delta);
				// Try to slide the remaining distance along the surface.
				SlideAlongSurface(Delta, 1.f-Hit.Time, Hit.Normal, Hit, true);
			}

			// Update velocity
			// We don't want position changes to vastly reverse our direction (which can happen due to penetration fixups etc)
			if (!bPositionCorrected)
			{
				const FVector NewLocation = UpdatedComponent->GetComponentLocation();
				Velocity = ((NewLocation - OldLocation) / DeltaTime);
			}
		}
		
		// Finalize
		UpdateComponentVelocity();
	}
}

void UTankMovementComponent::RotateTank(FVector TargetDirection, float DeltaTime)
{

	FRotator FinalRotation = FRotationMatrix::MakeFromX(TargetDirection).Rotator();
	PawnOwner->SetActorRotation(FMath::RInterpConstantTo(PawnOwner->GetActorRotation(), FinalRotation, DeltaTime, RotateSpeed));
	
	DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(),PawnOwner->GetActorLocation()+TargetDirection*100, FColor::Red);
	DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(),PawnOwner->GetActorLocation()+PawnOwner->GetActorForwardVector()*100, FColor::Green);

	ConsumeInputVector();
}


void UTankMovementComponent::ApplyControlInputToVelocity(float DeltaTime)
{
	const FVector ControlAcceleration = GetPendingInputVector().GetClampedToMaxSize(1.f);
	FVector InputDirection = ControlAcceleration.GetSafeNormal();

	const float ForwardDotInput = FVector::DotProduct(PawnOwner->GetActorForwardVector(), InputDirection);
	const float BackwardDotInput = FVector::DotProduct(-PawnOwner->GetActorForwardVector(), InputDirection);

	float FinalDotInput = ForwardDotInput > BackwardDotInput ? ForwardDotInput : BackwardDotInput;

	if(abs(FinalDotInput)<0.999f && InputDirection.Size()>0.05f)
	{
		Velocity = FVector::ZeroVector;
		DrawDebugLine(GetWorld(), PawnOwner->GetActorLocation(),PawnOwner->GetActorLocation()+InputDirection*200, FColor::Blue);
		if(FinalDotInput == BackwardDotInput)
		{
			InputDirection = -InputDirection;
		}

		RotateTank(InputDirection, DeltaTime);
		return;
	}

	const float AnalogInputModifier = (ControlAcceleration.SizeSquared() > 0.f ? ControlAcceleration.Size() : 0.f);
	const float MaxPawnSpeed = GetMaxSpeed() * AnalogInputModifier;

	// Apply acceleration and clamp velocity magnitude.
	const float NewMaxSpeed = (IsExceedingMaxSpeed(MaxPawnSpeed)) ? Velocity.Size() : MaxPawnSpeed;
	Velocity = ControlAcceleration * FMath::Abs(MaxMoveSpeed);
	
	ConsumeInputVector();
}

bool UTankMovementComponent::LimitWorldBounds()
{
	return false;
}
