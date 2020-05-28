/**
 *	@file	btower_scr.c
 *	@brief	�o�g���^���[�@�X�N���v�g�R�}���h�n
 *	@author	Miyuki Iwasawa
 *	@date	06.04.17
 */

#include "common.h"
#include "savedata/savedata_def.h"
#include "savedata/record.h"
#include "savedata/fnote_mem.h"
#include "system/buflen.h"
#include "savedata/tv_work.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "system/procsys.h"
#include "system/gamedata.h"
#include "application/pokelist.h"
#include "fieldsys.h"
#include "sysflag.h"
#include "field/situation.h"
#include "field/situation_local.h"
#include "field/tv_topic.h"
#include "field/tvtopic_extern.h"
#include "ev_mapchange.h"
#include "fielddata/base_goods/goods_id_def.h"
#include "savedata/undergrounddata.h"
#include "savedata/b_tower.h"
#define __B_TOWER_SCR_H_GLOBAL
#include "field/b_tower_scr.h"
#include "field/b_tower_ev.h"
#include "b_tower_fld.h"
#include "field/field_encount.h"

//#include "field/b_tower_deb.h"

///�T�u�֐��v���g�^�C�v
static u16 towerscr_PokeRibbonSet(SAVEDATA* sv,u8 ribbon,BTOWER_SCRWORK* wk);
static u16 towerscr_IfRenshouPrizeGet(BTOWER_SCRWORK* wk);
static void towerscr_SaveMemberPokeData(BTOWER_SCRWORK* wk,SAVEDATA* sv,BTWR_SCORE_POKE_DATA mode);


/**
 *	@brief	�v���C���[�h�ʂ̃����o�[�����擾����
 *
 *	@param	mode	BTWR_MODE_�`
 */
u16	TowerScrTools_GetMemberNum(u16 mode)
{
	switch(mode){
	case BTWR_MODE_SINGLE:
	case BTWR_MODE_WIFI:
	case BTWR_MODE_RETRY:
		return 3;
	case BTWR_MODE_DOUBLE:
		return 4;
	case BTWR_MODE_MULTI:
	case BTWR_MODE_COMM_MULTI:
		return 2;
	}
	return 0;
}

typedef struct POKE_CHK{
	u16	monsno;
	u16	itemno;
}POKE_CHK;

//������ރ|�P����������������������|�P�������`�F�b�N
static BOOL pokechk_CheckSamePoke(POKE_CHK* plist,u16 monsno,u16 itemno,int num)
{
	int i;

	for(i = 0;i < num;i++){
		if(plist[i].monsno == monsno){
			if(itemno == 0){
				continue;
			}
			if(plist[i].itemno == itemno){
				return TRUE;
			}
		}
	}
	return FALSE;
}

//���̑g�ݍ��킹�Œ���\���ǂ����H
static BOOL pokechk_IsEntryPattern(POKE_CHK* plist,int num)
{
	int i,j;

	for(i = 0;i < num-1;i++){
		for(j = i+1;j < num;j++){
			if(plist[i].monsno == plist[j].monsno){
				return FALSE;
			}
			if(plist[i].itemno == 0){
				continue;
			}
			if(plist[i].itemno == plist[j].itemno){
				return FALSE;
			}
		}
	}
	return TRUE;
}

//�Q���`�F�b�N�g�ݍ��킹������
static BOOL pokechk_CheckPattern(POKE_CHK* ps,int num,int pokenum,int max)
{
	int i,j,k,l;
	POKE_CHK	pd[4];

	MI_CpuClear8(pd,sizeof(POKE_CHK)*4);
	
	//�c�����|�P�����̒��ő�����
	for(i = 0;i < max;i++){	//��̖�
		pd[0] = ps[i];
		for(j = i+1;j < pokenum;j++){	//��̖�
			pd[1] = ps[j];
			if(num == 2){
				if(pokechk_IsEntryPattern(pd,num)){
					return TRUE;
				}
				continue;
			}
			for(k = j+1;k < pokenum;k++){	//�R�̖�
				pd[2] = ps[k];
				if(num == 3){
					if(pokechk_IsEntryPattern(pd,num)){
						return TRUE;
					}
					continue;
				}
				for(l = k+1;l < pokenum;l++){	//�S�̖�
					pd[3] = ps[l];
					if(pokechk_IsEntryPattern(pd,num)){
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

/**
 *	@brief	�o�g���^���[�@�Q���\�ȃ|�P�������̃`�F�b�N
 *
 *	@param	num		�Q���ɕK�v�ȃ|�P������
 *
 *	@retval	true	�Q���\
 *	@retval	false	�Q���s��
 */
BOOL TowerScrTools_CheckEntryPokeNum(u16 num,SAVEDATA *savedata)
{
	u8	i,j,ct,pokenum;
	u16	monsno,itemno;
	POKEPARTY	*party;
	POKEMON_PARAM* pp;
	POKE_CHK	ps[6];
	
	party = SaveData_GetTemotiPokemon(savedata);
	pokenum = PokeParty_GetPokeCount(party);

	if(pokenum < num){
		return FALSE;
	}

	for(i = 0,ct = 0;i < pokenum;i++){
		pp = PokeParty_GetMemberPointer(party,i);
		monsno = PokeParaGet(pp,ID_PARA_monsno,NULL);
		itemno = PokeParaGet(pp,ID_PARA_item,NULL);
		
		//�^�}�S�łȂ����`�F�b�N
		if(PokeParaGet(pp,ID_PARA_tamago_flag,NULL) != 0){
			continue;
		}
		if(BattleTowerExPokeCheck_MonsNo(monsno) == TRUE){
			continue;
		}
		if(pokechk_CheckSamePoke(ps,monsno,itemno,ct) == TRUE){
			//���ɑI�΂�Ă���|�P�����Ɠ���
			continue;
		}
		ps[ct].monsno = monsno;
		ps[ct].itemno = itemno;
		ct++;
	}
	if(ct < num){
		return FALSE;
	}
	return pokechk_CheckPattern(ps,num,ct,(ct-num)+1);
}

/**
 *	@brief	���Z�b�g���ă^�C�g���ɖ߂�
 */
void TowerScrTools_SystemReset(void)
{
	OS_ResetSystem(0);
}

/**
 *	@brief	new game���Ƀv���C�f�[�^���N���A����
 */
void TowerScrTools_ClearPlaySaveData(BTLTOWER_PLAYWORK* playSave)
{
	TowerPlayData_Clear(playSave);
}

/**
 * @brief	�Z�[�u�f�[�^���L�����ǂ����Ԃ�
 */
BOOL TowerScrTools_IsSaveDataEnable(BTLTOWER_PLAYWORK* playSave)
{
	return TowerPlayData_GetSaveFlag(playSave);
}

/**
 *	@brief	�E�o�p�Ɍ��݂̃��P�[�V�������L������
 */
void TowerScrTools_PushNowLocation(FIELDSYS_WORK* fsys)
{
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	//���݈ʒu�����ڑ���ɐݒ�
	SetLocation(sp, fsys->location->zone_id, DOOR_ID_JUMP_CODE,
			Player_NowGPosXGet(fsys->player), Player_NowGPosZGet(fsys->player), DIR_UP);

	//����ڑ��t���OON
	SysFlag_CommCounterSet(SaveData_GetEventWork(fsys->savedata));
	
}

/**
 *	@brief	�Q�[�g����o�鎞�ɓ���ڑ�������ɖ߂�
 */
void TowerScrTools_PopNowLocation(FIELDSYS_WORK* fsys)
{
	//����ڑ��t���OOff
	SysFlag_CommCounterReset(SaveData_GetEventWork(fsys->savedata));
}

/**
 *	@brief	�������Q�[�g�̈ʒu���擾����
 */
void TowerScrTools_GetGateLocation(FIELDSYS_WORK* fsys,u16* x,u16* y)
{
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	*x = sp->grid_x;
	*y = sp->grid_z;
}

/**
 *	@brief	�v���C���[�h�ʃ��R�[�h�Z�[�u�f�[�^�A������Ԃ�
 */
u16	TowerScrTools_GetRenshouRecord(SAVEDATA* sv,u16 play_mode)
{
	u16 val;
	if(play_mode == BTWR_MODE_RETRY){
		return 0;
	}
	val = RECORD_Get(SaveData_GetRecord(sv),
			RECID_RENSHOU_SINGLE_CNT+play_mode*2);

	return val;
}

/**
 *	@brief	�X�R�A�f�[�^�̃t���O��Ԃ�
 */
u16 TowerScrTools_GetScoreFlags(SAVEDATA* sv,BTWR_SFLAG_ID flagid)
{
	BTLTOWER_SCOREWORK	*score = SaveData_GetTowerScoreData(sv);

	return (u16)TowerScoreData_SetFlags(score,flagid,BTWR_DATA_get);
}


/**
 *	@brief	Wifi���т̖��A�b�v���[�h�t���O�𐧌䂷��
 */
void TowerScrTools_SetWifiUploadFlag(SAVEDATA* sv,u8 flag)
{
	BTLTOWER_SCOREWORK	*score = SaveData_GetTowerScoreData(sv);
	
	if(flag == 0){	//���Z�b�g
		TowerScoreData_SetFlags(score,BTWR_SFLAG_WIFI_UPLOAD,BTWR_DATA_reset);
	}else{	//�Z�b�g
		TowerScoreData_SetFlags(score,BTWR_SFLAG_WIFI_UPLOAD,BTWR_DATA_set);
	}
}

/**
 *	@brief	WiFi�v���C���т̖��A�b�v���[�h�t���O���擾����
 */
u16 TowerScrTools_GetWifiUploadFlag(SAVEDATA* sv)
{
	BTLTOWER_SCOREWORK	*score = SaveData_GetTowerScoreData(sv);
	return (u16)TowerScoreData_SetFlags(score,BTWR_SFLAG_WIFI_UPLOAD,BTWR_DATA_get);
}

/**
 *	@brief	�Z�[�u�����Ɏ~�߂��Ƃ��̃G���[����
 *
 *	@return	�v���C���Ă������[�h��Ԃ�
 */
u16 TowerScrTools_SetNGScore(SAVEDATA* savedata)
{
	u8	play_mode;
	int id;
	BTLTOWER_PLAYWORK* playSave;
	BTLTOWER_SCOREWORK* scoreSave;
//	RECORD*  record;
	
	//�Z�[�u�f�[�^�擾
	playSave = SaveData_GetTowerPlayData(savedata);
	scoreSave = SaveData_GetTowerScoreData(savedata);

	//�ǂ̃��[�h���v���C���Ă������H
	play_mode = (u8)TowerPlayData_Get(playSave,BTWR_PSD_playmode,NULL);
	
	if(play_mode == BTWR_MODE_RETRY){
		return play_mode;
	}
	//���R�[�h���풆�t���O�𗎂Ƃ�
	TowerScoreData_SetFlags(scoreSave,BTWR_SFLAG_SINGLE_RECORD+play_mode,BTWR_DATA_reset);
	//���݂̎��񐔃��Z�b�g
	TowerScoreData_SetStage(scoreSave,play_mode,BTWR_DATA_reset);
	if(play_mode != BTWR_MODE_WIFI){
		//�v���C�����_���V�[�h���ЂƂ����Ői�߂�
		BtlTower_UpdatePlayRndSeed(savedata);
	}

	OS_Printf("TowerNGScoreSet -> mode = %d\n",play_mode);
	return play_mode;	
}

/**
 *	@brief	WIFI�̃v���C���[DL�f�[�^�����邩�ǂ����`�F�b�N
 */
u16	TowerScrTools_IsPlayerDataEnable(SAVEDATA* sv)
{
	BTLTOWER_WIFI_DATA	*wifiSave;
	wifiSave = SaveData_GetTowerWifiData(sv);

	return (u16)TowerWifiData_IsPlayerDataEnable(wifiSave);
}

//***************************************************************
//===============================================================
//	���[�N�̏������Ɖ��
//===============================================================
//***************************************************************
/**
 *	@brief	fsys���̃o�g���^���[���䃏�[�N�|�C���^������������
 *			�o�g���^���[�J�n���ɕK���Ăяo��
 */
void TowerScr_WorkClear(BTOWER_SCRWORK** pp)
{
	GF_ASSERT(*pp==NULL && "btower work is reake");
	*pp = NULL;
}

/**
 *	@brief	���[�N�G���A���擾���ď���������
 *
 *	@param	savedata	�Z�[�u�f�[�^�ւ̃|�C���^
 *	@param	init		���������[�h BTWR_PLAY_NEW:���߂���ABTWR_PLAY_CONTINE:��������
 *	@param	playmode	�v���C���[�h�w��:BTWR_MODE_�`
 *	
 *	�����Ȃ炸 TowerScr_WorkRelease()�ŗ̈���J�����邱��
 */
BTOWER_SCRWORK* TowerScr_WorkInit(SAVEDATA* savedata,u16 init,u16 playmode)
{
	u8 buf8;
	u16	i,chg_flg;
	BTOWER_SCRWORK* wk;
	RECORD	*record;

	//���[�N�G���A�擾
	HeapStatePush();

	sys_CreateHeapLo(HEAPID_BASE_APP,HEAPID_BTLTOWER_SCR,0x4000);
	wk =  sys_AllocMemory(HEAPID_BTLTOWER_SCR,sizeof(BTOWER_SCRWORK));
	MI_CpuClear8(wk,sizeof(BTOWER_SCRWORK));

	wk->heapID = HEAPID_BTLTOWER_SCR;

	//�Z�[�u�f�[�^�擾
	wk->playSave = SaveData_GetTowerPlayData(savedata);
	wk->scoreSave = SaveData_GetTowerScoreData(savedata);

	//�}�W�b�N�i���o�[�ݒ�
	wk->magicNo = BTOWER_SCRWORK_MAGIC;

	//�Z�[�u�t���O�𖳌���ԂɃ��Z�b�g
	TowerPlayData_SetSaveFlag(wk->playSave,FALSE);
	
	if(init == BTWR_PLAY_NEW){
		wk->play_mode = playmode;
		wk->member_num = (u8)TowerScrTools_GetMemberNum(wk->play_mode);
		wk->now_round = 1;
		wk->now_win = 0;

		for(i = 0;i < BTOWER_STOCK_MEMBER_MAX;i++){
			wk->member[i] = BTWR_NULL_POKE;
		}
		for(i = 0;i < BTOWER_STOCK_TRAINER_MAX;i++){
			wk->trainer[i] = BTWR_NULL_TRAINER;
		}
		//�Z�[�u�f�[�^������
		TowerPlayData_Clear(wk->playSave);
		//�v���C���[�h�����͂��̎��_�ŃZ�[�u�f�[�^�ɏ����o��
		buf8 = wk->play_mode;
		TowerPlayData_Put(wk->playSave,BTWR_PSD_playmode,&buf8);

#ifdef BTOWER_AUTO_DEB
		if(wk->play_mode == BTWR_MODE_WIFI){
			OS_Printf(" #WifiTowerStage=%d\n",DebugBTowerAutoStage++);
		}
#endif
	}else{
		//���݂̃v���C�i�s�f�[�^�擾
		wk->play_mode = (u8)TowerPlayData_Get(wk->playSave,BTWR_PSD_playmode,NULL);
		wk->now_round = (u8)TowerPlayData_Get(wk->playSave,BTWR_PSD_round,NULL);
		wk->now_win = wk->now_round-1;

		wk->member_num = (u8)TowerScrTools_GetMemberNum(wk->play_mode);

		//�I�΂�Ă���|�P����No
		TowerPlayData_Get(wk->playSave,BTWR_PSD_pokeno,wk->member);

		//���I�ς݂̃g���[�i�[No
		TowerPlayData_Get(wk->playSave,BTWR_PSD_trainer,wk->trainer);

		//�v���C�����_���V�[�h�擾
		wk->play_rnd_seed = TowerPlayData_Get(wk->playSave,BTWR_PSD_rnd_seed,NULL);
		OS_Printf("TowerContinueRndSeed = %d\n",wk->play_rnd_seed);
		
		if(wk->play_mode == BTWR_MODE_MULTI){
			wk->partner = (u8)TowerPlayData_Get(wk->playSave,BTWR_PSD_partner,NULL);
			//�p�[�g�i�[�g���[�i�[�f�[�^�Đ���
			TowerPlayData_Get(wk->playSave,BTWR_PSD_pare_poke,&(wk->five_poke[wk->partner]));
			RomBattleTowerPartnerDataMake(wk,&wk->five_data[wk->partner],
				TOWER_FIVE_FIRST+wk->partner,
				TowerPlayData_Get(wk->playSave,BTWR_PSD_pare_itemfix,NULL),
				&(wk->five_poke[wk->partner]),wk->heapID);
		}
	}
	//�����̐��ʂ��擾
	wk->my_sex = MyStatus_GetMySex(SaveData_GetMyStatus(savedata));

	//���݂̃��R�[�h���擾
	if(wk->play_mode != BTWR_MODE_RETRY){
		record = SaveData_GetRecord(savedata);
		//���݂̘A�����͒��풆�t���O��on�̂Ƃ����������p��
		chg_flg = TowerScoreData_SetFlags(wk->scoreSave,
					BTWR_SFLAG_SINGLE_RECORD+wk->play_mode,BTWR_DATA_get);
		if(chg_flg){
			wk->renshou = (u16)RECORD_Get(record,RECID_RENSHOU_SINGLE_CNT+wk->play_mode*2);	
		}
		wk->win_cnt = RECORD_Get(record,RECID_BTOWER_WIN);	
		wk->stage = TowerScoreData_SetStage(wk->scoreSave,wk->play_mode,BTWR_DATA_get);
	}

	return wk;
}

/**
 *	@brief	���[�N�G���A���J������
 */
void TowerScr_WorkRelease(BTOWER_SCRWORK* wk)
{
	int	heap;

	if(wk == NULL){
		return;
	}
	GF_ASSERT(wk->magicNo == BTOWER_SCRWORK_MAGIC && "btower word is crash");
	heap = wk->heapID;

	MI_CpuClear8(wk,sizeof(BTOWER_SCRWORK));
	sys_FreeMemoryEz(wk);
	wk = NULL;

	HeapStatePop();
	HeapStateCheck(heap);

	sys_DeleteHeap(heap);
}


//***************************************************************
//===============================================================
//	���[�N�Ɉˑ�����T�u�c�[��
//===============================================================
//***************************************************************

/**
 *	@brief	�o�g���^���[�p�|�P�����I���ďo��
 */
void TowerScr_SelectPoke(BTOWER_SCRWORK* wk,
		GMEVENT_CONTROL *ev_work,void** proc_wk)
{
	EventCmd_BTowerPokeSelectCall(ev_work,proc_wk,
		PL_MODE_BATTLE_TOWER,PST_MODE_NORMAL,
		wk->member_num,wk->member_num,100,0);
}

/**
 *	@brief	�I�������|�P�������擾
 *	
 *	@retval	TRUE	�I������
 *	@retval	FALSE	�I�������ɂ�߂�
 */
BOOL TowerScr_GetEntryPoke(BTOWER_SCRWORK* wk,void** app_work,SAVEDATA* sv)
{
	u16	i = 0;
	PLIST_DATA* pld = *app_work;
	POKEPARTY* party;
	POKEMON_PARAM* pp;

#ifdef BTOWER_AUTO_DEB
	if(pld->ret_mode != 0){
		sys_FreeMemoryEz(*app_work);
		*app_work = NULL;
		return FALSE;
	}
#else	//BTOWER_AUTO_DEB
	//�f�[�^�擾
	if(pld->ret_mode != 0 || pld->ret_sel == PL_SEL_POS_EXIT){
		sys_FreeMemoryEz(*app_work);
		*app_work = NULL;
		return FALSE;
	}
#endif	//BTOWER_AUTO_DEB
	party = SaveData_GetTemotiPokemon(sv);
	
	for(i = 0;i < wk->member_num;i++){
		wk->member[i] = pld->in_num[i]-1;
		pp = PokeParty_GetMemberPointer(party,wk->member[i]);
		wk->mem_poke[i] = PokeParaGet(pp,ID_PARA_monsno,NULL);	
		wk->mem_item[i] = PokeParaGet(pp,ID_PARA_item,NULL);	
	}
	//���[�N�̈���
	sys_FreeMemoryEz(*app_work);
	*app_work = NULL;
	return TRUE;
}

/**
 *	@brief	�Q���w�肵���莝���|�P�����̏����`�F�b�N
 *
 *	@retval	0	�Q��OK
 *	@retval	1	�����|�P����������
 *	@retval 2	�����A�C�e���������Ă���
 */
int TowerScr_CheckEntryPoke(BTOWER_SCRWORK* wk,SAVEDATA* savedata)
{
	u16	i = 0,j = 0;
	u16	monsno[BTOWER_STOCK_MEMBER_MAX],itemno[BTOWER_STOCK_MEMBER_MAX];
	POKEPARTY* party;
	POKEMON_PARAM* poke;

	party = SaveData_GetTemotiPokemon(savedata);

	for(i = 0;i < wk->member_num;i++){
		poke = PokeParty_GetMemberPointer(party,wk->member[i]);
		monsno[i] = PokeParaGet(poke,ID_PARA_monsno,NULL);
		itemno[i] = PokeParaGet(poke,ID_PARA_item,NULL);

		if(i == 0){
			continue;
		}
		for(j = 0;j < i;j++){
			if(monsno[i] == monsno[j]){
				//�����|�P����������
				return 1;
			}
			if((itemno[i] != 0) && (itemno[i] == itemno[j])){
				//�����A�C�e���������Ă���
				return 2;
			}
		}
	}
	return 0;
}

static BOOL is_trainer_conflict(u16* trainer,u16 id,u16 num)
{
	u16 i;
	for(i = 0;i < num;i++){
		if(trainer[i] == id){
			return TRUE;
		}
	}
	return FALSE;
}

/**
 *	@brief�@�ΐ�g���[�i�[No���I
 */
void TowerScr_BtlTrainerNoSet(BTOWER_SCRWORK* wk,SAVEDATA* sv)
{
	int i;
	u16	no,stage;
	
	if(	wk->play_mode == BTWR_MODE_MULTI ||
		wk->play_mode == BTWR_MODE_COMM_MULTI){
		if(wk->play_mode == BTWR_MODE_COMM_MULTI && wk->pare_stage > wk->stage){
			stage = wk->pare_stage;	//�ʐM���ɂ͎��񐔂̑����ق��Œ��I
		}else{
			stage = wk->stage;
		}
		for(i = 0;i < BTOWER_STOCK_TRAINER_MAX;i++){
			do{
				no = BattleTowerTrainerNoGet(wk,stage,i/2,wk->play_mode);
			}while(is_trainer_conflict(wk->trainer,no,i));
#ifdef BTOWER_AUTO_DEB
#if 0
			wk->trainer[i] = DebugBTowerAutoTrainer;
			OS_Printf(" #TowerStage = %d,%d\n",DebugBTowerAutoStage,DebugBTowerAutoTrainer);
			if(DebugBTowerAutoTrainer++ >= 299){
				DebugBTowerAutoTrainer = 0;
				DebugBTowerAutoStage++;
			}
#endif
			wk->trainer[i] = no;
			if(DebugBTowerAutoTrainer++ >= 299){
				DebugBTowerAutoStage++;
			}
			OS_Printf(" #TowerStage = %d,%d\n",DebugBTowerAutoStage,DebugBTowerAutoTrainer);
#else		
			wk->trainer[i] = no;
#endif
		}
	}else{
		for(i = 0;i < (BTOWER_STOCK_TRAINER_MAX/2);i++){
			do{
				no = BattleTowerTrainerNoGet(wk,wk->stage,i,wk->play_mode);
			}while(is_trainer_conflict(wk->trainer,no,i));
#ifdef BTOWER_AUTO_DEB
#if 0
			wk->trainer[i] = DebugBTowerAutoTrainer;
			OS_Printf(" #TowerStage = %d,%d\n",DebugBTowerAutoStage,DebugBTowerAutoTrainer);
			if(DebugBTowerAutoTrainer++ >= 299){
				DebugBTowerAutoTrainer = 0;
				DebugBTowerAutoStage++;
			}
#endif
			if(DebugBTowerAutoTrainer++ >= 299){
				DebugBTowerAutoStage++;
			}
			OS_Printf(" #TowerStage = %d,%d\n",DebugBTowerAutoStage,DebugBTowerAutoTrainer);
			wk->trainer[i] = 25;//no;
#else		
			wk->trainer[i] = no;
#endif
		}
	}
}

/**
 *	@brief	���݂̃��E���h�����X�N���v�g���[�N�Ɏ擾����
 */
u16	TowerScr_GetNowRound(BTOWER_SCRWORK* wk)
{
	return wk->now_round;
}

/**
 *	@brief	���E���h�����C���N�������g
 */
u16	TowerScr_IncRound(BTOWER_SCRWORK* wk)
{
	++wk->now_win;	//���������C���N�������g

	//�����_���̎�X�V
	wk->play_rnd_seed = BtlTower_PlayFixRand(wk->play_rnd_seed);

	OS_Printf("TowerRoundInc = %d\n",wk->play_rnd_seed);

	return ++wk->now_round;
}

/**
 *	@brief	7�A�����Ă��邩�ǂ����`�F�b�N
 */
BOOL TowerScr_IsClear(BTOWER_SCRWORK* wk)
{
	if(wk->clear_f){
		return TRUE;
	}
	if(wk->now_round > BTWR_CLEAR_WINCNT){
		//�N���A�t���Oon
		wk->clear_f = 1;
		return TRUE;
	}
	return FALSE;
}

/**
 *	@brief	�v���C���̘A�������擾����
 */
u16 TowerScr_GetRenshouCount(BTOWER_SCRWORK* wk)
{
	if((u32)wk->renshou+wk->now_win > 0xFFFF){
		return 0xFFFF;
	}else{
		return wk->renshou+wk->now_win;
	}
}

/**
 *	@brief	�ő�A���L�^�X�V�ԑg�쐬�֐�
 */
static void towerscr_MakeTVRenshouMaxUpdate(BTOWER_SCRWORK* wk,FIELDSYS_WORK* fsys,u16 renshou)
{
	POKEPARTY *party;

	if(	wk->play_mode != BTWR_MODE_SINGLE &&
		wk->play_mode != BTWR_MODE_DOUBLE){
		return;
	}
	party = SaveData_GetTemotiPokemon(fsys->savedata);

	if(wk->play_mode == BTWR_MODE_SINGLE){
		TVTOPIC_Entry_Record_BTower(fsys,
			renshou,PokeParty_GetMemberPointer(party,wk->member[0]), TRUE);
	}else{
		TVTOPIC_Entry_Record_BTower(fsys,
			renshou,PokeParty_GetMemberPointer(party,wk->member[0]), FALSE);
	}
}

/**
 *	@brief	7�l���������܂��͕��������̋��ʃf�[�^�Z�[�u����
 *
 *	@param	now_renshou	���݂̘A����
 */
static void towerscr_SetCommonScore(BTOWER_SCRWORK* wk,SAVEDATA* sv,u8 win_f,u16 now_renshou)
{
	u8	buf8;

	switch(wk->play_mode){
	case BTWR_MODE_SINGLE:
		//�|�P�����f�[�^�Z�b�g
		towerscr_SaveMemberPokeData(wk,sv,BTWR_SCORE_POKE_SINGLE);
	case BTWR_MODE_DOUBLE:
		if(now_renshou >= 7){
			//TV�C���^�r���[�f�[�^�Z�b�g(�V���O���ƃ_�u���Ŏ��s)
			TVTOPIC_BTowerTemp_Set(SaveData_GetTvWork(sv),win_f,now_renshou);
		}
		break;
	case BTWR_MODE_WIFI:
		//�|�P�����f�[�^�Z�b�g
		towerscr_SaveMemberPokeData(wk,sv,BTWR_SCORE_POKE_WIFI);
		//�X�R�A�����o��
		TowerPlayData_WifiRecordAdd(wk->playSave,wk->rec_down,wk->rec_turn,wk->rec_damage);

		//�v���C���[�h�����o��
		buf8 = wk->play_mode;
		TowerPlayData_Put(wk->playSave,BTWR_PSD_playmode,&buf8);
		//���E���h�������o��
		buf8 = wk->now_round;
		TowerPlayData_Put(wk->playSave,BTWR_PSD_round,&buf8);
		
		TowerScoreData_SetWifiScore(wk->scoreSave,wk->playSave);
		break;
	default:
		break;
	}

}

/**
 *	@brief	�s�폈��	
 */
void TowerScr_SetLoseScore(BTOWER_SCRWORK* wk,FIELDSYS_WORK* fsys)
{
	u32	ret = 0;
	int	id;
	u16	before,after,chg_flg;
	SAVEDATA* savedata = fsys->savedata;
	RECORD* record = SaveData_GetRecord(savedata);
	
	if(wk->play_mode == BTWR_MODE_RETRY){
		return;
	}
	
	OS_Printf("TowerLoseScoreSet -> mode = %d\n",wk->play_mode);

	id = wk->play_mode*2+RECID_RENSHOU_SINGLE;

	//���݂̍ő�A�����擾
	before = RECORD_Get(record,id);
	//�ő�A�����X�V
	after = RECORD_SetIfLarge(record,id,wk->renshou+wk->now_win);

	//�X�V���Ă���||(�L�^��7�̔{��&&�O��̒l������)�Ȃ�ԑg�쐬
	if(after > 1){
		if(	(before < after) ||
			((before == after) && (after%7==0)) ){
			towerscr_MakeTVRenshouMaxUpdate(wk,fsys,after);
		}
	}
	//���у��j�^�p�Ɍ��݂̘A�����������o���Ă���
	chg_flg = TowerScoreData_SetFlags(wk->scoreSave,
			BTWR_SFLAG_SINGLE_RECORD+wk->play_mode,BTWR_DATA_get);
	if(chg_flg){	//�A���L�^���풆�Ȃ���Z
		ret = RECORD_Add(record,id+1,wk->now_win);
	}else{	//�O�񕉂��Ă���΃Z�b�g
		ret = RECORD_Set(record,id+1,wk->now_win);
	}

	//���R�[�h���풆�t���O�𗎂Ƃ�
	TowerScoreData_SetFlags(wk->scoreSave,BTWR_SFLAG_SINGLE_RECORD+wk->play_mode,BTWR_DATA_reset);

	//���׏������X�V
	RECORD_Add(record,RECID_BTOWER_WIN,wk->now_win);
	//���݂̎��񐔃��Z�b�g
	TowerScoreData_SetStage(wk->scoreSave,wk->play_mode,BTWR_DATA_reset);
	//�o�g���^���[�ւ̃`�������W���ǉ�
	RECORD_Add(SaveData_GetRecord(savedata),RECID_BTOWER_CHALLENGE,1);
	
	//�A�����{�������炦�邩�ǂ����̃t���O���Z�b�g
	towerscr_IfRenshouPrizeGet(wk);

	//�����������ʃf�[�^����
	ret+=1;
	if(ret > 9999){
		ret = 9999;	
	}
	towerscr_SetCommonScore(wk,savedata,FALSE,ret);
}

/**
 *	@brief	�N���A����
 */
void TowerScr_SetClearScore(BTOWER_SCRWORK* wk,FIELDSYS_WORK* fsys)
{
	u32	ret = 0;
	int	id;
	void* note;
	u16	before,after,chg_flg;
	RECORD*  record;
	SAVEDATA	*savedata = fsys->savedata;
		
	if(wk->play_mode == BTWR_MODE_RETRY){
		return;
	}
	OS_Printf("TowerClearScoreSet -> mode = %d\n",wk->play_mode);
	
	record = SaveData_GetRecord(savedata);
	id = wk->play_mode*2+RECID_RENSHOU_SINGLE;
	
	//���݂̘A�����������o��
	chg_flg = TowerScoreData_SetFlags(wk->scoreSave,
			BTWR_SFLAG_SINGLE_RECORD+wk->play_mode,BTWR_DATA_get);

	if(chg_flg){	//���݂��A���L�^���풆�Ȃ���Z
		ret = RECORD_Add(record,id+1,BTWR_CLEAR_WINCNT);
	}else{	//�O�񕉂��Ă��ꍇ�͈�U���Z�b�g
		ret = RECORD_Set(record,id+1,BTWR_CLEAR_WINCNT);
	}
	//���R�[�h���풆�t���O�𗧂Ă�
	TowerScoreData_SetFlags(wk->scoreSave,BTWR_SFLAG_SINGLE_RECORD+wk->play_mode,BTWR_DATA_set);

	//���݂̍ő�A�����擾
	before = RECORD_Get(record,id);
	//�ő�A�����X�V
	after = RECORD_SetIfLarge(record,id,ret);

	//�X�V���Ă���ԑg�쐬
#if 0
	if(before < after){
		towerscr_MakeTVRenshouMaxUpdate(wk,fsys,after);
	}
#endif
	//���׏������X�V
	RECORD_Add(record,RECID_BTOWER_WIN,BTWR_CLEAR_WINCNT);
	//���񐔃v���X
	TowerScoreData_SetStage(wk->scoreSave,wk->play_mode,BTWR_DATA_inc);
	//�o�g���^���[�ւ̃`�������W���ǉ�
	RECORD_Add(record,RECID_BTOWER_CHALLENGE,1);
	//�X�R�A���Z
	RECORD_Score_Add(record,SCORE_ID_BTOWER_7WIN);
	
	//�A�����{�������炦�邩�ǂ����̃t���O���Z�b�g
	towerscr_IfRenshouPrizeGet(wk);

	//�����������ʃf�[�^����
	towerscr_SetCommonScore(wk,savedata,TRUE,ret);

	//�`���m�[�g(�ʐM�}���`&wifi�̂�)
	if(	wk->play_mode == BTWR_MODE_COMM_MULTI ||
		wk->play_mode == BTWR_MODE_WIFI){
		note = FNOTE_SioBattleTowerDataMake(wk->heapID);
		FNOTE_DataSave( fsys->fnote,note, FNOTE_TYPE_SIO );
	}
}

/**
 *	@brief	�x�ނƂ��Ɍ��݂̃v���C�󋵂��Z�[�u�ɏ����o��
 */
void TowerScr_SaveRestPlayData(BTOWER_SCRWORK* wk)
{
	u16	i;
	u8	buf8[4];

	//�v���C���[�h�����o��
	buf8[0] = wk->play_mode;
	TowerPlayData_Put(wk->playSave,BTWR_PSD_playmode,buf8);
	
	//���E���h�������o��
	buf8[0] = wk->now_round;
	TowerPlayData_Put(wk->playSave,BTWR_PSD_round,buf8);

	//�I�񂾃|�P����No
	TowerPlayData_Put(wk->playSave,BTWR_PSD_pokeno,wk->member);
	
	//�o�g�����я����o��
	TowerPlayData_WifiRecordAdd(wk->playSave,wk->rec_down,wk->rec_turn,wk->rec_damage);

	//���I���ꂽ�g���[�i�[No�����o��
	TowerPlayData_Put(wk->playSave,BTWR_PSD_trainer,wk->trainer);
	
	//�v���C�����_���V�[�h�ۑ�
	TowerPlayData_Put(wk->playSave,BTWR_PSD_rnd_seed,&(wk->play_rnd_seed));
	OS_Printf("TowerRestRndSeed = %d\n",wk->play_rnd_seed);
	
	//�Z�[�u�t���O��L����ԂɃ��Z�b�g
	TowerPlayData_SetSaveFlag(wk->playSave,TRUE);

	if(wk->play_mode != BTWR_MODE_MULTI){
		return;
	}
	//AI�}���`���[�h�Ȃ�p�[�g�i�[���o���Ă���
	buf8[0] = wk->partner;
	TowerPlayData_Put(wk->playSave,BTWR_PSD_partner,buf8);

	//�p�[�g�i�[�̃|�P�����p�����[�^�������Ă���
	TowerPlayData_Put(wk->playSave,BTWR_PSD_pare_poke,&(wk->five_poke[wk->partner]));
	//�A�C�e�����Œ肾�������ǂ��������Ă���
	TowerPlayData_Put(wk->playSave,BTWR_PSD_pare_itemfix,&(wk->five_item[wk->partner]));
	//�v���C�����_���V�[�h�������Ă���
	
}

/**
 *	@brief	�ΐ�g���[�i�[���I
 */
void TowerScr_ChoiceBtlPartner(BTOWER_SCRWORK* wk,SAVEDATA* sv)
{
	int i;
	u16	monsno[2];
	u16	itemno[2];
	
	switch(wk->play_mode){
	case BTWR_MODE_WIFI:
	case BTWR_MODE_RETRY:
		btltower_BtlPartnerSelectWifi(sv,wk->tr_data,wk->now_round-1);
		break;
	case BTWR_MODE_MULTI:
	case BTWR_MODE_COMM_MULTI:
		RomBattleTowerTrainerDataMake(wk,&(wk->tr_data[0]),
			wk->trainer[(wk->now_round-1)*2+0],wk->member_num,NULL,NULL,NULL,wk->heapID);
		
		//�����X�^�[No�̏d���`�F�b�N
		for(i = 0;i < wk->member_num;i++){
			monsno[i] = wk->tr_data[0].btpwd[i].mons_no;
			itemno[i] = wk->tr_data[0].btpwd[i].item_no;
		}
		RomBattleTowerTrainerDataMake(wk,&(wk->tr_data[1]),
			wk->trainer[(wk->now_round-1)*2+1],wk->member_num,monsno,itemno,NULL,wk->heapID);
		break;
	case BTWR_MODE_DOUBLE:
	case BTWR_MODE_SINGLE:
	default:
		RomBattleTowerTrainerDataMake(wk,&(wk->tr_data[0]),
			wk->trainer[wk->now_round-1],wk->member_num,NULL,NULL,NULL,wk->heapID);
		break;
	}
}

/**
 *	@brief	AI�}���`�y�A�|�P�������I
 */
void TowerScr_ChoiceBtlSeven(BTOWER_SCRWORK* wk)
{
	int i;

	for(i = 0;i < BTWR_FIVE_NUM;i++){
		wk->five_item[i] = (u8)RomBattleTowerTrainerDataMake(wk,&(wk->five_data[i]),
			TOWER_FIVE_FIRST+i,wk->member_num,wk->mem_poke,wk->mem_item,&(wk->five_poke[i]),wk->heapID);
	}
}

/**
 *	@brief	�ΐ�g���[�i�[OBJ�R�[�h�擾
 */
u16 TowerScr_GetEnemyObj(BTOWER_SCRWORK* wk,u16 idx)
{
	//�g���[�i�[�^�C�v����OBJ�R�[�h���擾���Ă���
	return BtlTower_TrType2ObjCode(wk->tr_data[idx].bt_trd.tr_type);
}

/**
 *	@brief	�퓬�Ăяo��
 */
void TowerScr_LocalBattleCall(GMEVENT_CONTROL* event,BTOWER_SCRWORK* wk,BOOL* win_flag)
{
	EventCmd_TowerLocalBattle(event,wk,win_flag);
}

/**
 *	@brief	���݂̃v���C���[�h��Ԃ�
 */
u16	TowerScr_GetPlayMode(BTOWER_SCRWORK* wk)
{
	return wk->play_mode;
}

/**
 *	@brief	���[�_�[�N���A�t���O�𗧂Ă�
 */
void TowerScr_SetLeaderClearFlag(BTOWER_SCRWORK* wk,u16 mode)
{
	wk->leader_f = mode;
}

/**
 *	@brief	���[�_�[�N���A�t���O���擾����
 */
u16	TowerScr_GetLeaderClearFlag(BTOWER_SCRWORK* wk)
{
	return (u16)wk->leader_f;
}

/**
 *	@brief	�^���[�N���A���Ƀo�g���|�C���g�����Z����
 *
 *	@return	�V���Ɏ擾�����o�g���|�C���g
 */
u16	TowerScr_AddBtlPoint(BTOWER_SCRWORK* wk)
{
	u16	stage;
	u16	point = 0;
	static const u8	bpoint_wifi[] = {0,
		BTLPOINT_VAL_TOWER_WIFI1,BTLPOINT_VAL_TOWER_WIFI2,BTLPOINT_VAL_TOWER_WIFI3,
		BTLPOINT_VAL_TOWER_WIFI4,BTLPOINT_VAL_TOWER_WIFI5,BTLPOINT_VAL_TOWER_WIFI6,
		BTLPOINT_VAL_TOWER_WIFI7,BTLPOINT_VAL_TOWER_WIFI8,BTLPOINT_VAL_TOWER_WIFI9,
		BTLPOINT_VAL_TOWER_WIFI10,
	};
	static const u8 bpoint_normal[] = {0,
		BTLPOINT_VAL_TOWER_STAGE1,BTLPOINT_VAL_TOWER_STAGE2,BTLPOINT_VAL_TOWER_STAGE3,
		BTLPOINT_VAL_TOWER_STAGE4,BTLPOINT_VAL_TOWER_STAGE5,BTLPOINT_VAL_TOWER_STAGE6,
		BTLPOINT_VAL_TOWER_STAGE7,
	};

	if(wk->play_mode == BTWR_MODE_RETRY){
		return 0;
	}
	if(wk->play_mode == BTWR_MODE_WIFI){
		//�����N����
		point = bpoint_wifi[TowerScoreData_SetWifiRank(wk->scoreSave,BTWR_DATA_get)];
	}else{
		//���񐔂���
		stage = TowerScoreData_SetStage(wk->scoreSave,wk->play_mode,BTWR_DATA_get);
		if(wk->leader_f){
			point = BTLPOINT_VAL_TOWER_LEADER;
		}else if(stage >= 7){
			point = BTLPOINT_VAL_TOWER_STAGE8;
		}else{
			point = bpoint_normal[stage];
		}
	}
	//�o�g���|�C���g�����Z����
	TowerScoreData_SetBattlePoint(wk->scoreSave,point,BTWR_DATA_add);
	return point;
}

/**
 *	@brief	�V���O���ŘA���������̂��J���̃g���t�B�[��������t���O�𗧂ĂĂ���
 */
u16	TowerScr_GoodsFlagSet(BTOWER_SCRWORK* wk,SAVEDATA* sv)
{
	u8	id,fid;
	u16	record,goods,ret;

	record = TowerScrTools_GetRenshouRecord(sv,wk->play_mode);

	if(record < BTWR_50_RENSHOU_CNT){
		return 0;
	}
	if(record >= BTWR_100_RENSHOU_CNT){
		if(TowerScoreData_SetFlags(wk->scoreSave,BTWR_SFLAG_GOLD_GET,BTWR_DATA_get)){
			return 0;
		}
	}else{
		if(TowerScoreData_SetFlags(wk->scoreSave,BTWR_SFLAG_SILVER_GET,BTWR_DATA_get)){
			return 0;
		}
	}
	return 1;
}

/**
 *	@brief	���݂�WIFI�����N�𑀍삵�ĕԂ�
 */
u16	TowerScr_SetWifiRank(BTOWER_SCRWORK* wk,SAVEDATA* sv,u8 mode)
{
	u8	ct,rank;
	BTLTOWER_SCOREWORK* score = SaveData_GetTowerScoreData(sv);
	
	static const u8	btower_wifi_rankdown[] = {
	 0,5,4,4,3,3,2,2,1,1,
//	 0,2,1,1,1,1,1,1,1,1,
	};

	switch(mode){
	//Get
	case 0:
		return (u16)TowerScoreData_SetWifiRank(score,BTWR_DATA_get);
	case 1:	//Inc
		//�A���s��t���O�𗎂Ƃ�
		TowerScoreData_SetFlags(score,BTWR_SFLAG_WIFI_LOSE_F,BTWR_DATA_reset);
		//���݂̃����N���擾
		rank = TowerScoreData_SetWifiRank(score,BTWR_DATA_get);

		if(rank == 10){	
			return 0;	//�����オ��Ȃ�
		}
		//�����N�A�b�v����
		TowerScoreData_SetWifiRank(score,BTWR_DATA_inc);

		//�����N5�ȏ�ɃA�b�v���Ă��烊�{�������炦��
		if(rank+1 >= 5){
			wk->prize_f = 1;
		}
		return 1;
	case 2:	//dec
		//���݂̘A���s�퐔���J�E���g
		ct = TowerScoreData_SetWifiLoseCount(score,BTWR_DATA_inc);
		rank = TowerScoreData_SetWifiRank(score,BTWR_DATA_get);

		if(rank == 1){
			return 0;
		}
		//�����N�ʔs��J�E���g�`�F�b�N
		if(ct >= btower_wifi_rankdown[rank-1] ){
			//�����N�_�E��
			TowerScoreData_SetWifiRank(score,BTWR_DATA_dec);
			//�A���s�퐔�ƘA���s��t���O�����Z�b�g
			TowerScoreData_SetWifiLoseCount(score,BTWR_DATA_reset);
			TowerScoreData_SetFlags(score,BTWR_SFLAG_WIFI_LOSE_F,BTWR_DATA_reset);
			return 1;
		}
		return 0;
	}
	return 0;
}

/**
 *	@brief	���[�_�[��|�������J�����{����������
 */
u16 TowerScr_LeaderRibbonSet(BTOWER_SCRWORK* wk,SAVEDATA* sv)
{
	if(wk->play_mode != BTWR_MODE_SINGLE){
		return 0;
	}
	
	//�����o�[�Ƀ��{���Z�b�g
	switch(wk->leader_f){
	case 1:
		return towerscr_PokeRibbonSet(sv,ID_PARA_sinou_battle_tower_ttwin_first,wk);
	case 2:
		return towerscr_PokeRibbonSet(sv,ID_PARA_sinou_battle_tower_ttwin_second,wk);
	}
	return 0;
}

/**
 *	@brief	�t���O�������Ă�����A���̂��J�����{����������	
 */
u16 TowerScr_RenshouRibbonSet(BTOWER_SCRWORK* wk,SAVEDATA* sv)
{
	u8	id,fid;
	u16	record,goods,ret;
	UNDERGROUNDDATA* gSave;

	if(wk->play_mode == BTWR_MODE_RETRY){
		return 0;
	}
	if(!wk->prize_f){
		return 0;
	}
	switch(wk->play_mode){
	case BTWR_MODE_DOUBLE:
		id = ID_PARA_sinou_battle_tower_2vs2_win50;
		break;
	case BTWR_MODE_MULTI:
		id = ID_PARA_sinou_battle_tower_aimulti_win50;
		break;
	case BTWR_MODE_COMM_MULTI:
		id = ID_PARA_sinou_battle_tower_siomulti_win50;
		break;
	case BTWR_MODE_WIFI:
		id = ID_PARA_sinou_battle_tower_wifi_rank5;
		break;
	}
	//�����o�[�Ƀ��{���Z�b�g
	return towerscr_PokeRibbonSet(sv,id,wk);
}

/**
 *	@biref	�v���C�����_���V�[�h���X�V����
 */
u16 TowerScr_PlayRandUpdate(BTOWER_SCRWORK* wk,SAVEDATA* sv)
{
	u8	chg_flg;
	//���݃`�������W�p�������ǂ����H
	chg_flg = TowerScoreData_SetFlags(wk->scoreSave,
			BTWR_SFLAG_SINGLE_RECORD+wk->play_mode,BTWR_DATA_get);
	
	if(!chg_flg){
		//�v���C�X�V�����_���V�[�h�����l�擾&���t�X�V�V�[�h�X�V
		wk->play_rnd_seed = BtlTower_UpdatePlayRndSeed(sv);
	}else{
		//�L�^����J�n����day�V�[�h����_�ɁA���݂�play�V�[�h���擾����
		wk->play_rnd_seed = BtlTower_GetContinuePlayRndSeed(sv);
	}
	return (wk->play_rnd_seed/65535);
}

//////////////////////////////////////////////////////////////////////////////
//���[�J���֐��Q
//
/**
 *	@brief	�|�P�����Ƀ��{��������@�T�u
 */
static u16 towerscr_PokeRibbonSet(SAVEDATA* sv,u8 ribbon,BTOWER_SCRWORK* wk)
{
	u8	flag = 1;
	u8 ct;
	int i;
	POKEPARTY	*party;
	POKEMON_PARAM* pp;
	
	party = SaveData_GetTemotiPokemon(sv);

	ct = 0;
	for(i = 0;i < wk->member_num;i++){
		pp = PokeParty_GetMemberPointer(party,wk->member[i]);
		if(PokeParaGet(pp,ribbon,NULL)){
			continue;	//���Ɏ����Ă�
		}
		PokeParaPut(pp,ribbon,&flag);
		++ct;
	}
	if(ct == 0){
		//�݂�Ȃ��������Ă�
		return FALSE;
	}
	return TRUE;
}

/**
 *	@brief	�A���̂��J�����{�������炦�邩�ǂ����̃t���O�𗧂ĂĂ���
 */
static u16 towerscr_IfRenshouPrizeGet(BTOWER_SCRWORK* wk)
{
	u16 win;
	if(	wk->play_mode == BTWR_MODE_RETRY ||
		wk->play_mode == BTWR_MODE_SINGLE ||
		wk->play_mode == BTWR_MODE_WIFI){
		return 0;
	}
	win = wk->renshou+wk->now_win;

	//50�A���ȏ�ł��炦��
	if(win < BTWR_50_RENSHOU_CNT){
		return 0;
	}
	//prize get�t���O�𗧂ĂĂ���
	wk->prize_f = 1;
	return 1;
}


/**
 *	@brief	�Q�������|�P�����̃p�����[�^��B_TOWER_POKEMON�^�Ƀp�b�N����
 */
static void towerscr_PokeDataPack(B_TOWER_POKEMON* dat,POKEMON_PARAM* pp)
{
	int i;
	
	//mons_no/form_no/item_no
	dat->mons_no = PokeParaGet(pp,ID_PARA_monsno,NULL);
	dat->form_no = PokeParaGet(pp,ID_PARA_form_no,NULL);
	dat->item_no = PokeParaGet(pp,ID_PARA_item,NULL);

	//waza/pp_count
	for(i = 0;i < WAZA_TEMOTI_MAX;i++){
		dat->waza[i] = PokeParaGet(pp,ID_PARA_waza1+i,NULL);
		dat->pp_count |= ((PokeParaGet(pp,ID_PARA_pp_count1+i,NULL)) << (i*2));
	}
	//country,id,personal
	dat->country_code = PokeParaGet(pp,ID_PARA_country_code,NULL);
	dat->id_no = PokeParaGet(pp,ID_PARA_id_no,NULL);
	dat->personal_rnd = PokeParaGet(pp,ID_PARA_personal_rnd,NULL);

	//power_rnd
	dat->power_rnd = PokeParaGet(pp,ID_PARA_power_rnd,NULL);

	//exp
	for(i = 0;i < 6;i++){
		dat->exp[i] = PokeParaGet(pp,ID_PARA_hp_exp+i,NULL);
	}
	//tokusei,natukido
	dat->tokusei = PokeParaGet(pp,ID_PARA_speabino,NULL);
	dat->natuki = PokeParaGet(pp,ID_PARA_friend,NULL);
	
	//�j�b�N�l�[��
	PokeParaGet(pp,ID_PARA_nickname,dat->nickname);
}

/**
 *	@brief	�Q�������|�P�����̃p�����[�^��ۑ�����
 */
static void towerscr_SaveMemberPokeData(BTOWER_SCRWORK* wk,SAVEDATA* sv,BTWR_SCORE_POKE_DATA mode)
{
	int i = 0;
	B_TOWER_POKEMON* dat;
	POKEPARTY	*party;
	POKEMON_PARAM* pp;
	
	dat = sys_AllocMemoryLo(wk->heapID,sizeof(B_TOWER_POKEMON)*3);
	MI_CpuClear8(dat,sizeof(B_TOWER_POKEMON)*3);

	party = SaveData_GetTemotiPokemon(sv);
	for(i = 0;i < 3;i++){
		pp = PokeParty_GetMemberPointer(party,wk->member[i]);
		towerscr_PokeDataPack(&(dat[i]),pp);	
	}
	TowerScoreData_SetUsePokeData(wk->scoreSave,mode,dat);

	MI_CpuClear8(dat,sizeof(B_TOWER_POKEMON)*3);
	sys_FreeMemoryEz(dat);
}
