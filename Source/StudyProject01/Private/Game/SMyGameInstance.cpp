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

    const int32 SetSize = 10;
    TSet<int32> IntSet;

    for (int32 i = 1; i <= SetSize; ++i)
    {
        IntSet.Add(i);
    }

    for (int32 Element : IntSet)
    {
        static int32 i = 0;
        UE_LOG(LogTemp, Log, TEXT("[%d]: %d"), i++, Element);
    }
    UE_LOG(LogTemp, Log, TEXT("====="));

    IntSet.Remove(2);
    IntSet.Remove(4);
    IntSet.Remove(6);
    IntSet.Remove(8);
    IntSet.Remove(10);

    for (int32 Element : IntSet)
    {
        static int32 i = 0;
        UE_LOG(LogTemp, Log, TEXT("[%d]: %d"), i++, Element);
    }
    UE_LOG(LogTemp, Log, TEXT("====="));

    IntSet.Add(2);
    IntSet.Add(4);
    IntSet.Add(6);
    IntSet.Add(8);
    IntSet.Add(10);

    for (int32 Element : IntSet)
    {
        static int32 i = 0;
        UE_LOG(LogTemp, Log, TEXT("[%d]: %d"), i++, Element);
    }
    UE_LOG(LogTemp, Log, TEXT("====="));

    int32 Key = 2;
    UE_LOG(LogTemp, Log, TEXT("%d: %s"), Key, nullptr == IntSet.Find(Key) ? TEXT("nullptr") : TEXT("Is in"));

    Key = 11;
    UE_LOG(LogTemp, Log, TEXT("%d: %s"), Key, nullptr == IntSet.Find(Key) ? TEXT("nullptr") : TEXT("Is in"));
}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();
}