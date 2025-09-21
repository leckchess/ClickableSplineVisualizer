// Copyright Epic Games, Inc. All Rights Reserved.

#include "ClickableHISMVisualizerEditorMode.h"
#include "ClickableHISMVisualizerEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "ClickableHISMVisualizerEditorModeCommands.h"
#include "Modules/ModuleManager.h"


//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// AddYourTool Step 1 - include the header file for your Tools here
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
#include "Tools/ClickableHISMVisualizerSimpleTool.h"
#include "Tools/ClickableHISMVisualizerInteractiveTool.h"

// step 2: register a ToolBuilder in FClickableHISMVisualizerEditorMode::Enter() below


#define LOCTEXT_NAMESPACE "ClickableHISMVisualizerEditorMode"

const FEditorModeID UClickableHISMVisualizerEditorMode::EM_ClickableHISMVisualizerEditorModeId = TEXT("EM_ClickableHISMVisualizerEditorMode");

FString UClickableHISMVisualizerEditorMode::SimpleToolName = TEXT("ClickableHISMVisualizer_ActorInfoTool");
FString UClickableHISMVisualizerEditorMode::InteractiveToolName = TEXT("ClickableHISMVisualizer_MeasureDistanceTool");


UClickableHISMVisualizerEditorMode::UClickableHISMVisualizerEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UClickableHISMVisualizerEditorMode::EM_ClickableHISMVisualizerEditorModeId,
		LOCTEXT("ModeName", "ClickableHISMVisualizer"),
		FSlateIcon(),
		true);
}


UClickableHISMVisualizerEditorMode::~UClickableHISMVisualizerEditorMode()
{
}


void UClickableHISMVisualizerEditorMode::ActorSelectionChangeNotify()
{
}

void UClickableHISMVisualizerEditorMode::Enter()
{
	UEdMode::Enter();

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// AddYourTool Step 2 - register the ToolBuilders for your Tools here.
	// The string name you pass to the ToolManager is used to select/activate your ToolBuilder later.
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 
	const FClickableHISMVisualizerEditorModeCommands& SampleToolCommands = FClickableHISMVisualizerEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.SimpleTool, SimpleToolName, NewObject<UClickableHISMVisualizerSimpleToolBuilder>(this));
	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UClickableHISMVisualizerInteractiveToolBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, SimpleToolName);
}

void UClickableHISMVisualizerEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FClickableHISMVisualizerEditorModeToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UClickableHISMVisualizerEditorMode::GetModeCommands() const
{
	return FClickableHISMVisualizerEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE
