//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_textver.c
 *	@brief		�}�ӌ���o�[�W����
 *	@author		tomoya takahashi
 *	@data		2006.02.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"
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

#include "include/battle/battle_common.h"

#include "include/application/zukanlist/zukan.naix"
#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"
#include "include/application/zukanlist/zkn_world_text_sys.h"

// �G�t�F�N�g�ō��W��Link�����邽�߁A�d���Ȃ��C���N���[�h
#include "include/application/zukanlist/zkn_pokelist.h"

#define	__ZKN_ZUKAN_TEXTVER_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan_textver.h"

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
#define ZKN_ZUKANTEXTVER_EVENT_NUM ( 0 )	// �C�x���g��
#define ZKN_ZUKANTEXTVER_OAM_BG_PRI	( 0 )
#define ZKN_ZUKANTEXTVER_OAM_SOFT_PRI	( 32 )

// BG�u���C�g�l�X�t�F�[�h��
#define ZKN_ZUKANTEXTVER_BRIGHTNESS_MSK	( GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )
#define ZKN_ZUKANTEXTVER_BRIGHTNESSCH_POKELIST_MSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

// �w�i���W
#define ZKN_ZUKANTEXTVER_POKE_DRAW_FRAME_CX	( 0 )
#define ZKN_ZUKANTEXTVER_POKE_DRAW_FRAME_CY	( 3 )
#define ZKN_ZUKANTEXTVER_TEXT_FRAME_CX			( 0 )
#define ZKN_ZUKANTEXTVER_TEXT_FRAME_CY			( 16 )
#define ZKN_ZUKANTEXTVER_TEXTEX_FRAME_CX		( 14 )
#define ZKN_ZUKANTEXTVER_TEXTEX_FRAME_CY		( 8 )


// �������
#define ZKN_ZUKANTEXTVER_NUM_STR		( 64 )	// �o�b�t�@�T�C�Y
#define ZKN_ZUKANTEXTVER_NUM_STRTEXT	( 256 )	// �o�b�t�@�T�C�Y

#define ZKN_ZUKANTEXTVER_FONT_COMMENT_X	( 8 )
#define ZKN_ZUKANTEXTVER_FONT_COMMENT_Y	( 136 )
#define ZKN_ZUKANTEXTVER_FONT_PAGE_NUM_X ( 16 )
#define ZKN_ZUKANTEXTVER_FONT_PAGE_OFS_X ( 8 )
#define ZKN_ZUKANTEXTVER_FONT_PAGE_Y ( 116 )
#define ZKN_ZUKANTEXTVER_FONT_PAGE_PLACE ( 1 )	// ��
#define ZKN_ZUKNATEXTVER_FONT_ZUKAN_NAME_C_X	( 184 )
#define ZKN_ZUKNATEXTVER_FONT_ZUKAN_NAME_Y	( 72 )
#define ZKN_ZUKNATEXTVER_FONT_MONSNO_X	( 128 )
#define ZKN_ZUKNATEXTVER_FONT_MONSNO_Y	( 96 )
#define ZKN_ZUKANTEXTVER_FONT_MONSNO_PLACE ( 3 )	// ��
#define ZKN_ZUKNATEXTVER_FONT_MONSNAME_X	( 160 )
#define ZKN_ZUKNATEXTVER_FONT_MONSNAME_Y	( 96 )
#define ZKN_ZUKNATEXTVER_FONT_MONSTYPE_X_OFS ( 8 )
#define ZKN_ZUKNATEXTVER_FONT_MONSTYPE_Y	( 112 )
#define ZKN_ZUKNATEXTVER_FONT_POKEMON_X	( 200 )
#define ZKN_ZUKNATEXTVER_FONT_POKEMON_Y	( 112 )

//-------------------------------------
//	�`�揉�����V�[�P���X
//=====================================
enum
{
	ZKN_ZUKANTEXTVER_SEQINIT_ALLOC,
	ZKN_ZUKANTEXTVER_SEQINIT_LOAD,
	ZKN_ZUKANTEXTVER_SEQINIT_FADEIN,
	ZKN_ZUKANTEXTVER_SEQINIT_END,
};

//-------------------------------------
//	�}�Ӕj���V�[�P���X
//=====================================
enum{
	ZKN_ZUKANTEXTVER_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKANTEXTVER_SEQDELETE_FADEOUT,
	ZKN_ZUKANTEXTVER_SEQDELETE_RELEASE,
	ZKN_ZUKANTEXTVER_SEQDELETE_FREE,
	ZKN_ZUKANTEXTVER_SEQDELETE_END,
};

// �|�P�������X�g���W
#define ZKN_ZUKANTEXTVER_POKELIST_MAT_X	( ZKN_ZUKANTEXTVER_POKELIST_MAT_IX*FX32_ONE )
#define ZKN_ZUKANTEXTVER_POKELIST_MAT_Y	( ZKN_ZUKANTEXTVER_POKELIST_MAT_IY*FX32_ONE )


// �^�C�v���W
#define ZKN_ZUKANTEXTVER_POKETYPE1_MAT_X	( 170 * FX32_ONE )
#define ZKN_ZUKANTEXTVER_POKETYPE2_MAT_X	( 220 * FX32_ONE )
#define ZKN_ZUKANTEXTVER_POKETYPE_MAT_Y	( 72 * FX32_ONE )
// �^�C�v�A�j���V�[�P���X
enum{
	ZKN_ZUKANTEXTVER_POKETYPE_NORMAL = 0,
};

// �`�|�P�������W
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_MAT_X	( 192 * FX32_ONE )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_MAT_Y	( 52 * FX32_ONE )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_FONT_OFS_X	( -58 )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_FONT_OFS_Y	( -8 )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_BMP_SCX	( 16 )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_BMP_SCY	( 2 )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_TBL_SEQ	( 0x11 )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�}�Ӊ�ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	int*				p_event_key;		// �C�x���g�L�[
	ZKN_GLB_DATA*		p_glb;				// �O���[�o���f�[�^

	int poke_gra_move_x;					// �|�P�O�������
	int poke_gra_move_y;					// �|�P�O�������

	// �}�ӃR�����A�v���f�[�^
	const ZKN_APL_DATA* cp_zukan_common_apl;
	int					fade_mode;			// �t�F�[�h���[�h

	// �\���f�[�^
	int zukan_type;		// �\���^�C�v
	int zukan_page;		// �y�[�W��
} ZKN_ZUKANTEXTVER_GLB;

//-------------------------------------
//	�}�Ӊ�ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// �`��O���[�o���f�[�^
} ZKN_ZUKANTEXTVER_DRAWGLB;

//-------------------------------------
//	�}�Ӊ�ʁ@�`�惏�[�N
//=====================================
typedef struct {
	// �`�|�P����
	CLACT_WORK_PTR  poketype_text_tbl;
	ZKN_FONTOAM_DATA*  p_poketype_text;
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resource�I�u�W�F�|�C���^
	
	// �|�P���X�g�t�F�[�h�p���샏�[�N
	ZKN_UTIL_MOVE_WORK pokegra_move;
	ZKN_UTIL_MOVE_WORK pokelist_move;
} ZKN_ZUKANTEXTVER_DRAW;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		�A�v���P�[�V�����f�[�^�쐬�֌W
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKANTEXTVER_GLB* MakeZukanTextverGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKANTEXTVER_DRAWGLB* MakeZukanTextverDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
//static ZKN_EVENT_DATA* MakeZukanTextverEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanTextverGlb( ZKN_ZUKANTEXTVER_GLB* p_glb );
static void DeleteZukanTextverDrawGlb( ZKN_ZUKANTEXTVER_DRAWGLB* p_glb );
//static void DeleteZukanTextverEvent( ZKN_EVENT_DATA* p_event );


static int ZukanTextverEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanTextverProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanTextverProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanTextverProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanTextverProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanTextverProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// �t�F�[�h�C���A�E�g
static void ZknZukanTextverDefaultFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanTextverDefaultFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb , BOOL fadein_out );
static void ZknZukanTextverChPokeListFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanTextverChPokeListFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out );
static void ZknZukanTextverChOtherFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanTextverChOtherFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb , BOOL fadein_out );

static void ZknZukanTextverSpritePokeGraPalFade( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );

static void ZknZukanTextverOamFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw );
static void ZknZukanTextverOamFadeDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw );

static void ZknZukanTextverPokeGraFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw, int move_x, int move_y, int sync );
static BOOL ZknZukanTextverPokeGraFadeMain( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );
static void ZknZukanTextverPokeListFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw );
static BOOL ZknZukanTextverPokeListFadeMain( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );


// BG�ݒ�
static void ZknZukanTextverLoadResource( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap );
static void ZknZukanTextverReleaseResource( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );
static void ZknZukanTextverSetUpBackGround( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap );
static void ZknZukanTextverSetUpFontBg( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap );
static void ZknZukanTextverFontSetUpText( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang, int page );
static int ZknZukanTextverZukanNameGmmIDGet( int lang );
static void ZknZukanTextvereFontPokeName( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang );
static void ZknZukanTextvereFontPokeType( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang );

// �`�|�P����
static void ZknZukanTextverPokeTypeTextAdd( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap );
static void ZknZukanTextverPokeTypeTextDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw );
static GF_BGL_BMPWIN* ZknZukanTextverPokeTypeTextBmpMake( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int mons_no, int heap );
static void ZknZukanTextverClactResLoad( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap );
static void ZknZukanTextverClactResDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );

// �|�P�������X�g
static void ZknZukanTextverPokeListDrawOn( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap );
static void ZknZukanTextverPokeListDrawOff( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );

// �|�P�����O���t�B�b�N
static void ZknZukanTextverPokeGraDrawOn( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb );
static void ZknZukanTextverPokeGraDrawOff( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�A�v���쐬
 *
 *	@param	p_data		�A�v���P�[�V�����f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	heap		�g�p�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanTextverAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKANTEXTVER_GLB*	p_glb;
	ZKN_ZUKANTEXTVER_DRAWGLB*	p_drawglb;
//	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanTextverGlb( heap, zkn_sys );
	p_drawglb = MakeZukanTextverDrawGlb( heap, zkn_sys );
//	p_event = MakeZukanTextverEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= NULL;
//	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanTextverEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanTextverProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanTextverProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanTextverProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanTextverProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanTextverProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanTextverProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g	�T�u��ʁ@���j���[�A�v���j��
 *
 *	@param	p_data	�A�v���P�[�V�����f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanTextverAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanTextverGlb( p_data->p_glb_data ); 
	DeleteZukanTextverDrawGlb( p_data->p_glb_draw );
//	DeleteZukanTextverEvent( p_data->p_event_data );
}

// �A�v���f�[�^�O���ύX�֐�
//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�C���A�E�g�O���t�B�b�N���W�ݒ�
 *
 *	@param	p_data		�O���t�B�b�N�f�[�^
 *	@param	x			�����W	
 *	@param	y			�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanTextverPokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_data->p_glb_data;

	p_glb->poke_gra_move_x = x;
	p_glb->poke_gra_move_y = y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄt�F�[�h���[�h�ݒ�
 *
 *	@param	p_data		�A�v���P�[�V�����f�[�^
 *	@param	fade_mode	�t�F�[�h���[�h
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanTextverFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_data->p_glb_data;

	p_glb->fade_mode = fade_mode;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӌ���y�[�W�ύX
 *
 *	@param	p_data	�}�ӃA�v��
 *
 *	@retval TRUE	�ύX����
 *	@retval	FALSE	�ύX���Ȃ�����
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanTexverPageAdd( ZKN_APL_DATA* p_data )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_data->p_glb_data;

/*	
	p_glb->zukan_page = (p_glb->zukan_page + 1) % ZKN_WT_WORLD_TEXT_PAGE_NUM;

	return TRUE;
//*/


/* ���{ */
#if( PM_LANG == LANG_JAPAN )
	// �S��2�y�[�W�ڂȂ�
	return FALSE;
#endif
/* �A�����J */
#if( PM_LANG == LANG_ENGLISH )
	// �S��2�y�[�W�ڂȂ�
	return FALSE;
#endif
/* �t�����X */
#if( PM_LANG == LANG_FRANCE )
	// �S��2�y�[�W�ڂȂ�
	return FALSE;
#endif
/* �C�^���A */
#if( PM_LANG == LANG_ITALY )
	// �S��2�y�[�W�ڂȂ�
	return FALSE;
#endif
/* �h�C�c */
#if( PM_LANG == LANG_GERMANY )
	// �S��2�y�[�W�ڂȂ�
	return FALSE;
#endif
/* �X�y�C�� */
#if( PM_LANG == LANG_SPAIN )
	// �S��2�y�[�W�ڂȂ�
	return FALSE;
#endif
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӌ���y�[�W�ݒ�
 *
 *	@param	p_data	�}�ӃA�v���f�[�^
 *	@param	page	�y�[�W	(0�`1)
 *
 *	@retval	TRUE	�ύX����
 *	@retval	FALSE	�ύX���Ȃ�����
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanTexverPageSet( ZKN_APL_DATA* p_data, int page )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_data->p_glb_data;
	BOOL ret = TRUE;

/* ���{ */
#if( PM_LANG == LANG_JAPAN )
	// 2�y�[�W�ڂȂ�
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif
/* �A�����J */
#if( PM_LANG == LANG_ENGLISH )
	// 2�y�[�W�ڂȂ�
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif
/* �t�����X */
#if( PM_LANG == LANG_FRANCE )
	// 2�y�[�W�ڂȂ�
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif
/* �C�^���A */
#if( PM_LANG == LANG_ITALY )
	// 2�y�[�W�ڂȂ�
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif
/* �h�C�c */
#if( PM_LANG == LANG_GERMANY )
	// 2�y�[�W�ڂȂ�
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif
/* �X�y�C�� */
#if( PM_LANG == LANG_SPAIN )
	// 2�y�[�W�ڂȂ�
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif

	p_glb->zukan_page = page;

	return ret;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӌ��ꍑ�R�[�h�ݒ�
 *
 *	@param	p_data	�}�ӃA�v��
 *	@param	lang	���R�[�h
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanTexverTypeSet( ZKN_APL_DATA* p_data, int lang )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_data->p_glb_data;
	p_glb->zukan_type = lang;

/* ���{ */
#if( PM_LANG == LANG_JAPAN )
	// �S��2�y�[�W�ڂȂ�
	p_glb->zukan_page = 0;
#endif
/* �A�����J */
#if( PM_LANG == LANG_ENGLISH )
	// �S��2�y�[�W�ڂȂ�
	p_glb->zukan_page = 0;
#endif
/* �t�����X */
#if( PM_LANG == LANG_FRANCE )
	// �S��2�y�[�W�ڂȂ�
	p_glb->zukan_page = 0;
#endif
/* �C�^���A */
#if( PM_LANG == LANG_ITALY )
	// �S��2�y�[�W�ڂȂ�
	p_glb->zukan_page = 0;
#endif
/* �h�C�c */
#if( PM_LANG == LANG_GERMANY )
	// �S��2�y�[�W�ڂȂ�
	p_glb->zukan_page = 0;
#endif
/* �X�y�C�� */
#if( PM_LANG == LANG_SPAIN )
	// �S��2�y�[�W�ڂȂ�
	p_glb->zukan_page = 0;
#endif
}


//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKANTEXTVER_GLB* MakeZukanTextverGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKANTEXTVER_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKANTEXTVER_GLB) );

	// main��ʂ���̃C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys ); 

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// �}�ӃR�����A�v���O���[�o���f�[�^
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );
	p_glb->cp_zukan_common_apl = p_apl;
	

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}��	�`��O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�`��O���[�o���f�[�^
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKANTEXTVER_DRAWGLB* MakeZukanTextverDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKANTEXTVER_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKANTEXTVER_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKANTEXTVER_DRAWGLB) );

	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );
	
	return p_glb;
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeZukanTextverEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = ZukanTextverEventDataNumGet();

	// �C�x���g�f�[�^�e�[�u���쐬
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeRange( heap, &p_event_tbl[0], zkn_sys, ZKN_ZUKNA_EVENT_CHANGE_RANGE );

	return p_event_tbl;
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanTextverGlb( ZKN_ZUKANTEXTVER_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�`��O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanTextverDrawGlb( ZKN_ZUKANTEXTVER_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanTextverEvent( ZKN_EVENT_DATA* p_event )
{

	GF_ASSERT( p_event );
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );//*/
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃA�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	�}�ӃA�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZukanTextverEventDataNumGet( void )
{
	return ZKN_ZUKANTEXTVER_EVENT_NUM;
}


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	[������]
 *	@brief	�A�v���P�[�V�����v���Z�X	�f�[�^�ύX
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 *	[���C��]
 *	@brief	�A�v���P�[�V�����v���Z�X	�f�[�^�ύX
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_glbdata;
	
	
	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	[�j��]
 *	@brief	�A�v���P�[�V�����v���Z�X	�f�[�^�ύX
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 * [������]
 *
 *	@brief	�A�v���P�[�V�����v���Z�X	�`��
 *
 *	@param	p_glbdraw	�`��O���[�o���f�[�^
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *	@param	cp_dodata	���̏����̓������[�N�f�[�^
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKANTEXTVER_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKANTEXTVER_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_ZUKANTEXTVER_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_ZUKANTEXTVER_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKANTEXTVER_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANTEXTVER_SEQINIT_LOAD:
		ZknZukanTextverLoadResource( p_drawwork, p_drawglb, cp_glb, p_drawdata->heap );

		switch( cp_glb->fade_mode ){
		case ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST:	
			ZknZukanTextverChPokeListFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL:
			ZknZukanTextverDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_OTHER:
			ZknZukanTextverChOtherFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANTEXTVER_SEQINIT_FADEIN:

		switch( cp_glb->fade_mode ){
		case ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST:	
			check = ZknZukanTextverChPokeListFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL:
			check = ZknZukanTextverDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_OTHER:
			check = ZknZukanTextverChOtherFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		}

		if( check ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKANTEXTVER_SEQINIT_END:
		G2_BlendNone();
		return ZKN_PROC_TRUE;

	default:
		break;
	}
	
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [���C��]
 *
 *	@brief	�A�v���P�[�V�����v���Z�X	�`��
 *
 *	@param	p_glbdraw	�`��O���[�o���f�[�^
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *	@param	cp_dodata	���̏����̓������[�N�f�[�^
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [�j��]
 *
 *	@brief	�A�v���P�[�V�����v���Z�X	�`��
 *
 *	@param	p_glbdraw	�`��O���[�o���f�[�^
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	�Ǘ��҂���󂯎��f�[�^�@�i�ۑ����Ă��������f�[�^�j
 *	@param	cp_dodata	���̏����̓������[�N�f�[�^
 *
 *	@retval	ZKN_PROC_TRUE		���̏����֐i�݂܂��B
 *	@retval	ZKN_PROC_FALSE		�܂��i�݂܂���B
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKANTEXTVER_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKANTEXTVER_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
		
	case ZKN_ZUKANTEXTVER_SEQDELETE_FADEOUT_INIT:
		switch( cp_glb->fade_mode ){
		case ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST:	
			ZknZukanTextverChPokeListFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL:
			ZknZukanTextverDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_OTHER:
			ZknZukanTextverChOtherFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		}

		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANTEXTVER_SEQDELETE_FADEOUT:
		switch( cp_glb->fade_mode ){
		case ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST:	
			check = ZknZukanTextverChPokeListFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL:
			check = ZknZukanTextverDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_OTHER:
			check = ZknZukanTextverChOtherFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		}

		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_ZUKANTEXTVER_SEQDELETE_RELEASE:
		ZknZukanTextverReleaseResource( p_drawwork, p_drawglb );
		p_drawdata->seq++;
		break;

	case ZKN_ZUKANTEXTVER_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANTEXTVER_SEQDELETE_END:
		return ZKN_PROC_TRUE;

	default:
		break;
	}
	
	return ZKN_PROC_FALSE;
}






//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�ǂݍ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverLoadResource(  ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap  )
{

	// �O���[�o���̈�ɂ���|�P�������X�g�̍��W��ݒ�
	// �\��ON
	ZknZukanTextverPokeListDrawOn( p_drawglb, cp_glb, heap );

	// �|�P�����O���t�B�b�N�\��ON
	ZknZukanTextverPokeGraDrawOn( p_drawglb, cp_glb );

	// �A�N�^�[���\�[�X�ǂݍ���
	ZknZukanTextverClactResLoad( p_draw, p_drawglb, heap );

	// �`�|�P�����\��
	ZknZukanTextverPokeTypeTextAdd( p_draw, p_drawglb, cp_glb, heap );
	// �w�i�ݒ�
	ZknZukanTextverSetUpBackGround( p_drawglb, heap );

	// �����ʐݒ�
	ZknZukanTextverSetUpFontBg( p_drawglb, cp_glb, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�̔j��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverReleaseResource(  ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{

	// �`�|�P�����\��
	ZknZukanTextverPokeTypeTextDelete( p_draw );
	
	// bmp�j��
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// �A�N�^�[���\�[�X�j��
	ZknZukanTextverClactResDelete( p_draw, p_drawglb );

	// ������ʏ�����
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�w�i�ݒ�
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverSetUpBackGround( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	
	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �|�P�����̕\���g��w�i�ɓ\��t��	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_a_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_ZUKANTEXTVER_POKE_DRAW_FRAME_CX, ZKN_ZUKANTEXTVER_POKE_DRAW_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �e�L�X�g�\���g��w�i�ɓ\��t��	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_e_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_ZUKANTEXTVER_TEXT_FRAME_CX, ZKN_ZUKANTEXTVER_TEXT_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �e�L�X�g�ڍ׃f�[�^�\���g��w�i�ɓ\��t��	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_f_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_ZUKANTEXTVER_TEXTEX_FRAME_CX, ZKN_ZUKANTEXTVER_TEXTEX_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	������ʐݒ�
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverSetUpFontBg( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_ZUKANTEXTVER_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);
	int mons_no = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	int gmm_id;
	int str_width;

	// �ߊl���Ă��邩�`�F�b�N
	if( ZKN_GLBDATA_PokeMonsTypeGet( cp_glb->p_glb ) != ZKN_POKELIST_TYPE_GET ){
		mons_no = 0;	// �ߊl���Ă��Ȃ��̂Ń_�~�[
		GF_ASSERT(0);
	}

/*	// �y�[�W
	MSGMAN_GetString( man, ZNK_ZUKAN_TEXT_06, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKANTEXTVER_FONT_PAGE_NUM_X + ZKN_ZUKANTEXTVER_FONT_PAGE_OFS_X, ZKN_ZUKANTEXTVER_FONT_PAGE_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// �y�[�W��
	STRBUF_SetNumber( str, cp_glb->zukan_page + 1, ZKN_ZUKANTEXTVER_FONT_PAGE_PLACE, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKANTEXTVER_FONT_PAGE_NUM_X, ZKN_ZUKANTEXTVER_FONT_PAGE_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );//*/

	// �}�Ӗ�
	gmm_id = ZknZukanTextverZukanNameGmmIDGet( cp_glb->zukan_type );
	MSGMAN_GetString( man, gmm_id, str );
	str_width = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
	str_width /= 2;	// �Z���^�[����̕��ɂ���
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKNATEXTVER_FONT_ZUKAN_NAME_C_X - str_width, ZKN_ZUKNATEXTVER_FONT_ZUKAN_NAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	

	// �|�P�����i���o�[�`��
	STRBUF_SetNumber( str, mons_no, ZKN_ZUKANTEXTVER_FONT_MONSNO_PLACE, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKNATEXTVER_FONT_MONSNO_X, ZKN_ZUKNATEXTVER_FONT_MONSNO_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// Poke'mon
	MSGMAN_GetString( man, ZNK_ZUKAN_TEXT_05, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKNATEXTVER_FONT_POKEMON_X, ZKN_ZUKNATEXTVER_FONT_POKEMON_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	STRBUF_Delete(str);

	MSGMAN_Delete(man);

	// text�\��
	ZknZukanTextverFontSetUpText( p_drawglb, heap, mons_no, cp_glb->zukan_type, cp_glb->zukan_page );

	// �|�P������
	ZknZukanTextvereFontPokeName( p_drawglb, heap, mons_no, cp_glb->zukan_type );
	
	// �|�P�����^�C�v
	ZknZukanTextvereFontPokeType( p_drawglb, heap, mons_no, cp_glb->zukan_type );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P��������text�Z�b�g
 *	
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *	@param	mons_no		�ݒ胂���X�^�[�i���o�[
 *	@param	lang		���R�[�h
 *	@param	page		�y�[�W
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverFontSetUpText( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang, int page )
{
	STRBUF* str = ZKN_WT_GetText( mons_no, lang, page, heap);
	// �|�P�����̃��b�Z�[�W
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKANTEXTVER_FONT_COMMENT_X, ZKN_ZUKANTEXTVER_FONT_COMMENT_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// �j��
	ZKN_WT_DeleteStrBuf( str );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�`��I��
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeListDrawOn( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap )
{
	// ���X�g�쐬
	ZKN_UTIL_PokeListPokeNameMakeGlb( 
			p_drawglb->p_drawglb, cp_glb->p_glb, heap,
			ZKN_GLBDATA_PokeListTblNoGet( cp_glb->p_glb ), 
			ZKN_ZUKANTEXTVER_POKELIST_MAT_X, ZKN_ZUKANTEXTVER_POKELIST_MAT_Y );

	ZKN_GlbPokeNameTblBGPriSet( p_drawglb->p_drawglb, ZKN_ZUKANTEXTVER_OAM_BG_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�`��I�t
 *
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeListDrawOff( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	ZKN_GlbPokeNameTblDrawFlagSet( p_drawglb->p_drawglb, FALSE );
	ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�\��ON
 *
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeGraDrawOn( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// �|�P�����ݒ�
	ZKN_UTIL_PokemonGraphicSet( p_drawglb->p_drawglb, cp_glb->p_glb, monsno,
			PARA_FRONT, ZKN_ZUKANTEXTVER_POKEGRA_MAT_X, ZKN_ZUKANTEXTVER_POKEGRA_MAT_Y );
	
	// �\��
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�\��OFF
 *
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeGraDrawOff( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );

	// �\��OFF
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, TRUE );

	// �\�t�g�p���b�g�t�F�[�h���������Ă���\��������̂�OFF
	SoftSpritePalFadeOff( p_pokegra );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�̃��\�[�X�ǂݍ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverClactResLoad( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main2_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_main2_lzh_NCGR + ZKN_ZUKAN_FOOT_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_data_oam2_NCLR, FALSE, 
			NARC_zukan_zkn_data_oam2_NCLR + ZKN_ZUKAN_FOOT_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_ZUKAN_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main2_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_main2_lzh_NCER + ZKN_ZUKAN_FOOT_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_main2_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_main2_lzh_NANR + ZKN_ZUKAN_FOOT_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[���\�[�X�j��
 *	
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverClactResDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;


	CLACT_U_CharManagerDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj[ CLACT_U_CELLANM_RES ] );
}	

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����^�C�v�i�`�|�P�����j�̕\���A�N�^�[�쐬
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeTypeTextAdd( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int mons_no			= ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	GF_BGL_BMPWIN* p_bmp;
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR pltt_res;

	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_main2_lzh_NCGR + ZKN_ZUKAN_FOOT_RES_ID,
			NARC_zukan_zkn_data_oam2_NCLR + ZKN_ZUKAN_FOOT_RES_ID, 
			NARC_zukan_zkn_data_oam_main2_lzh_NCER + ZKN_ZUKAN_FOOT_RES_ID,
			NARC_zukan_zkn_data_oam_main2_lzh_NANR + ZKN_ZUKAN_FOOT_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKANTEXTVER_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKANTEXTVER_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// �e�[�u������
	add.mat.x = ZKN_ZUKANTEXTVER_POKETYPE_TEXT_MAT_X;
	add.mat.y = ZKN_ZUKANTEXTVER_POKETYPE_TEXT_MAT_Y;
	p_draw->poketype_text_tbl = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->poketype_text_tbl, ZKN_ZUKANTEXTVER_POKETYPE_TEXT_TBL_SEQ );

	// �߂܂��Ă��邩�`�F�b�N
	if( ZKN_GLBDATA_PokeMonsTypeGet( cp_glb->p_glb ) != ZKN_POKELIST_TYPE_GET ){
		mons_no = 0;	// �_�~�[�f�[�^�\��
	}

	// ������쐬
	p_bmp = ZknZukanTextverPokeTypeTextBmpMake( p_drawglb, mons_no, heap );

	// �p���b�gResource�擾
	pltt_res = ZKN_GlbPokeNameTblResObjGet( p_drawglb->p_drawglb, CLACT_U_PLTT_RES );
	
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_drawglb->p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( pltt_res, NULL );
	fontoam_init.parent		 = p_draw->poketype_text_tbl;
	fontoam_init.x			 = ZKN_ZUKANTEXTVER_POKETYPE_TEXT_FONT_OFS_X;
	fontoam_init.y			 = ZKN_ZUKANTEXTVER_POKETYPE_TEXT_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_ZUKANTEXTVER_OAM_BG_PRI;
	fontoam_init.soft_pri	 = ZKN_ZUKANTEXTVER_OAM_SOFT_PRI - 1;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;
	fontoam_init.p_bmp		 = p_bmp;
	p_draw->p_poketype_text = ZKN_FONTOAM_Make( &fontoam_init );
	

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( p_bmp );

}


//----------------------------------------------------------------------------
/**
 *	@brief	�`�|�P����������BMP�쐬
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	mons_no		�����X�^�[�i���o�[
 *	@param	heap		�q�[�v
 *
 *	@return	�쐬�r�b�g�}�b�v
 *
 *	�j�����K�v
 */
//-----------------------------------------------------------------------------
static GF_BGL_BMPWIN* ZknZukanTextverPokeTypeTextBmpMake( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int mons_no, int heap )
{
	GF_BGL_BMPWIN* p_bmp;
	STRBUF* str;

	p_bmp = ZKN_FONTOAM_GetBmp( p_drawglb->p_drawglb->fontoam_sys, ZKN_ZUKANTEXTVER_POKETYPE_TEXT_BMP_SCX, ZKN_ZUKANTEXTVER_POKETYPE_TEXT_BMP_SCY );

	// �`�|�P����������擾
	str = ZKN_WT_GetPokeType( mons_no, PM_LANG, heap );
	ZKN_FONTOAM_PrintBmpStrBuf( p_drawglb->p_drawglb->fontoam_sys,
			p_bmp, str, 0, 0 );
	ZKN_WT_DeleteStrBuf( str );

	return p_bmp;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����^�C�vtext�A�N�^�[�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeTypeTextDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw )
{
	CLACT_Delete( p_draw->poketype_text_tbl );
	p_draw->poketype_text_tbl = NULL;
	ZKN_FONTOAM_Delete( p_draw->p_poketype_text );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄf�t�H���g�t�F�[�h����
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���A�E�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverDefaultFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out )
{
	
	// ������OAM�ݒ�
	ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_XLU );
	ZknZukanTextverOamFadeInit( p_draw );

	// �u���C�g�l�X���g���ėǂ�������
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKANTEXTVER_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKANTEXTVER_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );

		}
	}

	// �|�P�O���p���b�g�t�F�[�h�ݒ�
	ZknZukanTextverSpritePokeGraPalFade( p_drawglb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄf�t�H���g�t�F�[�h�����@�I���`�F�b�N
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C�� TRUE �A�E�g FALSE
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanTextverDefaultFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;
	
	// �t�F�[�h���[�N��}�Ӄf�[�^���������Ă悢���`�F�b�N
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}
	

	if( check == TRUE ){

		// �t�F�[�h�C���̂Ƃ��͔������j��
		if( fadein_out == TRUE ){
			// OAM�������ݒ�j��
			ZknZukanTextverOamFadeDelete( p_draw );
			ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
		}else{
			// �|�P�����O���t�B�b�N�\��OFF
			ZknZukanTextverPokeGraDrawOff( p_drawglb );

			// �O���[�o���̈�ɂ���|�P�������X�g�\��OFF
			ZknZukanTextverPokeListDrawOff( p_drawglb );
		}
	}else{
		// �|�P�O���p���b�g�t�F�[�h�ݒ�
		ZknZukanTextverSpritePokeGraPalFade( p_drawglb );
	}

	return check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P���X�g�Ƃ̃t�F�[�h�������N�G�X�g
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o��
 *	@param	fadein_out	�t�F�[�h�C���A�E�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverChPokeListFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknZukanTextverOamFadeInit( p_draw );


	// �t�F�[�h�A�E�g�̎������̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N�t�F�[�h
		ZknZukanTextverPokeGraFadeInit( p_draw, cp_glb->poke_gra_move_x, cp_glb->poke_gra_move_y, ZKN_FADE_SYNC_LONG_COMMON );

		// �|�P�����O���t�B�b�N�t�F�[�h
		ZknZukanTextverPokeListFadeInit( p_draw );
	}

	// �u���C�g�l�X���g���ėǂ�������
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKANTEXTVER_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKANTEXTVER_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );

		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P���X�g�Ƃ̃t�F�[�h����	�I���`�F�b�N
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���A�E�g
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanTextverChPokeListFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check[ 3 ];
	int i;
	

	// �t�F�[�h�A�E�g�̂Ƃ��݂̂̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N
		check[0] = ZknZukanTextverPokeGraFadeMain( p_draw, p_drawglb );

		// �|�P�������X�g
		check[1] = ZknZukanTextverPokeListFadeMain( p_draw, p_drawglb );
	}else{
		check[0] = TRUE;
		check[1] = TRUE;
	}
	
	// �u���C�g�l�X���g�p���Ă悢�Ƃ��͎�����fade�𓮂���
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check[2] = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check[2] = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}

	for( i=0; i<3; i++ ){
		if( check[i] == FALSE ){
			break;
		}
	}

	if( i==3 ){

		// �t�F�[�h�C���̂Ƃ��͔������j��
		if( fadein_out == TRUE ){
			// OAM�������ݒ�j��
			ZknZukanTextverOamFadeDelete( p_draw );
		}
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̑���ʂւ̈ړ�
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���A�E�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverChOtherFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknZukanTextverOamFadeInit( p_draw );

	// �|�P�������X�g�e�[�u����������
	ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_XLU );


	// �t�F�[�h�A�E�g�̎������̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N�t�F�[�h
		ZknZukanTextverPokeGraFadeInit( p_draw, cp_glb->poke_gra_move_x, cp_glb->poke_gra_move_y, ZKN_FADE_SYNC_COMMON );
	}

	// �u���C�g�l�X���g���ėǂ�������
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKANTEXTVER_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKANTEXTVER_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );

		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̑���ʂƂ̃t�F�[�h����	�I���`�F�b�N
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���A�E�g
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanTextverChOtherFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb , BOOL fadein_out )
{
	BOOL check[ 2 ];
	int i;
	

	// �t�F�[�h�A�E�g�̂Ƃ��݂̂̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N
		check[0] = ZknZukanTextverPokeGraFadeMain( p_draw, p_drawglb );

	}else{
		check[0] = TRUE;
	}
	
	// �u���C�g�l�X���g�p���Ă悢�Ƃ��͎�����fade�𓮂���
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check[1] = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check[1] = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}

	for( i=0; i<2; i++ ){
		if( check[i] == FALSE ){
			break;
		}
	}

	if( i==2 ){

		// �t�F�[�h�C���̂Ƃ��͔������j��
		if( fadein_out == TRUE ){
			// OAM�������ݒ�j��
			ZknZukanTextverOamFadeDelete( p_draw );

			// �|�P�e�[�u��
			ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
		}else{
			// �O���[�o���̈�ɂ���|�P�������X�g�\��OFF
			ZknZukanTextverPokeListDrawOff( p_drawglb );
		}
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	OAM�̃t�F�[�h����������
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverOamFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw )
{
	// �`�|�P����
	CLACT_ObjModeSet( p_draw->poketype_text_tbl, GX_OAM_MODE_XLU );
	FONTOAM_ObjModeSet( p_draw->p_poketype_text->p_fontoam, GX_OAM_MODE_XLU );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�̃t�F�[�h�������Z�b�g
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverOamFadeDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw )
{
	// �`�|�P����
	CLACT_ObjModeSet( p_draw->poketype_text_tbl, GX_OAM_MODE_NORMAL );
	FONTOAM_ObjModeSet( p_draw->p_poketype_text->p_fontoam, GX_OAM_MODE_NORMAL );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�p���b�g�t�F�[�h�l�ݒ�
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverSpritePokeGraPalFade( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	// �u���C�g�l�X�l�ݒ�
	ZKN_GLB_SpritePokeGraPalFade( p_drawglb->p_drawglb, &p_drawglb->p_drawglb->fade );
}

//----------------------------------------------------------------------------
/**
 * [�|�P�������X�g��ʃt�F�[�h]
 *	@brief	�|�P�����O���t�B�b�N�t�F�[�h������
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	move_x	���삘���W
 *	@param	move_y	���삙���W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeGraFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw, int move_x, int move_y, int sync )
{
	ZKN_UTIL_MoveReq( &p_draw->pokegra_move, ZKN_ZUKANTEXTVER_POKEGRA_MAT_X, move_x, ZKN_ZUKANTEXTVER_POKEGRA_MAT_Y, move_y, sync);
}

//----------------------------------------------------------------------------
/**
 * [�|�P�������X�g��ʃt�F�[�h]
 *	@brief	�|�P�����O���t�B�b�N�t�F�[�h
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanTextverPokeGraFadeMain( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	BOOL check;
	
	check = ZKN_UTIL_MoveMain( &p_draw->pokegra_move );

	// ���W�ݒ�
	ZKN_GlbPokemonGraphicSetMatrix( p_drawglb->p_drawglb, p_draw->pokegra_move.x, p_draw->pokegra_move.y );

	return check;
}

//----------------------------------------------------------------------------
/**
 * [�|�P�������X�g��ʃt�F�[�h]
 *	@brief	�|�P�������X�g�t�F�[�h
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeListFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw )
{
	ZKN_UTIL_MoveReq( &p_draw->pokelist_move, ZKN_ZUKANTEXTVER_POKELIST_MAT_IX, ZKN_POKELIST_TBL_MAT_X, ZKN_ZUKANTEXTVER_POKELIST_MAT_IY, ZKN_POKELIST_TBL_MAT_Y, ZKN_FADE_SYNC_LONG_COMMON);
}

//----------------------------------------------------------------------------
/**
 * [�|�P�������X�g��ʃt�F�[�h]
 *	@brief	�|�P�������X�g�t�F�[�h
 *	
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanTextverPokeListFadeMain( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	BOOL check;
	
	check = ZKN_UTIL_MoveMain( &p_draw->pokelist_move );

	// ���W�ݒ�
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet( p_drawglb->p_drawglb, p_draw->pokelist_move.x, p_draw->pokelist_move.y );

	return check;
}


//----------------------------------------------------------------------------
/**
 *	@brief	���R�[�h�ɑΉ�����GMM�f�[�^ID�擾
 *
 *	@param	lang	���R�[�h
 *
 *	@return	GMM�f�[�^
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverZukanNameGmmIDGet( int lang )
{
	int gmm_id;
	
	switch( lang ){
	case LANG_JAPAN:		///<	����R�[�h�F���{
		gmm_id = ZNK_ZUKAN_TEXT_00;
		break;
		
	case LANG_ENGLISH:		///<	����R�[�h�F�p��
		gmm_id = ZNK_ZUKAN_TEXT_00;
		break;
		
	case LANG_FRANCE:		///<	����R�[�h�F�t�����X��
		gmm_id = ZNK_ZUKAN_TEXT_01;
		break;
		
	case LANG_ITALY:		///<	����R�[�h�F�C�^���A��
		gmm_id = ZNK_ZUKAN_TEXT_03;
		break;
		
	case LANG_GERMANY:		///<	����R�[�h�F�h�C�c��
		gmm_id = ZNK_ZUKAN_TEXT_02;
		break;
		
	case LANG_SPAIN:		///<	����R�[�h�F�X�y�C����
		gmm_id = ZNK_ZUKAN_TEXT_04;
		break;
	default:
		//�@��������
		GF_ASSERT( 0 );
		break;
	}

	return gmm_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P��������`��
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	heap			�q�[�v
 *	@param	mons_no			�����X�^�[�i���o�[
 *	@param	lang			���R�[�h
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextvereFontPokeName( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang )
{
	STRBUF* str = ZKN_WT_GetPokeName( mons_no, lang, heap);
	// �|�P�����̃��b�Z�[�W
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKNATEXTVER_FONT_MONSNAME_X, ZKN_ZUKNATEXTVER_FONT_MONSNAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// �j��
	ZKN_WT_DeleteStrBuf( str );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����^�C�v�̕`��
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	heap			�q�[�v
 *	@param	mons_no			�����X�^�[�i���o�[
 *	@param	lang			���R�[�h
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextvereFontPokeType( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang )
{
	STRBUF* str = ZKN_WT_GetPokeType( mons_no, lang, heap);
	u32 x_mat;

	// X���W�v�Z
	x_mat = ZKN_ZUKNATEXTVER_FONT_POKEMON_X - (FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 ) + ZKN_ZUKNATEXTVER_FONT_MONSTYPE_X_OFS);
	
	// �|�P�����̃��b�Z�[�W
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, x_mat, ZKN_ZUKNATEXTVER_FONT_MONSTYPE_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// �j��
	ZKN_WT_DeleteStrBuf( str );
}
