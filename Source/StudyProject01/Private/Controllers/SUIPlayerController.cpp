// SUIPlayerController.cpp


#include "Controllers/SUIPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ASUIPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (true == ::IsValid(UIWidgetClass))
    {
        UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
        // CreateWidget()�� ȣ��� �� UIWidgetInstance->NativeOnInitialize() �Լ��� ȣ���.
        if (true == ::IsValid(UIWidgetInstance))
        {
            UIWidgetInstance->AddToViewport();
            // AddToViewport()�� ȣ�� �� �� UIWidgetInstance->NativeConstruct() �Լ��� ȣ���.

            FInputModeUIOnly Mode;
            Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
            SetInputMode(Mode);

            bShowMouseCursor = true;
        }
    }
}

void ASUIPlayerController::JoinServer(const FString& InIPAddress)
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("Loading"), true, FString::Printf(TEXT("NextLevel=%s?Saved=false"), *InIPAddress));
}