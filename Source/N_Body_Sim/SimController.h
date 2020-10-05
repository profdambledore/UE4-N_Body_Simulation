// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		TArray<ACelestialBody*> BodiesArray;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
