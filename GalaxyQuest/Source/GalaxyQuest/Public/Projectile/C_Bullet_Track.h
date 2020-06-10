// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/C_Bullet_Base.h"
#include "C_Bullet_Track.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYQUEST_API AC_Bullet_Track : public AC_Bullet_Base
{
	GENERATED_BODY()

public:
    AC_Bullet_Track();

public:
    virtual void BeginPlay();

    virtual void Tick(float DeltaTime) override;

    virtual void CollisionComOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult) override;

private:
    float FindNearestEnemy();

    void UpDateRotation();

public:
    UFUNCTION()
        void Explore();
public:
    UPROPERTY(EditAnyWhere,Category = "Attributes")
      class AC_SpaceEnemy* TargetEnemy;
    UPROPERTY(EditAnyWhere, Category = "Attributes")
        float HoldOnTime;
    UPROPERTY(EditAnyWhere, Category = "Attributes")
        float ExploreRadial;

    bool bIsStillUpdate;

    FTimerHandle TH_WaitToExplore;

};
