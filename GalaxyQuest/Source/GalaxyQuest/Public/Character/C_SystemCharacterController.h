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

	virtual void Tick(float DeltaSeconds) override;

#pragma region Initialize Controller
public:
	void InitializeShip();
	void InitializeStarWidget();
	void InitializeShipWidget();
	void InitializeBulletWindow();

public:
	UPROPERTY()
		class AC_SystemCharacter* ShipCharacter;
	FString TargetMapName;

	UPROPERTY()
		class UC_StarIntroduce_UI* StarInfor;
	UPROPERTY()
		class UC_SolarUserFace* ShipUI;

#pragma endregion

#pragma region Ship Move Relatived
public:
	virtual void SetupInputComponent() override;

	UFUNCTION()
		void MouseUpDown(float value);
	UFUNCTION()
		void MouseRightLeft(float value);
	UFUNCTION()
		void MoveForward(float value);
	UFUNCTION()
		void MoveTurn(float value);
	UFUNCTION()
		void MoveUpDown(float value);

	UFUNCTION()
		void ShipSpeedUp();
	UFUNCTION()
		void ShipSpeedEnd();
	UFUNCTION()
		void UpdateSpeedState(float DeltaSeconds);

public:
	bool  bIsSpeedUpMode;
	bool  bIsRevertMode;

	float SpeedGap;
	float CurSpeed;

	float ArmBaseLength;
	float ArmMinLength;
	float ArmLenChangeRate;

	float CamBaseField;
	float CamMaxField;
	float CamAngChangeRate;

	float RushLeft;
	float RushRevertRate;
	float RushLestAlarm;

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


#pragma region Fire Relatied
public:
	FVector FireLocation;
	FRotator FireRotation;

public:
	UFUNCTION()
		void Fire();
	UFUNCTION()
		void ChangeBulletAdd();
	UFUNCTION()
		void ChangeBulletExtract();

private:
	void ChangeBulletWindow(float WindowIndex, bool bIsUpgrade);

	bool GenerateBulletItem();

	bool BulletStateCheck();

	void UpdateBulletLoadingTime(float DeltaSeconds);

private:
	//TSubclassOf<AC_Bullet_Base> CurrentBullet;
	TArray<struct FBulletBagItem> BulletItemList;
	int CurrentIndex;
	float BulletWindowBaseSize;
#pragma endregion
};
