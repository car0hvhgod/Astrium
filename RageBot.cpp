#include "RageBot.h"
#include "RenderManager.h"
#include "Autowall.h"
#include <iostream>
#include "UTIL Functions.h"
#include "AntiAntiAim.h"
#include <algorithm>
#include <stdlib.h>
#include "Vector.h"
int realyaw;
int fakeyaw;
#define TICK_INTERVAL			( Interfaces::Globals->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define clamp(v, a, b) max(min(v, b), a)

#define Yaw ( pCmd->viewangles.y )
#define Pitch (pCmd->viewangles.x )
void CRageBot::Init()
{
	IsAimStepping = false;
	IsLocked = false;
	TargetID = -1;
}
//real o.O
void CRageBot::Draw()
{

}

bool IsAbleToShoot(IClientEntity* pLocal)
{
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	if (!pLocal)
		return false;

	if (!pWeapon)
		return false;

	float flServerTime = pLocal->GetTickBase() * Interfaces::Globals->interval_per_tick;

	return (!(pWeapon->GetNextPrimaryAttack() > flServerTime));
}


float hitchance(IClientEntity* pLocal, CBaseCombatWeapon* pWeapon)
{
	//	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	float hitchance = 101;
	if (!pWeapon) return 0;
	if (Menu::Window.RageBotTab.AccuracyHitchance.GetValue() > 1)
	{
		float inaccuracy = pWeapon->GetInaccuracy();
		if (inaccuracy == 0) inaccuracy = 0.0000001;
		inaccuracy = 1 / inaccuracy;
		hitchance = inaccuracy;
	}
	return hitchance;
}

// (DWORD)g_pNetVars->GetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
// You need something like this
bool CanOpenFire() // Creds to untrusted guy
{
	IClientEntity* pLocalEntity = (IClientEntity*)Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (!pLocalEntity)
		return false;

	CBaseCombatWeapon* entwep = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocalEntity->GetActiveWeaponHandle());

	float flServerTime = (float)pLocalEntity->GetTickBase() * Interfaces::Globals->interval_per_tick;
	float flNextPrimaryAttack = entwep->GetNextPrimaryAttack();

	std::cout << flServerTime << " " << flNextPrimaryAttack << std::endl;

	return !(flNextPrimaryAttack > flServerTime);
}

void CRageBot::Move(CUserCmd *pCmd, bool &bSendPacket)
{
	IClientEntity* pLocalEntity = (IClientEntity*)Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (!pLocalEntity)
		return;



	// Anti Aim 
	if (Menu::Window.RageBotTab.AntiAimEnable.GetState())
	{
		static int ChokedPackets = -1;

		CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(hackManager.pLocal()->GetActiveWeaponHandle());
		if (!pWeapon)
			return;

		if (ChokedPackets < 1 && pLocalEntity->GetLifeState() == LIFE_ALIVE && pCmd->buttons & IN_ATTACK && CanOpenFire() && GameUtils::IsBallisticWeapon(pWeapon))
		{
			bSendPacket = false;
		}
		else
		{
			if (pLocalEntity->GetLifeState() == LIFE_ALIVE)
			{
				DoAntiAim(pCmd, bSendPacket);
			}
			ChokedPackets = -1;
		}
	}

	// Aimbot
	if (Menu::Window.RageBotTab.AimbotEnable.GetState())
		DoAimbot(pCmd, bSendPacket);

	// Recoil
	if (Menu::Window.RageBotTab.AccuracyRecoil.GetState())
		DoNoRecoil(pCmd);

	// Aimstep
	if (Menu::Window.RageBotTab.AimbotAimStep.GetState())
	{
		Vector AddAngs = pCmd->viewangles - LastAngle;
		if (AddAngs.Length2D() > 25.f)
		{
			Normalize(AddAngs, AddAngs);
			AddAngs *= 25;
			pCmd->viewangles = LastAngle + AddAngs;
			GameUtils::NormaliseViewAngle(pCmd->viewangles);
		}
	}

	LastAngle = pCmd->viewangles;
}

Vector BestPoint(IClientEntity *targetPlayer, Vector &final)
{
	IClientEntity* pLocal = hackManager.pLocal();

	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	filter.pSkip = targetPlayer;
	ray.Init(final + Vector(0, 0, 10), final);
	Interfaces::Trace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	final = tr.endpos;
	return final;
}

// Functionality
void CRageBot::DoAimbot(CUserCmd *pCmd, bool &bSendPacket) // Ragebot, Aimbot
{
	IClientEntity* pTarget = nullptr;
	IClientEntity* pLocal = hackManager.pLocal();
	Vector Start = pLocal->GetViewOffset() + pLocal->GetOrigin();
	IClientEntity *pEntity = nullptr;
	bool FindNewTarget = true;
	//IsLocked = false;

	CSWeaponInfo* weapInfo = ((CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle()))->GetCSWpnData();

	// Don't aimbot with the knife..
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	if (GameUtils::IsRevolver(pWeapon) && Menu::Window.RageBotTab.AimbotAutoRevolver.GetState())
	{
		static int delay = 0;
		delay++;

		if (delay <= 15)
			pCmd->buttons |= IN_ATTACK;
		else
			delay = 0;
	}

	/* if (GameUtils::IsRevolver(pWeapon) && Menu::Window.RageBotTab.AimbotAutoRevolver.GetState())
	{
	if (pCmd->buttons |= IN_ATTACK)
	AimAtPoint(pLocal, AimPoint, pCmd, bSendPacket);

	float flPostponeFireReady = pWeapon->GetFireReadyTime();
	if (flPostponeFireReady > 0 && flPostponeFireReady < Interfaces::Globals->curtime)
	{
	pCmd->buttons &= ~IN_ATTACK;
	}
	} */

	if (pWeapon)
	{
		if (pWeapon->GetAmmoInClip() == 0 || !GameUtils::IsBallisticWeapon(pWeapon))
		{
			//TargetID = 0;
			//pTarget = nullptr;
			//HitBox = -1;
			return;
		}
	}
	else
		return;

	// Make sure we have a good target
	if (IsLocked && TargetID >= 0 && HitBox >= 0)
	{
		pTarget = Interfaces::EntList->GetClientEntity(TargetID);
		if (pTarget  && TargetMeetsRequirements(pTarget))
		{
			HitBox = HitScan(pTarget);
			if (HitBox >= 0)
			{
				Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
				Vector View;
				Interfaces::Engine->GetViewAngles(View);
				float FoV = FovToPlayer(ViewOffset, View, pTarget, HitBox);
				if (FoV < Menu::Window.RageBotTab.AimbotFov.GetValue())
					FindNewTarget = false;
			}
		}
	}

	// Find a new target, apparently we need to
	if (FindNewTarget)
	{
		TargetID = 0;
		pTarget = nullptr;
		HitBox = -1;

		// Target selection type
		switch (Menu::Window.RageBotTab.TargetSelection.GetIndex())
		{
		case 0:
			TargetID = GetTargetCrosshair();
			break;
		case 1:
			TargetID = GetTargetDistance();
			break;
		case 2:
			TargetID = GetTargetHealth();
			break;
		}

		// Memes
		if (TargetID >= 0)
		{
			pTarget = Interfaces::EntList->GetClientEntity(TargetID);
		}
		else
		{
			pTarget = nullptr;
			HitBox = -1;
		}
	}

	Globals::Target = pTarget;
	Globals::TargetID = TargetID;

	// If we finally have a good target
	if (TargetID >= 0 && pTarget)
	{

		// Get the hitbox to shoot at
		HitBox = HitScan(pTarget);

		if (!CanOpenFire())
			return;

		// Key
		if (Menu::Window.RageBotTab.AimbotKeyPress.GetState())
		{
			int Key = Menu::Window.RageBotTab.AimbotKeyBind.GetKey();
			if (Key >= 0 && !GUI.GetKeyState(Key))
			{
				TargetID = -1;
				pTarget = nullptr;
				HitBox = -1;
				return;
			}
		}

		// Stop key
		int StopKey = Menu::Window.RageBotTab.AimbotStopKey.GetKey();
		if (StopKey >= 0 && GUI.GetKeyState(StopKey))
		{
			TargetID = -1;
			pTarget = nullptr;
			HitBox = -1;
			return;
		}

		Vector Point;
		Vector AimPoint = GetHitboxPosition(pTarget, HitBox) + Vector(0, 0, 0);


		Point = BestPoint(pTarget, AimPoint);
	
		if (GameUtils::IsScopedWeapon(pWeapon) && !pWeapon->IsScoped() && Menu::Window.RageBotTab.AccuracyAutoScope.GetState()) // Autoscope
		{
			pCmd->buttons |= IN_ATTACK2;
		}
		else
		{
			if ((Menu::Window.RageBotTab.AccuracyHitchance.GetValue() * 1.5 <= hitchance(pLocal, pWeapon)) || Menu::Window.RageBotTab.AccuracyHitchance.GetValue() == 0 || *pWeapon->m_AttributeManager()->m_Item()->ItemDefinitionIndex() == 64)
			{
				if (AimAtPoint(pLocal, Point, pCmd, bSendPacket))
				{
					if (Menu::Window.RageBotTab.AimbotAutoFire.GetState() && !(pCmd->buttons & IN_ATTACK))
					{
						pCmd->buttons |= IN_ATTACK;
					}
					else
					{
						return;
					}
				}
				else if (Menu::Window.RageBotTab.AimbotAutoFire.GetState() && !(pCmd->buttons & IN_ATTACK))
				{
					pCmd->buttons |= IN_ATTACK;
				}
			}
		}

		if (IsAbleToShoot(pLocal) && pCmd->buttons & IN_ATTACK)
		{
			Globals::Shots += 1;
		
		}
		// Stop and Crouch
		if (TargetID >= 0 && pTarget)
		{
			if (Menu::Window.RageBotTab.AccuracyAutoStop.GetState())
			{

				pCmd->buttons |= IN_DUCK;
			}
		}
	}

	// Auto Pistol
	if (GameUtils::IsPistol(pWeapon) && Menu::Window.RageBotTab.AimbotAutoPistol.GetState())
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			static bool WasFiring = false;
			WasFiring = !WasFiring;

			if (WasFiring)
			{
				pCmd->buttons |= IN_ATTACK2;
			}
		}
	}
}


float CRageBot::FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity* pEntity, int aHitBox)
{
	// Anything past 180 degrees is just going to wrap around
	CONST FLOAT MaxDegrees = 180.0f;

	// Get local angles
	Vector Angles = View;

	// Get local view / eye position
	Vector Origin = ViewOffSet;

	// Create and intiialize vectors for calculations below
	Vector Delta(0, 0, 0);
	//Vector Origin(0, 0, 0);
	Vector Forward(0, 0, 0);

	// Convert angles to normalized directional forward vector
	AngleVectors(Angles, &Forward);
	Vector AimPos = GetHitboxPosition(pEntity, aHitBox);
	// Get delta vector between our local eye position and passed vector
	VectorSubtract(AimPos, Origin, Delta);
	//Delta = AimPos - Origin;

	// Normalize our delta vector
	Normalize(Delta, Delta);

	// Get dot product between delta position and directional forward vectors
	FLOAT DotProduct = Forward.Dot(Delta);

	// Time to calculate the field of view
	return (acos(DotProduct) * (MaxDegrees / PI));
}
int CRageBot::GetTargetNoVisualCheck()
{
	// New Distance Aimbot
	int target = -1;
	int minDist = 8192;

	IClientEntity* pLocal = hackManager.pLocal();
	Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector View; Interfaces::Engine->GetViewAngles(View);

	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		if (AtTargetRequirements(pEntity))
		{

			Vector Difference = pLocal->GetOrigin() - pEntity->GetOrigin();
			int Distance = Difference.Length();
			float fov = FovToPlayer(ViewOffset, View, pEntity, 0);
			if (Distance < minDist && fov < Menu::Window.RageBotTab.AimbotFov.GetValue())
			{
				minDist = Distance;
				target = i;
			}
		}
	}
	return target;

}
int CRageBot::GetTargetCrosshair()
{
	// Target selection
	int target = -1;
	float minFoV = Menu::Window.RageBotTab.AimbotFov.GetValue();

	IClientEntity* pLocal = hackManager.pLocal();
	Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector View; Interfaces::Engine->GetViewAngles(View);

	for (int i = 0; i < Interfaces::EntList->GetMaxEntities(); i++) //GetHighestEntityIndex()
	{
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		if (TargetMeetsRequirements(pEntity))
		{
			int NewHitBox = HitScan(pEntity);
			if (NewHitBox >= 0)
			{
				float fov = FovToPlayer(ViewOffset, View, pEntity, 0);
				if (fov < minFoV)
				{
					minFoV = fov;
					target = i;
				}
			}
		}
	}

	return target;
}

int CRageBot::GetTargetDistance()
{
	// New Distance Aimbot
	int target = -1;
	int minDist = 8192;

	IClientEntity* pLocal = hackManager.pLocal();
	Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector View; Interfaces::Engine->GetViewAngles(View);

	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		if (TargetMeetsRequirements(pEntity))
		{
			int NewHitBox = HitScan(pEntity);
			if (NewHitBox >= 0)
			{
				Vector Difference = pLocal->GetOrigin() - pEntity->GetOrigin();
				int Distance = Difference.Length();
				float fov = FovToPlayer(ViewOffset, View, pEntity, 0);
				if (Distance < minDist && fov < Menu::Window.RageBotTab.AimbotFov.GetValue())
				{
					minDist = Distance;
					target = i;
				}
			}
		}
	}
	return target;

	/*
	// Target selection
	int target = -1;
	int minDist = 9999999999;

	IClientEntity* pLocal = hackManager.pLocal();
	Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector View; Interfaces::Engine->GetViewAngles(View);

	for (int i = 0; i < Interfaces::EntList->GetMaxEntities(); i++)
	{
	IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
	if (TargetMeetsRequirements(pEntity))
	{
	int NewHitBox = HitScan(pEntity);
	if (NewHitBox >= 0)
	{
	Vector Difference = pLocal->GetOrigin() - pEntity->GetOrigin();
	int Distance = Difference.Length();
	float fov = FovToPlayer(ViewOffset, View, pEntity, 0);
	if (Distance < minDist && fov < Menu::Window.RageBotTab.AimbotFov.GetValue())
	{
	minDist = Distance;
	target = i;
	}
	}
	}
	}

	return target;
	*/
}

bool CRageBot::TargetMeetsRequirements(IClientEntity* pEntity)
{
	// Is a valid player
	if (pEntity && pEntity->IsDormant() == false && pEntity->IsAlive() && pEntity->GetIndex() != hackManager.pLocal()->GetIndex())
	{
		// Entity Type checks
		ClientClass *pClientClass = pEntity->GetClientClass();
		player_info_t pinfo;
		if (pClientClass->m_ClassID == (int)CSGOClassID::CCSPlayer && Interfaces::Engine->GetPlayerInfo(pEntity->GetIndex(), &pinfo))
		{
			// Team Check
			if (pEntity->GetTeamNum() != hackManager.pLocal()->GetTeamNum() || Menu::Window.RageBotTab.TargetFriendlyFire.GetState())
			{
				// Spawn Check
				if (!pEntity->HasGunGameImmunity())
				{
					return true;
				}
			}
		}
	}

	// They must have failed a requirement
	return false;
}
bool CRageBot::AtTargetRequirements(IClientEntity* pEntity)
{
	// Is a valid player
	if (pEntity && pEntity->IsDormant() == false && pEntity->IsAlive() && pEntity->GetIndex() != hackManager.pLocal()->GetIndex())
	{
		// Entity Type checks
		ClientClass *pClientClass = pEntity->GetClientClass();
		player_info_t pinfo;
		if (/*pClientClass->m_ClassID == (int)CSGOClassID::CCSPlayer &&*/Interfaces::Engine->GetPlayerInfo(pEntity->GetIndex(), &pinfo))
		{

			if (pEntity->GetTeamNum() != hackManager.pLocal()->GetTeamNum())
			{

				return true;

			}
		}
	}

	// They must have failed a requirement
	return false;
}



int CRageBot::GetTargetHealth()
{
	int target = -1;
	int minHealth = 101;

	IClientEntity* pLocal = hackManager.pLocal();
	Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector View; Interfaces::Engine->GetViewAngles(View);

	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		if (TargetMeetsRequirements(pEntity))
		{
			int NewHitBox = HitScan(pEntity);
			if (NewHitBox >= 0)
			{
				int Health = pEntity->GetHealth();
				float fov = FovToPlayer(ViewOffset, View, pEntity, 0);
				if (Health < minHealth && fov < Menu::Window.RageBotTab.AimbotFov.GetValue())
				{
					minHealth = Health;
					target = i;
				}
			}
		}
	}
	return target;
	/*
	// Target selection
	int target = -1;
	int minHealth = 101;

	IClientEntity* pLocal = hackManager.pLocal();
	Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector View; Interfaces::Engine->GetViewAngles(View);

	for (int i = 0; i < Interfaces::EntList->GetMaxEntities(); i++)
	{
	IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
	if (TargetMeetsRequirements(pEntity))
	{
	int NewHitBox = HitScan(pEntity);
	if (NewHitBox >= 0)
	{
	int Health = pEntity->GetHealth();
	float fov = FovToPlayer(ViewOffset, View, pEntity, 0);
	if (Health < minHealth && fov < Menu::Window.RageBotTab.AimbotFov.GetValue())
	{
	minHealth = Health;
	target = i;
	}
	}
	}
	}

	return target;
	*/
}

int CRageBot::HitScan(IClientEntity* pEntity)
{
	std::vector<int> HitBoxesToScan;
	bool AWall = true;

	// Get the hitboxes to scan
	bool HitScanMode = Menu::Window.RageBotTab.TargetHitscan.GetState();
	if (HitScanMode)
	{
		HitBoxesToScan.push_back((int)Menu::Window.RageBotTab.TargetHitbox.GetIndex());
		HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
		HitBoxesToScan.push_back((int)CSGOHitboxID::NeckLower);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
		HitBoxesToScan.push_back((int)CSGOHitboxID::UpperChest);
		HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LowerChest);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftUpperArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightUpperArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftThigh);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightThigh);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftHand);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightHand);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftShin);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightShin);
		HitBoxesToScan.push_back((int)CSGOHitboxID::LeftLowerArm);
		HitBoxesToScan.push_back((int)CSGOHitboxID::RightLowerArm);
	}
	else
	{

		switch (Menu::Window.RageBotTab.TargetHitbox.GetIndex())
		{
		case 0:
			HitBoxesToScan.push_back((int)CSGOHitboxID::Head);
			break;
		case 1:
			HitBoxesToScan.push_back((int)CSGOHitboxID::Neck);
			break;
		case 2:
			HitBoxesToScan.push_back((int)CSGOHitboxID::Chest);
			break;
		case 3:
			HitBoxesToScan.push_back((int)CSGOHitboxID::Stomach);
			break;
		case 4:
			HitBoxesToScan.push_back((int)CSGOHitboxID::Pelvis);
			break;
		case 5:
			HitBoxesToScan.push_back((int)CSGOHitboxID::LeftFoot);
			break;
		case 6:
			HitBoxesToScan.push_back((int)CSGOHitboxID::RightFoot);
			break;
		}
	}

	for (auto HitBoxID : HitBoxesToScan)
	{
		if (AWall)
		{
			Vector Point = GetHitboxPosition(pEntity, HitBoxID);
			float Damage = 0.f;
			if (CanHit(Point, &Damage))
			{
				if (Damage >= Menu::Window.RageBotTab.AccuracyMinimumDamage.GetValue())
				{
					return HitBoxID;
				}
			}
		}
		else
		{
			if (GameUtils::IsVisible(hackManager.pLocal(), pEntity, HitBoxID))
				return HitBoxID;
		}
	}
	return -1;
}

void CRageBot::DoNoRecoil(CUserCmd *pCmd)
{
	// Ghetto rcs shit, implement properly later
	IClientEntity* pLocal = hackManager.pLocal();
	if (pLocal)
	{
		Vector AimPunch = pLocal->localPlayerExclusive()->GetAimPunchAngle();
		if (AimPunch.Length2D() > 0 && AimPunch.Length2D() < 150)
		{
			pCmd->viewangles -= AimPunch * 2;
			GameUtils::NormaliseViewAngle(pCmd->viewangles);
		}
	}
}

bool CRageBot::AimAtPoint(IClientEntity* pLocal, Vector point, CUserCmd *pCmd, bool &bSendPacket)
{
	bool ReturnValue = false;
	if (point.Length() == 0) return ReturnValue;
	Vector angles;
	Vector src = pLocal->GetOrigin() + pLocal->GetViewOffset();

	if (Menu::Window.RageBotTab.TargetPointscale.GetValue() == 0.50)
	{
		point = point;
	}
	if (Menu::Window.RageBotTab.TargetPointscale.GetValue() != 0.50)
	{
		if (Menu::Window.RageBotTab.TargetPointscale.GetValue() > 0.50)
		{
			float PointScale = Menu::Window.RageBotTab.TargetPointscale.GetValue();
			float maxpsx = PointScale * 4;
			point.z += maxpsx - 0.50;

		}
		if (Menu::Window.RageBotTab.TargetPointscale.GetValue() < 0.50)
		{
			float PointScale = Menu::Window.RageBotTab.TargetPointscale.GetValue();
			float maxpsx = PointScale * 4;
			point.z -= 0.50 - maxpsx;

		}
	}

	CalcAngle(src, point, angles);
	GameUtils::NormaliseViewAngle(angles);
	IsLocked = true;

	// Aim Step Calcs
	Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
	if (!IsAimStepping)
		LastAimstepAngle = LastAngle; // Don't just use the viewangs because you need to consider aa

	float fovLeft = FovToPlayer(ViewOffset, LastAimstepAngle, Interfaces::EntList->GetClientEntity(TargetID), 0);

	if (fovLeft > 25.0f && Menu::Window.RageBotTab.AimbotAimStep.GetState())
	{
		Vector AddAngs = angles - LastAimstepAngle;
		Normalize(AddAngs, AddAngs);
		AddAngs *= 25;
		LastAimstepAngle += AddAngs;
		GameUtils::NormaliseViewAngle(LastAimstepAngle);
		angles = LastAimstepAngle;
	}
	else
	{
		ReturnValue = true;
	}
	if (Menu::Window.RageBotTab.AimbotSilentAim.GetState())
	{
		// Client Side
		pCmd->viewangles = angles;
	}
	// Silent Aim
	/*if (Menu::Window.RageBotTab.AimbotSilentAim.GetState() && !Menu::Window.RageBotTab.AimbotPerfectSilentAim.GetState())
	{
		if (Menu::Window.RageBotTab.AimbotSilentAim.GetState())
		{
			static int ChokedPackets = -1;
			ChokedPackets++;

			if (ChokedPackets < 6)
			{
				bSendPacket = false;
				pCmd->viewangles = angles;
			}
			else
			{
				bSendPacket = true; //zeigt alte sicht an
				pCmd->viewangles = angles;
				ChokedPackets = -1;
				ReturnValue = false;
			}

			//pCmd->viewangles.z = 0;

		}
		return ReturnValue;
	}

	*/

	// Normal Aim
	if (!Menu::Window.RageBotTab.AimbotSilentAim.GetState() && !Menu::Window.RageBotTab.AimbotPerfectSilentAim.GetState())
	{
		Interfaces::Engine->SetViewAngles(angles);
	}

	// pSilent Aim 
	Vector Oldview = pCmd->viewangles;

	if (Menu::Window.RageBotTab.AimbotPerfectSilentAim.GetState())
	{
		static int ChokedPackets = -1;
		ChokedPackets++;

		if (ChokedPackets < 6)
		{
			bSendPacket = false;
			pCmd->viewangles = angles;
		}
		else
		{
			bSendPacket = true;
			pCmd->viewangles = Oldview;
			ChokedPackets = -1;
			ReturnValue = false;
		}
	}
	return ReturnValue;
}

namespace AntiAims
{
	/*Pitch Anti Aims*/

	void Down2(CUserCmd *pCmd, bool &bSendPacket)
	{
		static int ChokedPackets = -1;
		ChokedPackets++;
		if (ChokedPackets < 1)
		{
			bSendPacket = false;
			pCmd->viewangles.x = 89;
		}
		else
		{
			bSendPacket = true;
			pCmd->viewangles.x = 51;
			ChokedPackets = -1;
		}
	}

	void JitterPitch(CUserCmd *pCmd)
	{
		static bool flip = true;
		if (flip)
		{
			pCmd->viewangles.x = -89;
			flip = !flip;
		}
		else
		{
			pCmd->viewangles.x = 89;
			flip = !flip;
		}
	}

	void spinreverse(CUserCmd *pCmd)
	{
		static bool flip = true;
		if (flip)
		{
			int random = rand() % 100;
			int random2 = rand() % 1000;

			static bool dir;
			static float current_y = pCmd->viewangles.y;

			if (random == 1) dir = !dir;

			if (dir)
				current_y += 5.0f;
			else
				current_y -= 5.0f;

			pCmd->viewangles.y = current_y;

			if (random == random2)
				pCmd->viewangles.y += random;
		}
		else
		{
			int random = rand() % 100;
			int random2 = rand() % 1000;

			static bool dir;
			static float current_y = pCmd->viewangles.y;

			if (random == 1) dir = !dir;

			if (dir)
				current_y += 5.0f;
			else
				current_y -= 5.0f;

			pCmd->viewangles.y = current_y;

			if (random == random2)
				pCmd->viewangles.y -= random;
		}
	}
	void Arizona1(CUserCmd *pCmd, bool &bSendPacket) //Jitter Movement mit static bool Fast :)
	{
		static bool Fast = false;
		if (Fast)
		{
			bSendPacket = false; //true angle
			pCmd->viewangles.y = pCmd->viewangles.y - 134.0;
		}
		else
		{
			bSendPacket = true; //fake angle
			pCmd->viewangles.y = pCmd->viewangles.y - 226.0;
		}
		Fast = !Fast;
	}

	void FakeSpinLeft(CUserCmd* pCmd, bool &bSendPacket)
	{
		static bool fake;
		if (fake)
		{
			bSendPacket = true;
			Vector SpinSoSlow;
			SpinSoSlow.y = (Interfaces::Globals->curtime * 800.0);
			GameUtils::NormaliseViewAngle(SpinSoSlow);
			pCmd->viewangles.y = SpinSoSlow.y;
			fake = false;
		}
		else
		{
			bSendPacket = false;
			pCmd->viewangles.y += 90;
			fake = true;
		}
	}
	void LBYJ(CUserCmd* cmd, bool& packet)
	{
		static bool ySwitch;
		static bool jbool;
		static bool jboolt;
		ySwitch = !ySwitch;
		jbool = !jbool;
		jboolt = !jbool;
		if (ySwitch)
		{
			if (jbool)
			{
				if (jboolt)
				{
					cmd->viewangles.y = hackManager.pLocal()->GetLowerBodyYaw() - 90.f;
					packet = false;
				}
				else
				{
					cmd->viewangles.y = hackManager.pLocal()->GetLowerBodyYaw() + 90.f;
					packet = false;
				}
			}
			else
			{
				if (jboolt)
				{
					cmd->viewangles.y = hackManager.pLocal()->GetLowerBodyYaw() - 125.f;
					packet = false;
				}
				else
				{
					cmd->viewangles.y = hackManager.pLocal()->GetLowerBodyYaw() + 125.f;
					packet = false;
				}
			}
		}
		else
		{
			cmd->viewangles.y = hackManager.pLocal()->GetLowerBodyYaw();
			packet = true;
		}
	}
	void CSpin(CUserCmd *pCmd, bool &bSendPacket)
	{
		static bool f_flip = true;
		f_flip = !f_flip;

		if (f_flip)
		{
			float CalculatedCurTime = (Interfaces::Globals->curtime * 350.0);
			pCmd->viewangles.y += CalculatedCurTime;
		}
		else if (!f_flip)
		{
			float CalculatedCurTime = (Interfaces::Globals->curtime * 350.0);
			pCmd->viewangles.y -= CalculatedCurTime;
		}

	}

	void halfSpin(CUserCmd *pCmd, bool &bSendPacket)
	{
		static bool f_flip = true;
		f_flip = !f_flip;


		if (f_flip)
		{
			bSendPacket = true;
			pCmd->viewangles.y = 0;
		}
		else if (!f_flip)
		{
			bSendPacket = true;
			pCmd->viewangles.y = -180;
		}
		else
			bSendPacket = false;
	}

	void FakeForward(CUserCmd *pCmd, bool &bSendPacket)
	{
		static int jitterangle = 0;


		static int iChoked = -1;
		iChoked++;
		if (iChoked < 1)
		{
			bSendPacket = true;
			if (jitterangle <= 1)
			{
				pCmd->viewangles.y += 0;
				jitterangle += 1;
			}
			else if (jitterangle > 1 && jitterangle <= 3)
			{
				pCmd->viewangles.y -= 0;
				jitterangle += 1;
			}
			else
			{
				jitterangle = 0;
			}
		}
	}

	void TickOverRide(CUserCmd *pCmd, bool &bSendPacket)
	{
		bool jitter = false;
		int Add = 0;

		if (bSendPacket)
		{
			if (jitter)
				Add = -90;
			else
				Add = 90;
		}
		else
		{
			float flRandom = rand() % 5 + 1.f;
			switch (pCmd->tick_count % 4)
			{
			case 0:
				Add = -170.f - flRandom;
				break;
			case 3:
			case 1:
				Add = 180.f;
				break;
			case 2:
				Add = 170.f + flRandom;
				break;
			}
		}
	}


	void fakespin(CUserCmd *pCmd, bool &bSendPacket)
	{
		IClientEntity* pLocal = hackManager.pLocal();
		float server_time = pLocal->GetTickBase() * Interfaces::Globals->interval_per_tick;

		if (bSendPacket)
		{
			pCmd->viewangles.y += (float)(fmod(server_time / 0.80f * 360.0f, 360.0f));
		}
		else
		{
			pCmd->viewangles.y -= (float)(fmod(server_time / 0.80f * 360.0f, 360.0f));
		}
	}

	void FakeTwoStep(CUserCmd* pCmd, bool& bSendPacket)
	{

		static bool bFlipYaw;
		float flInterval = Interfaces::Globals->interval_per_tick;
		float flTickcount = pCmd->tick_count;
		float flTime = flInterval * flTickcount;
		if (std::fmod(flTime, 1) == 0.f)
			bFlipYaw = !bFlipYaw;

		if (bSendPacket)
			pCmd->viewangles.y += bFlipYaw ? 90.f : -90.f;
		else
			pCmd->viewangles.y -= hackManager.pLocal()->GetLowerBodyYaw() + bFlipYaw ? -90.f : 90.f;
	}




	void BackJitter(CUserCmd *pCmd)
	{
		int random = rand() % 100;

		// Small chance of starting fowards
		if (random < 98)
			// Look backwards
			pCmd->viewangles.y -= 180;

		// Some gitter
		if (random < 15)
		{
			float change = -70 + (rand() % (int)(140 + 1));
			pCmd->viewangles.y += change;
		}
		if (random == 69)
		{
			float change = -90 + (rand() % (int)(180 + 1));
			pCmd->viewangles.y += change;
		}
	}

	void FakeSideways(CUserCmd *pCmd, bool &bSendPacket)
	{

		static int ChokedPackets = -1;
		ChokedPackets++;
		if (ChokedPackets < Menu::Window.RageBotTab.FakeLagChoke.GetValue())
		{
			bSendPacket = false;
			pCmd->viewangles.y += 90;
		}
		else
		{
			bSendPacket = true;
			pCmd->viewangles.y -= 180;
			ChokedPackets = -1;
		}
	}

	void Jitter(CUserCmd *pCmd)
	{
		static int jitterangle = 0;

		if (jitterangle <= 1)
		{
			pCmd->viewangles.y += 90;
		}
		else if (jitterangle > 1 && jitterangle <= 3)
		{
			pCmd->viewangles.y -= 90;
		}

		int re = rand() % 4 + 1;


		if (jitterangle <= 1)
		{
			if (re == 4)
				pCmd->viewangles.y += 180;
			jitterangle += 1;
		}
		else if (jitterangle > 1 && jitterangle <= 3)
		{
			if (re == 4)
				pCmd->viewangles.y -= 180;
			jitterangle += 1;
		}
		else
		{
			jitterangle = 0;
		}
	}

	void FakeStatic(CUserCmd *pCmd, bool &bSendPacket)
	{
		static int ChokedPackets = -1;
		ChokedPackets++;
		if (ChokedPackets < Menu::Window.RageBotTab.FakeLagChoke.GetValue())
		{
			bSendPacket = false;
			static int y2 = -179;
			int spinBotSpeedFast = 360.0f / 1.618033988749895f;

			y2 += spinBotSpeedFast;

			if (y2 >= 179)
				y2 = -179;

			pCmd->viewangles.y = y2;
		}
		else
		{
			bSendPacket = true;
			pCmd->viewangles.y -= 180;
			ChokedPackets = -1;
		}
	}

	void TJitter(CUserCmd *pCmd)
	{
		static bool Turbo = true;
		if (Turbo)
		{
			pCmd->viewangles.y -= 90;
			Turbo = !Turbo;
		}
		else
		{
			pCmd->viewangles.y += 90;
			Turbo = !Turbo;
		}
	}


	void TFake(CUserCmd *pCmd, bool &bSendPacket)
	{

		static int ChokedPackets = -1;
		ChokedPackets++;
		if (ChokedPackets < Menu::Window.RageBotTab.FakeLagChoke.GetValue())
		{
			bSendPacket = false;
			pCmd->viewangles.y = -90;
		}
		else
		{
			bSendPacket = true;
			pCmd->viewangles.y = 90;
			ChokedPackets = -1;
		}
	}

	void FakeJitter(CUserCmd* pCmd, bool &bSendPacket)
	{
		static int jitterangle = 0;

		if (jitterangle <= 1)
		{
			pCmd->viewangles.y += 135;
		}
		else if (jitterangle > 1 && jitterangle <= 3)
		{
			pCmd->viewangles.y += 225;
		}

		static int iChoked = -1;
		iChoked++;
		if (iChoked < Menu::Window.RageBotTab.FakeLagChoke.GetValue())
		{
			bSendPacket = false;
			if (jitterangle <= 1)
			{
				pCmd->viewangles.y += 45;
				jitterangle += 1;
			}
			else if (jitterangle > 1 && jitterangle <= 3)
			{
				pCmd->viewangles.y -= 45;
				jitterangle += 1;
			}
			else
			{
				jitterangle = 0;
			}
		}
		else
		{
			bSendPacket = true;
			iChoked = -1;
		}
	}

	void opaf(CUserCmd* pCmd, bool &bSendPacket)
	{
		static int jitterangle = 0;

		if (jitterangle <= 1)
		{
			pCmd->viewangles.y += 90;
		}
		else if (jitterangle > 1 && jitterangle <= 2)
		{
			pCmd->viewangles.y += -90;
		}


		if (jitterangle <= 1)
		{
			bSendPacket = false;
			if (jitterangle <= 1)
			{
				pCmd->viewangles.y += 180;
				jitterangle += 1;
			}
			else if (jitterangle > 1 && jitterangle <= 2)
			{
				pCmd->viewangles.y -= -179;
				jitterangle += 1;
			}
			else
			{
				jitterangle = 0;
			}
		}
		else
		{
			bSendPacket = true;

		}
	}
	void FakeBackwards(CUserCmd *pCmd, bool &bSendPacket)
	{
			bSendPacket = true;
			pCmd->viewangles.y += 180.f; //fake angle
	}
	void Mixed(CUserCmd *pCmd) //Test
	{
		static float pDance = 0.0f;

		pDance += 45.0f;
		if (pDance > 100)
			pDance = 0.0f;
		else if (pDance > 75.f)
			pCmd->viewangles.x = -11.295f;
		else if (pDance < 45.f)
			pCmd->viewangles.x = 26.3491651f;
		else if (pDance < 65)
			pCmd->viewangles.x = -9.91545f;
		else if (pDance < 75.f)
			pCmd->viewangles.x = 67.945324f;
		else if (pDance < 89.f)
			pCmd->viewangles.x = -72.62294519f;
		else if (pDance < 85.f)
			pCmd->viewangles.x = 35.19245635f;
	}
	/*Yaw AntiAims*/

	void MoveFix(CUserCmd *cmd, Vector &realvec)
	{
		Vector vMove(cmd->forwardmove, cmd->sidemove, cmd->upmove);
		float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
		Vector vMove2;
		VectorAngles(vMove, vMove2);

		flYaw = DEG2RAD(cmd->viewangles.y - realvec.y + vMove2.y);
		cmd->forwardmove = cos(flYaw) * flSpeed;
		cmd->sidemove = sin(flYaw) * flSpeed;

		if (cmd->viewangles.x < -90.f || cmd->viewangles.x > 90.f)
			cmd->forwardmove = -cmd->forwardmove;
	}


	void FakeRotation(CUserCmd* pCmd, bool& bSendPacket) {

		IClientEntity* pLocal = hackManager.pLocal();
		float server_time = pLocal->GetTickBase() * Interfaces::Globals->interval_per_tick;

		if (bSendPacket)
		{
			pCmd->viewangles.y += Menu::Window.RageBotTab.FakeAntiAimYawSlider.GetValue();
		}
		else
		{
			pCmd->viewangles.y += Menu::Window.RageBotTab.RealAntiAimYawSlider.GetValue();;
		}
	}
	void AASystem(CUserCmd* pCmd, bool& bSendPacket)
	{

		IClientEntity* pLocal = hackManager.pLocal();

		if (bSendPacket)
		{
			pCmd->viewangles.y += Menu::Window.RageBotTab.FakeAntiAimYawSlider.GetValue();
		}
		else
		{
			pCmd->viewangles.y += Menu::Window.RageBotTab.RealAntiAimYawSlider.GetValue();;
		}
	}

	void FastSpin(CUserCmd *pCmd, bool &bSendPacket)
	{
		static int y2 = -179;
		int spinBotSpeedFast = 100;
		bSendPacket = true;
		y2 += spinBotSpeedFast;

		if (y2 >= 179)
			y2 = -179;

		pCmd->viewangles.y = y2;
	}

	void kiduaJitter(CUserCmd *pCmd, bool &bSendPacket)
	{
		static int jitterangle;
		static int iChoked = -1;
		iChoked++;
		if (iChoked < Menu::Window.RageBotTab.FakeLagChoke.GetValue())
		{
			bSendPacket = true;
			if (jitterangle <= 1)
			{
				pCmd->viewangles.y += 90;
				jitterangle += 1;
			}
			else if (jitterangle > 1 && jitterangle <= 3)
			{
				pCmd->viewangles.y += 90;
				jitterangle += 1;
			}
			else
			{
				jitterangle = -90;
			}

		}
	}
}



void AtTarget(IClientEntity *Target, CUserCmd *pCmd) {
	if (!Target)
		return;

	if ((Target->GetTeamNum() == hackManager.pLocal()->GetTeamNum()) || Target->IsDormant() || !Target->IsAlive() || Target->GetHealth() <= 0)
		return;

	Vector TargetPosition = Target->GetEyePosition();
	CalcAngle(hackManager.pLocal()->GetEyePosition(), TargetPosition, pCmd->viewangles);
}
bool anyAlive()
{
	for (INT i = 0; i <= Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		IClientEntity* pEntity = (IClientEntity*)Interfaces::EntList->GetClientEntity(i);
		if (pEntity == NULL)
			continue;
		if (!pEntity->IsAlive())
			continue;
		if (pEntity == hackManager.pLocal())
			continue;
		if (pEntity->IsDormant())
			continue;
		if (pEntity->GetTeamNum() == hackManager.pLocal()->GetTeamNum())
			continue;
		player_info_t info;
		if (!(Interfaces::Engine->GetPlayerInfo(pEntity->GetIndex(), &info)))
			continue;
		return true;
	}
	return false;
}

// AntiAim
void CRageBot::DoAntiAim(CUserCmd *pCmd, bool &bSendPacket) // pCmd->viewangles.y = 0xFFFFF INT_MAX or idk
{
	IClientEntity* pLocal = hackManager.pLocal();

	if (pLocal->GetMoveType() == MOVETYPE_LADDER)
		return;

	bool alive = anyAlive();
	// If the aimbot is doing something don't do anything
	if ((IsAimStepping) && !Menu::Window.RageBotTab.AimbotPerfectSilentAim.GetState())
		return;
	if (!Menu::Window.MiscTab.OtherSafeMode.GetState())
	{
		if (!alive)
			return;
	}
	// Weapon shit
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(hackManager.pLocal()->GetActiveWeaponHandle());
	if (pWeapon)
	{
		CSWeaponInfo* pWeaponInfo = pWeapon->GetCSWpnData();
		// Knives or grenades
		if (!GameUtils::IsBallisticWeapon(pWeapon))
		{
			if (Menu::Window.RageBotTab.AntiAimKnife.GetState())
			{
				if (!CanOpenFire() || pCmd->buttons & IN_ATTACK2)
					return;
			}
			else
			{
				return;
			}
		}
	}
	if (Menu::Window.RageBotTab.AntiAimTarget.GetState()) {
		TargetID = GetTargetNoVisualCheck();
		IClientEntity *Target = Interfaces::EntList->GetClientEntity(TargetID);


		AtTarget(Target, pCmd);
	}

	CTraceFilterNoPlayer tfNoPlayers;

	IClientEntity *Target = Interfaces::EntList->GetClientEntity(this->TargetID);


	// Don't do antiaim
	// if (DoExit) return;

	// Anti-Aim Pitch
	RECT scrn = Render::GetViewport();
	int yaw = pCmd->viewangles.y;
	switch (Menu::Window.RageBotTab.AntiAimPitch.GetIndex()) // Magic pitch is 69.69?
	{
	case 0:
		// No Pitch AA
		break;
	case 1:
		pCmd->viewangles.x = 89.f;
		break;
	case 2:
		pCmd->viewangles.x = -181.f;
		break;
	case 3:
		pCmd->viewangles.x = 181.f;
		break;
	case 4:
		AntiAims::Mixed(pCmd);
		break;
	}
	/*
	switch (Menu::Window.RageBotTab.AntiAimYaw.GetIndex())
	{
	case 0:
		// No Yaw AA
		break;
	case 1:
		// Fake Inverse
		pCmd->viewangles.y += 180;
		break;
	case 2:
		// Fake Sideways
		pCmd->viewangles.y += 90;
		break;
	case 3:
		// Fake Static
		pCmd->viewangles.y -= 90;
		break;
	case 4:
		pCmd->viewangles.y -= hackManager.pLocal()->GetLowerBodyYaw();
		break;
	case 5:
		AntiAims::LBYJ(pCmd, bSendPacket);
		break;
	case 6:
		AntiAims::FakeTwoStep(pCmd, bSendPacket);
		break;
	}*/

	int real = Menu::Window.RageBotTab.RealAntiAimYawSlider.GetValue();
	int fake = Menu::Window.RageBotTab.FakeAntiAimYawSlider.GetValue();

	//pCmd->viewangles.y += bSendPacket ? fake : real;
	static int ChokedPackets = -1;
	ChokedPackets++;
	if (ChokedPackets < 1)
	{
		bSendPacket = false;
		pCmd->viewangles.y += Menu::Window.RageBotTab.RealAntiAimYawSlider.GetValue();
	}
	else
	{
		bSendPacket = true;
		pCmd->viewangles.y -= Menu::Window.RageBotTab.FakeAntiAimYawSlider.GetValue();
		ChokedPackets = -1;
	}

	
}