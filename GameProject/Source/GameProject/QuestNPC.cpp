// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNPC.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "FindAppleGameMode.h"
#include "Dialogue/DialogueDataStruct.h"
#include "Dialogue/QuestListWidget.h"
#include "Dialogue/DialogueWidget.h"
#include "Dialogue/BlackScreenPop.h"
#include "Dialogue/QuestListTextWidget.h"
#include "Inventory/InventoryDataTable.h"
#include "Inventory/InventoryComponent.h"
#include "Components/WrapBox.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/TextBlock.h"
#include "Components/TimelineComponent.h"
#include "Components/ScrollBox.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "FindAppleCharacter.h"


// Sets default values
AQuestNPC::AQuestNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* �ؽ�Ʈ ���� */
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PressQ"));
	Text->SetupAttachment(GetRootComponent());
	Text->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
	Text->SetTextRenderColor(FColor::White);
	Text->SetWorldSize(110.f);
	Text->SetHorizontalAlignment(EHTA_Center);
	Text->SetText(FText::FromString(TEXT("!")));

	/* Set Mesh ( ĳ���� ���̷��� �޽� ) */
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_NPC(TEXT("SkeletalMesh'/Game/Semin/Character/SKM_NPC.SKM_NPC'"));
	if (SK_NPC.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_NPC.Object);
	}

	/* ��ȭ �� �÷��̾� ��ġ ������ ��(����) �޽� */
	MyCone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone"));
	MyCone->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	if (ConeMesh.Succeeded())
	{
		MyCone->SetStaticMesh(ConeMesh.Object);
		MyCone->SetRelativeLocationAndRotation(FVector(180.f, 0.f, 0.f), FRotator(0.f, 180.f, 0.f));
		MyCone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MyCone->SetHiddenInGame(true);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance>  BP_Anim(TEXT("/Script/Engine.AnimBlueprint'/Game/Semin/Character/NPC/ABP_NPC.ABP_NPC_C'"));
	if (BP_Anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(BP_Anim.Class);
	}


	/* Quest System - Item Data Table */
	static ConstructorHelpers::FObjectFinder<UDataTable> InventoryDataTable(TEXT("/Game/Semin/UI/Inventory/InventoryDataTable.InventoryDataTable"));
	if (InventoryDataTable.Succeeded())
	{
		ItemDataTable = InventoryDataTable.Object;
	}
	/* Quest List -> My Character�� �߰��ϱ� �뵵 */
	ConstructorHelpers::FClassFinder<UQuestListTextWidget>  QuestListTextWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Dialogue/WBP_QuestListText.WBP_QuestListText_C'"));
	if (QuestListTextWidget.Succeeded())
	{
		QuestListTextWidgetClass = QuestListTextWidget.Class;
	}
	/* Dialogue Widgets */
	ConstructorHelpers::FClassFinder<UDialogueWidget>  DialogueWidget(TEXT("WidgetBlueprint'/Game/Semin/UI/Dialogue/WBP_Dialogue.WBP_Dialogue_C'"));
	if (DialogueWidget.Succeeded())
	{
		DialogueWidgetClass = DialogueWidget.Class;
	}
	ConstructorHelpers::FClassFinder<UBlackScreenPop>  DialoguePopWidgetObject(TEXT("WidgetBlueprint'/Game/Semin/UI/Dialogue/WBP_BlackScreenPop.WBP_BlackScreenPop_C'"));
	if (DialoguePopWidgetObject.Succeeded())
	{
		DialoguePopWidgetClass = DialoguePopWidgetObject.Class;
	}
	/* Press key Widget */
	ConstructorHelpers::FClassFinder<UUserWidget>  PressKeyWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Semin/UI/Dialogue/WBP_PressQ.WBP_PressQ_C'"));
	if (PressKeyWidget.Succeeded())
	{
		PressKeyWidgetClass = PressKeyWidget.Class;
	}

	ConstructorHelpers::FObjectFinder<UCurveFloat>  CurveObject(TEXT("CurveFloat'/Game/Semin/UI/Dialogue/BlackScreenTimeline.BlackScreenTimeline'"));
	if (CurveObject.Succeeded())
	{
		CurveFloat = CurveObject.Object;
	}

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	//CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetRelativeLocationAndRotation(FVector(187.f, 178.f, 0.f), FRotator(0.f, -110.f, 0.f));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.f), FRotator(0.0f, 270.0f, 0.0f));

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->SetRelativeLocationAndRotation(FVector(0.1f, 100.f, 70.f), FRotator(0.f, 0.f, 0.f));
	CollisionMesh->SetBoxExtent(FVector(130.f, 130.f, 32.f));
	CollisionMesh->SetupAttachment(GetMesh());
	 

	static ConstructorHelpers::FObjectFinder<UDataTable> DialogueDataTable(TEXT("/Game/Semin/UI/CPP_Dialogue_File.CPP_Dialogue_File"));
	if (DialogueDataTable.Succeeded())
	{
		DialogueDatatable = DialogueDataTable.Object;
	}


	//GetMesh()->SetAnimClass()
}

// Called when the game starts or when spawned
void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &AQuestNPC::OnOverlapEnd);
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AQuestNPC::OnOverlapBegin);

	if (DialogueDatatable != nullptr)
	{
		DialogueDatatable->GetAllRows<FDialogueTableRow>(TEXT("GetAllRows"), DialogueData);
		TArray<FName> RowNames = DialogueDatatable->GetRowNames();

		for (int i = 0; i < RowNames.Num(); i++)
		{
			FDialogueTableRow Dialogue = *(DialogueDatatable->FindRow<FDialogueTableRow>(RowNames[i], RowNames[i].ToString()));
			if (NPC_ID == Dialogue.NPC_ID) {
				MyDialogue.Add(RowNames[i]);
			}
		}
	}
}

void AQuestNPC::DialogueGetLine()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	TArray<FText> ReturnLines;

	/* FindAppleCharacter�� Cast */
	AActor* ActorItr = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(ActorItr);

	for ( FName CurDialogue : MyDialogue )
	{
		if (QuestAccept == false)
		{
			FDialogueTableRow Dialogue = *(DialogueDatatable->FindRow<FDialogueTableRow>(CurDialogue, CurDialogue.ToString()));
			if (Conversation_ID == Dialogue.Conversation_ID && CurrentLine == Dialogue.Line_ID)
			{
				MyNameText = Dialogue.NPC_Name;
				ReturnLines.Add(Dialogue.Dialogue);
				if (ReturnLines.Num() == 1)
				{
					if (!ReturnLines[0].IsEmpty())
					{
						DialogueUIObject->ChangeText(MyNameText, ReturnLines[0]);

						Text->SetText(FText::FromString(TEXT("!")));

						/* ���� ���� ����Ʈ �ʿ� ������ ����Ʈ�� �ִٸ� ( ĳ���Ͱ� NPC���� ��� �ϴ� �� ) */
						if (!QuestRequirItem.IsEmpty()) 
						{
							//UE_LOG(LogTemp, Warning,TEXT("Quest Item Need"));
							MyCharacter->InventoryComponent->RemoveFromInventory(QuestRequirItemName, QuestRequirItemCnt);
							QuestRequirItem.Remove(QuestRequirItemName);
						}

						if (!Dialogue.Conditions_Item.IsNone())	/* ���� �� ��ȭ�� ����Ʈ��� (�ʿ� ������ ����) */
						{
							/* ���� ��ȭ�� ���� ����Ʈ ������ �ʿ�� �����ٸ� */
							if (SetQuestList == false) 
							{
								/* ����Ʈ ����Ʈ ��� */
								MyCharacter->QuestListUIObject->SetVisibility(ESlateVisibility::Visible);

								/* ����Ʈ ����Ʈ�� �ش� ����Ʈ �߰� */
								QuestListTextUIObject = CreateWidget<UQuestListTextWidget>(GetWorld(), QuestListTextWidgetClass);
								QuestListTextUIObject->QuestTitle->SetText(Dialogue.QuestTitle);
								QuestListTextUIObject->QuestDes->SetText(Dialogue.QuestDes);
								MyCharacter->QuestListUIObject->ScrollBox->AddChild(QuestListTextUIObject);
								SetQuestList = true;

								/* ĳ������ ����Ʈ ���� �ϳ� ���� */
								MyCharacter->QuestNum += 1;

								/* ����Ʈ ������ ���� �߰� */
								QuestRequirItem.Add(Dialogue.Conditions_Item, Dialogue.Conditions_cnt);
								QuestRequirItemName = Dialogue.Conditions_Item;
								QuestRequirItemCnt = Dialogue.Conditions_cnt;
							}


							/* ����Ʈ �޾��� ���� �� ������ ��Ȳ �˻�, ���� �̹� ������ �ִٸ� �ٷ� ����Ʈ �Ϸ� */
							if (ItemDataTable != nullptr)
							{
								ItemDataTable->GetAllRows<FInventoryTableRow>(TEXT("GetAllRows"), InventoryData);
								TArray<FName> RowNames = ItemDataTable->GetRowNames();

								for (FName RowName : RowNames)
								{
									//FInventoryTableRow InventoryRow = *(ItemDataTable->FindRow<FInventoryTableRow>(RowName, RowName.ToString()));

									if (RowName == Dialogue.Conditions_Item)		/* �̹� ������ �ִ� �������̶�� ?�� �߰� */
									{
										if (MyCharacter->InventoryComponent->InventoryContent.Find(Dialogue.Conditions_Item))
										{
											if (*MyCharacter->InventoryComponent->InventoryContent.Find(Dialogue.Conditions_Item) >= Dialogue.Conditions_cnt)
											{
												GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, TEXT("I Have Quest Item !!"));
												Text->SetText(FText::FromString(TEXT("?")));
												Conversation_ID += 1;
												CurrentLine = 0;

												Text->SetHiddenInGame(false);
												QuestAccept = true;
											}
											else
											{
												Text->SetText(FText::FromString(TEXT("!")));
											}
										}
									}
								}
							}
						}

						return;
					}
				}
			}
		}
	}

	if (ReturnLines.IsEmpty()) {
		bIsValid = false;
		DialogueUIObject->RemoveFromParent();
		DialoguePopWidget->RemoveFromParent();
		CurrentLine = 0;

		PlayerController->SetViewTargetWithBlend(MyCharacter->CameraComponent->GetOwner(), 1.3f);

		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);

		PlayerController->GetCharacter()->GetCharacterMovement()->SetActive(true);


		QuestAccept = false;
		SetQuestList = false;
		Text->SetHiddenInGame(false);
	}

	//if (!ReturnLines[CurrentLine].IsEmpty())
	//{
	//	DialogueUIObject->ChangeText(ReturnLines[CurrentLine], MyNameText);
	//}
	//else 
	//{
	//	DialogueUIObject->RemoveFromParent();
	//	DialogueUIObject = nullptr;
	//	CurrentLine = 0;
	//}


}

void AQuestNPC::DialogueCreate() 
{
	if (bIsValid)	// Widget is 'not' valid !!
	{
		DialogueGetLine();
	}
	else 
	{
		if (DialogueWidgetClass)
		{
			bIsValid = true;
			DialogueUIObject = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
			DialogueUIObject->AddToViewport();
			DialogueGetLine();
		}
	}

}

void AQuestNPC::PlayerAdjustmentss()
{
	/* �÷��̾� ��Ʈ�ѷ� ������ ���� */
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeUIOnly());

	/* ���� ���� */
	DialoguePopWidget = CreateWidget(GetWorld(), DialoguePopWidgetClass);
	DialoguePopWidget->AddToViewport();

	/* 2�� ���� */
	FTimerHandle GravityTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle, FTimerDelegate::CreateLambda([&]()	// Ÿ�̸� 2��
		{ GetWorld()->GetTimerManager().ClearTimer(GravityTimerHandle);}), 0.2f, false);	// �ݺ��Ϸ��� false�� true�� ����

	/* �÷��̾��� ī�޶� ���� */
	PlayerController->SetViewTargetWithBlend(CameraComponent->GetOwner(), 2.f);

	/* �÷��̾� ��ġ �̵� */
	
	/* Ŀ�� ��� */
	if (CurveFloat)
	{
		FVector Forward = GetActorForwardVector();

		FOnTimelineFloat TimelineProgress;
		FOnTimelineEvent LerpTimelineFinishedCallback;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		LerpTimelineFinishedCallback.BindUFunction(this, FName("TimelineFinished"));

		CurveFTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveFTimeline.SetTimelineFinishedFunc(LerpTimelineFinishedCallback);
		StartLoc = PlayerController->GetCharacter()->GetActorLocation(); 
		EndLoc = MyCone->GetComponentLocation();

		StartRot = PlayerController->GetCharacter()->GetActorRotation();
		EndRot = MyCone->GetComponentRotation();

		CurveFTimeline.SetTimelineLength(1.f);

		CurveFTimeline.PlayFromStart();
	}

}

void AQuestNPC::TimelineProgress(float Value)
{	/* �÷��̾� ��ġ, ȸ�� ���� */
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector NewLocation = FMath::Lerp(StartLoc, EndLoc, Value);
	FRotator NewRotation = FMath::Lerp(StartRot, EndRot, Value);

	CharacterActor->SetActorRelativeLocation(NewLocation);
	CharacterActor->SetActorRelativeRotation(NewRotation);
	PlayerController->GetCharacter()->GetCharacterMovement()->Velocity.X = 80.f;
}

void AQuestNPC::TimelineFinished()
{	/* Ÿ�Ӷ��� ���� �� ���� ���� */
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->GetCharacter()->GetCharacterMovement()->SetActive(false);
	DialogueCreate();

	PlayerController->SetInputMode(FInputModeGameAndUI());

	PlayerController->SetShowMouseCursor(false);
//	//DialoguePopWidget->RemoveFromParent();
}


void AQuestNPC::OnActivate_Implementation()
{
	CurrentLine++;
	if (bIsValid)
	{
		DialogueCreate();
	}
	else
	{
		PlayerAdjustmentss();
		Text->SetHiddenInGame(true);
	}
}

void AQuestNPC::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (bIsPressKeyValid == false)
		{
			bIsPressKeyValid = true;
			PressKeyWidgetUIObejct = CreateWidget<UUserWidget>(GetWorld(), PressKeyWidgetClass);
			PressKeyWidgetUIObejct->AddToViewport();
		}
	}
}

void AQuestNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Overlap End"));
		if (bIsPressKeyValid == true)
		{
			PressKeyWidgetUIObejct->RemoveFromParent();
			bIsPressKeyValid = false;
		}
		if (bIsValid) {
			DialogueUIObject->RemoveFromParent();
			bIsValid = false;
			CurrentLine = 0;
		}
	}
}

void AQuestNPC::OnConstruction(const FTransform& Transform)
{

}
// Called every frame
void AQuestNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurveFTimeline.TickTimeline(DeltaTime);


	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector camLocation = camManager->GetCameraLocation();
	FRotator rotatorToCamera = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), camLocation);

	Text->SetWorldRotation((rotatorToCamera.Quaternion()).Rotator());

}

// Called to bind functionality to input
void AQuestNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}