// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LogUI_Widget.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTVR_API ULogUI_Widget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* logText;
};
