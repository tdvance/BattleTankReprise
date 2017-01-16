// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 *
 */
UCLASS()
class BATTLETANKREPRISE_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	//how close can the AI tank get to the player
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 3000;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void AimAtPlayerTank();

};
