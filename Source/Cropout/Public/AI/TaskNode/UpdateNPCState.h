// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Enum/NPCState/NPCState.h"


#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UpdateNPCState.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API UUpdateNPCState : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ENPCState NPCState;

private:



};
