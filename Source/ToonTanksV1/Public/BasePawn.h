// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKSV1_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleDestruction();

	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float MaxHealth = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Health = 0.f;

protected:

	virtual void BeginPlay() override;

	
	void RotateTurret(FVector LookAtTarget);

	void Fire();

	/*UFUNCTION(Server, Reliable, WithValidation)
	void Server_Fire(FVector Location, FRotator Rotation);
	bool Server_Fire_Validate(FVector Location, FRotator Rotation);
	void Server_Fire_Implementation(FVector Location, FRotator Rotation);*/

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

private:

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	
	
	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;


	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")	
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")	
	USoundBase* FireSound;

	class ATimeAttackGameMode* TimeAttackGameMode;
	class ALevelUpGameMode* LevelUpGameMode;
};
