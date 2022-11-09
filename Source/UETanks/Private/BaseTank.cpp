// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTank.h"

#include "TankMovementComponent.h"

// Sets default values
ABaseTank::ABaseTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(TEXT("Tank Movement Controller"));
	TankMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Mesh"));
}

// Called when the game starts or when spawned
void ABaseTank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);	
	PlayerInputComponent->BindAxis("MoveVertical", this, &ABaseTank::MoveTankVertical);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ABaseTank::MoveTankHorizontal);

	PlayerInputComponent->BindAxis("AimVertical", this, &ABaseTank::AimHeadVertical);
	PlayerInputComponent->BindAxis("AimHorizontal", this, &ABaseTank::AimHeadHorizontal);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABaseTank::OnFireWeapon);
}

void ABaseTank::MoveTankVertical(float VerticalMoveDirection)
{
	AddMovementInput(FVector::ForwardVector, VerticalMoveDirection);
}

void ABaseTank::MoveTankHorizontal(float HorizontalMoveDirection)
{
	AddMovementInput(FVector::RightVector, HorizontalMoveDirection);
}

void ABaseTank::AimHeadVertical(float VerticalLookDirection)
{
}

void ABaseTank::AimHeadHorizontal(float HorizontalLookDirection)
{
}

void ABaseTank::OnFireWeapon()
{
}
