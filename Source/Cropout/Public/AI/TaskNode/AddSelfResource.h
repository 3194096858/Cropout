// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Enum/GameObjectType/GameObjectType.h"
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AddSelfResource.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API UAddSelfResource : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere)
	EGameObjectType GameObjectType =EGameObjectType::None;
};
