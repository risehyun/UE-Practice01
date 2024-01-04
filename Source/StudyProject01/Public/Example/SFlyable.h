// SFlyable.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SFlyable.generated.h"

USTRUCT()
struct FBirdData
{
    GENERATED_BODY()

public:
    FBirdData() {}

    FBirdData(const FString& InName, int32 InID)
        : Name(InName)
        , ID(InID)
    {
    }

    friend FArchive& operator<<(FArchive& Ar, FBirdData& InBirdData)
    {
        Ar << InBirdData.Name;
        Ar << InBirdData.ID;
        return Ar;
    }

    UPROPERTY()
    FString Name = TEXT("DefaultBirdName");

    UPROPERTY()
    int32 ID = 0;

};

// This class does not need to be modified.
// Ŭ���� ������ ������ �� ����ϰ� �Ǵ� U Ŭ�����̴�.
UINTERFACE(MinimalAPI)
class USFlyable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
// ��κ��� ���Ǵ� �Ʒ��� I Ŭ�������� �ϰ� �ȴ�.
class STUDYPROJECT01_API ISFlyable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Fly() = 0;
};
