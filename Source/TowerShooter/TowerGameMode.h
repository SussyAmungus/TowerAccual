// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerGameMode.generated.h"

/**
 * 
 */




//you can either set a lets enimes with all random, left and right, or have one that you can set what target and wich left and right they go ONLY those to options
USTRUCT()
struct FROUND{

	GENERATED_BODY()

public:
	//UPROPERTY()
	int32 round;
	
	int32 time;

	TArray<FString> SpawnList;
	//if -1 for [0] then random distribution
	TArray<int32> SpawnTargetInt;


	//if size 0 then random counter or nah (for if it rotates one way or the other
	TArray<bool> SpawnTargetCounter;

	// Default constructor
	FROUND()
		: round(0), time(0), SpawnTargetInt({ -1 })
	{
	}

	//level num samething as round
	FROUND(int32 levelnum, int32 timenum, TArray<FString> Stringa, TArray<int32> TargetNum, TArray<bool> Targetbool)
		:round(levelnum),time(timenum),SpawnList(Stringa), SpawnTargetInt(TargetNum), SpawnTargetCounter(Targetbool)
	{

	}

	//for randomnesss
	FROUND(int32 levelnum, int32 timenum, TArray<FString> Stringa)
		:round(levelnum), time(timenum), SpawnList(Stringa), SpawnTargetInt({-1})
	{
		
	}


};



//class FTimerHandle;
//class ABasicPlane;

class ATower;
class ABasicPlane;
UCLASS()
class TOWERSHOOTER_API ATowerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ATowerGameMode();

//	virtual ~ATowerGameMode() = default;

	virtual void Tick(float DeltaTime) override;

	int32 coins;

	int32 currentRound = 0;

	int32 totalTimer;

	//starts high goes low
	//starts at 0 wich automaticly makes it okay to start the first round
	int32 roundTimer = 0;

	void NextSecond();

	void StartGame();

	void EndLoop();

	void ReadSpawn(int32 num);
	//this one is for randomness
	void SpawnPlane(FString key);
	//this one is for to place each plane
	void SpawnPlane(FString key,int32 num,bool counter);

	void InitLevels();

	FTimerHandle EverySecondTimer;

	FTimerHandle PollTimer;




	TArray<ABasicPlane*> Planes;

	TArray<FROUND> Levels;


	UPROPERTY(EditAnywhere)
	class TSubclassOf <ABasicPlane>Plane0;
	
	
	//gets it auto at beginplay
	ATower* Towerr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
