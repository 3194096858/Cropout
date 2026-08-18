// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/GetDistanceBetweenSelfAndObject.h"


#include "Interface/GameObjectInteractionInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"




EBTNodeResult::Type UGetDistanceBetweenSelfAndObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector ObjectLocation;
	float Distance = 0.0f;
	IGameObjectInteractionInterface* InteractionInterface = Cast<IGameObjectInteractionInterface>(OwnerComp.GetAIOwner()->GetPawn());
	if (InteractionInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGetDistanceBetweenSelfAndObject::ExecuteTask(): InteractionInterface == nullptr"));
		return EBTNodeResult::Failed;
	}
	ObjectLocation = InteractionInterface->GetGameObjectLocation();
	Distance = FVector::Distance(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), ObjectLocation);
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(FName("DistanceBetweenSelfAndObject"), Distance);
	//UE_LOG(LogTemp, Warning, TEXT("Distance = %f  ！！！！"),Distance);
	//UKismetSystemLibrary::DrawDebugLine(this,OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), ObjectLocation,FColor::Red,20.0f);
	return EBTNodeResult::Succeeded;
}
