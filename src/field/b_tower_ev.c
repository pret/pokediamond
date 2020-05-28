/**
 *	@file	b_tower_ev.c
 *	@brief	バトルタワー　常駐イベントコントローラ
 *	@author	Miyuki Iwasawa
 *	@date	06.04.24
 */

#include "common.h"
#include "savedata/savedata_def.h"
#include "savedata/savedata.h"
#include "savedata/zukanwork.h"
#include "savedata/perapvoice.h"
#include "savedata/record.h"
#include "savedata/undergrounddata.h"
#include "savedata/sp_ribbon.h"
#include "system/procsys.h"
#include "system/wipe.h"
#include "system/brightness.h"
#include "poketool/poke_tool.h"
#include "poketool/monsno.h"
#include "poketool/poke_number.h"
#include "application/p_status.h"
#include "application/pokelist.h"
#include "field/fieldsys.h"
#include "field/field_event.h"
#include "field/encount_set.h"
#include "field/ev_time.h"
#include "field/ev_mapchange.h"
#include "field/script.h"
#include "fielddata/maptable/zone_id.h"
#include "fielddata/base_goods/goods_id_def.h"
#include "communication/comm_tool.h"
#include "communication/comm_system.h"
#include "battle/battle_common.h"

#include "savedata/record.h"
#include "poketool/pokeparty.h"
#include "system/gamedata.h"
#include "sysflag.h"
#include "application/wbtower.h"
#include "wifi/dwc_rap.h"


#include "b_tower_scr_def.h"
#include "b_tower_fld.h"

#define _B_TOWER_EV_H_GLOBAL 
#include "b_tower_ev.h"

//#include "field/b_tower_deb.h"

///ポケモン選択イベントワーク
typedef struct _BTWR_POKESEL_EVENT{
	int	ret_val;
	int	seq;
	u8	plist_mode;
	u8	pst_mode;
	u8	min;
	u8	max;
	u8	level;	
	u8	pos;
	u8	sel[6];
	void** sp_wk;
}BTWR_POKESEL_EVENT;

///ポケモン選択イベントシーケンスID
typedef enum{
 BTWR_POKESEL_PLIST_CALL,
 BTWR_POKESEL_PLIST_WAIT,
 BTWR_POKESEL_PST_CALL,
 BTWR_POKESEL_PST_WAIT,
 BTWR_POKESEL_EXIT,
 BTWR_POKESEL_ENTER,
};

///Wifiイベントワーク
typedef struct _BTWR_WIFI_EVENT{
	int	ret_val;
	int	seq;
	WBTOWER_PARAM*	app_wk;
	u16**			scr_ret_wk;
	u16				scr_ret_wkno;
	u16	mode;
	u16	dpw_code;
}BTWR_WIFI_EVENT;

typedef enum{
	BTWR_WIFI_CONNECT_CALL,
	BTWR_WIFI_CONNECT_WAIT,
	BTWR_WIFI_EV_EXIT,
};

///通信マルチデータ受信ワーク
typedef struct _BTWR_SIO_EVENT{
	u16	mode;
	u16	scr_ret_wkno;
}BTWR_SIO_EVENT;

/**
 *	@brief	バトルタワー　ポケモンリスト呼び出し
 */
static int BtlTower_PokeListCall(BTWR_POKESEL_EVENT* wk,FIELDSYS_WORK* fsys,int heapID)
{
	u8	i;
	SAVEDATA* sv;
	PLIST_DATA * pld = sys_AllocMemoryLo(heapID,sizeof(PLIST_DATA));

	sv = fsys->savedata;

	MI_CpuClear8(pld,sizeof(PLIST_DATA));
	pld->cfg = SaveData_GetConfig(sv);
	pld->pp = SaveData_GetTemotiPokemon(sv);
	pld->myitem = SaveData_GetMyItem(sv);

	pld->type = PL_TYPE_SINGLE;
	pld->mode = wk->plist_mode;

	pld->in_min = wk->min;
	pld->in_max = wk->max;
	pld->in_lv = wk->level;

	pld->ret_sel = wk->pos;

	for(i = 0;i < 6;i++){
		pld->in_num[i] = wk->sel[i];
	}
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	*(wk->sp_wk) = pld;
	return BTWR_POKESEL_PLIST_WAIT;
}

/**
 *	@brief	ポケモンリスト終了待ち
 */
static int BtlTower_PokeListWait(BTWR_POKESEL_EVENT* wk,FIELDSYS_WORK* fsys)
{
	int	ret;
	PLIST_DATA * pld;

	// サブプロセス終了待ち
	if( FieldEvent_Cmd_WaitSubProcEnd( fsys ) ) {
		return BTWR_POKESEL_PLIST_WAIT;
	}

	pld = *(wk->sp_wk);

	//データ取得
	switch(pld->ret_sel){
	case PL_SEL_POS_EXIT:	//やめる
		wk->ret_val = 0;
		return BTWR_POKESEL_EXIT;
	case PL_SEL_POS_ENTER:	//決定
		wk->ret_val = 1;
		return BTWR_POKESEL_EXIT;
	default:	//つよさをみる
		break;
	}
	//現在選ばれているポケモンを保存
	MI_CpuCopy8(pld->in_num,wk->sel,6);
	
	//ポジションを保存
	wk->pos = pld->ret_sel;

	sys_FreeMemoryEz(pld);
	*(wk->sp_wk) = NULL;
	return	BTWR_POKESEL_PST_CALL;
}

/**
 *	@brief	バトルタワー　ポケモンステータス呼び出し
 */
static int BtlTower_PokeStatusCall(BTWR_POKESEL_EVENT* wk,FIELDSYS_WORK* fsys,int heapID)
{
	PSTATUS_DATA* psd;
	SAVEDATA	*sv;

	static const u8 PST_PageTbl[] = {
		PST_PAGE_INFO,			// 「ポケモンじょうほう」
		PST_PAGE_MEMO,			// 「トレーナーメモ」
		PST_PAGE_PARAM,			// 「ポケモンのうりょく」
		PST_PAGE_CONDITION,		// 「コンディション」
		PST_PAGE_B_SKILL,		// 「たたかうわざ」
		PST_PAGE_C_SKILL,		// 「コンテストわざ」
		PST_PAGE_RIBBON,		// 「きねんリボン」
		PST_PAGE_RET,			// 「もどる」
		PST_PAGE_MAX
	};
	
	sv = fsys->savedata;

	//ポケモンステータスを呼び出す
	//
	psd = sys_AllocMemoryLo(heapID, sizeof(PSTATUS_DATA));
	MI_CpuClear8(psd,sizeof(PSTATUS_DATA));

	psd->cfg  = SaveData_GetConfig(sv);
	psd->ppd  = SaveData_GetTemotiPokemon(sv);
	psd->zukan_mode = PMNumber_GetMode(sv);
	psd->ev_contest = PokeStatus_ContestFlagGet(sv);
	psd->ppt  = PST_PP_TYPE_POKEPARTY;
	psd->pos  = wk->pos;
	psd->max  = (u8)PokeParty_GetPokeCount( psd->ppd );
	psd->waza = 0;
	psd->mode = wk->pst_mode;
	psd->ribbon = SaveData_GetSpRibbon(sv);
	PokeStatus_PageSet( psd, PST_PageTbl);
	PokeStatus_PlayerSet(psd,SaveData_GetMyStatus(sv));
	
	GameSystem_StartSubProc( fsys, &PokeStatusProcData, psd );
	
	*(wk->sp_wk) = psd;
	return BTWR_POKESEL_PST_WAIT;
}

/**
 *	@brief	バトルタワー　ポケモンステータス終了待ち
 */
static int BtlTower_PokeStatusWait(BTWR_POKESEL_EVENT* wk,FIELDSYS_WORK* fsys)
{
	PSTATUS_DATA* psd;

	// サブプロセス終了待ち
	if( FieldEvent_Cmd_WaitSubProcEnd(fsys) ) {
		return BTWR_POKESEL_PST_WAIT;
	}

	psd = *(wk->sp_wk);
	
	//切り替えられたカレントを保存する
	wk->pos = psd->pos;

	sys_FreeMemoryEz(psd);
	*(wk->sp_wk) = NULL;

	return BTWR_POKESEL_PLIST_CALL;
}

//--------------------------------------------------------------
/**
 * @brief	ゲームイベントコントローラ　ポケモンリスト&ステータス
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
 */
//--------------------------------------------------------------
static BOOL BtlTowerEv_PokeSelect( GMEVENT_CONTROL *ev )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( ev );
	BTWR_POKESEL_EVENT *wk = FieldEvent_GetSpecialWork( ev );

	switch (wk->seq) {
	case BTWR_POKESEL_PLIST_CALL:
#ifdef BTOWER_AUTO_DEB
		DebugBTowerAutoKey = 0;
		DebugBTowerAutoKeyMode = 1;
#endif
		wk->seq = BtlTower_PokeListCall(wk,fsys,HEAPID_WORLD);
		break;
	case BTWR_POKESEL_PLIST_WAIT:
		wk->seq = BtlTower_PokeListWait(wk,fsys);
		break;
	case BTWR_POKESEL_PST_CALL:
#ifdef BTOWER_AUTO_DEB
		DebugBTowerAutoKey = 0;
		DebugBTowerAutoKeyMode = 2;
#endif
		wk->seq = BtlTower_PokeStatusCall(wk,fsys,HEAPID_WORLD);
		break;
	case BTWR_POKESEL_PST_WAIT:
		wk->seq = BtlTower_PokeStatusWait(wk,fsys);
		break;
	case BTWR_POKESEL_EXIT:
#ifdef BTOWER_AUTO_DEB
		DebugBTowerAutoKey = 0;
		DebugBTowerAutoKeyMode = 0;
#endif
		sys_FreeMemoryEz(wk);
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	ポケモン選択　サブイベント呼び出し
 * @param	event	GMEVENT_CONTROL*
 * @retval	nothing
 */
//--------------------------------------------------------------
void EventCmd_BTowerPokeSelectCall(GMEVENT_CONTROL *event,void** buf,
	u8 plmode,u8 psmode,u8 min,u8 max,u8 level,u8 pos)
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork(event);
	
	BTWR_POKESEL_EVENT *wk = sys_AllocMemory( HEAPID_WORLD,sizeof(BTWR_POKESEL_EVENT));
	MI_CpuClear8(wk,sizeof(BTWR_POKESEL_EVENT));

	wk->plist_mode = plmode;
	wk->pst_mode = psmode;

	wk->min = min;
	wk->max = max;
	wk->level = level;
	wk->pos = pos;
	wk->sp_wk = buf;

	FieldEvent_Call(fsys->event,BtlTowerEv_PokeSelect,wk);
}

/**
 *	@brief	バトルタワー　WiFiコネクト呼び出し
 */
static int BtlTower_WifiConnectCall(BTWR_WIFI_EVENT* wk,FIELDSYS_WORK* fsys)
{
	SAVEDATA* sv;
	if( mydwc_checkMyGSID(fsys->savedata) ){
		wk->app_wk = Field_WifiBattleTowerConnect_SetProc(fsys,wk->mode,wk->dpw_code);
		return BTWR_WIFI_CONNECT_WAIT;
	}else{
		wk->ret_val = WIFI_BTOWER_RESULT_CANCEL;
		return BTWR_WIFI_EV_EXIT;
	}
}

/**
 *	@brief	バトルタワー　WiFiコネクト終了待ち
 */
static int BtlTower_WifiConnectWait(BTWR_WIFI_EVENT* wk,FIELDSYS_WORK* fsys)
{
	u8	i;
	WBTOWER_PARAM	*param;

	// サブプロセス終了待ち
	if( FieldEvent_Cmd_WaitSubProcEnd(fsys) ) {
		return BTWR_WIFI_CONNECT_WAIT;
	}
//	param = (WBTOWER_PARAM*)wk->app_wk;

	//ステータスを取得
	wk->ret_val = wk->app_wk->result;//param->result;
	OS_Printf("wifi_ret_val = %d,%d\n",wk->app_wk->result,wk->ret_val);
	//メモリ解放
	sys_FreeMemoryEz(wk->app_wk);
	return BTWR_WIFI_EV_EXIT;
}


//--------------------------------------------------------------
/**
 * @brief	ゲームイベントコントローラ　WiFi接続
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
 */
//--------------------------------------------------------------
static BOOL BtlTowerEv_WifiConnect( GMEVENT_CONTROL *ev )
{
	u16	*buf16;
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( ev );
	BTWR_WIFI_EVENT *wk = FieldEvent_GetSpecialWork( ev );

	switch (wk->seq) {
	case BTWR_WIFI_CONNECT_CALL:
		wk->seq = BtlTower_WifiConnectCall(wk,fsys);
		break;
	case BTWR_WIFI_CONNECT_WAIT:
		wk->seq = BtlTower_WifiConnectWait(wk,fsys);
		break;
	case BTWR_WIFI_EV_EXIT:
		//戻り値指定
		buf16 = GetEventWorkAdrs(fsys,wk->scr_ret_wkno);//*(wk->scr_ret_wk);
		OS_Printf("wifi_ret_val = %d\n",wk->ret_val);
		*buf16 = wk->ret_val;
		sys_FreeMemoryEz(wk);
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	WiFi接続　サブイベント呼び出し
 * @param	event	GMEVENT_CONTROL*
 * @param	mode	接続モード
 * @param	ret_wk_no	返り値を返すワークID
 * @param	dpw_code	DPW_INIT_PROCが返した返り値
 * @retval	nothing
 */
//--------------------------------------------------------------
void EventCmd_BTowerWifiCall(GMEVENT_CONTROL *event,u16 mode,u16 ret_wk_no,u16 dpw_code)
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork(event);
	
	BTWR_WIFI_EVENT *wk = sys_AllocMemory( HEAPID_WORLD,sizeof(BTWR_WIFI_EVENT));
	MI_CpuClear8(wk,sizeof(BTWR_WIFI_EVENT));

	wk->mode = mode;
	wk->dpw_code = dpw_code;
	wk->scr_ret_wkno = ret_wk_no;
	/*
	if(mode == BTWR_WIFI_UP_PLAY){
		//アップロードデータ生成
	}*/
	FieldEvent_Call(fsys->event,BtlTowerEv_WifiConnect,wk);
}

//--------------------------------------------------------------
/**
 * @brief	ゲームイベントコントローラ 通信マルチデータ受信　
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
 */
//--------------------------------------------------------------
static BOOL BtlTowerEv_SioRecvBuf( GMEVENT_CONTROL *ev )
{
	u16	*buf16;
	const void* recv;
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( ev );
	BTWR_SIO_EVENT *wk = FieldEvent_GetSpecialWork( ev );

	//データ受信待ち
	recv = CommToolGetTempData(1-CommGetCurrentID());
	if(recv == NULL){
		return FALSE;
	}
#if 1
	//戻り値指定バッファアドレス取得
	buf16 = GetEventWorkAdrs(fsys,wk->scr_ret_wkno);
	
	//受信データモード別解析
	switch(wk->mode){
	case 0:
		*buf16 = BTowerComm_RecvPlayerData(fsys,recv);
		break;
	case 1:
		*buf16 = BTowerComm_RecvTrainerData(fsys,recv);
		break;
	case 2:
		*buf16 = BTowerComm_RecvRetireSelect(fsys,recv);
	}
#endif
	sys_FreeMemoryEz(wk);
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	通信マルチ　データ受信サブイベント
 * @param	event	GMEVENT_CONTROL*
 * @param	mode	受信モード
 * @param	ret_wk_no	返り値取得用ワークID
 * @retval	nothing
 */
//--------------------------------------------------------------
void EventCmd_BTowerSioRecvBuf(GMEVENT_CONTROL *event,u16 mode,u16 ret_wk_no)
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork(event);
	
	BTWR_SIO_EVENT *wk = sys_AllocMemory( HEAPID_WORLD,sizeof(BTWR_SIO_EVENT));
	MI_CpuClear8(wk,sizeof(BTWR_SIO_EVENT));

	wk->mode = mode;
	wk->scr_ret_wkno = ret_wk_no;
	FieldEvent_Call(fsys->event,BtlTowerEv_SioRecvBuf,wk);
}

/**
 *	@brief	プライズをもらえるかどうかチェックする
 *
 *	@retval	0	もらえない
 */
u16 BtlTower_IsPrizeGet(SAVEDATA* sv)
{
	RECORD* record;
	BTLTOWER_SCOREWORK* score;
	UNDERGROUNDDATA* gSave;
	u16	win;
	u8	c_on,s_on,g_on,c_ready,s_ready,g_ready;
	
	//シングルモードの最大連勝数レコードを取得
	record = SaveData_GetRecord(sv);
	win = RECORD_Get(record,RECID_RENSHOU_SINGLE);

	if(win < BTWR_20_RENSHOU_CNT){
		return 0;
	}
	score = SaveData_GetTowerScoreData(sv);

	c_on = TowerScoreData_SetFlags(score,BTWR_SFLAG_COPPER_GET,BTWR_DATA_get);
	s_on = TowerScoreData_SetFlags(score,BTWR_SFLAG_SILVER_GET,BTWR_DATA_get);
	g_on = TowerScoreData_SetFlags(score,BTWR_SFLAG_GOLD_GET,BTWR_DATA_get);
	c_ready = TowerScoreData_SetFlags(score,BTWR_SFLAG_COPPER_READY,BTWR_DATA_get);
	s_ready = TowerScoreData_SetFlags(score,BTWR_SFLAG_SILVER_READY,BTWR_DATA_get);
	g_ready = TowerScoreData_SetFlags(score,BTWR_SFLAG_GOLD_READY,BTWR_DATA_get);
	
	if(c_on && s_on && g_on){
//	if(s_on && g_on){
		return 0;	//もう三つとも貰った
	}
	gSave = SaveData_GetUnderGroundData(sv);

	//まだ20を貰っていない
	if(!c_on){
		//グッズに空きがあればあげる
		if(UnderGroundAddChkGoodsPCItem(gSave,BTWR_GOODS_COPPER)){
			//入った
			TowerScoreData_SetFlags(score,BTWR_SFLAG_COPPER_GET,BTWR_DATA_set);
			return 1;
		}else{
			//一回あげようとして入らなかったフラグを立てておく
			if(!c_ready){
				TowerScoreData_SetFlags(score,BTWR_SFLAG_COPPER_READY,BTWR_DATA_set);
			}
			return 4;	//入らない
		}
	}
	//まだ50連勝していない
	if(win < BTWR_50_RENSHOU_CNT){
		return 0;
	}
	
	//まだ50を貰っていない
	if(!s_on){
		//グッズに空きがあればあげる
		if(UnderGroundAddChkGoodsPCItem(gSave,BTWR_GOODS_SILVER)){
//		if(UnderGroundAddGoodsPCItem(gSave,BTWR_GOODS_SILVER)){
			//入った
			TowerScoreData_SetFlags(score,BTWR_SFLAG_SILVER_GET,BTWR_DATA_set);
			return 2;
		}else{
			//一回あげようとして入らなかったフラグを立てておく
			if(!s_ready){
				TowerScoreData_SetFlags(score,BTWR_SFLAG_SILVER_READY,BTWR_DATA_set);
			}
			return 4;	//入らない
		}
	}
	//まだ100連勝していないか、もう貰っている
	if(win < BTWR_100_RENSHOU_CNT || (g_on)){
		return 0;
	}
	//グッズに空きがあればあげる
	if(UnderGroundAddChkGoodsPCItem(gSave,BTWR_GOODS_GOLD)){
//	if(UnderGroundAddGoodsPCItem(gSave,BTWR_GOODS_GOLD)){
		//入った
		TowerScoreData_SetFlags(score,BTWR_SFLAG_GOLD_GET,BTWR_DATA_set);
		return 3;
	}else{
		//一回あげようとして入らなかったフラグを立てておく
		if(!g_ready){
			TowerScoreData_SetFlags(score,BTWR_SFLAG_GOLD_READY,BTWR_DATA_set);
		}
		return 4;	//入らない
	}
}

/**
 *	@brief	プライズをくれるヒトの表示状態を返す
 *
 *	@retval	0	非表示
 *	@retval	1	
 */
u16 BtlTower_IsPrizemanSet(SAVEDATA* sv)
{
	RECORD* record;
	BTLTOWER_SCOREWORK* score;
	u16	win;
	u8	c_on,s_on,g_on,c_ready,s_ready,g_ready;
	
	//シングルモードの最大連勝数レコードを取得
	record = SaveData_GetRecord(sv);
	win = RECORD_Get(record,RECID_RENSHOU_SINGLE);

	if(win < BTWR_20_RENSHOU_CNT){
		return 0;
	}
	score = SaveData_GetTowerScoreData(sv);

	c_on = TowerScoreData_SetFlags(score,BTWR_SFLAG_COPPER_GET,BTWR_DATA_get);
	s_on = TowerScoreData_SetFlags(score,BTWR_SFLAG_SILVER_GET,BTWR_DATA_get);
	g_on = TowerScoreData_SetFlags(score,BTWR_SFLAG_GOLD_GET,BTWR_DATA_get);
	c_ready = TowerScoreData_SetFlags(score,BTWR_SFLAG_COPPER_READY,BTWR_DATA_get);
	s_ready = TowerScoreData_SetFlags(score,BTWR_SFLAG_SILVER_READY,BTWR_DATA_get);
	g_ready = TowerScoreData_SetFlags(score,BTWR_SFLAG_GOLD_READY,BTWR_DATA_get);

	if(c_on && s_on && g_on){	//両方既に貰っている
		return 0;
	}

	//20をまだ貰っていない
	if(!c_on){
		if(c_ready){
			return 4;
		}
		return 1;
	}
	
	//まだ50連勝してない
	if(win < BTWR_50_RENSHOU_CNT){
		return 0;
	}
	//50をまだ貰っていない
	if(!s_on){
		if(s_ready){
			return 5;
		}
		return 2;
	}
	//100連勝まだしてない
	if(win < BTWR_100_RENSHOU_CNT){
		return 0;
	}
	//100はもう貰った
	if(g_on){
		return 0;
	}
	//100をまだ貰ってない
	if(g_ready){
		return 6;
	}
	return 3;
}

/**
 *	@brief	タワー対戦結果　アップデート処理
 */
void BtlTower_BattleRecordUpdate(FIELDSYS_WORK* fsys,const BATTLE_TOWER_RECORD* rec)
{
	BTOWER_SCRWORK* wk = fsys->btower_wk;

	wk->rec_turn += rec->total_turn;
	wk->rec_down += rec->total_hinshi;
	wk->rec_damage += rec->total_damage;
}

#include "savedata/randomgroup.h"
/**
 *	@brief	タワープレイ更新ランダム計算
 */
u32	BtlTower_PlayFixRand(u32 seed)
{
	// ここで返す値を保存しておけば次の乱数の種になる
	return seed * 48828125L + 1;
}

/**
 *	@brief	タワー日付更新ランダム計算
 */
u32 BtlTower_DayFixRand(u32 seed)
{
	return seed * 1566083941 + 1;
}

/**
 *	@brief	タワー日付更新ランダムシード　一日一回の更新処理
 *
 *	＊日付変更処理/レコード交換(グループ内)/new game処理時に呼ぶこと
 */
u32	BtlTower_UpdateDayRndSeed(SAVEDATA* sv)
{
	u32	seed;

	//ゲームランダムシードのオリジナルを取得
	seed = RandomGroup_GetDefaultRandom(SaveData_GetRandomGroup(sv));
	OS_Printf("BTowerRndSeed = %d : ",seed);
	//オリジナルからタワー用Dayシードを取得
	seed = BtlTower_DayFixRand(seed);
	OS_Printf("%d\n",seed);

	//タワーセーブデータ更新しておく
	TowerScoreData_SetDayRndSeed(SaveData_GetTowerScoreData(sv),seed);

	return seed;
}

/**
 *	@brief	タワー日付/プレイ更新ランダムシード　挑戦開始時の更新処理
 */
u32	BtlTower_UpdatePlayRndSeed(SAVEDATA* sv)
{
	u32	seed,day_seed;
	BTLTOWER_SCOREWORK* score = SaveData_GetTowerScoreData(sv);
	
	//現在セーブされているDayシードを取得
	day_seed = TowerScoreData_GetDayRndSeed(score);
	//取得した値を更新
	day_seed = BtlTower_DayFixRand(day_seed);
	//値を書き戻す
	TowerScoreData_SetDayRndSeed(score,day_seed);

	//DayシードからPlayシードを取得
	seed = BtlTower_PlayFixRand(day_seed);
	//取得した値を更新
	TowerPlayData_Put(SaveData_GetTowerPlayData(sv),BTWR_PSD_rnd_seed,&seed);

	OS_Printf("BTowerPlayRndUpdate = %d <- %d \n",seed,day_seed);
	return seed;
}

/**
 *	@brief	タワー日付/プレイ更新ランダムシード取得　継続挑戦開始時の取得処理
 */
u32	BtlTower_GetContinuePlayRndSeed(SAVEDATA* sv)
{
	int i,round;
	u32	seed,day_seed;
	BTLTOWER_SCOREWORK* score = SaveData_GetTowerScoreData(sv);
	BTLTOWER_PLAYWORK* play = SaveData_GetTowerPlayData(sv);
	
	//現在セーブされているDayシードを取得してそのまま使う
	day_seed = TowerScoreData_GetDayRndSeed(score);

	//DayシードからPlayシードを取得
	seed = BtlTower_PlayFixRand(day_seed);
	round = TowerScoreData_SetStage(score,
			TowerPlayData_Get(play,BTWR_PSD_playmode,NULL),BTWR_DATA_get);
	round *= 24;
	//周回数分予め進めておく
	for(i = 0;i < round;i++){
		seed = BtlTower_PlayFixRand(seed);
	}
	//取得した値をプレイデータに書き込んでおく
	TowerPlayData_Put(SaveData_GetTowerPlayData(sv),BTWR_PSD_rnd_seed,&seed);

	OS_Printf("BTowerPlayRndUpdate = %d <- %d \n",seed,day_seed);
	return seed;
}

/**
 *	@brief	バトルタワーサロン判定
 */
BOOL BtlTower_IsSalon(FIELDSYS_WORK* fsys)
{
	if(fsys->location->zone_id == ZONE_ID_D31R0207){
		return TRUE;
	}
	return FALSE;
}

