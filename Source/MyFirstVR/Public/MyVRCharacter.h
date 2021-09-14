// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyVRCharacter.generated.h"

UCLASS()
class MYFIRSTVR_API AMyVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyVRCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
	class USceneComponent* cameraRoot;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
	class UCameraComponent* playerCam;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
	class UMotionControllerComponent* leftController;

	UPROPERTY(EditAnywhere, Category = PlayerSettings)
	class UMotionControllerComponent* rightController;


	FRotator hmdRotate;
	FVector hmdLocation;
	class UVRCharacterAnimInstance* anim;
};
