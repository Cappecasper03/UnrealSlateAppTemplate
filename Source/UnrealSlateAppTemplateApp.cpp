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

	// Flags this program as staged sos that the saved folder is inside the project directory
	const TCHAR* Filename   = *FPaths::Combine( FPaths::EngineConfigDir(), FString::Printf( TEXT( "StagedBuild_%s.ini" ), FApp::GetProjectName() ) );
	FArchive*    FileWriter = IFileManager::Get().CreateFileWriter( Filename );
	if( FileWriter )
	{
		FileWriter->Close();
		delete FileWriter;
	}

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
		TRACE_CPUPROFILER_EVENT_SCOPE( RunUnrealSlateAppTemplate::Tick );
		TRACE_BEGIN_FRAME( TraceFrameType_Game );

		BeginExitIfRequested();

		FApp::SetCurrentTime( FPlatformTime::Seconds() );
		FApp::SetDeltaTime( FApp::GetCurrentTime() - FApp::GetLastTime() );
		FApp::UpdateLastTime();

		FTaskGraphInterface::Get().ProcessThreadUntilIdle( ENamedThreads::GameThread );
		FStats::AdvanceFrame( false );
		FTSTicker::GetCoreTicker().Tick( FApp::GetDeltaTime() );
		FSlateApplication::Get().PumpMessages();
		FSlateApplication::Get().Tick();

		{
			TRACE_CPUPROFILER_EVENT_SCOPE( RunUnrealSlateAppTemplate::Tick::Sleep );
			static constexpr double IdealDeltaTime = 1.f / 60.f;
			FPlatformProcess::Sleep( FMath::Max< double >( 0, IdealDeltaTime - ( FPlatformTime::Seconds() - FApp::GetLastTime() ) ) );
		}

		GFrameCounter++;

		TRACE_END_FRAME( TraceFrameType_Game );
	}

	FCoreDelegates::OnExit.Broadcast();
	FSlateApplication::Shutdown();
	FModuleManager::Get().UnloadModulesAtShutdown();

	GEngineLoop.AppPreExit();
	GEngineLoop.AppExit();

	return 0;
}