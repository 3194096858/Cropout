
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AudioManager.generated.h"

class UAudioComponent;

UCLASS()
class CROPOUT_API UAudioManager : public UObject
{
	GENERATED_BODY()
	
public:
   

private:
    UPROPERTY()
    UAudioComponent* AudioComponent;


public:
    UFUNCTION()
	void PlayBGM(UWorld* World , USoundBase* Sound);
	UFUNCTION()
	void PauseBGM();




};
