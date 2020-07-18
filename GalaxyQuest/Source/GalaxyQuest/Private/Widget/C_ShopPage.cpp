// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Widget/C_ShopPage.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Slider.h"


bool UC_ShopPage::Initialize() {
	if (!Super::Initialize())
	{
		return false;
	}

	Button_BuyBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Buy")));

	Image_Item = Cast<UImage>(GetWidgetFromName(TEXT("Image_ItemPic")));

	Text_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Name")));

	Text_Intro = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_ItemIntro")));

	Text_CurCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_CurCount")));

	Text_TotalCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_TotalCount")));

	Slider_Buy = Cast<USlider>(GetWidgetFromName(TEXT("Slider_CountBar")));

	TotalCount = 0;
	CurCount = 0;

	BulletInfor = nullptr;
	ShieldInfor = nullptr;

	Slider_Buy->OnValueChanged.AddDynamic(this, &UC_ShopPage::UpdateCurCount);

	return true;
}

void UC_ShopPage::UpdateCurCount(float value)
{
	CurCount = TotalCount * value;
	Text_CurCount->SetText(FText::FromString(FString::FromInt(CurCount)));
}

void UC_ShopPage::UpdateTotalCount(int newCount)
{
	TotalCount = newCount;
	CurCount = 0;
	Slider_Buy->SetValue(0.0f);

	Text_CurCount->SetText(FText::FromString("0"));
	Text_TotalCount->SetText(FText::FromString(FString::FromInt(TotalCount)));
}
