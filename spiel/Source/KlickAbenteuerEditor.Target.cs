using UnrealBuildTool;

public class KlickAbenteuerEditorTarget : TargetRules
{
	public KlickAbenteuerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("KlickAbenteuer");
	}
}
