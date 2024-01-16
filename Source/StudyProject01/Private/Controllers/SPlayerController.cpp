// SPlayerController.cpp

#include "Controllers/SPlayerController.h"
#include "UI/SHUD.h"
#include "Game/SPlayerState.h"
#include "Component/SStatComponent.h"
// #include "Characters/SRPGCharacter.h"
#include "Characters/STPSCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

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

    if (true == HasAuthority())
    {
        return;
    }

    if (true == ::IsValid(HUDWidgetClass))
    {
        HUDWidget = CreateWidget<USHUD>(this, HUDWidgetClass);
        if (true == ::IsValid(HUDWidget))
        {
            HUDWidget->AddToViewport();

            //ASPlayerState* SPlayerState = GetPlayerState<ASPlayerState>();
            //if (true == ::IsValid(SPlayerState))
            //{
            //    HUDWidget->BindPlayerState(SPlayerState);
            //}

            ASCharacter* PC = GetPawn<ASCharacter>();
            if (true == ::IsValid(PC))
            {
                USStatComponent* StatComponent = PC->GetStatComponent();
                if (true == ::IsValid(StatComponent))
                {
                    HUDWidget->BindStatComponent(StatComponent);
                }
            }

            FTimerHandle TimerHandle;

            // Ch04 Pawn�� �̺�Ʈ �Լ� �� ����.
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
                ASPlayerState* SPlayerState = GetPlayerState<ASPlayerState>();
                if (true == ::IsValid(SPlayerState))
                {
                    HUDWidget->BindPlayerState(SPlayerState);
                }
                }), 0.5f, false);
        }
    }

    if (true == ::IsValid(MenuUIClass))
    {
        MenuUIInstance = CreateWidget<UUserWidget>(this, MenuUIClass);
        if (true == ::IsValid(MenuUIInstance))
        {
            MenuUIInstance->AddToViewport(3); // ������ ���.

            MenuUIInstance->SetVisibility(ESlateVisibility::Collapsed);
        }
    }

    if (true == ::IsValid(CrosshairUIClass))
    {
        UUserWidget* CrosshairUI = CreateWidget<UUserWidget>(this, CrosshairUIClass);
        if (true == ::IsValid(CrosshairUI))
        {
            CrosshairUI->AddToViewport(1);

            CrosshairUI->SetVisibility(ESlateVisibility::Visible);
        }
    }

    if (true == ::IsValid(NotificationTextUIClass))
    {
        UUserWidget* NotificationTextUI = CreateWidget<UUserWidget>(this, NotificationTextUIClass);
        if (true == ::IsValid(NotificationTextUI))
        {
            NotificationTextUI->AddToViewport(1);

            NotificationTextUI->SetVisibility(ESlateVisibility::Visible);
        }
    }

}

void ASPlayerController::ToggleMenu()
{
    if (false == bIsMenuOn)
    {
        MenuUIInstance->SetVisibility(ESlateVisibility::Visible);

        FInputModeUIOnly Mode;
        Mode.SetWidgetToFocus(MenuUIInstance->GetCachedWidget());
        SetInputMode(Mode);

        // SetPause(true); ���� ���� �Ͻ� ������ ���Ѵٸ�.
        bShowMouseCursor = true;
    }
    else
    {
        MenuUIInstance->SetVisibility(ESlateVisibility::Collapsed);

        FInputModeGameOnly InputModeGameOnly;
        SetInputMode(InputModeGameOnly);

        // SetPause(false); ���� ���� �Ͻ� ������ ���Ѵٸ�.
        bShowMouseCursor = false;
    }

    bIsMenuOn = !bIsMenuOn;
}

void ASPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, NotificationText);
}
