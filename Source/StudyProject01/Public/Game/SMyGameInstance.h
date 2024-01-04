// SMyGameInstance.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SMyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT01_API USMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USMyGameInstance();

	virtual void Init() override;

	virtual void Shutdown() override;

	UFUNCTION()
	void HandlePigeonFlying(const FString& InName, const int32 InID);

private:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	TObjectPtr<class USPigeon> SerializedPigeon;
	// Ŭ������ ��� ������ ��Ŭ��� ���� �ʰ�, �ش� Ŭ���� �̸� �տ� class Ű���带 ���� ���� ���漱���̶� ��.
	// ��� ���Ͽ��� �ٸ� ��� ������ �����ϸ�, �ٸ� ��� ������ �����Ǿ��� �� �� ��� ���ϵ� �Բ� ������ ��.
	// USPigeon ��������� ����Ǵ��� �� ��������� �ٽ� ������� �����Ƿ�, ���� �ð��� �����ų �� �ִ�.
	// ���� ������ϵ��� ���θ� ��ȯ �����ϸ鼭 ���� ������ ������ ���� ������ ���� �ִ�.
	// ���� �� �ʿ��� ��찡 �ƴ϶�� ��� ���Ͽ��� �ٸ� ��������� ��Ŭ��� ���� �ʰ� ���漱���� Ȱ����.

	UPROPERTY()
	TObjectPtr<class USPigeon> SpawnedPigeon;
};
