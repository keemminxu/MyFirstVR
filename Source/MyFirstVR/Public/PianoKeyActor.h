// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PianoKeyActor.generated.h"

UCLASS()
class MYFIRSTVR_API APianoKeyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APianoKeyActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category=KeySettings)
	class UStaticMeshComponent* barMesh;

	UPROPERTY(EditAnywhere, Category = KeySettings)
	class USoundBase* keySound;

	UPROPERTY(EditAnywhere, Category = KeySettings)
	class UHapticFeedbackEffect_Base* ffx;

	
private:
	class UMaterialInstanceDynamic* keyMat;
	FTimerHandle keyColorHandle;

	UFUNCTION()
	void HitAction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ResetKeyColor();
};
