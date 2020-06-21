// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "C_BTD_RuturnDistance.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYQUEST_API UC_BTD_RuturnDistance : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnyWhere)
		float AllowDistance;
public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
