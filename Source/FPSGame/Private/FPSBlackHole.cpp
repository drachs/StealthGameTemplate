// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp_Blackhole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackHole"));
	MeshComp_Blackhole->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp_Blackhole;

	SphereComp_TouchEvent = CreateDefaultSubobject<USphereComponent>(TEXT("TouchEvent"));
	SphereComp_TouchEvent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp_TouchEvent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	SphereComp_TouchEvent->SetupAttachment(MeshComp_Blackhole);
	
	SphereComp_TouchEvent->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OverlapBlackHole);

	SphereComp_GravityWell = CreateDefaultSubobject<USphereComponent>(TEXT("GravityField"));
	SphereComp_GravityWell->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp_GravityWell->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	SphereComp_GravityWell->SetupAttachment(MeshComp_Blackhole);
}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSBlackHole::OverlapBlackHole(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Touch"));
}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor *> Hits;

	SphereComp_GravityWell->GetOverlappingActors(Hits);

	for (auto& Hit : Hits) {
		UStaticMeshComponent *MeshComp = Cast<UStaticMeshComponent>(Hit->GetRootComponent());
		if (MeshComp && MeshComp->IsSimulatingPhysics()) {
			MeshComp->AddRadialForce(GetActorLocation(), SphereComp_GravityWell->GetScaledSphereRadius(), -2000.0f, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}

}

