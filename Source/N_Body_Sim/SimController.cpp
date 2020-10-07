// Fill out your copyright notice in the Description page of Project Settings.


#include "SimController.h"

// Sets default values
ASimController::ASimController()
{
	// Setup the simulations viewport
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-90.0f, 0.0f, 0.0f));
	CameraArm->TargetArmLength = 2000.0f;
	CameraArm->bDoCollisionTest = false;

	CameraViewport = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraViewport"));
	CameraViewport->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASimController::BeginPlay()
{
	Super::BeginPlay();

	// Show mouse curson
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	Controller->bShowMouseCursor = true;

	// Spawn the starting bodies
	StartingBodies(N);
}

// Camera Control Functions
// Change the zoom level of the camera
void ASimController::CameraZoom(float AxisValue)
{
	float Inverse = (AxisValue* 10) * -1;
	CameraArm->TargetArmLength = (CameraArm->TargetArmLength + Inverse);
	if (CameraArm->TargetArmLength <= 1000)
	{
		CameraArm->TargetArmLength = 1000;
	}
	else if (CameraArm->TargetArmLength >= 3000)
	{
		CameraArm->TargetArmLength = 3000;
	}
}

// Rotate the whole actor on the X Axis
void ASimController::RotateCameraX(float AxisValue)
{
	AddActorLocalRotation(FRotator(AxisValue, 0.0f, 0.0f), false, 0, ETeleportType::None);
};

// Rotate the whole actor on the Y Axis
void ASimController::RotateCameraY(float AxisValue)
{
	AddActorLocalRotation(FRotator(0.0f, AxisValue, 0.0f), false, 0, ETeleportType::None);
}

// Simulation functions
// Called every time a new body is added after the beginning bodies
void ASimController::ModifyBodyAmn()
{
	if (BodiesArray.Num() > N) // There are more bodies in the simulation than needed
	{
		RemoveBody();
	}
	//if (BodiesArray.Num() < N) // There are not enough bodies in the simulation
	//{
		//AddBody(false);
	//}
}

// Spawn a new body to the world and add it to the BodiesArray
void ASimController::AddBody(bool IsStartingBody, FVector SpawnPos)
{
	BodyHold = GetWorld()->SpawnActor<ACelestialBody>(SpawnPos, FRotator(0.0f, 0.0f, 0.0f), FActorSpawnParameters());
	BodyHold->SetupBody(SphereObject, BodyMaterial);
	BodiesArray.Push(BodyHold);
	//if (IsStartingBody == false);
	//{

	//}
};

//Destroy the body in the newest array cell and remove it from said array.  If the array is empty, do nothing
void ASimController::RemoveBody() 
{
	if (BodiesArray.Num() - 1 != -1)
	{
		uint8 i = BodiesArray.Num() - 1;
		BodyHold = BodiesArray[i];
		BodiesArray.RemoveAt(i);
		BodyHold->Destroy();
		GetWorld()->ForceGarbageCollection(true);
	};
}

// Set the start positions of the starting bodies.  Does not set body positions for any bodies added after the startup
double ASimController::SetStartPosition(FVector BodyRandPos)
{
	double yes = 0;
	return yes;
}

void ASimController::StartingBodies(int NoOfBodies)
{
	for (int i = 0; i < NoOfBodies; i++)
	{
		double BodyX = FMath::RandRange(-1000.0f, 1000.0f);
		double BodyY = FMath::RandRange(-1000.0f, 1000.0f);
		double BodyZ = FMath::RandRange(-1000.0f, 1000.0f);
		FVector RandPos = FVector(BodyX, BodyY, BodyZ);
		AddBody(true, RandPos);
	}	
}

void ASimController::AddForcesToBodies(int NoOfBodies)
{

}

// Called every frame
void ASimController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASimController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

