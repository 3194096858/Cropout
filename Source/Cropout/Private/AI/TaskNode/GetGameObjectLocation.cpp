// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/GetGameObjectLocation.h"
#include "Interface/GameObjectInteractionInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"




EBTNodeResult::Type UGetGameObjectLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	//OwnerComp.PauseLogic(true);
	FVector ObjectLocation;
	FVector ObjectOffsetLocation;
	const float OffsetValue = 300.0f;
	IGameObjectInteractionInterface* InteractionInterface = Cast<IGameObjectInteractionInterface>(OwnerComp.GetAIOwner()->GetPawn());
    if (InteractionInterface == nullptr)
    {
		UE_LOG(LogTemp, Warning, TEXT("UGetGameObjectLocation::ExecuteTask(): InteractionInterface == nullptr"));
        return EBTNodeResult::Failed;
    }
	ObjectLocation = InteractionInterface->GetGameObjectLocation();
	ObjectOffsetLocation = ObjectLocation + FVector(FMath::RandPointInCircle(OffsetValue), 0.0f);
	//UKismetSystemLibrary::DrawDebugSphere(GetWorld(), ObjectLocation, 200.0f, 12, FLinearColor::Red,20.0f);
	//UKismetSystemLibrary::DrawDebugSphere(GetWorld(), ObjectOffsetLocation, 100.0f, 12, FLinearColor::Red,20.0f);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("GameObjectLocation"),ObjectOffsetLocation );
	return EBTNodeResult::Succeeded;
}
