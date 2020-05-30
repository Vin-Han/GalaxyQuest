// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/C_SpaceEnemy.h"
#include "../public/SpaceEnemy/C_SpaceEnemySpawner.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

AC_SpaceEnemy::AC_SpaceEnemy(){
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	CollisionCom = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	EnemyMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("EnemyMovement"));

	TriggerCom = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComponent"));

	RootComponent = CollisionCom;
	EnemyMesh->SetupAttachment(CollisionCom);

	TriggerCom->SetupAttachment(CollisionCom);

	CurrentState = EnemyState::PATROL;

	PartolSpeed = 10;
	RotateMaxDegree = 60;
	RotateCostTime = 2;
	ReloadMaxTime = 2;

	TrackSpeed = 10;
	TrackCostTime = 1;
	AllowDistance = 300;

	AroundCostTime = 1;
	AroundSpeed = 12;
}

void AC_SpaceEnemy::OnDestory(){
	if (ParentSpawner && ParentSpawner->ReduceCount())
		this->Destroy();
}
