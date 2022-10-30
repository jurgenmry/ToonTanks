// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "BaseMinion.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"

void ALevelUpGameMode::ActorDied(AActor* DeadActor) 
{
    if (DeadActor == Tank)                                             // check if dead actor is player
    {
        Tank->HandleDestrucion();                                      // call function on player to destroy
        if (ToonTanksPlayerController)                                 // check if player function on getcontroller is valid                  
        {
            ToonTanksPlayerController->SetPlayerEnableState(false);
        }
        GameOver(false);
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
    }
    else if (ABaseMinion* DestroyedMinion = Cast<ABaseMinion>(DeadActor))
    {
        DestroyedMinion->HandleDestruction();
    }
}

void ALevelUpGameMode::BeginPlay() 
{
    Super::BeginPlay();
    HandleGameStart(); 
}

void ALevelUpGameMode::HandleGameStart() 
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));      //set pawn var
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnableState(false);
        
        FTimerHandle PlayerEnableTimerHandle;               //create timerhandle                          
        FTimerDelegate DelayDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true); //create delegate
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, DelayDelegate, StartDelay, false);   //pass handle & delegate + params to SetTimer()
    }
}

bool ALevelUpGameMode::LevelUp(int Exp) 
{
    if (Exp >= ExperienceToLevelUp)
    {
        Level = Level++;
        ExperienceToLevelUp = ExperienceToLevelUp * 2;
        UE_LOG(LogTemp, Warning, TEXT("Level %i"), ExperienceToLevelUp);
        UE_LOG(LogTemp, Warning, TEXT("Level %i"), Level);

        Tank->AddSkill();
        return true;
    }
    else return false;
}

