// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVideoActor.h"
#include "Components/SceneComponent.h"
#include "MediaPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "MediaSoundComponent.h"
#include "Components/WidgetComponent.h"
#include "ButtonWidget.h"

AMyVideoActor::AMyVideoActor()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	screenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Screen Mesh"));
	screenMesh->SetupAttachment(rootComp);
	screenMesh->SetRelativeScale3D(FVector(8.f, 4.5f, 1.f));

	soundComp = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("Media Sound"));
	soundComp->SetupAttachment(rootComp);

	buttonWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("ButtonWidget"));
	buttonWidgetComp->SetupAttachment(rootComp);
	buttonWidgetComp->SetRelativeLocation(FVector(0, 0, -280));
}

void AMyVideoActor::BeginPlay()
{
	Super::BeginPlay();
	
	UButtonWidget* btnWidget = Cast<UButtonWidget>(buttonWidgetComp->GetUserWidgetObject());

	if (btnWidget)
	{
		btnWidget->videoActor = this;
	}
}

void AMyVideoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyVideoActor::PlayVideo()
{
	// 미디어 플레이어를 이용하여 영상 소스를 실행하기
	if (mediaPlayer)
	{
		// 만일, 미디어 소스 파일이 열려져 있으면 종료하고...
		if (mediaPlayer->IsPlaying())
		{
			mediaPlayer->Close();
		}
		// 그렇지 않다면, 미디어 소스 파일을 연다.
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Video Play!!!!!!!!!!!!"));
			mediaPlayer->OpenSource(mysource);
		}
	}
}

void AMyVideoActor::BackVideo()
{
	// 만일, 미디어가 플레이 중이라면, 현재 시간 - 5초 부분을 플레이한다.
	if (mediaPlayer)
	{
		if (mediaPlayer->IsPlaying())
		{
			FTimespan playTime = mediaPlayer->GetTime() - FTimespan(0, 0, 5);
			mediaPlayer->Seek(playTime);
			mediaPlayer->Play();
		}
	}
}

void AMyVideoActor::ForwardVideo()
{
	// 만일, 미디어가 플레이 중이라면, 현재 시간 + 5초 부분을 플레이한다.
	if (mediaPlayer)
	{
		if (mediaPlayer->IsPlaying())
		{
			FTimespan playTime = mediaPlayer->GetTime() + FTimespan(0, 0, 5);
			mediaPlayer->Seek(playTime);
			mediaPlayer->Play();
		}
	}
}