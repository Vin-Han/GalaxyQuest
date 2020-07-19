// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Widget/C_ShopPage.h"

#include "../Public/Character/C_SystemCharacterController.h"

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

	Text_CurPrice = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_CurPrice")));

	Text_TotalPrice = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_TotalPrice")));

	TotalCount = 0;
	CurCount = 0;

	BulletInfor = nullptr;
	ShieldInfor = nullptr;

	Slider_Buy->OnValueChanged.AddDynamic(this, &UC_ShopPage::UpdateCurCount);
	Button_BuyBtn->OnClicked.AddDynamic(this, &UC_ShopPage::BuyItemBtn);

	return true;
}

void UC_ShopPage::UpdateCurCount(float value)
{
	CurCount = TotalCount * value;
	if (BulletInfor)
	{
		BulletInfor->CurrentAccout = CurCount;
	}
	Text_CurCount->SetText(FText::FromString(FString::FromInt(CurCount)));

	if (BulletInfor)
	{
		Text_TotalPrice->SetText(FText::FromString(FString::FromInt(
			CurCount* BulletInfor->CurPrice)));
	}
	else if (ShieldInfor)
	{
		Text_TotalPrice->SetText(FText::FromString(FString::FromInt(
			CurCount* ShieldInfor->CurPrice)));
	}

}

void UC_ShopPage::UpdateTotalCount(int newCount)
{
	TotalCount = newCount;
	CurCount = 0;
	Slider_Buy->SetValue(0.0f);

	if (TotalCount == 0)
	{
		Button_BuyBtn->OnClicked.RemoveAll(this);
	}
	if (BulletInfor)
	{
		BulletInfor->TotalAccout = newCount;
		BulletInfor->CurrentAccout = 0;
	}

	Text_CurCount->SetText(FText::FromString("0"));
	Text_TotalPrice->SetText(FText::FromString("0"));
	Text_TotalCount->SetText(FText::FromString(FString::FromInt(TotalCount)));
}

void UC_ShopPage::BuyItemBtn()
{
	AC_SystemCharacterController* buyer = Cast<AC_SystemCharacterController>(tempController);
	if (buyer)
	{
		bool buyResult = false;
		if (BulletInfor)
		{
			buyResult = buyer->BuySomeItem(BulletInfor);
		}
		else if (ShieldInfor)
		{
			buyResult = buyer->BuySomeItem(ShieldInfor);
		}

		if (buyResult)
		{
			UpdateTotalCount(TotalCount - CurCount);
		}
	}
}
