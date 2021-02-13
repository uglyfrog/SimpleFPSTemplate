// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackhole.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AFPSBlackhole::AFPSBlackhole()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	RootComponent = MeshComp;


	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComp->SetSphereRadius(100);
	InnerSphereComp->SetupAttachment(MeshComp);
	InnerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackhole::OverlapInnerSphere);
	//InnerSphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//InnerSphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);


	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComp->SetSphereRadius(3000);
	OuterSphereComp->SetupAttachment(MeshComp);

	SetReplicates(true);
	SetReplicateMovement(true);
}

	// Called when the game starts or when spawned
void AFPSBlackhole::BeginPlay()
{
	Super::BeginPlay();
}


void AFPSBlackhole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		if (OtherActor)
		{
			OtherActor->Destroy();
		}

	}

}

void AFPSBlackhole::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSBlackhole, bBlackholeTrigger);
}

// Called every frame
void AFPSBlackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetLocalRole() == ROLE_Authority)
	{
		if (bBlackholeTrigger)
		{
			TArray<UPrimitiveComponent*> OverlappingComps;

			OuterSphereComp->GetOverlappingComponents(OverlappingComps);

			for (int32 i = 0; i < OverlappingComps.Num(); i++)
			{
				UPrimitiveComponent* PrimComp = OverlappingComps[i];
				if (PrimComp && PrimComp->IsSimulatingPhysics())
				{
					const float SphereRadius = OuterSphereComp->GetScaledSphereRadius();
					const float ForceStrength = -2000;

					PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);

				}

			}
		}

	}


}

void AFPSBlackhole::SetTrigger(bool value)
{
	{
		bBlackholeTrigger = value;
	}
}
