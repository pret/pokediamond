/**
 *	@file	b_tower_wifi.c
 *	@brief	バトルタワー WiFi関連データ収集
 *	@author	Miyuki Iwasawa
 *	@date	06.05.10
 *	
 */
#include "common.h"
#include "savedata/savedata_def.h"
#include "savedata/savedata.h"
#include "savedata/zukanwork.h"
#include "savedata/wifihistory.h"
#include "savedata/mystatus.h"
#include "system/procsys.h"
#include "poketool/poke_tool.h"
#include "poketool/monsno.h"
#include "application/p_status.h"
#include "application/pokelist.h"
#include "field/fieldsys.h"
#include "field/field_event.h"
#include "field/encount_set.h"
#include "field/ev_time.h"
#include "field/union_beacon_tool.h"

#include "libdpw/dpw_bt.h"
#include "b_tower_scr_def.h"
#include "b_tower_fld.h"
#include "b_tower_ev.h"

void BtlTowerData_MakeUpdatePlayerData(SAVEDATA* sv,BTWR_SCORE_POKE_DATA mode,Dpw_Bt_Player* dat);

/**
 *	@brief	通信用にアップデートするプレイヤーデータをセーブデータから作成する
 *
 *	@param	mode	0:シングル用(トレーナーロード用)
 *					1:wifi用(タワーwifi用)
 */
void BtlTowerData_MakeUpdatePlayerData(SAVEDATA* sv,BTWR_SCORE_POKE_DATA mode,Dpw_Bt_Player* dat)
{
	int i;
	MYSTATUS	*my = SaveData_GetMyStatus(sv);
	WIFI_HISTORY	*wifi = SaveData_GetWifiHistory(sv);
	BTLTOWER_SCOREWORK*	score = SaveData_GetTowerScoreData(sv);
	
	MI_CpuClear8(dat,sizeof(Dpw_Bt_Player));

	//name
	MI_CpuCopy8(MyStatus_GetMyName(my),dat->playerName,8*2);
	//playerid
	*((u32*)dat->playerId) = MyStatus_GetID(my);
	//version
	dat->versionCode = CasetteVersion;
	//language
	dat->langCode = CasetteLanguage;
	//countryCode
	dat->countryCode = (u8)WIFIHISTORY_GetMyNation(wifi);
	//localCode
	dat->localCode = (u8)WIFIHISTORY_GetMyArea(wifi);
	//gender
	dat->gender = MyStatus_GetMySex(my);
	//tr_type
	dat->trainerType = UnionView_GetTrainerInfo(
			dat->gender,MyStatus_GetTrainerView(my),UNIONVIEW_TRTYPE);
 
	//メッセージデータ取得
	for(i = 0;i < 3;i++){
		MI_CpuCopy8(TowerPlayerMsg_Get(sv,BTWR_MSG_PLAYER_READY+i),&(dat->message[8*i]),8);
	}
	MI_CpuCopy8(TowerPlayerMsg_Get(sv,BTWR_MSG_LEADER),dat->leaderMessage,8);

	//タワーセーブデータ取得
	if(mode==BTWR_SCORE_POKE_SINGLE){
		//データが有効ならresultに1,無効ならfalse
		dat->result = TowerScoreData_SetFlags(score,BTWR_SFLAG_SINGLE_POKE_DATA,BTWR_DATA_get);
		if(dat->result){
			//ポケモンデータ取得
			TowerScoreData_GetUsePokeDataDpw(score,mode,(DPW_BT_POKEMON_DATA*)dat->pokemon);
		}
	}else{
		dat->result =  TowerScoreData_GetWifiScore(score);
		//ポケモンデータ取得
		TowerScoreData_GetUsePokeDataDpw(score,mode,(DPW_BT_POKEMON_DATA*)dat->pokemon);
	}
}

#ifdef PM_DEBUG
/**
 *	@brie	Wifiバトルタワーダミーデータをbin出力するための関数
 */
static void* debug_btower_wifi_data = NULL;
void DebugWifiBTower_DummyDataMake(SAVEDATA* sv);
void DebugWifiBTower_DummyDataMake(SAVEDATA* sv)
{
	int i;
	Dpw_Bt_Player* dest;
	Dpw_Bt_Player** dat = (Dpw_Bt_Player**)&debug_btower_wifi_data;
	*dat = sys_AllocMemoryLo(HEAPID_WORLD,sizeof(Dpw_Bt_Player)*7);
	dest = *dat;
	MI_CpuClear8(dest,sizeof(Dpw_Bt_Player)*7);	
	for(i = 0;i < 7;i++){
		BtlTowerData_MakeUpdatePlayerData(sv,BTWR_SCORE_POKE_WIFI,&dest[i]);
	}
	
	sys_FreeMemoryEz(debug_btower_wifi_data);
}

#endif	//PM_DEBUG
