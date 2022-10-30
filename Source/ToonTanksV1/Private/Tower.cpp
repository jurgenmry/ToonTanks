// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    
    if (InFireRange())
        {
            RotateTurret(Tank->GetActorLocation());
        }
}

void ATower::BeginPlay() 
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
  
    /* GetWorldTimerManager().SetTimer(SpawnDelayTimerHandle, this, &ATower::Fire, SpawnDelay, false); */

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true, 3.0f);

}

void ATower::CheckFireCondition() 
{
    if (Tank->IsHidden())
    {
        //Do nothing xD
    }
    else if (InFireRange())
    {
        Fire();
    }
}

bool ATower::InFireRange() 
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
