/**
 *	@file	b_tower.c
 *	@brief	�o�g���^���[�@�Z�[�u�f�[�^
 *	@author	Miyuki Iwasawa
 *	@date	06.04.14
 */

#include "common.h"
#include "savedata/savedata_def.h"
#include "savedata/savedata.h"

#include "system/gamedata.h"
#include "system/pms_data.h"
#include "system/buflen.h"
#include "system/msgdata.h"
#include "battle/battle_common.h"
#include "battle/b_tower_data.h"

#include "b_tower_local.h"
#define _B_TOWER_H_GLOBAL
#include "savedata/b_tower.h"
#include "field/b_tower_scr_def.h"
#include "libdpw/dpw_bt.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_btower_app.h"

#ifdef _NITRO
// �\���̂��z��̃T�C�Y�ƂȂ��Ă��邩�`�F�b�N
SDK_COMPILER_ASSERT(sizeof(B_TOWER_LEADER_DATA) == 34);
SDK_COMPILER_ASSERT(sizeof(B_TOWER_POKEMON) == 56);
SDK_COMPILER_ASSERT(sizeof(BTLTOWER_WIFI_PLAYER) == 228);
#endif

/**
 *	@brief	�^���[�@�v���C�f�[�^�T�C�Y
 */
int TowerPlayData_GetWorkSize(void)
{
	return sizeof(BTLTOWER_PLAYWORK);
}

/**
 *	@brief	�^���[�@�v���C���[�X�R�A�f�[�^�T�C�Y
 */
int	TowerSocreData_GetWorkSize(void)
{
	return sizeof(BTLTOWER_SCOREWORK);
}

/**
 *	@brief	�^���[�@�|�P�����f�[�^�T�C�Y
 */
int TowerWifiPoke_GetWorkSize(void)
{
	return sizeof(B_TOWER_POKEMON);
}

/**
 *	@brief	�^���[�@Wifi�f�[�^�T�C�Y
 */
int	TowerWifiData_GetWorkSize(void)
{
	return sizeof(BTLTOWER_WIFI_DATA);
}

/**
 *	@brief�@�^���[ Wifi/�g���[�i�[���[�h�v���C���[�f�[�^�\���̃f�[�^�T�C�Y
 */
int TowerDpwBtPlayer_GetWorkSize(void)
{
	return sizeof(Dpw_Bt_Player);
}
/**
 *	@brief	�^���[�@�v���C�f�[�^�N���A
 */
void TowerPlayData_Clear(BTLTOWER_PLAYWORK* dat)
{
	MI_CpuClear8(dat,sizeof(BTLTOWER_PLAYWORK));
}

/**
 *	@brief	�^���[	�X�R�A�f�[�^�N���A
 */
void TowerScoreData_Clear(BTLTOWER_SCOREWORK* dat)
{
	MI_CpuClear8(dat,sizeof(BTLTOWER_SCOREWORK));
	dat->wifi_rank = 1;
}

/**
 *	@brief	�^���[�@�v���C���[���b�Z�[�W�f�[�^�N���A
 */
void TowerPlayerMsg_Clear(BTLTOWER_PLAYER_MSG* dat)
{
	PMSDAT_SetupDefaultBattleTowerMessage(&dat->msg[0], BTWR_MSG_PLAYER_READY);
	PMSDAT_SetupDefaultBattleTowerMessage(&dat->msg[1], BTWR_MSG_PLAYER_WIN);
	PMSDAT_SetupDefaultBattleTowerMessage(&dat->msg[2], BTWR_MSG_PLAYER_LOSE);
	PMSDAT_SetupDefaultBattleTowerMessage(&dat->msg[3], BTWR_MSG_LEADER);
}

/**
 *	@brief	�^���[�@Wifi�f�[�^�N���A
 */
void TowerWifiData_Clear(BTLTOWER_WIFI_DATA* dat)
{
	MI_CpuClear8(dat,sizeof(BTLTOWER_WIFI_DATA));
}

//=======================================================
//�@�^���[�@�v���C�f�[�^�A�N�Z�X�n
//=======================================================

/**
 *	@brief	�v���C�f�[�^�@�擾
 *
 *	@param	dat	BTLTOWRE_PLAYWORK*
 *	@param	id	�擾����f�[�^ID BTOWER_PSD_ID�^
 *	@param	buf	void*:�f�[�^�擾�|�C���^
 */
u32	TowerPlayData_Get(BTLTOWER_PLAYWORK* dat,BTWR_PSD_ID id,void* buf)
{
	switch(id){
	case BTWR_PSD_playmode:
		return (u32)dat->play_mode;
	case BTWR_PSD_round:
		return (u32)dat->tower_round;
	case BTWR_PSD_rec_down:
		return (u32)dat->wifi_rec_down;
	case BTWR_PSD_rec_turn:
		return dat->wifi_rec_turn;
	case BTWR_PSD_rec_damage:
		return dat->wifi_rec_damage;
	case BTWR_PSD_pokeno:
		MI_CpuCopy8(dat->member_poke,buf,BTOWER_STOCK_MEMBER_MAX);
		return 0;
	case BTWR_PSD_pare_poke:
		MI_CpuCopy8(&dat->pare_poke,buf,sizeof(B_TOWER_PAREPOKE_PARAM));
		return 0;
	case BTWR_PSD_pare_itemfix:
		return dat->itemfix_f;
	case BTWR_PSD_trainer:
		MI_CpuCopy8(dat->trainer_no,buf,2*BTOWER_STOCK_TRAINER_MAX);
		return 0;
	case BTWR_PSD_partner:
		return dat->partner;
	case BTWR_PSD_rnd_seed:
		return dat->play_rnd_seed;
	}
	return 0;
}

/**
 *	@brief	�v���C�f�[�^�@�Z�b�g
 *	
 *	@param	dat	BTLTOWRE_PLAYWORK*
 *	@param	id	�擾����f�[�^ID BTOWER_PSD_ID�^
 *	@param	buf	void*:�f�[�^���i�[�����o�b�t�@�ւ̃|�C���^
 */
void TowerPlayData_Put(BTLTOWER_PLAYWORK* dat,BTWR_PSD_ID id,const void* buf)
{
	u32	*buf32 = (u32 *)buf;
	u16	*buf16=(u16 *)buf;
	u8	*buf8=(u8 *)buf;

	switch(id){
	case BTWR_PSD_playmode:
		dat->play_mode = buf8[0];
		return;
	case BTWR_PSD_round:
		dat->tower_round = buf8[0];
		return;
	case BTWR_PSD_rec_down:
		dat->wifi_rec_down = buf8[0];
		return;
	case BTWR_PSD_rec_turn:
		dat->wifi_rec_turn = buf16[0];
		return;
	case BTWR_PSD_rec_damage:
		dat->wifi_rec_damage = buf16[0];
		return;
	case BTWR_PSD_pokeno:
		MI_CpuCopy8(buf8,dat->member_poke,4);
		return;
	case BTWR_PSD_pare_poke:
		MI_CpuCopy8(buf16,&dat->pare_poke,sizeof(B_TOWER_PAREPOKE_PARAM));
		return;
	case BTWR_PSD_pare_itemfix:
		dat->itemfix_f = buf8[0];
		return;
	case BTWR_PSD_trainer:
		MI_CpuCopy8(buf16,dat->trainer_no,2*BTOWER_STOCK_TRAINER_MAX);
		return;
	case BTWR_PSD_rnd_seed:
		dat->play_rnd_seed = buf32[0];
		return;
	case BTWR_PSD_partner:
		dat->partner = buf8[0];
		return;
	}
}

/**
 *	@brief �v���C�f�[�^�@Wifi���R�[�h�f�[�^Add	
 *
 *	@param	down	�|���ꂽ�|�P�����ǉ���
 *	@param	turn	���������^�[���ǉ���
 *	@param	damage	�󂯂��_���[�W�ǉ��l
 */
void TowerPlayData_WifiRecordAdd(BTLTOWER_PLAYWORK* dat,u8 down,u16 turn,u16 damage)
{
	if(dat->wifi_rec_down + down < 255){
		dat->wifi_rec_down += down;
	}
	if(dat->wifi_rec_turn + turn < 65535){
		dat->wifi_rec_turn += turn;
	}
	if(dat->wifi_rec_damage + damage < 65535){
		dat->wifi_rec_damage += damage;
	}
}

/**
 *	@brief	�v���C�f�[�^�@�������Z�[�u�ς݂��ǂ����H
 *
 *	@retval	TRUE	�������Z�[�u����Ă���
 *	@retval FALSE	�Z�[�u����Ă��Ȃ�
 */
BOOL TowerPlayData_GetSaveFlag(BTLTOWER_PLAYWORK* dat)
{
	return dat->saved_f;
}

/**
 *	@brief	�v���C�f�[�^�@�Z�[�u��ԃt���O���Z�b�g
 */
void TowerPlayData_SetSaveFlag(BTLTOWER_PLAYWORK* dat,BOOL flag)
{
	dat->saved_f = flag;
}

//=======================================================
//�@�^���[�@�X�R�A�f�[�^�A�N�Z�X�n
//=======================================================
/**
 *	@brief	�X�R�A�f�[�^ �o�g���|�C���g�Z�b�g
 *
 *	�L���R�}���h set/get/add/sub
 */
u16 TowerScoreData_SetBattlePoint(BTLTOWER_SCOREWORK* dat,u16 num,BTWR_DATA_SETID mode)
{
	switch(mode){
	case BTWR_DATA_set:
		if(num > 9999){
			dat->btl_point = 9999;
		}else{
			dat->btl_point = num;
		}
		break;
	case BTWR_DATA_add:
		if(dat->btl_point+num > 9999){
			dat->btl_point = 9999;
		}else{
			dat->btl_point += num;
		}
		break;
	case BTWR_DATA_sub:
		if(dat->btl_point < num){
			dat->btl_point = 0;
		}else{
			dat->btl_point -= num;
		}
	case BTWR_DATA_get:
	default:
		break;
	}
	return dat->btl_point;
}

/**
 *	@brief	�X�R�A�f�[�^�@Wifi�A���s��J�E���g����
 *
 *	�L���R�}���h get/reset/inc
 *
 *	@return	�����̃J�E���g
 */
u8 TowerScoreData_SetWifiLoseCount(BTLTOWER_SCOREWORK* dat,BTWR_DATA_SETID mode)
{
	switch(mode){
	case BTWR_DATA_reset:
		dat->wifi_lose = 0;
		dat->wifi_lose_f = 0;
		break;
	case BTWR_DATA_inc:
		if(dat->wifi_lose_f){
			//�A���s�풆
			dat->wifi_lose += 1;
		}else{
			dat->wifi_lose = 1;
			dat->wifi_lose_f = 1;
		}
		break;
	}
	return dat->wifi_lose;
}

/**
 *	@brief	�X�R�A�f�[�^�@Wifi�����N����
 *
 *	�L���R�}���h get/reset/inc/dec
 */
u8	TowerScoreData_SetWifiRank(BTLTOWER_SCOREWORK* dat,BTWR_DATA_SETID mode)
{
	switch(mode){
	case BTWR_DATA_reset:
		dat->wifi_rank = 1;
		break;
	case BTWR_DATA_inc:
		if(dat->wifi_rank < 10){
			dat->wifi_rank += 1;
		}
		break;
	case BTWR_DATA_dec:
		if(dat->wifi_rank>1){
			dat->wifi_rank -= 1;
		}
		break;
	}
	return dat->wifi_rank;
}

/**
 *	@brief	�g�p�|�P�����f�[�^�ۑ�
 */
void TowerScoreData_SetUsePokeData(BTLTOWER_SCOREWORK* dat,
				BTWR_SCORE_POKE_DATA mode,B_TOWER_POKEMON* poke)
{
	if(mode == BTWR_SCORE_POKE_SINGLE){
		MI_CpuCopy8(poke,dat->single_poke,sizeof(B_TOWER_POKEMON)*3);
	}else{
		MI_CpuCopy8(poke,dat->wifi_poke,sizeof(B_TOWER_POKEMON)*3);
	}
}

/**
 *	@brief	�g�p�|�P�����f�[�^���o�b�t�@�ɃR�s�[���Ď擾
 */
void TowerScoreData_GetUsePokeData(BTLTOWER_SCOREWORK* dat,
			BTWR_SCORE_POKE_DATA mode,B_TOWER_POKEMON* poke)
{
	if(mode == BTWR_SCORE_POKE_SINGLE){
		MI_CpuCopy8(dat->single_poke,poke,sizeof(B_TOWER_POKEMON)*3);
	}else{
		MI_CpuCopy8(dat->wifi_poke,poke,sizeof(B_TOWER_POKEMON)*3);
	}
}

/**
 *	@brief	�g�p�|�P�����f�[�^���o�b�t�@�ɃR�s�[���Ď擾(WiFi�\���̃f�[�^�^)
 */
void TowerScoreData_GetUsePokeDataDpw(BTLTOWER_SCOREWORK* dat,
			BTWR_SCORE_POKE_DATA mode,DPW_BT_POKEMON_DATA* poke)
{
	if(mode == BTWR_SCORE_POKE_SINGLE){
		MI_CpuCopy8(dat->single_poke,poke,sizeof(B_TOWER_POKEMON)*3);
	}else{
		MI_CpuCopy8(dat->wifi_poke,poke,sizeof(B_TOWER_POKEMON)*3);
	}
}

/**
 *	@brief	�X�R�A�f�[�^ Wifi���ё���
 */
u16	TowerScoreData_SetWifiScore(BTLTOWER_SCOREWORK* dat,BTLTOWER_PLAYWORK *playdata)
{
	u16	sa,sb,sc,sd,st;
	u16	score = 0;

	//���E���h���͏���������+1�ɂȂ��Ă���̂Ń}�C�i�X�P���Čv�Z����
	sa = (playdata->tower_round-1)*1000;
	sb = playdata->wifi_rec_turn*10;
	sc = playdata->wifi_rec_down*20;
	if(sb+sc > 950){
		st = 0;
	}else{
		st = 950-(sb+sc);
	}
	if(playdata->wifi_rec_damage>(1000-30)){
		sd = 0;
	}else{
		sd = (1000-playdata->wifi_rec_damage)/30;
	}
	score = sa+st+sd;
	dat->wifi_score = score;
	return score;
}

/**
 *	@brief	�X�R�A�f�[�^�@Wifi����0�N���A
 */
void TowerScoreData_ClearWifiScore(BTLTOWER_SCOREWORK* dat)
{
	dat->wifi_score = 0;
}

/**
 *	@brief	�X�R�A�f�[�^�@Wifi���ю擾
 */
u16	TowerScoreData_GetWifiScore(BTLTOWER_SCOREWORK* dat)
{
	return dat->wifi_score;
}

/**
 *	@brief	�X�R�A�f�[�^���珟�������������擾
 */
u8	TowerScoreData_GetWifiWinNum(BTLTOWER_SCOREWORK* dat)
{
	u8 ret = 0;
	ret = (dat->wifi_score)/1000;

	return ret;
}

/**
 *	@brief	�X�R�A�f�[�^�@���񐔑���
 *
 *	�L���R�}���h reset/inc/get
 */
u16 TowerScoreData_SetStage(BTLTOWER_SCOREWORK* dat,u16 id,BTWR_DATA_SETID mode)
{
	if(id == BTWR_MODE_RETRY){
		return 0;	//���g���C���[�h�ł̓J�E���g���Ȃ�
	}
	switch(mode){
	case BTWR_DATA_reset:
		dat->tower_stage[id] = 0;
		break;
	case BTWR_DATA_inc:
		if(dat->tower_stage[id] < 65534){
			dat->tower_stage[id] += 1;
		}
		break;
	}
	return dat->tower_stage[id];
}
#ifdef PM_DEBUG
/**
 *	@brief	�f�o�b�O����@���݂̃X�e�[�W�l���Z�b�g����
 */
u16 TowerScoreData_DebugSetStageValue(BTLTOWER_SCOREWORK* dat,u16 id,u16 value)
{
	if(id >= BTWR_MODE_RETRY){
		return 0;	//���g���C���[�h�ł̓J�E���g���Ȃ�
	}
	dat->tower_stage[id] = value;
	return dat->tower_stage[id];
}
#endif	//PM_DEBUG
	
/**
 *	@brief	�X�R�A�f�[�^ �t���O�G���A�Z�b�g
 */
BOOL	TowerScoreData_SetFlags(BTLTOWER_SCOREWORK* dat,u16 id,BTWR_DATA_SETID mode)
{
	u16	i;
	u16	flag = 1;

	//�t���OID����
	for(i = 0;i < id;i++){
		flag <<= 1;
	}
	switch(mode){
	case BTWR_DATA_reset:
		flag = (flag^0xFFFF);
		dat->flags &= flag;
		break;
	case BTWR_DATA_set:
		dat->flags |= flag;
		break;
	case BTWR_DATA_get:
		return (BOOL)((dat->flags>>id)&0x0001);
		
	}
	return 0;
}

/**
 *	@brief	�^���[�p���t�ω������_���V�[�h�ۑ�
 */
void TowerScoreData_SetDayRndSeed(BTLTOWER_SCOREWORK* dat,u32 rnd_seed)
{
	dat->day_rnd_seed = rnd_seed;
}

/**
 *	@brief	�^���[�p���t�ω������_���V�[�h�擾
 */
u32 TowerScoreData_GetDayRndSeed(BTLTOWER_SCOREWORK* dat)
{
	return dat->day_rnd_seed;
}
//=======================================================
//�@�^���[�@�v���C���[���b�Z�[�W�f�[�^�A�N�Z�X�n
//=======================================================

/**
 *	@brief	�ȈՉ�b�f�[�^���Z�b�g
 */
void TowerPlayerMsg_Set(SAVEDATA* sv,BTWR_PLAYER_MSG_ID id,PMS_DATA* src)
{
	BTLTOWER_SAVEWORK* data = SaveData_Get(sv,GMDATA_ID_BTLTOWER);
	
	PMSDAT_Copy(&(data->player_msg.msg[id]),src);
}

/**
 *	@brief	�ȈՉ�b�f�[�^���擾
 */
PMS_DATA* TowerPlayerMsg_Get(SAVEDATA* sv,BTWR_PLAYER_MSG_ID id)
{
	BTLTOWER_SAVEWORK* data = SaveData_Get(sv,GMDATA_ID_BTLTOWER);
	
	return &(data->player_msg.msg[id]);
}

//=======================================================
//�@�^���[�@Wifi�f�[�^�A�N�Z�X�n
//=======================================================
/**
 *	@brief	�w�肵�����[���f�[�^�̎擾�t���O�𗧂Ă�
 *
 *	@param	rank	1�I���W���Ȃ̂Œ���
 *	@param	roomno	1�I���W���Ȃ̂Œ���
 */
void TowerWifiData_SetRoomDataFlag(BTLTOWER_WIFI_DATA* dat,
		u8 rank,u8 roomno,RTCDate *day)
{
	u8	idx,ofs;
	u8	flag = 1;
	u16	roomid;
	
	if(roomno == 0 || roomno > 200){
		return;
	}
	if(rank == 0 || rank > 10){
		return;
	}
	//����1�I���W���Ȃ̂�-1���Čv�Z
	roomid = (rank-1)*200+(roomno-1);
	
	idx = roomid/8;
	ofs = roomid%8;
	flag <<= ofs;

	dat->flags[idx] |= flag;

	dat->day = RTCDate2GFDate(day);
}

/**
 *	@brief	���[���f�[�^�擾�t���O���N���A����
 */
void TowerWifiData_ClearRoomDataFlag(BTLTOWER_WIFI_DATA* dat)
{
	MI_CpuClear8(dat->flags,BTOWER_ROOM_DATA_FLAGS_LEN);
	MI_CpuClear8(&dat->day,sizeof(GF_DATE));
}

/**
 *	@brief	���t���ς���Ă��邩�ǂ����`�F�b�N
 */
static BOOL check_day(RTCDate* new,RTCDate* old)
{
	if(new->year > old->year){
		return TRUE;
	}
	if(new->month > old->month){
		return TRUE;
	}
	if(new->day > old->day){
		return TRUE;
	}
	return FALSE;
}

/**
 *	@brief	�w�肵�����[����DL�t���O�������Ă��邩�`�F�b�N
 *
 *	@param	rank	1�I���W���Ȃ̂Œ���
 *	@param	roomno	1�I���W���Ȃ̂Œ���
 */
BOOL TowerWifiData_CheckRoomDataFlag(BTLTOWER_WIFI_DATA* dat,u8 rank,u8 roomno,RTCDate* day)
{
	u8	idx,ofs;
	u8	flag = 1;
	u16	roomid;
	RTCDate old_day;
	
	if(roomno > 200 || rank > 10){
		return FALSE;
	}

	//�Ō��DL�������t����A�����ς���Ă��邩�ǂ����`�F�b�N
	GFDate2RTCDate(dat->day,&old_day);
	if(check_day(day,&old_day)){
		//�����ς���Ă���̂ŁA�t���O�Q���I�[���N���A
		TowerWifiData_ClearRoomDataFlag(dat);
		return FALSE;
	}
	//����1�I���W���Ȃ̂�-1���Čv�Z
	roomid = (rank-1)*200+(roomno-1);
	
	idx = roomid/8;
	ofs = roomid%8;
	flag <<= ofs;

	if(dat->flags[idx] & flag){
		return TRUE;
	}
	return FALSE;
}

/**
 *	@brief	�v���C���[�f�[�^�����݂��Ă��邩�`�F�b�N
 */
BOOL TowerWifiData_IsPlayerDataEnable(BTLTOWER_WIFI_DATA* dat)
{
	return (BOOL)dat->player_data_f;
}

/**
 *	@brief	���[�_�[�f�[�^�����邩�ǂ����`�F�b�N
 */
BOOL TowerWifiData_IsLeaderDataEnable(BTLTOWER_WIFI_DATA* dat)
{
	return (BOOL)dat->leader_data_f;
}

/**
 *	@brief	�v���C���[�f�[�^���Z�[�u
 *	
 *	@param	rank	1�I���W���Ȃ̂Œ��� 
 *	@param	roomno	1�I���W���Ȃ̂Œ���
 */
void TowerWifiData_SetPlayerData(BTLTOWER_WIFI_DATA* dat,DPW_BT_PLAYER* src,u8 rank,u8 roomno)
{
	MI_CpuCopy8(src,dat->player,
		sizeof(BTLTOWER_WIFI_PLAYER)*BTOWER_STOCK_WIFI_PLAYER_MAX);
	
	//roomno��rank��ۑ�
	dat->player_rank = rank;
	dat->player_room = roomno;
	dat->player_data_f = 1;
}

/**
 *	@brief	�v���C���[�f�[�^���N���A
 */
void TowerWifiData_ClearPlayerData(BTLTOWER_WIFI_DATA* dat)
{
	MI_CpuClear8(dat->player,
		sizeof(BTLTOWER_WIFI_PLAYER)*BTOWER_STOCK_WIFI_PLAYER_MAX);
	dat->player_data_f = 0;
}

/**
 *	@brief	�v���C���[�f�[�^��RoomID(�����N��roomNo)���擾
 *
 *	@param	roomid	BTOWER_ROOMID�^(b_tower.h�Ō��J)
 */
void TowerWifiData_GetPlayerDataRoomID(BTLTOWER_WIFI_DATA* dat,BTOWER_ROOMID *roomid)
{
	roomid->rank = dat->player_rank;
	roomid->no = dat->player_room;
}

/**
 *	@brief	�v���C���[�f�[�^���^���[�퓬�p�ɉ�
 */
void TowerWifiData_GetBtlPlayerData(BTLTOWER_WIFI_DATA* dat,
		B_TOWER_PARTNER_DATA* player,const u8 round)
{
	B_TOWER_TRAINER	*tr;			//�g���[�i�[�f�[�^
	B_TOWER_POKEMON	*poke;		//�����|�P�����f�[�^
	BTLTOWER_WIFI_PLAYER* src;
	MSGDATA_MANAGER* pMan;

	tr = &(player->bt_trd);
	poke = player->btpwd;
	src = &(dat->player[round]);

	//�g���[�i�[�p�����[�^�擾
	tr->player_id = BATTLE_TOWER_TRAINER_ID;//src->id_no;	//�^���[�pID�͌Œ�l
	tr->tr_type = src->tr_type;
	//NG�l�[���t���O�`�F�b�N
	if(src->ngname_f){
		pMan = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
				NARC_msg_btower_app_dat,HEAPID_WORLD);

		MSGMAN_GetStr(pMan,msg_def_player_name01+src->gender,tr->name);
		MSGMAN_Delete(pMan);
	}else{
		MI_CpuCopy8(src->name,tr->name,16);
	}
	MI_CpuCopy8(src->appear_word,tr->appear_word,8);
	MI_CpuCopy8(src->win_word,tr->win_word,8);
	MI_CpuCopy8(src->lose_word,tr->lose_word,8);

	//�|�P�����f�[�^�擾
	MI_CpuCopy8(src->poke,poke,sizeof(B_TOWER_POKEMON)*3);
}

/**
 *	@brief	���[�_�[�f�[�^���Z�[�u
 *	
 *	@param	rank	1�I���W���Ȃ̂Œ���
 *	@param	roomno	1�I���W���Ȃ̂Œ���
 */
void TowerWifiData_SetLeaderData(BTLTOWER_WIFI_DATA* dat,DPW_BT_LEADER* src,u8 rank,u8 roomno)
{
	MI_CpuCopy8(src,&dat->leader,
		sizeof(B_TOWER_LEADER_DATA)*BTOWER_STOCK_WIFI_LEADER_MAX);
	
	//roomno��rank��ۑ�
	dat->leader_rank = rank;
	dat->leader_room = roomno;
	dat->leader_data_f = 1;
}

/**
 *	@brief	���[�_�[�f�[�^���N���A
 */
void TowerWifiData_ClearLeaderData(BTLTOWER_WIFI_DATA* dat)
{
	MI_CpuClear8(&dat->leader,
		sizeof(B_TOWER_LEADER_DATA)*BTOWER_STOCK_WIFI_LEADER_MAX);
	dat->leader_data_f = 0;
}

/**
 *	@brief	���[�_�[�f�[�^��RoomID(�����N��roomNo)���擾
 *
 *	@param	roomid	BTOWER_ROOMID�^(b_tower.h�Ō��J)
 */
void TowerWifiData_GetLeaderDataRoomID(BTLTOWER_WIFI_DATA* dat,BTOWER_ROOMID *roomid)
{
	roomid->rank = dat->leader_rank;
	roomid->no = dat->leader_room;
}

/**
 *	@brief	���[�_�[�f�[�^��Alloc�����������ɃR�s�[���Ď擾����
 *
 *	��������Alloc�����������̈��Ԃ��̂ŁA�Ăяo�����������I�ɉ�����邱�ƁI
 */
B_TOWER_LEADER_DATA* TowerWifiData_GetLeaderDataAlloc(BTLTOWER_WIFI_DATA* dat,int heapID) 
{
	B_TOWER_LEADER_DATA* bp;

	bp = sys_AllocMemory(heapID,sizeof(B_TOWER_LEADER_DATA)*BTOWER_STOCK_WIFI_LEADER_MAX);
	MI_CpuCopy8(dat->leader,bp,sizeof(B_TOWER_LEADER_DATA)*BTOWER_STOCK_WIFI_LEADER_MAX);

	return bp;
}

//=======================================================
//	�^���[�@�Z�[�u�f�[�^�u���b�N�֘A
//=======================================================

/**
 *	@brief	�^���[�@�Z�[�u�f�[�^�u���b�N�T�C�Y���擾
 */
int TowerData_GetWorkSize(void)
{
	return sizeof(BTLTOWER_SAVEWORK);
}

/**
 *	@brief	�^���[�@�Z�[�u�f�[�^�u���b�N������
 */
void TowerData_Init(BTLTOWER_SAVEWORK* save)
{
	TowerPlayData_Clear(&save->play);
	TowerScoreData_Clear(&save->score);
	TowerPlayerMsg_Clear(&save->player_msg);
	TowerWifiData_Clear(&save->wifi);
}

/**
 *	@brief	�^���[�@�v���C�f�[�^�ւ̃|�C���^���擾
 */
BTLTOWER_PLAYWORK* SaveData_GetTowerPlayData(SAVEDATA* sv)
{
	BTLTOWER_SAVEWORK* data = SaveData_Get(sv,GMDATA_ID_BTLTOWER);
	
	return &data->play;
}

/**
 *	@brief	�^���[�@�X�R�A�f�[�^�ւ̃|�C���^���擾
 */
BTLTOWER_SCOREWORK* SaveData_GetTowerScoreData(SAVEDATA* sv)
{
	BTLTOWER_SAVEWORK* data = SaveData_Get(sv,GMDATA_ID_BTLTOWER);
	
	return &data->score;
}

/**
 *	@brief	�^���[ Wifi�f�[�^�ւ̃|�C���^���擾	
 */
BTLTOWER_WIFI_DATA*	SaveData_GetTowerWifiData(SAVEDATA* sv)
{
	BTLTOWER_SAVEWORK* data = SaveData_Get(sv,GMDATA_ID_BTLTOWER);
	
	return &data->wifi;
}
