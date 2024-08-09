// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedPlayerInput.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


#include "Engine/EngineTypes.h"


// Sets default values
ATower::ATower()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Zpos = 0;


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

	
	SpringArm->TargetArmLength = 600;
	




}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {

		PlayerController->SetShowMouseCursor(true);

		//Wack but needed
		//PlayerController->SetInputMode(FInputModeGameOnly());
		

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


			//Might be conflicting with the look
			FRotator NewRotation = FRotator(0, FloatValue * 1, 0);

			FQuat QuatRotation = FQuat(NewRotation);

			SpringArm->AddLocalRotation(QuatRotation, false, 0);
			//FRotator SpringRotation = SpringArm->GetRelativeRotation();
			//SpringArm->SetRelativeRotation(SpringRotation.Quaternion(), false, 0);
			

		}
		if (FloatValue < 0.f) {
			//if (GEngine)
			//{
			//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("Right")));

		//	}

			//Might be conflicting with the look
			FRotator NewRotation = FRotator(0, FloatValue * 1, 0);

			FQuat QuatRotation = FQuat(NewRotation);

			SpringArm->AddLocalRotation(QuatRotation, false, 0);
			//FRotator SpringRotation = SpringArm->GetRelativeRotation();
			//SpringArm->SetRelativeRotation(SpringRotation.Quaternion(), false, 0);

		}

	}
}

void ATower::Look(const FInputActionValue& Value)
{

	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (GetController()) {

		float mouseX;
		float mouseY;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(mouseX, mouseY);

		FVector2D ScreenSize = FVector2D(1, 1);
		if (GEngine)
		{
		GEngine->GameViewport->GetViewportSize(ScreenSize);

		}

		float XDelta = ((ScreenSize.X / 2) - mouseX)*-1;
		float YDelta = ((ScreenSize.Y / 2) - mouseY) * -1;


		FRotator NewRotation = FRotator(YDelta * 0.01, XDelta * 0.01, 0);

		NewRotation.Roll = 0;

		FQuat QuatRotation = FQuat(NewRotation);



		Cam->AddLocalRotation(NewRotation.Quaternion(), false, 0);

		FRotator CamRotation = Cam->GetRelativeRotation();

		CamRotation.Roll = 0;

		Cam->SetRelativeRotation(CamRotation.Quaternion(), false, 0);

		

		//Cam->SetWorldRotation()

		


		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(XDelta));

		}
		//AddControllerYawInput(LookAxisValue.X);
		//AddControllerYawInput(LookAxisValue.Y);

	}

}

void ATower::Zoom(const FInputActionValue& Value)
{
	const float FloatValue = Value.Get<float>();

	
	if (Controller) {


		ArmRadius = ArmRadius + FloatValue * 100;

		ArmRadius = FMath::Clamp(ArmRadius, 600.0f, 2000.0f);
		
		SpringArm->TargetArmLength = ArmRadius;


	}
}

void ATower::UpDown(const FInputActionValue& Value)
{
	const float FloatValue = Value.Get<float>();

	if (Controller) {

		//Zpos = FloatValue; Do not uncomment 

		SpringArm->AddLocalOffset(FVector(0.0f, 0.0f, FloatValue), false);

	}

}

void ATower::Fire(const FInputActionValue& Value)
{
	const bool shot = Value.Get<bool>();

	if (Controller) {

		//more later

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

		EnchancedInputComponent->BindAction(Zoomo, ETriggerEvent::Triggered, this, &ATower::Zoom);

		EnchancedInputComponent->BindAction(UpDowno, ETriggerEvent::Triggered, this, &ATower::UpDown);
	}

}

