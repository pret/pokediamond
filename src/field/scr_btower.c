/**
 *	@file	scr_btower.c
 *	@brief	�o�g���^���[�n�@�X�N���v�g�R�}���h��p�\�[�X
 *	@author	Miyuki Iwasawa
 *	@date	06.05.23
 */
#include "common.h"
#include "system/lib_pack.h"
#include "system/wordset.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "itemtool/itemsym.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "field/ev_win.h"
#include "sysflag.h"
#include "syswork.h"

#include "savedata/b_tower.h"
#include "field/b_tower_scr.h"
#include "field/b_tower_fld.h"
#include "field/b_tower_ev.h"
#include "savedata/record.h"
#include "savedata/config.h"

#include "msgdata\msg.naix"			//NARC_msg_??_dat
#include "communication/comm_tool.h"
#include "communication/comm_system.h"
#include "communication/comm_def.h"

#define __SCR_BTOWER_H_GLOBAL
#include "field/scr_btower.h"
#include "field/b_tower_wifi.h"

static u16 btltower_GetMineObj(BTOWER_SCRWORK* wk,u8 mode);

//--------------------------------------------------------------------------------------------
//�o�g���^���[�p�X�N���v�g�R�}���h
//-------------------------------------------------------------------------------------------
/**
 *	@brief	�o�g���^���[����p���[�N�|�C���^������
 */
BOOL EvCmdBattleTowerWorkClear(VM_MACHINE* core)
{
	TowerScr_WorkClear(&(core->fsys->btower_wk));
	return 0;
}

/**
 *	@brief	�o�g���^���[�p���[�N�쐬&������
 *
 *	@param	init	���������[�h�w��
 *					BTWR_PLAY_NEW:new game
 *					BTWR_PLAY_CONTINUE:new game
 *					
 *	@param	mode	�v���C���[�h�w��:BTWR_MODE_�`
 *
 *	@return 0
 */
BOOL EvCmdBattleTowerWorkInit(VM_MACHINE* core)
{
	u16	init,mode;
	
	init = VMGetU16(core);
	mode = VMGetU16(core);
	core->fsys->btower_wk = TowerScr_WorkInit(GameSystem_GetSaveData(core->fsys),init,mode);
	return 0;
}

/**
 *	@brief	�o�g���^���[�p���[�N���
 *
 *	@return 0
 */
BOOL EvCmdBattleTowerWorkRelease(VM_MACHINE* core)
{
	BTOWER_SCRWORK* wk;
	
	//���[�N�̈���
	TowerScr_WorkRelease(core->fsys->btower_wk);
	core->fsys->btower_wk = NULL;
	return 0;
}

/**
 *	@brief	�o�g���^���[�p�R�}���h�Q�Ăяo���C���^�[�t�F�[�X
 *
 *	@param	com_id		u16:�R�}���hID
 *	@param	retwk_id	u16:�Ԃ�l���i�[���郏�[�N��ID
 */
BOOL EvCmdBattleTowerTools(VM_MACHINE* core)
{
	u16	com_id,param,retwk_id;
	u16* ret_wk,*prm_wk;
	void ** buf;
	BTOWER_SCRWORK* wk;

	com_id = VMGetU16(core);
	param = VMGetWorkValue(core);
	retwk_id = VMGetU16(core);
	ret_wk = GetEventWorkAdrs( core->fsys, retwk_id );

	wk = core->fsys->btower_wk;

	switch(com_id){
	//���[�N��ˑ�
	case BTWR_TOOL_GET_MEMBER_NUM:
		*ret_wk = TowerScrTools_GetMemberNum(param);
		break;
	case BTWR_TOOL_CHK_ENTRY_POKE_NUM:
		if(param == 0){
			*ret_wk = TowerScrTools_CheckEntryPokeNum(wk->member_num,core->fsys->savedata);
		}else{
			*ret_wk = TowerScrTools_CheckEntryPokeNum(param,core->fsys->savedata);
		}
		break;
	case BTWR_TOOL_SYSTEM_RESET:
		TowerScrTools_SystemReset();
		break;
	case BTWR_TOOL_CLEAR_PLAY_DATA:
		TowerScrTools_ClearPlaySaveData(SaveData_GetTowerPlayData(core->fsys->savedata));
		break;
	case BTWR_TOOL_IS_SAVE_DATA_ENABLE:
		*ret_wk = TowerScrTools_IsSaveDataEnable(
						SaveData_GetTowerPlayData(core->fsys->savedata));
		break;
	case BTWR_TOOL_PUSH_NOW_LOCATION:
		TowerScrTools_PushNowLocation(core->fsys);
		break;
	case BTWR_TOOL_POP_NOW_LOCATION:
		TowerScrTools_PopNowLocation(core->fsys);
		break;
	case BTWR_TOOL_GET_RENSHOU_RECORD:
		*ret_wk = TowerScrTools_GetRenshouRecord(core->fsys->savedata,param);
		break;
	case BTWR_TOOL_WIFI_RANK_DOWN:
		*ret_wk = TowerScr_SetWifiRank(NULL,core->fsys->savedata,2);
		break;
	case BTWR_TOOL_GET_WIFI_RANK:
		*ret_wk = TowerScr_SetWifiRank(NULL,core->fsys->savedata,0);
		break;
	case BTWR_TOOL_SET_WIFI_UPLOAD_FLAG:
		TowerScrTools_SetWifiUploadFlag(core->fsys->savedata,param);
		break;
	case BTWR_TOOL_GET_WIFI_UPLOAD_FLAG:
		*ret_wk = TowerScrTools_GetWifiUploadFlag(core->fsys->savedata);
		break;
	case BTWR_TOOL_SET_NG_SCORE:
		*ret_wk = TowerScrTools_SetNGScore(core->fsys->savedata);
		break;
	case BTWR_TOOL_IS_PLAYER_DATA_ENABLE:
		*ret_wk = TowerScrTools_IsPlayerDataEnable(core->fsys->savedata);
		break;
	case BTWR_TOOL_WIFI_CONNECT:
		EventCmd_BTowerWifiCall(core->event_work,param,retwk_id,*ret_wk);
		return 1;
	
		//���[�N�ˑ�
	case BTWR_SUB_SELECT_POKE:
		buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
		TowerScr_SelectPoke(wk,core->event_work,buf);
		return 1;
	case BTWR_SUB_GET_ENTRY_POKE:
		buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
		*ret_wk = TowerScr_GetEntryPoke(wk,buf,core->fsys->savedata);
		break;
	case BTWR_SUB_CHK_ENTRY_POKE:
		*ret_wk = TowerScr_CheckEntryPoke(wk,core->fsys->savedata);
		break;
	case BTWR_SUB_GET_NOW_ROUND:
		*ret_wk = TowerScr_GetNowRound(wk);
		break;
	case BTWR_SUB_INC_ROUND:
		*ret_wk = TowerScr_IncRound(wk);
		break;
	case BTWR_SUB_IS_CLEAR:
		*ret_wk = TowerScr_IsClear(wk);
		break;
	case BTWR_SUB_GET_RENSHOU_CNT:
		*ret_wk  =TowerScr_GetRenshouCount(wk);
		break;
	case BTWR_SUB_SET_LOSE_SCORE:
		TowerScr_SetLoseScore(wk,core->fsys);
		break;
	case BTWR_SUB_SET_CLEAR_SCORE:
		TowerScr_SetClearScore(wk,core->fsys);
		break;
	case BTWR_SUB_SAVE_REST_PLAY_DATA:
		TowerScr_SaveRestPlayData(wk);
		break;
	case BTWR_SUB_CHOICE_BTL_PARTNER:
		TowerScr_ChoiceBtlPartner(wk,core->fsys->savedata);
		break;
	case BTWR_SUB_CHOICE_BTL_SEVEN:
		TowerScr_ChoiceBtlSeven(wk);
		break;
	case BTWR_SUB_GET_ENEMY_OBJ:
		*ret_wk = TowerScr_GetEnemyObj(wk,param);
		break;
	case BTWR_SUB_LOCAL_BTL_CALL:
		TowerScr_LocalBattleCall(core->fsys->event,wk,
			GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WIN_FLAG ));
		return 1;
	case BTWR_SUB_GET_PLAY_MODE:
		*ret_wk = (u16)TowerScr_GetPlayMode(wk);
		break;
	case BTWR_SUB_SET_LEADER_CLEAR_FLAG:
		TowerScr_SetLeaderClearFlag(wk,param);
		break;
	case BTWR_SUB_GET_LEADER_CLEAR_FLAG:
		*ret_wk = TowerScr_GetLeaderClearFlag(wk);
		break;
	case BTWR_SUB_ADD_BATTLE_POINT:
		*ret_wk = TowerScr_AddBtlPoint(wk);
		break;
	case BTWR_SUB_GOODS_FLAG_SET:
		TowerScr_GoodsFlagSet(wk,core->fsys->savedata);
		break;
	case BTWR_SUB_LEADER_RIBBON_SET:
		*ret_wk = TowerScr_LeaderRibbonSet(wk,core->fsys->savedata);
		break;
	case BTWR_SUB_RENSHOU_RIBBON_SET:
		*ret_wk = TowerScr_RenshouRibbonSet(wk,core->fsys->savedata);
		break;
	case BTWR_SUB_SET_PARTNER_NO:
		wk->partner = param;
		break;
	case BTWR_SUB_GET_PARTNER_NO:
		*ret_wk = wk->partner;
		break;
	case BTWR_SUB_BTL_TRAINER_SET:
		 TowerScr_BtlTrainerNoSet(wk,core->fsys->savedata);
		 break;
	case BTWR_SUB_GET_SELPOKE_IDX:
		 *ret_wk = wk->member[param];
		break;
	case BTWR_SUB_WIFI_RANK_UP:
		*ret_wk = TowerScr_SetWifiRank(wk,core->fsys->savedata,1);
		break;
	case BTWR_SUB_GET_MINE_OBJ:
		*ret_wk = btltower_GetMineObj(wk,param);
		break;
	case BTWR_SUB_UPDATE_RANDOM:
		*ret_wk = TowerScr_PlayRandUpdate(wk,core->fsys->savedata);
		break;
	case BTWR_DEB_IS_WORK_NULL:
		if(wk == NULL){
			*ret_wk = 1;
		}else{
			*ret_wk = 0;
		}
		break;
	default:
		*ret_wk = 0;
		break;
	}
	return 0;
}

/**
 *	@brief	���I�ς݂�5�l�O�̃|�P�����f�[�^��Ԃ�
 */
BOOL EvCmdBattleTowerGetSevenPokeData(VM_MACHINE* core)
{
	u16	id,idx;
	u16 *ret_poke,*ret_waza;
	BTOWER_SCRWORK* wk = core->fsys->btower_wk;

	id =  VMGetWorkValue(core);		//5�l�Oid
	idx =  VMGetWorkValue(core);	//��肽���|�P������idx

	ret_poke = GetEventWorkAdrs(core->fsys,VMGetU16(core));
	ret_waza = GetEventWorkAdrs(core->fsys,VMGetU16(core));

	*ret_poke = wk->five_data[id].btpwd[idx].mons_no;
	*ret_waza = wk->five_data[id].btpwd[idx].waza[0];

	return 0;
}

/**
 *	@brief	�o�g���^���[ �v���C�Y�����炦���Ԃ��ǂ����H
 *
 *	@param	retwk_id	u16:�Ԃ�l���i�[���郏�[�N��ID
 */
BOOL EvCmdBattleTowerIsPrizeGet(VM_MACHINE* core)
{
	u16	retwk_id,win,ret;
	u16* ret_wk;
	
	retwk_id = VMGetU16(core);
	ret_wk = GetEventWorkAdrs( core->fsys, retwk_id );

	*ret_wk = BtlTower_IsPrizeGet(core->fsys->savedata);
	return 0;
}

/**
 *	@brief	�o�g���^���[�@�v���C�Y��n���q�g��\�����邩�ǂ����H
 *
 *	@param	retwk_id	u16:�Ԃ�l���i�[���郏�[�N��ID
 */
BOOL EvCmdBattleTowerIsPrizemanSet(VM_MACHINE* core)
{
	u16	retwk_id,win,ret;
	u16* ret_wk;
	
	retwk_id = VMGetU16(core);
	ret_wk = GetEventWorkAdrs( core->fsys, retwk_id );

	*ret_wk = BtlTower_IsPrizemanSet(core->fsys->savedata);
	return 0;
}

/**
 *	@brief	�ʐM�}���`�f�[�^���M
 */
BOOL EvCmdBattleTowerSendBuf(VM_MACHINE* core)
{
	u16 mode = VMGetWorkValue(core);
	u16 param = VMGetWorkValue(core);

	BTOWER_SCRWORK* wk = core->fsys->btower_wk;

	MI_CpuClear8(wk->recv_buf,BTWR_SIO_BUF_LEN);
	switch(mode){
	case 0:	//�|�P�����I��
		BTowerComm_SendPlayerData(core->fsys->btower_wk,core->fsys->savedata);
		break;
	case 1:	//���I�g���[�i�[
		BTowerComm_SendTrainerData(core->fsys->btower_wk);
		break;
	case 2:	//���^�C�A��I�Ԃ��H
		BTowerComm_SendRetireSelect(core->fsys->btower_wk,param);
		break;
	}
	OS_Printf(">>btwr send = %d,%d,%d\n",wk->send_buf[0],wk->send_buf[1],wk->send_buf[2]);
	CommToolSetTempData(CommGetCurrentID(),wk->send_buf);
	return 0;
}

/**
 *	@brief	�ʐM�}���`�f�[�^��M
 */
BOOL EvCmdBattleTowerRecvBuf(VM_MACHINE* core)
{
	u16	retwk_id;
	u16	mode;

	mode = VMGetWorkValue(core);
	retwk_id = VMGetU16(core);
	
	EventCmd_BTowerSioRecvBuf(core->fsys->event,mode,retwk_id);
	return 1;
}

/**
 *	@brief	���[�_�[�f�[�^���[��ID���擾
 */
BOOL EvCmdBattleTowerGetLeaderRoomID(VM_MACHINE* core)
{
	BTOWER_ROOMID roomid;
	
	u16	*ret01 = GetEventWorkAdrs(core->fsys,VMGetU16(core));
	u16	*ret02 = GetEventWorkAdrs(core->fsys,VMGetU16(core));

	TowerWifiData_GetLeaderDataRoomID(
			SaveData_GetTowerWifiData(core->fsys->savedata),&roomid);
	
	*ret01 = roomid.rank;
	*ret02 = roomid.no;
	return 0;
}

/**
 *	@brief	���[�_�[DL�f�[�^�����݂��邩�ǂ����H
 */
BOOL EvCmdBattleTowerIsLeaderDataExist(VM_MACHINE* core)
{
	u16	*ret_wk = GetEventWorkAdrs(core->fsys,VMGetU16(core));
	*ret_wk = TowerWifiData_IsLeaderDataEnable(
			SaveData_GetTowerWifiData(core->fsys->savedata));
	return 0;
}



/**
 *	@biref	�K�v�Ȑl��OBJ�R�[�h��Ԃ�
 */
static u16 btltower_GetMineObj(BTOWER_SCRWORK* wk,u8 mode)
{
	static const u16 five_cord[] = {
	 SEVEN1,SEVEN5,SEVEN2,SEVEN3,SEVEN4
	};
	if(mode == BTWR_PTCODE_OBJ){
		return wk->partner;
	}
	if(mode == BTWR_PTCODE_MINE2){
		if(wk->play_mode == BTWR_MODE_MULTI){
			return five_cord[wk->partner];
		}else{
			if(wk->pare_sex){
				return HEROINE;
			}else{
				return HERO;
			}
		}
	}
	if(wk->my_sex){
		return HEROINE;
	}else{
		return HERO;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �����o�g���|�C���g�E�B���h�E�\��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBtlPointWinWrite(VM_MACHINE * core)	
{
	FIELDSYS_WORK* fsys = core->fsys;
	u8 x = VMGetU8(core);
	u8 z = VMGetU8(core);

	GF_BGL_BMPWIN** pMsgWinDat;
	pMsgWinDat = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_COINWINDAT );
	*pMsgWinDat = EvWin_BtlPointWinPut( core->fsys, x, z );
	return 0;
}
//--------------------------------------------------------------------------------------------
/**
 * �����o�g���|�C���g�E�B���h�E�폜
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBtlPointWinDel(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	GF_BGL_BMPWIN** pMsgWinDat = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_COINWINDAT );
	EvWin_CoinWinDel(* pMsgWinDat );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����o�g���|�C���g�ĕ\��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBtlPointWrite(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	GF_BGL_BMPWIN** pMsgWinDat = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_COINWINDAT );
	EvWin_BtlPointWrite( core->fsys, *pMsgWinDat );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����o�g���|�C���g���擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCheckBtlPoint( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	u16 * ret_wk = VMGetWork(core);
	
	*ret_wk = TowerScoreData_SetBattlePoint(
				SaveData_GetTowerScoreData(sv),0,BTWR_DATA_get);
	return	0;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�g���|�C���g��������
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddBtlPoint( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	u16 value = VMGetWorkValue(core);

	TowerScoreData_SetBattlePoint(
			SaveData_GetTowerScoreData(sv),value,BTWR_DATA_add);

	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * �o�g���|�C���g������
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSubBtlPoint( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	u16 value = VMGetWorkValue(core);

	TowerScoreData_SetBattlePoint(
			SaveData_GetTowerScoreData(sv),value,BTWR_DATA_sub);

	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * �o�g���|�C���g���w��|�C���g�����Ă��邩�ǂ�����Ԃ��i_COMP_GOLD�̃o�g���|�C���g�Łj
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCompBtlPoint( VM_MACHINE * core )
{
	u16	now_bp;
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	u16 value = VMGetWorkValue(core);
	u16* ret_wk	= VMGetWork( core );

	now_bp = TowerScoreData_SetBattlePoint(
				SaveData_GetTowerScoreData(sv),0,BTWR_DATA_get);

	if(now_bp < value){
		*ret_wk = FALSE;
	}else{
		*ret_wk = TRUE;
	}
	return	0;
}

//--------------------------------------------------------------------------------------------
/**
 * �o�g���|�C���g�ƌ����ł���A�C�e���̃f�[�^��Ԃ�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetBtlPointGift( VM_MACHINE * core )
{
	u8	ofs = 0;
	u16	list_id = VMGetWorkValue(core);	//���X�gno
	u16	item_idx = VMGetWorkValue(core);	//�A�C�e��index
	u16* ret_item = VMGetWork(core);
	u16* ret_bp = VMGetWork(core);

	static const u16 bpgift_list[][2] = {
		{ITEM_TAURIN,1},
		{ITEM_RIZOTIUMU,1},
		{ITEM_BUROMUHEKISIN,1},
		{ITEM_KITOSAN,1},
		{ITEM_INDOMETASIN,1},
		{ITEM_MAKKUSUAPPU,1},
		{ITEM_PAWAARISUTO,16},
		{ITEM_PAWAABERUTO,16},
		{ITEM_PAWAARENZU,16},
		{ITEM_PAWAABANDO,16},
		{ITEM_PAWAAANKURU,16},
		{ITEM_PAWAAUEITO,16},
		{ITEM_DOKUDOKUDAMA,16},
		{ITEM_KAENDAMA,16},
		{ITEM_SIROIHAABU,32},
		{ITEM_PAWAHURUHAABU,32},
		{ITEM_HIKARINOKONA,48},
		{ITEM_KODAWARIHATIMAKI,48},
		{ITEM_KIAINOHATIMAKI,48},
		{ITEM_PINTORENZU,48},
		{ITEM_TIKARANOHATIMAKI,48},
		{ITEM_KIAINOTASUKI,48},
		{ITEM_KODAWARISUKAAHU,48},
		{ITEM_SURUDOITUME,48},
		{ITEM_SURUDOIKIBA,48},
		{ITEM_HUSIGINAAME,48},
		
		{ITEM_WAZAMASIN06,32},
		{ITEM_WAZAMASIN73,32},
		{ITEM_WAZAMASIN61,32},
		{ITEM_WAZAMASIN45,32},
		{ITEM_WAZAMASIN40,40},
		{ITEM_WAZAMASIN31,40},
		{ITEM_WAZAMASIN08,48},
		{ITEM_WAZAMASIN04,48},
		{ITEM_WAZAMASIN81,64},
		{ITEM_WAZAMASIN30,64},
		{ITEM_WAZAMASIN53,64},
		{ITEM_WAZAMASIN36,80},
		{ITEM_WAZAMASIN59,80},
		{ITEM_WAZAMASIN71,80},
		{ITEM_WAZAMASIN26,80},
	};

	if(list_id == 1){
		ofs = BP_GIFT_NUM01;
	}else{
		ofs = 0;
	}
	*ret_item = bpgift_list[ofs+item_idx][0];
	*ret_bp = bpgift_list[ofs+item_idx][1];

	return 0;
}
