// SAnimInstance.h

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT01_API USAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

    friend class ASRPGCharacter;
	
public:
    USAnimInstance();

    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
    void PlayAttackAnimMontage();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USAnimInstance")
    float CurrentSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USAnimInstance")
    FVector Velocity;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USAnimInstance")
    uint8 bIsFalling : 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USAnimInstance")
    uint8 bIsCrouching : 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USAnimInstance", Meta = (AllowPrivateAccess))
    TObjectPtr<class UAnimMontage> AttackAnimMontage;
};
