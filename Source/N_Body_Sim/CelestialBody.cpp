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
	BodyMesh->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));

	// Set Random Mass
	Mass = FMath::RandRange(6.0f, 9.0f);

	// Set Random Colour
	Colour = FVector(FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f));
	UMaterialInstanceDynamic* BodyDynMaterial = UMaterialInstanceDynamic::Create(BodyMaterial, this);
	BodyDynMaterial->SetVectorParameterValue("BodyColour", Colour);
	BodyMesh->SetMaterial(0, BodyDynMaterial);
}

void ACelestialBody::AddForceToBodies(ACelestialBody* B)
{
	// Calculate forces applying to body
	ACelestialBody* A = this;
	FVector APos = GetActorLocation();
	FVector BPos = B->GetActorLocation();

	// Calculate forces for A
	FVector DistanceOnAxis = FVector(BPos.X - APos.X, BPos.Y - APos.Y, BPos.Z - APos.Z);
	float Distance = FVector::Dist(APos, BPos);
	double NewForces = (GravitationalConstant * A->Mass * B->Mass) / (Distance * Distance);
	Force.X += NewForces * DistanceOnAxis.X / Distance;
	Force.Y += NewForces * DistanceOnAxis.Y / Distance;
	Force.Z += NewForces * DistanceOnAxis.Z / Distance;

	// Calculate forces for B -- Inverse Calculations
	B->Force.X += NewForces * (DistanceOnAxis.X * -1) / Distance;
	B->Force.Y += NewForces * (DistanceOnAxis.Y * -1) / Distance;
	B->Force.Z += NewForces * (DistanceOnAxis.Z * -1) / Distance;
	
	// Update Velocity
	Velocity = FVector(Force.X * Mass, Force.Y * Mass, Force.Z * Mass);
	B->Velocity = FVector(B->Force.X * B->Mass, B->Force.Y * B->Mass, B->Force.Z * B->Mass);
	// Add repulsive potential?
}

// Called every frame
void ACelestialBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if paused
	if (bIsPaused == false)
	{
		// Move body
		AddActorWorldTransform(FTransform(FQuat(0, 0, 0, 0), Velocity, FVector(0.3, 0.3, 0.3)), false, 0, ETeleportType::None);
	};
}

// Called to bind functionality to input
void ACelestialBody::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
