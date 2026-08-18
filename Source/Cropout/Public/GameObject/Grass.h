// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObject/GameObject.h"
#include "Grass.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API AGrass : public AGameObject
{
	GENERATED_BODY()

public:
	AGrass();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	//*********************************变量
public:

private:
	FTimerHandle DeathTimer;

	//********************************函数
protected:
	virtual void OnObjectBeginPlay(AActor* Object) override;
	virtual void OnObjectEndPlay(AActor* Object) override;
};
