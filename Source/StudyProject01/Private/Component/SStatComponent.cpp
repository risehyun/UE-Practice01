// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SStatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SMyGameInstance.h"

// Sets default values for this component's properties
USStatComponent::USStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = false;
	// ...
}


// Called when the game starts
void USStatComponent::BeginPlay()
{
	Super::BeginPlay();

    GameInstance = Cast<USMyGameInstance>(GetWorld()->GetGameInstance());
    if (true == ::IsValid(GameInstance))
    {
        if (nullptr != GameInstance->GetCharacterStatDataTable() || nullptr != GameInstance->GetCharacterStatDataTableRow(1))
        {
            float NewMaxHP = GameInstance->GetCharacterStatDataTableRow(1)->MaxHP;
            SetMaxHP(NewMaxHP);
            SetCurrentHP(MaxHP);
        }
    }
	
}

// Called every frame
void USStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USStatComponent::SetMaxHP(float InMaxHP)
{
    if (true == OnMaxHPChangeDelegate.IsBound())
    {
        OnMaxHPChangeDelegate.Broadcast(MaxHP, InMaxHP);
    }

    MaxHP = FMath::Clamp<float>(InMaxHP, 0.f, 9999);
}

void USStatComponent::SetCurrentHP(float InCurrentHP)
{
    if (true == OnCurrentHPChangeDelegate.IsBound())
    {
        OnCurrentHPChangeDelegate.Broadcast(CurrentHP, InCurrentHP);
    }

    CurrentHP = FMath::Clamp<float>(InCurrentHP, 0.f, MaxHP);

    if (CurrentHP < KINDA_SMALL_NUMBER)
    {
        OnOutOfCurrentHPDelegate.Broadcast();
        CurrentHP = 0.f;
    }
}
