// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Widget/C_StarLocation_UI.h"

#include "Components/TextBlock.h"

bool UC_StarLocation_UI::Initialize() {
	if (!Super::Initialize())
	{
		return false;
	}
	Text_StarLocation = Cast<UTextBlock>( GetWidgetFromName(TEXT("TextBlock_StarLocation")));
	Text_StarDistance = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_StarDistance")));
	return true;
}