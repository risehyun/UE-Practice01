// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SGameModeBase.h"
#include "Controllers/SPlayerController.h"
#include "Characters/SPlayerPawn.h"
#include "Game/SPlayerState.h"
#include "Game/SGameState.h"
#include "Kismet/GameplayStatics.h"

ASGameModeBase::ASGameModeBase()
{
    PlayerControllerClass = ASPlayerController::StaticClass();
    DefaultPawnClass = ASPlayerPawn::StaticClass();
}

void ASGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    UE_LOG(LogTemp, Error, TEXT("         Start ASGameMode::        InitGame()"));
    Super::InitGame(MapName, Options, ErrorMessage);
    UE_LOG(LogTemp, Error, TEXT("         End   ASGameMode::        InitGame()"));
}

void ASGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    ASGameState* SGameState = GetGameState<ASGameState>();
    if (false == SGameState)
    {
        return;
    }

    //if (MatchState != EMatchState::Waiting)
    if (SGameState->MatchState != EMatchState::Waiting)
    {
        NewPlayer->SetLifeSpan(0.1f);
        return;
    }

    ASPlayerState* PlayerState = NewPlayer->GetPlayerState<ASPlayerState>();
    if (true == ::IsValid(PlayerState))
    {
        PlayerState->InitPlayerState();
    }

    ASPlayerController* NewPlayerController = Cast<ASPlayerController>(NewPlayer);
    if (true == ::IsValid(NewPlayerController))
    {
        AlivePlayerControllers.Add(NewPlayerController);
        NewPlayerController->NotificationText = FText::FromString(TEXT("Connected to the game server."));
    }
}

void ASGameModeBase::Logout(AController* Exiting)
{
    Super::Logout(Exiting);

    ASPlayerController* ExitingPlayerController = Cast<ASPlayerController>(Exiting);
    if (true == ::IsValid(ExitingPlayerController) && INDEX_NONE != AlivePlayerControllers.Find(ExitingPlayerController))
    {
        AlivePlayerControllers.Remove(ExitingPlayerController);
        DeadPlayerControllers.Add(ExitingPlayerController);
    }
}

void ASGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(MainTimerHandle, this, &ThisClass::OnMainTimerElapsed, 1.f, true);

    RemainWaitingTimeForPlaying = WaitingTime;
}

void ASGameModeBase::OnMainTimerElapsed()
{
    ASGameState* SGameState = GetGameState<ASGameState>();
    if (false == ::IsValid(SGameState))
    {
        return;
    }

    //switch (MatchState)
    switch (SGameState->MatchState)
    {
    case EMatchState::None:
        break;
    case EMatchState::Waiting:
    {
        FString NotificationString = FString::Printf(TEXT(""));

        if (AlivePlayerControllers.Num() < MinimumPlayerCountForPlaying)
        {
            NotificationString = FString::Printf(TEXT("Wait another players for playing."));

            RemainWaitingTimeForPlaying = WaitingTime; // �ּ��ο��� �ȵȴٸ� ��� �ð� �ʱ�ȭ.
        }
        else
        {
            NotificationString = FString::Printf(TEXT("Wait %d seconds for playing."), RemainWaitingTimeForPlaying);

            --RemainWaitingTimeForPlaying;
        }

        if (0 == RemainWaitingTimeForPlaying)
        {
            NotificationString = FString::Printf(TEXT(""));

          // MatchState = EMatchState::Playing;

            SGameState->MatchState = EMatchState::Playing;
        }

        NotifyToAllPlayer(NotificationString);

        break;
    }
    case EMatchState::Playing:
    {
        //FString NotificationString = FString::Printf(TEXT("%d / %d"), AlivePlayerControllers.Num(), AlivePlayerControllers.Num() + DeadPlayerControllers.Num());

        //NotifyToAllPlayer(NotificationString);

        //if (AlivePlayerControllers.Num() <= 1)
        //{
        //    MatchState = EMatchState::Ending;
        //}

      //  ASGameState* SGameState = GetGameState<ASGameState>();
        if (true == ::IsValid(SGameState))
        {
            SGameState->AlivePlayerControllerCount = AlivePlayerControllers.Num();

            FString NotificationString = FString::Printf(TEXT("%d / %d"), SGameState->AlivePlayerControllerCount, SGameState->AlivePlayerControllerCount + DeadPlayerControllers.Num());

            NotifyToAllPlayer(NotificationString);

            if (SGameState->AlivePlayerControllerCount <= 1)
            {
          //      MatchState = EMatchState::Ending;
                AlivePlayerControllers[0]->ShowWinnerUI();
                SGameState->MatchState = EMatchState::Ending;
            }
        }

        break;
    }
    case EMatchState::Ending:
    {
        FString NotificationString = FString::Printf(TEXT("Waiting %d for returning to lobby."), RemainWaitingTimeForEnding);

        NotifyToAllPlayer(NotificationString);

        --RemainWaitingTimeForEnding;

        if (0 == RemainWaitingTimeForEnding)
        {
            for (auto AliveController : AlivePlayerControllers)
            {
                AliveController->ReturnToLobby();
            }

            for (auto DeadController : AlivePlayerControllers)
            {
                DeadController->ReturnToLobby();
            }

            MainTimerHandle.Invalidate();

            FName CurrentLevelName = FName(UGameplayStatics::GetCurrentLevelName(this));
            UGameplayStatics::OpenLevel(this, CurrentLevelName, true, FString(TEXT("listen")));
            // ���� ���� ������ ���� ���� ���񽺵�� �����Ǿ� �ִٸ�,
            // �̷��� ������ �ٽ� �غ�� �� ���� �������� �˷���. "���ο� �÷��̾� ���� �� ����."
            // �׷� ���� ���񽺴� ���ο� �÷��̾�鿡�� ���� ������ IP �ּҸ� �������༭ ���� ����.
        }

        break;
    }
    case EMatchState::End:
        break;
    default:
        break;
    }
}

void ASGameModeBase::NotifyToAllPlayer(const FString& NotificationString)
{
    for (auto AlivePlayerController : AlivePlayerControllers)
    {
        if (true == IsValid(AlivePlayerController))
        {
            AlivePlayerController->NotificationText = FText::FromString(NotificationString);
        }

    }

    for (auto DeadPlayerController : DeadPlayerControllers)
    {
        if (true == IsValid(DeadPlayerController))
        {
            DeadPlayerController->NotificationText = FText::FromString(NotificationString);
        }
    }
}

void ASGameModeBase::OnControllerDead(ASPlayerController* InDeadController)
{
    if (false == ::IsValid(InDeadController) || INDEX_NONE == AlivePlayerControllers.Find(InDeadController))
    {
        return;
    }

    InDeadController->ShowLooserUI(AlivePlayerControllers.Num());

    AlivePlayerControllers.Remove(InDeadController);
    DeadPlayerControllers.Add(InDeadController);
}
