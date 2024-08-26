// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Tower.generated.h"

class UInputMappingContext;
class UInputAction;
class UCurveVector;
class UTowerBlock;
class APlayerBullet;

UCLASS()
class TOWERSHOOTER_API ATower : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* PlayerMapCont;

	UPROPERTY(EditAnywhere)
	UInputAction* Rotatato;


	UPROPERTY(EditAnywhere)
	UInputAction* Looko;

	UPROPERTY(EditAnywhere)
	UInputAction* Zoomo;

	UPROPERTY(EditAnywhere)
	UInputAction* UpDowno;

	UPROPERTY(EditAnywhere)
	UInputAction* Shooto;


//	UPROPERTY(EditAnywhere)
//	UCurveVector* Curve;

	void Rotater(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);  

	void Zoom(const FInputActionValue& Value);

	void UpDown(const FInputActionValue& Value);

	void Fire(const FInputActionValue& Value);

	void ResetFire();

	



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class TSubclassOf <APlayerBullet> Bulletitor;

	UPROPERTY(EditAnywhere)
	float fireDelay;

	bool canFire = true;

	

	UPROPERTY()
	USceneComponent* Root;

	//UPROPERTY(EditAnywhere)
	//UStaticMeshComponent* BasicMesh;

//	UPROPERTY(EditAnywhere)
//	class UBoxComponent* BoxCollide;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	//UPROPERTY(EditAnywhere)
	//class UTowerBlock* TemplateBlock;

	TArray<UTowerBlock*> TowerStack;

	double runningSum = 150;

	void TEMPAddBasicTower();

	void AddBasicTowerConst(FString text);

	void AddBasicTower();
	bool CheckBlockExistance();

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Cam;


	float ArmRadius;

	//int Zpos; Reduntent


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
