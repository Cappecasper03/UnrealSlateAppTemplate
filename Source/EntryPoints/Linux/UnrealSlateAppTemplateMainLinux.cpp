// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSlateAppTemplateApp.h"

#if PLATFORM_LINUX
#include "UnixCommonStartup.h"

int main( int argc, char* argv[ ] )
{
	return CommonUnixMain( argc, argv, &RunUnrealSlateAppTemplate );
}
#endif