// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameProject : ModuleRules
{
	public GameProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "AIModule", "GameplayTasks", "SlateCore", "EnhancedInput", "Niagara", "LevelSequence", "MovieScene", "CableComponent", "PhysicsCore" });

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"EnhancedInput", "CableComponent"
            }
		);
	}
}
