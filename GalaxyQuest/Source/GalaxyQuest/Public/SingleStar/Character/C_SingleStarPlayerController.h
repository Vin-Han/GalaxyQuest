// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_SingleStarPlayerController.generated.h"

#define SHIPMESH_RORATE_LIMIT 10
#define SHIPTRADE_DISTANCE 300

class AC_SingleStarPlayer;
class AC_StarBeacon;
class AC_SystemCharacterState;
struct FSourceBase;

UCLASS()
class GALAXYQUEST_API AC_SingleStarPlayerController : public APlayerController
{
	GENERATED_BODY()
		
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

	void InitializeData();

	void InitializeState();

	void InitializeBagWidget();

public:
	UPROPERTY()
		AC_SingleStarPlayer* ShipPlayer;
	UPROPERTY()
		AC_SystemCharacterState* ShipState;

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

	UFUNCTION()
		void ClosePoint();

	void LoadBeaconInfor(AC_StarBeacon* tempBeacon);

	void LoadBeaconList(AC_StarBeacon* tempBeacon);

	void LoadBagList(AC_StarBeacon* tempBeacon);

	bool BuySource(FSourceBase* newItem);

	bool SellSource(FSourceBase* newItem);

#pragma endregion

#pragma region Beacon Widget
public:
	UPROPERTY()
		class UC_Beacon_Player* BeaconWidget;
	AC_StarBeacon* tempStarPoint;
public:
	void InitializeBeaconWidget();

	void InitializeItemList();
#pragma endregion

#pragma region Player Bag
public:
	UPROPERTY()
		class UC_Single_Bag* bagWidget;
public:
	UFUNCTION()
		void OpenBag();
	UFUNCTION()
		void CloseBag();
	UFUNCTION()
		void BackToSystem();
	void LoadBagList();

#pragma endregion

};
