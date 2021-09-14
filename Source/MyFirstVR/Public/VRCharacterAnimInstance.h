// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VRCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYFIRSTVR_API UVRCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IK_Settings)
	FVector leftHandLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IK_Settings)
	FRotator leftHandRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = IK_Settings)
	FVector rightHandLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = IK_Settings)
	FRotator rightHandRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = IK_Settings)
	FVector headLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = IK_Settings)
	FRotator headRotation;
};
