// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedPlayerInput.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


#include "Engine/EngineTypes.h"


// Sets default values
ATower::ATower()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollide = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Cam = CreateDefaultSubobject<UCameraComponent>("Camera");
	Cam->SetupAttachment(SpringArm);

	Mesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	BoxCollide->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);

	

	



}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {

			Subsystem->AddMappingContext(PlayerMapCont,0);
		}
	}

}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATower::Rotater(const FInputActionValue& Value) {

	const float FloatValue = Value.Get<float>();
	

	if (Controller) {


		

		if (FloatValue > 0.f) {
			

		}
		if (FloatValue < 0.f) {
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("Right")));

			}

		}

	}
}

void ATower::Look(const FInputActionValue& Value)
{

	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (GetController()) {

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(LookAxisValue.X));

		}
		AddControllerYawInput(LookAxisValue.X);
		AddControllerYawInput(LookAxisValue.Y);

	}

}






// Called to bind functionality to input
void ATower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnchancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is a screen debug message!"));
		}


		EnchancedInputComponent->BindAction(Rotatato, ETriggerEvent::Triggered, this, &ATower::Rotater);

		EnchancedInputComponent->BindAction(Looko, ETriggerEvent::Triggered, this, &ATower::Look);
	}

}

