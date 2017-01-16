//(C) Todd D. Vance, Deplorable Mountaineer
#include "BattleTankReprise.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}



void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{	

	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}

	FVector LaunchVelocity;
	FVector AimDirection;

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OUT LaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")), HitLocation, LaunchSpeed, 
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);

	}
	else
	{
		//can't aim
	}


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
		
}


