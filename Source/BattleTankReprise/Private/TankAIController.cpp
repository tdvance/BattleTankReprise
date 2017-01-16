// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankReprise.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	/*UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller Begin Play"));

	ATank* Tank = Cast<ATank>(GetPawn());
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("  AI Controlled tank: %s"), *Tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("  AI No controlled tank!"));
	}

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("  AI found player tank: %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("  AI found no player tank!"));
	}*/
}


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ATank* Tank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	AimAtPlayerTank();
	Tank->Fire();
	MoveToActor(PlayerTank, AcceptanceRadius);//TODO check radius is in cm
}


void ATankAIController::AimAtPlayerTank()
{
	ATank* Tank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// move tank barrel towards where a shot would hit where cross hair intersects world
	if (!Tank || !PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("missing tank!"));
		return; //do nothing if no tank
	}

	Tank->AimAt(PlayerTank->GetActorLocation());

}
