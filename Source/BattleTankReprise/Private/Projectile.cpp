// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankReprise.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMeshComponent"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlastComponent"));

	//TODO check these transform rules to make sure they are right
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlastComponent"));

	ImpactBlast->bAutoActivate = false;

	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForceComponent"));

	ExplosionForce->bAutoActivate = false;

	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::LaunchProjectile(float speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector*speed);
	ProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, 
		&AProjectile::DestroyDelegate, DestroyDelay);
}

void AProjectile::DestroyDelegate()
{
	Destroy();
}

