//===========================================================================
/**
 * @file	game_init.c
 * @brief	ゲーム開始用初期設定
 * @author	tamada GAME FREAK Inc.
 * @date	2005.10.13
 *
 * 2006.06.17	debug_init.cからリネームした
 */
//===========================================================================
#include "common.h"

#include "fieldsys.h"
#include "savedata/savedata.h"
#include "field/field.h"
#include "field/game_init.h"

#include "ev_mapchange.h"

#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "savedata/mystatus.h"
#include "savedata/zukanwork.h"
#include "savedata/config.h"
#include "savedata/coin.h"
#include "field/situation.h"
#include "situation_local.h"

#include "itemtool/myitem.h"

#include "mapdefine.h"

#include "msgdata/msg_debugname.h"
#include "msgdata/msg.naix"
#include "system/msgdata.h"

#include "poketool/monsno.h"

#include "ev_pokemon.h"

#include "itemtool/itemsym.h"
#include "field/ug_itemtype.h"
#include "savedata/undergrounddata.h"

#include "field/union_beacon_tool.h"

#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "battle/wazano_def.h"
#include "battle/attr_def.h"
#include "zonedata.h"




//============================================================================================
//
//		ゲーム再開時のセーブデータ読み込み
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	ゲームデータ処理：コンティニュー
 * @param	savedata	セーブデータへのポインタ
 */
//------------------------------------------------------------------
void GameData_SetContinueData(int heapID, SAVEDATA * savedata)
{
	if (!SaveData_Load(savedata)) {
		OS_Printf("セーブデータがありません\n");
		OS_ResetSystem(0);
	}
}

//============================================================================================
//
//		ゲーム開始時のセーブデータ初期設定
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	ゲームデータ処理：新規ゲーム
 * @param	savedata	セーブデータへのポインタ
 */
//------------------------------------------------------------------
void GameData_SetNewGame(int heapID, SAVEDATA * savedata)
{
	MYSTATUS * my;

	SaveData_ClearData(savedata);

	//初期スタート位置設定
	LOCATION_GameInit(savedata);

	//お金だけセット
	my = SaveData_GetMyStatus(savedata);
	MyStatus_SetGold(my, 3000);

	//手持ちコインセット
	//COIN_Set(SaveData_GetMyCoin(savedata), 100);

	//メニュー「バッグ」
	SysFlag_BagSet( SaveData_GetEventWork(savedata) );
}


#ifdef	PM_DEBUG

//============================================================================================
//
//
//		ゲーム開始時のセーブデータ初期設定・デバッグ用
//
//
//============================================================================================
typedef struct {
	u16 monsno;
	u8 level;
}MINEPOKE;

static void Debug_MakeStartData(int heapID, SAVEDATA * savedata, int usr_id);

static void Debug_SetMyStatus(MYSTATUS * my, int usr_id);
static void Debug_PersonalSetting(int heapID, SAVEDATA * sv, int usr_id);

static void AddItemList(int heapID, MYITEM * myitem, const MINEITEM * addlist);
static void AddMonsList(int heapID, SAVEDATA * savedata, const MINEPOKE * addlist);

static int DebugPersonMax;

//------------------------------------------------------------------
/**
 * @brief	ゲームデータ処理：新規ゲーム（デバッグ）
 * @param	savedata	セーブデータへのポインタ
 */
//------------------------------------------------------------------
void GameData_SetDebugNewGame(int heapID, SAVEDATA * savedata, int usr_id)
{
	SaveData_ClearData(savedata);

	if (usr_id < 0 || usr_id >= DebugPersonMax){
		usr_id = Debug_GetMyID();
	}
	Debug_MakeStartData(heapID, savedata, usr_id);
}





//============================================================================================
//============================================================================================
static const MINEPOKE MinePokeList[] = {
	{MONSNO_GOUKAZARU,	99},
	{MONSNO_POTTYAMA,	99},
	{MONSNO_UOTTO,		99},
	{0,0},
};

//------------------------------------------------------------------
/**
 * @brief	デバッグ用：初期セーブデータ設定
 */
//------------------------------------------------------------------
void Debug_MakeStartData(int heapID, SAVEDATA * savedata, int usr_id)
{
	MYITEM * bag;
	MYSTATUS * my;
	ZUKAN_WORK * zw;
	CONFIG * cfg;

	//初期スタート位置設定
	//LOCATION_GameInit(savedata);
	LOCATION_GameInit_Debug(savedata);

	//適当に自分状態データ生成
	my = SaveData_GetMyStatus(savedata);
	Debug_SetMyStatus(my, usr_id);

	MyStatus_SetGold(my, 123456);

	//適当にプレイ時間をセット
	//PLAYTIME_Set(SaveData_GetPlayTime(savedata), 789, 56, 43);

	//デバッグで始めたときはMSG速度を最速にする
	cfg = SaveData_GetConfig(savedata);
	CONFIG_SetMsgSpeed(cfg, MSGSPEED_FAST);

	//手持ちアイテムを適当に生成
	bag = SaveData_GetMyItem(savedata);
	Debug_MyItem_MakeBag(bag, HEAPID_BASE_DEBUG);

	//手持ちポケモンを適当に生成
	AddMonsList(heapID, savedata, MinePokeList);

	//手持ちコインセット
	COIN_Set(SaveData_GetMyCoin(savedata), 500);

	//システムフラグセット
	{
		SITUATION *situ;
		PLAYER_SAVE_DATA *jikisave;

		situ = SaveData_GetSituation( savedata );
		jikisave = Situation_GetPlayerSaveData( situ );
		Player_SaveDataDashSet( jikisave, TRUE );

		//メニュー「図鑑」
		zw = SaveData_GetZukanWork( savedata );
		ZukanWork_SetZukanGetFlag( zw );

		//メニュー「バッグ」
		SysFlag_BagSet( SaveData_GetEventWork(savedata) );

		//メニュー「ポケモン」(注意！　最初のポケモンはフシギダネ固定！)
		SysWork_FirstPokeNoSet( SaveData_GetEventWork(savedata), MONSNO_HUSIGIDANE );
	}


	//個人ごとの設定呼び出し
	Debug_PersonalSetting(heapID, savedata, usr_id);
}

//============================================================================================
//============================================================================================
typedef void (*DEBUG_INIT_FUNC)(int, SAVEDATA *);
//------------------------------------------------------------------
/**
 */
//------------------------------------------------------------------
typedef struct {
	u16 sex;
	u16 name_id;
	DEBUG_INIT_FUNC init_func;
}DEBUG_PERSON;


static void DebugTamadaSetting(int heapID, SAVEDATA * sv);
static void DebugNoharaSetting(int heapID, SAVEDATA * sv);
static void DebugTadashiSetting(int heapID, SAVEDATA * sv);
static void DebugTetsujiSetting(int heapID, SAVEDATA * sv);
static void DebugNGNameSetting(int heapID, SAVEDATA * sv);
//------------------------------------------------------------------
//------------------------------------------------------------------
static const DEBUG_PERSON DebugPerson[] = {
	{ PM_MALE,	DEBUG_NAME_MASUDA, NULL },
	{ PM_MALE,	DEBUG_NAME_SUGIMORI, NULL },
	{ PM_MALE,	DEBUG_NAME_MORIMOTO, NULL },
	{ PM_MALE,	DEBUG_NAME_WATANABE, NULL },
	{ PM_MALE,	DEBUG_NAME_OHMORI, NULL },
	{ PM_MALE,	DEBUG_NAME_UNNO, NULL },
	{ PM_MALE,	DEBUG_NAME_ICHINOSE, NULL },
	{ PM_MALE,	DEBUG_NAME_MATSUSHIMA, NULL },
	{ PM_MALE,	DEBUG_NAME_SOGABE, NULL },
	{ PM_MALE,	DEBUG_NAME_FUJIWARA, NULL },
	{ PM_MALE,	DEBUG_NAME_TAMADA, DebugTamadaSetting },
	{ PM_MALE,	DEBUG_NAME_MORI, NULL },
	{ PM_MALE,	DEBUG_NAME_HIRONOBU, NULL },
	{ PM_MALE,	DEBUG_NAME_OOTA, NULL },
	{ PM_FEMALE,	DEBUG_NAME_EO, NULL },
	{ PM_MALE,	DEBUG_NAME_FUCHINO, NULL },
	{ PM_MALE,	DEBUG_NAME_TOYAMA, NULL },
	{ PM_FEMALE,	DEBUG_NAME_EMI, NULL },
	{ PM_MALE,	DEBUG_NAME_YAGI, NULL },
	{ PM_MALE,	DEBUG_NAME_OOMURA, NULL },
	{ PM_MALE,	DEBUG_NAME_TOMOMICHI, NULL },
	{ PM_MALE,	DEBUG_NAME_MATSUDA, NULL },
	{ PM_MALE,	DEBUG_NAME_KAGAYA, NULL },
	{ PM_MALE,	DEBUG_NAME_NOHARA, DebugNoharaSetting },
	{ PM_MALE,	DEBUG_NAME_TAYA, NULL },
	{ PM_MALE,	DEBUG_NAME_NAHI, NULL },
	{ PM_FEMALE,	DEBUG_NAME_IWASAWA, NULL },
	{ PM_MALE,	DEBUG_NAME_GOTO, NULL },
	{ PM_MALE,	DEBUG_NAME_SAITO, NULL },
	{ PM_MALE,	DEBUG_NAME_TOMOYA, NULL },
	{ PM_MALE,	DEBUG_NAME_OHNO, NULL },
	{ PM_MALE,	DEBUG_NAME_NISHINO, NULL },
	{ PM_MALE,	DEBUG_NAME_TETSUJI, DebugTetsujiSetting },
	{ PM_MALE,	DEBUG_NAME_SIMOYAMADA, NULL },
	{ PM_MALE,	DEBUG_NAME_TOMISAWA, NULL },
	{ PM_MALE,	DEBUG_NAME_KAWACHIMARU, NULL },
	{ PM_FEMALE,	DEBUG_NAME_SATO, NULL },
	{ PM_MALE,	DEBUG_NAME_TADASHI, DebugTadashiSetting },
	{ PM_MALE,	DEBUG_NAME_NAKATSUI, NULL },
	{ PM_MALE,	DEBUG_NAME_HIROKI, NULL },
	{ PM_MALE,	DEBUG_NAME_MATSUMIYA, NULL },
	{ PM_FEMALE,	DEBUG_NAME_JOHNNY, NULL },
	{ PM_MALE,	DEBUG_NAME_MASAFUMI, NULL },
	{ PM_FEMALE,	DEBUG_NAME_SAYA, NULL },
	{ PM_MALE,	DEBUG_NAME_DIAMOND, NULL },
	{ PM_FEMALE,	DEBUG_NAME_PEARL, NULL },
	{ PM_MALE,	DEBUG_NAME_NGNAME, DebugNGNameSetting },
	{ PM_FEMALE,	DEBUG_NAME_KAEDE,     NULL },
	{ PM_MALE,	DEBUG_NAME_PUKA,      NULL },
	{ PM_MALE,	DEBUG_NAME_MASARIN,   NULL },
	{ PM_FEMALE,	DEBUG_NAME_NORIRIN,   NULL },
	{ PM_MALE,	DEBUG_NAME_YOSINORI,  NULL },
	{ PM_FEMALE,	DEBUG_NAME_T_1,       NULL },
	{ PM_MALE,	DEBUG_NAME_TAKAFUMI,  NULL },
	{ PM_FEMALE,	DEBUG_NAME_TORECHEKO, NULL },
	{ PM_MALE,	DEBUG_NAME_NORIHIDE,  NULL },
	{ PM_FEMALE,	DEBUG_NAME_NORISTAR,  NULL },
	{ PM_MALE,	DEBUG_NAME_WWWWW,  NULL },



};
static int DebugPersonMax = NELEMS(DebugPerson);

//------------------------------------------------------------------
//------------------------------------------------------------------
int Debug_GetMyID(void)
{
#ifdef	DEBUG_ONLY_FOR_masuda
	return DEBUG_NAME_MASUDA;
#elif	defined(DEBUG_ONLY_FOR_sugimori)
	return DEBUG_NAME_SUGIMORI;
#elif	defined(DEBUG_ONLY_FOR_morimoto)
	return DEBUG_NAME_MORIMOTO;
#elif	defined(DEBUG_ONLY_FOR_watanabe)
	return DEBUG_NAME_WATANABE;
#elif	defined(DEBUG_ONLY_FOR_ohmori)
	return DEBUG_NAME_OHMORI;
#elif	defined(DEBUG_ONLY_FOR_unno)
	return DEBUG_NAME_UNNO;
#elif	defined(DEBUG_ONLY_FOR_ichinose)
	return DEBUG_NAME_ICHINOSE;
#elif	defined(DEBUG_ONLY_FOR_matsushima)
	return DEBUG_NAME_MATSUSHIMA;
#elif	defined(DEBUG_ONLY_FOR_sogabe)
	return DEBUG_NAME_SOGABE;
#elif	defined(DEBUG_ONLY_FOR_fujiwara)
	return DEBUG_NAME_FUJIWARA;
#elif	defined(DEBUG_ONLY_FOR_tamada)
	return DEBUG_NAME_TAMADA;
#elif	defined(DEBUG_ONLY_FOR_mori)
	return DEBUG_NAME_MORI;
#elif	defined(DEBUG_ONLY_FOR_yoshida)
	return DEBUG_NAME_HIRONOBU;
#elif	defined(DEBUG_ONLY_FOR_oota)
	return DEBUG_NAME_OOTA;
#elif	defined(DEBUG_ONLY_FOR_kanako_eo)
	return DEBUG_NAME_EO;
#elif	defined(DEBUG_ONLY_FOR_fuchino)
	return DEBUG_NAME_FUCHINO;
#elif	defined(DEBUG_ONLY_FOR_toyama)
	return DEBUG_NAME_TOYAMA;
#elif	defined(DEBUG_ONLY_FOR_emi_yoshida)
	return DEBUG_NAME_EMI;
#elif	defined(DEBUG_ONLY_FOR_hiroyuki_yagi)
	return DEBUG_NAME_YAGI;
#elif	defined(DEBUG_ONLY_FOR_yusuke_ohmura)
	return DEBUG_NAME_OOMURA;
#elif	defined(DEBUG_ONLY_FOR_tomo_ohta)
	return DEBUG_NAME_TOMOMICHI;
#elif	defined(DEBUG_ONLY_FOR_matsuda)
	return DEBUG_NAME_MATSUDA;
#elif	defined(DEBUG_ONLY_FOR_kagaya)
	return DEBUG_NAME_KAGAYA;
#elif	defined(DEBUG_ONLY_FOR_nohara)
	return DEBUG_NAME_NOHARA;
#elif	defined(DEBUG_ONLY_FOR_taya)
	return DEBUG_NAME_TAYA;
#elif	defined(DEBUG_ONLY_FOR_nakamura)
	return DEBUG_NAME_NAHI;
#elif	defined(DEBUG_ONLY_FOR_iwasawa)
	return DEBUG_NAME_IWASAWA;
#elif	defined(DEBUG_ONLY_FOR_gotou)
	return DEBUG_NAME_GOTO;
#elif	defined(DEBUG_ONLY_FOR_saitou)
	return DEBUG_NAME_SAITO;
#elif	defined(DEBUG_ONLY_FOR_tomoya_takahashi)
	return DEBUG_NAME_TOMOYA;
#elif	defined(DEBUG_ONLY_FOR_ohno)
	return DEBUG_NAME_OHNO + gf_mtRand() % 10; // 自分の名前以外を適当に
#elif	defined(DEBUG_ONLY_FOR_nishino)
	return DEBUG_NAME_NISHINO;
#elif	defined(DEBUG_ONLY_FOR_tetsuji_ohta)
	return DEBUG_NAME_TETSUJI;
#elif	defined(DEBUG_ONLY_FOR_shimoyamada)
	return DEBUG_NAME_SIMOYAMADA;
#elif	defined(DEBUG_ONLY_FOR_tomisawa)
	return DEBUG_NAME_TOMISAWA;
#elif	defined(DEBUG_ONLY_FOR_kawachimaru)
	return DEBUG_NAME_KAWACHIMARU;
#elif	defined(DEBUG_ONLY_FOR_satou)
	return DEBUG_NAME_SATO;
#elif	defined(DEBUG_ONLY_FOR_takahashi)
	return DEBUG_NAME_TADASHI;
#elif	defined(DEBUG_ONLY_FOR_nakatsui)
	return DEBUG_NAME_NAKATSUI;
#elif	defined(DEBUG_ONLY_FOR_fuchino)
	return DEBUG_NAME_HIROKI;
#elif	defined(DEBUG_ONLY_FOR_matsumiya)
	return DEBUG_NAME_MATSUMIYA;
#endif
	return DEBUG_NAME_DIAMOND;
}

//------------------------------------------------------------------
/**
 * @brief	個人毎のMyStatus初期化
 */
//------------------------------------------------------------------
static void Debug_SetMyStatus(MYSTATUS * my, int usr_id)
{
	STRBUF * strbuf;
	MSGDATA_MANAGER * msgman;

	MyStatus_SetMySex(my, DebugPerson[usr_id].sex);
	MyStatus_SetID(my, gf_mtRand());

	msgman = MSGMAN_Create(	MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_debugname_dat, HEAPID_BASE_DEBUG);
	strbuf = MSGMAN_AllocString(msgman, usr_id);
	MyStatus_SetMyNameFromString(my, strbuf);
	STRBUF_Delete(strbuf);
	MSGMAN_Delete(msgman);
}

//------------------------------------------------------------------
/**
 * @brief	個人毎の初期設定呼び出し
 */
//------------------------------------------------------------------
static void Debug_PersonalSetting(int heapID, SAVEDATA * sv, int usr_id)
{
	DEBUG_INIT_FUNC func = DebugPerson[usr_id].init_func;
	if (func != NULL) {
		func(heapID, sv);
	}
}


//============================================================================================
//============================================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
static const MINEITEM Items[] = {
//	{ITEM_ZITENSYA, 1},
//	{ITEM_TAUNMAPPU, 1},
//	{ITEM_MONSUTAABOORU, 99},
	{ITEM_KIZUGUSURI, 1},
};

//------------------------------------------------------------------
//------------------------------------------------------------------
static void AddItemList(int heapID, MYITEM * myitem, const MINEITEM * addlist)
{
	int i; 
	for (i = 0; addlist[i].id != 0; i++) {
		MyItem_AddItem(myitem, addlist[i].id, addlist[i].no, heapID);
	}
}

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
static void AddMonsList(int heapID, SAVEDATA * savedata, const MINEPOKE * addlist)
{
	int i;
	LOCATION_WORK * loc;
	int place_id;
	loc = Situation_GetNowLocation(SaveData_GetSituation(savedata));
	place_id = ZoneData_GetPlaceNameID(loc->zone_id);
	for (i = 0; i < TEMOTI_POKEMAX && addlist[i].monsno != 0; i++) {
		EvPoke_Add(HEAPID_BASE_DEBUG, savedata, addlist[i].monsno, addlist[i].level, 0,
				place_id, GROUND_ID_FLOOR);
	}
}


//============================================================================================
//============================================================================================
//------------------------------------------------------------------
///	テツジー用初期化ルーチン
//------------------------------------------------------------------
static void DebugTetsujiSetting(int heapID, SAVEDATA * sv)
{
	static const MINEPOKE plist[] = {
		{MONSNO_GOUKAZARU, 50},
		{MONSNO_MORIGAME, 50},
		{MONSNO_ENPERIO, 50},
		{MONSNO_RUKARIO, 50},
		{MONSNO_GENGAA, 50},
		{MONSNO_METAGUROSU, 50},
	};
	POKEPARTY * temoti = SaveData_GetTemotiPokemon(sv);
	PokeParty_InitWork(temoti);	//手持ち初期化

	AddMonsList(heapID, sv, plist);
}
//------------------------------------------------------------------
///	玉田用初期化ルーチン
//------------------------------------------------------------------
static void DebugTamadaSetting(int heapID, SAVEDATA * sv)
{
	static const MINEPOKE plist[] = {
		{MONSNO_NASSII, 99},
		{MONSNO_MAGUMARASI, 99},
		{MONSNO_RAGURAAZI, 99},
		{0,0},
	};
	POKEPARTY * temoti = SaveData_GetTemotiPokemon(sv);
	PokeParty_InitWork(temoti);	//手持ち初期化

	AddMonsList(heapID, sv, plist);

	EvPoke_ChangeWaza(temoti, 0, 0, WAZANO_IAIGIRI);
	EvPoke_ChangeWaza(temoti, 0, 1, WAZANO_IWAKUDAKI);
	EvPoke_ChangeWaza(temoti, 0, 2, WAZANO_NAMINORI);
	EvPoke_ChangeWaza(temoti, 0, 3, WAZANO_ROKKUKURAIMU);
	EvPoke_ChangeWaza(temoti, 1, 0, WAZANO_KAIRIKI);
	EvPoke_ChangeWaza(temoti, 1, 1, WAZANO_SORAWOTOBU);
	EvPoke_ChangeWaza(temoti, 1, 2, WAZANO_KIRIBARAI);
	EvPoke_ChangeWaza(temoti, 1, 3, WAZANO_TAKINOBORI);
	EvPoke_ChangeWaza(temoti, 2, 0, WAZANO_HURASSYU);
	EvPoke_ChangeWaza(temoti, 2, 1, WAZANO_ANAWOHORU);
	EvPoke_ChangeWaza(temoti, 2, 2, WAZANO_TEREPOOTO);
	EvPoke_ChangeWaza(temoti, 2, 3, WAZANO_TAMAGOUMI);
}

//------------------------------------------------------------------
///	野原用初期化ルーチン
//------------------------------------------------------------------
static void DebugNoharaSetting(int heapID, SAVEDATA * sv)
{
	LOCATION_WORK * loc;
	int place_id;
	POKEPARTY * temoti = SaveData_GetTemotiPokemon(sv);
	loc = Situation_GetNowLocation(SaveData_GetSituation(sv));
	place_id = ZoneData_GetPlaceNameID(loc->zone_id);
	PokeParty_InitWork(temoti);	//手持ち初期化

	EvPoke_Add(heapID, sv, MONSNO_KAIRIKII, 99,
			ITEM_KURABONOMI, place_id, GROUND_ID_FLOOR);
	EvPoke_Add(heapID, sv, MONSNO_PERAPPU, 2,
			ITEM_KURABONOMI, place_id, GROUND_ID_FLOOR);

	EvPoke_ChangeWaza(temoti, 1, 0, WAZANO_OSYABERI);
}

//------------------------------------------------------------------
///	忠士用初期化ルーチン
//------------------------------------------------------------------
static void DebugTadashiSetting(int heapID, SAVEDATA * sv)
{
	LOCATION_WORK * loc;
	int place_id;
	POKEPARTY * temoti = SaveData_GetTemotiPokemon(sv);
	PokeParty_InitWork(temoti);	//手持ち初期化
	loc = Situation_GetNowLocation(SaveData_GetSituation(sv));
	place_id = ZoneData_GetPlaceNameID(loc->zone_id);
	EvPoke_Add(HEAPID_BASE_DEBUG, sv, MONSNO_TATETOPUSU, 2,
			ITEM_KURABONOMI, place_id, GROUND_ID_FLOOR);
}

//------------------------------------------------------------------
//------------------------------------------------------------------
static void DebugNGNameSetting(int heapID, SAVEDATA * sv)
{
	MYITEM * myitem = SaveData_GetMyItem(sv);
	POKEPARTY * temoti = SaveData_GetTemotiPokemon(sv);
	LOCATION_WORK * loc;
	int place_id;
	MyItem_Init(myitem);
	PokeParty_InitWork(temoti);	//手持ち初期化
	loc = Situation_GetNowLocation(SaveData_GetSituation(sv));
	place_id = ZoneData_GetPlaceNameID(loc->zone_id);
	EvPoke_Add(HEAPID_BASE_DEBUG, sv, MONSNO_TATETOPUSU, 2, 0, place_id, GROUND_ID_FLOOR);
	EvPoke_Add(HEAPID_BASE_DEBUG, sv, MONSNO_PERAPPU, 2, 0, place_id, GROUND_ID_FLOOR);
}


#endif	//	PM_DEBUG
