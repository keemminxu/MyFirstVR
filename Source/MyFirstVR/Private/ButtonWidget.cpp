// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonWidget.h"
#include "Components/Button.h"
#include "MyVideoActor.h"

void UButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 이벤트 콜백 바인딩하기
	btn_Play->OnClicked.AddDynamic(this, &UButtonWidget::MediaPlay);
	btn_back->OnClicked.AddDynamic(this, &UButtonWidget::MediaBack);
	btn_forward->OnClicked.AddDynamic(this, &UButtonWidget::MediaForward);
}

void UButtonWidget::MediaPlay()
{
	if (videoActor)
	{
		videoActor->PlayVideo();
	}
}

void UButtonWidget::MediaBack()
{
	if (videoActor)
	{
		videoActor->BackVideo();
	}
}

void UButtonWidget::MediaForward()
{
	if (videoActor)
	{
		videoActor->ForwardVideo();
	}
}