// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"
#include "C_Bullet_Base.generated.h"

UCLASS()
class GALAXYQUEST_API AC_Bullet_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Bullet_Base();

	virtual void BeginPlay();

public:
	UPROPERTY(VisibleAnyWhere)
		class UBoxComponent* CollisionCom;
	UPROPERTY(VisibleAnyWhere)
		class UStaticMeshComponent* BulletMesh;
	UPROPERTY(VisibleAnyWhere)
		class UProjectileMovementComponent* MovementCom;

public:
	UPROPERTY(EditAnyWhere, Category = "ItemInformation")
		FString BulletName;
	UPROPERTY(EditAnyWhere, Category = "ItemInformation")
		UTexture2D* BulletPicture;
	UPROPERTY(EditAnyWhere, Category = "ItemInformation")
		float BulletLoadingTime;

	UPROPERTY(EditAnyWhere, Category = "Trade Attributes")
		float DisappearPercent;
	UPROPERTY(EditAnyWhere, Category = "Trade Attributes")
		float OccurPercent;
	UPROPERTY(EditAnyWhere, Category = "Trade Attributes")
		int RandomCount;
	UPROPERTY(EditAnyWhere, Category = "Trade Attributes")
		int MinPrice;
	UPROPERTY(EditAnyWhere, Category = "Trade Attributes")
		int MaxPrice;

protected:
	float BaseDamage = 0;

public:
	virtual void BulletMovement();
	virtual void SelfDestroy();
	virtual void OverlapWithEnemy();
	virtual void OverlapWithPlayer();

public:
	UFUNCTION()
		virtual void CollisionComOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult);
};
