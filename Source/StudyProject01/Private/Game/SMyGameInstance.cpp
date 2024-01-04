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

    SpawnedPigeon = NewObject<USPigeon>();
    if (false == SpawnedPigeon->OnPigeonFlying.IsAlreadyBound(this, &ThisClass::HandlePigeonFlying))
    {
        SpawnedPigeon->OnPigeonFlying.AddDynamic(this, &ThisClass::HandlePigeonFlying);
    }
    SpawnedPigeon->Fly();
}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();

    if (true == SpawnedPigeon->OnPigeonFlying.IsAlreadyBound(this, &ThisClass::HandlePigeonFlying))
    {
        SpawnedPigeon->OnPigeonFlying.RemoveDynamic(this, &ThisClass::HandlePigeonFlying);
    }
}

void USMyGameInstance::HandlePigeonFlying(const FString& InName, const int32 InID)
{
    UE_LOG(LogTemp, Log, TEXT("[%d] %s is now flying."), InID, *InName);
}