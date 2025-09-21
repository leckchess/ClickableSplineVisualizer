// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "SplineHISMActor.generated.h"

class UClickableHISMComponent;

UCLASS()
class SPLINEISMVISUALIZER_API ASplineHISMActor : public AActor
{
	GENERATED_BODY()
	
public:
	ASplineHISMActor();

#if WITH_EDITOR
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	UPROPERTY(VisibleAnywhere, Category = "Spline")
	USplineComponent* Spline;

	// Markers for each spline point
	UPROPERTY(VisibleAnywhere, Category = "Editor Viz")
	UClickableHISMComponent* PointHISM;

	// Optional: “ticks” along the segments
	UPROPERTY(VisibleAnywhere, Category = "Editor Viz")
	UClickableHISMComponent* SegmentHISM;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Editor Viz|Meshes")
	UStaticMesh* PointMesh;

	UPROPERTY(EditAnywhere, Category = "Editor Viz|Meshes")
	UStaticMesh* SegmentMesh;

	// spacing between segment ticks (cm)
	UPROPERTY(EditAnywhere, Category = "Editor Viz|Settings", meta = (ClampMin = "5.0"))
	float SegmentStep = 100.f;

	// uniform scale for markers
	UPROPERTY(EditAnywhere, Category = "Editor Viz|Settings", meta = (ClampMin = "0.01"))
	float MarkerScale = 0.2f;

	// turn on per-instance hit proxies for clickable instances (Editor only)
	UPROPERTY(EditAnywhere, Category = "Editor Viz|Settings")
	bool bPerInstanceHitProxy = true;
#endif

private:
#if WITH_EDITOR
	void RebuildInstances();
#endif

};
