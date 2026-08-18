#include "VFX/CircleRing.h"
#include "Components/TimelineComponent.h"
#include "Component/CollisionDetectionComponent.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"


ACircleRing::ACircleRing()
{
	PrimaryActorTick.TickInterval = 0.1f;
	this->TimelineComponent_Floating = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent_Floating"));
	this->TimelineComponent_Absorption = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent_Absorption"));
	this->TimelineComponent_BeginPlay = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent_BeginPlay"));
	this->TimelineComponent_Separation = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent_Separation"));
	GetMeshComponent()->SetRelativeScale3D(FVector(3.0f));


}

void ACircleRing::BeginPlay()
{
	Super::BeginPlay();
	InitializeAnimation();
	InitializeMinFloatingSizeMap();
	this->OriginalMeshScale = GetMeshComponent()->GetRelativeScale3D();
	
}

void ACircleRing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SearchAborptionTarget();

}


void ACircleRing::SearchAborptionTarget()
{
	const float Radius = 300.0f;
	FHitResult HitResult;
	IGameObjectTypeInterface* Interface = nullptr;
	this->CollisionDetectionComponent->SphereTraceForObject(this->CropoutGameMode->GetMouseLocation(), this->CropoutGameMode->GetMouseLocation(),Radius,this->CollisionDetectionComponent->DefaultObjectTypeQueryArray);
	if (this->CollisionDetectionComponent->GetHitResultArray().Num() == 0)
	{
		if (this->IsAbsorb == true)
		{
			DetachFromTarget();
		}
		this->IsAbsorb = false;
		return;
	}
	HitResult = this->CollisionDetectionComponent->GetHitResultArray()[0];
	Interface = Cast<IGameObjectTypeInterface>(HitResult.GetActor());
    if(Interface == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("ACircleRing::SearchAborptionTarget(): Interface == nullptr"));
		return;
	}
	this->GameObjectType = Interface->GetGameObjectType();
	if(this->FloatingMinScaleMap.Find(this->GameObjectType) == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("ACircleRing::SearchAborptionTarget(): this->CircleRingSizeMap.Find(this->GameObjectType) == nullptr"));
		return;
	}
	if(this->LastAborptionTarget == nullptr && this->CurrentAborptionTarget == nullptr)
	{
		this->CurrentAborptionTarget = HitResult.GetActor();
		AbsorbToTarget();
		this->IsAbsorb = true;
		this->CanMove = false;
		return;
	}
	if (this->CurrentAborptionTarget == HitResult.GetActor())
	{
		return;
	}
	this->LastAborptionTarget = this->CurrentAborptionTarget;
	this->CurrentAborptionTarget = HitResult.GetActor();
	AbsorbToTarget();
	this->CanMove = false;
	this->IsAbsorb = true;



}


void ACircleRing::AbsorbToTarget()
{ 
	if (this->CurrentAborptionTarget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" ACircleRing::AbsorbToTarget(): this->CurrentAborptionTarget == nullptr"));
		return;
	}
	if (this->FloatingMinScaleMap.Find(this->GameObjectType) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACircleRing::AbsorbToTarget(): this->FloatingMinScaleMap.Find(this->GameObjectType) == nullptr"));
		return;
	}
	if (this->LastAborptionTarget == nullptr)
	{
		this->AbsorptionStartLocation = this->CropoutGameMode->GetMouseLocation();
	}
	else
	{
		this->AbsorptionStartLocation = this->LastAborptionTarget->GetActorLocation();
	}
    this->AbsorptionEndLocation = this->CurrentAborptionTarget->GetActorLocation();
	this->AbsorptionStarScale = GetMeshComponent()->GetComponentScale();
	this->AbsorptionEndScale = FVector(*this->FloatingMinScaleMap.Find(this->GameObjectType)) * this->CurrentAborptionTarget->GetActorScale();
	this->FloatingStartScale = FVector(*this->FloatingMinScaleMap.Find(this->GameObjectType)) * this->CurrentAborptionTarget->GetActorScale();
	this->FloatingEndScale = FVector(*this->FloatingMinScaleMap.Find(this->GameObjectType)) * this->CurrentAborptionTarget->GetActorScale() * this->FloatingAmplitude;
	PlayAnimation(this->TimelineComponent_Absorption,true,false,4.0f);

}


void ACircleRing::DetachFromTarget()
{
	if (this->CurrentAborptionTarget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACircleRing::DetachFromTarget(): this->CurrentAborptionTarget == nullptr"));
		return;
	}
	if (this->FloatingMinScaleMap.Find(this->GameObjectType) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACircleRing::DetachFromTarget(): this->FloatingMinScaleMap.Find(this->GameObjectType) == nullptr"));
		return;
	}
	this->SeparationStartLocation = this->CurrentAborptionTarget->GetActorLocation();
	this->SeparationStartScale = GetMeshComponent()->GetComponentScale();
	auto Lambda = [this]()
		{
			if (this->IsAbsorb == false)
			{
				this->TimelineComponent_Floating->Stop();
				SetActorTickEnabled(false);
				PlayAnimation(this->TimelineComponent_Separation, true, false, 4.0f);
			}
		};
	GetWorld()->GetTimerManager().SetTimer(this->SeparationTimer, Lambda, 0.3f,false);


}


void ACircleRing::PlayAnimation(UTimelineComponent* Timeline,  bool IsPlayFromStart, bool IsLooping, float PlayRate)
{
	Timeline->SetLooping(IsLooping);
	Timeline->SetPlayRate(PlayRate);
	IsPlayFromStart == true ? Timeline->PlayFromStart() : Timeline->ReverseFromEnd();

}


void ACircleRing::InitializeAnimation()
{
	if (this->Curve_01 == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACircleRing::InitializeAnimation(): this->Curve_01 == nullptr"));
		return;
	}
	if (this->Curve_010 == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACircleRing::InitializeAnimation(): this->Curve_010 == nullptr"));
		return;
	}
	FOnTimelineFloatStatic Delegate1;
	Delegate1.BindUObject(this, &ACircleRing::SetFloatingAnimation);
	this->TimelineComponent_Floating->AddInterpFloat(this->Curve_010, Delegate1);
	Delegate1.Unbind();
	Delegate1.BindUObject(this, &ACircleRing::SetAbsorptionAnimation);
	this->TimelineComponent_Absorption->AddInterpFloat(this->Curve_01, Delegate1);
	Delegate1.Unbind();
	Delegate1.BindUObject(this, &ACircleRing::SetSeparationAnimation);
	this->TimelineComponent_Separation->AddInterpFloat(this->Curve_01, Delegate1);
	Delegate1.Unbind();
	Delegate1.BindUObject(this, &ACircleRing::SetBeginPlayAnimation);
	this->TimelineComponent_BeginPlay->AddInterpFloat(this->Curve_01, Delegate1);
	FOnTimelineEventStatic Delegate2;
    Delegate2.BindUObject(this, &ACircleRing::OnBeginPlayAnimationFinished);
	this->TimelineComponent_BeginPlay->SetTimelineFinishedFunc(Delegate2);
	Delegate2.Unbind();
	Delegate2.BindUObject(this, &ACircleRing::OnAbsorptionAnimationFinished);
	this->TimelineComponent_Absorption->SetTimelineFinishedFunc(Delegate2);
	Delegate2.Unbind();
	Delegate2.BindUObject(this, &ACircleRing::OnSeparationAnimationFinished);
	this->TimelineComponent_Separation->SetTimelineFinishedFunc(Delegate2);
}


void ACircleRing::SetFloatingAnimation(float Value)
{
	FVector NewScale;
	NewScale = FMath::Lerp(this->FloatingStartScale,this->FloatingEndScale, Value);
    GetMeshComponent()->SetWorldScale3D(NewScale);
}


void ACircleRing::SetAbsorptionAnimation(float Value)
{
	FVector NewScale;
	FVector NewLocation;
	NewScale = FMath::Lerp(this->AbsorptionStarScale, this->AbsorptionEndScale, Value);
	NewLocation = FMath::Lerp(this->AbsorptionStartLocation, this->AbsorptionEndLocation, Value);
	SetActorLocation(FVector(NewLocation.X, NewLocation.Y, 3.0f));
	GetMeshComponent()->SetWorldScale3D(NewScale);

}


void ACircleRing::SetSeparationAnimation(float Value)
{
	FVector NewScale;
	FVector NewLocation;
	NewScale = FMath::Lerp(this->SeparationStartScale, this->OriginalMeshScale, Value);
	NewLocation = FMath::Lerp(this->SeparationStartLocation, this->CropoutGameMode->GetMouseLocation(), Value);
	SetActorLocation(FVector(NewLocation.X, NewLocation.Y, 3.0f));
	GetMeshComponent()->SetWorldScale3D(NewScale);
}


void ACircleRing::SetBeginPlayAnimation(float Value)
{
	FVector NewScale;
	NewScale = FMath::Lerp(FVector(0.0f), this->OriginalMeshScale, Value);
	GetMeshComponent()->SetWorldScale3D(NewScale);
	
}


void ACircleRing::InitializeMinFloatingSizeMap()
{
	this->FloatingMinScaleMap.Add(EGameObjectType::Tree, 5.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::Stone, 5.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::Shrub, 4.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::TownHall, 10.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::VillagerHouse, 6.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::CornField, 7.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::WheatField, 7.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::PumpkinField, 7.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::LettuceField, 7.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::Monument, 12.0f);

}


void ACircleRing::OnBeginPlayAnimationFinished()
{ 


}


void ACircleRing::OnAbsorptionAnimationFinished()
{
	//PlayAnimation(this->TimelineComponent_Floating, true, true);
	
}


void ACircleRing::OnSeparationAnimationFinished()
{
	GetMeshComponent()->SetWorldScale3D(this->OriginalMeshScale);
	SetActorTickEnabled(true);
	this->IsAbsorb = false;
	this->CanMove = true;
	this->LastAborptionTarget = nullptr;
	this->CurrentAborptionTarget = nullptr;

}


void ACircleRing::OnObjectBeginPlay(AActor* Object)
{
	if(Object != this)
	{ 
		return;
	}
	PlayAnimation(this->TimelineComponent_BeginPlay,true,false,3.0f);


}


void ACircleRing::OnObjectEndPlay(AActor* Object)
 {
	if (Object != this)
	{
		return;
	}
	GetMeshComponent()->SetWorldScale3D(this->OriginalMeshScale);
	this->LastAborptionTarget = nullptr;
	this->CurrentAborptionTarget = nullptr;
	this->IsAbsorb = false;
	this->CanMove = true;

 }


void ACircleRing::OnMouseMove(const FVector& MouseLocation)
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::CircleRing) == false)
	{
		return;
	}
	if (this->CanMove == false)
	{
		return;
	}
	FVector NewLocation = FVector(MouseLocation.X, MouseLocation.Y, 3.0f);
	SetActorLocation(NewLocation);


}


void ACircleRing::OnMouseLeftKeyRelease()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::CircleRing) == false)
	{
		return;
	}
	if(this->TimelineComponent_Separation->IsPlaying())
	{
		this->TimelineComponent_Separation->Stop();
	}
	if (this->TimelineComponent_Absorption->IsPlaying())
	{
		this->TimelineComponent_Absorption->Stop();
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this,EObjectPoolType::CircleRing);

}


//****************************************接口
void ACircleRing::SetGameObjectType(EGameObjectType NewType)
{
    this->GameObjectType = NewType;
	
}


EGameObjectType ACircleRing::GetGameObjectType()
{
	return this->GameObjectType;
}