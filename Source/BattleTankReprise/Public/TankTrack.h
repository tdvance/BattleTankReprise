// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank track properties, to apply motion/rotation forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKREPRISE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float amount);
	
private:
	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000;
	
	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
		const FHitResult& Hit);

	void DriveTrack();

	float CurrentThrottle = 0;

};
