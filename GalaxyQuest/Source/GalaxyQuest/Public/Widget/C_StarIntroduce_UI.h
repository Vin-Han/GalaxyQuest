#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_StarIntroduce_UI.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class GALAXYQUEST_API UC_StarIntroduce_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	
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
	
};
