

#include "ObjectPool/ShrubObjectPool.h"




AShrubObjectPool::AShrubObjectPool()
{
	PrimaryActorTick.bCanEverTick = true;

	SetObjectPoolType(EObjectPoolType::Shrub);
	this->PoolSize = 50;

}

void AShrubObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void AShrubObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}