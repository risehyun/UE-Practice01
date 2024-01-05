// ASPlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT01_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ASPlayerController();

    virtual void PostInitializeComponents() override;

    virtual void PlayerTick(float DeltaSeconds) override;

protected:
    virtual void SetupInputComponent() override;

    virtual void OnPossess(APawn* aPawn) override;

    virtual void OnUnPossess() override;

    virtual void BeginPlay() override;

    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

};
