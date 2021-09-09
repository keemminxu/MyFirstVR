// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrabActorComponent.generated.h"

UENUM()
enum class EGrabType : uint8
{
	EGT_LineType UMETA(DisplayName ="LineType"),
	EGT_SweepType UMETA(DisplayName = "SweepType"),
};


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GrabSettings)
	EGrabType myGrabType = EGrabType::EGT_LineType;

private:
	void ShowGrabLine();
	void HideGrabLine();
	void DrawGrabLine();
	void GrabAction();
	void ReleaseAction();

	bool bIsShowing = false;
	class APickUpActor* pickObject;
	class AVR_Player* player;
	FHitResult grabObject;
	
};
