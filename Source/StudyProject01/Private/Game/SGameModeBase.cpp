// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SGameModeBase.h"
#include "Controllers/SPlayerController.h"
#include "Characters/SPlayerPawn.h"

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
