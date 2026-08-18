
#pragma once

#include "Enum/GameObjectType/GameObjectType.h"

#include "Enum/ObjectPoolType.h"




#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameObjectGenerator.generated.h"




class UCollisionDetectionComponent;
class ACropoutGameMode;
class USceneComponent;
class UBoxComponent;


UCLASS()
class CROPOUT_API AGameObjectGenerator : public AActor
{
	GENERATED_BODY()
public:	
	AGameObjectGenerator();
	virtual ~AGameObjectGenerator() override;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
public:	
	virtual void Tick(float DeltaTime) override;


public:
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, Category = "Component")
	UCollisionDetectionComponent* CollisionDetectionComponent;
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;
	static int32 InstanceCount;
private:
	static bool IsCompleteInitialization;
	EGameObjectType GameObjectType;
	FTimerHandle InitializationTimer;
	FTimerHandle TickTimer;
	float TickTimerInterval = 0.3f;
    int32 GameObjectCount = 0;
public:
	static int32 GetInstanceCount()
	{
		return InstanceCount;
	};
	UFUNCTION()
	FORCEINLINE void SetGameObjectType(EGameObjectType NewType)
	{
		this->GameObjectType = NewType;
	};
	UFUNCTION()
	FORCEINLINE EGameObjectType GetGameObjectType() const
	{
		return this->GameObjectType;
	};
	UFUNCTION()
	void SpawnTree(int32 Number);
    UFUNCTION()
	void SpawnTownHall(int32 Number = 1);
	UFUNCTION()
	void SpawnStone(int32 Number); 
	UFUNCTION()
	void SpawnShrub(int32 Number);
	UFUNCTION()
	void SpawnGrass(int32 Number);
	UFUNCTION()
	void SpawnVillager(int32 Number);
protected:

private:
	UFUNCTION()
	void OnGameOver();
	UFUNCTION()
	void OnGameWin();
	UFUNCTION()
	void OnGameStart();
	UFUNCTION()
	void OnGameStartInitialization();
	UFUNCTION()
	void OnGameRestart();
	UFUNCTION()
	void OnGameResume();
	UFUNCTION()
	void OnGamePause();
	UFUNCTION()
	FTransform GetRandomTransform(const FVector& Range,float MinLocationZ = 0.0f,float MaxLocationZ= 0.0f,float MinRotationYaw = 0.0f,float MaxRotationYaw = 0.0f,int32 MinScale = 1.0f,int32 MaxScale = 1.0f);
	UFUNCTION()
	void TickTimerFunction();
};
