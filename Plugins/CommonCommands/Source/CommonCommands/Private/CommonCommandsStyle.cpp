// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonCommandsStyle.h"
#include "CommonCommands.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FCommonCommandsStyle::StyleInstance = nullptr;

void FCommonCommandsStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FCommonCommandsStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FCommonCommandsStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("CommonCommandsStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FCommonCommandsStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("CommonCommandsStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("CommonCommands")->GetBaseDir() / TEXT("Resources"));

	Style->Set("CommonCommands.PluginAction", new IMAGE_BRUSH(TEXT("CommonCommandsIcon"), Icon20x20));
	return Style;
}

void FCommonCommandsStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FCommonCommandsStyle::Get()
{
	return *StyleInstance;
}
