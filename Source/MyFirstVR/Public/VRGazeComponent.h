// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VRGazeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFIRSTVR_API UVRGazeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVRGazeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = GazeSettings)
	FVector initSize = FVector(0.01f, 0.01f, 0.01f);

	UPROPERTY(EditAnywhere, Category = GazeSettings)
	FVector maxSize = FVector(0.1f, 0.1f, 0.1f);

	UPROPERTY(EditAnywhere, Category = GazeSettings)
	float changeTime = 3.0f;

private:
	void CheckGazeState(float deltaTime);
	void GazeCounting(bool ascent, float deltaTime);

	class AVR_Player* player;
	class AActor* gazeActor;

	float processTime;
};
