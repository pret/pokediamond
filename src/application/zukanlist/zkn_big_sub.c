//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_big_sub.c
 *	@brief		������������׃T�u���
 *	@author		tomoya takahashi 
 *	@data		2006.01.21
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

#define	__ZKN_BIG_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_big_sub.h"

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
#define ZKN_BIG_SUB_EVENT_NUM ( 2 )	// �C�x���g��
#define ZKN_BIG_SUB_EVENT_CHANGE_HEIGHT	(1<<0)
#define ZKN_BIG_SUB_EVENT_CHANGE_WEIGHT	(1<<1)

#define ZKN_BIG_SUB_OAM_BG_PTR	( 2 )

enum{
	ZKN_BIGSUB_SEQINIT_ALLOC,
	ZKN_BIGSUB_SEQINIT_LOAD,
	ZKN_BIGSUB_SEQINIT_FADEIN,
	ZKN_BIGSUB_SEQINIT_END,
};
enum{
	ZKN_BIGSUB_SEQDELETE_FADEOUT_INIT,
	ZKN_BIGSUB_SEQDELETE_FADEOUT,
	ZKN_BIGSUB_SEQDELETE_RELEASE,
	ZKN_BIGSUB_SEQDELETE_FREE,
	ZKN_BIGSUB_SEQDELETE_END,
};





//-------------------------------------
//	�{�^�����
//=====================================
enum{
	ZKN_BIGSUB_BUTTON_HEIGHT,
	ZKN_BIGSUB_BUTTON_GRAM,
	ZKN_BIGSUB_BUTTON_NUM,
};
#define ZKN_BIGSUB_BUTTON_DEF_Y		( 120 )
#define ZKN_BIGSUB_BUTTON_HEIGHT_X	( 68 )
#define ZKN_BIGSUB_BUTTON_GRAM_X	( 188 )
#define ZKN_BIGSUB_BUTTON_SIZE_X	( 120 )
#define ZKN_BIGSUB_BUTTON_SIZE_Y	( 112 )
#define ZKN_BIGSUB_BUTTON_ANM_SEQ	( 1 )
#define ZKN_BIGSUB_BUTTON_HEIGHTBG_PLTT_NO	(4)
#define ZKN_BIGSUB_BUTTON_GRAMBG_PLTT_NO	(5)

#define ZKN_BIGSUB_CURSOR_SIZE_X	( 104 )
#define ZKN_BIGSUB_CURSOR_SIZE_Y	( 96 )

// FONTOAM
#define ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CX ( 12 )
#define ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CY ( 2 )
#define ZKN_BIGSUB_BUTTON_PAL_OFS			( 4 )
#define ZKN_BIGSUB_BUTTON_PAL_OFS_ON		( 1 )
#define ZKN_BIGSUB_BUTTON_FONT_OFS_X		( -40 )
#define ZKN_BIGSUB_BUTTON_FONT_OFS_Y		( -8 )

#define ZKN_BIGSUB_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

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

	int now_apply;

	ZKN_GLB_DATA* p_glb;
	
	// �}�ӃR�����T�u�A�v���f�[�^
	const ZKN_APL_DATA* cp_zukan_common_apl;
} ZKN_BIG_SUB_GLB;

//-------------------------------------
//	�傫������׃T�u��ʉ�ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_BIG_SUB_DRAWGLB;

//-------------------------------------
//	�{�^���R�[���o�b�N�ւ̃��[�N
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_BIG_BUTTON_CALLBACK;

//-------------------------------------
//	������������׃T�u��ʁ@�������[�N
//=====================================
typedef struct {
	// �{�^���}�l�[�W��
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// �{�^���f�[�^
	ZKN_BIG_BUTTON_CALLBACK callcack;

	// �A�v���f�[�^
	int button_event[ ZKN_BIGSUB_BUTTON_NUM ];	// �{�^���C�x���g�f�[�^

} ZKN_BIG_SUB_WORK;

//-------------------------------------
//	������������׃T�u��ʉ�ʁ@�������[�N
//=====================================
typedef struct {
	// �{�^���O���t�B�b�N
	CLACT_WORK_PTR button[ ZKN_BIGSUB_BUTTON_NUM ];
	ZKN_FONTOAM_DATA* p_button_font[ ZKN_BIGSUB_BUTTON_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// �J�[�\��
	CLACT_WORK_PTR cursor[ ZKN_CURROS_MAT_RECT_NUM ];

	int	bgpltt_no[ ZKN_BIGSUB_BUTTON_NUM ];

	void* pltt_buff[ ZKN_BIGSUB_BUTTON_NUM ];
} ZKN_BIG_SUB_DRAW;


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
static ZKN_BIG_SUB_GLB* MakeBigSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_BIG_SUB_DRAWGLB* MakeBigSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeBigSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteBigSubGlb( ZKN_BIG_SUB_GLB* p_glb );
static void DeleteBigSubDrawGlb( ZKN_BIG_SUB_DRAWGLB* p_glb );
static void DeleteBigSubEvent( ZKN_EVENT_DATA* p_event );


static int BigSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknBigSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// �t�F�[�h����
static void ZknBigSubOamFadeInit( ZKN_BIG_SUB_DRAW* p_draw );
static void ZknBigSubOamFadeDelete( ZKN_BIG_SUB_DRAW* p_draw );
static void ZknBigSubFadeInit( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknBigSubFadeMain( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb, BOOL fadein_out );

// �{�^������
static void ZknBigSubButtonMake( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb, int heap );
static void ZknBugSubButtonEventBuffInit( ZKN_BIG_SUB_WORK* p_work );
static void ZknBigSubButtonMove( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb );
static void ZknBigSubButtonDelete( ZKN_BIG_SUB_WORK* p_work );
static void ZknBigSubButtonCallBack( u32 button_no, u32 event, void* p_work );


// �{�^���`�搧��
static void ZknBigSubButtonControl( ZKN_BIG_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff );
static void ZknBigSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt );
static void ZknBigSubButtonDrawMain( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_WORK* cp_work, int heap );


// �J�[�\������
static void ZknBigSubCursorMove( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb );
static void ZknBigSubCursorDraw( ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb );
static void ZknBigSubCursorMatSet( ZKN_BIG_SUB_DRAWGLB* p_drawglb, int x, int y, int size_x, int size_y );



// �ǂݍ���
static void ZknBigSubLoadResource( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubReleaseResource( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubSetUpBg( ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubLoadOamData( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubReleaseOamData( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb );
static void ZknBigSubAddClact( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubDeleteClact( ZKN_BIG_SUB_DRAW* p_draw );
static void ZknBigSubAddFontOam( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubDeleteFontOam( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb );

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
void ZKN_BigSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_BIG_SUB_GLB*	p_glb;
	ZKN_BIG_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeBigSubGlb( heap, zkn_sys );
	p_drawglb = MakeBigSubDrawGlb( heap, zkn_sys );
	p_event = MakeBigSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= BigSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknBigSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknBigSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigSubProcDrawFuncDelete;
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
void ZKN_BigSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteBigSubGlb( p_data->p_glb_data ); 
	DeleteBigSubDrawGlb( p_data->p_glb_draw ); 
	DeleteBigSubEvent( p_data->p_event_data );
}


//----------------------------------------------------------------------------
/**
 *	@brief	���݂̃A�v���P�[�V�����f�[�^�擾
 *
 *	@param	p_data	�A�v���f�[�^
 *
 *	@retval	ZKN_BIGSUB_CONTROL_HEIGHT	�������
 *	@retval	ZKN_BIGSUB_CONTROL_GRAM		�d�����
 */
//-----------------------------------------------------------------------------
int ZKN_BigSubNowAplTypeGet( ZKN_APL_DATA* p_data )
{
	ZKN_BIG_SUB_GLB* p_glb = p_data->p_glb_data;

	return p_glb->now_apply;
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
static ZKN_BIG_SUB_GLB* MakeBigSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_SUB_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_SUB_GLB) );

	// �ϐ�������
	// �C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );		

	// �}�ӃR�����A�v���O���[�o���f�[�^
	p_glb->cp_zukan_common_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );

	// ���̃A�v���P�[�V����
	p_glb->now_apply = ZKN_BIGSUB_CONTROL_HEIGHT;

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
static ZKN_BIG_SUB_DRAWGLB* MakeBigSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_SUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_SUB_DRAWGLB) );


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
static ZKN_EVENT_DATA* MakeBigSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = BigSubEventDataNumGet();

	// �C�x���g�f�[�^�e�[�u���쐬
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeBigMain( heap, &p_event_tbl[0], zkn_sys, ZKN_BIG_SUB_EVENT_CHANGE_HEIGHT );
	ZKN_EVENT_MakeChangeBigWeightMain( heap, &p_event_tbl[1], zkn_sys, ZKN_BIG_SUB_EVENT_CHANGE_WEIGHT );

	return p_event_tbl;
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
static void DeleteBigSubGlb( ZKN_BIG_SUB_GLB* p_glb )
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
static void DeleteBigSubDrawGlb( ZKN_BIG_SUB_DRAWGLB* p_glb )
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
static void DeleteBigSubEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );
	ZKN_EVENT_DeleteData( &p_event[1] );

	sys_FreeMemoryEz( p_event );
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
static int BigSubEventDataNumGet( void )
{
	return ZKN_BIG_SUB_EVENT_NUM;
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
static int ZknBigSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_SUB_GLB* p_glb = p_glbdata;
	ZKN_BIG_SUB_WORK* p_work = p_dodata->p_work;
	int i;

	// ���[�N�̍쐬
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_BIG_SUB_WORK) );
	memset( p_work, 0, sizeof(ZKN_BIG_SUB_WORK) );

	// �{�^���C�x���g�f�[�^
	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;	// �{�^���C�x���g�f�[�^
	}

	// ���̃A�v���P�[�V����
	p_glb->now_apply = ZKN_BIGSUB_CONTROL_HEIGHT;


	// �{�^�����쐬
	ZknBigSubButtonMake( p_work, p_glb, p_dodata->heap );

	// �{�^���̏�Ԃ��P��ݒ�
	// �{�^������
	ZknBigSubButtonMove( p_work, p_glb );

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
static int ZknBigSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{

	ZKN_BIG_SUB_GLB* p_glb = p_glbdata;
	ZKN_BIG_SUB_WORK* p_work = p_dodata->p_work;
	
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
		ZknBugSubButtonEventBuffInit( p_work );
		
		// �J�[�\������
		// �J�[�\������L���ŁA�T�u�A�v���ɃJ�[�\�����삪������Ă���Ƃ��̂�
		if( ZKN_ZukanCommonSubCursorFlagGet( p_glb->cp_zukan_common_apl ) &&
			ZKN_GLBDATA_TouchCursorFlagGet( p_glb->p_glb ) ){

			ZknBigSubCursorMove( p_work, p_glb );
		}

		// �{�^������
		ZknBigSubButtonMove( p_work, p_glb );

		
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
static int ZknBigSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_SUB_GLB* p_glb = p_glbdata;
	ZKN_BIG_SUB_WORK* p_work = p_dodata->p_work;

	// �{�^���j��
	ZknBigSubButtonDelete( p_work );

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
static int ZknBigSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_BIGSUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_BIG_SUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_BIG_SUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGSUB_SEQINIT_LOAD:
		// Resource�ǂݍ���
		ZknBigSubLoadResource( p_drawwork, p_drawglb, p_drawdata->heap );

		// �t�F�[�h����
		ZknBigSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGSUB_SEQINIT_FADEIN:
		
		if( ZknBigSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_BIGSUB_SEQINIT_END:
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
static int ZknBigSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	// ����`�F�b�N
	if( ZKN_ZukanCommonSubMoveFlagGet( cp_dataglb->cp_zukan_common_apl ) ){
		
		// �{�^���`�惁�C��
		ZknBigSubButtonDrawMain( p_drawwork, p_drawglb, cp_datawork, p_drawdata->heap );

		// �J�[�\���`�惁�C��
		ZknBigSubCursorDraw( p_drawglb, cp_dataglb );
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
static int ZknBigSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_BIGSUB_SEQDELETE_FADEOUT_INIT:
		// �J�[�\���A�j����~
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, TRUE );

		// �t�F�[�h����
		ZknBigSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGSUB_SEQDELETE_FADEOUT:
		if( ZknBigSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_BIGSUB_SEQDELETE_RELEASE:
		// Resource�ǂݍ���
		ZknBigSubReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGSUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_BIGSUB_SEQDELETE_END:
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
static void ZknBigSubOamFadeInit( ZKN_BIG_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODE�𔼓����ɂ���
	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubOamFadeDelete( ZKN_BIG_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODE���m�[�}���ɂ���
	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubFadeInit( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknBigSubOamFadeInit( p_draw );

	// �u���C�g�l�X�������s���Ă悢��
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_BIGSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_BIGSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
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
static BOOL ZknBigSubFadeMain( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb, BOOL fadein_out )
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
			ZknBigSubOamFadeDelete( p_draw );
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
static void ZknBigSubButtonMake( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb, int heap )
{
	// �e�[�u���쐬
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_BIGSUB_BUTTON_NUM );

	// �e�[�u���f�[�^�ݒ�
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_BIGSUB_BUTTON_HEIGHT ],
			ZKN_BIGSUB_BUTTON_DEF_Y - (ZKN_BIGSUB_BUTTON_SIZE_Y/2),
			ZKN_BIGSUB_BUTTON_DEF_Y + (ZKN_BIGSUB_BUTTON_SIZE_Y/2),
			ZKN_BIGSUB_BUTTON_HEIGHT_X - (ZKN_BIGSUB_BUTTON_SIZE_X/2),
			ZKN_BIGSUB_BUTTON_HEIGHT_X + (ZKN_BIGSUB_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_BIGSUB_BUTTON_GRAM ],
			ZKN_BIGSUB_BUTTON_DEF_Y - (ZKN_BIGSUB_BUTTON_SIZE_Y/2),
			ZKN_BIGSUB_BUTTON_DEF_Y + (ZKN_BIGSUB_BUTTON_SIZE_Y/2),
			ZKN_BIGSUB_BUTTON_GRAM_X - (ZKN_BIGSUB_BUTTON_SIZE_X/2),
			ZKN_BIGSUB_BUTTON_GRAM_X + (ZKN_BIGSUB_BUTTON_SIZE_X/2) );

	p_work->callcack.p_glb = p_glb;
	p_work->callcack.p_work = p_work;

	// �{�^���}�l�[�W���쐬
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_BIGSUB_BUTTON_NUM,
			ZknBigSubButtonCallBack,
			&p_work->callcack,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brieuf	�{�^���o�b�t�@������
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBugSubButtonEventBuffInit( ZKN_BIG_SUB_WORK* p_work )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubButtonMove( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb )
{

	BMN_Main( p_work->p_button_man );

	// ���I�𒆂̃A�v���P�[�V�����̃{�^���͉������ςȂ��ɂ���
	switch( p_glb->now_apply ){
	case ZKN_BIGSUB_BUTTON_HEIGHT:	//������� 
		if( p_work->button_event[ ZKN_BIGSUB_BUTTON_HEIGHT ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_BIGSUB_BUTTON_HEIGHT ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_BIGSUB_BUTTON_GRAM:	//�d�����
		if( p_work->button_event[ ZKN_BIGSUB_BUTTON_GRAM ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_BIGSUB_BUTTON_GRAM ] = BMN_EVENT_RELEASE;
		}
		break;
		
	default:
		break;
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
static void ZknBigSubButtonDelete( ZKN_BIG_SUB_WORK* p_work )
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
static void ZknBigSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_BIG_BUTTON_CALLBACK* p_work_data = p_work;
	ZKN_BIG_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_BIG_SUB_WORK* p_subwork = p_work_data->p_work;

	// �{�^���C�x���g�i�[
	p_subwork->button_event[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		switch( button_no ){
		case ZKN_BIGSUB_BUTTON_HEIGHT:
			if( p_glb->now_apply != ZKN_BIGSUB_CONTROL_HEIGHT ){
				// �{�^���Ƀ^�b�`
				Snd_SePlay( ZKN_SND_BUTTON );
				p_glb->now_apply = ZKN_BIGSUB_CONTROL_HEIGHT;
				*p_glb->p_event_key |= ZKN_BIG_SUB_EVENT_CHANGE_HEIGHT;
			}
			break;
			
		case ZKN_BIGSUB_BUTTON_GRAM:
			if( p_glb->now_apply != ZKN_BIGSUB_CONTROL_GRAM ){
				// �{�^���Ƀ^�b�`
				Snd_SePlay( ZKN_SND_BUTTON );
				p_glb->now_apply = ZKN_BIGSUB_CONTROL_GRAM;
				*p_glb->p_event_key |= ZKN_BIG_SUB_EVENT_CHANGE_WEIGHT;
			}
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
static void ZknBigSubLoadResource( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	// �w�i
	ZknBigSubSetUpBg( p_drawglb, heap );

	// OAM
	ZknBigSubLoadOamData( p_draw, p_drawglb, heap );

	// �Z���A�N�^�[�o�^
	ZknBigSubAddClact( p_draw, p_drawglb, heap );

	// FONTOAM�o�^
	ZknBigSubAddFontOam( p_draw, p_drawglb, heap );
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
static void ZknBigSubReleaseResource( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	int i;
	
	// �p���b�g�����Z�b�g
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_4_NCLR, PALTYPE_SUB_BG, ZKN_BIGSUB_BUTTON_HEIGHTBG_PLTT_NO*32, 32, heap );
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_4_NCLR, PALTYPE_SUB_BG, ZKN_BIGSUB_BUTTON_GRAMBG_PLTT_NO*32, 32, heap );
	
	// �Z���A�N�^�[�j��
	ZknBigSubDeleteClact( p_draw );

	// FONTOAM�j��
	ZknBigSubDeleteFontOam( p_draw, p_drawglb );

	// OAM
	ZknBigSubReleaseOamData( p_draw, p_drawglb );

	// �p���b�g�o�b�t�@�j��
	for( i=0;i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubSetUpBg( ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub2_b_lzh_NSCR, TRUE, &p_scrn, heap );
	
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
static void ZknBigSubLoadOamData( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_BIG_SUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_BIG_SUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_BIG_SUB_RES_ID,
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
static void ZknBigSubReleaseOamData( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb )
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
static void ZknBigSubAddClact( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_BIG_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_BIG_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_BIG_SUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_BIG_SUB_OAM_BG_PTR,
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
	
	// ����
	add.mat.x = ZKN_BIGSUB_BUTTON_HEIGHT_X << FX32_SHIFT;
	add.mat.y = ZKN_BIGSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_BIGSUB_BUTTON_HEIGHT ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_BIGSUB_BUTTON_HEIGHT ], ZKN_BIGSUB_BUTTON_ANM_SEQ );	

	// �d��
	add.mat.x = ZKN_BIGSUB_BUTTON_GRAM_X << FX32_SHIFT;
	add.mat.y = ZKN_BIGSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_BIGSUB_BUTTON_GRAM ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_BIGSUB_BUTTON_GRAM ], ZKN_BIGSUB_BUTTON_ANM_SEQ );	
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
static void ZknBigSubDeleteClact( ZKN_BIG_SUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubAddFontOam( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// �p���b�g�A�h���X

	// ���CLACT��o�^���Ă���K�v������
	GF_ASSERT( p_draw->button[ ZKN_BIGSUB_BUTTON_HEIGHT ] );

	// �p���b�g�̃��\�[�X�f�[�^�擾
	// �p���b�g�v���N�V�擾�p
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS );

	// �������f�[�^�̋��ʕ������쐬
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.x			 = ZKN_BIGSUB_BUTTON_FONT_OFS_X;
	fontoam_init.y			 = ZKN_BIGSUB_BUTTON_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_BIG_SUB_OAM_BG_PTR;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CY );

	// ������
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_BIG_BUTTON_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->button[ ZKN_BIGSUB_BUTTON_HEIGHT ];
	p_draw->p_button_font[ ZKN_BIGSUB_BUTTON_HEIGHT ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_button_font[ ZKN_BIGSUB_BUTTON_HEIGHT ]->p_fontoam, pltt_ofs + ZKN_BIGSUB_BUTTON_PAL_OFS );

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );

	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CY );


	// ���߂�
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_BIG_BUTTON_01, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->button[ ZKN_BIGSUB_BUTTON_GRAM ];
	p_draw->p_button_font[ ZKN_BIGSUB_BUTTON_GRAM ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_button_font[ ZKN_BIGSUB_BUTTON_GRAM ]->p_fontoam, pltt_ofs + ZKN_BIGSUB_BUTTON_PAL_OFS );


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
static void ZknBigSubDeleteFontOam( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb )
{
	int i;

	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubButtonControl( ZKN_BIG_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff )
{
	int now_frm;
	NNSG2dPaletteData* p_plt;
	BOOL check;
	BOOL chenge = FALSE;
	int arc_data_idx;

	
	// �{�^������
	ZKN_UTIL_ButtonMove( button,
			event );

	ZknBigSubFontButtonMove( 
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
static void ZknBigSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt )
{
	ZKN_UTIL_ButtonFontMove_Col( act, p_fontoam, def_y, off_pltt, on_pltt );
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
static void ZknBigSubButtonDrawMain( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_WORK* cp_work, int heap )
{
	int i;	// ���[�v�p
	int bgpltt_no;

	// �{�^���\������
	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){

		if( i == ZKN_BIGSUB_BUTTON_HEIGHT ){
			bgpltt_no = ZKN_BIGSUB_BUTTON_HEIGHTBG_PLTT_NO;
		}else{
			bgpltt_no = ZKN_BIGSUB_BUTTON_GRAMBG_PLTT_NO;
		}
		
		ZknBigSubButtonControl( p_drawglb,
				p_draw->button[i],
				p_draw->p_button_font[i], cp_work->button_event[i],
				ZKN_BIGSUB_BUTTON_FONT_OFS_Y, bgpltt_no,
				&p_draw->bgpltt_no[i], heap,
				ZKN_BIGSUB_BUTTON_PAL_OFS, 
				ZKN_BIGSUB_BUTTON_PAL_OFS_ON,
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
static void ZknBigSubCursorMove( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb )
{
	// A�{�^���ŃA�v���P�[�V�����𕪊�
	if( sys.trg & PAD_BUTTON_A ){

		// �A�v���ɂ�蕪��
		if( p_glb->now_apply == ZKN_BIGSUB_CONTROL_GRAM ){	
			p_glb->now_apply = ZKN_BIGSUB_CONTROL_HEIGHT;
			*p_glb->p_event_key |= ZKN_BIG_SUB_EVENT_CHANGE_HEIGHT;

			p_work->button_event[ ZKN_BIGSUB_BUTTON_HEIGHT ] = BMN_EVENT_HOLD;
		}else{
			p_glb->now_apply = ZKN_BIGSUB_CONTROL_GRAM;
			*p_glb->p_event_key |= ZKN_BIG_SUB_EVENT_CHANGE_WEIGHT;

			p_work->button_event[ ZKN_BIGSUB_BUTTON_GRAM ] = BMN_EVENT_HOLD;
		}
		// �{�^���Ƀ^�b�`
		Snd_SePlay( ZKN_SND_BUTTON );
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
static void ZknBigSubCursorDraw( ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb )
{
	
	// �����̍��W��ݒ肵�Ă悢���`�F�b�N
	if( ZKN_ZukanCommonSubCursorFlagGet( cp_glb->cp_zukan_common_apl ) == TRUE ){

		// �A�v���ɂ�蕪��
		if( cp_glb->now_apply == ZKN_BIGSUB_CONTROL_HEIGHT ){
			ZknBigSubCursorMatSet( p_drawglb, ZKN_BIGSUB_BUTTON_GRAM_X, ZKN_BIGSUB_BUTTON_DEF_Y, ZKN_BIGSUB_CURSOR_SIZE_X, ZKN_BIGSUB_CURSOR_SIZE_Y );
		}else{
			ZknBigSubCursorMatSet( p_drawglb, ZKN_BIGSUB_BUTTON_HEIGHT_X, ZKN_BIGSUB_BUTTON_DEF_Y, ZKN_BIGSUB_CURSOR_SIZE_X, ZKN_BIGSUB_CURSOR_SIZE_Y );
		}
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
static void ZknBigSubCursorMatSet( ZKN_BIG_SUB_DRAWGLB* p_drawglb, int x, int y, int size_x, int size_y )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	ZKN_UTIL_CursorSetMatrix( p_draw, x, y, size_x, size_y );
}

