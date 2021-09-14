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
	// �̵�� �÷��̾ �̿��Ͽ� ���� �ҽ��� �����ϱ�
	if (mediaPlayer)
	{
		// ����, �̵�� �ҽ� ������ ������ ������ �����ϰ�...
		if (mediaPlayer->IsPlaying())
		{
			mediaPlayer->Close();
		}
		// �׷��� �ʴٸ�, �̵�� �ҽ� ������ ����.
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Video Play!!!!!!!!!!!!"));
			mediaPlayer->OpenSource(mysource);
		}
	}
}

void AMyVideoActor::BackVideo()
{
	// ����, �̵� �÷��� ���̶��, ���� �ð� - 5�� �κ��� �÷����Ѵ�.
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
	// ����, �̵� �÷��� ���̶��, ���� �ð� + 5�� �κ��� �÷����Ѵ�.
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