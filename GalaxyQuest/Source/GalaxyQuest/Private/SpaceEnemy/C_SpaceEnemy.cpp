// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/C_SpaceEnemy.h"
#include "../public/SpaceEnemy/C_SpaceEnemySpawner.h"
#include "../Public/Projectile/C_Bullet_Base.h"

#include "../Public/GameMode/C_Galaxy_Instance.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"

#include "../Public/Character/C_SystemCharacterController.h"

#include "GameFramework/FloatingPawnMovement.h"

#include "Kismet/KismetMathLibrary.h"

AC_SpaceEnemy::AC_SpaceEnemy()
{
	CollisionCom	= CreateDefaultSubobject<UBoxComponent>			(TEXT("CollisionComponent"));

	EnemyMesh		= CreateDefaultSubobject<UStaticMeshComponent>	(TEXT("EnemyMesh"));
	TriggerCom		= CreateDefaultSubobject<USphereComponent>		(TEXT("TriggerSphere"));
	EnemyBlood		= CreateDefaultSubobject<UWidgetComponent>		(TEXT("BloodWidget"));

	EnemyMovement	= CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("EnemyMovement"));

	RootComponent = CollisionCom;
	EnemyMesh	->SetupAttachment(CollisionCom);
	TriggerCom	->SetupAttachment(CollisionCom);
	EnemyBlood	->SetupAttachment(CollisionCom);

	CurrentState = EnemyState::PATROL;

	PartolSpeed = 10;
	RotateMaxDegree = 60;
	RotateCostTime = 2;
	ReloadMaxTime = 2;

	TrackSpeed = 10;
	AllowDistance = 300;

	EnemyTolHP = 100;
	EnemyCurHP = EnemyTolHP;

	MinBounty = 15;
	MaxBounty = 20;

	Bounty = UKismetMathLibrary::RandomIntegerInRange(MinBounty,MaxBounty);
}

void AC_SpaceEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitializeBloodUI();
}

void AC_SpaceEnemy::OnDestory()
{
	if (ParentSpawner && ParentSpawner->ReduceCount())
	{
		this->Destroy();
	}

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
	EnemyCurHP = FMath::Max(0.f, EnemyCurHP - Damage);
	if (EnemyCurHP == 0 && Cast<AC_SystemCharacterController>(EventInstigator))
	{
		Cast<AC_SystemCharacterController>(EventInstigator)->GetMoney(Bounty);
		if (Cast<UC_Galaxy_Instance>(GetGameInstance()))
		{
			FString tempMessage = FString("Get ") + FString::FromInt(Bounty) + FString(" bounty");
			Cast<UC_Galaxy_Instance>(GetGameInstance())->SendMessageToPlayer(tempMessage,1.0,FColor::Green);
		}
	}
	return 0.0f;
}
