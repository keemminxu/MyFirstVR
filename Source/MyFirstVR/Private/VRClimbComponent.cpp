// Fill out your copyright notice in the Description page of Project Settings.


#include "VRClimbComponent.h"
#include "VR_Player.h"
#include "Components/CapsuleComponent.h"
#include "MotionControllerComponent.h"

UVRClimbComponent::UVRClimbComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UVRClimbComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(GetOwner());
}


void UVRClimbComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsClimbing_Left)
	{
	    // 최초로 등반 시작 콘트롤러 위치에서 현재 콘트롤러 위치의 변위량을 저장한다.
		FVector deltaPosition = player->leftController->GetComponentLocation() - startClimbingPos_Left;

		// 콘트롤러 변위량의 반대 방향으로 플레이어 본체의 위치를 이동시킨다.
		player->AddActorWorldOffset(deltaPosition * -1.0f);
	}
}

void UVRClimbComponent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("LeftGrip", IE_Pressed, this, &UVRClimbComponent::StartClimbing);
	PlayerInputComponent->BindAction("LeftGrip", IE_Released, this, &UVRClimbComponent::EndClimbing);
}

void UVRClimbComponent::StartClimbing()
{
	// 올라갈 물체를 쥐고 있는 상황인가?
	if (!bCanClimbing_Left)
	{
		return;
	}

	// 지금 올라가고 있던 중인가?
	if (!bIsClimbing_Left)
	{
		bIsClimbing_Left = true;
		// 현재 모션 콘트롤러의 위치 값을 저장한다.
		startClimbingPos_Left = player->leftController->GetComponentLocation();

		if (player)
		{
			player->capsuleComp->SetSimulatePhysics(false);
		}
	}
}

void UVRClimbComponent::EndClimbing()
{
	bIsClimbing_Left = false;
	if (player)
	{
		player->capsuleComp->SetSimulatePhysics(true);
	}
}