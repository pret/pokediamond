//============================================================================================
/**
 * @file	b_plist_obj.c
 * @brief	�퓬�p�|�P�������X�g���OBJ����
 * @author	Hiroyuki Nakamura
 * @date	05.02.07
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/palanm.h"
#include "system/msgdata.h"
#include "system/numfont.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "battle/battle_common.h"
#include "battle/fight_tool.h"
#include "battle/wazatype_icon.h"
#include "poketool/pokeparty.h"
#include "poketool/pokeicon.h"
#include "poketool/waza_tool.h"
#include "application/p_status.h"
#include "application/pokelist.h"
#include "application/app_tool.h"
#include "itemtool/item.h"
#include "b_app_tool.h"

#define	B_PLIST_OBJ_H_GLOBAL
#include "b_plist.h"
#include "b_plist_main.h"
#include "b_plist_obj.h"
#include "b_plist_gra.naix"


//============================================================================================
//	�萔��`
//============================================================================================
#define	CLACT_ID_COMMON		( 45063 )	// ���̉�ʂŎg�p����Z���A�N�^�[��ID

// �L�������\�[�XID
enum {
	CHR_ID_POKE1 = CLACT_ID_COMMON,		// �|�P�����A�C�R���F�P�C��
	CHR_ID_POKE2,						// �|�P�����A�C�R���F�Q�C��
	CHR_ID_POKE3,						// �|�P�����A�C�R���F�R�C��
	CHR_ID_POKE4,						// �|�P�����A�C�R���F�S�C��
	CHR_ID_POKE5,						// �|�P�����A�C�R���F�T�C��
	CHR_ID_POKE6,						// �|�P�����A�C�R���F�U�C��

	CHR_ID_STATUS,						// ��Ԉُ�A�C�R���F�P�C��

	CHR_ID_POKETYPE1,					// �|�P�����^�C�v�A�C�R���P
	CHR_ID_POKETYPE2,					// �|�P�����^�C�v�A�C�R���Q

	CHR_ID_WAZATYPE1,					// �Z�^�C�v�A�C�R���P
	CHR_ID_WAZATYPE2,					// �Z�^�C�v�A�C�R���Q
	CHR_ID_WAZATYPE3,					// �Z�^�C�v�A�C�R���R
	CHR_ID_WAZATYPE4,					// �Z�^�C�v�A�C�R���S
	CHR_ID_WAZATYPE5,					// �Z�^�C�v�A�C�R���T

	CHR_ID_BUNRUI,						// ���ރA�C�R��

	CHR_ID_ITEM,						// �A�C�e���A�C�R��

	CHR_ID_CND,							// �R���f�B�V����

	CHR_ID_CURSOR,						// �J�[�\��

	CHR_ID_MAX = CHR_ID_CURSOR - CLACT_ID_COMMON + 1
};

// �p���b�g���\�[�XID
enum {
	PAL_ID_POKE = CLACT_ID_COMMON,		// �|�P�����A�C�R���i�R�{�j
	PAL_ID_STATUS,						// ��Ԉُ�A�C�R���i�P�{�j
	PAL_ID_TYPE,						// �^�C�v/���ރA�C�R���i�R�{�j
	PAL_ID_ITEM,						// �A�C�e���A�C�R���i�P�{�j
	PAL_ID_CND,							// �R���f�B�V�����i�P�{�j
	PAL_ID_CURSOR,						// �J�[�\���i�P�{�j
	PAL_ID_MAX = PAL_ID_CURSOR - CLACT_ID_COMMON + 1
};

// �Z�����\�[�XID
enum {
	CEL_ID_POKE = CLACT_ID_COMMON,		// �|�P�����A�C�R��
	CEL_ID_STATUS,						// ��Ԉُ�A�C�R��
	CEL_ID_TYPE,						// �^�C�v/���ރA�C�R��
	CEL_ID_ITEM,						// �A�C�e���A�C�R��
	CEL_ID_CND,							// �R���f�B�V����
	CEL_ID_CURSOR,						// �J�[�\��
	CEL_ID_MAX = CEL_ID_CURSOR - CLACT_ID_COMMON + 1
};

// �Z���A�j�����\�[�XID
enum {
	ANM_ID_POKE = CLACT_ID_COMMON,		// �|�P�����A�C�R��
	ANM_ID_STATUS,						// ��Ԉُ�A�C�R��
	ANM_ID_TYPE,						// �^�C�v/���ރA�C�R��
	ANM_ID_ITEM,						// �A�C�e���A�C�R��
	ANM_ID_CND,							// �R���f�B�V����
	ANM_ID_CURSOR,						// �J�[�\��
	ANM_ID_MAX = ANM_ID_CURSOR - CLACT_ID_COMMON + 1
};

#define	CURSOR_CLA_MAX		( 5 )		// �J�[�\����OBJ��


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void BPL_ClactResManInit( BPLIST_WORK * wk );
static void BPL_ClactPokeLoad( BPLIST_WORK * wk );
static void BPL_ClactStatusLoad( BPLIST_WORK * wk );
static void BPL_ClactConditionLoad( BPLIST_WORK * wk );
static void BPL_ClactTypeLoad( BPLIST_WORK * wk );
static void BPL_ClactItemLoad( BPLIST_WORK * wk );
static void BPL_ClactAddAll( BPLIST_WORK * wk );

static void BPL_PokeIconPaletteChg( BPLIST_WORK * wk );

static void BPL_Page1ObjSet( BPLIST_WORK * wk );
static void BPL_ChgPageObjSet( BPLIST_WORK * wk );
static void BPL_StMainPageObjSet( BPLIST_WORK * wk );
static void BPL_StWazaSelPageObjSet( BPLIST_WORK * wk );
static void BPL_Page4ObjSet( BPLIST_WORK * wk );
static void BPL_Page5ObjSet( BPLIST_WORK * wk );
static void BPL_Page6ObjSet( BPLIST_WORK * wk );
static void BPL_Page7ObjSet( BPLIST_WORK * wk );
static void BPL_Page8ObjSet( BPLIST_WORK * wk );
static void BPL_Page9ObjSet( BPLIST_WORK * wk );

static void BPL_BattleWazaTypeSet( BPLIST_WORK * wk );
static void BPL_ContestWazaTypeSet( BPLIST_WORK * wk );

static void BPL_EzConditionPut( BPLIST_WORK * wk );

static void BPL_ClactCursorAdd( BPLIST_WORK * wk );
static void BPL_CursorDel( BPLIST_WORK * wk );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// ���\�[�X�e�[�u��
static const int ObjParamEz[][5] =
{	// �L�����A�p���b�g�A�Z���A�Z���A�j���AOBJ�v���C�I���e�B
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �A�C�e���A�C�R���P
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �A�C�e���A�C�R���Q
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �A�C�e���A�C�R���R
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �A�C�e���A�C�R���S
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �A�C�e���A�C�R���T
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �A�C�e���A�C�R���U
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �A�C�e���A�C�R���V
	{ CHR_ID_POKE1, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// �|�P�����A�C�R���P
	{ CHR_ID_POKE2, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// �|�P�����A�C�R���Q
	{ CHR_ID_POKE3, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// �|�P�����A�C�R���R
	{ CHR_ID_POKE4, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// �|�P�����A�C�R���S
	{ CHR_ID_POKE5, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// �|�P�����A�C�R���T
	{ CHR_ID_POKE6, PAL_ID_POKE, CEL_ID_POKE, ANM_ID_POKE, 1 },			// �|�P�����A�C�R���U
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// ��Ԉُ�A�C�R���P
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// ��Ԉُ�A�C�R���Q
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// ��Ԉُ�A�C�R���R
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// ��Ԉُ�A�C�R���S
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// ��Ԉُ�A�C�R���T
	{ CHR_ID_STATUS, PAL_ID_STATUS, CEL_ID_STATUS, ANM_ID_STATUS, 1 },	// ��Ԉُ�A�C�R���U
	{ CHR_ID_POKETYPE1, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// �|�P�����^�C�v�A�C�R���P
	{ CHR_ID_POKETYPE2, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// �|�P�����^�C�v�A�C�R���Q
	{ CHR_ID_WAZATYPE1, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// �Z�^�C�v�A�C�R���P
	{ CHR_ID_WAZATYPE2, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// �Z�^�C�v�A�C�R���Q
	{ CHR_ID_WAZATYPE3, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// �Z�^�C�v�A�C�R���R
	{ CHR_ID_WAZATYPE4, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// �Z�^�C�v�A�C�R���S
	{ CHR_ID_WAZATYPE5, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// �Z�^�C�v�A�C�R���S
	{ CHR_ID_BUNRUI, PAL_ID_TYPE, CEL_ID_TYPE, ANM_ID_TYPE, 0 },		// ���ރA�C�R��
	{ CHR_ID_CND, PAL_ID_CND, CEL_ID_CND, ANM_ID_CND, 0 },				// �R���f�B�V�����P
	{ CHR_ID_CND, PAL_ID_CND, CEL_ID_CND, ANM_ID_CND, 0 },				// �R���f�B�V�����Q
	{ CHR_ID_CND, PAL_ID_CND, CEL_ID_CND, ANM_ID_CND, 0 },				// �R���f�B�V�����R
	{ CHR_ID_CND, PAL_ID_CND, CEL_ID_CND, ANM_ID_CND, 0 },				// �R���f�B�V�����S
	{ CHR_ID_CND, PAL_ID_CND, CEL_ID_CND, ANM_ID_CND, 0 },				// �R���f�B�V�����T
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �J�X�^���{�[���A�C�R���P
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �J�X�^���{�[���A�C�R���Q
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �J�X�^���{�[���A�C�R���R
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �J�X�^���{�[���A�C�R���S
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �J�X�^���{�[���A�C�R���T
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �J�X�^���{�[���A�C�R���U
	{ CHR_ID_ITEM, PAL_ID_ITEM, CEL_ID_ITEM, ANM_ID_ITEM, 0 },			// �J�X�^���{�[���A�C�R���V
};

// �y�[�W�P�̃|�P�����A�C�R���̍��W
static const int P1_PokePos[][2] =
{
	{ 16,  16 }, { 144,  24 },
	{ 16,  64 }, { 144,  72 },
	{ 16, 112 }, { 144, 120 },
};
// �y�[�W�P�̏�Ԉُ�A�C�R���̍��W
static const int P1_StatusPos[][2] =
{
	{ 16+12,  16+24 }, { 144+12,  24+24 },
	{ 16+12,  64+24 }, { 144+12,  72+24 },
	{ 16+12, 112+24 }, { 144+12, 120+24 },
};

static const int P_CHG_PokePos[2] = { 128, 72 };	// ����ւ��y�[�W�̃|�P�����A�C�R���̍��W

static const int P2_PokePos[2] = { 24, 12 };		// �y�[�W�Q�̃|�P�����A�C�R���̍��W
static const int P2_StatusPos[2] = { 192+6, 17+3 };	// �y�[�W�Q�̏�Ԉُ�A�C�R���̍��W
// �y�[�W�Q�̃|�P�����̃^�C�v�A�C�R���̍��W
static const int P2_PokeTypePos[][2] =
{
	{ 128+2, 16 },
	{ 160+4, 16 }
};
// �y�[�W�Q�̋Z�̃^�C�v�A�C�R���̍��W
static const int P2_WazaTypePos[][2] =
{
	{  24,  80 },
	{ 152,  80 },
	{  24, 128 },
	{ 152, 128 }
};

static const int P3_PokePos[2] = { 24, 12 };		// �y�[�W�R�̃|�P�����A�C�R���̍��W
static const int P3_StatusPos[2] = { 192+6, 17+3 };	// �y�[�W�R�̏�Ԉُ�A�C�R���̍��W
// �y�[�W�R�̃|�P�����̃^�C�v�A�C�R���̍��W
static const int P3_PokeTypePos[][2] =
{
	{ 128+2, 16 },
	{ 160+4, 16 }
};

static const int P4_PokePos[2] = { 24, 12 };		// �y�[�W�S�̃|�P�����A�C�R���̍��W
static const int P4_StatusPos[2] = { 192+6, 17+3 };	// �y�[�W�S�̏�Ԉُ�A�C�R���̍��W
// �y�[�W�S�̃|�P�����̃^�C�v�A�C�R���̍��W
static const int P4_PokeTypePos[][2] =
{
	{ 128+2, 16 },
	{ 160+4, 16 }
};
static const int P4_WazaTypePos[2] = { 136, 48 };	// �y�[�W�S�̋Z�^�C�v�A�C�R���̍��W
static const int P4_WazaKindPos[2] = { 24, 88 };	// �y�[�W�S�̋Z���ރA�C�R���̍��W

static const int P5_PokePos[2] = { 24, 12 };		// �y�[�W�T�̃|�P�����A�C�R���̍��W
// �y�[�W�T�̃|�P�����̃^�C�v�A�C�R���̍��W
static const int P5_PokeTypePos[][2] =
{
	{ 128+2, 16 },
	{ 160+4, 16 }
};
// �y�[�W�T�̋Z�̃^�C�v�A�C�R���̍��W
static const int P5_WazaTypePos[][2] =
{
	{  24,  80 },
	{ 152,  80 },
	{  24, 128 },
	{ 152, 128 },
	{  88, 176 }
};

static const int P6_PokePos[2] = { 24, 12 };		// �y�[�W�U�̃|�P�����A�C�R���̍��W
// �y�[�W�U�̃|�P�����̃^�C�v�A�C�R���̍��W
static const int P6_PokeTypePos[][2] =
{
	{ 128+2, 16 },
	{ 160+4, 16 }
};
static const int P6_WazaTypePos[2] = { 136, 48 };	// �y�[�W�U�̋Z�^�C�v�A�C�R���̍��W
static const int P6_WazaKindPos[2] = { 24, 88 };	// �y�[�W�U�̋Z���ރA�C�R���̍��W

static const int P8_WazaTypePos[2] = { 136, 72 };	// �y�[�W�W�̋Z�^�C�v�A�C�R���̍��W


//--------------------------------------------------------------------------------------------
/**
 * �퓬�p�|�P���X�gOBJ������
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattlePokeList_ObjInit( BPLIST_WORK * wk )
{
	BPL_ClactResManInit( wk );
	BPL_ClactPokeLoad( wk );
	BPL_ClactStatusLoad( wk );
	BPL_ClactTypeLoad( wk );
	BPL_ClactItemLoad( wk );
	BPL_ClactConditionLoad( wk );
	BPL_ClactAddAll( wk );
	BPL_ClactCursorAdd( wk );

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
static void BPL_ClactResManInit( BPLIST_WORK * wk )
{
	TCATS_RESOURCE_NUM_LIST	crnl = { CHR_ID_MAX, PAL_ID_MAX, CEL_ID_MAX, ANM_ID_MAX, 0, 0 };
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	wk->crp = CATS_ResourceCreate( csp );
	CATS_ClactSetInit( csp, wk->crp, BPL_CA_MAX+CURSOR_CLA_MAX );
	CATS_ResourceManagerInit( csp, wk->crp, &crnl );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����A�C�R���̃O���t�B�b�N���[�h
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactPokeLoad( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// �p���b�g
	CATS_LoadResourcePlttWorkArc(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp,
		ARC_POKEICON, PokeIconPalArcIndexGet(), 0, 3, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_POKE );
	// �Z��
	CATS_LoadResourceCellArc(
		csp, wk->crp, ARC_POKEICON, PokeIconAnmCellArcIndexGet(), 0, CEL_ID_POKE );
	// �Z���A�j��
	CATS_LoadResourceCellAnmArc(
		csp, wk->crp, ARC_POKEICON, PokeIconAnmCellAnmArcIndexGet(), 0, ANM_ID_POKE );
	// �L����
	for( i=0; i<6; i++ ){
		if( wk->poke[i].mons != 0 ){
			CATS_LoadResourceCharArc(
				csp, wk->crp, ARC_POKEICON,
				PokeIconCgxArcIndexGetByPP(wk->poke[i].pp),
				0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_POKE1+i );
		}else{
			CATS_LoadResourceCharArc(
				csp, wk->crp, ARC_POKEICON,
				PokeIconCgxArcIndexGetByMonsNumber(0,0,0),
				0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_POKE1+i );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���̃O���t�B�b�N���[�h
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactStatusLoad( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// �p���b�g
	CATS_LoadResourcePlttWorkArc(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp, ARC_PSTATUS_GRA,
		BadStatusIconPlttArcGet(), 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_STATUS );
	// �Z��
	CATS_LoadResourceCellArc(
		csp, wk->crp, ARC_PSTATUS_GRA, BadStatusIconCellArcGet(), 0, CEL_ID_STATUS );
	// �Z���A�j��
	CATS_LoadResourceCellAnmArc(
		csp, wk->crp, ARC_PSTATUS_GRA, BadStatusIconCanmArcGet(), 0, ANM_ID_STATUS );
	// �L����
	CATS_LoadResourceCharArc(
		csp, wk->crp, ARC_PSTATUS_GRA,
		BadStatusIconCharArcGet(), 0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_STATUS );
}

//--------------------------------------------------------------------------------------------
/**
 * �^�C�v/���ރA�C�R���̃O���t�B�b�N���[�h
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactTypeLoad( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// �p���b�g
	WazaTypeIcon_PlttWorkResourceLoad(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_TYPE );
	// �Z���E�A�j��
	WazaTypeIcon_CellAnmResourceLoad( csp, wk->crp, CEL_ID_TYPE, ANM_ID_TYPE );
	// �L����
	for( i=CHR_ID_POKETYPE1; i<=CHR_ID_WAZATYPE5; i++ ){
		WazaTypeIcon_CharResourceLoad( csp, wk->crp, NNS_G2D_VRAM_TYPE_2DSUB, 0, i );
	}
	// ���ރL����
	WazaKindIcon_CharResourceLoad( csp, wk->crp, NNS_G2D_VRAM_TYPE_2DSUB, 0, CHR_ID_BUNRUI );
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
static void BPL_ClactItemLoad( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// �p���b�g
	CATS_LoadResourcePlttWorkArc(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp, ARC_PLIST_GRA,
		Pokelist_ItemIconPalArcGet(), 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_ITEM );
	// �Z��
	CATS_LoadResourceCellArc(
		csp, wk->crp, ARC_PLIST_GRA, Pokelist_ItemIconCellArcGet(), 0, CEL_ID_ITEM );
	// �Z���A�j��
	CATS_LoadResourceCellAnmArc(
		csp, wk->crp, ARC_PLIST_GRA, Pokelist_ItemIconCAnmArcGet(), 0, ANM_ID_ITEM );
	// �L����
	CATS_LoadResourceCharArc(
		csp, wk->crp, ARC_PLIST_GRA,
		Pokelist_ItemIconCgxArcGet(), 0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_ITEM );
}

//--------------------------------------------------------------------------------------------
/**
 * �R���f�B�V�����̃O���t�B�b�N���[�h
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ClactConditionLoad( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	// �p���b�g
	CATS_LoadResourcePlttWorkArc(
		wk->pfd, FADE_SUB_OBJ, csp, wk->crp, ARC_BPLIST_GRA,
		NARC_b_plist_gra_b_plist_obj_NCLR, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_CND );
	// �Z��
	CATS_LoadResourceCellArc(
		csp, wk->crp, ARC_BPLIST_GRA, NARC_b_plist_gra_b_plist_obj_NCER, 0, CEL_ID_CND );
	// �Z���A�j��
	CATS_LoadResourceCellAnmArc(
		csp, wk->crp, ARC_BPLIST_GRA, NARC_b_plist_gra_b_plist_obj_NANR, 0, ANM_ID_CND );
	// �L����
	CATS_LoadResourceCharArc(
		csp, wk->crp, ARC_BPLIST_GRA,
		NARC_b_plist_gra_b_plist_obj_NCGR, 0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_CND );
}



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
static CATS_ACT_PTR BPL_ClactAdd( BPLIST_WORK * wk, u32 id )
{
	TCATS_OBJECT_ADD_PARAM_S	prm;
	CATS_SYS_PTR	csp;

	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	prm.x = 0;
	prm.y = 0;
	prm.z = 0;

	prm.anm = 0;
	prm.pri = ObjParamEz[id][4];
	prm.pal = 0;
	prm.d_area = NNS_G2D_VRAM_TYPE_2DSUB;

	prm.id[0] = ObjParamEz[id][0];
	prm.id[1] = ObjParamEz[id][1];
	prm.id[2] = ObjParamEz[id][2];
	prm.id[3] = ObjParamEz[id][3];
	
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
static void BPL_ClactAddAll( BPLIST_WORK * wk )
{
	u32	i;

	for( i=0; i<BPL_CA_MAX; i++ ){
		wk->cap[i] = BPL_ClactAdd( wk, i );
	}
	BPL_PokeIconPaletteChg( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * �퓬�p�|�P���X�gOBJ�폜
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattlePokeList_ObjFree( BPLIST_WORK * wk )
{
	CATS_SYS_PTR	csp;
	u32	i;
	
	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	for( i=0; i<BPL_CA_MAX; i++ ){
		CATS_ActorPointerDelete_S( wk->cap[i] );
	}

	BPL_CursorDel( wk );

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
static void BPL_ClactOn( CATS_ACT_PTR cap, const int x, const int y )
{
	CATS_ObjectEnableCap( cap, 1 );
	CATS_ObjectPosSetCap( cap, x, y );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����A�C�R���̃p���b�g�؂�ւ�
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_PokeIconPaletteChg( BPLIST_WORK * wk )
{
	s32	i;

	for( i=0; i<6; i++ ){
		if( wk->poke[i].mons == 0 ){ continue; }
		CATS_ObjectPaletteSetCap(
			wk->cap[BPL_CA_POKE1+i],
			PokeIconPalNumGet(wk->poke[i].mons,wk->poke[i].form,wk->poke[i].egg) );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �^�C�v�A�C�R���؂�ւ�
 *
 * @param	wk		���[�N
 * @param	cap		�Z���A�N�^�[�f�[�^
 * @param	res_id	���\�[�XID
 * @param	type	�^�C�v
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_TypeIconChange( BPLIST_WORK * wk, CATS_ACT_PTR cap, u32 res_id, u8 type )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	CATS_ChangeResourceCharArc(
		csp, wk->crp, WazaTypeIcon_ArcIDGet(),
		WazaTypeIcon_CgrIDGet(type), WAZATYPEICON_COMP_CHAR, res_id );

	CATS_ObjectPaletteSetCap( cap, WazaTypeIcon_PlttOffsetGet(type)+4 );
}

//--------------------------------------------------------------------------------------------
/**
 * ���ރA�C�R���؂�ւ�
 *
 * @param	wk		���[�N
 * @param	cap		�Z���A�N�^�[�f�[�^
 * @param	kind	����
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_KindIconChange( BPLIST_WORK * wk, CATS_ACT_PTR cap, u32 kind )
{
	CATS_SYS_PTR	csp = BattleWorkCATS_SYS_PTRGet( wk->dat->bw );

	CATS_ChangeResourceCharArc(
		csp, wk->crp, WazaKindIcon_ArcIDGet(),
		WazaKindIcon_CgrIDGet(kind), WAZAKINDICON_COMP_CHAR, CHR_ID_BUNRUI );

	CATS_ObjectPaletteSetCap( cap, WazaKindIcon_PlttOffsetGet(kind)+4 );
}

//--------------------------------------------------------------------------------------------
/**
 * ��Ԉُ�A�C�R���؂�ւ�
 *
 * @param	st		�X�e�[�^�X
 * @param	cap		�Z���A�N�^�[�f�[�^
 * @param	x		X���W
 * @param	y		Y���W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_StIconPut( u16 st, CATS_ACT_PTR cap, const int x, const int y )
{
	if( st == ST_ICON_NONE ){ return; }

	CATS_ObjectAnimeSeqSetCap( cap, st );
	BPL_ClactOn( cap, x, y );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����̃^�C�v�A�C�R���؂�ւ�
 *
 * @param	wk		���[�N
 * @param	pd		�|�P�����f�[�^
 * @param	pos		���W�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_PokeTypeIconPut( BPLIST_WORK * wk, BPL_POKEDATA * pd, const int * pos )
{
	BPL_TypeIconChange( wk, wk->cap[BPL_CA_POKETYPE1], CHR_ID_POKETYPE1, pd->type1 );
	BPL_ClactOn( wk->cap[BPL_CA_POKETYPE1], pos[0], pos[1] );
	if( pd->type1 != pd->type2 ){
		BPL_TypeIconChange( wk, wk->cap[BPL_CA_POKETYPE2], CHR_ID_POKETYPE2, pd->type2 );
		BPL_ClactOn( wk->cap[BPL_CA_POKETYPE2], pos[2], pos[3] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���A�C�R���؂�ւ�
 *
 * @param	item	�X�e�[�^�X
 * @param	cap		�Z���A�N�^�[�f�[�^
 * @param	x		X���W
 * @param	y		Y���W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ItemIconPut( u16 item, CATS_ACT_PTR cap, const int x, const int y )
{
	if( item == 0 ){ return; }

	if( ItemMailCheck( item ) == TRUE ){
		CATS_ObjectAnimeSeqSetCap( cap, 1 );
	}else{
		CATS_ObjectAnimeSeqSetCap( cap, 0 );
	}
	BPL_ClactOn( cap, x, y );
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���A�C�R���؂�ւ�
 *
 * @param	cb		�J�X�^���{�[��ID
 * @param	cap		�Z���A�N�^�[�f�[�^
 * @param	x		X���W
 * @param	y		Y���W
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_CustomBallIconPut( u8 cb, CATS_ACT_PTR cap, const int x, const int y )
{
	if( cb == 0 ){ return; }

	CATS_ObjectAnimeSeqSetCap( cap, 2 );
	BPL_ClactOn( cap, x, y );
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
void BattlePokeList_PageObjSet( BPLIST_WORK * wk, u32 page )
{
	u32	i;

	for( i=0; i<BPL_CA_MAX; i++ ){
		CATS_ObjectEnableCap( wk->cap[i], 0 );
	}

	switch( page ){
	case BPLIST_PAGE_SELECT:	// �|�P�����I���y�[�W
		BPL_Page1ObjSet( wk );
		break;
	case BPLIST_PAGE_POKE_CHG:	// �|�P��������ւ��y�[�W
		BPL_ChgPageObjSet( wk );
		break;
	case BPLIST_PAGE_MAIN:		// �X�e�[�^�X���C���y�[�W
		BPL_StMainPageObjSet( wk );
		break;

	case BPLIST_PAGE_WAZA_SEL:	// �X�e�[�^�X�Z�I���y�[�W
		BPL_StWazaSelPageObjSet( wk );
		break;

	case BPLIST_PAGE_SKILL:		// �X�e�[�^�X�Z�y�[�W
		BPL_Page4ObjSet( wk );
		break;

	case BPLIST_PAGE_PP_RCV:		// PP�񕜋Z�I���y�[�W
		BPL_Page7ObjSet( wk );
		break;

	case BPLIST_PAGE_WAZASET_BS:	// �X�e�[�^�X�Z�Y��P�y�[�W�i�퓬�Z�I���j
		BPL_Page5ObjSet( wk );
		break;

	case BPLIST_PAGE_WAZASET_BI:	// �X�e�[�^�X�Z�Y��Q�y�[�W�i�퓬�Z�ڍׁj
		BPL_Page6ObjSet( wk );
		break;

	case BPLIST_PAGE_WAZASET_CS:	// �X�e�[�^�X�Z�Y��R�y�[�W�i�R���e�X�g�Z�ڍׁj
		BPL_Page9ObjSet( wk );
		break;

	case BPLIST_PAGE_WAZASET_CI:	// �X�e�[�^�X�Z�Y��S�y�[�W�i�R���e�X�g�Z�I���j
		BPL_Page8ObjSet( wk );
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�P��OBJ���Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page1ObjSet( BPLIST_WORK * wk )
{
	s32	i;

	for( i=0; i<6; i++ ){
		if( wk->poke[i].mons == 0 ){ continue; }
		// �|�P�����A�C�R��
		BPL_ClactOn( wk->cap[BPL_CA_POKE1+i], P1_PokePos[i][0], P1_PokePos[i][1] );
		// ��Ԉُ�A�C�R��
		BPL_StIconPut(
			wk->poke[i].st, wk->cap[BPL_CA_STATUS1+i], P1_StatusPos[i][0], P1_StatusPos[i][1] );
		// �A�C�e���A�C�R��
		BPL_ItemIconPut(
			wk->poke[i].item, wk->cap[BPL_CA_ITEM1+i], P1_PokePos[i][0]+8, P1_PokePos[i][1]+8 );
		// �J�X�^���{�[���A�C�R��
		BPL_CustomBallIconPut(
			wk->poke[i].cb, wk->cap[BPL_CA_CB1+i], P1_PokePos[i][0]+16, P1_PokePos[i][1]+8 );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ����ւ��y�[�W��OBJ���Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ChgPageObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// �|�P�A�C�R��
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P_CHG_PokePos[0], P_CHG_PokePos[1] );
	// �A�C�e���A�C�R��
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P_CHG_PokePos[0]+8, P_CHG_PokePos[1]+8 );
	// �J�X�^���{�[���A�C�R��
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P_CHG_PokePos[0]+16, P_CHG_PokePos[1]+8 );
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�Q��OBJ���Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
#define	P_STMAIN_ITEM_PX	( 20 )
#define	P_STMAIN_ITEM_PY	( 132 )

static void BPL_StMainPageObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// �|�P�A�C�R��
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P2_PokePos[0], P2_PokePos[1] );
	// �X�e�[�^�X�ُ�
	BPL_StIconPut(
		pd->st, wk->cap[BPL_CA_STATUS1+wk->dat->sel_poke], P2_StatusPos[0], P2_StatusPos[1] );
	// �^�C�v
	BPL_PokeTypeIconPut( wk, pd, &P2_PokeTypePos[0][0] );
	// �A�C�e���A�C�R��
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P2_PokePos[0]+8, P2_PokePos[1]+8 );
	// �J�X�^���{�[���A�C�R��
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P2_PokePos[0]+16, P2_PokePos[1]+8 );

	// �A�C�e���A�C�R���i�A�C�e�����̉��́j
	BPL_ItemIconPut( pd->item, wk->cap[BPL_CA_ITEM7], P_STMAIN_ITEM_PX, P_STMAIN_ITEM_PY );
}

//--------------------------------------------------------------------------------------------
/**
 * �X�e�[�^�X�Z�I���y�[�W��OBJ���Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_StWazaSelPageObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u32	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// �|�P�A�C�R��
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P3_PokePos[0], P3_PokePos[1] );
	// �X�e�[�^�X�ُ�
	BPL_StIconPut(
		pd->st, wk->cap[BPL_CA_STATUS1+wk->dat->sel_poke], P3_StatusPos[0], P3_StatusPos[1] );
	// �^�C�v
	BPL_PokeTypeIconPut( wk, pd, &P3_PokeTypePos[0][0] );
	// �A�C�e���A�C�R��
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P3_PokePos[0]+8, P3_PokePos[1]+8 );
	// �J�X�^���{�[���A�C�R��
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P3_PokePos[0]+16, P3_PokePos[1]+8 );

	// �Z�^�C�v
	for( i=0; i<4; i++ ){
		if( pd->waza[i].id == 0 ){ continue; }

		BPL_TypeIconChange(
			wk, wk->cap[BPL_CA_WAZATYPE1+i], CHR_ID_WAZATYPE1+i, pd->waza[i].type );
		BPL_ClactOn( wk->cap[BPL_CA_WAZATYPE1+i], P2_WazaTypePos[i][0], P2_WazaTypePos[i][1] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�S��OBJ���Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page4ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd = &wk->poke[wk->dat->sel_poke];

	// �|�P�A�C�R��
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P4_PokePos[0], P4_PokePos[1] );
	// �X�e�[�^�X�ُ�
	BPL_StIconPut(
		pd->st, wk->cap[BPL_CA_STATUS1+wk->dat->sel_poke], P4_StatusPos[0], P4_StatusPos[1] );
	// �^�C�v
	BPL_PokeTypeIconPut( wk, pd, &P4_PokeTypePos[0][0] );
	// �Z�^�C�v
	BPL_ClactOn(
		wk->cap[BPL_CA_WAZATYPE1+wk->dat->sel_wp], P4_WazaTypePos[0], P4_WazaTypePos[1] );
	// �A�C�e���A�C�R��
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P4_PokePos[0]+8, P4_PokePos[1]+8 );
	// �J�X�^���{�[���A�C�R��
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P4_PokePos[0]+16, P4_PokePos[1]+8 );
	// ���ރA�C�R��
	BPL_KindIconChange(
		wk, wk->cap[BPL_CA_BUNRUI], pd->waza[wk->dat->sel_wp].kind );
	BPL_ClactOn( wk->cap[BPL_CA_BUNRUI], P4_WazaKindPos[0], P4_WazaKindPos[1] );
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�T��OBJ���Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page5ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// �|�P�A�C�R��
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P5_PokePos[0], P5_PokePos[1] );
	// �^�C�v
	BPL_PokeTypeIconPut( wk, pd, &P5_PokeTypePos[0][0] );
	// �A�C�e���A�C�R��
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P5_PokePos[0]+8, P5_PokePos[1]+8 );
	// �J�X�^���{�[���A�C�R��
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P5_PokePos[0]+16, P5_PokePos[1]+8 );

	// �Z�^�C�v
	BattlePokelist_WazaTypeSet( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�U��OBJ���Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page6ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd = &wk->poke[wk->dat->sel_poke];

	// �|�P�A�C�R��
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P6_PokePos[0], P6_PokePos[1] );
	// �^�C�v
	BPL_PokeTypeIconPut( wk, pd, &P6_PokeTypePos[0][0] );
	// �Z�^�C�v
	BPL_ClactOn(
		wk->cap[BPL_CA_WAZATYPE1+wk->dat->sel_wp], P6_WazaTypePos[0], P6_WazaTypePos[1] );
	// �A�C�e���A�C�R��
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P6_PokePos[0]+8, P6_PokePos[1]+8 );
	// �J�X�^���{�[���A�C�R��
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P6_PokePos[0]+16, P6_PokePos[1]+8 );
	// ���ރA�C�R��
	if( wk->dat->sel_wp < 4 ){
		BPL_KindIconChange(
			wk, wk->cap[BPL_CA_BUNRUI], pd->waza[wk->dat->sel_wp].kind );
	}else{
		BPL_KindIconChange(
			wk, wk->cap[BPL_CA_BUNRUI], WT_WazaDataParaGet(wk->dat->chg_waza,ID_WTD_kind) );
	}
	BPL_ClactOn( wk->cap[BPL_CA_BUNRUI], P6_WazaKindPos[0], P6_WazaKindPos[1] );
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�V��OBJ���Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page7ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// �|�P�A�C�R��
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P5_PokePos[0], P5_PokePos[1] );
	// �^�C�v
	BPL_PokeTypeIconPut( wk, pd, &P5_PokeTypePos[0][0] );
	// �A�C�e���A�C�R��
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P5_PokePos[0]+8, P5_PokePos[1]+8 );
	// �J�X�^���{�[���A�C�R��
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P5_PokePos[0]+16, P5_PokePos[1]+8 );

	// �Z�^�C�v
	BattlePokelist_WazaTypeSet( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�W��OBJ���Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page8ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd = &wk->poke[wk->dat->sel_poke];

	// �|�P�A�C�R��
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P6_PokePos[0], P6_PokePos[1] );

	// �Z�^�C�v
	BPL_ClactOn(
		wk->cap[BPL_CA_WAZATYPE1+wk->dat->sel_wp], P8_WazaTypePos[0], P8_WazaTypePos[1] );
	// �A�C�e���A�C�R��
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P6_PokePos[0]+8, P6_PokePos[1]+8 );
	// �J�X�^���{�[���A�C�R��
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P6_PokePos[0]+16, P6_PokePos[1]+8 );

	// �R���f�B�V����
	BPL_EzConditionPut( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * �y�[�W�X��OBJ���Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_Page9ObjSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd = &wk->poke[wk->dat->sel_poke];

	// �|�P�A�C�R��
	BPL_ClactOn( wk->cap[BPL_CA_POKE1+wk->dat->sel_poke], P6_PokePos[0], P6_PokePos[1] );

	// �Z�^�C�v
//	BPL_ClactOn(
//		wk->cap[BPL_CA_WAZATYPE1+wk->dat->sel_wp], P8_WazaTypePos[0], P8_WazaTypePos[1] );

	// �A�C�e���A�C�R��
	BPL_ItemIconPut(
		pd->item, wk->cap[BPL_CA_ITEM1+wk->dat->sel_poke], P6_PokePos[0]+8, P6_PokePos[1]+8 );
	// �J�X�^���{�[���A�C�R��
	BPL_CustomBallIconPut(
		pd->cb, wk->cap[BPL_CA_CB1+wk->dat->sel_poke], P6_PokePos[0]+16, P6_PokePos[1]+8 );

	// �Z�^�C�v
	BattlePokelist_WazaTypeSet( wk );

	// �R���f�B�V����
	BPL_EzConditionPut( wk );
}


//--------------------------------------------------------------------------------------------
/**
 * �Z�A�C�R���Z�b�g�F�퓬
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_BattleWazaTypeSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// �Z�^�C�v
	for( i=0; i<4; i++ ){
		if( pd->waza[i].id == 0 ){ continue; }

		BPL_TypeIconChange(
			wk, wk->cap[BPL_CA_WAZATYPE1+i], CHR_ID_WAZATYPE1+i, pd->waza[i].type );
		BPL_ClactOn( wk->cap[BPL_CA_WAZATYPE1+i], P5_WazaTypePos[i][0], P5_WazaTypePos[i][1] );
	}

	if( wk->dat->chg_waza != 0 ){
		BPL_TypeIconChange(
			wk, wk->cap[BPL_CA_WAZATYPE5], CHR_ID_WAZATYPE5,
			WT_WazaDataParaGet( wk->dat->chg_waza, ID_WTD_wazatype ) );
		BPL_ClactOn( wk->cap[BPL_CA_WAZATYPE5], P5_WazaTypePos[4][0], P5_WazaTypePos[4][1] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �Z�A�C�R���Z�b�g�F�R���e�X�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_ContestWazaTypeSet( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	// �Z�^�C�v
	for( i=0; i<4; i++ ){
		if( pd->waza[i].id == 0 ){ continue; }

		BPL_TypeIconChange(
			wk, wk->cap[BPL_CA_WAZATYPE1+i], CHR_ID_WAZATYPE1+i,
			WT_WazaDataParaGet(pd->waza[i].id,ID_WTD_contype)+ICONTYPE_STYLE );
		BPL_ClactOn( wk->cap[BPL_CA_WAZATYPE1+i], P5_WazaTypePos[i][0], P5_WazaTypePos[i][1] );
	}

	if( wk->dat->chg_waza != 0 ){
		BPL_TypeIconChange(
			wk, wk->cap[BPL_CA_WAZATYPE5], CHR_ID_WAZATYPE5,
			WT_WazaDataParaGet(wk->dat->chg_waza,ID_WTD_contype)+ICONTYPE_STYLE );
		BPL_ClactOn( wk->cap[BPL_CA_WAZATYPE5], P5_WazaTypePos[4][0], P5_WazaTypePos[4][1] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �Z�A�C�R���Z�b�g�F�퓬 or �R���e�X�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BattlePokelist_WazaTypeSet( BPLIST_WORK * wk )
{
	if( wk->bc_put == 0 ){
		BPL_BattleWazaTypeSet( wk );
	}else{
		BPL_ContestWazaTypeSet( wk );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * �|�P�����A�C�R���A�j���؂�ւ�
 *
 * @param	cap		�Z���A�N�^�[�f�[�^
 * @param	anm		�A�j��
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BPL_PokeIconAnmChg( CATS_ACT_PTR cap, u8 anm )
{
	if( CATS_ObjectAnimeSeqGetCap( cap ) == anm ){ return; }
	CATS_ObjectAnimeFrameSetCap( cap, 0 );
	CATS_ObjectAnimeSeqSetCap( cap, anm );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����A�C�R���A�j���`�F�b�N
 *
 * @param	pd		�|�P�����f�[�^
 *
 * @return	�A�j���ԍ�
 */
//--------------------------------------------------------------------------------------------
static u8 BPL_PokeIconAnmCheck( BPL_POKEDATA * pd )
{
	if( pd->hp == 0 ){
		return POKEICON_ANM_DEATH;
	}

	if( pd->st != ST_ICON_NONE && pd->st != ST_ICON_HINSI ){
		return POKEICON_ANM_STCHG;
	}

	switch( GetHPGaugeDottoColor( pd->hp, pd->mhp, BPL_HP_DOTTO_MAX ) ){
	case HP_DOTTO_MAX:
		return POKEICON_ANM_HPMAX;
	case HP_DOTTO_GREEN:	// ��
		return POKEICON_ANM_HPGREEN;
	case HP_DOTTO_YELLOW:	// ��
		return POKEICON_ANM_HPYERROW;
	case HP_DOTTO_RED:		// ��
		return POKEICON_ANM_HPRED;
	}

	return POKEICON_ANM_DEATH;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����A�C�R���A�j��
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BPL_PokeIconAnime( BPLIST_WORK * wk )
{
	u16	i;
	u16	anm;

	for( i=0; i<PokeParty_GetPokeCount(wk->dat->pp); i++ ){

		if( wk->poke[i].mons == 0 ){ continue; }

		anm = BPL_PokeIconAnmCheck( &wk->poke[i] );

		BPL_PokeIconAnmChg( wk->cap[BPL_CA_POKE1+i], anm );
		CATS_ObjectUpdateNumCap( wk->cap[BPL_CA_POKE1+i], FX32_ONE );

/*
		if( wk->pos == i && anm != POKEICON_ANM_DEATH && anm != POKEICON_ANM_STCHG ){
			if( CLACT_AnmFrameGet( dat->icon_cwp ) == 0 ){
				CATS_ObjectPosSet( dat->icon_cwp, dat->mons_px, dat->mons_py-3 );
			}else{
				CATS_ObjectPosSet( dat->icon_cwp, dat->mons_px, dat->mons_py+1 );
			}
			continue;
		}
		CATS_ObjectPosSet( dat->icon_cwp, dat->mons_px, dat->mons_py );
*/

	}
}

//============================================================================================
//	�ȈՃR���f�B�V����
//============================================================================================
#define	EZCON1_MIN_X	( 144 )
#define	EZCON1_MAX_X	( 144 )
#define	EZCON1_MIN_Y	( 24 )
#define	EZCON1_MAX_Y	( 2 )

#define	EZCON2_MIN_X	( 144 )
#define	EZCON2_MAX_X	( 167 )
#define	EZCON2_MIN_Y	( 24 )
#define	EZCON2_MAX_Y	( 18 )

#define	EZCON3_MIN_X	( 144 )
#define	EZCON3_MAX_X	( 159 )
#define	EZCON3_MIN_Y	( 24 )
#define	EZCON3_MAX_Y	( 47 )

#define	EZCON4_MIN_X	( 143 )
#define	EZCON4_MAX_X	( 128 )
#define	EZCON4_MIN_Y	( 24 )
#define	EZCON4_MAX_Y	( 47 )

#define	EZCON5_MIN_X	( 143 )
#define	EZCON5_MAX_X	( 120 )
#define	EZCON5_MIN_Y	( 24 )
#define	EZCON5_MAX_Y	( 18 )

#define	EZCND_MAX_RPM	( 300 )
#define	EZCND_DEF_RPM	( 44 )		// 300 = 256 + EZCND_DEF_RPM



static s16 BPL_EzCndPosGet( u32 prm, s16 max, s16 min )
{
	u32	dot;

	prm += EZCND_DEF_RPM;

	if( min > max ){
		dot = ( ( min - max ) * prm ) << 16;
		dot = ( dot / EZCND_MAX_RPM ) >> 16;
		return min + (s16)dot * -1;
	}
	
	dot = ( ( max - min ) * prm ) << 16;
	dot = ( dot / EZCND_MAX_RPM ) >> 16;
	return min + (s16)dot;
}


static void BPL_EzConditionPut( BPLIST_WORK * wk )
{
	BPL_POKEDATA * pd;
	u16	i;

	pd = &wk->poke[wk->dat->sel_poke];

	BPL_PokeIconAnmChg( wk->cap[BPL_CA_CND1], 0 );
	BPL_PokeIconAnmChg( wk->cap[BPL_CA_CND2], 1 );
	BPL_PokeIconAnmChg( wk->cap[BPL_CA_CND3], 3 );
	BPL_PokeIconAnmChg( wk->cap[BPL_CA_CND4], 4 );
	BPL_PokeIconAnmChg( wk->cap[BPL_CA_CND5], 2 );

	BPL_ClactOn(
		wk->cap[BPL_CA_CND1],
		BPL_EzCndPosGet( pd->style, EZCON1_MAX_X, EZCON1_MIN_X ),
		BPL_EzCndPosGet( pd->style, EZCON1_MAX_Y, EZCON1_MIN_Y ) );
	BPL_ClactOn(
		wk->cap[BPL_CA_CND2],
		BPL_EzCndPosGet( pd->beautiful, EZCON2_MAX_X, EZCON2_MIN_X ),
		BPL_EzCndPosGet( pd->beautiful, EZCON2_MAX_Y, EZCON2_MIN_Y ) );
	BPL_ClactOn(
		wk->cap[BPL_CA_CND3],
		BPL_EzCndPosGet( pd->cute, EZCON3_MAX_X, EZCON3_MIN_X ),
		BPL_EzCndPosGet( pd->cute, EZCON3_MAX_Y, EZCON3_MIN_Y ) );
	BPL_ClactOn(
		wk->cap[BPL_CA_CND4],
		BPL_EzCndPosGet( pd->clever, EZCON4_MAX_X, EZCON4_MIN_X ),
		BPL_EzCndPosGet( pd->clever, EZCON4_MAX_Y, EZCON4_MIN_Y ) );
	BPL_ClactOn(
		wk->cap[BPL_CA_CND5],
		BPL_EzCndPosGet( pd->strong, EZCON5_MAX_X, EZCON5_MIN_X ),
		BPL_EzCndPosGet( pd->strong, EZCON5_MAX_Y, EZCON5_MIN_Y ) );
}


//============================================================================================
//	�J�[�\��
//============================================================================================
static void BPL_ClactCursorAdd( BPLIST_WORK * wk )
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

static void BPL_CursorDel( BPLIST_WORK * wk )
{
	BCURSOR_ActorDelete( BAPP_CursorMvWkGetBCURSOR_PTR( wk->cmv_wk ) );
	BCURSOR_ResourceFree(
		wk->crp, CHR_ID_CURSOR, PAL_ID_CURSOR, CEL_ID_CURSOR, ANM_ID_CURSOR );
}


// �|�P�����I����ʈړ��e�[�u��
static const POINTER_WORK P1_CursorPosTbl[] =
{
	{   8,   8, 120,  40, 6, 2, 6, 1 },		// 0
	{ 136,  16, 248,  48, 4, 3, 0, 2 },		// 1
	{   8,  56, 120,  88, 0, 4, 1, 3 },		// 2
	{ 136,  64, 248,  96, 1, 5, 2, 4 },		// 3
	{   8, 104, 120, 136, 2, 1, 3, 5 },		// 4
	{ 136, 112, 248, 144, 3, 6, 4, 6 },		// 5
	{ 224, 160, 248, 184, 5, 0, 5, 0 },		// 6�i�߂�j
};
static const POINTER_WORK Chg_CursorPosTbl[] =
{
	{  16,  16, 240, 136, 0, BAPP_CMV_RETBIT|1, 0, 0 },		// 0 : ���ꂩ����
	{   8, 160,  96, 184, 0, 1, 1, 2 },						// 1 : ����������
	{ 112, 160, 200, 184, 0, 2, 1, 3 },						// 2 : �Z������
	{ 224, 160, 248, 184, 0, 3, 2, 3 },						// 3 : �߂�
};
static const POINTER_WORK StMain_CursorPosTbl[] =
{
	{   8, 160,  32, 184, 0, 0, 0, 1 },		// 0 : ��
	{  48, 160,  72, 184, 1, 1, 0, 2 },		// 1 : ��
	{ 104, 160, 192, 184, 2, 2, 1, 3 },		// 2 : �Z������
	{ 224, 160, 248, 184, 3, 3, 2, 3 },		// 3 : �߂�
};
static const POINTER_WORK StWazaSel_CursorPosTbl[] =
{
	{   8,  56, 120,  88, 0, 2, 0, 1 },		// 0 : �Z�P
	{ 136,  56, 248,  88, 1, 3, 0, 1 },		// 1 : �Z�Q
	{   8, 104, 120, 136, 0, BAPP_CMV_RETBIT|4, 2, 3 },		// 2 : �Z�R
	{ 136, 104, 248, 136, 1, BAPP_CMV_RETBIT|7, 2, 3 },		// 3 : �Z�S
	{   8, 160,  32, 184, 2, 4, 4, 5 },		// 4 : ��
	{  48, 160,  72, 184, 2, 5, 4, 6 },		// 5 : ��
	{ 104, 160, 192, 184, 3, 6, 5, 7 },		// 6 : ����������
	{ 224, 160, 248, 184, 3, 7, 6, 7 },		// 7 : �߂�
};
static const POINTER_WORK StWazaInfo_CursorPosTbl[] =
{
	{  92, 157, 124, 165, 0, 2, 0, 1 },		// 0 : �Z�P
	{ 132, 157, 164, 165, 1, 3, 0, 4 },		// 1 : �Z�Q
	{  92, 173, 124, 181, 0, 2, 2, 3 },		// 2 : �Z�R
	{ 132, 173, 164, 181, 1, 3, 2, 4 },		// 3 : �Z�S
	{ 224, 160, 248, 184, 4, 4, BAPP_CMV_RETBIT|3, 4 },		// 4 : �߂�
};
static const POINTER_WORK DelSel_CursorPosTbl[] =
{
	{   8,  56, 120,  88, 5, 2, 0, 1 },						// 0 : �Z�P��ʂ�
	{ 136,  56, 248,  88, 5, 3, 0, 1 },						// 1 : �Z�Q��ʂ�
	{   8, 104, 120, 136, 0, 4, 2, 3 },						// 2 : �Z�R��ʂ�
	{ 136, 104, 248, 136, 1, 6, 2, 3 },						// 3 : �Z�S��ʂ�
	{  72, 152, 184, 184, 2, 4, 4, 6 },						// 4 : �Z�T��ʂ�
	{ 192,   8, 248,  24, 5, BAPP_CMV_RETBIT|1, 0, 5 },		// 5 : �퓬<->�R���e�X�g�̐؂�ւ�
	{ 224, 160, 248, 184, 3, 6, 4, 6 },						// 6 : �߂�
};

static const POINTER_WORK DelInfo_CursorPosTbl[] =
{
	{   8, 160, 200, 184, 1, 0, 0, 2 },						// 0 : �킷���
	{ 192,   8, 248,  24, 1, BAPP_CMV_RETBIT|2, 0, 1 },		// 1 : �퓬<->�R���e�X�g�̐؂�ւ�
	{ 224, 160, 248, 184, 1, 2, 0, 2 },						// 2 : �߂�
};

static const POINTER_WORK PPRcv_CursorPosTbl[] =
{
	{   8,  56, 120,  88, 0, 2, 0, 1 },						// 0 : �Z�P��
	{ 136,  56, 248,  88, 1, 3, 0, 1 },						// 1 : �Z�Q��
	{   8, 104, 120, 136, 0, 4, 2, 3 },						// 2 : �Z�R��
	{ 136, 104, 248, 136, 1, 4, 2, 3 },						// 3 : �Z�S��
	{ 224, 160, 248, 184, BAPP_CMV_RETBIT|3, 4, 4, 4 },		// 4 : �߂�
};

static const POINTER_WORK * const CursorPosTable[] = {
	P1_CursorPosTbl,			// �|�P�����I���y�[�W
	Chg_CursorPosTbl,			// �|�P��������ւ��y�[�W
	StMain_CursorPosTbl,		// �X�e�[�^�X���C���y�[�W
	StWazaSel_CursorPosTbl,		// �X�e�[�^�X�Z�I���y�[�W
	StWazaInfo_CursorPosTbl,	// �X�e�[�^�X�Z�ڍ׃y�[�W
	PPRcv_CursorPosTbl,			// PP�񕜋Z�I���y�[�W
	DelSel_CursorPosTbl,		// �X�e�[�^�X�Z�Y��P�y�[�W�i�퓬�Z�I���j
	DelInfo_CursorPosTbl,		// �X�e�[�^�X�Z�Y��Q�y�[�W�i�퓬�Z�ڍׁj
	DelSel_CursorPosTbl,		// �X�e�[�^�X�Z�Y��R�y�[�W�i�R���e�X�g�Z�I���j
	DelInfo_CursorPosTbl,		// �X�e�[�^�X�Z�Y��S�y�[�W�i�R���e�X�g�Z�ڍׁj
};

/*
#define	P1_DEF_CMV_TBL	( 0x40 )	// �y�[�W�P�̃f�t�H���g�J�[�\���ړ��e�[�u��
#define	P2_DEF_CMV_TBL	( 0x1e1 )	// �y�[�W�Q�̃f�t�H���g�J�[�\���ړ��e�[�u��
#define	P7_DEF_CMV_TBL	( 0x10 )	// �y�[�W�V�̃f�t�H���g�J�[�\���ړ��e�[�u��

static void BPL_P1CursorMvTblMake( BPLIST_WORK * wk )
{
	u32	tbl;
	u32	i;

	tbl = P1_DEF_CMV_TBL;
	for( i=0; i<6; i++ ){
		if( wk->poke[i].mons == 0 ){ continue; }
		tbl |= (1<<i);
	}
	BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, tbl );
}

void BPL_P2CursorMvTblMake( BPLIST_WORK * wk )
{
	u32	tbl;
	u32	i;

	tbl = P2_DEF_CMV_TBL;
	for( i=0; i<4; i++ ){
		if( wk->poke[wk->dat->sel_poke].waza[i].id == 0 ){ continue; }
		tbl |= (1<<(i+1));
	}
	BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, tbl );
}

static void BPL_P7CursorMvTblMake( BPLIST_WORK * wk )
{
	u32	tbl;
	u32	i;

	tbl = P7_DEF_CMV_TBL;
	for( i=0; i<4; i++ ){
		if( wk->poke[wk->dat->sel_poke].waza[i].id == 0 ){ continue; }
		tbl |= (1<<i);
	}
	BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, tbl );
}
*/

#define	WAZADEL_SEL_MV_TBL_N	( 0x7f )	// �Z�Y��̋Z�I���̃J�[�\���ړ��e�[�u���i�ʏ�j
#define	WAZADEL_SEL_MV_TBL_C	( 0x5f )	// �Z�Y��̋Z�I���̃J�[�\���ړ��e�[�u���i�R���e�X�g�Ȃ��j
#define	WAZADEL_MAIN_MV_TBL_N	( 7 )	// �Z�Y��̏ڍׂ̃J�[�\���ړ��e�[�u���i�ʏ�j
#define	WAZADEL_MAIN_MV_TBL_C	( 5 )	// �Z�Y��̏ڍׂ̃J�[�\���ړ��e�[�u���i�R���e�X�g�Ȃ��j

static void BPL_WazaDelSelCursorMvTblMake( BPLIST_WORK * wk )
{
	if( wk->ev_contest == 0 ){
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, WAZADEL_SEL_MV_TBL_C );
	}else{
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, WAZADEL_SEL_MV_TBL_N );
	}
}

static void BPL_WazaDelMainCursorMvTblMake( BPLIST_WORK * wk )
{
	if( wk->ev_contest == 0 ){
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, WAZADEL_MAIN_MV_TBL_C );
	}else{
		BAPP_CursorMvWkSetMvTbl( wk->cmv_wk, WAZADEL_MAIN_MV_TBL_N );
	}
}


void BattlePokeList_CursorMoveSet( BPLIST_WORK * wk, u8 page )
{
	BAPP_CursorMvWkSetPoint( wk->cmv_wk, CursorPosTable[page] );

	switch( page ){

	case BPLIST_PAGE_SELECT:		// �|�P�����I���y�[�W
//		if( BAPP_CursorMvWkGetFlag( wk->cmv_wk ) == 1 ){
//			OS_Printf( "SEL_POS : %d\n", wk->dat->sel_poke );
			BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->dat->sel_poke );
//		}
//		BPL_P1CursorMvTblMake( wk );
		wk->chg_page_cp = 0;
		wk->dat->sel_wp = 0;
		break;

	case BPLIST_PAGE_POKE_CHG:		// �|�P��������ւ��y�[�W
		BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->chg_page_cp );
		wk->dat->sel_wp = 0;
		break;

	case BPLIST_PAGE_WAZA_SEL:		// �X�e�[�^�X�Z�I���y�[�W
	case BPLIST_PAGE_SKILL:			// �X�e�[�^�X�Z�ڍ׃y�[�W
		BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->dat->sel_wp );
		break;

/*
	case BPLIST_PAGE_MAIN:			// �X�e�[�^�X���C���y�[�W
//		if( BAPP_CursorMvWkGetFlag( wk->cmv_wk ) == 1 && wk->page == BPLIST_PAGE_SKILL ){
		if( wk->page == BPLIST_PAGE_SKILL ){
			BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->dat->sel_wp+1 );
		}
		BPL_P2CursorMvTblMake( wk );
		break;
*/
//	case BPLIST_PAGE_WAZA_SEL:		// �X�e�[�^�X�ڍ׃y�[�W
//	case BPLIST_PAGE_SKILL:			// �X�e�[�^�X�Z�y�[�W
//	case BPLIST_PAGE_WAZASET_BS:	// �X�e�[�^�X�Z�Y��P�y�[�W�i�퓬�Z�I���j
//	case BPLIST_PAGE_WAZASET_BI:	// �X�e�[�^�X�Z�Y��Q�y�[�W�i�퓬�Z�ڍׁj
/*
	case BPLIST_PAGE_PP_RCV:		// PP�񕜋Z�I���y�[�W
//		BPL_P7CursorMvTblMake( wk );
		break;
*/

	case BPLIST_PAGE_WAZASET_BS:	// �X�e�[�^�X�Z�Y��P�y�[�W�i�퓬�Z�I���j
	case BPLIST_PAGE_WAZASET_CS:	// �X�e�[�^�X�Z�Y��R�y�[�W�i�R���e�X�g�Z�I���j
		BPL_WazaDelSelCursorMvTblMake( wk );
		BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->wws_page_cp );
		break;

	case BPLIST_PAGE_WAZASET_BI:	// �X�e�[�^�X�Z�Y��Q�y�[�W�i�퓬�Z�ڍׁj
	case BPLIST_PAGE_WAZASET_CI:	// �X�e�[�^�X�Z�Y��S�y�[�W�i�R���e�X�g�Z�ڍׁj
		BPL_WazaDelMainCursorMvTblMake( wk );
		BAPP_CursorMvWkSetPos( wk->cmv_wk, wk->wwm_page_cp );
		break;
	}
}


void BattlePokeList_CursorOff( BPLIST_WORK * wk )
{
	BAPP_CursorMvWkSetFlag( wk->cmv_wk, 0 );
	BAPP_CursorMvWkPosInit( wk->cmv_wk );
	BCURSOR_OFF( BAPP_CursorMvWkGetBCURSOR_PTR( wk->cmv_wk ) );
}
