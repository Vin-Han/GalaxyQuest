// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/Character/C_SingleStarPlayer.h"

#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
AC_SingleStarPlayer::AC_SingleStarPlayer()
{
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ShipCamera"));
	ShipArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ShipArm"));
	ShipMid = CreateDefaultSubobject<USphereComponent>(TEXT("ShipMid"));

	RootComponent = ShipMid;
	ShipArm->SetupAttachment(ShipMid);
	ShipMesh->SetupAttachment(ShipArm);
	ShipCamera->SetupAttachment(ShipArm);

	minArmSize = 1500;
	maxArmSize = 2500;
}


