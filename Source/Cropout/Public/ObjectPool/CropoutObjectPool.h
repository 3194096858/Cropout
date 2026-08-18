
#pragma once

#include "Enum/ObjectPoolType.h"


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CropoutObjectPool.generated.h"

class USceneComponent;
class UBoxComponent;
class ACropoutGameMode;

UCLASS()
class CROPOUT_API ACropoutObjectPool : public AActor
{
	GENERATED_BODY()
public:	
	ACropoutObjectPool();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditAnywhere, Category = "Component")
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, Category = "Component")
	USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, Category = "Default")
	UClass* ObjectClass;
	UPROPERTY(EditAnywhere, Category = "Default")
	bool IsInitialize = true;
	UPROPERTY(EditAnywhere, Category = "Default")
	int PoolSize = 3;

protected:

	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;

private:
	//TArray<AActor*> ObjectArray;
	TMap<AActor*,bool> ObjectMap;
	EObjectPoolType ObjectPoolType = EObjectPoolType::None;
	FTimerHandle InitializationTimer;

public:
	UFUNCTION()
	bool CheckObjectPoolIsEmpty();
	UFUNCTION()
    bool CheckObjectIsActive(AActor* Object);
	UFUNCTION()
	int GetActiveObjectNumber();
	UFUNCTION()
	TArray<AActor*> GetAllActiveObject();
protected:
	UFUNCTION()
	TMap<AActor*, bool>& GetObjectMap();
	UFUNCTION()
	void SetObjectPoolType(EObjectPoolType NewType);
	virtual void ObjectBeginPlay(AActor* Object, const FTransform& ObjectTransform);
	virtual void ObjectEndPlay(AActor* Object);
	virtual void OnObjectLeavePool(AActor* Object,const FTransform& ObjectTransform, EObjectPoolType TargetObjectPoolType);
	virtual void OnObjectEnterPool(AActor* Object, EObjectPoolType TargetObjectPoolType);
	virtual void OnMouseMove(const FVector& MouseLocation);
	virtual void OnMouseLeftKeyRelease();
	virtual void OnMouseLeftKeyPress(const FVector& MouseLocation);
	UFUNCTION()
	ACropoutGameMode* GetGameMode();
private:
	UFUNCTION()
	void OnGameInitializationComplete();
	UFUNCTION()
	void Initialize();
	UFUNCTION()
	AActor* GetObjectByName(const FName& ObjectName);
	UFUNCTION()
	AActor* GetRandomObjectFromPool();
	UFUNCTION()
	AActor* GetTargetObjectFromPool(AActor* TargetObject);
};
