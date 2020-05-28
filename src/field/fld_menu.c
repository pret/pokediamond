//============================================================================================
/**
 * @file	fld_menu.c
 * @brief	�t�B�[���h���j���[����
 * @author	Hiroyuki Nakamura
 * @date	2004.11.05
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/bmp_menu.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/clact_tool.h"
#include "system/menu_gra.naix"
#include "system/wipe.h"
#include "poketool/pokeparty.h"
#include "poketool/poke_number.h"
#include "itemtool/item.h"
#include "application/bag.h"
#include "application/pokelist.h"
#include "application/p_status.h"
#include "application/trainer_card.h"
#include "application/nuts_tag.h"
#include "application/config_tool.h"
#include "application/mailtool.h"
#include "application/zukanlist/zkn_sys.h"
#include "application/townmap.h"
#include "application/nuts_tag.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_fieldmenu.h"
#include "savedata/mystatus.h"
#include "savedata/config.h"
#include "savedata/sp_ribbon.h"
#include "savedata/trainercard_data.h"
#include "battle/shinka.h"
#include "field/field.h"
#include "fld_bgm.h"
#include "fld_bmp.h"
#include "fieldmap.h"
#include "fieldsys.h"
#include "field/field_skill.h"
#include "field_skill_local.h"
#include "field_clact.h"
#include "field_flysky.h"
#include "ev_mapchange.h"
#include "ev_time.h"
#include "syswork.h"
#include "sysflag.h"
#include "tr_card_setup.h"
#include "report.h"
#include "situation_local.h"
#include "pokepark_sys.h"
#include "b_tower_ev.h"
#include "zonedata.h"

#include "communication/communication.h"	// �ȈՉ�b���������̂��߂ɕK�v
#include "communication/comm_state.h"
#include "comm_union_beacon.h"				// �ȈՉ�b���������̂��߂ɕK�v
#include "field/comm_union_view_common.h"

#include "script.h"
#include "../fielddata/script/common_scr_def.h"		//SCRID_REPORT
#include "../fielddata/script/safari_def.h"
#include "../fielddata/script/d10r0101_def.h"

#include "field/itemuse.h"

#define FLD_MENU_H_GLOBAL
#include "fld_menu.h"


//============================================================================================
//	�萔��`
//============================================================================================
enum {
	MENU_POS_ZUKAN = 0,
	MENU_POS_POKEMON,
	MENU_POS_BAG,
	MENU_POS_HERO,
	MENU_POS_REPORT,
	MENU_POS_CONFIG,
	MENU_POS_EXIT,
	MENU_POS_CHAT,
	MENU_POS_RETIRE,
};

// �Z�g�p
typedef struct {
	u16	poke;	// �|�P�����ʒu
	u16	waza;	// �Z
}SKILL_USE;

// ���[���쐬
typedef struct {
	u16	item;
	u8	pos;
	u8	mode;
}FM_MAIL_WORK;


#define	FLDMENU_CLA_CHR_RES_MAX		( 8 )	// �Z���A�N�^�[�̃L������
#define	FLDMENU_CLA_PAL_RES_MAX		( 1 )	// �Z���A�N�^�[�̃p���b�g��
#define	FLDMENU_CLA_CEL_RES_MAX		( 2 )	// �Z���A�N�^�[�̃Z����
#define	FLDMENU_CLA_ANM_RES_MAX		( 2 )	// �Z���A�N�^�[�̃Z���A�j����

// �Z���A�N�^�[�̃L����ID
enum {
	FLDMENU_CLA_CHR_H_ID_CURSOR	= 13528,	// �I���J�[�\��
	FLDMENU_CLA_CHR_H_ID_ICON,				// �A�C�R��
};
// �Z���A�N�^�[�̃p���b�gID
enum {
	FLDMENU_CLA_PAL_H_ID = 13528,			// �I���J�[�\�����A�C�R��
};
// �Z���A�N�^�[�̃Z��ID
enum {
	FLDMENU_CLA_CEL_H_ID_CURSOR	= 13528,	// �I���J�[�\��
	FLDMENU_CLA_CEL_H_ID_ICON,				// �A�C�R��
};
// �Z���A�N�^�[�̃Z���A�j��ID
enum {
	FLDMENU_CLA_ANM_H_ID_CURSOR	= 13528,	// �I���J�[�\��
	FLDMENU_CLA_ANM_H_ID_ICON,				// �A�C�R��
};

// �A�C�R��ID
enum {
	ICON_ZUKAN,		// �}�ӃA�C�R��
	ICON_POKEMON,	// �|�P�������X�g�A�C�R��
	ICON_BAG,		// �o�b�O�A�C�R��
	ICON_HERO,		// �g���[�i�[�J�[�h�A�C�R��
	ICON_REPORT,	// ���|�[�g�A�C�R��
	ICON_CONFIG,	// �ݒ�A�C�R��
	ICON_CLOSE,		// ����A�C�R��
	ICON_CHAT,		// �`���b�g
	ICON_RETIRE,	// ���^�C�A
	ICON_BAG_F,		// �o�b�O�i���j�@�� ��ԉ��ɒu������
};

// �Z���A�N�^�[�o�^�ꏊ
#define	CLA_SET_CURSOR	( 0 )	// �I���J�[�\��
#define	CLA_SET_ICON	( 1 )	// �A�C�R��

#define	CLA_CURSOR_PX	( 204 )		// �I���J�[�\���\��X���W
#define	CLA_CURSOR_PY	( 20 )		// �I���J�[�\���\��Y���W
#define	CLA_ICON_PX		( 174 )		// �A�C�R���\��X���W
#define	CLA_ICON_PY		( 20 )		// �A�C�R���\��Y���W
#define	CLA_ICON_SPC_Y	( 24 )		// �A�C�R����Y�X�y�[�X

// �A�C�R���A�j��ID
enum {
	ICON_ANM_STOP = 0,	// ��~
	ICON_ANM_CHANGE,	// �I�����ꂽ�u��
	ICON_ANM_SELECT,	// �I��
};

// �c��{�[���E�B���h�E
#define	BALL_NAME_PX		( 0 )		// �{�[�����\��X
#define	BALL_NAME_PY		( 0 )		// �{�[�����\��Y
#define	BALL_VAL_PX			( 0 )		// �{�[�����\��X
#define	BALL_VAL_PY			( 16 )		// �{�[�����\��Y
#define	BALL_VAL_MSG_SIZ	( 32 )		// �{�[�����W�J�������i�K���j


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static FLD_MENU * MenuWorkAllocSet(void);
static u32 FieldMenuParamSet( FIELDSYS_WORK * repw );
static u32 FieldMenuParamSetSafari( FIELDSYS_WORK * repw );
static u32 FieldMenuParamSetPokePark( FIELDSYS_WORK * repw );
static u32 FieldMenuParamSetBtlTowerSalon( FIELDSYS_WORK * repw );
static u32 FieldMenuParamSetUnion( FIELDSYS_WORK * repw );
static u32 FieldMenuParamSetVS( FIELDSYS_WORK * repw );

static void CellActSet( FLD_MENU * wk, u8 * list, u32 max, u8 sex );
static void CellActDelete( FLD_MENU * wk );
static void CellActAnm( FLD_MENU * wk );
static void CursorMove( CLACT_WORK_PTR cwp, u32 cur_pos );
static void IconAnmChange( CLACT_WORK_PTR cwp, u16 anm, u16 pal );
static void MoveIconAnmChg( FLD_MENU * wk, u16 old_pos, u16 new_pos );
static void SelectIconAnmCheck( CLACT_WORK_PTR cwp );

static BOOL GMEVENT_FieldMenu(GMEVENT_CONTROL * event);
static void FieldMenuSet( GMEVENT_CONTROL * event );
static BOOL FieldMenuSelect( GMEVENT_CONTROL * event );
static u32 FieldMenuListMake( FLD_MENU * wk, u8 * list );
static void FieldMenuListExit( FLD_MENU * wk );
static void FldMenu_UnionBeaconChg( FLD_MENU * wk, FIELDSYS_WORK *fsys );
static void FieldBallWinSet( GMEVENT_CONTROL * event );
static void FieldBallWinExit( GMEVENT_CONTROL * event );

static void FldMenu_AppCall( GMEVENT_CONTROL * event );
static void FldMenu_AppWait( GMEVENT_CONTROL * event );

static BOOL FldMenu_ZukanInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_ZukanCall( GMEVENT_CONTROL * event );
static BOOL FldMenu_ZukanEnd( GMEVENT_CONTROL * event );

static BOOL FldMenu_TrCardInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_TrCardCall( GMEVENT_CONTROL * event );
static BOOL FldMenu_TrCardEnd( GMEVENT_CONTROL * event );

static BOOL FldMenu_ConfigInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_ConfigCall( GMEVENT_CONTROL * event );
static BOOL FldMenu_ConfigEnd( GMEVENT_CONTROL * event );

static BOOL FldMenu_ChatInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_ChatCall( GMEVENT_CONTROL * event );
static BOOL FldMenu_ChatEnd( GMEVENT_CONTROL * event );

static BOOL FldMenu_PokeListInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_PokeListCall( GMEVENT_CONTROL * event );

static BOOL FldMenu_BagInit( GMEVENT_CONTROL * event );
static BOOL FldMenu_BagCall( GMEVENT_CONTROL * event );
static BOOL FldMenu_BagEnd( GMEVENT_CONTROL * event );

static BOOL FldMenu_ReportInit( GMEVENT_CONTROL * event );
static void FldMenu_ReportWait( GMEVENT_CONTROL * event );
static void FldMenu_ReportCall( GMEVENT_CONTROL * event );

static BOOL FldMenu_PokeStatusEnd( GMEVENT_CONTROL * event );

static void FldMenu_NutsTagCall( GMEVENT_CONTROL * event, u16 item );
static BOOL FldMenu_NutsTagEnd( GMEVENT_CONTROL * event );

BOOL FldMenu_SorawotobuEnd( GMEVENT_CONTROL * event );

static void FldMenu_ShinkaInit( GMEVENT_CONTROL * event );
static void FldMenu_ShinkaMain( GMEVENT_CONTROL * event );

static BOOL FldMenu_RetireInit( GMEVENT_CONTROL * event );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
static const u32 FldMenuData[][2] =
{
	{ msg_menu_00, (u32)FldMenu_ZukanInit },		// ������
	{ msg_menu_01, (u32)FldMenu_PokeListInit },		// �|�P����
	{ msg_menu_02, (u32)FldMenu_BagInit },			// �o�b�O
	{ msg_menu_03, (u32)FldMenu_TrCardInit },		// ��l��
	{ msg_menu_04, (u32)FldMenu_ReportInit },		// ���|�[�g
	{ msg_menu_05, (u32)FldMenu_ConfigInit },		// �����Ă�
	{ msg_menu_06, (u32)BMPMENU_CANCEL },			// �Ƃ���
	{ msg_menu_07, (u32)FldMenu_ChatInit },			// �`���b�g
	{ msg_menu_08, (u32)FldMenu_RetireInit },		// ���^�C�A
};

// �Z���A�N�^�[�f�[�^
static const TCATS_OBJECT_ADD_PARAM_S ActAddParam_S[] =
{
	{	// �J�[�\��
		CLA_CURSOR_PX, CLA_CURSOR_PY, 0,
		0, 1, 1, NNS_G2D_VRAM_TYPE_2DMAIN,
		{
			FLDMENU_CLA_CHR_H_ID_CURSOR, FLDMENU_CLA_PAL_H_ID,
			FLDMENU_CLA_CEL_H_ID_CURSOR, FLDMENU_CLA_ANM_H_ID_CURSOR, 0, 0,
		},
		0, 0
	},
	{	// �A�C�R���P
		CLA_ICON_PX, CLA_ICON_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{
			FLDMENU_CLA_CHR_H_ID_ICON, FLDMENU_CLA_PAL_H_ID,
			FLDMENU_CLA_CEL_H_ID_ICON, FLDMENU_CLA_ANM_H_ID_ICON, 0, 0,
		},
		0, 0
	},
};

// �|�P�������X�g�u��������v����Ă΂��o�b�O�̃f�[�^
static const u8 PokeList_ItemSetBagList[] = {
	BAG_POKE_NORMAL, BAG_POKE_DRUG, BAG_POKE_BALL, BAG_POKE_WAZA,
	BAG_POKE_NUTS, BAG_POKE_SEAL, BAG_POKE_BATTLE, BAG_POKE_EVENT, 0xff
};

// �ʏ�̃X�e�[�^�X��ʃy�[�W
const u8 PST_PageTbl_Normal[] = {
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

// �Z�o���p�X�e�[�^�X��ʃy�[�W
static const u8 PST_PageTbl_WazaSet[] = {
	PST_PAGE_B_SKILL,		// �u���������킴�v
	PST_PAGE_C_SKILL,		// �u�R���e�X�g�킴�v
	PST_PAGE_MAX
};


//============================================================================================
//	�Ăяo��
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h���j���[�N�������i�ʏ�j
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldMenuInit( FIELDSYS_WORK * repw )
{
	FLD_MENU * wk = MenuWorkAllocSet();

	if( SysFlag_SafariCheck( SaveData_GetEventWork(repw->savedata) ) == TRUE ){
		wk->ev_flg = FieldMenuParamSetSafari( repw );	// �T�t�@��
	}else if( SysFlag_PokeParkCheck( SaveData_GetEventWork(repw->savedata) ) == TRUE ){
		wk->ev_flg = FieldMenuParamSetPokePark( repw );	// �|�P�p�[�N
	}else if( BtlTower_IsSalon(repw) == TRUE ){
		wk->ev_flg = FieldMenuParamSetBtlTowerSalon( repw );	// �o�g���^���[�T����
	}else{
		wk->ev_flg = FieldMenuParamSet( repw );			// �ʏ탁�j���[
	}
	wk->union_flg = FALSE;

	if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
		Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
	}

	FieldEvent_Set(repw, GMEVENT_FieldMenu, wk);
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h���j���[�N�������i���j�I�����[���p�j
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldMenuInitUnion( FIELDSYS_WORK * repw )
{
	FLD_MENU * wk = MenuWorkAllocSet();

	wk->ev_flg    = FieldMenuParamSetUnion( repw );
	wk->union_flg = TRUE;

	if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
		Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
	}

	FieldEvent_Set(repw, GMEVENT_FieldMenu, wk);
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h���j���[�N�������i�ΐ핔���p�j
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldMenuInitVS( FIELDSYS_WORK * repw )
{
	FLD_MENU * wk = MenuWorkAllocSet();

	wk->ev_flg    = FieldMenuParamSetVS( repw );
	wk->union_flg = FALSE;

	if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
		Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
	}

	FieldEvent_Set(repw, GMEVENT_FieldMenu, wk);
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h���j���[�N�����荞�ݏ����i�ʏ�j
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	none
 *
 *	�ŔȂǂ̏����𒆒f���ČĂяo������
 */
//--------------------------------------------------------------------------------------------
void FieldMenuEvChg( FIELDSYS_WORK * repw )
{
	FLD_MENU * wk;
	
	// ���̃��[�N�����
	//sys_FreeMemoryEz( FieldEvent_GetSpecialWork(repw->event) );
	
	// ���j���[���[�N�쐬
	Snd_SePlay( SE_WIN_OPEN );
	wk = MenuWorkAllocSet();

	wk->union_flg = FALSE;

	if( SysFlag_SafariCheck( SaveData_GetEventWork(repw->savedata) ) == TRUE ){
		wk->ev_flg = FieldMenuParamSetSafari( repw );	// �T�t�@��
	}else if( SysFlag_PokeParkCheck( SaveData_GetEventWork(repw->savedata) ) == TRUE ){
		wk->ev_flg = FieldMenuParamSetPokePark( repw );	// �|�P�p�[�N
	}else if( BtlTower_IsSalon(repw) == TRUE ){
		wk->ev_flg = FieldMenuParamSetBtlTowerSalon( repw );	// �o�g���^���[�T����
	}else if( repw->MapMode == MAP_MODE_COLOSSEUM) {
		wk->ev_flg = FieldMenuParamSetVS( repw );		// �ΐ핔��
	}else if( repw->MapMode == MAP_MODE_UNION ) {
		wk->ev_flg = FieldMenuParamSetUnion( repw );	// ���j�I��
		wk->union_flg = TRUE;
	}else{
		wk->ev_flg = FieldMenuParamSet( repw );			// �ʏ탁�j���[
	}

	FieldEvent_Change( repw->event, GMEVENT_FieldMenu, wk );
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h���j���[�N�����荞�ݏ����i���j�I�����[���p�j
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	none
 *
 *	�ŔȂǂ̏����𒆒f���ČĂяo������
 */
//--------------------------------------------------------------------------------------------
void FieldMenuEvChgUnion( FIELDSYS_WORK * repw )
{
	FLD_MENU * wk;
	
	// ���̃��[�N�����
	//sys_FreeMemoryEz( FieldEvent_GetSpecialWork(repw->event) );
	
	// ���j���[���[�N�쐬
	Snd_SePlay( SE_WIN_OPEN );
	wk = MenuWorkAllocSet();
	wk->ev_flg    = FieldMenuParamSetUnion( repw );
	wk->union_flg = TRUE;
	FieldEvent_Change( repw->event, GMEVENT_FieldMenu, wk );
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h���j���[���[�N�m��
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static FLD_MENU * MenuWorkAllocSet(void)
{
	FLD_MENU * wk;

	wk = sys_AllocMemory( HEAPID_WORLD, sizeof(FLD_MENU) );
	wk->seq = FLD_MENU_SEQ_INIT;
	wk->pos = 0;
	wk->app_wk = NULL;

	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �\�����ڐ���p�����[�^�쐬�i�ʏ�j
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	�\�����ڐ���p�����[�^
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSet( FIELDSYS_WORK * repw )
{
	u32	prm = 0;

	if( ZukanWork_GetZukanGetFlag(SaveData_GetZukanWork(repw->savedata)) == FALSE ){
		prm |= FLD_MENU_VANISH_ZUKAN;
	}
	if( SysWork_FirstPokeNoGet(SaveData_GetEventWork(repw->savedata)) == 0 ){
		prm |= FLD_MENU_VANISH_PLIST;
	}
	if( SysFlag_BagCheck(SaveData_GetEventWork(repw->savedata)) == 0 ){
		prm |= FLD_MENU_VANISH_BAG;
	}
	// ���R�������ǂ����̃`�F�b�N
	if( ZoneData_IsNaturalPark( repw->location->zone_id ) == TRUE ){
		prm |= FLD_MENU_VANISH_PLIST;
		prm |= FLD_MENU_VANISH_BAG;
	}
	prm |= FLD_MENU_VANISH_CHAT;
	prm |= FLD_MENU_VANISH_RETIRE;

	return prm;
}

//--------------------------------------------------------------------------------------------
/**
 * �\�����ڐ���p�����[�^�쐬�i�T�t�@���j
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	�\�����ڐ���p�����[�^
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSetSafari( FIELDSYS_WORK * repw )
{
	return (FLD_MENU_VANISH_REPORT|FLD_MENU_VANISH_CHAT);
}

//--------------------------------------------------------------------------------------------
/**
 * �\�����ڐ���p�����[�^�쐬�i�|�P�p�[�N�j
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	�\�����ڐ���p�����[�^
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSetPokePark( FIELDSYS_WORK * repw )
{
	return (FLD_MENU_VANISH_REPORT|FLD_MENU_VANISH_CHAT|FLD_MENU_VANISH_BAG);
}

//--------------------------------------------------------------------------------------------
/**
 * �\�����ڐ���p�����[�^�쐬�i�o�g���^���[�T�����j
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	�\�����ڐ���p�����[�^
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSetBtlTowerSalon( FIELDSYS_WORK * repw )
{
	return (FLD_MENU_VANISH_ZUKAN|FLD_MENU_VANISH_BAG|FLD_MENU_VANISH_REPORT|FLD_MENU_VANISH_CHAT|FLD_MENU_VANISH_RETIRE);
}

//--------------------------------------------------------------------------------------------
/**
 * �\�����ڐ���p�����[�^�쐬�i���j�I���j
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	�\�����ڐ���p�����[�^
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSetUnion( FIELDSYS_WORK * repw )
{
	return (FLD_MENU_VANISH_REPORT|FLD_MENU_VANISH_RETIRE);
}

//--------------------------------------------------------------------------------------------
/**
 * �\�����ڐ���p�����[�^�쐬�i�ΐ핔���j
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	�\�����ڐ���p�����[�^
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuParamSetVS( FIELDSYS_WORK * repw )
{
	return (FLD_MENU_VANISH_REPORT|FLD_MENU_VANISH_ZUKAN|FLD_MENU_VANISH_CHAT|FLD_MENU_VANISH_RETIRE);
}


//============================================================================================
//	����
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�C�x���g�F���j���[����
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 * @retval	TRUE	�C�x���g�I��
 * @retval	FALSE	�C�x���g�p��
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_FieldMenu(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork(event);
	wk = FieldEvent_GetSpecialWork(event);

	switch( wk->seq ){
	case FLD_MENU_SEQ_INIT:		// ������
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		ItemUse_CheckWorkMake( fsys, &wk->item_check );
		FieldSkill_CheckWorkMake( fsys, &wk->skill_check );
		FieldMenuSet( event );
		FieldBallWinSet( event );
		wk->seq = FLD_MENU_SEQ_SELECT;
		break;

	case FLD_MENU_SEQ_SELECT:	// ���j���[�I��
		if( FieldMenuSelect( event ) == FALSE ){
			return FALSE;
		}
		break;

	case FLD_MENU_SEQ_APP_CALL:	// �A�v���Ăяo��
		FldMenu_AppCall( event );
		break;

	case FLD_MENU_SEQ_APP_WAIT:	// �A�v���I���҂�
		FldMenu_AppWait( event );
		break;

	case FLD_MENU_SEQ_REPORT_CALL:
		FldMenu_ReportCall( event );
		break;
	case FLD_MENU_SEQ_REPORT_WAIT:
		FldMenu_ReportWait( event );
		break;

	case FLD_MENU_SEQ_SHINKA_INIT:	// �i����ʌĂяo��
		FldMenu_ShinkaInit( event );
		break;

	case FLD_MENU_SEQ_SHINKA_MAIN:	// �i����ʑ҂�
		FldMenu_ShinkaMain( event );
		break;

	case FLD_MENU_SEQ_AGAIN:	// ������������������
		//�t�B�[���h�}�b�v�v���Z�X�J�n�҂�
		if (FieldEvent_Cmd_WaitMapProcStart(fsys)) {
			FieldOBJSys_MovePauseAll( fsys->fldobjsys );
			FieldMenuSet( event );
			FieldBallWinSet( event );
			//�u���b�N�C�����N�G�X�g
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = FLD_MENU_SEQ_WAIT_BLACK_IN;
		}
		break;

	case FLD_MENU_SEQ_BLACK_IN_END:
		//�t�B�[���h�}�b�v�v���Z�X�J�n�҂�
		if(FieldEvent_Cmd_WaitMapProcStart(fsys)) {
			//�u���b�N�C�����N�G�X�g
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = FLD_MENU_SEQ_BLACK_IN_END_WAIT;
		}
		break;

	case FLD_MENU_SEQ_BLACK_IN_END_WAIT:
		if( WIPE_SYS_EndCheck() ){
			FldMenu_UnionBeaconChg( wk, fsys );
			sys_FreeMemoryEz( wk );
			FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
			return TRUE;
		}
		break;

	case FLD_MENU_SEQ_BLACK_IN_EVCHG:
		//�t�B�[���h�}�b�v�v���Z�X�J�n�҂�
		if(FieldEvent_Cmd_WaitMapProcStart(fsys)) {
			FieldOBJSys_MovePauseAll( fsys->fldobjsys );
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = FLD_MENU_SEQ_BLACK_IN_EVCHG_WAIT;
		}
		break;

	case FLD_MENU_SEQ_BLACK_IN_EVCHG_WAIT:
		if( WIPE_SYS_EndCheck() ){
//			wk->app_func(event);
			FieldEvent_Change( event, wk->app_func, wk->app_wk );
			sys_FreeMemoryEz( wk );
//			return TRUE;
		}
		break;

	case FLD_MENU_SEQ_END_NOMENU:
		//���j���[�����łɕ��Ă����ԂŏI��
		sys_FreeMemoryEz( wk );
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		return TRUE;

	case FLD_MENU_SEQ_END:
		FldMenu_UnionBeaconChg( wk, fsys );
		FieldMenuListExit( wk );
		BmpMenuWinClear( &wk->win, WINDOW_TRANS_OFF );
		GF_BGL_BmpWinDel( &wk->win );
		FieldBallWinExit( event );
		GF_BGL_LoadScreenV_Req( fsys->bgl, FLD_MBGFRM_FONT );
		sys_FreeMemoryEz( wk );
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		return TRUE;

	case FLD_MENU_SEQ_WAIT_BLACK_IN:
		if ( WIPE_SYS_EndCheck() ){
			wk->seq = FLD_MENU_SEQ_SELECT;
		}
		break;
	}

	if( wk->mw != NULL ){
		CellActAnm( wk );
		CLACT_Draw( wk->fcat.cas );
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �t�B�[���h���j���[�쐬
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FieldMenuSet( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	MSGDATA_MANAGER * man;
	BMPMENU_HEADER	hed;
	u32	i, max;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	max = FieldMenuListMake( wk, wk->list );

	GF_BGL_BmpWinAdd(
		fsys->bgl, &wk->win, FLD_MBGFRM_FONT, FLD_MENU_WIN_PX, FLD_MENU_WIN_PY,
		FLD_MENU_WIN_SX, max*3, FLD_MSG_WIN_PAL, FLD_MENU_WIN_CGX );

	MenuWinGraphicSet(
		fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, MENU_TYPE_FIELD, HEAPID_WORLD );
	BmpMenuWinWrite( &wk->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );

	man = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_fieldmenu_dat, HEAPID_WORLD );
	wk->ld = BMP_MENULIST_Create( max, HEAPID_WORLD );
	wk->pos = 0;
	for( i=0; i<max; i++ ){
		if( wk->list[i] == MENU_POS_HERO ){
			WORDSET * wset;
			STRBUF * expb;
			STRBUF * strb;
			
			wset = WORDSET_Create( HEAPID_WORLD );
			expb = STRBUF_Create( BUFLEN_PERSON_NAME, HEAPID_WORLD );
			strb = MSGMAN_AllocString( man, FldMenuData[wk->list[i]][0] );

			WORDSET_RegisterPlayerName( wset, 0, SaveData_GetMyStatus(fsys->savedata) );
			WORDSET_ExpandStr( wset, expb, strb );

			BMP_MENULIST_AddString( wk->ld, expb, wk->list[i] );

			STRBUF_Delete( strb );
			STRBUF_Delete( expb );
			WORDSET_Delete( wset );
		}else{
			BMP_MENULIST_AddArchiveString(
				wk->ld, man, FldMenuData[wk->list[i]][0], wk->list[i] );
		}
		if( fsys->startmenu_pos == wk->list[i] ){
			wk->pos = i;
		}
	}
	fsys->startmenu_pos = wk->list[wk->pos];
	MSGMAN_Delete( man );

	hed.menu  = wk->ld;
	hed.win   = &wk->win;
	hed.font  = FONT_TALK;
	hed.x_max = 1;
	hed.y_max = max;
	hed.line_spc = 8;
	hed.c_disp_f = 1;
	if( max >= 4 ){
		hed.loop_f = 1;
	}else{
		hed.loop_f = 0;
	}

	wk->mw = BmpMenuAdd_NoTrans(
				&hed, 28, 4, wk->pos, HEAPID_WORLD, PAD_BUTTON_CANCEL|PAD_BUTTON_X );

	GF_BGL_BmpWinOnVReq( &wk->win );

	CellActSet( wk, wk->list, max, MyStatus_GetMySex(SaveData_GetMyStatus(fsys->savedata)) );
}

//--------------------------------------------------------------------------------------------
/**
 * ���j���[���X�g�쐬
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 * @param	list	���X�g�쐬�ꏊ
 *
 * @return	���ڐ�
 */
//--------------------------------------------------------------------------------------------
static u32 FieldMenuListMake( FLD_MENU * wk, u8 * list )
{
	u32	max = 0;

	// ���^�C�A
	if( ( wk->ev_flg & FLD_MENU_VANISH_RETIRE ) == 0 ){
		list[max] = MENU_POS_RETIRE;
		max++;
	}
	// �`���b�g
	if( ( wk->ev_flg & FLD_MENU_VANISH_CHAT ) == 0 ){
		list[max] = MENU_POS_CHAT;
		max++;
	}
	// �}��
	if( ( wk->ev_flg & FLD_MENU_VANISH_ZUKAN ) == 0 ){
		list[max] = MENU_POS_ZUKAN;
		max++;
	}
	// �|�P�������X�g
	if( ( wk->ev_flg & FLD_MENU_VANISH_PLIST ) == 0 ){
		list[max] = MENU_POS_POKEMON;
		max++;
	}
	// �o�b�O
	if( ( wk->ev_flg & FLD_MENU_VANISH_BAG ) == 0 ){
		list[max] = MENU_POS_BAG;
		max++;
	}
	// �g���[�i�[�J�[�h
	if( ( wk->ev_flg & FLD_MENU_VANISH_TRCARD ) == 0 ){
		list[max] = MENU_POS_HERO;
		max++;
	}
	// ���|�[�g
	if( ( wk->ev_flg & FLD_MENU_VANISH_REPORT ) == 0 ){
		list[max] = MENU_POS_REPORT;
		max++;
	}
	// �ݒ�
	if( ( wk->ev_flg & FLD_MENU_VANISH_CONFIG ) == 0 ){
		list[max] = MENU_POS_CONFIG;
		max++;
	}
	// ����
	if( ( wk->ev_flg & FLD_MENU_VANISH_CLOSE ) == 0 ){
		list[max] = MENU_POS_EXIT;
		max++;
	}

	return max;
}

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�폜
 *
 * @param	wk		���j���[���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FieldMenuListExit( FLD_MENU * wk )
{
	CellActDelete( wk );

	BmpMenuExit( wk->mw, NULL );

	BMP_MENULIST_Delete( wk->ld );

	wk->mw = NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * �T�t�@���i�p�[�N�j�{�[���̌��E�B���h�E�쐬
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FieldBallWinSet( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	MSGDATA_MANAGER * man;
	WORDSET * wset;
	STRBUF * expb;
	STRBUF * strb;
	u8	flg;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	if( SysFlag_SafariCheck( SaveData_GetEventWork(fsys->savedata) ) == TRUE ){
		flg = 0;
	}else if( SysFlag_PokeParkCheck( SaveData_GetEventWork(fsys->savedata) ) == TRUE ){
		flg = 1;
	}else{
		return;
	}

	GF_BGL_BmpWinAdd(
		fsys->bgl, &wk->ball_win,
		FLD_MBGFRM_FONT, FLD_BALL_WIN_PX, FLD_BALL_WIN_PY,
		FLD_BALL_WIN_SX, FLD_BALL_WIN_SY, FLD_BALL_WIN_PAL, FLD_BALL_WIN_CGX );

	MenuWinGraphicSet(
		fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM,
		MENU_WIN_PAL, MENU_TYPE_FIELD, HEAPID_WORLD );

	BmpMenuWinWrite( &wk->ball_win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	GF_BGL_BmpWinDataFill( &wk->ball_win, 15 );

	man  = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_fieldmenu_dat, HEAPID_WORLD );
	if( flg == 0 ){
		strb = MSGMAN_AllocString( man, msg_menu_09 );	// �T�t�@���{�[��
	}else{
		strb = MSGMAN_AllocString( man, msg_menu_10 );	// �p�[�N�{�[��
	}
	GF_STR_PrintSimple(
		&wk->ball_win, FONT_SYSTEM, strb, BALL_NAME_PX, BALL_NAME_PY, MSG_NO_PUT, NULL );
	STRBUF_Delete( strb );

	wset = WORDSET_Create( HEAPID_WORLD );
	expb = STRBUF_Create( BALL_VAL_MSG_SIZ, HEAPID_WORLD );
	strb = MSGMAN_AllocString( man, msg_menu_11 );
	if( flg == 0 ){
		u16 * ball = Situation_GetSafariBallCount( SaveData_GetSituation(fsys->savedata) );
		WORDSET_RegisterNumber( wset, 0, *ball, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}else{
		int	ball = PokeParkSys_GetBallCount( fsys );
		WORDSET_RegisterNumber( wset, 0, ball, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
	}
	WORDSET_ExpandStr( wset, expb, strb );
	GF_STR_PrintSimple(
		&wk->ball_win, FONT_SYSTEM, expb, BALL_VAL_PX, BALL_VAL_PY, MSG_NO_PUT, NULL );

	STRBUF_Delete( expb );
	STRBUF_Delete( strb );
	WORDSET_Delete( wset );
	MSGMAN_Delete( man );

	GF_BGL_BmpWinOnVReq( &wk->ball_win );
}

//--------------------------------------------------------------------------------------------
/**
 * �T�t�@���i�p�[�N�j�{�[���̌��E�B���h�E�폜
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FieldBallWinExit( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	if( SysFlag_SafariCheck( SaveData_GetEventWork(fsys->savedata) ) == FALSE &&
		SysFlag_PokeParkCheck( SaveData_GetEventWork(fsys->savedata) ) == FALSE ){
		return;
	}

	BmpMenuWinClear( &wk->ball_win, WINDOW_TRANS_OFF );
	GF_BGL_BmpWinDel( &wk->ball_win );
}


//--------------------------------------------------------------------------------------------
/**
 * �I������
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL FieldMenuSelect( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	u16	cur;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	cur = BmpMenuCursorPosGet( wk->mw );
	wk->ret = BmpMenuMain_SE( wk->mw, SE_FLD_MENU_SELECT );
	wk->pos = BmpMenuCursorPosGet( wk->mw );

	if( cur != wk->pos ){
		CursorMove( wk->cap[CLA_SET_CURSOR]->act, wk->pos );
		MoveIconAnmChg( wk, cur, wk->pos );
		fsys->startmenu_pos = wk->list[wk->pos];
	}

	SelectIconAnmCheck( wk->cap[CLA_SET_ICON+wk->pos]->act );

	switch( wk->ret ){
	case BMPMENU_NULL:
		break;
	case BMPMENU_CANCEL:
		wk->seq = FLD_MENU_SEQ_END;
		break;
	default:
		if( FldMenuData[wk->ret][1] == BMPMENU_CANCEL ){
			wk->seq = FLD_MENU_SEQ_END;
		}else if( FldMenuData[wk->ret][1] != BMPMENU_NULL ){
			GMEVENT_FUNC func = (GMEVENT_FUNC)FldMenuData[wk->ret][1];
			return func( event );
		}
	}

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * ���j�I�����[���Řb�������\�̏�Ԃɂ���
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FldMenu_UnionBeaconChg( FLD_MENU * wk, FIELDSYS_WORK *fsys )
{
	// �ʐM���[�N�����݂��Ă���Ȃ�
	if( CommMPIsInitialize() ){
		// ���j�I�����[���Ȃ�
	    if( wk->union_flg ){
			UnionRoomView_ObjAllRise( fsys->union_view );
//			UnionRoomView_ObjInit( fsys->union_view );
			CommStateUnionBconCollectionRestart();
	        Union_BeaconChange( UNION_PARENT_MODE_FREE );
		}
    }
}


//============================================================================================
//	�Z���A�N�^�[
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�Z�b�g
 *
 * @param	wk		���[�N
 * @param	list	���j���[���X�g
 * @param	max		���j���[��
 * @param	sex		��l���̐���
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CellActSet( FLD_MENU * wk, u8 * list, u32 max, u8 sex )
{
	TCATS_RESOURCE_NUM_LIST	crnl = {
		FLDMENU_CLA_CHR_RES_MAX, FLDMENU_CLA_PAL_RES_MAX,
		FLDMENU_CLA_CEL_RES_MAX, FLDMENU_CLA_ANM_RES_MAX, 0, 0
	};
	u32	i;

	FieldCellActSet_S( &wk->fcat, &crnl, FLDMENU_CLACT_MAX, HEAPID_WORLD );

	// ���ʃp���b�g�ǂݍ���
	FldClact_LoadResPlttArc(
		&wk->fcat, ARC_MENU_GRA,
		NARC_menu_gra_fmenu_obj_NCLR, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, FLDMENU_CLA_PAL_H_ID );

	// �I���J�[�\��
	FldClact_LoadResCellArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_cur_NCER, 0, FLDMENU_CLA_CEL_H_ID_CURSOR );

	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_cur_NANR, 0, FLDMENU_CLA_ANM_H_ID_CURSOR );

	FldClact_LoadResourceCharArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_cur_NCGR,
		0, NNS_G2D_VRAM_TYPE_2DMAIN, FLDMENU_CLA_CHR_H_ID_CURSOR );

	wk->cap[CLA_SET_CURSOR] = FieldCellActAdd_S( &wk->fcat, &ActAddParam_S[CLA_SET_CURSOR] );

	CursorMove( wk->cap[CLA_SET_CURSOR]->act, wk->pos );

	// �A�C�R��
	FldClact_LoadResCellArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_obj_NCER, 0, FLDMENU_CLA_CEL_H_ID_ICON );

	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_obj_NANR, 0, FLDMENU_CLA_ANM_H_ID_ICON );

	FldClact_LoadResourceCharArc(
		&wk->fcat, ARC_MENU_GRA, NARC_menu_gra_fmenu_obj_NCGR,
		0, NNS_G2D_VRAM_TYPE_2DMAIN, FLDMENU_CLA_CHR_H_ID_ICON );

	for( i=0; i<max; i++ ){
		TCATS_OBJECT_ADD_PARAM_S	prm;

		prm = ActAddParam_S[CLA_SET_ICON];
		prm.y += CLA_ICON_SPC_Y * i;

		if( list[i] == MENU_POS_BAG && sex == 1 ){
			prm.anm = ICON_BAG_F * 3;
		}else{
			prm.anm = list[i] * 3;
		}

		wk->cap[CLA_SET_ICON+i] = FieldCellActAdd_S( &wk->fcat, &prm );

		{
			VecFx32 sca = { FX32_ONE, FX32_ONE, FX32_ONE };
			CLACT_SetScaleAffine( wk->cap[CLA_SET_ICON+i]->act, &sca, CLACT_AFFINE_NORMAL );
		}
	}
	IconAnmChange( wk->cap[CLA_SET_ICON+wk->pos]->act, ICON_ANM_SELECT, 1 );

	wk->clact_max = max + 1;	// �Z���A�N�^�[���i���ڐ��{�I���J�[�\���j

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CellActDelete( FLD_MENU * wk )
{
	u16	i;

	for( i=0; i<wk->clact_max; i++ ){
		CATS_ActorPointerDelete_S( wk->cap[i] );
	}
	FieldCellActDelete_S( &wk->fcat );
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�A�j��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CellActAnm( FLD_MENU * wk )
{
	u16	i;

	for( i=0; i<wk->clact_max; i++ ){
		CLACT_AnmFrameChg( wk->cap[i]->act, FX32_ONE );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �J�[�\���ړ�
 *
 * @param	cwp			�Z���A�N�^�[���[�N
 * @param	cur_pos		�J�[�\���ʒu
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CursorMove( CLACT_WORK_PTR cwp, u32 cur_pos )
{
	VecFx32	act_pos;

	act_pos = *(CLACT_GetMatrix( cwp ));
	act_pos.y = ( CLA_CURSOR_PY + CLA_ICON_SPC_Y * cur_pos ) * FX32_ONE;
	CLACT_SetMatrix( cwp, &act_pos );
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�R���A�j���ύX
 *
 * @param	cwp		�Z���A�N�^�[���[�N
 * @param	anm		�A�j���ԍ�
 * @param	pal		�p���b�g�ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void IconAnmChange( CLACT_WORK_PTR cwp, u16 anm, u16 pal )
{
	u32	now_anm = CLACT_AnmGet( cwp );

	CLACT_AnmChg( cwp, (now_anm/3)*3+anm );
	CLACT_PaletteNoChgAddTransPlttNo( cwp, pal );
}

//--------------------------------------------------------------------------------------------
/**
 * �J�[�\���ړ����̃A�C�R���A�j���ύX
 *
 * @param	wk			���[�N
 * @param	old_pos		�O��I������Ă����A�C�R���ʒu
 * @param	new_pos		�V�����I������Ă����A�C�R���ʒu
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void MoveIconAnmChg( FLD_MENU * wk, u16 old_pos, u16 new_pos )
{
	IconAnmChange( wk->cap[CLA_SET_ICON+old_pos]->act, ICON_ANM_STOP, 0 );
	IconAnmChange( wk->cap[CLA_SET_ICON+new_pos]->act, ICON_ANM_CHANGE, 1 );
}

//--------------------------------------------------------------------------------------------
/**
 * �I�����ꂽ�A�C�R���̃A�j���Ď�
 *
 * @param	cwp			�Z���A�N�^�[���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SelectIconAnmCheck( CLACT_WORK_PTR cwp )
{
	if( ( CLACT_AnmGet( cwp ) % 3 ) != ICON_ANM_CHANGE ){
		return;
	}
	if( CLACT_AnmActiveCheck( cwp ) == FALSE ){
		IconAnmChange( cwp, ICON_ANM_SELECT, 1 );
	}
}


//============================================================================================
//	���ڂ��Ƃ̏���
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�v���Ăяo��
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FldMenu_AppCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	if( WIPE_SYS_EndCheck() == FALSE ){ return; }

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	FieldMenuListExit( wk );
	GF_BGL_BmpWinDel( &wk->win );
	FieldBallWinExit( event );

	wk->app_func( event );
	wk->seq = FLD_MENU_SEQ_APP_WAIT;
}

//--------------------------------------------------------------------------------------------
/**
 * �A�v���I���҂�
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FldMenu_AppWait( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	// �T�u�v���Z�X�I���҂�
	if( FieldEvent_Cmd_WaitSubProcEnd( fsys ) ) {
		return;
	}

	wk->app_func( event );
}

//--------------------------------------------------------------------------------------------
/**
 * �A�v���I���҂������Z�b�g
 *
 * @param	wk		���[�N
 * @param	func	�I���҂�����
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldMenu_AppWaitFuncSet( FLD_MENU * wk, void * func )
{
	wk->app_func = func;
	wk->seq      = FLD_MENU_SEQ_APP_WAIT;
}


//============================================================================================
//	���j���[�F������
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �}�ӌĂяo���ݒ�
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ZukanInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_ZukanCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �}�ӌĂяo��
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ZukanCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	ZKN_PEARENT_DATA * p_pearent;
	ZUKAN_WORK * p_zukan;
	MYSTATUS * p_mystatus;
	EVENTWORK * p_eventwork;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	p_pearent = sys_AllocMemory( HEAPID_WORLD, sizeof(ZKN_PEARENT_DATA) );
	p_zukan   = SaveData_GetZukanWork( fsys->savedata );
	p_mystatus = SaveData_GetMyStatus( fsys->savedata );
	p_eventwork = SaveData_GetEventWork( fsys->savedata );
	p_pearent->cp_zukansave_data = p_zukan;
	p_pearent->cp_hero_data = p_mystatus;
	p_pearent->time_zone = EVTIME_GetTimeZone( fsys );
	p_pearent->hidemap_id_D15 = SysWork_HideMapWorkCheck( p_eventwork, HIDEMAP_ID_D15 );
	p_pearent->hidemap_id_D30 = SysWork_HideMapWorkCheck( p_eventwork, HIDEMAP_ID_D30 );
	p_pearent->hidemap_id_L04 = SysWork_HideMapWorkCheck( p_eventwork, HIDEMAP_ID_L04 );
	p_pearent->hidemap_id_D18 = SysWork_HideMapWorkCheck( p_eventwork, HIDEMAP_ID_D18 );
	p_pearent->p_zkn_work = fsys->p_zukandata;
	FieldZukan_SetProc( fsys, p_pearent );

	wk->app_wk   = p_pearent;
	wk->app_func = FldMenu_ZukanEnd;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �}�ӏI������
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ZukanEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	//�t�B�[���h�}�b�v�v���Z�X���A
	FieldEvent_Cmd_SetMapProc( fsys );

	if( wk->app_wk != NULL ){
		sys_FreeMemory( HEAPID_WORLD, wk->app_wk );
	}

	wk->seq = FLD_MENU_SEQ_AGAIN;

	return 0;
}


//=============================================================================================
//	���j���[�F�|�P����
//=============================================================================================
typedef struct {
	u8	pos;
	u8	mode;
	u16	item;
	u16	after_mons;
	int shinka_cond;
}FLDMENU_SHINKA_WORK;

typedef struct {
	u16	item;
	u16	cnt;
}FLDMENU_WAZADEL_WORK;

static BOOL FldMenu_PokeListInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_PokeListCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

static BOOL FldMenu_PokeListCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk   = FieldPokeList_SetProc( fsys, &wk->skill_check, 0 );
	wk->app_func = FldMenu_PokeListEnd;

	return 0;
}

BOOL FldMenu_PokeListEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	PLIST_DATA * dat;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );
	dat	 = (PLIST_DATA *)sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );

	memcpy( dat, wk->app_wk, sizeof(PLIST_DATA) );
	sys_FreeMemoryEz( wk->app_wk );

	switch( dat->ret_mode ){
	case PL_RET_STATUS:
		{
			PSTATUS_DATA * psd = sys_AllocMemory( HEAPID_WORLD, sizeof(PSTATUS_DATA) );

			psd->ppd  = SaveData_GetTemotiPokemon(fsys->savedata);
			psd->cfg  = SaveData_GetConfig( fsys->savedata );
			psd->ppt  = PST_PP_TYPE_POKEPARTY;
			psd->pos  = dat->ret_sel;
			psd->max  = (u8)PokeParty_GetPokeCount( psd->ppd );
			psd->waza = 0;
			psd->mode = PST_MODE_NORMAL;
			psd->ribbon = SaveData_GetSpRibbon( fsys->savedata );
			psd->zukan_mode = PMNumber_GetMode( fsys->savedata );
			psd->ev_contest = PokeStatus_ContestFlagGet( fsys->savedata );
			psd->perap = NULL;
			PokeStatus_PageSet( psd, PST_PageTbl_Normal );
			PokeStatus_PlayerSet( psd, SaveData_GetMyStatus(fsys->savedata) );
			FieldPokeStatus_SetProc( fsys, psd );

			wk->app_wk   = psd;
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeStatusEnd );
		}
		break;

	case PL_RET_WAZASET:		// �Z�Y��i�Z�}�V���j
		{
			PSTATUS_DATA * psd = sys_AllocMemory( HEAPID_WORLD, sizeof(PSTATUS_DATA) );

			psd->ppd  = SaveData_GetTemotiPokemon(fsys->savedata);
			psd->cfg  = SaveData_GetConfig( fsys->savedata );
			psd->ppt  = PST_PP_TYPE_POKEPARTY;
			psd->pos  = dat->ret_sel;
			psd->max  = 1;
			psd->waza = dat->waza;
			psd->mode = PST_MODE_WAZAADD;
			psd->zukan_mode = PMNumber_GetMode( fsys->savedata );
			psd->ev_contest = PokeStatus_ContestFlagGet( fsys->savedata );
			psd->perap = NULL;
			PokeStatus_PageSet( psd, PST_PageTbl_WazaSet );
			PokeStatus_PlayerSet( psd, SaveData_GetMyStatus(fsys->savedata) );
			FieldPokeStatus_SetProc( fsys, psd );

			{
				FLDMENU_WAZADEL_WORK * del = sys_AllocMemory( HEAPID_WORLD, sizeof(FLDMENU_WAZADEL_WORK) );
				del->item  = dat->item;
				del->cnt   = 0;
				wk->tmp_wk = del;
			}
			wk->app_wk   = psd;
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeStatusEnd );
		}
		break;

	case PL_RET_LVUP_WAZASET:	// �Z�Y��i�s�v�c�ȃA���j
		{
			PSTATUS_DATA * psd = sys_AllocMemory( HEAPID_WORLD, sizeof(PSTATUS_DATA) );

			psd->ppd  = SaveData_GetTemotiPokemon(fsys->savedata);
			psd->cfg  = SaveData_GetConfig( fsys->savedata );
			psd->ppt  = PST_PP_TYPE_POKEPARTY;
			psd->pos  = dat->ret_sel;
			psd->max  = 1;
			psd->waza = dat->waza;
			psd->mode = PST_MODE_WAZAADD;
			psd->zukan_mode = PMNumber_GetMode( fsys->savedata );
			psd->ev_contest = PokeStatus_ContestFlagGet( fsys->savedata );
			psd->perap = NULL;
			PokeStatus_PageSet( psd, PST_PageTbl_WazaSet );
			PokeStatus_PlayerSet( psd, SaveData_GetMyStatus(fsys->savedata) );
			FieldPokeStatus_SetProc( fsys, psd );

			{
				FLDMENU_WAZADEL_WORK * del = sys_AllocMemory( HEAPID_WORLD, sizeof(FLDMENU_WAZADEL_WORK) );
				del->item  = ITEM_DUMMY_DATA;
				del->cnt   = (u16)dat->lv_cnt;
				wk->tmp_wk = del;
			}
			wk->app_wk   = psd;
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeStatusEnd );
		}
		break;

	case PL_RET_MAILSET:
		{
			MAIL_PARAM * mail;

			mail = FieldMailCreate_InitCall(
					fsys, MAILBLOCK_TEMOTI, dat->ret_sel,
					ItemMailDesignGet(dat->item), HEAPID_WORLD );
			wk->app_wk = mail;
			if( dat->mode == PL_MODE_ITEMSET_RET ){
				wk->tmp_wk = FieldMenu_MailWorkMake( 
								dat->item, FM_MAIL_MODE_MAKE_LIST, dat->ret_sel );
			}else{
				wk->tmp_wk = FieldMenu_MailWorkMake(
								dat->item, FM_MAIL_MODE_MAKE_BAG, dat->ret_sel );
			}
			FldMenu_AppWaitFuncSet( wk, FldMenu_MailEnd );
		}
		break;

	case PL_RET_MAILREAD:
		{
			MAIL_PARAM * mail;
			POKEMON_PARAM * pp;

			pp = PokeParty_GetMemberPointer(
					SaveData_GetTemotiPokemon(fsys->savedata), dat->ret_sel );
			mail = FieldMailViewPoke_InitCall( fsys, pp, HEAPID_WORLD );
			wk->app_wk   = mail;
			wk->tmp_wk   = FieldMenu_MailWorkMake( dat->item, FM_MAIL_MODE_READ, dat->ret_sel );
			FldMenu_AppWaitFuncSet( wk, FldMenu_MailEnd );
		}
		break;

	case PL_RET_ITEMSET:	// �o�b�O�̎�������A�C�e���I����
		{
			MYITEM * myitem;
			void * myst;
			u32 * sel_pos;

			// �I�������|�P�����ʒu��ޔ�
			sel_pos = (u32 *)sys_AllocMemory( HEAPID_WORLD, 4 );
			*sel_pos = dat->ret_sel;
			wk->tmp_wk = (void *)sel_pos;

			myitem = SaveData_GetMyItem( fsys->savedata );
			myst   = SaveData_GetMyStatus( fsys->savedata );
			wk->app_wk = MyItem_MakeBagData( myitem, PokeList_ItemSetBagList, HEAPID_WORLD );
			BAG_SysDataSet( wk->app_wk, fsys->savedata, BAG_MODE_ITEMSET, fsys->bag_cursor );
		}

		FieldBag_SubProcSet( fsys, wk->app_wk );
		FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );
		break;

	case PL_RET_ITEMSHINKA:		// �i����ʂցi�A�C�e���i���j
		{
			FLDMENU_SHINKA_WORK * swk = sys_AllocMemory(HEAPID_WORLD,sizeof(FLDMENU_SHINKA_WORK));

			swk->item  = dat->item;
			swk->mode  = ITEM_SHINKA_CHECK;
			swk->pos   = dat->ret_sel;
			swk->after_mons = dat->after_mons;
			swk->shinka_cond = dat->shinka_cond;
			wk->app_wk = swk;
			wk->seq = FLD_MENU_SEQ_SHINKA_INIT;
		}
		break;

	case PL_RET_LVUPSHINKA:		// �i����ʂցi���x���i���j
		{
			FLDMENU_SHINKA_WORK * swk = sys_AllocMemory(HEAPID_WORLD,sizeof(FLDMENU_SHINKA_WORK));

			swk->item  = ZoneData_GetShinkaPlaceID( fsys->location->zone_id );
			swk->mode  = LEVELUP_SHINKA;
			swk->pos   = dat->ret_sel;
			swk->after_mons = dat->after_mons;
			swk->shinka_cond = dat->shinka_cond;
			wk->app_wk = swk;
			wk->seq = FLD_MENU_SEQ_SHINKA_INIT;
		}
		break;

	case PL_RET_IWAKUDAKI:		// ���j���[ �Z�F���킭����
	case PL_RET_IAIGIRI:		// ���j���[ �Z�F����������
	case PL_RET_SORAWOTOBU:		// ���j���[ �Z�F������Ƃ�
	case PL_RET_KIRIBARAI:		// ���j���[ �Z�F����΂炢
	case PL_RET_KAIRIKI:		// ���j���[ �Z�F�����肫
	case PL_RET_NAMINORI:		// ���j���[ �Z�F�Ȃ݂̂�
	case PL_RET_ROCKCLIMB:		// ���j���[ �Z�F���b�N�N���C��
	case PL_RET_TAKINOBORI:		// ���j���[ �Z�F�����̂ڂ�
	case PL_RET_FLASH:			// ���j���[ �Z�F�t���b�V��
	case PL_RET_TELEPORT:		// ���j���[ �Z�F�e���|�[�g
	case PL_RET_ANAWOHORU:		// ���j���[ �Z�F���Ȃ��ق�
	case PL_RET_AMAIKAORI:		// ���j���[ �Z�F���܂�������
	case PL_RET_OSYABERI:		// ���j���[ �Z�F������ׂ�
		{
			SKILLUSE_FUNC func;
			SKILLUSE_WORK suwk;

			suwk.skill    = dat->ret_mode - PL_RET_IAIGIRI;
			suwk.poke_pos = dat->ret_sel;
			suwk.event    = event;

			func = (SKILLUSE_FUNC)FieldSkill_FuncGet( FIELDSKILL_PRM_USEFUNC, suwk.skill );
			func( &suwk, &wk->skill_check);
		}
		break;

	case PL_RET_BAG:			// �o�b�O�֖߂�
		wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
		FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );
		break;

	default:
/*
		if( dat->mode == PL_MODE_ITEMUSE || dat->mode == PL_MODE_ITEMSET ||
			dat->mode == PL_MODE_WAZASET || dat->mode == PL_MODE_WAZASET_RET ||
			dat->mode == PL_MODE_SHINKA || dat->mode == PL_MODE_LVUPWAZASET_RET ){
*/
		if( dat->mode == PL_MODE_ITEMUSE || dat->mode == PL_MODE_WAZASET ||
			dat->mode == PL_MODE_WAZASET_RET || dat->mode == PL_MODE_SHINKA ||
			dat->mode == PL_MODE_LVUPWAZASET_RET ){

			wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
			if( dat->ret_sel >= 6 ){
				Bag_UsePokeSet( wk->app_wk, 0 );
			}else{
				Bag_UsePokeSet( wk->app_wk, dat->ret_sel );
			}
			FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

		}else if( dat->mode == PL_MODE_ITEMSET ){
			wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
			FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

		}else{
			//�t�B�[���h�}�b�v�v���Z�X���A
			FieldEvent_Cmd_SetMapProc( fsys );
			wk->seq = FLD_MENU_SEQ_AGAIN;
		}
	}
	sys_FreeMemoryEz( dat );

	return 0;
}





//=============================================================================================
//=============================================================================================
//	���j���[�F�o�b�O
//=============================================================================================
//=============================================================================================

static BOOL FldMenu_BagInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk   = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_BagCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

static BOOL FldMenu_BagCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	Bag_UsePokeSet( wk->app_wk, 0 );
	wk->app_func = FldMenu_BagEnd;

	return 0;
}

static BOOL FldMenu_BagEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	BAG_DATA * dat;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );
	dat  = BagSystemDataAlloc( HEAPID_WORLD );

	memcpy( dat, wk->app_wk, BagSystemDataSizeGet() );
	sys_FreeMemoryEz( wk->app_wk );

	switch( BagSysReturnModeGet( dat ) ){
	case BAG_RET_USE:		// ����
		{
			ITEMUSE_FUNC func;
			ITEMUSE_WORK iuwk;
			s32	use_id;

			iuwk.item     = BagSysReturnItemGet( dat );
			iuwk.use_poke = Bag_UsePokeGet( dat );
			iuwk.event    = event;
			use_id = ItemParamGet( iuwk.item, ITEM_PRM_FIELD, HEAPID_WORLD );
			func   = (ITEMUSE_FUNC)ItemUse_FuncGet( ITEMUSE_PRM_USEFUNC, use_id );
			func( &iuwk, &wk->item_check);
		}
		break;

	case BAG_RET_TAG:		// �^�O���݂�
		FldMenu_NutsTagCall( event, BagSysReturnItemGet(dat) );
		break;

	case BAG_RET_ITEMSET:	// ��������
		{
			PLIST_DATA * pld;

			pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );
			memset( pld, 0, sizeof(PLIST_DATA) );
			pld->pp     = SaveData_GetTemotiPokemon(fsys->savedata);
			pld->myitem = SaveData_GetMyItem( fsys->savedata );
			pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
			pld->cfg = SaveData_GetConfig( fsys->savedata );
			pld->scwk = &wk->skill_check;
			pld->type = PL_TYPE_SINGLE;
			pld->mode = PL_MODE_ITEMSET;
			pld->item = BagSysReturnItemGet( dat );
			GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

			wk->app_wk   = pld;
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
		}
		break;

	case BAG_RET_POKEITEMSET:	// �|�P�������X�g�u��������v
		{
			POKEPARTY * party;
			POKEMON_PARAM * pp;
			u32 pos;
			u16	item;

			party = SaveData_GetTemotiPokemon( fsys->savedata );
			pos   = *(u32 *)wk->tmp_wk;
			item  = BagSysReturnItemGet( dat );
			pp    = PokeParty_GetMemberPointer( party, pos );

			sys_FreeMemoryEz( wk->tmp_wk );

			if( ItemMailCheck( item ) == TRUE && PokeParaGet( pp, ID_PARA_item, NULL ) == 0 ){
				MAIL_PARAM * mail;
				FM_MAIL_WORK * make;

				mail = FieldMailCreate_InitCall(
						fsys, MAILBLOCK_TEMOTI, pos,
						ItemMailDesignGet(item), HEAPID_WORLD );
				wk->app_wk   = mail;
				wk->tmp_wk   = FieldMenu_MailWorkMake( item, FM_MAIL_MODE_MAKE_LIST, (u8)pos );
				FldMenu_AppWaitFuncSet( wk, FldMenu_MailEnd );
			}else{
				PLIST_DATA * pld;

				pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );
				memset( pld, 0, sizeof(PLIST_DATA) );
				pld->pp     = party;
				pld->myitem = SaveData_GetMyItem( fsys->savedata );
				pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
				pld->cfg = SaveData_GetConfig( fsys->savedata );
				pld->scwk = &wk->skill_check;
				pld->type = PL_TYPE_SINGLE;
				pld->item = BagSysReturnItemGet( dat );
				pld->ret_sel = (u8)pos;
				pld->fsys = fsys;
				if( pld->item == 0 ){
					pld->mode = PL_MODE_FIELD;
				}else{
					pld->mode = PL_MODE_ITEMSET_RET;
				}
				GameSystem_StartSubProc( fsys, &PokeListProcData, pld );
				wk->app_wk   = pld;
				FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
			}
		}
		break;

	case BAG_RET_CANCEL:
	default:
		//�t�B�[���h�}�b�v�v���Z�X���A
		FieldEvent_Cmd_SetMapProc( fsys );
		wk->seq = FLD_MENU_SEQ_AGAIN;
	}
	sys_FreeMemoryEz( dat );

	return 0;
}




//=============================================================================================
//	���j���[�F�i��l���j
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h�Ăяo���ݒ�
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_TrCardInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_TrCardCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h�Ăяo��
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_TrCardCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = TRCSET_AllocTrainerCardData( HEAPID_WORLD );
	TRCSET_MakeTrainerInfo( BADGE_BRUSH_ON, TIME_UPDATE_ON, GYM_READER_MASK_NONE,
							UNION_TR_NONE,
							fsys, (TR_CARD_DATA *)wk->app_wk );

	FieldTrCard_SetProc( fsys, (TR_CARD_DATA *)wk->app_wk );

	wk->app_func = FldMenu_TrCardEnd;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�J�[�h�I������
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_TrCardEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	//�o�b�W�����񐔍X�V
	TRCSET_UpdateBadgeScruchCount(fsys, (TR_CARD_DATA *)wk->app_wk);
	TRCSET_FreeTrainerCardData( (TR_CARD_DATA *)wk->app_wk );
	//�t�B�[���h�}�b�v�v���Z�X���A
	FieldEvent_Cmd_SetMapProc( fsys );
	wk->seq = FLD_MENU_SEQ_AGAIN;

	return 0;
}


//=============================================================================================
//=============================================================================================
//	���j���[�F���|�[�g
//=============================================================================================
//=============================================================================================
typedef struct {
	void * infowin;		///<�Z�[�u���E�B���h�E�p�|�C���^
//	int result;			///<�Z�[�u���ʎ󂯎��p���[�N
	u16 result;			///<�Z�[�u���ʎ󂯎��p���[�N
}FLDMENU_REPORT_WORK;

///���j���[���ځF���|�[�g�F������
static BOOL FldMenu_ReportInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk   = FieldEvent_GetSpecialWork( event );

	//�t�B�[���h���j���[����
	FieldMenuListExit( wk );
	BmpMenuWinClear( &wk->win, WINDOW_TRANS_OFF );
	GF_BGL_LoadScreenV_Req( wk->win.ini, wk->win.frmnum );
	GF_BGL_BmpWinDel( &wk->win );
	FieldBallWinExit( event );

	wk->seq = FLD_MENU_SEQ_REPORT_CALL;

	return TRUE;
}

///���j���[���ځF���|�[�g�F�Ăяo��
static void FldMenu_ReportCall( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk   = FieldEvent_GetSpecialWork( event );
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork( event );
	FLDMENU_REPORT_WORK * repwk;

	if (SaveData_IsOverwritingOtherData(fsys->savedata)) {
		EventCall_Script( event, SCRID_REPORT_NG, NULL, NULL );
	} else {
		//���|�[�g��񐶐�
		wk->app_wk = sys_AllocMemory(HEAPID_EVENT, sizeof(FLDMENU_REPORT_WORK));
		repwk = wk->app_wk;
		//���ʎ󂯎��p���[�N������
		repwk->result = FALSE;
		
		EventCall_Script( event, SCRID_REPORT, NULL, &repwk->result );
	}

	wk->seq = FLD_MENU_SEQ_REPORT_WAIT;
}

///���j���[���ځF���|�[�g�F���ʏ���
static void FldMenu_ReportWait( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork( event );
	FLD_MENU * wk   = FieldEvent_GetSpecialWork( event );
	FLDMENU_REPORT_WORK * repwk = wk->app_wk;

	if (SaveData_IsOverwritingOtherData(fsys->savedata)) {
		wk->seq = FLD_MENU_SEQ_INIT;
	} else {
		if( repwk->result == FALSE ){		//�Z�[�u���Ă��Ȃ�
			wk->seq = FLD_MENU_SEQ_INIT;
		}else{								//�Z�[�u����
			wk->seq = FLD_MENU_SEQ_END_NOMENU;
		}
		sys_FreeMemoryEz(repwk);
	}
}


//=============================================================================================
//	���j���[�F�����Ă�
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �R���t�B�O��ʌĂяo���ݒ�
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ConfigInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk   = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_ConfigCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �R���t�B�O��ʌĂяo��
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ConfigCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk   = FieldConfig_SetProc( fsys );
	wk->app_func = FldMenu_ConfigEnd;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �R���t�B�O��ʏI������
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ConfigEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	//���������
	sys_FreeMemoryEz( wk->app_wk );
	//�t�B�[���h�}�b�v�v���Z�X���A
	FieldEvent_Cmd_SetMapProc( fsys );
	wk->seq = FLD_MENU_SEQ_AGAIN;

	return	0;
}


//=============================================================================================
//=============================================================================================
//	���j���[�F�`���b�g
//=============================================================================================
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �`���b�g��ʌĂяo���ݒ�
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ChatInit( GMEVENT_CONTROL * event )
{
	FLD_MENU * wk;

	wk   = FieldEvent_GetSpecialWork( event );

	FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );

	wk->app_func = FldMenu_ChatCall;
	wk->seq = FLD_MENU_SEQ_APP_CALL;

	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �`���b�g��ʌĂяo��
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ChatCall( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	PMS_DATA  pmsDat;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = PMSI_PARAM_Create(
					PMSI_MODE_SENTENCE, PMSI_GUIDANCE_DEFAULT, fsys->savedata, HEAPID_WORLD );
	PMSDAT_Init( &pmsDat, PMS_TYPE_UNION);
	PMSI_PARAM_SetInitializeDataSentence( wk->app_wk, &pmsDat );
	FieldProc_SetPmsInput( fsys, (PMSI_PARAM*)wk->app_wk );

	wk->app_func = FldMenu_ChatEnd;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �`���b�g��ʏI������
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL FldMenu_ChatEnd( GMEVENT_CONTROL * event )
{
	PMS_DATA pmsdata;

	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	// �ȈՉ�b���X�V�������H
	if ( PMSI_PARAM_CheckCanceled( wk->app_wk )==0 ){

		// �ȈՉ�b�擾
		PMSI_PARAM_GetInputDataSentence( wk->app_wk,  &pmsdata);

		// �ʐM���[�N�����݂��Ă���Ȃ�
		if(CommMPIsInitialize()){
			// �r�[�R���f�[�^�̊ȈՉ�b������������ & �ʐM�f�[�^�ɔ��f
//			CommMPSetMyPMS( &pmsdata );
//			CommMPFlashMyBss();
			Union_PMSReWrite( &pmsdata );							// �r�[�R���f�[�^�ɔ��f������
			Union_SetMyPmsData( fsys->union_work, &pmsdata );		// ���j�I�����[�N�ŕۑ����Ă�������ʂɕ\��������
		}
		wk->seq = FLD_MENU_SEQ_BLACK_IN_END;
	}else{
		wk->seq = FLD_MENU_SEQ_AGAIN;
	}
	
	//���������
	PMSI_PARAM_Delete( (PMSI_PARAM*)wk->app_wk );

	//�t�B�[���h�}�b�v�v���Z�X���A
	FieldEvent_Cmd_SetMapProc( fsys );
//	UnionRoomView_ObjInit( fsys->union_view );
	UnionRoomView_ObjAllRise( fsys->union_view );

	return 0;
}


//=============================================================================================
//=============================================================================================
//	���j���[�F���^�C�A
//=============================================================================================
//=============================================================================================
static BOOL FldMenu_RetireInit( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	//�t�B�[���h���j���[����
	FieldMenuListExit( wk );
	BmpMenuWinClear( &wk->win, WINDOW_TRANS_OFF );
	GF_BGL_LoadScreenV_Req( wk->win.ini, wk->win.frmnum );
	GF_BGL_BmpWinDel( &wk->win );
	FieldBallWinExit( event );

	if( SysFlag_SafariCheck( SaveData_GetEventWork(fsys->savedata) ) == TRUE ){
		EventChange_Script( event, SCRID_SAFARI_RETIRE, NULL );
	}else{
		EventChange_Script( event, SCRID_D10R0101_ASK_RETIRE, NULL );
	}

	sys_FreeMemoryEz( wk );
	return FALSE;
}


//=============================================================================================
//=============================================================================================
//	�T�u�A�v���F�X�e�[�^�X���
//=============================================================================================
//=============================================================================================
static BOOL FldMenu_PokeStatusEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	PSTATUS_DATA * dat;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	dat = sys_AllocMemory( HEAPID_WORLD, sizeof(PSTATUS_DATA) );

	memcpy( dat, wk->app_wk, sizeof(PSTATUS_DATA) );
	sys_FreeMemoryEz( wk->app_wk );

	switch( dat->mode ){
	case PST_MODE_WAZAADD:	// �Z�o��/�Z�Y��
		{
			PLIST_DATA * pld;
			FLDMENU_WAZADEL_WORK * del;

			pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );
			del = (FLDMENU_WAZADEL_WORK *)wk->tmp_wk;
			memset( pld, 0, sizeof(PLIST_DATA) );
			pld->pp     = SaveData_GetTemotiPokemon(fsys->savedata);
			pld->myitem = SaveData_GetMyItem( fsys->savedata );
			pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
			pld->cfg = SaveData_GetConfig( fsys->savedata );
			pld->scwk = &wk->skill_check;
			pld->type = PL_TYPE_SINGLE;
			pld->fsys = fsys;
			if( del->item != ITEM_DUMMY_DATA ){
				pld->mode   = PL_MODE_WAZASET_RET;
				pld->lv_cnt = 0;
			}else{
				pld->mode   = PL_MODE_LVUPWAZASET_RET;
				pld->lv_cnt = del->cnt;
			}
			pld->item = del->item;
			pld->ret_sel = dat->pos;
			pld->waza = dat->waza;
			pld->waza_pos = dat->ret_sel;
			GameSystem_StartSubProc( fsys, &PokeListProcData, pld );
			sys_FreeMemoryEz( wk->tmp_wk );

			wk->app_wk   = pld;
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
		}
		break;

	default:
		wk->app_wk = FieldPokeList_SetProc( fsys, &wk->skill_check, dat->pos );
		FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
	}
	sys_FreeMemoryEz( dat );

	return 0;
}


//=============================================================================================
//=============================================================================================
//	�T�u�A�v���F�؂̎��^�O
//=============================================================================================
//=============================================================================================
static void FldMenu_NutsTagCall( GMEVENT_CONTROL * event, u16 item )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	MYITEM * myitem;
	u8	i;
	u8	scr, cur, max;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = NutsTagSystemDataAlloc( HEAPID_WORLD );
	myitem = SaveData_GetMyItem( fsys->savedata );
	NutsTagPutDataSet( wk->app_wk, item, TAG_ON );
	max = 0;
	for( i=0; i<ITEM_NUTS_MAX; i++ ){
		item = NutsIDItemGet( i );
		if( MyItem_CheckItem( myitem, item, 1, HEAPID_WORLD ) == TRUE ){
			NutsTagPutDataSet( wk->app_wk, item, TAG_OFF );
			max++;
		}
	}
	MyItem_FieldBagCursorGet( fsys->bag_cursor, BAG_POKE_NUTS, &cur, &scr );
	NutsTagBagCursorSet( wk->app_wk, scr, cur, max+3 );

	FieldNutsTag_SetProc( fsys, wk->app_wk );
	FldMenu_AppWaitFuncSet( wk, FldMenu_NutsTagEnd );
}

static BOOL FldMenu_NutsTagEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	u8	scr, cur;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	TagPosGet( wk->app_wk, &scr, &cur );
	MyItem_FieldBagCursorSet( fsys->bag_cursor, BAG_POKE_NUTS, cur, scr );

	sys_FreeMemory( HEAPID_WORLD, wk->app_wk );

	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

	return 0;
}


//=============================================================================================
//=============================================================================================
//	�T�u�A�v���F�^�E���}�b�v
//=============================================================================================
//=============================================================================================
BOOL FldMenu_TownMapEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	sys_FreeMemory( HEAPID_WORLD, wk->app_wk );
	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

	return 0;
}

// �����
BOOL FldMenu_SorawotobuEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	TOWNMAP_PARAM * tmwk;
	u32	sel_pos;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	sel_pos = *((u32 *)wk->tmp_wk);
	sys_FreeMemory( HEAPID_WORLD, wk->tmp_wk );

	tmwk = (TOWNMAP_PARAM *)wk->app_wk;
	if( !(tmwk->retval) ){
		sys_FreeMemory( HEAPID_WORLD, wk->app_wk );
		wk->app_wk = FieldPokeList_SetProc( fsys, &wk->skill_check, sel_pos );
		FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
	}else{
		POKEMON_PARAM * pp;
		void * ciwk;
		void * buf;

		pp = PokeParty_GetMemberPointer(
				SaveData_GetTemotiPokemon(fsys->savedata), sel_pos );
		ciwk = EventWorkSet_FlySkyMapChange( HEAPID_WORLD,
				fsys, pp, tmwk->ret_zone, tmwk->ret_x*32+16, tmwk->ret_z*32+16 );

		buf = FNOTE_ActionSkillDataMake( FNOTE_SORAWOTOBU, tmwk->ret_zone, HEAPID_WORLD );
		FNOTE_DataSave( fsys->fnote, buf, FNOTE_TYPE_ACTION );

		sys_FreeMemory( HEAPID_WORLD, wk->app_wk );

		FieldEvent_Cmd_SetMapProc( fsys );

		wk->app_func = GMEVENT_FlySkyMapChange;
		wk->app_wk   = ciwk;
		wk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
	}

	return 0;
}


//=============================================================================================
//=============================================================================================
//	�T�u�A�v���F�`���m�[�g
//=============================================================================================
//=============================================================================================
BOOL FldMenu_FantasyNoteEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

	return 0;
}


//=============================================================================================
//=============================================================================================
//	�T�u�A�v���F���[��
//=============================================================================================
//=============================================================================================
static void FM_MailMakeTrue( FIELDSYS_WORK * fsys, FLD_MENU * wk, u8 list_mode );

void * FieldMenu_MailWorkMake( u16 item, u8 mode, u8 poke_pos )
{
	FM_MAIL_WORK * mw = sys_AllocMemory( HEAPID_WORLD, sizeof(FM_MAIL_WORK) );

	mw->item = item;
	mw->pos  = poke_pos;
	mw->mode = mode;
	return (void *)mw;
}



BOOL FldMenu_MailEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	FM_MAIL_WORK * mw;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );
	mw   = wk->tmp_wk;

	switch( mw->mode ){
	case FM_MAIL_MODE_VIEW:		// ���[��������
		MailSys_ReleaseCallWork( wk->app_wk );
		wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
		FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );
		break;

	case FM_MAIL_MODE_READ:		// ���[����ǂ�
		MailSys_ReleaseCallWork( wk->app_wk );
		wk->app_wk = FieldPokeList_SetProc( fsys, &wk->skill_check, mw->pos );
		FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
		break;

	case FM_MAIL_MODE_MAKE_LIST:	// ���[������������i�|�P�������X�g����j
		if( MailSys_IsDataCreate( wk->app_wk ) == TRUE ){
			FM_MailMakeTrue( fsys, wk, PL_MODE_MAILSET_BAG );
		}else{
			MailSys_ReleaseCallWork( wk->app_wk );
			wk->app_wk = FieldPokeList_SetProc( fsys, &wk->skill_check, mw->pos );
			FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
		}
		break;

	case FM_MAIL_MODE_MAKE_BAG:		// ���[������������i�o�b�O����j
		if( MailSys_IsDataCreate( wk->app_wk ) == TRUE ){
			FM_MailMakeTrue( fsys, wk, PL_MODE_MAILSET );
		}else{
			MailSys_ReleaseCallWork( wk->app_wk );
			wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
			FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );
		}
		break;
	}
	sys_FreeMemoryEz( wk->tmp_wk );
	return 0;
}

static void FM_MailMakeTrue( FIELDSYS_WORK * fsys, FLD_MENU * wk, u8 list_mode )
{
	FM_MAIL_WORK * mw;
	PLIST_DATA * pld;

	mw  = wk->tmp_wk;
	pld = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );
	memset( pld, 0, sizeof(PLIST_DATA) );
	pld->pp      = SaveData_GetTemotiPokemon(fsys->savedata);
	pld->myitem  = SaveData_GetMyItem( fsys->savedata );
	pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
	pld->cfg = SaveData_GetConfig( fsys->savedata );
	pld->scwk    = &wk->skill_check;
	pld->type    = PL_TYPE_SINGLE;
	pld->item    = mw->item;
	pld->ret_sel = mw->pos;
	pld->mode    = list_mode;
	pld->fsys = fsys;
	MailSys_PushDataToSavePoke( wk->app_wk, PokeParty_GetMemberPointer(pld->pp,mw->pos) );
	MailSys_ReleaseCallWork( wk->app_wk );

	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );
	wk->app_wk   = pld;
	FldMenu_AppWaitFuncSet( wk, FldMenu_PokeListEnd );
}



//=============================================================================================
//=============================================================================================
//	�T�u�A�v���F�|���g�P�[�X
//=============================================================================================
//=============================================================================================
BOOL FldMenu_PorutoCaseEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	PorutoSys_ReleaseCallWork( wk->app_wk );

	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

	return 0;
}


//=============================================================================================
//=============================================================================================
//	�T�u�A�v���F�F�B�蒠
//=============================================================================================
//=============================================================================================
BOOL FldMenu_FriendBookEnd( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
	FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );

	return 0;
}



//=============================================================================================
//=============================================================================================
//	�T�u�A�v���F�i����ʁi����j
//=============================================================================================
//=============================================================================================

static void FldMenu_ShinkaInit( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;
	FLDMENU_SHINKA_WORK * swk;
	POKEPARTY * party;
	POKEMON_PARAM * pp;
	SHINKA_WORK * demo;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );
	swk  = wk->app_wk;

	Snd_Stop();	//�T�E���h�S��~

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_ITEMSHINKA, 0x30000 );

	party = SaveData_GetTemotiPokemon(fsys->savedata);
	pp   = PokeParty_GetMemberPointer( party, swk->pos );

	if( swk->mode == LEVELUP_SHINKA ){
		demo = ShinkaInit(
					party,//ppt
					pp, swk->after_mons,
					SaveData_GetConfig(fsys->savedata),
					PokeStatus_ContestFlagGet(fsys->savedata), 
					SaveData_GetZukanWork(fsys->savedata),
					SaveData_GetMyItem(fsys->savedata),//my_item
					SaveData_GetRecord(fsys->savedata),//record
					SaveData_GetPoketchData(fsys->savedata),//poketch_data
					swk->shinka_cond,//shinka_cond
					SHINKA_STATUS_FLAG_CANCEL_ON, HEAPID_ITEMSHINKA );
	}else{
		demo = ShinkaInit(
					party,//ppt
					pp, swk->after_mons,
					SaveData_GetConfig(fsys->savedata),
					PokeStatus_ContestFlagGet(fsys->savedata), 
					SaveData_GetZukanWork(fsys->savedata),
					SaveData_GetMyItem(fsys->savedata),//my_item
					SaveData_GetRecord(fsys->savedata),//record
					SaveData_GetPoketchData(fsys->savedata),//poketch_data
					swk->shinka_cond,//shinka_cond
					NULL, HEAPID_ITEMSHINKA );
	}


	{
		u32 * ret_sel = sys_AllocMemory( HEAPID_WORLD, 4 );
		*ret_sel = swk->pos;
		wk->tmp_wk = ret_sel;
	}

	sys_FreeMemoryEz( wk->app_wk );
	wk->app_wk = demo;
	wk->seq    = FLD_MENU_SEQ_SHINKA_MAIN;
}

static void FldMenu_ShinkaMain( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	if( ShinkaEndCheck( wk->app_wk ) == TRUE ){
		ShinkaEnd( wk->app_wk );
		sys_DeleteHeap( HEAPID_ITEMSHINKA );

		Snd_BgmStop( SEQ_SHINKA, 0 );				//�i���Ȃ��~�߂�
		Snd_SceneSet( SND_SCENE_DUMMY );			//�K���t�B�[���h�f�[�^���ă��[�h������I
		Snd_FieldMapInitBgmPlay( fsys, fsys->location->zone_id );

		wk->app_wk = FieldBag_SetProc( fsys, &wk->item_check );
		{
			u32	ret_sel = *((u32 *)wk->tmp_wk);
			Bag_UsePokeSet( wk->app_wk, (u8)ret_sel );
			sys_FreeMemoryEz( wk->tmp_wk );
		}
		FldMenu_AppWaitFuncSet( wk, FldMenu_BagEnd );
	}
}
