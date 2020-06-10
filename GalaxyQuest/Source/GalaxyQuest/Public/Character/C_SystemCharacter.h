// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Projectile/C_Bullet_Base.h"
#include "C_SystemCharacter.generated.h"

UCLASS()
class GALAXYQUEST_API AC_SystemCharacter : public APawn
{
	GENERATED_BODY()

#pragma region Initialize Components
public:
	AC_SystemCharacter();
public:
	UPROPERTY(VisibleAnyWhere)
		class USpringArmComponent*	 SpringArmCom;
	UPROPERTY(VisibleAnyWhere)
		class UCameraComponent*		 CameraCom;
	UPROPERTY(VisibleAnyWhere)
		class UStaticMeshComponent*	 ShipMesh;
	UPROPERTY(VisibleAnyWhere)
		class UBoxComponent*		 CollisionCom;
	UPROPERTY(VisibleAnyWhere)
		class UFloatingPawnMovement* ShipMovement;

#pragma endregion

#pragma region Move Related
public:
	UPROPERTY(EditAnyWhere, Category = "Speed")
		float CameraSpeed;
	UPROPERTY(EditAnyWhere, Category = "Speed")
		float RotateSpeed;
	UPROPERTY(EditAnyWhere, Category = "Speed")
		float MaxSpeed;
	UPROPERTY(EditAnyWhere, Category = "Speed")
		float DecayRate;
	UPROPERTY(EditAnyWhere, Category = "Speed")
		float Acceleration;

#pragma endregion

#pragma region Speed Rush Related
public:
	UPROPERTY(EditAnyWhere, Category = "RushHour")
		float MaxSpeedRate;
	UPROPERTY(EditAnyWhere, Category = "RushHour")
		float AccelerationRate;
	UPROPERTY(EditAnyWhere, Category = "RushHour")
		float ArmChangeRatio;
	UPROPERTY(EditAnyWhere, Category = "RushHour")
		float CameraChangeRatio;
	UPROPERTY(EditAnyWhere, Category = "RushHour")
		float ChangeDuration;
	UPROPERTY(EditAnyWhere, Category = "RushHour")
		float MaxRushTime;
	UPROPERTY(EditAnyWhere, Category = "RushHour")
		float RushTimeRevertTime;
	UPROPERTY(EditAnyWhere, Category = "RushHour")
		float RushLeftAlarmRate;
#pragma endregion

public:
	UPROPERTY(EditAnyWhere, Category = "Projectile")
		TArray<TSubclassOf<AC_Bullet_Base>> BulletList;

public:
	UPROPERTY(EditAnyWhere, Category = "WarMode")
		bool bIsInWarMode;
};
