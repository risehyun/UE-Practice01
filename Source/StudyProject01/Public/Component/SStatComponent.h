// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfCurrentHPDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentHPChangeDelegate, float, InOldCurrentHP, float, InNewCurrentHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMaxHPChangeDelegate, float, InOldMaxHP, float, InNewMaxHP);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STUDYPROJECT01_API USStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USStatComponent();

	virtual void BeginPlay() override;

	float GetMaxHP() const { return MaxHP; }

	void SetMaxHP(float InMaxHP);

	float GetCurrentHP() const { return CurrentHP; }

	void SetCurrentHP(float InCurrentHP);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnOutOfCurrentHPDelegate OnOutOfCurrentHPDelegate;

	FOnCurrentHPChangeDelegate OnCurrentHPChangeDelegate;

	FOnMaxHPChangeDelegate OnMaxHPChangeDelegate;
		
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "USStatComponent", Meta = (AllowPrivateAccess))
	TObjectPtr<class USMyGameInstance> GameInstance;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "USStatComponent", Meta = (AllowPrivateAccess))
	float MaxHP;

	// <Transient>
	// 속성들 중에 현재 값을 저장할 때가 있다.
	// 그런데 이 현재 값이라는건 순간마다 값이 바뀔 수 있기 때문에
	// 직렬화를 하는 경우 매번 다시 직렬화를 해줘야 한다.
	// 따라서 메모리를 차지하고 성능상의 이점들을 악화시킬 수 있는 이런 요소를 배제하기 위해 따로 쓴다.

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "USStatComponent", Meta = (AllowPrivateAccess))
	float CurrentHP;
};
