// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TP1Obligatorio : ModuleRules
{
	public TP1Obligatorio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TP1Obligatorio",
			"TP1Obligatorio/Variant_Platforming",
			"TP1Obligatorio/Variant_Platforming/Animation",
			"TP1Obligatorio/Variant_Combat",
			"TP1Obligatorio/Variant_Combat/AI",
			"TP1Obligatorio/Variant_Combat/Animation",
			"TP1Obligatorio/Variant_Combat/Gameplay",
			"TP1Obligatorio/Variant_Combat/Interfaces",
			"TP1Obligatorio/Variant_Combat/UI",
			"TP1Obligatorio/Variant_SideScrolling",
			"TP1Obligatorio/Variant_SideScrolling/AI",
			"TP1Obligatorio/Variant_SideScrolling/Gameplay",
			"TP1Obligatorio/Variant_SideScrolling/Interfaces",
			"TP1Obligatorio/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
