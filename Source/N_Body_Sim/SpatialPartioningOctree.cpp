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
		float offsetMax;
		float offset;
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

			UE_LOG(LogTemp, Log, TEXT("center before: %s"), *center.ToString());

			// To understand the math here check out the constructors in FOctreeNodeContext
			// Offset nodes that are not the root bounds
			if (!OctreeData->GetRootBounds().Extent.Equals(CurrentBounds.Extent))
			{
				for (int i = 1; i < level; i++)
				{
					// Calculate offset
					offsetMax = max / (1.0f + (1.0f / FOctreeNodeContext::LoosenessDenominator));
					offset = max - offsetMax;
					max = offsetMax;

					// Calculate Center Offset
					if (center.X > 0)
					{
						center.X = center.X + offset;
					}
					else
					{
						center.X = center.X - offset;
					}

					if (center.Y > 0)
					{
						center.Y = center.Y + offset;
					}
					else
					{
						center.Y = center.Y - offset;
					}

					if (center.Z > 0)
					{
						center.Z = center.Z + offset;
					}
					else
					{
						center.Z = center.Z - offset;
					}
				}
			}

			UE_LOG(LogTemp, Log, TEXT("max: %f"), max);
			// UE_LOG(LogTemp, Log, TEXT("center of nodes: %s"), *center.ToString());

			maxExtent = FVector(max, max, max);


			// UE_LOG(LogTemp, Log, TEXT("Extent of nodes: %s"), *tempForCoercion.ToString());

			DrawDebugBox(GetWorld(), center, maxExtent, FColor().Blue, false, 0.0f);
			DrawDebugSphere(GetWorld(), center + maxExtent, 4.0f, 12, FColor().Green, false, 0.0f);
			DrawDebugSphere(GetWorld(), center - maxExtent, 4.0f, 12, FColor().Red, false, 0.0f);

			for (FSimulationOctree::ElementConstIt ElementIt(CurrentNode.GetElementIt()); ElementIt; ++ElementIt)
			{
				const FOctreeElement& Sample = *ElementIt;

				// Draw debug boxes around elements
				max = Sample.BoxSphereBounds.BoxExtent.GetMax();
				maxExtent = FVector(max, max, max);
				center = Sample.OctreeBody->GetActorLocation();

				DrawDebugBox(GetWorld(), center, maxExtent, FColor().Green, false, 0.0f);
				DrawDebugSphere(GetWorld(), center + maxExtent, 4.0f, 12, FColor().White, false, 0.0f);
				DrawDebugSphere(GetWorld(), center - maxExtent, 4.0f, 12, FColor().White, false, 0.0f);
				elementCount++;
			}
		}
		// UE_LOG(LogTemp, Log, TEXT("Node Count: %d, Element Count: %d"), nodeCount, elementCount);
	}
}

void ASpatialPartioningOctree::AddOctreeElement(const FOctreeElement& inNewOctreeElement)
{
	check(bInitialized);
	OctreeData->AddElement(inNewOctreeElement);
	UE_LOG(LogTemp, Log, TEXT("Added element to Octree."));
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

