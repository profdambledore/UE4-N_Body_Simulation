// Fill out your copyright notice in the Description page of Project Settings.


#include "SimController.h"

// Sets default values
ASimController::ASimController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimController::BeginPlay()
{
	Super::BeginPlay();

	StartingBodies(N);
	
}

void ASimController::ModifyBodyAmn()
{
	if (BodiesArray.Num() > N) // There are more bodies in the simulation than needed
	{
		RemoveBody();
	}
	if (BodiesArray.Num() < N) // There are not enough bodies in the simulation
	{
		AddBody(false);
	}
}

// Spawn a new body to the world and add it to the BodiesArray
void ASimController::AddBody(bool IsStartingBody)
{
	BodyHold = GetWorld()->SpawnActor<ACelestialBody>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), FActorSpawnParameters());
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
	double WorldX3 = BodyRandPos.X * BodyRandPos.X * BodyRandPos.X;
	double WorldY3 = BodyRandPos.Y * BodyRandPos.Y * BodyRandPos.Y;
	double WorldZ3 = BodyRandPos.Z * BodyRandPos.Z * BodyRandPos.Z;
	double R3 = FMath::Pow(WorldX3 + WorldY3 + WorldZ3, 1.0 / 3.0);
	double Numerator = GravitationalConstant * 1e6 * Solarmass;
	return FMath::Pow(Numerator, 1.0 / 3.0);
}

void ASimController::StartingBodies(int NoOfBodies)
{
	float radius = 1e18;
	for (int i = 0; i < NoOfBodies; i++)
	{
		double BodyX = 1e18 * exp(-1.8) * (0.5 - FMath::Rand());
		double BodyY = 1e18 * exp(-1.8) * (0.5 - FMath::Rand());
		double BodyZ = 1e18 * exp(-1.8) * (0.5 - FMath::Rand());
		FVector RandPos = FVector(BodyX, BodyY, BodyZ);
		AddBody(true);
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

