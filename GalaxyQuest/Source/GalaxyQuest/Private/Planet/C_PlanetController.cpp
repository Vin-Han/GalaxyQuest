// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Planet/C_PlanetController.h"

#include "../Public/Planet/C_NormalPlanetPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

void AC_PlanetController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
	FRotator TempRotator = FRotator(0, SelfRotation, 0);
	Planet->PlanetMesh->AddWorldRotation(TempRotator);
}

void AC_PlanetController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	Planet = Cast<AC_NormalPlanetPawn>(InPawn);
	if (Planet == NULL) { UE_LOG(LogTemp, Warning, TEXT("Planet Cast Fasiled"));}
	else {
		this->SelfRotation = Planet->SelfRotation;
	}
}