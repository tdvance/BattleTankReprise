// (C) Todd D. Vance, Deplorable Mountaineer

#include "BattleTankReprise.h"
#include "Tank.h"

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Damage;
	if (CurrentHealth <= Damage)
	{
		CurrentHealth = 0;
		DamageApplied = CurrentHealth;
		OnDeath.Broadcast();
	}
	else
	{
		CurrentHealth -= Damage; 
	}
	return DamageApplied;
}

float ATank::GetHealthPercent() const
{
	return CurrentHealth / StartingHealth;
}

ATank::ATank()
{ 
	PrimaryActorTick.bCanEverTick = false;
}




