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
// 클래스 정보를 전달할 때 사용하게 되는 U 클래스이다.
UINTERFACE(MinimalAPI)
class USFlyable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
// 대부분의 정의는 아래의 I 클래스에서 하게 된다.
class STUDYPROJECT01_API ISFlyable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Fly() = 0;
};
