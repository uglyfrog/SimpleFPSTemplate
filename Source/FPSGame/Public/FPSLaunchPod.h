// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPod.generated.h"

UCLASS()
class FPSGAME_API AFPSLaunchPod : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPod();

	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void CppPrint(FString text);

protected:
	// Called when the game starts or when spawned

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* OverlapPod;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* LaunchFX;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPod")
	float LaunchStrengh;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPod")
	float LaunchAngle;

	void PlayEffect();

	UFUNCTION()
	void PodOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
