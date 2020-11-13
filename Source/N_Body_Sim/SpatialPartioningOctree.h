// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GenericOctree.h"

#include "GameFramework/Actor.h"
#include "CelestialBody.h"
#include "SpatialPartioningOctree.generated.h"

USTRUCT()
struct FOctreeElement
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		ACelestialBody* OctreeBody;

	UPROPERTY(EditAnywhere)
		FBoxSphereBounds BoxSphereBounds;

	FOctreeElement()
	{
		OctreeBody = nullptr;
		BoxSphereBounds = FBoxSphereBounds(FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f), 1.0f);
	}
};

struct FOctreeSematics
{
	enum { MaxElementsPerLeaf = 1 };
	enum { InclusiveElementsPerNode = 8 };
	enum { MaxNodeDepth = 10 };

	typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator;

	FORCEINLINE static FBoxSphereBounds GetBoundingBox(const FOctreeElement& Element)
	{
		return Element.BoxSphereBounds;
	}

	FORCEINLINE static bool AreElementsEqual(const FOctreeElement& A, const FOctreeElement& B)
	{
		return A.OctreeBody == B.OctreeBody;
	}

	FORCEINLINE static void SetElementId(const FOctreeElement& Element, FOctreeElementId Id)
	{
	}

};

typedef TOctree<FOctreeElement, FOctreeSematics> FSimulationOctree;

UCLASS()
class N_BODY_SIM_API ASpatialPartioningOctree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpatialPartioningOctree(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = Octree)
		void Initialize(const FBox& inNewBounds, const bool& inDrawDebugInfo);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void AddOctreeElement(const FOctreeElement& inNewOctreeElement);

	UFUNCTION()
		TArray<FOctreeElement> GetElementsWithinBounds(const FBoxSphereBounds& inBoundingBoxQuery);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		bool bDrawDebugInfo = false;

private:
	void DrawOctreeBounds();

	FSimulationOctree* OctreeData;
	bool bInitialized;
};
