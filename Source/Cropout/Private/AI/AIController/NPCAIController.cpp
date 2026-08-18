
#include "AI/AIController/NPCAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/GameObjectInteractionInterface.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Navigation/PathFollowingComponent.h"

#include "Manager/DataManager.h"




ANPCAIController::ANPCAIController()
{
	this->AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	this->BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

}


void ANPCAIController::BeginPlay()
{
    Super::BeginPlay();
	CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	
	if (CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ANPCAIController::BeginPlay(): CropoutGameMode == nullptr"));
		return;
	}
	if (CropoutGameMode->GetGameInstance() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ANPCAIController::BeginPlay(): CropoutGameMode->GetGameInstance() == nullptr"));
		return;
	}
	if (CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ANPCAIController::BeginPlay(): CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr"));
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectBeginPlay.AddUObject(this, &ANPCAIController::OnObjectBeginPlay);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEndPlay.AddUObject(this, &ANPCAIController::OnObjectEndPlay);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnNPCStateChange.AddUObject(this, &ANPCAIController::OnNPCStateChange);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.AddUObject(this, &ANPCAIController::OnVillagerCompleteJob);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGamePause.AddUObject(this, &ANPCAIController::OnGamePause);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameResume.AddUObject(this, &ANPCAIController::OnGameResume);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameSave.AddUObject(this, &ANPCAIController::OnGameSave);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStart.AddUObject(this, &ANPCAIController::OnGameStart);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameOver.AddUObject(this, &ANPCAIController::OnGameOver);




}



void ANPCAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//this->GetBehaviorTreeComponent();

}


void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (this->BlackboardData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANPCAIController::BeginPlay(): BlackboardData == nullptr"));
		return;
	}
	UseBlackboard(this->BlackboardData, BlackboardComponent);


}

void ANPCAIController::SetNPCState(ENPCState NewState)
{
	this->NPCState = NewState;
	GetBlackboardComponent()->SetValueAsName(FName("NPCState"), UEnum::GetValueAsName(this->NPCState));

}

void ANPCAIController::SetNPCStateBeforeTransport(ENPCState NewState)
{
	this->NPCStateBeforeTransport = NewState;
	GetBlackboardComponent()->SetValueAsName(FName("NPCStateBeforeTransport"), UEnum::GetValueAsName(this->NPCStateBeforeTransport));

}

void ANPCAIController::SetIsCompleteJob(bool NewBool)
{
	this->IsCompleteJob = NewBool;
	GetBlackboardComponent()->SetValueAsBool(FName("IsCompleteJob2"), this->IsCompleteJob);
	

}



void ANPCAIController::SetIsCropMature(bool NewBool)
{
	//this->IsCompleteJob = NewBool;
	GetBlackboardComponent()->SetValueAsBool(FName("IsCropMature"), NewBool);


}


void ANPCAIController::PauseMovement()
{
	if (GetPathFollowingComponent()->GetStatus() == EPathFollowingStatus::Moving)
	{
		PauseMove(FAIRequestID::AnyRequest);
	}

}

void ANPCAIController::ResumeMovement()
{
	if (GetPathFollowingComponent()->GetStatus() == EPathFollowingStatus::Paused)
	{
		ResumeMove(FAIRequestID::AnyRequest);

	}


}



void ANPCAIController::LoadDataByManager()
{
	/*FName ActorName = FName(GetPawn()->GetName());
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckVillagerDataIsExist(ActorName) == false)
	{
		return;
	}
	FVillagerData TargetData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerData(ActorName);
	GetBlackboardComponent()->SetValueAsFloat(FName("DistanceBetweetSelfAndObject"), TargetData.BehaviorTreeData.DistanceBetweenSelfAndObject);
	GetBlackboardComponent()->SetValueAsVector(FName("RandomLocation"), TargetData.BehaviorTreeData.RandomLocation);
	GetBlackboardComponent()->SetValueAsVector(FName("GameObjectLocation"), TargetData.BehaviorTreeData.GameObjectLocation);
	GetBlackboardComponent()->SetValueAsVector(FName("TownHallLocation"), TargetData.BehaviorTreeData.TownHallLocation);
	GetBlackboardComponent()->SetValueAsBool(FName("IsCompleteJob2"), TargetData.BehaviorTreeData.IsCompleteJob);
	GetBlackboardComponent()->SetValueAsBool(FName("IsCropoutMature"), TargetData.BehaviorTreeData.IsCropMature);
	GetBlackboardComponent()->SetValueAsName(FName("NPCState"), UEnum::GetValueAsName((TargetData.BehaviorTreeData.NPCState)));
	GetBlackboardComponent()->SetValueAsName(FName("NPCStateBeforeTransport"), UEnum::GetValueAsName((TargetData.BehaviorTreeData.NPCStateBeforeTransport)));
	this->PathFollowingStatus = TargetData.BehaviorTreeData.PathFollowingStatus;
	*/

}


void ANPCAIController::SaveDataToManager()
{
	/*FName ActorName = FName(GetPawn()->GetName());
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckVillagerDataIsExist(ActorName) == false)
	{
		return;
	}
	UEnum* Enum = StaticEnum<ENPCState>();
	int32 EnumIndex;
	FVillagerData NewData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerData(ActorName);
	NewData.BehaviorTreeData.PathFollowingStatus = GetPathFollowingComponent()->GetStatus();
	NewData.BehaviorTreeData.DistanceBetweenSelfAndObject = GetBlackboardComponent()->GetValueAsFloat(FName("DistanceBetweenSelfAndObject"));
	NewData.BehaviorTreeData.IsCropMature = GetBlackboardComponent()->GetValueAsBool(FName("IsCropMature"));
	NewData.BehaviorTreeData.IsCompleteJob = GetBlackboardComponent()->GetValueAsBool(FName("IsCompleteJob2"));
	NewData.BehaviorTreeData.RandomLocation = GetBlackboardComponent()->GetValueAsVector(FName("RandomLocation"));
	NewData.BehaviorTreeData.GameObjectLocation = GetBlackboardComponent()->GetValueAsVector(FName("GameobjectLocation"));
	NewData.BehaviorTreeData.TownHallLocation = GetBlackboardComponent()->GetValueAsVector(FName("TownHallLocation"));
	EnumIndex = Enum->GetIndexByName(GetBlackboardComponent()->GetValueAsName(FName("NPCState")));
	NewData.BehaviorTreeData.NPCStateBeforeTransport = static_cast<ENPCState>(Enum->GetValueByIndex(EnumIndex));
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdateVillagerData(ActorName, NewData);*/

}


void ANPCAIController::OnObjectBeginPlay(AActor* Object)
{	
	if (Object != GetPawn())
	{ 
		return;
	}
	if (this->BehaviorTreeComponent->IsPaused() == false)
	{
		RunBehaviorTree(this->BehaviorTree);
	}
	else
	{
		this->BehaviorTreeComponent->ResumeLogic(TEXT("ResumeLogic"));
		ResumeMovement();
	}
	if (GetBlackboardComponent() != nullptr)
	{
		GetBlackboardComponent()->SetValueAsBool(FName("IsCompleteJob2"), this->IsCompleteJob);
		GetBlackboardComponent()->SetValueAsName(FName("NPCState"), UEnum::GetValueAsName(NPCState));
	}
	
}


void ANPCAIController::OnObjectEndPlay(AActor* Object)
{
	if (Object != GetPawn())
	{
		return;
	}
    this->BehaviorTreeComponent->PauseLogic(TEXT("PauseLogic"));

}



void ANPCAIController::OnNPCStateChange(AActor* AIControllerOwner, ENPCState NewState)
{
	if (AIControllerOwner != GetPawn())
	{
		return;
	};
	if (NewState == ENPCState::Transport && this->NPCState != ENPCState::Transport)
	{
		this->NPCStateBeforeTransport = this->NPCState;
	}
	if (NewState != ENPCState::Patrol && NewState != ENPCState::Transport)
	{
		this->IsCompleteJob = false;
	}

	this->NPCState = NewState;
	GetBlackboardComponent()->SetValueAsName(FName("NPCState"), UEnum::GetValueAsName(this->NPCState));
	GetBlackboardComponent()->SetValueAsName(FName("NPCStateBeforeTransport"), UEnum::GetValueAsName(this->NPCStateBeforeTransport));
	GetBlackboardComponent()->SetValueAsBool(FName("IsCompleteJob2"), this->IsCompleteJob);
	
}


void ANPCAIController::OnVillagerCompleteJob(const FVector& ObjectLocation)
{
	



}





void ANPCAIController::OnGameSave()
{
	/*if (this->CropoutGameMode->CheckActorIsActive(GetPawn(), EObjectPoolType::Villager) == false)
	{
		return;
	}
	SaveDataToManager();*/



}


void ANPCAIController::OnGameRestart()
{



}


void ANPCAIController::OnGameOver()
{
	this->BehaviorTreeComponent->PauseLogic(TEXT("PauseLogic"));
	PauseMovement();



}

void ANPCAIController::OnGameStart()
{
	if (this->CropoutGameMode->CheckActorIsActive(GetPawn(), EObjectPoolType::Villager) == false)
	{
		return;
	}



}

void ANPCAIController::OnGamePause()
{
	if (this->CropoutGameMode->CheckActorIsActive(GetPawn(), EObjectPoolType::Villager) == false)
	{
		return;
	}
	this->BehaviorTreeComponent->PauseLogic(TEXT("PauseLogic"));
	PauseMovement();


}


void ANPCAIController::OnGameResume(EGameStatus CurrentStatus)
{
	if (this->CropoutGameMode->CheckActorIsActive(GetPawn(), EObjectPoolType::Villager) == false)
	{
		return;
	}
	this->BehaviorTreeComponent->ResumeLogic(TEXT("ResumeLogic"));
	ResumeMovement();
	/*if (CurrentStatus == EGameStatus::GameOver)
	{
		LoadDataByManager();

	}*/
	


}


