// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActorComponent.h"
#include "VR_Player.h"
#include "MotionControllerComponent.h"
#include "DrawDebugHelpers.h"

UMoveActorComponent::UMoveActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(GetOwner());

}


void UMoveActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 라인을 그릴지 말지 결정
	if (bIsShowingLine)
	{
		DrawTrajectory();
	}
}

void UMoveActorComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("RightThumbstick_X", this, &UMoveActorComponent::MoveHorizontal);
	PlayerInputComponent->BindAxis("RightThumbstick_Y", this, &UMoveActorComponent::MoveVertical);
	PlayerInputComponent->BindAxis("LeftThumbstick_X", this, &UMoveActorComponent::RotateHorizontal);
	PlayerInputComponent->BindAction("LeftGrip", IE_Pressed, this, &UMoveActorComponent::ShowLine);
	PlayerInputComponent->BindAction("LeftGrip", IE_Released, this, &UMoveActorComponent::HideLine);
}

void UMoveActorComponent::MoveHorizontal(float value)
{
	if(player == nullptr)
	{
		return;
	}

	FVector dir = player->GetActorRightVector() * value;
	player->SetActorLocation(player->GetActorLocation() + dir * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void UMoveActorComponent::MoveVertical(float value)
{
	if (player == nullptr)
	{
		return;
	}

	FVector dir = player->GetActorForwardVector() * value;
	player->SetActorLocation(player->GetActorLocation() + dir * moveSpeed * GetWorld()->DeltaTimeSeconds);
}

void UMoveActorComponent::RotateHorizontal(float value)
{
	if (player == nullptr)
	{
		return;
	}

	FRotator rot = FRotator(0, value* rotateSpeed* GetWorld()->DeltaTimeSeconds, 0);
	player->AddActorLocalRotation(rot);
}

void UMoveActorComponent::DrawTrajectory()
{
	// 1. 몇 초동안 시뮬레이션 할 것인가? 5초
	float simulationTime = 5.0f;

	// 2. 몇 번의 구획으로 예측을 구분할 것인가? 50번
	float interval = 50.0f;
	float timeSegment = simulationTime / interval;

	// 3. 시뮬레이션 결과 값을 담을 변수
	TArray<FVector> linePosition;

	FVector starPos = player->leftController->GetComponentLocation();
	FVector shootDirection = simulDirection * shootPower;

	// 발사 방향을 월드 좌표에서 왼손 모션 콘트롤러를 기준으로 하는 로컬 좌표로 환산한다.
	shootDirection = player->leftController->GetComponentTransform().TransformVectorNoScale(shootDirection);


	for (int i = 0; i < interval; i++)
	{
		float realTime = timeSegment * i;

		float xPos = shootDirection.X * realTime;
		float yPos = shootDirection.Y * realTime;
		float zPos = shootDirection.Z * realTime - 980.0f * realTime * realTime * 0.5f;

		FVector predictPosition = starPos + FVector(xPos, yPos,zPos);

		// 예측 지점을 배열에 추가한다.
		linePosition.Add(predictPosition);
	}

	// 예측 배열에 맞춰 라인 그리기
	for (int i = 0; i < linePosition.Num() - 1; i++)
	{
		DrawDebugLine(GetWorld(), linePosition[i], linePosition[i+1], FColor::Red, false, -1, 0, 2.0f);
	}
}

void UMoveActorComponent::ShowLine()
{
	bIsShowingLine = true;
}

void UMoveActorComponent::HideLine()
{
	bIsShowingLine = false;
}
