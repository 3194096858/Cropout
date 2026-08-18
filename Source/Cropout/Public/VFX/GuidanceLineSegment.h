// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VFX/VFX.h"
#include "GuidanceLineSegment.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API AGuidanceLineSegment : public AVFX
{
	GENERATED_BODY()
public:
	AGuidanceLineSegment();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;



};
