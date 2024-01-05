// SPlayerController.cpp


#include "Controllers/SPlayerController.h"

ASPlayerController::ASPlayerController()
{
	// ������ Tick�� ���ƾ� �Էµ� ó���� �� ����.
	PrimaryActorTick.bCanEverTick = true;
}

void ASPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

 //   InputComponent->BindAxis(TEXT("LeftRight"), this, &ThisClass::LeftRight);
}

void ASPlayerController::LeftRight(float InAxisValue)
{
    UE_LOG(LogTemp, Error, TEXT("ASPlayerController::LeftRight(%.3f)"), InAxisValue);
}

void ASPlayerController::BeginPlay()
{
    Super::BeginPlay();

    FInputModeGameOnly InputModeGameOnly;
    SetInputMode(InputModeGameOnly);
}