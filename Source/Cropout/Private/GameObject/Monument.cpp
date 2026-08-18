

#include "GameObject/Monument.h"



#include "Component/HealthComponent.h"

#include "Manager/DecalManager.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

#include "Component/CollisionDetectionComponent.h"
#include "Manager/WidgetManager.h"
#include "Manager/DataManager.h"


AMonument::AMonument()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetGameObjectType(EGameObjectType::Monument);
	GetHealthComponent()->SetMaxHealth(100.0f);
	this->CapsuleComponent->SetCapsuleSize(600.0f, 600.0f);
	SetRelatedObjectPoolType(EObjectPoolType::Monument);


}

void AMonument::BeginPlay()
{
	Super::BeginPlay();

	if (this->MeshArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMonument::BeginPlay(): MeshArray.Num() == 0"));
		return;
	}
	this->MeshIndex = 0;
	UStaticMesh* Mesh = MeshArray[this->MeshIndex];
	this->MeshComponent->SetStaticMesh(Mesh);
	this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));


}

void AMonument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}



void AMonument::OnObjectBeginPlay(AActor* Object)
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
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->BindHealthBar(this->CropoutGameMode->GetGameInstance(), this->CropoutGameMode->GetProgressBarWidgetClass(), FName(this->GetName()));
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckGameObjectDataIsExist(FName(GetName())) == false)
	{
		this->CropoutGameMode->GetGameInstance()->GetDataManager()->CreateGameObjectData(FName(this->GetName()));
	}
	auto Lambda = [this]()
		{
			this->CollisionDetectionComponent->LineTraceForObject(GetActorLocation(), GetActorLocation() + GetActorUpVector() * -999.0f, this->CollisionDetectionComponent->DefaultObjectTypeQueryArray);
			FHitResult HitResult = this->CollisionDetectionComponent->GetFirstHitResult();
			this->DecalComponent = this->CropoutGameMode->GetGameInstance()->GetDecalManager()->SpawnDecalAtLocation(this, this->Decal, GetActorLocation(), HitResult.Normal.Rotation() + GetActorRotation(), FVector(600.0f));
		};
	GetWorld()->GetTimerManager().ClearTimer(this->DelayTimer);
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 0.3f, false);
	this->CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	float Health = 0.0f;
	Health = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameObjectData(FName(GetName())).Health;
	GetHealthComponent()->SetCurrentHealth(Health);
	if (this->HealthComponent->GetHealthPercent() == 1.0f)
	{
		this->CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	}

}


void AMonument::OnObjectEndPlay(AActor* Object)
{
	//Super::OnObjectEndPlay(Object);
	if (Object != this)
	{
		return;
	}

	this->CropoutGameMode->GetGameInstance()->GetDecalManager()->DestroyDecal(this->DecalComponent, 3.0f, 1.0f);
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->UnbindHealthBar(FName(this->GetName()));
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->DeleteGameObjectData(FName(this->GetName()));



}

void AMonument::OnReduceHealth(float Damage, AActor* CauserActor)
{
	Super::OnReduceHealth(Damage, CauserActor);


}

void AMonument::OnAddHealth(float Damage, AActor* CauserActor)
{
	Super::OnAddHealth(Damage, CauserActor);
	if (this->MeshArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMonument::OnAddHealth(): MeshArray.Num() == 0"));
		return;
	}
	float HealthPercent = 0.0f;
	int32 LastIndex = this->MeshArray.Num() - 1;
	UStaticMesh* Mesh = nullptr;
	HealthPercent = this->HealthComponent->GetHealthPercent();
	switch (int32(HealthPercent * 10))
	{
	case 2:
		Mesh = this->MeshArray[LastIndex - 4];
		break;
	case 4:
		Mesh = this->MeshArray[LastIndex - 3];
		break;
	case 6:
		Mesh = this->MeshArray[LastIndex - 2];
		break;
	case 8:
		Mesh = this->MeshArray[LastIndex - 1];
		break;
	case 10:
		Mesh = this->MeshArray[LastIndex];
		auto Lambda = [this]()
		{
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameWin.Broadcast();
			this->CropoutGameMode->GetGameInstance()->GetDataManager()->SetGameStatus(EGameStatus::None);
		};
		this->CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		GetWorld()->GetTimerManager().ClearTimer(this->DelayTimer);
		GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 1.0f, false);
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());
		break;
	}
	if(Mesh != nullptr)
	{
		this->MeshComponent->SetStaticMesh(Mesh);
		this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));
	}
	

}



void AMonument::OnDied()
{


}



