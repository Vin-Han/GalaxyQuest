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

	RootComponent = CollisionCom;
	EnemyMesh->SetupAttachment(CollisionCom);
}

void AC_SpaceEnemy::OnDestory(){
	if (ParentSpawner && ParentSpawner->ReduceCount())
		this->Destroy();
}
