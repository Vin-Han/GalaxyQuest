#include "../Public/Character/C_SystemCharacterController.h"

#include "../Public/Character/C_SystemCharacter.h"
#include "../Public/Character/C_SystemCharacterState.h"
#include "../Public/Planet/C_NormalPlanetPawn.h"
#include "../Public/Widget/C_StarIntroduce_UI.h"
#include "../Public/Widget/C_SolarUserFace.h"
#include "../Public/GameMode/C_SolarSystemGameMode.h"
#include "../Public/Projectile/C_Bullet_Base.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Shield/C_Shield_Base.h"
#include "../Public/Projectile/C_Bullet_EnemyNormal.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

void AC_SystemCharacterController::BeginPlay()
{
	Super::BeginPlay();

	CleanupGameViewport();
	InitializeShip();
	InitializeStarWidget();
	InitializeShipWidget();
	InitializeBulletWindow();
	InitializeBaseSheild();
	InitializeShipState();

	TargetMapName = "/Game/Blueprint/BP_Map/BP_Test_Map";
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Hello,StartGameMode"));
}

void AC_SystemCharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateSpeedState(DeltaSeconds);
	UpdateBulletLoadingTime(DeltaSeconds);
	UpdatePlayerState();
}

#pragma region Initialize Controller
void AC_SystemCharacterController::InitializeShip()
{
	ShipCharacter = Cast<AC_SystemCharacter>(GetPawn());
	if (ShipCharacter)
	{
		ShipCharacter->CollisionCom->OnComponentBeginOverlap.AddDynamic(this,&AC_SystemCharacterController::OverlapStar);
		
		SpeedGap = ShipCharacter->MaxSpeed * ShipCharacter->MaxSpeedRate;
		CurSpeed = 0;

		ShipCharacter->CameraSpeed		= FMath::Clamp(ShipCharacter->CameraSpeed, 0.01f, 5.0f);
		ShipCharacter->RotateSpeed		= FMath::Clamp(ShipCharacter->RotateSpeed, 0.1f, 2.0f);
		ShipCharacter->MaxSpeedRate		= FMath::Max(ShipCharacter->MaxSpeedRate, 0.1f);
		ShipCharacter->AccelerationRate = FMath::Max(ShipCharacter->AccelerationRate, 0.1f);

		ShipCharacter->ShipMovement->MaxSpeed	  = ShipCharacter->MaxSpeed;
		ShipCharacter->ShipMovement->Acceleration = ShipCharacter->Acceleration;
		ShipCharacter->ShipMovement->Deceleration = ShipCharacter->DecayRate;

		ArmBaseLength = ShipCharacter->SpringArmCom->TargetArmLength;
		ArmMinLength = FMath::Max(ArmBaseLength * ShipCharacter->ArmChangeRatio, 0.0f);
		ArmLenChangeRate = FMath::Abs(ArmBaseLength - ArmMinLength) / ShipCharacter->ChangeDuration;

		CamBaseField  = ShipCharacter->CameraCom->FieldOfView;
		CamMaxField = FMath::Max(CamBaseField * ShipCharacter->CameraChangeRatio, 0.0f);
		CamAngChangeRate = FMath::Abs(CamBaseField - CamMaxField) / ShipCharacter->ChangeDuration;

		RushLeft = ShipCharacter->MaxRushTime;
		RushRevertRate = ShipCharacter->MaxRushTime / ShipCharacter->RushTimeRevertTime;
		RushLestAlarm = ShipCharacter->MaxRushTime * ShipCharacter->RushLeftAlarmRate;

		bIsSpeedUpMode = false;
		bIsRevertMode = false;
	}
}

void AC_SystemCharacterController::InitializeStarWidget()
{
	StarInfor = CreateWidget<UC_StarIntroduce_UI>(GetGameInstance(), 
				LoadClass<UC_StarIntroduce_UI>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_StarIntroduction.BP_StarIntroduction_c'")));
	if (StarInfor)
	{
		if (StarInfor->Button_Close)
		{
			StarInfor->Button_Close->OnClicked.AddDynamic(this, &AC_SystemCharacterController::StarCloseBtnOnClicked);
		}
		if (StarInfor->Button_Explore)
		{
		StarInfor->Button_Explore->OnClicked.AddDynamic(this, &AC_SystemCharacterController::StarExploreBtnOnClicked);
		}
	}
}

void AC_SystemCharacterController::InitializeShipWidget()
{
	ShipUI = CreateWidget<UC_SolarUserFace>(GetGameInstance(),
											LoadClass<UC_SolarUserFace>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_SolarUserFace.BP_SolarUserFace_c'")));
	if (ShipUI)
	{
		ShipUI->AddToViewport();
		if (ShipUI->Bar_SpeedUp) 
		{
			ShipUI->Bar_SpeedUp->SetPercent(1.f);
		}
		if (ShipUI->Bar_Speed)
		{
			ShipUI->Bar_Speed->SetPercent(0.f);
		}
		if (ShipUI->Bar_ExtraSpeed)
		{
			ShipUI->Bar_ExtraSpeed->SetPercent(0.f);
		}
		if (ShipUI->Bar_Horizontal)
		{
			ShipUI->Bar_Horizontal->SetPercent(1.f);
		}
		if (ShipUI->Bar_Blood)
		{
			ShipUI->Bar_Blood->SetPercent(1.f);
		}
		if (ShipUI->Bar_Shield)
		{
			ShipUI->Bar_Shield->SetPercent(1.f);
		}
	}
}

void AC_SystemCharacterController::InitializeBulletWindow()
{
	if (GenerateBulletItem() == false)
	{
		return;
	}
	BulletWindowBaseSize = 80;
	//CurrentBullet = BulletItemList[0].BulletClass;
	CurrentIndex = 0;

	if (ShipUI)
	{
		for (int i = 0; i < ShipUI->BulletOut.Num(); i++)
		{
			ShipUI->BulletOut[i]->SetVisibility(ESlateVisibility::Hidden);
			ShipUI->BulletPic[i]->SetOpacity(0.5f);
			ShipUI->BulletPic[i]->SetVisibility(ESlateVisibility::Hidden);
			ShipUI->BulletCD[i]->SetVisibility(ESlateVisibility::Hidden);
			ShipUI->BulletNum[i]->SetVisibility(ESlateVisibility::Hidden);
			ShipUI->BulletNum[i]->SetOpacity(0.8f);
		}
		//UE_LOG(LogTemp, Warning, TEXT("CheckingVisible"));
		int TolalIndex = FMath::Min(5, BulletItemList.Num());
		for (int i = 0; i < TolalIndex; i++)
		{
			ShipUI->BulletOut[i]->SetVisibility(ESlateVisibility::Visible);
			ShipUI->BulletPic[i]->SetVisibility(ESlateVisibility::Visible);
			ShipUI->BulletPic[i]->SetBrushFromTexture(
				BulletItemList[i].BulletClass.GetDefaultObject()->BulletPicture);
			ShipUI->BulletCD[i]->SetVisibility(ESlateVisibility::Visible);
			ShipUI->BulletNum[i]->SetVisibility(ESlateVisibility::Visible);
			ChangeBulletWindow(i, false);
		}
	}
	ChangeBulletWindow(CurrentIndex, true);
}

void AC_SystemCharacterController::InitializeBaseSheild()
{
	GenerateNewShield();
}

void AC_SystemCharacterController::InitializeShipState()
{
	ShipState = Cast<AC_SystemCharacterState>(this->PlayerState);
	if (ShipState)
	{
		ShipState->PlayerCurrentHp = ShipCharacter->TotalHP;
		if (CurrentEqipedShield)
		{
			ShipState->CurrentShield = CurrentEqipedShield->CurrentShield;
		}
	}
}

#pragma endregion

void AC_SystemCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("UpDown", this, &AC_SystemCharacterController::MouseUpDown);
	InputComponent->BindAxis("RightLeft", this, &AC_SystemCharacterController::MouseRightLeft);
	InputComponent->BindAxis("MoveForward", this, &AC_SystemCharacterController::MoveForward);
	InputComponent->BindAxis("MoveTurn", this, &AC_SystemCharacterController::MoveTurn);
	InputComponent->BindAxis("MoveUpDown", this, &AC_SystemCharacterController::MoveUpDown);

	InputComponent->BindAction("ShipSpeedUpEnd", EInputEvent::IE_Pressed, this, &AC_SystemCharacterController::ShipSpeedUp);
	InputComponent->BindAction("ShipSpeedUpEnd", EInputEvent::IE_Released, this, &AC_SystemCharacterController::ShipSpeedEnd);

	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AC_SystemCharacterController::Fire);
	InputComponent->BindAction("ChangeBulletAdd", EInputEvent::IE_Pressed, this, &AC_SystemCharacterController::ChangeBulletAdd);
	InputComponent->BindAction("ChangeBulletExtract", EInputEvent::IE_Pressed, this, &AC_SystemCharacterController::ChangeBulletExtract);
}

#pragma region Ship Move Relatived
void AC_SystemCharacterController::MouseUpDown(float value) 
{
	AddYawInput(value * ShipCharacter->CameraSpeed);
}

void AC_SystemCharacterController::MouseRightLeft(float value) 
{
	AddPitchInput(value * ShipCharacter->CameraSpeed);
}

void AC_SystemCharacterController::MoveTurn(float value) 
{
	FRotator temp = FRotator::ZeroRotator;
	float rSpeedLimit = CurSpeed
					  / ShipCharacter->ShipMovement->MaxSpeed;
	temp.Yaw = rSpeedLimit * (ShipCharacter->RotateSpeed*0.8 * value);
	ShipCharacter->AddActorWorldRotation(temp);
}

void AC_SystemCharacterController::MoveUpDown(float value) 
{
	FRotator temp = FRotator::ZeroRotator;
	float rSpeedLimit = CurSpeed
		/ ShipCharacter->ShipMovement->MaxSpeed;
	temp.Pitch = rSpeedLimit * (ShipCharacter->RotateSpeed * value);
	ShipCharacter->AddActorLocalRotation(temp);
}

void AC_SystemCharacterController::MoveForward(float value) 
{
	FVector temp = ShipCharacter->GetActorForwardVector();
	if (CurSpeed < ShipCharacter->ShipMovement->MaxSpeed)
	{
		ShipCharacter->AddMovementInput(temp, value);
	}
}

void AC_SystemCharacterController::ShipSpeedUp()
{
	if (!bIsRevertMode)
	{
		bIsSpeedUpMode = true;
		ShipCharacter->ShipMovement->MaxSpeed = ShipCharacter->MaxSpeed + SpeedGap;
		ShipCharacter->ShipMovement->Acceleration = ShipCharacter->Acceleration * ShipCharacter->AccelerationRate;
	}
}

void AC_SystemCharacterController::ShipSpeedEnd()
{
	bIsSpeedUpMode = false;
	ShipCharacter->ShipMovement->MaxSpeed = ShipCharacter->MaxSpeed;
	ShipCharacter->ShipMovement->Acceleration = ShipCharacter->Acceleration;
}

void AC_SystemCharacterController::UpdateSpeedState(float DeltaSeconds)
{
	CurSpeed = ShipCharacter->GetVelocity().Size();
	if ( RushLeft <= 0 )
	{
		bIsRevertMode = true;
		ShipSpeedEnd();
	}
	else if (bIsRevertMode && RushLeft > RushLestAlarm)
	{
		bIsRevertMode = false;
	}

	RushLeft += !bIsSpeedUpMode ? ( RushRevertRate * DeltaSeconds ):( -RushRevertRate * DeltaSeconds );
	RushLeft = FMath::Min(RushLeft, ShipCharacter->MaxRushTime);
	if (ShipUI && ShipUI->Bar_SpeedUp) 
	{
		if (RushLeft < RushLestAlarm)
		{
			ShipUI->Bar_SpeedUp->SetFillColorAndOpacity(FLinearColor(FColor::Red));
		}
		else
		{
			ShipUI->Bar_SpeedUp->SetFillColorAndOpacity(FLinearColor(FColor::Green));
		}
		ShipUI->Bar_SpeedUp->SetPercent(RushLeft / ShipCharacter->MaxRushTime);
	}
	if (ShipUI && ShipUI->Bar_Speed) 
	{
		float temp = FMath::Min(CurSpeed / ShipCharacter->MaxSpeed , 1.0f);
		ShipUI->Bar_Speed->SetPercent(temp);
		if (ShipUI->Bar_ExtraSpeed && temp == 1)
		{
			float extra = (CurSpeed - ShipCharacter->MaxSpeed) / (SpeedGap);
			ShipUI->Bar_ExtraSpeed->SetPercent(extra);
		}
	}

	if (bIsSpeedUpMode){
		if (ShipCharacter->SpringArmCom->TargetArmLength > ArmMinLength)
		{
			ShipCharacter->SpringArmCom->TargetArmLength -= ArmLenChangeRate * DeltaSeconds;
		}
		if (ShipCharacter->CameraCom->FieldOfView < CamMaxField) 
		{
			ShipCharacter->CameraCom->FieldOfView += CamAngChangeRate * DeltaSeconds;
		}
	}
	else{
		if (ShipCharacter->SpringArmCom->TargetArmLength < ArmBaseLength) 
		{
			ShipCharacter->SpringArmCom->TargetArmLength += ArmLenChangeRate * DeltaSeconds;
		}
		if (ShipCharacter->CameraCom->FieldOfView > CamBaseField) 
		{
			ShipCharacter->CameraCom->FieldOfView -= CamAngChangeRate * DeltaSeconds;
		}
	}

}

#pragma endregion

#pragma region Widget about Overlap With Star
void AC_SystemCharacterController::OverlapStar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	if (ShipCharacter->bIsInWarMode)
	{
		return;
	}
	AC_NormalPlanetPawn* tempStar = Cast<AC_NormalPlanetPawn>(OtherActor);
	if (tempStar) 
	{
		if (StarInfor) 
		{
			if (StarInfor->TextBlock_Name) 
			{
				StarInfor->TextBlock_Name->SetText(FText::FromString(tempStar->StarName));
			}
			if (StarInfor->TextBlock_Intro)
			{
				StarInfor->TextBlock_Intro->SetText(FText::FromString(tempStar->StarIntrodoce));
			}
			if (StarInfor->Image_Pic) 
			{ 
				StarInfor->Image_Pic->SetBrushFromTexture(tempStar->StarPicture); 
			}
			if (tempStar->StarName != "")  
			{
				TargetMapName = tempStar->StarMap;
			}
			UGameplayStatics::SetGamePaused(this,true);
			bShowMouseCursor = true;
			StarInfor->AddToViewport();
		}
	}
}

void AC_SystemCharacterController::StarCloseBtnOnClicked()
{
	UGameplayStatics::SetGamePaused(this, false);
	bShowMouseCursor = false;
	StarInfor->RemoveFromViewport();
}

void AC_SystemCharacterController::StarExploreBtnOnClicked()
{
	UGameplayStatics::SetGamePaused(this, false);
	bShowMouseCursor = false;
	StarInfor->RemoveFromViewport();
	UGameplayStatics::OpenLevel(GetWorld(), *TargetMapName);
}

#pragma endregion

#pragma region Fire Relatied
void AC_SystemCharacterController::Fire()
{
	if (BulletStateCheck() == true)
	{
		FireLocation = ShipCharacter->ShipMesh->GetSocketLocation(TEXT("BulletSpawner"));
		FireRotation = ShipCharacter->CollisionCom->GetComponentRotation();

		AC_Bullet_Base* test = Cast<AC_Bullet_Base>(
			GetWorld()->SpawnActor(BulletItemList[CurrentIndex].BulletClass,
				&FireLocation, &FireRotation));

		BulletItemList[CurrentIndex].CurrentAccout = BulletItemList[CurrentIndex].CurrentAccout - 1;
		BulletItemList[CurrentIndex].CurrentLoadingTime = 
					BulletItemList[CurrentIndex].BulletClass.GetDefaultObject()->BulletLoadingTime;
	}
}

void AC_SystemCharacterController::ChangeBulletAdd()
{
	ChangeBulletWindow(CurrentIndex, false);
	if (BulletItemList.Num() > 0)
	{
		if (CurrentIndex == BulletItemList.Num() - 1)
		{
			//CurrentBullet = BulletItemList[0].BulletClass;
			CurrentIndex = 0;
		}
		else
		{
			//CurrentBullet = BulletItemList[CurrentIndex + 1].BulletClass;
			CurrentIndex ++;
		}
	}
	ChangeBulletWindow(CurrentIndex, true);
}

void AC_SystemCharacterController::ChangeBulletExtract()
{
	ChangeBulletWindow(CurrentIndex, false);
	if (BulletItemList.Num() > 0)
	{
		if (CurrentIndex == 0)
		{
			//CurrentBullet = BulletItemList[ShipCharacter->BulletList.Num() - 1].BulletClass;
			CurrentIndex = BulletItemList.Num() - 1;
		}
		else
		{
			//CurrentBullet = BulletItemList[CurrentIndex - 1].BulletClass;
			CurrentIndex--;
		}
	}
	ChangeBulletWindow(CurrentIndex, true);
}

void AC_SystemCharacterController::ChangeBulletWindow(float WindowIndex, bool bIsUpgrade)
{
	if (ShipUI)
	{
		if (bIsUpgrade)
		{
			ShipUI->BulletOut[WindowIndex]->SetColorAndOpacity(FColor::White);
			ShipUI->BulletOut[WindowIndex]->SetBrushSize(FVector2D(BulletWindowBaseSize * 1.05));
			ShipUI->BulletPic[WindowIndex]->SetOpacity(1.0f);
			ShipUI->BulletPic[WindowIndex]->SetBrushSize(FVector2D(BulletWindowBaseSize * 1.05));
			ShipUI->BulletNum[WindowIndex]->SetOpacity(1.0f);
		}
		else
		{
			ShipUI->BulletOut[WindowIndex]->SetColorAndOpacity(FColor::Black);
			ShipUI->BulletOut[WindowIndex]->SetBrushSize(FVector2D(BulletWindowBaseSize));
			ShipUI->BulletPic[WindowIndex]->SetOpacity(0.5f);
			ShipUI->BulletPic[WindowIndex]->SetBrushSize(FVector2D(BulletWindowBaseSize));
			ShipUI->BulletNum[WindowIndex]->SetOpacity(0.8f);
		}
	}
}

bool AC_SystemCharacterController::GenerateBulletItem()
{
	if (ShipCharacter->BulletList.Num() == 0)
	{
		return false;
	}
	for (int i = 0; i < ShipCharacter->BulletList.Num(); i++)
	{
		FBulletBagItem tempBulletItem;
		tempBulletItem.TotalAccout = 999;
		tempBulletItem.CurrentAccout = 999;
		tempBulletItem.CurrentLoadingTime = 0;
		tempBulletItem.BulletClass = ShipCharacter->BulletList[i];
		BulletItemList.Add(tempBulletItem);
	}
	return true;
}

bool AC_SystemCharacterController::BulletStateCheck()
{
	if (CurrentIndex < BulletItemList.Num()
		&& BulletItemList[CurrentIndex].CurrentAccout > 0
		&& BulletItemList[CurrentIndex].CurrentLoadingTime <= 0
		)
	{
		return true;
	}
	UE_LOG(LogTemp, Warning, TEXT("FireNotAllow"));
	return false;
}

void AC_SystemCharacterController::UpdateBulletLoadingTime(float DeltaSeconds)
{

	for (int i = 0; i < BulletItemList.Num(); i++)
	{
		BulletItemList[i].CurrentLoadingTime = 
			FMath::Max(0.f, 
				BulletItemList[i].CurrentLoadingTime - DeltaSeconds);
	}
	for (int i = 0; i < ShipUI->BulletOut.Num(); i++)
	{
		if (ShipUI->BulletOut[i]->Visibility == ESlateVisibility::Visible)
		{
			ShipUI->BulletCD[i]->SetPercent(
				BulletItemList[i].CurrentLoadingTime / 
				BulletItemList[i].BulletClass.GetDefaultObject()->BulletLoadingTime);
			ShipUI->BulletNum[i]->SetText(FText::FromString(
				FString::FromInt( BulletItemList[i].CurrentAccout)));
		}
	}
}

float AC_SystemCharacterController::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Cast<AC_Bullet_EnemyNormal>(DamageCauser))
	{
		CalculateDamage(Damage);
	}
	return 0.0f;
}

#pragma endregion

#pragma region Shield Related
void AC_SystemCharacterController::GenerateNewShield()
{
	if (CurrentEqipedShield)
	{
		CurrentEqipedShield->SetEqipState(false);
		CurrentEqipedShield->Destroy();
	}
	if (ShipCharacter->CurrentShield)
	{
		CurrentEqipedShield = Cast<AC_Shield_Base>(GetWorld()->SpawnActor(ShipCharacter->CurrentShield));
		CurrentEqipedShield->AttachToComponent(ShipCharacter->ShipMesh, 
			FAttachmentTransformRules::KeepRelativeTransform);
		CurrentEqipedShield->SetActorRelativeScale3D(FVector(1.05f, 1.05f, 1.05f));
		CurrentEqipedShield->SetEqipState(true);
	}
}

void AC_SystemCharacterController::CalculateDamage(float Damage, bool bIfCalculateExtraDamage)
{
	if (CurrentEqipedShield && CurrentEqipedShield->CurrentShield > 0)
	{
		CurrentEqipedShield->AfterTakeDamage();
		CurrentEqipedShield->CurrentShield -= Damage;
		if (bIfCalculateExtraDamage && CurrentEqipedShield->CurrentShield < 0)
		{
			ShipState->PlayerCurrentHp -= CurrentEqipedShield->CurrentShield;
			CurrentEqipedShield->CurrentShield = 0;
			ShipState->CurrentShield = 0;
		}
		else
		{
			ShipState->CurrentShield = CurrentEqipedShield->CurrentShield;
		}
	}
	else
	{
		ShipState->PlayerCurrentHp -= Damage;
	}

	if (ShipState->PlayerCurrentHp < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Should Die"));
	}
}

void AC_SystemCharacterController::UpdatePlayerState()
{
	if (ShipState && ShipUI)
	{
		ShipUI->Bar_Blood->SetPercent( 
			ShipState->PlayerCurrentHp / ShipCharacter->TotalHP);

		if (CurrentEqipedShield)
		{
			ShipState->CurrentShield = CurrentEqipedShield->CurrentShield;
			ShipUI->Bar_Shield->SetPercent(
				CurrentEqipedShield->CurrentShield / CurrentEqipedShield->TotalShield);
		}
		else
		{
			ShipUI->Bar_Shield->SetPercent(0);
		}


		if (ShipUI->Bar_Blood->Percent < 0.2)
		{
			ShipUI->Bar_Blood->SetFillColorAndOpacity(FLinearColor(FColor::Red));
		}
		else
		{
			ShipUI->Bar_Blood->SetFillColorAndOpacity(FLinearColor(FColor::Green));
		}

		if (ShipUI->Bar_Shield->Percent < 0.2)
		{
			ShipUI->Bar_Shield->SetFillColorAndOpacity(FLinearColor(FColor::Red));
		}
		else
		{
			ShipUI->Bar_Shield->SetFillColorAndOpacity(FLinearColor(FColor::Yellow));
		}
	}

}
#pragma endregion
