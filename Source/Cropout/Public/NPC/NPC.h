
#pragma once

#include "Enum/GameStatus.h"
#include "Enum/NPCState/NPCState.h"
#include "Enum/ResourceType.h"
#include "Enum/GameObjectType/GameObjectType.h"
#include "Interface/NPCStateInterface/NPCStateInterface.h"
#include "Interface/GameObjectInteractionInterface.h"
#include "Interface/GameObjectTypeInterface.h"
#include "Struct/VillagerJobInformation.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

class UAIPerceptionComponent;
class UCollisionDetectionComponent;
class ACropoutGameMode;
class UHealthComponent;
class UDamageComponent;
class UDataTable;
class UAnimMontage;
class UStaticMeshComponent;
class UHealComponent;




UCLASS()
class CROPOUT_API ANPC : public ACharacter, public INPCStateInterface,public IGameObjectInteractionInterface, public IGameObjectTypeInterface
{
	GENERATED_BODY()
public:
	ANPC();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(EditAnywhere, Category = "DataTable")
	UDataTable* JobInformationTable;
protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* HatMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* WeaponMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* HairMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* CrateMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCollisionDetectionComponent* CollisionDetectionComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UDamageComponent* DamageComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UHealComponent* HealComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UHealthComponent* HealthComponent;
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;

private:
	FVector DamageTextLocation;
	//float MovementSpeed = 500.f;
	float MaxMovementSpeed = 500.f;
	ENPCState NPCState = ENPCState::Patrol;
	ENPCState NPCStateBeforeTransport = ENPCState::None;
	EGameObjectType GameObjectType = EGameObjectType::None;
	TMap<EResourceType, int32> ResourceMap;
	TMap<EResourceType, int32> MaxResourceMap;
	bool IsCompleteJob = true;
	bool IsCropMature = false;
	FVector GameObjectLocation = FVector::ZeroVector;
	FVector TownHallLcation = FVector::ZeroVector;
	FTimerHandle InitializationTimer;
	FTimerHandle TickTimer;
	FTimerHandle DelayTimer;

public:

	UFUNCTION()
	float GetMovementSpeed();
	virtual void Attack();
	virtual void Heal();
	UFUNCTION()
	void AddSelfResource(EGameObjectType ObjectType);
	UFUNCTION()
	void RemoveSelfAllResource();
	UFUNCTION()
	void AddHat();
	UFUNCTION()
	void AddWeapon();
	UFUNCTION()
	void RemoveHat();
	UFUNCTION()
	void RemoveWeapon();
	UFUNCTION()
	void AddCrate();
	UFUNCTION()
	void RemoveCrate();

protected:
	virtual ENPCState GetNPCState() override;
	virtual void UpdateNPCState(ENPCState NewState) override;
	virtual FVector GetGameObjectLocation() override;
	virtual void SetGameObjectLocation(const FVector& ObjectLocation) override;
	virtual void SetGameObjectType(EGameObjectType NewType) override;
	virtual EGameObjectType GetGameObjectType() override;
	virtual void OnObjectBeginPlay(AActor* Object);
	virtual void OnObjectEndPlay(AActor* Object);
	virtual void OnPlayerReturnStartMenu();

private:
	UFUNCTION()
	void TickFunction();
	UFUNCTION()
	void OnVillagerResourceIncrease(AActor* Villager,TMap<EResourceType, int32> OtherResource);
	UFUNCTION()
	FVillagerJobInformation GetJobInformationFromTable(const FName& JobName);
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void OnMontageStarted(UAnimMontage* Montage);
    UFUNCTION()
	void OnVillagerCompleteJob(const FVector& ObjectLocation);
	UFUNCTION()
	void OnCropMature(const FVector& ObjectLocation);
	UFUNCTION()
	void OnGameWin();
	UFUNCTION()
	void OnGameOver();
	UFUNCTION()
	void OnGameSave();
	UFUNCTION()
	void OnGameStart();
	UFUNCTION()
	void OnGameRestart();
	UFUNCTION()
	void OnGamePause();
	UFUNCTION()
	void OnGameResume(EGameStatus CurrentStatus);
	UFUNCTION()
	void LoadDataByManager();
	UFUNCTION()
	void SaveDataToManager();
	UFUNCTION()
	UAnimMontage* GetMontageFromTable(EGameObjectType ObjectType);
};
