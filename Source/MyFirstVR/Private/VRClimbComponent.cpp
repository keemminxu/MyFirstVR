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
	    // ���ʷ� ��� ���� ��Ʈ�ѷ� ��ġ���� ���� ��Ʈ�ѷ� ��ġ�� �������� �����Ѵ�.
		FVector deltaPosition = player->leftController->GetComponentLocation() - startClimbingPos_Left;

		// ��Ʈ�ѷ� �������� �ݴ� �������� �÷��̾� ��ü�� ��ġ�� �̵���Ų��.
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
	// �ö� ��ü�� ��� �ִ� ��Ȳ�ΰ�?
	if (!bCanClimbing_Left)
	{
		return;
	}

	// ���� �ö󰡰� �ִ� ���ΰ�?
	if (!bIsClimbing_Left)
	{
		bIsClimbing_Left = true;
		// ���� ��� ��Ʈ�ѷ��� ��ġ ���� �����Ѵ�.
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