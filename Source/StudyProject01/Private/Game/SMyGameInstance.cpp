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

    if (false == ::IsValid(CharacterStatDataTable) || CharacterStatDataTable->GetRowMap().Num() <= 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Not enuough data in CharacterStatDataTable."));
    }
    else
    {
        for (int32 i = 1; i <= CharacterStatDataTable->GetRowMap().Num(); ++i)
        {
            check(nullptr != GetCharacterStatDataTableRow(i));
        }
    }

    //SpawnedPigeon = NewObject<USPigeon>();
    //if (false == SpawnedPigeon->OnPigeonFlying.IsAlreadyBound(this, &ThisClass::HandlePigeonFlying))
    //{
    //    SpawnedPigeon->OnPigeonFlying.AddDynamic(this, &ThisClass::HandlePigeonFlying);
    //}
    //SpawnedPigeon->Fly();
}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();

    //if (true == SpawnedPigeon->OnPigeonFlying.IsAlreadyBound(this, &ThisClass::HandlePigeonFlying))
    //{
    //    SpawnedPigeon->OnPigeonFlying.RemoveDynamic(this, &ThisClass::HandlePigeonFlying);
    //}
}

FSStatTableRow* USMyGameInstance::GetCharacterStatDataTableRow(int32 InLevel)
{
    if (true == ::IsValid(CharacterStatDataTable))
    {
        return CharacterStatDataTable->FindRow<FSStatTableRow>(*FString::FromInt(InLevel), TEXT(""));
    }

    return nullptr;
}

//
//void USMyGameInstance::HandlePigeonFlying(const FString& InName, const int32 InID)
//{
//    //UE_LOG(LogTemp, Log, TEXT("[%d] %s is now flying."), InID, *InName);
//}