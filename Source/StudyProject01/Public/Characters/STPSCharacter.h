// STPSCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "Characters/SCharacter.h"
#include "InputActionValue.h"
#include "STPSCharacter.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT01_API ASTPSCharacter : public ASCharacter
{
	GENERATED_BODY()
	
public:
    ASTPSCharacter();

    virtual void BeginPlay() override;

    float GetForwardInputValue() const { return ForwardInputValue; }

    float GetRightInputValue() const { return RightInputValue; }

    float GetCurrentAimPitch() const { return CurrentAimPitch; }

    float GetCurrentAimYaw() const { return CurrentAimYaw; }

    virtual void Tick(float DeltaSeconds) override;

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void Move(const FInputActionValue& InValue);

    void Look(const FInputActionValue& InValue);

    void Attack(const FInputActionValue& InValue);

    void Fire();

    void ToggleTrigger(const FInputActionValue& InValue);

    void StartFire(const FInputActionValue& InValue);

    void StopFire(const FInputActionValue& InValue);

    void StartIronSight(const FInputActionValue& InValue);

    void EndIronSight(const FInputActionValue& InValue);

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
    TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
    TObjectPtr<class USInputConfigData> PlayerCharacterInputConfigData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
    TObjectPtr<class UInputMappingContext> PlayerCharacterInputMappingContext;

 //   UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess = true))

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess = true))
    TObjectPtr<class UAnimMontage> RifleFireAnimMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess = true))
    TSubclassOf<class UCameraShakeBase> FireShake;

    float ForwardInputValue;

    float RightInputValue;

    float TargetFOV = 70.f;

    float CurrentFOV = 70.f;

    bool bIsTriggerToggle = false;

    float FirePerMinute = 600;

    FTimerHandle BetweenShotsTimer;

    float TimeBetweenFire;

    float CurrentAimPitch = 0.f;

    float CurrentAimYaw = 0.f;

};
