

#include "GameMode/CropoutGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Manager/DelegateManager.h"
#include "GameInstance/CropoutGameInstance.h"
#include "ObjectPool/GuidanceLineSegmentObjectPool.h"
#include "ObjectPool/CircleRingObjectPool.h"
#include "ObjectPool/TreeObjectPool.h"
#include "ObjectPool/ShrubObjectPool.h"
#include "ObjectPool/StoneObjectPool.h"
#include "ObjectPool/TownHallObjectPool.h"
#include "ObjectPool/GrassObjectPool.h"
#include "Manager/WidgetManager.h"
#include "Struct/Cardinformation.h"
#include "ObjectPool/PlaceHolderObjectPool.h"
#include "ObjectPool/VillagerHouseObjectPool.h"
#include "ObjectPool/MonumentObjectPool.h"
#include "ObjectPool/LettuceFieldObjectPool.h"
#include "ObjectPool/WheatFieldObjectPool.h"
#include "ObjectPool/PumpkinFieldObjectPool.h"
#include "ObjectPool/CornFieldObjectPool.h"
#include "ObjectPool/VillagerObjectPool.h"
#include "GameObjectGenerator/GameObjectGenerator.h"
#include "Manager/DataManager.h"

ACropoutGameMode::ACropoutGameMode()
{
}


void ACropoutGameMode::BeginPlay()
{
	Super::BeginPlay();
	this->CropoutGameInstance = Cast<UCropoutGameInstance>(UGameplayStatics::GetGameInstance(this));
	if(this->CropoutGameInstance==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::BeginPlay(): this->CropoutGameInstance == nullptr"));
		return;
	}
	
	SpawnObjectPool();
	this->CropoutGameInstance->GetWidgetManager()->CreateCropoutWidget(this->GetGameInstance(),this->WidgetClassMap);
	this->CropoutGameInstance->GetWidgetManager()->AddBackGroundWidgetToViewport();
    this->CropoutGameInstance->GetWidgetManager()->AddUserTipWidgetYoViewport();
	this->CropoutGameInstance->GetWidgetManager()->AddLoadWidgetToViewport();
	this->CropoutGameInstance->GetWidgetManager()->AddStartWidgetToViewport();
	this->CropoutGameInstance->GetDelegateManager()->OnGameWin.AddUObject(this, &ACropoutGameMode::OnGameWin);
	this->CropoutGameInstance->GetDelegateManager()->OnGameOver.AddUObject(this, &ACropoutGameMode::OnGameOver);
	this->CropoutGameInstance->GetDelegateManager()->OnGameSave.AddUObject(this, &ACropoutGameMode::OnGameSave);
	this->CropoutGameInstance->GetDelegateManager()->OnGameRestart.AddUObject(this, &ACropoutGameMode::OnGameRestart);
	this->CropoutGameInstance->GetDelegateManager()->OnGameResume.AddUObject(this, &ACropoutGameMode::OnGameResume);
	this->CropoutGameInstance->GetDelegateManager()->OnGamePause.AddUObject(this, &ACropoutGameMode::OnGamePause);
	this->CropoutGameInstance->GetDelegateManager()->OnGameQuit.AddUObject(this, &ACropoutGameMode::OnGameQuit);
	this->CropoutGameInstance->GetDelegateManager()->OnGameStartInitialization.AddUObject(this, &ACropoutGameMode::OnGameStartInitialization);
	this->CropoutGameInstance->GetDelegateManager()->OnGameCompleteInitialization.AddUObject(this, &ACropoutGameMode::OnGameCompleteInitialization);
	this->CropoutGameInstance->GetDelegateManager()->OnGameStart.AddUObject(this, &ACropoutGameMode::OnGameStart);
	this->CropoutGameInstance->GetDelegateManager()->OnPlayerOpenCardSelectionPanel.AddUObject(this, &ACropoutGameMode::OnPlayerOpenCardSelectionPanel);
	this->CropoutGameInstance->GetDelegateManager()->OnPlayerCloseCardSelectionPanel.AddUObject(this, &ACropoutGameMode::OnPlayerCloseCardSelectionPanel);
	this->CropoutGameInstance->GetDelegateManager()->OnPlayerReturnStartMenu.AddUObject(this, &ACropoutGameMode::OnPlayerReturnStartMenu);
	GetWorld()->GetTimerManager().SetTimer(this->TickTimer, this, &ACropoutGameMode::TickFunction, 1.0f, true);
	GetWorld()->GetTimerManager().PauseTimer(this->TickTimer);
}


void ACropoutGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACropoutGameMode::TickFunction()
{
	int32 PlayTime = this->GetGameInstance()->GetDataManager()->GetPlayTime();
	PlayTime += 1;
	this->GetGameInstance()->GetDataManager()->SetPlayTime(PlayTime);
	int32 Minute = PlayTime / 60;
	int32 Second = PlayTime % 60;
	FString String = FString::FromInt(Minute) + FString(" M ") + FString::FromInt(Second) + FString(" S");
	UE_LOG(LogTemp, Warning, TEXT("PlayTime = %s"), *String);


}

UClass* ACropoutGameMode::GetGameObjectGeneratorClass()
{
	if(this->GameObjectGeneratorClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::GetGameObjectGeneratorClass(): GameObjectGeneratorClass is nullptr"));
		return nullptr;
	}
    return this->GameObjectGeneratorClass;

}



UClass* ACropoutGameMode::GetTextBlockWidgetClass()
{
	if(this->WidgetClassMap.Find(EWidgetType::TextBlock) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::GetTextBlockWidgetClass(): WidgetClassMap.Find(EWidgetType::TextBlock) == nullptr"));
		return nullptr;
	}
	return *this->WidgetClassMap.Find(EWidgetType::TextBlock);
}

UClass* ACropoutGameMode::GetProgressBarWidgetClass()
{
	if (this->WidgetClassMap.Find(EWidgetType::ProgressBar) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::GetProgressBarWidgetClass(): WidgetClassMap.Find(EWidgetType:ProgressBar) == nullptr"));
		return nullptr;
	}
	return *this->WidgetClassMap.Find(EWidgetType::ProgressBar);
}



TArray<AActor*> ACropoutGameMode::GetGuidanceLineSegmentArray()
{
	if (this->GuidanceLineSegmentObjectPool == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::GetGuidanceLineSegmentArray(): GuidanceLineSegmentObjectPool is nullptr"));
		return TArray<AActor*>();
	}
	return this->GuidanceLineSegmentObjectPool->GetGuidanceLineSegmentArray();
}

void ACropoutGameMode::SpawnTreeByGenerator()
{
	AGameObjectGenerator* Generator = nullptr;
	FVector Location = FVector::ZeroVector;
	const int32 Number = 10;
	if (this->GameObjectGeneratorClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnTreeByGenerator(): GameObjectGeneratorClass is nullptr"));
		return;
	}
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location, FRotator::ZeroRotator);
	Generator->SpawnTree(Number);
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + FVector(-3000.0f,3000.0f,0.0f), FRotator::ZeroRotator);
	Generator->SpawnTree(Number);
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + FVector(3000.0f, -3000.0f, 0.0f), FRotator::ZeroRotator);
	Generator->SpawnTree(Number);
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + FVector(3000.0f, 3000.0f, 0.0f), FRotator::ZeroRotator);
	Generator->SpawnTree(Number);
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + FVector(-3000.0f, -3000.0f, 0.0f), FRotator::ZeroRotator);
	Generator->SpawnTree(Number);


}

void ACropoutGameMode::SpawnStoneByGenerator()
{
	AGameObjectGenerator* Generator = nullptr;
	FVector Location = FVector::ZeroVector;
	bool i = true;
	const int32 Number = 10;
	if (this->GameObjectGeneratorClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnTreeByGenerator(): GameObjectGeneratorClass is nullptr"));
		return;
	}
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location, FRotator::ZeroRotator);
	Generator->SpawnStone(Number);
	i = FMath::RandBool();
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + (i == true ? FVector(3000.0f, 3000.0f, 0.0f) : FVector(-3000.0f, -3000.0f, 0.0f)), FRotator::ZeroRotator);
	Generator->SpawnStone(Number);
	i = FMath::RandBool();
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + (i == true ? FVector(3000.0f, -3000.0f, 0.0f) : FVector(-3000.0f, 3000.0f, 0.0f)), FRotator::ZeroRotator);
	Generator->SpawnStone(Number);


}

void ACropoutGameMode::SpawnShrubByGenerator()
{
	AGameObjectGenerator* Generator = nullptr;
	FVector Location = FVector::ZeroVector;
	bool i = true;
	const int32 Number = 10;
	if (this->GameObjectGeneratorClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnTreeByGenerator(): GameObjectGeneratorClass is nullptr"));
		return;
	}
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location, FRotator::ZeroRotator);
	Generator->SpawnShrub(Number);
	i = FMath::RandBool();
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + (i == true ? FVector(3000.0f, 3000.0f, 0.0f) : FVector(-3000.0f, -3000.0f, 0.0f)), FRotator::ZeroRotator);
	Generator->SpawnShrub(Number);
	i = FMath::RandBool();
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + (i == true ? FVector(3000.0f, -3000.0f, 0.0f) : FVector(-3000.0f, 3000.0f, 0.0f)), FRotator::ZeroRotator);
	Generator->SpawnShrub(Number);


}

void ACropoutGameMode::SpawnGrassByGenerator()
{
	AGameObjectGenerator* Generator = nullptr;
	FVector Location = FVector::ZeroVector;
	const int32 Number = 50;
	if (this->GameObjectGeneratorClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnGrassByGenerator(): GameObjectGeneratorClass is nullptr"));
		return;
	}
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location, FRotator::ZeroRotator);
	Generator->SpawnGrass(Number);
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + FVector(3000.0f,3000.0f,0.0f), FRotator::ZeroRotator);
	Generator->SpawnGrass(Number);
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + FVector(-3000.0f,-3000.0f, 0.0f), FRotator::ZeroRotator);
	Generator->SpawnGrass(Number);
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + FVector(3000.0f, -3000.0f, 0.0f), FRotator::ZeroRotator);
	Generator->SpawnGrass(Number);
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, Location + FVector(-3000.0f, 3000.0f, 0.0f), FRotator::ZeroRotator);
	Generator->SpawnGrass(Number);


}

void ACropoutGameMode::SpawnTownHallByGenerator()
{
	AGameObjectGenerator* Generator = nullptr;
	if (this->GameObjectGeneratorClass == nullptr)
	{
        UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnTownHallByGenerator(): GameObjectGeneratorClass is nullptr"));
        return;
	}
	Generator = GetWorld()->SpawnActor<AGameObjectGenerator>(this->GameObjectGeneratorClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if(Generator == nullptr)
	{ 
        UE_LOG(LogTemp,Warning,TEXT("ACropoutGameMode::SpawnTownHallByGenerator(): Generator == nullptr"));
        return;
	}
	Generator->SpawnTownHall();

}

void ACropoutGameMode::SpawnObjectPool()
{ 
	if (this->ObjectPoolClassMap.Find(EObjectPoolType::GuidanceLineSegment) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): ObjectPoolClassMap.Find(EObjectPoolType::GuidanceLineSegment) == nullptr"));
		return;
	}
	if (this->ObjectPoolClassMap.Find(EObjectPoolType::CircleRing) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::CircleRing) == nullptr"));
		return;
	}			
    if (this->ObjectPoolClassMap.Find(EObjectPoolType::Tree) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::Tree) == nullptr"));
		return;
	}
    if (this->ObjectPoolClassMap.Find(EObjectPoolType::Shrub) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::Shrub) == nullptr"));
		return;
	}
    if (this->ObjectPoolClassMap.Find(EObjectPoolType::Stone) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::Stone) == nullptr"));
		return;
	}
	if (this->ObjectPoolClassMap.Find(EObjectPoolType::Grass) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::Grass) == nullptr"));
		return;
	}
    if (this->ObjectPoolClassMap.Find(EObjectPoolType::TownHall) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::TownHall) == nullptr"));
		return;
	}
	if (this->ObjectPoolClassMap.Find(EObjectPoolType::VillagerHouse) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::VillagerHouse) == nullptr"));
		return;
	}
	if (this->ObjectPoolClassMap.Find(EObjectPoolType::Villager) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::VillagerHouse) == nullptr"));
		return;
	}
	if (this->ObjectPoolClassMap.Find(EObjectPoolType::Monument) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::Monument) == nullptr"));
		return;
	}
	if (this->ObjectPoolClassMap.Find(EObjectPoolType::CornField) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::CornField) == nullptr"));
		return;
	}
	if (this->ObjectPoolClassMap.Find(EObjectPoolType::WheatField) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::WheatField) == nullptr"));
		return;
	}

	if (this->ObjectPoolClassMap.Find(EObjectPoolType::PumpkinField) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::PumpkinField) == nullptr"));
		return;
	}
	if (this->ObjectPoolClassMap.Find(EObjectPoolType::LettuceField) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::SpawnObjectPool(): this->ObjectPoolClassMap.Find(EObjectPoolType::LettuceField) == nullptr"));
		return;
	}
	FTransform Transform;
	this->GuidanceLineSegmentObjectPool = GetWorld()->SpawnActor<AGuidanceLineSegmentObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::GuidanceLineSegment), Transform);
	this->CircleRingObjectPool = GetWorld()->SpawnActor<ACircleRingObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::CircleRing), Transform);
    this->TreeObjectPool = GetWorld()->SpawnActor<ATreeObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::Tree), Transform);
    this->ShrubObjectPool = GetWorld()->SpawnActor<AShrubObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::Shrub), Transform);
    this->StoneObjectPool = GetWorld()->SpawnActor<AStoneObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::Stone), Transform);
    this->TownHallObjectPool = GetWorld()->SpawnActor<ATownHallObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::TownHall), Transform);
    this->GrassObjectPool = GetWorld()->SpawnActor<AGrassObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::Grass), Transform);
	this->PlaceHolderObjectPool = GetWorld()->SpawnActor<APlaceHolderObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::PlaceHolder), Transform);
	this->VillagerHouseObjectPool = GetWorld()->SpawnActor<AVillagerHouseObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::VillagerHouse), Transform);
    this->MonumentObjectPool = GetWorld()->SpawnActor<AMonumentObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::Monument), Transform);
	this->CornFieldObjectPool = GetWorld()->SpawnActor<ACornFieldObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::CornField), Transform);
	this->WheatFieldObjectPool = GetWorld()->SpawnActor<AWheatFieldObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::WheatField), Transform);
	this->PumpkinFieldObjectPool = GetWorld()->SpawnActor<APumpkinFieldObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::PumpkinField), Transform);
	this->LettuceFieldObjectPool = GetWorld()->SpawnActor<ALettuceFieldObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::LettuceField), Transform);
	this->VillagerObjectPool = GetWorld()->SpawnActor<AVillagerObjectPool>(*this->ObjectPoolClassMap.Find(EObjectPoolType::Villager), Transform);


}

void ACropoutGameMode::SetMouseLocation(FVector NewLocation)
{
    this->MouseLocation = NewLocation;
}


FVector ACropoutGameMode::GetMouseLocation()
{
	return this->MouseLocation;
}

FVector ACropoutGameMode::GetTownHallLocation()
{
	return this->TownHallObjectPool->GetTownHallLocation();
}

TArray<FName> ACropoutGameMode::GetAllActiveObjectName(EObjectPoolType PoolType)
{
	TArray<FName> Array;
	switch (PoolType)
	{
	case EObjectPoolType::CircleRing:
		for (auto Element : this->CircleRingObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::Grass:
		for (auto Element : this->GrassObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::GuidanceLineSegment:
		for (auto Element : this->GuidanceLineSegmentObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::Monument:
		for (auto Element : this->MonumentObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::Shrub:
		for (auto Element : this->ShrubObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::Stone:
		for (auto Element : this->StoneObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::TownHall:
		for (auto Element : this->TownHallObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::Tree:
		for (auto Element : this->TreeObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::Villager:
		for (auto Element : this->VillagerObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));

		}
		break;
	case EObjectPoolType::VillagerHouse:
		for (auto Element : this->VillagerHouseObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::WheatField:
		for (auto Element : this->WheatFieldObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::CornField:
		for (auto Element : this->CornFieldObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::LettuceField:
		for (auto Element : this->LettuceFieldObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::PumpkinField:
		for (auto Element : this->PumpkinFieldObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	case EObjectPoolType::PlaceHolder:
		for (auto Element : this->PlaceHolderObjectPool->GetAllActiveObject())
		{
			Array.Add(FName(Element->GetName()));
		}
		break;
	}
	if (Array.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT(" ACropoutGameMode::GetAllActiveObjectName(): Array.Num() == 0"));
	}
    return Array;
}


bool ACropoutGameMode::CheckActorIsActive(AActor* Object, EObjectPoolType PoolType)
{
	bool IsActive = false;
	switch (PoolType)
	{
	case EObjectPoolType::CircleRing:
		IsActive = this->CircleRingObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::GuidanceLineSegment:
		IsActive = this->GuidanceLineSegmentObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::Grass:
		IsActive = this->GrassObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::Tree:
		IsActive = this->TreeObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::Shrub:
		IsActive = this->ShrubObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::Stone:
		IsActive = this->StoneObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::TownHall:
		IsActive = this->TownHallObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::VillagerHouse:
		IsActive = this->VillagerHouseObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::Villager:
		IsActive = this->VillagerObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::Monument:
		IsActive = this->MonumentObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::LettuceField:
		IsActive = this->LettuceFieldObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::WheatField:
		IsActive = this->WheatFieldObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::PumpkinField:
		IsActive = this->PumpkinFieldObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::CornField:
		IsActive = this->CornFieldObjectPool->CheckObjectIsActive(Object);
		break;
	case EObjectPoolType::PlaceHolder:
		IsActive = this->PlaceHolderObjectPool->CheckObjectIsActive(Object);
	}
	return IsActive;
}


bool ACropoutGameMode::CheckObjectPoolIsEmpty(EObjectPoolType PoolType)
{
	bool IsEmpty = false;
	switch (PoolType)
	{
	case EObjectPoolType::CircleRing:
		IsEmpty = this->CircleRingObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::GuidanceLineSegment:
		IsEmpty = this->GuidanceLineSegmentObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::Grass:
		IsEmpty = this->GrassObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::Tree:
		IsEmpty = this->TreeObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::Shrub:
		IsEmpty = this->ShrubObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::Stone:
		IsEmpty = this->StoneObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::TownHall:
		IsEmpty = this->TownHallObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::VillagerHouse:
		IsEmpty = this->VillagerHouseObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::Villager:
		IsEmpty = this->VillagerObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::Monument:
		IsEmpty = this->MonumentObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::LettuceField:
		IsEmpty = this->LettuceFieldObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::WheatField:
		IsEmpty = this->WheatFieldObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::PumpkinField:
		IsEmpty = this->PumpkinFieldObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::CornField:
		IsEmpty = this->CornFieldObjectPool->CheckObjectPoolIsEmpty();
		break;
	case EObjectPoolType::PlaceHolder:
		IsEmpty = this->PlaceHolderObjectPool->CheckObjectPoolIsEmpty();
	}
	return IsEmpty;
}


FCardInformation ACropoutGameMode::GetCardInformationFromTable(FName CardName)
{
	if (CardInformationTable == nullptr)
	{
        UE_LOG(LogTemp, Warning, TEXT("ACropoutGameMode::GetCardInformationFromTable(): CardInformationTable == nullptr"));
		return FCardInformation();
	}

    return *CardInformationTable->FindRow<FCardInformation>(CardName, "");
}

void ACropoutGameMode::OnPlayerReturnStartMenu()
{
	this->CropoutGameInstance->GetWidgetManager()->RemoveTopWidgetFromViewport();
	this->CropoutGameInstance->GetWidgetManager()->AddStartWidgetToViewport();


}

void ACropoutGameMode::OnGameWin()
{
	this->CropoutGameInstance->GetWidgetManager()->RemoveAllWidgetFromViewport();
	this->CropoutGameInstance->GetWidgetManager()->AddVictoryWidgetToViewport();
	GetWorld()->GetTimerManager().PauseTimer(this->TickTimer);

}

void ACropoutGameMode::OnGameOver()
{
	this->CropoutGameInstance->GetWidgetManager()->RemoveAllWidgetFromViewport();
	this->CropoutGameInstance->GetWidgetManager()->AddFailureWidgetToViewport();
	GetWorld()->GetTimerManager().PauseTimer(this->TickTimer);

}

void ACropoutGameMode::OnGameSave()
{
	
}

void ACropoutGameMode::OnGameQuit()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);

}


void ACropoutGameMode::OnGameStart()
{
	this->CropoutGameInstance->GetWidgetManager()->RemoveTopWidgetFromViewport();
	this->CropoutGameInstance->GetWidgetManager()->AddBattleWidgetToViewport();
	GetWorld()->GetTimerManager().UnPauseTimer(this->TickTimer);

}


void ACropoutGameMode::OnGameRestart()
{
	//this->CropoutGameInstance->GetWidgetManager()->RemoveAllWidgetFromViewport();
	//this->GetGameInstance()->GetWidgetManager()->PlayLoadAnimation(EUMGSequencePlayMode::Forward, 1.0f);


}

void ACropoutGameMode::OnGamePause()
{
	this->CropoutGameInstance->GetWidgetManager()->RemoveTopWidgetFromViewport();
	this->CropoutGameInstance->GetWidgetManager()->AddPauseWidgetToViewport();
	//this->CropoutGameInstance->GetWidgetManager()->UpdateBackGroundIamge(EWidgetType::Pause);
	GetWorld()->GetTimerManager().PauseTimer(this->TickTimer);


}


void ACropoutGameMode::OnGameResume(EGameStatus CurrentStatus)
{
	if (CurrentStatus == EGameStatus::GamePause)
	{
		this->CropoutGameInstance->GetWidgetManager()->RemoveTopWidgetFromViewport();
		this->CropoutGameInstance->GetWidgetManager()->AddBattleWidgetToViewport();
	}
	else
	{
		this->GetGameInstance()->GetWidgetManager()->PlayLoadAnimation(EUMGSequencePlayMode::PingPong, 1.0f);
	}
	GetWorld()->GetTimerManager().UnPauseTimer(this->TickTimer);

}


void ACropoutGameMode::OnGameStartInitialization()
{	
	SpawnGrassByGenerator();
	SpawnShrubByGenerator();
	SpawnStoneByGenerator();
	SpawnTreeByGenerator();
	SpawnTownHallByGenerator();
}


void ACropoutGameMode::OnGameCompleteInitialization()
{
	this->GetGameInstance()->GetWidgetManager()->PlayLoadAnimation(EUMGSequencePlayMode::Reverse, 1.0f);

}


void ACropoutGameMode::OnPlayerOpenCardSelectionPanel()
{
	this->CropoutGameInstance->GetWidgetManager()->AddConstructionWidgetInViewport();
    this->CropoutGameInstance->GetWidgetManager()->OpenCardSelectionPanel();
	
}


void ACropoutGameMode::OnPlayerCloseCardSelectionPanel()
{
    this->CropoutGameInstance->GetWidgetManager()->CloseCardSelectionPanel();
	
}


















