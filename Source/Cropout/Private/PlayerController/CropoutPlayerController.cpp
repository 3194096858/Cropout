

#include "PlayerController/CropoutPlayerController.h"

ACropoutPlayerController::ACropoutPlayerController()
{
	
	bShowMouseCursor = true;
}

void ACropoutPlayerController::BeginPlay()
{
	//GetOwner();
	
}


void ACropoutPlayerController::Tick(float DeltaTime)
{
}



UInputMappingContext* ACropoutPlayerController::GetInputMappingContext()
{
	if (InputMappingContext == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayerController::GetInputMappingContext(): InputMappingContext is nullptr"));
	};
    return InputMappingContext;
}

UInputAction* ACropoutPlayerController::GetMouseMovementInputAction()
{
	if (MouseMovementInputAction == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayerController::GetMouseMovementInputAction(): MouseMovementInputAction is nullptr"));
	};
	return MouseMovementInputAction;
}


UInputAction* ACropoutPlayerController::GetMouseWheelInputAction()
{
	if (MouseWheelInputAction == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayerController::GetMouseWheelInputAction(): MouseWheelInputAction == nullptr"));
	};
	return MouseWheelInputAction;
}


UInputAction* ACropoutPlayerController::GetMouseLeftKeyInputAction()
{
	if (MouseLeftKeyInputAction == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutPlayerController::GetMouseMovementInputAction(): MouseLeftKeyInputAction == nullptr"));
	};
	return MouseLeftKeyInputAction;
}


void ACropoutPlayerController::GetMouseLocationAndDirection(FVector& MouseLocation, FVector& MouseDirection)
{
	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, MouseLocation, MouseDirection);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("MouseLocation = %s , MouseDirection = %s  !!!!!"), *MouseLocation.ToString(), *MouseDirection.ToString()));


}




