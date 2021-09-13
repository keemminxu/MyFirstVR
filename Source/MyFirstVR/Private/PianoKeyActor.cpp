// Fill out your copyright notice in the Description page of Project Settings.


#include "PianoKeyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstance.h"

APianoKeyActor::APianoKeyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	barMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bar Mesh"));
	SetRootComponent(barMesh);
	// �浹 ȿ���� ���������� �����Ѵ�.
	barMesh->SetGenerateOverlapEvents(true);
	barMesh->SetNotifyRigidBodyCollision(false);
	barMesh->SetCollisionProfileName(TEXT("OverlapAll"));
}

void APianoKeyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// �浹 �̺�Ʈ �Լ� ���ε��ϱ�
	barMesh->OnComponentBeginOverlap.AddDynamic(this, &APianoKeyActor::HitAction);

	// ���� ��Ƽ���� �����ϱ�
	keyMat = UMaterialInstanceDynamic::Create(barMesh->GetMaterial(0), this, TEXT("DynamicKeyMat"));
	barMesh->SetMaterial(0, keyMat);
}

void APianoKeyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APianoKeyActor::HitAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �Ҹ��� �����Ѵ�.
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), keySound, GetActorLocation());

	// �浹�� ����� �̸��� �α׷� ����غ���.
	UE_LOG(LogTemp, Warning, TEXT("hit Actor: %s"), *OtherActor->GetName());

	// Ű�� Emissive ������ ��� �Ѵ�.
	keyMat->SetScalarParameterValue("Glow", 10);

	// 0.5�� �ڿ� Ű�� ������ �ٽ� ������� �ǵ����� ���� ������ �Ѵ�.
	GetWorldTimerManager().ClearTimer(keyColorHandle);
	GetWorldTimerManager().SetTimer(keyColorHandle, this, &APianoKeyActor::ResetKeyColor, 0.5f);

	// ������ ��Ʈ�ѷ� �ʿ� ������ �ش�.
	GetWorld()->GetFirstPlayerController()->PlayHapticEffect(ffx, EControllerHand::Right, 0.5f, false);
}

void APianoKeyActor::ResetKeyColor()
{
	// Ű�� Emissive ������ 0���� �����Ѵ�.
	keyMat->SetScalarParameterValue("Glow", 0);
}