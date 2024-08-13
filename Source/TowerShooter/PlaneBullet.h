// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaneBullet.generated.h"

class UPrimitiveComponent;

UCLASS()
class TOWERSHOOTER_API APlaneBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaneBullet();


	void SetterVelocityo(FVector FVect);

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;


	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjMove;


	UPROPERTY(EditAnywhere)
	float speed;

	//UFUNCTION()
	//void BeginComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	//	int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

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
