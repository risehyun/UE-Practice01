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

void ASGameModeBase::InitGameState()
{
    UE_LOG(LogTemp, Error, TEXT("         Start ASGameMode::        InitGameState()"));
    Super::InitGameState();
    UE_LOG(LogTemp, Error, TEXT("         End   ASGameMode::        InitGameState()"));
}

void ASGameModeBase::PostInitializeComponents()
{
    UE_LOG(LogTemp, Error, TEXT("         Start ASGameMode::        PostInitializeComponents()"));
    Super::PostInitializeComponents();
    UE_LOG(LogTemp, Error, TEXT("         End   ASGameMode::        PostInitializeComponents()"));
}

void ASGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMassage)
{
    UE_LOG(LogTemp, Error, TEXT("         Start ASGameMode::        PreLogin()"));
    Super::PreLogin(Options, Address, UniqueId, ErrorMassage);
    UE_LOG(LogTemp, Error, TEXT("         End   ASGameMode::        PreLogin()"));
}

APlayerController* ASGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    UE_LOG(LogTemp, Error, TEXT("         Start ASGameMode::        Login()"));
    APlayerController* PlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
    UE_LOG(LogTemp, Error, TEXT("         End   ASGameMode::        Login()"));

    return PlayerController;
}

void ASGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    UE_LOG(LogTemp, Error, TEXT("         Start ASGameMode::        PostLogin(ASPlayerController)"));
    Super::PostLogin(NewPlayer);
    UE_LOG(LogTemp, Error, TEXT("         End   ASGameMode::        PostLogin(ASPlayerController)"));
}
