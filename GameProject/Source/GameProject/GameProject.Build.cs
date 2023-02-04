// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameProject : ModuleRules
{
	public GameProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "GameplayTasks", "SlateCore", "EnhancedInput" });
      
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"EnhancedInput",
			}
		);
    }
}
