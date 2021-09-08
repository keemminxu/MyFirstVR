// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBallActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

ATestBallActor::ATestBallActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(sphereComp);
	// physics off
	sphereComp->SetSimulatePhysics(false);
	sphereComp->SetEnableGravity(true);
	sphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATestBallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

//void ATestBallActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

