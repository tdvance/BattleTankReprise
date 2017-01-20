// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankReprise.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "tank.h"


void ATankAIController::OnTankDeath()
{
	APawn* Tank = GetPawn();
	if (!Tank)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("AI Tank died"));
	Tank->DetachFromControllerPendingDestroy();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
			return;
		}
		//subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* Tank = GetPawn();
	if (!Tank)
	{
		return;
	}

	AimAtPlayerTank();


	EFiringStatus FiringStatus =
		Tank->FindComponentByClass<UTankAimingComponent>()->GetFiringState();
	if (FiringStatus == EFiringStatus::Ready)
	{
		Tank->FindComponentByClass<UTankAimingComponent>()->Fire();
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
	APawn* Tank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!Tank)
	{
		return; //probably dead
	}
	TankAimingComponent->AimAt(Tank->GetActorLocation());
}
