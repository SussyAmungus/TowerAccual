// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Tower.generated.h"

class UInputMappingContext;
class UInputAction;


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

	void Rotater(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);  

	void Zoom(const FInputActionValue& Value);

	void UpDown(const FInputActionValue& Value);

	void Fire(const FInputActionValue& Value);

	 



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxCollide;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;


	UPROPERTY(EditAnywhere)
	class UCameraComponent* Cam;


	float ArmRadius;

	int Zpos;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
