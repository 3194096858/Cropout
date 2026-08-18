// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/AddHat.h"


#include "NPC/NPC.h"
#include "AIController.h"


EBTNodeResult::Type UAddHat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ANPC* NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (NPC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAddHat::ExecuteTask(): NPC == nullptr"));
		return EBTNodeResult::Failed;
	}
	NPC->AddHat();
	return EBTNodeResult::Succeeded;
}
