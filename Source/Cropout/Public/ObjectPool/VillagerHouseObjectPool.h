// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool/CropoutObjectPool.h"
#include "VillagerHouseObjectPool.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API AVillagerHouseObjectPool : public ACropoutObjectPool
{
	GENERATED_BODY()

public:
	AVillagerHouseObjectPool();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
public:


};
