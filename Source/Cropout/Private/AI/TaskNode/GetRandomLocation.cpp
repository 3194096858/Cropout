// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/GetRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UGetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UNavigationSystemV1* NavigationSystemV1 = nullptr;
	UBlackboardComponent* BlackboardComponent = nullptr;
	AAIController* AIController = nullptr;
	FNavLocation RandomLocation = FNavLocation(FVector::ZeroVector);
	FVector CenterLocation;
	NavigationSystemV1 = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavigationSystemV1 == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGetRandomLocation::ExecuteTask(): NavigationSystemV1 == nullptr"));
		return EBTNodeResult::Failed;
	};
	BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (BlackboardComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGetRandomLocation::ExecuteTask(): BlackboardComponent == nullptr"));
		return EBTNodeResult::Failed;
	};
	AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGetRandomLocation::ExecuteTask(): AIController == nullptr"));
		return EBTNodeResult::Failed;
	};
	CenterLocation = AIController->GetPawn()->GetActorLocation();
	NavigationSystemV1->GetRandomPointInNavigableRadius(CenterLocation,this->PatrolRadius,RandomLocation);
	BlackboardComponent->SetValueAsVector(FName("RandomLocation"),RandomLocation.Location);
	//UE_LOG(LogTemp, Warning, TEXT("	return EBTNodeResult::Succeeded"));

	return EBTNodeResult::Succeeded;
}