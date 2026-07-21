using UnrealBuildTool;
using System.IO;

public class LibWebp : ModuleRules
{
    public LibWebp(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        
        PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "webp-1.6.0", "include"));
        bool bWithWebp = false;
        
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string LibPath = Path.Combine(ModuleDirectory, "lib", Target.Platform.ToString());
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libwebp.lib"));
            bWithWebp = true;
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            string LibPath = Path.Combine(ModuleDirectory, "lib", "Unix", Target.Architecture.LinuxName);
            PublicAdditionalLibraries.Add(Path.Combine(LibPath, "libwebp.a"));
            bWithWebp = true;
        }

        PublicDefinitions.Add("WITH_WEBP_LIB=" + (bWithWebp ? '1' : '0'));
    }
}