// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy_State.h"
#include "../Public/Character/C_BagItemBase.h"
#include "C_ShaceEnemyController.generated.h"

UCLASS()
class GALAXYQUEST_API AC_ShaceEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AC_ShaceEnemyController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY()
		class UBehaviorTreeComponent* BTCom;
	UPROPERTY()
		class UBlackboardComponent* BBCom;
	UPROPERTY()
		class AC_SpaceEnemy* EnemyShip;


#pragma region Update Movement
private:
	void UpdateMovement(float DeltaTime);

	void ShipPartolMove(float DeltaSeconds);
	void ShipTrackMove(float DeltaSeconds);
	void ShipAroundMove(float DeltaSeconds);
	void ShipReturnMove(float DeltaSeconds);

#pragma endregion

#pragma region Overlap Event
private:
	UFUNCTION()
		void EnemyBlock(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult);
	UFUNCTION()
		void TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult);

	void BlockWithShip();
	void BlockWithPlanet();
	void OverlapWithShip();
	void OverlapWithPlanet();

#pragma endregion

#pragma region Initialize State
private:
	void InitializeEnemyData();
	void InitializeEvent();
	void InitializeControllerData();
	void InitializeEnemyHealth();
	void InitializeEnemyBullet();

private:
	void InitializeTrack();
	void InitializeAround();
	void InilializePatrol();
	void IniilalizeReturn();

#pragma endregion

#pragma region State Change
public:
	UFUNCTION()
		void BackToOriginState();
	UFUNCTION()
		void TurnToAroundState();
	UFUNCTION()
		void TurnToReturnState();
	UFUNCTION()
		void TurnToPartolState();
	UFUNCTION()
		void TurnToTrackState();

#pragma endregion

#pragma region Checking Functions
public:
	bool CanPartolStateReset() { return bCanReset; }
	void SetPartolStateReset(bool newState) { bCanReset = newState; }

	bool IsAroundNeedAngle() { return bNeedAngle; }
	void SetAroundNeedAngle(bool newState){ bNeedAngle = newState;}

	bool IsAroundbKeepAround() { return bKeepAround; }
	void SetKeepAround(bool newState) { bKeepAround = newState; }

	bool IsTrackCanMove() { return bCanMove; }
	void SetTrackCanMove(bool newState) { bCanMove = newState; }

	void ReSetPartolInfor(float newReloadTime, FRotator newRotator, bool isCurTimeReset = true);

#pragma endregion

#pragma region Data Instance
	/*Partol State*/
public:
	bool bCanReset;
	FRotator GapDirection;
	float ReloadingTime;
	float CurLoadingTime;

	/*Track State*/
public:
	bool bCanMove;
	FRotator TargetDirection;

	/*Around State*/
public:
	bool bKeepAround;
	bool bNeedAngle;
	FRotator AroundDirectrion;
	FVector AroundPoint;
	float AroudSpeed;
	float CurAroundTime;
	EnemyState OriginalState;
	FTimerHandle TH_StateReverse;

	/*Return State*/
public:
	float ReturnSpeed;

#pragma endregion

#pragma region Enemy Health
private:
	void UpdateEnemyHP();
#pragma endregion

#pragma region Enemy Fire
public:
	FBulletItem EnemyBulletItem;
public:
	void Fire();
	void UpdateBullet(float DeltaSeconds);
#pragma endregion

};
