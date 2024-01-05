// ASPlayerPawn.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SPlayerPawn.generated.h"

UCLASS()
class STUDYPROJECT01_API ASPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
    // 언리얼의 Construction Script에 따라, CDO 생성 시점임. 우리가 생각하는 개체 생성 시점과 조금 다름. 
	ASPlayerPawn();

    // 우리가 생각하는 개체 생성 시점 함수.
    virtual void PostInitializeComponents() override;

    virtual void PossessedBy(AController* NewController) override;

    virtual void UnPossessed() override;

    virtual void Tick(float DeltaSeconds) override;

    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    virtual void BeginPlay() override;

};
