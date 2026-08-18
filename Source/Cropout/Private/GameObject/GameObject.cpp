
#include "GameObject/GameObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Component/CollisionDetectionComponent.h"
#include "Component/DamageComponent.h"
#include "Component/HealthComponent.h"
#include "Interface/NPCStateInterface/NPCStateInterface.h"
#include "Manager/WidgetManager.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Manager/DataManager.h"



AGameObject::AGameObject()
{

	PrimaryActorTick.bCanEverTick = false;
	this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	this->SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	this->CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	this->DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComponent"));
	this->HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	this->CollisionDetectionComponent = CreateDefaultSubobject<UCollisionDetectionComponent>(TEXT("CollisionDetectionComponent"));

	SetRootComponent(this->SceneComponent);

	this->MeshComponent->SetupAttachment(this->SceneComponent);
	this->CapsuleComponent->SetupAttachment(this->SceneComponent);

	this->MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->MeshComponent->bReceivesDecals = false;
	//EGameState::
}

void AGameObject::BeginPlay()
{
	Super::BeginPlay();
	CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameObject::BeginPlay(): CropoutGameMode == nullptr"));
		return;
	}
	this->HealthComponent->OnAddHealth.BindUObject(this, &AGameObject::OnAddHealth);
	this->HealthComponent->OnReduceHealth.BindUObject(this, &AGameObject::OnReduceHealth);
    this->HealthComponent->OnDied.BindUObject(this, &AGameObject::OnDied);
	auto Lambda = [this]()
		{
			if (CropoutGameMode->GetGameInstance() == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("AGameObject::BeginPlay(): CropoutGameMode->GetGameInstance() == nullptr"));
				return;
			}
			if (CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("AGameObject::BeginPlay(): CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr"));
				return;
			}
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameRestart.AddUObject(this, &AGameObject::OnGameRestart);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStartInitialization.AddUObject(this, &AGameObject::OnGameStartInitialization);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameCompleteInitialization.AddUObject(this, &AGameObject::OnGameCompleteInitialization);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerReturnStartMenu.AddUObject(this, &AGameObject::OnPlayerReturnStartMenu);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGamePause.AddUObject(this, &AGameObject::OnGamePause);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameResume.AddUObject(this, &AGameObject::OnGameResume);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameSave.AddUObject(this, &AGameObject::OnGameSave);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStart.AddUObject(this, &AGameObject::OnGameStart);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectBeginPlay.AddUObject(this, &AGameObject::OnObjectBeginPlay);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEndPlay.AddUObject(this, &AGameObject::OnObjectEndPlay);
		};
	GetWorld()->GetTimerManager().SetTimer(this->InitializationTimer, Lambda, 1.0f, false);


}

void AGameObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector2D Position;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PlayerController, FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f), Position, false);
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->UpdateHealthBarPosition(FName(this->GetName()), Position);

}

UCapsuleComponent* AGameObject::GetCapsuleComponent()
{
	if (CapsuleComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameObject::GetCapsuleComponent(): CapsuleComponent == nullptr"));
	}
	return CapsuleComponent;
}

ACropoutGameMode* AGameObject::GetGameMode()
{
    if (CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameObject::GetGameMode(): CropoutGameMode == nullptr"));
	}
	return CropoutGameMode;
}

UStaticMeshComponent* AGameObject::GetMeshComponent()
{
    if (MeshComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameObject::GetMeshComponent(): MeshComponent == nullptr"));
	}
	return MeshComponent;
}

USceneComponent* AGameObject::GetSceneComponent()
{
    if (SceneComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameObject::GetSceneComponent(): SceneComponent == nullptr"));
	}
	return SceneComponent;
}

UHealthComponent* AGameObject::GetHealthComponent()
{
    if (HealthComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameObject::GetHealthComponent(): HealthComponent == nullptr"));
	}
	return HealthComponent;
}

UDamageComponent* AGameObject::GetDamageComponent()
{
    if (DamageComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AGameObject::GetDamageComponent(): DamageComponent == nullptr"));
	}
	return DamageComponent;
}


EGameObjectType AGameObject::GetGameObjectType()
{
	
    return this->GameObjectType;
}

void AGameObject::SetGameObjectType(EGameObjectType NewType)
{
	this->GameObjectType = NewType;

}

void AGameObject::SetRelatedObjectPoolType(EObjectPoolType NewType)
{
	this->ObjectPoolType = NewType;

}

EObjectPoolType AGameObject::GetRelatedObjectPoolType()
{

	return this->ObjectPoolType;
}


FVector AGameObject::GetGameObjectLocation()
{
    return this->GetActorLocation();
}


void AGameObject::SetGameObjectLocation(const FVector& ObjectLocation)
{


}

UStaticMesh* AGameObject::GetRandomMesh()
{
	UStaticMesh* Mesh = nullptr;
	if (MeshArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AGameObject::GetRandomMesh(): MeshArray.Num() == 0"));
		return Mesh;
	}
	Mesh = MeshArray[FMath::RandRange(0, MeshArray.Num() - 1)];
	return Mesh;
	/*this->MeshComponent->SetStaticMesh(Mesh);
	this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));*/

}


void AGameObject::LoadDataByManager()
{
	FName ActorName = FName(GetName());
	FGameObjectData TargetData;
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckGameObjectDataIsExist(ActorName) == false)
	{
		return;
	}
	TargetData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameObjectData(ActorName);
	this->MeshIndex = TargetData.MeshIndex;
	this->HealthComponent->SetCurrentHealth(TargetData.Health);
	this->HealthComponent->SetMaxHealth(TargetData.MaxHealth);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(this,TargetData.Transform,this->ObjectPoolType);
	///UE_LOG(LogTemp, Warning, TEXT(" Load: Name = %s , Location = %s "),*GetName() ,*TargetData.Transform.GetLocation().ToString());

}

void AGameObject::SaveDataToManager()
{
	FName ActorName = FName(GetName());
	FGameObjectData NewData;
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckGameObjectDataIsExist(ActorName) == false)
	{
		return;
	}
	NewData.MeshIndex = MeshArray.Find(this->MeshComponent->GetStaticMesh());
	//NewData.MeshIndex = this->MeshIndex;
	NewData.Transform = GetActorTransform();
	NewData.Health = this->HealthComponent->GetCurrentHealth();
    NewData.MaxHealth = this->HealthComponent->GetMaxHealth();
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdateGameObjectData(ActorName, NewData);
	///UE_LOG(LogTemp, Warning, TEXT("Save: Name = %s, Location = %s "), *GetName() ,*NewData.Transform.GetLocation().ToString());
}


void AGameObject::OnGameCompleteInitialization()
{


}

void AGameObject::OnGameStartInitialization()
{


}

void AGameObject::OnReduceHealth(float Damage, AActor* CauserActor)
{
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->DisplayHealthBar(FName(this->GetName()), this->HealthComponent->GetHealthPercent());



}

void AGameObject::OnAddHealth(float Heal, AActor* CauserActor)
{
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->DisplayHealthBar(FName(this->GetName()), this->HealthComponent->GetHealthPercent());


}

void AGameObject::OnDied()
{
	//auto Lambda = [this]()
	//{
	//	/*this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::Tree);
	//	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());
	//	UE_LOG(LogTemp, Warning, TEXT("Tree Died !!!!!"));*/
	//};
	//GetWorld()->GetTimerManager().SetTimer(this->DeathTimer, Lambda, 2.0f, false);
	////this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::Tree);
	//this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());



}


void AGameObject::OnObjectBeginPlay(AActor* Object)
{
	if (Object != this)
	{
		return;
	}
	if (MeshArray.IsValidIndex(this->MeshIndex) == false )
	{
		if (MeshArray.Num() == 0)
		{
			return;
		}
		UStaticMesh* Mesh = GetRandomMesh();
		this->MeshIndex = this->MeshArray.Find(Mesh);
		this->MeshComponent->SetStaticMesh(Mesh);
		this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));
	}
	else
	{
		if (MeshArray.Num() == 0)
		{
			return;
		}
		this->MeshComponent->SetStaticMesh(MeshArray[this->MeshIndex]);
		this->MeshComponent->SetMaterial(0, MeshArray[this->MeshIndex]->GetMaterial(0));
	}
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->BindHealthBar(this->CropoutGameMode->GetGameInstance(), this->CropoutGameMode->GetProgressBarWidgetClass(), FName(this->GetName()));
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckGameObjectDataIsExist(FName(GetName())) == false)
	{
		this->CropoutGameMode->GetGameInstance()->GetDataManager()->CreateGameObjectData(FName(this->GetName()));
	}

}


void AGameObject::OnObjectEndPlay(AActor* Object)
{
	if (Object != this)
	{
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->UnbindHealthBar(FName(this->GetName()));
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->DeleteGameObjectData(FName(this->GetName()));
	this->MeshIndex = -1;

}



void AGameObject::OnPlayerReturnStartMenu()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, this->ObjectPoolType)==false)
	{
		return;
	}
	
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, this->ObjectPoolType);

}

void AGameObject::OnGameSave()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, this->ObjectPoolType) == false)
	{
		return;
	}
	SaveDataToManager();



}


void AGameObject::OnGameRestart()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, this->ObjectPoolType) == false)
	{
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, this->ObjectPoolType);

}

void AGameObject::OnGameStart()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, this->ObjectPoolType) == false)
	{
		return;
	}



}

void AGameObject::OnGamePause()
{
	

}


void AGameObject::OnGameResume(EGameStatus CurrentStatus)
{
	if (CurrentStatus == EGameStatus::None)
	{
		LoadDataByManager();

	}

}






