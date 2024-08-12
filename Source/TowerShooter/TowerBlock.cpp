// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TowerBlock.h"

// Sets default values for this component's properties
UTowerBlock::UTowerBlock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxCollide = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));

//	this->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	//Mesh->SetupAttachment(this);
	BoxCollide->SetupAttachment(this);

	Mesh->SetRelativeScale3D(FVector(2, 2, 2));
	BoxCollide->SetBoxExtent(FVector(100, 100, 100));

	BoxCollide->SetGenerateOverlapEvents(true);
	

	UStaticMesh* MeshAsset;

	//Can be bad
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAssetFinder(TEXT("/Script/Engine.StaticMesh'/Game/Meshes/Tower3_Cube_003.Tower3_Cube_003'"));
	 if (MeshAssetFinder.Succeeded())
	 {
	     MeshAsset = MeshAssetFinder.Object;

		 if (MeshAsset)
		 {
			 // UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(this);
			 Mesh->SetStaticMesh(MeshAsset);
			 Mesh->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
			Mesh->RegisterComponent();
		 }
	 }
	 

	// ...
}

//Has to be inside after initalizing it
void UTowerBlock::SetLoco(FVector vect)
{
	if(Mesh && BoxCollide){
		Mesh->SetRelativeLocation(vect);
		BoxCollide->SetRelativeLocation(vect);
	}

}

// Called when the game starts
void UTowerBlock::BeginPlay()
{
	Super::BeginPlay();


	
	//FVector FBOX = BoxCollide->GetScaledBoxExtent();
	
	// ...
	
}


// Called every frame
void UTowerBlock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

