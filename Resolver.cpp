#include "Resolver.h"

int Globals::Shots = 0;
bool Globals::change;
CUserCmd* Globals::UserCmd;
int Globals::TargetID;
IClientEntity* Globals::Target;
int iSmart;
#include "RageBot.h"
template<class T, class U>
T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}
/*float RezolverLagFix()
{

	//pAyy fakelag fix bro
	float updaterate = Interfaces::CVar->FindVar("cl_updaterate")->fValue;
	ConVar* minupdate = Interfaces::CVar->FindVar("sv_minupdaterate");
	ConVar* maxupdate = Interfaces::CVar->FindVar("sv_maxupdaterate");

	if (minupdate && maxupdate)
		updaterate = maxupdate->fValue;

	float ratio = Interfaces::CVar->FindVar("cl_interp_ratio")->fValue;

	if (ratio == 0)
		ratio = 1.0f;

	float lerp = Interfaces::CVar->FindVar("cl_interp")->fValue;
	ConVar* cmin = Interfaces::CVar->FindVar("sv_client_min_interp_ratio");
	ConVar* cmax = Interfaces::CVar->FindVar("sv_client_max_interp_ratio");

	if (cmin && cmax && cmin->fValue != 1)
		ratio = clamp(ratio, cmin->fValue, cmax->fValue);


	return max(lerp, ratio / updaterate);
}*/


float simulationtime[128];


float YawDelta[64];
float reset[64];
float Delta[64];
float OldLowerBodyYaw[64];
float Resolved_angles[64];
void AntiAntiAim::Resolve()
{
	IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	CUserCmd* pCmd;

	for (int i = 0; i < Interfaces::Engine->GetMaxClients(); ++i)
	{


		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		if (!pEntity || pEntity->IsDormant() || !pEntity->IsAlive())
			continue;

		if (pEntity->GetTeamNum() == pLocal->GetTeamNum() || !pLocal->IsAlive())
			continue;

		Vector AimAngle;
		CalcAngleYawOnly(pEntity->GetEyePosition(), pLocal->GetAbsOrigin2(), AimAngle);
		NormalizeVector(AimAngle);

		Vector* eyeAngles = pEntity->GetEyeAnglesPointer();
		if (Menu::Window.RageBotTab.AccuracyResolver.GetState())
		{
			int num = Globals::Shots % 70;
			switch (num) {
			case 0:eyeAngles->y = AimAngle.y - 0; break;
			case 1:eyeAngles->y = AimAngle.y - 15; break;
			case 2:eyeAngles->y = AimAngle.y + 40; break;
			case 3:eyeAngles->y = AimAngle.y - 40; break;
			case 4:eyeAngles->y = AimAngle.y + 15; break;
			case 5:eyeAngles->y = AimAngle.y + 90; break;
			case 6:eyeAngles->y = AimAngle.y - 90; break;

			case 7:pEntity->GetEyeAnglesPointer()->y = pLocal->GetLowerBodyYaw();
			}

		}
		
			

		

		if (Menu::Window.RageBotTab.AccuracyResolver.GetState())
		{
			if (!Menu::Window.MiscTab.OtherSafeMode.GetState())
			{
				if (eyeAngles->x > 90.0f && eyeAngles->x < 270.f)
				{
					if (eyeAngles->x > 180.f)
						eyeAngles->x = -89.f;
					else
						eyeAngles->x = 89.0f;
				}



			}
		}
	}
}

