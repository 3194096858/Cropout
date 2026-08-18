// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObject/FieldBase.h"
#include "WheatField.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API AWheatField : public AFieldBase
{
	GENERATED_BODY()

public:
	AWheatField();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

public:

private:
	FTimerHandle DelayTimer;

public:
	
protected:
	virtual void OnObjectBeginPlay(AActor* Object) override;
	virtual void OnObjectEndPlay(AActor* Object) override;
	virtual void OnReduceHealth(float Damage, AActor* CauserActor) override;
	virtual void OnDied() override;
	virtual void OnAddHealth(float Heal, AActor* CauserActor) override;

private:
};
