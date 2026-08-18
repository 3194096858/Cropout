
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelManager.generated.h"

class ULevelStreamingDynamic;


UCLASS()
class CROPOUT_API ULevelManager : public UObject
{
	GENERATED_BODY()
public:

private:
	UPROPERTY()
	ULevelStreamingDynamic* LevelStreaming;
	UPROPERTY()
	TMap<FName, FString> LevelPathMap;
public:
	UFUNCTION()
	void LoadLevel(UObject* World, FName LevelName);
	UFUNCTION()
	void UnloadLevel();
	UFUNCTION()
	void InitializeLevelPathMap();




};
