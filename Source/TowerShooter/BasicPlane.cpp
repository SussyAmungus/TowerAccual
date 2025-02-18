// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlane.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "TowerBlock.h"
#include "PlaneBulletNEW.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "EngineUtils.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ABasicPlane::ABasicPlane()
{


	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollide = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = Root;


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	BoxCollide->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	
}  




// Called when the game starts or when spawned
void ABasicPlane::BeginPlay()
{
	Super::BeginPlay();

	

	//Radius = 500;

	//FTimerHandle WhenSpawn;
	//GetWorld()->GetTimerManager().SetTimer(WhenSpawn, this, &ABasicPlane::InitTarget, 3.0f);
	//InitTarget();SetTimer(WhenSpaw, this, &ABasicPlane::InitTarget, 3.0f, false);


	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{

		// Get the player character
		APawn* PlayerPawn= PlayerController->GetPawn();

		ATower* tt = CastChecked<ATower>(PlayerPawn);

		if (tt) {

			Target = tt;
		}
		
	}

	//then the lerp from rotation to the place it will go to then spin around

	


}
//used to shoot
void ABasicPlane::planeFire() {
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.OverrideLevel = GetWorld()->GetCurrentLevel();
	//Cam->GetComponentRotation()Cam->GetComponentLocation()
	FTimerHandle FireTimer;

	//FVector Forward = GetActorLocation() - Target->GetActorLocation();
	FVector Forward = GetActorLocation() - Target->TowerStack[Block]->BoxCollide->GetComponentLocation();
	FVector WorldUp = FVector::UpVector;

	FRotator Rota = UKismetMathLibrary::MakeRotFromXZ(Forward, WorldUp);

	AActor* Bullo = GetWorld()->SpawnActor<APlaneBulletNEW>(Bulletito, GetActorLocation(), Rota, SpawnParams);

	if (Cast<APlaneBulletNEW>(Bullo)) {
		Cast<APlaneBulletNEW>(Bullo)->SetterVelocityo(Rota.Vector() * -500);
	}

	

}

// Called every frame
void ABasicPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	//JHohnscon
	
	//Target = GameMode->GetPlayer

	// = GameMode->Get





	if (Target) {

		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Vector: %s"), (TEXT("HAMMUD"))));

		}

		if (Target->CheckBlockExistance()) {

			MovePlane(DeltaTime);
			if (canFire) {

				if (GEngine) {
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("Spawned")));

				}

				planeFire();
				canFire = false;
				
				FTimerHandle FireTimer;
				GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ABasicPlane::ResetFire, 1);
			}
			
		}

		
	}



}

void ABasicPlane::ResetFire() {

	canFire = true;
}

void ABasicPlane::MovePlane(float Delta) {

	if (GEngine) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("Moving")));

	}

	//UBoxComponent* TowerCollide = Target->FindComponentByClass<UBoxComponent>();

	//FVector FBOX = TowerCollide->GetScaledBoxExtent();

	//float height = FBOX.Z * HeightPercent;


	//FRotator Rot = GetActorRotation();
	//FVector Location = GetActorLocation();

	//FRotator NewRot = FRotator(Rot.Yaw, Rot.Pitch, Rot.Roll + Delta * 0.1);

	/*
	if (CurRadius / DesRadius <= 1.0001 || CurRadius / DesRadius >= 9.9999) {
		
		if (CurRadius > DesRadius) {

			CurRadius = CurRadius - Delta * 50;
		}
		if (CurRadius < DesRadius) {

			CurRadius = CurRadius + Delta * 50;
		}

		


	}

	*/


	//Lowkey quadratic but can change to linear if you really want!
	CurRadius = FMath::Lerp(CurRadius, DesRadius, Delta);


	//if (GEngine) {
		//GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Purple, FString::FromInt(CurRadius));
	//}


		//PROB PUT ALL IN A FUCNTION THAT RUNS ONCE but as it looks not it will ot be bad
		FRotator off;
		if (isCounter) {
			off = FRotator(90, 0, 0);
		}
		else {
			off = FRotator(-90, 0, 0);
		}



	
	//FVector EEE = NewRot.RotateVector(TempLoco);

	//EEE.X


	//UBoxComponent* TowerCollide = Target->FindComponentByClass<UBoxComponent>();

	//FVector FBOX = TowerCollide->GetScaledBoxExtent();

	if (Target->TowerStack[Block]) {

		//UBoxComponent* TowerCollide = Target->TowerStack[Block]->FindComponentByClass<UBoxComponent>();
		UTowerBlock* BlockTarget = Target->TowerStack[Block];
		UBoxComponent* TowerCollide = BlockTarget->BoxCollide;

		FVector FBOX = TowerCollide->GetScaledBoxExtent();

		float height = (Block * 400) + FBOX.Z * HeightPercent;
		CenterPnt = FVector(Target->GetActorLocation().X, Target->GetActorLocation().Y, height);


		CurrentAngle += Speed * Delta;

		// Keep the angle within 0-360 degrees
		if (CurrentAngle >= 360.0f)
		{
			CurrentAngle -= 360.0f;
		}

		// Calculate the new position of the actor
		float Radians = FMath::DegreesToRadians(CurrentAngle);

		//right to left
		if (isCounter) {

			FVector NewLocation = CenterPnt + FVector(CurRadius * FMath::Cos(Radians), CurRadius * FMath::Sin(Radians), 0.0f);

			FRotator NewRot = FRotator(150, -CurrentAngle, 180);

			// Set the new location of the actor
			SetActorLocation(NewLocation);
			SetActorRotation(NewRot);

		}
		else {

			FVector NewLocation = CenterPnt + FVector(-CurRadius * FMath::Cos(Radians), -CurRadius * FMath::Sin(Radians), 0.0f);

			FRotator NewRot = FRotator(150, CurrentAngle, 180);

			// Set the new location of the actor
			SetActorLocation(NewLocation);
			SetActorRotation(NewRot);
		}




}
	//if (GEngine)
	//{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Vector: %s"), *NewLocation.ToString()));

	//}
	


	//Location = Location + GetActorLocation() * Speed * Delta;

	//SetActorLocation(Location);

	//float sin = FMath::Sin();
}
//prob not use atall
void ABasicPlane::InitTarget()
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("INIT")));

	}

	//CASUSES ALLOT OF ISSUES LIKE ALLOT IF YOU CANT GET INTO WORLD THEN YOU MUST DISABLE ALLOT, FIX LATER
	UWorld* World = GEditor->GetEditorWorldContext().World();

	//UWorld* World = GetWorld();

	if (World != nullptr) {
		TArray<AActor*> Towers = TArray<AActor*>();
		UGameplayStatics::GetAllActorsOfClass(World, ATower::StaticClass(), Towers);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Myint = %d"), Towers.Num()));

		}

		if (Towers.Num() > 0) {

			

			Target = (ATower*)Towers[0];
		}

	}
}



// Called to bind functionality to input
void ABasicPlane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

