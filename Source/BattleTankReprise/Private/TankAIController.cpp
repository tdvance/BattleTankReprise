// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankReprise.h"
#include "TankAIController.h"




ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}

ATank* ATankAIController::GetPlayerTank() const
{
	return  Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller Begin Play"));

	ATank* Tank = GetControlledTank();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("  AI Controlled tank: %s"), *Tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("  AI No controlled tank!"));
	}

	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("  AI found player tank: %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("  AI found no player tank!"));
	}
}


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("tick"));
	AimAtPlayerTank();

}


void ATankAIController::AimAtPlayerTank()
{
	// move tank barrel towards where a shot would hit where cross hair intersects world
	if (!GetPlayerTank() || !GetControlledTank())
	{
		UE_LOG(LogTemp, Error, TEXT("missing tank!"));
		return; //do nothing if no tank
	}

	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

}
