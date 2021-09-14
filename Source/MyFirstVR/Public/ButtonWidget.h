// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTVR_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Play;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_back;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_forward;

	class AMyVideoActor* videoActor;

private:
	UFUNCTION()
	void MediaPlay();

	UFUNCTION()
	void MediaBack();

	UFUNCTION()
	void MediaForward();

};
