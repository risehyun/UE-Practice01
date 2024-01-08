// SViewCharacter.cpp


#include "Characters/SViewCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Inputs/SInputConfigData.h"

ASViewCharacter::ASViewCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASViewCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (true == ::IsValid(PlayerController))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (true == ::IsValid(Subsystem))
		{
			Subsystem->AddMappingContext(PlayerCharacterInputMappingContext, 0);
		}
	}
}

void ASViewCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (CurrentViewMode)
	{
	case EViewMode::BackView:
		break;
	case EViewMode::QuarterView:
	{
		// �ƹ��͵� �Է����� ���� ���� ������ �������� �ʴ� ������� ����ȭ�մϴ�.
		if (KINDA_SMALL_NUMBER < DirectionToMove.SizeSquared())
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
			DirectionToMove = FVector::ZeroVector;
		}
		break;
	}
	case EViewMode::End:
		break;
	default:
		break;
	}

	if (KINDA_SMALL_NUMBER < abs(DestArmLength - SpringArmComponent->TargetArmLength))
	{
		SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, DestArmLength, DeltaSeconds, ArmLengthChangeSpeed);
		SpringArmComponent->SetRelativeRotation(FMath::RInterpTo(SpringArmComponent->GetRelativeRotation(), DestArmRotation, DeltaSeconds, ArmRotationChangeSpeed));
	}
}

void ASViewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (true == ::IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->MoveAction, ETriggerEvent::Triggered, this, &ASViewCharacter::Move);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->LookAction, ETriggerEvent::Triggered, this, &ASViewCharacter::Look);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfigData->ChangeViewAction, ETriggerEvent::Started, this, &ASViewCharacter::ChangeView);
	}
}

void ASViewCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D MovementVector = InValue.Get<FVector2D>();

	switch (CurrentViewMode)
	{
	case EViewMode::None:
		break;
	case EViewMode::BackView:
	{ // Switch-Case ���� ������ Scope�� �����ϸ� �ش� Scope ������ ���� ������ ��������.
		const FRotator ControlRotation = GetController()->GetControlRotation();
		const FRotator ControlRotationYaw(0.f, ControlRotation.Yaw, 0.f);

		const FVector ForwardVector = FRotationMatrix(ControlRotationYaw).GetUnitAxis(EAxis::X);
		const FVector RightVector = FRotationMatrix(ControlRotationYaw).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardVector, MovementVector.X);
		AddMovementInput(RightVector, MovementVector.Y);

		break;
	}


	case EViewMode::QuarterView:
		DirectionToMove.X = MovementVector.X;
		DirectionToMove.Y = MovementVector.Y;

		break;

	case EViewMode::End:
		break;
	default:
		AddMovementInput(GetActorForwardVector(), MovementVector.X);
		AddMovementInput(GetActorRightVector(), MovementVector.Y);
		break;
	}

	//// ���콺�� � �����ӵ� �÷��̾� ������ �����̴�.
	//const FRotator ControlRotation = GetController()->GetControlRotation();
	//const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
	//// �÷��̾��� ȸ�� ���� �� Yaw �������θ� ���� ������ �����ϰ��� ��.

	//// Rotator�� �̿��ؼ� Matrix�� ���� �� �ִ�. (������ ����)
	//// �� Matrix�� �־�߸� UnitAxis�� �� �� �ִ�.
	//// p = x, y = y, r = z�� ���� �ȴ�.
	//// GetUnitAixs �� ����ϸ� 3���� �� �� �Ѱ����� ��� �� �� �ִ�.
	//// ��, �Ʒ� �ڵ�� x���� ������ �ͼ� ������ ���ϴ� Forward vector�� ���Ѵٴ� �ǹ��̴�.
	//const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//// y���� ������ �ͼ� ������ ���ϴ� Right Vector�� ���Ѵ�.
	//const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//AddMovementInput(ForwardVector, MovementVector.X);
	//AddMovementInput(RightVector, MovementVector.Y);
}

void ASViewCharacter::Look(const FInputActionValue& InValue)
{
	FVector2D LookVector = InValue.Get<FVector2D>();

	switch (CurrentViewMode)
	{
	case EViewMode::BackView:
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
		break;
	case EViewMode::QuarterView:
		break;
	case EViewMode::End:
		break;
	default:
		break;
	}

	//if (nullptr != GetController())
	//{
	//    FVector2D LookVector = InValue.Get<FVector2D>();

	//    AddControllerYawInput(LookVector.X);
	//    // �Ʊ� IMC���� X���ٰ� ���콺 �¿� ���� �־���.
	//    AddControllerPitchInput(LookVector.Y);
	//}
}

void ASViewCharacter::ChangeView(const FInputActionValue& InValue)
{

	switch (CurrentViewMode)
	{
	case EViewMode::BackView:
		/* Case 1. ������ BackView �����̾��ٸ�

		  BackView�� ��Ʈ�� ȸ���� == �������� ȸ����.
		  �׷��� QuarterView�� ĳ������ ȸ���� == ��Ʈ�� ȸ����.
		  ���� ���� ���� ���� ĳ������ ���� ȸ������ ��Ʈ�� ȸ���� �����ص־� ��.
		  �ȱ׷��� ��Ʈ�� ȸ���� �Ͼ�鼭 ���� ĳ������ ȸ������ �������� ȸ����(��Ʈ�� ȸ����)���� ����ȭ��.
		*/
		GetController()->SetControlRotation(GetActorRotation());
		DestArmLength = 900.f;
		DestArmRotation = FRotator(-45.f, 0.f, 0.f);
		SetViewMode(EViewMode::QuarterView);

		break;
	case EViewMode::QuarterView:
		/* Case 2. ������ QuarterView �����̾��ٸ�

		  ��Ʈ�� ȸ���� ĳ���� ȸ���� ������ ��������.
		  //QuarterView�� ���� ���������� ȸ������ ��Ʈ�� ȸ���� �����ص� ���¿��� ���� �����ؾ� �ùٸ�.
		  BackView������ ��Ʈ�� �����̼��� ���� ȸ���� ����ȭ�ǰ� ���� ȸ���� ������ ���� ȸ���� ����ȭ.
		  ���� ������ ���� ȸ���� ���Ƿ� ������ �� ����. 0���� ����.
		*/
		GetController()->SetControlRotation(FRotator::ZeroRotator);
		DestArmLength = 400.f;
		DestArmRotation = FRotator::ZeroRotator;
		SetViewMode(EViewMode::BackView);

		break;
	case EViewMode::End:
		break;
	default:
		break;
	}

}

void ASViewCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//SetViewMode(EViewMode::QuarterView);
	SetViewMode(EViewMode::BackView);
	DestArmLength = 400.f; // �ʱ�ȭ���� �� �� ��������� ��.
	DestArmRotation = FRotator::ZeroRotator;
}

void ASViewCharacter::SetViewMode(EViewMode InViewMode)
{
	if (CurrentViewMode == InViewMode)
	{
		return;
	}

	CurrentViewMode = InViewMode;

	switch (CurrentViewMode)
	{
	case EViewMode::BackView:
		//SpringArmComponent->TargetArmLength = 400.f;
		//SpringArmComponent->SetRelativeRotation(FRotator::ZeroRotator);
		// ControlRotation�� Pawn�� ȸ���� ����ȭ -> Pawn�� ȸ���� SprintArm�� ȸ�� ����ȭ. �̷� ���� SetRotation()�� ���ǹ�.

		// �÷��̾��� ���� ������ �ٲ��� �ʰ�,
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;

		// ī�޶��� ��ġ�� ����ǵ��� ��.
		SpringArmComponent->bUsePawnControlRotation = true;
		SpringArmComponent->bDoCollisionTest = true;
		SpringArmComponent->bInheritPitch = true;
		SpringArmComponent->bInheritYaw = true;
		SpringArmComponent->bInheritRoll = false;

		// ī�޶��� ������ �� ������ �켱 ȸ�� ��Ű��, �� �Ŀ� ĳ���� �̵��� �Է��ϸ�
		// �� ���� ȸ���� ī�޶� �������� ����ȭ��Ű�� ���ؼ� true�� �������ش�.
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

		break;

	case EViewMode::QuarterView:
		//SpringArmComponent->TargetArmLength = 900.f;
		//SpringArmComponent->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

		// ���ͺ信���� ī�޶� �������� �ʰ� �����Ǿ� �ֱ� ������ 
		// ���� ȸ����Ű�� �ʵ��� ��� false ó�����ش�.
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;

		SpringArmComponent->bUsePawnControlRotation = false;
		SpringArmComponent->bDoCollisionTest = false;
		SpringArmComponent->bInheritPitch = false;
		SpringArmComponent->bInheritYaw = false;
		SpringArmComponent->bInheritRoll = false;

		GetCharacterMovement()->bOrientRotationToMovement = false;
		// ���� ��Ʈ�� �����̼� ���� �ٷ� ĳ���� ���� ���⿡ ����ȭ�ǹ����� ������
		// �Ʒ� ������ true�� �����ؼ� 45�� ������ ���� ��� �̵��Ǵ� ���� �����Ѵ�.
		// �̷��� �Ǹ� ��Ʈ�ѷ� �����̼� �������� ���� ���ӵ��� ������ �ε巴�� ȸ���ϵ��� ���ش�.
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

		break;

	case EViewMode::End:
		break;
	default:
		break;
	}
}
