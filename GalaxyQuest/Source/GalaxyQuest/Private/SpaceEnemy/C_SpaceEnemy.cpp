// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/C_SpaceEnemy.h"
#include "../public/SpaceEnemy/C_SpaceEnemySpawner.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"

#include "GameFramework/FloatingPawnMovement.h"

AC_SpaceEnemy::AC_SpaceEnemy(){
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	CollisionCom = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	EnemyMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("EnemyMovement"));

	TriggerCom = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerComponent"));
	EnemyBlood = CreateDefaultSubobject<UWidgetComponent>(TEXT("BloodWidget"));

	RootComponent = CollisionCom;
	EnemyMesh->SetupAttachment(CollisionCom);

	TriggerCom->SetupAttachment(CollisionCom);
	EnemyBlood->SetupAttachment(CollisionCom);

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

	EnemyTolHP = 100;
	EnemyCurHP = EnemyTolHP;
}

void AC_SpaceEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitializeBloodUI();
}

void AC_SpaceEnemy::OnDestory(){
	if (ParentSpawner && ParentSpawner->ReduceCount())
		this->Destroy();
}

void AC_SpaceEnemy::InitializeBloodUI()
{
	if (EnemyBlood)
	{
		EnemyBloodBar = Cast<UProgressBar>(EnemyBlood->GetUserWidgetObject()->GetWidgetFromName(TEXT("Bar_EnemyBlood")));
	}
}

float AC_SpaceEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//UE_LOG(LogTemp, Warning, TEXT("TakeDamage"));
	EnemyCurHP = FMath::Max(0.f, EnemyCurHP - Damage);
	return 0.0f;
}
