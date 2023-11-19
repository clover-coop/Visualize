// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Visualize : ModuleRules
{
	public Visualize(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "..", "ThirdParty", "cppdelaunay", "libcppdelaunay.a"));
		// PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "..", "ThirdParty", "cppdelaunay"));
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
			"Foliage",
			"Json", "JsonUtilities",
			"Landscape", "LandscapeEditor",
			"LevelSequence",
			"ProceduralMeshComponent", "MeshDescription",
			"Text3D",
			"UMG",
			"WebSockets",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "MovieScene" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
