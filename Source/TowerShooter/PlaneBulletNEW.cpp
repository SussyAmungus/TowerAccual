// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaneBulletNEW.h"

// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "BasicPlane.h"




// Sets default values
APlaneBulletNEW::APlaneBulletNEW()
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



}

// Called when the game starts or when spawned
void APlaneBulletNEW::BeginPlay()
{
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &APlaneBulletNEW::OnOverlapBegin);
	//SphereComp->OnComponentEndOverlap.AddDynamic(this, &APlaneBulletNEW::OnOverlapEnd);
	Super::BeginPlay();
}
void APlaneBulletNEW::BulletHit()
{
}
void APlaneBulletNEW::SetterVelocityo(FVector FVect) {

	if (ProjMove) {

		ProjMove->Velocity = FVect;
	}
}

void APlaneBulletNEW::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//class ABasicPlane;

	ABasicPlane* Planer = Cast<ABasicPlane>(OtherActor);
	APlaneBulletNEW* Bulleter = Cast<APlaneBulletNEW>(OtherActor);

	
	if (OtherActor && (OtherActor != this) && OtherComp && Bulleter == nullptr && Planer == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));

		const FString otherName = OtherActor->GetName();
		if (GEngine) {
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, otherName);
		}

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactFX, GetActorLocation());
		BulletHit();
		this->Destroy();
	}
}

void APlaneBulletNEW::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	//ABasicPlane* Planer = Cast<ABasicPlane>(OtherActor);
	APlaneBulletNEW* Bulleter = Cast<APlaneBulletNEW>(OtherActor);
	//&& Planer == nullpt
	if (OtherActor && (OtherActor != this) && OtherComp  && Bulleter == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactFX, GetActorLocation());
		BulletHit();
		this->Destroy();
	}
}

// Called every frame
void APlaneBulletNEW::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

