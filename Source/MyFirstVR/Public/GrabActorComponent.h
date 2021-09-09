// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTVR_API UGrabActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGrabActorComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	
	UPROPERTY(EditAnywhere, Category = GrabSettings)
	float grabDistance = 1000.f;

private:
	void ShowGrabLine();
	void HideGrabLine();
	void DrawGrabLine();
	void GrabAction();

	bool bIsShowing = false;
	class APickUpActor* pickObject;
	class AVR_Player* player;

	
};
