// ASPlayerPawn.cpp


#include "Characters/SPlayerPawn.h"

ASPlayerPawn::ASPlayerPawn()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASPlayerPawn::PostInitializeComponents()
{
    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      PostInitializeComponents()"));
    Super::PostInitializeComponents();
    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      PostInitializeComponents()"));
}

void ASPlayerPawn::PossessedBy(AController* NewController)
{
    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      PossessedBy(ASPlayerController)"));
    Super::PossessedBy(NewController);
    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      PossessedBy(ASPlayerController)"));
}

void ASPlayerPawn::UnPossessed()
{
    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      UnPossessed()"));
    Super::UnPossessed();
    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      UnPossessed()"));
}

void ASPlayerPawn::Tick(float DeltaSeconds)
{
    static bool bOnce = false;
    if (false == bOnce)
    {
        UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      Tick()"));
    }
    Super::Tick(DeltaSeconds);
    if (false == bOnce)
    {
        UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      Tick()"));
        bOnce = true;
    }
}

void ASPlayerPawn::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      EndPlay()"));
    Super::EndPlay(EndPlayReason);
    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      EndPlay()"));
}

void ASPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      SetupPlayerInputComponent(PlayerInputComponent)"));
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      SetupPlayerInputComponent(PlayerInputComponent)"));
}

void ASPlayerPawn::BeginPlay()
{
    UE_LOG(LogTemp, Log, TEXT("                Start ASPlayerPawn::      BeginPlay()"));
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("                End   ASPlayerPawn::      BeginPlay()"));
}