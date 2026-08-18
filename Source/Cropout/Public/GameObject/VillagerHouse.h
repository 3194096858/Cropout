
#pragma once

#include "CoreMinimal.h"
#include "GameObject/GameObject.h"
#include "VillagerHouse.generated.h"

class UMaterialInterface;


UCLASS()
class CROPOUT_API AVillagerHouse : public AGameObject
{
	GENERATED_BODY()
public:
	AVillagerHouse();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterialInterface* Decal;
private:
	FTimerHandle DelayTimer;

public:

protected:
	virtual void OnObjectBeginPlay(AActor* Object) override;
	virtual void OnObjectEndPlay(AActor* Object) override;
	virtual void OnReduceHealth(float Damage, AActor* CauserActor) override;
	virtual void OnDied() override;
	virtual void OnAddHealth(float Damage, AActor* CauserActor) override;
	virtual void LoadDataByManager() override;
	virtual void SaveDataToManager() override;

private:
	UFUNCTION()
	void SpawnVillagerByGenerator();






};
