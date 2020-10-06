// Fill out your copyright notice in the Description page of Project Settings.


#include "CelestialBody.h"

// Sets default values
ACelestialBody::ACelestialBody()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add Static Mesh
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Celestial Body Mesh"));

}

// Called when the game starts or when spawned
void ACelestialBody::BeginPlay()
{
	Super::BeginPlay();
}

void ACelestialBody::SetupBody(UStaticMesh* SphereObject, UMaterialInstance* BodyMaterial)
{
	// Setup Static Mesh
	BodyMesh->SetStaticMesh(SphereObject);

	// Set Random Colour
	Colour = FVector(FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f));
	UMaterialInstanceDynamic* BodyDynMaterial = UMaterialInstanceDynamic::Create(BodyMaterial, this);
	BodyDynMaterial->SetVectorParameterValue("BodyColour", Colour);
	BodyMesh->SetMaterial(0, BodyDynMaterial);
}

void ACelestialBody::ResetForce() // Resets force on this body
{
	Force = FVector(0.0f, 0.0f, 0.0f);
}

float ACelestialBody::DistanceBetweenBody(ACelestialBody* B)
{
	float dist = FVector::Dist(GetActorLocation(), B->GetActorLocation());
	return dist;
}

void ACelestialBody::AddForceToBodies(ACelestialBody* B)
{
	FVector BodyWorldPos = FVector(GetActorLocation());
	float dist = DistanceBetweenBody(B);
	float InfinityParameter = 3E4;
	float CalculatedForce = (GravitationalConstant * Mass * B->Mass) / (dist * dist + InfinityParameter * InfinityParameter);
	Force += FVector(Force.X * BodyWorldPos.X / dist, Force.Y * BodyWorldPos.Y / dist, Force.Z * BodyWorldPos.Z / dist);
}



// Called every frame
void ACelestialBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACelestialBody::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

