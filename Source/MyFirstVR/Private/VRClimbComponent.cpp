// Fill out your copyright notice in the Description page of Project Settings.


#include "VRClimbComponent.h"
#include "VR_Player.h"
#include "Components/CapsuleComponent.h"
#include "MotionControllerComponent.h"
#include "Components/TextRenderComponent.h"

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

	FVector deltaPosition;

	if (bIsClimbing_Left)
	{
	    // 최초로 등반 시작 콘트롤러 위치에서 현재 콘트롤러 위치의 변위량을 저장한다.
		deltaPosition = player->leftController->GetComponentLocation() - startClimbingPos_Left;

		
	}
	else if (bIsClimbing_Right)
	{
		deltaPosition = player->rightController->GetComponentLocation() - startClimbingPos_Right;
	}

	// 콘트롤러 변위량의 반대 방향으로 플레이어 본체의 위치를 이동시킨다.
	player->AddActorWorldOffset(deltaPosition * -1.0f);
}

void UVRClimbComponent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("LeftGrip", IE_Pressed, this, &UVRClimbComponent::StartClimbingLeft);
	PlayerInputComponent->BindAction("LeftGrip", IE_Released, this, &UVRClimbComponent::EndClimbingLeft);
	PlayerInputComponent->BindAction("RightGrip", IE_Pressed, this, &UVRClimbComponent::StartClimbingRight);
	PlayerInputComponent->BindAction("RightGrip", IE_Released, this, &UVRClimbComponent::EndClimbingRight);
}

void UVRClimbComponent::StartClimbingLeft()
{
	FHitResult hitInfo;
	FVector startPos = player->leftController->GetComponentLocation() + player->leftController->GetForwardVector() * 10;
	FCollisionObjectQueryParams objParams;
	objParams.AddObjectTypesToQuery(ECC_GameTraceChannel3);

	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	bCanClimbing_Left = GetWorld()->SweepSingleByObjectType(hitInfo, startPos, startPos, FQuat::Identity, objParams, FCollisionShape::MakeSphere(5), params);
	
	if(hitInfo.GetActor() != nullptr)
	{
		player->leftLog->SetText(FText::FromString(hitInfo.GetActor()->GetName()));
	}

	// 올라갈 물체를 쥐고 있는 상황인가?
	if (!bCanClimbing_Left)
	{
		return;
	}

	// 지금 올라가고 있던 중인가?
	if (!bIsClimbing_Left)
	{
		bIsClimbing_Left = true;
		bIsClimbing_Right = false;
		// 현재 모션 콘트롤러의 위치 값을 저장한다.
		startClimbingPos_Left = player->leftController->GetComponentLocation();

		if (player)
		{
			player->capsuleComp->SetSimulatePhysics(false);
		}
	}
}

void UVRClimbComponent::EndClimbingLeft()
{
	bIsClimbing_Left = false;
	if (player && !bIsClimbing_Right)
	{
		player->capsuleComp->SetSimulatePhysics(true);
	}
}

void UVRClimbComponent::StartClimbingRight()
{
	FHitResult hitInfo;
	FVector startPos = player->rightController->GetComponentLocation() + player->rightController->GetForwardVector() * 10;
	FCollisionObjectQueryParams objParams;
	objParams.AddObjectTypesToQuery(ECC_GameTraceChannel3);

	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	bCanClimbing_Right = GetWorld()->SweepSingleByObjectType(hitInfo, startPos, startPos, FQuat::Identity, objParams, FCollisionShape::MakeSphere(5), params);

	// 올라갈 물체를 쥐고 있는 상황인가?
	if (!bCanClimbing_Right)
	{
		return;
	}

	// 지금 올라가고 있던 중인가?
	if (!bIsClimbing_Right)
	{
		bIsClimbing_Right = true;
		bIsClimbing_Left = false;

		// 현재 모션 콘트롤러의 위치 값을 저장한다.
		startClimbingPos_Right = player->rightController->GetComponentLocation();

		if (player)
		{
			player->capsuleComp->SetSimulatePhysics(false);
		}
	}
}

void UVRClimbComponent::EndClimbingRight()
{
	bIsClimbing_Right = false;
	if (player && !bIsClimbing_Left)
	{
		player->capsuleComp->SetSimulatePhysics(true);
	}
}