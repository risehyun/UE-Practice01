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

    TCHAR TCHARArray[] = TEXT("Hello, Unreal!");
    // UTF-16 ���ڵ��� ���ڿ��� �����ϱ� ���� �𸮾� ǥ�� ���� Ÿ���� TCHAR.
    // TCHAR �ڷ��� ������ ���ڿ��� �����ϱ� ���ؼ��� TEXT() ��ũ�θ� ����.

    FString String0 = TCHARArray;
    // ���ڿ��� �� �� �����Ӱ� �����ϰ� �ʹٸ� TCHAR �迭 ��� FString �ڷ����� ����ϸ� ��. 
    // TCHAR �迭�� Wrapping�� ���� Ŭ������ FString.
    FString String1 = FString(TEXT("Hello, Unreal!"));
    // String0�� String1�� ����.
    UE_LOG(LogTemp, Log, TEXT("String1: %s"), *String1);
    // FString�� Asterisk�� ������� TCHAR �迭�� ��ȯ��.

    const TCHAR* TCHARPtr = *String1;
    TCHAR* TCHARDataPtr = String1.GetCharArray().GetData();

    TCHAR TCHARArrayWithSize[100];
    FCString::Strcpy(TCHARArrayWithSize, String1.Len(), *String1);
    // C ���ڿ� ���̺귯������ �����ϴ� ���ڿ� ó�� �Լ�(strstr(), ...)�� �����ϴ� Ŭ���� FCString.
    // �ٸ� ����� �����ϴٴ°� ������� ����.

    if (true == String1.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))
    {
        int32 Index = String1.Find(TEXT("unreal"), ESearchCase::IgnoreCase);
        FString EndString = String1.Mid(Index);
        // "unreal" ���ڿ��� ���۵Ǵ� ���������� ���������� �ڸ�.
        UE_LOG(LogTemp, Log, TEXT("Find unreal: %s"), *EndString);
    }

    int32 IntValue = 32;
    float FloatValue = 3.141592f;

    FString StringWithNumber = FString::Printf(TEXT("int32: %d and float: %f"), IntValue, FloatValue);
    UE_LOG(LogTemp, Log, TEXT("StringWithNumber: %s"), *StringWithNumber);
    FString StringWithFloat = FString::SanitizeFloat(FloatValue);
    // float �ڷ����� ǥ���� ����� ������. �̸� �����ؼ� ���ڿ��� �ٲ���.
    UE_LOG(LogTemp, Log, TEXT("StringWithFloat: %s"), *StringWithFloat);
    FString StringWithInt = FString::FromInt(IntValue);
    UE_LOG(LogTemp, Log, TEXT("StringWithInt: %s"), *StringWithInt);

    int32 IntValueFromString = FCString::Atoi(*StringWithInt);
    float FloatValueFromString = FCString::Atof(*StringWithFloat);
    StringWithNumber = FString::Printf(TEXT("int32: %d and float: %f"), IntValueFromString, FloatValueFromString);
    UE_LOG(LogTemp, Log, TEXT("���ڷκ��� ���� ���ڿ�: %s"), *StringWithNumber);
    // File > Save as ... > Save ��ư ���� ���ﰢ�� Ŭ�� > Save with Encoding > Encoding�� UTF-8�� ����
    // �̷��� �ؾ� Output log�� �ѱ��� ����� ��µ�.

    FName KeyName1(TEXT("PELVIS"));
    FName KeyName2(TEXT("pelvis"));
    UE_LOG(LogTemp, Log, TEXT("Compare FName: %s"), KeyName1 == KeyName2 ? TEXT("Same") : TEXT("Different"));

    for (int i = 0; i < 10000; ++i)
    {
        FName SearchInNamePool = FName(TEXT("pelvis"));
        const static FName StaticOnlyOnce(TEXT("pelvis"));
        // FName�� �ᱹ ���� Pool�� �����غ��� �۾��� ���ݵ�. 
        // �׷��� static Ű���带 ���ؼ� �����簡 �̷����� �ʰԲ� ��.
    }
}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();
}