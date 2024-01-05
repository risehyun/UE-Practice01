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

protected:
    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

private:
    void LeftRight(float InAxisValue);

};
