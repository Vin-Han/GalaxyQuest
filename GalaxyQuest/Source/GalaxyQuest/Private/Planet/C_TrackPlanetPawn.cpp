
#include "../Public/Planet/C_TrackPlanetPawn.h"

#include "Components/StaticMeshComponent.h"

AC_TrackPlanetPawn::AC_TrackPlanetPawn()
{
    TrackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrackMesh"));
    RootComponent = TrackMesh;
}

