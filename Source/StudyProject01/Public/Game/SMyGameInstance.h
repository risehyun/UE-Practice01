// SMyGameInstance.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SMyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT01_API USMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USMyGameInstance();

	virtual void Init() override;

	virtual void Shutdown() override;

private:
	UPROPERTY()
	FString Name;

};
