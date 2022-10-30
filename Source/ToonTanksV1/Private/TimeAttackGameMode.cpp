// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAttackGameMode.h"
#include"Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "BaseMinion.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"


void ATimeAttackGameMode::ActorDied(AActor* DeadActor) 
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
        AddScore();
        AddSeconds();
    }
    else if (ABaseMinion* DestroyedMinion = Cast<ABaseMinion>(DeadActor))
    {
        DestroyedMinion->HandleDestruction();
        AddScore();
        AddSeconds();
    }
}

void ATimeAttackGameMode::AddScore() 
{
    Score = Score + 100;
}

void ATimeAttackGameMode::AddSeconds() 
{
    Seconds = Seconds + SecondsToAdd;
    if (Seconds > 60)
    {
        Minutes ++;
        Seconds = Seconds - 60;
    }
    
}

void ATimeAttackGameMode::BeginPlay() 
{
    Super::BeginPlay();
    HandleGameStart(); 
}
    
void ATimeAttackGameMode::HandleGameStart() 
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

        FTimerHandle TimerHandleCountdown;
        GetWorldTimerManager().SetTimer(TimerHandleCountdown, this, &ATimeAttackGameMode::Countdown, 1.f, true, 3.0);
    }
    
}

void ATimeAttackGameMode::Countdown() 
{
    if (Seconds != 0 )
    {
        Seconds = Seconds - 1;
    }
    else
    {
        if (Minutes == 0 && Seconds <= 0)
        {
            GameOver(false);
        }
        
        else
        {
            Minutes = Minutes -1;
            Seconds = 59;
        }
    }
}
