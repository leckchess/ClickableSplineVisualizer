// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "ClickableHISMComponent.generated.h"

/**
 * 
 */
UCLASS()
class SPLINEISMVISUALIZER_API UClickableHISMComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	UClickableHISMComponent();

#if WITH_EDITORONLY_DATA
	/** Make each instance individually selectable in the editor */
	UPROPERTY(EditAnywhere, Category = "Editor")
	bool bPerInstanceHitProxy = true;
#endif
	
};
