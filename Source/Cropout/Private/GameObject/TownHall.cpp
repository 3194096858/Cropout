

#include "GameObject/TownHall.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/DecalManager.h"
#include "Component/CollisionDetectionComponent.h"
#include "GameObjectGenerator/GameObjectGenerator.h"
#include "Manager/DataManager.h"






ATownHall::ATownHall()
{

	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCapsuleHalfHeight(600.0f);
    GetCapsuleComponent()->SetCapsuleRadius(500.0f);
	GetCapsuleComponent()->SetRelativeLocation(FVector(50.0f, 0.0f, 230.0f));
	SetGameObjectType(EGameObjectType::TownHall);
	SetRelatedObjectPoolType(EObjectPoolType::TownHall);
	this->MeshComponent->SetRelativeRotation(FRotator(0.0f, 45.0f, 0.0f));


}



void ATownHall::BeginPlay()
{
	Super::BeginPlay();
	//AActor::Be
	/*auto Lambda = [this]()
	{
			
	};
	GetWorld()->GetTimerManager().SetTimer(this->InitializationTimer, Lambda, 1.2f, false);*/


}

void ATownHall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void ATownHall::LoadDataByManager()
{
	//Super::LoadDataByManager();
	FTownHallData TargetData;
	TargetData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetTownHallData();
	this->VillagerNameArray = TargetData.VillagerNameArray;
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(nullptr, TargetData.Transform, GetRelatedObjectPoolType());

}


void ATownHall::SaveDataToManager()
{
	//Super::SaveDataToManager();
	FTownHallData NewData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetTownHallData();
	NewData.Transform = GetActorTransform();
	NewData.VillagerNameArray = this->VillagerNameArray;
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdateTownHallData(NewData);


}




void ATownHall::SpawnVillagerByGenerator()
{
	AGameObjectGenerator* Generator = nullptr;
	FVector Location = GetActorLocation();
	const int32 VillagerCount = 2;
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->CropoutGameMode->GetGameObjectGeneratorClass(), Location, FRotator::ZeroRotator);
	if (Generator == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATownHall::SpawnVillagerByGenerator(): GameObjectGenerator == nullptr"));
		return;
	}
	Generator->SpawnVillager(VillagerCount);
	auto Lambada = [this]()
		{
			VillagerNameArray = this->CropoutGameMode->GetAllActiveObjectName(EObjectPoolType::Villager);
		};
	GetWorld()->GetTimerManager().ClearTimer(this->DelayTimer);
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambada, 1.0f, false);


}





void ATownHall::OnObjectBeginPlay(AActor* Object)
{
	//Super::OnObjectBeginPlay(Object);
	if (Object != this)
	{
		return;
	}
	auto Lambda = [this]()
	{ 
			this->CollisionDetectionComponent->LineTraceForObject(GetActorLocation(), GetActorLocation() + GetActorUpVector() * -999.0f, this->CollisionDetectionComponent->DefaultObjectTypeQueryArray);
			if (this->CollisionDetectionComponent->GetHitResultArray().Num() == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("ATownHall::OnObjectBeginPlay(): GetHitResultArray().Num() == 0"));
				return;
			}
			FHitResult HitResult = this->CollisionDetectionComponent->GetHitResultArray()[0];
			this->DecalComponent = this->CropoutGameMode->GetGameInstance()->GetDecalManager()->SpawnDecalAtLocation(this, Decal, GetActorLocation(), HitResult.Normal.Rotation() + FRotator(0.0f, 45.0f, 0.0f), FVector(600.0f));
	};
	GetWorld()->GetTimerManager().ClearTimer(this->DelayTimer);
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 0.3f, false);


}


void ATownHall::OnObjectEndPlay(AActor* Object)
{
	//Super::OnObjectEndPlay(Object);

	if (Object != this)
	{
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDecalManager()->DestroyDecal(this->DecalComponent, 3.0f, 1.0f);

}



void ATownHall::OnGameSave()
{
	Super::OnGameSave();
	


}


void ATownHall::OnGameStart()
{
	Super::OnGameStart();
	if (this->CropoutGameMode->CheckActorIsActive(this, GetRelatedObjectPoolType()) == false)
	{
		return;
	}

	SpawnVillagerByGenerator();
	

}


void ATownHall::OnPlayerReturnStartMenu()
{
	Super::OnPlayerReturnStartMenu();
	
}



void ATownHall::OnGameCompleteInitialization()
{
	Super::OnGameCompleteInitialization();
	/*if (VillagerNameArray.Num() == 0)
	{
		SpawnVillagerByGenerator();
	}*/

}