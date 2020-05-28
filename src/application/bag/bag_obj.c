//============================================================================================
/**
 * @file	bag_obj.c	
 * @brief	�o�b�O���OBJ����
 * @author	Hiroyuki Nakamura
 * @date	05.10.31
 */
//============================================================================================
#include "common.h"
#include "gflib/touchpanel.h"
#include "system/gamedata.h"
#include "system/procsys.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/pm_str.h"
#include "system/lib_pack.h"
#include "system/snd_tool.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/brightness.h"
#include "system/buflen.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "savedata/config.h"
#include "itemtool/item.h"
#include "battle/wazatype_icon.h"
#include "battle/battle_common.h"
#include "poketool/waza_tool.h"
#include "../../field/shop_gra.naix"

#define	BAG_OBJ_H_GLOBAL
#include "application/bag.h"
#include "bag_main.h"
#include "bag_obj.h"
#include "bag_gra.naix"


//============================================================================================
//	�萔��`
//============================================================================================
enum {
	PCMV_SEQ_WAIT = 0,
	PCMV_SEQ_MOVE,
};

#define	BMP_P_ICON_PX	( 0 )
#define	BMP_P_ICON_PY	( 11 )
#define	BMP_P_ICON_SX	( 12 )
#define	BMP_P_ICON_SY	( 2 )


#define	CLACT_ID_COMMON		( 49401 )	// ���̉�ʂŎg�p����Z���A�N�^�[��ID

// �L�������\�[�XID
enum {
	CHR_ID_BAG = CLACT_ID_COMMON,		// �o�b�O
	CHR_ID_POKECURSOR,					// �|�P�b�g�J�[�\��
	CHR_ID_SELCURSOR,					// �A�C�e���I���J�[�\��
	CHR_ID_CHGCURSOR,					// ����ւ��J�[�\��
	CHR_ID_POKEARROW,					// �|�P�b�g�ړ����
	CHR_ID_BUTTONEFF,					// �{�^���G�t�F�N�g
	CHR_ID_ITEMICON,					// �A�C�e���A�C�R��
	CHR_ID_NUMARROW,					// ���I����
	CHR_ID_TYPEICON,					// �^�C�v�A�C�R��
	CHR_ID_KINDICON,					// ���ރA�C�R��

	CHR_ID_MAX = CHR_ID_KINDICON - CLACT_ID_COMMON + 1
};
// �p���b�g���\�[�XID
enum {
	PAL_ID_BAG = CLACT_ID_COMMON,		// �o�b�O
	PAL_ID_CURSOR,						// �J�[�\���֘A
	PAL_ID_BUTTONEFF,					// �{�^���G�t�F�N�g
	PAL_ID_ITEMICON,					// �A�C�e���A�C�R��
	PAL_ID_NUMARROW,					// ���I����
	PAL_ID_TYPEICON,					// �^�C�v�A�C�R��

	PAL_ID_MAX = PAL_ID_TYPEICON - CLACT_ID_COMMON + 1
};
// �Z�����\�[�XID
enum {
	CEL_ID_BAG = CLACT_ID_COMMON,		// �o�b�O
	CEL_ID_POKECURSOR,					// �|�P�b�g�J�[�\��
	CEL_ID_SELCURSOR,					// �A�C�e���I���J�[�\��
	CEL_ID_CHGCURSOR,					// ����ւ��J�[�\��
	CEL_ID_POKEARROW,					// �|�P�b�g�ړ����
	CEL_ID_BUTTONEFF,					// �{�^���G�t�F�N�g
	CEL_ID_ITEMICON,					// �A�C�e���A�C�R��
	CEL_ID_NUMARROW,					// ���I����
	CEL_ID_TYPEICON,					// �^�C�v�A�C�R��

	CEL_ID_MAX = CEL_ID_TYPEICON - CLACT_ID_COMMON + 1
};
// �Z���A�j�����\�[�XID
enum {
	ANM_ID_BAG = CLACT_ID_COMMON,		// �o�b�O
	ANM_ID_POKECURSOR,					// �|�P�b�g�J�[�\��
	ANM_ID_SELCURSOR,					// �A�C�e���I���J�[�\��
	ANM_ID_CHGCURSOR,					// ����ւ��J�[�\��
	ANM_ID_POKEARROW,					// �|�P�b�g�ړ����
	ANM_ID_BUTTONEFF,					// �{�^���G�t�F�N�g
	ANM_ID_ITEMICON,					// �A�C�e���A�C�R��
	ANM_ID_NUMARROW,					// ���I����
	ANM_ID_TYPEICON,					// �^�C�v�A�C�R��

	ANM_ID_MAX = ANM_ID_TYPEICON - CLACT_ID_COMMON + 1
};

#define	NUM_ARROW_DEL_UX	( 220 )		// ���I������X���W�i�̂Ă�j
#define	NUM_ARROW_DEL_UY	( 156 )		// ���I������Y���W�i�̂Ă�j
#define	NUM_ARROW_DEL_DX	( 220 )		// ���I�������X���W�i�̂Ă�j
#define	NUM_ARROW_DEL_DY	( 180 )		// ���I�������Y���W�i�̂Ă�j
#define	NUM_ARROW_SALE_UX	( 162 )		// ���I������X���W�i����j
#define	NUM_ARROW_SALE_UY	( 108 )		// ���I������Y���W�i����j
#define	NUM_ARROW_SALE_DX	( 162 )		// ���I�������X���W�i����j
#define	NUM_ARROW_SALE_DY	( 132 )		// ���I�������Y���W�i����j


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void BAGOBJ_ClactResManInit( BAG_WORK * wk );
static void BAGOBJ_ClactGraphicLoad( BAG_WORK * wk );
static void BAGOBJ_ClactAdd( BAG_WORK * wk );

static void PocketMvTblMake( BAG_WORK * wk );
static u8 PocketCursorObjPXGet( BAG_WORK * wk, u8 poke );
static void PocketCursorMove( BAG_WORK * wk );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// �Z���A�N�^�[�f�[�^
static const TCATS_OBJECT_ADD_PARAM_S ClactParamTbl[] =
{
	{	// �o�b�O
		48, 50, 0,
		0, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ CHR_ID_BAG, PAL_ID_BAG, CEL_ID_BAG, ANM_ID_BAG, 0, 0 },
		1, 0
	},
	{	// �|�P�b�g�J�[�\��
		13, 97, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ CHR_ID_POKECURSOR, PAL_ID_CURSOR, CEL_ID_POKECURSOR, ANM_ID_POKECURSOR, 0, 0 },
		0, 0
	},
	{	// �|�P�b�g�����
		2, 96, 0,
		1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ CHR_ID_POKEARROW, PAL_ID_CURSOR, CEL_ID_POKEARROW, ANM_ID_POKEARROW, 0, 0 },
		0, 0
	},
	{	// �|�P�b�g�E���
		98, 96, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ CHR_ID_POKEARROW, PAL_ID_CURSOR, CEL_ID_POKEARROW, ANM_ID_POKEARROW, 0, 0 },
		0, 0
	},
	{	// �A�C�e���I���J�[�\��
		CURSOR_ACT_PX, CURSOR_ACT_PY, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ CHR_ID_SELCURSOR, PAL_ID_CURSOR, CEL_ID_SELCURSOR, ANM_ID_SELCURSOR, 0, 0 },
		1, 0
	},
	{	// �A�C�e������ւ��J�[�\��
		177, 14, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ CHR_ID_CHGCURSOR, PAL_ID_CURSOR, CEL_ID_CHGCURSOR, ANM_ID_CHGCURSOR, 0, 0 },
		1, 0
	},
	{	// �{�^���G�t�F�N�g
		0, 0, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DSUB,
		{ CHR_ID_BUTTONEFF, PAL_ID_BUTTONEFF, CEL_ID_BUTTONEFF, ANM_ID_BUTTONEFF, 0, 0 },
		0, 0
	},
	{	// �A�C�e���A�C�R��
		22,172, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ CHR_ID_ITEMICON, PAL_ID_ITEMICON, CEL_ID_ITEMICON, ANM_ID_ITEMICON, 0, 0 },
		1, 0
	},
	{	// �����I���E��
		220,156, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ CHR_ID_NUMARROW, PAL_ID_NUMARROW, CEL_ID_NUMARROW, ANM_ID_NUMARROW, 0, 0 },
		0, 0
	},
	{	// �����I���E��
		220,180, 0,
		1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ CHR_ID_NUMARROW, PAL_ID_NUMARROW, CEL_ID_NUMARROW, ANM_ID_NUMARROW, 0, 0 },
		0, 0
	},
	{	// �^�C�v�A�C�R��
		64, 152, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ CHR_ID_TYPEICON, PAL_ID_TYPEICON, CEL_ID_TYPEICON, ANM_ID_TYPEICON, 0, 0 },
		0, 0
	},
	{	// ���ރA�C�R��
		168, 152, 0,
		0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
		{ CHR_ID_KINDICON, PAL_ID_TYPEICON, CEL_ID_TYPEICON, ANM_ID_TYPEICON, 0, 0 },
		0, 0
	},
};



//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[������
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BagCellActorInit( BAG_WORK * wk )
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// MAIN DISP OBJ ON
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );		// SUB DISP OBJ ON

	initVramTransferManagerHeap( 32, HEAPID_BAG );

	BAGOBJ_ClactResManInit( wk );
	BAGOBJ_ClactGraphicLoad( wk );
	BAGOBJ_ClactAdd( wk );
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
static void BAGOBJ_ClactResManInit( BAG_WORK * wk )
{
	TCATS_RESOURCE_NUM_LIST	crnl = { CHR_ID_MAX, PAL_ID_MAX, CEL_ID_MAX, ANM_ID_MAX, 0, 0 };

	wk->csp = CATS_AllocMemory( HEAPID_BAG );
	wk->crp = CATS_ResourceCreate( wk->csp );
	{
		TCATS_OAM_INIT	coi = {
			0, 128,
			0, 32,
			0, 128,
			0, 32,
		};
		TCATS_CHAR_MANAGER_MAKE ccmm = {
			BAG_ACT_MAX,
			1024*128,
			1024*16,
			GX_OBJVRAMMODE_CHAR_1D_32K,
			GX_OBJVRAMMODE_CHAR_1D_32K
		};
		CATS_SystemInit( wk->csp, &coi, &ccmm, 32 );
	}
	CATS_ClactSetInit( wk->csp, wk->crp, BAG_ACT_MAX );
	CATS_ResourceManagerInit( wk->csp, wk->crp, &crnl );
}

static void BAGOBJ_ClactGraphicLoad( BAG_WORK * wk )
{
	u32	chr, pal;

	if( wk->sex == 0 ){
		chr = NARC_bag_gra_bag_01_NCGR;
		pal = NARC_bag_gra_bag_01_NCLR;
	}else{
		chr = NARC_bag_gra_bag_02_NCGR;
		pal = NARC_bag_gra_bag_02_NCLR;
	}

	// �o�b�O
	// �L����
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_BAG_GRA, chr, 0, NNS_G2D_VRAM_TYPE_2DMAIN, CHR_ID_BAG );
	// �|�P�b�g�J�[�\��
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_BAG_GRA,
		NARC_bag_gra_bag_pokecur_NCGR, 0, NNS_G2D_VRAM_TYPE_2DMAIN, CHR_ID_POKECURSOR );
	// �A�C�e���I���J�[�\��
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_BAG_GRA,
		NARC_bag_gra_bag_selcur_NCGR, 0, NNS_G2D_VRAM_TYPE_2DMAIN, CHR_ID_SELCURSOR );
	// ����ւ��J�[�\��
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_BAG_GRA,
		NARC_bag_gra_bag_selcur2_NCGR, 0, NNS_G2D_VRAM_TYPE_2DMAIN, CHR_ID_CHGCURSOR );
	// �|�P�b�g�ړ����
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_BAG_GRA,
		NARC_bag_gra_bag_arrow_NCGR, 0, NNS_G2D_VRAM_TYPE_2DMAIN, CHR_ID_POKEARROW );
	// �{�^���G�t�F�N�g
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_BAG_GRA,
		NARC_bag_gra_button_ef_NCGR, 0, NNS_G2D_VRAM_TYPE_2DSUB, CHR_ID_BUTTONEFF );
	// ���I����
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_SHOP_GRA,
		NARC_shop_gra_shop_arw_NCGR, 0, NNS_G2D_VRAM_TYPE_2DMAIN, CHR_ID_NUMARROW );
	// �A�C�e���A�C�R��
	CATS_LoadResourceCharArc(
		wk->csp, wk->crp, ARC_ITEMICON,
		GetItemIndex(0,ITEM_GET_ICON_CGX), 0, NNS_G2D_VRAM_TYPE_2DMAIN, CHR_ID_ITEMICON );
	// �^�C�v�A�C�R��
	WazaTypeIcon_CharResourceLoad( wk->csp, wk->crp, NNS_G2D_VRAM_TYPE_2DMAIN, 0, CHR_ID_TYPEICON );
	// ���ރA�C�R��
	WazaKindIcon_CharResourceLoad( wk->csp, wk->crp, NNS_G2D_VRAM_TYPE_2DMAIN, 0, CHR_ID_KINDICON );

	// �p���b�g
	// �o�b�O
	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_BAG_GRA, pal, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, PAL_ID_BAG );
	// �J�[�\���֘A
	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_BAG_GRA,
		NARC_bag_gra_bag_cursor_NCLR, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, PAL_ID_CURSOR );
	// �A�C�e���A�C�R��
	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_ITEMICON,
		GetItemIndex(0,ITEM_GET_ICON_PAL), 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, PAL_ID_ITEMICON );
	// ���I����
	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_SHOP_GRA,
		NARC_shop_gra_shop_obj_NCLR, 0, 2, NNS_G2D_VRAM_TYPE_2DMAIN, PAL_ID_NUMARROW );
	// �^�C�v�A�C�R��
	WazaTypeIcon_PlttResourceLoad( wk->csp, wk->crp, NNS_G2D_VRAM_TYPE_2DMAIN, PAL_ID_TYPEICON );
	// �{�^���G�t�F�N�g
	CATS_LoadResourcePlttArc(
		wk->csp, wk->crp, ARC_BAG_GRA,
		NARC_bag_gra_button_ef_NCLR, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, PAL_ID_BUTTONEFF );

	// �Z��
	// �o�b�O
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_bag_01_NCER, 0, CEL_ID_BAG );
	// �|�P�b�g�J�[�\��
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_bag_pokecur_NCER, 0, CEL_ID_POKECURSOR );
	// �A�C�e���I���J�[�\��
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_bag_selcur_NCER, 0, CEL_ID_SELCURSOR );
	// ����ւ��J�[�\��
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_bag_selcur2_NCER, 0, CEL_ID_CHGCURSOR );
	// �|�P�b�g�ړ����
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_bag_arrow_NCER, 0, CEL_ID_POKEARROW );
	// �{�^���G�t�F�N�g
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_button_ef_NCER, 0, CEL_ID_BUTTONEFF );
	// �A�C�e���A�C�R��
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_ITEMICON, ItemIconCellGet(), 0, CEL_ID_ITEMICON );
	// ���I����
	CATS_LoadResourceCellArc(
		wk->csp, wk->crp, ARC_SHOP_GRA, NARC_shop_gra_shop_arw_NCER, 0, CEL_ID_NUMARROW );

	// �Z���A�j��
	// �o�b�O
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_bag_01_NANR, 0, ANM_ID_BAG );
	// �|�P�b�g�J�[�\��
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_bag_pokecur_NANR, 0, ANM_ID_POKECURSOR );
	// �A�C�e���I���J�[�\��
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_bag_selcur_NANR, 0, ANM_ID_SELCURSOR );
	// ����ւ��J�[�\��
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_bag_selcur2_NANR, 0, ANM_ID_CHGCURSOR );
	// �|�P�b�g�ړ����
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_bag_arrow_NANR, 0, ANM_ID_POKEARROW );
	// �{�^���G�t�F�N�g
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_BAG_GRA, NARC_bag_gra_button_ef_NANR, 0, ANM_ID_BUTTONEFF );
	// �A�C�e���A�C�R��
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_ITEMICON, ItemIconCAnmGet(), 0, ANM_ID_ITEMICON );
	// ���I����
	CATS_LoadResourceCellAnmArc(
		wk->csp, wk->crp, ARC_SHOP_GRA, NARC_shop_gra_shop_arw_NANR, 0, ANM_ID_NUMARROW );

	// �^�C�v�A�C�R���̃Z���ƃA�j��
	WazaTypeIcon_CellAnmResourceLoad( wk->csp, wk->crp, CEL_ID_TYPEICON, ANM_ID_TYPEICON );
}


//--------------------------------------------------------------------------------------------
/**
 * �o�b�O��ʂ̃Z���A�N�^�[���Z�b�g
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BAGOBJ_ClactAdd( BAG_WORK * wk )
{
	u32	i;

	for( i=0; i<BAG_ACT_MAX; i++ ){
		wk->cap[i] = CATS_ObjectAdd_S( wk->csp, wk->crp, &ClactParamTbl[i] );
	}

	CATS_ObjectEnableCap( wk->cap[ ACT_LIST_SEL_CHANGE ], ACT_OFF );
	CATS_ObjectEnableCap( wk->cap[ ACT_BUTTON_ANM ], ACT_OFF );

	CATS_ObjectEnableCap( wk->cap[ ACT_TYPE ], ACT_OFF );
	CATS_ObjectEnableCap( wk->cap[ ACT_KIND ], ACT_OFF );

	if( wk->dat->mode == BAG_MODE_MIX || wk->dat->mode == BAG_MODE_MIX_SIO ){
		CATS_ObjectEnableCap( wk->cap[ ACT_POKE_CURSOR ], ACT_OFF );
	}

	if( wk->p_max == 1 ){
		CATS_ObjectEnableCap( wk->cap[ ACT_POKE_ARROW_LEFT ], ACT_OFF );
		CATS_ObjectEnableCap( wk->cap[ ACT_POKE_ARROW_RIGHT ], ACT_OFF );
	}

	Bag_NumArrowPut( wk, ACT_OFF );

	CATS_ObjectAnimeSeqSetCap( wk->cap[ACT_BAG], wk->dat->p_data[wk->dat->p_now].type );
	CATS_ObjectPosSetCap(
		wk->cap[ACT_POKE_CURSOR], PocketCursorObjPXGet( wk, wk->dat->p_now ), 97 );
	CATS_ObjectPosSetCap(
		wk->cap[ACT_LIST_SEL_CURSOR],
		CURSOR_ACT_PX, CURSOR_ACT_PY + (wk->dat->p_data[wk->dat->p_now].cur-1) * 16 );

	{
		VecFx32 sca = { FX32_ONE, FX32_ONE, FX32_ONE };
		CLACT_SetScaleAffine( wk->cap[ACT_BAG]->act, &sca, CLACT_AFFINE_DOUBLE );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[���
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BAGOBJ_ClactFree( BAG_WORK * wk )
{
	u32	i;

	for( i=0; i<BAG_ACT_MAX; i++ ){
		CATS_ActorPointerDelete_S( wk->cap[i] );
	}
	CATS_ResourceDestructor_S( wk->csp, wk->crp );
	CATS_FreeMemory( wk->csp );
}

void Bag_ObjAnmMain( BAG_WORK * wk )
{
	u32	i;

	for( i=0; i<BAG_ACT_MAX; i++ ){
		CATS_ObjectUpdateCap( wk->cap[i] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e���A�C�R���ύX
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 * @param	item	�A�C�e���ԍ�
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BagItemIconChange( BAG_WORK * wk, u16 item )
{
	CATS_ChangeResourceCharArc(
		wk->csp, wk->crp,
		ARC_ITEMICON, GetItemIndex( item, ITEM_GET_ICON_CGX ), 0, CHR_ID_ITEMICON );
	CATS_ChangeResourcePlttArc(
		wk->csp, wk->crp,
		ARC_ITEMICON, GetItemIndex( item, ITEM_GET_ICON_PAL ), 0, PAL_ID_ITEMICON );
}




void BagObj_CursorPalChg( BAG_WORK * wk, u8 num )
{
	CATS_ObjectPaletteSetCap( wk->cap[ACT_LIST_SEL_CURSOR], num );
	CATS_ObjectPaletteSetCap( wk->cap[ACT_POKE_CURSOR], num );
}



//============================================================================================
//	�|�P�b�g�J�[�\��
//============================================================================================
u8 BagPocketCursorMoveCheck( BAG_WORK * wk )
{
	if( wk->pcmv.req == PCMV_SEQ_WAIT ){
		return TRUE;
	}
	return FALSE;
}

void BagPocketCursorMoveInit( BAG_WORK * wk )
{
	wk->pcmv.cnt  = 0;
//	wk->pcmv.next = next;
	wk->pcmv.req  = PCMV_SEQ_MOVE;
	PocketMvTblMake( wk );
}

void BagPocketCursorMoveMain( BAG_WORK * wk )
{
	switch( wk->pcmv.req ){
	case PCMV_SEQ_WAIT:
		break;
	case PCMV_SEQ_MOVE:
		PocketCursorMove( wk );
		break;
	}
}

static void PocketCursorMove( BAG_WORK * wk )
{
	VecFx32 vec;
		
	vec = *(CLACT_GetMatrix( wk->cap[ACT_POKE_CURSOR]->act ));

	if( wk->pcmv.mv == 0 ){
		vec.x -= wk->pcmv.tbl[wk->pcmv.cnt];
	}else{
		vec.x += wk->pcmv.tbl[wk->pcmv.cnt];
	}
	CLACT_SetMatrix( wk->cap[ACT_POKE_CURSOR]->act, &vec );

	wk->pcmv.cnt++;
	if( wk->pcmv.cnt == 8 ){
		vec.x = PocketCursorObjPXGet( wk, wk->p_next ) * FX32_ONE;
		CLACT_SetMatrix( wk->cap[ACT_POKE_CURSOR]->act, &vec );
		wk->pcmv.req = PCMV_SEQ_WAIT;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g�J�[�\��OBJ��X���W
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 * @param	poke	�|�P�b�g�ԍ�
 *
 * @return	�J�[�\��OBJ��X���W
 *
 * @li	�|�P�b�g�ԍ�����J�[�\���ʒu���擾����
 */
//--------------------------------------------------------------------------------------------
static u8 PocketCursorObjPXGet( BAG_WORK * wk, u8 poke )
{
	return BMP_P_ICON_PX * 8 + wk->p_icon_gx + wk->p_icon_sx * poke + P_ICON_DEF_PX;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g�J�[�\���ړ��e�[�u���쐬
 *
 * @param	wk		�o�b�O��ʂ̃��[�N
 *
 * @return	none
 *
 *	8sync�ňړ�����
 *		0sync =  0%, 1sync = 40%, 2sync = 25%, 3sync = 15%,
 *		4sync = 10%, 5sync =  7%, 6sync =  3%, 7sync =  0%
 */
//--------------------------------------------------------------------------------------------
static void PocketMvTblMake( BAG_WORK * wk )
{
	VecFx32	vec;
	fx32	p;

	vec = *(CLACT_GetMatrix( wk->cap[ACT_POKE_CURSOR]->act ));
	p   = PocketCursorObjPXGet( wk, wk->p_next ) * FX32_ONE;

	if( p < vec.x ){
		p = ( vec.x - p ) / 100;
		wk->pcmv.mv = 0;
	}else{
		p = ( p - vec.x ) / 100;
		wk->pcmv.mv = 1;
	}

	wk->pcmv.tbl[0] = 0;
	wk->pcmv.tbl[1] = p * 40;
	wk->pcmv.tbl[2] = p * 25;
	wk->pcmv.tbl[3] = p * 15;
	wk->pcmv.tbl[4] = p * 10;
	wk->pcmv.tbl[5] = p *  7;
	wk->pcmv.tbl[6] = p *  3;
	wk->pcmv.tbl[7] = 0;
}

void Bag_NumArrowSet( BAG_WORK * wk, u8 mode )
{
	// ���Ă�
	if( mode == 0 ){
		CATS_ObjectPosSetCap( wk->cap[ACT_NUM_ARROW_UP], NUM_ARROW_DEL_UX, NUM_ARROW_DEL_UY );
		CATS_ObjectPosSetCap( wk->cap[ACT_NUM_ARROW_DOWN], NUM_ARROW_DEL_DX, NUM_ARROW_DEL_DY );
	// ����
	}else{
		CATS_ObjectPosSetCap( wk->cap[ACT_NUM_ARROW_UP], NUM_ARROW_SALE_UX, NUM_ARROW_SALE_UY );
		CATS_ObjectPosSetCap( wk->cap[ACT_NUM_ARROW_DOWN], NUM_ARROW_SALE_DX, NUM_ARROW_SALE_DY );
	}
	Bag_NumArrowPut( wk, ACT_ON );
}

void Bag_NumArrowPut( BAG_WORK * wk, u8 flg )
{
	CATS_ObjectEnableCap( wk->cap[ ACT_NUM_ARROW_UP ], flg );
	CATS_ObjectEnableCap( wk->cap[ ACT_NUM_ARROW_DOWN ], flg );
}


void BagObj_WazaIconPut( BAG_WORK * wk, u16 item, u8 flg )
{
	u16	waza;
	u16	type;
	u16	kind;

	CATS_ObjectEnableCap( wk->cap[ ACT_TYPE ], flg );
	CATS_ObjectEnableCap( wk->cap[ ACT_KIND ], flg );

	if( flg == ACT_OFF ){ return; }

	waza = GetWazaNoItem( item );
	type = WT_WazaDataParaGet( waza, ID_WTD_wazatype );
	kind = WT_WazaDataParaGet( waza, ID_WTD_kind );

	CATS_ChangeResourceCharArc(
		wk->csp, wk->crp, WazaTypeIcon_ArcIDGet(),
		WazaTypeIcon_CgrIDGet(type), WAZATYPEICON_COMP_CHAR, CHR_ID_TYPEICON );
	CATS_ObjectPaletteSetCap( wk->cap[ACT_TYPE], WazaTypeIcon_PlttOffsetGet(type)+6 );

	CATS_ChangeResourceCharArc(
		wk->csp, wk->crp, WazaKindIcon_ArcIDGet(),
		WazaKindIcon_CgrIDGet(kind), WAZAKINDICON_COMP_CHAR, CHR_ID_KINDICON );
	CATS_ObjectPaletteSetCap( wk->cap[ACT_KIND], WazaKindIcon_PlttOffsetGet(kind)+6 );
}




//--------------------------------------------------------------------------------------------
/**
 * �T�u�{�^���G�t�F�N�g
 */
//--------------------------------------------------------------------------------------------
void BagObj_SubButtonEffInit( BAG_WORK * wk, s16 x, s16 y )
{
	CATS_ObjectEnableCap( wk->cap[ACT_BUTTON_ANM], ACT_ON );
	CATS_ObjectPosSetCap( wk->cap[ACT_BUTTON_ANM], x, y );
	CATS_ObjectAnimeFrameSetCap( wk->cap[ACT_BUTTON_ANM], 0 );
	CATS_ObjectAnimeSeqSetCap( wk->cap[ACT_BUTTON_ANM], 0 );
}

void BagObj_SubButtonEffMain( BAG_WORK * wk )
{
	if( CATS_ObjectEnableGetCap( wk->cap[ACT_BUTTON_ANM] ) == ACT_ON ){
		CATS_ObjectUpdateNumCap( wk->cap[ACT_BUTTON_ANM], FX32_ONE );

		if( CATS_ObjectAnimeFrameGetCap( wk->cap[ACT_BUTTON_ANM] ) == 2 ){
			CATS_ObjectEnableCap( wk->cap[ACT_BUTTON_ANM], ACT_OFF );
		}
	}
}
