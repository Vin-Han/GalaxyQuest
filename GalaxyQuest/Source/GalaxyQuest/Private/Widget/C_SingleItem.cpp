// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Widget/C_SingleItem.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

bool UC_SingleItem::Initialize() {
	if (!Super::Initialize())
	{
		return false;
	}
	Item_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Name")));

	Item_Intro = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Intro")));

	Item_BtnName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_BtnText")));

	Item_Btn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Function")));

	Item_Pic = Cast<UImage>(GetWidgetFromName(TEXT("Image_Item")));

	return true;
}
