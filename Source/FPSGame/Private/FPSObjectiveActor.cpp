// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectiveActor.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "FPSBlackhole.h"
#include "EngineUtils.h"


// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(MeshComp);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}
// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	PlayEffect();
	
}



void AFPSObjectiveActor::PlayEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

// Called every frame
//void AFPSObjectiveActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffect();

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);


	TActorIterator<AFPSBlackhole> ActorItr = TActorIterator<AFPSBlackhole>(GetWorld());


	if (MyCharacter)
	{
		if (ActorItr)
		{
			ActorItr->bBlackholeTrigger = true;
			//ActorItr->SetTrigger(true);
			CppPrint("Trigger is on!");
		}
		else
		{
			CppPrint("Black hole is not casted correctly!");
		}

		MyCharacter->bIsCarryingObjective = true;
		Destroy();
	}
}

void AFPSObjectiveActor::CppPrint(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, text);
}