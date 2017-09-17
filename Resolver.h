#pragma once

#include "Interfaces.h"
#include "Hacks.h"
#include "igameeventmanager.h"
#define TICK_INTERVAL			( Interfaces::Globals->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

namespace AntiAntiAim
{

	void Resolve();

};

namespace Globals
{
	extern CUserCmd* UserCmd;
	extern IClientEntity* Target;
	extern int Shots;
	extern bool change;
	extern int TargetID;
}
struct ResolveData
{
	ResolveData()
	{
		LastAnglesHit.Invalidate();
	}
	int ID;
	bool IsStatic = false;
	bool IsSpinning = false;
	int ShotsFiredAtTarget = 0;
	QAngle LastAnglesHit;
	QAngle AdjustedAngles = QAngle(0, 0, 0);
	QAngle LastAttemptedAngles = QAngle(0, 0, 0);
	QAngle LastOriginalAngles = QAngle(0, 0, 0);
	QAngle LastSetAngles = QAngle(0, 0, 0);
	int MissedShots = 0;
	int KilledByCount = 0;
	int LastTickHit = 0;
	float AdjustedPitch = 0;
	float AdjustedYaw = 0;
};

extern std::map<int, ResolveData> PlayerData;