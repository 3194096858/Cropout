// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/LettuceFieldObjectPool.h"




ALettuceFieldObjectPool::ALettuceFieldObjectPool()
{
	PrimaryActorTick.bCanEverTick = false;
	SetObjectPoolType(EObjectPoolType::LettuceField);
	this->PoolSize = 50;

}

void ALettuceFieldObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void ALettuceFieldObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}