// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/SingleStar/C_SingleStarController.h"
#include "../Public/SingleStar/SingleStar/C_SingleStar.h"

void AC_SingleStarController::BeginPlay() {
	Super::BeginPlay();
	Star = Cast<AC_SingleStar>(GetPawn());
	if (Star)
	{
		UE_LOG(LogTemp, Warning, TEXT("StarLoadSuccessful"));
	}
}

void AC_SingleStarController::Tick(float DetlaTime) {
	Super::Tick(DetlaTime);

	if (Star)
	{
		Star->AddActorWorldRotation(
			FRotator(0, Star->RotationTime/ DetlaTime, 0));
	}
}