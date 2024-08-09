// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicPlane.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "EngineUtils.h"


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

	FTimerHandle WhenSpawn;
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

			UBoxComponent* TowerCollide = Target->FindComponentByClass<UBoxComponent>();

			FVector FBOX = TowerCollide->GetScaledBoxExtent();

			float height = FBOX.Z * HeightPercent;
			CenterPnt = FVector(Target->GetActorLocation().X, Target->GetActorLocation().Y, height);
		}

		
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

		MovePlane(DeltaTime);
	}



}

void ABasicPlane::MovePlane(float Delta) {

	if (GEngine){
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("Moving")));

	}

	UBoxComponent* TowerCollide = Target->FindComponentByClass<UBoxComponent>();

	FVector FBOX = TowerCollide->GetScaledBoxExtent();

	float height = FBOX.Z * HeightPercent;

	
	FRotator Rot = GetActorRotation();
	FVector Location = GetActorLocation();

	//FRotator NewRot = FRotator(Rot.Yaw, Rot.Pitch, Rot.Roll + Delta * 0.1);
	
	
	

	
	
	

	//FVector EEE = NewRot.RotateVector(TempLoco);

	//EEE.X

	

	CurrentAngle += Speed * Delta;

	// Keep the angle within 0-360 degrees
	if (CurrentAngle >= 360.0f)
	{
		CurrentAngle -= 360.0f;
	}

	// Calculate the new position of the actor
	float Radians = FMath::DegreesToRadians(CurrentAngle);
	FVector NewLocation = CenterPnt + FVector(Radius * FMath::Cos(Radians), Radius * FMath::Sin(Radians), 0.0f);

	// Set the new location of the actor
	SetActorLocation(NewLocation);

	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Vector: %s"), *NewLocation.ToString()));

	}
	


	//Location = Location + GetActorLocation() * Speed * Delta;

	//SetActorLocation(Location);

	//float sin = FMath::Sin();
}

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

