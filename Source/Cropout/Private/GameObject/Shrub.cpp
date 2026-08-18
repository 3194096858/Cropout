

#include "GameObject/Shrub.h"

#include "Component/CollisionDetectionComponent.h"

#include "Component/HealthComponent.h"

#include "Enum/ObjectPoolType.h"

#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"

#include "Components/CapsuleComponent.h"


AShrub::AShrub()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetGameObjectType(EGameObjectType::Shrub);
	GetHealthComponent()->SetCurrentHealth(100.0f);
	this->CapsuleComponent->SetCapsuleSize(120.0f, 130.0f);
	this->CapsuleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	SetRelatedObjectPoolType(EObjectPoolType::Shrub);


}

void AShrub::BeginPlay()
{
	Super::BeginPlay();



}

void AShrub::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}




void AShrub::OnObjectBeginPlay(AActor* Object)
{
	Super::OnObjectBeginPlay(Object);

	if (Object != this)
	{
		return;
	}
	/*if (MeshArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AShrub::OnObjectBeginPlay(): MeshArray.Num() == 0"));
        return;
	}
	UStaticMesh* Mesh = MeshArray[FMath::RandRange(0, MeshArray.Num() - 1)];
	this->MeshComponent->SetStaticMesh(Mesh);
	this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));*/


}


void AShrub::OnObjectEndPlay(AActor* Object)
{
	Super::OnObjectEndPlay(Object);


}

void AShrub::OnReduceHealth(float Damage, AActor* CauserActor)
{
	Super::OnReduceHealth(Damage, CauserActor);
	TMap<EResourceType, int> ResourceMap;
	ResourceMap.Add(EResourceType::Food, 10);
	ResourceMap.Add(EResourceType::Wood, 0);
	ResourceMap.Add(EResourceType::Stone, 0);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerResourceIncrease.Broadcast(CauserActor, ResourceMap);



}


void AShrub::OnDied()
{
	Super::OnDied();

	auto Lambda = [this]()
		{
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::Shrub);
		};
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 1.0f, false);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());



}


void AShrub::OnPlayerReturnStartMenu()
{
	Super::OnPlayerReturnStartMenu();
	
}



