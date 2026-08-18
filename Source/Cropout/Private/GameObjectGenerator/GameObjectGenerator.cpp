#include "GameObjectGenerator/GameObjectGenerator.h"

#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Component/CollisionDetectionComponent.h"
#include "Components/BoxComponent.h"
#include "Containers/Set.h"
#include "Manager/DataManager.h"

int32 AGameObjectGenerator::InstanceCount = 0;
bool AGameObjectGenerator::IsCompleteInitialization = false;

AGameObjectGenerator::AGameObjectGenerator()
{
	PrimaryActorTick.bCanEverTick = false;
	this->SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	this->BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	this->CollisionDetectionComponent = CreateDefaultSubobject<UCollisionDetectionComponent>(TEXT("CollisionDetectionComponent"));
	this->SetRootComponent(this->SceneComponent);
	this->BoxComponent->SetupAttachment(this->SceneComponent);
	if(HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject| RF_NeedLoad) == false)
	{
		this->InstanceCount++;
	}


}

AGameObjectGenerator::~AGameObjectGenerator()
{
	
}



void AGameObjectGenerator::BeginPlay()
{
	Super::BeginPlay();
	CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT(" AGameObjectGenerator::BeginPlay(): CropoutGameMode == nullptr"));
		return;
	}
	EGameStatus GameStatus = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameStatus();
	if (this->IsCompleteInitialization == true && (GameStatus == EGameStatus::None|| GameStatus == EGameStatus::GameOver || GameStatus == EGameStatus::GamePause))
	{
		this->IsCompleteInitialization = false;

	}
	
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStart.AddUObject(this, &AGameObjectGenerator::OnGameStart);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameRestart.AddUObject(this, &AGameObjectGenerator::OnGameRestart);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStartInitialization.AddUObject(this, &AGameObjectGenerator::OnGameStartInitialization);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameWin.AddUObject(this, &AGameObjectGenerator::OnGameWin);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGamePause.AddUObject(this, &AGameObjectGenerator::OnGamePause);


}

void AGameObjectGenerator::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject | RF_NeedLoad) == false)
	{
		this->InstanceCount--;
		if (this->InstanceCount == 0 && this->IsCompleteInitialization == false)
		{
			this->IsCompleteInitialization = true;
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameCompleteInitialization.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT(" AGameObjectGenerator::EndPlay(): Game Complete Initialization !!!!!"));

		}
	}
	//UE_LOG(LogTemp, Warning, TEXT(" AGameObjectGenerator::EndPlay(): %s, InstanceCount = %d"),*GetName(),this->InstanceCount);
}


void AGameObjectGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameObjectGenerator::TickTimerFunction()
{

}

FTransform AGameObjectGenerator::GetRandomTransform(const FVector& Range, float MinLocationZ, float MaxLocationZ, float MinRotationYaw, float MaxRotationYaw, int32 MinScale, int32 MaxScale)
{
	FTransform RandomTransform;
	FVector RandomLocation;
	FRotator RandomRotation;
	FVector RandomScale;
	float LocationX = 0.0f;
	float LocationY = 0.0f;
	const float OffsetValue = 900.0f;
	this->BoxComponent->SetBoxExtent(Range);
	LocationX = this->BoxComponent->GetUnscaledBoxExtent().X / 2 + OffsetValue;
	LocationY = this->BoxComponent->GetUnscaledBoxExtent().Y / 2 + OffsetValue;
	RandomLocation.X = FMath::RandRange(-LocationX, LocationX);
	RandomLocation.Y = FMath::RandRange(-LocationY, LocationY);
	RandomLocation.Z = FMath::RandRange(MinLocationZ, MaxLocationZ);
	RandomLocation = FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f) + RandomLocation;
	RandomRotation.Yaw = FMath::RandRange(MinRotationYaw, MaxRotationYaw);
	RandomScale = FVector(FMath::RandRange(MinScale, MaxScale)) * 0.1;
	RandomTransform.SetLocation(RandomLocation);
    RandomTransform.SetRotation(RandomRotation.Quaternion());
	RandomTransform.SetScale3D(RandomScale);
	return RandomTransform;
}

void AGameObjectGenerator::SpawnTree(int32 Number)
{
	
	//0.5(0,-100),0.6(0,-120),0.7(0,-140),0.8(0,-160),0.9(0,-180),1.0(0,-200),1.1(0,-220),1.2(0,-240)
	TMap<float,float> MaxLocationZMap;
	for (int32 i = 0; i < 11; i++)
	{
		MaxLocationZMap.Add(i * 0.1 + 0.5f, -100 - (i * 20.0f));
	}
	auto Lambda = [this,Number,MaxLocationZMap]()
	{
		FTransform RandomTransform;
		float LocationZ = 0.0f;
		RandomTransform = GetRandomTransform(FVector(2000.0f, 2000.0f, 100.0f), 0.0f, 0.0f,-180.0f,180.0f,5,15);
		if(MaxLocationZMap.Find(RandomTransform.GetScale3D().X)==nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT(" AGameObjectGenerator::SpawnTree(): MaxLocationZMap.Find(RandomTransform.GetScale3D().X)==nullptr"));
			return ;
		}
		LocationZ = FMath::RandRange(0.0f, *MaxLocationZMap.Find(RandomTransform.GetScale3D().X));
        RandomTransform.SetLocation(FVector(RandomTransform.GetLocation().X,RandomTransform.GetLocation().Y,LocationZ));
		this->CollisionDetectionComponent->SphereTraceForObject(RandomTransform.GetLocation(), RandomTransform.GetLocation() + GetActorUpVector() * 700.0f,200.0f);
        if (this->CollisionDetectionComponent->GetHitResultArray().Num() == 0)
		{ 
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(nullptr,RandomTransform, EObjectPoolType::Tree);
			GameObjectCount++;
			if (GameObjectCount >= Number)
			{
				GetWorld()->GetTimerManager().ClearTimer(this->TickTimer);
				GameObjectCount = 0;
				Destroy();

			}

		}
		
	};
	GetWorld()->GetTimerManager().ClearTimer(this->TickTimer);
	GetWorld()->GetTimerManager().SetTimer(this->TickTimer, Lambda ,this->TickTimerInterval, true);



}

void AGameObjectGenerator::SpawnStone(int32 Number)
{
	auto Lambda = [this, Number]()
		{
			FTransform RandomTransform;
			RandomTransform = GetRandomTransform(FVector(2000.0f, 2000.0f, 100.0f), 0.0f, 0.0f, -180.0f, 180.0f, 5, 15);
			this->CollisionDetectionComponent->SphereTraceForObject(RandomTransform.GetLocation(), RandomTransform.GetLocation() + GetActorUpVector() * 200.0f, 200.0f);
			if (this->CollisionDetectionComponent->GetHitResultArray().Num() == 0)
			{
				this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(nullptr,RandomTransform, EObjectPoolType::Stone);
				GameObjectCount++;
				if (GameObjectCount >= Number)
				{
					GetWorld()->GetTimerManager().ClearTimer(this->TickTimer);
					GameObjectCount = 0;
					Destroy();
				}
			}
		};
	GetWorld()->GetTimerManager().ClearTimer(this->TickTimer);
	GetWorld()->GetTimerManager().SetTimer(this->TickTimer, Lambda, this->TickTimerInterval, true);



}

void AGameObjectGenerator::SpawnShrub(int32 Number)
{
	auto Lambda = [this, Number]()
		{
			FTransform RandomTransform;
			RandomTransform = GetRandomTransform(FVector(2000.0f, 2000.0f, 100.0f), -30.0f, 0.0f, -180.0f, 180.0f, 5, 15);
			this->CollisionDetectionComponent->SphereTraceForObject(RandomTransform.GetLocation(), RandomTransform.GetLocation() + GetActorUpVector() * 200.0f, 100.0f);
			if (this->CollisionDetectionComponent->GetHitResultArray().Num() == 0)
			{
				this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(nullptr,RandomTransform, EObjectPoolType::Shrub);
				GameObjectCount++;
				if (GameObjectCount >= Number)
				{
					GetWorld()->GetTimerManager().ClearTimer(this->TickTimer);
					GameObjectCount = 0;

					Destroy();
				}
			}
		};
	GetWorld()->GetTimerManager().ClearTimer(this->TickTimer);
	GetWorld()->GetTimerManager().SetTimer(this->TickTimer, Lambda, this->TickTimerInterval, true);



}

void AGameObjectGenerator::SpawnGrass(int32 Number)
{
	
	auto Lambda = [this, Number]()
		{
			FTransform RandomTransform;
			RandomTransform = GetRandomTransform(FVector(3000.0f, 3000.0f, 100.0f), 0.0f, 0.0f, -180.0f, 180.0f, 5, 15);
			this->CollisionDetectionComponent->SphereTraceForObject(RandomTransform.GetLocation(), RandomTransform.GetLocation() + GetActorUpVector() * 200.0f, 50.0f);
			if (this->CollisionDetectionComponent->GetHitResultArray().Num() == 0)
			{
				this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(nullptr,RandomTransform, EObjectPoolType::Grass);
				GameObjectCount++;
				if (GameObjectCount >= Number)
				{
					GetWorld()->GetTimerManager().ClearTimer(this->TickTimer);
					GameObjectCount = 0;
					Destroy();
				}
			}
		};
	GetWorld()->GetTimerManager().ClearTimer(this->TickTimer);
	GetWorld()->GetTimerManager().SetTimer(this->TickTimer, Lambda, this->TickTimerInterval, true);



}

void AGameObjectGenerator::SpawnTownHall(int32 Number)
{

	FTransform RandomTransform;
	RandomTransform = GetRandomTransform(FVector(3000.0f, 3000.0f, 100.0f));
	RandomTransform.SetRotation(FRotator(0.0f).Quaternion());
	RandomTransform.SetScale3D(FVector(1.0f));
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(nullptr, RandomTransform, EObjectPoolType::TownHall);
	Destroy();
	



}


void AGameObjectGenerator::SpawnVillager(int32 Number)
{

	auto Lambda = [this, Number]()
		{
			FTransform RandomTransform;
			RandomTransform = GetRandomTransform(FVector(1000.0f, 1000.0f, 100.0f), 200.0f, 300.0f, 0.0f, 180.0f);
            RandomTransform.SetScale3D(FVector(1.0f));
			this->CollisionDetectionComponent->SphereTraceForObject(RandomTransform.GetLocation(), RandomTransform.GetLocation() + GetActorUpVector() * 500.0f, 20.0f);
			if (this->CollisionDetectionComponent->GetHitResultArray().Num() == 0)
			{
				this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(nullptr, RandomTransform, EObjectPoolType::Villager);
				this->GameObjectCount++;
				if (this->GameObjectCount >= Number)
				{
					this->CropoutGameMode->GetGameInstance()->GetDataManager()->SetVillagerCount(this->GameObjectCount);
					this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCountIncrease.Broadcast(this->GameObjectCount);

					GetWorld()->GetTimerManager().ClearTimer(this->TickTimer);
					this->GameObjectCount = 0;
					Destroy();
				}
			}
			
			
		};
	GetWorld()->GetTimerManager().ClearTimer(this->TickTimer);
	GetWorld()->GetTimerManager().SetTimer(this->TickTimer, Lambda, this->TickTimerInterval, true);



}

void AGameObjectGenerator::OnGameWin()
{

}

void AGameObjectGenerator::OnGameOver()
{

}

void AGameObjectGenerator::OnGameStartInitialization()
{
	/*if (this->IsCompleteInitialization == true)
	{
		this->IsCompleteInitialization = false;
		UE_LOG(LogTemp, Warning, TEXT("666666666666666"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("777777777777777777"));

	}*/
}

void AGameObjectGenerator::OnGameStart()
{
	//UE_LOG(LogTemp, Warning, TEXT("777777777777777777"));

}

void AGameObjectGenerator::OnGameRestart()
{
	//this->IsCompleteInitialization = false;

}


void AGameObjectGenerator::OnGamePause()
{

}


void AGameObjectGenerator::OnGameResume()
{

}



