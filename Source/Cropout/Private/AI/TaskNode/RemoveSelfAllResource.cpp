// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/RemoveSelfAllResource.h"



#include "Interface/GameObjectInteractionInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "NPC/NPC.h"



EBTNodeResult::Type URemoveSelfAllResource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ANPC* NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (NPC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("URemoveSelfAllResource::ExecuteTask(): NPC == nullptr"));
		return EBTNodeResult::Failed;
	}
	NPC->RemoveSelfAllResource();

	return EBTNodeResult::Succeeded;
}