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
	
}

void ASimController::ModifyBodyAmn()
{
	if (BodiesArray.Num() > TotalBodies) // There are more bodies in the simulation than needed
	{
		RemoveBody();
	}
	if (BodiesArray.Num() < TotalBodies) // There are not enough bodies in the simulation
	{
		AddBody();
	}
}

// Spawn a new body to the world and add it to the BodiesArray
void ASimController::AddBody() 
{
	BodyHold = GetWorld()->SpawnActor<ACelestialBody>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), FActorSpawnParameters());
	BodiesArray.Push(BodyHold);
}

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
};

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

