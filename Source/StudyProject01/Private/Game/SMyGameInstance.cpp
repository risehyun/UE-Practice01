// USMyGameInstance.cpp


#include "Game/SMyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SUnrealObjectClass.h"
#include "Example/SFlyable.h"
#include "Example/SPigeon.h"
#include "JsonObjectConverter.h"
#include "UObject/SavePackage.h"

USMyGameInstance::USMyGameInstance()
{

}

void USMyGameInstance::Init()
{
	// �����Լ��� �������̵��� �Լ��� �ۼ��� ���� �׻� Super Ű������ Init�� ����� �𸮾� ����� ���� �����ϵ��� �Ѵ�.
	Super::Init();

    TMap<int32, FString> BirdMap;
    BirdMap.Add(5, TEXT("Pigeon"));
    BirdMap.Add(2, TEXT("Owl"));
    BirdMap.Add(7, TEXT("Albatross"));
    // BirdMap == [
    //  { Key: 5, Value: "Pigeon"     },
    //  { Key: 2, Value: "Owl"        },
    //  { Key: 7, Value: "Albatross"  }
    // ]

    BirdMap.Add(2, TEXT("Penquin"));
    // BirdMap == [
    //  { Key: 5, Value: "Pigeon"     },
    //  { Key: 2, Value: "Penquin"    },
    //  { Key: 7, Value: "Albatross"  }
    // ]

    FString* BirdIn7 = BirdMap.Find(7);
    // *BirdIn7 == "Albatross"
    FString* BirdIn8 = BirdMap.Find(8);
    // *BirdIn8 == nullptr
}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();
}