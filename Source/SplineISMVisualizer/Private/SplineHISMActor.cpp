// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineHISMActor.h"
#include "ClickableHISMComponent.h"

ASplineHISMActor::ASplineHISMActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;

	Spline->ClearSplinePoints(false);
	Spline->AddSplinePoint(FVector(0, 0, 10), ESplineCoordinateSpace::Local);
	Spline->AddSplinePoint(FVector(300, 0, 10), ESplineCoordinateSpace::Local);
	Spline->AddSplinePoint(FVector(600, 300, 10), ESplineCoordinateSpace::Local);
	Spline->AddSplinePoint(FVector(600, 600, 10), ESplineCoordinateSpace::Local);

	Spline->SetClosedLoop(false);

	PointHISM = CreateDefaultSubobject<UClickableHISMComponent>(TEXT("PointHISM"));
	SegmentHISM = CreateDefaultSubobject<UClickableHISMComponent>(TEXT("SegmentHISM"));

	PointHISM->SetupAttachment(RootComponent);
	SegmentHISM->SetupAttachment(RootComponent);

	// Editor-only visualization flags and perf defaults
#if WITH_EDITORONLY_DATA
	PointHISM->bIsEditorOnly = true;
	SegmentHISM->bIsEditorOnly = true;
	PointHISM->SetIsVisualizationComponent(true);
	SegmentHISM->SetIsVisualizationComponent(true);
#endif

	PointHISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SegmentHISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PointHISM->SetMobility(EComponentMobility::Movable);
	SegmentHISM->SetMobility(EComponentMobility::Movable);
}

#if WITH_EDITOR
void ASplineHISMActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	RebuildInstances();
}

void ASplineHISMActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	// Rebuild when you tweak settings in the Details panel
	RebuildInstances();
}

void ASplineHISMActor::RebuildInstances()
{
	// Clear previous instances
	PointHISM->ClearInstances();
	SegmentHISM->ClearInstances();

	// Assign meshes if set

	if (PointMesh)   PointHISM->SetStaticMesh(PointMesh);
	// Per-instance clickability (Editor only)
	PointHISM->bHasPerInstanceHitProxies = bPerInstanceHitProxy;
	PointHISM->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PointHISM->SetCollisionResponseToAllChannels(ECR_Ignore);
	PointHISM->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	if (SegmentMesh) SegmentHISM->SetStaticMesh(SegmentMesh);
	SegmentHISM->bHasPerInstanceHitProxies = bPerInstanceHitProxy;
	SegmentHISM->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SegmentHISM->SetCollisionResponseToAllChannels(ECR_Ignore);
	SegmentHISM->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	const int32 Num = Spline->GetNumberOfSplinePoints();
	if (Num <= 0 || !PointMesh) return;

	// Add an instance at each spline point
	for (int32 i = 0; i < Num; ++i)
	{
		const FVector  LPos = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		const FRotator LRot = Spline->GetRotationAtSplinePoint(i, ESplineCoordinateSpace::Local);

		FTransform Xf(LRot, LPos, FVector(MarkerScale));
		PointHISM->AddInstance(Xf);
	}

	// Optionally add �tick� markers along segments
	if (SegmentMesh && SegmentStep > 1.f)
	{
		const float TotalLen = Spline->GetSplineLength();
		for (float Dist = 0.f; Dist <= TotalLen; Dist += SegmentStep)
		{
			const FVector  LPos = Spline->GetLocationAtDistanceAlongSpline(Dist, ESplineCoordinateSpace::Local);
			const FRotator LRot = Spline->GetRotationAtDistanceAlongSpline(Dist, ESplineCoordinateSpace::Local);
			FTransform Xf(LRot, LPos, FVector(MarkerScale));
			SegmentHISM->AddInstance(Xf);
		}
	}

	// If you�re using a material that reads Per-Instance Custom Data,
	// you can set values per instance like so (example: color index = point id):
	// PointHISM->NumCustomDataFloats = 1;
	// for (int32 i = 0; i < PointHISM->GetInstanceCount(); ++i)
	//     PointHISM->SetCustomDataValue(i, /*DataIndex=*/0, (float)i, /*MarkRenderStateDirty=*/false);
	// PointHISM->MarkRenderStateDirty();
}
#endif

