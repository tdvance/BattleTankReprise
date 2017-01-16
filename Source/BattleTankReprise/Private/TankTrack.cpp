//(C) Todd D. Vance, Deplorable Mountaineer
#include "BattleTankReprise.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Amount)
{
	FString Name = GetName();

	FVector ForceApplied = GetForwardVector() * FMath::Clamp<float>(Amount,-1,1) * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}
