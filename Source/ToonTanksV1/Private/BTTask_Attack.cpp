// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseMinion.h"

UBTTask_Attack::UBTTask_Attack() 
{
    NodeName = "Attack";
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    ABaseMinion* BaseMinion = Cast<ABaseMinion>(OwnerComp.GetAIOwner()->GetPawn());

    if (BaseMinion == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    BaseMinion->Fire();
    BaseMinion->bAttacking = true;

    return EBTNodeResult::Succeeded;

}

