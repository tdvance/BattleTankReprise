// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 *  Holds turret properties and rotate method
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKREPRISE_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//-1 is max downward movement, +1 is max upward movement
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreesPerSecond = 20;
	
	
};
