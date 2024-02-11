class CfgPatches
{
	class Loadingscreen_Scripts
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class Loadingscreen
	{
		dir="Loadingscreen";
		author="TheGamingChief";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"Loadingscreen/Scripts/3_Game"
				};
			};
		};
	};
};
