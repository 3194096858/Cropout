// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/RemoveCrate.h"



#include "NPC/NPC.h"
#include "AIController.h"




EBTNodeResult::Type URemoveCrate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ANPC* NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (NPC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("URemoveCrate::ExecuteTask(): NPC == nullptr"));
		return EBTNodeResult::Failed;
	}
	NPC->RemoveCrate();
	return EBTNodeResult::Succeeded;
}