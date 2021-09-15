// Fill out your copyright notice in the Description page of Project Settings.


#include "VRGazeComponent.h"
#include "VR_Player.h"
#include "Camera/CameraComponent.h"

UVRGazeComponent::UVRGazeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UVRGazeComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(GetOwner());
}


void UVRGazeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckGazeState(DeltaTime);
}

// ������ �����Ͱ� ������ �����ϰ� �ִ����� üũ�ϴ� �Լ�
void UVRGazeComponent::CheckGazeState(float deltaTime)
{
	FHitResult hitInfo;
	FVector startPos = player->playerCam->GetComponentLocation();
	FVector endPos = startPos + player->playerCam->GetForwardVector()*1000.f;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	// ���� Ʈ���̽� �߻�!
	if (GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params))
	{
		// ����, �����ϰ� �ִ� ��ü�� ���ٸ�, ���� ��ü�� �����Ѵ�.
		if(gazeActor == nullptr)
		{
			gazeActor = hitInfo.GetActor();
		}
		// �׷��� �ʴٸ�...
		else
		{
			// 1. ���� �����ϴ� ��ü�� ���� �������� ���� ��ü�� �����ϴٸ� ������ �����͸� Ȯ���Ų��.
			if (gazeActor == hitInfo.GetActor())
			{
				GazeCounting(true, deltaTime);
			}
			// 2. ���� �����ϴ� ��ü�� ���� �������� ���� ��ü�� �ٸ��ٸ�, ���� ��ü ������ �����Ѵ�.
			else
			{
				gazeActor = hitInfo.GetActor();
			}

		}
	}
	else
	{
		// ������ �����͸� ��ҽ�Ų��.
		GazeCounting(false, deltaTime);

		// ���� ��ü �����͸� ����д�.
		gazeActor = nullptr;
	}
}

// ������ �������� ����� Ȯ���ϰų� ����ϴ� �Լ�
void UVRGazeComponent::GazeCounting(bool ascent, float deltaTime)
{
	processTime = ascent ? FMath::Min(processTime + deltaTime, changeTime) : FMath::Max(processTime - deltaTime, 0.0f);
	FVector currentSize = FMath::Lerp(initSize, maxSize, processTime / changeTime);

	player->gazePointer->SetRelativeScale3D(currentSize);
}