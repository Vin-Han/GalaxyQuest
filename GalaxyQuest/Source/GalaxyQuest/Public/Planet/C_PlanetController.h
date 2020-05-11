// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_PlanetController.generated.h"

/**
 * 
 */

class AC_NormalPlanetPawn;

UCLASS()
class GALAXYQUEST_API AC_PlanetController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;
	
public:
	UPROPERTY()
		AC_NormalPlanetPawn* Planet;

public:
	float RotationOnce;
	float RevolutionOnce;
	float CurRevolution;
};
