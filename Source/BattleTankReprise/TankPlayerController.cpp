// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankReprise.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller Begin Play"));

	ATank* Tank = GetControlledTank();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("  Controlled tank: %s"), *Tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("  No controlled tank!"));
	}
}

void ATankPlayerController::AimTowardsCrosshair()
{
	// move tank barrel towards where a shot would hit where crosshair intersects world
	if (!GetControlledTank())
	{
		return; //do nothing if no tank
	}

	// Get world location if linetrace through crosshair
	// if hits landscape
	    // tell controlled tank to aim at this point
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("tick"));

	AimTowardsCrosshair();

}