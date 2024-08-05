// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tower.h"
#include "GameFramework/GameMode.h"
#include "TimerManager.h"
#include "BasicPlane.generated.h"

UCLASS()
class TOWERSHOOTER_API ABasicPlane : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MovePlane(float Delta);

	void InitTarget();

	
	
	 
	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxCollide;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float Radius;


	
	ATower* Target;

	UPROPERTY(EditAnywhere)
	AGameModeBase* GameMode;


	UPROPERTY(EditAnywhere)
	float HeightPercent;

	float CurrentAngle;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
