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
	// �����Լ��� �������̵��� �Լ��� �ۼ��� ���� �׻� Super Ű������ Init�� ����� �𸮾� ����� ���� �����ϵ��� �Ѵ�.
	Super::Init();

    USPigeon* Pigeon1 = NewObject<USPigeon>();
    ISFlyable* Bird1 = Cast<ISFlyable>(Pigeon1);
    // �������� �������̽� ������ ��κ� �̷������� ��ĳ���� �ϱ� ����.

    if (nullptr != Bird1)
    {
        Bird1->Fly();
    }
}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();
}