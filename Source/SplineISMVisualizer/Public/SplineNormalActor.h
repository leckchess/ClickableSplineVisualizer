// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "SplineNormalActor.generated.h"

UCLASS()
class SPLINEISMVISUALIZER_API ASplineNormalActor : public AActor
{
	GENERATED_BODY()
	
public:
	ASplineNormalActor();

protected:
	UPROPERTY(VisibleAnywhere)
	USplineComponent* SplineComp;

};
