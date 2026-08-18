// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/CircleRingObjectPool.h"

#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"


ACircleRingObjectPool::ACircleRingObjectPool()
{
	PrimaryActorTick.bCanEverTick = true;

	SetObjectPoolType(EObjectPoolType::CircleRing);

}

void ACircleRingObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void ACircleRingObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




void ACircleRingObjectPool::OnMouseLeftKeyPress(const FVector& MouseLocation)
{
	

}




void ACircleRingObjectPool::OnMouseMove(const FVector& MouseLocation)
{
//	if (GetObjectMap().FindKey(true) == nullptr)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("ACircleRingObjectPool::OnMouseMove(): GetObjectMap().FindKey(true) == nullptr"));
//		return;
//	}
//	FVector NewLocation = FVector(MouseLocation.X, MouseLocation.Y, 3.0f);
//	AActor* Object = *GetObjectMap().FindKey(true);
//	//UE_LOG(LogTemp, Warning, TEXT(" Object = %s"), *Object->GetName());
//
//	Object->SetActorLocation(NewLocation);
////	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,FString::Printf(TEXT("Object Location : %s"),*Object->GetActorLocation().ToString()));


}



void ACircleRingObjectPool::OnMouseLeftKeyRelease()
{
	/*if (GetObjectMap().FindKey(true) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACircleRingObjectPool::OnMouseLeftKeyRelease(): GetObjectMap().FindKey(true) == nullptr"));
		return;
	}
	AActor* Object = *GetObjectMap().FindKey(true);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(Object,EObjectPoolType::CircleRing);
	*/
}












