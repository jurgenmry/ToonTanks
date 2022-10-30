// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseMinion.generated.h"

UCLASS()
class TOONTANKSV1_API ABaseMinion : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMinion();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleDestruction();
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float MaxHealth = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Health = 0.f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AttackCondition();

	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bAttacking;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

private:

	class ATank* Tank;

	UPROPERTY(EditAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	bool InFireRange();

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 600.f;

	FTimerHandle FireRateTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 2.f;
		
	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 25.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")	
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")	
	USoundBase* FireSound;

	class ATimeAttackGameMode* TimeAttackGameMode;
	class ALevelUpGameMode* LevelUpGameMode;
};
