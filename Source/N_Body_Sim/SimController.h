// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* SphereObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInstance* BodyMaterial;

	// - PROPERTIES -- 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		TArray<ACelestialBody*> BodiesArray;

	UPROPERTY(EditAnywhere)
		ACelestialBody* BodyHold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		uint8 N = 100;

	UPROPERTY()
		double Solarmass = 1.98892e30;

	UPROPERTY()
		double GravitationalConstant = 6.67e-11;

	// - FUNCTIONS
	UFUNCTION(BlueprintCallable, Category = "Control")
		void ModifyBodyAmn();

	UFUNCTION(BlueprintCallable, Category = "Control")
		void AddBody(bool IsStartingBody);

	UFUNCTION(BlueprintCallable, Category = "Control")
		void RemoveBody();

	UFUNCTION()
		double SetStartPosition(FVector BodyRandPos);

	UFUNCTION()
		void StartingBodies(int NoOfBodies);

	UFUNCTION()
		void AddForcesToBodies(int NoOfBodies);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
