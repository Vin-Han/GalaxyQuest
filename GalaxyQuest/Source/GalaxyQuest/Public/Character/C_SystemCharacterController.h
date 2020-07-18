// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"
#include "C_SystemCharacterController.generated.h"

#define BAG_SIZE 5
#define BULLET_WINDOW_SIZE 80

UCLASS()
class GALAXYQUEST_API AC_SystemCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupInputComponent() override;

#pragma region Initialize Controller
public:
	/*initialize player related*/
	void InitializeShip();
	void InitializeShipState();

	/*initialize widgets*/
	void InitializeStarWidget();
	void InitializeShipWidget();
	void InitializeBagWidget();
	void InitializeShipMessage();

	/*initialize instance system*/
	void InitializeBulletWindow();
	void InitializeBaseSheild();

public:
	/*base proprety*/
	UPROPERTY()
		class AC_SystemCharacter* ShipCharacter;
	UPROPERTY()
		class AC_SystemCharacterState* ShipState;

	/*widget instance*/
	UPROPERTY()
		class UC_StarIntroduce_UI* StarInfor;
	UPROPERTY()
		class UC_SolarUserFace* ShipUI;
	UPROPERTY()
		class UC_UserBag* ShipBag;
	UPROPERTY()
		class UC_StarLocation_UI* ShipMassage;

	/*temp name for second map*/
	FString TargetMapName;

#pragma endregion

#pragma region Ship Move Relatived
public:
	/*base move function*/
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

	/*speed up function*/
	UFUNCTION()
		void ShipSpeedUp();
	UFUNCTION()
		void ShipSpeedEnd();

	/*update speed*/
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
		void OverlapWithStar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult);
	UFUNCTION()
		void EndOverlapWithStar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex);
	UFUNCTION()
		void OpenStarWidget();

	UFUNCTION()
		void StarCloseBtnOnClicked();
	UFUNCTION()
		void StarExploreBtnOnClicked();

private:
	void RefleshStarIntro(class AC_NormalPlanetPawn* targetStar);

private:
	bool bIfCanOpenStarPage;
#pragma endregion

#pragma region Fire Relatied
public:
	UFUNCTION()
		void Fire();
	UFUNCTION()
		void ChangeBulletAdd();
	UFUNCTION()
		void ChangeBulletExtract();
	UFUNCTION()
		void DelayModeChange();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void ChangeBulletWindow(float WindowIndex, bool bIsUpgrade);

	bool BulletStateCheck();

	void UpdateBulletLoadingTime(float DeltaSeconds);

	void ChangeWarMode();

	void UpdateBulletWindow();

private:
	FBulletBagItem* curBulletList[BAG_SIZE];

	int CurrentIndex;

	FTimerHandle TH_ChangeWarMode;

	float WarTimeDelaySecond;

#pragma endregion

#pragma region Shield Related
	private:
		void GenerateNewShield(FSheildBagItem* newShield = nullptr);

		void CalculateDamage(float Damage, bool bIfCalculateExtraDamage = false);

		void UpdatePlayerState();
#pragma endregion

#pragma region Bag related Function
public:
	FSheildBagItem* curSheildPtr;
	FBulletBagItem* curBulletPtr;
public:
	UFUNCTION()
		void BagBtn_CloseWindow();
	UFUNCTION()
		void BagOpen_Function();
	UFUNCTION()
		void BulletSetEquip();
	UFUNCTION()
		void BulletEndEquip();
	UFUNCTION()
		void ShieldSetEquip();
	UFUNCTION()
		void ShieldEndEquip();

	void ShowItemInformation();

private:
	void CreatItemList();
	void CreatBulletList();
	void CreatShieldList();

	void LoadPlayerBagState();

private:
	bool GenerateBulletList();
	bool GenerateShieldList();

#pragma endregion

#pragma region Shop Related
private:
	void GenerateShopList(AC_NormalPlanetPawn* targetStar);

	void ResetStarShop(AC_NormalPlanetPawn* targetStar);
#pragma endregion

};
