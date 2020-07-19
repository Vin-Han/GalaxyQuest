#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_StarIntroduce_UI.generated.h"

class UButton;
class UTextBlock;
class UImage;
class UScrollBox;

UCLASS()
class GALAXYQUEST_API UC_StarIntroduce_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	UFUNCTION()
		void OpenShop();
	UFUNCTION()
		void CloseShop();

public:
	
	UPROPERTY()
		UButton* Button_Close;
	UPROPERTY()
		UButton* Button_Explore;
	UPROPERTY()
		UTextBlock* TextBlock_Name;
	UPROPERTY()
		UTextBlock* TextBlock_Intro;
	UPROPERTY()
		UImage* Image_Pic;


	UPROPERTY()
		UImage*		Image_Shop;
	UPROPERTY()
		UTextBlock* Text_ShopName;
	UPROPERTY()
		UScrollBox* Roll_Shop;
	UPROPERTY()
		UButton* Button_ShopBtn;
	UPROPERTY()
		UTextBlock* Text_ShopBtn;
	UPROPERTY()
		UTextBlock* Text_Money;
	UPROPERTY()
		UTextBlock* Text_Curmoney;
};
