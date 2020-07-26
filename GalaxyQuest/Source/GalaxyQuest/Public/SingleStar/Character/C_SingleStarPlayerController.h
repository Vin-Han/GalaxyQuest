// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_SingleStarPlayerController.generated.h"

#define SHIPMESH_RORATE_LIMIT 10
#define SHIPTRADE_DISTANCE 300

class AC_SingleStarPlayer;

UCLASS()
class GALAXYQUEST_API AC_SingleStarPlayerController : public APlayerController
{
	GENERATED_BODY()
		
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

public:
	AC_SingleStarPlayer* ShipPlayer;

#pragma region MoveMent
public:
	UFUNCTION()
		void SingleUD(float value);
	UFUNCTION()
		void SingleLR(float value);
	UFUNCTION()
		void SingleFN(float value);
#pragma endregion

#pragma region Ship Move Animation
public:
	float AniRotationRocord[2];
#pragma endregion

#pragma region Click Track
public:
	UFUNCTION()
		void MouseTrackPoint();
#pragma endregion

};
