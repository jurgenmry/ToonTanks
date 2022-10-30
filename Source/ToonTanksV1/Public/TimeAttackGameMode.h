// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeAttackGameMode.generated.h"


class ATank;
class AToonTanksPlayerController;
/**
 * 
 */
UCLASS()
class TOONTANKSV1_API ATimeAttackGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void ActorDied(AActor* DeadActor);        // function to implement for dead actor

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Minutes = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Seconds = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SecondsToAdd = 2;

	void AddScore();

	void AddSeconds();

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Score = 0;

private:

	ATank* Tank;                        // declare class var pointer for player
	AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f;

	//UFUNCTION(BlueprintImplementableEvent)
	void HandleGameStart();

	void Countdown();
	
};
