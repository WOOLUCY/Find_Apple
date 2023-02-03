// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameProject : ModuleRules
{
	public GameProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "GameplayTasks", "SlateCore" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG"});

		PublicIncludePaths.AddRange(new string[]
		{
			"EnhancedInput/Public"
		});
    }
}
