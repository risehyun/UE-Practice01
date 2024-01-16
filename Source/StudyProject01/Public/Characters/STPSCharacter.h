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

    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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

    UFUNCTION()
    void OnHittedRagdollRestoreTimerElapsed();

    void SpawnLandMine(const FInputActionValue& InValue);

    UFUNCTION(Server, Reliable, WithValidation)
    void SpawnLandMine_Server();

    UFUNCTION(Server, Unreliable) // �� �ι� ������ ������ �Ǳ� ����.
    void UpdateInputValue_Server(const float& InForwardInputValue, const float& InRightInputValue);

    UFUNCTION(Server, Unreliable)
    void UpdateAimValue_Server(const float& InAimPitchValue, const float& InAimYawValue);

    UFUNCTION(Server, Unreliable)
    void PlayAttackMontage_Server();

    UFUNCTION(NetMulticast, Unreliable)
    void PlayAttackMontage_NetMulticast();

    UFUNCTION(Server, Reliable)
    void ApplyDamageAndDrawLine_Server(const FVector& InDrawStart, const FVector& InDrawEnd, class ACharacter* InHittedCharacter, float InDamage, struct FDamageEvent const& InDamageEvent, AController* InEventInstigator, AActor* InDamageCauser);

    UFUNCTION(NetMulticast, Reliable)
    void DrawLine_NetMulticast(const FVector& InDrawStart, const FVector& InDrawEnd);

    UFUNCTION(NetMulticast, Unreliable)
    void PlayRagdoll_NetMulticast();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
    TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
    TObjectPtr<class USInputConfigData> PlayerCharacterInputConfigData;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
    TObjectPtr<class UInputMappingContext> PlayerCharacterInputMappingContext;

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess = true))
    float ForwardInputValue;

    float PreviousForwardInputValue = 0.f;

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess = true))
    float RightInputValue;

    float PreviousRightInputValue = 0.f;



    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess = true))
    TObjectPtr<class UAnimMontage> RifleFireAnimMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess = true))
    TSubclassOf<class UCameraShakeBase> FireShake;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess = true))
    TSubclassOf<class AActor> LandMineClass;

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess = true))
    float CurrentAimPitch = 0.f;

    float PreviousAimPitch = 0.f;

    UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess = true))
    float CurrentAimYaw = 0.f;

    float PreviousAimYaw = 0.f;



    float TargetFOV = 70.f;

    float CurrentFOV = 70.f;

    bool bIsTriggerToggle = false;

    float FirePerMinute = 600;

    FTimerHandle BetweenShotsTimer;

    float TimeBetweenFire;

    float TargetRagDollBlendWeight = 0.f;

    float CurrentRagDollBlendWeight = 0.f;

    bool bIsNowRagdollBlending = false;

    FTimerHandle HittedRagdollRestoreTimer;

    FTimerDelegate HittedRagdollRestoreTimerDelegate;

};
