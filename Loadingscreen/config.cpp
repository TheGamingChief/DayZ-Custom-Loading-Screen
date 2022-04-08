class CfgPatches {
	class YourPatchesHere {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data", "DZ_Gear_Consumables", "DZ_Vehicles_Wheeled", "DZ_Structures_Residential", "DZ_Sounds_Effects", "DZ_Sounds_Weapons"};
	};
};

class CfgMods {
	class YourModHere {
		dir = "Loadingscreen";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "Loadingscreen";
		credits = "";
		author = "TheGamingChief";
		authorID = "0";
		version = 1;
		extra = 0;
		type = "mod";
		dependencies[] = {"Game"};
		
		class defs {
			class gameScriptModule {
				value = "";
				files[] = {"Loadingscreen/scripts/3_Game"};
			};
		};
	};
};
