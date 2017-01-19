// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankReprise.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimAtPlayerTank();


	EFiringStatus FiringStatus = 
		GetPawn()->FindComponentByClass<UTankAimingComponent>()->GetFiringState();
	if (FiringStatus == EFiringStatus::Ready)
	{
		GetPawn()->FindComponentByClass<UTankAimingComponent>()->Fire();
	}

	MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), AcceptanceRadius);//TODO check radius is in cm
}


void ATankAIController::AimAtPlayerTank()
{
	UTankAimingComponent* TankAimingComponent = 
		GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(TankAimingComponent))
	{
		return;
	}
	TankAimingComponent->AimAt(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
}
