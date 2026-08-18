

#include "GameObject/VillagerHouse.h"

#include "Component/HealthComponent.h"

#include "Manager/DecalManager.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameObjectGenerator/GameObjectGenerator.h"
#include "Component/CollisionDetectionComponent.h"
#include "Manager/DataManager.h"

#include "Manager/WidgetManager.h"



AVillagerHouse::AVillagerHouse()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetGameObjectType(EGameObjectType::VillagerHouse);
	GetHealthComponent()->SetMaxHealth(100.0f);
	this->CapsuleComponent->SetCapsuleSize(85.0f, 440.0f);
	this->CapsuleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 410.0f));
	SetRelatedObjectPoolType(EObjectPoolType::VillagerHouse);


}

void AVillagerHouse::BeginPlay()
{
	Super::BeginPlay();
	GetHealthComponent()->SetCurrentHealth(0.0f);
	if (this->MeshArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AVillagerHouse::BeginPlay(): MeshArray.Num() == 0"));
		return;
	}
	this->MeshIndex = 0;
	UStaticMesh* Mesh = MeshArray[this->MeshIndex];
	this->MeshComponent->SetStaticMesh(Mesh);
	this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));
	

}

void AVillagerHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AVillagerHouse::LoadDataByManager()
{
	Super::LoadDataByManager();
	
}


void AVillagerHouse::SaveDataToManager()
{
	Super::SaveDataToManager();
	

}



void AVillagerHouse::SpawnVillagerByGenerator()
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

}





void AVillagerHouse::OnObjectBeginPlay(AActor* Object)
{
	//Super::OnObjectBeginPlay(Object);
	if (Object != this)
	{
		return;
	}
	if (MeshArray.IsValidIndex(this->MeshIndex) == true && MeshArray.Num() != 0)
	{
		this->MeshComponent->SetStaticMesh(MeshArray[this->MeshIndex]);
		this->MeshComponent->SetMaterial(0, MeshArray[this->MeshIndex]->GetMaterial(0));
	}
	auto Lambda = [this]()
		{
			this->CollisionDetectionComponent->LineTraceForObject(GetActorLocation(), GetActorLocation() + GetActorUpVector() * -999.0f, this->CollisionDetectionComponent->DefaultObjectTypeQueryArray);
			FHitResult HitResult = this->CollisionDetectionComponent->GetFirstHitResult();
			this->DecalComponent = this->CropoutGameMode->GetGameInstance()->GetDecalManager()->SpawnDecalAtLocation(this, this->Decal, GetActorLocation(), HitResult.Normal.Rotation() + GetActorRotation(), FVector(300.0f));

		};
	GetWorld()->GetTimerManager().ClearTimer(this->DelayTimer);
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 0.3f, false);
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->BindHealthBar(this->CropoutGameMode->GetGameInstance(), this->CropoutGameMode->GetProgressBarWidgetClass(), FName(this->GetName()));
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckGameObjectDataIsExist(FName(GetName())) == false)
	{
		this->CropoutGameMode->GetGameInstance()->GetDataManager()->CreateGameObjectData(FName(this->GetName()));
	}
	float Health = 0.0f;
	Health = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameObjectData(FName(GetName())).Health;
	GetHealthComponent()->SetCurrentHealth(Health);
	if (this->HealthComponent->GetHealthPercent() == 1.0f)
	{
		this->CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}

}


void AVillagerHouse::OnObjectEndPlay(AActor* Object)
{
	//Super::OnObjectBeginPlay(Object);
	if (Object != this)
	{
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDecalManager()->DestroyDecal(this->DecalComponent, 3.0f, 1.0f);
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->UnbindHealthBar(FName(this->GetName()));
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->DeleteGameObjectData(FName(this->GetName()));
}

void AVillagerHouse::OnReduceHealth(float Damage, AActor* CauserActor)
{
	Super::OnReduceHealth(Damage, CauserActor);



}

void AVillagerHouse::OnAddHealth(float Damage, AActor* CauserActor)
{
	Super::OnAddHealth(Damage, CauserActor);
	if(this->MeshArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AVillagerHouse::OnAddHealth(): MeshArray.Num() == 0"));
		return;
	}
	float HealthPercent = 0.0f;
	int32 LastIndex = this->MeshArray.Num() - 1;
	UStaticMesh* Mesh = nullptr;
	HealthPercent = this->HealthComponent->GetHealthPercent();
	switch (int32(HealthPercent * 10))
	{
	case 3:
        Mesh = this->MeshArray[LastIndex - 2];
		break;
	case 6:
		Mesh = this->MeshArray[LastIndex - 1];
		break;
	case 10:
		Mesh = this->MeshArray[LastIndex];
		SpawnVillagerByGenerator();
		this->CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());
		break;

	}
	if (Mesh != nullptr)
	{
		this->MeshComponent->SetStaticMesh(Mesh);
		this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));
	}

}



void AVillagerHouse::OnDied()
{
	//auto Lambda = [this]()
	//	{
	//		//this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::Tree);
	//	};
	//GetWorld()->GetTimerManager().SetTimer(this->DeathTimer, Lambda, 1.0f, false);
	//this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());



}









