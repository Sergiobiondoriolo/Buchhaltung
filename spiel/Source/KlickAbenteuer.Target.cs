using UnrealBuildTool;

public class KlickAbenteuerTarget : TargetRules
{
	public KlickAbenteuerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("KlickAbenteuer");
	}
}
