// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTT_Return.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYQUEST_API UC_BTT_Return : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnyWhere)
		float AllowDostance;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
