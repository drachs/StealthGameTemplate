// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackHole();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp_Blackhole;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp_TouchEvent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp_GravityWell;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Check out in order to fix gun https://www.unrealengine.com/en-US/blog/collision-filtering
	UFUNCTION()
	void OverlapBlackHole(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
