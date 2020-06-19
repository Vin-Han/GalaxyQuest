#include "../Public/Character/C_SystemCharacter.h"
#include "../Public/Projectile/C_Bullet_EnemyNormal.h" 

#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"

AC_SystemCharacter::AC_SystemCharacter() 
{
	/*Initialize Components*/
	CollisionCom = CreateDefaultSubobject<UBoxComponent>		(TEXT("CollisionComponent"));
	SpringArmCom = CreateDefaultSubobject<USpringArmComponent>	(TEXT("SpringArmComponent"));
	CameraCom	 = CreateDefaultSubobject<UCameraComponent>		(TEXT("CameraComponent"));
	ShipMesh	 = CreateDefaultSubobject<UStaticMeshComponent>	(TEXT("ShipMesh"));
	ShipMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	/*Set Relationship Between Components*/
	RootComponent = CollisionCom;
	SpringArmCom->SetupAttachment(RootComponent);
	ShipMesh->SetupAttachment(RootComponent);
	CameraCom->SetupAttachment(SpringArmCom);

	/*Move Control Relate*/
	SpringArmCom->bUsePawnControlRotation = true;
	CameraSpeed = 1;
	RotateSpeed = 1;
	MaxSpeed	= 1200;
	DecayRate	= 1200;
	Acceleration= 1200;

	/*Speed Rush Related*/
	MaxSpeedRate = 2.0;
	AccelerationRate = 2.0;
	ArmChangeRatio = 0.7f;
	CameraChangeRatio = 1.3f;
	ChangeDuration = 0.3f;
	MaxRushTime = 10;
	RushTimeRevertTime = 5;
	RushLeftAlarmRate = 0.2;

	TotalHP = 300;
}
/*
float AC_SystemCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Cast<AC_Bullet_EnemyNormal>(DamageCauser))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit By Enemy Bullet"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("It Is Not Enemy Bullet"));
	}
	return 0.0f;
}
*/