#include "Player/CropoutPlayer.h"

#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerController/CropoutPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Component/CollisionDetectionComponent.h"
#include "Enum/GameObjectType/GameObjectType.h"
#include "Components/SplineComponent.h"
#include "Interface/GameObjectTypeInterface.h"
#include "Interface/GameObjectInteractionInterface.h"
#include "Interface/NPCStateInterface/NPCStateInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enum/ObjectPoolType.h"
#include "Manager/WidgetManager.h"
#include "Manager/DataManager.h"


//#include "Blueprint/WidgetBlueprintLibrary.h"


ACropoutPlayer::ACropoutPlayer()
{
	this->PrimaryActorTick.bCanEverTick = true;
	this->SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	this->SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	this->CollisionDetectionComponent = CreateDefaultSubobject<UCollisionDetectionComponent>(TEXT("CollisionDetectionComponent"));
	this->SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SetRootComponent(this->SceneComponent);
    this->SpringArmComponent->SetupAttachment(SceneComponent);
	this->CameraComponent->SetupAttachment(SpringArmComponent);
	this->SplineComponent->SetupAttachment(SceneComponent);



    this->SpringArmComponent->bDoCollisionTest = false;
	this->SpringArmComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	this->CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
	this->CameraComponent->SetOrthoWidth(6000.0f);
	this->CollisionDetectionComponent->IsUseDefaultObjectTypeQuery = false;



}

void ACropoutPlayer::BeginPlay()
{
	Super::BeginPlay();
	this->CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if(this->CropoutGameMode==nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ACropoutPlayer::BeginPlay(): CropoutGameMode == nullptr"));
		return;
	}
	if(this->CropoutGameMode->GetGameInstance()==nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ACropoutPlayer::BeginPlay(): CropoutGameMode->GetGameInstance() == nullptr"));
		return;
	}
	if(this->CropoutGameMode->GetGameInstance()->GetDelegateManager()==nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ACropoutPlayer::BeginPlay(): CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr"));
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameRestart.AddUObject(this, &ACropoutPlayer::OnGameRestart);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameWin.AddUObject(this, &ACropoutPlayer::OnGameWin);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGamePause.AddUObject(this, &ACropoutPlayer::OnGamePause);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameResume.AddUObject(this, &ACropoutPlayer::OnGameResume);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameSave.AddUObject(this, &ACropoutPlayer::OnGameSave);
	//this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameLoad.AddUObject(this, &ACropoutPlayer::OnGameStart);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStart.AddUObject(this, &ACropoutPlayer::OnGameStart);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerSelectCard.AddUObject(this, &ACropoutPlayer::OnPlayerSelectCard);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerResourceIncrease.AddUObject(this, &ACropoutPlayer::OnPlayerResourceIncrease);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerResourceReduce.AddUObject(this, &ACropoutPlayer::OnPlayerResourceReduce);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStartInitialization.AddUObject(this, &ACropoutPlayer::OnGameStartInitialization);



}

void ACropoutPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACropoutPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	ACropoutPlayerController* PlayerController = Cast<ACropoutPlayerController>(GetController());
	if(PlayerController==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayer::SetupPlayerInputComponent(): PlayerController == nullptr"));
		return;
	}
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(EnhancedInputComponent==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayer::SetupPlayerInputComponent(): EnhancedInputComponent == nullptr"));
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    if(LocalPlayerSubsystem==nullptr)
    {
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayer::SetupPlayerInputComponent(): LocalPlayerSubsystem==nullptr"));
	}
	EnhancedInputComponent->BindAction(PlayerController->GetMouseMovementInputAction(), ETriggerEvent::Triggered, this, &ACropoutPlayer::OnMouseMove);
    EnhancedInputComponent->BindAction(PlayerController->GetMouseLeftKeyInputAction(), ETriggerEvent::Started, this, &ACropoutPlayer::OnMouseLeftKeyPress);
	EnhancedInputComponent->BindAction(PlayerController->GetMouseLeftKeyInputAction(), ETriggerEvent::Completed, this, &ACropoutPlayer::OnMouseLeftKeyRelease);
	EnhancedInputComponent->BindAction(PlayerController->GetMouseWheelInputAction(), ETriggerEvent::Triggered, this, &ACropoutPlayer::OnMouseWheel);
	LocalPlayerSubsystem->AddMappingContext(PlayerController->GetInputMappingContext(), 0);




}

void ACropoutPlayer::UpdateScreenLocation(const FInputActionValue& Value)
{ 
	FVector NewLocation;
	FVector MovementDistance;
	FVector2D InputActionValue = Value.Get<FVector2D>();
	FVector2D ScreenPosition = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData().Operation.ScreenPosition;
	FVector2D ScreenPositionXRange = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData().Operation.ScreenPositionXRange;
	FVector2D ScreenPositionYRange = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData().Operation.ScreenPositionYRange;
	FGameSettingsData NewData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData();
	float ScreenMovementRate = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData().Operation.ScreenMovementRate;
	MovementDistance = FVector(InputActionValue.Y * -1, InputActionValue.X * -1, 0.0f) * ScreenMovementRate;
	NewLocation.X = FMath::Clamp(FVector(GetActorLocation() + MovementDistance).X,ScreenPositionXRange.X, ScreenPositionXRange.Y);
    NewLocation.Y = FMath::Clamp(FVector(GetActorLocation() + MovementDistance).Y, ScreenPositionYRange.X, ScreenPositionYRange.Y);
	SetActorLocation(NewLocation);
	NewData.Operation.ScreenPosition = FVector2D(NewLocation.X,NewLocation.Y);
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdateGameSettingsData(NewData);


}


void ACropoutPlayer::UpdateScreenScale(const FInputActionValue& Value)
{
	float InputActionValue = Value.Get<float>();
	FGameSettingsData NewData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData();

	float ScreenScaleRate = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData().Operation.ScreenScaleRate;
	float MinScreenScale = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData().Operation.MinScreenScale;
	float MaxScreenScale = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData().Operation.MaxScreenScale;
	float ScaleInterval = ScreenScaleRate * (InputActionValue * -1);
	float NewOrthoWidth = FMath::Clamp((this->CameraComponent->OrthoWidth + ScaleInterval), MinScreenScale, MaxScreenScale);
	this->CameraComponent->SetOrthoWidth(NewOrthoWidth);
	NewData.Operation.ScreenScale = NewOrthoWidth;
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdateGameSettingsData(NewData);


}

void ACropoutPlayer::MouseLineTrace(TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQuery)
{
	FVector Location;
	FVector Direction;
	float Distance = 9999.0f;
	FVector StartLocation;
	FVector EndLocation;
	ACropoutPlayerController* PlayerController = Cast<ACropoutPlayerController>(GetController());
	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayer::OnMouseLeftKeyClick(): PlayerController == nullptr"));
		return;
	}
	PlayerController->GetMouseLocationAndDirection(Location, Direction);
	StartLocation = Location;
	EndLocation = Location + Distance * Direction;
	this->CollisionDetectionComponent->LineTraceForObject(StartLocation, EndLocation,ObjectTypeQuery);


}

void ACropoutPlayer::SwitchOperationMode(EGameObjectType ObjectType)
{
	switch (ObjectType)
	{
	case EGameObjectType::Shrub:
	case EGameObjectType::Stone:
	case EGameObjectType::TownHall:
	case EGameObjectType::Tree:
	case EGameObjectType::VillagerHouse:
		this->PlayerOperationMode = EPlayerOperationMode::None;
		break;
	case EGameObjectType::Ground:
		this->PlayerOperationMode = EPlayerOperationMode::Movement;
		break;
	case EGameObjectType::None:
		if (this->SelectedNPC == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayer::SwitchOperationMode(): this->SelectedNPC == nullptr"));
			return;
		}
		this->PlayerOperationMode = EPlayerOperationMode::Control;
		break;
	case EGameObjectType::PlaceHolder:
		this->PlayerOperationMode = EPlayerOperationMode::Construction;
		break;
	}
}

void ACropoutPlayer::SetFirstSplinePointLocation(const FVector& Location)
{
    this->SplineComponent->SetLocationAtSplinePoint(0, Location, ESplineCoordinateSpace::World);
}

void ACropoutPlayer::SetLastSplinePointLocation(const FVector& Location)
{
    this->SplineComponent->SetLocationAtSplinePoint(this->SplineComponent->GetNumberOfSplinePoints() - 1, Location, ESplineCoordinateSpace::World);
}


int32 ACropoutPlayer::GetGuidanceLineSegmentTotal(float SplineLength)
{
	const int32 MinCount = 2;
	//const float LengthInterval = 400.0f;
	const float MinCriticalValue = 400.0f;
	const float Interval = 130.0f;
	if (SplineLength < MinCriticalValue)
	{
        return MinCount;
	}
	else if(SplineLength < MinCriticalValue + Interval)
	{
		return MinCount + 1;
	}
	else if (SplineLength < MinCriticalValue + Interval * 2)
	{
		return MinCount + 2;
	}
	else if (SplineLength < MinCriticalValue + Interval * 3)
	{
        return MinCount + 3;
	}
	else if (SplineLength < MinCriticalValue + Interval * 4)
	{
		return MinCount + 3;
	}
	else if (SplineLength < MinCriticalValue + Interval * 5)
	{
		return MinCount + 4;
	}
	else if (SplineLength < MinCriticalValue + Interval * 6)
	{
		return MinCount + 5;
	}
	else if (SplineLength < MinCriticalValue + Interval * 7)
	{
		return MinCount + 6;
	}
	else if (SplineLength < MinCriticalValue + Interval * 8)
	{
		return MinCount + 7;
	}
	else if (SplineLength < MinCriticalValue + Interval * 9)
	{
		return MinCount + 8;
	}
	else if (SplineLength < MinCriticalValue + Interval * 10)
	{
		return MinCount + 9;
	}
	else if (SplineLength < MinCriticalValue + Interval * 11)
	{
		return MinCount + 10;
	}
	else if (SplineLength < MinCriticalValue + Interval * 12)
	{
		return MinCount + 11;
	}
	else if (SplineLength < MinCriticalValue + Interval * 13)
	{
		return MinCount + 12;
	}
	else if (SplineLength < MinCriticalValue + Interval * 14)
	{
		return MinCount + 13;
	}
	else if (SplineLength < MinCriticalValue + Interval * 15)
	{
		return MinCount + 14;
	}
	else if (SplineLength < MinCriticalValue + Interval * 16)
	{
		return MinCount + 15;
	}
	else if (SplineLength < MinCriticalValue + Interval * 17)
	{
		return MinCount + 16;
	}
	else if (SplineLength < MinCriticalValue + Interval * 18)
	{
		return MinCount + 17;
	}
	else if (SplineLength < MinCriticalValue + Interval * 19)
	{
		return MinCount + 18;
	}
	else if (SplineLength < MinCriticalValue + Interval * 20)
	{
		return MinCount + 19;
	}
	else if (SplineLength < MinCriticalValue + Interval * 21)
	{
		return MinCount + 20;
	}
	else if (SplineLength < MinCriticalValue + Interval * 22)
	{
		return MinCount + 21;
	}
	else if (SplineLength < MinCriticalValue + Interval * 23)
	{
		return MinCount + 22;
	}
	else if (SplineLength < MinCriticalValue + Interval * 24)
	{
		return MinCount + 23;
	}
	else if (SplineLength < MinCriticalValue + Interval * 25)
	{
		return MinCount + 24;
	}
	else if (SplineLength < MinCriticalValue + Interval * 26)
	{
		return MinCount + 25;
	}
	else if (SplineLength < MinCriticalValue + Interval * 27)
	{
		return MinCount + 26;
	}
	else if (SplineLength < MinCriticalValue + Interval * 28)
	{
		return MinCount + 27;
	}
	else
	{
		return MinCount + 28;
	}
}

void ACropoutPlayer::InitializeGuidanceLine(int32 LineSegmentTotal)
{
	FTransform Transform = FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, -1000.0f));
	auto Lambda = [this]()
	{
		if(this->SelectedNPC == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayer::InitializeGuidanceLine(): Selected NPC == nullptr"));
			return;
		}
		FVector VFXLocation = FVector(this->SelectedNPC->GetActorLocation().X, this->SelectedNPC->GetActorLocation().Y, 3.0f);
		SetFirstSplinePointLocation(VFXLocation);
		UpdateGuidanceLineState();
	};
	for(int32 i = 0; i < LineSegmentTotal; i++)
	{ 
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(nullptr,Transform, EObjectPoolType::GuidanceLineSegment);
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnInitializeGuidanceLine.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(GuidanceLineTimer, Lambda, 0.01f, true);
	this->GuidanceLineSegmentArray = this->CropoutGameMode->GetGuidanceLineSegmentArray();


}


void ACropoutPlayer::UpdateGuidanceLineState()
{ 
	if (this->GuidanceLineSegmentArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("GuidanceLineSegmentArray.Num() == 0"));
		return;
	}
	for (auto& Element : this->GuidanceLineSegmentArray)
	{
		Element->SetActorHiddenInGame(true);
	}
	float Distance = 0.0f;
	FVector LineSegmentLocation;
	FRotator LineSegmentRotation;
	FVector LastPointLocation = this->SplineComponent->GetLocationAtSplinePoint(this->SplineComponent->GetNumberOfSplinePoints() - 1,ESplineCoordinateSpace::World);
	int32 LineSegmentTotal = GetGuidanceLineSegmentTotal(this->SplineComponent->GetSplineLength());
	for (int32 i = 0; i < LineSegmentTotal; i++)
	{
		if (i == 0 || i == LineSegmentTotal - 1)
		{
			continue;
		}
		Distance = this->SplineComponent->GetSplineLength() * i / LineSegmentTotal;
		LineSegmentLocation = this->SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		LineSegmentRotation = FRotator(0.0f,UKismetMathLibrary::FindLookAtRotation(LineSegmentLocation, LastPointLocation).Yaw,0.0f);
		this->GuidanceLineSegmentArray[i]->SetActorHiddenInGame(false);
		this->GuidanceLineSegmentArray[i]->SetActorLocation(LineSegmentLocation);
		this->GuidanceLineSegmentArray[i]->SetActorRotation(LineSegmentRotation);
	}


}



void ACropoutPlayer::RemoveGuidanceLine()
{
	GetWorld()->GetTimerManager().ClearTimer(GuidanceLineTimer);
	if (this->GuidanceLineSegmentArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayer::RemoveGuidanceLine(): this->GuidanceLineSegmentArray.Num() == 0"));
        return;
	}
	for(auto& Element : this->GuidanceLineSegmentArray)
	{
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(Element,EObjectPoolType::GuidanceLineSegment);

	}
	this->GuidanceLineSegmentArray.Reset();



}



void ACropoutPlayer::LoadDataByManager()
{
	FTransform CurrentTransform = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayerData().Transform;
	this->ResourceMap = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayerData().ResourceMap;
	this->MaxResourceMap = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayerData().MaxResourceMap;
	SetActorTransform(CurrentTransform);

}

void ACropoutPlayer::SaveDataToManager()
{
	FPlayerData NewData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayerData();
	NewData.MaxResourceMap = this->MaxResourceMap;
    NewData.ResourceMap = this->ResourceMap;
    NewData.Transform = GetActorTransform();
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdatePlayerData(NewData);



}



void ACropoutPlayer::OnMouseLeftKeyPress(const FInputActionValue& Value)
{
	EGameStatus GameStatus = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameStatus();
	if(GameStatus != EGameStatus::GameStart)
	{ 
		if(this->PlayerOperationMode != EPlayerOperationMode::None)
		{
			this->PlayerOperationMode = EPlayerOperationMode::None;
		}
		return;
	}

	FHitResult HitResult;
	EGameObjectType GameObjectType = EGameObjectType::None;
	MouseLineTrace(this->DetectionInformation_MouseLeftKeyPress.ObjectTypeQueryArray);
	if(CollisionDetectionComponent->GetHitResultArray().Num() == 0)
	{ 
        return;
	}
	HitResult = CollisionDetectionComponent->GetHitResultArray()[0];
	this->MouseLocation = HitResult.Location;
	this->CropoutGameMode->SetMouseLocation(this->MouseLocation);
	IGameObjectTypeInterface* GameObjectTypeInterface = Cast<IGameObjectTypeInterface>(HitResult.GetActor());
	if(GameObjectTypeInterface!=nullptr)
	{
		GameObjectType = GameObjectTypeInterface->GetGameObjectType();
	}
	if (GameObjectType == EGameObjectType::None)
	{
		this->SelectedNPC = HitResult.GetActor();
		FVector VFXLocation = FVector(this->SelectedNPC->GetActorLocation().X, this->SelectedNPC->GetActorLocation().Y, 3.0f);
		InitializeGuidanceLine(this->MaxGuidanceLineSegmentNumber);
		SetFirstSplinePointLocation(VFXLocation);
		SetLastSplinePointLocation(VFXLocation);
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(nullptr,FTransform(FRotator(),VFXLocation),EObjectPoolType::CircleRing);
	}
	SwitchOperationMode(GameObjectType);

}


void ACropoutPlayer::OnMouseMove(const FInputActionValue& Value)
{ 
	if (PlayerOperationMode == EPlayerOperationMode::None)
	{
		return;
	}
	if (PlayerOperationMode == EPlayerOperationMode::Movement)
	{
		UpdateScreenLocation(Value);
		return;
	};
	FHitResult HitResult;
	MouseLineTrace(this->DetectionInformation_MouseMovement.ObjectTypeQueryArray);
	if (CollisionDetectionComponent->GetHitResultArray().Num() == 0)
	{
		return;
	}
	HitResult = CollisionDetectionComponent->GetHitResultArray()[0];
	this->MouseLocation = HitResult.Location;
	this->CropoutGameMode->SetMouseLocation(this->MouseLocation);
	
	if(PlayerOperationMode == EPlayerOperationMode::Control)
	{
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnMouseMove.Broadcast(this->MouseLocation);
		FVector VFXLocation = FVector(HitResult.Location.X, HitResult.Location.Y, 3.0f);
		SetLastSplinePointLocation(VFXLocation);
		UpdateGuidanceLineState();
		return;

	};
	if (PlayerOperationMode == EPlayerOperationMode::Construction)
	{
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnMouseMove.Broadcast(this->MouseLocation);
	}


	
}


void ACropoutPlayer::OnMouseLeftKeyRelease(const FInputActionValue& Value)
{
	if (PlayerOperationMode != EPlayerOperationMode::Control)
	{
		return;
	};
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnMouseLeftKeyRelease.Broadcast();
	FHitResult HitResult;
	IGameObjectInteractionInterface* InteractionInterface = Cast<IGameObjectInteractionInterface>(this->SelectedNPC);
	INPCStateInterface* NPCStateInterface = Cast<INPCStateInterface>(this->SelectedNPC);
	IGameObjectTypeInterface* GameObjectTypeInterface_NPC = Cast<IGameObjectTypeInterface>(this->SelectedNPC);
	IGameObjectTypeInterface* GameObjectTypeInterface = nullptr;
	ENPCState NewNPCState = ENPCState::None;
	AActor* SelectedGameObject = nullptr;
	if (InteractionInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayer::OnMouseLeftKeyRelease(): InteractionInterface == nullptr"));
		return;
	};
	MouseLineTrace(this->DetectionInformation_MouseLeftKeyRelease.ObjectTypeQueryArray);
	RemoveGuidanceLine();
	if (this->CollisionDetectionComponent->GetHitResultArray().Num() == 0)
	{
		return;
	}
    HitResult = this->CollisionDetectionComponent->GetHitResultArray()[0];
	SelectedGameObject = HitResult.GetActor();
	GameObjectTypeInterface = Cast<IGameObjectTypeInterface>(SelectedGameObject);
	if(GameObjectTypeInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayer::OnMouseLeftKeyRelease(): GameObjectTypeInterface == nullptr"));
		return;
	}
	if (GameObjectTypeInterface_NPC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayer::OnMouseLeftKeyRelease(): GameObjectTypeInterface_NPC == nullptr"));
		return;
	}
    InteractionInterface->SetGameObjectLocation(SelectedGameObject->GetActorLocation());
	GameObjectTypeInterface_NPC->SetGameObjectType(GameObjectTypeInterface->GetGameObjectType());
	switch (GameObjectTypeInterface->GetGameObjectType())
	{
	case EGameObjectType::CornField:
	case EGameObjectType::WheatField:
	case EGameObjectType::PumpkinField:
	case EGameObjectType::LettuceField:
		NewNPCState = ENPCState::Farming;
		break;
	case EGameObjectType::Shrub:
		NewNPCState = ENPCState::Gathering;
		break;
	case EGameObjectType::Stone:
		NewNPCState = ENPCState::Mining;
		break;
	case EGameObjectType::Tree:
		NewNPCState = ENPCState::Woodcutting;
		break;
	case EGameObjectType::VillagerHouse:
	case EGameObjectType::Monument:
		NewNPCState = ENPCState::Construction;
		break;
	}
	if (NewNPCState == ENPCState::None)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayer::OnMouseLeftKeyRelease(): NewNPCState == ENPCState::None"));
		return;
	}
	NPCStateInterface->UpdateNPCState(NewNPCState);
	this->PlayerOperationMode = EPlayerOperationMode::Movement;
	this->SelectedNPC = nullptr;


}


void ACropoutPlayer::OnMouseWheel(const FInputActionValue& Value)
{
	EGameStatus GameStatus = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameStatus();
	if (GameStatus != EGameStatus::GameStart)
	{
		return;
	}
	UpdateScreenScale(Value);

}


void ACropoutPlayer::OnGameWin()
{
	

}

void ACropoutPlayer::OnGameSave()
{
	SaveDataToManager();



}


void ACropoutPlayer::OnGameRestart()
{



}

void ACropoutPlayer::OnGameStart()
{
	LoadDataByManager();
	


}

void ACropoutPlayer::OnGameStartInitialization()
{
	FGameSettingsData GameSettingsData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData();
	FPlayerData PlayerData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayerData();
	this->CameraComponent->SetOrthoWidth(GameSettingsData.Operation.ScreenScale);
	SetActorTransform(PlayerData.Transform);

}

void ACropoutPlayer::OnGamePause()
{
	


}


void ACropoutPlayer::OnGameResume(EGameStatus CurrentStatus)
{
	if(CurrentStatus == EGameStatus::None)
	{
		LoadDataByManager();
	}

	

}


void ACropoutPlayer::OnPlayerSelectCard(const FCardInformation& SelectedCard)
{
	FTransform Transform;
	FHitResult HitResult;
	MouseLineTrace(this->DetectionInformation_MouseMovement.ObjectTypeQueryArray);
	if(this->CollisionDetectionComponent->GetHitResultArray().Num() == 0)
	{ 
		return;
	}
	HitResult = this->CollisionDetectionComponent->GetHitResultArray()[0];
	Transform.SetLocation(HitResult.ImpactPoint);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(nullptr,Transform,EObjectPoolType::PlaceHolder);



}



void ACropoutPlayer::OnPlayerPlaceGameObject(const FCardInformation& SelectedCard)
{



}

void ACropoutPlayer::OnPlayerResourceIncrease(TMap<EResourceType, int32> OtherResource)
{
	int32* NewValue = nullptr;
	for(auto& Element : this->ResourceMap)
	{
		NewValue = OtherResource.Find(Element.Key);
		if(NewValue)
		{
			Element.Value += *NewValue;
		}
	}
	FPlayerData NewData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayerData();
    NewData.MaxResourceMap = this->MaxResourceMap;
	NewData.ResourceMap = this->ResourceMap;
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdatePlayerData(NewData);

}


void ACropoutPlayer::OnPlayerResourceReduce(TMap<EResourceType, int32> OtherResource)
{
	int32* NewValue = nullptr;
	for (auto& Element : this->ResourceMap)
	{
		NewValue = OtherResource.Find(Element.Key);
		if (NewValue)
		{
			Element.Value -= *NewValue;
		}
	}
	EGameStatus GameStatus = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameStatus();
	FPlayerData NewData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayerData();
	NewData.MaxResourceMap = this->MaxResourceMap;
	NewData.ResourceMap = this->ResourceMap;
	if(*NewData.ResourceMap.Find(EResourceType::Food) < 0 && GameStatus != EGameStatus::GameOver)
	{
		*NewData.ResourceMap.Find(EResourceType::Food) = 0;
		this->CropoutGameMode->GetGameInstance()->GetDataManager()->DeleteSaveGame(FString("GameProgressSaveGame"),0);
		this->CropoutGameMode->GetGameInstance()->GetDataManager()->SetGameStatus(EGameStatus::GameOver);
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameOver.Broadcast();
	}
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdatePlayerData(NewData);



}










