// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_SystemCharacterController.generated.h"

class UC_StarIntroduce_UI;

UCLASS()
class GALAXYQUEST_API AC_SystemCharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	void InitializeShip();
	void InitializeStar();
public:
	UPROPERTY()
		class AC_SystemCharacter* ShipCharacter;

public:
	UFUNCTION()
		void OverlapStar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult);

public:
	UPROPERTY()
		UC_StarIntroduce_UI* StarInfor;
	FString TargetMapName;
public:
	UFUNCTION()
		void StarCloseBtnOnClicked();
	UFUNCTION()
		void StarExploreBtnOnClicked();
};
