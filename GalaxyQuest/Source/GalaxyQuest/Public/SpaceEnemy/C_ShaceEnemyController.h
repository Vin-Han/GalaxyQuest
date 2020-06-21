// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy_State.h"
#include "../Public/Bag/C_BulletItemBase.h"
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
	UFUNCTION()
		void TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex);

private:
	void BlockWithShip();
	void BlockWithPlanet();
	void OverlapWithShip();
	void OverlapWithPlanet(AActor* OtherActor);
	void EndOverlapWithPlanet();

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
		void TurnToAroundState(FVector NewAroundPoint);
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
	bool bIfTrackKeepMove;
	FRotator TargetDirection;

	/*Around State*/
public:
	bool bIsAroudFinished;
	FRotator AroundTargetDirection;
	FVector AroundPoint;
	EnemyState OriginalState;

	/*Return State*/
public:
	bool bIfReturnKeepRotate;
	FRotator ReturnTargetDirection;

#pragma endregion

#pragma region Enemy Health
private:
	void UpdateEnemyHP();
#pragma endregion

#pragma region Enemy Fire
public:
	FBulletBagItem EnemyBulletItem;
public:
	void Fire();
	void UpdateBullet(float DeltaSeconds);
#pragma endregion

};
