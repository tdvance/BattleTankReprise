//(C) Todd D. Vance, Deplorable Mountaineer

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Ready,
	Aiming,
	Reloading,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKREPRISE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Input")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

	EFiringStatus GetFiringState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
		int32 AmmoRemaining = 20;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 5.0f;



	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, 
		FActorComponentTickFunction *ThisTickFunction) override;

	virtual void BeginPlay() override;
	
	bool IsBarrelMoving();

	void MoveBarrelTowards();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	FVector AimDirection = FVector::ZeroVector;
	double LastFireTime = 0;
	bool bBarrelMoving = false;

};
