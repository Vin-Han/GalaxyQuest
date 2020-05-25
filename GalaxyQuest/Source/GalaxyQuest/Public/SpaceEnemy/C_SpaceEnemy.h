// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_SpaceEnemy.generated.h"

UCLASS()
class GALAXYQUEST_API AC_SpaceEnemy : public APawn
{
	GENERATED_BODY()

public:
	AC_SpaceEnemy();

public:
	UPROPERTY(VisibleAnyWhere)
		class UStaticMeshComponent* EnemyMesh;
	UPROPERTY(VisibleAnyWhere)
		class UBoxComponent* CollisionCom;
	UPROPERTY(VisibleAnyWhere)
		class UFloatingPawnMovement* EnemyMovement;

public:
	void OnDestory();

public:
	class AC_SpaceEnemySpawner* ParentSpawner;
};
