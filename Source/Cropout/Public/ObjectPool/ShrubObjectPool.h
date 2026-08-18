// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool/CropoutObjectPool.h"
#include "ShrubObjectPool.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API AShrubObjectPool : public ACropoutObjectPool
{
	GENERATED_BODY()

public:
	AShrubObjectPool();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	//*************************变量
public:

};
