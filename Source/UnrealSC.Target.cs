using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealSCTarget : TargetRules
{
    public UnrealSCTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("UnrealSC");
    }
}
