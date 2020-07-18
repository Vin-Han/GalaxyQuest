#include "../Public/Widget/C_StarIntroduce_UI.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"

bool UC_StarIntroduce_UI::Initialize() {
	if (!Super::Initialize())
	{
		return false;
	}
	
	Button_Close	= Cast<UButton>(GetWidgetFromName(TEXT("ButtonClose")));
	Button_Explore	= Cast<UButton>(GetWidgetFromName(TEXT("ButtonExplore")));
	TextBlock_Intro	= Cast<UTextBlock>(GetWidgetFromName(TEXT("TextIntro")));
	TextBlock_Name	= Cast<UTextBlock>(GetWidgetFromName(TEXT("TextName")));
	Image_Pic		= Cast<UImage>(GetWidgetFromName(TEXT("ImagePic")));
	
	Image_Shop = Cast<UImage>(GetWidgetFromName(TEXT("Image_ShopBG")));
	Text_ShopName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_ShopList")));
	Roll_Shop = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollBox_ShopRoll")));
	Button_ShopBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Shop")));
	Text_ShopBtn = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Shop")));

	CloseShop();

	return true;
}

void UC_StarIntroduce_UI::OpenShop()
{
	Image_Shop->SetVisibility(ESlateVisibility::Visible);
	Text_ShopName->SetVisibility(ESlateVisibility::Visible);
	Roll_Shop->SetVisibility(ESlateVisibility::Visible);
	Button_ShopBtn->OnClicked.RemoveAll(this);
	Button_ShopBtn->OnClicked.AddDynamic(this, &UC_StarIntroduce_UI::CloseShop);
	Text_ShopBtn->SetText(FText::FromString("CloseShop"));
}

void UC_StarIntroduce_UI::CloseShop()
{
	Image_Shop->SetVisibility(ESlateVisibility::Hidden);
	Text_ShopName->SetVisibility(ESlateVisibility::Hidden);
	Roll_Shop->SetVisibility(ESlateVisibility::Hidden);
	Button_ShopBtn->OnClicked.RemoveAll(this);
	Button_ShopBtn->OnClicked.AddDynamic(this, &UC_StarIntroduce_UI::OpenShop);
	Text_ShopBtn->SetText(FText::FromString("OpenShop"));
}
