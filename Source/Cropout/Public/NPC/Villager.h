// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC/NPC.h"
#include "Villager.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API AVillager : public ANPC
{
	GENERATED_BODY()
public:
	AVillager();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
public:

private:
	FTimerHandle DelayTimer;

public:

protected:
	virtual void Attack() override;
	virtual void OnObjectBeginPlay(AActor* Object) override;
	virtual void OnObjectEndPlay(AActor* Object) override;
	virtual void OnPlayerReturnStartMenu() override;

	/*virtual void OnReduceHealth(float Damage, AActor* CauserActor) override;
	virtual void OnDied() override;
	virtual void OnAddHealth(float Damage, AActor* CauserActor) override;*/

};
