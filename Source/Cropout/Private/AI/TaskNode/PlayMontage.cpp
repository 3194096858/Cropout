// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/PlayMontage.h"


#include "AIController.h"


#include "NPC/NPC.h"



EBTNodeResult::Type UPlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ANPC* NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (NPC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlayMontage::ExecuteTask(): NPC == nullptr"));
		return EBTNodeResult::Failed;
	}
	if (TargetMontage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlayMontage::ExecuteTask(): TargetMontage == nullptr"));
		return EBTNodeResult::Failed;
	}
	NPC->PlayAnimMontage(TargetMontage);
	return EBTNodeResult::Succeeded;
}
