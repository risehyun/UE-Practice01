// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldStatics/SLandMine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASLandMine::ASLandMine()
{
    PrimaryActorTick.bCanEverTick = true;

    BodyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyBoxComponent"));
    SetRootComponent(BodyBoxComponent);

    BodyStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyStaticMeshComponent"));
    BodyStaticMeshComponent->SetupAttachment(GetRootComponent());

    ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
    ParticleSystemComponent->SetupAttachment(GetRootComponent());
    ParticleSystemComponent->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void ASLandMine::BeginPlay()
{
    Super::BeginPlay();

    //UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::BeginPlay() has been called.")));

    if (true == HasAuthority())
    {
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::BeginPlay() has been called in Server PC.")));
    }
    else
    {
        if (GetOwner() == UGameplayStatics::GetPlayerController(this, 0))
        {
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::BeginPlay() has been called in OwningClient PC.")));
        }
        else
        {
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::BeginPlay() has been called in OtherClient PC.")));
        }
    }

    if (false == OnActorBeginOverlap.IsAlreadyBound(this, &ThisClass::OnLandMineBeginOverlap))
    {
        OnActorBeginOverlap.AddDynamic(this, &ThisClass::OnLandMineBeginOverlap);
    }
}

// Called every frame
void ASLandMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASLandMine::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    //UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::EndPlay() has been called.")));

    if (true == HasAuthority())
    {
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::EndPlay() has been called in Server PC.")));
    }
    else
    {
        if (GetOwner() == UGameplayStatics::GetPlayerController(this, 0))
        {
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::EndPlay() has been called in OwningClient PC.")));
        }
        else
        {
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::EndPlay() has been called in OtherClient PC.")));
        }
    }

    if (true == OnActorBeginOverlap.IsAlreadyBound(this, &ThisClass::OnLandMineBeginOverlap))
    {
        OnActorBeginOverlap.RemoveDynamic(this, &ThisClass::OnLandMineBeginOverlap);
    }
}

void ASLandMine::OnLandMineBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (true == HasAuthority())
    {
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::OnLandMineBeginOverlap() has been called in Server PC.")));
    }
    else
    {
        if (GetOwner() == UGameplayStatics::GetPlayerController(this, 0))
        {
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::OnLandMineBeginOverlap() has been called in OwningClient PC.")));
        }
        else
        {
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ASLandMine::OnLandMineBeginOverlap() has been called in OtherClient PC.")));
        }
    }

    if (true == HasAuthority())
    {
        SpawnEffect_NetMulticast();
    }
}

void ASLandMine::SpawnEffect_NetMulticast_Implementation()
{
    ParticleSystemComponent->Activate(true);
}
