// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PlayerBullet.generated.h"

class UPrimitiveComponent;

UCLASS()
class TOWERSHOOTER_API APlayerBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerBullet();

	void SetterVelocity(FVector FVect);

	//UPROPERTY()
	//USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	//UPROPERTY(EditAnywhere)
	//class UBoxComponent* BoxCollide;



	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjMove;


	UPROPERTY(EditAnywhere)
	float speed;

	UFUNCTION()
	void BeginComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	

	virtual void BulletHit();

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* ImpactFX;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
