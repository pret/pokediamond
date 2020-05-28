//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_range_sub.c
 *	@brief		���z�}�T�u���
 *	@author		tomoya takahashi 
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "calctool.h"
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
#include "include/application/zukanlist/zkn_range.h"

#define	__ZKN_RANGE_SUB_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_range_sub.h"

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
#define ZKN_RANGE_SUB_EVENT_NUM ( 0 )	// �C�x���g��

#define ZKN_RANGE_SUB_OAM_BG_PRI	( 1 )
#define ZKN_RANGE_SUB_OAM_SOFT_PRI	( 31 )

enum{
	ZKN_RANGESUB_SEQINIT_ALLOC,
	ZKN_RANGESUB_SEQINIT_LOAD,
	ZKN_RANGESUB_SEQINIT_FADEIN,
	ZKN_RANGESUB_SEQINIT_END,
};
enum{
	ZKN_RANGESUB_SEQDELETE_FADEOUT_INIT,
	ZKN_RANGESUB_SEQDELETE_FADEOUT,
	ZKN_RANGESUB_SEQDELETE_RELEASE,
	ZKN_RANGESUB_SEQDELETE_FREE,
	ZKN_RANGESUB_SEQDELETE_END,
};

// �{�^��
enum{
	ZKN_RANGESUB_BUTTON_CURSOR,
	ZKN_RANGESUB_BUTTON_NUM,
};


// ���ԃe�[�u��
#define ZKN_RANGE_SUB_TIME_LIMIT	( 85 )

//BG�p���b�g�t�F�[�h
#define ZKN_RANGE_SUB_TIMEPLTT_LIMIT	( 51 )
#define ZKN_RANGE_SUB_PLTT_NUM			( 5 )
#define ZKN_RANGE_SUB_PLTT_NO			( 2 )

// �p���b�g�A�j��
#define ZKN_RANGE_SUB_PLTT_ANM_WAIT	( 0 )
enum{
	ZKN_RANGESUB_PLTTANM_SEQ_NOW_PLTT_0,
//	ZKN_RANGESUB_PLTTANM_SEQ_NOW_PLTT_0WAIT,
	ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_0,
//	ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_0WAIT,
	ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_1,
};
	

// �J�[�\���ʒu
#define ZKN_RANGE_SUB_CURSOR_MORNING_X	( 32 )
#define ZKN_RANGE_SUB_CURSOR_MORNING_Y	( 128 )
#define ZKN_RANGE_SUB_CURSOR_NOON_X		( 128 )
#define ZKN_RANGE_SUB_CURSOR_NOON_Y		( 96 )
#define ZKN_RANGE_SUB_CURSOR_NIGHT_X	( 224 )
#define ZKN_RANGE_SUB_CURSOR_NIGHT_Y	( 128 )
#define ZKN_RANGE_SUB_CURSOR_SEQ		( 0 )
#define ZKN_RANGE_SUB_CURSOR_SIZE_R		( 32 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_X	( 24 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_X_MAX	( 246 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_Y	( 64 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX	( 132 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_DIS	( 48 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X	( 40 )	// ���[���猸�炷X���W�l
#define ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X_CALC_DIS	( 256 - (ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X * 2) )	// ���[���猸�炷X���W�l���ւ炵����size
#define ZKN_RANGE_SUB_CURSOR_MARK_SIZE_X		( 32 )
#define ZKN_RANGE_SUB_CURSOR_MARK_SIZE_Y		( 32 )


// �t�F�[�h
#define ZKN_RANGESUB_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	���z�}�T�u��ʉ�ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	// ���z�}�T�u�A�v���f�[�^
	ZKN_APL_DATA* p_range_apl;
	
	// �}�ӃR�����T�u�A�v���f�[�^
	const ZKN_APL_DATA* cp_zukan_common_apl;
} ZKN_RANGE_SUB_GLB;

//-------------------------------------
//	���z�}�T�u��ʉ�ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_RANGE_SUB_DRAWGLB;

//-------------------------------------
//	�{�^���R�[���o�b�N�p���[�N
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_RANGE_SUB_CALLBACK_WORK;


//-------------------------------------
//	���z�}�T�u��ʉ�ʁ@�������[�N
//=====================================
typedef struct {
	// �^�b�`���W
	int x;
	int y;
	int ofs_x;	// �}����ꂽ�Ƃ��̒��S����̗��ꂽ���W
	int ofs_y;

	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// �{�^���f�[�^
	ZKN_RANGE_SUB_CALLBACK_WORK button_work;
	int touch;

	BOOL key_set;
	
} ZKN_RANGE_SUB_WORK;

//-------------------------------------
//	���z�}�T�u��ʉ�ʁ@�������[�N
//=====================================
typedef struct {
	CLACT_WORK_PTR cursor;	// �J�[�\��
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	void* pltt_buff;
	int pltt_no;
	int next_pltt_no;
	NNSG2dPaletteData* p_plt;
	int pltt_anm_seq;
	int pltt_anm_count;
} ZKN_RANGE_SUB_DRAW;

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
static ZKN_RANGE_SUB_GLB* MakeRangeSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_RANGE_SUB_DRAWGLB* MakeRangeSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeRangeSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteRangeSubGlb( ZKN_RANGE_SUB_GLB* p_glb );
static void DeleteRangeSubDrawGlb( ZKN_RANGE_SUB_DRAWGLB* p_glb );
static void DeleteRangeSubEvent( ZKN_EVENT_DATA* p_event );


static int RangeSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknRangeSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknRangeSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknRangeSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// �t�F�[�h����
static void ZknRangeSubOamFadeInit( ZKN_RANGE_SUB_DRAW* p_draw );
static void ZknRangeSubOamFadeDelete( ZKN_RANGE_SUB_DRAW* p_draw );
static void ZknRangeSubFadeInit( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknRangeSubFadeMain( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, BOOL fadein_out );

// �{�^������
static void ZknRangeSubCursorInit( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb, int heap );

static void ZknRangeSubCursorMain( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb );
static void ZknRangeSubButtonCallBack( u32 button_no, u32 event, void* p_work );
static void ZknRangeSubCursorDelete( ZKN_RANGE_SUB_WORK* p_work );
static void ZknRangeSubCursorMove( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb );
static void ZknRangeSubCursorDefMatSet( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb );

// �L�[�ɂ��J�[�\������
static void ZknRangeSubCursorMoveKey( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb );

static void ZknRangeSubCursorMoveKey_CorsorDrawSet( ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_WORK* cp_work, const ZKN_RANGE_SUB_GLB* cp_glb );


// �ǂݍ��ݏ���
static void ZknRangeSubLoadResource( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknRangeSubReleaseResource( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknRangeSubSetUpBg( ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknRangeSubLoadOamData( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknRangeSubReleaseOamData( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb );
static void ZknRangeSubAddClact( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknRangeSubDeleteClact( ZKN_RANGE_SUB_DRAW* p_draw );

// CURSOR�`�搧��
static void ZknRangeSubCursorDraw( ZKN_RANGE_SUB_DRAW* p_draw, const ZKN_RANGE_SUB_GLB* cp_glb, const ZKN_RANGE_SUB_WORK* cp_work );

static int ZknRangeSubCursorMoveMaxDisGet( int x );

// BG�p���b�g����
static void ZknRangeSubBgPlttDraw( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�T�u��ʁ@�A�v���쐬
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
void ZKN_RangeSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_RANGE_SUB_GLB*	p_glb;
	ZKN_RANGE_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeRangeSubGlb( heap, zkn_sys );
	p_drawglb = MakeRangeSubDrawGlb( heap, zkn_sys );
	p_event = MakeRangeSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= RangeSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknRangeSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknRangeSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknRangeSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknRangeSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknRangeSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknRangeSubProcDrawFuncDelete;
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
void ZKN_RangeSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteRangeSubGlb( p_data->p_glb_data ); 
	DeleteRangeSubDrawGlb( p_data->p_glb_draw ); 
	DeleteRangeSubEvent( p_data->p_event_data );
}



//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�T�u��ʁ@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_RANGE_SUB_GLB* MakeRangeSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_RANGE_SUB_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_RANGE_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_RANGE_SUB_GLB) );

	// ���z�}�A�v���f�[�^
	p_glb->p_range_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_RANGE );

	// �}�ӃT�u�R�����f�[�^
	p_glb->cp_zukan_common_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��O���[�o��
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static ZKN_RANGE_SUB_DRAWGLB* MakeRangeSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_RANGE_SUB_DRAWGLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_RANGE_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_RANGE_SUB_DRAWGLB) );

	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );


	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�T�u��ʁ@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeRangeSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	return NULL;	// ���͂Ȃ�
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�T�u��ʁ@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeSubGlb( ZKN_RANGE_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�T�u��ʁ@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeSubDrawGlb( ZKN_RANGE_SUB_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�T�u��ʁ@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeSubEvent( ZKN_EVENT_DATA* p_event )
{
	// ���͂Ȃ�
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���z�}�T�u��ʃA�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	���z�}�T�u��ʃA�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int RangeSubEventDataNumGet( void )
{
	return ZKN_RANGE_SUB_EVENT_NUM;
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
static int ZknRangeSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_SUB_GLB* p_glb = p_glbdata;
	ZKN_RANGE_SUB_WORK* p_work;

	// �������m��
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_RANGE_SUB_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_RANGE_SUB_WORK) );
	p_dodata->p_work = p_work;

	// CURSOR�f�t�H�ʒu�ݒ�
	ZknRangeSubCursorDefMatSet( p_work, p_glb );

	// �{�^���쐬
	// CURSOR�f�t�H�ʒu�ݒ�̌�̕K�v����
	ZknRangeSubCursorInit( p_work, p_glb, p_dodata->heap );
	
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
static int ZknRangeSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_SUB_GLB* p_glb = p_glbdata;
	ZKN_RANGE_SUB_WORK* p_work = p_dodata->p_work;

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
		// CURSOR����
		ZknRangeSubCursorMain( p_work, p_glb );	
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
static int ZknRangeSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_SUB_GLB* p_glb = p_glbdata;
	ZKN_RANGE_SUB_WORK* p_work = p_dodata->p_work;


	// �{�^���j��
	ZknRangeSubCursorDelete( p_work );
	
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
static int ZknRangeSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_RANGE_SUB_DRAW*		p_drawwork = p_drawdata->p_work;
	
	switch( p_drawdata->seq ){
	case ZKN_RANGESUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_RANGE_SUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_RANGE_SUB_DRAW) );

		p_drawdata->seq++;
		break;
		
	case ZKN_RANGESUB_SEQINIT_LOAD:
		// Resource�ǂݍ���
		ZknRangeSubLoadResource( p_drawwork, p_drawglb, p_drawdata->heap );
		// ���W�ݒ�
		ZknRangeSubCursorDraw( p_drawwork, cp_dataglb, cp_datawork );
		ZknRangeSubBgPlttDraw( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );

		// �t�F�[�h����
		ZknRangeSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGESUB_SEQINIT_FADEIN:
		// �A�j������̂ł����ƌĂ�
		ZknRangeSubBgPlttDraw( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );


		if( ZknRangeSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_RANGESUB_SEQINIT_END:
		// �A�j������̂ł����ƌĂ�
		ZknRangeSubBgPlttDraw( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );

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
static int ZknRangeSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_RANGE_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	// CURSOR����
	ZknRangeSubCursorDraw( p_drawwork, cp_dataglb, cp_datawork );

	// �J�[�\��MARK�`��
	ZknRangeSubCursorMoveKey_CorsorDrawSet( p_drawglb, cp_datawork, cp_dataglb );

	// �p���b�g�t�F�[�h
	ZknRangeSubBgPlttDraw( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );

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
static int ZknRangeSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_RANGE_SUB_DRAW*		p_drawwork = p_drawdata->p_work;
	
	switch( p_drawdata->seq ){
	case ZKN_RANGESUB_SEQDELETE_FADEOUT_INIT:

		// �J�[�\���A�j����~
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, TRUE );
		
		// �t�F�[�h����
		ZknRangeSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGESUB_SEQDELETE_FADEOUT:
		if( ZknRangeSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_RANGESUB_SEQDELETE_RELEASE:
		// Resource�ǂݍ���
		ZknRangeSubReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGESUB_SEQDELETE_FREE:

		sys_FreeMemoryEz( p_drawwork->pltt_buff );
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_RANGESUB_SEQDELETE_END:
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
static void ZknRangeSubOamFadeInit( ZKN_RANGE_SUB_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->cursor, GX_OAM_MODE_XLU );
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
static void ZknRangeSubOamFadeDelete( ZKN_RANGE_SUB_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->cursor, GX_OAM_MODE_NORMAL );
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
static void ZknRangeSubFadeInit( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknRangeSubOamFadeInit( p_draw );

	// �u���C�g�l�X�������s���Ă悢��
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_RANGESUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_RANGESUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
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
static BOOL ZknRangeSubFadeMain( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, BOOL fadein_out )
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
			ZknRangeSubOamFadeDelete( p_draw );
		}

		return TRUE;
	}

	return FALSE;
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
static void ZknRangeSubLoadResource( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap )
{
	// �w�i
	ZknRangeSubSetUpBg( p_drawglb, heap );

	// OAM
	ZknRangeSubLoadOamData( p_draw, p_drawglb, heap );

	// �Z���A�N�^�[�o�^
	ZknRangeSubAddClact( p_draw, p_drawglb, heap );


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
static void ZknRangeSubReleaseResource( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap )
{
	// �Z���A�N�^�[�j��
	ZknRangeSubDeleteClact( p_draw );

	// OAM
	ZknRangeSubReleaseOamData( p_draw, p_drawglb );
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
static void ZknRangeSubSetUpBg( ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_sub_lzh_NSCR, TRUE, &p_scrn, heap );
	
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
static void ZknRangeSubLoadOamData( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub4_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub4_lzh_NCGR + ZKN_RANGE_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub4_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub4_lzh_NCER + ZKN_RANGE_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub4_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub4_lzh_NANR + ZKN_RANGE_RES_ID,
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
static void ZknRangeSubReleaseOamData( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb )
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
static void ZknRangeSubAddClact( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub4_lzh_NCGR + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub4_lzh_NCER + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_data_oam_sub4_lzh_NANR + ZKN_RANGE_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_RANGE_SUB_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_RANGE_SUB_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	
	// CURSOR
	add.mat.x = 0;
	add.mat.y = 0;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->cursor = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->cursor, ZKN_RANGE_SUB_CURSOR_SEQ );	

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
static void ZknRangeSubDeleteClact( ZKN_RANGE_SUB_DRAW* p_draw )
{
	CLACT_Delete( p_draw->cursor );
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSOR�p�{�^���}�l�[�W���쐬
 *
 *	@param	p_work		���[�N
 *	@param	p_glb		�O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorInit( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb, int heap )
{
	// �e�[�u���쐬
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_RANGESUB_BUTTON_NUM );

	// �e�[�u���f�[�^�ݒ�
	p_work->hit_tbl[ 0 ].circle.code = TP_USE_CIRCLE;
	p_work->hit_tbl[ 0 ].circle.x	 = p_work->x;
	p_work->hit_tbl[ 0 ].circle.y	 = p_work->y;
	p_work->hit_tbl[ 0 ].circle.r	 = ZKN_RANGE_SUB_CURSOR_SIZE_R;

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// �{�^���}�l�[�W���쐬
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_RANGESUB_BUTTON_NUM,
			ZknRangeSubButtonCallBack,
			&p_work->button_work,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSOR���상�C���֐�
 *
 *	@param	p_work		���[�N
 *	@param	p_glb		�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorMain( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb )
{
	
	// �{�^���͈͓��ɓ�������
	BMN_Main( p_work->p_button_man );

	ZknRangeSubCursorMove( p_work, p_glb );

	// �����蔻��̈�ɐݒ�
	p_work->hit_tbl[ 0 ].circle.x = p_work->x;
	p_work->hit_tbl[ 0 ].circle.y = p_work->y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L�[���͓���
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o�����[�N
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorMoveKey( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb )
{
	s32 type;

	if( sys.tp_cont ){
		return ;
	}
	
	if( ZKN_ZukanCommonSubCursorFlagGet( p_glb->cp_zukan_common_apl ) == TRUE ){
		type = ZKN_RangeTypeGet( p_glb->p_range_apl );
		if( sys.trg & PAD_KEY_LEFT ){
			type --;
			if( type < 0 ){
				type = 0;
			}
			// ���̍��W�̂�������
			ZKN_RangeTypeSet( p_glb->p_range_apl, type );

			// ���̎��Ԃ̍��W���J�[�\���ɐݒ�
			ZknRangeSubCursorDefMatSet( p_work, p_glb );
			p_work->key_set = TRUE;
			
		}else if( sys.trg & PAD_KEY_RIGHT ){

			type ++;
			if( type >= ZKN_RANGE_TYPE_NUM ){
				type = ZKN_RANGE_TYPE_NUM - 1;
			}
			// ���̍��W�̂�������
			ZKN_RangeTypeSet( p_glb->p_range_apl, type );
			// ���̎��Ԃ̍��W���J�[�\���ɐݒ�
			ZknRangeSubCursorDefMatSet( p_work, p_glb );
			p_work->key_set = TRUE;
		}
	
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSOR����
 *
 *	@param	p_work	���[�N�f�[�^
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorMove( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb )
{
	int type;
	int y_max_dis;
	
	p_work->key_set = FALSE;
	
	if( p_work->touch ){

		// �^�b�`���Ă����炻�̍��W��ۑ���
		// ���̍��W�ʒu�̎��Ԃ�ݒ�b
		if( sys.tp_cont ){
			p_work->x = sys.tp_x - p_work->ofs_x;
			p_work->y = sys.tp_y - p_work->ofs_y;

			if( p_work->x < ZKN_RANGE_SUB_CURSOR_LIMIT_X ){
				p_work->x = ZKN_RANGE_SUB_CURSOR_LIMIT_X;
			}
			if( p_work->x > ZKN_RANGE_SUB_CURSOR_LIMIT_X_MAX ){
				p_work->x = ZKN_RANGE_SUB_CURSOR_LIMIT_X_MAX;
			}

			if( p_work->y < ZKN_RANGE_SUB_CURSOR_LIMIT_Y ){
				p_work->y = ZKN_RANGE_SUB_CURSOR_LIMIT_Y;
			}

			// Y�����ő�l�����߂�
			y_max_dis = ZknRangeSubCursorMoveMaxDisGet( p_work->x );
			if( p_work->y > (ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX + y_max_dis) ){
				p_work->y = (ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX + y_max_dis);
			}


			type = p_work->x / ZKN_RANGE_SUB_TIME_LIMIT;

			if( type > ZKN_RANGE_TYPE_NIGHT ){
				type = ZKN_RANGE_TYPE_NIGHT;
			}
			
			// ���̍��W�̂�������
			ZKN_RangeTypeSet( p_glb->p_range_apl, type );
		}else{
			p_work->touch = 0;
		}
	}else{
		ZknRangeSubCursorMoveKey( p_work, p_glb );
	}
}

//----------------------------------------------------------------------------
/**	
 *	@brief	�}�Ӄ{�^���R�[���΂����֐�
 *
 *	@param	button_no	�{�^���i���o�[
 *	@param	event		�C�x���g�i���o�[
 *	@param	p_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_RANGE_SUB_CALLBACK_WORK* p_work_data = p_work;
	ZKN_RANGE_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_RANGE_SUB_WORK* p_subwork = p_work_data->p_work;

	switch( event ){
	case BMN_EVENT_TOUCH:
		// �{�^���Ƀ^�b�`
		Snd_SePlay( ZKN_SND_BUTTON );
		p_subwork->touch = 1;	// �^�b�`

		// ���S����̍��W���擾
		p_subwork->ofs_x = sys.tp_x - p_subwork->x;
		p_subwork->ofs_y = sys.tp_y - p_subwork->y;
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSOR�f�[�^�j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorDelete( ZKN_RANGE_SUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );

	// �e�[�u�����[�N�j��
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSOR�`�搧��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	cp_work		�f�[�^���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorDraw( ZKN_RANGE_SUB_DRAW* p_draw, const ZKN_RANGE_SUB_GLB* cp_glb, const ZKN_RANGE_SUB_WORK* cp_work )
{
	VecFx32 mat;
	
	// CURSOR���W��ݒ�
	mat.x = cp_work->x << FX32_SHIFT;
	mat.y = cp_work->y << FX32_SHIFT;
	mat.y += SUB_SURFACE_Y;

	CLACT_SetMatrix( p_draw->cursor, &mat );

	// ���Ԃɂ���ĊG��ύX
	CLACT_AnmChg( p_draw->cursor, ZKN_RangeTypeGet( cp_glb->p_range_apl ) );
}

// BG�p���b�g����
//----------------------------------------------------------------------------
/**
 *	@brief	BG�p���b�g����
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	cp_glb	�O���[�o���f�[�^
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubBgPlttDraw( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, int heap )
{
	int pltt_no;
	int pltt_anm = 0;
	BOOL check;
	
	// �p���b�g�^�C�v�i���o�[
	pltt_no = ZKN_RangeTypeGet( cp_glb->p_range_apl );

	// �p���b�g�i���o�[���Ⴄ���o�b�t�@��NULL�̂Ƃ��ݒ�
	if( (p_draw->pltt_no != pltt_no) || ( p_draw->pltt_buff == NULL ) ||
		(p_draw->next_pltt_no != p_draw->pltt_no) ){

		// ���ݒ蒆�̃p���b�g�i���o�[���Ⴄ���̂ɂȂ��Ă��܂�����
		// �Đݒ�
		if( p_draw->next_pltt_no != pltt_no ){
			p_draw->pltt_no = p_draw->next_pltt_no;
			p_draw->pltt_anm_seq = 0;
		}
		
		// �p���b�g�A�j��������
		switch( p_draw->pltt_anm_seq ){
		case ZKN_RANGESUB_PLTTANM_SEQ_NOW_PLTT_0:
			// ���̃p���b�g�i���o�[�ݒ�
			p_draw->next_pltt_no = pltt_no;
			
			// ���܂ł̂�j��
			if( p_draw->pltt_buff ){
				sys_FreeMemoryEz( p_draw->pltt_buff );
			}
			// �p���b�g�ǂݍ���
			p_draw->pltt_buff = ZKN_GLBDATA_PalDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_00_NCLR + p_draw->pltt_no, &p_draw->p_plt, heap );
			p_draw->pltt_anm_count = ZKN_RANGE_SUB_PLTT_ANM_WAIT;

			// �p���b�g�A�j���Z�b�g
			if( p_draw->pltt_no > pltt_no ){
				pltt_anm = 1;	// ���[�����@���[����
			}else{
				pltt_anm = 2;	// ��[�����@���[����
			}
			p_draw->pltt_anm_seq ++;
			break;

/*		case ZKN_RANGESUB_PLTTANM_SEQ_NOW_PLTT_0WAIT:
			p_draw->pltt_anm_count--;
			if( p_draw->pltt_anm_count <= 0 ){
				p_draw->pltt_anm_seq ++;
			}
			return ;//*/

		case ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_0:
			// ���܂ł̂�j��
			if( p_draw->pltt_buff ){
				sys_FreeMemoryEz( p_draw->pltt_buff );
			}
			// �p���b�g�ǂݍ���
			p_draw->pltt_buff = ZKN_GLBDATA_PalDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_00_NCLR + p_draw->next_pltt_no, &p_draw->p_plt, heap );
			p_draw->pltt_anm_count = ZKN_RANGE_SUB_PLTT_ANM_WAIT;

			// �p���b�g�A�j���Z�b�g
			if( p_draw->pltt_no < p_draw->next_pltt_no ){
				pltt_anm = 1;	// ���[�����@���[����
			}else{
				pltt_anm = 2;	// ��[�����@���[����
			}
			p_draw->pltt_anm_seq ++;
			break;

/*		case ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_0WAIT:
			p_draw->pltt_anm_count--;
			if( p_draw->pltt_anm_count <= 0 ){
				p_draw->pltt_anm_seq ++;
			}
			return ;//*/
			
		case ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_1:
			pltt_anm = 0;		// �ʏ�
			p_draw->pltt_anm_seq = 0;
			p_draw->pltt_no = p_draw->next_pltt_no;
			break;

		}

		// TransferManager�ɓo�^
		check = AddVramTransferManager(
				NNS_GFD_DST_2D_BG_PLTT_SUB,
				ZKN_RANGE_SUB_PLTT_NO*32,
				&((u8*)(p_draw->p_plt->pRawData))[(pltt_anm*32)],
				32 );
		// �]���^�X�N�������s
		GF_ASSERT( check );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSOR�f�t�H���g�ʒu�ݒ�
 *
 *	@param	p_work	���샏�[�N
 *	@param	p_glb	�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorDefMatSet( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb )
{
	int type = ZKN_RangeTypeGet( p_glb->p_range_apl );
	
	// �ŏ��̃J�[�\���ʒu�ݒ�
	switch( type ){
	case ZKN_RANGE_TYPE_MORNING:	// ��
		p_work->x = ZKN_RANGE_SUB_CURSOR_MORNING_X;
		p_work->y = ZKN_RANGE_SUB_CURSOR_MORNING_Y;
		break;
		
	case ZKN_RANGE_TYPE_NOON:	// ��
		p_work->x = ZKN_RANGE_SUB_CURSOR_NOON_X;
		p_work->y = ZKN_RANGE_SUB_CURSOR_NOON_Y;
		break;
		
	case ZKN_RANGE_TYPE_NIGHT:	// ��
		p_work->x = ZKN_RANGE_SUB_CURSOR_NIGHT_X;
		p_work->y = ZKN_RANGE_SUB_CURSOR_NIGHT_Y;
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	Y���Ɉړ�����ő�l��X���W�ɂ��ϓ��l�����߂�
 *
 *	@param	x 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static int ZknRangeSubCursorMoveMaxDisGet( int x )
{
	int rota_num;
	int ret_num;
	
	// �ő�̕����͌v�Z���Ȃ��Ă��킩��
	if( (x < ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X) ||
		( (256 - ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X) < x ) ){

		return ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_DIS;
	}
	
	// ����Ă��邱�Ƃ͂����W���獡�̍��W��sin�J�[�u��]�p
	// ���擾���āA���̒l��Y���W���~�b�g�ύX�l
	// ���炢�����炷�ƍ��̃��~�b�g�ύX�l�ɂȂ邩�����߂Ă���
	x -= ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X;

	rota_num = FX_GET_ROTA_NUM( 180 ) * x;
	rota_num = rota_num / ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X_CALC_DIS;
	// ���̃��~�b�g���W�̂��猸�炷�l�����߂�
	ret_num = FX_Mul( FX_SinIdx( (u16)rota_num ), ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_DIS << FX32_SHIFT );
	ret_num >>= FX32_SHIFT;

	// ����
	ret_num = ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_DIS - ret_num;

	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���@���W��ݒ�
 *
 *	@param	p_drawglb
 *	@param	p_drawwork
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorMoveKey_CorsorDrawSet( ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_WORK* cp_work, const ZKN_RANGE_SUB_GLB* cp_glb )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;

	// �����̍��W��ݒ肵�Ă悢���`�F�b�N
	if( ZKN_ZukanCommonSubCursorFlagGet( cp_glb->cp_zukan_common_apl ) == TRUE ){

		if( cp_work->key_set == FALSE ){
			ZKN_UTIL_CursorSetMatrix( p_draw, 
					cp_work->x, cp_work->y,
					ZKN_RANGE_SUB_CURSOR_MARK_SIZE_X, 
					ZKN_RANGE_SUB_CURSOR_MARK_SIZE_Y);
		}else{
			ZKN_UTIL_CursorSetMatrixNotAnm(  p_draw, 
					cp_work->x, cp_work->y,
					ZKN_RANGE_SUB_CURSOR_MARK_SIZE_X, 
					ZKN_RANGE_SUB_CURSOR_MARK_SIZE_Y );
		}
	}
}

