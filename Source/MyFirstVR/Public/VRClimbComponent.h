// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VRClimbComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTVR_API UVRClimbComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVRClimbComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	
private:
	bool bCanClimbing_Left = false;
	bool bIsClimbing_Left = false;
	bool bCanClimbing_Right = false;
	bool bIsClimbing_Right = false;

	void StartClimbingLeft();
	void EndClimbingLeft();
	void StartClimbingRight();
	void EndClimbingRight();

	class AVR_Player* player;
	FVector startClimbingPos_Left;
	FVector startClimbingPos_Right;
};
