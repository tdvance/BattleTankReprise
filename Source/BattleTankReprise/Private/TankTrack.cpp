//(C) Todd D. Vance, Deplorable Mountaineer
#include "BattleTankReprise.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::SetThrottle(float Amount)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Amount, -1, 1);
}

void UTankTrack::DriveTrack()
{
	FString Name = GetName();

	FVector ForceApplied = GetForwardVector()*CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::ApplySidewaysForce()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector TankVelocity = GetOwner()->GetVelocity();
	FVector TankRight = GetOwner()->GetActorRightVector();
	float SlippageSpeed = FVector::DotProduct(TankVelocity, TankRight);
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime*TankRight;
	FVector CorrectionForce = CorrectionAcceleration*Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())->GetMass() / 2.f;
	Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())->AddForce(CorrectionForce);
}
