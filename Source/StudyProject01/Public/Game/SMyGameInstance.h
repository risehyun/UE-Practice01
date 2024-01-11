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
//	// Ŭ������ ��� ������ ��Ŭ��� ���� �ʰ�, �ش� Ŭ���� �̸� �տ� class Ű���带 ���� ���� ���漱���̶� ��.
//	// ��� ���Ͽ��� �ٸ� ��� ������ �����ϸ�, �ٸ� ��� ������ �����Ǿ��� �� �� ��� ���ϵ� �Բ� ������ ��.
//	// USPigeon ��������� ����Ǵ��� �� ��������� �ٽ� ������� �����Ƿ�, ���� �ð��� �����ų �� �ִ�.
//	// ���� ������ϵ��� ���θ� ��ȯ �����ϸ鼭 ���� ������ ������ ���� ������ ���� �ִ�.
//	// ���� �� �ʿ��� ��찡 �ƴ϶�� ��� ���Ͽ��� �ٸ� ��������� ��Ŭ��� ���� �ʰ� ���漱���� Ȱ����.
//
//	UPROPERTY()
//	TObjectPtr<class USPigeon> SpawnedPigeon;
};
