
#pragma once

#include "CoreMinimal.h"
#include "GameObject/GameObject.h"
#include "Shrub.generated.h"



UCLASS()
class CROPOUT_API AShrub : public AGameObject
{
	GENERATED_BODY()

public:
	AShrub();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
public:


private:
	FTimerHandle DelayTimer;




protected:
	virtual void OnObjectBeginPlay(AActor* Object) override;
	virtual void OnObjectEndPlay(AActor* Object) override;
	virtual void OnReduceHealth(float Damage, AActor* CauserActor) override;
	virtual void OnDied() override;
	virtual void OnPlayerReturnStartMenu() override;

};
