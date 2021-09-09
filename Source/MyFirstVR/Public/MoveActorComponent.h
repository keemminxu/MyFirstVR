// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTVR_API UMoveActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMoveActorComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UPROPERTY(EditAnywhere, Category = MoveSettings)
	float moveSpeed = 500;

	UPROPERTY(EditAnywhere, Category = MoveSettings)
	float rotateSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = MoveSettings)
	FVector simulDirection = FVector(100, 0, 100);

	UPROPERTY(EditAnywhere, Category = MoveSettings)
	float shootPower = 10.f;

	UPROPERTY(EditAnywhere, Category = MoveSettings)
	TSubclassOf<class ATestBallActor> testBall;

private:
	void MoveHorizontal(float value);
	void MoveVertical(float value);
	void RotateHorizontal(float value);
	void DrawTrajectory();
	void ShowLine();
	void HideLine();
	void ShootBall();
	void TeleportMySelf();
	void MoveTeleportLocation();

	class AVR_Player* player;

	bool bIsShowingLine = false;
	FVector teleportLocation;

	FTimerHandle teleportTimer;
};
