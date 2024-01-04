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

    const int32 ArraySize = 10;
    TArray<int32> IntArray;

    for (int32 i = 1; i <= ArraySize; ++i)
    {
        IntArray.Add(i);
    }

    for (int32 Element : IntArray)
    {
        static int32 i = 0;
        UE_LOG(LogTemp, Log, TEXT("[%d]: %d"), i++, Element);
    }
    UE_LOG(LogTemp, Log, TEXT("====="));

    IntArray.RemoveAll([](int32 InElement)->bool { return 0 == InElement % 2; });

    for (int32 Element : IntArray)
    {
        static int32 i = 0;
        UE_LOG(LogTemp, Log, TEXT("[%d]: %d"), i++, Element);
    }
    UE_LOG(LogTemp, Log, TEXT("====="));

    IntArray += {2, 4, 6, 8, 10};

    for (int32 Element : IntArray)
    {
        static int32 i = 0;
        UE_LOG(LogTemp, Log, TEXT("[%d]: %d"), i++, Element);
    }
    UE_LOG(LogTemp, Log, TEXT("====="));

    TArray<int32> IntArrayCompare;
    IntArrayCompare.Init(0, ArraySize);
    int32 IntArrayOriginal[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
    FMemory::Memcpy(IntArrayCompare.GetData(), IntArrayOriginal, sizeof(int32) * ArraySize);

    UE_LOG(LogTemp, Log, TEXT("IntArray == IntArrayCompare ? %d"), IntArray == IntArrayCompare);
}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();
}