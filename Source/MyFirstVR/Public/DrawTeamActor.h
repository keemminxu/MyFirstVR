// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DrawTeamActor.generated.h"

UCLASS()
class MYFIRSTVR_API ADrawTeamActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrawTeamActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = TeamSettings)
	TArray<FString> WholeNames;
	UPROPERTY(EditAnywhere, Category = TeamSettings)
	TArray<FString> Team1;
	UPROPERTY(EditAnywhere, Category = TeamSettings)
	TArray<FString> Team2;
	UPROPERTY(EditAnywhere, Category = TeamSettings)
	TArray<FString> Team3;
	UPROPERTY(EditAnywhere, Category = TeamSettings)
	TArray<FString> Team4;
	UPROPERTY(EditAnywhere, Category = TeamSettings)
	TArray<FString> Team5;

private:
	void DrawRandomTeam();
};
