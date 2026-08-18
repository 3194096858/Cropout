

#include "AI/TaskNode/RemoveWeapon.h"



#include "NPC/NPC.h"
#include "AIController.h"



EBTNodeResult::Type URemoveWeapon::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ANPC* NPC = Cast<ANPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (NPC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UAddWeapon::ExecuteTask(): NPC == nullptr"));
		return EBTNodeResult::Failed;
	}
	NPC->RemoveWeapon();
	
	return EBTNodeResult::Succeeded;
}