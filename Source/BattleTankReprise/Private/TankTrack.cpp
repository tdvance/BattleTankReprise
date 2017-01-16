// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankReprise.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Amount)
{
	FString Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s Throttle: %f"), *Name, Amount);
	//TODO clamp throttle to -1...1

	FVector ForceApplied = GetForwardVector() * FMath::Clamp<float>(Amount,-1,1) * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}
