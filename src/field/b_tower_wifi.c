/**
 *	@file	b_tower_wifi.c
 *	@brief	�o�g���^���[ WiFi�֘A�f�[�^���W
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
 *	@brief	�ʐM�p�ɃA�b�v�f�[�g����v���C���[�f�[�^���Z�[�u�f�[�^����쐬����
 *
 *	@param	mode	0:�V���O���p(�g���[�i�[���[�h�p)
 *					1:wifi�p(�^���[wifi�p)
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
 
	//���b�Z�[�W�f�[�^�擾
	for(i = 0;i < 3;i++){
		MI_CpuCopy8(TowerPlayerMsg_Get(sv,BTWR_MSG_PLAYER_READY+i),&(dat->message[8*i]),8);
	}
	MI_CpuCopy8(TowerPlayerMsg_Get(sv,BTWR_MSG_LEADER),dat->leaderMessage,8);

	//�^���[�Z�[�u�f�[�^�擾
	if(mode==BTWR_SCORE_POKE_SINGLE){
		//�f�[�^���L���Ȃ�result��1,�����Ȃ�false
		dat->result = TowerScoreData_SetFlags(score,BTWR_SFLAG_SINGLE_POKE_DATA,BTWR_DATA_get);
		if(dat->result){
			//�|�P�����f�[�^�擾
			TowerScoreData_GetUsePokeDataDpw(score,mode,(DPW_BT_POKEMON_DATA*)dat->pokemon);
		}
	}else{
		dat->result =  TowerScoreData_GetWifiScore(score);
		//�|�P�����f�[�^�擾
		TowerScoreData_GetUsePokeDataDpw(score,mode,(DPW_BT_POKEMON_DATA*)dat->pokemon);
	}
}

#ifdef PM_DEBUG
/**
 *	@brie	Wifi�o�g���^���[�_�~�[�f�[�^��bin�o�͂��邽�߂̊֐�
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
