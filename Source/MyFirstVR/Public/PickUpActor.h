// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpActor.generated.h"

UCLASS()
class MYFIRSTVR_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APickUpActor();

protected:
	virtual void BeginPlay() override;

public:	
	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = PickUPSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = PickUPSettings)
	class UStaticMeshComponent* meshComp;
};
