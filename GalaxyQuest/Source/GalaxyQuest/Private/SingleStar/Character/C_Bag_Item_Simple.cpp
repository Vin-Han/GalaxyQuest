// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/Character/C_Bag_Item_Simple.h"

bool UC_Bag_Item_Simple::Initialize() {
	if (!Super::Initialize())
	{
		return false;
	}

	Item_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Name")));

	Item_Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Count")));

	return	true;
}