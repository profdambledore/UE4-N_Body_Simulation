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

