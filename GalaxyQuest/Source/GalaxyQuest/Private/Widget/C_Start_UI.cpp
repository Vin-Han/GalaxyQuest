// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Widget/C_Start_UI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../Public/Widget/C_Galaxy_UI.h"

bool UC_Start_UI::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	Btn_Into = Cast<UButton>(GetWidgetFromName(TEXT("Button_Into")));

	Btn_Quit = Cast<UButton>(GetWidgetFromName(TEXT("Button_Quit")));

	Text_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Name")));

	Text_Intro = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Intro")));

	Img_Galaxy = Cast<UImage>(GetWidgetFromName(TEXT("Image_Galaxy_Light")));

	WG_Galaxy = Cast<UC_Galaxy_UI>(GetWidgetFromName(TEXT("Galaxy_UI")));

	return true;
}

void UC_Start_UI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (Img_Galaxy)
	{
		float curAngle = Img_Galaxy->GetRenderTransformAngle();
		if (curAngle >= 360)
		{
			Img_Galaxy->SetRenderTransformAngle(0.0f);
		}
		else
		{
			Img_Galaxy->SetRenderTransformAngle(curAngle + 4*InDeltaTime);
		}
	}
	if (WG_Galaxy)
	{
		float curAngle = WG_Galaxy->GetRenderTransformAngle();
		if (curAngle >= 360)
		{
			WG_Galaxy->SetRenderTransformAngle(0.0f);
		}
		else
		{
			WG_Galaxy->SetRenderTransformAngle(curAngle + InDeltaTime);
		}
	}
}