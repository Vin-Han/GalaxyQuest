// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Widget/C_UserBag.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/ScrollBox.h"
#include "Components/Image.h"

bool UC_UserBag::Initialize() {
	if (!Super::Initialize())
	{
		return false;
	}
	Left_Roll = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_Left")));

	Right_Roll = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_Right")));

	Exit_Btn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Exit")));

	Left_Btn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Left")));

	LeftBtn_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_LeftBtn")));;

	RightBtn_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_RightBtn")));;

	Right_Btn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Right")));

	HP_Bar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_HP")));

	Shield_Bar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Shield")));

	Intro_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Introduction")));

	Load_Image = Cast<UImage>(GetWidgetFromName(TEXT("Image_Main")));

	return true;
}