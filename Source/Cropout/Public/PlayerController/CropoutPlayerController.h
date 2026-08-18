
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CropoutPlayerController.generated.h"



class UInputMappingContext;
struct FInputActionValue;
class UInputAction;





UCLASS()
class CROPOUT_API ACropoutPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    ACropoutPlayerController();
	virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;



public:



private:
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MouseLeftKeyInputAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MouseWheelInputAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MouseMovementInputAction;







public:
    UFUNCTION()
    UInputMappingContext* GetInputMappingContext();

    UFUNCTION()
    UInputAction* GetMouseLeftKeyInputAction();

    UFUNCTION()
    UInputAction* GetMouseWheelInputAction();

    UFUNCTION()
    UInputAction* GetMouseMovementInputAction();

    UFUNCTION()
    void GetMouseLocationAndDirection(FVector& MouseLocation, FVector& MouseDirection);


};
