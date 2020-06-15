// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Widget/C_SolarUserFace.h"

#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

bool UC_SolarUserFace::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	Bar_SpeedUp = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_SpeedUp")));
	Bar_Speed = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Speed")));
	Bar_ExtraSpeed = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_ExtraSpeed")));
	Bar_Horizontal = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Horizontal")));

	Image_WP_1 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Bullet_1")));
	Image_WP_P1 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Bullet_P1")));
	Bar_WP_1 = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Bullet_1")));
	Text_WP_1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Bullet_1")));

	Image_WP_2 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Bullet_2")));
	Image_WP_P2 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Bullet_P2")));
	Bar_WP_2 = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Bullet_2")));
	Text_WP_2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Bullet_2")));

	Image_WP_3 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Bullet_3")));
	Image_WP_P3 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Bullet_P3")));
	Bar_WP_3 = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Bullet_3")));
	Text_WP_3 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Bullet_3")));

	Image_WP_4 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Bullet_4")));
	Image_WP_P4 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Bullet_P4")));
	Bar_WP_4 = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Bullet_4")));
	Text_WP_4 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Bullet_4")));

	Image_WP_5 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Bullet_5")));
	Image_WP_P5 = Cast<UImage>(GetWidgetFromName(TEXT("Image_Bullet_P5")));
	Bar_WP_5 = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Bullet_5")));
	Text_WP_5 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Bullet_5")));

	BulletOut.Add(Image_WP_1);
	BulletOut.Add(Image_WP_2);
	BulletOut.Add(Image_WP_3);
	BulletOut.Add(Image_WP_4);
	BulletOut.Add(Image_WP_5);

	BulletPic.Add(Image_WP_P1);
	BulletPic.Add(Image_WP_P2);
	BulletPic.Add(Image_WP_P3);
	BulletPic.Add(Image_WP_P4);
	BulletPic.Add(Image_WP_P5);

	BulletCD.Add(Bar_WP_1);
	BulletCD.Add(Bar_WP_2);
	BulletCD.Add(Bar_WP_3);
	BulletCD.Add(Bar_WP_4);
	BulletCD.Add(Bar_WP_5);

	BulletNum.Add(Text_WP_1);
	BulletNum.Add(Text_WP_2);
	BulletNum.Add(Text_WP_3);
	BulletNum.Add(Text_WP_4);
	BulletNum.Add(Text_WP_5);

	return true;
}
