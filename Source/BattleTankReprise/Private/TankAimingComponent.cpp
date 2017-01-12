// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankReprise.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;//TODO should this tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
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

	FVector LaunchVelocity;
	FVector AimDirection;

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OUT LaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")), HitLocation, LaunchSpeed, 
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);

		UE_LOG(LogTemp, Warning, TEXT("%s Aiming toward: %s"), 
			*GetOwner()->GetName(),*AimDirection.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s can't aim; start: %s; end: %s; speed: %f"),
			*GetOwner()->GetName(),
			*Barrel->GetSocketLocation(FName("Projectile")).ToString(),
			*HitLocation.ToString(),
			(double)LaunchSpeed
			);
	}


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(5);

	
}


