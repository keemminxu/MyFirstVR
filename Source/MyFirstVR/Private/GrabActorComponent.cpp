// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabActorComponent.h"
#include "PickUpActor.h"
#include "VR_Player.h"
#include "DrawDebugHelpers.h"
#include "HandActorComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

UGrabActorComponent::UGrabActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UGrabActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 캐싱하기
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
	PlayerInputComponent->BindAction("RightTrigger", IE_Released, this, &UGrabActorComponent::ReleaseAction);
}

void UGrabActorComponent::ShowGrabLine()
{
	bIsShowing = true;
}

void UGrabActorComponent::HideGrabLine()
{
	bIsShowing = false;
	grabObject = FHitResult();
}

void UGrabActorComponent::DrawGrabLine()
{
	if (pickObject == nullptr)
	{
		FHitResult hitInfo;
		FVector startPos = player->rightHand->GetComponentLocation();
		
		// 물리 객체와 동적 객체에 대해서 충돌 체크
		FCollisionObjectQueryParams objParams;
		objParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		objParams.AddObjectTypesToQuery(ECC_PhysicsBody);

		// 플레이어 액터는 무시
		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(player);

		if (myGrabType == EGrabType::EGT_LineType)
		{
			FVector endPos = startPos + player->rightHand->GetForwardVector() * grabDistance;

			if (GetWorld()->LineTraceSingleByObjectType(hitInfo, startPos, endPos, objParams, queryParams))
			{
				DrawDebugLine(GetWorld(), startPos, hitInfo.ImpactPoint, FColor::Green, false, -1, 0, 2);
				grabObject = hitInfo;
				player->rightLog->SetText(FText::FromString(hitInfo.GetActor()->GetName()));
			}
			else
			{
				DrawDebugLine(GetWorld(), startPos, endPos, FColor::Green, false, -1, 0, 2);
				grabObject = FHitResult();
			}
		}
		// 구체 형태로 검사하기 및 디버깅 스피어 그리기
		else if (myGrabType == EGrabType::EGT_SweepType)
		{
			if (GetWorld()->SweepSingleByObjectType(hitInfo, startPos, startPos, FQuat::Identity, objParams, FCollisionShape::MakeSphere(15.f), queryParams))
			{
				grabObject = hitInfo;
			}
			else
			{
				grabObject = FHitResult();
			}
			
			DrawDebugSphere(GetWorld(), startPos, 15.f, 30, FColor::Green, false, -1, 0, 1);
		}
	}
}


void UGrabActorComponent::GrabAction()
{
	AActor* grabActor = grabObject.GetActor();

	if (bIsShowing == false || grabActor == nullptr)
	{
		return;
	}

	if (pickObject == nullptr)
	{
		pickObject = Cast<APickUpActor>(grabActor);

		if (pickObject)
		{
			//FAttachmentTransformRules attachRules = FAttachmentTransformRules::KeepWorldTransform;
			FAttachmentTransformRules attachRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

			// 손에 붙이기
			pickObject->boxComp->SetSimulatePhysics(false);
			pickObject->AttachToComponent(player->rightHand, attachRules, TEXT("GrabPoint"));
			pickObject->boxComp->SetRelativeLocation(pickObject->grabOffset);
			pickObject->boxComp->SetEnableGravity(false);

			// 손을 쥐는 애니메이션 하기
			player->handComp->targetGripValueRight = 1.0f;
		}
	}
}

void UGrabActorComponent::ReleaseAction()
{
	if (pickObject)
	{
		pickObject->boxComp->SetEnableGravity(true);
		pickObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		pickObject->boxComp->SetSimulatePhysics(true);

		player->handComp->targetGripValueRight = 0.0f;

		pickObject = nullptr;
	}
}