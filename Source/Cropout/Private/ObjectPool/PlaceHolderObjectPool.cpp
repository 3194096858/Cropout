

#include "ObjectPool/PlaceHolderObjectPool.h"



APlaceHolderObjectPool::APlaceHolderObjectPool()
{
	PrimaryActorTick.bCanEverTick = true;

	SetObjectPoolType(EObjectPoolType::PlaceHolder);

}

void APlaceHolderObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void APlaceHolderObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}