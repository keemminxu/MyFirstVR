// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonWidget.h"
#include "Components/Button.h"

void UButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư �̺�Ʈ �ݹ� ���ε��ϱ�
	btn_Play->OnClicked.AddDynamic(this, &UButtonWidget::MediaPlay);
	btn_back->OnClicked.AddDynamic(this, &UButtonWidget::MediaBack);
	btn_forward->OnClicked.AddDynamic(this, &UButtonWidget::MediaForward);
}

void UButtonWidget::MediaPlay()
{

}

void UButtonWidget::MediaBack()
{

}

void UButtonWidget::MediaForward()
{

}