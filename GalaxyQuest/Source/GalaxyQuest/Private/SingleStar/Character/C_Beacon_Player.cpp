// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/Character/C_Beacon_Player.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"

bool UC_Beacon_Player::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	
	Beacon_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Intro_name")));

	Beacon_Intro = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Intro_Text")));

	Open_TEXT = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Intro_Open")));

	Close_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Intro_Close")));

	Money_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Money_Count")));

	TotalMoney_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Money")));

	Open_Btn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Intro_Open")));

	Close_Btn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Intro_Close")));

	Beacon_Pic = Cast<UImage>(GetWidgetFromName(TEXT("Image_Intro_Pic")));
	
	BG_Up = Cast<UImage>(GetWidgetFromName(TEXT("Image_Up_Pic")));

	BG_Down = Cast<UImage>(GetWidgetFromName(TEXT("Image_Down_BG")));

	Roll_Up = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_Up")));

	Roll_Down = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_Down")));
	
	ClosePage_Btn = Cast<UButton>(GetWidgetFromName(TEXT("Button_ClosePage")));

	ClosePage_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_ClosePage")));
	
	Open_Btn->OnClicked.AddDynamic(this, &UC_Beacon_Player::OpenShop);

	Close_Btn->OnClicked.AddDynamic(this, &UC_Beacon_Player::CloseShop);

	bIsShopShowing = true;
	CloseShop();
	
	return true;
}

void UC_Beacon_Player::OpenShop()
{
	if (bIsShopShowing == false)
	{
		bIsShopShowing = true;
		Money_Text->SetVisibility(ESlateVisibility::Visible);
		TotalMoney_Text->SetVisibility(ESlateVisibility::Visible);
		BG_Up->SetVisibility(ESlateVisibility::Visible);
		BG_Down->SetVisibility(ESlateVisibility::Visible);
		Roll_Up->SetVisibility(ESlateVisibility::Visible);
		Roll_Down->SetVisibility(ESlateVisibility::Visible);
	}
}

void UC_Beacon_Player::CloseShop()
{
	if (bIsShopShowing)
	{
		bIsShopShowing = false;
		Money_Text->SetVisibility(ESlateVisibility::Hidden);
		TotalMoney_Text->SetVisibility(ESlateVisibility::Hidden);
		BG_Up->SetVisibility(ESlateVisibility::Hidden);
		BG_Down->SetVisibility(ESlateVisibility::Hidden);
		Roll_Up->SetVisibility(ESlateVisibility::Hidden);
		Roll_Down->SetVisibility(ESlateVisibility::Hidden);
	}
}
