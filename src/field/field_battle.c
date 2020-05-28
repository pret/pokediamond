//============================================================================================
/**
 * @file	field_battle.c
 * @brief	フィールド戦闘パラメータなど
 * @date	2005.12.18
 * @author	tamada	
 *
 * 汎用的と思われるので、いずれはbattle/battle_param.cに移行したい。
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"

#include "field_battle.h"


#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/status_rcv.h"
#include "savedata/mystatus.h"
#include "itemtool/myitem.h"
#include "itemtool/itemsym.h"
#include "savedata/zukanwork.h"
#include "savedata/savedata.h"	//SaveData_GetBoxData
#include "savedata/perapvoice.h"
#include "savedata/config.h"
#include "savedata/wifihistory.h"

#include "situation_local.h"	//Situation_GetSafariBallCount
#include "application/p_status.h" //PokeStatus_ContestFlagGet
#include "communication/communication.h"

#include "zonedata.h"			//ZoneData_GetBattleBGID
#include "battle/attr_def.h"
#include "mapdefine.h"
#include "field/weather_no.h"
#include "field/syswork.h"
#include "field/sysflag.h"

#include "field/union_beacon_tool.h"

#include "map_attr.h"
#include "ev_time.h"

#include "gflib/strbuf_family.h"
#include "msgdata/msg.naix"

#include "system/pm_debug_wifi.h"

static void BattleParam_SetBgGroundID(BATTLE_PARAM * bp, const FIELDSYS_WORK * fsys);
void	BattleParam_TrainerDataMake(BATTLE_PARAM *bp);

//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータの生成処理
 * @param	heapID			使用するヒープの指定
 * @param	fight_type		戦闘タイプの指定（battle/battle_param.h参照）
 * @return	BATTLE_PARAM	生成した戦闘パラメータへのポインタ
 */
//-----------------------------------------------------------------------------
BATTLE_PARAM * BattleParam_Create(int heapID, u32 fight_type)
{
	int i;
	BATTLE_PARAM *bp;

	bp = sys_AllocMemory(heapID, sizeof(BATTLE_PARAM));
	MI_CpuClear8(bp,sizeof(BATTLE_PARAM));
	
	bp->fight_type = fight_type;
	bp->battle_status_flag = 0;
	bp->win_lose_flag = 0;
	for (i = 0; i < CLIENT_MAX; i++) {
		bp->trainer_id[i] = 0;
		MI_CpuClear32(&bp->trainer_data[i], sizeof(TRAINER_DATA));
	}
	bp->bg_id = BG_ID_BASIC;		//基本背景指定
	bp->ground_id = GROUND_ID_ALL;	//基本地面指定
	bp->place_id = 0;					//初期化、「なまえのないばしょ」
	bp->time_zone = TIMEZONE_MORNING;	//初期化、実際はこの後で状況に応じて設定
	bp->shinka_place_mode = SHINKA_NONE;	//初期化、実際は場所情報から設定
	bp->contest_see_flag = TRUE;			//初期化、実際はコンテスト参加後にTRUEと設定される
	bp->mizuki_flag = TRUE;				//初期化、実際はミズキにあった後にTRUEと設定される
	bp->weather = WEATHER_SYS_SUNNY;
	for (i = 0; i < CLIENT_MAX; i++) {
		bp->poke_party[i] = PokeParty_AllocPartyWork(heapID);
	}
	for (i = 0; i < CLIENT_MAX; i++) {
		bp->my_status[i] = MyStatus_AllocWork(heapID);
	}
	for (i = 0; i < CLIENT_MAX; i++) {
		bp->poke_voice[i] = PERAPVOICE_AllocWork(heapID);
	}
	bp->my_item = MyItem_AllocWork(heapID);

	bp->zw = ZukanWork_AllocWork(heapID);

	bp->config = CONFIG_AllocWork(heapID);
	
	bp->TVWatchBattleWork = TVWatchBattleWork_Create(heapID);

	bp->bag_cursor = NULL;

	bp->safari_ball = 0;

	bp->wifihistory = NULL;

	bp->record = NULL;

	bp->fnote_data = NULL;

	bp->regulation_flag = 0;

	MI_CpuClear8(&(bp->btr),sizeof(BATTLE_TOWER_RECORD));
	return bp;
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータの生成処理(サファリ用)
 * @param	heapID			使用するヒープの指定
 * @param	ball_num		サファリボールの数
 * @return	BATTLE_PARAM	生成した戦闘パラメータへのポインタ
 */
//-----------------------------------------------------------------------------
BATTLE_PARAM * BattleParam_CreateForSafari(int heapID, int ball_num)
{
	BATTLE_PARAM * bp;
	bp = BattleParam_Create(heapID, FIGHT_TYPE_SAFARI);

	bp->safari_ball = ball_num;		//サファリボール

	return bp;
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータの生成処理(サファリ用)
 * @param	heapID			使用するヒープの指定
 * @param	ball_num		サファリボールの数
 * @return	BATTLE_PARAM	生成した戦闘パラメータへのポインタ
 */
//-----------------------------------------------------------------------------
BATTLE_PARAM * BattleParam_CreateForPokePark(int heapID, int ball_num)
{
	BATTLE_PARAM * bp;
	bp = BattleParam_Create(heapID, FIGHT_TYPE_POKE_PARK);

	bp->safari_ball = ball_num;		//サファリボール

	return bp;
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータの生成処理(捕獲デモ用)
 * @param	heapID			使用するヒープの指定
 * @param	fsys	ゲーム制御ワークへのポインタ
 *
 * @return	BATTLE_PARAM	生成した戦闘パラメータへのポインタ
 */
//-----------------------------------------------------------------------------
BATTLE_PARAM * BattleParam_CreateForGetDemo(int heapID, const FIELDSYS_WORK * fsys)
{
	MYSTATUS		*my=SaveData_GetMyStatus(fsys->savedata);
	CONFIG			*cfg=SaveData_GetConfig(fsys->savedata);
	MSGDATA_MANAGER	*man;
	STRBUF			*msg;
	BATTLE_PARAM	*bp;
	POKEMON_PARAM	*pp;

	bp = BattleParam_Create(heapID, FIGHT_TYPE_GET_DEMO);

	//サポートの名前をセット
	man=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_supportname_dat,heapID);
	msg=STRBUF_Create(BUFLEN_PERSON_NAME,heapID);
	MSGMAN_GetString(man,MyStatus_GetMySex(my)^1,msg);
	MyStatus_SetMyName(bp->my_status[CLIENT_NO_MINE],STRBUF_GetStringCodePointer(msg));
	STRBUF_Delete(msg);
	MSGMAN_Delete(man);

	//自分とは反対の性別をセット
	MyStatus_SetMySex(bp->my_status[CLIENT_NO_MINE],MyStatus_GetMySex(my)^1);

    BattleParam_SetBgGroundID(bp, fsys);
	CONFIG_Copy(cfg, bp->config);
	bp->time_zone = EVTIME_GetTimeZone(fsys);

	//所持道具にモンスターボールをセット
	MyItem_AddItem(bp->my_item, ITEM_MONSUTAABOORU, 20, heapID );

	//手持ちポケモンデータを生成
	pp=PokemonParam_AllocWork(heapID);
	PokeParaSet(pp,SysWork_SupportPokeNoGet(SaveData_GetEventWork(fsys->savedata)),5,POW_RND,RND_NO_SET,0,ID_NO_RARE,0);
	PokeParty_Add(bp->poke_party[POKEPARTY_MINE],pp);

	PokeParaSet(pp,MONSNO_BIIBAA,2,POW_RND,RND_NO_SET,0,ID_NO_RARE,0);
	PokeParty_Add(bp->poke_party[POKEPARTY_ENEMY],pp);

	sys_FreeMemoryEz(pp);

	//ボックスデータは大きすぎるのでコピーしない
	bp->box = SaveData_GetBoxData(fsys->savedata);

	//バッグカーソルセット
	bp->bag_cursor = fsys->bag_cursor;

	//カウントアップレコード
	bp->record = SaveData_GetRecord(fsys->savedata);

	//冒険ノート
	bp->fnote_data = fsys->fnote;

	//ゾーンID
	bp->zone_id = fsys->location->zone_id;

	//トレーナーデータ生成（自分側）
	BattleParam_TrainerDataMake(bp);

	return bp;
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータの削除処理
 * @param	bp		生成した戦闘パラメータへのポインタ
 */
//-----------------------------------------------------------------------------
void BattleParam_Delete(BATTLE_PARAM * bp)
{
	int i;
	for (i = 0; i < CLIENT_MAX; i++) {
		GF_ASSERT(bp->poke_party[i] != NULL);
		sys_FreeMemoryEz(bp->poke_party[i]);
	}
	for (i = 0; i < CLIENT_MAX; i++) {
		GF_ASSERT(bp->my_status[i] != NULL);
		sys_FreeMemoryEz(bp->my_status[i]);
	}
	for (i = 0; i < CLIENT_MAX; i++) {
		GF_ASSERT(bp->poke_voice[i] != NULL);
		sys_FreeMemoryEz(bp->poke_voice[i]);
	}
	sys_FreeMemoryEz(bp->my_item);
	sys_FreeMemoryEz(bp->zw);
	sys_FreeMemoryEz(bp->config);
	TVWatchBattleWork_Delete(bp->TVWatchBattleWork);

	sys_FreeMemoryEz(bp);
}


//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータセット：ポケモンを加える
 * @param	bp			生成した戦闘パラメータへのポインタ
 * @param	pp			POKEMON_PARAMへのポインタ
 * @param	client_no	クライアント指定（自分、相手など）
 */
//-----------------------------------------------------------------------------
void BattleParam_AddPokemon(BATTLE_PARAM * bp, POKEMON_PARAM * pp, int client_no)
{
	int result;
	GF_ASSERT(client_no < CLIENT_MAX);
	result = PokeParty_Add(bp->poke_party[client_no], pp);
	GF_ASSERT_MSG(result, "battle_param[%d] is full\n", client_no);
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータセット：POKEPARTYのセット
 * @param	bp			生成した戦闘パラメータへのポインタ
 * @param	my			MYSTATUSへのポインタ
 * @param	client_no	クライアント指定（自分、相手など）
 */
//-----------------------------------------------------------------------------
void BattleParam_SetPokeParty(BATTLE_PARAM * bp, const POKEPARTY * party, int client_no)
{
	GF_ASSERT(client_no < CLIENT_MAX);
	PokeParty_Copy(party, bp->poke_party[client_no]);
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータセット：MYSTATUSのセット
 * @param	bp			生成した戦闘パラメータへのポインタ
 * @param	my			MYSTATUSへのポインタ
 * @param	client_no	クライアント指定（自分、相手など）
 */
//-----------------------------------------------------------------------------
void BattleParam_SetMyStatus(BATTLE_PARAM * bp, const MYSTATUS * my, int client_no)
{
	GF_ASSERT(client_no < CLIENT_MAX);
	MyStatus_Copy(my, bp->my_status[client_no]);
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータセット：PERAPVOICEのセット
 * @param	bp			生成した戦闘パラメータへのポインタ
 * @param	pv			PERAPVOICEへのポインタ
 * @param	client_no	クライアント指定（自分、相手など）
 */
//-----------------------------------------------------------------------------
void BattleParam_SetPokeVoice(BATTLE_PARAM * bp, const PERAPVOICE * pv, int client_no)
{
	PERAPVOICE_CopyData(bp->poke_voice[client_no], pv);
}

//============================================================================================
//============================================================================================
/**
 *	@brief	戦闘パラメータの収集コア(フィールド)
 */
void BattleParam_SetParamByGameDataCore(BATTLE_PARAM* bp,const FIELDSYS_WORK* fsys)
{
	MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);
	POKEPARTY * temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	MYITEM * item = SaveData_GetMyItem(fsys->savedata);
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
	PERAPVOICE * pv = SaveData_GetPerapVoice(fsys->savedata);
	CONFIG * cfg = SaveData_GetConfig(fsys->savedata);
	SITUATION * sit = SaveData_GetSituation(fsys->savedata);

    BattleParam_SetBgGroundID(bp, fsys);
	BattleParam_SetMyStatus(bp, my, POKEPARTY_MINE);
	BattleParam_SetPokeParty(bp, temoti, POKEPARTY_MINE);
	MyItem_Copy(item, bp->my_item);
	ZukanWork_Copy(zw, bp->zw);
	CONFIG_Copy(cfg, bp->config);
	BattleParam_SetPokeVoice(bp, pv, POKEPARTY_MINE);
	//ボックスデータは大きすぎるのでコピーしない
	bp->box = SaveData_GetBoxData(fsys->savedata);

	bp->place_id = ZoneData_GetPlaceNameID(fsys->location->zone_id);
	bp->time_zone = EVTIME_GetTimeZone(fsys);
	bp->shinka_place_mode = ZoneData_GetShinkaPlaceID(fsys->location->zone_id);
	bp->contest_see_flag = PokeStatus_ContestFlagGet(fsys->savedata);
	bp->mizuki_flag = SysFlag_MizukiCheck(SaveData_GetEventWork(fsys->savedata));
	bp->weather = Situation_GetWeatherID(sit);

	bp->bag_cursor = fsys->bag_cursor;

	bp->poketch_data = SaveData_GetPoketchData(fsys->savedata);

	bp->wifihistory = SaveData_GetWifiHistory(fsys->savedata);

	bp->record = SaveData_GetRecord(fsys->savedata);

	bp->fnote_data = fsys->fnote;

	bp->friendlist = SaveData_GetFriendList( fsys->savedata );

	bp->zone_id = fsys->location->zone_id;
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータのセット（フィールド）
 * @param	bp		戦闘パラメータへのポインタ
 * @param	fsys	ゲーム制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void BattleParam_SetParamByGameData(BATTLE_PARAM * bp, const FIELDSYS_WORK * fsys)
{
	BattleParam_SetParamByGameDataCore(bp,fsys);

	//トレーナーデータ生成（自分側）
	BattleParam_TrainerDataMake(bp);
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータのセット（WIFI）
 * @param	bp		戦闘パラメータへのポインタ
 * @param	fsys	ゲーム制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void BattleParam_SetParamByWiFiGameData(BATTLE_PARAM * bp, const FIELDSYS_WORK * fsys, int lvLimit)
{
    int i;
    u32 param;
	MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);
	POKEPARTY * temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	MYITEM * item = SaveData_GetMyItem(fsys->savedata);
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
	PERAPVOICE * pv = SaveData_GetPerapVoice(fsys->savedata);
	CONFIG * cfg = SaveData_GetConfig(fsys->savedata);
	POKEMON_PARAM *pp;

	bp->bg_id = BG_ID_ROOM_A;		//基本背景指定 
	bp->ground_id = GROUND_ID_FLOOR;
	BattleParam_SetMyStatus(bp, my, POKEPARTY_MINE);

    //ポケモンデータセット
	pp = PokemonParam_AllocWork(HEAPID_WORLD);
	//選んだ手持ちポケモンをセット

    PokeParty_Init(bp->poke_party[POKEPARTY_MINE],PokeParty_GetPokeCount(temoti));
	for(i = 0;i < PokeParty_GetPokeCount(temoti);i++){
		PokeCopyPPtoPP(PokeParty_GetMemberPointer(temoti, i),pp);
		//レベル調整
		if((PokeParaGet(pp,ID_PARA_level,NULL) != lvLimit) && (lvLimit != 0)){
			param = PokeLevelExpGet(PokeParaGet(pp,ID_PARA_monsno,NULL), lvLimit);

			PokeParaPut(pp,ID_PARA_exp,&param);
			PokeParaCalc(pp);
		}
		BattleParam_AddPokemon(bp,pp,POKEPARTY_MINE);
	}
    sys_FreeMemoryEz(pp);
    MyItem_Copy(item, bp->my_item);
	ZukanWork_Copy(zw, bp->zw);
	CONFIG_Copy(cfg, bp->config);
	BattleParam_SetPokeVoice(bp, pv, POKEPARTY_MINE);
	//ずかんデータは大きすぎるのでコピーしない
	bp->box = SaveData_GetBoxData(fsys->savedata);
	bp->time_zone = EVTIME_GetTimeZone(fsys);
	bp->bag_cursor = fsys->bag_cursor;
	bp->poketch_data = SaveData_GetPoketchData(fsys->savedata);
	bp->wifihistory = SaveData_GetWifiHistory(fsys->savedata);
	bp->record = SaveData_GetRecord(fsys->savedata);
	bp->fnote_data = fsys->fnote;
	bp->friendlist = SaveData_GetFriendList(fsys->savedata);
	bp->zone_id = fsys->location->zone_id;

	//トレーナーデータ生成（自分側）
	BattleParam_TrainerDataMake(bp);

#if defined(_WIFI_DEBUG_TUUSHIN)
    bp->battle_status_flag |= BATTLE_STATUS_FLAG_AUTO_BATTLE;
#endif
}


//------------------------------------------------------------------
/**
 * @brief	戦闘パラメータのセット（IFI）
 *
 * @param   bp		
 * @param   fsys		
 * @param   party		
 * @param   setlist		
 *
 */
//------------------------------------------------------------------
void BattleParam_SetCommBattle(BATTLE_PARAM* bp, const FIELDSYS_WORK* fsys, const POKEPARTY* party, const u8* setlist)
{
	MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);
	MYITEM * item = SaveData_GetMyItem(fsys->savedata);
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
	PERAPVOICE * pv = SaveData_GetPerapVoice(fsys->savedata);
	CONFIG * cfg = SaveData_GetConfig(fsys->savedata);
    const REGULATION* pReg = fsys->regulation;
    int type, i, j;
	POKEMON_PARAM *pp;
	//バトルパラメータのアロケーションとポケモンパーティの初期化

	bp->bg_id = BG_ID_ROOM_A;			//基本背景指定
	bp->ground_id = GROUND_ID_FLOOR;	//基本地面指定

	BattleParam_SetMyStatus(bp, my, POKEPARTY_MINE);

	if( setlist == NULL )
	{
		BattleParam_SetPokeParty(bp, party, POKEPARTY_MINE);
	}
	else
	{
		int num;
	    num = 0;
	    for(j = 0;j < POKEMON_TEMOTI_MAX;j++){
	        if(setlist[j] != 0){
	            num++;  // 数を確認
	        }
	    }
	    if(num == 0){
	        BattleParam_SetPokeParty(bp, party, POKEPARTY_MINE);
	    }
	    else{
	        pp = PokemonParam_AllocWork(HEAPID_WORLD);
	        PokeParty_Init(bp->poke_party[POKEPARTY_MINE], num);
	        for(j = 0;j < num; j++){
	            PokeCopyPPtoPP( PokeParty_GetMemberPointer(party, setlist[j]-1), pp );
	            OS_TPrintf("手持ち %d\n",setlist[j] );
	            BattleParam_AddPokemon(bp,pp,POKEPARTY_MINE);
	        }
	        sys_FreeMemoryEz(pp);
		}
    }
    if(pReg){
        if(Regulation_GetParam(pReg,REGULATION_FIXDAMAGE)){
            bp->regulation_flag=TRUE;
        }
    }
    MyItem_Copy(item, bp->my_item);
    ZukanWork_Copy(zw, bp->zw);
	CONFIG_Copy(cfg, bp->config);
	BattleParam_SetPokeVoice(bp, pv, POKEPARTY_MINE);
	//ボックスデータは大きすぎるのでコピーしない
	bp->box = SaveData_GetBoxData(fsys->savedata);
	bp->time_zone = EVTIME_GetTimeZone(fsys);
	bp->bag_cursor = fsys->bag_cursor;
	bp->wifihistory = SaveData_GetWifiHistory(fsys->savedata);
	bp->record = SaveData_GetRecord(fsys->savedata);
	bp->fnote_data = fsys->fnote;
	bp->zone_id = fsys->location->zone_id;
	bp->friendlist = SaveData_GetFriendList(fsys->savedata);


    if(CommLocalIsUnionGroup(CommStateGetServiceNo())){
        int type = MyStatus_GetTrainerView(my);
        int sex = MyStatus_GetMySex(my);
        bp->trainer_data[CLIENT_NO_MINE].tr_type = UnionView_GetTrainerInfo( sex, type, UNIONVIEW_TRTYPE);
        PM_strcpy(&bp->trainer_data[CLIENT_NO_MINE].name[0],MyStatus_GetMyName(bp->my_status[CLIENT_NO_MINE]));
        bp->trainer_data[CLIENT_NO_MINE2]=bp->trainer_data[CLIENT_NO_MINE];
    }
    else{
        //トレーナーデータ生成（自分側）
        BattleParam_TrainerDataMake(bp);
    }
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータのセット 手持ちポケモン配列渡し
 * @param	bp		戦闘パラメータへのポインタ
 * @param	fsys	ゲーム制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void BattleParam_SetTemotiListParamGameData(BATTLE_PARAM* bp, const FIELDSYS_WORK* fsys, const u8* temotiList)
{
	BattleParam_SetCommBattle( bp, fsys, SaveData_GetTemotiPokemon(fsys->savedata), temotiList );
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータをゲームデータに反映
 * @param	bp		戦闘パラメータへのポインタ
 * @param	fsys	ゲーム制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void BattleParam_UpdateGameData(const BATTLE_PARAM * bp, FIELDSYS_WORK * fsys)
{
	MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);
	POKEPARTY * temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	MYITEM * item = SaveData_GetMyItem(fsys->savedata);
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
	u16 * ball_count = Situation_GetSafariBallCount(SaveData_GetSituation(fsys->savedata));

	MyStatus_Copy(bp->my_status[POKEPARTY_MINE], my);
	PokeParty_Copy(bp->poke_party[POKEPARTY_MINE], temoti);
	MyItem_Copy(bp->my_item, item);
	ZukanWork_Copy(bp->zw, zw);
	//サファリボールカウント反映
	*ball_count = bp->safari_ball;
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘パラメータをゲームデータに反映（仮想対戦用）
 * @param	bp		戦闘パラメータへのポインタ
 * @param	fsys	ゲーム制御ワークへのポインタ
 *
 * バトルタワー、通信対戦などポケモンの経験値やお金の増減を伴わない場合の
 * アップデート処理
 */
//-----------------------------------------------------------------------------
void BattleParam_UpdateGameDataOfVirtualBattle(const BATTLE_PARAM * bp, FIELDSYS_WORK * fsys)
{
	MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);
	POKEPARTY * temoti = SaveData_GetTemotiPokemon(fsys->savedata);
	MYITEM * item = SaveData_GetMyItem(fsys->savedata);
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);

//	MyStatus_Copy(bp->my_status[POKEPARTY_MINE], my);
//	PokeParty_Copy(bp->poke_party[POKEPARTY_MINE], temoti);
//	MyItem_Copy(bp->my_item, item);
	ZukanWork_Copy(bp->zw, zw);
	//↑ずかんだけアップデート
}

//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	戦闘地形のID取得
 * @param	fsys	ゲーム制御ワークへのポインタ
 * @param	bg_id	戦闘背景のID
 */
//-----------------------------------------------------------------------------
static int GetGroundID(const FIELDSYS_WORK * fsys, int bg_id)
{
	MATR matr = GetAttributeLSB(fsys, fsys->location->grid_x, fsys->location->grid_z);
	static const BasicGroundTable[] = {
		GROUND_ID_GRAVEL,
		GROUND_ID_WATER,
		GROUND_ID_FLOOR,
		GROUND_ID_LAWN,
		GROUND_ID_ROCK,
		GROUND_ID_SNOW,
		GROUND_ID_FLOOR,
		GROUND_ID_FLOOR,
		GROUND_ID_FLOOR,
		GROUND_ID_CAVE,
		GROUND_ID_CAVE,
		GROUND_ID_CAVE,
	};

	if (MATR_IsIce(matr)) {
		return GROUND_ID_ICE;
	} else if (MATR_IsGrass(matr) || MATR_IsLongGrass(matr)) {
		return GROUND_ID_LAWN;
	} else if (MATR_IsSand(matr)) {
		return GROUND_ID_SANDS;
	} else if (MATR_IsSnow(matr)) {
		return GROUND_ID_SNOW;
	} else if (MATR_IsSwamp(matr) || MATR_IsSwampGrass(matr)) {
		return GROUND_ID_BOG;
	} else if (MATR_IsDunFloor(matr)) {
		return GROUND_ID_CAVE;
	}

	if (MATR_IsWater(matr)) {
		//上記条件に当てはまらず、水であれば水地形として返す
		return GROUND_ID_WATER;
	}
	if (bg_id < NELEMS(BasicGroundTable)) {
		//どのアトリビュートにも当てはまらない場合は背景ごとのデフォルト地形を返す
		return BasicGroundTable[bg_id];
	}
	GF_ASSERT(0);
	//ありえないはずだが、誤動作を避けるために値を返しておく
	return GROUND_ID_ALL;
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘背景＆地形のセット
 * @param	bp		戦闘パラメータへのポインタ
 * @param	fsys	ゲーム制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
static void BattleParam_SetBgGroundID(BATTLE_PARAM * bp, const FIELDSYS_WORK * fsys)
{
	PLAYER_SAVE_DATA * jikisave = Situation_GetPlayerSaveData(SaveData_GetSituation(fsys->savedata));
	bp->bg_id = ZoneData_GetBattleBGID(fsys->location->zone_id);
	if (jikisave->form == HERO_FORM_SWIM) {
		//自機がなみのり形態のとき、戦闘背景はBG_ID_SEA固定
		bp->bg_id = BG_ID_SEA;
	}
	bp->ground_id = GetGroundID(fsys, bp->bg_id);
}

//-----------------------------------------------------------------------------
/**
 * @brief	つりの場合のパラメータ付加
 * @param	bp		戦闘パラメータへのポインタ
 *
 * 地形セットを行っている
 */
//-----------------------------------------------------------------------------
void BattleParam_SetFisingParam(BATTLE_PARAM * bp)
{
	bp->ground_id = GROUND_ID_WATER;
}

//-----------------------------------------------------------------------------
/**
 * @brief	戦闘結果を単純な勝敗に変換
 * @param	result		BATTLE_PARAM::win_lose_flag
 * @retval	TRUE		勝利
 * @retval	FALSE		敗北
 */
//-----------------------------------------------------------------------------
BOOL BattleParam_IsWinResult(u32 result)
{
	switch (result) {
	case FIGHT_LOSE:
	case FIGHT_DRAW:
		return FALSE; //負けたときの処理
	default:
		return TRUE;	 //勝ったときの処理
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	隠しポケモンとの戦闘結果を返す
 * @param	result		BATTLE_PARAM::win_lose_flag
 * @retval	FALSE		捕獲成功or勝っちゃった(再戦不可)
 * @retval	TRUE		逃げたor逃げられた(再戦可能)
 */
//-----------------------------------------------------------------------------
BOOL BattleParam_IsSeacretPokeRetry(u32 result)
{
	switch (result) {
	case FIGHT_WIN:			//倒しちゃった
	case FIGHT_POKE_GET:	//捕まえた
		return FALSE;	//再戦不可
	default:
		return TRUE;	//再戦可
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	配布ポケモンとの戦闘結果を返す
 * @param	result		BATTLE_PARAM::win_lose_flag
 * @retval	FALSE		捕獲成功(再戦不可)
 * @retval	TRUE		倒したor逃げたor逃げられた(再戦可能)
 */
//-----------------------------------------------------------------------------
BOOL BattleParam_IsHaifuPokeRetry(u32 result)
{
	switch (result) {
	case FIGHT_POKE_GET:	//捕まえた
		return FALSE;	//再戦不可
	default:
		return TRUE;	//再戦可
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	トレーナーデータ生成（自分側）
 * @param	bp			BATTLE_PARAM
 */
//-----------------------------------------------------------------------------
void	BattleParam_TrainerDataMake(BATTLE_PARAM *bp)
{
	bp->trainer_data[CLIENT_NO_MINE].tr_type=MyStatus_GetMySex(bp->my_status[CLIENT_NO_MINE]);
	PM_strcpy(&bp->trainer_data[CLIENT_NO_MINE].name[0],MyStatus_GetMyName(bp->my_status[CLIENT_NO_MINE]));

	bp->trainer_data[CLIENT_NO_MINE2]=bp->trainer_data[CLIENT_NO_MINE];
}

