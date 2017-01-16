// (C) Todd D. Vance, Deplorable Mountaineer

#include "BattleTankReprise.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{ 
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}


void ATank::AimAt(FVector HitLocation)
{

	if (!ensure(TankAimingComponent))
	{
		TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
		if (!ensure(TankAimingComponent))
		{
			return;
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("Aim"));


	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds);
	if (!ensure(Barrel))
	{
		return;
	}
	if (isReloaded)
	{
		//spawn projectile at barrel projectile socket.
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")), FActorSpawnParameters());

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
