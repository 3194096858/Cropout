
#pragma once

#include "CoreMinimal.h"
#include "GameObject/GameObject.h"
#include "FieldBase.generated.h"



UCLASS()
class CROPOUT_API AFieldBase : public AGameObject
{
	GENERATED_BODY()

public:
	AFieldBase();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Decal")
	UMaterialInterface* Decal;
protected:
	int32 Maturation = 0;
	int32 MaxMaturation = 3;

private:

	FTimerHandle DelayTimer;

public:
	UFUNCTION()
	void SetMaxMaturation(int32 NewValue);
protected:
	virtual void OnObjectBeginPlay(AActor* Object) override;
	virtual void OnObjectEndPlay(AActor* Object) override;
	virtual void OnReduceHealth(float Damage, AActor* CauserActor) override;
	virtual void OnDied() override;
	virtual void OnAddHealth(float Heal, AActor* CauserActor) override;
	virtual void LoadDataByManager() override;
	virtual void SaveDataToManager() override;

private:
};
