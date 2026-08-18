
#include "GameObject/FieldBase.h"
#include "Component/HealthComponent.h"
#include "Manager/DecalManager.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Component/CollisionDetectionComponent.h"
#include "Manager/DataManager.h"

#include "Manager/WidgetManager.h"



AFieldBase::AFieldBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetGameObjectType(EGameObjectType::CornField);
	GetHealthComponent()->SetMaxHealth(100.0f);
	this->CapsuleComponent->SetCapsuleSize(250.0f, 250.0f);


}

void AFieldBase::BeginPlay()
{
	Super::BeginPlay();
	if (this->MeshArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AFieldBase::BeginPlay(): MeshArray.Num() == 0"));
		return;
	}
	UStaticMesh* Mesh = MeshArray[0];
	this->MeshComponent->SetStaticMesh(Mesh);
	this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));
	GetHealthComponent()->SetCurrentHealth(0.0f);


}

void AFieldBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AFieldBase::LoadDataByManager()
{
	//Super::LoadDataByManager();
	FName ActorName = FName(GetName());
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckFieldBaseDataIsExist(ActorName) == false)
	{
		return;
	}
	FFieldBaseData TargetData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetFieldBaseData(ActorName);
	this->MeshIndex = TargetData.MeshIndex;
	this->HealthComponent->SetCurrentHealth(TargetData.Health);
	this->HealthComponent->SetMaxHealth(TargetData.MaxHealth);
	this->Maturation = TargetData.Maturation;
	this->MaxMaturation = TargetData.MaxMaturation;
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(this, TargetData.Transform, GetRelatedObjectPoolType());

}


void AFieldBase::SaveDataToManager()
{
	//Super::SaveDataToManager();
	FName ActorName = FName(GetName());
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckFieldBaseDataIsExist(ActorName) == false)
	{
		return;
	}
	FFieldBaseData NewData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetFieldBaseData(ActorName);
	NewData.Transform = GetActorTransform();
	NewData.MaxHealth = this->HealthComponent->GetMaxHealth();
	NewData.Health = this->HealthComponent->GetCurrentHealth();
    NewData.MaxMaturation = this->MaxMaturation;
	NewData.MeshIndex = MeshArray.Find(this->MeshComponent->GetStaticMesh());
    NewData.Maturation = this->Maturation;
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdateFieldBaseData(ActorName,NewData);


}




void AFieldBase::SetMaxMaturation(int32 NewValue)
{
    this->MaxMaturation = FMath::Clamp(NewValue, 0, 100);

}





void AFieldBase::OnObjectBeginPlay(AActor* Object)
{
	///Super::OnObjectBeginPlay(Object);

	if (Object != this)
	{
		return;
	}
	GetHealthComponent()->SetCurrentHealth(this->HealthComponent->GetCurrentHealth());
	auto Lambda = [this]()
		{
			if (this->CollisionDetectionComponent->GetHitResultNumber() != 0)
			{
				FHitResult HitResult = this->CollisionDetectionComponent->GetFirstHitResult();
				this->DecalComponent = this->CropoutGameMode->GetGameInstance()->GetDecalManager()->SpawnDecalAtLocation(this, this->Decal, GetActorLocation(), HitResult.Normal.Rotation() + GetActorRotation(), FVector(300.0f));
			}
		
		};
	GetWorld()->GetTimerManager().ClearTimer(this->DelayTimer);
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 0.3f, false);
	this->CollisionDetectionComponent->LineTraceForObject(GetActorLocation(), GetActorLocation() + GetActorUpVector() * -999.0f, this->CollisionDetectionComponent->DefaultObjectTypeQueryArray);
	
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->BindHealthBar(this->CropoutGameMode->GetGameInstance(), this->CropoutGameMode->GetProgressBarWidgetClass(), FName(this->GetName()));
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckFieldBaseDataIsExist(FName(GetName())) == false)
	{
		this->CropoutGameMode->GetGameInstance()->GetDataManager()->CreateFieldBaseData(FName(this->GetName()));
	}

}


void AFieldBase::OnObjectEndPlay(AActor* Object)
{
	//Super::OnObjectEndPlay(Object);

	if (Object != this)
	{
		return;
	}
	this->Maturation = 0;
	this->CropoutGameMode->GetGameInstance()->GetDecalManager()->DestroyDecal(this->DecalComponent, 3.0f, 1.0f);
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->UnbindHealthBar(FName(this->GetName()));
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->DeleteFieldBaseData(FName(this->GetName()));
	this->MeshIndex = -1;



}

void AFieldBase::OnReduceHealth(float Damage, AActor* CauserActor)
{
	Super::OnReduceHealth(Damage, CauserActor);
	TMap<EResourceType, int> ResourceMap;
	ResourceMap.Add(EResourceType::Food, 40);
	ResourceMap.Add(EResourceType::Wood, 0);
	ResourceMap.Add(EResourceType::Stone, 0);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerResourceIncrease.Broadcast(CauserActor, ResourceMap);

}


void AFieldBase::OnAddHealth(float Heal, AActor* CauserActor)
{
	Super::OnAddHealth(Heal, CauserActor);
	if (this->MeshArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AFieldBase::OnAddHealth(): MeshArray.Num() == 0"));
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
		this->Maturation++;
		this->HealthComponent->SetCurrentHealth(1.0f);
		Mesh = this->MeshArray[LastIndex];
        this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnCropMature.Broadcast(GetActorLocation());
		break;
	}
	if (Mesh != nullptr)
	{
		this->MeshComponent->SetStaticMesh(Mesh);
		this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));
	}


}



void AFieldBase::OnDied()
{
	Super::OnDied();

	//if (this->Maturation < this->MaxMaturation)
	//{
	//	UStaticMesh* Mesh = MeshArray[0];
	//	this->MeshComponent->SetStaticMesh(Mesh);
	//	this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));
	//	this->HealthComponent->SetIsDeath(false);
	//	return;
	//}
	//auto Lambda = [this]()
	//	{
	//		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::CornField);
	//	};
	//GetWorld()->GetTimerManager().SetTimer(this->DeathTimer, Lambda, 1.0f, false);
	//this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());

}





