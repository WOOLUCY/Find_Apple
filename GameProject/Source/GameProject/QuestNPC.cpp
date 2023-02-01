// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNPC.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "FindAppleGameMode.h"
#include "Dialogue/DialogueDataStruct.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "Dialogue/DialogueWidget.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FindAppleCharacter.h"

// Sets default values
AQuestNPC::AQuestNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* 텍스트 설정 */
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PressQ"));
	Text->SetupAttachment(GetRootComponent());
	Text->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	Text->SetTextRenderColor(FColor::White);
	Text->SetHorizontalAlignment(EHTA_Center);
	Text->SetText(FText::FromString(TEXT("Press 'Q' to Chat")));

	/* Set Mesh ( 캐릭터 스켈레톤 메쉬 ) */
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_NPC(TEXT("SkeletalMesh'/Game/Semin/Character/SKM_NPC.SKM_NPC'"));
	if (SK_NPC.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_NPC.Object);
	}

	/* 대화 시 플레이어 위치 지정용 콘(원뿔) 메쉬 */
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

	ConstructorHelpers::FObjectFinder<UAnimBlueprint>  BP_Anim(TEXT("AnimBlueprint'/Game/Semin/Character/NPC/ABP_NPC.ABP_NPC'"));
	if (BP_Anim.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(BP_Anim.Object->GetAnimBlueprintGeneratedClass());
	}

	ConstructorHelpers::FClassFinder<UDialogueWidget>  DialogueWidget(TEXT("WidgetBlueprint'/Game/Semin/UI/Dialogue/BP_DialogueWidget.BP_DialogueWidget_C'"));
	if (DialogueWidget.Succeeded())
	{
		DialogueWidgetClass = DialogueWidget.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget>  DialoguePopWidgetObject(TEXT("WidgetBlueprint'/Game/Semin/UI/Dialogue/WBP_BlackScreenPop.WBP_BlackScreenPop_C'"));
	if (DialoguePopWidgetObject.Succeeded())
	{
		DialoguePopWidgetClass = DialoguePopWidgetObject.Class;
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


	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Semin/UI/CPP_Dialogue_File.CPP_Dialogue_File"));
	if (DataTable.Succeeded())
	{
		DialogueDatatable = DataTable.Object;
	}


	//GetMesh()->SetAnimClass()
}

// Called when the game starts or when spawned
void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();

	if (DialogueDatatable != nullptr)
	{
		DialogueDatatable->GetAllRows<FDialogueTableRow>(TEXT("GetAllRows"), DialogueData);
		TArray<FName> RowNames = DialogueDatatable->GetRowNames();

		for (int i = 0; i < RowNames.Num(); i++)
		{
			FDialogueTableRow Dialogue = *(DialogueDatatable->FindRow<FDialogueTableRow>(RowNames[i], RowNames[i].ToString()));
			if (NPC_ID == Dialogue.NPC_ID) {
				MyDialogue.Add(RowNames[i]);
				UE_LOG(LogTemp, Warning, TEXT("NPCID: %d, NPC Name: %s"), Dialogue.NPC_ID, *(Dialogue.NPC_Name.ToString()));
			}
		}
	}
}

void AQuestNPC::DialogueGetLine()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	TArray<FText> ReturnLines;

	for ( FName CurDialogue : MyDialogue )
	{
		FDialogueTableRow Dialogue = *(DialogueDatatable->FindRow<FDialogueTableRow>(CurDialogue, CurDialogue.ToString()));
		UE_LOG(LogTemp, Warning, TEXT("C_ID: %d, CD_ID: %d, L_ID: %d, LD_ID: %d"), Conversation_ID, Dialogue.Conversation_ID, CurrentLine, Dialogue.Line_ID);
		if ( Conversation_ID == Dialogue.Conversation_ID && CurrentLine == Dialogue.Line_ID)
		{
			UE_LOG(LogTemp, Warning, TEXT("NPCID: %d, NPC Name: %s"), Dialogue.NPC_ID, *(Dialogue.NPC_Name.ToString()));
			MyNameText = Dialogue.NPC_Name;
			ReturnLines.Add(Dialogue.Dialogue);
			if (ReturnLines.Num() == 1)
			{
				if (!ReturnLines[0].IsEmpty())
				{
					UE_LOG(LogTemp, Display, TEXT("TExt Set"));
					DialogueUIObject->ChangeText(MyNameText, ReturnLines[0]);
					return;
				}
			}
		}
		else {
		}
	}

	if (ReturnLines.IsEmpty()) {
		UE_LOG(LogTemp, Display, TEXT("Text Remove "));
		bIsValid = false;
		DialogueUIObject->RemoveFromParent();
		CurrentLine = 0;

		/* FindAppleCharacter로 Cast */
		AActor* ActorItr = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		AFindAppleCharacter* MyCharacter = Cast<AFindAppleCharacter>(ActorItr);

		PlayerController->SetViewTargetWithBlend(MyCharacter->CameraComponent->GetOwner(), 1.3f);

		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);

		PlayerController->GetCharacter()->GetCharacterMovement()->SetActive(true);


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
		UE_LOG(LogTemp, Display, TEXT("call dialogue get line "));
		DialogueGetLine();
	}
	else 
	{
		if (DialogueWidgetClass)
		{
			UE_LOG(LogTemp, Display, TEXT("widget create "));
			bIsValid = true;
			DialogueUIObject = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
			DialogueUIObject->AddToViewport();
			DialogueGetLine();
		}
	}

}

void AQuestNPC::PlayerAdjustmentss()
{
	/* 플레이어 컨트롤러 가지고 오기 */
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeUIOnly());

	/* 위젯 생성 */
	DialoguePopWidget = CreateWidget(GetWorld(), DialoguePopWidgetClass);
	DialoguePopWidget->AddToViewport();

	/* 2초 쉬기 */
	FTimerHandle GravityTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle, FTimerDelegate::CreateLambda([&]()	// 타이머 2초
		{ GetWorld()->GetTimerManager().ClearTimer(GravityTimerHandle);}), 0.2f, false);	// 반복하려면 false를 true로 변경

	/* 플레이어의 카메라 수정 */
	PlayerController->SetViewTargetWithBlend(CameraComponent->GetOwner(), 2.f);

	/* 플레이어 위치 이동 */
	
	/* 커브 사용 */
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
{	/* 플레이어 위치, 회전 변경 */
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AActor* CharacterActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector NewLocation = FMath::Lerp(StartLoc, EndLoc, Value);
	FRotator NewRotation = FMath::Lerp(StartRot, EndRot, Value);

	CharacterActor->SetActorRelativeLocation(NewLocation);
	CharacterActor->SetActorRelativeRotation(NewRotation);
	PlayerController->GetCharacter()->GetCharacterMovement()->Velocity.X = 80.f;
}

void AQuestNPC::TimelineFinished()
{	/* 타임라인 끝난 후 위젯 설정 */
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
		UE_LOG(LogTemp, Display, TEXT("Is That Rihgt?"));
		PlayerAdjustmentss();
		Text->SetHiddenInGame(true);
	}
}

void AQuestNPC::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
	
}

void AQuestNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (bIsValid) {
		DialogueUIObject->RemoveFromParent();
		bIsValid = false;
		CurrentLine = 0;
	}
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
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

	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &AQuestNPC::OnOverlapEnd);
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AQuestNPC::OnOverlapBegin);
}

// Called to bind functionality to input
void AQuestNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}