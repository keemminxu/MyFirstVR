// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVideoActor.h"
#include "Components/SceneComponent.h"
#include "MediaPlayer.h"
#include "Components/StaticMeshComponent.h"

AMyVideoActor::AMyVideoActor()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	screenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Screen Mesh"));
	screenMesh->SetupAttachment(rootComp);
}

void AMyVideoActor::BeginPlay()
{
	Super::BeginPlay();
	
	PlayVideo(mysource);
}

void AMyVideoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyVideoActor::PlayVideo(UMediaSource* playSource)
{
	// �̵�� �÷��̾ �̿��Ͽ� ���� �ҽ��� �����ϱ�
	if (mediaPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("Video Play!!!!!!!!!!!!"));
		mediaPlayer->OpenSource(playSource);
	}
}