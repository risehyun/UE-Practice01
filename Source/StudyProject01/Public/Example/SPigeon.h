// SFlyable.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SFlyable.h" // include ������ �׻� .generated.h ���� ���� �ۼ��ؾ� �Ѵ�.
#include "SPigeon.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPigeonFlying, const FString&, InName, const int32, InID);

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
	FOnPigeonFlying OnPigeonFlying;

	virtual void Fly() override;

	const FString& GetName() const { return Name; }

	void SetName(const FString& InName) { Name = InName; }

	int32 GetID() const { return ID; }

	void SetID(int32 InID) { ID = InID; }

	virtual void Serialize(FArchive& Ar) override;

private:
	UPROPERTY()
	FString Name;

	int32 ID;
};
