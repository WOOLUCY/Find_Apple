// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAppleCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFindAppleCharacter::AFindAppleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	//PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFindAppleCharacter::MoveForward);
	//PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFindAppleCharacter::MoveRight);
	//PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AFindAppleCharacter::LookUpRate);
	//PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AFindAppleCharacter::LookRightRate);
	//PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void AFindAppleCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AFindAppleCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AFindAppleCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * CameraRotationRate * GetWorld()->GetDeltaSeconds());
}

void AFindAppleCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * CameraRotationRate * GetWorld()->GetDeltaSeconds());
}
