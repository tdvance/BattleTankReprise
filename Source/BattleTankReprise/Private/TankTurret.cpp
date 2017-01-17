// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankReprise.h"
#include "TankTurret.h"




bool UTankTurret::Rotate(float RelativeSpeed)
{

	float YawChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewYaw = RelativeRotation.Yaw + YawChange;
	SetRelativeRotation(FRotator(0, RawNewYaw, 0));
	return FMath::Abs(YawChange) > .01f;
}
