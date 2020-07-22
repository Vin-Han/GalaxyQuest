// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/Character/C_SingleStarPlayerController.h"
#include "../Public/SingleStar/Character/C_SingleStarPlayer.h"

#include "GameFramework/SpringArmComponent.h"

void AC_SingleStarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ShipPlayer = Cast<AC_SingleStarPlayer>(GetPawn());
	bShowMouseCursor = true;
}

void AC_SingleStarPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AC_SingleStarPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UE_LOG(LogTemp, Warning, TEXT("BindAxis"));
	InputComponent->BindAxis("SingleUD", this, &AC_SingleStarPlayerController::SingleUD);
	InputComponent->BindAxis("SingleLR", this, &AC_SingleStarPlayerController::SingleLR);
	InputComponent->BindAxis("SingleFN", this, &AC_SingleStarPlayerController::SingleFN);

}

#pragma region Movement
void AC_SingleStarPlayerController::SingleUD(float value)
{
	if (ShipPlayer)
	{
		ShipPlayer->AddActorWorldRotation(FRotator(value, 0, 0));
	}
}

void AC_SingleStarPlayerController::SingleLR(float value)
{
	if (ShipPlayer)
	{
		ShipPlayer->AddActorWorldRotation(FRotator(0, value, 0));
	}
}

void AC_SingleStarPlayerController::SingleFN(float value)
{
	if (ShipPlayer)
	{
		if (value > 0 && 
			ShipPlayer->ShipArm->TargetArmLength < ShipPlayer->maxArmSize)
		{
			ShipPlayer->ShipArm->TargetArmLength += value*10;
		}
		else if (value < 0 &&
			ShipPlayer->ShipArm->TargetArmLength > ShipPlayer->minArmSize)
		{
			ShipPlayer->ShipArm->TargetArmLength += value*10;
		}
	}
}

#pragma endregion


