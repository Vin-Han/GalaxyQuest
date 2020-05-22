// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_SystemCharacterController.generated.h"

UCLASS()
class GALAXYQUEST_API AC_SystemCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void InitializeShip();
	void InitializeStarWidget();
	void InitializeShipWidget();
	void InitializeDistanceLimit();

#pragma region Distance Limit Related
public:
	void ResetPlayer();
	bool DistanceCheck();
public:
	float VerDisLim;
	float HorDisLim;
	float CurVer;
	float CurHor;
	FVector PlayerStartPoint;
#pragma endregion


public:
	UPROPERTY()
		class AC_SystemCharacter* ShipCharacter;
	FString TargetMapName;

	UPROPERTY()
		class UC_StarIntroduce_UI* StarInfor;
	UPROPERTY()
		class UC_SolarUserFace* ShipUI;

#pragma region Speed Up Related
public:
	virtual void SetupInputComponent() override;
	UFUNCTION()
		void ShipSpeedUp(float value);

public:
	float ArmChangeRate;
	float CameraChangeRate;
	float CurSpeedUpTime;
	float SpeedUptime;
#pragma endregion

#pragma region Widget about Overlap With Star
public:
	UFUNCTION()
		void OverlapStar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult);
	UFUNCTION()
		void StarCloseBtnOnClicked();
	UFUNCTION()
		void StarExploreBtnOnClicked();
#pragma endregion
};
