// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialPartioningOctree.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASpatialPartioningOctree::ASpatialPartioningOctree(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, OctreeData(NULL)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OctreeData = new FSimulationOctree(FVector(0.0f, 0.0f, 0.0f), 100.0f); // const FVector & InOrigin, float InExtent
}

// Called when the game starts or when spawned
void ASpatialPartioningOctree::BeginPlay()
{
	Super::BeginPlay();
}

void ASpatialPartioningOctree::Initialize(const FBox& inNewBounds, const bool& inDrawDebugInfo)
{
	bInitialized = true;
	bDrawDebugInfo = inDrawDebugInfo;
	OctreeData = new FSimulationOctree(inNewBounds.GetCenter(), inNewBounds.GetExtent().GetMax()); // const FVector & InOrigin, float InExtent
}

// Called every frame
void ASpatialPartioningOctree::Tick(float DeltaTime)
{
	if (bInitialized && bDrawDebugInfo)
	{
		int level = 0;
		float max;
		FVector maxExtent;
		FVector center;
		FVector tempForCoercion;
		FBoxCenterAndExtent OldBounds = FBoxCenterAndExtent();

		int nodeCount = 0;
		int elementCount = 0;

		// Go through the nodes of the octree
		for (FSimulationOctree::TConstIterator<> NodeIt(*OctreeData); NodeIt.HasPendingNodes(); NodeIt.Advance())
		{
			const FSimulationOctree::FNode& CurrentNode = NodeIt.GetCurrentNode();
			const FOctreeNodeContext& CurrentContext = NodeIt.GetCurrentContext();
			const FBoxCenterAndExtent& CurrentBounds = CurrentContext.Bounds;

			nodeCount++;

			FOREACH_OCTREE_CHILD_NODE(ChildRef)
			{
				if (CurrentNode.HasChild(ChildRef))
				{
					NodeIt.PushChild(ChildRef);
				}
			}

			// If the extents have changed then we have moved a level.
			if (!OldBounds.Extent.Equals(CurrentBounds.Extent))
			{
				level++;
			}
			OldBounds = CurrentBounds;

			UE_LOG(LogTemp, Log, TEXT("Level: %d"), level);

			// Draw Node Bounds
			tempForCoercion = CurrentBounds.Extent;
			max = tempForCoercion.GetMax();
			center = CurrentBounds.Center;

			maxExtent = FVector(max, max, max);

			FOREACH_OCTREE_CHILD_NODE(ChildRef)
			{
				if (bDrawDebugInfo == true) 
				{
					if (CurrentNode.IsLeaf())
					{
						DrawDebugBox(GetWorld(), center, maxExtent, FColor().Green, false, 0.0f);
					}
				}
			}
		}
	}
}

void ASpatialPartioningOctree::AddOctreeElement(const FOctreeElement& inNewOctreeElement)
{
	check(bInitialized);
	OctreeData->AddElement(inNewOctreeElement);
}

TArray<FOctreeElement> ASpatialPartioningOctree::GetElementsWithinBounds(const FBoxSphereBounds& inBoundingBoxQuery)
{
	return TArray<FOctreeElement>();
}

void ASpatialPartioningOctree::DrawOctreeBounds()
{
	FVector extent = this->OctreeData->GetRootBounds().Extent;

	float max = extent.GetMax();
	FVector maxExtent = FVector(max, max, max);
	FVector center = this->OctreeData->GetRootBounds().Center;

	DrawDebugBox(GetWorld(), center, maxExtent, FColor().Green, false, 0.0f);
	DrawDebugSphere(GetWorld(), center + maxExtent, 4.0f, 12, FColor().White, false, 0.0f);
	DrawDebugSphere(GetWorld(), center - maxExtent, 4.0f, 12, FColor().White, false, 0.0f);
}

