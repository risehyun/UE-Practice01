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
	// 가상함수를 오버라이드한 함수를 작성할 때는 항상 Super 키워드의 Init을 사용해 언리얼 기능을 먼저 실행하도록 한다.
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