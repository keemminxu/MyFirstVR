// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestBallActor.generated.h"

UCLASS()
class MYFIRSTVR_API ATestBallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATestBallActor();

protected:
	virtual void BeginPlay() override;

public:	
	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;
};
