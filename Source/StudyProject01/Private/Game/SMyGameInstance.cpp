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

    TCHAR TCHARArray[] = TEXT("Hello, Unreal!");
    // UTF-16 인코딩의 문자열을 생성하기 위한 언리얼 표준 문자 타입이 TCHAR.
    // TCHAR 자료형 변수에 문자열을 저장하기 위해서는 TEXT() 매크로를 제공.

    FString String0 = TCHARArray;
    // 문자열을 좀 더 자유롭게 조작하고 싶다면 TCHAR 배열 대신 FString 자료형을 사용하면 됨. 
    // TCHAR 배열을 Wrapping한 헬퍼 클래스가 FString.
    FString String1 = FString(TEXT("Hello, Unreal!"));
    // String0와 String1은 같음.
    UE_LOG(LogTemp, Log, TEXT("String1: %s"), *String1);
    // FString에 Asterisk를 붙혀줘야 TCHAR 배열이 반환됨.

    const TCHAR* TCHARPtr = *String1;
    TCHAR* TCHARDataPtr = String1.GetCharArray().GetData();

    TCHAR TCHARArrayWithSize[100];
    FCString::Strcpy(TCHARArrayWithSize, String1.Len(), *String1);
    // C 문자열 라이브러리에서 제공하는 문자열 처리 함수(strstr(), ...)를 제공하는 클래스 FCString.
    // 다만 사용이 안전하다는건 보장받지 못함.

    if (true == String1.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))
    {
        int32 Index = String1.Find(TEXT("unreal"), ESearchCase::IgnoreCase);
        FString EndString = String1.Mid(Index);
        // "unreal" 문자열이 시작되는 곳에서부터 마지막까지 자름.
        UE_LOG(LogTemp, Log, TEXT("Find unreal: %s"), *EndString);
    }

    int32 IntValue = 32;
    float FloatValue = 3.141592f;

    FString StringWithNumber = FString::Printf(TEXT("int32: %d and float: %f"), IntValue, FloatValue);
    UE_LOG(LogTemp, Log, TEXT("StringWithNumber: %s"), *StringWithNumber);
    FString StringWithFloat = FString::SanitizeFloat(FloatValue);
    // float 자료형의 표준은 상당히 복잡함. 이를 정돈해서 문자열로 바꿔줌.
    UE_LOG(LogTemp, Log, TEXT("StringWithFloat: %s"), *StringWithFloat);
    FString StringWithInt = FString::FromInt(IntValue);
    UE_LOG(LogTemp, Log, TEXT("StringWithInt: %s"), *StringWithInt);

    int32 IntValueFromString = FCString::Atoi(*StringWithInt);
    float FloatValueFromString = FCString::Atof(*StringWithFloat);
    StringWithNumber = FString::Printf(TEXT("int32: %d and float: %f"), IntValueFromString, FloatValueFromString);
    UE_LOG(LogTemp, Log, TEXT("숫자로부터 만든 문자열: %s"), *StringWithNumber);
    // File > Save as ... > Save 버튼 우측 역삼각형 클릭 > Save with Encoding > Encoding에 UTF-8로 지정
    // 이렇게 해야 Output log에 한글이 제대로 출력됨.

    FName KeyName1(TEXT("PELVIS"));
    FName KeyName2(TEXT("pelvis"));
    UE_LOG(LogTemp, Log, TEXT("Compare FName: %s"), KeyName1 == KeyName2 ? TEXT("Same") : TEXT("Different"));

    for (int i = 0; i < 10000; ++i)
    {
        FName SearchInNamePool = FName(TEXT("pelvis"));
        const static FName StaticOnlyOnce(TEXT("pelvis"));
        // FName은 결국 전역 Pool을 조사해보는 작업이 수반됨. 
        // 그래서 static 키워드를 통해서 재조사가 이뤄지지 않게끔 함.
    }
}

void USMyGameInstance::Shutdown()
{
	Super::Shutdown();
}