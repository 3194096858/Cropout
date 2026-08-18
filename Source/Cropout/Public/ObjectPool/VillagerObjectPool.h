// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool/CropoutObjectPool.h"
#include "VillagerObjectPool.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API AVillagerObjectPool : public ACropoutObjectPool
{
	GENERATED_BODY()

public:
	AVillagerObjectPool();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
public:
};
