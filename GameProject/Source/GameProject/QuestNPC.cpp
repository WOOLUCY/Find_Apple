// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNPC.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "FindAppleGameMode.h"
#include "DialogueDataStruct.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.h"

// Sets default values
AQuestNPC::AQuestNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_NPC(TEXT("SkeletalMesh'/Game/Semin/Character/SKM_NPC.SKM_NPC'"));
	if (SK_NPC.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_NPC.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimBlueprint>  BP_Anim(TEXT("AnimBlueprint'/Game/Semin/Character/NPC/ABP_NPC.ABP_NPC'"));
	if (BP_Anim.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(BP_Anim.Object->GetAnimBlueprintGeneratedClass());
	}

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


void AQuestNPC::OnActivate_Implementation()
{
	CurrentLine++;
	DialogueCreate();
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

// Called every frame
void AQuestNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &AQuestNPC::OnOverlapEnd);
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AQuestNPC::OnOverlapBegin);
}

// Called to bind functionality to input
void AQuestNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

