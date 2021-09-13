// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPianoActor.h"
#include "PianoKeyActor.h"
#include "Components/ChildActorComponent.h"
#include "Components/SceneComponent.h"

AMyPianoActor::AMyPianoActor()
{
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	ConstructorHelpers::FClassFinder<APianoKeyActor> pianoBP(TEXT("/Game/Blueprints/BP_PianoKeyActor"));

	if (pianoBP.Succeeded())
	{
		// 자식 액터 생성하기
		for (int i = 0; i < keyCount; i++)
		{
			FString actorName = "PianoKey" + FString::FromInt(i + 1);
			pianoKeyArray.Add(CreateDefaultSubobject<UChildActorComponent>(FName(*actorName)));
			pianoKeyArray[i]->SetupAttachment(rootComp);
			pianoKeyArray[i]->SetChildActorClass(pianoBP.Class);
		}
	}
}

void AMyPianoActor::BeginPlay()
{
	Super::BeginPlay();

}

//void AMyPianoActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

