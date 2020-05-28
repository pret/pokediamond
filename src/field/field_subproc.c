//===========================================================================
/**
 * @file	field_subproc.c
 * @brief	�t�B�[���h�ł̃T�u�v���Z�X�Ăяo���֘A
 * @author	GAME FREAK Inc.
 * @date	2005.10.21
 * 
 * fieldsys.c����؂藣���č쐬����
 *
 */
//===========================================================================
#include "common.h"

#include <nitro/code16.h> 
#define __FIELDSYS_H_GLOBAL__
#include "fieldsys.h"

#include "field_subproc.h"
#include "field/field.h"
#include "field/townmap_footmark.h"
#include "field/situation_local.h"

#include "fieldmap.h"

#include "battle/fight.h"		//BattleSystemProc
#include "battle/shinka.h"

#include "field_encount.h"		//FieldBattle_SetProc
#include "zonedata.h"
#include "savedata/config.h"
#include "savedata/trainercard_data.h"
#include "savedata/worldtrade_data.h"
#include "savedata/zukanwork.h"
#include "savedata/wifilist.h"
#include "savedata/wifihistory.h"
#include "savedata/randomgroup.h"
#include "savedata/record.h"
#include "savedata/misc.h"
#include "system/pm_rtc.h"

#include "system/gamedata.h"
#include "application/bag.h"
#include "application/pokelist.h"
#include "application/p_status.h"
#include "application/townmap.h"
#include "application/namein.h"
#include "application/tradelist.h"
#include "application/oekaki.h"
#include "application/record_corner.h"
#include "application/trainer_card.h"
#include "application\box.h"
#include "application/imageClip/imc_sys.h"
#include "application/imageClip/imc_preview.h"
#include "application/zukanlist/zkn_sys.h"
#include "application/nuts_tag.h"
#include "application/config_tool.h"
#include "application/mailtool.h"
#include "application/pms_input.h"
#include "application/f_note.h"
#include "application/cb_sys.h"
#include "application/mysign.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/poke_number.h"
#include "application/wifi_note.h"
#include "application/worldtrade.h"
#include "application/wbtower.h"
#include "application/btwr_app.h"
#include "ship_demo.h"


#include "itemtool/myitem.h"

#include "communication/communication.h"  // �ʐM�����̂���
#include "communication/comm_state.h"  // �ʐM�����̂���
#include "comm_union_def.h"
#include "comm_union.h"

#include "ev_mapchange.h"
#include "system/pm_str.h"
#include "system/mystatus.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"

#include "fld_bgm.h"

//#include "demo/opening/opening_sys.h"

#include "tv_topic.h"

#include "field_clact.h"
#include "fld_menu.h"
#include "savedata/sp_ribbon.h"
#include "savedata/randomgroup.h"

#include "field_accessory_shop.h"

#include "syswork.h"

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�֐��F�������F�퓬�i�e�X�g�j
 */
//------------------------------------------------------------------
static PROC_RESULT TestBattleProc_Init(PROC * proc, int * seq)
{
	return PROC_RES_FINISH;
}
//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�֐��F���C���F�퓬�i�e�X�g�j
 */
//------------------------------------------------------------------
static PROC_RESULT TestBattleProc_Main(PROC * proc, int * seq)
{
	if (BattleSystemProc(proc,seq)) {
		return PROC_RES_FINISH;
	} else {
		return PROC_RES_CONTINUE;
	}
}
//------------------------------------------------------------------
/**
 * @brief	�v���Z�X�֐��F�I���F�퓬�i�e�X�g�j
 */
//------------------------------------------------------------------
static PROC_RESULT TestBattleProc_End(PROC * proc, int * seq)
{
	return PROC_RES_FINISH;
}

//------------------------------------------------------------------
/**
 * @brief	�v���Z�X��`�f�[�^�F�퓬�i�e�X�g�j
 */
//------------------------------------------------------------------

//------------------------------------------------------------------
//------------------------------------------------------------------
void FieldBattle_SetProc(FIELDSYS_WORK * fsys, BATTLE_PARAM *param )
{
	FS_EXTERN_OVERLAY(battle);

static const PROC_DATA TestBattleProcData = {
	TestBattleProc_Init,
	TestBattleProc_Main,
	TestBattleProc_End,
	FS_OVERLAY_ID(battle),
};

	GameSystem_StartSubProc(fsys, &TestBattleProcData, param);
}


//===========================================================================
//===========================================================================
static const u8 FieldMenuBagList[] = {
	BAG_POKE_NORMAL, BAG_POKE_DRUG, BAG_POKE_BALL, BAG_POKE_WAZA,
	BAG_POKE_NUTS, BAG_POKE_SEAL, BAG_POKE_BATTLE, BAG_POKE_EVENT, 0xff
};
//------------------------------------------------------------------
//	�o�b�O
//------------------------------------------------------------------
void FieldBag_SubProcSet( FIELDSYS_WORK * fsys, void * buf )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(fld_bag);

	// �v���Z�X��`�f�[�^
	const PROC_DATA BagProcData = {
		BagProc_Init,
		BagProc_Main,
		BagProc_End,
		FS_OVERLAY_ID(fld_bag)
	};
	
	GameSystem_StartSubProc( fsys, &BagProcData, buf );
}

void * FieldBag_SetProc( FIELDSYS_WORK * fsys, ITEMCHECK_WORK * icwk )
{
	MYITEM * myitem;
	void * buf;

	myitem = SaveData_GetMyItem( fsys->savedata );
	buf = MyItem_MakeBagData( myitem, FieldMenuBagList, HEAPID_WORLD );

	BAG_SysDataSet( buf, fsys->savedata, BAG_MODE_FIELD, fsys->bag_cursor );

	BAG_SysMapModeSet( buf, fsys->MapMode );

	if( Player_FormGet( fsys->player ) == HERO_FORM_CYCLE ){
		BagCycleFlagSet( buf );
	}
	
	Bag_ItemUseCheckSet( buf, icwk );

	FieldBag_SubProcSet( fsys, buf );

	return buf;
}

//------------------------------------------------------------------
/**
 * �C�x���g����o�b�O��ʂ��Ăяo��
 * @param	fsys
 * @param	mode	�o�b�O�̎w��iEVBAG_MODE�̒�`���Q�Ɓj
 * @return	void *	�o�b�O��ʃp�����[�^�ւ̃|�C���^
 */
//------------------------------------------------------------------
void * FieldBagEvent_SetProc( FIELDSYS_WORK * fsys, EVBAG_MODE mode )
{
	void * buf;
	static const u8 * baglist;
	static const u8 kinomi_bag[] = {BAG_POKE_NUTS, 0xff};
	static const u8 dougu_bag[] = {BAG_POKE_NORMAL, 0xff};
	MYITEM * myitem = SaveData_GetMyItem(fsys->savedata);
	switch (mode) {
	case EVBAG_MODE_NORMAL_ONLY:
		baglist = dougu_bag;
		break;
	case EVBAG_MODE_KINOMI_ONLY:
		baglist = kinomi_bag;
		break;
	default:
		GF_ASSERT(0);
	}
	buf = MyItem_MakeBagData(myitem, baglist, HEAPID_EVENT);

	BAG_SysDataSet( buf, fsys->savedata, BAG_MODE_KINOMI, fsys->bag_cursor );

	FieldBag_SubProcSet( fsys, buf );

	return buf;
}

//------------------------------------------------------------------
/**
 * �o�b�O��ʂőI�������ǂ������󂯎��
 * @param	void *	�o�b�O��ʃp�����[�^�ւ̃|�C���^
 * @return	u16		�I�������ǂ����̃i���o�[�i�O�̂Ƃ��A�L�����Z���j
 */
//------------------------------------------------------------------
u16 FieldBagEvent_GetSelectedItem(void * param)
{
	u16 item;
	item = BagSysReturnItemGet(param);
	if (item != 0 && BagSysReturnModeGet(param) == BAG_RET_CANCEL) {
		GF_ASSERT(0);
	}
	return item;
}


//===========================================================================
//===========================================================================
//------------------------------------------------------------------
//	�؂̎��^�O
//------------------------------------------------------------------
void FieldNutsTag_SetProc( FIELDSYS_WORK * fsys, void * buf )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(nuts_tag);

	// �v���Z�X��`�f�[�^
	const PROC_DATA NutsTagProcData = {
		NutsTagProc_Init,
		NutsTagProc_Main,
		NutsTagProc_End,
		FS_OVERLAY_ID(nuts_tag)
	};

	GameSystem_StartSubProc( fsys, &NutsTagProcData, buf );
}


//===========================================================================
//===========================================================================
//------------------------------------------------------------------
//	�`���m�[�g
//------------------------------------------------------------------
void FieldFantasyNote_SetProc( FIELDSYS_WORK * fsys, void * buf )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(fnote);

	// �v���Z�X��`�f�[�^
	const PROC_DATA FantasyNoteProcData = {
		FantasyNoteProc_Init,
		FantasyNoteProc_Main,
		FantasyNoteProc_End,
		FS_OVERLAY_ID(fnote)
	};

	GameSystem_StartSubProc( fsys, &FantasyNoteProcData, fsys->savedata );

}


//============================================================================================
//============================================================================================
static PSTATUS_DATA * PSTATUS_Temoti_Create(FIELDSYS_WORK* fsys,int heapID, int mode);
//------------------------------------------------------------------
//------------------------------------------------------------------
void FieldPokeStatus_SetProc( FIELDSYS_WORK * fsys, void * psd )
{
	GameSystem_StartSubProc( fsys, &PokeStatusProcData, psd );
}

//============================================================================================
//
//
//			�|�P�������X�g�Ăяo��
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�|�P�������X�g�Ăяo���p�����[�^����
 * @param	heapID
 * @param	fsys
 * @param	type
 * @param	mode
 * @return	PLIST_DATA *
 */
//------------------------------------------------------------------
static PLIST_DATA * PLISTDATA_Create(int heapID, FIELDSYS_WORK * fsys, int type, int mode)
{
	PLIST_DATA * pld = sys_AllocMemory(heapID, sizeof(PLIST_DATA));
	MI_CpuClearFast(pld, sizeof(PLIST_DATA));
	pld->pp = SaveData_GetTemotiPokemon(fsys->savedata);
	pld->myitem = SaveData_GetMyItem( fsys->savedata );
	pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
	pld->cfg = SaveData_GetConfig( fsys->savedata );
	pld->type = type;
	pld->mode = mode;
	pld->fsys = fsys;
	return pld;
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h���j���[����̃|�P�������X�g�Ăяo��
 */
//------------------------------------------------------------------
void * FieldPokeList_SetProc( FIELDSYS_WORK * fsys, SKILLCHECK_WORK * scwk, u8 pos )
{
	PLIST_DATA * pld = PLISTDATA_Create(HEAPID_WORLD, fsys, PL_TYPE_SINGLE, PL_MODE_FIELD);
	pld->scwk = scwk;			//�킴�g�p����
	pld->ret_sel = pos;			//�I�������ʒu
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	return pld;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g����̃|�P�������X�g�Ăяo���i�I���̂݁j
 * @param	heap	�g�p����q�[�v�̎w��
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	void *	�|�P�������X�g�p�p�����[�^�̃|�C���^
 */
//------------------------------------------------------------------
void * FieldPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys)
{
	PLIST_DATA * pld = PLISTDATA_Create(HEAPID_WORLD, fsys, PL_TYPE_SINGLE, PL_MODE_SET);
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	return pld;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g����̃|�P�������X�g�Ăяo���i�Q�[���������j
 * @param	heap	�g�p����q�[�v�̎w��
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	void *	�|�P�������X�g�p�p�����[�^�̃|�C���^
 */
//------------------------------------------------------------------
void * FieldPokeListEventNpcTrade_SetProc(int heap, FIELDSYS_WORK * fsys)
{
	PLIST_DATA * pld = PLISTDATA_Create(HEAPID_WORLD, fsys, PL_TYPE_SINGLE, PL_MODE_NPC_TRADE);
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );
	return pld;
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�������X�g�I�����ʂ̎擾
 * @param	wk		�|�P�������X�g�p�p�����[�^�̃|�C���^
 * @return	int		�I������
 */
//------------------------------------------------------------------
int FieldPokeListEvent_GetSelect(void * wk)
{
	PLIST_DATA * pld = wk;
	return pld->ret_sel;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g����̃|�P�������X�g�Ăяo��(�����Ă��p�Łj
 * @param	heap	�g�p����q�[�v�̎w��
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	pos 	�����ʒu
 * @return	void *	�|�P�������X�g�p�p�����[�^�̃|�C���^
 */
//------------------------------------------------------------------
void * SodateyaPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys, int pos)
{
	PLIST_DATA * pld = PLISTDATA_Create(HEAPID_WORLD, fsys, PL_TYPE_SINGLE, PL_MODE_SODATEYA);
	pld->ret_sel = pos;
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	return pld;
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�������X�g�I�����ʂ̃��[�h�擾
 * @param	wk		�|�P�������X�g�p�p�����[�^�̃|�C���^
 * @return	int		�I������
 */
//------------------------------------------------------------------
int FieldPokeListEvent_GetMode(void * wk)
{
	PLIST_DATA * pld = wk;
	return pld->ret_mode;
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�����X�e�[�^�X�I�����ʂ̎擾
 * @param	wk		�|�P�����X�e�[�^�X�p�p�����[�^�̃|�C���^
 * @return	int		�I������
 */
//------------------------------------------------------------------
int FieldPokeStatusEvent_GetPos(void * wk)
{
	PSTATUS_DATA * psd = wk;
	return psd->pos;
}

//------------------------------------------------------------------
/**
 * @brief	���j�I�����[���ΐ�̎��̃|�P�������X�g�Ăяo��
 * @param	heap	�g�p����q�[�v�̎w��
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	void *	�|�P�������X�g�p�p�����[�^�̃|�C���^
 */
//------------------------------------------------------------------
void * UnionPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys)
{
	PLIST_DATA * pld = PLISTDATA_Create(HEAPID_WORLD, fsys, PL_TYPE_SINGLE, PL_MODE_SELECT);
	pld->in_min = 2;		// �Q���ŏ���
	pld->in_max = 2;		// �Q���ő吔
	pld->in_lv  = 30;		// �Q�����x��
	pld->reg    = NULL;		// ���M�����[�V�����֌W�Ȃ�

	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	return pld;
}

typedef struct {
	int heapID;
	PLIST_DATA * pld;
	PSTATUS_DATA * psd;
}UNION_PMLIST_WORK;

//------------------------------------------------------------------
/**
 * @brief   ���j�I�����[���ΐ�p�|�P�������X�g�I��҂��C�x���g
 *
 * @param   event		
 *
 * @retval  BOOL		TRUE:�C�x���g�I��
 */
//------------------------------------------------------------------
static BOOL GMEVENT_UnionPokeList(GMEVENT_CONTROL * event)
{
	enum {
		SEQ_POKELIST_CALL = 0,
		SEQ_POKELIST_WAIT,
		SEQ_POKESTATUS_CALL,
		SEQ_POKESTATUS_WAIT,
		SEQ_POKELIST_DECIDE,
	};
	FIELDSYS_WORK * fsys;
	UNION_PMLIST_WORK * upw;
	int * seq;

	fsys = FieldEvent_GetFieldSysWork(event);
	upw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case SEQ_POKELIST_CALL:
		GameSystem_StartSubProc(fsys, &PokeListProcData, upw->pld);
		*seq = SEQ_POKELIST_WAIT;
		break;
	case SEQ_POKELIST_WAIT:
		if (!FieldEvent_Cmd_WaitSubProcEnd(fsys)) {
			switch (upw->pld->ret_sel) {
			case PL_SEL_POS_EXIT:	//��߂�
				Union_BattlePokeListResult( UNION_BATTLE_POKELIST_NG );
				*seq = SEQ_POKELIST_DECIDE;
				break;
			case PL_SEL_POS_ENTER:	//����
				Union_BattlePokeListResult( UNION_BATTLE_POKELIST_OK );
				*seq = SEQ_POKELIST_DECIDE;
				break;
			default:				//���̑�������������
				*seq = SEQ_POKESTATUS_CALL;
			}
		}
		break;
	case SEQ_POKESTATUS_CALL:
		upw->psd = PSTATUS_Temoti_Create(fsys, upw->heapID, PST_MODE_NORMAL);
		upw->psd->pos = upw->pld->ret_sel;
		FieldPokeStatus_SetProc( fsys, upw->psd );
		*seq = SEQ_POKESTATUS_WAIT;
		break;
	case SEQ_POKESTATUS_WAIT:
		if (!FieldEvent_Cmd_WaitSubProcEnd(fsys)) {
			sys_FreeMemoryEz(upw->psd);
			*seq = SEQ_POKELIST_CALL;
		}
		break;
	case SEQ_POKELIST_DECIDE:
		//sys_FreeMemoryEz(upw->pld);
		sys_FreeMemoryEz(upw);
		return TRUE;
	}
	return FALSE;
}

//==============================================================================
/**
 * @brief   ���j�I�����[���ΐ�p�|�P�������X�g�Ăяo��
 *
 * @param   event		
 * @param   heapID		
 *
 * @retval  void *		�|�P�������X�g���[�N�|�C���^
 */
//==============================================================================
void * EventCmd_PokeListSelect(GMEVENT_CONTROL * event, int heapID)
{
	UNION_PMLIST_WORK * upw;
	PLIST_DATA * pld;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	upw = sys_AllocMemory(heapID, sizeof(UNION_PMLIST_WORK));
	upw->heapID = heapID;
	pld = PLISTDATA_Create(heapID, fsys, PL_TYPE_SINGLE, PL_MODE_SELECT);
	pld->in_min = 2;		// �Q���ŏ���
	pld->in_max = 2;		// �Q���ő吔
	pld->in_lv  = 30;		// �Q�����x��
	pld->reg    = NULL;		// ���M�����[�V�����֌W�Ȃ�
	upw->pld = pld;
	FieldEvent_Call(event, GMEVENT_UnionPokeList, upw);
	return pld;
}


//------------------------------------------------------------------
/**
 * @brief	�R���e�X�g�Q���I���C�x���g����̃|�P�������X�g�Ăяo��
 * @param	heap	�g�p����q�[�v�̎w��
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param   con_type	CONTYPE_???
 * @param   con_rank	CONRANK_???
 * @param   sio_flag	TRUE:�ʐM��t�A�@FALSE:��l�p��t
 * @param   pos			�ŏ��ɊJ�����̃J�[�\�������ʒu
 * @return	void *	�|�P�������X�g�p�p�����[�^�̃|�C���^
 */
//------------------------------------------------------------------
void * ContestPokeListEvent_SetProc(int heap, FIELDSYS_WORK * fsys, 
	int con_type, int con_rank, int sio_flag, int pos)
{
	PLIST_DATA * pld = PLISTDATA_Create(HEAPID_WORLD, fsys, PL_TYPE_SINGLE, PL_MODE_CONTEST);
	pld->ret_sel = pos;
	pld->con_mode = CONMODE_GRAND;	//��{�����ꂽ�̂ŁA�O�����h�Œ�
	pld->con_type = con_type;		//�R���e�X�g�^�C�v
	if(sio_flag == FALSE){
		pld->con_rank = con_rank;
	}
	else{	//�ʐM�̎��͎Q���t���[�ɂ��邽�߁ANORMAL�Œ�ɂ���
		pld->con_rank = CONRANK_NORMAL;
	}
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	return pld;
}

//------------------------------------------------------------------
/**
 * @brief	�R���e�X�g�Q���I���C�x���g����̃|�P�����X�e�[�^�X�Ăяo��
 * 
 * @param	heap	�g�p����q�[�v�̎w��
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param   pos		�ŏ��ɊJ���莝���J�n�ʒu
 *
 * @return	void *	�|�P�������X�g�p�p�����[�^�̃|�C���^
 */
//------------------------------------------------------------------
void * ContestPokeStatusEvent_SetProc(int heap, FIELDSYS_WORK * fsys, int pos)
{
	PSTATUS_DATA * psd = sys_AllocMemory( HEAPID_WORLD, sizeof(PSTATUS_DATA) );

	psd->ppd  = SaveData_GetTemotiPokemon(fsys->savedata);
	psd->cfg  = SaveData_GetConfig( fsys->savedata );
	psd->ppt  = PST_PP_TYPE_POKEPARTY;
	psd->pos  = pos;
	psd->max  = (u8)PokeParty_GetPokeCount( psd->ppd );
	psd->waza = 0;
	psd->mode = PST_MODE_NORMAL;
	psd->ribbon = SaveData_GetSpRibbon( fsys->savedata );
	psd->zukan_mode = PMNumber_GetMode( fsys->savedata );
	psd->ev_contest = PokeStatus_ContestFlagGet( fsys->savedata );
	psd->perap = NULL;
	PokeStatus_PageSet( psd, PST_PageTbl_Normal );
	PokeStatus_PlayerSet( psd, SaveData_GetMyStatus(fsys->savedata) );

	GameSystem_StartSubProc( fsys, &PokeStatusProcData, psd );

	return psd;
}

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 */
//------------------------------------------------------------------
static PSTATUS_DATA * PSTATUS_Temoti_Create(FIELDSYS_WORK* fsys,int heapID, int mode)
{
	PSTATUS_DATA* psd;
	SAVEDATA	*sv;

	static const u8 PST_PageTbl[] = {
		PST_PAGE_INFO,			// �u�|�P�������傤�ق��v
		PST_PAGE_MEMO,			// �u�g���[�i�[�����v
		PST_PAGE_PARAM,			// �u�|�P�����̂���傭�v
		PST_PAGE_CONDITION,		// �u�R���f�B�V�����v
		PST_PAGE_B_SKILL,		// �u���������킴�v
		PST_PAGE_C_SKILL,		// �u�R���e�X�g�킴�v
		PST_PAGE_RIBBON,		// �u���˂񃊃{���v
		PST_PAGE_RET,			// �u���ǂ�v
		PST_PAGE_MAX
	};
	
	sv = fsys->savedata;

	//�|�P�����X�e�[�^�X���Ăяo��
	//
	psd = sys_AllocMemoryLo(heapID, sizeof(PSTATUS_DATA));
	MI_CpuClear8(psd,sizeof(PSTATUS_DATA));

	psd->cfg  = SaveData_GetConfig(sv);
	psd->ppd  = SaveData_GetTemotiPokemon(sv);
	psd->ppt  = PST_PP_TYPE_POKEPARTY;
	psd->pos  = 0;
	psd->max  = PokeParty_GetPokeCount( psd->ppd );
	psd->waza = 0;
	psd->mode = mode;
	psd->zukan_mode = PMNumber_GetMode( sv );
	psd->ev_contest = PokeStatus_ContestFlagGet( sv );
	psd->ribbon = SaveData_GetSpRibbon(sv);
	PokeStatus_PageSet( psd, PST_PageTbl);
	PokeStatus_PlayerSet( psd, SaveData_GetMyStatus(sv) );
	
	return psd;
}

//------------------------------------------------------------------
//	�킴�Y�ꃊ�X�g
//------------------------------------------------------------------
static const u8 PST_PageTbl_WazaSet[] = {
	PST_PAGE_B_SKILL,		// �u���������킴�v
	PST_PAGE_C_SKILL,		// �u�R���e�X�g�킴�v
//	PST_PAGE_RET,			// �u���ǂ�v
	PST_PAGE_MAX
};
//------------------------------------------------------------------
/**
 * @brief	�C�x���g����̂킴���X�g�Ăяo��(�킴�Y��j
 * @param	heap	�g�p����q�[�v�̎w��
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	void *	�|�P�������X�g�p�p�����[�^�̃|�C���^
 */
//------------------------------------------------------------------
void * FieldWazaListEvent_SetProc(int heap, FIELDSYS_WORK * fsys, u8 pos)
{
	PSTATUS_DATA * psd = sys_AllocMemory( heap, sizeof(PSTATUS_DATA) );

	memset( psd, 0, sizeof(PSTATUS_DATA) );
	psd->ppd = SaveData_GetTemotiPokemon(fsys->savedata);
	psd->cfg  = SaveData_GetConfig( fsys->savedata );
	psd->ppt  = PST_PP_TYPE_POKEPARTY;
	psd->pos  = pos;
	psd->max  = 1;
	psd->waza = 0;
	psd->mode = PST_MODE_WAZAADD;
	psd->zukan_mode = PMNumber_GetMode( fsys->savedata );
	psd->ev_contest = PokeStatus_ContestFlagGet( fsys->savedata );
	PokeStatus_PageSet( psd, PST_PageTbl_WazaSet );
	PokeStatus_PlayerSet( psd, SaveData_GetMyStatus(fsys->savedata) );
	FieldPokeStatus_SetProc( fsys, psd );

	return psd;
}

//------------------------------------------------------------------
/**
 * @brief	�킴���X�g�I�����ʂ̎擾�i�Z�Y��p�j
 * @param	wk		�|�P�������X�g�p�p�����[�^�̃|�C���^
 * @return	int		�I������
 */
//------------------------------------------------------------------
int FieldWazaListEvent_GetSelect(void * wk)
{
	PSTATUS_DATA * psd = wk;
	return psd->ret_sel;
}

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
// �{�b�N�X�֘A
//------------------------------------------------------------------
void FieldBox_SetProc( FIELDSYS_WORK * fsys, BOX_PROC_PARAM* param )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(overlay_box);

	// �v���Z�X��`�f�[�^
	static const PROC_DATA BoxProcData = {
		BoxProc_Init,
		BoxProc_Main,
		BoxProc_End,
	///	NO_OVERLAY_ID,
		FS_OVERLAY_ID(overlay_box),
	};


	GameSystem_StartSubProc(fsys,  &BoxProcData, param );
}


//==============================================================================================
// �ȈՉ�b���
//==============================================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
typedef struct {
	u16 * result;		///<���͂������ǂ����̌��ʂ�Ԃ����[�N�ւ̃|�C���^
	u16 * pms1;			///<���͒P��P��Ԃ����[�N�ւ̃|�C���^
	u16 * pms2;			///<���͒P��Q��Ԃ����[�N�ւ̃|�C���^
	PMSI_PARAM * param;	///<�ȈՉ�b���͂ɕK�v�ȃ��[�N�ւ̃|�C���^
}PMSEVENT_WORK;

//------------------------------------------------------------------
/**
 * @brief	�ȈՉ�b�Ăяo���C�x���g
 */
//------------------------------------------------------------------
static BOOL GMEVENT_PMSInput(GMEVENT_CONTROL * event)
{
	int * seq = FieldEvent_GetSeqWork(event);
	PMSEVENT_WORK * pew = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	switch (*seq) {
	case 0:
		FieldProc_SetPmsInput(fsys, pew->param);
		(*seq) ++;
		break;
	case 1:
		if(!FieldEvent_Cmd_WaitSubProcEnd(fsys)) {
			(*seq) ++;
		}
		break;
	case 2:
		if (PMSI_PARAM_CheckCanceled(pew->param) || !PMSI_PARAM_CheckModified(pew->param)) {
			*(pew->result) = FALSE;	//�L�����Z���A���邢�͕ύX�Ȃ�
		} else {
			*(pew->result) = TRUE;	//���͂��ꂽ
			if (pew->pms2 == NULL) {
				//�P���̏ꍇ
				*(pew->pms1) = PMSI_PARAM_GetInputDataSingle(pew->param);
			} else {
				//�P���̏ꍇ
				PMS_WORD result[2];
				PMSI_PARAM_GetInputDataDouble(pew->param, result);
				*(pew->pms1) = result[0];
				*(pew->pms2) = result[1];
			}
		}
		PMSI_PARAM_Delete(pew->param);
		sys_FreeMemoryEz(pew);
		return TRUE;
		break;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�R�}���h�F�ȈՉ�b�Ăяo��
 */
//------------------------------------------------------------------
void EventCmd_PMSInput(GMEVENT_CONTROL * event, u16 * result, u16 * pms1, u16 * pms2)
{
	PMSEVENT_WORK * pew;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	
	pew = sys_AllocMemory(HEAPID_EVENT, sizeof(PMSEVENT_WORK));
	pew->result = result;
	pew->pms1 = pms1;
	pew->pms2 = pms2;
	if (pms2 == NULL) {
		//�P���̏ꍇ
		pew->param = PMSI_PARAM_Create(PMSI_MODE_SINGLE,
				PMSI_GUIDANCE_DEFAULT, fsys->savedata, HEAPID_EVENT);
		PMSI_PARAM_SetInitializeDataSingle(pew->param, *pms1);
	} else {
		//�P���̏ꍇ
		pew->param = PMSI_PARAM_Create(PMSI_MODE_DOUBLE,
				PMSI_GUIDANCE_DEFAULT, fsys->savedata, HEAPID_EVENT);
		PMSI_PARAM_SetInitializeDataDouble(pew->param, *pms1, *pms2);
	}

	FieldEvent_Call(event, GMEVENT_PMSInput, pew);
}

//------------------------------------------------------------------
// �ȈՉ�b���
//------------------------------------------------------------------

void FieldProc_SetPmsInput( FIELDSYS_WORK* fsys, PMSI_PARAM* param )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(overlay_pmsi);

	// �v���Z�X��`�f�[�^
	static const PROC_DATA proc_data = {
		PMSInput_Init,
		PMSInput_Main,
		PMSInput_Quit,
		FS_OVERLAY_ID(overlay_pmsi),
	};


	GameSystem_StartSubProc(fsys, &proc_data, param );
}



//==============================================================================================
//==============================================================================================
//-------------------------------------------------------------------
// �^�E���}�b�v�֘A
//-------------------------------------------------------------------
#define  OSP_TMAP_HEAP_SIZE 0

//-------------------------------------------------------------------
/**
 *	@brief	�t�B�[���h ���[���h�}�b�v���W���[���Ăяo��
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	mode	u8:�Ăяo�����[�h(enum TMAP_MODE)
 *	@param	work	void*:���[�N�̈��p��
 *
 *	@retval	0:����
 *	@retval else	���s
 */
//-------------------------------------------------------------------
void FieldTMap_SetProc(FIELDSYS_WORK *fsys, TOWNMAP_PARAM * tp)
{
	TMAP_IO_DAT* wk;

	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(townmap);

	///�I�[�o�[���C�v���Z�X��`�f�[�^
	const PROC_DATA TMapProcData = {
		TMapProc_Init,
		TMapProc_Main,
		TMapProc_End,
		FS_OVERLAY_ID(townmap)
	};

	GameSystem_StartSubProc(fsys, &TMapProcData,tp);
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
void * FieldMenuTMap_SetProc( FIELDSYS_WORK * fsys )
{
	TOWNMAP_PARAM * tp;
    MYSTATUS* pMyStatus;
	int i = 0,pos = 0;
	TOWN_MAP_FOOTMARK * fmark
		= Situation_GetTMFootMark(SaveData_GetSituation(fsys->savedata));
	
	tp = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(TOWNMAP_PARAM));

	//�f�[�^�Z�b�g
	FieldTMap_CallDataSet(fsys,tp,TMAP_MNORMAL);
	FieldTMap_SetProc( fsys, tp );
	return tp;
}


//-------------------------------------------------------------------
/**
 *	@brief	�R���t�B�O��ʌĂяo��(�t�B�[���h����)
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	CONFIG*	:�R���t�B�O�Z�[�u�f�[�^�n���h���ւ̃|�C���^
 */
//-------------------------------------------------------------------
static void ConfigTool_SetProc(FIELDSYS_WORK* fsys,CONFIG* sp)
{
	//�I�[�o�[���CID��`
	FS_EXTERN_OVERLAY(config);

	//�I�[�o�[���C�v���Z�X��`�f�[�^
	static const PROC_DATA ConfigProcData = {
		ConfigProc_Init,
		ConfigProc_Main,
		ConfigProc_End,
//		NO_OVERLAY_ID,
		FS_OVERLAY_ID(config),
	};
	GameSystem_StartSubProc(fsys, &ConfigProcData,sp);
}

/**
 *	@brief	�R���t�B�O��ʃt�B�[���h���j���[�Ăяo��
 *	
 *	@param	fsys FIELDSYS_WORK *
 *
 *	@retval	CONFIG_PARAM* :�����m�ۂ����p�����[�^���[�N�ւ̃|�C���^
 *						�@�@�Ăяo�����������I�ɉ������K�v����
 */
void * FieldConfig_SetProc( FIELDSYS_WORK * fsys )
{
	CONFIG_PARAM* cp;
	CONFIG*	sp;

	cp = sys_AllocMemoryLo(HEAPID_WORLD,sizeof(CONFIG_PARAM));

	//�R���t�B�O�Z�[�u�f�[�^�擾
	sp = SaveData_GetConfig(GameSystem_GetSaveData(fsys));
	ConfigTool_SetProc(fsys,sp);

	return cp;
}

//==============================================================================================
//==============================================================================================
extern const PROC_DATA MailSysProcData;
/**
 *	@brief	���[���쐬�Ăяo��(�t�B�[���h����)
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	MAIL_PARAM*	:���[���p�����[�^�ւ̃|�C���^
 */
static void MailSys_SetProc(FIELDSYS_WORK* fsys,MAIL_PARAM* mp)
{
	GameSystem_StartSubProc(fsys, &MailSysProcData,mp);
}

/**
 *	@brief	���[���쐬��ʃt�B�[���h���j���[�Ăяo��
 *	
 *	@param	fsys FIELDSYS_WORK *
 *
 *	@retval	MAIL_PARAM* :�����m�ۂ����p�����[�^���[�N�ւ̃|�C���^
 *						�@�@�Ăяo�����������I�ɉ������K�v����
 *
 *					TRUE�Ȃ烁�[�����쐬�AFALSE�̎��͖��쐬
 */
MAIL_PARAM * FieldMailCreate_InitCall( FIELDSYS_WORK * fsys ,
		MAILBLOCK_ID blockID,u8 poke_pos,u8 design,int heapID)
{
	MAIL_PARAM*	pRet;

	pRet = MailSys_GetWorkCreate(GameSystem_GetSaveData(fsys),
			blockID,poke_pos,design,HEAPID_WORLD);

#if 0
	if(pRet == NULL){
		return NULL;	//�쐬�󂫗̈悪�Ȃ�
	}
#endif
	MailSys_SetProc(fsys,pRet);
	return pRet;
}

/**
 *	@brief	���[���`���ʃt�B�[���h���j���[�Ăяo��
 *	
 *	@param	fsys FIELDSYS_WORK *
 *
 *	@retval	MAIL_PARAM* :�����m�ۂ����p�����[�^���[�N�ւ̃|�C���^
 *						�@�@�Ăяo�����������I�ɉ������K�v����
 *
 *	���󃁁[����\���������ꍇ�ɂ�
 *		MAILBLOCK_ID�� MAILBLOCK_NULL��
 *		dataID �� �f�U�C��No�@��
 *	�@�n���ČĂяo���܂�
 */
MAIL_PARAM * FieldMailView_InitCall( FIELDSYS_WORK * fsys,
		MAILBLOCK_ID blockID,u8 dataID,int heapID)
{
	MAIL_PARAM*	pRet;

	if(blockID == MAILBLOCK_NULL){
		//�G���݂̂̃v���r���[
		pRet = MailSys_GetWorkViewPrev(GameSystem_GetSaveData(fsys),dataID,heapID);
	}else{
		pRet = MailSys_GetWorkView(GameSystem_GetSaveData(fsys),
				blockID,dataID,heapID);
	}

	MailSys_SetProc(fsys,pRet);

	return pRet;
}

/**
 *	@brief	���[���`���ʃt�B�[���h���j���[�Ăяo��(�|�P�������[��)
 *	
 *	@param	fsys FIELDSYS_WORK *
 *
 *	@retval	MAIL_PARAM* :�����m�ۂ����p�����[�^���[�N�ւ̃|�C���^
 *						�@�@�Ăяo�����������I�ɉ������K�v����
 *
 */
MAIL_PARAM * FieldMailViewPoke_InitCall( FIELDSYS_WORK * fsys,
		POKEMON_PARAM* poke,int heapID)
{
	MAIL_PARAM*	pRet;

	pRet = MailSys_GetWorkViewPoke(GameSystem_GetSaveData(fsys),poke,heapID);

	MailSys_SetProc(fsys,pRet);

	return pRet;
}

//-----------------------------------------------------------------------------
/**
*	�|���g�֘A
*/
//-----------------------------------------------------------------------------
/**
 *	@brief	�|���g�P�[�X�T�u�v���Z�X�o�^
 */
static void PorutoSys_SetProc(FIELDSYS_WORK* fsys,PORUTO_PARAM* pp)
{
	GameSystem_StartSubProc(fsys, &PorutoSysProcData,pp);
}

/**
 *	@brief	�|���g�P�[�X�Ăяo��
 */
PORUTO_PARAM* FieldPorutoCase_InitCall(FIELDSYS_WORK* fsys,int heapID)
{
	PORUTO_PARAM* pp;
	
	pp = PorutoSys_CreateCallWork(GameSystem_GetSaveData(fsys),heapID);	
	PorutoSys_SetProc(fsys,pp);
	
	return pp;
}

/**
 *	@brief	�t�B�[���h �^���[�A�v���Ăяo��
 *
 *	@param	fsys FIELDSYS_WORK *
 *	@param	work	void*:���[�N�̈��p��
 *
 *	@retval	0:����
 *	@retval else	���s
 */
void BTowerApp_SetProc(FIELDSYS_WORK *fsys,BTOWER_APP_PARAM * ap)
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(btower_app);

	///�I�[�o�[���C�v���Z�X��`�f�[�^
	const PROC_DATA BTowerAppProcData = {
		BTowerAppProc_Init,
		BTowerAppProc_Main,
		BTowerAppProc_End,
		FS_OVERLAY_ID(btower_app)
//		NO_OVERLAY_ID
	};

	GameSystem_StartSubProc(fsys, &BTowerAppProcData,ap);
}
//-----------------------------------------------------------------------------
/**
*	�C���[�W�N���b�v�֘A
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�C���[�W�N���b�v�@���s�C�x���g���[�N
//=====================================
typedef struct {
	u32 seq;
	u16* result;
	BOOL imc_save_flg;
	IMC_PROC_WORK* p_imc_w;
} IMGCLIP_TVEVENT_WORK;


//--------------------------------------------------------------------------------------------
//	�N���b�v�f�[�^�쐬
//--------------------------------------------------------------------------------------------
static IMC_PROC_WORK* ImageClip_DataMake( int heap, SAVEDATA* p_savedata, int pos, BOOL* p_save_flg, BOOL reference )
{
	IMC_PROC_WORK* imc_w;
	POKEMON_PARAM* poke;
	int poke_no;
	IMC_SAVEDATA* p_save;
	IMC_TELEVISION_SAVEDATA* p_save_one;
	IMC_ITEM_SAVEDATA* p_save_item;

	// �C���[�W�N���b�v�ɓn���f�[�^�쐬
	imc_w = sys_AllocMemory( heap, sizeof( IMC_PROC_WORK ) );
	memset( imc_w, 0, sizeof( IMC_PROC_WORK ) );

	//�|�P�����ւ̃|�C���^�擾
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(p_savedata), pos);

	imc_w->p_poke_para = poke;
	// �Z�[�u�f�[�^
	p_save = SaveData_GetImcSaveData( p_savedata );
	p_save_one = ImcSaveData_GetTelevisionSaveData( p_save, 0 );
	p_save_item = ImcSaveData_GetItemSaveData( p_save );
	imc_w->p_imc_one_data = p_save_one;
	imc_w->cp_imc_item =  p_save_item;

	imc_w->cp_config = SaveData_GetConfig( p_savedata );
	imc_w->p_record = SaveData_GetRecord( p_savedata );
	imc_w->cp_tr	= SaveData_GetMyStatus( p_savedata );
	imc_w->p_save_flg = p_save_flg;
	imc_w->reference = reference;

	return imc_w;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�e���r�p�C���[�W�N���b�v�@�Ǘ��C�x���g
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_ImcClip_TV(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	IMGCLIP_TVEVENT_WORK * p_imc_w = FieldEvent_GetSpecialWork(event);

	switch( p_imc_w->seq ){
	case 0:
		// �C���[�W�N���b�v�Ăяo��
		FieldImageClip_SetProc( fsys, p_imc_w->p_imc_w );
		p_imc_w->seq ++;
		break;

	case 1:	
		// �I���҂�
		if( FieldEvent_Cmd_WaitSubProcEnd(fsys) == FALSE ){		//�T�u�v���Z�X�I���҂�
			if( p_imc_w->imc_save_flg == TRUE ){
				*p_imc_w->result = 1;
			}else{
				*p_imc_w->result = 0;
			}
			// ���[�N�̔j��
			sys_FreeMemoryEz( p_imc_w->p_imc_w );
			sys_FreeMemoryEz( p_imc_w );
			return TRUE;	// �I��
		}
		break;
	}
	return FALSE;	// ���s
}

//----------------------------------------------------------------------------
/**
 *	@brief	�C���[�W�N���b�v�@�e���r�Ǘp�@�C�x���g�J�n
 *
 *	@param	event		�C�x���g
 *	@param	result		�߂�l�i�[���[�N	�X�N���v�g�p�Ȃ̂�u16
 *	@param	p_save		�Z�[�u�f�[�^
 *	@param	pos			�|�P�p�[�e�B�[�ʒu
 */
//-----------------------------------------------------------------------------
void EventCmd_ImcClipTvStart(GMEVENT_CONTROL * event, u16* result, SAVEDATA* p_save, u16 pos, u16 reference )
{
	IMGCLIP_TVEVENT_WORK* p_imc_w;

	// �C�x���g���[�N�쐬
	p_imc_w  = sys_AllocMemory( HEAPID_EVENT, sizeof(IMGCLIP_TVEVENT_WORK) );
	memset( p_imc_w, 0, sizeof(IMGCLIP_TVEVENT_WORK) );
	
	// �C���[�W�N���b�v�f�[�^�쐬
	p_imc_w->p_imc_w = ImageClip_DataMake( HEAPID_EVENT, p_save, pos, &p_imc_w->imc_save_flg, reference );
	p_imc_w->result = result;

	// �C�x���g����
	FieldEvent_Call(event, GMEVENT_ImcClip_TV, p_imc_w);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�v�v���b�N�Z�b�g
 *
 *	@param	fsys		�t�B�[���h���[�N
 *	@param	buff		�f�[�^�o�b�t�@	�i����NULL�j
 *
 *	@retval		TRUE	����
 *	@retval		FALSE	���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL FieldImageClip_SetProc( FIELDSYS_WORK * fsys, void* buff )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(ol_imageclip);
	
	// �v���b�N�f�[�^
	static PROC_DATA IMC_SYS_Proc = {
		IMC_ProcInit,
		IMC_ProcMain,
		IMC_ProcEnd,
		FS_OVERLAY_ID(ol_imageclip),
	};

	GameSystem_StartSubProc(fsys,  &IMC_SYS_Proc, buff );

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C���[�W�N���b�vViewer�v���b�N�Z�b�g
 *
 *	@param	fsys		�t�B�[���h���[�N
 *	@param	buff		�f�[�^�o�b�t�@	�i����NULL�j
 *
 *	@retval		TRUE	����
 *	@retval		FALSE	���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL FieldImageClipViewer_SetProc( FIELDSYS_WORK * fsys, void* buff )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(ol_imageclip);
	
	// �v���b�N�f�[�^
	static PROC_DATA IMC_SYS_Proc = {
		IMC_Prev_ProcInit,
		IMC_Prev_ProcMain,
		IMC_Prev_ProcEnd,
		FS_OVERLAY_ID(ol_imageclip),
	};

	GameSystem_StartSubProc(fsys,  &IMC_SYS_Proc, buff );

	return TRUE;
}


//-----------------------------------------------------------------------------
/**
*	���O����(��l���E�|�P�����E�{�b�N�X)
*
* @param param(���e��namein.h���Q�Ɓj
*
*/
//-----------------------------------------------------------------------------
void NameInput_SetProc( FIELDSYS_WORK * fsys, void *param)
{

	GameSystem_StartSubProc(fsys,  &NameInProcData, param );

}


//==============================================================================
//
//
//				�ʐM�������X�g��ʌĂяo��
//
//
//==============================================================================
// �I�[�o�[���CID�錾
FS_EXTERN_OVERLAY(tradelist);

// �v���b�N�f�[�^
static PROC_DATA TradeListProcData = {
	TradeListProc_Init,
	TradeListProc_Main,
	TradeListProc_End,
	FS_OVERLAY_ID(tradelist),
};

// �����f��
#include "demo\demo_trade.h"
#include "system\timezone.h"
#include "ev_time.h"

FS_EXTERN_OVERLAY(demo_trade);

static const PROC_DATA  TradeDemoProcData = {
	TradeDemoProc_Init,
	TradeDemoProc_Main,
	TradeDemoProc_Quit,
	FS_OVERLAY_ID(demo_trade),
};

typedef struct {
	int seq;
	TRADELIST_PARAM		tradeparam;
	DEMO_TRADE_PARAM	demoparam;
	SHINKA_WORK			*shinka_work;
	int					times;			// �������X�g���Ă񂾉�
}TRADE_CONTROL_WORK;


//------------------------------------------------------------------
/**
 * �������X�g��ʃp�����[�^�\�z
 *
 * @param   param		
 * @param   fsys		
 *
 */
//------------------------------------------------------------------
static void  SetupTradeListParam( TRADELIST_PARAM* param, FIELDSYS_WORK* fsys )
{
	param->mystatus    = SaveData_GetMyStatus(fsys->savedata);
	param->myparty     = SaveData_GetTemotiPokemon(fsys->savedata);
	param->friendlist  = SaveData_Get(fsys->savedata, GMDATA_ID_FRIEND);
	param->wifihistory = SaveData_GetWifiHistory(fsys->savedata);
	param->config      = SaveData_GetConfig( fsys->savedata );
	param->zukanwork   = SaveData_GetZukanWork(fsys->savedata);
	param->zukanmode   = PMNumber_GetMode(fsys->savedata);
	param->savedata    = fsys->savedata;
	param->fnote       = fsys->fnote;
	param->record      = SaveData_GetRecord(fsys->savedata);
	param->result_partner  = sys_AllocMemory( HEAPID_EVENT, MyStatus_GetWorkSize() );
	param->result_sendPoke = sys_AllocMemory( HEAPID_EVENT, PokemonParamSizeGet() );
	param->result_recvPoke = sys_AllocMemory( HEAPID_EVENT, PokemonParamSizeGet() );
	param->fsys            = fsys;
	param->times           = 0;
}
//------------------------------------------------------------------
/**
 * �������X�g��ʃp�����[�^�j��
 *
 * @param   param		
 *
 */
//------------------------------------------------------------------
static void CleanupTradeListParam( TRADELIST_PARAM* param )
{
	if( param->result_partner )
	{
		sys_FreeMemoryEz( param->result_partner );
		param->result_partner = NULL;
	}
	if( param->result_sendPoke )
	{
		sys_FreeMemoryEz( param->result_sendPoke );
		param->result_sendPoke = NULL;
	}
	if( param->result_recvPoke )
	{
		sys_FreeMemoryEz( param->result_recvPoke );
		param->result_recvPoke = NULL;
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
BOOL GMEVENT_UnionTradeList(GMEVENT_CONTROL * event)
{
	int len;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	TRADE_CONTROL_WORK * tcw = FieldEvent_GetSpecialWork(event);

	switch (tcw->seq) {
	case 0:
        if(!CommStateIsWifiConnect()){
            EventCmd_FinishFieldMap(event);
        }
		tcw->seq ++;
		break;
	case 1:
		SetupTradeListParam( &(tcw->tradeparam), fsys );
		tcw->seq++;
		/* fallthru */
	case 2:
		EventCmd_CallSubProc(event, &TradeListProcData, &tcw->tradeparam);
		tcw->seq ++;
		break;

//	������ĂԕK�v�͂���̂��H�H
//	case 2:
//		EventCmd_StartFieldMap(event);

	case 3:
		if (tcw->tradeparam.result == TRADELIST_END_FINISH){
			CleanupTradeListParam( &(tcw->tradeparam) );
			sys_FreeMemoryEz(tcw);
			return TRUE;
		}
		tcw->seq ++;
		break;
	case 4:
		/* �����f���Ăяo���@ */
		tcw->demoparam.partner  = tcw->tradeparam.result_partner;
		tcw->demoparam.sendPoke = PPPPointerGet(tcw->tradeparam.result_sendPoke);
		tcw->demoparam.recvPoke = PPPPointerGet(tcw->tradeparam.result_recvPoke);
		tcw->demoparam.config = SaveData_GetConfig( fsys->savedata );
		tcw->demoparam.seqFlag = DEMO_TRADE_SEQ_FULL;
		switch( EVTIME_GetTimeZone(fsys) ){
		case TIMEZONE_MORNING:
		case TIMEZONE_NOON:
		default:
			tcw->demoparam.bgType = DEMO_TRADE_BGTYPE_MORNING;
			break;
		case TIMEZONE_EVENING:
			tcw->demoparam.bgType = DEMO_TRADE_BGTYPE_EVENING;
			break;
		case TIMEZONE_NIGHT:
		case TIMEZONE_MIDNIGHT:
			tcw->demoparam.bgType = DEMO_TRADE_BGTYPE_NIGHT;
			break;
		}
        if(CommStateIsWifiConnect()){
            tcw->demoparam.bgType = DEMO_TRADE_BGTYPE_WIFI;
        }
		EventCmd_CallSubProc(event, &TradeDemoProcData, &tcw->demoparam);
		tcw->seq = 5;
		break;
	case 5:
		// �i������
		{
			int item     = PokeParaGet( tcw->tradeparam.result_recvPoke, ID_PARA_item, NULL );
			int shinkano;
			int shinka_cond;
			
			//����POKEPARTY�͐����ł��Ȃ���������̂ŁANULL�w��i�i���`�F�b�N���őΏ��j by soga 2006.05.18
			if((shinkano=PokeShinkaCheck( NULL, tcw->tradeparam.result_recvPoke, TUUSHIN_SHINKA, item, &shinka_cond))!=0){
				sys_CreateHeap( HEAPID_BASE_APP, HEAPID_TRADELIST, 0x30000 );
				tcw->shinka_work = ShinkaInit(	NULL,//ppt
												tcw->tradeparam.result_recvPoke,
												shinkano,
												SaveData_GetConfig( fsys->savedata ),
												PokeStatus_ContestFlagGet( fsys->savedata ),
												SaveData_GetZukanWork( fsys->savedata ),
												SaveData_GetMyItem(fsys->savedata),//my_item
												SaveData_GetRecord(fsys->savedata),//record
												SaveData_GetPoketchData(fsys->savedata),//poketch_data
					 							shinka_cond,//shinka_cond
												SHINKA_STATUS_FLAG_SIO_MODE,
												HEAPID_TRADELIST);
				tcw->seq = 6;
				
			}else{
				tcw->seq = 7;
			}
		}
		break;
	case 6:
		// �i���I���҂�
		if(ShinkaEndCheck(tcw->shinka_work)){

			// �i����̃|�P�������Ă����ɔ��f������
			PokeCopyPPtoPP( tcw->tradeparam.result_recvPoke, 
							PokeParty_GetMemberPointer(tcw->tradeparam.myparty, tcw->tradeparam.exchangepos));

			// �i���f����n��
			ShinkaEnd( tcw->shinka_work );
			sys_DeleteHeap( HEAPID_TRADELIST );

			tcw->seq = 7;
			
		}
		break;
	
	case 7:
		// �����f���S�ďI���B�܂��������X�g��

		// �������X�g�ɍs�����񐔂𑝂₷�i�Q��ڈȍ~�̓Z�[�u������j
		tcw->tradeparam.times++;
		tcw->seq = 2;

		{
			// �X�R�A���Z
			RECORD *record = SaveData_GetRecord( fsys->savedata );
			RECORD_Score_Add( record, SCORE_ID_COMM_TRADE_POKE );
		}
	
		break;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void EventCmd_UnionTrade(GMEVENT_CONTROL * event)
{
	TRADE_CONTROL_WORK * tcw = sys_AllocMemory(HEAPID_EVENT, sizeof(TRADE_CONTROL_WORK));
	tcw->seq = 0;
	FieldEvent_Call(event, GMEVENT_UnionTradeList, tcw);
}





FS_EXTERN_OVERLAY(oekaki_board);

//============================================================================================
//============================================================================================
// �v���Z�X��`�f�[�^
const PROC_DATA OekakiProcData = {
	OekakiProc_Init,
	OekakiProc_Main,
	OekakiProc_End,
	FS_OVERLAY_ID(oekaki_board),
};

FS_EXTERN_OVERLAY(record_corner);
// �v���Z�X��`�f�[�^
const PROC_DATA RecordCornerProcData = {
	RecordCornerProc_Init,
	RecordCornerProc_Main,
	RecordCornerProc_End,
	FS_OVERLAY_ID(record_corner),
};

//==============================================================================
/**
 * $brief   ���G�����{�[�h�Ăяo��
 *
 * @param   fsys		
 *
 * @retval  BOOL		
 */
//==============================================================================
void OekakiBoard_SetProc( FIELDSYS_WORK *fsys )
{
	OEKAKI_PARAM *param = sys_AllocMemory( HEAPID_EVENT, sizeof(OEKAKI_PARAM));
	
	param->view   = fsys->union_view;
	param->fnote  = fsys->fnote;
	param->config = SaveData_GetConfig(fsys->savedata);
	
	GameSystem_StartSubProc(fsys,  &OekakiProcData, param );
}


//===========================================================================
//===========================================================================

//==============================================================================
/**
 * $brief   ���R�[�h�R�[�i�[�Ăяo��
 *
 * @param   fsys		
 *
 * @retval  BOOL		
 */
//==============================================================================
void * RecordCorner_SetProc( FIELDSYS_WORK *fsys )
{
	RECORD_INPUT_PARAM *param = sys_AllocMemory(HEAPID_WORLD, sizeof(RECORD_INPUT_PARAM));

	param->sv         = fsys->savedata;
	param->union_view = fsys->union_view;
	param->config	  = SaveData_GetConfig( fsys->savedata );
	param->record     = SaveData_GetRecord( fsys->savedata );
	param->fnote      = fsys->fnote;

	GameSystem_StartSubProc(fsys,  &RecordCornerProcData, param );

	return param;
}


//===========================================================================
//===========================================================================
FS_EXTERN_OVERLAY(wifi_note);
// �v���Z�X��`�f�[�^
const PROC_DATA WifiNoteEntryProcData = {
	WifiNoteEntryProc_Init,
	WifiNoteProc_Main,
	WifiNoteProc_End,
	FS_OVERLAY_ID(wifi_note),
};

//==============================================================================
/**
 * $brief   WIFI�Ƃ������蒠�o�^�Ăяo��
 *
 * @param   fsys		
 *
 * @retval  BOOL		
 */
//==============================================================================
void WifiNoteEntry_SetProc( FIELDSYS_WORK *fsys,SAVEDATA* pSaveData )
{
	GameSystem_StartSubProc(fsys,  &WifiNoteEntryProcData, pSaveData );
}

//===========================================================================
//===========================================================================
FS_EXTERN_OVERLAY(wifi_note);
// �v���Z�X��`�f�[�^
const PROC_DATA WifiNoteProcData = {
	WifiNoteProc_Init,
	WifiNoteProc_Main,
	WifiNoteProc_End,
	FS_OVERLAY_ID(wifi_note),
};

//==============================================================================
/**
 * $brief   WIFI�Ƃ������蒠�Ăяo��
 *
 * @param   fsys		
 *
 * @retval  BOOL		
 */
//==============================================================================
void WifiNote_SetProc( FIELDSYS_WORK *fsys,SAVEDATA* pSaveData )
{
	GameSystem_StartSubProc(fsys,  &WifiNoteProcData, pSaveData );
}


//===========================================================================
//
//		���O���͌Ăяo��
//
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	���O���͐���p���[�N
 */
//------------------------------------------------------------------
typedef struct{
	int seq;				///<����V�[�P���X���[�N
	int pos;				///<�ΏۂƂȂ�|�P�����̈ʒu
	u16* ret_work;			///<���ʂ�Ԃ����߂�u16�̃��[�N�ւ̃|�C���^
	NAMEIN_PARAM * namein;	///<���O���̓��[�N�ւ̃|�C���^
	STRBUF * org_name_buf;	///<���̖��O��ێ����邽��STRBUF�ւ̃|�C���^
}NAMEIN_EVENT_WORK;

static void namein_str_set(GMEVENT_CONTROL * event);

//------------------------------------------------------------------
/**
 * @brief
 */
//------------------------------------------------------------------
static BOOL GMEVENT_Sub_NameIn(GMEVENT_CONTROL * event)
{
	int len;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	NAMEIN_EVENT_WORK * new = FieldEvent_GetSpecialWork(event);

	switch (new->seq) {
	case 0:
		EventCmd_FinishFieldMap(event);
		new->seq ++;
		break;
	case 1:
		EventCmd_CallSubProc(event, &NameInProcData, new->namein);
		new->seq ++;
		break;
	case 2:
		EventCmd_StartFieldMap(event);
		new->seq ++;
		break;
	case 3:
		if (new->namein->mode == NAMEIN_POKEMON) {
			if (STRBUF_Compare(new->namein->strbuf, new->org_name_buf) == 0) {
				//�|�P�������[�h�ŁA�Ƃ��Ă�����������Ɠ������̂���͂����ꍇ
				//�L�����Z�������ɂ���
				new->namein->cancel = 1;
			}
		} else if (new->namein->mode == NAMEIN_RANDOMGROUP) {
			const STRCODE * name = STRBUF_GetStringCodePointer(new->namein->strbuf);
			RANDOM_GROUP * rg = SaveData_GetRandomGroup(fsys->savedata);
			if (RandomGroup_SameGroupNameCheck(rg, name)) {
				//�O���[�v�����͂ŁA�Ƃ��Ă�����������Ɠ������̂���͂����ꍇ
				//�����I�Ƃ����R�[�h��Ԃ�
				new->namein->cancel = 2;
			}
		}

		if (new->namein->cancel == 0 ) {
			namein_str_set(event);						//���͂���������ŏ㏑��
		}

		if( new->ret_work != NULL ){
			*new->ret_work = new->namein->cancel;		//���ʂ����[�N�ɑ��
		}
		
		NameIn_ParamDelete(new->namein);				// ���O���̓��[�N�����
		STRBUF_Delete(new->org_name_buf);
		sys_FreeMemoryEz(new);
		return TRUE;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief
 */
//------------------------------------------------------------------
static void namein_str_set(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	NAMEIN_EVENT_WORK * new = FieldEvent_GetSpecialWork(event);

	switch( new->namein->mode ){

	case NAMEIN_MYNAME:
		{
			MYSTATUS * my = SaveData_GetMyStatus(fsys->savedata);
			MyStatus_SetMyName(my, new->namein->str);
		}
		break;
	case NAMEIN_POKEMON:
		{
			POKEMON_PARAM * poke;
			int				flag;

			poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), new->pos);
			PokeParaPut( poke, ID_PARA_nickname_code_flag, (u8 *)&new->namein->str );
			//flag=1;
			//PokeParaPut( poke, ID_PARA_nickname_flag, (u8 *)&flag );
		}
		break;
	case NAMEIN_RANDOMGROUP:
		{
			RANDOM_GROUP * rg = SaveData_GetRandomGroup(fsys->savedata);
			RandomGroup_SetName(rg, RANDOMGROUP_MINE, RANDOMGROUP_NAME_GROUP, new->namein->strbuf);
		}
		break;
	case NAMEIN_STONE:	//r224�Δ�
		{
			MISC * misc = SaveData_GetMisc(fsys->savedata);
			MISC_SetMonumentName(misc,new->namein->strbuf);
		}
		break;
	//case NAMEIN_BOX:
		//���Ή�
		break;
	};

	return;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F���O���͌Ăяo��
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	mode		���̓��[�h(application/namein.h�Q��)
 * @param	info		�j�E���A�|�P�����̊J��NO�Ȃ�
 * @param	wordmax		���͕����ő吔
 * @param	pos			�莝���̉��Ԗڂ�(�K�v�Ȃ��Ƃ���0)
 * @param	str			���O���͉�ʂŕ\������镶����(�����\���������Ȃ�����NULL)
 * @param	ret_work	���͕������O�����B�������͍ŏ��Ɠ����������ꍇ�̃t���O���擾���郏�[�N(NULL)
 *
 * �t�B�[���h�v���Z�X�I�������O���́��t�B�[���h�v���Z�X�ĊJ���s���B
 *
 * ���[�h��NAMEIN_POKEMON(�|�P������)�ANAMEIN_BOX(�{�b�N�X��)�ɂ������́A
 * ���͂��ꂽ������ŏ㏑�����鏈���́A���쐬�ł��B(namein_str_set)
 */
//------------------------------------------------------------------
void EventCmd_NameIn(GMEVENT_CONTROL * event, int mode, int info, int wordmax, int pos, const STRCODE* str, u16* ret_work)
{
	POKEMON_PARAM * poke;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	NAMEIN_EVENT_WORK * param = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(NAMEIN_EVENT_WORK));

	param->seq = 0;
	param->pos = pos;
	param->ret_work = ret_work;
	param->namein = NameIn_ParamAllocMake(HEAPID_WORLD, mode, info, wordmax, SaveData_GetConfig(fsys->savedata));
	param->org_name_buf = STRBUF_Create(BUFLEN_POKEMON_NAME, HEAPID_WORLD);

	switch( mode ) {
	case NAMEIN_POKEMON:
		//�|�P�������[�h��������
		poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), param->pos );
		param->namein->sex  = PokeParaGet( poke, ID_PARA_sex, NULL );
		param->namein->form = PokeParaGet( poke, ID_PARA_form_no, NULL );
		if (str != NULL) {
			//�|�P�������[�h�ŕ������n����Ă���ꍇ�͔�r�p�ɕۑ����Ă���
			STRBUF_SetStringCode( param->org_name_buf, str );
		}
		break;
	case NAMEIN_RANDOMGROUP:
		//�����_���O���[�v���[�h���������r�p�ɕ����������Ă���
		STRBUF_SetStringCode( param->org_name_buf, str );
		break;
	default:
		if( str != NULL ){
		//�|�P�������[�h�ȊO�ŁA�������n����Ă���΃f�t�H���g�Ƃ��Đݒ肷��
			STRBUF_SetStringCode( param->namein->strbuf, str );
		}
		break;
	}

	FieldEvent_Call( event, GMEVENT_Sub_NameIn, param );
}

//------------------------------------------------------------------
//	�g���[�i�[�J�[�h�֘A
//------------------------------------------------------------------
void FieldTrCard_SetProc( FIELDSYS_WORK * fsys, TR_CARD_DATA *tcd )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(trainer_card);

	// �v���Z�X��`�f�[�^
	static const PROC_DATA TrCardProcData = {
		TrCardProc_Init,
		TrCardProc_Main,
		TrCardProc_End,
		FS_OVERLAY_ID(trainer_card),
	};
	
	GameSystem_StartSubProc( fsys, &TrCardProcData, tcd );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄv���b�N�Z�b�g
 *
 *	@param	fsys		�t�B�[���h���[�N
 *	@param	p_rearent	�}�ӂɕK�v�ȃf�[�^	(ZKN_PEARENT_DATA)
 *
 *	@retval		TRUE	����
 *	@retval		FALSE	���s
 */
//-----------------------------------------------------------------------------
BOOL FieldZukan_SetProc( FIELDSYS_WORK * fsys, void* p_pearent )
{

	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(ol_zukan);

	// �}�Ӄv���b�N�f�[�^
	static const PROC_DATA ZKN_SYS_Proc = {	
		ZKN_ProcInit,
		ZKN_ProcMain,
		ZKN_ProcEnd,
		FS_OVERLAY_ID(ol_zukan),
	};



	GameSystem_StartSubProc(fsys,  &ZKN_SYS_Proc, p_pearent );
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�n�|�P�����I���v���b�N�Z�b�g
 *
 *	@param	fsys		�t�B�[���h���[�N
 *	@param	p_rearent	�J�n�|�P�����I���ɕK�v�ȃf�[�^
 *
 *	@retval		TRUE	����
 *	@retval		FALSE	���s
 */
//-----------------------------------------------------------------------------
void Field_EVPokeSelect_SetProc( FIELDSYS_WORK * fsys, EV_POKESELECT_PEARENT_DATA* p_pearent )
{

	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(ev_pokeselect);

	// �}�Ӄv���b�N�f�[�^
	static const PROC_DATA EV_PokeSelect_Proc = {	
		EV_PokeSelect_ProcInit,
		EV_PokeSelect_ProcMain,
		EV_PokeSelect_ProcEnd,
		FS_OVERLAY_ID(ev_pokeselect)
	};

	GameSystem_StartSubProc(fsys,  &EV_PokeSelect_Proc, p_pearent );
}


//--------------------------------------------------------------
/**
 * @brief	�{�[���J�X�^�}�C�Y�Ăяo��
 *
 * @param	fsys	
 * @param	buff	
 *
 * @retval	BOOL	TRUE = OK
 *
 */
//--------------------------------------------------------------
BOOL Field_CustomBall_SetProc( FIELDSYS_WORK * fsys, void* buff )
{
	GameSystem_StartSubProc(fsys, &CustomBallProcData, buff );

	return TRUE;
}


//============================================================================================
//============================================================================================

//==============================================================================
/**
 * $brief   �����T�C���쐬��ʌĂяo��
 *
 * @param   fsys		
 *
 * @retval  none		
 */
//==============================================================================
void Field_MySign_SetProc( FIELDSYS_WORK *fsys )
{
	TR_CARD_SV_PTR trcard = TRCSave_GetSaveDataPtr(fsys->savedata);

	FS_EXTERN_OVERLAY(mysign);

	// �v���Z�X��`�f�[�^
	const PROC_DATA MySignProcData = {
		MySignProc_Init,
		MySignProc_Main,
		MySignProc_End,
		FS_OVERLAY_ID(mysign),
	};
		
	GameSystem_StartSubProc(fsys,  &MySignProcData, fsys->savedata );
}

//==============================================================================
/**
 * $brief   ���E������ʂ��Ăяo��
 *
 * @param   fsys		
 *
 * @retval  none		
 */
//==============================================================================
void Field_WorldTrade_SetProc( FIELDSYS_WORK *fsys, int connect )
{

	WORLDTRADE_PARAM *param;
	FS_EXTERN_OVERLAY(worldtrade);


	// �v���Z�X��`�f�[�^
	const PROC_DATA WorldTradeProcData = {
		WorldTradeProc_Init,
		WorldTradeProc_Main,
		WorldTradeProc_End,
		FS_OVERLAY_ID(worldtrade),
	};

	param = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(WORLDTRADE_PARAM));
	param->worldtrade_data = SaveData_GetWorldTradeData(fsys->savedata);
	param->systemdata      = SaveData_GetSystemData(fsys->savedata);
	param->myparty  	   = SaveData_Get(fsys->savedata,GMDATA_ID_TEMOTI_POKE);
	param->mybox           = SaveData_GetBoxData(fsys->savedata);
	param->zukanwork       = SaveData_GetZukanWork(fsys->savedata);
	param->wifilist        = SaveData_GetWifiListData(fsys->savedata);
	param->wifihistory     = SaveData_GetWifiHistory(fsys->savedata);
	param->mystatus        = SaveData_GetMyStatus(fsys->savedata);
	param->config          = SaveData_GetConfig(fsys->savedata);
	param->record          = SaveData_GetRecord(fsys->savedata);
	param->fnote		   = fsys->fnote;
	param->contestflag     = PokeStatus_ContestFlagGet( fsys->savedata );
	param->savedata        = fsys->savedata;
	param->zukanmode	   = PMNumber_GetMode(fsys->savedata);
	param->profileId       = mydwc_getMyGSID(param->wifilist);
	param->myitem		   = SaveData_GetMyItem(fsys->savedata);
	param->connect		   = connect;

	GameSystem_StartSubProc(fsys,  &WorldTradeProcData, param );
}


//==============================================================================
/**
 * $brief   WIFI�o�g���^���[�ڑ���ʂ��Ăяo��
 *
 * @param   fsys		
 *
 * @retval  none		
 */
//==============================================================================
void* Field_WifiBattleTowerConnect_SetProc( FIELDSYS_WORK *fsys, int mode, int connect )
{


	WBTOWER_PARAM *param;
	FS_EXTERN_OVERLAY(dpw_tower);

	// �v���Z�X��`�f�[�^
	const PROC_DATA WBTowerProcData = {
		WBTowerProc_Init,
		WBTowerProc_Main,
		WBTowerProc_End,
		FS_OVERLAY_ID(dpw_tower),
	};
	
	param = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(WBTOWER_PARAM));

	param->btowerscore   = SaveData_GetTowerScoreData(fsys->savedata);
	param->wifitowerdata = SaveData_GetTowerWifiData(fsys->savedata);
	param->systemdata    = SaveData_GetSystemData(fsys->savedata);
	param->config        = SaveData_GetConfig(fsys->savedata);
	param->MyUserData    = WifiList_GetMyUserInfo( SaveData_GetWifiListData(fsys->savedata) );
	param->savedata      = fsys->savedata;
	param->profileId     = mydwc_getMyGSID(SaveData_GetWifiListData(fsys->savedata));
	param->mode          = mode;	// btower.h�Q��
	param->connect       = connect;

	GameSystem_StartSubProc(fsys,  &WBTowerProcData, param );

	return (void*)param;
} 

//============================================================================================
//
//
//		WiFi�n���V�\��
//
//
//============================================================================================
#include "application/wifi_earth.h"

FS_EXTERN_OVERLAY(wifiearth);
//-----------------------------------------------------------------------------
/**
 * @brief	WiFi�n���V�pPROC��`�f�[�^
 */
//-----------------------------------------------------------------------------
static const PROC_DATA Earth_Demo_proc_data = {
	Earth_Demo_Init,
	Earth_Demo_Main,
	Earth_Demo_Exit,
	FS_OVERLAY_ID(wifiearth),
};

//-----------------------------------------------------------------------------
/**
 * @brief	WiFi�n���V��ʌĂяo��
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
void Field_WifiEarth_SetProc(FIELDSYS_WORK * fsys)
{
	GameSystem_StartSubProc(fsys, &Earth_Demo_proc_data, fsys->savedata);
}


//==============================================================================================
//
// �a������f���Ăяo��
//
//==============================================================================================
#include  "demo\demo_dendou.h"

void Field_DendouDemo_SetProc( FIELDSYS_WORK * fsys, DEMO_DENDOU_PARAM* param )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(demo_dendou);

	// �v���Z�X��`�f�[�^
	static const PROC_DATA proc_data = {
		DemoDendouPROC_Init,
		DemoDendouPROC_Main,
		DemoDendouPROC_Quit,
		FS_OVERLAY_ID(demo_dendou),
	};

	GameSystem_StartSubProc(fsys,  &proc_data, param );
}


//==============================================================================================
//
//		�a������p�\�R�����
//
//==============================================================================================
FS_EXTERN_OVERLAY(dendou_pc);

#include "savedata\dendou_data.h"
#include "application\dendou_pc.h"

void * Field_DendouPC_Call( FIELDSYS_WORK* fsys )
{
	// �v���Z�X��`�f�[�^
	static const PROC_DATA proc_data = {
		DendouPc_PROC_Init,
		DendouPc_PROC_Main,
		DendouPc_PROC_Quit,
		FS_OVERLAY_ID(dendou_pc),
	};

	DENDOU_SAVEDATA*  dd;
	LOAD_RESULT result;

	dd = SaveData_Extra_LoadDendouData(fsys->savedata, HEAPID_WORLD, &result);
	if (result == LOAD_RESULT_NG) {
		sys_FreeMemoryEz(dd);
		return NULL;
	} else {
		GameSystem_StartSubProc(fsys, &proc_data, dd);
		return dd;
	}
}

//==============================================================================================
//
// �G���f�B���O�f���Ăяo��
//
//==============================================================================================
void Field_EndingDemo_SetProc( FIELDSYS_WORK * fsys, ENDING_PROC_PARAM* param )
{
	FS_EXTERN_OVERLAY(demo_ending);

	// �v���Z�X��`�f�[�^
	static const PROC_DATA proc_data = {
		EndingDemoProc_Init,
		EndingDemoProc_Main,
		EndingDemoProc_Quit,
		FS_OVERLAY_ID(demo_ending),
	};

	GameSystem_StartSubProc(fsys,  &proc_data, param );
}


//==============================================================================================
//
//	�Z�����E�v���o��
//
//==============================================================================================
void WazaOshie_ProcSet( FIELDSYS_WORK * fsys , WAZAOSHIE_DATA * wk )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(waza_oshie);

	const PROC_DATA ProcData = {
		WazaOshieProc_Init,
		WazaOshieProc_Main,
		WazaOshieProc_End,
		FS_OVERLAY_ID(waza_oshie)
	};

	GameSystem_StartSubProc( fsys, &ProcData, wk );
}

//==============================================================================================
//
//	�D�f��
//
//==============================================================================================
void ShipDemo_ProcSet( FIELDSYS_WORK * fsys , void * wk )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(ship_demo);	
	const PROC_DATA ProcData = {
		ShipDemoProc_Init,
		ShipDemoProc_Main,
		ShipDemoProc_End,
		FS_OVERLAY_ID(ship_demo)
	};

	GameSystem_StartSubProc( fsys, &ProcData, wk );
}

//==============================================================================================
//
//	�^�}�S���܂��f��
//
//==============================================================================================
#include "../demo/egg/egg.h"	//EGG_CALL_PARAM	EventCmd_EGGProc
#include "sodateya.h"			//SodateyaSearchHatchingEgg
//-----------------------------------------------------------------------------
/**
 * @brief	�^�}�S�Y�܂��f��
 */
//-----------------------------------------------------------------------------
void Field_EggDemo_Call(FIELDSYS_WORK * fsys)
{
	EGG_CALL_PARAM ecp;
	POKEPARTY * party = SaveData_GetTemotiPokemon(fsys->savedata);
	POKEMON_PARAM * pp = SodateyaSearchHatchingEgg(party);

	GF_ASSERT(pp != NULL);
	TVTOPIC_Entry_Watch_HatchEgg(fsys, pp);		//�e���r�g�s�b�N����
	ecp.pp   = pp;
	ecp.cfg  = SaveData_GetConfig(fsys->savedata);
	ecp.my	 = SaveData_GetMyStatus(fsys->savedata);
	ecp.bgmno= Snd_FieldBgmNoGet( fsys,fsys->location->zone_id );
	
	EventCmd_EGGProc(fsys->event, &ecp);
}

//==============================================================================================
//
//	�X���b�g
//
//==============================================================================================
#include "savedata/coin.h"
//----------------------------------------------------------------------------
/**
 *	@brief	�X���b�g�֐��Z�b�g
 *
 *	@param	fsys		�t�B�[���h���[�N
 *	@param	hard		��ݒ�
 *
 *	@retval		TRUE	����
 *	@retval		FALSE	���s
 */
//-----------------------------------------------------------------------------
BOOL FieldSlot_SetProc( FIELDSYS_WORK *fsys, SLOT_PARAM *slotparam )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(slot);
	
	//�X���b�g�v���Z�X�f�[�^
	static const PROC_DATA SlotProc = {	
		SlotProc_Init,
		SlotProc_Main,
		SlotProc_End,
		FS_OVERLAY_ID(slot),
	};
	
	GameSystem_StartSubProc(fsys,  &SlotProc, slotparam );
	return TRUE;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
typedef struct {
	int coin_work;
	s64 start_time;
	SLOT_PARAM slotparam;
}SLOT_CALL_WORK;

//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_SlotMachine(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENTWORK *ev = SaveData_GetEventWork(fsys->savedata);
	SLOT_CALL_WORK * scw = FieldEvent_GetSpecialWork(event);
	int *seq = FieldEvent_GetSeqWork(event);
	int	count;

	switch (*seq) {
	case 0:
		FieldSlot_SetProc(fsys, &scw->slotparam);
		(*seq) ++;
		break;
	case 1:
		if (FieldEvent_Cmd_WaitSubProcEnd(fsys) == FALSE) {
			COIN * coin = SaveData_GetMyCoin(fsys->savedata);
			s64 end_time = GF_RTC_GetDateTimeBySecond();
			TVTOPIC_Entry_Record_Slot(fsys, COIN_GetValue(coin), scw->coin_work,
					GF_RTC_GetPassTime(scw->start_time, end_time) / 60);
			COIN_Set(SaveData_GetMyCoin(fsys->savedata), scw->coin_work);

OS_Printf("rencyan[%d]\n",scw->slotparam.r_count);

			count = SysWork_RensyouCountGet(ev);

			if ( (scw->slotparam.r_count) > count) {
				SysWork_RensyouCountSet(ev, scw->slotparam.r_count);
			}
			sys_FreeMemoryEz(scw);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
static u8 get_slot_setting( SAVEDATA* sv, u8 id );

void EventCmd_SlotMachine(GMEVENT_CONTROL * event, int id)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	CONFIG * config = SaveData_GetConfig(fsys->savedata);
	SLOT_CALL_WORK * scw = sys_AllocMemory(HEAPID_EVENT, sizeof(SLOT_CALL_WORK));

	scw->slotparam.coin = &scw->coin_work;
	scw->coin_work = COIN_GetValue(SaveData_GetMyCoin(fsys->savedata));
	scw->start_time = GF_RTC_GetDateTimeBySecond();
	scw->slotparam.record = SaveData_GetRecord(fsys->savedata);
	scw->slotparam.r_count = 0;
	scw->slotparam.win_type = CONFIG_GetWindowType( config );
	
	scw->slotparam.hard = get_slot_setting( fsys->savedata, id);

	//�X���b�g�ŗV�񂾂�X�R�A���Z
	RECORD_Score_Add(SaveData_GetRecord(fsys->savedata), SCORE_ID_PLAY_SLOT);

	FieldEvent_Call(event, GMEVENT_SlotMachine, scw);
}

//------------------------------------------------------------------
/**
 * �X���b�g��̓�Փx���擾�i�����_���O���[�v�Őݒ�����L����j
 *
 * @param   sv		
 * @param   id		
 *
 * @retval  u8		
 */
//------------------------------------------------------------------
static u8 get_slot_setting( SAVEDATA* sv, u8 id )
{
	enum {
		SLOT_ID_MAX = 12,
	};
	static const u8 SettingTable[SLOT_ID_MAX] = {
		0, 5, 1, 1, 4, 4, 2, 2, 2, 3, 3, 3,
	};

	RANDOM_GROUP*  randGroup = SaveData_GetRandomGroup(sv);
	u32  seed;
	u8   setting[SLOT_ID_MAX];
	u8   i, j, p, tmp;

	seed = gf_get_seed();
	gf_srand( RandomGroup_GetDefaultRandom(randGroup) );

	MI_CpuCopy8( SettingTable, setting, sizeof(setting) );
	for(i=0; i<SLOT_ID_MAX; i++)
	{
		for(j=i+1; j<SLOT_ID_MAX; j++)
		{
			p = gf_rand() % SLOT_ID_MAX;
			tmp = setting[i];
			setting[i] = setting[p];
			setting[p] = tmp;
		}
	}
	gf_srand( seed );

	OS_TPrintf("rand=%d\n", RandomGroup_GetDefaultRandom(randGroup));
	OS_TPrintf("Slot ID = %d ", id);
	OS_TPrintf("setting = %d\n", setting[id]);

	return setting[id];
}

//==============================================================================================
//
//		�A�N�Z�T���[�V���b�v
//
//		���T�u�v���Z�X�ؑւ��s���킯�ł͂Ȃ����A�T�u�C�x���g�Ăяo���Ƃ���
//		�@���̃\�[�X�ɂ����Ă���
//
//==============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_AcceShop(GMEVENT_CONTROL * event)
{
	FIELD_ACCE_SHOP * fasw = FieldEvent_GetSpecialWork(event);
	if (FIELD_AcceShop_Main(fasw) == TRUE) {
		FIELD_AcceShop_Free(fasw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief
 */
//-----------------------------------------------------------------------------
void EventCmd_AcceShop(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FIELD_ACCE_SHOP * fasw = FIELD_AcceShop_Alloc(HEAPID_FIELD, fsys->savedata, fsys->bgl);
	FieldEvent_Call(event, GMEVENT_AcceShop, fasw);
}

//==============================================================================================
//
//	�\����
//
//==============================================================================================
//----------------------------------------------------------------------------
/**
 *	@brief	�\����Ăяo��
 *
 *	@param	fsys		�t�B�[���h���[�N
 *	@param	heapID		�q�[�v�h�c
 *	@param	type		SYOUJYOU_TYPE_SINOU:�V���I�E�R���v, SYOUJYOU_TYPE_ZENKOKU:�S���R���v
 *
 *	@retval	ini			�����p�����[�^�|�C���^
 */
//-----------------------------------------------------------------------------
#include "demo/syoujyou.h"
void* Syoujyou_SetProc( FIELDSYS_WORK * fsys, int heapID, int type )
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY( syoujyou );
	
	//�܏�v���Z�X�f�[�^
	static const PROC_DATA SyoujyouProc = {	
		Syoujyou_Init,
		Syoujyou_Main,
		Syoujyou_Exit,
		FS_OVERLAY_ID(syoujyou),
	};
	SYOUJYOU_INI* ini = sys_AllocMemory( heapID, sizeof( SYOUJYOU_INI ) );
	{
		ini->type		= type;
		ini->savedata	= fsys->savedata;
	}
	GameSystem_StartSubProc(fsys, &SyoujyouProc, ini );

	return ini;
}

