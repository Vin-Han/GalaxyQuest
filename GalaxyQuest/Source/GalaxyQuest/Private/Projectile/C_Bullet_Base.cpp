// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Projectile/C_Bullet_Base.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

AC_Bullet_Base::AC_Bullet_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionCom = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MovementCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	RootComponent = CollisionCom;
	BulletMesh->SetupAttachment(CollisionCom);

	MovementCom->ProjectileGravityScale	= 0.0f;
	MovementCom->InitialSpeed			= 300.0f;
	MovementCom->Friction				= 0.0f;

	InitialLifeSpan = 5.0f;

}

void AC_Bullet_Base::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BaseBullet"));
	CollisionCom->OnComponentBeginOverlap.AddDynamic(this,&AC_Bullet_Base::CollisionComOnOverlap);
}

void AC_Bullet_Base::BulletMovement()
{

}

void AC_Bullet_Base::SelfDestroy()
{
	Destroy();
}

void AC_Bullet_Base::OverlapWithEnemy()
{
	UE_LOG(LogTemp,Warning,TEXT("OverlapWith-Enemy"));
}

void AC_Bullet_Base::OverlapWithPlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("OverlapWith-Player"));
}

void AC_Bullet_Base::CollisionComOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	UE_LOG(LogTemp, Warning, TEXT("BaseOverlap"));
}
