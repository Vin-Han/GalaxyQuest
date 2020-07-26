// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_SingleStarPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class GALAXYQUEST_API AC_SingleStarPlayer : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnyWhere, Category = "Component")
		UStaticMeshComponent* ShipMesh;
	UPROPERTY(VisibleAnyWhere, Category = "Component")
		UCameraComponent* ShipCamera;
	UPROPERTY(VisibleAnyWhere, Category = "Component")
		USpringArmComponent* ShipArm;
	UPROPERTY(VisibleAnyWhere, Category = "Component")
		USphereComponent* ShipMid;

public:
	UPROPERTY(EditAnyWhere, Category = "ArmLimit")
		float minArmSize;
	UPROPERTY(EditAnyWhere, Category = "ArmLimit")
		float maxArmSize;

public:
	AC_SingleStarPlayer();

};
