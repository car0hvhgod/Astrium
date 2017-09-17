#pragma once

#include "GUI.h"
#include "Controls.h"



struct PlayerListItem_t
{
	bool Friendly;
	bool AimPrio;
	bool Callout;
};

DWORD GetPlayerListIndex(int EntId);
bool IsFriendly(int EntId);
bool IsAimPrio(int EntId);
bool IsCalloutTarget(int EntId);

extern std::map<DWORD, PlayerListItem_t> PlayerList;

class CRageBotTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CCheckBox AccuracyResolver;
	// Aimbot Settings
	CSilentGroupBox AimbotGroup;
	CGroupBox ConfigRage;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CSlider	  AimbotFov;
	CCheckBox AimbotSilentAim;
	CCheckBox AimbotPerfectSilentAim;
	CCheckBox AimbotAutoPistol;
	CCheckBox AimbotAutoRevolver;
	CCheckBox AimbotAimStep;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CKeyBind  AimbotStopKey;
	CGroupBox AimbotTitle;
	CSilentGroupBox AimbotGroup2;
	CSilentGroupBox AimbotGroup3;
	// Target Selection Settings
	CGroupBox TargetGroup;
	CComboBox TargetSelection;
	CCheckBox TargetFriendlyFire;
	CComboBox TargetHitbox;
	CCheckBox TargetHitscan;
	CCheckBox TargetMultipoint;
	CSlider   TargetPointscale;

	// Accuracy Settings
	CGroupBox AccuracyGroup;
	CCheckBox AccuracyRecoil;
	CCheckBox AccuracyAutoWall;
	CSlider	  AccuracyMinimumDamage;
	CCheckBox AccuracyAutoStop;
	CCheckBox AccuracyAutoCrouch;
	CCheckBox AccuracyAutoScope;
	CSlider   AccuracyHitchance;
	CComboBox AccuracyResolverPitch;
	CComboBox AccuracyResolverYaw;
	CCheckBox ResolverMain;
	CSlider   AccuracySmart;
	CSilentGroupBox epic3;
	CSilentGroupBox Epic;
	CSilentGroupBox Epic2;
	// Anti-Aim Settings
	CSilentGroupBox AntiAimGroup;

	CCheckBox AntiAimEnable;
	CComboBox AntiAimPitch;
	CSlider   AntiAimPitchSlider;
	CComboBox AntiAimYaw;
	CComboBox AntiAimRoll;
	CComboBox AntiAimFakeYaw;
	CSlider   RealAntiAimYawSlider;
	CComboBox FakeAntiAimYaw;
	CSlider   FakeAntiAimYawSlider;
	CCheckBox AccuracyPrediction;
	// CCheckBox AntiAimEdge;
	CSlider   AntiAimTicks;
	CSlider   AntiAimPercentage;

	// CSlider	  AntiAimOffset;
	CSlider   AntiAimSpinspeed;
	CCheckBox AntiAimKnife;
	CCheckBox AntiAimTarget;
	CGroupBox FakeLagGroup;
	CCheckBox FakeLagEnable;
	CSlider   FakeLagChoke;
	CSlider	  FakeLagSend;
	CComboBox FakeLag;
	CGroupBox HvHLabeled;
};

class CLegitBotTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Aimbot Settings
	CGroupBox AimbotGroup;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CCheckBox AimbotFriendlyFire;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CCheckBox AimbotAutoPistol;
	CSlider   AimbotInaccuracy;
	CKeyBind  AimbotDisableVis;

	// Main
	CGroupBox TriggerGroup;
	CCheckBox TriggerEnable;
	CCheckBox TriggerKeyPress;
	CKeyBind  TriggerKeyBind;
	CSlider   TriggerDelay;

	// Main
	CGroupBox WeaponMainGroup;
	CSlider   WeaponMainSpeed;
	CSlider   WeaponMainFoV;
	CCheckBox WeaponMainRecoil;
	CCheckBox WeaponMainPSilent;
	CSlider   WeaponMainInacc;
	CComboBox WeaponMainHitbox;

	// Pistol
	CGroupBox WeaponPistGroup;
	CSlider   WeaponPistSpeed;
	CSlider   WeaponPistFoV;
	CCheckBox WeaponPistRecoil;
	CCheckBox WeaponPistPSilent;
	CSlider   WeaponPistInacc;
	CComboBox WeaponPistHitbox;

	// Sniper
	CGroupBox WeaponSnipGroup;
	CSlider   WeaponSnipSpeed;
	CSlider   WeaponSnipFoV;
	CCheckBox WeaponSnipRecoil;
	CCheckBox WeaponSnipPSilent;
	CSlider   WeaponSnipInacc;
	CComboBox WeaponSnipSkitbox;
};

class CVisualTab : public CTab
{
public:
	void Setup();

	CGroupBox Visuals;
	CGroupBox Others;

	CGroupBox ConfigVisual;
	// Options Settings
	CSilentGroupBox OptionsGroup;
	CCheckBox OptionsBox;
	CCheckBox OptionsName;
	CCheckBox OptionHealthEnable;
	CCheckBox OptionsArmourEnable;
	CCheckBox OptionsWeapon;
	CCheckBox OptionsInfo;
	CCheckBox OptionsHelmet;
	CCheckBox OptionsKit;
	CCheckBox OptionsDefuse;
	CComboBox NightMode;
	CCheckBox DistanceMeme;
	CCheckBox IsScoped;
	CCheckBox GrenadeTracer;
	CComboBox SKINchanger;
	//CCheckBox OptionsGlow;
	CCheckBox OptionsChams;
	CCheckBox OptionsSkeleton;
	CCheckBox OptionsAimSpot;
	CCheckBox OptionsCompRank;
	CCheckBox Bones;
	// Skeleton ESP Colour
	CGroupBox ESPColorSkeleton;
	CSlider   RSkele;
	CSlider   GSkele;
	CSlider   BSkele;
	CSlider   ASkele;

	// Box ESP Colour
	CGroupBox ESPColorBox;
	CSlider   RBoxCT;
	CSlider   GBoxCT;
	CSlider   BBoxCT;
	CSlider   ABoxCT;
	CSlider   RBoxCTV;
	CSlider   GBoxCTV;
	CSlider   BBoxCTV;
	CSlider   ABoxCTV;


	// Other Settings
	CSilentGroupBox OtherGroup;
	CCheckBox OtherCrosshair;
	CComboBox OtherRecoilCrosshair;
	CCheckBox OtherHitlerCrosshair;

	CCheckBox OtherRadar;
	CCheckBox OtherNoVisualRecoil;
	CCheckBox OtherNoSky;
	CCheckBox OtherNoFlash;
	CCheckBox OtherNoSmoke;
	CCheckBox OtherAsusWalls;
	CComboBox OtherNoHands;
	CCheckBox OtherThirdperson;
	CKeyBind OtherThirdPersonKey;
	CSlider OtherThirdPersonRange;
	CSlider OtherViewmodelFOV;
	CSlider OtherFOV;
	CCheckBox CustomSky;
	CCheckBox OtherNoScope;
	CCheckBox BulletTrace;
	CSlider   TraceLength;
	CSlider OtherRadarXPosition;
	CSlider OtherRadarYPosition;
	CSilentGroupBox VisualsEffectsGroup;

};

class CMiscTab : public CTab
{
public:
	void Setup();

	CGroupBox FirstPart;
	CGroupBox SecondPart;

	CGroupBox ConfigMisc;
	// Knife Changer
	CGroupBox KnifeGroup;
	CCheckBox KnifeEnable;
	CComboBox KnifeModel;
	CComboBox KnifeSkin;
	CButton   KnifeApply;
	CCheckBox Circlestrafe;
	// Other Settings
	CSilentGroupBox OtherGroup;
	CCheckBox OtherSafeMode;
	CCheckBox OtherChatSpam;
	CCheckBox OtherTeamChat;
	CSlider	  OtherChatDelay;
	CKeyBind  OtherAirStuck;
	CKeyBind  OtherLagSwitch;
	CCheckBox OtherSpectators;
	CGroupBox ConfigGroup;
	CComboBox ConfigBox;
	CCheckBox NameSpam;
	//CCheckBox OtherAutoAccept;
	CCheckBox OtherWalkbot;
	CCheckBox OtherClantag;
	CCheckBox Logs;
	// Fake Lag Settings
	CSilentGroupBox FakeLagGroup;
	CCheckBox OtherHitmarker;
	CCheckBox OtherRoundSay;
	CCheckBox OtherRoundWin;
	CSlider OtherHitmarkerSize;
	//CCheckBox FakeLagWhileShooting;

	// Teleport shit cause we're cool
	CGroupBox TeleportGroup;
	CCheckBox TeleportEnable;
	CKeyBind  TeleportKey;
	CCheckBox OtherSlowMo;
	CSlider OtherSlowMoFactor;
	// Strafing
	CSilentGroupBox StrafingGroup;
	CCheckBox OtherAutoJump;
	CCheckBox OtherAutoStrafe;
	CSlider   OtherStrafeSpeed;
	CCheckBox OtherEdgeJump;
	CCheckBox Watermark;

	// Rank Reveal
	CGroupBox RankGroup;
	CCheckBox RankRevealer;
	CCheckBox OtherKillSpam;
	CCheckBox OtherKillSpamchat;

	CComboBox lstPlayers;
};

class CSkinTab : public CTab
{
public:
	void Setup();
	CGroupBox grpPList;

};

class CGUITab : public CTab
{
public:
	void Setup();

	// Main Menu
	CGroupBox ColorMain;
	CSlider   RMainMenuA;
	CSlider   GMainMenuA;
	CSlider   BMainMenuA;
	CSlider   AMainMenuA;
	CSlider   RMainMenuB;
	CSlider   GMainMenuB;
	CSlider   BMainMenuB;
	CSlider   AMainMenuB;

	// Menu Text
	CGroupBox ColorText;
	CSlider   RMenuText;
	CSlider   GMenuText;
	CSlider   BMenuText;

	// Inner Window
	CGroupBox ColorInner;
	CSlider   RInner;
	CSlider   GInner;
	CSlider   BInner;
	CSlider   AInner;

	// Tabs
	CGroupBox ColorTabs;
	CSlider   RTabs;
	CSlider   GTabs;
	CSlider   BTabs;

};


class CPlayersTab : public CTab
{
public:
	void Setup();
	CGroupBox EnemyESP;
	CGroupBox TeamESP;
	CGroupBox Hands;
	
	// Enemy Colors
	CSlider EnemyR;
	CSlider EnemyG;
	CSlider EnemyB;

	// Team Colors
	CSlider TeamR;
	CSlider TeamG;
	CSlider TeamB;

	// Hand Colors
	CSlider HandR;
	CSlider HandG;
	CSlider HandB;
	CSlider HandAlpha;
};
class silenthacks : public CWindow
{
public:
	void Setup();

	CRageBotTab RageBotTab;
	CLegitBotTab LegitBotTab;
	CVisualTab VisualsTab;
	CMiscTab MiscTab;
	CSkinTab SkinTab;
	CGUITab GUITab;
	CPlayersTab PlayersTab;
	CButton SaveButton;
	CButton LoadButton;
	CButton SaveButton2;
	CButton LoadButton2;
	CButton SaveButton3;
	CButton LoadButton3;
	CButton UnloadButton;

};

namespace Menu
{
	void SetupMenu();
	void DoUIFrame();
	extern silenthacks Window;
};