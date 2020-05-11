// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_NormalPlanetPawn.generated.h"

class USphereComponent;
class USceneComponent;
class USplineComponent;

UCLASS()
class GALAXYQUEST_API AC_NormalPlanetPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC_NormalPlanetPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnyWhere)
		USphereComponent* CollisionCom;
	UPROPERTY(VisibleAnyWhere)
		UStaticMeshComponent* PlanetMesh;
	UPROPERTY(VisibleAnyWhere)
		USceneComponent* SceneCom;
	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category = "Components")
		USplineComponent* SplineCom;
public:
	UPROPERTY(EditAnyWhere,CateGory = "Speed")
		float SelfRotation;
};
