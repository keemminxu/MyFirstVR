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

// 게이즈 포인터가 무엇을 응시하고 있는지를 체크하는 함수
void UVRGazeComponent::CheckGazeState(float deltaTime)
{
	FHitResult hitInfo;
	FVector startPos = player->playerCam->GetComponentLocation();
	FVector endPos = startPos + player->playerCam->GetForwardVector()*1000.f;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	// 라인 트레이스 발사!
	if (GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params))
	{
		// 만일, 응시하고 있던 객체가 없다면, 응시 객체를 설정한다.
		if(gazeActor == nullptr)
		{
			gazeActor = hitInfo.GetActor();
		}
		// 그렇지 않다면...
		else
		{
			// 1. 지금 응시하는 객체가 직전 프레임의 응시 객체와 동일하다면 게이즈 포인터를 확대시킨다.
			if (gazeActor == hitInfo.GetActor())
			{
				GazeCounting(true, deltaTime);
			}
			// 2. 지금 응시하는 객체가 직전 프레임의 응시 객체와 다르다면, 응시 객체 설정을 변경한다.
			else
			{
				gazeActor = hitInfo.GetActor();
			}

		}
	}
	else
	{
		// 게이즈 포인터를 축소시킨다.
		GazeCounting(false, deltaTime);

		// 응시 객체 포인터를 비워둔다.
		gazeActor = nullptr;
	}
}

// 게이즈 포인터의 사이즈를 확대하거나 축소하는 함수
void UVRGazeComponent::GazeCounting(bool ascent, float deltaTime)
{
	processTime = ascent ? FMath::Min(processTime + deltaTime, changeTime) : FMath::Max(processTime - deltaTime, 0.0f);
	FVector currentSize = FMath::Lerp(initSize, maxSize, processTime / changeTime);

	player->gazePointer->SetRelativeScale3D(currentSize);
}