
#pragma once

#include "Enum/GameStatus.h"
#include "Enum/ObjectPoolType.h"

#include "Enum/GameObjectType/GameObjectType.h"

#include "Interface/GameObjectTypeInterface.h"

#include "Interface/GameObjectInteractionInterface.h"


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameObject.generated.h"






class UDecalComponent;
class UCollisionDetectionComponent;
class UHealthComponent;
class UDamageComponent;
class ACropoutGameMode;
class UStaticMeshComponent;
class USceneComponent;
class UCapsuleComponent;

UCLASS()
class CROPOUT_API AGameObject : public AActor,public IGameObjectTypeInterface, public IGameObjectInteractionInterface
{
	GENERATED_BODY()
public:
	AGameObject();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	//*********************************变量
public:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	TArray<UStaticMesh*> MeshArray;
protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCollisionDetectionComponent* CollisionDetectionComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UDamageComponent* DamageComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UHealthComponent* HealthComponent;
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UDecalComponent* DecalComponent;
	int32 MeshIndex = -1;

private:
	FTimerHandle DeathTimer;
	FTimerHandle InitializationTimer;
	EGameObjectType GameObjectType = EGameObjectType::None;
	EObjectPoolType ObjectPoolType = EObjectPoolType::None;

//*********************************函数
public:
	UFUNCTION()
	EObjectPoolType GetRelatedObjectPoolType();
	UFUNCTION()
	void SetRelatedObjectPoolType(EObjectPoolType NewType);
	UFUNCTION()
	USceneComponent* GetSceneComponent();
	UFUNCTION()
	UStaticMeshComponent* GetMeshComponent();
	UFUNCTION()
	UCapsuleComponent* GetCapsuleComponent();
	UFUNCTION()
	UHealthComponent* GetHealthComponent();
    UFUNCTION()
	UDamageComponent* GetDamageComponent();
	UFUNCTION()
	ACropoutGameMode* GetGameMode();
protected:
	virtual void OnGameStartInitialization();
	virtual void OnGameCompleteInitialization();
	UFUNCTION()
	UStaticMesh* GetRandomMesh();
	virtual void SaveDataToManager();
	virtual void LoadDataByManager();
	virtual void OnObjectBeginPlay(AActor* Object);
	virtual void OnObjectEndPlay(AActor* Object);
	virtual void OnAddHealth(float Heal, AActor* CauserActor);
	virtual void OnReduceHealth(float Damage,AActor* CauserActor);
	virtual void OnDied();
	virtual void SetGameObjectType(EGameObjectType NewType) override;
	virtual EGameObjectType GetGameObjectType() override;
	virtual FVector GetGameObjectLocation() override;
	virtual void SetGameObjectLocation(const FVector& ObjectLocation) override;
	virtual void OnPlayerReturnStartMenu();
	virtual void OnGameSave();
	virtual void OnGameStart();
private:
	UFUNCTION()
	void OnGameRestart();
	UFUNCTION()
	void OnGamePause();
	UFUNCTION()
	void OnGameResume(EGameStatus CurrentStatus);
	
};
