
#pragma once

#include "Enum/NPCState/NPCState.h"



#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NPCAnimInstance.generated.h"

class ANPC;
class ACropoutGameMode;


UCLASS()
class CROPOUT_API UNPCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(BlueprintReadWrite)
	float MovementSpeed = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	ENPCState NPCState = ENPCState::Patrol;



protected:
	
private:
	UPROPERTY()
	ANPC* NPC = nullptr;
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;

public:

private:
	UFUNCTION()
	void OnNPCStateChange(AActor* AnimInstanceOwner, ENPCState NewState);
	UFUNCTION()
	void SaveDataToManager();
	UFUNCTION()
	void LoadDataByManager();

};
