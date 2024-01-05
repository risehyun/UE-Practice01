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
    // �𸮾��� Construction Script�� ����, CDO ���� ������. �츮�� �����ϴ� ��ü ���� ������ ���� �ٸ�. 
	ASPlayerPawn();

    // �츮�� �����ϴ� ��ü ���� ���� �Լ�.
    virtual void PostInitializeComponents() override;

    virtual void PossessedBy(AController* NewController) override;

    virtual void UnPossessed() override;

    virtual void Tick(float DeltaSeconds) override;

    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    virtual void BeginPlay() override;

};
