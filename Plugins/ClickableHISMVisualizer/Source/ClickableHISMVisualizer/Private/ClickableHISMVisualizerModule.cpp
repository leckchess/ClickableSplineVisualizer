// Copyright Epic Games, Inc. All Rights Reserved.

#include "ClickableHISMVisualizerModule.h"
#include "Editor/UnrealEdEngine.h"
#include "UnrealEdGlobals.h"
#include "ClickableHISMVisualizerEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "ClickableHISMVisualizerModule"

void FClickableHISMVisualizerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FClickableHISMVisualizerEditorModeCommands::Register();

#if WITH_EDITOR
	if (GUnrealEd)
	{
		TSharedPtr<FComponentVisualizer> Visualizer = MakeShared<FClickableHISMVisualizer>();
		GUnrealEd->RegisterComponentVisualizer(UClickableHISMComponent::StaticClass()->GetFName(), Visualizer);
		Visualizer->OnRegister();
	}
#endif
}

void FClickableHISMVisualizerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FClickableHISMVisualizerEditorModeCommands::Unregister();

#if WITH_EDITOR
	if (GUnrealEd)
	{
		GUnrealEd->UnregisterComponentVisualizer(UClickableHISMComponent::StaticClass()->GetFName());
	}
#endif
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FClickableHISMVisualizerModule, ClickableHISMVisualizer)

IMPLEMENT_HIT_PROXY(HClickableHISMVisProxy, HComponentVisProxy);
void FClickableHISMVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView*, FPrimitiveDrawInterface* PDI)
{
	const UClickableHISMComponent* HISM = Cast<UClickableHISMComponent>(Component);
	if (!HISM) return;
	
	for (int32 Idx = 0; Idx < HISM->GetInstanceCount(); ++Idx)
	{
		FTransform Xf;
		HISM->GetInstanceTransform(Idx, Xf, true);

		// Attach proxy to this draw call
		PDI->SetHitProxy(new HClickableHISMVisProxy(HISM, Idx));
		DrawWireSphere(PDI, Xf.GetLocation(), FLinearColor::Yellow, 8.f, 8, SDPG_Foreground, 1.0f);
		PDI->SetHitProxy(nullptr);
	}
}

bool FClickableHISMVisualizer::VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click)
{
	if (HClickableHISMVisProxy* MyProxy = HitProxyCast<HClickableHISMVisProxy>(VisProxy))
	{
		if (const UClickableHISMComponent* HISM = Cast<UClickableHISMComponent>(MyProxy->Component.Get()))
		{
			UE_LOG(LogTemp, Log, TEXT("Clicked HISM %s instance %d"), HISM->GetOwner() ? *HISM->GetOwner()->GetName() : TEXT(""), MyProxy->InstanceIndex);
			return true;
		}
	}
	return false;
}
