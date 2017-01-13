// Fill out your copyright notice in the Description page of Project Settings.

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

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	/*UE_LOG(LogTemp, Warning, TEXT("Tank: %s; Barrel location: %s; \n  HitLocation: %s LaunchSpeed : %f"), 
		*GetOwner()->GetName(), *Barrel->GetComponentLocation().ToString(),  *HitLocation.ToString(), (double)LaunchSpeed);*/

	if (!Barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing barrel!"), *GetOwner()->GetName());

		return;
	}

	if (!Turret)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing turret!"), *GetOwner()->GetName());

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
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
		
}


