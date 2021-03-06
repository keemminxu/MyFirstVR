// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Player.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "MoveActorComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "HandActorComponent.h"
#include "GrabActorComponent.h"
#include "VRMovieComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "VRGazeComponent.h"
#include "VRClimbComponent.h"

AVR_Player::AVR_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	SetRootComponent(capsuleComp);
	capsuleComp->SetCapsuleHalfHeight(65.0f);
	capsuleComp->SetCapsuleRadius(40.0f);
	capsuleComp->SetCollisionProfileName(TEXT("VR_Player"));

	bodyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	bodyComp->SetupAttachment(RootComponent);
	bodyComp->SetRelativeScale3D(FVector(0.8f, 0.8f, 1.2f));

	cameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	cameraRoot->SetupAttachment(RootComponent);
	cameraRoot->SetRelativeLocation(FVector(0, 0, 30.0f));

	playerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	playerCam->SetupAttachment(cameraRoot);

	gazePointer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gaze Pointer"));
	gazePointer->SetupAttachment(playerCam);
	gazePointer->SetRelativeLocation(playerCam->GetForwardVector() * 200);
	gazePointer->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	leftController->SetupAttachment(cameraRoot);
	leftController->MotionSource = "Left";

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	rightController->SetupAttachment(cameraRoot);
	rightController->MotionSource = "Right";

	leftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetRelativeRotation(FRotator(0, 0, -90.0f));
	leftHand->SetRelativeScale3D(FVector(1.0f, -1.f, 1.f));

	rightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetRelativeRotation(FRotator(0, 0, 90.0f));

	widgetPointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Widget Pointer"));
	widgetPointer->SetupAttachment(rightController);

	// 3D ?????? ?????????? ???? ???? ??????
	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log"));
	leftLog->SetupAttachment(leftController);
	// ???? ????
	leftLog->SetWorldSize(20);
	// ???? ????(?????? ????)
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);
	// ???? ????
	leftLog->SetTextRenderColor(FColor::Yellow);
	leftLog->SetRelativeRotation(FRotator(0, 180.0f, 0));
	leftLog->SetRelativeLocation(FVector(0, 0, 40.f));

	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log"));
	rightLog->SetupAttachment(rightController);
	rightLog->SetWorldSize(20);
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);
	rightLog->SetTextRenderColor(FColor::Yellow);
	rightLog->SetRelativeRotation(FRotator(0, 180.0f, 0));
	rightLog->SetRelativeLocation(FVector(0, 0, 40.f));

	// ???? ??????????
	moveComp = CreateDefaultSubobject<UMoveActorComponent>(TEXT("MoveComponent"));
	handComp = CreateDefaultSubobject<UHandActorComponent>(TEXT("HandComponent"));
	grabComp = CreateDefaultSubobject<UGrabActorComponent>(TEXT("GrabComponent"));
	movieComp = CreateDefaultSubobject<UVRMovieComponent>(TEXT("MovieComponent"));
	gazeComp = CreateDefaultSubobject<UVRGazeComponent>(TEXT("GazeComponent"));
	climbComp = CreateDefaultSubobject<UVRClimbComponent>(TEXT("ClimbComponent"));

	// ???????? ???????? ????
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AVR_Player::BeginPlay()
{
	Super::BeginPlay();
	
	// ???? ?????? ?????????? ?????? ???? ???????? ????????
	UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(hmdRotate, hmdLocation);

	// HMD ?????? ???????? ???????? ????????
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);

	// HMD ?????? ?????? ??????????
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ???? ???? ?? ???? ???????????? ????????
	moveComp->SetupPlayerInputComponent(PlayerInputComponent);
	grabComp->SetupPlayerInputComponent(PlayerInputComponent);
	movieComp->SetupPlayerInputComponent(PlayerInputComponent);
	climbComp->SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("HMDReset", IE_Pressed, this, &AVR_Player::ResetHMD);

	// ???? ??????
	//PlayerInputComponent->BindAction("RightTrigger", IE_Pressed, this, &AVR_Player::Fire1);
	//PlayerInputComponent->BindAction("RightGrip", IE_Pressed, this, &AVR_Player::Fire2);

	// ?????? ??????
	//PlayerInputComponent->BindAxis("LeftThumbstick_X", this, &AVR_Player::HorizontalMove);
	//PlayerInputComponent->BindAxis("LeftThumbstick_Y", this, &AVR_Player::VerticalMove);
}

void AVR_Player::Fire1()
{
	rightLog->SetText(FText::FromString("Trigger R"));
}

void AVR_Player::Fire2()
{
	rightLog->SetText(FText::FromString("Grip!!"));
}

void AVR_Player::HorizontalMove(float value)
{
	FString stickValue = FString::Printf(TEXT("x: %f"), value);
	leftLog->SetText(FText::FromString(stickValue));
}

void AVR_Player::VerticalMove(float value)
{
	// thumbstick?? y?? ??
	FString stickValue = FString::Printf(TEXT("\r\ny: %f"), value);
	// ???? ?????? ???? ???? ????
	FText curText = leftLog->Text;
	// ???? ?????? ?????? ????
	FText interMission = FText::FromString(", ");
	// ???? ??????
	FText resultText = FText::Join(interMission, curText, FText::FromString(stickValue));

	leftLog->SetText(resultText);
}

void AVR_Player::ResetHMD()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}