// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/UpdateNPCState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/NPCStateInterface/NPCStateInterface.h"
#include "AIController.h"

EBTNodeResult::Type UUpdateNPCState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* BlackboardComponent = nullptr;
	AAIController* AIController = nullptr;
	AIController = OwnerComp.GetAIOwner();
	AActor* AIControllerOwner = AIController->GetPawn();
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (AIController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UUpdateNPCState::ExecuteTask(): AIController == nullptr"));
		return EBTNodeResult::Failed;
	};
	INPCStateInterface* NPCStateInterface = Cast<INPCStateInterface>(AIControllerOwner);
	if (NPCStateInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UUpdateNPCState::ExecuteTask(): NPCStateInterface == nullptr"));
		return EBTNodeResult::Failed;
	}
	NPCStateInterface->UpdateNPCState(this->NPCState);
	BlackboardComponent->SetValueAsName(FName("NPCState"),UEnum::GetValueAsName(NPCState));

	return EBTNodeResult::Succeeded;
}









