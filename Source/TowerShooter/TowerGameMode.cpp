// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerGameMode.h"
#include "TimerManager.h"
#include "BasicPlane.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Tower.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TowerBlock.h"

ATowerGameMode::ATowerGameMode()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitLevels();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString(TEXT("GAMMEE")));

	}

}

void ATowerGameMode::Tick(float DeltaTime)
{
	//FTimerHandle FireTimer;
	
	Super::Tick(DeltaTime);
	 
}


void ATowerGameMode::NextSecond()
{
	if (roundTimer <= 0) {
		//when changes round
		
		currentRound++;
		ReadSpawn(currentRound);

		//if no more waves it does not call this if else yes, i think?
		
	}else {

		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::FromInt(roundTimer) + FString(TEXT("+ Current Round")));

		}

		roundTimer--;
	}

	//Updates every second
	totalTimer++;

	/*if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::FromInt(roundTimer));

	}*/
}

void ATowerGameMode::BeginPlay()
{

	Super::BeginPlay();

	//GetWorld()->GetTimerManager().ClearTimer(EverySecondTimer);

	GetWorld()->GetTimerManager().SetTimer(PollTimer, this, &ATowerGameMode::StartGame, 2.0f, false);
	
}

void ATowerGameMode::StartGame()
{
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController)
	{



		// Get the player character
		APawn* PlayerPawn = PlayerController->GetPawn();

		ATower* tt = CastChecked<ATower>(PlayerPawn);
		
		if (tt) {

			Towerr = tt;

			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString(TEXT("Has player")));

			}

			//Here starts the first round time starts

			roundTimer = Levels[0].time;
			//Spawn the first wave of johns
			ReadSpawn(0);
		}
	}


	
	
	//Does NOT call readspawn for first wave instead just ticks
	GetWorld()->GetTimerManager().SetTimer(EverySecondTimer, this, &ATowerGameMode::NextSecond, 1.0f, true, 0.5f);
		
	

}

void ATowerGameMode::EndLoop()
{
}



//for all plane spawns sets parameters
void ATowerGameMode::ReadSpawn(int32 Level)
{
	if (Level < Levels.Num()) {

		bool IsRandom = false;
		if (Levels[Level].SpawnTargetInt[0] == -1) {
			IsRandom = true;

		}

		for (int i = 0; i < Levels[Level].SpawnList.Num(); i++) {

			
			

			if (Levels[Level].SpawnList[i].Equals("BASICPLANE")) {
				

				if (IsRandom) {

					SpawnPlane(Levels[Level].SpawnList[i]);
				}
				else if (IsRandom != true) {

					SpawnPlane(Levels[Level].SpawnList[i],Levels[Level].SpawnTargetInt[i], Levels[Level].SpawnTargetCounter[i]);
				}

			}

		}

	}


	

}


//this is just for the random one
void ATowerGameMode::SpawnPlane(FString key)
{

	//Values to set the randmoness in the plane
	//wich block
	int randomNumber = FMath::RandRange(0, Towerr->TowerStack.Num() -1);
	//if it will come from right or left
	bool randomCounter = FMath::RandBool();

	float randomHeight = FMath::FRandRange(0.0f, 1.0f);




	if (key.Equals("BASICPLANE")) {

		
		//ABasicPlane* Plane = GetWorld()->SpawnActor<ABasicPlane>(Plane0, Cam->GetComponentLocation(), Cam->GetRelativeRotation(), SpawnParams);


		//like 100 units and then det on the counter or not wich way will it come 
		//yes it goes right then offset right

		FVector offset;
		if (randomCounter) {
			offset = FVector(0, 300, 0);

		}
		else {
			offset = FVector(0, -300, 0);

		}
		
		FVector BehindCamLoco = Towerr->Cam->GetComponentLocation() +
			
		(-Towerr->Cam->GetForwardVector() * 500) + offset + FVector(0,0,(randomNumber +1)* 400);

		/*
		//FVector Forward = BehindCamLoco - (Towerr->TowerStack[randomNumber]->BoxCollide->GetComponentLocation());
		FVector Forward = BehindCamLoco - (Towerr->TowerStack[randomNumber]->BoxCollide->GetComponentLocation());
		FVector WorldUp = FVector::UpVector;

		FRotator Rota = UKismetMathLibrary::MakeRotFromXZ(Forward, WorldUp);
		*/
		FTransform MyTransform;
		MyTransform.SetLocation(BehindCamLoco);

		//MyTransform.SetLocation(FVector(200,200,200));
		MyTransform.SetScale3D(FVector(1, 1, 1));
		//MyTransform.SetRotation(Rota.Quaternion());

		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Purple, Towerr->Cam->GetComponentLocation().ToString() + TEXT("Camloco"));
			GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Purple, BehindCamLoco.ToString() + TEXT("Begind cam loco"));
			
			GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Purple, MyTransform.ToHumanReadableString());
			//GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Purple, FVector(0, 0, Towerr->TowerStack[randomNumber]->GetComponentLocation().Z).ToString());
		}


		//if sizing issues than this is it.
		//SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* Plane = GetWorld()->SpawnActorDeferred< ABasicPlane>(Plane0, MyTransform, nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		/*FActorSpawnParameters SpawnParams;
		
		SpawnParams.OverrideLevel = GetWorld()->GetCurrentLevel();
		FTimerHandle FireTimer;

		
		AActor* Plane = GetWorld()->SpawnActor<ABasicPlane>(Plane0, FVector(200,200,200), MyTransform.GetRotation().Rotator(), SpawnParams);
		if (Plane) {
			Cast<ABasicPlane>(Plane)->Block = randomNumber;
			Cast<ABasicPlane>(Plane)->HeightPercent = randomHeight;
			Planes.Add(Cast<ABasicPlane>(Plane));
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, Plane->GetActorLocation().ToString());

			}
		}
		*/




		if (Plane) {

			float radingus = FMath::Sqrt((Cast<ABasicPlane>(Plane)->GetActorLocation().X * Cast<ABasicPlane>(Plane)->GetActorLocation().X)
				+ (Cast<ABasicPlane>(Plane)->GetActorLocation().Y * Cast<ABasicPlane>(Plane)->GetActorLocation().Y));


			Cast<ABasicPlane>(Plane)->Block = randomNumber;
			Cast<ABasicPlane>(Plane)->HeightPercent = randomHeight;
			Cast<ABasicPlane>(Plane)->CurRadius = radingus;
				

		//UGameplayStatics::FinishSpawningActor(Plane, MyTransform);

			

			Planes.Add(Cast<ABasicPlane>(Plane));
			Plane->FinishSpawning(Plane->GetActorTransform());
		}



	}

}

void ATowerGameMode::SpawnPlane(FString key,int32 num, bool Iscounter)
{
	//finsih later

}

void ATowerGameMode::InitLevels()
{

	TArray<FString> r0 = { TEXT("BASICPLANE") };
	FROUND Level1(0, 5, r0);
	Levels.Add(Level1);


	TArray<FString> r1 = { TEXT("BASICPLANE") };
	FROUND Level2(1, 10, r0);
	Levels.Add(Level2);

	

}



