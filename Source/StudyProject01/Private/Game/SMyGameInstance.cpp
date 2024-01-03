// USMyGameInstance.cpp


#include "Game/SMyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SUnrealObjectClass.h"
#include "Example/SFlyable.h"
#include "Example/SPigeon.h"

USMyGameInstance::USMyGameInstance()
{
	UE_LOG(LogTemp, Log, TEXT("USMyGameInstance() has been called."));

	Name = TEXT("USGameInstance Class Default Object");
	// CDO�� Name �Ӽ��� �����.
	// �ߴ����� �ɾ�� �𸮾� �����Ͱ� ����Ǳ� ���� ȣ����� �� �� ����.
}

void USMyGameInstance::Init()
{
	// �����Լ��� �������̵��� �Լ��� �ۼ��� ���� �׻� Super Ű������ Init�� ����� �𸮾� ����� ���� �����ϵ��� �Ѵ�.
	Super::Init();

    USUnrealObjectClass* USObject1 = NewObject<USUnrealObjectClass>();
    // �𸮾��� �̷������� new Ű���带 �Ⱦ��� NewObject<>() API�� ����ؾ� ��.

    UE_LOG(LogTemp, Log, TEXT("USObject1's Name: %s"), *USObject1->GetName());
    // �츮�� ������ Getter()

    FProperty* NameProperty = USUnrealObjectClass::StaticClass()->FindPropertyByName(TEXT("Name"));
    // ������Ƽ �ý����� Ȱ���� Getter()

    FString CompiletimeUSObjectName;
    if (nullptr != NameProperty)
    {
        NameProperty->GetValue_InContainer(USObject1, &CompiletimeUSObjectName);
        UE_LOG(LogTemp, Log, TEXT("CompiletimeUSObjectName: %s"), *CompiletimeUSObjectName);
    }

    USObject1->HelloUnreal();

    UFunction* HelloUnrealFunction = USObject1->GetClass()->FindFunctionByName(TEXT("HelloUnreal"));
    if (nullptr != HelloUnrealFunction)
    {
        USObject1->ProcessEvent(HelloUnrealFunction, nullptr);
    }

}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();
	UE_LOG(LogTemp, Log, TEXT("Shutdown() has been called."));
}