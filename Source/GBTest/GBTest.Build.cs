// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GBTest : ModuleRules
{
	public GBTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
