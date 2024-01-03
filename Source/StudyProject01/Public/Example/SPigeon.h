// SFlyable.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SFlyable.h" // include ������ �׻� .generated.h ���� ���� �ۼ��ؾ� �Ѵ�.
#include "SPigeon.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT01_API USPigeon 
	: public UObject
	, public ISFlyable
{
	GENERATED_BODY()

public:
	USPigeon();

	virtual void Fly() override;

private:
	UPROPERTY()
	FString Name;

};
