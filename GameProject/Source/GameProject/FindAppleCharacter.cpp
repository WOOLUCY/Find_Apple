// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAppleCharacter.h"
#include "FindAppleAnimInstance.h"
#include "Sword.h"
#include "Ax.h"
#include "FarmGround.h"


#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "FindAppleInterface.h"
#include "InputActionValue.h"
#include "Inventory/InventoryUW.h"
#include "Inventory/InventoryComponent.h"
#include "Components/InputComponent.h"

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


	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_HERO
	(TEXT("/Script/Engine.AnimBlueprint'/Game/Characters/Hero/ABP_Char.ABP_Char_C'"));

	if (ABP_HERO.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(ABP_HERO.Class);
	}

	IsAction = false;
	CurEqip = 0;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 500.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_MoveForward(TEXT("InputAction'/Game/Semin/KeyInput/IA_MoveForward.IA_MoveForward'"));
	{
		MoveForwardAction = Input_MoveForward.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_MoveRight(TEXT("InputAction'/Game/Semin/KeyInput/IA_MoveRight.IA_MoveRight'"));
	if (Input_MoveRight.Succeeded())
	{
		MoveRightAction = Input_MoveRight.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Look(TEXT("InputAction'/Game/Semin/KeyInput/IA_Look.IA_Look'"));
	if (Input_Look.Succeeded())
	{
		LookAction = Input_Look.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_QuestInteraction(TEXT("InputAction'/Game/Semin/KeyInput/IA_QuestInteraction.IA_QuestInteraction'"));
	if (Input_QuestInteraction.Succeeded())
	{
		QuestInteractionAction = Input_QuestInteraction.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Inventory(TEXT("InputAction'/Game/Semin/KeyInput/IA_Inventory.IA_Inventory'"));
	if (Input_Inventory.Succeeded())
	{
		InventoryAction = Input_Inventory.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Jump(TEXT("InputAction'/Game/Semin/KeyInput/IA_Jump.IA_Jump'"));
	if (Input_Jump.Succeeded())
	{
		JumpAction = Input_Jump.Object;
	}
	/* 아이템 줍기 키 */
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_PickUp(TEXT("InputAction'/Game/Semin/KeyInput/IA_PickItem.IA_PickItem'"));
	if (Input_PickUp.Succeeded())
	{
		PickItemAction = Input_PickUp.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Dash(TEXT("InputAction'/Game/Semin/KeyInput/IA_Jump.IA_Jump'"));
	if (Input_Dash.Succeeded())
	{
		DashMapping = Input_Dash.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Equip(TEXT("InputAction'/Game/Semin/KeyInput/IA_Jump.IA_Jump'"));
	if (Input_Equip.Succeeded())
	{
		EquipChoicMapping = Input_Equip.Object;
	}


	
	/* Inventory Widget */
	ConstructorHelpers::FClassFinder<UInventoryUW>  InventoryWidget(TEXT("WidgetBlueprint'/Game/Semin/UI/Inventory/UI/BP/WBP_InventoryCPP.WBP_InventoryCPP_C'"));
	if (InventoryWidget.Succeeded())
	{
		InventoryWidgetClass = InventoryWidget.Class;
	}

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//InventoryComponent
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

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

	//auto CurEquip = GetWorld()->SpawnActor<ASword>(FVector::ZeroVector, FRotator::ZeroRotator);

}

void AFindAppleCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Anim = Cast<UFindAppleAnimInstance>(GetMesh()->GetAnimInstance());
	Anim->OnMontageEnded.AddDynamic(this, &AFindAppleCharacter::OnActionMontageEnded);

	
	
	
	

}

void AFindAppleCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AFindAppleCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

}

void AFindAppleCharacter::QuestInteraction(const FInputActionValue& Value)
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

void AFindAppleCharacter::Inventory(const FInputActionValue& Value)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if ( bInventoryWidget ) 
	{
		InventoryUIObject->RemoveFromParent();
		bInventoryWidget = false;
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}
	else  
	{
		InventoryUIObject = CreateWidget<UInventoryUW>(GetWorld(), InventoryWidgetClass);
		InventoryUIObject->AddToViewport();
		bInventoryWidget = true;
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
	}
}

void AFindAppleCharacter::PickItem(const FInputActionValue& Value)
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
				Interface->Execute_PicUpItem(Actor);
			}
		}
	}
}

void AFindAppleCharacter::EquipSword(const FInputActionValue& Value)
{
	CurEqip = 1;
	auto CurEquip = GetWorld()->SpawnActor<ASword>(FVector::ZeroVector, FRotator::ZeroRotator);

	if (CurEquip != nullptr) {
		CurEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SwordSocket"));
	}

}

void AFindAppleCharacter::EquipAx(const FInputActionValue& Value)
{
	CurEqip = 2;
	auto CurEquip = GetWorld()->SpawnActor<AAx>(FVector::ZeroVector, FRotator::ZeroRotator);

	if (CurEquip != nullptr) {
		CurEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("AxSocket"));
	}


}
void AFindAppleCharacter::EquipPick(const FInputActionValue& Value)
{
	CurEqip = 3;
	auto CurEquip = GetWorld()->SpawnActor<AAx>(FVector::ZeroVector, FRotator::ZeroRotator);

	if (CurEquip != nullptr) {
		CurEquip->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SwordSocket"));
	}


}
void AFindAppleCharacter::EquipReset(const FInputActionValue& Value)
{
	CurEqip = 0;
 

}


void AFindAppleCharacter::ChangeSpeed(const FInputActionValue& Value)
{
	//여기서 스피드를 바꾸던가 올리던가 어쩌구저쩌구해야함
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
		EnhancedInputComponent->BindAction(QuestInteractionAction, ETriggerEvent::Started, this, &AFindAppleCharacter::QuestInteraction);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AFindAppleCharacter::Inventory);
		EnhancedInputComponent->BindAction(PickItemAction, ETriggerEvent::Started, this, &AFindAppleCharacter::PickItem);
		
	//	EnhancedInputComponent->BindAction(DashMapping, ETriggerEvent::Triggered, this, &AFindAppleCharacter::ChangeSpeed);
		//EnhancedInputComponent->BindAction(EquipChoicMapping, ETriggerEvent::Triggered, this, &AFindAppleCharacter::ChangeEqip);

	}
	PlayerInputComponent->BindAction(TEXT("Action"), EInputEvent::IE_Pressed, this, &AFindAppleCharacter::Action);

	//PlayerInputComponent->BindAction(TEXT("EquipAx"), EInputEvent::IE_Pressed, this, &AFindAppleCharacter::EquipAx);

	//PlayerInputComponent->KeyBindings()
//	PlayerInputComponent->BindKey(EKeys::M, IE_Pressed, this, &AFindAppleCharacter::Test);
}

void AFindAppleCharacter::Action()
{
	if (IsAction) {
		return;
	}
	else {
		Anim->PlayActionMontage();
		IsAction = true;
	}


}



void AFindAppleCharacter::OnActionMontageEnded(UAnimMontage* Montage, bool bInteruppted)
{
	IsAction = false;
}

void AFindAppleCharacter::ActionPlant()
{//??d이거 왜썻지...
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Action Plant Delegate"));

}
