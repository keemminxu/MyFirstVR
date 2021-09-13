// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPianoActor.generated.h"

UCLASS()
class MYFIRSTVR_API AMyPianoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyPianoActor();

protected:
	virtual void BeginPlay() override;

public:	
	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = KeySettings)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = KeySettings)
	TArray<class UChildActorComponent*> pianoKeyArray;

	UPROPERTY(EditAnywhere, Category = KeySettings)
	int32 keyCount = 8;
};
