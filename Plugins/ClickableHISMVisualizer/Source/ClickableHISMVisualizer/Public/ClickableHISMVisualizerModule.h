// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "ClickableHISMComponent.h"
#include "SceneManagement.h"
#include "HitProxies.h"
#include "ComponentVisualizer.h"

/**
 * This is the module definition for the editor mode. You can implement custom functionality
 * as your plugin module starts up and shuts down. See IModuleInterface for more extensibility options.
 */
class FClickableHISMVisualizerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

// Custom proxy that represents a specific instance of your HISM
struct HClickableHISMVisProxy : public HComponentVisProxy
{
	DECLARE_HIT_PROXY();

	int32 InstanceIndex = INDEX_NONE;

	HClickableHISMVisProxy(const UClickableHISMComponent* InComponent, int32 InInstanceIndex)
		: HComponentVisProxy(InComponent, HPP_Wireframe)
		, InstanceIndex(InInstanceIndex)
	{}
};

class FClickableHISMVisualizer : public FComponentVisualizer
{
public:
	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView*, FPrimitiveDrawInterface* PDI) override;
	virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient,
	                                 HComponentVisProxy* VisProxy,
	                                 const FViewportClick& Click) override;
	// We don't need to draw custom geometry; engine already renders HISM
};