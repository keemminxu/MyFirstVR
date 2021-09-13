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
	// 충돌 효과는 오버랩으로 설정한다.
	barMesh->SetGenerateOverlapEvents(true);
	barMesh->SetNotifyRigidBodyCollision(false);
	barMesh->SetCollisionProfileName(TEXT("OverlapAll"));
}

void APianoKeyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 충돌 이벤트 함수 바인딩하기
	barMesh->OnComponentBeginOverlap.AddDynamic(this, &APianoKeyActor::HitAction);

	// 동적 머티리얼 생성하기
	keyMat = UMaterialInstanceDynamic::Create(barMesh->GetMaterial(0), this, TEXT("DynamicKeyMat"));
	barMesh->SetMaterial(0, keyMat);
}

void APianoKeyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APianoKeyActor::HitAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 소리를 실행한다.
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), keySound, GetActorLocation());

	// 충돌한 대상의 이름을 로그로 출력해본다.
	UE_LOG(LogTemp, Warning, TEXT("hit Actor: %s"), *OtherActor->GetName());

	// 키의 Emissive 색상을 밝게 한다.
	keyMat->SetScalarParameterValue("Glow", 10);

	// 0.5초 뒤에 키의 색상을 다시 원래대로 되돌리기 위한 예약을 한다.
	GetWorldTimerManager().ClearTimer(keyColorHandle);
	GetWorldTimerManager().SetTimer(keyColorHandle, this, &APianoKeyActor::ResetKeyColor, 0.5f);

	// 오른손 콘트롤러 쪽에 진동을 준다.
	GetWorld()->GetFirstPlayerController()->PlayHapticEffect(ffx, EControllerHand::Right, 0.5f, false);
}

void APianoKeyActor::ResetKeyColor()
{
	// 키의 Emissive 색상을 0으로 변경한다.
	keyMat->SetScalarParameterValue("Glow", 0);
}