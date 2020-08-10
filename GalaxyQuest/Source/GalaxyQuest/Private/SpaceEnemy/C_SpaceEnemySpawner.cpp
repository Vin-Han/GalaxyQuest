#include "../Public/SpaceEnemy/C_SpaceEnemySpawner.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"
#include "../Public/Character/C_SystemCharacter.h"

#include "Components/BoxComponent.h"

#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AC_SpaceEnemySpawner::AC_SpaceEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;

	EnemyMaxCount = FMath::Max(EnemyMaxCount, 0);
	EnemyDistanceLimit = FMath::Max(EnemyDistanceLimit, 0.0f);
	CurrentEnemy = 0;
}

void AC_SpaceEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerShip && CurrentEnemy < EnemyMaxCount) 
	{
		FTimerHandle TH_EnemySpaner;
		GetWorld()->GetTimerManager().SetTimer(TH_EnemySpaner,this,&AC_SpaceEnemySpawner::ChildNumCheck, EnemyMaxCount - CurrentEnemy,false,2.0);
		CurrentEnemy = EnemyMaxCount;
	}
}

void AC_SpaceEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	PlayerShip = Cast<AC_SystemCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerShip)
	{
		while (CurrentEnemy < EnemyMaxCount)
		{
			if (SpawnEnemy())
			{
				CurrentEnemy++;
			}
		}
	}
}

bool AC_SpaceEnemySpawner::SpawnEnemy()
{
	FTransform SpawnTransform = FindLocationInBox();
	AC_SpaceEnemy* NewEnemy = GetWorld()->SpawnActor<AC_SpaceEnemy>(Enemy, 
							SpawnTransform.GetLocation(), 
							SpawnTransform.GetRotation().Rotator());
	if (NewEnemy) 
	{
		NewEnemy->ParentSpawner = this;
		NewEnemy->SpawnerLocation = this->GetActorLocation();
		return true;
	}
	return false;
}

FTransform AC_SpaceEnemySpawner::FindLocationInBox()
{
	FVector location;
	do
	{
		location = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), SpawnArea->Bounds.BoxExtent);
	} 
	while (FVector(PlayerShip->GetActorLocation() - location).Size() < EnemyDistanceLimit);

	FRotator rotation = UKismetMathLibrary::RandomRotator();
	FTransform result = FTransform(rotation,location);
	return result;
}

bool AC_SpaceEnemySpawner::ReduceCount()
{
	//UE_LOG(LogTemp, Warning, TEXT("ChildDead"));
	if (CurrentEnemy >0)
	{
		CurrentEnemy--;
		return true;
	}
	return false;
}

void AC_SpaceEnemySpawner::ChildNumCheck()
{
	SpawnEnemy();
}

