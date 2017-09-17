/*
Syn's AyyWare Framework 2015
*/

#pragma once

#include "Hacks.h"

Vector GetAutostrafeView();

class CMiscHacks : public CHack
{
public:
	void Init();
	void Draw();
	void meme();
	void Move(CUserCmd * pCmd, bool & bSendPacket);
private:
	void AutoJump(CUserCmd *pCmd);
	void AutoJumpSMAC(CUserCmd *pCmd);
	void EdgeJump(CUserCmd *pCmd);
	void OtherLBYIndicator(CUserCmd *pCmd);
	void Walkbot(CUserCmd *pCmd);
	void PerfectStrafe(CUserCmd *pCmd);
	void LegitStrafe(CUserCmd *pCmd);
	void RageStrafe(CUserCmd *pCmd);
	void ChatSpamInterwebz();
	void ChatSpamName();
	void ChatSpamDisperseName();
	void ChatSpamAdvertise();
	void ChatSpamRegular();
	void ChatSpamReports();
	void LBYIndicator();
	void ChatSpamCallout();
	//void ChatSpamAchievement();
	//void NameDispersion();
	//void ChatSpamAchievement();
	void Fakelag(CUserCmd *pCmd, bool &bSendPacket);

	



	

	



	void circlestrafer(CUserCmd * cmd, Vector & Originalview);

	void lby();

	void thatsameme();

	void scopememe();

	void SlowMotion(CUserCmd * pCmd, bool & bSendPacket);




	void LBYINDICATOR();

	//std::string GetNameChange();

	/*void ChatSpam();
	void Namechanger();

	std::string GetRegularSpam();
	std::string GetCustomSpam();
	std::string GetPlayerSpam();
	std::string GetSinglePlayerSpam();

	std::string GetNameChange();
	std::string GetNameCalloutChange();*/
};