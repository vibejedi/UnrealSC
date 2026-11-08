using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealSCEditorTarget : TargetRules
{
    public UnrealSCEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("UnrealSC");
    }
}
