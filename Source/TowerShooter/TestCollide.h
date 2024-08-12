// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestCollide.generated.h"

UCLASS()
class TOWERSHOOTER_API ATestCollide : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestCollide();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	//UPROPERTY(EditAnywhere)
	//class UBoxComponent* BoxCollide;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Sphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	void BulletHit();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
