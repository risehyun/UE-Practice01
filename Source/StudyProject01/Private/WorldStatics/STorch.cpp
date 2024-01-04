// STorch.cpp


#include "WorldStatics/STorch.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
ASTorch::ASTorch()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    SetRootComponent(BoxComponent);

    BodyStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyStaticMeshComponent"));
    BodyStaticMeshComponent->SetupAttachment(GetRootComponent());
    BodyStaticMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Architecture/Pillar_50x500.Pillar_50x500'"));
    // ��� ������ �÷��� �߿��� ������� �����Ƿ�, static Ű���� ���.
    if (true == BodyStaticMesh.Succeeded())
    {
        BodyStaticMeshComponent->SetStaticMesh(BodyStaticMesh.Object);
    }

    PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
    PointLightComponent->SetupAttachment(GetRootComponent());
    PointLightComponent->SetRelativeLocation(FVector(0.f, 0.f, 500.f));

    ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
    ParticleSystemComponent->SetupAttachment(GetRootComponent());
    ParticleSystemComponent->SetRelativeLocation(FVector(0.f, 0.f, 500.f));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleTemplate(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
    if (true == ParticleTemplate.Succeeded())
    {
        ParticleSystemComponent->SetTemplate(ParticleTemplate.Object);
    }

    RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
}

// Called when the game starts or when spawned
void ASTorch::BeginPlay()
{
	Super::PostInitializeComponents();

    RotationSpeed = 300.f;
    RotatingMovementComponent->RotationRate = FRotator(0.f, RotationSpeed, 0.f);
}

// Called every frame
void ASTorch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

 //   AddActorWorldRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
}