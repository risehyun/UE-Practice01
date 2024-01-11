// SMyGameInstance.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "SMyGameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSStatTableRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    FSStatTableRow()
    {
    }

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxEXP;

};

UCLASS()
class STUDYPROJECT01_API USMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USMyGameInstance();

	virtual void Init() override;

	virtual void Shutdown() override;

    const UDataTable* GetCharacterStatDataTable() { return CharacterStatDataTable; }

    FSStatTableRow* USMyGameInstance::GetCharacterStatDataTableRow(int32 InLevel);


//	UFUNCTION()
//	void HandlePigeonFlying(const FString& InName, const int32 InID);
//
private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "USGameInstance", Meta = (AllowPrivateAccess))
    class UDataTable* CharacterStatDataTable;

//	UPROPERTY()
//	FString Name;
//
//	UPROPERTY()
//	TObjectPtr<class USPigeon> SerializedPigeon;
//	// 클래스의 헤더 파일을 인클루드 하지 않고, 해당 클래스 이름 앞에 class 키워드를 적는 것을 전방선언이라 함.
//	// 헤더 파일에서 다른 헤더 파일을 참조하면, 다른 헤더 파일이 수정되었을 때 이 헤더 파일도 함께 컴파일 됨.
//	// USPigeon 헤더파일이 변경되더라도 이 헤더파일은 다시 빌드되지 않으므로, 빌드 시간을 단축시킬 수 있다.
//	// 또한 헤더파일들이 서로를 순환 참조하면서 무한 루프에 빠지는 것을 방지할 수도 있다.
//	// 따라서 꼭 필요한 경우가 아니라면 헤더 파일에서 다른 헤더파일을 인클루드 하지 않고 전방선언을 활용함.
//
//	UPROPERTY()
//	TObjectPtr<class USPigeon> SpawnedPigeon;
};
