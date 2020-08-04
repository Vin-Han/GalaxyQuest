// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/Character/C_Single_Bag.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"

bool UC_Single_Bag::Initialize() {
	if (!Super::Initialize())
	{
		return false;
	}

	List_Roll = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_Bag")));

	Star_Img = Cast<UImage>(GetWidgetFromName(TEXT("Image_StarImage")));

	Star_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_StarName")));

	Star_Intro = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Intro")));

	Star_Infor = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Infor")));

	Btn_Close = Cast<UButton>(GetWidgetFromName(TEXT("Button_Close")));

	Btn_Quit = Cast<UButton>(GetWidgetFromName(TEXT("Button_Quit")));

	return true;
}
