// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

[SupportedPlatforms( "Win64", "Linux" )]
[SupportedConfigurations( UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development, UnrealTargetConfiguration.Shipping )]
public sealed class UnrealSlateAppTemplateTarget : TargetRules
{
	public UnrealSlateAppTemplateTarget( TargetInfo Target ) : base( Target )
	{
		Type                 = TargetType.Program;
		LinkType             = TargetLinkType.Monolithic;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion  = EngineIncludeOrderVersion.Latest;

		LaunchModuleName = "UnrealSlateAppTemplate";

		bCompileAgainstEngine      = false;
		bCompileAgainstCoreUObject = true;
		bUseLoggingInShipping      = true;
		bUseChecksInShipping       = false;
		bHasExports                = false;
		bBuildDeveloperTools       = false;
		bEnableTrace               = true;
		bCompileICU                = true;
	}
}