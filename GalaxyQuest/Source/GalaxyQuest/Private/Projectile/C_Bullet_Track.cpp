// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Projectile/C_Bullet_Track.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "TimerManager.h"
#include "Engine/World.h"

AC_Bullet_Track::AC_Bullet_Track() 
{
	BaseDamage = 30;
	InitialLifeSpan = 0.0f;

	BulletName = "TrackBullet";
}

void AC_Bullet_Track::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("BaseBullet"));
	bIsStillUpdate = true;
	HoldOnTime = FMath::Max(0.0f, HoldOnTime);
	ExploreRadial = FMath::Max(0.0f, ExploreRadial);

	if (!FindNearestEnemy())
	{
		TargetEnemy = nullptr;
	}
}

void AC_Bullet_Track::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsStillUpdate)
	{
		UpDateRotation();
	}
}

void AC_Bullet_Track::CollisionComOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	Super::CollisionComOnOverlap(OverlappedComponent, OtherActor, OtherComponent, BodyIndex, FromSweep, HitRusult);

	AC_SpaceEnemy* Enemy = Cast<AC_SpaceEnemy>(OtherActor);
	if (Enemy)
	{
		Explore();
	}
}

float AC_Bullet_Track::FindNearestEnemy()
{
	TArray<AActor*> tempArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_SpaceEnemy::StaticClass(), tempArray);
	float NearestDistance = 0;
	for (AActor* tempActor : tempArray)
	{
		float tempDistance = UKismetMathLibrary::Vector_Distance(
							 GetActorLocation(), tempActor->GetActorLocation());
		if (NearestDistance == 0 || tempDistance < NearestDistance)
		{
			if (Cast<AC_SpaceEnemy>(tempActor))
			{
				TargetEnemy = Cast<AC_SpaceEnemy>(tempActor);
				NearestDistance = tempDistance;
			}
		}
	}
	return NearestDistance;
}

void AC_Bullet_Track::UpDateRotation()
{
	if (TargetEnemy == nullptr)
	{
		bIsStillUpdate = false;
		GetWorld()->GetTimerManager().SetTimer(TH_WaitToExplore,this,&AC_Bullet_Track::Explore,1, false, HoldOnTime);
	}
	else
	{
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(
			GetActorLocation(),TargetEnemy->GetActorLocation()));
		MovementCom->SetVelocityInLocalSpace(
			FVector(GetVelocity().Size(),0,0));
	}
}

void AC_Bullet_Track::Explore()
{
	TArray<AActor*> IgnoreActor;
	UGameplayStatics::ApplyRadialDamage(GetWorld(), BaseDamage, GetActorLocation(),
										ExploreRadial,nullptr, IgnoreActor);
	SelfDestroy();
}
