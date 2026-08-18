// Fill out your copyright notice in the Description page of Project Settings.


#include "VFX/GuidanceLineSegment.h"


AGuidanceLineSegment::AGuidanceLineSegment()
{
	GetMeshComponent()->SetRelativeScale3D(FVector(1.5f,0.5f,1.0f));


}



void AGuidanceLineSegment::BeginPlay()
{
	Super::BeginPlay();

}



void AGuidanceLineSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//this->TimelineComponent->ReceiveTick(DeltaTime);




}
