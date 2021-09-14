// Fill out your copyright notice in the Description page of Project Settings.


#include "VRMovieComponent.h"
#include "VR_Player.h"
#include "Components/WidgetInteractionComponent.h"

UVRMovieComponent::UVRMovieComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


}


void UVRMovieComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AVR_Player>(GetOwner());
}

//void UVRMovieComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//}

void UVRMovieComponent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Right_A", IE_Pressed, this, &UVRMovieComponent::ButtonClick);
	PlayerInputComponent->BindAction("Right_A", IE_Released, this, &UVRMovieComponent::ButtonRelease);
}

void UVRMovieComponent::ButtonClick()
{
	// 위젯 인터렉션 포인터의 클릭 포인터 키 값을 마우스 왼쪽 버튼 클릭으로 설정한다.
	player->widgetPointer->PressPointerKey(EKeys::LeftMouseButton);
}

void UVRMovieComponent::ButtonRelease()
{
	player->widgetPointer->ReleasePointerKey(EKeys::LeftMouseButton);
}