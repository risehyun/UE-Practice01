// ASPlayerController.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STUDYPROJECT01_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ASPlayerController();

    class USHUD* GetHUDWidget() const { return HUDWidget; };

    void ToggleMenu();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "ASPlayerController", Meta = (AllowPrivateAccess))
    FText NotificationText;

    void OnOwningCharacterDead();

    UFUNCTION(Client, Reliable)
    void ShowWinnerUI();

    UFUNCTION(Client, Reliable)
    void ShowLooserUI(int32 InRanking);

    UFUNCTION(Client, Reliable)
    void ReturnToLobby();

protected:
    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
    TSubclassOf<class UUserWidget> MenuUIClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
    TObjectPtr<class UUserWidget> MenuUIInstance;

    bool bIsMenuOn = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
    TSubclassOf<class UUserWidget> NotificationTextUIClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
    TSubclassOf<class USGameResultWidget> WinnerUIClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
    TSubclassOf<class USGameResultWidget> LooserUIClass;

private:
    void LeftRight(float InAxisValue);

    UPROPERTY();
    TObjectPtr<class USHUD> HUDWidget;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ASPlayerController", Meta = (AllowPrivateAccess));
    TSubclassOf<class USHUD> HUDWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerController, Meta = (AllowPrivateAccess))
    TSubclassOf<class UUserWidget> CrosshairUIClass;

};
