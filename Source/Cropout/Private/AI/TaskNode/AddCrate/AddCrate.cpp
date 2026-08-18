// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/AddCrate/AddCrate.h"


#include "NPC/NPC.h"
#include "AIController.h"


EBTNodeResult::Type UAddCrate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ANPC* NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (NPC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAddCrate::ExecuteTask(): NPC == nullptr"));
		return EBTNodeResult::Failed;
	}
	NPC->AddCrate();
	return EBTNodeResult::Succeeded;
}
