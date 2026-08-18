// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/GuidanceLineSegmentObjectPool.h"


#include "Kismet/KismetMathLibrary.h"


#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"

AGuidanceLineSegmentObjectPool::AGuidanceLineSegmentObjectPool()
{
	PrimaryActorTick.bCanEverTick = true;

	SetObjectPoolType(EObjectPoolType::GuidanceLineSegment);
	this->PoolSize = 35;

}

void AGuidanceLineSegmentObjectPool::BeginPlay()
{
	Super::BeginPlay();
	
	auto Lambda = [this]()
		{
			GetGameMode()->GetGameInstance()->GetDelegateManager()->OnInitializeGuidanceLine.AddUObject(this, &AGuidanceLineSegmentObjectPool::OnInitializeGuidanceLine);

		};
	GetWorld()->GetTimerManager().SetTimer(this->InitializationTimer, Lambda, 1.0f, false);



}

void AGuidanceLineSegmentObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AGuidanceLineSegmentObjectPool::ObjectBeginPlay(AActor* Object, const FTransform& ObjectTransform)
{
	Super::ObjectBeginPlay(Object, ObjectTransform);
	
}



void AGuidanceLineSegmentObjectPool::ObjectEndPlay(AActor* Object)
{
	Super::ObjectEndPlay(Object);



}

TArray<AActor*> AGuidanceLineSegmentObjectPool::GetGuidanceLineSegmentArray()
{
    return this->GuidanceLineSegmentArray;
}


void AGuidanceLineSegmentObjectPool::OnObjectLeavePool(AActor* Object,const FTransform& ObjectTransform, EObjectPoolType TargetObjectPoolType)
{
	Super::OnObjectLeavePool(Object,ObjectTransform, TargetObjectPoolType);


}



void AGuidanceLineSegmentObjectPool::OnObjectEnterPool(AActor* Object, EObjectPoolType TargetObjectPoolType)
{
	Super::OnObjectEnterPool(Object, TargetObjectPoolType);

}


void AGuidanceLineSegmentObjectPool::OnInitializeGuidanceLine()
{
	for(auto& Element : GetObjectMap())
	{
		if(Element.Value == true)
		{
			GuidanceLineSegmentArray.Add(Element.Key);
		}
	}
	

}

void AGuidanceLineSegmentObjectPool::OnMouseLeftKeyPress(const FVector& MouseLocation)
{
	

}




void AGuidanceLineSegmentObjectPool::OnMouseMove(const FVector& MouseLocation)
{
	
}



void AGuidanceLineSegmentObjectPool::OnMouseLeftKeyRelease()
{
	if (GetObjectMap().FindKey(true) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACircleRingObjectPool::OnMouseLeftKeyRelease(): GetObjectMap().FindKey(true) == nullptr"));
		return;
	}
	

}








