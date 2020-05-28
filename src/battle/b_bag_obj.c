//============================================================================================
/**
 * @file	b_bag_obj.c
 * @brief	�퓬�p�o�b�O��� OBJ�֘A
 * @author	Hiroyuki Nakamura
 * @date	05.02.15
 */
//============================================================================================
#include "common.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "battle/battle_common.h"
#include "battle/fight_tool.h"
#include "itemtool/item.h"
#include "b_app_tool.h"

#include "../src/demo/ev_pokeselect.naix"

#define	B_BAG_OBJ_H_GLOBAL
#include "b_bag.h"
#include "b_bag_main.h"
#include "b_bag_obj.h"
#include "b_bag_item.h"


//============================================================================================
//	�萔��`
//============================================================================================
#define	CLACT_ID_COMMON		( 46263 )	// ���̉�ʂŎg�p����Z���A�N�^�[��ID

// �L�������\�[�XID
enum {
	CHR_ID_ITEM1 = CLACT_ID_COMMON,		// �A�C�e���A�C�R���F�P
	CHR_ID_ITEM2,						// �A�C�e���A�C�R���F�Q
	CHR_ID_ITEM3,						// �A�C�e���A�C�R���F�R
	CHR_ID_ITEM4,						// �A�C�e���A�C�R���F�S
	CHR_ID_ITEM5,						// �A�C�e���A�C�R���F�T
	CHR_ID_ITEM6,						// �A�C�e���A�C�R���F�U
	CHR_ID_GETDEMO,						// �ߊl�f���J�[�\��
	CHR_ID_CURSOR,						// �J�[�\��

	CHR_ID_MAX = CHR_ID_CURSOR - CLACT_ID_COMMON + 1
};

// �p���b�g���\�[�XID
enum {
	PAL_ID_ITEM1 = CLACT_ID_COMMON,		// �A�C�e���A�C�R���F�P
	PAL_ID_ITEM2,						// �A�C�e���A�C�R���F�Q
	PAL_ID_ITEM3,						// �A�C�e���A�C�R���F�R
	PAL_ID_ITEM4,						// �A�C�e���A�C�R���F�S
	PAL_ID_ITEM5,						// �A�C�e���A�C�R���F�T
	PAL_ID_ITEM6,						// �A�C�e���A�C�R���F�U
	PAL_ID_GETDEMO,						// �ߊl�f���J�[�\��
	PAL_ID_CURSOR,						// �J�[�\��

	PAL_ID_MAX = PAL_ID_CURSOR - CLACT_ID_COMMON + 1
};

// �Z�����\�[�XID
enum {
	CEL_ID_ITEM = CLACT_ID_COMMON,		// �A�C�e���A�C�R��
	CEL_ID_GETDEMO,						// �ߊl�f���J�[�\��
	CEL_ID_CURSOR,						// �J�[�\��

	CEL_ID_MAX = CEL_ID_CURSOR - CLACT_ID_COMMON + 1
};

// �Z���A�j�����\�[�XID
enum {
	ANM_ID_ITEM = CLACT_ID_COMMON,		// �A�C�e���A�C�R��
	ANM_ID_GETDEMO,						// �ߊl�f���J�[�\��
	ANM_ID_CURSOR,						// �J�[�\��

	ANM_ID_MAX = ANM_ID_CURSOR - CLACT_ID_COMMON + 1
};

#define	CURSOR_CLA_MAX		( 5 )		// �J�[�\����OBJ��
#define	FINGER_CLA_MAX		( 1 )		// �w�J�[�\����OBJ��


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void BBAG_ClactResManInit( BBAG_WORK * wk );
static void BBAG_ClactItemLoad( BBAG_WORK * wk );
static void BBAG_ItemIconCharChg( BBAG_WORK * wk, u16 item, u32 res_id );
static void BBAG_ItemIconPlttChg( BBAG_WORK * wk, u16 item, u16 pos, u32 res_id );
static void BBAG_ClactGetDemoLoad( BBAG_WORK * wk );
static void BBAG_ClactAddAll( BBAG_WORK * wk );
static void BBAG_Page1ObjSet( BBAG_WORK * wk );
static void BBAG_Page2ObjSet( BBAG_WORK * wk );
static void BBAG_Page3ObjSet( BBAG_WORK * wk );
static void BBAG_ClactCursorAdd( BBAG_WORK * wk );
static void BBAG_CursorDel( BBAG_WORK * wk );
static void BBAG_ClactGetDemoCursorAdd( BBAG_WORK * wk );
static void BBAG_GetDemoCursorDel( BBAG_WORK * wk );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// �y�[�W�P�̃|�P�����A�C�R���̍��W
static const int P1_ItemIconPos[2] = { 24, 178 };

// �y�[�W�Q�̃A�C�e���A�C�R���̍��W
static const int P2_ItemIconPos[][2] =
{
	{  44,  45 }, { 172,  45 },
	{  44,  93 }, { 172,  93 },
	{  44, 141 }, { 172, 141 },
};

// �y�[�W�R�̃|�P�����A�C�R���̍��W
static const int P3_ItemIconPos[2] = { 40, 44 };

// �Z���A�N�^�[�̃f�[�^
static const int ClactDat[][5] =
{	// char, pal, cell, anm, obj_pri
	{ CHR_ID_ITEM1, PAL_ID_ITEM1, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
	{ CHR_ID_ITEM2, PAL_ID_ITEM2, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
	{ CHR_ID_ITEM3, PAL_ID_ITEM3, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
	{ CHR_ID_ITEM4, PAL_ID_ITEM4, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
	{ CHR_ID_ITEM5, PAL_ID_ITEM5, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
	{ CHR_ID_ITEM6, PAL_ID_ITEM6, CEL_ID_ITEM, ANM_ID_ITEM, 1 },
//	{ CHR_ID_GETDEMO, PAL_ID_GETDEMO, CEL_ID_GETDEMO, ANM_ID_GETDEMO, 0 }
};



//--------------------------------------------------------------------------------------------
/**
 * �퓬�p�o�b�OOBJ������
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_ObjInit( BBAG_WORK * wk )
{
	BBAG_ClactResManInit( wk );
	BBAG_ClactItemLoad( wk );
//	BBAG_ClactGetDemoLoad( wk );
	BBAG_ClactAddAll( wk );
	BBAG_ClactCursorAdd( wk );
	BBAG_ClactGetDemoCursorAdd( wk );

	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//--------------------------------------------------------------------------------------------
/**
 * ���\�[�X�}�l�[�W���[������
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BBAG_ClactResManInit( BBAG_WORK * wk )
{
	TCATS_RESOURCE_NUM_LIST	crnl = { CHR_ID_MAX, PAL_ID_MAX, CEL_ID_MAX, ANM_ID_MAX, 0, 0 };
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	wk->crp = CATS_ResourceCreate( csp );
	CATS_ClactSetInit( csp, wk->crp, BBAG_CA_MAX+CURSOR_CLA_MAX+FINGER_CLA_MAX );
	CATS_ResourceManagerInit( csp, wk->crp, &crnl );
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���A�C�R���̃O���t�B�b�N���[�h
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BBAG_ClactItemLoad( BBAG_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	for( i=0; i<6; i++ ){
		// �L����
		CATS_LoadResourceCharArc(
			csp, wk->crp, ARC_ITEMICON,
			GetItemIndex(1,ITEM_GET_ICON_CGX), 0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_ITEM1+i );
		// �p���b�g
		CATS_LoadResourcePlttWorkArc(
			wk->pfd, FADE_SUB_OBJ, csp, wk->crp, ARC_ITEMICON,
			GetItemIndex(1,ITEM_GET_ICON_PAL), 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_ITEM1+i );
	}
	// �Z��
	CATS_LoadResourceCellArc( csp, wk->crp, ARC_ITEMICON, ItemIconCellGet(), 0, CEL_ID_ITEM );
	// �Z���A�j��
	CATS_LoadResourceCellAnmArc( csp, wk->crp, ARC_ITEMICON, ItemIconCAnmGet(), 0, ANM_ID_ITEM );
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���A�C�R���؂�ւ�
 *
 * @param	wk		���[�N
 * @param	cap		�Z���A�N�^�[�f�[�^
 * @param	item	�A�C�e���ԍ�
 * @param	res_id	�L�������\�[�XID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BBAG_ItemIconCharChg( BBAG_WORK * wk, u16 item, u32 res_id )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	CATS_ChangeResourceCharArc(
		csp, wk->crp, ARC_ITEMICON,
		GetItemIndex(item,ITEM_GET_ICON_CGX), 0, res_id );
}

static void BBAG_ItemIconPlttChg( BBAG_WORK * wk, u16 item, u16 pos, u32 res_id )
{
	PaletteWorkSet_Arc(
		wk->pfd, ARC_ITEMICON,
		GetItemIndex(item,ITEM_GET_ICON_PAL), wk->dat->heap,FADE_SUB_OBJ, 0x20, pos*16 );
}


//--------------------------------------------------------------------------------------------
/**
 * �ߊl�f���J�[�\���̃O���t�B�b�N���[�h
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
/*
static void BBAG_ClactGetDemoLoad( BBAG_WORK * wk )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// �L����
	CATS_LoadResourceCharArc(
		csp, wk->crp, ARC_EV_POKESELECT_GRA,
		NARC_ev_pokeselect_psel_cursol_NCGR, 0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_GETDEMO );
	// �p���b�g
	CATS_LoadResourcePlttWorkArc(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp, ARC_EV_POKESELECT_GRA,
		NARC_ev_pokeselect_psel_cursol_NCLR, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_GETDEMO );
	// �Z��
	CATS_LoadResourceCellArc(
		csp, wk->crp, ARC_EV_POKESELECT_GRA,
		NARC_ev_pokeselect_psel_cursol_NCER, 0, CEL_ID_GETDEMO );
	// �Z���A�j��
	CATS_LoadResourceCellAnmArc(
		csp, wk->crp, ARC_EV_POKESELECT_GRA,
		NARC_ev_pokeselect_psel_cursol_NANR, 0, ANM_ID_GETDEMO );
}
*/

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�ǉ��i�ʁj
 *
 * @param	wk		���[�N
 * @param	id		�ǉ�����Z���A�N�^�[��ID
 *
 * @return	�Z���A�N�^�[�f�[�^
 */
//--------------------------------------------------------------------------------------------
static CATS_ACT_PTR BBAG_ClactAdd( BBAG_WORK * wk, u32 id )
{
	TCATS_OBJECT_ADD_PARAM_S	prm;
	CATS_SYS_PTR	csp;

	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	prm.x = 0;
	prm.y = 0;
	prm.z = 0;

	prm.anm = 0;
	prm.pri = ClactDat[id][4];
	prm.pal = 0;
	prm.d_area = NNS_G2D_VRAM_TYPE_2DSUB;

	prm.id[0] = ClactDat[id][0];
	prm.id[1] = ClactDat[id][1];
	prm.id[2] = ClactDat[id][2];
	prm.id[3] = ClactDat[id][3];
	
	prm.bg_pri = 1;
	prm.vram_trans = 0;

	return CATS_ObjectAdd_S( csp, wk->crp, &prm );
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�ǉ��i�S�āj
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BBAG_ClactAddAll( BBAG_WORK * wk )
{
	u32	i;

	for( i=0; i<BBAG_CA_MAX; i++ ){
		wk->cap[i] = BBAG_ClactAdd( wk, i );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �퓬�p�o�b�OOBJ�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_ObjFree( BBAG_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	for( i=0; i<BBAG_CA_MAX; i++ ){
		CATS_ActorPointerDelete_S( wk->cap[i] );
	}

	BBAG_CursorDel( wk );
	BBAG_GetDemoCursorDel( wk );

	CATS_ResourceDestructor_S( csp, wk->crp );
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[��\�����č��W�ύX
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BBAG_ClactOn( CATS_ACT_PTR cap, const int x, const int y )
{
	CATS_ObjectEnableCap( cap, 1 );
	CATS_ObjectPosSetCap( cap, x, y );
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W���Ƃ�OBJ���Z�b�g
 *
 * @param	wk		���[�N
 * @param	page	�y�[�W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattleBag_PageObjSet( BBAG_WORK * wk, u32 page )
{
	u32	i;

	for( i=0; i<BBAG_CA_MAX; i++ ){
		CATS_ObjectEnableCap( wk->cap[i], 0 );
	}

	switch( page ){
	case BBAG_PAGE_POCKET:		// �|�P�b�g�I���y�[�W
		BBAG_Page1ObjSet( wk );
		break;
	case BBAG_PAGE_MAIN:		// �A�C�e���I���y�[�W
		BBAG_Page2ObjSet( wk );
		break;
	case BBAG_PAGE_ITEM:		// �A�C�e���g�p�y�[�W
		BBAG_Page3ObjSet( wk );
		break;
	}
}

#define	P1_GETDEMO_CURSOR_X		( 192 )
#define	P1_GETDEMO_CURSOR_Y		( 24 )
#define	P2_GETDEMO_CURSOR_X		( 64 )
#define	P2_GETDEMO_CURSOR_Y		( 16 )
#define	P3_GETDEMO_CURSOR_X		( 104 )
#define	P3_GETDEMO_CURSOR_Y		( 152 )

static void BBAG_Page1ObjSet( BBAG_WORK * wk )
{
	u16	item;

	if( wk->dat->used_item != 0 ){
		BBAG_ItemIconCharChg( wk, wk->dat->used_item, CHR_ID_ITEM1 );
		BBAG_ItemIconPlttChg( wk, wk->dat->used_item, 0, PAL_ID_ITEM1 );
		BBAG_ClactOn( wk->cap[BBAG_CA_ITEM1], P1_ItemIconPos[0], P1_ItemIconPos[1] );
	}
/*
	if( wk->dat->mode == BBAG_MODE_GETDEMO ){
		BBAG_ClactOn( wk->cap[BBAG_CA_GETDEMO], P1_GETDEMO_CURSOR_X, P1_GETDEMO_CURSOR_Y );
	}
*/
}

static void BBAG_Page2ObjSet( BBAG_WORK * wk )
{
	u32	i;
	u16	item;

	for( i=0; i<6; i++ ){
		item = BattleBag_PosItemCheck( wk, i );
		if( item == 0 ){ continue; }
		BBAG_ItemIconCharChg( wk, item, CHR_ID_ITEM1+i );
		BBAG_ItemIconPlttChg( wk, item, (u16)i, PAL_ID_ITEM1+i );
		BBAG_ClactOn( wk->cap[i], P2_ItemIconPos[i][0], P2_ItemIconPos[i][1] );
	}
/*
	if( wk->dat->mode == BBAG_MODE_GETDEMO ){
		BBAG_ClactOn( wk->cap[BBAG_CA_GETDEMO], P2_GETDEMO_CURSOR_X, P2_GETDEMO_CURSOR_Y );
	}
*/
}

static void BBAG_Page3ObjSet( BBAG_WORK * wk )
{
	u16	item;

	item = BattleBag_PosItemCheck( wk, wk->dat->item_pos[wk->poke_id] );
	BBAG_ItemIconCharChg( wk, item, CHR_ID_ITEM1 );
	BBAG_ItemIconPlttChg( wk, item, 0, PAL_ID_ITEM1 );
	BBAG_ClactOn( wk->cap[BBAG_CA_ITEM1], P3_ItemIconPos[0], P3_ItemIconPos[1] );
/*
	if( wk->dat->mode == BBAG_MODE_GETDEMO ){
		BBAG_ClactOn( wk->cap[BBAG_CA_GETDEMO], P3_GETDEMO_CURSOR_X, P3_GETDEMO_CURSOR_Y );
	}
*/
}


//============================================================================================
//	�J�[�\��
//============================================================================================
static void BBAG_ClactCursorAdd( BBAG_WORK * wk )
{
	CATS_SYS_PTR csp;
	BCURSOR_PTR	cursor;

	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	BCURSOR_ResourceLoad(
		csp, wk->crp, wk->pfd, CHR_ID_CURSOR, PAL_ID_CURSOR, CEL_ID_CURSOR, ANM_ID_CURSOR );

	cursor = BCURSOR_ActorCreate(
				csp, wk->crp, wk->dat->heap,
				CHR_ID_CURSOR, PAL_ID_CURSOR, CEL_ID_CURSOR, ANM_ID_CURSOR, 0, 1 );

	BAPP_CursorMvWkSetBCURSOR_PTR( wk->cmv_wk, cursor );
}

static void BBAG_CursorDel( BBAG_WORK * wk )
{
	BCURSOR_ActorDelete( BAPP_CursorMvWkGetBCURSOR_PTR( wk->cmv_wk ) );
	BCURSOR_ResourceFree(
		wk->crp, CHR_ID_CURSOR, PAL_ID_CURSOR, CEL_ID_CURSOR, ANM_ID_CURSOR );
}


// �|�P�b�g�I����ʈړ��e�[�u��
static const POINTER_WORK P1_CursorPosTbl[] =
{
	{   8,  16, 120,  72, 0, 1, 0, 2 },					// 0 : HP�񕜃|�P�b�g
	{   8,  88, 120, 144, 0, 4, 1, 3 },					// 1 : ��ԉ񕜃|�P�b�g
	{ 136,  16, 248,  72, 2, 3, 0, 2 },					// 2 : �{�[���|�P�b�g
	{ 136,  88, 248, 144, 2, 5, 1, 3 },					// 3 : �퓬�p�|�P�b�g
	{   8, 160, 200, 184, 1, 4, 4, 5 },					// 4 : �Ō�Ɏg�p��������
	{ 224, 160, 248, 184, BAPP_CMV_RETBIT|3, 5, 4, 5 },	// 5 : �߂�
//	{ 224, 160, 248, 184, BAPP_CMV_RETBIT|3, 5, 4, 5 },	// 5 : �߂�
};

// �A�C�e���I����ʈړ��e�[�u��
static const POINTER_WORK P2_CursorPosTbl[] =
{
	{   8,  16, 120,  48, 0, 2, 0, 1 },					// 0 : �A�C�e���P
	{ 136,  16, 248,  48, 1, 3, 0, 1 },					// 1 : �A�C�e���Q
	{   8,  64, 120,  96, 0, 4, 2, 3 },					// 2 : �A�C�e���R
	{ 136,  64, 248,  96, 1, 5, 2, 3 },					// 3 : �A�C�e���S
	{   8, 112, 120, 144, 2, BAPP_CMV_RETBIT|6, 4, 5 },	// 4 : �A�C�e���T
	{ 136, 112, 248, 144, 3, 8, 4, 5 },					// 5 : �A�C�e���U
	{   8, 160,  32, 184, 4, 6, 6, 7 },					// 6 : �O��
	{  48, 160,  72, 184, 4, 7, 6, 8 },					// 7 : ����
	{ 224, 160, 248, 184, 5, 8, 7, 8 },					// 8 : �߂�
};

// �A�C�e���I����ʈړ��e�[�u��
static const POINTER_WORK P3_CursorPosTbl[] =
{
	{   8, 160, 200, 184, 0, 0, 0, 1 },	// 0 : �g��
	{ 224, 160, 248, 184, 1, 1, 0, 1 },	// 1 : �߂�
};

static const POINTER_WORK * const CursorPosTable[] = {
	P1_CursorPosTbl,
	P2_CursorPosTbl,
	P3_CursorPosTbl,
};


#define	P1_DEF_CMV_TBL	( 0x3f )	// �y�[�W�P�̃f�t�H���g�J�[�\���ړ��e�[�u��
#define	P1_LST_CMV_TBL	( 0x2f )	// �y�[�W�P�̍Ō�Ɏg��������L�̃J�[�\���ړ��e�[�u��
#define	P2_DEF_CMV_TBL	( 0x100 )	// �y�[�W�Q�̃f�t�H���g�J�[�\���ړ��e�[�u��
#define	P2_PAGE_TBL		( 0xc0 )	// �y�[�W�Q�̃y�[�W�؂�ւ��J�[�\���ړ��e�[�u��

/*
void BBAG_P1CursorMvTblMake( BBAG_WORK * wk )
{
	if( wk->dat->used_item != 0 ){
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, P1_DEF_CMV_TBL );
	}else{
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, P1_LST_CMV_TBL );
	}
}
*/

void BBAG_P2CursorMvTblMake( BBAG_WORK * wk )
{
	u32	tbl;
	u32	i;

	tbl = P2_DEF_CMV_TBL;
	for( i=0; i<6; i++ ){
		if( wk->pocket[wk->poke_id][wk->dat->item_scr[wk->poke_id]*6+i].id == 0 ){
			continue;
		}
		tbl |= (1<<i);
	}
	if( wk->scr_max[wk->poke_id] != 0 ){
		tbl |= P2_PAGE_TBL;
	}
	BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, tbl );
}

void BattleBag_CursorMoveSet( BBAG_WORK * wk, u8 page )
{
	BAPP_CursorMvWkSetPoint( wk->cmv_wk, CursorPosTable[page] );

	switch( page ){
	case BBAG_PAGE_POCKET:		// �|�P�b�g�I���y�[�W
//		if( BAPP_CursorMvWkGetFlag( wk->cmv_wk ) == 1 ){
			BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->poke_id );
//		}
//		BBAG_P1CursorMvTblMake( wk );
		break;

	case BBAG_PAGE_MAIN:		// �A�C�e���I���y�[�W
//		if( BAPP_CursorMvWkGetFlag( wk->cmv_wk ) == 1 ){
			BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->dat->item_pos[wk->poke_id] );
//		}
//		BBAG_P2CursorMvTblMake( wk );
		break;

	case BBAG_PAGE_ITEM:		// �A�C�e���g�p�y�[�W
		break;
	}
}

void BattleBag_CursorOff( BBAG_WORK * wk )
{
	BAPP_CursorMvWkSetFlag( wk->cmv_wk, 0 );
	BAPP_CursorMvWkPosInit( wk->cmv_wk );
	BCURSOR_OFF( BAPP_CursorMvWkGetBCURSOR_PTR( wk->cmv_wk ) );
}



//============================================================================================
//	�ߊl�f���J�[�\��
//============================================================================================
/*
void BattleBag_GetDemoCursorAnm( BBAG_WORK * wk )
{
	CATS_ObjectUpdateNumCap( wk->cap[BBAG_CA_GETDEMO], FX32_ONE );
//	BattleBag_GetDemoCursorPush( wk );
}

void BattleBag_GetDemoCursorPush( BBAG_WORK * wk )
{
//	if( wk->get_anm == 1 ){
		s16	x, y;
		CATS_ObjectPosGetCap( wk->cap[BBAG_CA_GETDEMO], &x, &y );
		CATS_ObjectPosSetCap( wk->cap[BBAG_CA_GETDEMO], x, y+8 );
//	}
}
*/

static void BBAG_ClactGetDemoCursorAdd( BBAG_WORK * wk )
{
	CATS_SYS_PTR csp;
	FINGER_PTR	finger;

	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	FINGER_ResourceLoad(
		csp, wk->crp, wk->pfd, CHR_ID_GETDEMO, PAL_ID_GETDEMO, CEL_ID_GETDEMO, ANM_ID_GETDEMO );


	wk->finger = FINGER_ActorCreate(
					csp, wk->crp, wk->dat->heap,
					CHR_ID_GETDEMO, PAL_ID_GETDEMO, CEL_ID_GETDEMO, ANM_ID_GETDEMO, 0, 0 );
}

static void BBAG_GetDemoCursorDel( BBAG_WORK * wk )
{
	FINGER_ActorDelete( wk->finger );
	FINGER_ResourceFree(
		wk->crp, CHR_ID_GETDEMO, PAL_ID_GETDEMO, CEL_ID_GETDEMO, ANM_ID_GETDEMO );
}


#define	GET_DEMO_FINGER_WAIT	( 60 )

static const int GetDemoCursorPos[3][2] =
{
	{ P1_GETDEMO_CURSOR_X, P1_GETDEMO_CURSOR_Y },
	{ P2_GETDEMO_CURSOR_X, P2_GETDEMO_CURSOR_Y },
	{ P3_GETDEMO_CURSOR_X, P3_GETDEMO_CURSOR_Y }
};

void BBAG_GetDemoCursorSet( BBAG_WORK * wk, u8 page )
{
	if( wk->dat->mode == BBAG_MODE_GETDEMO ){
		FINGER_PosSetON( wk->finger, GetDemoCursorPos[page][0], GetDemoCursorPos[page][1] );
		FINGER_TouchReq( wk->finger, GET_DEMO_FINGER_WAIT );
	}else{
		FINGER_OFF( wk->finger );
	}
}
