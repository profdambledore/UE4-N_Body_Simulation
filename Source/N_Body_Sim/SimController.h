// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

#include "CelestialBody.h"

#include "SimController.generated.h"

UCLASS()
class N_BODY_SIM_API ASimController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASimController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// - COMPONENTS
	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere)
		UCameraComponent* CameraViewport;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* SphereObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInstance* BodyMaterial;

	// - PROPERTIES -- 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		TArray<ACelestialBody*> BodiesArray;

	UPROPERTY(EditAnywhere)
		ACelestialBody* BodyHold;

	UPROPERTY()
		uint16 N = 1000;

	UPROPERTY()
		double Solarmass = 1.98892e30;

	UPROPERTY()
		double GravitationalConstant = 6.67e-11;

	// - FUNCTIONS
	// Camera Control Functions
	UFUNCTION(BlueprintCallable, Category = "Camera")
		void CameraZoom(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera")
		void RotateCameraX(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera")
		void RotateCameraY(float AxisValue);

	// Simulation Functions
	UFUNCTION(BlueprintCallable, Category = "Control")
		void ModifyBodyAmn();

	UFUNCTION(BlueprintCallable, Category = "Control")
		void AddBody(bool IsStartingBody, FVector SpawnPos);

	UFUNCTION(BlueprintCallable, Category = "Control")
		void RemoveBody();

	UFUNCTION()
		void StartingBodies(int NoOfBodies);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
