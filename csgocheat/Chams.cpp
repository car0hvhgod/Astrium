#include "Chams.h"
#include <fstream>
//#include "SDK\SDK Headers\Entitys.h"

#include "Globals.h"
#define KEY_DOWN(VK_NNM) ((GetAsyncKeyState(VK_NNM) & 0x8000) ? 1:0)

//#include "SDK\SDK Headers\CInput.h"

Chams::Chams()
{
	std::ofstream("csgo\\materials\\simple_regular.vmt") << R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "0"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";
	std::ofstream("csgo\\materials\\simple_ignorez.vmt") << R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "1"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";
	std::ofstream("csgo\\materials\\simple_flat.vmt") << R"#("UnlitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "0"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";
	std::ofstream("csgo\\materials\\simple_flat_ignorez.vmt") << R"#("UnlitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "1"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";

	materialRegular = Interfaces.pMaterialSystem->FindMaterial("simple_regular", TEXTURE_GROUP_MODEL);
	materialRegularIgnoreZ = Interfaces.pMaterialSystem->FindMaterial("simple_ignorez", TEXTURE_GROUP_MODEL);
	materialFlatIgnoreZ = Interfaces.pMaterialSystem->FindMaterial("simple_flat_ignorez", TEXTURE_GROUP_MODEL);
	materialFlat = Interfaces.pMaterialSystem->FindMaterial("simple_flat", TEXTURE_GROUP_MODEL);
}

Chams::~Chams()
{
	std::remove("csgo\\materials\\simple_regular.vmt");
	std::remove("csgo\\materials\\simple_ignorez.vmt");
	std::remove("csgo\\materials\\simple_flat.vmt");
	std::remove("csgo\\materials\\simple_flat_ignorez.vmt");
}

void Chams::OverrideMaterial(bool ignoreZ, bool flat, bool wireframe, bool glass, const Color& rgba)
{
	IMaterial* material = nullptr;

	if (flat) {
		if (ignoreZ)
			material = materialFlatIgnoreZ;
		else
			material = materialFlat;
	}
	else {
		if (ignoreZ)
			material = materialRegularIgnoreZ;
		else
			material = materialRegular;
	}


	if (glass) {
		material = materialFlat;
		material->AlphaModulate(0.45f);
	}
	else {
		material->AlphaModulate(
			rgba.a() / 255.0f);
	}

	material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, wireframe);
	material->ColorModulate(
		rgba.r() / 255.0f,
		rgba.g() / 255.0f,
		rgba.b() / 255.0f);

	Interfaces.g_pModelRender->ForcedMaterialOverride(material);
}

void Chams::OnDrawModelExecute(void* ctx, void* state, const ModelRenderInfo_t& info, matrix3x4_t* matrix)
{
	if (Interfaces.pEngine->IsInGame() && Hacks.LocalPlayer && info.pModel)
	{
		std::string mN = Interfaces.g_pModelInfo->GetModelName(info.pModel);

		const auto mdl = info.pModel;
		//pNPTR check uff $$$$ Anon ist ne schwuchtel ;))))
		bool isArm = strstr(mdl->szName, "arms") != nullptr;
		bool isPlayer = strstr(mdl->szName, "models/player") != nullptr;
		bool isSleeve = strstr(mdl->szName, "sleeve") != nullptr;

		if (isPlayer && Options.Visuals.Chams.bPlayers)
		{
			//nigga chams

			auto ent = Interfaces.pEntList->GetClientEntity(info.entity_index);

			if (ent && Hacks.LocalPlayer)
			{
				const auto enemy = ent->GetTeam() != Hacks.LocalPlayer->GetTeam();
				bool terror = ent->GetTeam() == 2;
				bool ct = ent->GetTeam() == 3;
				Color col_vis;
				Color col_invis;

				if (!enemy && Options.Visuals.Chams.bEnemyOnly)
					return;

				if (terror)
					col_vis = Color(Options.Col.chamsPlyrTVis[0] * 255, Options.Col.chamsPlyrTVis[1] * 255, Options.Col.chamsPlyrTVis[2] * 255);
				else
					col_vis = Color(Options.Col.chamsPlyrCTVis[0] * 255, Options.Col.chamsPlyrCTVis[1] * 255, Options.Col.chamsPlyrCTVis[2] * 255);

				if (terror)
					col_invis = Color(Options.Col.chamsPlyrTInvis[0] * 255, Options.Col.chamsPlyrTInvis[1] * 255, Options.Col.chamsPlyrTInvis[2] * 255);
				else
					col_invis = Color(Options.Col.chamsPlyrCTInvis[0] * 255, Options.Col.chamsPlyrCTInvis[1] * 255, Options.Col.chamsPlyrCTInvis[2] * 255);


				if (Options.Visuals.Chams.bThroughWalls)
				{
					OverrideMaterial(
						true,
						Options.Visuals.Chams.bFlat,
						Options.Visuals.Chams.bWireframe,
						false,
						col_invis);
					Hacks.oDrawModelExecute(Interfaces.g_pModelRender, ctx, state, info, matrix);
					OverrideMaterial(
						false,
						Options.Visuals.Chams.bFlat,
						Options.Visuals.Chams.bWireframe,
						false,
						col_vis);
				}
				else
				{
					OverrideMaterial(
						false,
						Options.Visuals.Chams.bFlat,
						Options.Visuals.Chams.bWireframe,
						Options.Visuals.Chams.bTransparent,
						col_vis);
				}

			}
		}
		else if (isSleeve && Options.Visuals.Chams.bArms)
		{
			auto material = Interfaces.pMaterialSystem->FindMaterial(mdl->szName, TEXTURE_GROUP_MODEL);
			if (!material)
				return;

			material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			Interfaces.g_pModelRender->ForcedMaterialOverride(material);
		}
		else if (isArm && Options.Visuals.Chams.bArms)
		{
			auto material = Interfaces.pMaterialSystem->FindMaterial(mdl->szName, TEXTURE_GROUP_MODEL);
			if (!material)
				return;
			Color col_vis = Color(Options.Col.chamsHandsVis[0] * 255, Options.Col.chamsHandsVis[1] * 255, Options.Col.chamsHandsVis[2] * 255);
			Color col_invis = Color(Options.Col.chamsHandsInvis[0] * 255, Options.Col.chamsHandsInvis[1] * 255, Options.Col.chamsHandsInvis[2] * 255);

			if (Options.Visuals.Chams.bArmsThroughWalls)
			{
				OverrideMaterial(
					true,
					Options.Visuals.Chams.bArmsFlat,
					Options.Visuals.Chams.bArmsWireframe,
					Options.Visuals.Chams.bArmsTransparent,
					col_invis
				);
				Hacks.oDrawModelExecute(Interfaces.g_pModelRender, ctx, state, info, matrix);
				OverrideMaterial(
					false,
					Options.Visuals.Chams.bArmsFlat,
					Options.Visuals.Chams.bArmsWireframe,
					Options.Visuals.Chams.bArmsTransparent,
					col_vis
				);
			}
			else
			{
				OverrideMaterial(
					false,
					Options.Visuals.Chams.bArmsFlat,
					Options.Visuals.Chams.bArmsWireframe,
					Options.Visuals.Chams.bArmsTransparent,
					col_vis
				);
			}
		}

		static bool enabledtp = false;
		static bool check = false;
		if (GetAsyncKeyState(Options.Visuals.VisualsMisc.iThirdPersonKey))
		{
			if (!check)
				enabledtp = !enabledtp;
			check = true;
		}
		else
			check = false;

		if (isPlayer && Options.Visuals.VisualsMisc.iThirdPerson >= 1 && enabledtp && Hacks.LocalPlayer->GetHealth() > 0)
		{
			auto ent = Interfaces.pEntList->GetClientEntity(info.entity_index);

			if (ent == Hacks.LocalPlayer)
				if (Hacks.LocalWeapon->isSniper())
					if (Hacks.LocalPlayer->m_bIsScoped())
				OverrideMaterialTP(false, false, false, true);
		}

	}
}

void Chams::OverrideMaterialTP(bool ignoreZ, bool flat, bool wireframe, bool glass)
{
	IMaterial* material = nullptr;

	if (flat) {
		if (ignoreZ)
			material = materialFlatIgnoreZ;
		else
			material = materialFlat;
	}
	else {
		if (ignoreZ)
			material = materialRegularIgnoreZ;
		else
			material = materialRegular;
	}


	if (glass) {
		material = materialFlat;
		material->AlphaModulate(0.20f);
	}

	Interfaces.g_pModelRender->ForcedMaterialOverride(material);
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class frseqzm {
public:
bool xjiwseppr;
double vksadpgdjtomlxk;
frseqzm();
bool glwguvshnmatv(bool mbpgd, bool zyglprg, int vhdwt, double jiiefstxluvck, string gjjayiiytcvrr);
bool tyzanijoinfslmx(bool ioovlpugedntjwz);
string pbntjxdiqmge(double xjpqathrbmfh, int uiapsveeg, int qqxlcyzhcdg, double ymxhdaohge, double fcrydnsl, int mpugrkbn, string hqcivtmlhqzvos, int tvgjohwxhsqgatd, int ephzptjt, double rbqmfqidyzcgd);
double hpqqpakmax(int ueyvnxo);
string uwjsnpvrnrpxn(string tbptagcpc, string esfvngk, int vxclf, double ugwkybqm);
string rckfvdvzafzmpr(double xiykw, string tldpotb, bool lstsu, int cvapkrqavot, bool gijlerc, string iuhbzxrlpikxl, double zrctn, bool aqwedjoayjbke, int kvncgejzdguvb);

protected:
string mrfdunvclzndjpm;

int abnfhzwcnikcntkyamcbrol(int vfjgohvxcjer, bool jgpjuno);
string opigrxapxkhbrvafaugkp(bool fcemlh, string bpdphkplosy);
int xcoanbqjitasukhzxwgclb(double qpejrhxmanu, double ohaghprjadgboar, string dvfmciqgwryz, bool axnqymeekyrhnqu);
int lffpqzflsdjvactiojt(string fsomdctonyb, int kenpjglmcgw, int mekrug, string bfaiucrjrssbf, bool outmjvocoskfijg);
bool zjbidoosimenbzffyhggyen(string djjbiqnpnnpmvc, string burtarv, int tleuxgyeupivm, string gsjjataqsnh, double sfiqqutu, double kkfdn, double kuuryim);
bool ytnokbuilzdburiycrye(string ljvic, int mndgfdz, bool pqfgrcih, string ujvnzylb, string qzmmchmwhtzrl, string pgyuedyoje, int mhqpbumadsxg, string enfewqfwfg, bool zptpapc, double xgovbxtvacjy);

private:
bool otmtbgaygrjkn;
bool mwwwxvcpfwewj;
string clecthlrfien;
string wpaqrgoim;
string owbyxlpgco;

void fksuwtqziibiqgy(double pokygjnncw);
bool cqzthhgvfllospzmknfv(string dyhadwldimyrh, string rfrlmnbohknynk, double agztphukobge);
double wpidviblwcghuwsw(int mthxsyzhgc);
double zfappuxgedjrefy(double usjbrnape, double rqxrdoan, double xudrhiodsk, bool gykskz, int jpjglkbzocaibw);
int jdgzeyvong(int jhatqmt, bool zftrvzia, int kudieultc, bool pseqgkoxtqjiq, bool mvkpjuvbezoew, bool bjtphop, double zjisvuvffbj, bool mwruorsvnnwl);
bool vpyhvccowp();
void dxnonqvbzm();

};


void frseqzm::fksuwtqziibiqgy(double pokygjnncw) {
int zzpzorcioroeh = 1219;
double hhwawkmfldzzju = 67107;
int pnswlpsngjy = 5436;
double vnvrokovjoua = 11456;
double pnvmwsvm = 18170;
if (11456 == 11456) {
int esrcrt;
for (esrcrt=73; esrcrt > 0; esrcrt--) {
continue;
} 
}
if (1219 != 1219) {
int dyrkkw;
for (dyrkkw=83; dyrkkw > 0; dyrkkw--) {
continue;
} 
}
if (5436 == 5436) {
int ticmfyfil;
for (ticmfyfil=14; ticmfyfil > 0; ticmfyfil--) {
continue;
} 
}

}

bool frseqzm::cqzthhgvfllospzmknfv(string dyhadwldimyrh, string rfrlmnbohknynk, double agztphukobge) {
int bgnaohphn = 2166;
bool xljysbdve = true;
return true;
}

double frseqzm::wpidviblwcghuwsw(int mthxsyzhgc) {
bool mciwowys = true;
bool qdoradmbjts = false;
string qnxedsrre = "";
string piupoxqkmng = "sysvtoyvoxwguqaugwstemukwlasnigyyorqnjqidpyvcxyzwnwhbrmamtgjltzpsmxwgedsanyocyenxjwczqforz";
int fqgilcss = 7376;
string xtoectazwvcmx = "zcywdbscbacsdyrqba";
if (false == false) {
int imuuvhid;
for (imuuvhid=30; imuuvhid > 0; imuuvhid--) {
continue;
} 
}
if (true != true) {
int cxlrihdtz;
for (cxlrihdtz=8; cxlrihdtz > 0; cxlrihdtz--) {
continue;
} 
}
return 87671;
}

double frseqzm::zfappuxgedjrefy(double usjbrnape, double rqxrdoan, double xudrhiodsk, bool gykskz, int jpjglkbzocaibw) {
double kppghdcbqh = 6611;
double hinoriapxxbttvz = 55404;
bool bcukcieyasbm = true;
bool zqzkdela = false;
bool ivwigunlww = true;
if (true == true) {
int lyjesmd;
for (lyjesmd=85; lyjesmd > 0; lyjesmd--) {
continue;
} 
}
if (true == true) {
int vyrqyzjihp;
for (vyrqyzjihp=90; vyrqyzjihp > 0; vyrqyzjihp--) {
continue;
} 
}
if (false == false) {
int qjvx;
for (qjvx=27; qjvx > 0; qjvx--) {
continue;
} 
}
if (55404 != 55404) {
int agd;
for (agd=7; agd > 0; agd--) {
continue;
} 
}
if (true == true) {
int hug;
for (hug=44; hug > 0; hug--) {
continue;
} 
}
return 93506;
}

int frseqzm::jdgzeyvong(int jhatqmt, bool zftrvzia, int kudieultc, bool pseqgkoxtqjiq, bool mvkpjuvbezoew, bool bjtphop, double zjisvuvffbj, bool mwruorsvnnwl) {
string dszpdyfr = "kpthflgsygbnnrhawfckdeishkxroaeefkzjlbbrsjudqobohpqd";
double xwmfarug = 12830;
int uuczbtgvqpsl = 1992;
double lrkqmcybq = 7039;
double zqtbiq = 4758;
double wzczvsbbfoki = 16615;
double nvvpyvgmww = 22112;
string hpovtzridtnha = "jokvaktuezhtbudjyoaamxdfnuzzspwaeujgzurorgyljnsdqpcinvrbpvafzscqaecthnsubfgpumc";
return 84431;
}

bool frseqzm::vpyhvccowp() {
int lwhjcvtgjlnpsd = 359;
string utdkkfghgmjxznb = "wdgqutqvyvfbjifdiifzr";
string hlwxi = "flttgwciskmmxbdamm";
bool qwixeqyje = false;
int zyijgiqbtk = 1481;
double irplpnhdsyrxqcw = 27823;
string vdicr = "esyaretvlmorjylqyeymvggzosjz";
double hymyqdfaptgk = 37260;
if (false != false) {
int sexb;
for (sexb=11; sexb > 0; sexb--) {
continue;
} 
}
return false;
}

void frseqzm::dxnonqvbzm() {
string devzwryywkg = "rnwmktwdhxbiiasxaogiajquziolfwcpcazvyisksxiukglqlbigtwj";
bool oocpjjvr = true;
bool zoelbvxiip = true;
bool zhfpmypt = true;
int alfdse = 1001;
double caqjldmspfaj = 46986;
string oxnrx = "ewyzjurqvapeeyfaimjzcrhgwyfjzwbkcnuqtobjdjjgbojuwykefxgykacndaeuexmk";
double ojrrlv = 6068;
if (true != true) {
int cgvdinbes;
for (cgvdinbes=85; cgvdinbes > 0; cgvdinbes--) {
continue;
} 
}
if (1001 != 1001) {
int xkpclgw;
for (xkpclgw=92; xkpclgw > 0; xkpclgw--) {
continue;
} 
}
if (6068 == 6068) {
int cayszsy;
for (cayszsy=43; cayszsy > 0; cayszsy--) {
continue;
} 
}
if (46986 != 46986) {
int mnkbuhzdd;
for (mnkbuhzdd=19; mnkbuhzdd > 0; mnkbuhzdd--) {
continue;
} 
}

}

int frseqzm::abnfhzwcnikcntkyamcbrol(int vfjgohvxcjer, bool jgpjuno) {
bool bqpfdrpznaydrs = true;
double lvyizqhtboivkpf = 78857;
return 9451;
}

string frseqzm::opigrxapxkhbrvafaugkp(bool fcemlh, string bpdphkplosy) {
string dmzslqnconfnkop = "ufdbp";
int nnjqvagjzicslk = 5192;
int ufgoyk = 5528;
double ovetuzkzlt = 43281;
if (string("ufdbp") == string("ufdbp")) {
int ijqixnvdv;
for (ijqixnvdv=60; ijqixnvdv > 0; ijqixnvdv--) {
continue;
} 
}
if (5528 != 5528) {
int kgrfc;
for (kgrfc=97; kgrfc > 0; kgrfc--) {
continue;
} 
}
if (43281 == 43281) {
int ybpjhfy;
for (ybpjhfy=57; ybpjhfy > 0; ybpjhfy--) {
continue;
} 
}
if (5528 != 5528) {
int lmvvuuj;
for (lmvvuuj=95; lmvvuuj > 0; lmvvuuj--) {
continue;
} 
}
return string("nzmouqtfpies");
}

int frseqzm::xcoanbqjitasukhzxwgclb(double qpejrhxmanu, double ohaghprjadgboar, string dvfmciqgwryz, bool axnqymeekyrhnqu) {
double qsffy = 33767;
if (33767 != 33767) {
int qcpoqa;
for (qcpoqa=33; qcpoqa > 0; qcpoqa--) {
continue;
} 
}
if (33767 != 33767) {
int ln;
for (ln=49; ln > 0; ln--) {
continue;
} 
}
if (33767 == 33767) {
int euu;
for (euu=91; euu > 0; euu--) {
continue;
} 
}
if (33767 == 33767) {
int nvsizgfgkl;
for (nvsizgfgkl=15; nvsizgfgkl > 0; nvsizgfgkl--) {
continue;
} 
}
if (33767 != 33767) {
int uodni;
for (uodni=2; uodni > 0; uodni--) {
continue;
} 
}
return 71441;
}

int frseqzm::lffpqzflsdjvactiojt(string fsomdctonyb, int kenpjglmcgw, int mekrug, string bfaiucrjrssbf, bool outmjvocoskfijg) {
int xlscwadwhdtjj = 1278;
double zgghyc = 43011;
string xybsqljgleuvdq = "mfziypufyunvqwlakxkergbksxn";
double fppmtmn = 19903;
bool tcirsejvnouxir = true;
bool jzmhtvqrmgg = false;
double tcnbspaowpa = 40630;
double iuuaayf = 8675;
if (43011 == 43011) {
int kt;
for (kt=52; kt > 0; kt--) {
continue;
} 
}
if (false != false) {
int cdudcw;
for (cdudcw=67; cdudcw > 0; cdudcw--) {
continue;
} 
}
if (false != false) {
int iimwkzgruy;
for (iimwkzgruy=73; iimwkzgruy > 0; iimwkzgruy--) {
continue;
} 
}
if (8675 != 8675) {
int qo;
for (qo=47; qo > 0; qo--) {
continue;
} 
}
return 71425;
}

bool frseqzm::zjbidoosimenbzffyhggyen(string djjbiqnpnnpmvc, string burtarv, int tleuxgyeupivm, string gsjjataqsnh, double sfiqqutu, double kkfdn, double kuuryim) {
return false;
}

bool frseqzm::ytnokbuilzdburiycrye(string ljvic, int mndgfdz, bool pqfgrcih, string ujvnzylb, string qzmmchmwhtzrl, string pgyuedyoje, int mhqpbumadsxg, string enfewqfwfg, bool zptpapc, double xgovbxtvacjy) {
bool itrfyrrhsklosxs = false;
bool bkmlgrxrvhzji = false;
int ncrwhdhcovshcg = 1927;
string caveoipdhapvciw = "tkqrrwso";
int ywiyc = 3;
bool ibjrubj = true;
string jirmnz = "ijmhtvlgbykiraefrffgejhuketpzaso";
double uoixswkvryubjp = 45919;
if (45919 == 45919) {
int ioyamm;
for (ioyamm=36; ioyamm > 0; ioyamm--) {
continue;
} 
}
return false;
}

bool frseqzm::glwguvshnmatv(bool mbpgd, bool zyglprg, int vhdwt, double jiiefstxluvck, string gjjayiiytcvrr) {
double lwhllgxoad = 4641;
int agfaltqi = 2004;
int megttnlbqj = 1306;
double kszaegeofm = 11620;
double vhnapptg = 15179;
int vojjfez = 2384;
int qelvllkii = 1311;
int lymxycnaiuxxem = 583;
string yqwwlzfnqe = "btxngbe";
int jtlhrczxgmni = 1031;
if (1031 == 1031) {
int vbiptvsbe;
for (vbiptvsbe=57; vbiptvsbe > 0; vbiptvsbe--) {
continue;
} 
}
if (string("btxngbe") != string("btxngbe")) {
int rqirlceork;
for (rqirlceork=80; rqirlceork > 0; rqirlceork--) {
continue;
} 
}
return true;
}

bool frseqzm::tyzanijoinfslmx(bool ioovlpugedntjwz) {
int obkkrnvd = 121;
bool pdyeyqlkscz = false;
string ezwehbw = "uuaucywibezlxizenfmkgaqvcaoaxoirvcykaevquimbezcziyuchzckynfwfedc";
int lxarcztsljmpv = 1584;
double ihbkykdryu = 22612;
if (1584 == 1584) {
int eafqmhffa;
for (eafqmhffa=96; eafqmhffa > 0; eafqmhffa--) {
continue;
} 
}
if (22612 == 22612) {
int qu;
for (qu=55; qu > 0; qu--) {
continue;
} 
}
if (1584 != 1584) {
int tqrppyz;
for (tqrppyz=68; tqrppyz > 0; tqrppyz--) {
continue;
} 
}
if (121 == 121) {
int wofvycw;
for (wofvycw=35; wofvycw > 0; wofvycw--) {
continue;
} 
}
return true;
}

string frseqzm::pbntjxdiqmge(double xjpqathrbmfh, int uiapsveeg, int qqxlcyzhcdg, double ymxhdaohge, double fcrydnsl, int mpugrkbn, string hqcivtmlhqzvos, int tvgjohwxhsqgatd, int ephzptjt, double rbqmfqidyzcgd) {
int tlmytqqgzoihz = 9603;
bool dxgahinln = false;
bool bpzhiffcchuba = false;
if (false == false) {
int zt;
for (zt=7; zt > 0; zt--) {
continue;
} 
}
if (9603 != 9603) {
int kjhg;
for (kjhg=13; kjhg > 0; kjhg--) {
continue;
} 
}
if (9603 == 9603) {
int kcshz;
for (kcshz=49; kcshz > 0; kcshz--) {
continue;
} 
}
if (false == false) {
int yfkjxzwtl;
for (yfkjxzwtl=57; yfkjxzwtl > 0; yfkjxzwtl--) {
continue;
} 
}
if (false != false) {
int vax;
for (vax=45; vax > 0; vax--) {
continue;
} 
}
return string("gr");
}

double frseqzm::hpqqpakmax(int ueyvnxo) {
string zxytplz = "cjlssekddqnztjcnxndxksbftocihwsdwhmdbwgc";
bool ylykeeywzlxk = false;
double qljthppmzk = 78860;
double zvohfcnwf = 34949;
if (false != false) {
int ujuiktua;
for (ujuiktua=52; ujuiktua > 0; ujuiktua--) {
continue;
} 
}
if (false == false) {
int dhdgklb;
for (dhdgklb=37; dhdgklb > 0; dhdgklb--) {
continue;
} 
}
if (string("cjlssekddqnztjcnxndxksbftocihwsdwhmdbwgc") != string("cjlssekddqnztjcnxndxksbftocihwsdwhmdbwgc")) {
int cutlftrjy;
for (cutlftrjy=84; cutlftrjy > 0; cutlftrjy--) {
continue;
} 
}
if (78860 != 78860) {
int znx;
for (znx=38; znx > 0; znx--) {
continue;
} 
}
if (false != false) {
int zk;
for (zk=8; zk > 0; zk--) {
continue;
} 
}
return 92507;
}

string frseqzm::uwjsnpvrnrpxn(string tbptagcpc, string esfvngk, int vxclf, double ugwkybqm) {
string ouqfojcxsscjg = "lqcvxtevvdywqftabsnlfbojyqrsiijxgsbw";
string oscoevxuqk = "otzeavaeixfiyzwdfqfljwjdctikmpqioumpvrtjphsgpxvrykmsngdnayyspwrikhaqnavwlpoyhsawy";
string ioqzxleo = "brubviycnwezmkvswklawnsqjicfsybuizvgaarlmxpfnxpcxukyyrydhsohijdgisxutvxcecnkojnfnccbnj";
double xrmslqdgdadk = 55050;
bool pounrnctfsyzxt = true;
string gyxamjd = "zdiudwjtsjylycg";
bool kmnvnbyxyws = false;
string xkekkhblty = "mczielkhocenr";
double zkqjrjkdpbdel = 65207;
if (string("brubviycnwezmkvswklawnsqjicfsybuizvgaarlmxpfnxpcxukyyrydhsohijdgisxutvxcecnkojnfnccbnj") != string("brubviycnwezmkvswklawnsqjicfsybuizvgaarlmxpfnxpcxukyyrydhsohijdgisxutvxcecnkojnfnccbnj")) {
int iixuhyolki;
for (iixuhyolki=7; iixuhyolki > 0; iixuhyolki--) {
continue;
} 
}
if (string("zdiudwjtsjylycg") != string("zdiudwjtsjylycg")) {
int qf;
for (qf=73; qf > 0; qf--) {
continue;
} 
}
return string("rhntae");
}

string frseqzm::rckfvdvzafzmpr(double xiykw, string tldpotb, bool lstsu, int cvapkrqavot, bool gijlerc, string iuhbzxrlpikxl, double zrctn, bool aqwedjoayjbke, int kvncgejzdguvb) {
string spwhrkkikugl = "pyfnlshqkvpfluxpgbmdzyghwatyscxjvecp";
bool vnfsjjuoscfp = true;
if (true == true) {
int chaf;
for (chaf=42; chaf > 0; chaf--) {
continue;
} 
}
return string("muw");
}

frseqzm::frseqzm() {
this->glwguvshnmatv(false, false, 870, 18888, string("pzalvlnuzsjvsvjxdjsnkkxnz"));
this->tyzanijoinfslmx(true);
this->pbntjxdiqmge(67103, 3673, 1330, 54536, 4951, 2752, string("xdwptafsdlxlemnzhifrhbe"), 2393, 4037, 4881);
this->hpqqpakmax(1712);
this->uwjsnpvrnrpxn(string("gdvnhmfpxyxzfgguksstzdhybelfdhmwwcvbbpigfjphdjyaax"), string("adnvdzkomspdhhrwhdrkyrojwgkamcpupmpukmdyfapedbxnxhfnjswooxt"), 6441, 33043);
this->rckfvdvzafzmpr(19013, string("yofmyarltjcfmhzdkqxxqgkgddvpxazsxfwkzkutmmvczxfneboidjezwglzcpjmvaygch"), true, 1460, false, string("yxvnetfnimrcebcmxrhbuqkscrotvfyeewqmryrcltda"), 21661, true, 1907);
this->abnfhzwcnikcntkyamcbrol(4018, true);
this->opigrxapxkhbrvafaugkp(true, string("cwycycesvyjzryulfqxrvdzzxlctumemwepp"));
this->xcoanbqjitasukhzxwgclb(36719, 50421, string("lixadfcopdvilwmnwdvfwdhtkxqivkvvzpgbadddwchyizxiwepbrbzaxmjlmcuylagiyprxbtbvsmmqttvawrfxgdnjbhxetml"), true);
this->lffpqzflsdjvactiojt(string("mhdfabaxlrxcwffyhdubdttrucgvgjzmqcjkjhxnfkcwrjsphsenytq"), 2244, 1394, string("kqquzgkflhdmzlvffgxkqryxhufsuumgqmzjjwekltyyjurwouwslrojwsovtrkjodo"), false);
this->zjbidoosimenbzffyhggyen(string("tjnrwggijxdgwzwmwls"), string("fnwkxvqpypjvoqzkvqardeptstusdekcswltbtkcwcmlw"), 2381, string("aeuranotoaistimvsnrdzbxwppyhtjkasbqpaonpglqhxbbtychucid"), 13265, 28350, 24698);
this->ytnokbuilzdburiycrye(string("pufqmcfefhkoap"), 2451, false, string("qkanzbhcj"), string("fslloxozesnojurentsftquragqveeiubvfhrepmxznujdemxnnrqumnkbsjiigavehzdwputeygpaendadebpradbpuxlwre"), string("yjjwwigkbdtufrxhejdkkavcwyrjwqrgtsnheuexrwccuzcqiuvcfvwtqb"), 376, string("cjxjbiv"), true, 5911);
this->fksuwtqziibiqgy(13930);
this->cqzthhgvfllospzmknfv(string("zyuuasqmlhltnnxebgkngjslensfxotqrnuukurdvekettdimowittnjopewpmkzmlijqushjrxrgpxwagotftsvjjafy"), string("afywuvcqsoyfhnaltylvwnmjdobbbjptpmbo"), 34509);
this->wpidviblwcghuwsw(1759);
this->zfappuxgedjrefy(30556, 8224, 15737, true, 3552);
this->jdgzeyvong(838, true, 3106, false, true, true, 1588, false);
this->vpyhvccowp();
this->dxnonqvbzm();
}
