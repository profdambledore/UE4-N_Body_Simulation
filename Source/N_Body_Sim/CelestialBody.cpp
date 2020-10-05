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
	// Setup Static Mesh
	BodyMesh->SetStaticMesh(SphereObject);

	// Set Random Colour
	Colour = FVector(FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f));
	UMaterialInstanceDynamic* BodyDynMaterial = UMaterialInstanceDynamic::Create(BodyMaterial, this);
	BodyDynMaterial->SetVectorParameterValue("BodyColour", Colour);
	BodyMesh->SetMaterial(0, BodyDynMaterial);

	Super::BeginPlay();
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

