//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_fight_text.c
 *	@brief		�}�Ӑ퓬��̃e�L�X�g�f�[�^�\���V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.03.22
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "include/gflib/display.h"

#include "include/system/brightness.h"
#include "include/system/arc_util.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"
#include "include/msgdata/msg_zkn_height.h"
#include "include/msgdata/msg_zkn_gram.h"
#include "include/msgdata/msg_zkn_comment_00.h"
#include "include/msgdata/msg_zkn_type.h"
#include "include/poketool/pokefoot.h"
#include "include/poketool/poke_tool.h"
#include "include/poketool/poke_number.h"
#include "include/gflib/vram_transfer_manager.h"

#include "include/system/snd_tool.h"

#include "include/battle/battle_common.h"

#include "include/application/zukanlist/zukan.naix"
#include "include/application/zukanlist/zkn_sys_static.h"

#define	__ZKN_FIGHT_TEXT_H_GLOBAL
#include "include/application/zukanlist/zkn_fight_text.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------


#define ZKN_FIGHT_MANAG_RES_NUM		( 8 )
#define ZKN_FIGHT_FONTOAM_WORKNUM	( 3 )
#define ZKN_FIGHT_CLACT_WORKNUM		( 32 )
#define ZKN_FIGHT_CHAR_WORKNUM		( 32 )
#define ZKN_FIGHT_CHAR_AREA_SIZE_MAIN	( 1024 * 0x40 )	// 64k
#define ZKN_FIGHT_CHAR_AREA_SIZE_SUB	( 512 * 0x20 )	// 32k

#define ZKN_FIGHT_OAM_BG_PRI	( 2 )
#define ZKN_FIGHT_OAM_SOFT_PRI	( 32 )

// �w�i���W
#define ZKN_FIGHT_POKE_DRAW_FRAME_CX	( 0 )
#define ZKN_FIGHT_POKE_DRAW_FRAME_CY	( 3 )
#define ZKN_FIGHT_FOOT_FRAME_CX			( 12 )
#define ZKN_FIGHT_FOOT_FRAME_CY			( 8 )
#define ZKN_FIGHT_TEXT_FRAME_CX			( 0 )
#define ZKN_FIGHT_TEXT_FRAME_CY			( 16 )


// �������
#define ZKN_FIGHT_NUM_STR		( 64 )	// �o�b�t�@�T�C�Y

#define ZKN_FIGHT_TITLE_TEXT_X	( 32 )
#define ZKN_FIGHT_TITLE_TEXT_Y	( 1 )

//-------------------------------------
//	�\���V�[�P���X
//=====================================
enum
{
	ZKN_FIGHT_FADE_IN,
	ZKN_FIGHT_FADE_IN_WAIT,
	ZKN_FIGHT_SND_PLY,
	ZKN_FIGHT_SND_WAIT,
	ZKN_FIGHT_END
};

// �|�P�������X�g���W
#define ZKN_FIGHT_POKELIST_MAT_X	( 172 )
#define ZKN_FIGHT_POKELIST_MAT_Y	( 32 )

// ����
#define ZKN_FIGHT_FOOT_MAT_X	( 120 * FX32_ONE )
#define ZKN_FIGHT_FOOT_MAT_Y	( 88 * FX32_ONE )

// �^�C�v���W
#define ZKN_FIGHT_POKETYPE1_MAT_X	( 170 * FX32_ONE )
#define ZKN_FIGHT_POKETYPE2_MAT_X	( 220 * FX32_ONE )
#define ZKN_FIGHT_POKETYPE_MAT_Y	( 72 * FX32_ONE )
// ���ߐ�
enum{
	ZKN_FIGHT_TYPE_1,
	ZKN_FIGHT_TYPE_2,
	ZKN_FIGHT_TYPE_NUM
};

// �`�|�P�������W
#define ZKN_FIGHT_POKETYPE_TEXT_MAT_X	( 192 * FX32_ONE )
#define ZKN_FIGHT_POKETYPE_TEXT_MAT_Y	( 52 * FX32_ONE )


// �p���b�g�A�j��
enum{
	ZKN_FIGHT_PALANM_ONE,
	ZKN_FIGHT_PALANM_TWO,
	ZKN_FIGHT_PALANM_NUM
};
#define ZKN_FIGHT_PALANM_TIMING		( 16 )
#define ZKN_FIGHT_PALANN_PAL		( 0 )
#define ZKN_FIGHT_PALANN_PAL_NUM	( 1 )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	���Ճf�[�^
//=====================================
typedef struct {
	CLACT_WORK_PTR foot;
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];
} ZKN_FIGHT_FOOT;

//-------------------------------------
//	�`�|�P����
//=====================================
typedef struct {
	CLACT_WORK_PTR  poketype_text_tbl;
	ZKN_FONTOAM_DATA*  p_poketype_text;
} ZKN_FIGHT_POKETYPE_NAME;

//-------------------------------------
//	����
//=====================================
typedef struct {
	CLACT_WORK_PTR  type[ ZKN_FIGHT_TYPE_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resource�I�u�W�F�|�C���^
} ZKN_FIGHT_TYPE;

//-------------------------------------
//	�p���b�g�A�j�����[�N
//=====================================
typedef struct {
	void* p_pltt_buff[ ZKN_FIGHT_PALANM_NUM ];
	NNSG2dPaletteData* p_plt[ ZKN_FIGHT_PALANM_NUM ];
	int count;
	int anmtbl[ ZKN_FIGHT_PALANM_NUM ];
	int now_set;
} ZKN_PALANM_WORK;




//-------------------------------------
//	�`�惏�[�N
//=====================================
typedef struct _ZKN_FIGHT_TEXT_DRAW{
	GF_BGL_INI*			p_bgl;		// BGL
	GF_BGL_BMPWIN*		p_bmp;		// �r�b�g�}�b�v�E�B���h�E
	PALETTE_FADE_PTR	p_pfd;		// �p���b�g�t�F�[�h
	SOFT_SPRITE*		p_ssp;		// �\���|�P�����f�[�^
	CLACT_U_EASYRENDER_DATA render_data;	// �����_���[�f�[�^
	CLACT_SET_PTR		clact_set;	// �Z���A�N�^�[�Z�b�g
	CLACT_U_RES_MANAGER_PTR	res_manager[ ZKN_CLACT_RES_MANAGER_NUM ];	// ���\�[�X�}�l�[�W��
	ZKN_FONTOAM_SYS_PTR p_fontoam_sys;	// FONTOAM�V�X�e��

	ZKN_POKELIST_DATA_OAM_DATA poketbl;	// �|�P�����f�[�^�e�[�u���f�[�^
	ZKN_FIGHT_FOOT pokefoot;	// �|�P��������
	ZKN_FIGHT_POKETYPE_NAME poketype_name;	// �`�|�P����
	ZKN_FIGHT_TYPE poke_type;	// �|�P�������߃��[�N

	u32 oam_mapping_mode_tmp;	// �I�u�W�F�}�b�v���[�h�ۑ�

	u32 seq;

	u32 monsno;

	TCB_PTR tcb;

	ZKN_PALANM_WORK palanm;	// �p���b�g�A�j��
	BOOL palanm_flag;

} ;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
// �^�X�N
static void ZknFight_TCB( TCB_PTR tcb, void* p_work );


// �p���b�g�t�F�[�h����
static void ZknFight_PalFadeWorkSet( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp );
static void ZknFight_PalFadeReq( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp, int ssp_s_evy, int s_evy, int e_evy, int wait, int rgb );
static BOOL ZknFight_PalFadeEndCheck( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp );


//�`��֌W�ł�
static void ZknFight_InitDraw( ZKN_FIGHT_TEXT_DRAW* p_zftd, const ZKN_FIGHT_TEXT_PARAM* cp_param );
static void ZknFight_DeleteDraw( ZKN_FIGHT_TEXT_DRAW* p_zftd );

static void ZknFight_InitBgSystem( GF_BGL_INI* p_bg, int heap );
static void ZknFitht_ReleaseBgSystem( GF_BGL_INI* p_bg );
static GF_BGL_BMPWIN* ZknFight_InitTextBmp( GF_BGL_INI* p_bgl, int heap );
static void ZknFight_DeleteTextBmp( GF_BGL_BMPWIN* p_bmp );
static void ZknFight_InitResManager( CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap );
static void ZknFight_DeleteResManager( CLACT_U_RES_MANAGER_PTR* pp_res_manager );
static void ZknFight_InitPokeNameTblFontOamData( ZKN_POKELIST_DATA_OAM_DATA* p_poketbl, ZKN_FONTOAM_SYS_PTR p_fontoam_sys, int heap, int monsno, int pokenum_mode );
static void ZknFight_DeletePokeNameTblFontOamData( ZKN_POKELIST_DATA_OAM_DATA* p_poketbl );
static SOFT_SPRITE* ZknFight_InitSoftSprite( SOFT_SPRITE_MANAGER* p_ssp, POKEMON_PARAM* p_pp, int x, int y, int heap );

static void ZknFight_DefaultClactResLoad( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int arc_idx, int charidx, int plttidx, int cellidx, int cellanmidx, int plttload_num, int common_res_id );
static void ZknFight_DefaultClactResDelete( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager );
static void ZknFight_DefaultClactHeaderMake( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, CLACT_HEADER* p_head, int bg_pri );

static void ZknFight_PokeFootResLoad( ZKN_FIGHT_FOOT* foot, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int monsno, int heap );
static void ZknFight_PokeFootResDelete( ZKN_FIGHT_FOOT* foot, CLACT_U_RES_MANAGER_PTR* pp_res_manager );
static void ZknFight_PokeFootClactAdd( ZKN_FIGHT_FOOT* foot, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap );
static void ZknFight_PokeFootClactDelete( ZKN_FIGHT_FOOT* foot );

static void ZknFight_PokeTypeNameClactAdd( ZKN_FIGHT_POKETYPE_NAME* typename, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, CLACT_U_RES_OBJ_PTR* pp_poketbl_res_obj );
static void ZknFight_PokeTypeNameClactDelete( ZKN_FIGHT_POKETYPE_NAME* typename );
static void ZknFight_PokeTypeNameFontAdd( ZKN_FIGHT_POKETYPE_NAME* typename, ZKN_FONTOAM_SYS_PTR p_fontoam_sys, int heap, int monsno, CLACT_U_RES_OBJ_PTR pltt_res );
static void ZknFight_PokeTypeNameFontDelete( ZKN_FIGHT_POKETYPE_NAME* typename );

static void ZknFight_PokeTypeResLoad( ZKN_FIGHT_TYPE* type, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int monsno, int heap );
static void ZknFight_PokeTypeResDelete( ZKN_FIGHT_TYPE* type, CLACT_U_RES_MANAGER_PTR* pp_res_manager );
static void ZknFight_PokeTypeClactAdd( ZKN_FIGHT_TYPE* type, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int monsno );
static void ZknFight_PokeTypeClactDelete( ZKN_FIGHT_TYPE* type );

static void ZknFight_BackGroundSetUp( GF_BGL_INI* p_bg, int heap );
static void ZknFight_BackUtilSetUp( GF_BGL_INI* p_bg, int heap );
static void ZknFight_TextSetUp( GF_BGL_BMPWIN* p_bmp, int heap, int monsno );
static void ZknFight_FontSetPokeTitle( GF_BGL_BMPWIN* p_bmp, int heap );

static int ZknFight_GetPokemonNumber( u32 mode, POKEMON_PARAM* p_pp );

static void ZknFight_InitCharManager( int heap );
static void ZknFight_DeleteCharManager( void );


// �p���b�g�A�j��
static void ZknFight_InitPalAnm( ZKN_PALANM_WORK* p_data, int heap, int poke_num_mode );
static void ZknFight_MainPalAnm( ZKN_PALANM_WORK* p_data );
static void ZknFight_DeletePalAnm( ZKN_PALANM_WORK* p_data );
static void ZknFight_TransPalAnm( ZKN_PALANM_WORK* p_data, int frm );
static void ZknFight_TransPalAnmVblank( ZKN_PALANM_WORK* p_data, int frm );


//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄe�L�X�g�`�惊�N�G�X�g
 *
 *	@param	cp_param	�f�[�^�p�����[�^
 *
 *	@return	�`�惏�[�N
 */
//-----------------------------------------------------------------------------
ZKN_FIGHT_TEXT_DRAW* ZKN_FIGHT_TextDrawReq( const ZKN_FIGHT_TEXT_PARAM* cp_param )
{
	ZKN_FIGHT_TEXT_DRAW* p_zftd = sys_AllocMemory( cp_param->heap, sizeof( ZKN_FIGHT_TEXT_DRAW ) );
	memset( p_zftd, 0, sizeof( ZKN_FIGHT_TEXT_DRAW ) );

	// �`��ʐݒ�
	ZknFight_InitDraw( p_zftd, cp_param );

	// �p���b�g�t�F�[�h������
	ZknFight_PalFadeWorkSet( p_zftd->p_pfd, p_zftd->p_ssp );
	ZknFight_PalFadeReq( p_zftd->p_pfd, p_zftd->p_ssp, 10, 15, 0, 0, 0x0 );
		
	// �^�X�N�o�^
	p_zftd->tcb = TCB_Add( ZknFight_TCB, p_zftd, ZKN_FIGHT_TCB_PRI );

	return p_zftd;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄe�L�X�g�`��@�j��
 *
 *	@param	p_data	�`�惏�[�N
 *
 *	@return	none
 *
 *	�t�F�[�h�A�E�g��ɔj������K�v������܂�.
 */
//-----------------------------------------------------------------------------
void ZKN_FIGHT_TextDrawDelete( ZKN_FIGHT_TEXT_DRAW* p_data )
{
	// ���[�N���f�[�^�j��
	ZknFight_DeleteDraw( p_data );

	// TCB�j��
	TCB_Delete( p_data->tcb );

	// ���[�N�j��
	sys_FreeMemoryEz( p_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄe�L�X�g�`��@�I���`�F�b�N
 *
 *	@param	cp_data		�}�Ӄ��[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
BOOL ZKN_FIGHT_TexDrawEndCheck( const ZKN_FIGHT_TEXT_DRAW* cp_data )
{
	if( cp_data->seq == ZKN_FIGHT_END ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�\�t�g�E�F�A�X�v���C�g���[�N��Ԃ�
 *
 *	@param	p_data	���[�N
 *
 *	@return	�\�t�g�E�F�A�X�v���C�g���[�N
 */
//-----------------------------------------------------------------------------
SOFT_SPRITE* ZKN_FIGHT_TexDrawGetSsp( ZKN_FIGHT_TEXT_DRAW* p_data )
{
	return p_data->p_ssp;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�A�j��ONOFF�t���O�ݒ�
 *
 *	@param	p_data	���[�N
 *	@param	flag	�p���b�g�A�j���t���O
 *
 *	@return	none
 *
 *	flag
 *		TRUE	�A�j��ON
 *		FALSE	�A�j��OFF
 */
//-----------------------------------------------------------------------------
void ZKN_FIGHT_PalAnmFlagSet( ZKN_FIGHT_TEXT_DRAW* p_data, BOOL flag )
{
	p_data->palanm_flag = flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�A�j��ONOFF�t���O�擾
 *
 *	@param	cp_data		���[�N
 *
 *	@retval	TRUE	�A�j����
 *	@retval	FALSE	�A�j��OFF��
 */
//-----------------------------------------------------------------------------
BOOL ZKN_FIGHT_PalAnmFlagGet( const ZKN_FIGHT_TEXT_DRAW* cp_data )
{
	return cp_data->palanm_flag;
}



//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�`��֌W�̑S������
 *
 *	@param	p_zftd		���[�N
 *	@param	cp_param	�V�X�e������
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitDraw( ZKN_FIGHT_TEXT_DRAW* p_zftd, const ZKN_FIGHT_TEXT_PARAM* cp_param )
{
	ZKN_FONTOAM_SYS_INIT fontoam_init;

	// �S���}�Ӄi���o�[
	p_zftd->monsno = PokeParaGet( cp_param->p_pp, ID_PARA_monsno, NULL );

	// BG�V�X�e��
	p_zftd->p_bgl = cp_param->p_bgl;

	// �Z���A�N�^�[�Z�b�g
	p_zftd->clact_set = CLACT_U_SetEasyInit( ZKN_FIGHT_CLACT_WORKNUM, &p_zftd->render_data, cp_param->heap );

	// �ꉞOAM�ʂ̃N���A
	CLACT_UtilOamRamClear_Main( cp_param->heap );

	//�@�L�����N�^�}�l�[�W��������
	ZknFight_InitCharManager( cp_param->heap );

	// ssp
	p_zftd->p_ssp	= ZknFight_InitSoftSprite( 
			cp_param->p_ssm, cp_param->p_pp,
			ZKN_FIGHT_POKEGRA_MAT_X, ZKN_FIGHT_POKEGRA_MAT_Y,
			cp_param->heap );
	
	// �p���b�g�t�F�[�h
	p_zftd->p_pfd	= cp_param->p_pfd;

	// FONTOAM�쐬
	fontoam_init.clact_set	= p_zftd->clact_set;
	fontoam_init.p_bg		= p_zftd->p_bgl;
	fontoam_init.work_num	= ZKN_FIGHT_FONTOAM_WORKNUM;
	fontoam_init.heap		= cp_param->heap;
	p_zftd->p_fontoam_sys	= ZKN_FONTOAM_InitSys( &fontoam_init );
	
	// BGSystem������
	ZknFight_InitBgSystem( p_zftd->p_bgl, cp_param->heap );

	// �S�Ă̖ʂ��\���ɂ���
	G2_SetBlendBrightness( PLANEMASK_ALL, -16 );
/*	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_OFF );
//*/
	// BMP�̎擾
	p_zftd->p_bmp = ZknFight_InitTextBmp( p_zftd->p_bgl, cp_param->heap );

	// ���\�[�X�}�l�[�W���쐬
	ZknFight_InitResManager( p_zftd->res_manager, cp_param->heap );
	
	// �|�P�������e�[�u���쐬
	ZKN_GlbPokeNameTblResLoad_Minute( &p_zftd->poketbl, p_zftd->res_manager, cp_param->heap );

	// �|�P�������e�[�u���A�N�^�[�o�^
	ZKN_GlbPokeNameTblActAdd_Minute( &p_zftd->poketbl, p_zftd->clact_set, p_zftd->res_manager, cp_param->heap, ZKN_FIGHT_OAM_BG_PRI );

	// �|�P�������ݒ�
	ZknFight_InitPokeNameTblFontOamData( &p_zftd->poketbl, p_zftd->p_fontoam_sys, cp_param->heap, p_zftd->monsno, cp_param->pokenum_mode );
	
	// �|�P���������W�ݒ�
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet_Minute( &p_zftd->poketbl, ZKN_FIGHT_POKELIST_MAT_X, ZKN_FIGHT_POKELIST_MAT_Y );

	// �|�P�������\��
	ZKN_GlbPokeNameTblDrawFlagSet_Minute( &p_zftd->poketbl, TRUE );

	// �|�P�t�b�g������
	ZknFight_PokeFootResLoad( &p_zftd->pokefoot, p_zftd->res_manager, p_zftd->monsno, cp_param->heap );
	ZknFight_PokeFootClactAdd( &p_zftd->pokefoot, p_zftd->clact_set, p_zftd->res_manager, cp_param->heap );

	// �|�P�������߃A�N�^�[������
	ZknFight_PokeTypeResLoad( &p_zftd->poke_type, p_zftd->res_manager, p_zftd->monsno, cp_param->heap );
	ZknFight_PokeTypeClactAdd( &p_zftd->poke_type, p_zftd->clact_set, p_zftd->res_manager, cp_param->heap, p_zftd->monsno );


	// �`�|�P����������
	ZknFight_PokeTypeNameClactAdd( &p_zftd->poketype_name, p_zftd->clact_set, p_zftd->res_manager, cp_param->heap, p_zftd->poke_type.res_obj );
	ZknFight_PokeTypeNameFontAdd( &p_zftd->poketype_name, p_zftd->p_fontoam_sys, cp_param->heap, p_zftd->monsno, p_zftd->poketbl.pokelist_res_obj[ CLACT_U_PLTT_RES ] );

	// �w�i�ݒ�
	ZknFight_BackGroundSetUp( p_zftd->p_bgl, cp_param->heap );
	ZknFight_BackUtilSetUp( p_zftd->p_bgl, cp_param->heap );

	// ������ʐݒ�
	ZknFight_TextSetUp( p_zftd->p_bmp, cp_param->heap, p_zftd->monsno );

	// �p���b�g�A�j��������
	ZknFight_InitPalAnm( &p_zftd->palanm, cp_param->heap, cp_param->pokenum_mode );
	p_zftd->palanm_flag = TRUE;		// �p���b�g�A�j���t���OON
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��֌W�̑S�j��
 *
 *	@param	p_zftd		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeleteDraw( ZKN_FIGHT_TEXT_DRAW* p_zftd )
{
	// �p���b�g�A�j���j��
	ZknFight_DeletePalAnm( &p_zftd->palanm );
	
	// �|�P�������߃A�N�^�[
	ZknFight_PokeTypeClactDelete( &p_zftd->poke_type );
	ZknFight_PokeTypeResDelete( &p_zftd->poke_type, p_zftd->res_manager );
	
	// �`�|�P�����̔j��
	ZknFight_PokeTypeNameFontDelete( &p_zftd->poketype_name );
	ZknFight_PokeTypeNameClactDelete( &p_zftd->poketype_name );
	
	// �|�P�t�b�g�j��
	ZknFight_PokeFootClactDelete( &p_zftd->pokefoot );
	ZknFight_PokeFootResDelete( &p_zftd->pokefoot, p_zftd->res_manager );
	
	// �|�P���������X�g�j��
	ZknFight_DeletePokeNameTblFontOamData( &p_zftd->poketbl );	// FONTOAM
	ZKN_GlbPokeNameTblActDelete_Minute( &p_zftd->poketbl );		// �A�N�^�[�j��
	ZKN_GlbPokeNameTblResRelease_Minute( &p_zftd->poketbl, p_zftd->res_manager );	// ���\�[�X�j��	

	// ���\�[�X�}�l�[�W���j��
	ZknFight_DeleteResManager( p_zftd->res_manager );

	// �Z���A�N�^�[�j��
	CLACT_DestSet( p_zftd->clact_set );

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZknFight_DeleteTextBmp( p_zftd->p_bmp );

	// BG�V�X�e���j��
	ZknFitht_ReleaseBgSystem( p_zftd->p_bgl );

	// FONTOAM�V�X�e���j��
	ZKN_FONTOAM_DeleteSys( p_zftd->p_fontoam_sys );

	// �L�����N�^�}�l�[�W���j��
	ZknFight_DeleteCharManager();
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�V�X�e���f�[�^��������
 *
 *	@param	p_bgl	BG�V�X�e��
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitBgSystem( GF_BGL_INI* p_bg, int heap )
{
	// ���C����� BG1��		�����񏑂����ݖ�
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_FONT_M );
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_FONT_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_FONT_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_FONT_M );
	}

	// ���C����� BG2��		���[�e�B���e�B��
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x0c000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_UTIL_M );
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_UTIL_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_UTIL_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_UTIL_M );
	}

	// 3D��
	GF_BGL_PrioritySet( GF_BGL_FRAME0_M, 0 );
	// BG0ON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_BGL_BGControlExit( p_bg, 0 );

	// ���C����� BG3��		�w�i��
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000,
			GX_BG_EXTPLTT_01, 3, 0, 0, FALSE
		};
		GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_BACK_M );
		GF_BGL_BGControlSet( p_bg, ZKN_BG_FRM_BACK_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( ZKN_BG_FRM_BACK_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_BACK_M );
	}

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�R���g���[���f�[�^�j��
 *
 *	@param	p_bg	BG�R���g���[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknFitht_ReleaseBgSystem( GF_BGL_INI* p_bg )
{
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_FONT_M );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_UTIL_M );
	GF_BGL_BGControlExit( p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�퓬�ߊl��@�}�Ӊ�ʁ@�r�b�g�}�b�v�E�B���h�E�쐬
 *
 *	@param	p_bgl	BG�V�X�e��
 *	@param	heap	�q�[�v
 *
 *	@return	�r�b�g�}�b�v�E�B���h�E	
 */
//-----------------------------------------------------------------------------
static GF_BGL_BMPWIN* ZknFight_InitTextBmp( GF_BGL_INI* p_bgl, int heap )
{
	GF_BGL_BMPWIN* p_bmp;

	// �������m��
	p_bmp = GF_BGL_BmpWinAllocGet( heap, 1 );	
	
	// ���W�����̃r�b�g�}�b�v�E�B���h�E�쐬
	// �r�b�g�}�b�v�E�B���h�E�o�^
	GF_BGL_BmpWinAdd( p_bgl, p_bmp, ZKN_BG_FRM_FONT_M, 0, 0, ZKN_BG_FONTBMP_CX, ZKN_BG_FONTBMP_CY, ZKN_BG_FIGHT_FONT_COLOR, 0 );

	// �N���[��
	GF_BGL_BmpWinDataFill( p_bmp, 0 );

	// �\��
	GF_BGL_BmpWinOn( p_bmp );

	return p_bmp;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�퓬�ߊl��@�}�Ӊ�ʁ@�r�b�g�}�b�v�E�B���h�E�j��
 *
 *	@param	p_bmp		�r�b�g�}�b�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeleteTextBmp( GF_BGL_BMPWIN* p_bmp )
{
	GF_BGL_BmpWinOff( p_bmp );
	GF_BGL_BmpWinDel( p_bmp );
	GF_BGL_BmpWinFree( p_bmp, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�}�l�[�W���̍쐬
 *
 *	@param	pp_res_manager	���\�[�X�}�l�[�W���o�b�t�@
 *	@param	heap			�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitResManager( CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap )
{
	int i;

	for( i=0; i<ZKN_CLACT_RES_MANAGER_NUM; i++ ){
		pp_res_manager[i] = CLACT_U_ResManagerInit( ZKN_FIGHT_MANAG_RES_NUM, i, heap );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�}�l�[�W���̂͂�
 *
 *	@param	pp_res_manager	���\�[�X�}�l�[�W��
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeleteResManager( CLACT_U_RES_MANAGER_PTR* pp_res_manager )
{
	int i;

	for( i=0; i<ZKN_CLACT_RES_MANAGER_NUM; i++ ){
		CLACT_U_ResManagerDelete( pp_res_manager[i] );
		pp_res_manager[i] = NULL;
	}	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������e�[�u�������쐬
 *
 *	@param	p_poketbl			�|�P�����e�[�u�����[�N
 *	@param	p_fontoam_sys		�t�H���gOAM�V�X�e��
 *	@param	heap				�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitPokeNameTblFontOamData( ZKN_POKELIST_DATA_OAM_DATA* p_poketbl, ZKN_FONTOAM_SYS_PTR p_fontoam_sys, int heap, int monsno, int pokenum_mode )
{
	ZKN_FONTOAM_INIT fontoam_init;
	GF_BGL_BMPWIN* p_bmp;	// �������ݗ̈�
	CLACT_U_RES_OBJ_PTR pltt_obj;	// �p���b�g�v���N�V�擾�p

	// �|�P�������A�N�^�[�Ɏg�p����p���b�g�v���N�V�擾
	pltt_obj = p_poketbl->pokelist_res_obj[ CLACT_U_PLTT_RES ];
		
	// �|�P�������A�N�^�[�쐬
	fontoam_init.zkn_fontoam = p_fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( pltt_obj, NULL );
	fontoam_init.parent		 = p_poketbl->pokelist_tbl;
	fontoam_init.x			 = -(ZKN_POKELIST_POKENAME_BMP_SIZE_X / 2);
	fontoam_init.y			 = -(ZKN_POKELIST_POKENAME_BMP_SIZE_Y / 2);
	fontoam_init.bg_pri		 = ZKN_FIGHT_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;


	// �����񏑂����ݗ̈�쐬
	if( pokenum_mode == PM_NUMBER_SHINOU ){
		p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake_Shinou( p_fontoam_sys, heap, monsno );
	}else{
		p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake_Zenkoku( p_fontoam_sys, heap, monsno );
	}

	// FONTOAM�o�^
	fontoam_init.p_bmp = p_bmp;
	ZKN_GlbPokeNameTblSet_Minute( p_poketbl, &fontoam_init, 0, monsno, pokenum_mode );
	// BMP�̈�j��
	ZKN_FONTOAM_DeleteBmp( p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����e�[�u���t�H���g�f�[�^�j��
 *
 *	@param	p_poketbl	�|�P�����e�[�u���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeletePokeNameTblFontOamData( ZKN_POKELIST_DATA_OAM_DATA* p_poketbl )
{
	if( p_poketbl->p_pokename ){
		ZKN_FONTOAM_Delete( p_poketbl->p_pokename );
		p_poketbl->p_pokename = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	��{�I�ȃA�N�^�[���\�[�X�ǂݍ��݊֐�
 *
 *	@param	p_res_obj		���\�[�X�I�u�W�F
 *	@param	pp_res_manager	���\�[�X�}�l�[�W��
 *	@param	heap			�q�[�v
 *	@param	charidx			�L�����N�^�f�[�^�C���f�b�N�X
 *	@param	plttidx			�p���b�g�f�[�^�C���f�b�N�X
 *	@param	cellidx			�Z���f�[�^�C���f�b�N�X
 *	@param	cellanmidx		�Z���A�j���C���f�b�N�X
 *	@param	plttload_num	�p���b�g�ǂݍ��ݖ{��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DefaultClactResLoad( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int arc_idx, int charidx, int plttidx, int cellidx, int cellanmidx, int plttload_num, int common_res_id )
{
	// �L�����N�^�f�[�^�ǂݍ���
	p_res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( 
			pp_res_manager[ CLACT_U_CHAR_RES ], arc_idx,
			charidx, TRUE,
			common_res_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( 
			pp_res_manager[ CLACT_U_PLTT_RES ], arc_idx,
			plttidx, FALSE, 
			common_res_id,
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			plttload_num, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			pp_res_manager[ CLACT_U_CELL_RES ], arc_idx,
			cellidx, TRUE,
			common_res_id,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			pp_res_manager[ CLACT_U_CELLANM_RES ], arc_idx, 
			cellanmidx, TRUE,
			common_res_id,
			CLACT_U_CELLANM_RES, heap );
}


//----------------------------------------------------------------------------
/**
 *	@brief	��{�I�ȃ��\�[�X�j��
 *
 *	@param	p_res_obj		���\�[�X�I�u�W�F	
 *	@param	pp_res_manager	���\�[�X�}�l�[�W��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DefaultClactResDelete( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager )
{
	CLACT_U_CharManagerDelete( p_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_res_obj[ CLACT_U_PLTT_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CHAR_RES ],
			p_res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_PLTT_RES ],
			p_res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CELL_RES ],
			p_res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			p_res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�w�b�_�[�f�[�^�쐬
 *
 *	@param	p_res_obj			���\�[�X�I�u�W�F
 *	@param	pp_res_manager		���\�[�X�}�l�[�W��
 *	@param	p_head				�w�b�_�[���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DefaultClactHeaderMake( CLACT_U_RES_OBJ_PTR* p_res_obj, CLACT_U_RES_MANAGER_PTR* pp_res_manager, CLACT_HEADER* p_head, int bg_pri )
{
	
	// �e�{�^����o�^
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( p_head,
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_CHAR_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_PLTT_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_CELL_RES ] ),
			CLACT_U_ResManagerGetResObjID( p_res_obj[ CLACT_U_CELLANM_RES ] ),
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, bg_pri,
			pp_res_manager[ CLACT_U_CHAR_RES ],
			pp_res_manager[ CLACT_U_PLTT_RES ],
			pp_res_manager[ CLACT_U_CELL_RES ],
			pp_res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������Ճ��\�[�X�ǂݍ���
 *
 *	@param	foot			���Ճ��[�N
 *	@param	pp_res_manager	���\�[�X�}�l�[�W��
 *	@param	monsno			�����X�^�[�i���o�[
 *	@param	heap			�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeFootResLoad( ZKN_FIGHT_FOOT* foot, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int monsno, int heap )
{
	int arc_file = PokeFootArcFileGet();
	int char_idx = PokeFootCharDataIdxGet( monsno );
	int pltt_idx = PokeFootPlttDataIdxGet();
	int cell_idx = PokeFootCellDataIdxGet();
	int cellanm_idx = PokeFootCellAnmDataIdxGet();

	// ���\�[�X�ǂݍ���
	ZknFight_DefaultClactResLoad( foot->res_obj, pp_res_manager, heap, arc_file, char_idx, pltt_idx, cell_idx, cellanm_idx, ZKN_ZUKAN_FOOT_PLTT_LOAD, ZKN_ZUKAN_FOOT_RES_ID );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������Ճ��\�[�X�j��
 *
 *	@param	foot
 *	@param	pp_res_manager 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeFootResDelete( ZKN_FIGHT_FOOT* foot, CLACT_U_RES_MANAGER_PTR* pp_res_manager )
{
	ZknFight_DefaultClactResDelete( foot->res_obj, pp_res_manager );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������ՃA�N�^�[�o�^
 *
 *	@param	foot			���Ճ��[�N
 *	@param	clact_set		�Z���A�N�^�[�Z�b�g
 *	@param	pp_res_manager	���\�[�X�}�l�[�W��
 *	@param	heap			�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeFootClactAdd( ZKN_FIGHT_FOOT* foot, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap )
{
	CLACT_ADD_SIMPLE add;
	CLACT_HEADER head;

	// �w�b�_�[�쐬
	ZknFight_DefaultClactHeaderMake( foot->res_obj, pp_res_manager, &head, ZKN_FIGHT_OAM_BG_PRI );

	// �ݒ�
	add.ClActSet	= clact_set;
	add.ClActHeader	= &head;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.pri			= ZKN_FIGHT_OAM_SOFT_PRI;
	add.heap		= heap;
	add.mat.x		= ZKN_FIGHT_FOOT_MAT_X;
	add.mat.y		= ZKN_FIGHT_FOOT_MAT_Y;
	foot->foot	= CLACT_AddSimple( &add );
	GF_ASSERT( foot->foot );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ՃA�N�^�[�j��
 *
 *	@param	foot	���Ճ��[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeFootClactDelete( ZKN_FIGHT_FOOT* foot )
{
	CLACT_Delete( foot->foot );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������ߖ��e�[�u���̃A�N�^�[�o�^
 *
 *	@param	typename			���[�N
 *	@param	clact_set			�A�N�^�[�Z�b�g
 *	@param	pp_res_manager		���\�[�X�}�l�[�W��
 *	@param	heap				�q�[�v
 *	@param	pp_poketbl_res_obj	�|�P���X�g�̃��\�[�X�I�u�W�F
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeNameClactAdd( ZKN_FIGHT_POKETYPE_NAME* typename, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, CLACT_U_RES_OBJ_PTR* pp_poketbl_res_obj )
{
	CLACT_ADD_SIMPLE add;
	CLACT_HEADER head;

	// �w�b�_�[�쐬
	ZknFight_DefaultClactHeaderMake( pp_poketbl_res_obj, pp_res_manager, &head, ZKN_FIGHT_OAM_BG_PRI );

	// �ݒ�
	add.ClActSet	= clact_set;
	add.ClActHeader	= &head;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.pri			= ZKN_FIGHT_OAM_SOFT_PRI;
	add.heap		= heap;
	add.mat.x		= ZKN_FIGHT_POKETYPE_TEXT_MAT_X;
	add.mat.y		= ZKN_FIGHT_POKETYPE_TEXT_MAT_Y;
	typename->poketype_text_tbl	= CLACT_AddSimple( &add );
	GF_ASSERT( typename->poketype_text_tbl );
	CLACT_AnmChg( typename->poketype_text_tbl, ZKN_ZUKAN_POKETYPE_TEXT_TBL_SEQ );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�|�P�����@�̃A�N�^�[�j��
 *
 *	@param	typename	�|�P�������ߖ����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeNameClactDelete( ZKN_FIGHT_POKETYPE_NAME* typename )
{
	CLACT_Delete( typename->poketype_text_tbl );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�|�P�����t�H���gOAM�A�b�h
 *
 *	@param	typename			�`�|�P�������[�N
 *	@param	p_fontoam_sys		�t�H���gOAM�V�X�e��
 *	@param	heap				�q�[�v
 *	@param	monsno				�����X�^�[�i���o�[
 *	@param	pltt_res			�g�p�p���b�g���\�[�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeNameFontAdd( ZKN_FIGHT_POKETYPE_NAME* typename, ZKN_FONTOAM_SYS_PTR p_fontoam_sys, int heap, int monsno, CLACT_U_RES_OBJ_PTR pltt_res )
{
	GF_BGL_BMPWIN* p_bmp;
	ZKN_FONTOAM_INIT fontoam_init;

	// �����f�[�^�쐬
	p_bmp = ZknZukanPokeTypeTextBmpMake( p_fontoam_sys, monsno, heap );

	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( pltt_res, NULL );
	fontoam_init.parent		 = typename->poketype_text_tbl;
	fontoam_init.x			 = ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_X;
	fontoam_init.y			 = ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_FIGHT_OAM_BG_PRI;
	fontoam_init.soft_pri	 = ZKN_FIGHT_OAM_SOFT_PRI - 1;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;
	fontoam_init.p_bmp		 = p_bmp;
	typename->p_poketype_text = ZKN_FONTOAM_Make( &fontoam_init );
	
	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�|�P�����@�t�H���gOAM�j��
 *
 *	@param	typename	�`�|�P�������[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeNameFontDelete( ZKN_FIGHT_POKETYPE_NAME* typename )
{
	ZKN_FONTOAM_Delete( typename->p_poketype_text );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������߁@�A�N�^�[�@���\�[�X�ǂݍ���
 *
 *	@param	type				���߃��[�N
 *	@param	pp_res_manager		���\�[�X�}�l�[�W��
 *	@param	monsno				�����X�^�[�i���o�[
 *	@param	heap				�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeResLoad( ZKN_FIGHT_TYPE* type, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int monsno, int heap )
{
	// ���\�[�X�ǂݍ���
	ZknFight_DefaultClactResLoad( type->res_obj, 
			pp_res_manager, heap, ARC_ZUKAN_GRA, 
			NARC_zukan_zkn_data_oam_main2_lzh_NCGR,
			NARC_zukan_zkn_data_oam2_NCLR,
			NARC_zukan_zkn_data_oam_main2_lzh_NCER,
			NARC_zukan_zkn_data_oam_main2_lzh_NANR,
			ZKN_ZUKAN_PLTT_LOAD,
			ZKN_ZUKAN_POKETYPE_RES_ID );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������߃��\�[�X�j��
 *
 *	@param	type				����
 *	@param	pp_res_manager		���\�[�X�}�l�[�W��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeResDelete( ZKN_FIGHT_TYPE* type, CLACT_U_RES_MANAGER_PTR* pp_res_manager )
{
	ZknFight_DefaultClactResDelete( type->res_obj, pp_res_manager );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������߃A�N�^�[�o�^
 *
 *	@param	type			���߃��[�N
 *	@param	clact_set		�Z���A�N�^�[�Z�b�g
 *	@param	pp_res_manager	���\�[�X�}�l�[�W��
 *	@param	heap			�q�[�v
 *	@param	monsno			�����X�^�[�i���o�[
 *		
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeClactAdd( ZKN_FIGHT_TYPE* type, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int monsno )
{
	CLACT_ADD_SIMPLE add;
	CLACT_HEADER head;
	int type1, type2;

	type1 = PokePersonalParaGet( monsno, ID_PER_type1 );
	type2 = PokePersonalParaGet( monsno, ID_PER_type2 );
	// type���j�g���L�����N�^�̃A�j���V�[�P���X�i���o�[�ɕύX
	type1 =	ZknZukanClactTypeNoChg( type1 );
	type2 =	ZknZukanClactTypeNoChg( type2 );


	// �w�b�_�[�쐬
	ZknFight_DefaultClactHeaderMake(type->res_obj, pp_res_manager, &head, ZKN_FIGHT_OAM_BG_PRI );
	
	// �ݒ�
	add.ClActSet	= clact_set;
	add.ClActHeader	= &head;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.pri			= ZKN_FIGHT_OAM_SOFT_PRI;
	add.heap		= heap;

	// ����1
	add.mat.x		= ZKN_FIGHT_POKETYPE1_MAT_X;
	add.mat.y		= ZKN_FIGHT_POKETYPE_MAT_Y;
	type->type[ ZKN_FIGHT_TYPE_1 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( type->type[ ZKN_FIGHT_TYPE_1 ], ZKN_ZUKAN_POKETYPE_NORMAL + type1 );

	// �^�C�v2
	if( type1 != type2 ){
		add.mat.x = ZKN_FIGHT_POKETYPE2_MAT_X;
		add.mat.y = ZKN_FIGHT_POKETYPE_MAT_Y;
		type->type[ ZKN_FIGHT_TYPE_2 ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( type->type[ ZKN_FIGHT_TYPE_2 ], ZKN_ZUKAN_POKETYPE_NORMAL + type2 );
	}else{
		type->type[ ZKN_FIGHT_TYPE_2 ] = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[���[�N�@�A�N�^�[�j��
 *
 *	@param	type ����
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PokeTypeClactDelete( ZKN_FIGHT_TYPE* type )
{
	if( type->type[ ZKN_FIGHT_TYPE_1 ] ){
		CLACT_Delete( type->type[ ZKN_FIGHT_TYPE_1 ] );
	}
	if(type->type[ ZKN_FIGHT_TYPE_2 ]){
		CLACT_Delete( type->type[ ZKN_FIGHT_TYPE_2 ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�w�i�ݒ�
 *
 *	@param	p_bg	BG�V�X�e��
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_BackGroundSetUp( GF_BGL_INI* p_bg, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �p���b�g�]��
	ArcUtil_PalSet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_NCLR, PALTYPE_MAIN_BG, 0, 0, heap );
	// �L�����N�^�f�[�^�]��
	ArcUtil_BgCharSet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_main_lzh_NCGR, p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ArcUtil_ScrnDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �|�P�����̕\���g��w�i�ɓ\��t��	
	buff = ArcUtil_ScrnDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_bg_main1_a_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_FIGHT_POKE_DRAW_FRAME_CX, ZKN_FIGHT_POKE_DRAW_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �|�P�������Ղ̕\���g��w�i�ɓ\��t��	
	buff = ArcUtil_ScrnDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_bg_main1_b_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_FIGHT_FOOT_FRAME_CX, ZKN_FIGHT_FOOT_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �|�P��������text�g��\��t��	
	buff = ArcUtil_ScrnDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_bg_main1_d_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_FIGHT_TEXT_FRAME_CX, ZKN_FIGHT_TEXT_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );
	
	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄ��[�e�B���e�B�ʐݒ�
 *
 *	@param	p_bg
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknFight_BackUtilSetUp( GF_BGL_INI* p_bg, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �L�����N�^�f�[�^�]��
	ArcUtil_BgCharSet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_main_lzh_NCGR, p_bg, ZKN_BG_FRM_UTIL_M, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ArcUtil_ScrnDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_bg_main2_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_UTIL_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_bg, ZKN_BG_FRM_UTIL_M );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�ߊl���ʃ^�X�N
 *
 *	@param	tcb			�^�X�N���[�N
 *	@param	p_work		�f�[�^���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_TCB( TCB_PTR tcb, void* p_work )
{
	ZKN_FIGHT_TEXT_DRAW* p_zftd = p_work;
	BOOL check;
	
	switch( p_zftd->seq ){
	case ZKN_FIGHT_FADE_IN:
		// �\��ON
		G2_BlendNone();
/*		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );//*/
		p_zftd->seq++;
		break;

	case ZKN_FIGHT_FADE_IN_WAIT:
		if( ZknFight_PalFadeEndCheck( p_zftd->p_pfd, p_zftd->p_ssp ) ){
			p_zftd->seq++;
		}
		break;

	case ZKN_FIGHT_SND_PLY:
		check = Snd_PMVoicePlayEx( PV_ZUKAN_NORMAL, p_zftd->monsno, PV_PTN_PARAM_NONE, 
								   PV_PTN_PARAM_NONE, PV_PTN_PARAM_NONE );	//�؃��b�v(default)
		GF_ASSERT( check );
		p_zftd->seq++;
		break;
		
	case ZKN_FIGHT_SND_WAIT:
		if( Snd_PMVoicePlayCheck() == 0 ){
			p_zftd->seq++;
		}
		break;

	case ZKN_FIGHT_END:
		break;

	default:
		break;
	}

	// �p���b�g�A�j���t���O
	if( p_zftd->palanm_flag ){
		// �p���b�g�A�j��
		ZknFight_MainPalAnm( &p_zftd->palanm );
	}

	// �Z���A�N�^�[�`��
	CLACT_Draw( p_zftd->clact_set );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�t�F�[�h�p���[�N�쐬
 *
 *	@param	pfd		�p���b�g�t�F�[�h���[�N
 *	@param	ssp		�\�t�g�E�F�A�X�v���C�g
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PalFadeWorkSet( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp )
{
	PaletteWorkSet_VramCopy( pfd, FADE_MAIN_BG, 0, 32 * 0x10 );
	PaletteWorkSet_VramCopy( pfd, FADE_MAIN_OBJ, 0, BATTLE_MAIN_OBJPAL_SIZE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�t�F�[�h�@�t�F�[�h�C�����N�G�X�g
 *
 *	@param	pfd		�p���b�g�t�F�[�h�V�X�e��
 *	@param	ssp		�\�t�g�E�F�A�X�v���C�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_PalFadeReq( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp, int ssp_s_evy, int s_evy, int e_evy, int wait, int rgb )
{
	SoftSpritePalFadeSet( ssp, ssp_s_evy, e_evy, wait, rgb );
	PaletteFadeReq( pfd, PF_BIT_MAIN_BG|PF_BIT_MAIN_OBJ, 0xffff, wait, s_evy, e_evy, rgb );

	// �S�]���͂��Ȃ�
	PaletteTrans_AutoSet( pfd, FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�t�F�[�h�I���`�F�b�N
 *
 *	@param	pfd		�p���b�g�t�F�[�h
 *	@param	ssp		�\�t�g�E�F�A�X�v���C�g
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknFight_PalFadeEndCheck( PALETTE_FADE_PTR pfd, SOFT_SPRITE* ssp )
{
	BOOL check[2];

	check[0] = PaletteFadeCheck( pfd );
	check[1] = SoftSpritePalFadeExist( ssp );

	if( (check[0] == FALSE) &&
		(check[1] == FALSE) ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	������`��
 *
 *	@param	p_bmp		�������ݐ�
 *	@param	heap		�q�[�v
 *	@param	monsno		�����X�^�[�i���o�[ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_TextSetUp( GF_BGL_BMPWIN* p_bmp, int heap, int monsno )
{
	ZknZukanSetUpFontBg_Minute( p_bmp, monsno, heap, 0, ZKN_BG_FIGHT_FONT_COLOR_MSK );

	// �|�P�����}�ӂ́@�o�^�@����
	ZknFight_FontSetPokeTitle( p_bmp, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����}�ӂ́@�o�^�@����
 *
 *	@param	p_bmp		�r�b�g�}�b�v	
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_FontSetPokeTitle( GF_BGL_BMPWIN* p_bmp, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_FIGHT_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	//	�|�P�����}�ӂ́@�o�^�@����
	MSGMAN_GetString( man, ZKN_POKEGET_00, str );
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_FIGHT_TITLE_TEXT_X, ZKN_FIGHT_TITLE_TEXT_Y, 0, ZKN_BG_FIGHT_FONT_COLOR2_MSK, NULL );

	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�\�t�g�E�F�A�X�v���C�g�@�̏�����
 *
 *	@param	p_ssp		�\�t�g�E�F�A�X�v���C�g
 *	@param	p_pp		�|�P�����p�����[�^
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	heap		�q�[�v
 *
 *	@return	SOFT_SPRITE
 */
//-----------------------------------------------------------------------------
static SOFT_SPRITE* ZknFight_InitSoftSprite( SOFT_SPRITE_MANAGER* p_ssp, POKEMON_PARAM* p_pp, int x, int y, int heap )
{
	SOFT_SPRITE_ARC arc;
	
	PokeGraArcDataGetPP( &arc, p_pp, PARA_FRONT );
		
	return SoftSpriteAdd( p_ssp,
					&arc,
					x, y, 0,
					0,
					NULL,
					NULL);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����i���o�[���擾����
 *
 *	@param	mode	���[�h
 *	@param	p_pp	�|�P�����p�����[�^
 *
 *	@return	�|�P�����i���o�[
 */
//-----------------------------------------------------------------------------
static int ZknFight_GetPokemonNumber( u32 mode, POKEMON_PARAM* p_pp )
{
	int monsno;
	
	monsno = PokeParaGet( p_pp, ID_PARA_monsno, NULL );
	return PMNumber_GetPokeNumber( mode, monsno );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�}�l�[�W��������
 *
 *	@param	heap	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitCharManager( int heap )
{
	CHAR_MANAGER_MAKE init = {
		ZKN_FIGHT_CHAR_WORKNUM,
		ZKN_FIGHT_CHAR_AREA_SIZE_MAIN,
		ZKN_FIGHT_CHAR_AREA_SIZE_SUB,
		0
	};
	init.heap = heap;
	InitCharManagerReg( &init, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L�����N�^�}�l�[�W���j��
 *
 *	@param	none 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeleteCharManager( void )
{
	DeleteCharManager();
}


//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�A�j��������
 *
 *	@param	p_data	���[�N
 *	@param	heap	�q�[�v
 *	@param	poke_num_mode �|�P�����i���o�[���[�h
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_InitPalAnm( ZKN_PALANM_WORK* p_data, int heap, int poke_num_mode )
{
	int i;
	
	// 1�t����
	if( poke_num_mode == PM_NUMBER_SHINOU ){
		p_data->p_pltt_buff[ZKN_FIGHT_PALANM_ONE] = ArcUtil_PalDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_sin_NCLR, &p_data->p_plt[ZKN_FIGHT_PALANM_ONE], heap );
	}else{
		p_data->p_pltt_buff[ZKN_FIGHT_PALANM_ONE] = ArcUtil_PalDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_zen_NCLR, &p_data->p_plt[ZKN_FIGHT_PALANM_ONE], heap );
	}
	
	// 2�t����
	p_data->p_pltt_buff[ZKN_FIGHT_PALANM_TWO] = ArcUtil_PalDataGet( ARC_ZUKAN_GRA, NARC_zukan_zkn_data_get_NCLR, &p_data->p_plt[ZKN_FIGHT_PALANM_TWO], heap );


	p_data->count = 0;
	p_data->now_set = 0;
	for( i=0; i<ZKN_FIGHT_PALANM_NUM; i++ ){
		p_data->anmtbl[ i ] = (i+1) * ZKN_FIGHT_PALANM_TIMING;
	}

	// �p���b�g�]��
	ZknFight_TransPalAnm( p_data, p_data->now_set );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�A�j�����C��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_MainPalAnm( ZKN_PALANM_WORK* p_data )
{
	// �A�j������
	if( p_data->anmtbl[ p_data->now_set ] <= p_data->count ){

		// �A�j���X�V
		p_data->now_set ++;

		if( p_data->now_set >= ZKN_FIGHT_PALANM_NUM ){
			p_data->now_set = 0;
			p_data->count = 0;
		}
		// �A�j���]��
		ZknFight_TransPalAnmVblank( p_data, p_data->now_set );
//		ZknFight_TransPalAnm( p_data, p_data->now_set );		
	}else{
		// �J�E���g�A�b�v
		p_data->count ++;	
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�A�j���j��
 *
 *	@param	p_data	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_DeletePalAnm( ZKN_PALANM_WORK* p_data )
{
	int i;
	
	for( i=0; i<ZKN_FIGHT_PALANM_NUM; i++ ){
		sys_FreeMemoryEz( p_data->p_pltt_buff[ZKN_FIGHT_PALANM_ONE] );
	}
	memset( p_data, 0, sizeof(ZKN_PALANM_WORK) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�]��
 *
 *	@param	p_data	���[�N
 *	@param	frm		�ݒ�t���[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_TransPalAnm( ZKN_PALANM_WORK* p_data, int frm )
{
	GX_LoadBGPltt(
			p_data->p_plt[ frm ]->pRawData,
			ZKN_FIGHT_PALANN_PAL * 32,
			ZKN_FIGHT_PALANN_PAL_NUM * 32 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p���b�g�]��
 *
 *	@param	p_data	���[�N
 *	@param	frm		�ݒ�t���[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFight_TransPalAnmVblank( ZKN_PALANM_WORK* p_data, int frm )
{
	AddVramTransferManager(
			NNS_GFD_DST_2D_BG_PLTT_MAIN,
			ZKN_FIGHT_PALANN_PAL * 32,
			p_data->p_plt[ frm ]->pRawData,
			ZKN_FIGHT_PALANN_PAL_NUM * 32 );
}
