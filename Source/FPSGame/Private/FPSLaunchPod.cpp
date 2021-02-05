// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPod.h"
#include "Components/MeshComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPod::AFPSLaunchPod()
{
	OverlapPod = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OverlapPod"));
	OverlapPod->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapPod->SetCollisionResponseToAllChannels(ECR_Overlap);
	OverlapPod->SetHiddenInGame(false);
	OverlapPod->SetRelativeScale3D(FVector(2.0f, 2.0f, 0.1f));
	RootComponent = OverlapPod;

	OverlapPod->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPod::PodOverlap);

	LaunchStrengh = 1500.0f;
	LaunchAngle = 55.0f;

}

//void AFPSLaunchPod::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	Super::NotifyActorBeginOverlap(OtherActor);
//
//	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
//
//	if (MyPawn)
//	{
//		MyPawn->LaunchCharacter(FVector(10.0f*LaunchStrengh), true, true);
//		CppPrint("It is ok!!");
//	}
//	else
//	{
//		CppPrint("no response");
//	}
//}

void AFPSLaunchPod::CppPrint(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, text);
}

void AFPSLaunchPod::PlayEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchFX, GetActorLocation());
}

void AFPSLaunchPod::PodOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrengh;

	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);

	if (MyPawn)
	{
		MyPawn->LaunchCharacter(LaunchVelocity, true, true);
		CppPrint("Launch People!!!");
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
		CppPrint("Launch Box!!!");
	}
	PlayEffect();
}


