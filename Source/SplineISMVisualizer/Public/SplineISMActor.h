// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "SplineISMActor.generated.h"

UCLASS()
class SPLINEISMVISUALIZER_API ASplineISMActor : public AActor
{
	GENERATED_BODY()
	
public:
	ASplineISMActor();

protected:
	UPROPERTY(VisibleAnywhere)
	USplineComponent* SplineComp;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* ISMComp;

#if WITH_EDITORONLY_DATA
	// Editor-only visualization mesh
	UPROPERTY(EditAnywhere, Category = "Editor")
	UStaticMesh* PointMesh;
#endif

#if WITH_EDITOR
	virtual void OnConstruction(const FTransform& Transform) override;
#endif

};
