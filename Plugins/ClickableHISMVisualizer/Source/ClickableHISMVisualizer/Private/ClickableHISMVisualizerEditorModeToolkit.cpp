// Copyright Epic Games, Inc. All Rights Reserved.

#include "ClickableHISMVisualizerEditorModeToolkit.h"
#include "ClickableHISMVisualizerEditorMode.h"
#include "Engine/Selection.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "ClickableHISMVisualizerEditorModeToolkit"

FClickableHISMVisualizerEditorModeToolkit::FClickableHISMVisualizerEditorModeToolkit()
{
}

void FClickableHISMVisualizerEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
}

void FClickableHISMVisualizerEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FClickableHISMVisualizerEditorModeToolkit::GetToolkitFName() const
{
	return FName("ClickableHISMVisualizerEditorMode");
}

FText FClickableHISMVisualizerEditorModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "ClickableHISMVisualizerEditorMode Toolkit");
}

#undef LOCTEXT_NAMESPACE
