
#pragma once

#include "CoreMinimal.h"
#include "GameObject/GameObject.h"
#include "TownHall.generated.h"

class UMaterialInterface;



UCLASS()
class CROPOUT_API ATownHall : public AGameObject
{
	GENERATED_BODY()

public:
	ATownHall();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Material")
    UMaterialInterface* Decal;


private:
	FTimerHandle InitializationTimer;
	TArray<FName> VillagerNameArray;
	FTimerHandle DelayTimer;

public:

protected:
	virtual void OnObjectBeginPlay(AActor* Object) override;
	virtual void OnObjectEndPlay(AActor* Object) override;
	virtual void OnPlayerReturnStartMenu() override;
	virtual void OnGameSave() override;
	virtual void LoadDataByManager() override;
	virtual void SaveDataToManager() override;
	virtual void OnGameCompleteInitialization() override;
	virtual void OnGameStart() override;

private:
	UFUNCTION()
	void SpawnVillagerByGenerator();

};
