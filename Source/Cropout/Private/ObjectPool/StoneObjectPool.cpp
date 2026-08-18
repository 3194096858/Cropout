

#include "ObjectPool/StoneObjectPool.h"




AStoneObjectPool::AStoneObjectPool()
{
	PrimaryActorTick.bCanEverTick = true;

	SetObjectPoolType(EObjectPoolType::Stone);
	this->PoolSize = 50;

}

void AStoneObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void AStoneObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}