// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_SingleStar.generated.h"

UCLASS()
class GALAXYQUEST_API AC_SingleStar : public APawn
{
	GENERATED_BODY()

public:
	AC_SingleStar();

public:
	UPROPERTY(VisibleAnyWhere,Category = "StiaticMesh")
		UStaticMeshComponent* StarMesh;

public:
	UPROPERTY(EditAnyWhere, Category = "Rotation")
		float RotationTime;
};
