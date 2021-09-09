// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabActorComponent.h"
#include "PickUpActor.h"
#include "VR_Player.h"
#include "DrawDebugHelpers.h"

UGrabActorComponent::UGrabActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UGrabActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// �÷��̾� ĳ���ϱ�
	player = Cast<AVR_Player>(GetOwner());
}


void UGrabActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsShowing)
	{
		DrawGrabLine();
	}
}

void UGrabActorComponent::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("RightGrip", IE_Pressed, this, &UGrabActorComponent::ShowGrabLine);
	PlayerInputComponent->BindAction("RightGrip", IE_Released, this, &UGrabActorComponent::HideGrabLine);
	PlayerInputComponent->BindAction("RightTrigger", IE_Pressed, this, &UGrabActorComponent::GrabAction);
}

void UGrabActorComponent::ShowGrabLine()
{
	bIsShowing = true;
}

void UGrabActorComponent::HideGrabLine()
{
	bIsShowing = false;
}

void UGrabActorComponent::DrawGrabLine()
{
	if (pickObject == nullptr)
	{
		FHitResult hitInfo;
		FVector startPos = player->rightHand->GetComponentLocation();
		FVector endPos = startPos + player->rightHand->GetForwardVector() * grabDistance;
		
		// ���� ��ü�� ���� ��ü�� ���ؼ� �浹 üũ
		FCollisionObjectQueryParams objParams;
		objParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		objParams.AddObjectTypesToQuery(ECC_PhysicsBody);

		// �÷��̾� ���ʹ� ����
		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(player);

		if (GetWorld()->LineTraceSingleByObjectType(hitInfo, startPos, endPos, objParams, queryParams))
		{
			DrawDebugLine(GetWorld(), startPos, hitInfo.ImpactPoint, FColor::Green, false, -1, 0, 2);
		}
		else
		{
			DrawDebugLine(GetWorld(), startPos, endPos, FColor::Green, false, -1, 0, 2);
		}
	}
}


void UGrabActorComponent::GrabAction()
{

}