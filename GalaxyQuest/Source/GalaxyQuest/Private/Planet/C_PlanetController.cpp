// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Planet/C_PlanetController.h"

#include "../Public/Planet/C_NormalPlanetPawn.h"
#include "../Public/Planet/C_TrackPlanetPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"

void AC_PlanetController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	Planet = Cast<AC_NormalPlanetPawn>(InPawn);
	if (Planet == NULL) { UE_LOG(LogTemp, Warning, TEXT("Planet Cast Fasiled"));}
	else {
		InitializePlanetOval();
		if (Planet->OrbitType) {
			Orbit = GetWorld()->SpawnActor<AC_TrackPlanetPawn>(Planet->OrbitType);

			FVector OrbitLocation = FVector(Planet->TargetPosition.X + (Planet->OvalA - Planet->OvalC) / 100, Planet->TargetPosition.Y, Planet->TargetPosition.Z);
			Orbit->SetActorLocation(OrbitLocation);

			Orbit->SetActorRotation(FRotator(Planet->SunTilt, 0, 0));
			FVector OrbitScale = FVector(Planet->OvalA / 100, Planet->OvalB / 100, 100);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::SanitizeFloat((Planet->OvalA - Planet->OvalC)/100));

			Orbit->SetActorScale3D(OrbitScale);
		}
	}
}

void AC_PlanetController::InitializePlanetOval()
{
	Planet->OvalA = (Planet->CloseDistance + Planet->FarDistance) / 2;
	Planet->OvalC = (Planet->FarDistance - Planet->CloseDistance) / 2;
	Planet->OvalA2 = Planet->OvalA * Planet->OvalA;
	Planet->OvalB2 = Planet->OvalA2 - (Planet->OvalC * Planet->OvalC);
	Planet->OvalB = pow(Planet->OvalB2, 0.5);
}
