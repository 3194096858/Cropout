
#pragma once

#include "Enum/NPCState/NPCState.h"



#include "CoreMinimal.h"
#include "AIController.h"
#include "NPCAIController.generated.h"

class UBehaviorTree;
class UBlackboardData;
class UAIPerceptionComponent;
class ACropoutGameMode;
class UBehaviorTreeComponent;
//namespace EPathFollowingStatus { enum Type : int; };


UCLASS()
class CROPOUT_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	ANPCAIController();
public:
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, Category = "AI")
	UBlackboardData* BlackboardData;
	UPROPERTY(EditAnywhere, Category = "Component")
	UBehaviorTreeComponent* BehaviorTreeComponent;

private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;
	/*EPathFollowingStatus::Type PathFollowingStatus;*/
	ENPCState NPCState = ENPCState::Patrol;
	ENPCState NPCStateBeforeTransport = ENPCState::None;
	bool IsCompleteJob = true;
public:
	UFUNCTION()
	void SetNPCStateBeforeTransport(ENPCState NewState);
	UFUNCTION()
	void SetNPCState(ENPCState NewState);
	UFUNCTION()
	void SaveDataToManager();
	UFUNCTION()
	void LoadDataByManager();
	/*UFUNCTION()
	void SetPathFollowingStatus(EPathFollowingStatus::Type PathFollowingStatus);*/
	UFUNCTION()
	void SetIsCropMature(bool NewBool);
	UFUNCTION()
	void SetIsCompleteJob(bool NewBool);
private:
	UFUNCTION()
	void OnNPCStateChange(AActor* AIControllerOwner, ENPCState NewState);
	UFUNCTION()
	void OnVillagerCompleteJob(const FVector& ObjectLocation);
	UFUNCTION()
	void OnGameSave();
	UFUNCTION()
	void OnGameOver();
	UFUNCTION()
	void OnGameStart();
	UFUNCTION()
	void OnGameRestart();
	UFUNCTION()
	void OnGamePause();
	UFUNCTION()
	void OnGameResume(EGameStatus CurrentStatus);
	UFUNCTION()
	void OnObjectBeginPlay(AActor* Object);
	UFUNCTION()
    void OnObjectEndPlay(AActor* Object);
	UFUNCTION()
	void PauseMovement();
	UFUNCTION()
	void ResumeMovement();



};
