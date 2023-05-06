// Fill out your copyright notice in the Description page of Project Settings.


#include "FindAppleCharacter.h"
#include "FindAppleAnimInstance.h"
#include "Plants/FarmGround.h"
#include "FindAppleGameMode.h"
#include "MyGameInstance.h"



#include "InputMappingContext.h"
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
#include "Inventory/InventoryDataTable.h"
#include "Dialogue/QuestListWidget.h"
#include "Dialogue/TeleportPosition.h"
#include "Teleport/WorldMapWidget.h"
#include "Components/InputComponent.h"
#include "Components/PostProcessComponent.h"
#include "PauseWidget.h"

#include "Teleport/BlackScreenBegin.h"

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
	CurEquipNum = 0;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 500.f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraLagSpeed = 20.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;


	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingConetext
	(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Semin/KeyInput/IMC_MyProject.IMC_MyProject'"));
	if(MappingConetext.Succeeded())
	{
		CharacterMappingContext = MappingConetext.Object;
	}



	static ConstructorHelpers::FObjectFinder<UInputAction> Input_MoveForward(TEXT("InputAction'/Game/Semin/KeyInput/IA_MoveForward.IA_MoveForward'"));
	if (Input_MoveForward.Succeeded())
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
	/* 마우스 토글 키 */
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_MouseToggle(TEXT("InputAction'/Game/Semin/KeyInput/IA_MouseToggle.IA_MouseToggle'"));
	if (Input_MouseToggle.Succeeded())
	{
		MouseToggleAction = Input_MouseToggle.Object;
	}
	/* 월드맵 키 */
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_WorldMap(TEXT("InputAction'/Game/Semin/KeyInput/IA_Map.IA_Map'"));
	if (Input_WorldMap.Succeeded())
	{
		WorldMapAction = Input_WorldMap.Object;
	}
	/* 일시정지 키 */
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Pause(TEXT("/Script/EnhancedInput.InputAction'/Game/Woo/KeyInput/IA_Pause.IA_Pause'"));
	if (Input_Pause.Succeeded())
	{
		PauseAction = Input_Pause.Object;
	}
	/* 퀘스트 스킵 키 (다음으로 바로 넘어감) */
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Skip(TEXT("/Script/EnhancedInput.InputAction'/Game/Semin/KeyInput/IA_Skip.IA_Skip'"));
	if (Input_Skip.Succeeded())
	{
		SkipAction = Input_Skip.Object;
	}
	/* 퀘스트 텔레포트 이동 키 (퀘스트 수행 지역으로 이동) */
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Teleport(TEXT("/Script/EnhancedInput.InputAction'/Game/Semin/KeyInput/IA_Teleport.IA_Teleport'"));
	if (Input_Teleport.Succeeded())
	{
		TeleportAction = Input_Teleport.Object;
	}
	/* 퀘스트 스킵 키 (다음으로 바로 넘어감) */
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_TeleportQuestNPC(TEXT("/Script/EnhancedInput.InputAction'/Game/Semin/KeyInput/IA_QuestNPCTeleport.IA_QuestNPCTeleport'"));
	if (Input_TeleportQuestNPC.Succeeded())
	{
		QuestTeleportAction = Input_TeleportQuestNPC.Object;
	}

	/* 도구 휠 */
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_WheelUp(TEXT("/Script/EnhancedInput.InputAction'/Game/Woo/KeyInput/IA_ToolUp.IA_ToolUp'"));
	if (Input_WheelUp.Succeeded())
	{
		WheelUpAction = Input_WheelUp.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_WheelDown(TEXT("/Script/EnhancedInput.InputAction'/Game/Woo/KeyInput/IA_ToolDown.IA_ToolDown'"));
	if (Input_WheelDown.Succeeded())
	{
		WheelDownAction = Input_WheelDown.Object;
	}


	//kaon - 대쉬, 도구선택
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Dash(TEXT("/Script/EnhancedInput.InputAction'/Game/Semin/KeyInput/IA_Dash.IA_Dash'"));
	if (Input_Dash.Succeeded())
	{
		DashMapping = Input_Dash.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Sword(TEXT("/Script/EnhancedInput.InputAction'/Game/Semin/KeyInput/IA_Sword.IA_Sword'"));
	if (Input_Sword.Succeeded())
	{
		SwordMapping = Input_Sword.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Ax(TEXT("/Script/EnhancedInput.InputAction'/Game/Semin/KeyInput/IA_Ax.IA_Ax'"));
	if (Input_Ax.Succeeded())
	{
		AxMapping = Input_Ax.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Pick(TEXT("/Script/EnhancedInput.InputAction'/Game/Semin/KeyInput/IA_Pick.IA_Pick'"));
	if (Input_Pick.Succeeded())
	{
		PickMapping = Input_Pick.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> Input_Reset(TEXT("/Script/EnhancedInput.InputAction'/Game/Semin/KeyInput/IA_ResetEquip.IA_ResetEquip'"));
	if (Input_Reset.Succeeded())
	{
		ResetEquipMapping = Input_Reset.Object;
	}

	/* CameraShake */
	ConstructorHelpers::FClassFinder<UCameraShakeBase>  CameraShake(TEXT("/Script/Engine.Blueprint'/Game/Woo/Camera/BP_HitCS.BP_HitCS_C'"));
	if (CameraShake.Succeeded())
	{
		HitCameraShakeClass = CameraShake.Class;
	}

	/* Inventory Widget */
	ConstructorHelpers::FClassFinder<UInventoryUW>  InventoryWidget(TEXT("WidgetBlueprint'/Game/Semin/UI/Inventory/UI/BP/WBP_InventoryCPP.WBP_InventoryCPP_C'"));
	if (InventoryWidget.Succeeded())
	{
		InventoryWidgetClass = InventoryWidget.Class;
	}

	/* Quest List Widget */
	//ConstructorHelpers::FClassFinder<UQuestListWidget>  QuestListWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Dialogue/WBP_QuestList.WBP_QuestList_C'"));
	//if (QuestListWidget.Succeeded())
	//{
	//	QuestListWidgetClass = QuestListWidget.Class;
	//}

	/* World Map Widget */
	ConstructorHelpers::FClassFinder<UWorldMapWidget>  WorldMapWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_WorldMap.WBP_WorldMap_C'"));
	if (WorldMapWidget.Succeeded())
	{
		WorldMapWidgetClass = WorldMapWidget.Class;
	}

	/* Pause Menu Widget */
	ConstructorHelpers::FClassFinder<UPauseWidget>  PauseWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Woo/UI/PauseWidget.PauseWidget_C'"));
	if (PauseWidget.Succeeded())
	{
		PauseWidgetClass = PauseWidget.Class;
	}



	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//InventoryComponent
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	static ConstructorHelpers::FObjectFinder<UDataTable> InventoryDataTable(TEXT("/Script/Engine.DataTable'/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable'"));
	if (InventoryDataTable.Succeeded())
	{
		ItemDataTable = InventoryDataTable.Object;
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	/* Post Process Material */
	PostProcessComp = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
	PostProcessComp->SetupAttachment(CameraComponent);

	/* Post Process Effect */
	FPostProcessSettings settings;
	settings.BloomIntensity = 5.f;
	PostProcessComp->Settings = settings;


	/* Combat */
	SetIsAttacked(false);
	SetIsAttacking(false);

	// semin, edit pitch min & max
	if (GetWorld())
	{
		APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
		if (CameraManager)
		{
			CameraManager->ViewPitchMin = -50.0;
			CameraManager->ViewPitchMax = 0.0;
		}
	}

	ConstructorHelpers::FClassFinder<UBlackScreenBegin>  UBlackScreenBeginWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Map/WBP_BlackScreenBegin.WBP_BlackScreenBegin_C'"));
	if (UBlackScreenBeginWidget.Succeeded())
	{
		BlackScreenBeginClass = UBlackScreenBeginWidget.Class;
	}
}



// Called when the game starts or when spawned
void AFindAppleCharacter::BeginPlay()
{
	Super::BeginPlay();

	BlackScreenBeginUIObject = CreateWidget<UBlackScreenBegin>(GetWorld(), BlackScreenBeginClass);
	BlackScreenBeginUIObject->AddToViewport();

	CurHealth = MaxHealth;
	CurHunger = MaxHunger;
	bIsRunning = false;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CharacterMappingContext, 0);
		}
	}

	/* Quest List 위젯 생성, 얘는 항상 Viewport 위에 있음 */
	//QuestListUIObject = CreateWidget<UQuestListWidget>(GetWorld(), QuestListWidgetClass);
	//QuestListUIObject->AddToViewport();
	//if (QuestNum == 0)
	//{
	//	QuestListUIObject->SetVisibility(ESlateVisibility::Hidden);
	//}
	//else
	//{
	//	QuestListUIObject->SetVisibility(ESlateVisibility::Visible);
	//}

	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr) {
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		AFindAppleGameMode* MyMode = Cast<AFindAppleGameMode>(GameMode);

		auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

		if (GameInstance != nullptr) {
			FVector Loc = GameInstance->GetCharLoc();
			if (Loc.Size() != 0) {
				FString LevelName = UGameplayStatics::GetCurrentLevelName(TheWorld);
				FString Name = "MainMap1";
				if (LevelName.Equals(Name)) {

					//UE_LOG(LogTemp, Warning, TEXT("Begin No Zero Play~~"));
					SetActorLocation(GameInstance->GetCharLoc());
				}
			}
			else {
				// 현재 월드 객체의 GetMapName 함수를 호출하여 현재 레벨 이름 가져오기
				UE_LOG(LogTemp, Warning, TEXT("Begin Zero Play~~"));


			}
		}
		if (MyMode != nullptr) {
			MyDelegateHandle = MyMode->DayChangeDelegate.AddUObject(
				this, &AFindAppleCharacter::DayChange);
		}


	}


	if (ItemDataTable != nullptr)
	{
		ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
		TArray<FName> RowNames = ItemDataTable->GetRowNames();

		for (FName RowName : RowNames)
		{
			FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

			if (InventoryRow.BeginningHaveCount != 0) {
				InventoryComponent->AddToInventory(RowName, InventoryRow.BeginningHaveCount);
			}
		}
	}

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

void AFindAppleCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


	//UWorld* TheWorld = GetWorld();
	//if (TheWorld != nullptr) {

	//	auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//	if (GameInstance != nullptr) {
	//		//FVector Loc = GameInstance->GetCharLoc();
	//		FString LevelName = UGameplayStatics::GetCurrentLevelName(TheWorld);
	//		FString Name = "MainMap1";
	//		if (LevelName.Equals(Name)) {
	//			SetActorRotation(FRotator(0, 90.f, 0.f));
	//			GameInstance->SetCharLoc(GetActorLocation()+FVector(0,100.f,0));

	//		}


	//	}


	//}


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
				Interface->Execute_PicUpItem(Actor);
			}
		}
	}
}


void AFindAppleCharacter::MouseToggle(const FInputActionValue& Value)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController->bShowMouseCursor == true )
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}
	else
	{
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
	}
}

void AFindAppleCharacter::ShowWorldMap(const FInputActionValue& Value)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (bWorldMapWidget)
	{
		WorldMapUIObject->RemoveFromParent();
		bWorldMapWidget = false;
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
	}
	else
	{
		WorldMapUIObject = CreateWidget<UWorldMapWidget>(GetWorld(), WorldMapWidgetClass);
		WorldMapUIObject->AddToViewport();
		bWorldMapWidget = true;
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
	}
}

void AFindAppleCharacter::ShowPauseMenu(const FInputActionValue& Value)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//if (bPauseWidget)
	//{
	//	PauseUIObject->RemoveFromParent();
	//	PlayerController->SetPause(!bPauseWidget);
	//	bPauseWidget = false;
	//	PlayerController->SetInputMode(FInputModeGameOnly());
	//	PlayerController->SetShowMouseCursor(false);
	//}
	//else
	//{
	//	PlayerController->SetPause(!bPauseWidget);
	//	PauseUIObject = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);
	//	PauseUIObject->AddToViewport();
	//	bPauseWidget = true;
	//	PlayerController->SetInputMode(FInputModeGameAndUI());
	//	PlayerController->SetShowMouseCursor(true);
	//}

	PlayerController->SetPause(!bPauseWidget);
	PauseUIObject = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);
	PauseUIObject->AddToViewport();
	bPauseWidget = true;
	PlayerController->SetInputMode(FInputModeGameAndUI());
	PlayerController->SetShowMouseCursor(true);
}

void AFindAppleCharacter::SkipQuest(const FInputActionValue& Value)
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
				Interface->Execute_NextDialouge(Actor);
			}
		}
	}
}

void AFindAppleCharacter::Teleport(const FInputActionValue& Value)
{
	TArray<AActor*> TeleportActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATeleportPosition::StaticClass(), Place, TeleportActors);

	{
		for (AActor* Actor : TeleportActors)
		{
			ATeleportPosition* Position = Cast<ATeleportPosition>(Actor);

			if (Position != nullptr)
			{
				FVector Location = Position->GetActorLocation();
				FVector MoveLocationLocal = Location + FVector(0.f, 0.f, 50.f);

				AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				CharacterActor->SetActorRelativeLocation(MoveLocationLocal);
			}
		}
	}
}

void AFindAppleCharacter::TeleportAtQuestNPCAction(const FInputActionValue& Value)
{
	TArray<AActor*> TeleportActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATeleportPosition::StaticClass(), "QuestNPC", TeleportActors);

	{
		for (AActor* Actor : TeleportActors)
		{
			ATeleportPosition* Position = Cast<ATeleportPosition>(Actor);

			if (Position != nullptr)
			{
				FVector Location = Position->GetActorLocation();
				FVector MoveLocationLocal = Location + FVector(0.f, 0.f, 50.f);

				AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				CharacterActor->SetActorRelativeLocation(MoveLocationLocal);
			}
		}
	}
}
 

void AFindAppleCharacter::EquipSword(const FInputActionValue& Value)
{

	//클래스 다 가져와서 있으면 안됨
	//TArray<AActor*> FoundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASword::StaticClass(), FoundActors);

	if (CurEquipNum == 1) return;

	if (CurEquipNum != 0 && CurEquipNum != 1 && isEquipOwn) {
		CurEquipActor->Destroy();
		isEquipOwn = false;
	}
	if (CurEquipNum != 1) {
		CurEquipNum = 1;

		if (ItemDataTable != nullptr)
		{
			ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
			TArray<FName> RowNames = ItemDataTable->GetRowNames();

			for (FName RowName : RowNames)
			{
				FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

				if (InventoryRow.ItemType == 12) {
					//Sword 는 아이템 타입이 12
					if (InventoryComponent->InventoryContent.Find(RowName))
					{
						ASword* ToolActor;
						ToolActor = GetWorld()->SpawnActor<ASword>(ASword::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

						ToolActor->SetMesh(InventoryRow.Mesh3D);
						CurEquipActor = ToolActor;
						CurEquipActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SwordSocket"));
						isEquipOwn = true;
					}
				}
			}
		}

	}

}

void AFindAppleCharacter::EquipAx(const FInputActionValue& Value)
{

	if (CurEquipNum == 2) return;

	if (CurEquipNum != 0 && CurEquipNum != 2 && isEquipOwn) {
		CurEquipActor->Destroy();
		isEquipOwn = false;
	}


	if (CurEquipNum != 2) {
		CurEquipNum = 2;

		if (ItemDataTable != nullptr)
		{
			ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
			TArray<FName> RowNames = ItemDataTable->GetRowNames();

			for (FName RowName : RowNames)
			{
				FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

				if (InventoryRow.ItemType == 10) {
					//AX 는 아이템 타입이 10
					if (InventoryComponent->InventoryContent.Find(RowName))
					{
						AAx* ToolActor;
						ToolActor = GetWorld()->SpawnActor<AAx>(AAx::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

						ToolActor->SetMesh(InventoryRow.Mesh3D);
						CurEquipActor = ToolActor;
						CurEquipActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("AxSocket"));
						isEquipOwn = true;
					}
				}
			}
		}

		//CurEquipActor = GetWorld()->SpawnActor<AAx>(FVector::ZeroVector, FRotator::ZeroRotator);
	}



}
void AFindAppleCharacter::EquipPick(const FInputActionValue& Value)
{
	if (CurEquipNum == 3) return;

	if (CurEquipNum != 0 && CurEquipNum != 3 && isEquipOwn) {
		CurEquipActor->Destroy();
		isEquipOwn = false;
	}

	if (CurEquipNum != 3) {
		CurEquipNum = 3;

		if (ItemDataTable != nullptr)
		{
			ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
			TArray<FName> RowNames = ItemDataTable->GetRowNames();

			for (FName RowName : RowNames)
			{
				FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

				if (InventoryRow.ItemType == 11) {
					//Pick 은 아이템 타입이 11
					if (InventoryComponent->InventoryContent.Find(RowName))
					{
						APick* ToolActor;
						ToolActor = GetWorld()->SpawnActor<APick>(APick::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

						ToolActor->SetMesh(InventoryRow.Mesh3D);
						CurEquipActor = ToolActor;
						CurEquipActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("PickSocket"));
						isEquipOwn = true;
					}
				}
			}
		}
	}

}
void AFindAppleCharacter::EquipReset(const FInputActionValue& Value)
{

	if (CurEquipNum != 0) {
		CurEquipActor->Destroy();
		CurEquipNum = 0;
	}


}




void AFindAppleCharacter::ChangeSpeed(const FInputActionValue& Value)
{
	//여기서 스피드를 바꾸던가 올리던가 어쩌구저쩌구해야함
	// 알겠읍니다

	if (GetIsRunning())	return;		// 이미 달리고 있는 상황이면 그냥 리턴

	// 만약 캐릭터가 달리고 있지 않다면
	// 캐릭터의 속도를 올림
	GetCharacterMovement()->MaxWalkSpeed = 2000.f;

	// TODO: 허기를 감소시킴

	// 일정 시간 이후 속도를 다시 줄임
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			GetCharacterMovement()->MaxWalkSpeed = 600.f;
			SetIsRunning(false);

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), 5.f, false);


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

	//CurHealth -= 0.5f;
	//if (CurHealth < 100) {
	//	UE_LOG(LogTemp, Warning, TEXT("CurHealth<100!!"));

	//}

	// TODO: 실시간으로 허기가 줄어들게

}


void AFindAppleCharacter::ChangeEquipment(int in)
{
	if (CurEquipActor)
		CurEquipActor->Destroy();

	if (in == 1) 
	{
		CurEquipActor = GetWorld()->SpawnActor<ASword>(FVector::ZeroVector, FRotator::ZeroRotator);
		CurEquipActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SwordSocket"));
		
		//CurEquipNum = 1;
	}

	else if (in == 2) 
	{
		CurEquipActor = GetWorld()->SpawnActor<AAx>(FVector::ZeroVector, FRotator::ZeroRotator);
		CurEquipActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("AxSocket"));
		//CurEquipNum = 2;

	}

	else if (in == 3) 
	{

		CurEquipActor = GetWorld()->SpawnActor<APick>(FVector::ZeroVector, FRotator::ZeroRotator);
		CurEquipActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("PickSocket"));
		//CurEquipNum = 3;
	}

	else if (in == 0)
	{
		if (CurEquipActor)
			CurEquipActor->Destroy();
	}
}

void AFindAppleCharacter::BlackScreenPopStart()
{
	BlackScreenBeginUIObject->BeginAnimation();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerController->SetShowMouseCursor(false);

	UE_LOG(LogTemp, Warning, TEXT("MoveLocation: %d %d %d"), MoveLocation.X, MoveLocation.Y, MoveLocation.Z);


	FTimerHandle TimerHandle;
	float BlackScreenBeginTime = 0.8;

	/* 타이머 진행, 위젯이 흐려지는 동안은 이동하지 않도록 잠시 Delay 효과 */
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			this->SetActorRelativeLocation(MoveLocation);
			this->SetActorRelativeRotation(MoveRotation);

			BlackScreenPopEnd();

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}), BlackScreenBeginTime, false);


}

void AFindAppleCharacter::BlackScreenPopEnd()
{
	BlackScreenBeginUIObject->EndAnimation();
}

void AFindAppleCharacter::UpEquip(const FInputActionValue& Value)
{
	// 도구 번호 변환
	int temp = GetEquipNum();

	if (temp + 1 > 3)
	{
		SetEquipNum(0);
	}
	else
		SetEquipNum(++temp);

	ChangeEquipment(GetEquipNum());

	UE_LOG(LogClass, Warning, TEXT("CurEquipNum:%d"), GetEquipNum());
}

void AFindAppleCharacter::DownEquip(const FInputActionValue& Value)
{
	int temp = GetEquipNum();

	if (temp - 1 < 0)
	{
		SetEquipNum(3);
	}
	else
		SetEquipNum(--temp);

	ChangeEquipment(GetEquipNum());

	UE_LOG(LogClass, Warning, TEXT("CurEquipNum:%d"), GetEquipNum());
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
		EnhancedInputComponent->BindAction(MouseToggleAction, ETriggerEvent::Started, this, &AFindAppleCharacter::MouseToggle);
		EnhancedInputComponent->BindAction(WorldMapAction, ETriggerEvent::Started, this, &AFindAppleCharacter::ShowWorldMap);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AFindAppleCharacter::ShowPauseMenu);
		EnhancedInputComponent->BindAction(SkipAction, ETriggerEvent::Started, this, &AFindAppleCharacter::SkipQuest);
		EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Started, this, &AFindAppleCharacter::Teleport);
		EnhancedInputComponent->BindAction(QuestTeleportAction, ETriggerEvent::Started, this, &AFindAppleCharacter::TeleportAtQuestNPCAction);

		//kaon - dash, equipment
		EnhancedInputComponent->BindAction(DashMapping, ETriggerEvent::Triggered, this, &AFindAppleCharacter::ChangeSpeed);
		EnhancedInputComponent->BindAction(SwordMapping, ETriggerEvent::Triggered, this, &AFindAppleCharacter::EquipSword);
		EnhancedInputComponent->BindAction(AxMapping, ETriggerEvent::Triggered, this, &AFindAppleCharacter::EquipAx);
		EnhancedInputComponent->BindAction(PickMapping, ETriggerEvent::Triggered, this, &AFindAppleCharacter::EquipPick);
		EnhancedInputComponent->BindAction(ResetEquipMapping, ETriggerEvent::Triggered, this, &AFindAppleCharacter::EquipReset);

		// W: Wheel Equipment
		EnhancedInputComponent->BindAction(WheelUpAction, ETriggerEvent::Triggered, this, &AFindAppleCharacter::UpEquip);
		EnhancedInputComponent->BindAction(WheelDownAction, ETriggerEvent::Triggered, this, &AFindAppleCharacter::DownEquip);

	}
	PlayerInputComponent->BindAction(TEXT("Action"), EInputEvent::IE_Pressed, this, &AFindAppleCharacter::Action);

}

void AFindAppleCharacter::Action()
{
	if (IsAction) {
		return;
	}
	else {
		if (CurEquipNum != 0 && isEquipOwn) {
			Anim->PlayActionMontage();
			IsAction = true;
		}
	}

	// When Player use Equipment, CurHunger decreases
	if(GetEquipNum() != 0)
		SetCurHunger((GetCurHunger() - 10.f));
}

void AFindAppleCharacter::DayChange()
{
	//여기서 하루 지나가면 초기화되는 정보들 저장하면된다.
	CurHealth = MaxHealth;
}


void AFindAppleCharacter::OnActionMontageEnded(UAnimMontage* Montage, bool bInteruppted)
{
	IsAction = false;
}

float AFindAppleCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 피격 불가 상태로 변경
	SetIsAttacked(true);

	// 체력 변경
	SetCurHealth((GetCurHealth() - Damage));

	// 카메라 쉐이크
	if (HitCameraShakeClass)
	{
		// Camera Shake
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}

	// Log
	UE_LOG(LogClass, Warning, TEXT("Player Is Attacked"));
	UE_LOG(LogClass, Warning, TEXT("Player Current HP: %f"), GetCurHealth());

	// 딜레이 후 피격 가능 상태로 변경
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		{
			SetIsAttacked(false);
		}, 3.f, false);	// 무적 시간

	return Damage;

	//return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

