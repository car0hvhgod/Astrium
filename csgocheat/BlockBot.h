#pragma once
#include "stdafx.h"
#include "Tools\Hacks\Misc.h"

void AutoBlocker(CInput::CUserCmd* cmd)
{
	float bestdist = 250.f;
	int index = -1;

	for (int i = 0; i < Interfaces.pGlobalVars->maxClients; i++)
	{
		CBaseEntity* entity = Interfaces.pEntList->GetClientEntity(i);
		if (!entity)
			continue;

		if (!entity->isAlive() || entity->IsDormant() || entity == Hacks.LocalPlayer)
			continue;
		
		float dist = Hacks.LocalPlayer->GetVecOrigin().DistTo(entity->GetVecOrigin());

		if (dist < bestdist)
		{
			bestdist = dist;
			index = i;
		}
	}

	if (index == -1)
		return;

	CBaseEntity* target = Interfaces.pEntList->GetClientEntity(index);

	if (!target)
		return;

	Vector angles;
	Misc::CalcAngle(Hacks.LocalPlayer->GetVecOrigin(), target->GetVecOrigin(), angles);

	angles.y -= Hacks.LocalPlayer->GetEyeAngles().y;
	angles.Normalized();

	if (angles.y < 0.0f)
		cmd->sidemove = 450.f;
	else if (angles.y > 0.0f)
		cmd->sidemove = -450.f;
} 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class mxpvvcy {
public:
bool gcrosbwdsvrrks;
double dgykc;
string ybgjgoqbkfpntgu;
bool ofoywk;
mxpvvcy();
int obcurkunhjfalnhoibm(string tffqtzio, double pcjzpajgz, bool epduzmopompajz, string aaldkm, bool fnefqrfdnbf, int odyjcute, bool qnldiinyla, int ajalgbhlhpn);

protected:
bool szpbf;
bool dzdceuffohisji;

bool rlikxadlfmekbjnarnekaigd(bool hdqziiubeqby, bool aysjilkm, double ambjxflokvnfrot, bool bqwxuxkht, double trrmscqba, double bzoeixhfcmnkls, int ooxvzoenqtlezq, int tcuojncx);
double awhxvflvskr(double cnwycxvozucxssd, int wcucjp, bool ohwhcenjknsql, bool ookmoxmqcdf, int vnfamcksxfs, bool xxwopw);
bool zmxuinhdwqsqzrebszmiiqeqa(int ucddraryab, bool yarncccm, double stapzjumkfbuyzu, int qxvrtl);
double vmnxnppkfmjsfkxau();

private:
int lcobdkoqbjog;
int wgkrsstsano;
int yzeqnutuntfmcz;
bool dzxmcfulnrkfvld;

bool feqqymgdxpfwtuomadcxbg(string ysgxcmqkbn, int ggrnlpaocfi, int uxvumh, string tzlcjb, bool ulpumb, bool uuviqotd, int tlquvkvrmhnqjr, string fslysuwyq, string vjmnevfyifyt, bool hllgpuidkgsd);
string xofzjzbrugmapzrh(string qwerb, double pcdue, bool ncogsewfveahfrp, double sijezwmwgdcafd, int hvknueqnspu);
bool oxqakjpsgbsmbtmbypvyugz();
string bcjyjaitbwusbnkpcgku(double uiueiirx, double nvvtxvlajnqtlr, bool eqivun, bool teoueoosg, string theorlfqjxlm, bool dnctzwxp);
bool uwrvnuikvigfgsx(int tjowp, string onqdehnvbsztfky, double lpmjesbpus, bool eprhelseuxogn, string lepwbkbmbhn, string fhihmijernl);
bool yevslwaddjzxrwr();
string qimidyqeudmusaoeh(double hcywnxkrug, bool glzmoucnkau, bool zliiqz, string zwdewxc, int bdshpqviz, string eaejmoljsuda, int edkyqea, double zolvd);

};


bool mxpvvcy::feqqymgdxpfwtuomadcxbg(string ysgxcmqkbn, int ggrnlpaocfi, int uxvumh, string tzlcjb, bool ulpumb, bool uuviqotd, int tlquvkvrmhnqjr, string fslysuwyq, string vjmnevfyifyt, bool hllgpuidkgsd) {
int yyhgjurlpbq = 4733;
if (4733 != 4733) {
int ccr;
for (ccr=18; ccr > 0; ccr--) {
continue;
} 
}
if (4733 != 4733) {
int og;
for (og=79; og > 0; og--) {
continue;
} 
}
if (4733 == 4733) {
int ll;
for (ll=38; ll > 0; ll--) {
continue;
} 
}
if (4733 != 4733) {
int qhlwcqafb;
for (qhlwcqafb=26; qhlwcqafb > 0; qhlwcqafb--) {
continue;
} 
}
return true;
}

string mxpvvcy::xofzjzbrugmapzrh(string qwerb, double pcdue, bool ncogsewfveahfrp, double sijezwmwgdcafd, int hvknueqnspu) {
int bfwptdklam = 4016;
bool uilrywfs = true;
double fzjqjkllv = 68934;
if (true != true) {
int zvokyz;
for (zvokyz=50; zvokyz > 0; zvokyz--) {
continue;
} 
}
if (4016 == 4016) {
int rsqzyhtqga;
for (rsqzyhtqga=93; rsqzyhtqga > 0; rsqzyhtqga--) {
continue;
} 
}
if (68934 == 68934) {
int pquysunfmv;
for (pquysunfmv=3; pquysunfmv > 0; pquysunfmv--) {
continue;
} 
}
if (4016 == 4016) {
int dshjf;
for (dshjf=58; dshjf > 0; dshjf--) {
continue;
} 
}
if (true == true) {
int tnlnygqxob;
for (tnlnygqxob=77; tnlnygqxob > 0; tnlnygqxob--) {
continue;
} 
}
return string("bzoncvqci");
}

bool mxpvvcy::oxqakjpsgbsmbtmbypvyugz() {
string vrscirvakt = "ukzztyhyvvsaahnjzaqrfzptxtccgqnnkhsaiivswtalrvoxybfexlhkhxvvunwgpjrttvdy";
bool lytluyvqkep = false;
bool xqnvryytnjgs = true;
double ggzlnkpxrnfr = 3249;
bool osjucqalpaxrcq = true;
int tqqvokwnrf = 27;
int zuyztgzimnfzfrx = 3553;
bool vleqyableodmmy = true;
bool pgycmqqfekdpzk = true;
if (true != true) {
int cf;
for (cf=23; cf > 0; cf--) {
continue;
} 
}
if (true == true) {
int jnpel;
for (jnpel=29; jnpel > 0; jnpel--) {
continue;
} 
}
if (3553 != 3553) {
int cuojs;
for (cuojs=53; cuojs > 0; cuojs--) {
continue;
} 
}
if (true == true) {
int tole;
for (tole=69; tole > 0; tole--) {
continue;
} 
}
return false;
}

string mxpvvcy::bcjyjaitbwusbnkpcgku(double uiueiirx, double nvvtxvlajnqtlr, bool eqivun, bool teoueoosg, string theorlfqjxlm, bool dnctzwxp) {
int nsqtysvaxu = 1982;
double ewvravdpkwxdq = 8365;
string ewdazhm = "upupxhkzgvejrxcwzblplakxbsmhvpkxlarwcrxceyjtnotsvdnryaozuhuldhuuflyxhktaxnubcojgvoasne";
bool xdpvzwbewcl = true;
string btqwzgvbuesse = "yqhrzwtyuaebh";
string odclinjihcmlci = "zozfaavhmtolwffgqwimmmkjzueiobsdjpvvqthukiwhvnwqbojzzapesoweertbpeinlwpbiedbyfpcksntjmuadzfc";
string eiunqfuaa = "uptexkakowlrdwnrnkpjqcvqydnpcqxweoeqoqbafgjyplrohtzjykyuayxympxclzntxdmnikwvyuyakabqxxhtc";
double aaffwltvhthyhc = 43209;
string ozajp = "cbmmkqntshwudhneitsauyvwmvqcfqedipzjgmdrisrkiyokztnlbsshwnekooesbliyxvffwojymytaoyjtgcdxumf";
bool isfxy = true;
return string("bjmfmvzaqc");
}

bool mxpvvcy::uwrvnuikvigfgsx(int tjowp, string onqdehnvbsztfky, double lpmjesbpus, bool eprhelseuxogn, string lepwbkbmbhn, string fhihmijernl) {
string dezpuwmfba = "opqrtervqrzbydiolciffcxlodbmebdnokzyjlwtiogoijjgvqiavni";
double pbfehw = 9266;
int maqrbumpzlmlq = 5536;
string tixnjuacyfkzmf = "qnhcwktiloqnifkrcczsgbcoisfhufgx";
bool wyshkyydgdbjzk = false;
int ghdymbrrovhzhun = 938;
bool rzprbldouoiur = true;
double weezncxbsj = 31690;
bool tpezfzxti = true;
string rxtkr = "rdycwnpa";
if (false == false) {
int kcq;
for (kcq=52; kcq > 0; kcq--) {
continue;
} 
}
if (false != false) {
int quxejb;
for (quxejb=36; quxejb > 0; quxejb--) {
continue;
} 
}
if (string("opqrtervqrzbydiolciffcxlodbmebdnokzyjlwtiogoijjgvqiavni") == string("opqrtervqrzbydiolciffcxlodbmebdnokzyjlwtiogoijjgvqiavni")) {
int zvjgnbca;
for (zvjgnbca=47; zvjgnbca > 0; zvjgnbca--) {
continue;
} 
}
if (true == true) {
int fmiqj;
for (fmiqj=61; fmiqj > 0; fmiqj--) {
continue;
} 
}
return true;
}

bool mxpvvcy::yevslwaddjzxrwr() {
int ifxcioufm = 970;
int qzxeqn = 3000;
bool xzxaz = true;
return false;
}

string mxpvvcy::qimidyqeudmusaoeh(double hcywnxkrug, bool glzmoucnkau, bool zliiqz, string zwdewxc, int bdshpqviz, string eaejmoljsuda, int edkyqea, double zolvd) {
double byaivgcfuoybri = 70401;
string imzxwzpuvuqayw = "zikhhtltpknkrpwfjrdulzozuxqxzfhtdhtnjqijexmn";
string hpzszlzuekrjvzg = "uotcgpdglavgagoxuoofhlpinjzeeuakcv";
bool zxvpzpsaqczeij = false;
int gkoggdbfsh = 3564;
int rcmuipwfoncf = 1570;
int jkruwhqg = 1412;
return string("yifowbvab");
}

bool mxpvvcy::rlikxadlfmekbjnarnekaigd(bool hdqziiubeqby, bool aysjilkm, double ambjxflokvnfrot, bool bqwxuxkht, double trrmscqba, double bzoeixhfcmnkls, int ooxvzoenqtlezq, int tcuojncx) {
double lvfqlydf = 7757;
int aaphmfpuaihemgt = 2604;
string kxocludfswdaz = "giavcmeteodwoijgvipjergazgpfqrqnzlhwvyfosnnorextpjpfjtnogwshgida";
if (7757 != 7757) {
int yccepye;
for (yccepye=9; yccepye > 0; yccepye--) {
continue;
} 
}
if (string("giavcmeteodwoijgvipjergazgpfqrqnzlhwvyfosnnorextpjpfjtnogwshgida") != string("giavcmeteodwoijgvipjergazgpfqrqnzlhwvyfosnnorextpjpfjtnogwshgida")) {
int xph;
for (xph=67; xph > 0; xph--) {
continue;
} 
}
if (string("giavcmeteodwoijgvipjergazgpfqrqnzlhwvyfosnnorextpjpfjtnogwshgida") != string("giavcmeteodwoijgvipjergazgpfqrqnzlhwvyfosnnorextpjpfjtnogwshgida")) {
int lodtuweiza;
for (lodtuweiza=30; lodtuweiza > 0; lodtuweiza--) {
continue;
} 
}
return false;
}

double mxpvvcy::awhxvflvskr(double cnwycxvozucxssd, int wcucjp, bool ohwhcenjknsql, bool ookmoxmqcdf, int vnfamcksxfs, bool xxwopw) {
double ududcy = 28862;
int wocfugycrmkkz = 1139;
double zzrmtrywmxbqdkw = 8167;
int aqvjbbocbjypjdo = 5825;
string kwafpm = "mcivtqohfmcdwmtxjqivgamjooob";
double vwntbzcrnm = 16179;
double styiuhfwut = 44129;
double qrptwx = 13400;
string tyrynuvliku = "sfutatqmzectvayysmugnihaodzcxsmeuplwlfsqumh";
if (1139 == 1139) {
int jzhksj;
for (jzhksj=73; jzhksj > 0; jzhksj--) {
continue;
} 
}
return 29791;
}

bool mxpvvcy::zmxuinhdwqsqzrebszmiiqeqa(int ucddraryab, bool yarncccm, double stapzjumkfbuyzu, int qxvrtl) {
double gorqoakmxlh = 21608;
double itkgpjgtjwum = 14022;
double sptfrnpj = 5852;
string mztrhicrzdnc = "pthpxgmrqvmfvazjtxpbgnwlexghcsdlhpzadrtpphwlrrdbamoopclkvl";
if (5852 == 5852) {
int ys;
for (ys=94; ys > 0; ys--) {
continue;
} 
}
if (string("pthpxgmrqvmfvazjtxpbgnwlexghcsdlhpzadrtpphwlrrdbamoopclkvl") != string("pthpxgmrqvmfvazjtxpbgnwlexghcsdlhpzadrtpphwlrrdbamoopclkvl")) {
int ahagyzz;
for (ahagyzz=60; ahagyzz > 0; ahagyzz--) {
continue;
} 
}
return false;
}

double mxpvvcy::vmnxnppkfmjsfkxau() {
string ksumugfnpvsz = "rsuisevfkbaxgycuyvxleqcfdgbjjttbgcmkokznappipkgj";
int owhuxfnzdl = 2548;
double lyyuvrtcduveb = 8398;
string ylczbjfumdkh = "wufgmnvyxlalzwcqvfdrwfgifdvidpkdfrojzgmsboswhsogsr";
double miwlwzbwv = 37197;
bool xrxyctdebwcwzx = false;
int gzyyggdahg = 380;
if (false != false) {
int sujfo;
for (sujfo=27; sujfo > 0; sujfo--) {
continue;
} 
}
if (string("wufgmnvyxlalzwcqvfdrwfgifdvidpkdfrojzgmsboswhsogsr") != string("wufgmnvyxlalzwcqvfdrwfgifdvidpkdfrojzgmsboswhsogsr")) {
int dtepwgtxi;
for (dtepwgtxi=17; dtepwgtxi > 0; dtepwgtxi--) {
continue;
} 
}
if (380 != 380) {
int zh;
for (zh=19; zh > 0; zh--) {
continue;
} 
}
return 80431;
}

int mxpvvcy::obcurkunhjfalnhoibm(string tffqtzio, double pcjzpajgz, bool epduzmopompajz, string aaldkm, bool fnefqrfdnbf, int odyjcute, bool qnldiinyla, int ajalgbhlhpn) {
int fyovo = 2891;
string qmdockugnh = "qkhypokanwnwgsmvnecuvilwzywxundocjyquhki";
bool tynpqcmd = true;
int ffkgb = 5341;
double otexmrcdqydwcph = 53282;
int luaszgriyv = 7363;
double awhnjzxbvgofqf = 27343;
bool qnuxns = false;
bool oczuzpuycyb = false;
if (7363 != 7363) {
int igyick;
for (igyick=12; igyick > 0; igyick--) {
continue;
} 
}
if (53282 != 53282) {
int qi;
for (qi=87; qi > 0; qi--) {
continue;
} 
}
if (5341 == 5341) {
int we;
for (we=0; we > 0; we--) {
continue;
} 
}
if (string("qkhypokanwnwgsmvnecuvilwzywxundocjyquhki") != string("qkhypokanwnwgsmvnecuvilwzywxundocjyquhki")) {
int orj;
for (orj=77; orj > 0; orj--) {
continue;
} 
}
if (false != false) {
int hnkavmu;
for (hnkavmu=15; hnkavmu > 0; hnkavmu--) {
continue;
} 
}
return 71073;
}

mxpvvcy::mxpvvcy() {
this->obcurkunhjfalnhoibm(string("ywpxixzlnjguijueb"), 18090, false, string("fpurgjslxfymvyfbattxxutyjqxgkwckhufjppkafkweatxegpjucykgvdhhznuqtvilipib"), true, 1899, true, 3525);
this->rlikxadlfmekbjnarnekaigd(true, false, 26648, false, 9726, 44295, 245, 5728);
this->awhxvflvskr(27790, 2734, false, true, 2654, true);
this->zmxuinhdwqsqzrebszmiiqeqa(2767, false, 11398, 2616);
this->vmnxnppkfmjsfkxau();
this->feqqymgdxpfwtuomadcxbg(string("cbvdikfycyhcpzukslvqdasuwdigiklpeqgyfxeyvidxxccliituwlvyolnrxiakfzqdhpbrdbeqjmcteptdwqvprttb"), 1320, 3036, string("auapstbolsaojfferofxomcsxumuaabjunanlgxarbhoqenrkcdwkllgsalgjqvrmduiussyty"), true, false, 3946, string("cgluphtilnpyknswfskimuiyyhtkgxdmakgjoqgplrhqblvthgnsgqmsjugpulmehqxunhgjlinpopwhzpxtqfumcs"), string("wghglsahaehhwakrvblgjberqddjreozjw"), false);
this->xofzjzbrugmapzrh(string("jdcsmezaljzw"), 10909, true, 65918, 4789);
this->oxqakjpsgbsmbtmbypvyugz();
this->bcjyjaitbwusbnkpcgku(71531, 7510, true, true, string("dtonoctlwfganwsgjwthdrytgcyloappysrviucmvsqwhqamormyyhfdclfo"), false);
this->uwrvnuikvigfgsx(6203, string("kywzywpbrahpsrdhblfrtuaqcoynnkxeshhybezj"), 32758, false, string("kflguwagjffnqglszdtyfyr"), string("snvwjjqnhbsckgvpnvxstqgutrfbw"));
this->yevslwaddjzxrwr();
this->qimidyqeudmusaoeh(4238, true, false, string("eyegkzenkeazcalouwomccg"), 220, string("jgsyezhdzglbpawbdaufxudelc"), 1112, 14610);
}
