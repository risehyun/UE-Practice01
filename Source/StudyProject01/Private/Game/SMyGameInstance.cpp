// USMyGameInstance.cpp


#include "Game/SMyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SUnrealObjectClass.h"
#include "Example/SFlyable.h"
#include "Example/SPigeon.h"

USMyGameInstance::USMyGameInstance()
{

}

void USMyGameInstance::Init()
{
	// 가상함수를 오버라이드한 함수를 작성할 때는 항상 Super 키워드의 Init을 사용해 언리얼 기능을 먼저 실행하도록 한다.
	Super::Init();

    USPigeon* Pigeon1 = NewObject<USPigeon>();
    ISFlyable* Bird1 = Cast<ISFlyable>(Pigeon1);
    // 현업에서 인터페이스 개념은 대부분 이런식으로 업캐스팅 하기 위함.

    if (nullptr != Bird1)
    {
        Bird1->Fly();
    }
}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();
}