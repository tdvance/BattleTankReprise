// (C) Todd D. Vance, Deplorable Mountaineer

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKREPRISE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);
	FDeathDelegate OnDeath;


protected:


private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly)
		float StartingHealth = 100.f;
	float CurrentHealth = StartingHealth;

};
