// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Projectile/C_Bullet_Normal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AC_Bullet_Normal::AC_Bullet_Normal() {
}

void AC_Bullet_Normal::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("NormalBullet"));

}

void AC_Bullet_Normal::CollisionComOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	Super::CollisionComOnOverlap(OverlappedComponent, OtherActor, OtherComponent, BodyIndex, FromSweep, HitRusult);
	UE_LOG(LogTemp, Warning, TEXT("NormalOverlap"));
}
