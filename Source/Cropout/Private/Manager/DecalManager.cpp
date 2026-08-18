

#include "Manager/DecalManager.h"

#include "Components/DecalComponent.h"

#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Kismet/GameplayStatics.h"


UDecalComponent* UDecalManager::SpawnDecalAtLocation(UObject* World,UMaterialInterface* Decal, FVector Location, FRotator Rotation, FVector Size,float Lifetime)
{
	if (Decal == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UDecalManager::SpawnDecalAtLocation(): Decal == nullptr"));
		return nullptr;
	}
	return UGameplayStatics::SpawnDecalAtLocation(World,Decal,Size,Location,Rotation,Lifetime);
}


void UDecalManager::DestroyDecal(UDecalComponent* DecalComponent, float Delay, float Duration)
{
	if (DecalComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UDecalManager::DestroyDecal(): DecalComponent == nullptr"));
		return;
	}
	DecalComponent->SetFadeOut(Delay,Duration,true);
	DecalComponent = nullptr;

}
