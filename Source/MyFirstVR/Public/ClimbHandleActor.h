// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClimbHandleActor.generated.h"

UCLASS()
class MYFIRSTVR_API AClimbHandleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AClimbHandleActor();

protected:
	virtual void BeginPlay() override;

public:	
	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Settings)
	class UStaticMeshComponent* meshComp;
};
