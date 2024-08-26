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
#include "Kismet/KismetMathLibrary.h"
#include "Curves/CurveVector.h"
#include "PlayerBullet.h"
#include "TowerBlock.h"
#include "TimerManager.h"

#include "Engine/EngineTypes.h"

#include "Components/SphereComponent.h"

// Sets default values
ATower::ATower()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//runningSum = 0;
	//Zpos = 0;


	//BoxCollide = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = Root;

//	BasicMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);


	Cam = CreateDefaultSubobject<UCameraComponent>("Camera");
	Cam->SetupAttachment(SpringArm);
	
	
	

	//Mesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	//BoxCollide->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);

	/*
	SpringArm->TargetArmLength = 600;
	
	////////COPY
	UTowerBlock* TemplateBlock = CreateDefaultSubobject<UTowerBlock>(TEXT("One"));

	TemplateBlock->SetLoco(FVector(0, 0, 400));
	runningSum = runningSum + 400;

	TowerStack.Add(TemplateBlock);
	*/
	///////PASTE

	////////COPY ---> This one doesnt work for some reason ill prob fix this later it doesnt really matter for first round bc its prob short or some, other rounds will not face this issue
	/*UTowerBlock* TemplateBlock2 = CreateDefaultSubobject<UTowerBlock>(TEXT("TWO"));

	TemplateBlock2->SetLoco(FVector(0, 100, runningSum));
	runningSum = runningSum + 400;

	TowerStack.Add(TemplateBlock2);*/
	///////PASTE

	//could casue issues

	///WILL ONLY GIVE TWO FOR THE FIRST ROUND TYPE SHIT MUST ADD/DUPE CODE MANUALY FOR MORE STARTING THINGS, OR DELAY WHEN IT TRYS TO GET THE TOWER STACK DATA BC GAMEMODES CONST IS TOO EARLY (prob better solution
	//Prob needs to be fixed with the delay thing or a better way to create defult subobjects
	
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();


	//AddBasicTower();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController) {

		//PlayerController->SetShowMouseCursor(true);

		//Wack but needed, nvm
		//PlayerController->SetInputMode(FInputModeGameOnly());
		

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem) {

			Subsystem->AddMappingContext(PlayerMapCont,0);
		}
	}
	
	AddBasicTower();
	AddBasicTower();

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

		//float XDelta = ((ScreenSize.X / 2) - mouseX)*-1;
		//float YDelta = ((ScreenSize.Y / 2) - mouseY) * 1;


		FRotator NewRotation = FRotator(LookAxisValue.Y, LookAxisValue.X, 0);


		NewRotation.Roll = 0;

		FQuat QuatRotation = FQuat(NewRotation);



		//Cam->AddLocalRotation(NewRotation.Quaternion(), false, 0);

		FRotator CamRotation = Cam->GetRelativeRotation();

		CamRotation.Roll = 0;

		//FVector Desired = Cam->GetRelativeLocation();

		//FRotator Des = FMath::Inter(CamRotation, NewRotation, GetWorld()->GetDeltaSeconds(), 40);
		
		//Cam->SetRelativeRotation(FMath::Lerp(FQuat(Cam->GetRelativeRotation()), CamRotation.Quaternion(),0.01), false, 0);
		//Cam->SetRelativeRotation(FMath::Vinter)
		//Cam->SetRelativeRotation(Des.Quaternion());
		
		FRotator test = CamRotation + NewRotation;
		FRotator build = CamRotation;
		if (test.Yaw < 45 && test.Yaw > -45) {
			build.Yaw = test.Yaw;
			
		}

		if (test.Pitch < 45 && test.Pitch > -45) {

			build.Pitch = test.Pitch;
		}

		Cam->SetRelativeRotation(build.Quaternion(), false, 0);
		//Cam->SetWorldRotation()

		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Vector: %s"), *Des.ToString()));

		}


		if (GEngine)
		{ 
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Float Value: %f"), GetWorld()->GetDeltaSeconds()));


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

	if (Controller && canFire) {

		canFire = false;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		SpawnParams.OverrideLevel = GetWorld()->GetCurrentLevel();
		//Cam->GetComponentRotation()Cam->GetComponentLocation()
		FTimerHandle FireTimer;
		AActor* Bull = GetWorld()->SpawnActor<APlayerBullet>(Bulletitor, Cam->GetComponentLocation(), Cam->GetRelativeRotation(), SpawnParams);

		Cast<APlayerBullet>(Bull)->SetterVelocity(Cam->GetComponentRotation().Vector() * 500);

		
		
		GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ATower::ResetFire, fireDelay);
		//more later

		

		//Cast<APlayerBullet>(Bull)->SphereComp->OnComponentBeginOverlap.AddDynamic(Cast<APlayerBullet>(Bull), &APlayerBullet::BeginComponentOverlap);


		if (GEngine)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Vector: %s"), *Cam->GetRelativeRotation().ToString()));

		}

	}

}

void ATower::ResetFire() {

	canFire = true;
}

bool ATower::CheckBlockExistance()
{
	if (TowerStack.Num() > 0) {

		return true;
	}


	return false;
}


//dont use this ever
void ATower::TEMPAddBasicTower() {

	UTowerBlock* TemplateBlock = CreateDefaultSubobject<UTowerBlock>(TEXT("BLOCKBasic"));
	TemplateBlock->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

//only really used to create a tocker block during a constructor ALSO NOT POSSIBLE // USED TO DUPE TEXT
void ATower::AddBasicTowerConst(FString texta)
{

	UTowerBlock* TemplateBlock = CreateDefaultSubobject<UTowerBlock>(*texta);
	
	TemplateBlock->SetLoco(FVector(0, 0, runningSum));
	runningSum = runningSum + 400;

	TowerStack.Add(TemplateBlock);

}

void ATower::AddBasicTower()
{
	UTowerBlock* TemplateBlock = NewObject<UTowerBlock>(this);
		//CreateDefaultSubobject<UTowerBlock>(TEXT("BLOCKBasic"));	 

	//TemplateBlock->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//TemplateBlock->SetRelativeLocation(FVector(0, 0, runningSum));
	
	TemplateBlock->SetLoco(FVector(0, 0, runningSum));
	runningSum = runningSum + 400;

	TowerStack.Add(TemplateBlock);



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

		EnchancedInputComponent->BindAction(Shooto, ETriggerEvent::Triggered, this, &ATower::Fire);

	}

}

