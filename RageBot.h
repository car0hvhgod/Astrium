#pragma once

#include "Hacks.h"

#define M_PI 3.14159265358979323846
#define M_PI_F 3.14159265358979323846

class CRageBot : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
	void ClampAngles(Vector& vecAngles);
	void NormalizeVector(Vector& vec);

private:
	// Targetting
	int GetTargetCrosshair();
	int GetTargetDistance();
	int GetTargetNoVisualCheck();
	int GetTargetHealth();
	bool TargetMeetsRequirements(IClientEntity* pEntity);
	float FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity* pEntity, int HitBox);
	int HitScan(IClientEntity* pEntity);
	bool AimAtPoint(IClientEntity* pLocal, Vector point, CUserCmd *pCmd, bool &bSendPacket);
	void aimAtPlayer(CUserCmd * pCmd);
	void DoAntiAim(CUserCmd * pCmd, bool & bSendPacket);

	// Functionality
	void DoAimbot(CUserCmd *pCmd, bool &bSendPacket);
	bool AtTargetRequirements(IClientEntity * pEntity);
	void DoNoRecoil(CUserCmd *pCmd);
	void PositionAdjustment(CUserCmd* pCmd);

	// AntiAim
	//bool EdgeAntiAim(IClientEntity* pLocalBaseEntity, CUserCmd* cmd, float flWall, float flCornor);
	//bool bEdge;

	// AimStep
	bool IsAimStepping;
	Vector LastAimstepAngle;
	Vector LastAngle;

	// Aimbot
	bool IsLocked;
	int TargetID;
	int HitBox;
	Vector AimPoint;
};

bool anyAlive();

void AtTarget(IClientEntity * Target, CUserCmd * pCmd);
