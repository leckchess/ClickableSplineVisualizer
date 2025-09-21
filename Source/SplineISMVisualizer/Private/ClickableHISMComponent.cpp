// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickableHISMComponent.h"

UClickableHISMComponent::UClickableHISMComponent()
{
#if WITH_EDITORONLY_DATA
	bIsEditorOnly = false;
	SetIsVisualizationComponent(false);
#endif
}
