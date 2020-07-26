// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/Beacon/C_Beacon_UI.h"
#include "Components/TextBlock.h"

bool UC_Beacon_UI::Initialize() {
	if (Super::Initialize())
	{
		return false;
	}
	Text_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Name")));
	Text_Information = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Information")));

	return true;
}