// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Projectile/C_Bullet_Normal.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Kismet/GameplayStatics.h"

AC_Bullet_Normal::AC_Bullet_Normal() 
{
	BaseDamage = 20;
	InitialLifeSpan = 5.0f;
	BulletName = "NormalBullet";
}

void AC_Bullet_Normal::BeginPlay() 
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("NormalBullet"));

}

void AC_Bullet_Normal::CollisionComOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	Super::CollisionComOnOverlap(OverlappedComponent, OtherActor, OtherComponent, BodyIndex, FromSweep, HitRusult);

	AC_SpaceEnemy* Enemy = Cast<AC_SpaceEnemy>(OtherActor);
	if (Enemy)
	{
		//UE_LOG(LogTemp, Warning, TEXT("ApplayDamage"));
		UGameplayStatics::ApplyDamage(Enemy, BaseDamage,
			UGameplayStatics::GetPlayerController(this, 0),
			UGameplayStatics::GetPlayerPawn(this, 0), nullptr);
	}
}
