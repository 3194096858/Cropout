#include "NPC/NPC.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/CollisionDetectionComponent.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Component/DamageComponent.h"
#include "Component/HealthComponent.h"
#include "Component/HealComponent.h"

#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Manager/WidgetManager.h"
#include "Manager/DataManager.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AI/AIController/NPCAIController.h"
#include "NavigationSystem.h"

#include "Blueprint/WidgetLayoutLibrary.h"


ANPC::ANPC()
{
	this->PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	this->CollisionDetectionComponent = CreateDefaultSubobject<UCollisionDetectionComponent>(TEXT("CollisionDetectionComponent"));
	this->DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComponent"));
    this->HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	this->HealComponent = CreateDefaultSubobject<UHealComponent>(TEXT("HealComponent"));
	this->CrateMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrateMeshComponent"));
	this->HatMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HatMeshComponent"));
	this->HairMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HairMeshComponent"));
	this->WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComponent"));
	this->HatMeshComponent->SetupAttachment(GetMesh());
	this->WeaponMeshComponent->SetupAttachment(GetMesh());
	this->HairMeshComponent->SetupAttachment(GetMesh());
	this->CrateMeshComponent->SetupAttachment(GetMesh());

	this->bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = this->MaxMovementSpeed;
	this->DamageComponent->SetDamage(10.0f);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));

	this->HatMeshComponent->SetVisibility(false);
	this->HairMeshComponent->SetVisibility(false);
	this->WeaponMeshComponent->SetVisibility(false);
	this->CrateMeshComponent->SetVisibility(false);
	this->HatMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->HairMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->CrateMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->GetMesh()->bReceivesDecals = false;
	this->HatMeshComponent->bReceivesDecals = false;
	this->HairMeshComponent->bReceivesDecals = false;
	this->WeaponMeshComponent->bReceivesDecals = false;
	this->CrateMeshComponent->bReceivesDecals = false;
	this->CollisionDetectionComponent->IsUseDefaultObjectTypeQuery = false;

}


void ANPC::BeginPlay()
{
	Super::BeginPlay();
	CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ANPC::BeginPlay(): CropoutGameMode == nullptr"));
		return;
	}
	GetMesh()->GetAnimInstance()->OnMontageStarted.AddDynamic(this, &ANPC::OnMontageStarted);
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &ANPC::OnMontageEnded);
	this->HairMeshComponent->SetVisibility(true);
	this->HatMeshComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("HeadSocket"));
	this->WeaponMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHandSocket"));
	this->HairMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HairSocket"));
	this->CrateMeshComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHandSocket"));
	auto Lambda = [this]()
		{
			if (CropoutGameMode->GetGameInstance() == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("ANPC::BeginPlay(): CropoutGameMode->GetGameInstance() == nullptr"));
				return;
			}
			if (CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("ANPC::BeginPlay(): CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr"));
				return;
			}
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameWin.AddUObject(this, &ANPC::OnGameWin);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameOver.AddUObject(this, &ANPC::OnGameOver);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameRestart.AddUObject(this, &ANPC::OnGameRestart);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerResourceIncrease.AddUObject(this, &ANPC::OnVillagerResourceIncrease);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerReturnStartMenu.AddUObject(this, &ANPC::OnPlayerReturnStartMenu);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGamePause.AddUObject(this, &ANPC::OnGamePause);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameResume.AddUObject(this, &ANPC::OnGameResume);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameSave.AddUObject(this, &ANPC::OnGameSave);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStart.AddUObject(this, &ANPC::OnGameStart);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectBeginPlay.AddUObject(this, &ANPC::OnObjectBeginPlay);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEndPlay.AddUObject(this, &ANPC::OnObjectEndPlay);
			CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnCropMature.AddUObject(this, &ANPC::OnCropMature);
			CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.AddUObject(this, &ANPC::OnVillagerCompleteJob);
		};
	GetWorld()->GetTimerManager().SetTimer(this->InitializationTimer, Lambda, 1.0f, false);
	GetWorld()->GetTimerManager().SetTimer(this->TickTimer, this, &ANPC::TickFunction, 10.0f, true,10.0f);
	GetWorld()->GetTimerManager().PauseTimer(this->TickTimer);
	

}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector2D Position;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PlayerController, this->DamageTextLocation, Position, false);
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->UpdateDamageTextPosition(FName(this->GetName()), Position);

}



void ANPC::TickFunction()
{
	FName ActorName = FName(GetName());
	TMap<EResourceType, int32> TargetResourceMap;
	int32 FoodConsumption = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerData(ActorName).FoodConsumption;
	TargetResourceMap.Add(EResourceType::Food,FoodConsumption);
	TargetResourceMap.Add(EResourceType::Wood, 0);
	TargetResourceMap.Add(EResourceType::Stone, 0);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerResourceReduce.Broadcast(TargetResourceMap);

}

void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float ANPC::GetMovementSpeed()
{
	float MovementSpeed = FMath::Abs(GetCharacterMovement()->Velocity.X) + FMath::Abs(GetCharacterMovement()->Velocity.Y);
	return MovementSpeed;
}

FVillagerJobInformation ANPC::GetJobInformationFromTable(const FName& JobName)
{
	FVillagerJobInformation JobInformation = FVillagerJobInformation();
	if (this->JobInformationTable==nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANPC::GetJobInformationFromTable(): JobInformationTable == nullptr"));
		return JobInformation;
	}
	if (this->JobInformationTable->FindRow<FVillagerJobInformation>(JobName, "") == nullptr)
	{
        UE_LOG(LogTemp, Warning, TEXT("ANPC::GetJobInformationFromTable(): this->JobInformationTable->FindRow<FVillagerJobInformation>(JobName, )== nullptr"));
		return JobInformation;
	}
	JobInformation = *this->JobInformationTable->FindRow<FVillagerJobInformation>(JobName, "");

	return JobInformation;
}


void ANPC::Attack()
{
	const float Radius = 20.0f;
	const float Distance = 300.0f;
	FVillagerJobInformation JobInformation = FVillagerJobInformation();
	FName JobName;
	FHitResult HitResult;
	FVector OffsetValue = FVector(0.0f,0.0f,FMath::RandRange(-200.0f,-50.0f));
	switch (this->NPCState)
	{
	case ENPCState::Farming:
		//JobName = FName("Farming");
		JobName = FName("Gathering");
		break;
	case ENPCState::Gathering:
		JobName = FName("Gathering");
		break;
	case ENPCState::Mining:
		JobName = FName("Mining");
		break;
	case ENPCState::Woodcutting:
		JobName = FName("Woodcutting");
		break;
	}
	this->DamageComponent->ApplyDamage(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * Distance,this->CollisionDetectionComponent,Radius);
	if (this->CollisionDetectionComponent->GetHitResultNumber() == 0)
	{
		if (this->IsCompleteJob == true)
		{
			RemoveHat();
		}
		return;
	}
	HitResult = this->CollisionDetectionComponent->GetFirstHitResult();
	this->DamageTextLocation = HitResult.ImpactPoint + OffsetValue;
	JobInformation = GetJobInformationFromTable(JobName);
	PlayAnimMontage(JobInformation.Montage);
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->DisplayDamageText(FName(this->GetName()), this->DamageComponent->GetDamage());
	


}


void ANPC::Heal()
{
	const float Radius = 20.0f;
	const float Distance = 300.0f;
	FVillagerJobInformation JobInformation = FVillagerJobInformation();
	FName JobName;
	switch (this->NPCState)
	{
	case ENPCState::Farming:
		JobName = FName("Farming");
		break;
	case ENPCState::Construction:
		JobName = FName("Construction");
		break;
	}
	this->HealComponent->ApplyHeal(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * Distance,this->CollisionDetectionComponent,Radius);
	JobInformation = GetJobInformationFromTable(JobName);
	PlayAnimMontage(JobInformation.Montage);


}


void ANPC::AddSelfResource(EGameObjectType ObjectType)
{


}

void ANPC::RemoveSelfAllResource()
{
	FName ActorName = FName(GetName());
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckVillagerDataIsExist(ActorName) == false)
	{
		return;
	}
	FVillagerData TargetData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerData(ActorName);

	int32* Value = nullptr;
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerResourceIncrease.Broadcast(TargetData.ResourceMap);	
	for (int32 i = 0; i < TargetData.ResourceMap.Num(); i++)
	{
		switch (i)
		{
		case 0:
			Value = TargetData.ResourceMap.Find(EResourceType::Food);
			//UE_LOG(LogTemp, Warning, TEXT(" Remove Resource: Food = %d !!!!!!! "), *Value);
			break;
		case 1:
			Value = TargetData.ResourceMap.Find(EResourceType::Stone);
			//UE_LOG(LogTemp, Warning, TEXT(" Remove Resource: Stone = %d !!!!!!! "), *Value);
			break;
		case 2:
			Value = TargetData.ResourceMap.Find(EResourceType::Wood);
			//UE_LOG(LogTemp, Warning, TEXT(" Remove Resource: Wood = %d !!!!!!! "), *Value);
			break;
		}
		if (Value == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ANPC::RemoveSelfAllResource(): Value == nullptr"));
			return;
		}
		if (*Value != 0)
		{
			*Value = 0;
		}
	}
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdateVillagerData(ActorName,TargetData);
	if (this->NPCStateBeforeTransport == ENPCState::Farming )
	{
		ANPCAIController* NPCAIController = Cast<ANPCAIController>(this->GetController());
		if (NPCAIController == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ANPC::OnCropMature(): NPCAIController == nullptr"));
			return;
		}
		this->IsCropMature = false;
		NPCAIController->SetIsCropMature(this->IsCropMature);
	}

}

UAnimMontage* ANPC::GetMontageFromTable(EGameObjectType ObjectType)
{
	FVillagerJobInformation JobInformation;
	switch (ObjectType)
	{
	case EGameObjectType::VillagerHouse:
	case EGameObjectType::Monument:
		JobInformation = GetJobInformationFromTable(FName("Construction"));
		break;
	case EGameObjectType::CornField:
	case EGameObjectType::WheatField:
	case EGameObjectType::PumpkinField:
	case EGameObjectType::LettuceField:
		JobInformation = GetJobInformationFromTable(FName("Farming"));
		break;
	case EGameObjectType::Tree:
		JobInformation = GetJobInformationFromTable(FName("Woodcutting"));
		break;
	case EGameObjectType::Shrub:
		JobInformation = GetJobInformationFromTable(FName("Gathering"));
		break;
	case EGameObjectType::Stone:
		JobInformation = GetJobInformationFromTable(FName("Mining"));
		break;
	case EGameObjectType::None:
		break;
	}
	
	return JobInformation.Montage;
}


void ANPC::AddCrate()
{
	this->CrateMeshComponent->SetVisibility(true);


}

void ANPC::RemoveCrate()
{
	this->CrateMeshComponent->SetVisibility(false);



}

void ANPC::AddHat()
{ 
	FVillagerJobInformation JobInformation;
	switch (this->GameObjectType)
	{
	case EGameObjectType::VillagerHouse:
	case EGameObjectType::Monument:
		JobInformation = GetJobInformationFromTable(FName("Construction"));
		break;
	case EGameObjectType::CornField:
	case EGameObjectType::WheatField:
	case EGameObjectType::PumpkinField:
	case EGameObjectType::LettuceField:
		JobInformation = GetJobInformationFromTable(FName("Farming"));
		break;
	case EGameObjectType::Tree:
		JobInformation = GetJobInformationFromTable(FName("Woodcutting"));
		break;
	case EGameObjectType::Shrub:
		JobInformation = GetJobInformationFromTable(FName("Gathering"));
		break;
	case EGameObjectType::Stone:
		JobInformation = GetJobInformationFromTable(FName("Mining"));
		break;
	case EGameObjectType::None:
		break;
	}
	if(JobInformation.HatMesh == nullptr)
	{
		return;
	}
	this->HatMeshComponent->SetStaticMesh(JobInformation.HatMesh);
	this->HatMeshComponent->SetVisibility(true);


}

void ANPC::RemoveHat()
{ 
	this->HatMeshComponent->SetVisibility(false);



}


void ANPC::AddWeapon()
{ 
	FVillagerJobInformation JobInformation;
	switch (this->GameObjectType)
	{
	case EGameObjectType::VillagerHouse:
	case EGameObjectType::Monument:
		JobInformation = GetJobInformationFromTable(FName("Construction"));
		break;
	case EGameObjectType::CornField:
	case EGameObjectType::WheatField:
	case EGameObjectType::PumpkinField:
	case EGameObjectType::LettuceField:
		JobInformation = GetJobInformationFromTable(FName("Farming"));
		break;
	case EGameObjectType::Tree:
		JobInformation = GetJobInformationFromTable(FName("Woodcutting"));
		break;
	case EGameObjectType::Shrub:
		JobInformation = GetJobInformationFromTable(FName("Gathering"));
		break;
	case EGameObjectType::Stone:
		JobInformation = GetJobInformationFromTable(FName("Mining"));
		break;
	case EGameObjectType::None:
		break;
	}
	if(JobInformation.WeaponMesh == nullptr)
	{
		return;
	}
	this->WeaponMeshComponent->SetStaticMesh(JobInformation.WeaponMesh);
	this->WeaponMeshComponent->SetVisibility(true);


}


void ANPC::RemoveWeapon()
{ 
	this->WeaponMeshComponent->SetVisibility(false);


}


ENPCState ANPC::GetNPCState()
{
	return this->NPCState;
}

void ANPC::UpdateNPCState(ENPCState NewState)
{
	if (NewState == ENPCState::Transport && this->NPCState != ENPCState::Transport)
	{
		this->NPCStateBeforeTransport = this->NPCState;
	}
	if (NewState != ENPCState::Patrol && NewState != ENPCState::Transport)
	{
		this->IsCompleteJob = false;
	}
	this->NPCState = NewState;
	CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnNPCStateChange.Broadcast(this, NewState);
}

FVector ANPC::GetGameObjectLocation()
{
	return this->GameObjectLocation;
}


void ANPC::SetGameObjectLocation(const FVector& ObjectLocation)
{
	this->GameObjectLocation = ObjectLocation;
}

EGameObjectType ANPC::GetGameObjectType()
{
	return this->GameObjectType;
}

void ANPC::SetGameObjectType(EGameObjectType NewType)
{
	this->GameObjectType = NewType;

}



void ANPC::LoadDataByManager()
{
	FName ActorName = FName(GetName());
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckVillagerDataIsExist(ActorName) == false)
	{
		return;
	}
	ANPCAIController* AIController = Cast<ANPCAIController>(GetController());
	FVillagerData TargetData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerData(ActorName);
	this->ResourceMap = TargetData.ResourceMap;
	this->MaxResourceMap = TargetData.MaxResourceMap;
	this->GameObjectType = TargetData.GameObjectType;
	this->GameObjectLocation = TargetData.GameObjectLocation;
	this->IsCropMature = TargetData.BehaviorTreeData.IsCropMature;
	this->IsCompleteJob = TargetData.BehaviorTreeData.IsCompleteJob;
	this->NPCState = TargetData.BehaviorTreeData.NPCState;
	this->NPCStateBeforeTransport = TargetData.BehaviorTreeData.NPCStateBeforeTransport;
	AIController->GetBlackboardComponent()->SetValueAsFloat(FName("DistanceBetweetSelfAndObject"), TargetData.BehaviorTreeData.DistanceBetweenSelfAndObject);
	AIController->GetBlackboardComponent()->SetValueAsVector(FName("RandomLocation"), TargetData.BehaviorTreeData.RandomLocation);
	AIController->GetBlackboardComponent()->SetValueAsVector(FName("GameObjectLocation"), TargetData.BehaviorTreeData.GameObjectLocation);
	AIController->GetBlackboardComponent()->SetValueAsVector(FName("TownHallLocation"), TargetData.BehaviorTreeData.TownHallLocation);
	AIController->SetIsCropMature( TargetData.BehaviorTreeData.IsCropMature);
	AIController->SetIsCompleteJob(TargetData.BehaviorTreeData.IsCompleteJob);
	UpdateNPCState(TargetData.BehaviorTreeData.NPCState);
	AIController->SetNPCStateBeforeTransport(TargetData.BehaviorTreeData.NPCStateBeforeTransport);
	AIController->SetNPCState(TargetData.BehaviorTreeData.NPCState);

	if (TargetData.AnimationData.IsActive == true)
	{
		PlayAnimMontage(GetMontageFromTable(this->GameObjectType));
		GetMesh()->GetAnimInstance()->Montage_SetPosition(GetMontageFromTable(this->GameObjectType), TargetData.AnimationData.Position);
		GetMesh()->GetAnimInstance()->Montage_SetPlayRate(GetMontageFromTable(this->GameObjectType), TargetData.AnimationData.PlayRate);

	}
	if (TargetData.IsHatVisible == true)
	{
		AddHat();
	}
	if (TargetData.IsWeaponVisible == true)
	{
		AddWeapon();
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(this,TargetData.Transform, EObjectPoolType::Villager);

}

void ANPC::SaveDataToManager()
{
	FName ActorName = FName(GetName());
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckVillagerDataIsExist(ActorName) == false)
	{
		return;
	}
	ANPCAIController* AIController = Cast<ANPCAIController>(GetController());
	UEnum* Enum = StaticEnum<ENPCState>();
	int32 EnumIndex;
	FVillagerData NewData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerData(ActorName);
	//NewData.MaxResourceMap = this->MaxResourceMap;
	//NewData.ResourceMap = this->ResourceMap;
	NewData.Transform = GetActorTransform();
	NewData.GameObjectType = this->GameObjectType;
	NewData.GameObjectLocation = this->GameObjectLocation;
	NewData.IsHatVisible = this->HatMeshComponent->IsVisible();
    NewData.IsWeaponVisible = this->WeaponMeshComponent->IsVisible();
	NewData.BehaviorTreeData.NPCStateBeforeTransport = this->NPCStateBeforeTransport;
	NewData.BehaviorTreeData.NPCState = this->NPCState;
	NewData.BehaviorTreeData.DistanceBetweenSelfAndObject = AIController->GetBlackboardComponent()->GetValueAsFloat(FName("DistanceBetweenSelfAndObject"));
	NewData.BehaviorTreeData.IsCropMature = AIController->GetBlackboardComponent()->GetValueAsBool(FName("IsCropMature"));
	NewData.BehaviorTreeData.IsCompleteJob = AIController->GetBlackboardComponent()->GetValueAsBool(FName("IsCompleteJob2"));
	NewData.BehaviorTreeData.RandomLocation = AIController->GetBlackboardComponent()->GetValueAsVector(FName("RandomLocation"));
	NewData.BehaviorTreeData.GameObjectLocation = AIController->GetBlackboardComponent()->GetValueAsVector(FName("GameobjectLocation"));
	NewData.BehaviorTreeData.TownHallLocation = AIController->GetBlackboardComponent()->GetValueAsVector(FName("TownHallLocation"));
	EnumIndex = Enum->GetIndexByName(AIController->GetBlackboardComponent()->GetValueAsName(FName("NPCState")));
	NewData.BehaviorTreeData.NPCState = static_cast<ENPCState>(Enum->GetValueByIndex(EnumIndex));
	if(NewData.BehaviorTreeData.NPCState == ENPCState::None)
	{
		UE_LOG(LogTemp, Warning, TEXT("NewData.BehaviorTreeData.NPCState == ENPCState::None"));
	}
	EnumIndex = Enum->GetIndexByName(AIController->GetBlackboardComponent()->GetValueAsName(FName("NPCStateBeforeTransport")));
	NewData.BehaviorTreeData.NPCStateBeforeTransport = static_cast<ENPCState>(Enum->GetValueByIndex(EnumIndex));
	NewData.AnimationData.IsActive = GetMesh()->GetAnimInstance()->Montage_IsActive(GetCurrentMontage());
	if (NewData.AnimationData.IsActive == true)
	{
		NewData.AnimationData.PlayRate = GetMesh()->GetAnimInstance()->Montage_GetPlayRate(GetCurrentMontage());
		NewData.AnimationData.Position = GetMesh()->GetAnimInstance()->Montage_GetPosition(GetCurrentMontage());
		NewData.AnimationData.StectionName = GetMesh()->GetAnimInstance()->Montage_GetCurrentSection(GetCurrentMontage());

	}
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdateVillagerData(ActorName,NewData);

}




void ANPC::OnObjectBeginPlay(AActor* Object)
{
	if (Object != this)
	{
		return;
	}
	GetWorld()->GetTimerManager().UnPauseTimer(this->TickTimer);
	
}


void ANPC::OnObjectEndPlay(AActor* Object)
{
	if (Object != this)
	{
		return;
	}
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(GetCurrentMontage()) == true)
	{
		StopAnimMontage();
	}
	GetWorld()->GetTimerManager().PauseTimer(this->TickTimer);
	
	
}



void ANPC::OnCropMature(const FVector& ObjectLocation)
{
	if (this->GameObjectLocation != ObjectLocation)
	{
		return;
	}
	ANPCAIController* NPCAIController = Cast<ANPCAIController>(this->GetController());
	this->IsCropMature = true;
	if (NPCAIController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANPC::OnCropMature(): NPCAIController == nullptr"));
		return;
	}
	NPCAIController->SetIsCropMature(this->IsCropMature);

}



void ANPC::OnMontageStarted(UAnimMontage* Montage)
{
	


}

void ANPC::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{ 
	FName ActorName = FName(GetName());
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckVillagerDataIsExist(ActorName) == false)
	{
		return;
	}
	FVillagerData TargetData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerData(ActorName);

	if (*TargetData.ResourceMap.Find(EResourceType::Wood) >= *TargetData.MaxResourceMap.Find(EResourceType::Wood) || *TargetData.ResourceMap.Find(EResourceType::Stone) >= *TargetData.MaxResourceMap.Find(EResourceType::Stone) || *TargetData.ResourceMap.Find(EResourceType::Food) >= *TargetData.MaxResourceMap.Find(EResourceType::Food))
	{
		UpdateNPCState(ENPCState::Transport);
		return;
	}
	if (this->GameObjectLocation == FVector::ZeroVector && (*TargetData.ResourceMap.Find(EResourceType::Food) > 0 || *TargetData.ResourceMap.Find(EResourceType::Wood) > 0 || *TargetData.ResourceMap.Find(EResourceType::Stone) > 0))
	{
		UpdateNPCState(ENPCState::Transport);
		return;
	}
	
	
}

void ANPC::OnVillagerCompleteJob(const FVector& ObjectLocation)
{
	if (this->GameObjectLocation != ObjectLocation)
	{
		return;
	}
	ANPCAIController* NPCAIController = Cast<ANPCAIController>(this->GetController());
	this->IsCompleteJob = true;
	this->IsCropMature = false;
	this->GameObjectLocation = FVector::ZeroVector;
	this->GameObjectType = EGameObjectType::None;
	if(NPCAIController==nullptr)
	{
        UE_LOG(LogTemp, Warning, TEXT("ANPC::OnVillagerCompleteJob(): NPCAIController == nullptr"));
		return;
	}
	NPCAIController->SetIsCompleteJob(this->IsCompleteJob);


}




void ANPC::OnGameSave()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::Villager) == false)
	{
		return;
	}
	SaveDataToManager();



}


void ANPC::OnGameOver()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::Villager) == false)
	{
		return;
	}
	GetWorld()->GetTimerManager().PauseTimer(this->TickTimer);




}

void ANPC::OnGameRestart()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::Villager) == false)
	{
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::Villager);



}

void ANPC::OnGameWin()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::Villager) == false)
	{
		return;
	}
	GetWorld()->GetTimerManager().PauseTimer(this->TickTimer);



}

void ANPC::OnGameStart()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::Villager) == false)
	{
		return;
	}
	//GetWorld()->GetTimerManager().UnPauseTimer(this->TickTimer);
	LoadDataByManager();



}

void ANPC::OnGamePause()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::Villager) == false)
	{
		return;
	}
	if(GetMesh()->GetAnimInstance()->Montage_IsPlaying(GetCurrentMontage()) == true) 
	{
		GetMesh()->GetAnimInstance()->Montage_Pause();

	}
	GetWorld()->GetTimerManager().PauseTimer(this->TickTimer);

}


void ANPC::OnGameResume(EGameStatus CurrentStatus)
{
	if (CurrentStatus == EGameStatus::None)
	{
		LoadDataByManager();

		return;
	}
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::Villager) == true)
	{
		GetWorld()->GetTimerManager().UnPauseTimer(this->TickTimer);
	}

}




void ANPC::OnPlayerReturnStartMenu()
{


}



void ANPC::OnVillagerResourceIncrease(AActor* Villager,TMap<EResourceType,int32> OtherResource)
{
	if(Villager != this)
	{
		return;
	}
	FName ActorName = FName(GetName());
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckVillagerDataIsExist(ActorName) == false)
	{
		return;
	}
	FVillagerData TargetData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerData(ActorName);

	for(auto& Element : OtherResource)
	{
		if (TargetData.ResourceMap.Find(Element.Key) ==nullptr)
		{
			continue;
		}
		*TargetData.ResourceMap.Find(Element.Key) += Element.Value;
	}
	
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdateVillagerData(ActorName,TargetData);


}
