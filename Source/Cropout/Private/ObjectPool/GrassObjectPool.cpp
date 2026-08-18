// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/GrassObjectPool.h"


AGrassObjectPool::AGrassObjectPool()
{
	PrimaryActorTick.bCanEverTick = true;

	SetObjectPoolType(EObjectPoolType::Grass);
	this->PoolSize = 300;

}

void AGrassObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void AGrassObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}