// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCarPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "MotionControllerComponent.h"
#include "Components/WidgetComponent.h"
#include "LogUI_Widget.h"
#include "Components/TextBlock.h"

AMyCarPawn::AMyCarPawn()
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
	
	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	leftController->SetupAttachment(cameraRoot);
	leftController->MotionSource = "Left";

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	rightController->SetupAttachment(cameraRoot);
	rightController->MotionSource = "Right";

	logWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	logWidget->SetupAttachment(playerCam);
	logWidget->SetWorldLocation(playerCam->GetForwardVector() * 100);

	// 플레이어 컨트롤러 빙의
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMyCarPawn::BeginPlay()
{
	Super::BeginPlay();
	
	myLogWidget = Cast<ULogUI_Widget>(logWidget->GetWidget());
	//FString myLog = FString(TEXT("여기가 로그 쓰는 곳"));
	//myLogWidget->logText->SetText(FText::FromString(TEXT("한글 테스트")));

	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, TEXT("디버깅 결과"));
}

void AMyCarPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 루트의 rightVector와 모션 컨트롤러의 방향 벡터를 내적한다.

	FVector baseRight = capsuleComp->GetRightVector();
	FVector targetVec = (rightController->GetComponentLocation() - leftController->GetComponentLocation()).GetSafeNormal();

	// 내적하기(radian -> degree)
	float dotResult = FVector::DotProduct(baseRight, targetVec);
	float myDegree = FMath::Acos(dotResult);
	myDegree = FMath::RadiansToDegrees(myDegree);

	// 외적하기
	FVector crossResult = FVector::CrossProduct(baseRight, targetVec);

	// 결과를 출력한다.
	myLogWidget->logText->SetText(FText::FromString(FString::Printf(TEXT("각도: %f"), myDegree)));
	myLogWidget->logText->SetText(FText::FromString(FString::Printf(TEXT("\r\n외적 결과 x: %f\r\ny: %f\r\nz: %f"), crossResult.X, crossResult.Y, crossResult.Z)));

	// 외적 결과에 따라 각도 값의 +, -부호를 변경한다.
	myDegree = crossResult.X >= 0 ? -myDegree : myDegree;

	// 나를 그 각도 방향으로 회전시킨다.
	bodyComp->AddWorldRotation(FRotator(0, myDegree * 0.01f, 0));
}

void AMyCarPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

