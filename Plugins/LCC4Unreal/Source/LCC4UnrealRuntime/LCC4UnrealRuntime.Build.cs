// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class LCC4UnrealRuntime : ModuleRules
{
	public LCC4UnrealRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUsePrecompiled = true;
		bEnableExceptions = true;

		PublicDefinitions.Add("WITH_LCC=1");

		PublicIncludePaths.AddRange(
			new string[]
			{
				// ... add public include paths required here ...
			}
		);

		PrivateIncludePaths.AddRange(
			new[]
			{
				"LCC4UnrealRuntime/Private",
				Path.Combine(GetModuleDirectory("Renderer"), "Private")
			}
		);

		var Version = Target.Version;
		// FPostProcessingInputs / FTranslucencyPassResources live under Renderer/Internal
		// starting with UE 5.4 (needed by the PrePostProcessPass InverseACES path).
		if (Version.MajorVersion >= 5 && Version.MinorVersion >= 4)
			PrivateIncludePaths.AddRange(
				new[]
				{
					Path.Combine(GetModuleDirectory("Renderer"), "Internal")
				}
			);

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
				"CoreUObject",
				"DeveloperSettings"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"Engine",
				"Slate",
				"SlateCore",
				"Core",
				"Engine",
				"RenderCore",
				"Renderer",
				"Projects",
				"RHI",
				"InputCore",
				"Json",
				"JsonUtilities",
				"HTTP",
				"SSL",
				"EngineSettings",
				"ApplicationCore",
				"OpenSSL",
				"GeoReferencing",
				"LCC4UnrealCesium",
				"LibWebp",
				"LCCLibZip"
			}
		);

		if (Target.bBuildEditor)
			PrivateDependencyModuleNames.AddRange(
				new[]
				{
					"EditorFramework",
					"UnrealEd",
					"PropertyEditor",
					"ContentBrowser",
					"AssetRegistry",
					"DesktopPlatform"
				}
			);

		var ResourcePath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../Resources/"));
		RuntimeDependencies.Add(Path.Combine(ResourcePath, "public_key.pem"));

		// GPU memory monitoring: PDH (Performance Data Helper) for Windows
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicSystemLibraries.Add("pdh.lib");
			PublicSystemLibraries.Add("dxgi.lib");
		}
	}
}
