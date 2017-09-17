/*
Syn's AyyWare Framework 2015
*/

#pragma once

#include "Hacks.h"

class CEsp : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:

	// Other shit
	IClientEntity *BombCarrier;

	struct ESPBox
	{
		int x, y, w, h;
	};

	// Draw a player
	void DrawPlayer(IClientEntity* pEntity, player_info_t pinfo);

	// Get player info
	Color GetPlayerColor(IClientEntity* pEntity);
	bool GetBox(IClientEntity* pEntity, ESPBox &result);

	// Draw shit about player
	void SpecList();
	void DrawGlow(IClientEntity *pEntity, int r, int g, int b, int a);
	void DrawBox(ESPBox size, Color color);
	void DrawName(player_info_t pinfo, ESPBox size);
	void HealthBar(IClientEntity * pEntity, CEsp::ESPBox size);
	void HealthBar(IClientEntity * pEntity, int x, int y, int height);
	void DrawHealth(IClientEntity* pEntity, ESPBox size);
	void DrawArmour(IClientEntity * pEntity, CEsp::ESPBox size);
	void DrawInfo(IClientEntity* pEntity, ESPBox size);
	void DrawCross(IClientEntity* pEntity);

	void GrenadeTracer(IClientEntity * pEntity, CEsp::ESPBox size, player_info_t pinfo);
	void DrawSkeleton(IClientEntity* pEntity);

	void DrawChicken(IClientEntity* pEntity, ClientClass* cClass);
	void DrawDrop(IClientEntity* pEntity, ClientClass* cClass);
	void DrawBombPlanted(IClientEntity* pEntity, ClientClass* cClass);
	void DrawScoped(IClientEntity * pEntity, CEsp::ESPBox size);
	void DrawDistance(IClientEntity * pEntity, CEsp::ESPBox size);
	void DrawBomb(IClientEntity* pEntity, ClientClass* cClass);
	CEsp::ESPBox GetBOXX(IClientEntity * pEntity);
	void DrawArmor(IClientEntity * pEntity, CEsp::ESPBox size);
};

void DrawBoneTest(IClientEntity * pEntity);
