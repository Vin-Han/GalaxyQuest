// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_SingleStarController.generated.h"

class AC_SingleStar;

UCLASS()
class GALAXYQUEST_API AC_SingleStarController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DetlaTime) override;

public:
	AC_SingleStar* Star;
	
};
