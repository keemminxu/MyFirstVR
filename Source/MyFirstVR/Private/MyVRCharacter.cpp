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
	
	// 헤드 마운트 디스플레이 장치의 초기 위치값을 설정하기
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotate, hmdLocation);

	// HMD 장치의 기준점을 바닥으로 설정하기
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);

	// HMD 장치의 위치를 초기화하기
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();

	anim = Cast<UVRCharacterAnimInstance>(GetMesh()->GetAnimInstance());
}

void AMyVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (anim)
	{
		// 모션 콘트롤러의 값을 애니메이션 인스턴스의 변수로 전달한다.
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

