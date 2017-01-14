// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKREPRISE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
		void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
		void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);


private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

};
