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


void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("tick"));
	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair()
{
	// move tank barrel towards where a shot would hit where cross hair intersects world
	if (!GetControlledTank())
	{
		return; //do nothing if no tank
	}

	FVector HitLocation = FVector(1.0);

	if (GetSightRayHitLocation(OUT HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}


bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const
{
	// find cross hair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation,
		ViewportSizeY*CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	// deproject screen position of cross hair to world direction
	FVector LookDirection = GetLookDirection(ScreenLocation);
	if (LookDirection == FVector::ZeroVector)
	{
		return false;
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString());
	}


	FHitResult HitResult;
	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();

	if (!GetWorld()->LineTraceSingleByChannel(OUT HitResult, CameraLocation,
		CameraLocation + LineTraceRange*LookDirection, ECollisionChannel::ECC_Visibility))
	{
		return false;
	}

	HitLocation = HitResult.Location;

	//line trace along that direction and see what we hit (up to max range)
	// if hit landscape, set HitLocation to coordinates and return true	
	return true;
}


FVector ATankPlayerController::GetLookDirection(FVector2D ScreenLocation) const
{
	FVector WorldLocation;
	FVector WorldDirection;

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, 
		OUT WorldLocation, OUT WorldDirection))
	{
		return WorldDirection;

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WorldDirection not found"));
		return FVector::ZeroVector;
	}
}