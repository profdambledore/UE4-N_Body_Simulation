// Fill out your copyright notice in the Description page of Project Settings.


#include "SimController.h"

// Sets default values
ASimController::ASimController()
{
	// Setup the simulations viewport
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-90.0f, 0.0f, 0.0f));
	CameraArm->TargetArmLength = 20000.0f;
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

	CreateNewOctree();

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
	float Inverse = (AxisValue* 100) * -1;
	CameraArm->TargetArmLength = (CameraArm->TargetArmLength + Inverse);
	if (CameraArm->TargetArmLength <= 1000)
	{
		CameraArm->TargetArmLength = 1000;
	}
	else if (CameraArm->TargetArmLength >= 300000)
	{
		CameraArm->TargetArmLength = 300000;
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
// Pause or Un-pause the Simulation
void ASimController::PauseSimulation()
{
	if (bIsPaused == true)
	{
		bIsPaused = false;
		for (int i = 0; i < BodiesArray.Num(); i++)
		{
			BodiesArray[i]->bIsPaused = false;
		}
	}
	else
	{
		bIsPaused = true;
		for (int i = 0; i < BodiesArray.Num(); i++)
		{
			BodiesArray[i]->bIsPaused = true;
		}
	}
}

// Spawn a new body to the world and add it to the BodiesArray
void ASimController::AddBody(bool IsStartingBody, FVector SpawnPos)
{
	BodyHold = GetWorld()->SpawnActor<ACelestialBody>(SpawnPos, FRotator(0.0f, 0.0f, 0.0f), FActorSpawnParameters());
	BodyHold->SetupBody(SphereObject, BodyMaterial);

	// Add Body to Octree - first calculate bounds in Blueprint
	CreateBodyBounds(BodyHold);

	BodiesArray.Push(BodyHold);
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

void ASimController::StartingBodies(int NoOfBodies)
{
	for (int i = 0; i < N; i++)
	{
		double BodyX = FMath::RandRange(-10000.0f, 10000.0f);
		double BodyY = FMath::RandRange(-10000.0f, 10000.0f); // Uniformed spherical distribution?
		double BodyZ = FMath::RandRange(-10000.0f, 10000.0f);
		FVector RandPos = FVector(BodyX, BodyY, BodyZ);
		AddBody(true, RandPos);
	}	
}

void ASimController::AddBodyToOctree(ACelestialBody* BodyToAdd, FBoxSphereBounds NewSphereBounds)
{
	FOctreeElement* OE = new FOctreeElement();
	OE->OctreeBody = BodyToAdd; OE->BoxSphereBounds = NewSphereBounds;
	SimulationOctree->AddOctreeElement(*OE);
}

// Called every frame
void ASimController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsPaused == false)
	{
		for (int i = 0; i < BodiesArray.Num(); i++)
		{
			for (int j = i; j < BodiesArray.Num(); j++)
			{
				if (BodiesArray[i] != BodiesArray[j])
				{
					BodiesArray[i]->AddForceToBodies(BodiesArray[j]);
				};
			};
		};
	};
}

// Called to bind functionality to input
void ASimController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

