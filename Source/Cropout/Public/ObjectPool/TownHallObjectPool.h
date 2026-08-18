// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool/CropoutObjectPool.h"
#include "TownHallObjectPool.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API ATownHallObjectPool : public ACropoutObjectPool
{
	GENERATED_BODY()

public:
	ATownHallObjectPool();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	//*************************变量
public:



    //*************************函数
public:
	FVector GetTownHallLocation();
};
