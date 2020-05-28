//============================================================================================
/**
 * @file	itemuse.c
 * @brief	�t�B�[���h�A�C�e���g�p����
 * @author	Hiroyuki Nakamura
 * @date	05.12.12
 */
//============================================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/clact_tool.h"
#include "system/snd_tool.h"
#include "system/wipe.h"
#include "system/window.h"
#include "poketool/pokeparty.h"
#include "itemtool/item.h"
#include "itemtool/myitem.h"
#include "application/pokelist.h"
#include "application/poru_tool.h"
#include "application/bag.h"
#include "savedata/tv_work.h"

#include "field_common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "field_clact.h"
#include "field_subproc.h"
#include "fld_menu.h"
#include "fld_bgm.h"
#include "fieldmap.h"
#include "talk_msg.h"
#include "ev_mapchange.h"
#include "zonedata.h"
#include "map_attr.h"
#include "sway_grass_enc.h"	//for SwayGrass_InitSwayGrass
#include "sysflag.h"
#include "syswork.h"
#include "savedata/zukanwork.h"
#include "field_fishing.h"
#include "field_ananuke.h"
#include "eventdata.h"
#include "b_tower_ev.h"

#define	ITEMUSE_H_GLOBAL
#include "field/itemuse.h"

#include "seedsys.h"
#include "script.h"
#include "sxy.h"
#include "../fielddata/script/kinomi_def.h"
#include "../fielddata/script/saisen_def.h"
#include "amaikaori_eff.h"

#include "../fielddata/script/common_scr_def.h"	//SCRID_TENKAINOFUE
//#include "mapdefine.h"

//============================================================================================
//	�萔��`
//============================================================================================
typedef void * (*CNVFUNC_CALL)(void*);

// �֗��{�^�����[�N
typedef struct {
	FIELDSYS_WORK * fsys;
	ITEMCHECK_WORK	icwk;
	CNVFUNC_CALL	call;
	void * app_wk;
	u16	item;
	u8	seq;
}CONV_WORK;

typedef BOOL (*ITEMCNV_FUNC)(CONV_WORK*);	// �֗��{�^���g�p�֐�

typedef struct {
	ITEMUSE_FUNC	use_func;		// �o�b�O����g�p
	ITEMCNV_FUNC	cnv_func;		// �֗��{�^������g�p
	ITEMCHECK_FUNC	check_func;		// �g�p�`�F�b�N
}ITEMUSE_FUNC_DATA;


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
extern void * FieldMenuTMap_SetProc( FIELDSYS_WORK * fsys );

static void ItemUse_Recover( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Townmap( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Tankenset( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Cycle( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_FantasyNote( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_WazaMachine( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Mail( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Kinomi( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_PrtCase( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_FriendBook( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_PokeSearcher( ITEMUSE_WORK * iuwk , const ITEMCHECK_WORK * icwk);
static void ItemUse_Zyouro( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Compost( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_SweetHoney( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_BtlSearcher( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_FishingRodBad( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_FishingRodGood( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_FishingRodGreat( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Evolution( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Ananuke( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);
static void ItemUse_Tenkainofue( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk);

static BOOL ItemCnv_Cycle( CONV_WORK * wk );
static BOOL ItemCnv_FantasyNote( CONV_WORK * wk );
static BOOL ItemCnv_FishingRodBad( CONV_WORK * wk );
static BOOL ItemCnv_FishingRodGood( CONV_WORK * wk );
static BOOL ItemCnv_FishingRodGreat( CONV_WORK * wk );
static BOOL ItemCnv_BagMsgItem( CONV_WORK * wk );
static BOOL ItemCnv_Townmap( CONV_WORK * wk );
static BOOL ItemCnv_PrtCase( CONV_WORK * wk );
static BOOL ItemCnv_FriendBook( CONV_WORK * wk );
static BOOL ItemCnv_Tankenset( CONV_WORK * wk );
static BOOL ItemCnv_PokeSearcher( CONV_WORK * wk );
static BOOL ItemCnv_Zyouro( CONV_WORK * wk );
static BOOL ItemCnv_BtlSearcher( CONV_WORK * wk );
static BOOL ItemCnv_Tenkainofue( CONV_WORK * wk );
static void * ConvCall_FriendBook( void * fsys );
static void * ConvCall_PrtCase( void * fsys );
static void * ConvCall_Townmap( void * fsys );
static void * ConvCall_FantasyNote( void * fsys );

static u32 ItemUseCheck_Cycle( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Tankenset( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Kinomi( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_PokeSearcher( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Zyouro( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Compost( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_BtlSearcher( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_FishingRod( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Ananuke( const ITEMCHECK_WORK * icwk );
static u32 ItemUseCheck_Tenkainofue( const ITEMCHECK_WORK * icwk );

static BOOL GMEVENT_ItemUseCycle( GMEVENT_CONTROL * event );
static BOOL GMEVENT_BagMsgItem( GMEVENT_CONTROL * event );

static void ConvFuncCallSet( CONV_WORK * wk, CNVFUNC_CALL call );
static BOOL GMEVENT_ConvButtonCommon( GMEVENT_CONTROL * event );

static BOOL GMEVENT_AnanukeMapChangeInit( GMEVENT_CONTROL *event );

//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// �g�p�֐��e�[�u��
static const ITEMUSE_FUNC_DATA ItemFuncTable[] =
{
	{	// 000:�_�~�[
		NULL,				// �o�b�O����̎g�p����
		ItemCnv_BagMsgItem,	// �֗��{�^������̎g�p����
		NULL				// �g�p�`�F�b�N
	},
	{	// 001:��
		ItemUse_Recover,
		NULL,
		NULL
	},
	{	// 002:�^�E���}�b�v
		ItemUse_Townmap,
		ItemCnv_Townmap,
		NULL,
	},
	{	// 003:�T���Z�b�g
		ItemUse_Tankenset,
		ItemCnv_Tankenset,
		ItemUseCheck_Tankenset
	},
	{	// 004:���]��
		ItemUse_Cycle,
		ItemCnv_Cycle,
		ItemUseCheck_Cycle,
	},
	{	// 005:�`���m�[�g
		ItemUse_FantasyNote,
		ItemCnv_FantasyNote,
		NULL,
	},
	{	// 006:�Z�}�V��
		ItemUse_WazaMachine,
		NULL,
		NULL
	},
	{	// 007:���[��
		ItemUse_Mail,
		NULL,
		NULL
	},
	{	// 008:���̂�
		ItemUse_Kinomi,
		NULL,
		ItemUseCheck_Kinomi
	},
	{	// 009:�|���g�P�[�X
		ItemUse_PrtCase,
		ItemCnv_PrtCase,
		NULL
	},
	{	// 010:�F�B�蒠
		ItemUse_FriendBook,
		ItemCnv_FriendBook,
		NULL
	},
	{	// 011:�|�P�T�[�`���[
		ItemUse_PokeSearcher,
		ItemCnv_PokeSearcher,
		ItemUseCheck_PokeSearcher
	},
	{	// 012:���傤��
		ItemUse_Zyouro,
		ItemCnv_Zyouro,
		ItemUseCheck_Zyouro
	},
	{	// 013:�R���V
		ItemUse_Compost,
		NULL,
		ItemUseCheck_Compost
	},
	{	// 014:�Â���
		ItemUse_SweetHoney,
		NULL,
		NULL
	},
	{	// 015:�o�g���T�[�`���[
		ItemUse_BtlSearcher,
		ItemCnv_BtlSearcher,
		ItemUseCheck_BtlSearcher
	},
	{	// 016:�{���̒ފ�
		ItemUse_FishingRodBad,
		ItemCnv_FishingRodBad,
		ItemUseCheck_FishingRod
	},
	{	// 017:�ǂ��ފ�
		ItemUse_FishingRodGood,
		ItemCnv_FishingRodGood,
		ItemUseCheck_FishingRod
	},
	{	// 018:�����ފ�
		ItemUse_FishingRodGreat,
		ItemCnv_FishingRodGreat,
		ItemUseCheck_FishingRod
	},
	{	// 019:�o�b�O���Ŏg�p���铹��
		NULL,
		ItemCnv_BagMsgItem,
		NULL
	},
	{	// 020:�i��
		ItemUse_Evolution,
		NULL,
		NULL
	},
	{	// 021:�������̕R
		ItemUse_Ananuke,
		NULL,
		ItemUseCheck_Ananuke
	},
	{	// 022:�V�E�̓J
		ItemUse_Tenkainofue,
		ItemCnv_Tenkainofue,
		ItemUseCheck_Tenkainofue
	},
};



//--------------------------------------------------------------------------------------------
/**
 * �g�p�֐��擾
 *
 * @param	prm		�擾�p�����[�^
 * @param	id		�֐�ID
 *
 * @return	�g�p�֐�
 */
//--------------------------------------------------------------------------------------------
u32 ItemUse_FuncGet( u16 prm, u16 id )
{
	if( prm == ITEMUSE_PRM_USEFUNC ){
		return (u32)ItemFuncTable[id].use_func;
	}else if( prm == ITEMUSE_PRM_CNVFUNC ){
		return (u32)ItemFuncTable[id].cnv_func;
	}
	return (u32)ItemFuncTable[id].check_func;
}

//--------------------------------------------------------------------------------------------
/**
 * �g�p�`�F�b�N���[�N�쐬
 *
 * @param	fsys	�t�B�[���h���[�N
 * @param	id		�`�F�b�N���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void ItemUse_CheckWorkMake( FIELDSYS_WORK * fsys, ITEMCHECK_WORK * icwk )
{
	int x, z, dir;
	FIELD_OBJ_PTR obj;

	icwk->fsys = fsys;

	//�]�[���h�c
	icwk->zone_id = fsys->location->zone_id;

	//�A�����
	icwk->Companion = SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata));

	//���@�`��
	icwk->PlayerForm = Player_FormGet( fsys->player );
	x = Player_NowGPosXGet( fsys->player );
	z = Player_NowGPosZGet( fsys->player );
	//���݃A�g���r���[�g
	icwk->NowAttr = GetAttributeLSB(fsys, x, z);

	dir = Player_DirGet( fsys->player );
	switch(dir){
	case DIR_UP:
		z--;
		break;
	case DIR_DOWN:
		z++;
		break;
	case DIR_RIGHT:
		x++;
		break;
	case DIR_LEFT:
		x--;
		break;
	}
	//�O���A�g���r���[�g
	icwk->FrontAttr = GetAttributeLSB(fsys, x, z);
	SXY_HeroFrontObjGet(fsys, &obj);
	//���̂݊֘A�ǂ����̎g�p�`�F�b�N
	icwk->SeedInfo = SeedSys_ItemUseCheck(fsys, obj);

	//���@���Q�ƃ|�C���^
	icwk->player = fsys->player;
}

//============================================================================================
//
//	�X�N���v�g�Ăяo��
//
//============================================================================================
static BOOL GMEVENT_ItemScript(GMEVENT_CONTROL * event);
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
typedef struct {
	u32 scr_id;		///<�Ăяo���X�N���v�g��ID
	u16 param0;		///<�����n���p�����[�^���̂P
	u16 param1;		///<�����n���p�����[�^���̂Q
	u16 param2;		///<�����n���p�����[�^���̂R
	u16 param3;		///<�����n���p�����[�^���̂S
}CALL_SCR_WORK;

//--------------------------------------------------------------------------------------------
/**
 * @brief 
 * @param scr_id;		///<�Ăяo���X�N���v�g��ID
 * @param param0;		///<�����n���p�����[�^���̂P
 * @param param1;		///<�����n���p�����[�^���̂Q
 * @param param2;		///<�����n���p�����[�^���̂R
 * @param param3;		///<�����n���p�����[�^���̂S
 * @return	CALL_SCR_WORK	�X�N���v�g�Ăяo���p���[�N
 */
//--------------------------------------------------------------------------------------------
static CALL_SCR_WORK * CSW_Create(u32 scr_id, u16 param0, u16 param1, u16 param2, u16 param3)
{
	CALL_SCR_WORK * csw;
	csw = sys_AllocMemory(HEAPID_EVENT, sizeof(CALL_SCR_WORK));
	csw->scr_id = scr_id;
	csw->param0 = param0;
	csw->param1 = param1;
	csw->param2 = param2;
	csw->param3 = param3;
	return csw;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���p�X�N���v�g�N���̐ݒ�
 * @param	iuwk	�A�C�e���g�p���[�N
 * @param	icwk	�A�C�e���g�p�`�F�b�N���[�N
 * @param	scr_id	�X�N���v�gID
 */
//--------------------------------------------------------------------------------------------
static void SetUpItemScript(ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk, u32 scr_id)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	FieldEvent_Cmd_SetMapProc( fsys );

	mwk->app_func = GMEVENT_ItemScript;
	mwk->app_wk   = CSW_Create(scr_id, iuwk->item, 0, 0, 0);
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���p�X�N���v�g�N���̐ݒ�i�֗��{�^���j
 * @param	iuwk	�A�C�e���g�p���[�N
 * @param	icwk	�A�C�e���g�p�`�F�b�N���[�N
 * @param	scr_id	�X�N���v�gID
 */
//--------------------------------------------------------------------------------------------
static void SetUpItemScriptCnv( CONV_WORK * wk, u32 scr_id )
{
	void * work = CSW_Create(scr_id, wk->item, 0, 0, 0);
	FieldEvent_Set( wk->fsys, GMEVENT_ItemScript, work );
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���p�X�N���v�g�̌Ăяo���C�x���g
 * @param	event	�C�x���g���䃏�[�N�ւ̃|�C���^
 * @return	BOOL	TRUE�ŃC�x���g�I���AFALSE�ŃC�x���g���s
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_ItemScript(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	CALL_SCR_WORK * csw = FieldEvent_GetSpecialWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	FIELD_OBJ_PTR obj;
	switch (*seq) {
	case 0:
		SXY_HeroFrontObjGet(fsys, &obj);
		EventCall_Script(event, csw->scr_id, obj, NULL);
		*(u16*)(GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_WK_PARAM0)) = csw->param0;
		*(u16*)(GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_WK_PARAM1)) = csw->param1;
		*(u16*)(GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_WK_PARAM2)) = csw->param2;
		*(u16*)(GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_WK_PARAM3)) = csw->param3;

		(*seq) ++;
		break;
	case 1:
		sys_FreeMemoryEz(csw);
		return TRUE;
	}
	return FALSE;
}

//============================================================================================
//	001:��
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F��
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Recover( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	PLIST_DATA * pld;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );

	memset( pld, 0, sizeof(PLIST_DATA) );
	pld->pp     = SaveData_GetTemotiPokemon( fsys->savedata );
	pld->myitem = SaveData_GetMyItem( fsys->savedata );
	pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
	pld->cfg = SaveData_GetConfig( fsys->savedata );
	pld->tvwk = SaveData_GetTvWork( fsys->savedata );
	pld->scwk = &mwk->skill_check;
	pld->type = PL_TYPE_SINGLE;
	pld->mode = PL_MODE_ITEMUSE;
	pld->fsys = fsys;
	pld->item = iuwk->item;
	pld->ret_sel = iuwk->use_poke;
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	mwk->app_wk = pld;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_PokeListEnd );
}


//============================================================================================
//	002:�^�E���}�b�v
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F�^�E���}�b�v
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Townmap( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	mwk->app_wk = FieldMenuTMap_SetProc( fsys );
	FldMenu_AppWaitFuncSet( mwk, FldMenu_TownMapEnd );
}


//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�^�E���}�b�v
 *
 * @param	wk	�֗��{�^�����[�N
 *
 * @return	TRUE�i�֗��{�^�����[�N��������Ȃ��j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_Townmap( CONV_WORK * wk )
{
	ConvFuncCallSet( wk, ConvCall_Townmap );
	return TRUE;
}

static void * ConvCall_Townmap( void * fsys )
{
	return FieldMenuTMap_SetProc( fsys );
}



//============================================================================================
//	003:�T���Z�b�g
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F�T���Z�b�g
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Tankenset( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	FieldEvent_Cmd_SetMapProc( fsys );

	//mwk->app_func = GMEVENT_UgChange;
	mwk->app_func = GMEVENT_GroundToUnderGround;
	mwk->app_wk   = MakeUGChangeWork( fsys );
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;

	fsys->startmenu_pos = 0;		// ���j���[�ʒu�N���A
}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�T���Z�b�g
 *
 * @param	wk	�֗��{�^�����[�N
 *
 * @return	FALSE�i�֗��{�^�����[�N����j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_Tankenset( CONV_WORK * wk )
{
	void * work = MakeUGChangeWork( wk->fsys );
	FieldOBJSys_MovePauseAll( wk->fsys->fldobjsys );
	FieldEvent_Set( wk->fsys, GMEVENT_GroundToUnderGround, work );
	wk->fsys->startmenu_pos = 0;		// ���j���[�ʒu�N���A
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�`�F�b�N�֐��F�T���Z�b�g
 *
 * @param	icwk	�A�C�e���g�p�`�F�b�N���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Tankenset( const ITEMCHECK_WORK * icwk )
{
	// �t�B�[���h��
	if( !(ZoneData_IsSinouField(icwk->zone_id)) ){
		return ITEMCHECK_FALSE;
	}

	// �T�C�N�����O���[�h�`�F�b�N
	if( Player_MoveBitCheck_CyclingRoad( icwk->player ) == TRUE ){
		return ITEMCHECK_FALSE;
	}

	// �|�P�p�[�N�E�T�t�@���`�F�b�N
	if( SysFlag_SafariCheck( SaveData_GetEventWork(icwk->fsys->savedata) ) == TRUE ||
		SysFlag_PokeParkCheck( SaveData_GetEventWork(icwk->fsys->savedata) ) == TRUE ){
		return ITEMCHECK_FALSE;
	}

	// �Ȃ݂̂蒆�`�F�b�N
	if( Player_FormGet( icwk->player ) == HERO_FORM_SWIM ){
		return ITEMCHECK_FALSE;
	}

	// ���̏�
	if( MATR_IsBridge( icwk->NowAttr ) == TRUE ){
		return ITEMCHECK_FALSE;
	}

	{	// OBJ�Ɣ��Ȃ���
		u16	x, z;
		
		x = Player_NowGPosXGet( icwk->fsys->player );
		z = Player_NowGPosZGet( icwk->fsys->player );

		if( EventData_CheckIntoUGPos( icwk->fsys, x, z ) == FALSE ){
			return ITEMCHECK_FALSE;
		}
	}

	return ITEMCHECK_TRUE;
}


//============================================================================================
//	004:���]��
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F���]��
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Cycle( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = GMEVENT_ItemUseCycle;
	mwk->app_wk   = NULL;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F���]��
 *
 * @param	wk	�֗��{�^�����[�N
 *
 * @return	FALSE�i�֗��{�^�����[�N����j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_Cycle( CONV_WORK * wk )
{
	FieldEvent_Set( wk->fsys, GMEVENT_ItemUseCycle, NULL );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�C�x���g�F���]��
 *
 * @param	event	�t�B�[���h�C�x���g�p�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_ItemUseCycle( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	int * seq;

	fsys = FieldEvent_GetFieldSysWork( event );
	seq = FieldEvent_GetSeqWork( event );

	switch (*seq) {
	case 0:
		(*seq) ++;
		break;
	case 1:
		if( Player_FormGet( fsys->player ) == HERO_FORM_CYCLE ){

			FieldOBJ_MovePauseClear( Player_FieldOBJGet( fsys->player ) );
			Player_RequestSet( fsys->player, HERO_REQBIT_NORMAL );
			Player_Request( fsys->player );

			//��Ɍ`���߂��Ă���ABGM�������ĂԁI(060803)
			Snd_FieldBgmSetSpecial( fsys, 0 );					//�N���A
			Snd_FadeOutNextPlayCall(
				fsys, Snd_FieldBgmNoGet(fsys,fsys->location->zone_id), BGM_FADE_FIELD_MODE );
		}else{

			//���BGM�������Ă�ł���A�`������]�Ԃɂ���I(060803)
			Snd_FieldBgmSetSpecial( fsys, SEQ_BICYCLE );		//�Z�b�g
			Snd_FadeOutNextPlayCall( fsys, SEQ_BICYCLE, BGM_FADE_FIELD_MODE );

			FieldOBJ_MovePauseClear( Player_FieldOBJGet( fsys->player ) );
			Player_RequestSet( fsys->player, HERO_REQBIT_CYCLE );
			Player_Request( fsys->player );

			//���]�ԏ������h�ꑐ�N���A
			SwayGrass_InitSwayGrass(fsys->SwayGrass);
		}
		(*seq) ++;
		break;
	case 2:
		//FieldOBJ_MovePauseClear( Player_FieldOBJGet( fsys->player ) );
		//Player_Request( fsys->player );
		(*seq) ++;
		break;
	case 3:
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�`�F�b�N�֐��F���]��
 *
 * @param	icwk	�A�C�e���g�p�`�F�b�N���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Cycle( const ITEMCHECK_WORK * icwk )
{
	// �A��������͎g�p�s��
	if( icwk->Companion == TRUE ){
		return ITEMCHECK_ERR_COMPANION;
	}

	// �T�C�N�����O���[�h�`�F�b�N
	if( Player_MoveBitCheck_CyclingRoad( icwk->player ) == TRUE ){
		return ITEMCHECK_ERR_CYCLE_OFF;
	}

	{	// ��{��
		FIELD_OBJ_PTR	fldobj = Player_FieldOBJGet( icwk->player );
		if( FieldOBJ_MapAttrKindCheck_BridgeV( fldobj, icwk->NowAttr ) == TRUE ||
			FieldOBJ_MapAttrKindCheck_BridgeH( fldobj, icwk->NowAttr ) == TRUE ){
			return ITEMCHECK_ERR_CYCLE_OFF;
		}
	}

	// ������ / �� / ����
	if( MATR_IsLongGrass( icwk->NowAttr ) == TRUE ||
		MATR_IsSwamp( icwk->NowAttr ) == TRUE ||
		MATR_IsSwampGrass( icwk->NowAttr ) == TRUE ){
		return ITEMCHECK_FALSE;
	}

	// �]�[���`�F�b�N
	if( ZoneData_GetEnableBicycleFlag(icwk->zone_id) == FALSE ){
		return ITEMCHECK_FALSE;
	}

	//�Ȃ݂̂��Ԃ��ǂ���
	if( icwk->PlayerForm == HERO_FORM_SWIM ){
		return ITEMCHECK_FALSE;
	}

	return ITEMCHECK_TRUE;
}


//============================================================================================
//	005:�`���m�[�g
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F�`���m�[�g
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_FantasyNote( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	FieldFantasyNote_SetProc( fsys, NULL );
	FldMenu_AppWaitFuncSet( mwk, FldMenu_FantasyNoteEnd );
}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�`���m�[�g
 *
 * @param	wk	�֗��{�^�����[�N
 *
 * @return	TRUE�i�֗��{�^�����[�N��������Ȃ��j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_FantasyNote( CONV_WORK * wk )
{
	ConvFuncCallSet( wk, ConvCall_FantasyNote );
	return TRUE;
}

static void * ConvCall_FantasyNote( void * fsys )
{
	FieldFantasyNote_SetProc( fsys, NULL );
	return NULL;
}


//============================================================================================
//	006:�Z�}�V��
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F�Z�}�V��
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_WazaMachine( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	PLIST_DATA * pld;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );

	memset( pld, 0, sizeof(PLIST_DATA) );
	pld->pp     = SaveData_GetTemotiPokemon( fsys->savedata );
	pld->myitem = SaveData_GetMyItem( fsys->savedata );
	pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
	pld->cfg = SaveData_GetConfig( fsys->savedata );
	pld->scwk = &mwk->skill_check;
	pld->type = PL_TYPE_SINGLE;
	pld->mode = PL_MODE_WAZASET;
	pld->fsys = fsys;
	pld->item = iuwk->item;
	pld->ret_sel = iuwk->use_poke;
	pld->waza = GetWazaNoItem( iuwk->item );
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	mwk->app_wk = pld;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_PokeListEnd );
}


//============================================================================================
//	007:���[��
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F���[��
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Mail( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	MAIL_PARAM * mail;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	mail = FieldMailView_InitCall(
				fsys, MAILBLOCK_NULL, ItemMailDesignGet(iuwk->item), HEAPID_WORLD );

	mwk->tmp_wk = FieldMenu_MailWorkMake( iuwk->item, FM_MAIL_MODE_VIEW, 0 );
	mwk->app_wk = mail;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_MailEnd );
}


//============================================================================================
//	008:���̂�
//============================================================================================
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Kinomi(const ITEMCHECK_WORK * icwk)
{
	return ITEMCHECK_TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F���̂�
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Kinomi( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	FIELD_OBJ_PTR	obj;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	if (icwk->SeedInfo & SEEDITEMCHK_USE_SEED) {
		SetUpItemScript(iuwk, icwk, SCRID_KINOMI_BAG_KINOMI);
	} else {
		ItemUse_Recover( iuwk, icwk );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ���̂ݎg�p�^�C�v�擾
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @retval	"TRUE = ���߂�"
 * @retval	"FALSE = ����ȊO"
 */
//--------------------------------------------------------------------------------------------
BOOL ItemUse_KinomiTypeCheck( const ITEMCHECK_WORK * icwk )
{
	if (icwk->SeedInfo & SEEDITEMCHK_USE_SEED) {
		return TRUE;
	}
	return FALSE;
}


//============================================================================================
//	009:�|���g�P�[�X
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F�|���g�P�[�X
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_PrtCase( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	PORUTO_PARAM * prt;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	prt  = FieldPorutoCase_InitCall( fsys, HEAPID_WORLD );

	mwk->app_wk = prt;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_PorutoCaseEnd );
}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�|���g�P�[�X
 *
 * @param	wk	�֗��{�^�����[�N
 *
 * @return	TRUE�i�֗��{�^�����[�N��������Ȃ��j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_PrtCase( CONV_WORK * wk )
{
	ConvFuncCallSet( wk, ConvCall_PrtCase );
	return TRUE;
}

static void * ConvCall_PrtCase( void * fsys )
{
	return FieldPorutoCase_InitCall( fsys, HEAPID_WORLD );
}

//============================================================================================
//	010:�F�B�蒠
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F�F�B�蒠
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_FriendBook( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	WifiNote_SetProc( fsys, fsys->savedata );

	mwk->app_wk = NULL;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_FriendBookEnd );
}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�F�B�蒠
 *
 * @param	wk	�֗��{�^�����[�N
 *
 * @return	TRUE�i�֗��{�^�����[�N��������Ȃ��j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_FriendBook( CONV_WORK * wk )
{
	ConvFuncCallSet( wk, ConvCall_FriendBook );
	return TRUE;
}

static void * ConvCall_FriendBook( void * fsys )
{
	WifiNote_SetProc( fsys, ((FIELDSYS_WORK *)fsys)->savedata );
	return NULL;
}


//============================================================================================
//	011:�|�P�T�[�`���[
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F�|�P�T�[�`���[
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_PokeSearcher( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	int *seq;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	seq = sys_AllocMemoryLo(HEAPID_WORLD,sizeof(int));
	(*seq) = 0;	
	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = SwayGrass_SetupEvent;
	mwk->app_wk   = seq;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�|�P�T�[�`���[
 *
 * @param	wk		�֗��{�^�����[�N
 *
 * @return	FALSE�i�֗��{�^�����[�N����j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_PokeSearcher( CONV_WORK * wk )
{
	int * seq = sys_AllocMemoryLo(HEAPID_WORLD,sizeof(int));
	*seq = 0;
	FieldEvent_Set( wk->fsys, SwayGrass_SetupEvent, seq );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�`�F�b�N�֐��F�|�P�T�[�`���[
 *
 * @param	icwk	�A�C�e���g�p�`�F�b�N���[�N
 *
 * @return	BOOL	TRUE:�g����@FALSE:�g���Ȃ�
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_PokeSearcher( const ITEMCHECK_WORK * icwk )
{
	//�A��������͎g�p�s��
	if( icwk->Companion == TRUE ){
		return ITEMCHECK_ERR_COMPANION;
	}
	//���]�ԏ���Ă�Ƃ��͎g�p�s��
	if ( Player_FormGet( icwk->fsys->player ) == HERO_FORM_CYCLE ){
		return ITEMCHECK_FALSE;
	}
	//���A�g���r���[�g�ȊO�͎g�p�s��
	if (!MATR_IsGrass(icwk->NowAttr)){
		return ITEMCHECK_FALSE;
	}
	return ITEMCHECK_TRUE;
}


//============================================================================================
//	012:���傤��
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���g�p�֐��F���傤��
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Zyouro( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	SetUpItemScript(iuwk, icwk, SCRID_KINOMI_BAG_ZYOURO);
}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F���傤��
 *
 * @param	wk		�֗��{�^�����[�N
 *
 * @return	FALSE�i�֗��{�^�����[�N����j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_Zyouro( CONV_WORK * wk )
{
	SetUpItemScriptCnv( wk, SCRID_KINOMI_BAG_ZYOURO );
	return FALSE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���g�p�`�F�b�N�֐��F���傤��
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Zyouro( const ITEMCHECK_WORK * icwk )
{
	// �A��������͎g�p�s��
	if( icwk->Companion == TRUE ){
		return ITEMCHECK_ERR_COMPANION;
	}

	if (icwk->SeedInfo & SEEDITEMCHK_USE_ZYOURO) {
		return ITEMCHECK_TRUE;
	} else {
		return ITEMCHECK_FALSE;
	}
}

//============================================================================================
//	013:�R���V
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���g�p�֐��F�R���V
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Compost( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	SetUpItemScript(iuwk, icwk, SCRID_KINOMI_BAG_COMPOST);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���g�p�`�F�b�N�֐��F�R���V
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Compost( const ITEMCHECK_WORK * icwk )
{
	if (icwk->SeedInfo & SEEDITEMCHK_USE_COMPOST) {
		return ITEMCHECK_TRUE;
	} else {
		return ITEMCHECK_FALSE;
	}
}

//============================================================================================
//	014:�Â���
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���g�p�֐��F�Â���
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_SweetHoney( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	EVENT_AMAIKAORI_EFF_WORK	*work;
	int size;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );

	FieldEvent_Cmd_SetMapProc( fsys );
	
	size = FLDMAP_Amaikaori_WorkSize();
	work = sys_AllocMemoryLo( HEAPID_WORLD, size );
	memset(work, 0, size);
	
	mwk->app_func = FLDMAP_AmaikaoriEvent;
	mwk->app_wk   = work;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
	//�A�C�e�����炷
	MyItem_SubItem( SaveData_GetMyItem(fsys->savedata), iuwk->item, 1, HEAPID_WORLD );	
}


//============================================================================================
//	015:�o�g���T�[�`���[
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���g�p�֐��F�o�g���T�[�`���[
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_BtlSearcher( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	SetUpItemScript(iuwk, icwk, SCRID_BTL_SEARCHER);
}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�o�g���T�[�`���[
 *
 * @param	wk		�֗��{�^�����[�N
 *
 * @return	FALSE�i�֗��{�^�����[�N����j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_BtlSearcher( CONV_WORK * wk )
{
	SetUpItemScriptCnv( wk, SCRID_BTL_SEARCHER );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�`�F�b�N�֐��F�o�g���T�[�`���[
 *
 * @param	icwk	�A�C�e���g�p�`�F�b�N���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_BtlSearcher( const ITEMCHECK_WORK * icwk )
{
	if( ZoneData_IsSinouField(icwk->zone_id) ){
		return ITEMCHECK_TRUE;
	}
	return ITEMCHECK_FALSE;
}


//============================================================================================
//	016:�{�����ފ�
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���g�p�֐��F�{�����ފ�
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_FishingRodBad( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	
	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	
	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = GMEVENT_Fishing;
	mwk->app_wk   = EventWorkSet_Fishing( fsys, HEAPID_WORLD, FISHINGROD_BAD );
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�{�����ފ�
 * @param	wk	�֗��{�^�����[�N
 * @return	FALSE�i�֗��{�^�����[�N����j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_FishingRodBad( CONV_WORK * wk )
{
	void *work = EventWorkSet_Fishing( wk->fsys, HEAPID_FIELD, FISHINGROD_BAD );
	FieldEvent_Set( wk->fsys, GMEVENT_Fishing, work );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���g�p�֐��F�ǂ��ފ�
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_FishingRodGood( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	
	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	
	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = GMEVENT_Fishing;
	mwk->app_wk   = EventWorkSet_Fishing( fsys, HEAPID_WORLD, FISHINGROD_GOOD );
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�ǂ��ފ�
 * @param	wk	�֗��{�^�����[�N
 * @return	FALSE�i�֗��{�^�����[�N����j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_FishingRodGood( CONV_WORK * wk )
{
	void *work = EventWorkSet_Fishing( wk->fsys, HEAPID_FIELD, FISHINGROD_GOOD );
	FieldEvent_Set( wk->fsys, GMEVENT_Fishing, work );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���g�p�֐��F�����ފ�
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_FishingRodGreat( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	
	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	
	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = GMEVENT_Fishing;
	mwk->app_wk   = EventWorkSet_Fishing( fsys, HEAPID_WORLD, FISHINGROD_GREAT );
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�����ފ�
 * @param	wk	�֗��{�^�����[�N
 * @return	FALSE�i�֗��{�^�����[�N����j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_FishingRodGreat( CONV_WORK * wk )
{
	void *work = EventWorkSet_Fishing( wk->fsys, HEAPID_FIELD, FISHINGROD_GREAT );
	FieldEvent_Set( wk->fsys, GMEVENT_Fishing, work );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�`�F�b�N�֐��F�ފ�
 *
 * @param	icwk	�A�C�e���g�p�`�F�b�N���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_FishingRod( const ITEMCHECK_WORK * icwk )
{
	// �A��������͎g�p�s��
	if( icwk->Companion == TRUE ){
		return ITEMCHECK_ERR_COMPANION;
	}

	// �ڂ̑O����
	if( MATR_IsWater(icwk->FrontAttr) == TRUE ){
		// ���̏�ɂ��Ȃ����OK
		if( MATR_IsBridge( icwk->NowAttr ) == TRUE ||
			MATR_IsBridgeFlag( icwk->NowAttr ) == TRUE ){
			FIELD_OBJ_PTR	fldobj = Player_FieldOBJGet( icwk->player );
			if( FieldOBJ_StatusBitCheck_Bridge(fldobj) == TRUE ){
				return ITEMCHECK_FALSE;
			}
		}
		return ITEMCHECK_TRUE;
	}

	return ITEMCHECK_FALSE;
}


//============================================================================================
//	019:�o�b�O���Ŏg�p���铹��
//		�R�C���P�[�X�A�A�N�Z�T���[����A�V�[������A�|�C���g�J�[�h
//============================================================================================
typedef struct {
	GF_BGL_BMPWIN win;	// �E�B���h�E�f�[�^
	STRBUF * msg;		// ���b�Z�[�W
	u16	midx;			// ���b�Z�[�W�C���f�b�N�X
	u16	seq;			// �V�[�P���X
}BAGMSG_WORK;

#define	BAGMSG_TMP_SIZ		( 128 )


//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�o�b�O���Ŏg�p���铹��
 *
 * @param	wk	�֗��{�^�����[�N
 *
 * @return	FALSE�i�֗��{�^�����[�N������j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_BagMsgItem( CONV_WORK * wk )
{
	BAGMSG_WORK * bmwk = sys_AllocMemory( HEAPID_WORLD, sizeof(BAGMSG_WORK) );
	bmwk->seq = 0;

	bmwk->msg = STRBUF_Create( BAGMSG_TMP_SIZ, HEAPID_WORLD );
	BAG_ItemUseMsgSet(
		wk->fsys->savedata, bmwk->msg,
		MyItem_CnvButtonItemGet( SaveData_GetMyItem(wk->fsys->savedata) ), HEAPID_WORLD );

	FieldEvent_Set( wk->fsys, GMEVENT_BagMsgItem, bmwk );
	return FALSE;
}

static BOOL GMEVENT_BagMsgItem( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	BAGMSG_WORK * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	switch( wk->seq ){
	case 0:
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );

/*
		wk->msg = STRBUF_Create( BAGMSG_TMP_SIZ, HEAPID_WORLD );

		BAG_ItemUseMsgSet(
			fsys->savedata, wk->msg,
			MyItem_CnvButtonItemGet( SaveData_GetMyItem(fsys->savedata) ), HEAPID_WORLD );
*/

		FldTalkBmpAdd( fsys->bgl, &wk->win, FLD_MBGFRM_FONT );
		{
			const CONFIG * cfg = SaveData_GetConfig( fsys->savedata );
			FieldTalkWinPut( &wk->win, cfg );
			wk->midx = FieldTalkMsgStart( &wk->win, wk->msg, cfg, 1 );
		}
		wk->seq++;
		break;

	case 1:
		if( FldTalkMsgEndCheck( wk->midx ) == 1 ){
			if(sys.trg & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_LEFT|PAD_KEY_RIGHT|PAD_BUTTON_A|PAD_BUTTON_B)){
				BmpTalkWinClear( &wk->win, WINDOW_TRANS_ON );
				wk->seq++;
			}
		}
		break;

	case 2:
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		GF_BGL_BmpWinDel( &wk->win );
		STRBUF_Delete( wk->msg );
		sys_FreeMemoryEz( wk );
		return TRUE;
	}

	return FALSE;
}


//============================================================================================
//	020:�i��
//============================================================================================

static void ItemUse_Evolution( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk )
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	PLIST_DATA * pld;

	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	pld  = sys_AllocMemory( HEAPID_WORLD, sizeof(PLIST_DATA) );

	memset( pld, 0, sizeof(PLIST_DATA) );
	pld->pp     = SaveData_GetTemotiPokemon( fsys->savedata );
	pld->myitem = SaveData_GetMyItem( fsys->savedata );
	pld->mailblock = SaveData_GetMailBlock( fsys->savedata );
	pld->cfg = SaveData_GetConfig( fsys->savedata );
	pld->tvwk = SaveData_GetTvWork( fsys->savedata );
	pld->scwk = &mwk->skill_check;
	pld->type = PL_TYPE_SINGLE;
	pld->mode = PL_MODE_SHINKA;
	pld->item = iuwk->item;
	pld->ret_sel = iuwk->use_poke;
	GameSystem_StartSubProc( fsys, &PokeListProcData, pld );

	mwk->app_wk = pld;
	FldMenu_AppWaitFuncSet( mwk, FldMenu_PokeListEnd );
}


//============================================================================================
//	021	:�������̕R
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	�A�C�e���g�p�֐��F�������̕R
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Ananuke( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	FIELDSYS_WORK * fsys;
	FLD_MENU * mwk;
	
	fsys = FieldEvent_GetFieldSysWork( iuwk->event );
	mwk  = FieldEvent_GetSpecialWork( iuwk->event );
	
	FieldEvent_Cmd_SetMapProc( fsys );
	mwk->app_func = GMEVENT_AnanukeMapChangeInit;
	mwk->app_wk   = NULL;
	mwk->seq      = FLD_MENU_SEQ_BLACK_IN_EVCHG;
	//�A�C�e�����炷
	MyItem_SubItem( SaveData_GetMyItem(fsys->savedata), iuwk->item, 1, HEAPID_WORLD );
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�`�F�b�N�֐��F�������̕R
 *
 * @param	icwk	�A�C�e���g�p�`�F�b�N���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Ananuke( const ITEMCHECK_WORK * icwk )
{
	// �A��������͎g�p�s��
	if( icwk->Companion == TRUE ){
		return ITEMCHECK_ERR_COMPANION;
	}

	if( ZoneData_IsDungeon(icwk->zone_id) == TRUE &&
		ZoneData_GetEnableEscapeFlag(icwk->zone_id) == TRUE ){
		return ITEMCHECK_TRUE;
	}

	return ITEMCHECK_FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�������̕R���[�N���������������C�x���g��
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_AnanukeMapChangeInit( GMEVENT_CONTROL *event )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	void *work = EventWorkSet_AnanukeMapChange( fsys, HEAPID_WORLD );
	FieldEvent_Change( event, GMEVENT_AnanukeMapChange, work );
	return( FALSE );
}


//============================================================================================
//	022:�Ă񂩂��̂ӂ�
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�֐��F�Ă񂩂��̂ӂ�
 *
 * @param	iuwk	�A�C�e���g�p���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ItemUse_Tenkainofue( ITEMUSE_WORK * iuwk, const ITEMCHECK_WORK * icwk)
{
	SetUpItemScript(iuwk, icwk, SCRID_TENKAINOFUE);

}

//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���g�p�֐��F�Ă񂩂��̂ӂ�
 *
 * @param	wk		�֗��{�^�����[�N
 *
 * @return	FALSE�i�֗��{�^�����[�N����j
 */
//--------------------------------------------------------------------------------------------
static BOOL ItemCnv_Tenkainofue( CONV_WORK * wk )
{
	SetUpItemScriptCnv( wk, SCRID_TENKAINOFUE );
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���g�p�`�F�b�N�֐��F�Ă񂩂��̂ӂ�
 *
 * @param	icwk	�A�C�e���g�p�`�F�b�N���[�N
 *
 * @return	BOOL	TRUE:�g����@FALSE:�g���Ȃ�
 */
//--------------------------------------------------------------------------------------------
static u32 ItemUseCheck_Tenkainofue( const ITEMCHECK_WORK * icwk )
{
	EVENTWORK * ev = SaveData_GetEventWork(icwk->fsys->savedata);
	//�Q�[���N���A�ォ�H
	if (SysFlag_GameClearCheck(ev) == FALSE) {
		return ITEMCHECK_FALSE;
	}
	//�z�z�C�x���g�t���O�͐���ɐݒ肳��Ă��邩�H
	if (SysWork_HaihuEventWorkCheck(ev, HAIHUEVENT_ID_D05) == FALSE) {
		return ITEMCHECK_FALSE;
	}
	//�S���}�ӓ���ォ?
	if (ZukanWork_GetZenkokuZukanFlag(SaveData_GetZukanWork(icwk->fsys->savedata)) == FALSE) {
		return ITEMCHECK_FALSE;
	}

	if ( !ZoneData_IsUseTenkainofueZone(icwk->zone_id) ){
		return ITEMCHECK_FALSE;
	}
	
	return ITEMCHECK_TRUE;
}












//============================================================================================
//	�֗��{�^��
//============================================================================================
// ��ʐ؂�ւ��C�x���g�V�[�P���X
enum {
	SEQ_FADEOUT_SET = 0,	// �t�F�[�h�A�E�g�Z�b�g
	SEQ_FADEOUT_WAIT,		// �t�F�[�h�A�E�g�҂�
	SEQ_END_WAIT,			// �T�u�v���Z�X�I���҂�
	SEQ_RCV_WAIT,			// �t�B�[���h�}�b�v�v���Z�X�J�n�҂�
	SEQ_FADEIN_WAIT,		// �t�F�[�h�C���҂�
};

static void ItemCnv_ErrorMsgSet( CONV_WORK * wk, u32 err );


//--------------------------------------------------------------------------------------------
/**
 * �֗��{�^���N������
 *
 * @param	repw	�t�B�[���h���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
BOOL FieldConvButtonEventInit( FIELDSYS_WORK * repw )
{
	CONV_WORK * wk;
	ITEMCNV_FUNC	cnv;
	ITEMCHECK_FUNC	check;
	u16	item;
	u16	id;
	BOOL	ret;

	// �o�g���^���[�̃T�����ł͎g�p�ł��Ȃ�
	if( BtlTower_IsSalon(repw) == TRUE ){ return FALSE; }

	// �|�P�p�[�N�ł͎g�p�ł��Ȃ�
	if( SysFlag_PokeParkCheck(SaveData_GetEventWork(repw->savedata)) == TRUE ){
		return FALSE;
	}

	item  = (u16)MyItem_CnvButtonItemGet( SaveData_GetMyItem(repw->savedata) );
//	if( item == 0 ){ return FALSE; }

	id    = (u16)ItemParamGet( item, ITEM_PRM_FIELD, HEAPID_WORLD );
	check = (ITEMCHECK_FUNC)ItemUse_FuncGet( ITEMUSE_PRM_CHECKFUNC, id );
	cnv   = (ITEMCNV_FUNC)ItemUse_FuncGet( ITEMUSE_PRM_CNVFUNC, id );

	if( cnv == NULL ){ return FALSE; }	// �֗��{�^������g�p�ł��Ȃ�

	wk = sys_AllocMemory( HEAPID_WORLD, sizeof(CONV_WORK) );
	memset( wk, 0, sizeof(CONV_WORK) );
	wk->fsys = repw;
	wk->item = item;
	ItemUse_CheckWorkMake( repw, &wk->icwk );

	ret = FALSE;
	if( check == NULL ){
		ret = cnv( wk );
	}else{
		u32 err = check( &wk->icwk );
		if( err == ITEMCHECK_TRUE ){
			ret = cnv( wk );
		}else{
			ItemCnv_ErrorMsgSet( wk, err );
		}
	}

	if( ret == FALSE ){
		sys_FreeMemoryEz( wk );
	}

	return TRUE;
}


static void ItemCnv_ErrorMsgSet( CONV_WORK * wk, u32 err )
{
	BAGMSG_WORK * bmwk = sys_AllocMemory( HEAPID_WORLD, sizeof(BAGMSG_WORK) );
	bmwk->seq = 0;

	bmwk->msg = STRBUF_Create( BAGMSG_TMP_SIZ, HEAPID_WORLD );

	BAG_ItemUseErrorMsgSet(
		SaveData_GetMyStatus( wk->fsys->savedata ), bmwk->msg, wk->item, err, HEAPID_WORLD );

	FieldEvent_Set( wk->fsys, GMEVENT_BagMsgItem, bmwk );
}


//--------------------------------------------------------------------------------------------
/**
 * ��ʐ؂�ւ��A�C�e���p���ʃC�x���g
 *
 * @param	event
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static BOOL GMEVENT_ConvButtonCommon( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * fsys;
	CONV_WORK * wk;

	fsys = FieldEvent_GetFieldSysWork( event );
	wk   = FieldEvent_GetSpecialWork( event );

	switch( wk->seq ){
	case SEQ_FADEOUT_SET:	// �t�F�[�h�A�E�g�Z�b�g
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKOUT );
		wk->seq = SEQ_FADEOUT_WAIT;
		break;

	case SEQ_FADEOUT_WAIT:	// �t�F�[�h�A�E�g�҂�
		if( WIPE_SYS_EndCheck() ){
			wk->app_wk = wk->call( fsys );
			wk->seq = SEQ_END_WAIT;
		}
		break;

	case SEQ_END_WAIT:		// �T�u�v���Z�X�I���҂�
		if( FieldEvent_Cmd_WaitSubProcEnd( fsys ) ) {
			break;
		}
		if( wk->app_wk != NULL ){
			if(wk->call == ConvCall_PrtCase){
				//�|���g�P�[�X�̎��͐�p����������֐����Ă� 06.07.05 iwasawa
				PorutoSys_ReleaseCallWork(wk->app_wk);
			}else{
				sys_FreeMemoryEz( wk->app_wk );
			}
		}
		FieldEvent_Cmd_SetMapProc( fsys );
		wk->seq = SEQ_RCV_WAIT;
		break;

	case SEQ_RCV_WAIT:		// �t�B�[���h�}�b�v�v���Z�X�J�n�҂�
		if( FieldEvent_Cmd_WaitMapProcStart(fsys) ) {
			FieldOBJSys_MovePauseAll( fsys->fldobjsys );
			FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
			wk->seq = SEQ_FADEIN_WAIT;
		}
		break;

	case SEQ_FADEIN_WAIT:	// �t�F�[�h�C���҂�
		if( WIPE_SYS_EndCheck() ){
			FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
			sys_FreeMemoryEz( wk );
			return TRUE;
		}
	}

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * ��ʐ؂�ւ��A�C�e���p���ʃC�x���g�Z�b�g
 *
 * @param	wk		�֗��{�^�����[�N
 * @param	call	�t�F�[�h�A�E�g��ɌĂ΂�鏈��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ConvFuncCallSet( CONV_WORK * wk, CNVFUNC_CALL call )
{
	wk->call = call;
	FieldEvent_Set( wk->fsys, GMEVENT_ConvButtonCommon, wk );
}
