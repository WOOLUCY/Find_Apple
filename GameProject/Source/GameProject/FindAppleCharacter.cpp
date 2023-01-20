// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAppleCharacter.h"
#include "FindAppleAnimInstance.h"
#include "Sword.h"

#include "Kismet/GameplayStatics.h"
#include "FindAppleInterface.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "InputActionValue.h"

#include "Components/InputComponent.h"
#include "Engine/World.h"

// Sets default values
AFindAppleCharacter::AFindAppleCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_HERO
	(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Hero/Char.Char'"));
	if (SK_HERO.Succeeded()) {
		GetMesh()->SetSkeletalMesh(SK_HERO.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	//애니메이션 연결
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_HERO
	(TEXT("/Script/Engine.AnimBlueprint'/Game/Characters/Hero/ABP_Char.ABP_Char_C'"));
	if (ABP_HERO.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(ABP_HERO.Class);
	}


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 500.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

}

// Called when the game starts or when spawned
void AFindAppleCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CharacterMappingContext, 0);
		}
	}

	auto CurEquip = GetWorld()->SpawnActor<ASword>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (CurEquip != nullptr) {
		CurEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandSocket"));
	}
	//FName SwordSocket(TEXT("RightHand"));


}

void AFindAppleCharacter::QuestInteraction(const FInputActionValue & Value)
{
	TArray<AActor*> TalkableActor;

	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UFindAppleInterface::StaticClass(), TalkableActor);

	for (AActor* Actor : TalkableActor)
	{
		IFindAppleInterface* Interface = Cast<IFindAppleInterface>(Actor);

		if (Interface != nullptr)
		{
			if (this->IsOverlappingActor(Actor))
			{
				UE_LOG(LogTemp, Display, TEXT("collised"));
				Interface->Execute_OnActivate(Actor);
			}
		}
	}

}


void AFindAppleCharacter::MoveForward(const FInputActionValue& Value)
{	// Character movement
	const FVector2D DirectionValue = Value.Get<FVector2D>();
	if (Controller && (DirectionValue != FVector2D(0, 0))) {
		FVector DirectionForward = UKismetMathLibrary::GetForwardVector(FRotator(0.f, GetControlRotation().Yaw, 0.f));
		AddMovementInput(DirectionForward, DirectionValue.Y);
	}
}

void AFindAppleCharacter::MoveRight(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();
	if (Controller && (DirectionValue != FVector2D(0, 0))) {
		FVector DirectionRight = UKismetMathLibrary::GetRightVector(FRotator(0.f, GetControlRotation().Yaw, 0.f));
		AddMovementInput(DirectionRight, DirectionValue.X);

	}
}

void AFindAppleCharacter::Look(const FInputActionValue& Value)
{	// Camera movement
	const FVector2D DirectionValue = Value.Get<FVector2D>();
	if (Controller && (DirectionValue != FVector2D(0, 0))) {
		AddControllerYawInput(DirectionValue.X);
		AddControllerPitchInput(DirectionValue.Y);
	}
}


// Called every frame
void AFindAppleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFindAppleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AFindAppleCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AFindAppleCharacter::MoveRight);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFindAppleCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(QuestInteractionAction, ETriggerEvent::Completed, this, &AFindAppleCharacter::QuestInteraction);
	}

	PlayerInputComponent->BindAction(TEXT("Action"),EInputEvent::IE_Pressed, this, &AFindAppleCharacter::Action);

	//PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFindAppleCharacter::MoveRight);
	//PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AFindAppleCharacter::LookUpRate);
	//PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AFindAppleCharacter::LookRightRate);
	//PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}



void AFindAppleCharacter::Action()
{

	auto AnimInst = Cast<UFindAppleAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInst) return;

	AnimInst->PlayActionMontage();

	//소켓일단 여기다 붙혀놓고


	//(X = -2.191723, Y = -7.376023, Z = 0.871590)
	UE_LOG(LogTemp, Warning, TEXT("Action function end"));


}
