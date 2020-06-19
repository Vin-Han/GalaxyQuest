// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Projectile/C_Bullet_EnemyNormal.h"
#include "../Public/Character/C_SystemCharacter.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Engine/World.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

AC_Bullet_EnemyNormal::AC_Bullet_EnemyNormal() 
{
	BaseDamage = 20;
	InitialLifeSpan = 0.0f;
	BulletLoadingTime = 2.0f;
	BulletName = "EnemyNormalBullet";
}

void AC_Bullet_EnemyNormal::BeginPlay()
{
	Super::BeginPlay();
	APawn* Player =	UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Player)
	{
		FRotator TargetDirection = UKismetMathLibrary::FindLookAtRotation(
			GetActorLocation(), Player->GetActorLocation());
		SetActorRotation(TargetDirection);
		MovementCom->SetVelocityInLocalSpace(
			FVector(GetVelocity().Size(), 0, 0));
	}
	else
	{
		SelfDestroy();
	}
}

void AC_Bullet_EnemyNormal::OverlapWithPlayer()
{
	//UE_LOG(LogTemp, Warning, TEXT("OverlapWith-Player"));
	UGameplayStatics::ApplyDamage(UGameplayStatics::GetPlayerController(GetWorld(),0),
		BaseDamage,nullptr,this,nullptr);
	SelfDestroy();
}

void AC_Bullet_EnemyNormal::CollisionComOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	Super::CollisionComOnOverlap(OverlappedComponent, OtherActor, OtherComponent, BodyIndex, FromSweep, HitRusult);
	AC_SystemCharacter* player = Cast<AC_SystemCharacter>(OtherActor);
	if (player)
	{
		OverlapWithPlayer();
	}
}