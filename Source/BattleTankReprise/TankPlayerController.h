// (C) Todd D. Vance, Deplorable Mountaineer

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANKREPRISE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);


private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;

	FVector GetLookDirection(FVector2D ScreenLocation) const;


	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = .333f;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0f;

};
