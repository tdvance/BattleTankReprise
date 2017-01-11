// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKREPRISE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;

	FVector GetLookDirection(FVector2D ScreenLocation) const;
		

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = .333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;

};
