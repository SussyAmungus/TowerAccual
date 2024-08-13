// Fill out your copyright notice in the Description page of Project Settings.
#include "TestCollide.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ATestCollide::ATestCollide()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Sphere->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);

}

// Called when the game starts or when spawned
void ATestCollide::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ATestCollide::OnOverlapStart);
}

void ATestCollide::OnOverlapStart(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	const FString otherName = OtherActor->GetName();
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("AHH")));

	}

	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactFX, GetActorLocation());
	//BulletHit();
	//Destroy();

}

void ATestCollide::BulletHit()
{

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("Moving")));

	}

}

// Called every frame
void ATestCollide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

