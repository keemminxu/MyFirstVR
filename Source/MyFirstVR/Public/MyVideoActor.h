// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyVideoActor.generated.h"

UCLASS()
class MYFIRSTVR_API AMyVideoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyVideoActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = VideoSettings)
	class UMediaPlayer* mediaPlayer;

	UPROPERTY(EditAnywhere, Category = VideoSettings)
	class UMediaSource* mysource;

	UPROPERTY(EditAnywhere, Category = VideoSettings)
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = VideoSettings)
	class UStaticMeshComponent* screenMesh;

	UPROPERTY(EditAnywhere, Category = VideoSettings)
	class UMediaSoundComponent* soundComp;

	UPROPERTY(EditAnywhere, Category = VideoSettings)
	class UWidgetComponent* buttonWidgetComp;

	void PlayVideo();
	void BackVideo();
	void ForwardVideo();
};
