// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy_State.h"
#include "../Public/SpaceEnemy/C_SpaceEnemySpawner.h"
#include "BehaviorTree/BehaviorTree.h"
#include "C_SpaceEnemy.generated.h"

UCLASS()
class GALAXYQUEST_API AC_SpaceEnemy : public APawn
{
	GENERATED_BODY()

public:
	AC_SpaceEnemy();

	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnyWhere)
		class UBoxComponent* CollisionCom;
	UPROPERTY(VisibleAnyWhere)
		class UStaticMeshComponent* EnemyMesh;
	UPROPERTY(VisibleAnyWhere)
		class USphereComponent* TriggerCom;
	UPROPERTY(VisibleAnyWhere)
		class UFloatingPawnMovement* EnemyMovement;

	UPROPERTY(VisibleAnyWhere)
		class UWidgetComponent* EnemyBlood;

public:
	void OnDestory();

public:
	AC_SpaceEnemySpawner* ParentSpawner;
	FVector SpawnerLocation;
	int Bounty;
public:
	UPROPERTY(EditAnyWhere, Category = "AIEnemy")
		UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnyWhere,Category = "AIEnemy")
		EnemyState CurrentState;
	UPROPERTY(EditAnyWhere, Category = "AIEnemy")
		TSubclassOf<class AC_Bullet_Base> EnemyBullet;
public:
	UPROPERTY(EditAnyWhere, Category = "PartolState")
		float PartolSpeed;
	UPROPERTY(EditAnyWhere, Category = "PartolState")
		float RotateMaxDegree;
	UPROPERTY(EditAnyWhere, Category = "PartolState")
		float RotateCostTime;
	UPROPERTY(EditAnyWhere, Category = "PartolState")
		float ReloadMaxTime;

public:
	UPROPERTY(EditAnyWhere, Category = "TrackState")
		float TrackSpeed;
	UPROPERTY(EditAnyWhere, Category = "TrackState")
		float AllowDistance;
public:
	UPROPERTY(EditAnyWhere, Category = "Attribute")
		int MinBounty;
	UPROPERTY(EditAnyWhere, Category = "Attribute")
		int MaxBounty;
public:
	void InitializeBloodUI();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UPROPERTY()
		class UProgressBar* EnemyBloodBar;
public:
	float EnemyTolHP;

	float EnemyCurHP;
};
