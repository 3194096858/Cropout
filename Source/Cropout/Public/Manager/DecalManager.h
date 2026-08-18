
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DecalManager.generated.h"



class UDecalComponent;


UCLASS()
class CROPOUT_API UDecalManager : public UObject
{
	GENERATED_BODY()

public:

private:
	//UPROPERTY()
  //  UDecalComponent* DecalComponent;


public:
	UFUNCTION()
	UDecalComponent* SpawnDecalAtLocation(UObject* World ,UMaterialInterface* Decal,FVector Location, FRotator Rotation, FVector Size,float Lifetime = 0.0f);
	UFUNCTION()
	void DestroyDecal(UDecalComponent* DecalComponent,float Delay,float Duration);

};
