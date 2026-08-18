

#include "ObjectPool/TownHallObjectPool.h"




ATownHallObjectPool::ATownHallObjectPool()
{
	PrimaryActorTick.bCanEverTick = true;

	SetObjectPoolType(EObjectPoolType::TownHall);
	this->PoolSize = 1;


}

void ATownHallObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void ATownHallObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


FVector ATownHallObjectPool::GetTownHallLocation()
{
	AActor* TownHall = nullptr;
	if(this->GetObjectMap().FindKey(true) == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("TownHallObjectPool::GetTownHallLocation() : TownHallObjectPool::GetObjectMap().FindKey(true) == nullptr"));
		return FVector(0,0,0);
	}
	TownHall = *this->GetObjectMap().FindKey(true);
    return TownHall->GetActorLocation();
	
}