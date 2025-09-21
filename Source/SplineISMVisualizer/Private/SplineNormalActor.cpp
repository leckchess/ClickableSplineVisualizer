// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineNormalActor.h"

// Sets default values
ASplineNormalActor::ASplineNormalActor()
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

}

