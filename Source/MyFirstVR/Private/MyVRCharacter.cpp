// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVRCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "VRCharacterAnimInstance.h"

AMyVRCharacter::AMyVRCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(GetCapsuleComponent());

	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	cameraRoot->SetupAttachment(RootComponent);
	cameraRoot->SetRelativeLocation(FVector(0, 0, 30.0f));

	playerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	playerCam->SetupAttachment(cameraRoot);

	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	leftController->SetupAttachment(cameraRoot);
	leftController->MotionSource = "Left";

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	rightController->SetupAttachment(cameraRoot);
	rightController->MotionSource = "Right";
}

void AMyVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// ��� ����Ʈ ���÷��� ��ġ�� �ʱ� ��ġ���� �����ϱ�
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotate, hmdLocation);

	// HMD ��ġ�� �������� �ٴ����� �����ϱ�
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);

	// HMD ��ġ�� ��ġ�� �ʱ�ȭ�ϱ�
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();

	anim = Cast<UVRCharacterAnimInstance>(GetMesh()->GetAnimInstance());
}

void AMyVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (anim)
	{
		// ��� ��Ʈ�ѷ��� ���� �ִϸ��̼� �ν��Ͻ��� ������ �����Ѵ�.
		anim->leftHandLocation = leftController->GetComponentLocation();
		anim->leftHandRotation = leftController->GetComponentRotation();
		anim->rightHandLocation = rightController->GetComponentLocation();
		anim->rightHandRotation = rightController->GetComponentRotation();
		anim->headLocation = playerCam->GetComponentLocation() - playerCam->GetForwardVector()* 0.15f;
		anim->headRotation = playerCam->GetComponentRotation();
	}


}

// Called to bind functionality to input
void AMyVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

