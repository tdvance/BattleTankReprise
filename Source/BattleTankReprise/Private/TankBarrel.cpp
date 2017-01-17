// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankReprise.h"
#include "TankBarrel.h"


bool UTankBarrel::Elevate(float RelativeSpeed)
{
	//adjust barrel pitch and yaw by delta, taking into account delta seconds
	

	float ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float NewPitch = FMath::Clamp<float>(
		RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(NewPitch, 0, 0));
	return FMath::Abs(NewPitch - RelativeRotation.Pitch) > .01f;
}
