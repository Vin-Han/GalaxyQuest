// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/Beacon/C_StarBeacon.h"
#include "../Public/SingleStar/Beacon/C_Beacon_UI.h"
#

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"

#include "Kismet/KismetMathLibrary.h"


AC_StarBeacon::AC_StarBeacon()
{
	PrimaryActorTick.bCanEverTick = true;

	PointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Point Mesh"));
	PointCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	PointWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));

	RootComponent = PointMesh;
	PointWidget->SetupAttachment(PointMesh);
	PointCollision->SetupAttachment(PointWidget);

	Point_Name = "NoName";
	Point_Infor_S = "NoInformation";
	
}

void AC_StarBeacon::BeginPlay()
{
	Super::BeginPlay();
	InitializeShortWidget();
}


void AC_StarBeacon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_StarBeacon::InitializeShortWidget()
{
	if (PointWidget)
	{
		Text_Name = Cast<UTextBlock>(PointWidget->GetUserWidgetObject()->GetWidgetFromName(TEXT("TextBlock_Name")));
		Text_Information = Cast<UTextBlock>(PointWidget->GetUserWidgetObject()->GetWidgetFromName(TEXT("TextBlock_Information")));

		if (Text_Name)
		{
			Text_Name->SetText(FText::FromString(Point_Name));
		}
		if (Text_Information)
		{
			Text_Information->SetText(FText::FromString(Point_Infor_S));
		}
		PointWidget->SetWorldRotation(
				UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, GetActorLocation()));
	}
}

