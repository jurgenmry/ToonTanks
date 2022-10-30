// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "TimeAttackGameMode.h"
#include "LevelUpGameMode.h"



// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

float ABasePawn::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	
	if (HasAuthority())
	{
		Health -= DamageToApply;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	
	if (DamageToApply <= 0.f) return DamageToApply;

	if (Health <= 0.f && TimeAttackGameMode && HasAuthority())
	{
		TimeAttackGameMode->ActorDied(this);
	}
	else if (Health <= 0.f && LevelUpGameMode && HasAuthority())
	{
		LevelUpGameMode->ActorDied(this);
	}

	return DamageToApply;
}

void ABasePawn::BeginPlay() 
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	TimeAttackGameMode = Cast<ATimeAttackGameMode>(UGameplayStatics::GetGameMode(this));
	LevelUpGameMode = Cast<ALevelUpGameMode>(UGameplayStatics::GetGameMode(this));
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(LookAtRotation);
}

void ABasePawn::Fire() 
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);

	//Server_Fire(Location, Rotation);
	
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	//DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 12.0f, 20, FColor::Red, false, 3.0f);
}

//bool ABasePawn::Server_Fire_Validate(FVector Location, FRotator Rotation)
//{
//	return true;
//}
//
//void ABasePawn::Server_Fire_Implementation(FVector Location, FRotator Rotation)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Server_Fire_Implementation"));
//}

