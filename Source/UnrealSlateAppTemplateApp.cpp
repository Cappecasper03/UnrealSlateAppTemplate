// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSlateAppTemplateApp.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "Runtime/Launch/Public/RequiredProgramMainCPPInclude.h"
#include "StandaloneRenderer.h"

IMPLEMENT_APPLICATION( UnrealSlateAppTemplate, "UnrealSlateAppTemplate" );

DEFINE_LOG_CATEGORY( UnrealSlateAppTemplate );

int RunUnrealSlateAppTemplate( const TCHAR* Commandline )
{
	FTaskTagScope TaskTagScope( ETaskTag::EGameThread );

	// start up the main loop
	GEngineLoop.PreInit( Commandline );

	// Make sure all UObject classes are registered and default properties have been initialized
	ProcessNewlyLoadedUObjects();

	// Tell the module manager it may now process newly-loaded UObjects when new C++ modules are loaded
	FModuleManager::Get().StartProcessingNewlyLoadedObjects();

	// Crank up a normal Slate application using the platform's standalone renderer
	FSlateApplication::InitializeAsStandaloneApplication( GetStandardStandaloneRenderer() );
	FSlateApplication::InitHighDPI( true );

	// Set the application name
	FGlobalTabmanager::Get()->SetApplicationTitle( FText::FromString( "UnrealSlateAppTemplate" ) );

	// launch the main window of the UnrealSlateAppTemplate application
	FSlateApplication::Get().AddWindow( SNew( SWindow )[ SNew( STextBlock ).Text( FText::FromString( "Find this in the UnrealSlateAppTemplateApp.cpp to change it" ) ) ] );

	while( !IsEngineExitRequested() )
	{
		BeginExitIfRequested();

		FTaskGraphInterface::Get().ProcessThreadUntilIdle( ENamedThreads::GameThread );
		FStats::AdvanceFrame( false );
		FTSTicker::GetCoreTicker().Tick( FApp::GetDeltaTime() );
		FSlateApplication::Get().PumpMessages();
		FSlateApplication::Get().Tick();
		FPlatformProcess::Sleep( 0.01 );

		GFrameCounter++;
	}

	FCoreDelegates::OnExit.Broadcast();
	FSlateApplication::Shutdown();
	FModuleManager::Get().UnloadModulesAtShutdown();

	GEngineLoop.AppPreExit();
	GEngineLoop.AppExit();

	return 0;
}