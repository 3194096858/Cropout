// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/Attack.h"


#include "NPC/NPC.h"
#include "AIController.h"

EBTNodeResult::Type UAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ANPC* NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (NPC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAttack::ExecuteTask(): NPC == nullptr"));
		return EBTNodeResult::Failed;
	}
	NPC->Attack();
	return EBTNodeResult::Succeeded;
}


EBTNodeResult::Type UAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);
	/*ANPC* NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (NPC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAttack::ExecuteTask(): NPC == nullptr"));
		return EBTNodeResult::Failed;
	}
	NPC->StopAnimMontage();
	UE_LOG(LogTemp, Warning, TEXT("UAttack::AbortTask(): Aborted !!!!!!!"));*/
	return EBTNodeResult::Aborted;
}