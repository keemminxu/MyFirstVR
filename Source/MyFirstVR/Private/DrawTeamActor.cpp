// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawTeamActor.h"

// Sets default values
ADrawTeamActor::ADrawTeamActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADrawTeamActor::BeginPlay()
{
	Super::BeginPlay();
	
	DrawRandomTeam();
}

void ADrawTeamActor::DrawRandomTeam()
{
	Team1.SetNum(16);

	for (int32 i = 0; i < WholeNames.Num(); i++)
	{
		int32 num = FMath::RandRange(0, WholeNames.Num() - 1);
		Team1[i] = WholeNames[num];

		for (int j = 0; j < i; j++)
		{
			if (Team1[j] == WholeNames[num])
			{
				i--;
			}
		}
	}
}


// Called every frame
void ADrawTeamActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


