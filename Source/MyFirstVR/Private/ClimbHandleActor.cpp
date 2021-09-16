// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbHandleActor.h"
#include "Components/StaticMeshComponent.h"

AClimbHandleActor::AClimbHandleActor()
{
	PrimaryActorTick.bCanEverTick = false;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(meshComp);
	meshComp->SetGenerateOverlapEvents(true);
	meshComp->SetCollisionProfileName(TEXT("ClimbHandle"));
}

void AClimbHandleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

//void AClimbHandleActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

