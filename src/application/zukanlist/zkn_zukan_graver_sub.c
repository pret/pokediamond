//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_graver_sub.c
 *	@brief		���������
 *	@author		tomoya takahashi
 *	@data		2006.03.07
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/gflib/vram_transfer_manager.h"
#include "include/system/brightness.h"
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"
#include "include/application/zukanlist/zkn_cursor.h"
#include "include/application/zukanlist/zkn_zukan_graver.h"

#define	__ZKN_ZUKAN_GRAVER_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan_graver_sub.h"

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
#define ZKN_GRAPHIC_SUB_EVENT_NUM ( 0 )	// �C�x���g��

#define ZKN_GRAPHIC_SUB_OAM_BG_PTR	( 2 )

enum{
	ZKN_GRAPHICSUB_SEQINIT_ALLOC,
	ZKN_GRAPHICSUB_SEQINIT_LOAD,
	ZKN_GRAPHICSUB_SEQINIT_FADEIN,
	ZKN_GRAPHICSUB_SEQINIT_END,
};
enum{
	ZKN_GRAPHICSUB_SEQDELETE_FADEOUT_INIT,
	ZKN_GRAPHICSUB_SEQDELETE_FADEOUT,
	ZKN_GRAPHICSUB_SEQDELETE_RELEASE,
	ZKN_GRAPHICSUB_SEQDELETE_FREE,
	ZKN_GRAPHICSUB_SEQDELETE_END,
};





//-------------------------------------
//	�{�^�����
//=====================================
enum{
	ZKN_GRAPHICSUB_BUTTON_GRAPHIC,
	ZKN_GRAPHICSUB_BUTTON_NUM,
};
#define ZKN_GRAPHICSUB_BUTTON_DEF_Y		( 144 )
#define ZKN_GRAPHICSUB_BUTTON_GRAPHIC_X	( 128 )
#define ZKN_GRAPHICSUB_BUTTON_SIZE_X	( 240 )
#define ZKN_GRAPHICSUB_BUTTON_SIZE_Y	( 80 )
#define ZKN_GRAPHICSUB_BUTTON_ANM_SEQ	( 2 )
#define ZKN_GRAPHICSUB_BUTTON_GRAPHICBG_PLTT_NO	(4)

#define ZKN_GRAPHICSUB_CURSOR_SIZE_X	( 228 )
#define ZKN_GRAPHICSUB_CURSOR_SIZE_Y	( 64 )

// FONTOAM
#define ZKN_GRAPHICSUB_BUTTONFONT_BMP_SIZE_CX ( 16 )
#define ZKN_GRAPHICSUB_BUTTONFONT_BMP_SIZE_CY ( 2 )
#define ZKN_GRAPHICSUB_BUTTON_PAL_OFS			( 4 )
#define ZKN_GRAPHICSUB_BUTTON_PAL_OFS_ON		( 1 )
#define ZKN_GRAPHICSUB_BUTTON_FONT_OFS_X		( -60 )
#define ZKN_GRAPHICSUB_BUTTON_FONT_OFS_Y		( -8 )

#define ZKN_GRAPHICSUB_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	������������׃T�u��ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	int* p_event_key;

	ZKN_GLB_DATA* p_glb;
	
	// �}�ӃR�����T�u�A�v���f�[�^
	const ZKN_APL_DATA* cp_zukan_common_apl;

	// �}�ӂ�������ʃ��C��
	ZKN_APL_DATA* p_zukan_sugata_apl;
} ZKN_GRAPHIC_SUB_GLB;

//-------------------------------------
//	�傫������׃T�u��ʉ�ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_GRAPHIC_SUB_DRAWGLB;

//-------------------------------------
//	�{�^���R�[���o�b�N�ւ̃��[�N
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_GRAPHIC_BUTTON_CALLBACK;

//-------------------------------------
//	������������׃T�u��ʁ@�������[�N
//=====================================
typedef struct {
	// �{�^���}�l�[�W��
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// �{�^���f�[�^
	ZKN_GRAPHIC_BUTTON_CALLBACK callcack;

	// �A�v���f�[�^
	int button_event[ ZKN_GRAPHICSUB_BUTTON_NUM ];	// �{�^���C�x���g�f�[�^

	// ���C����ʂ�ύX���郊�N�G�X�g�t���O
	BOOL change_apl_req;
} ZKN_GRAPHIC_SUB_WORK;

//-------------------------------------
//	������������׃T�u��ʉ�ʁ@�������[�N
//=====================================
typedef struct {
	// �{�^���O���t�B�b�N
	CLACT_WORK_PTR button[ ZKN_GRAPHICSUB_BUTTON_NUM ];
	ZKN_FONTOAM_DATA* p_button_font[ ZKN_GRAPHICSUB_BUTTON_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// �J�[�\��
	CLACT_WORK_PTR cursor[ ZKN_CURROS_MAT_RECT_NUM ];

	int	bgpltt_no[ ZKN_GRAPHICSUB_BUTTON_NUM ];

	void* pltt_buff[ ZKN_GRAPHICSUB_BUTTON_NUM ];
} ZKN_GRAPHIC_SUB_DRAW;


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
static ZKN_GRAPHIC_SUB_GLB* MakeGraphicSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_GRAPHIC_SUB_DRAWGLB* MakeGraphicSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeGraphicSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteGraphicSubGlb( ZKN_GRAPHIC_SUB_GLB* p_glb );
static void DeleteGraphicSubDrawGlb( ZKN_GRAPHIC_SUB_DRAWGLB* p_glb );
static void DeleteGraphicSubEvent( ZKN_EVENT_DATA* p_event );


static int GraphicSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknGraphicSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknGraphicSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknGraphicSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknGraphicSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknGraphicSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknGraphicSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// �t�F�[�h����
static void ZknGraphicSubOamFadeInit( ZKN_GRAPHIC_SUB_DRAW* p_draw );
static void ZknGraphicSubOamFadeDelete( ZKN_GRAPHIC_SUB_DRAW* p_draw );
static void ZknGraphicSubFadeInit( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknGraphicSubFadeMain( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb, BOOL fadein_out );

// �{�^������
static void ZknGraphicSubButtonMake( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb, int heap );
static void ZknGraphicSubButtonEventBuffInit( ZKN_GRAPHIC_SUB_WORK* p_work );
static void ZknGraphicSubButtonMove( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb );
static void ZknGraphicSubButtonDelete( ZKN_GRAPHIC_SUB_WORK* p_work );
static void ZknGraphicSubButtonCallBack( u32 button_no, u32 event, void* p_work );


// �{�^���`�搧��
static void ZknGraphicSubButtonControl( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff );
static void ZknGraphicSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt );
static void ZknGraphicSubButtonDrawMain( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, ZKN_GRAPHIC_SUB_DRAW* p_draw, const ZKN_GRAPHIC_SUB_WORK* cp_work, int heap );


// ���̃O���t�B�b�N�ɕύX����
static void ZknGraphicSubNextGraphicChange( const ZKN_GRAPHIC_SUB_GLB* cp_glb );

// �J�[�\������
static void ZknGraphicSubCursorMove( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb );
static void ZknGraphicSubCursorDraw( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb );
static void ZknGraphicSubCursorMatSet( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int x, int y, int size_x, int size_y );



// �ǂݍ���
static void ZknGraphicSubLoadResource( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubReleaseResource( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubSetUpBg( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubLoadOamData( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubReleaseOamData( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb );
static void ZknGraphicSubAddClact( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubDeleteClact( ZKN_GRAPHIC_SUB_DRAW* p_draw );
static void ZknGraphicSubAddFontOam( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubDeleteFontOam( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	������������׃T�u��ʁ@�A�v���쐬
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
void ZKN_GraphicSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_GRAPHIC_SUB_GLB*	p_glb;
	ZKN_GRAPHIC_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeGraphicSubGlb( heap, zkn_sys );
	p_drawglb = MakeGraphicSubDrawGlb( heap, zkn_sys );
	p_event = MakeGraphicSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= GraphicSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknGraphicSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknGraphicSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknGraphicSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknGraphicSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknGraphicSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknGraphicSubProcDrawFuncDelete;
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
void ZKN_GraphicSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteGraphicSubGlb( p_data->p_glb_data ); 
	DeleteGraphicSubDrawGlb( p_data->p_glb_draw ); 
	DeleteGraphicSubEvent( p_data->p_event_data );
}


//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	������������׃T�u��ʁ@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_GRAPHIC_SUB_GLB* MakeGraphicSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_GRAPHIC_SUB_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_GRAPHIC_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_GRAPHIC_SUB_GLB) );

	// �ϐ�������
	// �C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );		

	// �}�ӃR�����A�v���O���[�o���f�[�^
	p_glb->cp_zukan_common_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );

	// �}�ӎp��ʃ��C���@�A�v���f�[�^
	p_glb->p_zukan_sugata_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_GRA );

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	������������׃T�u��ʁ@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_GRAPHIC_SUB_DRAWGLB* MakeGraphicSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_GRAPHIC_SUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_GRAPHIC_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_GRAPHIC_SUB_DRAWGLB) );


	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	������������׃T�u��ʁ@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeGraphicSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
/*	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = GraphicSubEventDataNumGet();

	// �C�x���g�f�[�^�e�[�u���쐬
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeGraphicMain( heap, &p_event_tbl[0], zkn_sys, ZKN_GRAPHIC_SUB_EVENT_CHANGE_GRAPHIC );
	ZKN_EVENT_MakeChangeGraphicWeightMain( heap, &p_event_tbl[1], zkn_sys, ZKN_GRAPHIC_SUB_EVENT_CHANGE_WEIGHT );

	return p_event_tbl;//*/
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	������������׃T�u��ʁ@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteGraphicSubGlb( ZKN_GRAPHIC_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	������������׃T�u��ʁ@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteGraphicSubDrawGlb( ZKN_GRAPHIC_SUB_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	������������׃T�u��ʁ@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteGraphicSubEvent( ZKN_EVENT_DATA* p_event )
{
/*	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );
	ZKN_EVENT_DeleteData( &p_event[1] );

	sys_FreeMemoryEz( p_event );//*/
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	������������׃T�u��ʃA�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	������������׃T�u��ʃA�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int GraphicSubEventDataNumGet( void )
{
	return ZKN_GRAPHIC_SUB_EVENT_NUM;
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
static int ZknGraphicSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_GRAPHIC_SUB_GLB* p_glb = p_glbdata;
	ZKN_GRAPHIC_SUB_WORK* p_work = p_dodata->p_work;
	int i;

	// ���[�N�̍쐬
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_GRAPHIC_SUB_WORK) );
	memset( p_work, 0, sizeof(ZKN_GRAPHIC_SUB_WORK) );

	// �{�^���C�x���g�f�[�^
	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;	// �{�^���C�x���g�f�[�^
	}

	// �{�^�����쐬
	ZknGraphicSubButtonMake( p_work, p_glb, p_dodata->heap );

	// �{�^���̏�Ԃ��P��ݒ�
	// �{�^������
	ZknGraphicSubButtonMove( p_work, p_glb );


	p_dodata->p_work = p_work;
	
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
static int ZknGraphicSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{

	ZKN_GRAPHIC_SUB_GLB* p_glb = p_glbdata;
	ZKN_GRAPHIC_SUB_WORK* p_work = p_dodata->p_work;
	
	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}


	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// ����`�F�b�N
	if( ZKN_ZukanCommonSubMoveFlagGet( p_glb->cp_zukan_common_apl ) ){

		// �{�^���C�x���g�o�b�t�@������
		ZknGraphicSubButtonEventBuffInit( p_work );
		
		// �J�[�\������
		// �J�[�\������L���ŁA�T�u�A�v���ɃJ�[�\�����삪������Ă���Ƃ��̂�
		if( ZKN_ZukanCommonSubCursorFlagGet( p_glb->cp_zukan_common_apl ) &&
			ZKN_GLBDATA_TouchCursorFlagGet( p_glb->p_glb ) ){

			ZknGraphicSubCursorMove( p_work, p_glb );
		}
		
		// �{�^������
		ZknGraphicSubButtonMove( p_work, p_glb );

		// ���̃A�v���ւ̃t���O����������ڍs����
		if( p_work->change_apl_req ){
			ZknGraphicSubNextGraphicChange( p_glb );
			p_work->change_apl_req = FALSE;
		}
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
static int ZknGraphicSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_GRAPHIC_SUB_GLB* p_glb = p_glbdata;
	ZKN_GRAPHIC_SUB_WORK* p_work = p_dodata->p_work;

	// �{�^���j��
	ZknGraphicSubButtonDelete( p_work );

	// ���[�N�j��
	sys_FreeMemoryEz( p_work );

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
static int ZknGraphicSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_GRAPHIC_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_GRAPHIC_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_GRAPHIC_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_GRAPHIC_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_GRAPHICSUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_GRAPHIC_SUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_GRAPHIC_SUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_GRAPHICSUB_SEQINIT_LOAD:
		// Resource�ǂݍ���
		ZknGraphicSubLoadResource( p_drawwork, p_drawglb, p_drawdata->heap );

		// �t�F�[�h����
		ZknGraphicSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_GRAPHICSUB_SEQINIT_FADEIN:
		
		if( ZknGraphicSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_GRAPHICSUB_SEQINIT_END:
		// �J�[�\���A�j���J�n
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, FALSE );
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
static int ZknGraphicSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_GRAPHIC_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_GRAPHIC_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_GRAPHIC_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_GRAPHIC_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	// ����`�F�b�N
	if( ZKN_ZukanCommonSubMoveFlagGet( cp_dataglb->cp_zukan_common_apl ) ){
		
		// �{�^���`�惁�C��
		ZknGraphicSubButtonDrawMain( p_drawglb, p_drawwork, cp_datawork, p_drawdata->heap );

		// �J�[�\���`�惁�C��
		ZknGraphicSubCursorDraw( p_drawglb, cp_dataglb );
	}


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
static int ZknGraphicSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_GRAPHIC_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_GRAPHIC_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_GRAPHIC_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_GRAPHIC_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_GRAPHICSUB_SEQDELETE_FADEOUT_INIT:
		// �J�[�\���A�j����~
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, TRUE );

		// �t�F�[�h����
		ZknGraphicSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_GRAPHICSUB_SEQDELETE_FADEOUT:
		if( ZknGraphicSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_GRAPHICSUB_SEQDELETE_RELEASE:
		// Resource�ǂݍ���
		ZknGraphicSubReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_GRAPHICSUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_GRAPHICSUB_SEQDELETE_END:
		return ZKN_PROC_TRUE;
		
	default:
		break;
	}
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�t�F�[�h����	������
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubOamFadeInit( ZKN_GRAPHIC_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODE�𔼓����ɂ���
	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->button[ i ], GX_OAM_MODE_XLU );
		FONTOAM_ObjModeSet( p_draw->p_button_font[ i ]->p_fontoam, GX_OAM_MODE_XLU );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�t�F�[�h�����@�㏈��
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubOamFadeDelete( ZKN_GRAPHIC_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODE���m�[�}���ɂ���
	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->button[ i ], GX_OAM_MODE_NORMAL );
		FONTOAM_ObjModeSet( p_draw->p_button_font[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u��ʃt�F�[�h����
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb		�O���[�o��
 *	@param	fadein_out	�t�F�[�h�C���@TRUE�@�A�E�g FALSE	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubFadeInit( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknGraphicSubOamFadeInit( p_draw );

	// �u���C�g�l�X�������s���Ă悢��
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_GRAPHICSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_GRAPHICSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�����@���C��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb		�O���[�o��
 *	@param	fadein_out	�t�F�[�h�C���@TRUE�@�A�E�g�@FALSE
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknGraphicSubFadeMain( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;

	// �u���C�g�l�X���悤���łĂ邩�`�F�b�N
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade_sub );
	}else{
//		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade_sub );
		check = IsFinishedBrightnessChg( MASK_SUB_DISPLAY );
	}

	// �I�������I������
	if( check ){
		if( fadein_out ){
			// ������OAM�j��
			ZknGraphicSubOamFadeDelete( p_draw );
		}

		return TRUE;
	}

	return FALSE;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���쐬�֐�
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o��
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonMake( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb, int heap )
{
	// �e�[�u���쐬
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_GRAPHICSUB_BUTTON_NUM );

	// �e�[�u���f�[�^�ݒ�
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ],
			ZKN_GRAPHICSUB_BUTTON_DEF_Y - (ZKN_GRAPHICSUB_BUTTON_SIZE_Y/2),
			ZKN_GRAPHICSUB_BUTTON_DEF_Y + (ZKN_GRAPHICSUB_BUTTON_SIZE_Y/2),
			ZKN_GRAPHICSUB_BUTTON_GRAPHIC_X - (ZKN_GRAPHICSUB_BUTTON_SIZE_X/2),
			ZKN_GRAPHICSUB_BUTTON_GRAPHIC_X + (ZKN_GRAPHICSUB_BUTTON_SIZE_X/2) );

	p_work->callcack.p_glb = p_glb;
	p_work->callcack.p_work = p_work;

	// �{�^���}�l�[�W���쐬
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_GRAPHICSUB_BUTTON_NUM,
			ZknGraphicSubButtonCallBack,
			&p_work->callcack,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���C�x���g�o�b�t�@������
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonEventBuffInit( ZKN_GRAPHIC_SUB_WORK* p_work )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = BMN_EVENT_SLIDEOUT;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�{�^�����쏈��
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonMove( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb )
{
	BMN_Main( p_work->p_button_man );

	if( p_work->change_apl_req ){
		p_work->button_event[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ] = BMN_EVENT_HOLD;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonDelete( ZKN_GRAPHIC_SUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );

	// �e�[�u�����[�N�j��
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���R�[���o�b�N�֐�
 *
 *	@param	button_no	�{�^���i���o�[
 *	@param	event		�{�^���C�x���g�^�C�v
 *	@param	p_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_GRAPHIC_BUTTON_CALLBACK* p_work_data = p_work;
	ZKN_GRAPHIC_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_GRAPHIC_SUB_WORK* p_subwork = p_work_data->p_work;

	// �{�^���C�x���g�i�[
	p_subwork->button_event[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_TOUCH:
		switch( button_no ){
		case ZKN_GRAPHICSUB_BUTTON_GRAPHIC:
			// ���̊G��
			p_subwork->change_apl_req = TRUE;
			break;
			
		default:
			break;
		}
		break;

	case BMN_EVENT_HOLD:		///< ��������
		switch( button_no ){
		case ZKN_GRAPHICSUB_BUTTON_GRAPHIC:
			// ���̊G��
			p_subwork->change_apl_req = TRUE;
			break;
			
		default:
			break;
		}
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N����������
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubLoadResource( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	// �w�i
	ZknGraphicSubSetUpBg( p_drawglb, heap );

	// OAM
	ZknGraphicSubLoadOamData( p_draw, p_drawglb, heap );

	// �Z���A�N�^�[�o�^
	ZknGraphicSubAddClact( p_draw, p_drawglb, heap );

	// FONTOAM�o�^
	ZknGraphicSubAddFontOam( p_draw, p_drawglb, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�j������
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubReleaseResource( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	int i;
	
	// �p���b�g�����Z�b�g
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_4_NCLR, PALTYPE_SUB_BG, ZKN_GRAPHICSUB_BUTTON_GRAPHICBG_PLTT_NO*32, 32, heap );
	
	// �Z���A�N�^�[�j��
	ZknGraphicSubDeleteClact( p_draw );

	// FONTOAM�j��
	ZknGraphicSubDeleteFontOam( p_draw, p_drawglb );

	// OAM
	ZknGraphicSubReleaseOamData( p_draw, p_drawglb );

	// �p���b�g�o�b�t�@�j��
	for( i=0;i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		if( p_draw->pltt_buff[i] ){
			sys_FreeMemoryEz( p_draw->pltt_buff[i] );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�ʃZ�b�g�A�b�v
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubSetUpBg( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub0_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM���\�[�X�ǂݍ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubLoadOamData( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw_glb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_GRAPHIC_SUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_GRAPHIC_SUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_GRAPHIC_SUB_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM���\�[�X�j��
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubReleaseOamData( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;


	CLACT_U_CharManagerDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�o�^
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubAddClact( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_GRAPHIC_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_GRAPHIC_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_GRAPHIC_SUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_GRAPHIC_SUB_OAM_BG_PTR,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 31;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	
	// �ʂ̎p
	add.mat.x = ZKN_GRAPHICSUB_BUTTON_GRAPHIC_X << FX32_SHIFT;
	add.mat.y = ZKN_GRAPHICSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ], ZKN_GRAPHICSUB_BUTTON_ANM_SEQ );	

}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubDeleteClact( ZKN_GRAPHIC_SUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		CLACT_Delete( p_draw->button[ i ] );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�쐬
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubAddFontOam( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// �p���b�g�A�h���X

	// ���CLACT��o�^���Ă���K�v������
	GF_ASSERT( p_draw->button[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ] );

	// �p���b�g�̃��\�[�X�f�[�^�擾
	// �p���b�g�v���N�V�擾�p
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS );

	// �������f�[�^�̋��ʕ������쐬
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.x			 = ZKN_GRAPHICSUB_BUTTON_FONT_OFS_X;
	fontoam_init.y			 = ZKN_GRAPHICSUB_BUTTON_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_GRAPHIC_SUB_OAM_BG_PTR;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_GRAPHICSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_GRAPHICSUB_BUTTONFONT_BMP_SIZE_CY );

	// ������
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SHAPE_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->button[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ];
	p_draw->p_button_font[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_button_font[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ]->p_fontoam, pltt_ofs + ZKN_GRAPHICSUB_BUTTON_PAL_OFS );

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );

}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�j��
 *	
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubDeleteFontOam( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb )
{
	int i;

	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		ZKN_FONTOAM_Delete( p_draw->p_button_font[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���`�搧��
 *
 *	@param	button		�{�^���A�N�^�[
 *	@param	event		�C�x���g
 *	@param	p_fontoam	�t�H���gOAM
 *	@param	def_y		Y����
 *	@param	bgpltt_no	BG�p���b�gNO
 *	@param	heap		�q�[�v
 *	@param	off_fontoam_pl	�t�H���gOAM�I�t��
 *	@param	on_fontoam_pl	�t�H���gOAM�I����
 *	@param	�p���b�g�o�b�t�@	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonControl( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff )
{
	int now_frm;
	NNSG2dPaletteData* p_plt;
	BOOL check;
	BOOL chenge = FALSE;
	int arc_data_idx;

	
	// �{�^������
	ZKN_UTIL_ButtonMove( button,
			event );

	ZknGraphicSubFontButtonMove( 
			button,
			p_fontoam,
			def_y,
			off_fontoam_pl,
			on_fontoam_pl );

	// ���݃t���[���擾
	now_frm = CLACT_AnmFrameGet( button );


	// �J���[�p���b�g�ݒ�
	switch( now_frm ){
	case ZKN_UTIL_BUTTON_FRAME_NONE:
	case ZKN_UTIL_BUTTON_FRAME_PUSH1:
		if( *p_nowbgpltt_no != 0 ){
			// off_pltt
			chenge = TRUE;
			arc_data_idx = NARC_zukan_zkn_data_4_NCLR;
			*p_nowbgpltt_no = 0;
		}
		break;
	case ZKN_UTIL_BUTTON_FRAME_PUSH2:
		if( *p_nowbgpltt_no != 1 ){
			// on_pltt
			chenge = TRUE;
			arc_data_idx = NARC_zukan_zkn_data_5_NCLR;
			*p_nowbgpltt_no = 1;
		}
		break;

	case ZKN_UTIL_BUTTON_FRAME_SELECT:
		if( *p_nowbgpltt_no != 2 ){
			// on_pltt
			chenge = TRUE;
			arc_data_idx = NARC_zukan_zkn_data_3_NCLR;
			*p_nowbgpltt_no = 2;
		}
		break;
	}
	if( chenge ){
		// ���܂ł̂�j��
		if( *buff ){
			sys_FreeMemoryEz( *buff );
		}
		*buff = ZKN_GLBDATA_PalDataGet( p_drawglb->p_drawglb, arc_data_idx, &p_plt, heap );
		// TransferManager�ɓo�^
		check = AddVramTransferManager(
				NNS_GFD_DST_2D_BG_PLTT_SUB,
				bgpltt_no*32,
				p_plt->pRawData,
				32);
		// �]���^�X�N�������s
		GF_ASSERT( check );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���t�H���g����
 *
 *	@param	act				�A�N�^�[
 *	@param	p_fontoam		�t�H���gOAM
 *	@param	def_y			�f�t�H���gY�ʒu
 *	@param	off_pltt		�{�^��OFF���̃J���[�p���b�g
 *	@param	on_pltt			�{�^��ON���̃J���[�p���b�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt )
{
	int now_frm;
	
	ZKN_UTIL_ButtonFontMove( 
			act,
			p_fontoam,
			def_y );

	// ���݃t���[���擾
	now_frm = CLACT_AnmFrameGet( act );

	// �J���[�p���b�g�ݒ�
	if( now_frm < ZKN_UTIL_BUTTON_FRAME_PUSH2 ){
		// off_pltt
		FONTOAM_SetPaletteOffsetAddTransPlttNo( p_fontoam->p_fontoam, off_pltt );
	}else{
		// on_pltt
		FONTOAM_SetPaletteOffsetAddTransPlttNo( p_fontoam->p_fontoam, on_pltt );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���`�揈�����C��
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	cp_work	���[�N
 *	@parma	heap	�q�[�v
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonDrawMain( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, ZKN_GRAPHIC_SUB_DRAW* p_draw, const ZKN_GRAPHIC_SUB_WORK* cp_work, int heap )
{
	int i;	// ���[�v�p
	int bgpltt_no;

	// �{�^���\������
	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){

		bgpltt_no = ZKN_GRAPHICSUB_BUTTON_GRAPHICBG_PLTT_NO;
		
		ZknGraphicSubButtonControl( p_drawglb,
				p_draw->button[i],
				p_draw->p_button_font[i], cp_work->button_event[i],
				ZKN_GRAPHICSUB_BUTTON_FONT_OFS_Y, bgpltt_no,
				&p_draw->bgpltt_no[i], heap,
				ZKN_GRAPHICSUB_BUTTON_PAL_OFS, 
				ZKN_GRAPHICSUB_BUTTON_PAL_OFS_ON,
				&p_draw->pltt_buff[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�傫����׃J�[�\������
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubCursorMove( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb )
{
	// A�{�^���ŃA�v���P�[�V�����𕪊�
	if( sys.cont & PAD_BUTTON_A ){
		// ���̊G��
		p_work->change_apl_req = TRUE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�傫����׃J�[�\���`�搧��
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�f�[�^�O���[�o�� 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubCursorDraw( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb )
{
	
	// �����̍��W��ݒ肵�Ă悢���`�F�b�N
	if( ZKN_ZukanCommonSubCursorFlagGet( cp_glb->cp_zukan_common_apl ) == TRUE ){

		ZknGraphicSubCursorMatSet( p_drawglb, ZKN_GRAPHICSUB_BUTTON_GRAPHIC_X, ZKN_GRAPHICSUB_BUTTON_DEF_Y, ZKN_GRAPHICSUB_CURSOR_SIZE_X, ZKN_GRAPHICSUB_CURSOR_SIZE_Y );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\�����W�ݒ�
 *
 *	@param	p_drawglb
 *	@param	x
 *	@param	y
 *	@param	size_x
 *	@param	size_y 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubCursorMatSet( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int x, int y, int size_x, int size_y )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	ZKN_UTIL_CursorSetMatrix( p_draw, x, y, size_x, size_y );
}


//----------------------------------------------------------------------------
/**
 *	@brief	���̊G�֕ύX
 *
 *	@param	cp_glb	�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubNextGraphicChange( const ZKN_GRAPHIC_SUB_GLB* cp_glb )
{
	// ���̊G��
	ZKN_ZukanGraverDrawTypeAdd( cp_glb->p_zukan_sugata_apl, 1 );
}
