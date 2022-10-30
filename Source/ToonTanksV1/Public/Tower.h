// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TimerManager.h"
#include "Tower.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TOONTANKSV1_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	ATank* Tank;


	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 300.f;

	FTimerHandle FireRateTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 2.f;

	void CheckFireCondition();

	bool InFireRange();

};
