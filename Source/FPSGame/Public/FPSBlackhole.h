// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "FPSBlackhole.generated.h"

UCLASS()
class FPSGAME_API AFPSBlackhole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackhole();

	//UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	bool bBlackholeTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly, Category = "Materials")
	//UMaterialInterface* MyMaterial;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* InnerSphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* OuterSphereComp;

	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetTrigger(bool value);
};
