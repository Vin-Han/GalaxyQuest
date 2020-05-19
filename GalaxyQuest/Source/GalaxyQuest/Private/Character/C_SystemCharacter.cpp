#include "../Public/Character/C_SystemCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetMathLibrary.h"

AC_SystemCharacter::AC_SystemCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	/*Initialize Components*/
	CollisionCom = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	SpringArmCom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraCom = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	ShipMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShipMesh"));
	RootComponent = CollisionCom;
	SpringArmCom->SetupAttachment(RootComponent);
	ShipMesh->SetupAttachment(RootComponent);
	CameraCom->SetupAttachment(SpringArmCom);

	/*Move Control Relate*/
	SpringArmCom->bUsePawnControlRotation = true;
	CameraSpeed = 1;
	RotateSpeed = 1;
	MoveSpeed = 5;
	AttenuationSpeed = 1;
	StopSpeed = 10;
}

void AC_SystemCharacter::BeginPlay()
{
	Super::BeginPlay();

}

#pragma region Move Control Relate
void AC_SystemCharacter::MouseUpDown(float value) {
	if (CameraSpeed < 1) AddControllerYawInput(value);
	else AddControllerYawInput(value * CameraSpeed);
}
void AC_SystemCharacter::MouseRightLeft(float value) {
	if (CameraSpeed < 1) AddControllerPitchInput(value);
	else AddControllerPitchInput(value * CameraSpeed);
}

void AC_SystemCharacter::MoveTurn(float value) {
	FRotator temp = FRotator::ZeroRotator;
	float rSpeed = (CurrentSpeed.Size() / 100) * (RotateSpeed * value / 30);
	temp.Yaw = rSpeed;
	AddActorWorldRotation(temp);
}
void AC_SystemCharacter::MoveUpDown(float value) {
	FRotator temp = FRotator::ZeroRotator;
	float rSpeed = (CurrentSpeed.Size() / 100) * (RotateSpeed * value / 30);
	temp.Pitch = rSpeed;
	CollisionCom->AddRelativeRotation(temp);
}

void AC_SystemCharacter::MoveForward(float value) {
	FVector temp = GetActorRotation().Vector();
	CollisionCom->AddImpulse(1000 * temp * MoveSpeed * value);
}
void AC_SystemCharacter::UpdateCurrentSpeed(float value)
{
	CurrentSpeed = GetVelocity();
	if (CurrentSpeed.Size() < StopSpeed)
		CurrentSpeed = FVector::ZeroVector;
	if (AttenuationSpeed != 0)
		CurrentSpeed -= CurrentSpeed * value / AttenuationSpeed;
	else CurrentSpeed -= CurrentSpeed * value;
	CollisionCom->SetPhysicsLinearVelocity(CurrentSpeed);
}
#pragma endregion

void AC_SystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCurrentSpeed(DeltaTime);
}

void AC_SystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("UpDown", this, &AC_SystemCharacter::MouseUpDown);
	PlayerInputComponent->BindAxis("RightLeft", this, &AC_SystemCharacter::MouseRightLeft);
	PlayerInputComponent->BindAxis("MoveForward", this, &AC_SystemCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveTurn", this, &AC_SystemCharacter::MoveTurn);
	PlayerInputComponent->BindAxis("MoveUpDown", this, &AC_SystemCharacter::MoveUpDown);
}

