#include "Menu.h"
#include "Controls.h"
#include "Hooks.h" // For the unloading pepe
#include "Interfaces.h"
#include "CRC32.h"
#include "AltXor.h"
#define WINDOW_WIDTH 560 // Menu Width
#define WINDOW_HEIGHT 350 // Menu Height

silenthacks Menu::Window;
#include "xor.h"
void UpdatePlayerList();

bool showaimbot;
std::map<DWORD, PlayerListItem_t> PlayerList;

void SaveLegitCallbk()
{
	switch (Menu::Window.MiscTab.lstPlayers.GetIndex())
	{
	case 0:
		GUI.SaveWindowState(&Menu::Window, "legit3949.cfg");
		break;

	case 1:
		GUI.SaveWindowState(&Menu::Window, "Rage3949.cfg");
		break;

	case 2:
		GUI.SaveWindowState(&Menu::Window, "HvH3949.cfg");
		break;
	}
}


void LoadLegitCallbk()
{
	switch (Menu::Window.MiscTab.lstPlayers.GetIndex())
	{
	case 0:
		GUI.LoadWindowState(&Menu::Window, "legit3949.cfg");
		break;

	case 1:
		GUI.LoadWindowState(&Menu::Window, "Rage3949.cfg");
		break;

	case 2:
		GUI.LoadWindowState(&Menu::Window, "HvH3949.cfg");
		break;
	}
}
void SaveCallbk() // Saving Config to CSGO directory
{
	GUI.SaveWindowState(&Menu::Window, "config.xml");
}

void LoadCallbk() // Loading Config from CSGO directory
{
	GUI.LoadWindowState(&Menu::Window, "config.xml");
}

//void UnLoadCallbk() // Unload Button Function
//{
//	DoUnload = true;
//}


void silenthacks::Setup()
{
	SetPosition(300, 300);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	SetTitle(XorStringAlt("silenthacks build date: " __DATE__));


	RegisterTab(&RageBotTab);
	
	RegisterTab(&VisualsTab);
	RegisterTab(&MiscTab);
	//RegisterTab(&SkinTab);

	RECT Client = GetClientArea();
	Client.bottom -= 29;

	RageBotTab.Setup();
	
	VisualsTab.Setup();
	MiscTab.Setup();
	
	//SkinTab.Setup();
	



	 // The Ones I Dont Use
	//RegisterTab(&LegitBotTab);
	RegisterTab(&PlayersTab);
	//RegisterTab(&GUITab);
	//LegitBotTab.Setup();
	PlayersTab.Setup();
	//GUITab.Setup();

#pragma region Bottom Buttons
	SaveButton3.SetText("Save");
	SaveButton3.SetCallback(SaveLegitCallbk);
	SaveButton3.SetPosition(300, 50);

	LoadButton3.SetText("Load");
	LoadButton3.SetCallback(LoadLegitCallbk);
	LoadButton3.SetPosition(300, 80);


	/*RageBotTab.RegisterControl(&SaveButton);
	RageBotTab.RegisterControl(&LoadButton);
		
	VisualsTab.RegisterControl(&SaveButton);
	VisualsTab.RegisterControl(&LoadButton);

	MiscTab.RegisterControl(&SaveButton);
	MiscTab.RegisterControl(&LoadButton);


	RageBotTab.RegisterControl(&SaveButton2);
	RageBotTab.RegisterControl(&LoadButton2);

	VisualsTab.RegisterControl(&SaveButton2);
	VisualsTab.RegisterControl(&LoadButton2);

	MiscTab.RegisterControl(&SaveButton2);
	MiscTab.RegisterControl(&LoadButton2);

	RageBotTab.RegisterControl(&SaveButton3);
	RageBotTab.RegisterControl(&LoadButton3);

	VisualsTab.RegisterControl(&SaveButton3);
	VisualsTab.RegisterControl(&LoadButton3);
	*/
	MiscTab.RegisterControl(&SaveButton3);
	MiscTab.RegisterControl(&LoadButton3);

	//Playerlist.RegisterControl(&SaveButton);

	//MiscTab.RegisterControl(&ConfigBox);
	//MiscTab.RegisterControl(&LoadButton);


	//Playerlist.RegisterControl(&LoadButton);

	//	RageBotTab.RegisterControl(&UnloadButton);
	//	LegitBotTab.RegisterControl(&UnloadButton);
	//VisualsTab.RegisterControl(&UnloadButton);
	//MiscTab.RegisterControl(&UnloadButton);
	//	SkinTab.RegisterControl(&UnloadButton);
	//	GUITab.RegisterControl(&UnloadButton);
	//Playerlist.RegisterControl(&UnloadButton);

#pragma endregion Setting up the settings buttons
}

void CRageBotTab::Setup()
{
	SetTitle("R");

#pragma region Aimbot

	AimbotGroup.SetPosition(0, 5);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(200, 150);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("Enabled", this, &AimbotEnable);

	TargetSelection.SetFileId("tgt_selection");
	TargetSelection.AddItem("Cycle");
	TargetSelection.AddItem("Distance");
	TargetSelection.AddItem("Health");
	AimbotGroup.PlaceLabledControl("Target selection", this, &TargetSelection);

	TargetHitbox.SetFileId("tgt_hitbox");
	TargetHitbox.AddItem("Head");
	TargetHitbox.AddItem("Neck");
	TargetHitbox.AddItem("Chest");
	TargetHitbox.AddItem("Stomach");
	TargetHitbox.AddItem("Pelvis");
	AimbotGroup.PlaceLabledControl("Target hitbox", this, &TargetHitbox);

	TargetMultipoint.SetFileId("tgt_multipoint");
	AimbotGroup.PlaceLabledControl("Multipoint", this, &TargetMultipoint);

	TargetHitscan.SetFileId("tgt_hitscan");
	AimbotGroup.PlaceLabledControl("Hitscan", this, &TargetHitscan);

#pragma endregion Aimbot Controls Get Setup in here
#pragma region AlternetAimbot

	AimbotGroup2.SetPosition(173, 5);
	AimbotGroup2.SetText("Aimbot");
	AimbotGroup2.SetSize(200, 150);
	RegisterControl(&AimbotGroup2);


	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup2.PlaceLabledControl("Automatic fire", this, &AimbotAutoFire);

	AccuracyRecoil.SetFileId("acc_norecoil");
	AimbotGroup2.PlaceLabledControl("Remove recoil", this, &AccuracyRecoil);

	AimbotSilentAim.SetFileId("aim_silent");
	AimbotGroup2.PlaceLabledControl("Silent aim", this, &AimbotSilentAim);

	AccuracyHitchance.SetFileId("acc_chance");
	AccuracyHitchance.SetBoundaries(0, 100);
	AccuracyHitchance.SetValue(0);
	AimbotGroup2.PlaceLabledControl("Minimum hit chance", this, &AccuracyHitchance);

	AccuracyMinimumDamage.SetFileId("acc_mindmg");
	AccuracyMinimumDamage.SetBoundaries(0.f, 100.f);
	AccuracyMinimumDamage.SetValue(0.f);
	AimbotGroup2.PlaceLabledControl("Minimum damage", this, &AccuracyMinimumDamage);


#pragma endregion Alternet Controls Get Setup in here
#pragma region epic
	AimbotTitle.SetPosition(10, 15);
	AimbotTitle.SetText("Aimbot");
	AimbotTitle.SetSize(525, 150);
	RegisterControl(&AimbotTitle);
#pragma endregion epic2

#pragma region Alternet3Aimbot

	AimbotGroup3.SetPosition(345, 5);
	AimbotGroup3.SetText("Aimbot");
	AimbotGroup3.SetSize(200, 150);
	RegisterControl(&AimbotGroup3);

	AimbotFov.SetFileId("aim_fov");
	AimbotFov.SetBoundaries(0.f, 180.f);
	AimbotFov.SetValue(39.f);
	AimbotGroup3.PlaceLabledControl("Maximum FOV", this, &AimbotFov);

	AccuracyAutoStop.SetFileId("acc_stop");
	AimbotGroup3.PlaceLabledControl("Quick stop + duck", this, &AccuracyAutoStop);

	AccuracyAutoScope.SetFileId("acc_scope");
	AimbotGroup3.PlaceLabledControl("Automatic Scope", this, &AccuracyAutoScope);

	AimbotAutoPistol.SetFileId("aim_autopistol");
	AimbotGroup3.PlaceLabledControl("Automatic Pistol", this, &AimbotAutoPistol);

	AimbotAutoRevolver.SetFileId("aim_autorevolver");
	AimbotGroup3.PlaceLabledControl("Automatic Revolver", this, &AimbotAutoRevolver);

#pragma endregion Alternet3 Controls Get Setup in here


#pragma region epic
	HvHLabeled.SetPosition(10, 170);
	HvHLabeled.SetText("Hack Vs Hack");
	HvHLabeled.SetSize(525, 110);
	RegisterControl(&HvHLabeled);
#pragma endregion epic2
#pragma region asd
	Epic.SetPosition(173, 160);
	Epic.SetText("Hack Vs Hack");
	Epic.SetSize(200, 150);
	RegisterControl(&Epic);



	AntiAimTarget.SetFileId("aa_target");
	Epic.PlaceLabledControl("Dynamic", this, &AntiAimTarget);

	FakeLag.SetFileId("hvh_fakelag");
	FakeLag.AddItem("Off");
	FakeLag.AddItem("Minimal");
	FakeLag.AddItem("Average");
	FakeLag.AddItem("Maximum");
	Epic.PlaceLabledControl("Fakelag", this, &FakeLag);

	AccuracyResolver.SetFileId("tgt_resolver");
	Epic.PlaceLabledControl("Angle correction", this, &AccuracyResolver);

	AccuracyPrediction.SetFileId("tgt_accuracyboost");
	Epic.PlaceLabledControl("Accuracy Boost", this, &AccuracyPrediction);



	
#pragma endregion sadda

#pragma region asd
	Epic2.SetPosition(345, 160);
	Epic2.SetText("Hack Vs Hack");
	Epic2.SetSize(200, 150);
	RegisterControl(&Epic2);



#pragma endregion sadda
#pragma region Anti-Aim

	// Anti-Aim
	AntiAimGroup.SetPosition(0, 160);
	AntiAimGroup.SetText("Anti-aimbot");
	AntiAimGroup.SetSize(200, 150);
	RegisterControl(&AntiAimGroup);

	//AntiAimEnable.SetFileId("aa_enable");
	AntiAimEnable.SetState(true);
	//AntiAimGroup.PlaceLabledControl("Enable", this, &AntiAimEnable);

	AntiAimPitch.SetFileId("aa_x");
	AntiAimPitch.AddItem("None");
	AntiAimPitch.AddItem("Down");
	AntiAimPitch.AddItem("Default");
	AntiAimPitch.AddItem("Fake Zero");
	AntiAimGroup.PlaceLabledControl("Pitch", this, &AntiAimPitch);

	RealAntiAimYawSlider.SetFileId("aa_yaw_real");
	RealAntiAimYawSlider.SetBoundaries(0, 360);
	RealAntiAimYawSlider.SetValue(0);
	AntiAimGroup.PlaceLabledControl("Real Yaw", this, &RealAntiAimYawSlider);

	FakeAntiAimYawSlider.SetFileId("aa_yaw_fake");
	FakeAntiAimYawSlider.SetBoundaries(0, 360);
	FakeAntiAimYawSlider.SetValue(0);
	AntiAimGroup.PlaceLabledControl("Fake Yaw", this, &FakeAntiAimYawSlider);


#pragma endregion  AntiAim controls get setup in here
#pragma region fuckinggay
	epic3.SetPosition(345, 170);
	epic3.SetText("Aimbot");
	epic3.SetSize(200, 150);
	RegisterControl(&epic3);

	TargetPointscale.SetFileId("acc_pointscale");
	TargetPointscale.SetBoundaries(0.f, 1.f);
	TargetPointscale.SetValue(0.f);
	epic3.PlaceLabledControl("Pointscale", this, &TargetPointscale);
#pragma endregion  fuckinggay controls get setup in here
}



void CVisualTab::Setup()
{
	SetTitle("V");

#pragma region visuals
	Visuals.SetPosition(10, 15);
	Visuals.SetText("Visuals");
	Visuals.SetSize(525, 150);
	RegisterControl(&Visuals);
#pragma endregion visuals


#pragma region Options
	OptionsGroup.SetText("ESP");
	OptionsGroup.SetPosition(0, 5);
	OptionsGroup.SetSize(200, 150);
	RegisterControl(&OptionsGroup);

	OptionsName.SetFileId("opt_name");
	OptionsGroup.PlaceLabledControl("Name", this, &OptionsName);

	OptionsBox.SetFileId("opt_box");
	OptionsGroup.PlaceLabledControl("Box", this, &OptionsBox);

	OptionHealthEnable.SetFileId("opt_health");
	OptionsGroup.PlaceLabledControl("Health", this, &OptionHealthEnable);

	OptionsArmourEnable.SetFileId("opt_armor");
	OptionsGroup.PlaceLabledControl("Armour", this, &OptionsArmourEnable);

	OptionsSkeleton.SetFileId("opt_skeleteon");
	OptionsGroup.PlaceLabledControl("Skeleton", this, &OptionsSkeleton);

	OptionsWeapon.SetFileId("opt_weapon"); // Antiaim List for Yaw
	OptionsGroup.PlaceLabledControl("Weapon", this, &OptionsWeapon);

#pragma endregion Setting up the Options controls
#pragma region epic
	Others.SetPosition(10, 170);
	Others.SetText("Extra");
	Others.SetSize(525, 110);
	RegisterControl(&Others);
#pragma endregion epic2

#pragma region Other
	OtherGroup.SetText("Extra");
	OtherGroup.SetPosition(0, 160);
	OtherGroup.SetSize(200, 150);
	RegisterControl(&OtherGroup);	

	OtherNoVisualRecoil.SetFileId("otr_visrecoil");
	OtherGroup.PlaceLabledControl("Remove visual recoil", this, &OtherNoVisualRecoil);

	OtherNoScope.SetFileId("otr_antiscope");
	OtherGroup.PlaceLabledControl("Anti Scope", this, &OtherNoScope);

	NightMode.SetFileId("otr_worldeffects");
	NightMode.AddItem("Off");
	NightMode.AddItem("Nightmode");
	NightMode.AddItem("Asus");
	NightMode.AddItem("Normal");
	OtherGroup.PlaceLabledControl("World Effects", this, &NightMode);

	OtherNoHands.SetFileId("otr_handeffects");
	OtherNoHands.AddItem("Off");
	OtherNoHands.AddItem("Colored");
	OtherNoHands.AddItem("Wireframe");
	OtherGroup.PlaceLabledControl("Hand Effects", this, &OtherNoHands);

	
#pragma endregion Setting up the Other controls
	
#pragma region gay
	VisualsEffectsGroup.SetText("Visual Effects");
	VisualsEffectsGroup.SetPosition(173, 160);
	VisualsEffectsGroup.SetSize(200, 150);
	RegisterControl(&VisualsEffectsGroup);

	OtherCrosshair.SetFileId("otr_crosshair");
	VisualsEffectsGroup.PlaceLabledControl("Crosshair", this, &OtherCrosshair);

	OtherFOV.SetFileId("regular_fov");
	OtherFOV.SetBoundaries(0, 120);
	OtherFOV.SetValue(90);
	VisualsEffectsGroup.PlaceLabledControl("FOV", this, &OtherFOV);

	OtherViewmodelFOV.SetFileId("viewmodel_fov");
	OtherViewmodelFOV.SetBoundaries(0, 200);
	OtherViewmodelFOV.SetValue(68);
	VisualsEffectsGroup.PlaceLabledControl("Viewmodel FOV", this, &OtherViewmodelFOV);

	//OtherThirdperson.SetFileId("tp_toggle");
	//VisualsEffectsGroup.PlaceLabledControl("Thirdperson", this, &OtherThirdperson);

	//OtherThirdPersonKey.SetFileId("tp_key");
	//VisualsEffectsGroup.PlaceLabledControl("Key", this, &OtherThirdPersonKey);

	//OtherThirdPersonRange.SetFileId("tp_key");
	//OtherThirdPersonRange.SetBoundaries(0, 150);
	//OtherThirdPersonRange.SetValue(90);
	//VisualsEffectsGroup.PlaceLabledControl("Range", this, &OtherThirdPersonRange);

#pragma endregion Setting up the gay controls


}

void CMiscTab::Setup()
{
	SetTitle("Misc");
#pragma region misc
	FirstPart.SetPosition(10, 15);
	FirstPart.SetText("Misc");
	FirstPart.SetSize(525, 150);
	RegisterControl(&FirstPart);
#pragma endregion misc

#pragma region epic
	SecondPart.SetPosition(10, 170);
	SecondPart.SetText("Extra");
	SecondPart.SetSize(525, 110);
	RegisterControl(&SecondPart);
#pragma endregion epic2
#pragma region Other
	OtherGroup.SetPosition(0, 5);
	OtherGroup.SetSize(200, 150);
	OtherGroup.SetText("Other");
	RegisterControl(&OtherGroup);


	//OtherSafeMode.SetFileId("otr_safemode");
	OtherSafeMode.SetState(true);
	//OtherGroup.PlaceLabledControl("Anti Untrusted", this, &OtherSafeMode);

	//Logs.SetFileId("otr_logs");
	Logs.SetState(true);
	//OtherGroup.PlaceLabledControl("Logs", this, &Logs);

	OtherHitmarker.SetFileId("otr_hitmarker");
	OtherGroup.PlaceLabledControl("Hitmarker", this, &OtherHitmarker);

	OtherClantag.SetFileId("otr_clantag");
	OtherGroup.PlaceLabledControl("Spam clantag", this, &OtherClantag);

	NameSpam.SetFileId("otr_spam");
	OtherGroup.PlaceLabledControl("Name spam", this, &NameSpam);

	OtherChatSpam.SetFileId("otr_spam");
	OtherGroup.PlaceLabledControl("Chat Spam", this, &OtherChatSpam);

#pragma endregion other random options

#pragma region FakeLag
	
	FakeLagGroup.SetPosition(173, 5);
	FakeLagGroup.SetSize(200, 150);
	FakeLagGroup.SetText("GameEvent Stuff");
	RegisterControl(&FakeLagGroup);
	lstPlayers.SetFileId("tgt_hitbox");
	lstPlayers.AddItem("Legit");
	lstPlayers.AddItem("MM HvH");
	lstPlayers.AddItem("NS HvH");
	FakeLagGroup.PlaceLabledControl("Configs", this, &lstPlayers);
#pragma region Strafing
	StrafingGroup.SetPosition(0, 160);
	StrafingGroup.SetSize(200, 150);
	StrafingGroup.SetText("Movement");
	RegisterControl(&StrafingGroup);

	OtherAutoJump.SetFileId("otr_autojump");
	StrafingGroup.PlaceLabledControl("Bhop", this, &OtherAutoJump);

	OtherAutoStrafe.SetFileId("otr_autostrafe");
	StrafingGroup.PlaceLabledControl("Auto Strafe", this, &OtherAutoStrafe);

	OtherSlowMo.SetFileId("otr_slowmo");
	StrafingGroup.PlaceLabledControl("Fakewalk", this, &OtherSlowMo);
#pragma endregion

}
void CPlayersTab::Setup()
{
	SetTitle("Colors");
	TeamESP.SetText("Team ESP");
	TeamESP.SetPosition(10, 15);
	TeamESP.SetSize(150, 125);
	RegisterControl(&TeamESP);

	TeamR.SetFileId("colors_team_r");
	TeamR.SetBoundaries(0, 255);
	TeamR.SetValue(0);
	TeamESP.PlaceLabledControl("R", this, &TeamR);

	TeamG.SetFileId("colors_team_g");
	TeamG.SetBoundaries(0, 255);
	TeamG.SetValue(255);
	TeamESP.PlaceLabledControl("G", this, &TeamG);

	TeamB.SetFileId("colors_team_b");
	TeamB.SetBoundaries(0, 255);
	TeamB.SetValue(0);
	TeamESP.PlaceLabledControl("B", this, &TeamB);


	EnemyESP.SetText("Enemy ESP");
	EnemyESP.SetPosition(200, 15);
	EnemyESP.SetSize(150, 125);
	RegisterControl(&EnemyESP);

	EnemyR.SetFileId("colors_enemy_r");
	EnemyR.SetBoundaries(0, 255);
	EnemyR.SetValue(255);
	EnemyESP.PlaceLabledControl("R", this, &EnemyR);

	EnemyG.SetFileId("colors_enemy_g");
	EnemyG.SetBoundaries(0, 255);
	EnemyG.SetValue(0);
	EnemyESP.PlaceLabledControl("G", this, &EnemyG);

	EnemyB.SetFileId("colors_enemy_b");
	EnemyB.SetBoundaries(0, 255);
	EnemyB.SetValue(0);
	EnemyESP.PlaceLabledControl("B", this, &EnemyB);


	Hands.SetText("Hand");
	Hands.SetPosition(380, 15);
	Hands.SetSize(150, 125);
	RegisterControl(&Hands);

	HandR.SetFileId("colors_hand_r");
	HandR.SetBoundaries(0, 255);
	HandR.SetValue(0);
	Hands.PlaceLabledControl("R", this, &HandR);

	HandG.SetFileId("colors_hand_g");
	HandG.SetBoundaries(0, 255);
	HandG.SetValue(0);
	Hands.PlaceLabledControl("G", this, &HandG);

	HandB.SetFileId("colors_hand_b");
	HandB.SetBoundaries(0, 255);
	HandB.SetValue(0);
	Hands.PlaceLabledControl("B", this, &HandB);
};

void CGUITab::Setup()
{
	SetTitle("Colors");
};
void CLegitBotTab::Setup()
{
	SetTitle("Legit");
};
void CSkinTab::Setup()
{

};
void Menu::SetupMenu()
{
	Window.Setup();

	GUI.RegisterWindow(&Window);
	GUI.BindWindow(VK_INSERT, &Window);
}

void Menu::DoUIFrame()
{
	// General Processing
	if (Menu::Window.RageBotTab.AntiAimEnable.GetState())
	{
		showaimbot = true;
	}
	else
	{
		showaimbot = false;
	}
	// If the "all filter is selected tick all the others

	GUI.Update();
	GUI.Draw();

}
