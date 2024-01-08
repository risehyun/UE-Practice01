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
		// 아무것도 입력하지 않을 때는 로직을 실행하지 않는 방식으로 최적화합니다.
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
	{ // Switch-Case 구문 내에서 Scope를 지정하면 해당 Scope 내에서 변수 선언이 가능해짐.
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

	//// 마우스의 어떤 움직임도 플레이어 의지의 일종이다.
	//const FRotator ControlRotation = GetController()->GetControlRotation();
	//const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
	//// 플레이어의 회전 의지 중 Yaw 성분으로만 전진 방향을 결정하고자 함.

	//// Rotator를 이용해서 Matrix를 만들 수 있다. (기즈모와 동일)
	//// 이 Matrix가 있어야만 UnitAxis를 쓸 수 있다.
	//// p = x, y = y, r = z에 대응 된다.
	//// GetUnitAixs 를 사용하면 3가지 축 중 한가지를 골라서 쓸 수 있다.
	//// 즉, 아래 코드는 x축을 가지고 와서 앞으로 향하는 Forward vector를 취한다는 의미이다.
	//const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//// y축을 가지고 와서 옆으로 향하는 Right Vector를 취한다.
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
	//    // 아까 IMC에서 X에다가 마우스 좌우 값을 넣었음.
	//    AddControllerPitchInput(LookVector.Y);
	//}
}

void ASViewCharacter::ChangeView(const FInputActionValue& InValue)
{

	switch (CurrentViewMode)
	{
	case EViewMode::BackView:
		/* Case 1. 이전에 BackView 시점이었다면

		  BackView는 컨트롤 회전값 == 스프링암 회전값.
		  그러나 QuarterView는 캐릭터의 회전값 == 컨트롤 회전값.
		  따라서 시점 변경 전에 캐릭터의 현재 회전값을 컨트롤 회전에 세팅해둬야 함.
		  안그러면 컨트롤 회전이 일어나면서 현재 캐릭터의 회전값이 스프링암 회전값(컨트롤 회전값)으로 동기화됨.
		*/
		GetController()->SetControlRotation(GetActorRotation());
		DestArmLength = 900.f;
		DestArmRotation = FRotator(-45.f, 0.f, 0.f);
		SetViewMode(EViewMode::QuarterView);

		break;
	case EViewMode::QuarterView:
		/* Case 2. 이전에 QuarterView 시점이었다면

		  컨트롤 회전이 캐릭터 회전에 맞춰져 있을거임.
		  //QuarterView는 현재 스프링암의 회전값을 컨트롤 회전에 세팅해둔 상태에서 시점 변경해야 올바름.
		  BackView에서는 컨트롤 로테이션이 폰의 회전과 동기화되고 폰의 회전이 스프링 암의 회전과 동기화.
		  따라서 스프링 암의 회전을 임의로 설정할 수 없음. 0으로 고정.
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
	DestArmLength = 400.f; // 초기화에서 한 번 지정해줘야 함.
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
		// ControlRotation이 Pawn의 회전과 동기화 -> Pawn의 회전이 SprintArm의 회전 동기화. 이로 인해 SetRotation()이 무의미.

		// 플레이어의 실제 방향은 바뀌지 않고,
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;

		// 카메라의 위치만 변경되도록 함.
		SpringArmComponent->bUsePawnControlRotation = true;
		SpringArmComponent->bDoCollisionTest = true;
		SpringArmComponent->bInheritPitch = true;
		SpringArmComponent->bInheritYaw = true;
		SpringArmComponent->bInheritRoll = false;

		// 카메라의 스프링 암 방향을 우선 회전 시키고, 그 후에 캐릭터 이동을 입력하면
		// 그 순간 회전을 카메라 방향으로 동기화시키기 위해서 true로 설정해준다.
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

		break;

	case EViewMode::QuarterView:
		//SpringArmComponent->TargetArmLength = 900.f;
		//SpringArmComponent->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

		// 쿼터뷰에서는 카메라가 움직이지 않고 고정되어 있기 때문에 
		// 폰을 회전시키지 않도록 모두 false 처리해준다.
		bUseControllerRotationPitch = false;
		bUseControllerRotationYaw = false;
		bUseControllerRotationRoll = false;

		SpringArmComponent->bUsePawnControlRotation = false;
		SpringArmComponent->bDoCollisionTest = false;
		SpringArmComponent->bInheritPitch = false;
		SpringArmComponent->bInheritYaw = false;
		SpringArmComponent->bInheritRoll = false;

		GetCharacterMovement()->bOrientRotationToMovement = false;
		// 현재 컨트롤 로테이션 값이 바로 캐릭터 폰의 방향에 동기화되버리기 때문에
		// 아래 설정을 true로 설정해서 45도 각도로 딱딱 끊어서 이동되는 것을 수정한다.
		// 이렇게 되면 컨트롤러 로테이션 방향으로 일정 각속도를 가지고 부드럽게 회전하도록 해준다.
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

		break;

	case EViewMode::End:
		break;
	default:
		break;
	}
}

