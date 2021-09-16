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
	    // ���ʷ� ��� ���� ��Ʈ�ѷ� ��ġ���� ���� ��Ʈ�ѷ� ��ġ�� �������� �����Ѵ�.
		deltaPosition = player->leftController->GetComponentLocation() - startClimbingPos_Left;

		
	}
	else if (bIsClimbing_Right)
	{
		deltaPosition = player->rightController->GetComponentLocation() - startClimbingPos_Right;
	}

	// ��Ʈ�ѷ� �������� �ݴ� �������� �÷��̾� ��ü�� ��ġ�� �̵���Ų��.
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

	// �ö� ��ü�� ��� �ִ� ��Ȳ�ΰ�?
	if (!bCanClimbing_Left)
	{
		return;
	}

	// ���� �ö󰡰� �ִ� ���ΰ�?
	if (!bIsClimbing_Left)
	{
		bIsClimbing_Left = true;
		bIsClimbing_Right = false;
		// ���� ��� ��Ʈ�ѷ��� ��ġ ���� �����Ѵ�.
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

	// �ö� ��ü�� ��� �ִ� ��Ȳ�ΰ�?
	if (!bCanClimbing_Right)
	{
		return;
	}

	// ���� �ö󰡰� �ִ� ���ΰ�?
	if (!bIsClimbing_Right)
	{
		bIsClimbing_Right = true;
		bIsClimbing_Left = false;

		// ���� ��� ��Ʈ�ѷ��� ��ġ ���� �����Ѵ�.
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