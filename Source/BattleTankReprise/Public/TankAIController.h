// (C) Todd D. Vance, Deplorable Mountaineer

#pragma once

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



	virtual void Tick(float DeltaSeconds) override;

	void AimAtPlayerTank();

};
