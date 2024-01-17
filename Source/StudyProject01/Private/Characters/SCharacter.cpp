// SCharacter.cpp


#include "Characters/SCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Component/SStatComponent.h"
#include "Controllers/SPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Game/SGameState.h"

ASCharacter::ASCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    float CharacterHalfHeight = 95.f;
    float CharacterRadius = 40.f;

    GetCapsuleComponent()->InitCapsuleSize(CharacterRadius, CharacterHalfHeight);

    FVector PivotPosition(0.f, 0.f, -CharacterHalfHeight);
    FRotator PivotRotation(0.f, -90.f, 0.f);
    GetMesh()->SetRelativeLocationAndRotation(PivotPosition, PivotRotation);

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->TargetArmLength = 400.f;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    // 콘솔 개발시 디지털 입력과 아날로그 입력 사이의 간극을 보간하기 위함
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->JumpZVelocity = 700.f;
    // 공중에 떠있을 때, 움직임의 자유도 설정 (ex. 점프 상태에서 뒤로 돌기가 가능한지 등)
    GetCharacterMovement()->AirControl = 0.35f;
    // 이동중 멈췄을 때 얼마나 빨리 멈추게 할지 보간 값을 설정, 값이 커질 수록 빨리 멈춘다.
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

  //  bIsDead = false;

    StatComponent = CreateDefaultSubobject<USStatComponent>(TEXT("StatComponent"));

    if (true == HasAuthority())
    {
        StatComponent->SetIsReplicated(true);
    }
}

void ASCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (false == ::IsValid(StatComponent))
    {
        return;
    }

    if (false == StatComponent->OnOutOfCurrentHPDelegate.IsAlreadyBound(this, &ThisClass::OnCharacterDeath))
    {
        StatComponent->OnOutOfCurrentHPDelegate.AddDynamic(this, &ThisClass::OnCharacterDeath);
    }
}

float ASCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float FinalDamageAmount = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

    ASGameState* SGameState = Cast<ASGameState>(UGameplayStatics::GetGameState(this));
    if (true == ::IsValid(SGameState) && EMatchState::Playing != SGameState->MatchState)
    {
        return FinalDamageAmount;
    }

    StatComponent->SetCurrentHP(StatComponent->GetCurrentHP() - FinalDamageAmount);

    UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("%s [%.1f / %.1f]"), *GetName(), StatComponent->GetCurrentHP(), StatComponent->GetMaxHP()));

    return FinalDamageAmount;
}

void ASCharacter::OnCharacterDeath()
{
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

    if (true == StatComponent->OnOutOfCurrentHPDelegate.IsAlreadyBound(this, &ThisClass::OnCharacterDeath))
    {
        StatComponent->OnOutOfCurrentHPDelegate.RemoveDynamic(this, &ThisClass::OnCharacterDeath);
    }

    ASPlayerController* PlayerController = GetController<ASPlayerController>();
    if (true == ::IsValid(PlayerController) && true == HasAuthority())
    {
        PlayerController->OnOwningCharacterDead();
    }
}