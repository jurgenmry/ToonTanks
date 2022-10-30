// Fill out your copyright notice in the Description page of Project Settings.

#include "AIControllerMinion.h"
#include "BaseMinion.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"




void AAIControllerMinion::BeginPlay() 
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    /* SetFocus(PlayerPawn);
    MoveToActor(PlayerPawn); */

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
    }
}

void AAIControllerMinion::Tick(float DeltaSeconds) 
{
    Super::Tick(DeltaSeconds);

    if (LineOfSightTo(PlayerPawn))
    {
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerDead"), PlayerPawn->IsHidden());
    }
    else
    {
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }
    
}
