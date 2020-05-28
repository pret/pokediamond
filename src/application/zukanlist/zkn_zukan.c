//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan.c
 *	@brief		�}�ӃA�v���P�[�V����
 *	@author		tomoya takahashi
 *	@data		2006.01.20
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
#include "include/application/zukanlist/zkn_world_text_sys.h"

// �G�t�F�N�g�ō��W��Link�����邽�߁A�d���Ȃ��C���N���[�h
#include "include/application/zukanlist/zkn_pokelist.h"

#define	__ZKN_ZUKAN_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan.h"


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
#define ZKN_ZUKAN_EVENT_NUM ( 0 )	// �C�x���g��
#define ZKN_ZUKAN_OAM_BG_PRI	( 0 )
#define ZKN_ZUKAN_OAM_SOFT_PRI	( 32 )

// BG�u���C�g�l�X�t�F�[�h��
#define ZKN_ZUKAN_BRIGHTNESS_MSK	( GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )
#define ZKN_ZUKAN_BRIGHTNESSCH_POKELIST_MSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-------------------------------------
//	�}�ӃZ���A�N�^�[��
//=====================================
enum{
	ZKN_ZUKAN_CLACT_FOOT,
	ZKN_ZUKAN_CLACT_TYPE1,
	ZKN_ZUKAN_CLACT_TYPE2,
	ZKN_ZUKAN_CLACT_NUM,
};

// �w�i���W
#define ZKN_ZUKAN_POKE_DRAW_FRAME_CX	( 0 )
#define ZKN_ZUKAN_POKE_DRAW_FRAME_CY	( 3 )
#define ZKN_ZUKAN_FOOT_FRAME_CX			( 12 )
#define ZKN_ZUKAN_FOOT_FRAME_CY			( 8 )
#define ZKN_ZUKAN_TEXT_FRAME_CX			( 0 )
#define ZKN_ZUKAN_TEXT_FRAME_CY			( 16 )


// �������
#define ZKN_ZUKAN_NUM_STR		( 64 )	// �o�b�t�@�T�C�Y
#define ZKN_ZUKAN_NUM_STRTEXT	( 256 )	// �o�b�t�@�T�C�Y
#define ZKN_ZUKAN_FONT_HEIGHTGRAM_X	( 152 )
#define ZKN_ZUKAN_FONT_HEIGHT_Y	( 88 )
#define ZKN_ZUKAN_FONT_GRAM_Y	( 104 )
#define ZKN_ZUKAN_FONT_HEIGHTGRAM_TEXT_X	( 192 )

#define ZKN_ZUKAN_FONT_COMMENT_X	( 44 )
#define ZKN_ZUKAN_FONT_COMMENT_Y	( 136 )

//-------------------------------------
//	�`�揉�����V�[�P���X
//=====================================
enum
{
	ZKN_ZUKAN_SEQINIT_ALLOC,
	ZKN_ZUKAN_SEQINIT_LOAD,
	ZKN_ZUKAN_SEQINIT_FADEIN,
	ZKN_ZUKAN_SEQINIT_END,
};

//-------------------------------------
//	�}�Ӕj���V�[�P���X
//=====================================
enum{
	ZKN_ZUKAN_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKAN_SEQDELETE_FADEOUT,
	ZKN_ZUKAN_SEQDELETE_RELEASE,
	ZKN_ZUKAN_SEQDELETE_FREE,
	ZKN_ZUKAN_SEQDELETE_END,
};

// �|�P�������X�g���W
#define ZKN_ZUKAN_POKELIST_MAT_X	( ZKN_ZUKAN_POKELIST_MAT_IX*FX32_ONE )
#define ZKN_ZUKAN_POKELIST_MAT_Y	( ZKN_ZUKAN_POKELIST_MAT_IY*FX32_ONE )

// ����
#define ZKN_ZUKAN_FOOT_MAT_X	( 120 * FX32_ONE )
#define ZKN_ZUKAN_FOOT_MAT_Y	( 88 * FX32_ONE )

// �^�C�v���W
#define ZKN_ZUKAN_POKETYPE1_MAT_X	( 170 * FX32_ONE )
#define ZKN_ZUKAN_POKETYPE2_MAT_X	( 220 * FX32_ONE )
#define ZKN_ZUKAN_POKETYPE_MAT_Y	( 72 * FX32_ONE )

// �`�|�P�������W
#define ZKN_ZUKAN_POKETYPE_TEXT_MAT_X	( 192 * FX32_ONE )
#define ZKN_ZUKAN_POKETYPE_TEXT_MAT_Y	( 52 * FX32_ONE )


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�}�Ӊ�ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// �`��O���[�o���f�[�^
} ZKN_ZUKAN_DRAWGLB;

#if 0
//-------------------------------------
//	�}�Ӊ�ʁ@�������[�N
//=====================================
typedef struct {
	int dummy;
} ZKN_ZUKAN_WORK;
#endif

//-------------------------------------
//	�}�Ӊ�ʁ@�`�惏�[�N
//=====================================
typedef struct {
	CLACT_WORK_PTR	clact[ ZKN_ZUKAN_CLACT_NUM ];

	// �`�|�P����
	CLACT_WORK_PTR  poketype_text_tbl;
	ZKN_FONTOAM_DATA*  p_poketype_text;
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resource�I�u�W�F�|�C���^
	
	// ���՗p
	CLACT_U_RES_OBJ_PTR foot_resobj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// �|�P���X�g�t�F�[�h�p���샏�[�N
	ZKN_UTIL_MOVE_WORK pokegra_move;
	ZKN_UTIL_MOVE_WORK pokelist_move;
} ZKN_ZUKAN_DRAW;


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
static ZKN_ZUKAN_GLB* MakeZukanGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKAN_DRAWGLB* MakeZukanDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
//static ZKN_EVENT_DATA* MakeZukanEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanGlb( ZKN_ZUKAN_GLB* p_glb );
static void DeleteZukanDrawGlb( ZKN_ZUKAN_DRAWGLB* p_glb );
//static void DeleteZukanEvent( ZKN_EVENT_DATA* p_event );


static int ZukanEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknZukanProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// �t�F�[�h�C���A�E�g
static void ZknZukanDefaultFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanDefaultFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb , BOOL fadein_out );
static void ZknZukanChPokeListFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanChPokeListFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out );
static void ZknZukanChOtherFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanChOtherFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb , BOOL fadein_out );

static void ZknZukanSpritePokeGraPalFade( ZKN_ZUKAN_DRAWGLB* p_drawglb );

static void ZknZukanOamFadeInit( ZKN_ZUKAN_DRAW* p_draw );
static void ZknZukanOamFadeDelete( ZKN_ZUKAN_DRAW* p_draw );

static void ZknZukanPokeGraFadeInit( ZKN_ZUKAN_DRAW* p_draw, int move_x, int move_y, int sync_num );
static BOOL ZknZukanPokeGraFadeMain( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );
static void ZknZukanPokeListFadeInit( ZKN_ZUKAN_DRAW* p_draw );
static BOOL ZknZukanPokeListFadeMain( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );


// BG�ݒ�
static void ZknZukanLoadResource( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanReleaseResource( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );
static void ZknZukanSetUpBackGround( ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSetUpFontBg( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanFontSetUpHeight( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, u32 color_msk );
static void ZknZukanFontSetUpGram( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, u32 color_msk );
static void ZknZukanFontSetUpText( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, int page, u32 color_msk );

// ����
static void ZknZukanFootSetUp( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanFootDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );
static void ZknZukanFootResLoad( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap, int mons_no );
static void ZknZukanFootResDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );
static void ZknZukanFootActAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap );
static void ZknZukanFootActDelete( ZKN_ZUKAN_DRAW* p_draw );

// ���ՈȊO�̃A�N�^�[
static void ZknZukanClactResLoad( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap );
static void ZknZukanClactResDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );
static void ZknZukanClactAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanClactDelete( ZKN_ZUKAN_DRAW* p_draw );

// �`�|�P����
static void ZknZukanPokeTypeTextAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanPokeTypeTextDelete( ZKN_ZUKAN_DRAW* p_draw );

// �|�P�������X�g
static void ZknZukanPokeListDrawOn( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanPokeListDrawOff( ZKN_ZUKAN_DRAWGLB* p_drawglb );

// �|�P�����O���t�B�b�N
static void ZknZukanPokeGraDrawOn( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb );
static void ZknZukanPokeGraDrawOff( ZKN_ZUKAN_DRAWGLB* p_drawglb );

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
void ZKN_ZukanAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKAN_GLB*	p_glb;
	ZKN_ZUKAN_DRAWGLB*	p_drawglb;
//	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanGlb( heap, zkn_sys );
	p_drawglb = MakeZukanDrawGlb( heap, zkn_sys );
//	p_event = MakeZukanEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= NULL;
//	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanProcDrawFuncDelete;
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
void ZKN_ZukanAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanGlb( p_data->p_glb_data ); 
	DeleteZukanDrawGlb( p_data->p_glb_draw );
//	DeleteZukanEvent( p_data->p_event_data );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�����e�L�X�g�`��@�y�[�W�ݒ�
 *
 *	@param	p_data	�f�[�^
 *	@param	add		�����Z�l
 *
 *	@retval	TRUE	�ݒ肵�܂���
 *	@retval	FALSE	�ݒ肵�܂���ł���
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanAplPageAdd( ZKN_ZUKAN_GLB* p_data, int add )
{
/* ���{ */
#if( PM_LANG == LANG_JAPAN )
	// �S��2�y�[�W�ڂȂ�
	return FALSE;//*/

	// 2�y�[�W������΂���
/*	p_data->zukan_page = (p_data->zukan_page + add) % ZKN_WT_HOME_TEXT_PAGE_NUM;
	return TRUE;//*/
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
 *	@brief	�����e�L�X�g�y�[�W���ݒ�
 *
 *	@param	p_data	�f�[�^
 *	@param	set		�Z�b�g�y�[�W��
 *
 *	@retval	TRUE	�ݒ肵�܂���
 *	@retval	FALSE	�ݒ肵�܂���ł���
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanAplPageSet( ZKN_ZUKAN_GLB* p_data, int set )
{
	BOOL ret = TRUE;
	
/* ���{ */
#if( PM_LANG == LANG_JAPAN )
	// �S��2�y�[�W�ڂȂ�
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif
/* �A�����J */
#if( PM_LANG == LANG_ENGLISH )
	// �S��2�y�[�W�ڂȂ�
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif
/* �t�����X */
#if( PM_LANG == LANG_FRANCE )
	// �S��2�y�[�W�ڂȂ�
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif
/* �C�^���A */
#if( PM_LANG == LANG_ITALY )
	// �S��2�y�[�W�ڂȂ�
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif
/* �h�C�c */
#if( PM_LANG == LANG_GERMANY )
	// �S��2�y�[�W�ڂȂ�
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif
/* �X�y�C�� */
#if( PM_LANG == LANG_SPAIN )
	// �S��2�y�[�W�ڂȂ�
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif

	p_data->zukan_page = set;
	return ret;
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
static ZKN_ZUKAN_GLB* MakeZukanGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_GLB) );

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
static ZKN_ZUKAN_DRAWGLB* MakeZukanDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_DRAWGLB) );

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
static ZKN_EVENT_DATA* MakeZukanEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = ZukanEventDataNumGet();

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
static void DeleteZukanGlb( ZKN_ZUKAN_GLB* p_glb )
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
static void DeleteZukanDrawGlb( ZKN_ZUKAN_DRAWGLB* p_glb )
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
static void DeleteZukanEvent( ZKN_EVENT_DATA* p_event )
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
static int ZukanEventDataNumGet( void )
{
	return ZKN_ZUKAN_EVENT_NUM;
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
static int ZknZukanProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_GLB* p_glb = p_glbdata;
	// �}�ӌ����t���O�ݒ�
	ZKN_GLBDATA_PokeTextSeeSetMonsno( p_glb->p_glb, ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb ) );	
	ZKN_GLBDATA_PokeTextSeeSetZknMode( p_glb->p_glb, ZKN_GLBDATA_PokeZknModeGet( p_glb->p_glb ) );	
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
static int ZknZukanProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_GLB* p_glb = p_glbdata;
	
	
	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	switch( p_dodata->seq ){
	case 0:	// �����`�F�b�N
		if( p_glb->mons_snd_req == TRUE ){
			Snd_PMVoicePlayEx( PV_ZUKAN_NORMAL, ZKN_GLBDATA_PokeMonsNoGet(p_glb->p_glb), 
					PV_PTN_PARAM_NONE, PV_PTN_PARAM_NONE, PV_PTN_PARAM_NONE );	//�؃��b�v(default)

			p_glb->mons_snd_req = FALSE;
		}
		p_dodata->seq ++;
		break;

	default:
		break;
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
static int ZknZukanProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	Snd_PMVoiceStop(0);
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
static int ZknZukanProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKAN_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKAN_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_ZUKAN_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_ZUKAN_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKAN_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_SEQINIT_LOAD:
		ZknZukanLoadResource( p_drawwork, p_drawglb, cp_glb, p_drawdata->heap );

		switch( cp_glb->fade_mode ){
		case ZKN_ZUKAN_FADE_MODE_CHPOKELIST:	
			ZknZukanChPokeListFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKAN_FADE_MODE_NORMAL:
			ZknZukanDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKAN_FADE_MODE_OTHER:
			ZknZukanChOtherFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_SEQINIT_FADEIN:

		switch( cp_glb->fade_mode ){
		case ZKN_ZUKAN_FADE_MODE_CHPOKELIST:	
			check = ZknZukanChPokeListFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKAN_FADE_MODE_NORMAL:
			check = ZknZukanDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKAN_FADE_MODE_OTHER:
			check = ZknZukanChOtherFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		}

		if( check ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKAN_SEQINIT_END:
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
static int ZknZukanProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
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
static int ZknZukanProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKAN_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKAN_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
		
	case ZKN_ZUKAN_SEQDELETE_FADEOUT_INIT:
		switch( cp_glb->fade_mode ){
		case ZKN_ZUKAN_FADE_MODE_CHPOKELIST:	
			ZknZukanChPokeListFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKAN_FADE_MODE_NORMAL:
			ZknZukanDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKAN_FADE_MODE_OTHER:
			ZknZukanChOtherFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		}

		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_SEQDELETE_FADEOUT:
		switch( cp_glb->fade_mode ){
		case ZKN_ZUKAN_FADE_MODE_CHPOKELIST:	
			check = ZknZukanChPokeListFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKAN_FADE_MODE_NORMAL:
			check = ZknZukanDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKAN_FADE_MODE_OTHER:
			check = ZknZukanChOtherFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		}

		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_ZUKAN_SEQDELETE_RELEASE:
		ZknZukanReleaseResource( p_drawwork, p_drawglb );
		p_drawdata->seq++;
		break;

	case ZKN_ZUKAN_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_SEQDELETE_END:
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
static void ZknZukanLoadResource(  ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap  )
{

	// �O���[�o���̈�ɂ���|�P�������X�g�̍��W��ݒ�
	// �\��ON
	ZknZukanPokeListDrawOn( p_drawglb, cp_glb, heap );

	// �|�P�����O���t�B�b�N�\��ON
	ZknZukanPokeGraDrawOn( p_drawglb, cp_glb );

	// �A�N�^�[���\�[�X�ǂݍ���
	ZknZukanClactResLoad( p_draw, p_drawglb, heap );

	// �`�|�P�����\��
	ZknZukanPokeTypeTextAdd( p_draw, p_drawglb, cp_glb, heap );
	// �w�i�ݒ�
	ZknZukanSetUpBackGround( p_drawglb, heap );

	// �����ʐݒ�
	ZknZukanSetUpFontBg( p_drawglb, cp_glb, heap );

	// �߂܂��Ă��邩�`�F�b�N
	if( ZKN_GLBDATA_PokeMonsTypeGet( cp_glb->p_glb ) == ZKN_POKELIST_TYPE_GET ){
		// ����
		ZknZukanFootSetUp( p_draw, p_drawglb, cp_glb, heap );

		
		// �A�N�^�[�o�^
		ZknZukanClactAdd( p_draw, p_drawglb, cp_glb, heap );
	}


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
static void ZknZukanReleaseResource(  ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
{

	// �`�|�P�����\��
	ZknZukanPokeTypeTextDelete( p_draw );
	
	// bmp�j��
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// ����
	ZknZukanFootDelete( p_draw, p_drawglb );

	// �A�N�^�[�j��
	ZknZukanClactDelete( p_draw );	

	// �A�N�^�[���\�[�X�j��
	ZknZukanClactResDelete( p_draw, p_drawglb );

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
static void ZknZukanSetUpBackGround( ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap )
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
			ZKN_ZUKAN_POKE_DRAW_FRAME_CX, ZKN_ZUKAN_POKE_DRAW_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �|�P�������Ղ̕\���g��w�i�ɓ\��t��	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_b_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_ZUKAN_FOOT_FRAME_CX, ZKN_ZUKAN_FOOT_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �|�P��������text�g��\��t��	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_d_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_ZUKAN_TEXT_FRAME_CX, ZKN_ZUKAN_TEXT_FRAME_CY,
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
static void ZknZukanSetUpFontBg( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap )
{
	int mons_no = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// �ߊl���Ă��邩�`�F�b�N
	if( ZKN_GLBDATA_PokeMonsTypeGet( cp_glb->p_glb ) != ZKN_POKELIST_TYPE_GET ){
		mons_no = 0;	// �ߊl���Ă��Ȃ��̂Ń_�~�[
	}
	ZknZukanSetUpFontBg_Minute( &p_drawglb->p_drawglb->bmp_mfont,  mons_no, heap, cp_glb->zukan_page, ZKN_BG_FONT_COLOR_MSK );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӕ�����f�[�^�������݊֐�
 *
 *	@param	p_bmp		�r�b�g�}�b�v
 *	@param	monsno		�����X�^�[�i���o�[
 *	@param	heap		�q�[�v
 *	@param	page		�y�[�W
 *	@param	color_msk	�J���[�}�X�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZknZukanSetUpFontBg_Minute( GF_BGL_BMPWIN* p_bmp, int monsno, int heap, int page, u32 color_msk )
{
	STRBUF* str = STRBUF_Create(ZKN_ZUKAN_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);


	// ����
	MSGMAN_GetString( man, ZNK_ZUKAN_01, str );
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_ZUKAN_FONT_HEIGHTGRAM_X, ZKN_ZUKAN_FONT_HEIGHT_Y, 0, color_msk, NULL );

	// �d��
	MSGMAN_GetString( man, ZNK_ZUKAN_02, str );
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_ZUKAN_FONT_HEIGHTGRAM_X, ZKN_ZUKAN_FONT_GRAM_Y, 0, color_msk, NULL );

	STRBUF_Delete(str);

	MSGMAN_Delete(man);


	// �����\��
	ZknZukanFontSetUpHeight( p_bmp, heap, monsno, color_msk );

	// �d���\��
	ZknZukanFontSetUpGram( p_bmp, heap, monsno, color_msk );

	// text�\��
	ZknZukanFontSetUpText( p_bmp, heap, monsno, page, color_msk );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�����t�H���g�Z�b�g
 *
 *	@param	p_bmp		�r�b�g�}�b�v	
 *	@param	heap		�q�[�v
 *	@param	mons_no		�ݒ胂���X�^�[�i���o�[
 *	@param	color_msk	�J���[�}�X�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFontSetUpHeight( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, u32 color_msk )
{
	STRBUF* str = STRBUF_Create(ZKN_ZUKAN_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_height_dat, heap);

	// ����
	MSGMAN_GetString( man, mons_no, str );
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_ZUKAN_FONT_HEIGHTGRAM_TEXT_X, ZKN_ZUKAN_FONT_HEIGHT_Y, 0, color_msk, NULL );

	STRBUF_Delete(str);

	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�d���t�H���g�Z�b�g
 *
 *	@param	p_bmp		�r�b�g�}�b�v	
 *	@param	heap		�q�[�v
 *	@param	mons_no		�ݒ胂���X�^�[�i���o�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFontSetUpGram( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, u32 color_msk )
{
	STRBUF* str = STRBUF_Create(ZKN_ZUKAN_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_gram_dat, heap);

	// �d��
	MSGMAN_GetString( man, mons_no, str );
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_ZUKAN_FONT_HEIGHTGRAM_TEXT_X, ZKN_ZUKAN_FONT_GRAM_Y, 0, color_msk, NULL );

	STRBUF_Delete(str);

	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P��������text�Z�b�g
 *	
 *	@param	p_bmp		�r�b�g�}�b�v
 *	@param	heap		�q�[�v
 *	@param	mons_no		�ݒ胂���X�^�[�i���o�[
 *	@param	page		�y�[�W
 *	@param	color_msk	�J���[�}�X�N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFontSetUpText( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, int page, u32 color_msk )
{
	STRBUF* str = ZKN_WT_GetText( mons_no, PM_LANG, page, heap);
	// �|�P�����̃��b�Z�[�W
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_ZUKAN_FONT_COMMENT_X, ZKN_ZUKAN_FONT_COMMENT_Y, 0, color_msk, NULL );

	// �j��
	ZKN_WT_DeleteStrBuf( str );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���Ս쐬
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	p_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootSetUp( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap )
{
	int mons_no = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	
	// ���\�[�X�ǂݍ���
	ZknZukanFootResLoad( p_draw, p_drawglb, heap, mons_no );

	// �o�^
	ZknZukanFootActAdd( p_draw, p_drawglb, heap );

}

//----------------------------------------------------------------------------
/**
 *	@brief	���Քj��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
{

	// �j��
	ZknZukanFootActDelete( p_draw );
	
	// ���\�[�X�j��
	ZknZukanFootResDelete( p_draw, p_drawglb );

}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�ǂݍ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *	@param	mons_no		�����X�^�[�i���o�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootResLoad( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap, int mons_no )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	int arc_file = PokeFootArcFileGet();
	int char_idx = PokeFootCharDataIdxGet( mons_no );
	int pltt_idx = PokeFootPlttDataIdxGet();
	int cell_idx = PokeFootCellDataIdxGet();
	int cellanm_idx = PokeFootCellAnmDataIdxGet();

	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->foot_resobj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], arc_file,
			char_idx, TRUE,
			ZKN_ZUKAN_FOOT_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->foot_resobj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->foot_resobj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_draw->foot_resobj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], arc_file,
			pltt_idx, FALSE, 
			ZKN_ZUKAN_FOOT_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_ZUKAN_FOOT_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_draw->foot_resobj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->foot_resobj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->foot_resobj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], arc_file,
			cell_idx, TRUE,
			ZKN_ZUKAN_FOOT_RES_ID, 
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->foot_resobj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], arc_file, 
			cellanm_idx, TRUE,
			ZKN_ZUKAN_FOOT_RES_ID, 
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӑ��Ճ��\�[�X�j��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootResDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;

	if( p_draw->foot_resobj[ CLACT_U_CHAR_RES ] == NULL ){
		return;
	}

	CLACT_U_CharManagerDelete( p_draw->foot_resobj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw->foot_resobj[ CLACT_U_PLTT_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->foot_resobj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->foot_resobj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->foot_resobj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->foot_resobj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ՃA�N�^�[�ǉ�
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootActAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	
	// �e�{�^����o�^
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			ZKN_ZUKAN_FOOT_RES_ID,
			ZKN_ZUKAN_FOOT_RES_ID,
			ZKN_ZUKAN_FOOT_RES_ID,
			ZKN_ZUKAN_FOOT_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKAN_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKAN_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	add.mat.y		= ZKN_ZUKAN_FOOT_MAT_Y;
	add.mat.x		= ZKN_ZUKAN_FOOT_MAT_X;
	
	// �o�^�@�A�j���[�V�����ݒ�
	p_draw->clact[ ZKN_ZUKAN_CLACT_FOOT ] = CLACT_AddSimple( &add );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ՃA�N�^�[�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootActDelete( ZKN_ZUKAN_DRAW* p_draw )
{
	if(p_draw->clact[ ZKN_ZUKAN_CLACT_FOOT ]){
		CLACT_Delete( p_draw->clact[ ZKN_ZUKAN_CLACT_FOOT ] );
	}
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
static void ZknZukanPokeListDrawOn( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap )
{
	// ���X�g�쐬
	ZKN_UTIL_PokeListPokeNameMakeGlb( 
			p_drawglb->p_drawglb, cp_glb->p_glb, heap,
			ZKN_GLBDATA_PokeListTblNoGet( cp_glb->p_glb ), 
			ZKN_ZUKAN_POKELIST_MAT_X, ZKN_ZUKAN_POKELIST_MAT_Y );

	ZKN_GlbPokeNameTblBGPriSet( p_drawglb->p_drawglb, ZKN_ZUKAN_OAM_BG_PRI );
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
static void ZknZukanPokeListDrawOff( ZKN_ZUKAN_DRAWGLB* p_drawglb )
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
static void ZknZukanPokeGraDrawOn( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// �|�P�����ݒ�
	ZKN_UTIL_PokemonGraphicSet( p_drawglb->p_drawglb, cp_glb->p_glb, monsno,
			PARA_FRONT, ZKN_ZUKAN_POKEGRA_MAT_X, ZKN_ZUKAN_POKEGRA_MAT_Y );
	
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
static void ZknZukanPokeGraDrawOff( ZKN_ZUKAN_DRAWGLB* p_drawglb )
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
static void ZknZukanClactResLoad( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap )
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
static void ZknZukanClactResDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
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
 *	@brief	���ՈȊO�̃A�N�^�[�o�^
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanClactAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int mons_no			= ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	int type1, type2;
	int form = ZKN_GLBDATA_SaveData_FirstFormGet( cp_glb->p_glb, mons_no );


	type1 = PokeFormNoPersonalParaGet( mons_no, form, ID_PER_type1 );
	type2 = PokeFormNoPersonalParaGet( mons_no, form, ID_PER_type2 );

	// type���j�g���L�����N�^�̃A�j���V�[�P���X�i���o�[�ɕύX
	type1 =	ZknZukanClactTypeNoChg( type1 );
	type2 =	ZknZukanClactTypeNoChg( type2 );

	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_main2_lzh_NCGR + ZKN_ZUKAN_FOOT_RES_ID,
			NARC_zukan_zkn_data_oam2_NCLR + ZKN_ZUKAN_FOOT_RES_ID, 
			NARC_zukan_zkn_data_oam_main2_lzh_NCER + ZKN_ZUKAN_FOOT_RES_ID,
			NARC_zukan_zkn_data_oam_main2_lzh_NANR + ZKN_ZUKAN_FOOT_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKAN_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKAN_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// �^�C�v1
	add.mat.x = ZKN_ZUKAN_POKETYPE1_MAT_X;
	add.mat.y = ZKN_ZUKAN_POKETYPE_MAT_Y;
	p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE1 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE1 ], ZKN_ZUKAN_POKETYPE_NORMAL + type1 );

	// �^�C�v2
	if( type1 != type2 ){
		add.mat.x = ZKN_ZUKAN_POKETYPE2_MAT_X;
		add.mat.y = ZKN_ZUKAN_POKETYPE_MAT_Y;
		p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE2 ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE2 ], ZKN_ZUKAN_POKETYPE_NORMAL + type2 );
	}else{
		p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE2 ] = NULL;
	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����^�C�v���j�g���L�����N�^�̃A�j���V�[�P���X�ɂ��킹��
 *
 *	@param	type	�^�C�v
 *
 *	@return	�^�C�v
 */
//-----------------------------------------------------------------------------
int ZknZukanClactTypeNoChg( int type )
{
	int num;
	
	switch( type ){
	case NORMAL_TYPE:		
		num = 0x0;
		break;
		
	case BATTLE_TYPE:		
		num = 0x6; 
		break;
		
	case HIKOU_TYPE:		
		num = 0xe;
		break;
		
	case POISON_TYPE:		
		num = 0xa;
		break;
		
	case JIMEN_TYPE:		
		num = 0x8;
		break;
		
	case IWA_TYPE:		
		num = 0x5;
		break;
		
	case MUSHI_TYPE:		
		num = 0xb;
		break;
		
	case GHOST_TYPE:		
	case HATE_TYPE:		
		num = 0x7;
		break;
		
	case METAL_TYPE:		
		num = 0x9;
		break;
		
	case FIRE_TYPE:		
		num = 0x1;
		break;
		
	case WATER_TYPE:		
		num = 0x3;
		break;
		
	case KUSA_TYPE:		
		num = 0x2;
		break;
		
	case ELECTRIC_TYPE:	
		num = 0x4;
		break;
		
	case SP_TYPE:			
		num = 0xf;
		break;
		
	case KOORI_TYPE:		
		num = 0xd;
		break;
		
	case DRAGON_TYPE:				
		num = 0x10;
		break;
		
	case AKU_TYPE:
		num = 0x0c;
		break;
	}

	return num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���ՈȊO�̃A�N�^�[��j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanClactDelete( ZKN_ZUKAN_DRAW* p_draw )
{
	if( p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE1 ] ){
		CLACT_Delete( p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE1 ] );
	}
	if(p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE2 ]){
		CLACT_Delete( p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE2 ] );
	}
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
static void ZknZukanPokeTypeTextAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap )
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
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKAN_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKAN_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// �e�[�u������
	add.mat.x = ZKN_ZUKAN_POKETYPE_TEXT_MAT_X;
	add.mat.y = ZKN_ZUKAN_POKETYPE_TEXT_MAT_Y;
	p_draw->poketype_text_tbl = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->poketype_text_tbl, ZKN_ZUKAN_POKETYPE_TEXT_TBL_SEQ );

	// �߂܂��Ă��邩�`�F�b�N
	if( ZKN_GLBDATA_PokeMonsTypeGet( cp_glb->p_glb ) != ZKN_POKELIST_TYPE_GET ){
		mons_no = 0;	// �_�~�[�f�[�^�\��
	}

	// ������쐬
	p_bmp = ZknZukanPokeTypeTextBmpMake( p_drawglb->p_drawglb->fontoam_sys, mons_no, heap );

	// �p���b�gResource�擾
	pltt_res = ZKN_GlbPokeNameTblResObjGet( p_drawglb->p_drawglb, CLACT_U_PLTT_RES );
	
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_drawglb->p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( pltt_res, NULL );
	fontoam_init.parent		 = p_draw->poketype_text_tbl;
	fontoam_init.x			 = ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_X;
	fontoam_init.y			 = ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_ZUKAN_OAM_BG_PRI;
	fontoam_init.soft_pri	 = ZKN_ZUKAN_OAM_SOFT_PRI - 1;
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
GF_BGL_BMPWIN* ZknZukanPokeTypeTextBmpMake( ZKN_FONTOAM_SYS_PTR p_fontoamsys, int mons_no, int heap )
{
	GF_BGL_BMPWIN* p_bmp;
	STRBUF* str;

	p_bmp = ZKN_FONTOAM_GetBmp( p_fontoamsys, ZKN_ZUKAN_POKETYPE_TEXT_BMP_SCX, ZKN_ZUKAN_POKETYPE_TEXT_BMP_SCY );

	// �`�|�P����������擾
	str = ZKN_WT_GetPokeType( mons_no, PM_LANG, heap );
	ZKN_FONTOAM_PrintBmpStrBuf( p_fontoamsys,
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
static void ZknZukanPokeTypeTextDelete( ZKN_ZUKAN_DRAW* p_draw )
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
static void ZknZukanDefaultFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out )
{
	
	// ������OAM�ݒ�
	ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_XLU );
	ZknZukanOamFadeInit( p_draw );

	// �u���C�g�l�X���g���ėǂ�������
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKAN_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKAN_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );

		}
	}

	// �|�P�O���p���b�g�t�F�[�h�ݒ�
	ZknZukanSpritePokeGraPalFade( p_drawglb );
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
static BOOL ZknZukanDefaultFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out )
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
			ZknZukanOamFadeDelete( p_draw );
			ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
		}else{
			// �|�P�����O���t�B�b�N�\��OFF
			ZknZukanPokeGraDrawOff( p_drawglb );

			// �O���[�o���̈�ɂ���|�P�������X�g�\��OFF
			ZknZukanPokeListDrawOff( p_drawglb );
		}
	}else{
		// �|�P�O���p���b�g�t�F�[�h�ݒ�
		ZknZukanSpritePokeGraPalFade( p_drawglb );
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
static void ZknZukanChPokeListFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknZukanOamFadeInit( p_draw );


	// �t�F�[�h�A�E�g�̎������̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N�t�F�[�h
		ZknZukanPokeGraFadeInit( p_draw, cp_glb->poke_gra_move_x, cp_glb->poke_gra_move_y, ZKN_FADE_SYNC_LONG_COMMON );

		// �|�P�����O���t�B�b�N�t�F�[�h
		ZknZukanPokeListFadeInit( p_draw );
	}

	// �u���C�g�l�X���g���ėǂ�������
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_LONG_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKAN_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_LONG_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKAN_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );

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
static BOOL ZknZukanChPokeListFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check[ 3 ];
	int i;
	

	// �t�F�[�h�A�E�g�̂Ƃ��݂̂̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N
		check[0] = ZknZukanPokeGraFadeMain( p_draw, p_drawglb );

		// �|�P�������X�g
		check[1] = ZknZukanPokeListFadeMain( p_draw, p_drawglb );
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
			ZknZukanOamFadeDelete( p_draw );
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
static void ZknZukanChOtherFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknZukanOamFadeInit( p_draw );

	// �|�P�������X�g�e�[�u����������
	ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_XLU );


	// �t�F�[�h�A�E�g�̎������̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N�t�F�[�h
		ZknZukanPokeGraFadeInit( p_draw, cp_glb->poke_gra_move_x, cp_glb->poke_gra_move_y, ZKN_FADE_SYNC_COMMON );
	}

	// �u���C�g�l�X���g���ėǂ�������
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKAN_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKAN_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );

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
static BOOL ZknZukanChOtherFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb , BOOL fadein_out )
{
	BOOL check[ 2 ];
	int i;
	

	// �t�F�[�h�A�E�g�̂Ƃ��݂̂̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N
		check[0] = ZknZukanPokeGraFadeMain( p_draw, p_drawglb );

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
			ZknZukanOamFadeDelete( p_draw );

			// �|�P�e�[�u��
			ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
		}else{
			// �O���[�o���̈�ɂ���|�P�������X�g�\��OFF
			ZknZukanPokeListDrawOff( p_drawglb );
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
static void ZknZukanOamFadeInit( ZKN_ZUKAN_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKAN_CLACT_NUM; i++ ){
		if( p_draw->clact[ i ] ){
			CLACT_ObjModeSet( p_draw->clact[ i ], GX_OAM_MODE_XLU );
		}
	}

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
static void ZknZukanOamFadeDelete( ZKN_ZUKAN_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKAN_CLACT_NUM; i++ ){
		if( p_draw->clact[ i ] ){
			CLACT_ObjModeSet( p_draw->clact[ i ], GX_OAM_MODE_NORMAL );
		}
	}

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
static void ZknZukanSpritePokeGraPalFade( ZKN_ZUKAN_DRAWGLB* p_drawglb )
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
static void ZknZukanPokeGraFadeInit( ZKN_ZUKAN_DRAW* p_draw, int move_x, int move_y, int sync_num )
{
	ZKN_UTIL_MoveReq( &p_draw->pokegra_move, ZKN_ZUKAN_POKEGRA_MAT_X, move_x, ZKN_ZUKAN_POKEGRA_MAT_Y, move_y, sync_num);
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
static BOOL ZknZukanPokeGraFadeMain( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
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
static void ZknZukanPokeListFadeInit( ZKN_ZUKAN_DRAW* p_draw )
{
	ZKN_UTIL_MoveReq( &p_draw->pokelist_move, ZKN_ZUKAN_POKELIST_MAT_IX, ZKN_POKELIST_TBL_MAT_X, ZKN_ZUKAN_POKELIST_MAT_IY, ZKN_POKELIST_TBL_MAT_Y, ZKN_FADE_SYNC_LONG_COMMON);
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
static BOOL ZknZukanPokeListFadeMain( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
{
	BOOL check;
	
	check = ZKN_UTIL_MoveMain( &p_draw->pokelist_move );

	// ���W�ݒ�
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet( p_drawglb->p_drawglb, p_draw->pokelist_move.x, p_draw->pokelist_move.y );

	return check;
}
