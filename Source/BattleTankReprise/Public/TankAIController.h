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



protected:
	//how close can the AI tank get to the player
	UPROPERTY(EditDefaultsOnly)
		float AcceptanceRadius = 10000;

	UFUNCTION()
		void OnTankDeath();

private:

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	void AimAtPlayerTank();

};
