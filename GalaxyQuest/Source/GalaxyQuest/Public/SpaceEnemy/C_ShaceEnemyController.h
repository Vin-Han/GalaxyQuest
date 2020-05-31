// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy_State.h"
#include "C_ShaceEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYQUEST_API AC_ShaceEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AC_ShaceEnemyController();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY()
		class UBehaviorTreeComponent* BTCom;
	UPROPERTY()
		class UBlackboardComponent* BBCom;
	UPROPERTY()
		class AC_SpaceEnemy* EnemyShip;

#pragma region Partol State
public:
	bool bCanReset;
	FRotator GapDirection;

	float ReloadingTime;
	float CurLoadingTime;

public:
	void ShipPartolMove(float DeltaSeconds);

#pragma endregion

#pragma region Track State
public:
	bool bCanMove;
	FRotator TargetDirection;
public:
	void ShipTrackMove(float DeltaSeconds);

#pragma endregion

#pragma region Around State
public:
	bool bKeepAround;
	bool bNeedAngle;
	FRotator AroundDirectrion;
	FVector AroundPoint;
	float AroudSpeed;
	float CurAroundTime;
	EnemyState OriginalState;
public:
	void ShipAroundMove(float DeltaSeconds);

#pragma endregion

#pragma region Return State
public:
	float ReturnSpeed;

public:
	UFUNCTION()
		void ChangeToReturnMode();
	void ShipReturnMove(float DeltaSeconds);
#pragma endregion


#pragma region State Update
	UFUNCTION()
		void EnemyBlock(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult);
	UFUNCTION()
		void TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult);
	 
	UFUNCTION()
		void BlockWithShip();

	UFUNCTION()
		void BlockWithPlanet();

	UFUNCTION()
		void OverlapWithShip();

	UFUNCTION()
		void OverlapWithPlanet();

	UFUNCTION()
		void BackToOriginState();

	UFUNCTION()
		void InitializeTrack();

	UFUNCTION()
		void InitializeAround();
		FTimerHandle TH_StateReverse;

	UFUNCTION()
		void InilializePatrol();

	UFUNCTION()
		void BackToPatrolState();
#pragma endregion

};
