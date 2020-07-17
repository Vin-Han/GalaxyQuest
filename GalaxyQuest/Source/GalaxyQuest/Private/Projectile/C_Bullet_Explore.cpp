// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Projectile/C_Bullet_Explore.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "Engine/World.h"

AC_Bullet_Explore::AC_Bullet_Explore() 
{
	BaseDamage = 30;
	InitialLifeSpan = 0.f;
	HoldOnTime = 3.0f;
	ExploreRadial = 5000.0f;
	BulletLoadingTime = 2.0f;
	BulletName = "ExploreBullet";
}

void AC_Bullet_Explore::BeginPlay()
{
	Super::BeginPlay();
	HoldOnTime = FMath::Max(0.0f, HoldOnTime);
	ExploreRadial = FMath::Max(0.0f, ExploreRadial);
	GetWorld()->GetTimerManager().SetTimer(TH_WaitToExplore, this,
		&AC_Bullet_Explore::Explore, 1, false, HoldOnTime);
}

void AC_Bullet_Explore::CollisionComOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	Super::CollisionComOnOverlap(OverlappedComponent, OtherActor, OtherComponent, BodyIndex, FromSweep, HitRusult);

	AC_SpaceEnemy* Enemy = Cast<AC_SpaceEnemy>(OtherActor);
	if (Enemy)
	{
		Explore();
	}
}


void AC_Bullet_Explore::Explore()
{
	TArray<AActor*> IgnoreActor;
	IgnoreActor.Add(
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(), BaseDamage, GetActorLocation(),
		ExploreRadial, nullptr, IgnoreActor,
		UGameplayStatics::GetPlayerPawn(this, 0),
		UGameplayStatics::GetPlayerController(this, 0));
	SelfDestroy();
}