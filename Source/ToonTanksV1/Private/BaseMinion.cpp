// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMinion.h"
#include "TimeAttackGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Tank.h"
#include "AIController.h"
#include "LevelUpGameMode.h"





ABaseMinion::ABaseMinion()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

}

float ABaseMinion::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	
	if (DamageToApply <= 0.f) return DamageToApply;

	if (Health <= 0.f && TimeAttackGameMode)
	{
		TimeAttackGameMode->ActorDied(this);
	}
	else if (Health <= 0.f && LevelUpGameMode)
	{
		LevelUpGameMode->ActorDied(this);
	}

	return DamageToApply;
}

// Called when the game starts or when spawned
void ABaseMinion::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	TimeAttackGameMode = Cast<ATimeAttackGameMode>(UGameplayStatics::GetGameMode(this));
	LevelUpGameMode = Cast<ALevelUpGameMode>(UGameplayStatics::GetGameMode(this));

	/* GetWorldTimerManager().SetTimer(SpawnDelayTimerHandle, this, &ABaseMinion::Fire, SpawnDelay, false); */

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ABaseMinion::AttackCondition, FireRate, true, 3.0f);

}

void ABaseMinion::AttackCondition() 
{
	if (Tank->IsHidden())
    {
 		bAttacking = false;
    }
    else if (InFireRange())
    {
		//Fire();
    }
}

bool ABaseMinion::InFireRange() 
{
	if (Tank)
    {    
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
            if (Distance <= FireRange)
            {
                return true;
            }
    }
    return false;
}

void ABaseMinion::Fire() 
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
	
	
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	
}

// Called every frame
void ABaseMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

