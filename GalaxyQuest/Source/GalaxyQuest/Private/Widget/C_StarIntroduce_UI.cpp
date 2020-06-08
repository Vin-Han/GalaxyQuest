#include "../Public/Widget/C_StarIntroduce_UI.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

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
	
	return true;
}