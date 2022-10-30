// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Tank.generated.h"
/**
 * 
 */

UCLASS()
class TOONTANKSV1_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps);

	void HandleDestrucion();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool PowerUpFireActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool PowerUpFireRateActive;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float FireRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 800.f;

	void AddSkill();

	void Fire();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPause();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPaused;
	
private:

	UPROPERTY(EditAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USceneComponent* ProjectileSpawnPointA;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USceneComponent* ProjectileSpawnPointB;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 250.f;

	FTimerHandle FireRateTimerHandle;
	
	//Input Functions

	//UFUNCTION(Server, Reliable)
	void Move(float Value);
	//UFUNCTION(Server, Reliable)
	void Turn(float Value);
	void Pause();

	APlayerController* TankPlayerController;

};
