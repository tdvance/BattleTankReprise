//(C) Todd D. Vance, Deplorable Mountaineer
#include "BattleTankReprise.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("Tick"));
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AmmoRemaining <= 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Ready;
	}
}

void UTankAimingComponent::BeginPlay()
{
	//Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return true;
	}
	return bBarrelMoving;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{

	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}

	FVector LaunchVelocity;

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OUT LaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")), HitLocation, LaunchSpeed,
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();

	}
}

void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	bBarrelMoving = false;
	bBarrelMoving = bBarrelMoving || Barrel->Elevate(DeltaRotator.Pitch);
	float Yaw = DeltaRotator.Yaw;
	if (Yaw > 180)
	{
		Yaw -= 360;
	}
	else if (Yaw < -180)
	{
		Yaw += 360;
	}
	bBarrelMoving = bBarrelMoving || Turret->Rotate(Yaw);
}



void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel))
	{
		return;
	}
	if (FiringStatus != EFiringStatus::Reloading && FiringStatus != EFiringStatus::OutOfAmmo)
	{
		//spawn projectile at barrel projectile socket.
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")), FActorSpawnParameters());
		if (!ensure(Projectile))
		{
			return;
		}

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		AmmoRemaining--;
	}
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}
