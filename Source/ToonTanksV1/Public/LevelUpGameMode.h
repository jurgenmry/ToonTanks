// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelUpGameMode.generated.h"

/* *  TO ADD:
 * 			-Ability Tree(Weapons{Attacks}-Defense{Shields/Health}-Passive{Support})
 * 
 *			-Weapons(Drone-ChemicalBomb-DropMines-/AirBombs-Flamethrower-FireTurret-/TripleShot-/RocketLauncher)
 * 			-Defense(/Shield+-/+Health-HealthRegen-ShieldRegen-/ReduceIncomingDmg)
 * 			-Passive(/+Speed-CriticalDmg-AllDmgBoost-IncreasePickUpRadius-/FireRate)
 * 
 *          -ProjectilesMods(DamageArea-Incendiary-CriticalHit)
 */
UCLASS()
class TOONTANKSV1_API ALevelUpGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void ActorDied(AActor* DeadActor);        // function to implement for dead actor

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level =1;

	UFUNCTION(BlueprintCallable)
	bool LevelUp(int Exp);

	/* UFUNCTION(BlueprintCallable)
	void SkillHUD();
 */
protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	int ExperienceToLevelUp = 100;

private:

	class ATank* Tank;                        // declare class var pointer for player
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();

};
