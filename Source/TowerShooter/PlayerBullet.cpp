// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"


//For player BP use playerbulletBp   



// Sets default values
APlayerBullet::APlayerBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetSphereRadius(100.0f);
	RootComponent = SphereComp;

	// Set up collision for Sphere Component
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	// Create and initialize the Static Mesh Component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	ProjMove = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMove"));
	ProjMove->ProjectileGravityScale = 0.1;
	
	
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::BeginComponentOverlap);
}



void APlayerBullet::SetterVelocity(FVector FVect) {

	if (ProjMove) {

		ProjMove->Velocity = FVect;
	}
}


// Called when the game starts or when spawned
void APlayerBullet::BeginPlay()
{

	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::BeginComponentOverlap);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::OnOverlapBegin);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &APlayerBullet::OnOverlapEnd);

	Super::BeginPlay();
	
	
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("Spawned")));

	}
	
}

void APlayerBullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APlayerBullet* Bulleter = Cast<APlayerBullet>(OtherActor);

	if (OtherActor && (OtherActor != this) && OtherComp && Bulleter == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactFX, GetActorLocation());
		BulletHit();
		Destroy();
	}
}

void APlayerBullet::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	APlayerBullet* Bulleter = Cast<APlayerBullet>(OtherActor);
	if (OtherActor && (OtherActor != this) && OtherComp && Bulleter == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactFX, GetActorLocation());
		BulletHit();
		Destroy();
	}
}

//void APlayerBullet::BeginComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//
//	const FString otherName = OtherActor->GetName();
//	if (GEngine) {
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, otherName);
//
//	}
//
//	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactFX, GetActorLocation());
//	BulletHit();
//	Destroy();
//
//}

void APlayerBullet::BulletHit()
{

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("Moving")));

	}

}

// Called every frame
void APlayerBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

