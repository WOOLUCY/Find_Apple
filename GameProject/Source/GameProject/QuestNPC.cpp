// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNPC.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "FindAppleGameMode.h"
#include "DialogueDataStruct.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AQuestNPC::AQuestNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		UE_LOG(LogTemp, Warning, TEXT("Datatable Complete"));
		DialogueDatatable = DataTable.Object;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> DialogueWidget(TEXT("WidgetBlueprint'/Game/Semin/UI/WBP_Dialogue.WBP_Dialogue'"));
	if (DialogueWidget.Succeeded())
	{
		DialogueWidgetClass = DialogueWidget.Class;
	}

	//GetMesh()->SetAnimClass()
}

// Called when the game starts or when spawned
void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();

	if (DialogueDatatable != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Datatable Complete"));
		//DialogueDatatable->GetAllRows<FDialogueTableRow>(TEXT("GetAllRows"), DialogueData);
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

}

void AQuestNPC::DialogueCreate() 
{
	if (IsValid(DialogueWidgetClass)) 
	{
		UE_LOG(LogTemp, Display, TEXT("widget oo "));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Widget nono"));
		CreateWidget(GetWorld()->GetFirstPlayerController(), DialogueWidgetClass);
	}

}

void AQuestNPC::OnActivate_Implementation()
{
	CurrentLine++;
	DialogueCreate();
}


// Called every frame
void AQuestNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, );


}

// Called to bind functionality to input
void AQuestNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

