#pragma once

#include "CoreMinimal.h"
#include "QuestStruct.generated.h"

USTRUCT()
struct FQuestStruct
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FName ItemName;

	UPROPERTY()
	int32 ItemCnt;
};