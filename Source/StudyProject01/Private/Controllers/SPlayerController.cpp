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
#include "Kismet/GameplayStatics.h"
#include "Game/SGameModeBase.h"
#include "UI/SGameResultWidget.h"
#include "Components/TextBlock.h"

ASPlayerController::ASPlayerController()
{
	// 액터의 Tick이 돌아야 입력도 처리할 수 있음.
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

            // Ch04 Pawn의 이벤트 함수 절 참고.
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
            MenuUIInstance->AddToViewport(3); // 상위에 띄움.

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

        // SetPause(true); 만약 게임 일시 정지를 원한다면.
        bShowMouseCursor = true;
    }
    else
    {
        MenuUIInstance->SetVisibility(ESlateVisibility::Collapsed);

        FInputModeGameOnly InputModeGameOnly;
        SetInputMode(InputModeGameOnly);

        // SetPause(false); 만약 게임 일시 정지를 원한다면.
        bShowMouseCursor = false;
    }

    bIsMenuOn = !bIsMenuOn;
}

void ASPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, NotificationText);
}

void ASPlayerController::OnOwningCharacterDead()
{
    ASGameModeBase* GameMode = Cast<ASGameModeBase>(UGameplayStatics::GetGameMode(this));
    if (true == HasAuthority() && true == ::IsValid(GameMode))
    {
        GameMode->OnControllerDead(this);
    }
}

void ASPlayerController::ShowWinnerUI_Implementation()
{
    if (false == HasAuthority())
    {
        if (true == ::IsValid(WinnerUIClass))
        {
            USGameResultWidget* WinnerUI = CreateWidget<USGameResultWidget>(this, WinnerUIClass);
            if (true == ::IsValid(WinnerUI))
            {
                WinnerUI->AddToViewport(3);
                WinnerUI->RankingText->SetText(FText::FromString(TEXT("#01")));

                FInputModeUIOnly Mode;
                Mode.SetWidgetToFocus(WinnerUI->GetCachedWidget());
                SetInputMode(Mode);

                bShowMouseCursor = true;
            }
        }
    }
}

void ASPlayerController::ShowLooserUI_Implementation(int32 InRanking)
{
    if (false == HasAuthority())
    {
        if (true == ::IsValid(LooserUIClass))
        {
            USGameResultWidget* LooserUI = CreateWidget<USGameResultWidget>(this, LooserUIClass);
            if (true == ::IsValid(LooserUI))
            {
                LooserUI->AddToViewport(3);
                FString RankingString = FString::Printf(TEXT("#%02d"), InRanking);
                LooserUI->RankingText->SetText(FText::FromString(RankingString));

                FInputModeUIOnly Mode;
                Mode.SetWidgetToFocus(LooserUI->GetCachedWidget());
                SetInputMode(Mode);

                bShowMouseCursor = true;
            }
        }
    }
}

void ASPlayerController::ReturnToLobby_Implementation()
{
    if (false == HasAuthority())
    { // 서버의 레벨이 변경되는걸 원치 않음. 클라가 이동해야하므로 if() 처리 필수.
        UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Loading")), true, FString(TEXT("NextLevel=Lobby?Saved=false")));
    }
}