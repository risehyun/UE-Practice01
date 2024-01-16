// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SGameModeBase.h"
#include "Controllers/SPlayerController.h"
#include "Characters/SPlayerPawn.h"
#include "Game/SPlayerState.h"

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
