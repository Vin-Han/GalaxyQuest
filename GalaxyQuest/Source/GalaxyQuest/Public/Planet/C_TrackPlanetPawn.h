// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_TrackPlanetPawn.generated.h"

UCLASS()
class GALAXYQUEST_API AC_TrackPlanetPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC_TrackPlanetPawn();

public:
	UPROPERTY(VisibleAnyWhere)
		UStaticMeshComponent* TrackMesh;
};
