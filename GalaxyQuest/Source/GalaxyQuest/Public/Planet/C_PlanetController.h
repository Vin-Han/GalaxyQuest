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
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void InitializeOval();
	void InitializeOffsetLocation();
	void InitializeOrbit();
	void InitializePlanet();
	void InitializeLocation();

public:
	UPROPERTY()
		AC_NormalPlanetPawn* Planet;

public:
	UPROPERTY()
		float SelfRotaion;//Everyday
	UPROPERTY()
		float SelfTilt;//Everyday
	UPROPERTY()
		float TotalSelfTilt;//Total
	UPROPERTY()
		float bIsClockWise;
	UPROPERTY()
		float RelativeRevolution;//Everyday
	UPROPERTY()
		float CurrentRevolution;//Current
	UPROPERTY()
		FVector OvalLocation;//Circle Point

	/*Oval Related*/
	float OvalA;
	float OvalB;
	float OvalC;
	float OvalA2;
	float OvalB2;
public:
	void UpdateStarLocation(float DeltaTime);

public:
	UPROPERTY()
		class UC_StarLocation_UI* LocationUI;

	FVector PlayerLocation;

	FVector2D ScreenPosition;

	float PlayerDistance;
private:
	void UpdateLocationUI();
};
