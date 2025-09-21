// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineISMActor.h"

ASplineISMActor::ASplineISMActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
	RootComponent = SplineComp;

	SplineComp->ClearSplinePoints(false);
	SplineComp->AddSplinePoint(FVector(0, 0, 0), ESplineCoordinateSpace::Local);
	SplineComp->AddSplinePoint(FVector(300, 0, 0), ESplineCoordinateSpace::Local);
	SplineComp->AddSplinePoint(FVector(600, 300, 0), ESplineCoordinateSpace::Local);
	SplineComp->AddSplinePoint(FVector(600, 600, 0), ESplineCoordinateSpace::Local);

	SplineComp->SetClosedLoop(false);

	ISMComp = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ISMComp"));
	ISMComp->SetupAttachment(RootComponent);

#if WITH_EDITOR
	ISMComp->bHasPerInstanceHitProxies = true;
#endif


#if WITH_EDITORONLY_DATA
	ISMComp->bIsEditorOnly = true;
	ISMComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ISMComp->SetIsVisualizationComponent(true);
#endif
}

#if WITH_EDITOR
void ASplineISMActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ISMComp->ClearInstances();

	if (!PointMesh) return;
	ISMComp->SetStaticMesh(PointMesh);

	const int32 NumPoints = SplineComp->GetNumberOfSplinePoints();
	for (int32 i = 0; i < NumPoints; i++)
	{
		FVector Pos = SplineComp->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		FTransform InstanceXForm(FRotator::ZeroRotator, Pos, FVector(0.1f)); // small spheres/cubes
		ISMComp->AddInstance(InstanceXForm);
	}
}
#endif
