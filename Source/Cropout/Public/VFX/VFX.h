
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VFX.generated.h"



class UStaticMeshComponent;
class UCollisionDetectionComponent;
class ACropoutGameMode;
class UStaticMeshComponent;
class USceneComponent;
class UCapsuleComponent;
//class UTimelineComponent;


UCLASS()
class CROPOUT_API AVFX : public AActor
{
	GENERATED_BODY()
	
public:	
	AVFX();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

	//*********************************变量
public:


protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCollisionDetectionComponent* CollisionDetectionComponent;
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;

private:
	
	FTimerHandle InitializationTimer;
//*********************************函数
public:
	UFUNCTION()
	UStaticMeshComponent* GetMeshComponent();

protected:
	virtual void OnObjectBeginPlay(AActor* Object);
	virtual void OnObjectEndPlay(AActor* Object);
	virtual void OnMouseMove(const FVector& MouseLocation);
	virtual void OnMouseLeftKeyRelease();
private:
	


};
