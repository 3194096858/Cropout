// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TaskNode/GetTownHallLocation.h"

#include "Kismet/KismetSystemLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"


EBTNodeResult::Type UGetTownHallLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
    ACropoutGameMode* GameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if(GameMode == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("UGetTownHallLocation::ExecuteTask(): GameMode == nullptr"));
        return EBTNodeResult::Failed;
    }
	UNavigationSystemV1* NavigationSystemV1 = nullptr;
	FVector TownHallLocation = GameMode->GetTownHallLocation();
	FNavLocation OffsetLocation;
	float OffsetValue = 800.0f;
    NavigationSystemV1 = UNavigationSystemV1::GetCurrent(GetWorld());
	if(NavigationSystemV1 == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGetTownHallLocation::ExecuteTask(): NavigationSystemV1 is nullptr"));
        return EBTNodeResult::Failed;
	}
	NavigationSystemV1->GetRandomReachablePointInRadius(TownHallLocation, OffsetValue,OffsetLocation);
	//OffsetLocation = TownHallLocation + FVector(FMath::RandPointInCircle(OffsetValue), 0.0f);
	//UKismetSystemLibrary::DrawDebugSphere(GetWorld(), TownHallLocation, 500.0f, 12, FLinearColor::Red, 20.0f);
	//UKismetSystemLibrary::DrawDebugSphere(GetWorld(), OffsetLocation.Location, 100.0f, 12, FLinearColor::Red, 20.0f);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("TownHallLocation"), OffsetLocation.Location);
	return EBTNodeResult::Succeeded;
}
