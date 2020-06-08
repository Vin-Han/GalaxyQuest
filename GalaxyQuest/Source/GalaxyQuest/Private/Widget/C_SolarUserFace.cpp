// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Widget/C_SolarUserFace.h"

#include "Components/ProgressBar.h"

bool UC_SolarUserFace::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	Bar_SpeedUp = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_SpeedUp")));
	Bar_Speed = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Speed")));
	Bar_ExtraSpeed = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_ExtraSpeed")));
	Bar_Horizontal = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Horizontal")));

	return true;
}
