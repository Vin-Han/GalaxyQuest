// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_PlanetController.generated.h"

class AC_NormalPlanetPawn;
class AC_TrackPlanetPawn;
class UC_StarIntroduce_UI;

UCLASS()
class GALAXYQUEST_API AC_PlanetController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;

	//virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void InitializeOval();
	void InitializeOffsetLocation();
	void InitializeOrbit();
	void InitializePlanet();
	//void InitializeStarIntro();
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
	/*
protected:
	UPROPERTY()
		UC_StarIntroduce_UI* StarInfor;
public:
	UFUNCTION()
		void StarCloseBtnOnClicked();
	UFUNCTION()
		void StarExploreBtnOnClicked();
	*/
};
