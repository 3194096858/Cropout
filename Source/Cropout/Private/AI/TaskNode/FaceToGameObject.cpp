// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/FaceToGameObject.h"


#include "Interface/GameObjectInteractionInterface.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"




EBTNodeResult::Type UFaceToGameObject::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	FVector ObjectLocation;
	FRotator Rotation;
	FRotator CurrentRotation;
	IGameObjectInteractionInterface* InteractionInterface = Cast<IGameObjectInteractionInterface>(OwnerComp.GetAIOwner()->GetPawn());
	if (InteractionInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UFaceToGameObject::ExecuteTask(): InteractionInterface == nullptr"));
		return EBTNodeResult::Failed;
	}
	ObjectLocation = InteractionInterface->GetGameObjectLocation();
    CurrentRotation = OwnerComp.GetAIOwner()->GetPawn()->GetActorRotation();
	Rotation = UKismetMathLibrary::FindLookAtRotation(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(),ObjectLocation);
	OwnerComp.GetAIOwner()->GetPawn()->SetActorRotation(FRotator(CurrentRotation.Pitch, Rotation.Yaw, CurrentRotation.Roll));

	//UE_LOG(LogTemp, Warning, TEXT("NPCRotation.Yaw: %f"), FMath::Abs(Rotation.Yaw));

	return EBTNodeResult::Succeeded;
}
