/*
Syn's AyyWare Framework 2015
*/

#define _CRT_SECURE_NO_WARNINGS

#include "MiscHacks.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "RageBot.h"
#include <time.h>

template<class T, class U>
inline T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}

inline float bitsToFloat(unsigned long i)
{
	return *reinterpret_cast<float*>(&i);
}

inline float FloatNegate(float f)
{
	return bitsToFloat(FloatBits(f) ^ 0x80000000);
}

Vector AutoStrafeView;

void CMiscHacks::Init()
{
	// Any init
}

void CMiscHacks::Draw()
{

	lby();
	if (Menu::Window.MiscTab.OtherClantag.GetState())
	{
		meme();
	}
//	
	thatsameme();
	scopememe();
	// Any drawing	
	// Spams
	if (Menu::Window.MiscTab.OtherChatSpam.GetState())
		ChatSpamAdvertise();

}
void SetClanTag(const char* tag, const char* name)
{
	static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(((DWORD)Utilities::Memory::FindPattern("engine.dll", (PBYTE)"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15\x00\x00\x00\x00\x6A\x24\x8B\xC8\x8B\x30", "xxxxxxxxx????xxxxxx")));
	pSetClanTag(tag, name);
}
void CMiscHacks::meme()
{
	static int counter = 0;
	static int motion = 0;
	int ServerTime = (float)Interfaces::Globals->interval_per_tick * hackManager.pLocal()->GetTickBase() * 3;

	if (counter % 48 == 0)
		motion++;
	int value = ServerTime % 30;
	switch (value) {
	case 0:SetClanTag(">", "     "); break;
	case 1:SetClanTag(">s", "     "); break;
	case 2:SetClanTag(">si", "     "); break;
	case 3:SetClanTag(">sil", "     "); break;
	case 4:SetClanTag(">sile", "     "); break;
	case 5:SetClanTag(">silen", "     "); break;
	case 6:SetClanTag(">silent", "     "); break;
	case 7:SetClanTag(">silenth", "     "); break;
	case 8:SetClanTag(">silentha", "     "); break;
	case 9:SetClanTag(">silenthac", "     "); break;
	case 10:SetClanTag("<silenthack", "     "); break;
	case 11:SetClanTag("<silenthacks", "     "); break;
	case 12:SetClanTag("<ilenthacks", "     "); break;
	case 13:SetClanTag("<lenthacks", "     "); break;
	case 14:SetClanTag("<enthacks", "     "); break;
	case 15:SetClanTag("<nthacks", "     "); break;
	case 16:SetClanTag("<thacks", "     "); break;
	case 17:SetClanTag("<acks", "     "); break;
	case 18:SetClanTag("<cks", "     "); break;
	case 19:SetClanTag("<ks", "     "); break;
	case 20:SetClanTag("<s", "     "); break;
	case 21:SetClanTag("<", "     "); break;
	}
	counter++;
}

void CMiscHacks::Move(CUserCmd *pCmd, bool &bSendPacket)
{
	// Any Move Stuff

	// Bhop
	switch (Menu::Window.MiscTab.OtherAutoJump.GetState())
	{
	case 0:
		break;
	case 1:
		AutoJump(pCmd);
		break;
	}

	if (Menu::Window.MiscTab.OtherSlowMo.GetState())
	{
		SlowMotion(pCmd, bSendPacket);
	}



	if (Menu::Window.MiscTab.Logs.GetState())
	{
		
			ConVar* Developer = Interfaces::CVar->FindVar("developer");
			*(float*)((DWORD)&Developer->fnChangeCallback + 0xC) = NULL;
			Developer->SetValue("1");

			ConVar* con_filter_enable = Interfaces::CVar->FindVar("con_filter_enable");
			*(float*)((DWORD)&con_filter_enable->fnChangeCallback + 0xC) = NULL;
			con_filter_enable->SetValue("2");

			ConVar* con_filter_text = Interfaces::CVar->FindVar("con_filter_text");
			*(float*)((DWORD)&con_filter_text->fnChangeCallback + 0xC) = NULL;
			con_filter_text->SetValue("[silenthacks]");
	}
	if (Menu::Window.VisualsTab.OtherNoScope.GetState())
	{

	
		ConVar* con_filter_enable = Interfaces::CVar->FindVar("mat_postprocess_enable");
		*(float*)((DWORD)&con_filter_enable->fnChangeCallback + 0xC) = NULL;
		con_filter_enable->SetValue("0");


	}
	else
	{
		ConVar* con_filter_enable = Interfaces::CVar->FindVar("mat_postprocess_enable");
		*(float*)((DWORD)&con_filter_enable->fnChangeCallback + 0xC) = NULL;
		con_filter_enable->SetValue("1");
	}
	// AutoStrafe

	Interfaces::Engine->GetViewAngles(AutoStrafeView);
	switch (Menu::Window.MiscTab.OtherAutoStrafe.GetState())
	{
	case 0:
		break;
	case 1:
		RageStrafe(pCmd);

		break;
	}

		Fakelag(pCmd, bSendPacket);
}

void CMiscHacks::Draw()
{
	switch (Menu::Window.MiscTab.NameChanger.GetIndex())
	{
	case 0:
		break;
	case 1:
		Namespam();
		break;
	case 2:
		NoName();
		break;
	case 3:
		NameSteal();
		break;
	}

	if (Menu::Window.MiscTab.OtherChatSpam.GetState())
		ChatSpam();
}

void CMiscHacks::ChatSpamName()
{
	// Don't spam it too fast so you can still do stuff
	static clock_t start_t = clock();
	int spamtime = Menu::Window.MiscTab.OtherChatDelay.GetValue();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	if (timeSoFar < spamtime)
		return;

	static bool holzed = true;

	if (Menu::Window.MiscTab.OtherTeamChat.GetState())
	{
		SayInTeamChat("\silenthacks\n");
	}
	else
	{
		SayInChat("\nsilenthacks\n");
	}

	start_t = clock();
}

static __declspec(naked) void __cdecl Invoke_NET_SetConVar(void* pfn, const char* cvar, const char* value)
{
	__asm 
	{
		push    ebp
			mov     ebp, esp
			and     esp, 0FFFFFFF8h
			sub     esp, 44h
			push    ebx
			push    esi
			push    edi
			mov     edi, cvar
			mov     esi, value
			jmp     pfn
	}
}
// Color(0, 255, 0, 255),
// Color(255, 0, 0, 255),


void DECLSPEC_NOINLINE NET_SetConVar(const char* value, const char* cvar)
{
	static DWORD setaddr = Utilities::Memory::FindPattern("engine.dll", (PBYTE)"\x8D\x4C\x24\x1C\xE8\x00\x00\x00\x00\x56", "xxxxx????x");
	if (setaddr != 0) 
	{
		void* pvSetConVar = (char*)setaddr;
		Invoke_NET_SetConVar(pvSetConVar, cvar, value);
	}
}

void change_name(const char* name)
{
	if (Interfaces::Engine->IsInGame() && Interfaces::Engine->IsConnected())
		NET_SetConVar(name, "name");
}

void CMiscHacks::AutoJump(CUserCmd *pCmd)
{
	if (pCmd->buttons & IN_JUMP && GUI.GetKeyState(VK_SPACE))
	{
		int iFlags = hackManager.pLocal()->GetFlags();
		if (!(iFlags & FL_ONGROUND))
			pCmd->buttons &= ~IN_JUMP;

		if (hackManager.pLocal()->GetVelocity().Length() <= 50)
		{
			pCmd->forwardmove = 450.f;
		}
	}
}

void CMiscHacks::LegitStrafe(CUserCmd *pCmd)
{
	IClientEntity* pLocal = hackManager.pLocal();
	if (!(pLocal->GetFlags() & FL_ONGROUND))
	{
		pCmd->forwardmove = 0.0f;

		if (pCmd->mousedx < 0)
		{
			pCmd->sidemove = -450.0f;
		}
		else if (pCmd->mousedx > 0)
		{
			pCmd->sidemove = 450.0f;
		}
	}
}

void CMiscHacks::RageStrafe(CUserCmd *pCmd)
{
	

	if (GetAsyncKeyState(VK_SHIFT))
		return;
	
	IClientEntity* pLocal = hackManager.pLocal();
	static bool bDirection = true;

	bool bKeysPressed = true;

	float flYawBhop = 0.f;
	if (pLocal->GetVelocity().Length() > 50.f)
	{
		float x = 30.f, y = pLocal->GetVelocity().Length(), z = 0.f, a = 0.f;

		z = x / y;
		z = fabsf(z);

		a = x * z;

		flYawBhop = a;
	}

	if ((GetAsyncKeyState(VK_SPACE) && !(pLocal->GetFlags() & FL_ONGROUND)) && bKeysPressed)
	{

		if (bDirection)
		{
			AutoStrafeView -= flYawBhop;
			GameUtils::NormaliseViewAngle(AutoStrafeView);
			pCmd->sidemove = -400.f;
			bDirection = false;
		}
		else
		{
			AutoStrafeView += flYawBhop;
			GameUtils::NormaliseViewAngle(AutoStrafeView);
			pCmd->sidemove = 400.f;
			bDirection = true;
		}

		if (pCmd->mousedx < 0)
		{
			pCmd->sidemove = -450.f;
		}

		if (pCmd->mousedx > 0)
		{
			pCmd->sidemove = 450.f;
		}
	}
}

Vector GetAutostrafeView()
{
	return AutoStrafeView;
}

void CMiscHacks::ChatSpamInterwebz()
{
	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	if (timeSoFar < 0.001)
		return;

	static bool wasSpamming = true;
	//static std::string nameBackup = "INTERWEBZ";

	if (wasSpamming)
	{
		static bool useSpace = true;
		if (useSpace)
		{
			change_name ("money.bot ");
			useSpace = !useSpace;
		}
		else
		{
			change_name("money.bot");
			useSpace = !useSpace;
		}
	}

	start_t = clock();
}

void CMiscHacks::ChatSpamDisperseName()
{
	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	if (timeSoFar < 0.001)
		return;

	static bool wasSpamming = true;
	//static std::string nameBackup = "INTERWEBZ";

	if (wasSpamming)
	{
		static bool useSpace = true;
		if (useSpace)
		{
			change_name("™AIMWARE.NET");
			useSpace = !useSpace;
		}
		else
		{
			change_name("©AIMWARE.NET");
			useSpace = !useSpace;
		}
	}

	start_t = clock();
}

void CMiscHacks::ChatSpamAdvertise()
{
	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	if (timeSoFar < 0.001)
		return;

	static bool wasSpamming = true;

	if (wasSpamming)
	{
		static bool useSpace = true;
		if (useSpace)
		{
			change_name("Charisma-");
			useSpace = !useSpace;
		}
		else
		{
			change_name("©Charisma");
			useSpace = !useSpace;
		}
	}

	start_t = clock();
}

void CMiscHacks::ChatSpamName()
{
	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	if (timeSoFar < 0.001)
		return;

	std::vector < std::string > Names;

	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		// Get the entity
		IClientEntity *entity = Interfaces::EntList->GetClientEntity(i);

		player_info_t pInfo;
		// If it's a valid entity and isn't the player
		if (entity && hackManager.pLocal()->GetTeamNum() == entity->GetTeamNum() && entity != hackManager.pLocal())
		{
			ClientClass* cClass = (ClientClass*)entity->GetClientClass();

			// If entity is a player
			if (cClass->m_ClassID == (int)CSGOClassID::CCSPlayer)
			{
				if (Interfaces::Engine->GetPlayerInfo(i, &pInfo))
				{
					if (!strstr(pInfo.name, "GOTV"))
						Names.push_back(pInfo.name);
				}
			}
		}
	}

	static bool wasSpamming = true;
	//static std::string nameBackup = "INTERWEBZ.CC";

	int randomIndex = rand() % Names.size();
	char buffer[1024];
	sprintf_s(buffer, "%s ", Names[randomIndex].c_str());

	if (wasSpamming)
	{
		change_name("-CHARISMA - AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER  AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER ");
	}
	else
	{
		change_name("CHARISMA - AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER  AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER AYYWARE CRASHER ");
	}

	start_t = clock();
}

void CMiscHacks::ChatSpamRegular()
{
	// Don't spam it too fast so you can still do stuff
	static clock_t start_t = clock();
	int spamtime = Menu::Window.MiscTab.OtherChatDelay.GetValue();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	if (timeSoFar < spamtime)
		return;

	static bool holzed = true;

	if (Menu::Window.MiscTab.OtherTeamChat.GetState())
	{
		SayInTeamChat("INTERWEBZ.CC OWNS ME AND ALL");
	}
	else
	{
		SayInChat("INTERWEBZ.CC OWNS ME AND ALL");
	}

	start_t = clock();
}

void CMiscHacks::Fakelag(CUserCmd *pCmd, bool &bSendPacket)
{
	int iChoke;
	switch (Menu::Window.RageBotTab.FakeLag.GetIndex())
	{
	case 0:
		iChoke = 0;
		break;
	case 1:
		iChoke = 2;
		break;
	case 2:
		iChoke = 4;
		break;
	case 3:
		iChoke = 7;
		break;
	}
	static int iFakeLag = -1;
	iFakeLag++;

	if (iFakeLag <= iChoke && iFakeLag > -1)
	{
		bSendPacket = false;
	}
	else
	{
		bSendPacket = true;
		iFakeLag = -1;
	}

}



void CMiscHacks::lby()
{
	if (hackManager.pLocal()->IsAlive())
	{
		int iFlags = hackManager.pLocal()->GetFlags();
		Color color;
		bool lby;
		if (iFlags & FL_ONGROUND)
			lby = false;
		else
			lby = true;

		if (lby)
		{
			color = Color(5, 125, 5);
		}
		else
		{
			color = Color(125, 5, 5);
		}

	}
}


void CMiscHacks::thatsameme()
{
	static int counter = 0;
	static int motion = 0;
	int ServerTime = (float)Interfaces::Globals->interval_per_tick * hackManager.pLocal()->GetTickBase() * 3;

	if (counter % 48 == 0)
		motion++;
	int value = ServerTime % 30;
	switch (value) {

	}
	counter++;
}

void CMiscHacks::scopememe()
{
if (Menu::Window.VisualsTab.OtherNoScope.GetState())
{
if (hackManager.pLocal()->IsAlive() && hackManager.pLocal()->IsScoped())
{
int width, height;
Interfaces::Engine->GetScreenSize(width, height);
Render::Line(width / 2, 0, width / 2, height, Color(0, 0, 0, 255));
Render::Line(0, height / 2, width, height / 2, Color(0, 0, 0, 255));
}
}
}
 
void CMiscHacks::SlowMotion(CUserCmd * pCmd, bool &bSendPacket)
{
	int AirStuckKey122 = VK_SHIFT;
	if (GetAsyncKeyState(VK_MENU))
	{
		static int iChoked = -1;
		iChoked++;

		if (iChoked < 1)
		{
			bSendPacket = false;



			pCmd->tick_count += 10.95; // 10.95
			pCmd->command_number += 5.07 + pCmd->tick_count % 2 ? 0 : 1; // 5

			pCmd->buttons |= hackManager.pLocal()->GetMoveType() == IN_BACK;
			pCmd->forwardmove = pCmd->sidemove = 0.f;
		}
		else
		{
			bSendPacket = true;
			iChoked = -1;

			Interfaces::Globals->frametime *= (hackManager.pLocal()->GetVelocity().Length2D()) / 10; // 10
			pCmd->buttons |= hackManager.pLocal()->GetMoveType() == IN_FORWARD;
		}
	}
}

