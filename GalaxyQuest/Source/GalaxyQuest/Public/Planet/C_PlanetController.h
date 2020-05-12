// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_PlanetController.generated.h"

class AC_NormalPlanetPawn;
class AC_TrackPlanetPawn;

UCLASS()
class GALAXYQUEST_API AC_PlanetController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;

	void InitializePlanetOval();
	
public:
	UPROPERTY()
		AC_NormalPlanetPawn* Planet;
	UPROPERTY()
		AC_TrackPlanetPawn* Orbit;
};
