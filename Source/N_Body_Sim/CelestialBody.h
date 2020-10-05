// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Component Includes
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"

// Property Includes
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"

// Base
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CelestialBody.generated.h"

UCLASS()
class N_BODY_SIM_API ACelestialBody : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACelestialBody();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMesh* SphereObject;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UMaterialInstance* BodyMaterial;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Properties")
		FVector WorldPos = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Properties")
		FVector Velocity = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Properties")
		FVector Force = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Body Properties")
		uint8 Mass = 0;

	// Randomization Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomization Properties")
		FVector Colour = FVector(0.0f, 0.0f, 0.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
