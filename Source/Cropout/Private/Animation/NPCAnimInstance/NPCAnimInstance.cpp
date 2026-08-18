#include "Animation/NPCAnimInstance/NPCAnimInstance.h"
#include "NPC/NPC.h"
#include "Interface/NPCStateInterface/NPCStateInterface.h"

#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"

#include "Manager/DataManager.h"



void UNPCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	this->NPC = Cast<ANPC>(TryGetPawnOwner());
	CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UNPCAnimInstance::NativeBeginPlay(): CropoutGameMode == nullptr"));
		return;
	}
	if (CropoutGameMode->GetGameInstance() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UNPCAnimInstance::NativeBeginPlay(): CropoutGameMode->GetGameInstance() == nullptr"));
		return;
	}
	if (CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UNPCAnimInstance::NativeBeginPlay(): CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr"));
		return;
	}
	CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnNPCStateChange.AddUObject(this, &UNPCAnimInstance::OnNPCStateChange);


}

void UNPCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (this->NPC == nullptr)
	{
		return;
	}
	this->MovementSpeed = this->NPC->GetMovementSpeed();
	

}


void UNPCAnimInstance::LoadDataByManager()
{
	//FName ActorName = FName(TryGetPawnOwner()->GetName());
	//if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckVillagerDataIsExist(ActorName) == false)
	//{
	//	return;
	//}
	//FVillagerData TargetData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerData(ActorName);

	//if (TargetData.AnimationData.IsActive == true)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("Load111 : Montage Is Active "));
	//	//UE_LOG(LogTemp, Warning, TEXT("Load111 : Montage Position = %f "), TargetData.AnimationData.Position);
	//	Montage_Play(GetMontageFromTable(EGameObjectType::Tree));
	//	GetMesh()->GetAnimInstance()->Montage_SetPosition(GetMontageFromTable(EGameObjectType::Tree), TargetData.AnimationData.Position);
	//	GetMesh()->GetAnimInstance()->Montage_SetPlayRate(GetMontageFromTable(EGameObjectType::Tree), TargetData.AnimationData.PlayRate);
	//	//GetMesh()->GetAnimInstance()->Montage_SetPlayRate(GetMontageFromTable(EGameObjectType::Tree), 0.01f);

	//}
	//

}

void UNPCAnimInstance::SaveDataToManager()
{
	/*FName ActorName = FName(TryGetPawnOwner()->GetName());
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckVillagerDataIsExist(ActorName) == false)
	{
		return;
	}
	FVillagerData NewData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerData(ActorName);
	NewData.AnimationData.IsActive = Montage_IsActive(GetCurrentActiveMontage());
	if (NewData.AnimationData.IsActive == true)
	{
		NewData.AnimationData.PlayRate = Montage_GetPlayRate(GetCurrentActiveMontage());
		NewData.AnimationData.Position = Montage_GetPosition(GetCurrentActiveMontage());
		NewData.AnimationData.StectionName = Montage_GetCurrentSection(GetCurrentActiveMontage());
	}*/
	
	

	
}






void UNPCAnimInstance::OnNPCStateChange(AActor* AnimInstanceOwner, ENPCState NewState)
{
	if (AnimInstanceOwner == TryGetPawnOwner())
	{
		this->NPCState = NewState;
	}
}







