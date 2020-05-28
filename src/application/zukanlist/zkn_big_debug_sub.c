//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_big_debug_sub.c
 *	@brief		�������DEBUG�A�v��
 *	@author		tomoya takahashi
 *	@data		2006.03.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifdef PM_DEBUG

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
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_debug_zukan.h"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_big.h"

#define	__ZKN_BIG_DEBUG_DEBUG_H_GLOBAL
#include "include/application/zukanlist/zkn_big_debug_sub.h"

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
#define ZKN_BIG_DEBUG_EVENT_NUM ( 2 )	// �C�x���g��
#define ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT		(1<<0)
#define ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT_ALL	(2<<0)

#define ZKN_BIG_DEBUG_OAM_BG_PTR	( 2 )

enum{
	ZKN_BIGDEBUG_SEQINIT_ALLOC,
	ZKN_BIGDEBUG_SEQINIT_LOAD,
	ZKN_BIGDEBUG_SEQINIT_FADEIN,
	ZKN_BIGDEBUG_SEQINIT_END,
};
enum{
	ZKN_BIGDEBUG_SEQDELETE_FADEOUT_INIT,
	ZKN_BIGDEBUG_SEQDELETE_FADEOUT,
	ZKN_BIGDEBUG_SEQDELETE_RELEASE,
	ZKN_BIGDEBUG_SEQDELETE_FREE,
	ZKN_BIGDEBUG_SEQDELETE_END,
};

//-------------------------------------
//	�I������
//=====================================
enum{
	ZKN_BIGDEBUG_SELE_POKE,
	ZKN_BIGDEBUG_SELE_HERO,
	ZKN_BIGDEBUG_SELE_NUM,
};


//-------------------------------------
//	�r�b�g�}�b�v�E�B���h�E
//=====================================
enum{
	ZKN_BIGDEBUG_WND_POKEGRA_DATA,
	ZKN_BIGDEBUG_WND_HERO_DATA,
	ZKN_BIGDEBUG_WND_CONT_DATA,
	ZKN_BIGDEBUG_WND_NOW_POKE_DATA,
	ZKN_BIGDEBUG_WND_NUM
};

#define ZKN_BIGDEBUG_BMPWND_PL			( 0 )
#define ZKN_BIGDEBUG_STRNUM				( 512 )
#define ZKN_BIGDEBUG_STRNUM_KETA		( 4 )

//-------------------------------------
//	�|�P�����O���t�B�b�N�ް��p
//=====================================
#define ZKN_BIGDEBUG_POKEGRA_DATA_CX	( 1 )
#define ZKN_BIGDEBUG_POKEGRA_DATA_CY	( 18 )
#define ZKN_BIGDEBUG_POKEGRA_DATA_CSIZX	( 15 )
#define ZKN_BIGDEBUG_POKEGRA_DATA_CSIZY	( 6 )
#define ZKN_BIGDEBUG_POKEGRA_DATA_CGOFS	( 1 )

// ����
#define ZKN_BIGDEBUG_POKEHERO_NAME_X	( 0 )
#define ZKN_BIGDEBUG_POKEHERO_HIRITSU_X	( 0 )
#define ZKN_BIGDEBUG_POKEHERO_TAKASA_X	( 64 )
#define ZKN_BIGDEBUG_POKEHERO_NUM_Y		( 32 )
#define ZKN_BIGDEBUG_POKEHERO_STR_Y		( 16 )
#define ZKN_BIGDEBUG_POKEHERO_NAME_Y	( 0 )

//-------------------------------------
//	��l���ް��p
//=====================================
#define ZKN_BIGDEBUG_HERO_DATA_CX	( 16 )
#define ZKN_BIGDEBUG_HERO_DATA_CY	( 18 )
#define ZKN_BIGDEBUG_HERO_DATA_CSIZX	( 15 )
#define ZKN_BIGDEBUG_HERO_DATA_CSIZY	( 6 )
#define ZKN_BIGDEBUG_HERO_DATA_CGOFS	( 100 )

//-------------------------------------
//	������@�ް��p
//=====================================
#define ZKN_BIGDEBUG_CONT_DATA_CX	( 1 )
#define ZKN_BIGDEBUG_CONT_DATA_CY	( 0 )
#define ZKN_BIGDEBUG_CONT_DATA_CSIZX	( 20 )
#define ZKN_BIGDEBUG_CONT_DATA_CSIZY	( 18 )
#define ZKN_BIGDEBUG_CONT_DATA_CGOFS	( 200 )

//-------------------------------------
//	�ҏW���ް��p
//=====================================
#define ZKN_BIGDEBUG_NOW_POKE_DATA_CX	( 19 )
#define ZKN_BIGDEBUG_NOW_POKE_DATA_CY	( 10 )
#define ZKN_BIGDEBUG_NOW_POKE_DATA_CSIZX	( 12 )
#define ZKN_BIGDEBUG_NOW_POKE_DATA_CSIZY	( 4 )
#define ZKN_BIGDEBUG_NOW_POKE_DATA_CGOFS	( 600 )

#define ZKN_BIGDEBUG_NOW_POKE_DATA_STR_Y	( 16 )


//-------------------------------------
//	����n
//=====================================
#define ZKN_BIGDEBUG_CONT_TRG_TIME		( 16 )

#define ZKN_BIGDEBUG_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

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

	// ������׃A�v��
	ZKN_APL_DATA* p_height_apl;
} ZKN_BIG_DEBUG_GLB;

//-------------------------------------
//	�傫������׃T�u��ʉ�ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_BIG_DEBUG_DRAWGLB;

//-------------------------------------
//	������������׃T�u��ʁ@�������[�N
//=====================================
typedef struct {
	short scale[ZKN_BIGDEBUG_SELE_NUM];
	short yofs[ZKN_BIGDEBUG_SELE_NUM];

	int now_select;

	int trg_count;		// trg�{�^���ł��鶳��
} ZKN_BIG_DEBUG_WORK;

//-------------------------------------
//	������������׃T�u��ʉ�ʁ@�������[�N
//=====================================
typedef struct {
	GF_BGL_BMPWIN* p_bmp[ZKN_BIGDEBUG_WND_NUM];

	int local_now_select;

	short local_scale[ZKN_BIGDEBUG_SELE_NUM];
	short local_yofs[ZKN_BIGDEBUG_SELE_NUM];
} ZKN_BIG_DEBUG_DRAW;


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
static ZKN_BIG_DEBUG_GLB* MakeBigDebugGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_BIG_DEBUG_DRAWGLB* MakeBigDebugDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeBigDebugEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteBigDebugGlb( ZKN_BIG_DEBUG_GLB* p_glb );
static void DeleteBigDebugDrawGlb( ZKN_BIG_DEBUG_DRAWGLB* p_glb );
static void DeleteBigDebugEvent( ZKN_EVENT_DATA* p_event );


static int BigDebugEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknBigDebugProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigDebugProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigDebugProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigDebugProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigDebugProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigDebugProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// �t�F�[�h����
static void ZknBigDebugOamFadeInit( ZKN_BIG_DEBUG_DRAW* p_draw );
static void ZknBigDebugOamFadeDelete( ZKN_BIG_DEBUG_DRAW* p_draw );
static void ZknBigDebugFadeInit( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknBigDebugFadeMain( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, BOOL fadein_out );

static void ZknBigDebugObjDataReset( ZKN_BIG_DEBUG_WORK* p_work );


// �ǂݍ���
static void ZknBigDebugLoadResource( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap );
static void ZknBigDebugReleaseResource( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, int heap );


static void ZknBigDebugInitBmp( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, int heap );
static void ZknBigDebugDeleteBmp( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb );

static void ZknBigDebugDrawHeroBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap );
static void ZknBigDebugDrawPokeBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap );
static void ZknBigDebugDrawContBmp( GF_BGL_BMPWIN* p_bmp, int heap );
static void ZknBigDebugDrawSelectBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap );

static void ZknBigDebugOneParamDataPrint( GF_BGL_BMPWIN* p_bmp, short yofs, short scale, STRBUF* str, MSGDATA_MANAGER* man, STRBUF* name );

static void ZknBigDebug0xNumMake( GF_BGL_BMPWIN* p_bmp, u32 x, u32 y, STRBUF* str, u32 num, u32 keta, MSGDATA_MANAGER* man, u32 start_msg_idx );

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
void ZKN_BigDebugAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_BIG_DEBUG_GLB*	p_glb;
	ZKN_BIG_DEBUG_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeBigDebugGlb( heap, zkn_sys );
	p_drawglb = MakeBigDebugDrawGlb( heap, zkn_sys );
	p_event = MakeBigDebugEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= BigDebugEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknBigDebugProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigDebugProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigDebugProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknBigDebugProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigDebugProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigDebugProcDrawFuncDelete;
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
void ZKN_BigDebugAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteBigDebugGlb( p_data->p_glb_data ); 
	DeleteBigDebugDrawGlb( p_data->p_glb_draw ); 
	DeleteBigDebugEvent( p_data->p_event_data );
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
static ZKN_BIG_DEBUG_GLB* MakeBigDebugGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_DEBUG_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_DEBUG_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_DEBUG_GLB) );

	// �ϐ�������
	// �C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );		

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );


	// �}�Ӎ�������� �A�v��
	p_glb->p_height_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG );
	
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
static ZKN_BIG_DEBUG_DRAWGLB* MakeBigDebugDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_DEBUG_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_DEBUG_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_DEBUG_DRAWGLB) );


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
static ZKN_EVENT_DATA* MakeBigDebugEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = BigDebugEventDataNumGet();

	// �C�x���g�f�[�^�e�[�u���쐬
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeBigMain( heap, &p_event_tbl[0], zkn_sys, ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT );
	ZKN_EVENT_BigHeightDebugAplReturn( &p_event_tbl[1], zkn_sys, heap, ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT_ALL );

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
static void DeleteBigDebugGlb( ZKN_BIG_DEBUG_GLB* p_glb )
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
static void DeleteBigDebugDrawGlb( ZKN_BIG_DEBUG_DRAWGLB* p_glb )
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
static void DeleteBigDebugEvent( ZKN_EVENT_DATA* p_event )
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
static int BigDebugEventDataNumGet( void )
{
	return ZKN_BIG_DEBUG_EVENT_NUM;
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
static int ZknBigDebugProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_DEBUG_GLB* p_glb = p_glbdata;
	ZKN_BIG_DEBUG_WORK* p_work = p_dodata->p_work;
	int i;

	// ���[�N�̍쐬
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_BIG_DEBUG_WORK) );
	memset( p_work, 0, sizeof(ZKN_BIG_DEBUG_WORK) );

	ZknBigDebugObjDataReset( p_work );
	
	p_dodata->p_work = p_work;

	p_work->trg_count = ZKN_BIGDEBUG_CONT_TRG_TIME;

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
static int ZknBigDebugProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{

	ZKN_BIG_DEBUG_GLB* p_glb = p_glbdata;
	ZKN_BIG_DEBUG_WORK* p_work = p_dodata->p_work;
	
	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}


	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}


	// �g���K�[�@�R���g�@�J�E���g����
	if( sys.cont != 0 ){
		if( (p_work->trg_count - 1) >= 0 ){
			p_work->trg_count --;
		}
	}else{
		p_work->trg_count = ZKN_BIGDEBUG_CONT_TRG_TIME;
	}


	// �I���̕ύX
	if( sys.trg & PAD_BUTTON_A ){
		p_work->now_select ^= 1;
	}

	// �g���K�[���o���邩�@�`�F�b�N
	if( p_work->trg_count == 0 ){

		// �g�k
		if( sys.cont & PAD_KEY_LEFT ){
			p_work->scale[ p_work->now_select ] ++;
		}
		if( sys.cont & PAD_KEY_RIGHT ){
			p_work->scale[ p_work->now_select ] --;
		}

		// Y�ʒu
		if( sys.cont & PAD_KEY_UP ){
			p_work->yofs[ p_work->now_select ] --;
		}
		if( sys.cont & PAD_KEY_DOWN ){
			p_work->yofs[ p_work->now_select ] ++;
		}
	}else{
		// �g�k
		if( sys.trg & PAD_KEY_LEFT ){
			p_work->scale[ p_work->now_select ] ++;
		}
		if( sys.trg & PAD_KEY_RIGHT ){
			p_work->scale[ p_work->now_select ] --;
		}

		// Y�ʒu
		if( sys.trg & PAD_KEY_UP ){
			p_work->yofs[ p_work->now_select ] --;
		}
		if( sys.trg & PAD_KEY_DOWN ){
			p_work->yofs[ p_work->now_select ] ++;
		}
	}

	// ���̃|�P����
	if( sys.trg & PAD_BUTTON_L ){
		if( ZKN_GLBDATA_PokeListTblNoAdd( p_glb->p_glb, 1 ) == FALSE ){
			ZKN_GLBDATA_PokeListTblNoSet( p_glb->p_glb, 0 );
		}
		*p_glb->p_event_key |= ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT;
		ZknBigDebugObjDataReset( p_work );
	}

	// �O�̃|�P����
	if( sys.trg & PAD_BUTTON_R ){
		if( ZKN_GLBDATA_PokeListTblNoAdd( p_glb->p_glb, -1 ) == FALSE ){
			ZKN_GLBDATA_PokeListTblNoSet( p_glb->p_glb, ZKN_GLBDATA_PokeListTblNumGet( p_glb->p_glb ) - 1 );
		}
		*p_glb->p_event_key |= ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT;
		ZknBigDebugObjDataReset( p_work );
	}

	// �j��
	if( sys.trg & PAD_BUTTON_SELECT ){
		p_glb->p_glb->hero_sex ^= 1;
		*p_glb->p_event_key |= ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT;
		ZknBigDebugObjDataReset( p_work );
	}

	// �I��
	if( sys.trg & PAD_BUTTON_B ){
		*p_glb->p_event_key |= ZKN_BIG_DEBUG_EVENT_CHANGE_HEIGHT_ALL;
	}

	// �l���f
	ZKN_BigAplPokeGraScaleSet( p_glb->p_height_apl, p_work->scale[ ZKN_BIGDEBUG_SELE_POKE ] );
	ZKN_BigAplHeroGraScaleSet( p_glb->p_height_apl, p_work->scale[ ZKN_BIGDEBUG_SELE_HERO ] );
	ZKN_BigAplPokeGraYofsSet( p_glb->p_height_apl, p_work->yofs[ ZKN_BIGDEBUG_SELE_POKE ] );
	ZKN_BigAplHeroGraYofsSet( p_glb->p_height_apl, p_work->yofs[ ZKN_BIGDEBUG_SELE_HERO ] );


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
static int ZknBigDebugProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_DEBUG_GLB* p_glb = p_glbdata;
	ZKN_BIG_DEBUG_WORK* p_work = p_dodata->p_work;

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
static int ZknBigDebugProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_DEBUG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_DEBUG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DEBUG_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_DEBUG_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_BIGDEBUG_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_BIG_DEBUG_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_BIG_DEBUG_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGDEBUG_SEQINIT_LOAD:
		// Resource�ǂݍ���
		ZknBigDebugLoadResource( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );
 
		// �t�F�[�h����
		ZknBigDebugFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGDEBUG_SEQINIT_FADEIN:
		
		if( ZknBigDebugFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_BIGDEBUG_SEQINIT_END:
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
static int ZknBigDebugProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_DEBUG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_DEBUG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DEBUG_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_DEBUG_DRAW*		p_drawwork = p_drawdata->p_work;

	
	// �r�b�g�}�b�v�`��
	// �|�P�����ް�	
	if( (p_drawwork->local_scale[ ZKN_BIGDEBUG_SELE_POKE ] != cp_datawork->scale[ ZKN_BIGDEBUG_SELE_POKE ]) ||
		(p_drawwork->local_yofs[ ZKN_BIGDEBUG_SELE_POKE ] != cp_datawork->yofs[ ZKN_BIGDEBUG_SELE_POKE ]) ){
		ZknBigDebugDrawPokeBmp( p_drawwork->p_bmp[ ZKN_BIGDEBUG_WND_POKEGRA_DATA ], cp_dataglb, cp_datawork, p_drawdata->heap );

		p_drawwork->local_scale[ ZKN_BIGDEBUG_SELE_POKE ] = cp_datawork->scale[ ZKN_BIGDEBUG_SELE_POKE ];
		p_drawwork->local_yofs[ ZKN_BIGDEBUG_SELE_POKE ] = cp_datawork->yofs[ ZKN_BIGDEBUG_SELE_POKE ];
	}

	// ��l���ް�
	if( (p_drawwork->local_scale[ ZKN_BIGDEBUG_SELE_HERO ] != cp_datawork->scale[ ZKN_BIGDEBUG_SELE_HERO ]) ||
		(p_drawwork->local_yofs[ ZKN_BIGDEBUG_SELE_HERO ] != cp_datawork->yofs[ ZKN_BIGDEBUG_SELE_HERO ]) ){
		ZknBigDebugDrawHeroBmp( p_drawwork->p_bmp[ ZKN_BIGDEBUG_WND_HERO_DATA ], cp_dataglb, cp_datawork, p_drawdata->heap );

		p_drawwork->local_scale[ ZKN_BIGDEBUG_SELE_HERO ] = cp_datawork->scale[ ZKN_BIGDEBUG_SELE_HERO ];
		p_drawwork->local_yofs[ ZKN_BIGDEBUG_SELE_HERO ] = cp_datawork->yofs[ ZKN_BIGDEBUG_SELE_HERO ];
	}

	// �I���f�[�^
	if( p_drawwork->local_now_select != cp_datawork->now_select ){

		ZknBigDebugDrawSelectBmp( p_drawwork->p_bmp[ ZKN_BIGDEBUG_WND_NOW_POKE_DATA ], cp_dataglb, cp_datawork, p_drawdata->heap );
	
		p_drawwork->local_now_select = cp_datawork->now_select;
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
static int ZknBigDebugProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_DEBUG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_DEBUG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DEBUG_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_DEBUG_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_BIGDEBUG_SEQDELETE_FADEOUT_INIT:
		// �t�F�[�h����
		ZknBigDebugFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGDEBUG_SEQDELETE_FADEOUT:
		if( ZknBigDebugFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_BIGDEBUG_SEQDELETE_RELEASE:
		// Resource�ǂݍ���
		ZknBigDebugReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGDEBUG_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_BIGDEBUG_SEQDELETE_END:
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
static void ZknBigDebugOamFadeInit( ZKN_BIG_DEBUG_DRAW* p_draw )
{
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
static void ZknBigDebugOamFadeDelete( ZKN_BIG_DEBUG_DRAW* p_draw )
{
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
static void ZknBigDebugFadeInit( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknBigDebugOamFadeInit( p_draw );


	if( fadein_out ){
		// �t�F�[�h�C��
		ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
				BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_BIGDEBUG_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
	}else{
		// �t�F�[�h�A�E�g
		ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
				BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_BIGDEBUG_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
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
static BOOL ZknBigDebugFadeMain( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;

	check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade_sub );

	// �I�������I������
	if( check ){
		if( fadein_out ){
			// ������OAM�j��
			ZknBigDebugOamFadeDelete( p_draw );
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
static void ZknBigDebugLoadResource( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap )
{
	// �X�N���[��������
	GF_BGL_ClearCharSet( ZKN_BG_FRM_UTIL_S, 32, 0, heap );
	GF_BGL_ClearCharSet( ZKN_BG_FRM_BACK_S, 32, 0, heap );
	GF_BGL_ClearCharSet( ZKN_BG_FRM_AFFINE_S, 32, 0, heap );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_S );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S );
	
	
	// �r�b�g�}�b�v��
	ZknBigDebugInitBmp( p_draw, p_drawglb, heap );

	// ��l���ް��\��
	ZknBigDebugDrawHeroBmp( p_draw->p_bmp[ ZKN_BIGDEBUG_WND_HERO_DATA ], cp_glb, cp_work, heap );

	// �|�P�����ް��\��
	ZknBigDebugDrawPokeBmp( p_draw->p_bmp[ ZKN_BIGDEBUG_WND_POKEGRA_DATA ], cp_glb, cp_work, heap );

	// ������@
	ZknBigDebugDrawContBmp( p_draw->p_bmp[ ZKN_BIGDEBUG_WND_CONT_DATA ], heap );

	// �ް��\��
	// �I���f�[�^
	ZknBigDebugDrawSelectBmp( p_draw->p_bmp[ ZKN_BIGDEBUG_WND_NOW_POKE_DATA ], cp_glb, cp_work, heap );
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
static void ZknBigDebugReleaseResource( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, int heap )
{
	// �r�b�g�}�b�v�ʂ̔j��
	ZknBigDebugDeleteBmp( p_draw, p_drawglb );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�`��p�E�B���h�E�쐬
 *
 *	@param	p_draw
 *	@param	p_drawglb
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugInitBmp( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb, int heap )
{
	int i;
	GF_BGL_INI* p_bg = p_drawglb->p_drawglb->p_bg;

	// �������m��
	for( i=0; i<ZKN_BIGDEBUG_WND_NUM; i++ ){
		p_draw->p_bmp[ i ] = GF_BGL_BmpWinAllocGet( heap, 1 );
	}


	// �̈�m��
	// �߹����ް�
	GF_BGL_BmpWinAdd( p_bg, p_draw->p_bmp[ ZKN_BIGDEBUG_WND_POKEGRA_DATA ],
			ZKN_BG_FRM_BACK_S,
			ZKN_BIGDEBUG_POKEGRA_DATA_CX, ZKN_BIGDEBUG_POKEGRA_DATA_CY,
			ZKN_BIGDEBUG_POKEGRA_DATA_CSIZX, ZKN_BIGDEBUG_POKEGRA_DATA_CSIZY,
			ZKN_BIGDEBUG_BMPWND_PL, ZKN_BIGDEBUG_POKEGRA_DATA_CGOFS );

	// ��l���ް�
	GF_BGL_BmpWinAdd( p_bg, p_draw->p_bmp[ ZKN_BIGDEBUG_WND_HERO_DATA ],
			ZKN_BG_FRM_BACK_S,
			ZKN_BIGDEBUG_HERO_DATA_CX, ZKN_BIGDEBUG_HERO_DATA_CY,
			ZKN_BIGDEBUG_HERO_DATA_CSIZX, ZKN_BIGDEBUG_HERO_DATA_CSIZY,
			ZKN_BIGDEBUG_BMPWND_PL, ZKN_BIGDEBUG_HERO_DATA_CGOFS );

	// ������@�ް�
	GF_BGL_BmpWinAdd( p_bg, p_draw->p_bmp[ ZKN_BIGDEBUG_WND_CONT_DATA ],
			ZKN_BG_FRM_BACK_S,
			ZKN_BIGDEBUG_CONT_DATA_CX, ZKN_BIGDEBUG_CONT_DATA_CY,
			ZKN_BIGDEBUG_CONT_DATA_CSIZX, ZKN_BIGDEBUG_CONT_DATA_CSIZY,
			ZKN_BIGDEBUG_BMPWND_PL, ZKN_BIGDEBUG_CONT_DATA_CGOFS );

	// �ҏW���ް�
	GF_BGL_BmpWinAdd( p_bg, p_draw->p_bmp[ ZKN_BIGDEBUG_WND_NOW_POKE_DATA ],
			ZKN_BG_FRM_BACK_S,
			ZKN_BIGDEBUG_NOW_POKE_DATA_CX, ZKN_BIGDEBUG_NOW_POKE_DATA_CY,
			ZKN_BIGDEBUG_NOW_POKE_DATA_CSIZX, ZKN_BIGDEBUG_NOW_POKE_DATA_CSIZY,
			ZKN_BIGDEBUG_BMPWND_PL, ZKN_BIGDEBUG_NOW_POKE_DATA_CGOFS );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��l���ް��\��
 *
 *	@param	p_bmp
 *	@param	cp_glb
 *	@param	cp_work
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugDrawHeroBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	STRBUF* name = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_zukan_dat, heap);

	GF_BGL_BmpWinDataFill( p_bmp, 0 );

	// ��l���ް���������
	if( ZKN_GLBDATA_HeroSexGet( cp_glb->p_glb ) == 0 ){
		MSGMAN_GetString( man, DEBUG_ZUKAN_20, name );
	}else{
		MSGMAN_GetString( man, DEBUG_ZUKAN_03, name );
	}
	ZknBigDebugOneParamDataPrint( p_bmp, 
		cp_work->yofs[ZKN_BIGDEBUG_SELE_HERO], cp_work->scale[ZKN_BIGDEBUG_SELE_HERO],
		str, man, name );
	
	GF_BGL_BmpWinOn( p_bmp );

	STRBUF_Delete(name);
	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����ް��\��
 *
 *	@param	p_bmp
 *	@param	cp_glb
 *	@param	cp_work
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugDrawPokeBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_zukan_dat, heap);
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	STRBUF* mons_name = MSGDAT_UTIL_GetMonsName( monsno, heap );

	GF_BGL_BmpWinDataFill( p_bmp, 0 );

	// �|�P�����ް���������
	ZknBigDebugOneParamDataPrint( p_bmp, 
		cp_work->yofs[ZKN_BIGDEBUG_SELE_POKE], cp_work->scale[ZKN_BIGDEBUG_SELE_POKE],
		str, man, mons_name );

	GF_BGL_BmpWinOn( p_bmp );

	STRBUF_Delete(mons_name);
	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	������@�\��
 *
 *	@param	p_bmp
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugDrawContBmp( GF_BGL_BMPWIN* p_bmp, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_zukan_dat, heap);

	GF_BGL_BmpWinDataFill( p_bmp, 0 );

	// ������@
	MSGMAN_GetString( man, DEBUG_ZUKAN_02, str );
	GF_STR_PrintColor( p_bmp,
			FONT_SYSTEM, str, 0, 0, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	GF_BGL_BmpWinOn( p_bmp );

	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I����@�\��
 *
 *	@param	p_bmp
 *	@param	cp_glb
 *	@param	cp_work
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugDrawSelectBmp( GF_BGL_BMPWIN* p_bmp, const ZKN_BIG_DEBUG_GLB* cp_glb, const ZKN_BIG_DEBUG_WORK* cp_work, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	STRBUF* name = STRBUF_Create(ZKN_BIGDEBUG_STRNUM, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_zukan_dat, heap);
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	STRBUF* mons_name = MSGDAT_UTIL_GetMonsName( monsno, heap );

	GF_BGL_BmpWinDataFill( p_bmp, 0 );

	if( ZKN_GLBDATA_HeroSexGet( cp_glb->p_glb ) == 0 ){
		MSGMAN_GetString( man, DEBUG_ZUKAN_20, name );
	}else{
		MSGMAN_GetString( man, DEBUG_ZUKAN_03, name );
	}

	// �I�𒆂̂���
	if( cp_work->now_select == ZKN_BIGDEBUG_SELE_POKE ){
		GF_STR_PrintColor( p_bmp,
				FONT_SYSTEM, mons_name, 0, 0, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	}else{
		GF_STR_PrintColor( p_bmp,
				FONT_SYSTEM, name, 0, 0, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	}

	// �ւ񂵂イ���イ
	MSGMAN_GetString( man, DEBUG_ZUKAN_21, str );
	GF_STR_PrintColor( p_bmp,
			FONT_SYSTEM, str, 0, ZKN_BIGDEBUG_NOW_POKE_DATA_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	GF_BGL_BmpWinOn( p_bmp );

	STRBUF_Delete(str);
	STRBUF_Delete(mons_name);
	STRBUF_Delete(name);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�E�B���h�E�̔j��
 *
 *	@param	p_draw
 *	@param	p_drawglb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugDeleteBmp( ZKN_BIG_DEBUG_DRAW* p_draw, ZKN_BIG_DEBUG_DRAWGLB* p_drawglb )
{
	int i;

	// �j��
	for( i=0; i<ZKN_BIGDEBUG_WND_NUM; i++ ){
		GF_BGL_BmpWinOff( p_draw->p_bmp[ i ] );
		GF_BGL_BmpWinDel( p_draw->p_bmp[ i ] );
		GF_BGL_BmpWinFree( p_draw->p_bmp[ i ], 1 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����Ǝ�l�����ް���\������֐�
 *
 *	@param	p_bmp		�r�b�g�}�b�v�E�B���h�E
 *	@param	yofs		�\���f�[�^�P
 *	@param	scale		�\���f�[�^�Q
 *	@param	str			�g�p����STRBUF
 *	@param	man			�g�p���郁�b�Z�[�W�}�l�[�W��
 *	@param	name		�\�����閼�O
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugOneParamDataPrint( GF_BGL_BMPWIN* p_bmp, short yofs, short scale, STRBUF* str, MSGDATA_MANAGER* man, STRBUF* name )
{
	// �Ȃ܂�
	GF_STR_PrintColor( p_bmp,
			FONT_SYSTEM, name, ZKN_BIGDEBUG_POKEHERO_NAME_X, ZKN_BIGDEBUG_POKEHERO_NAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	
	// �Ђ��
	MSGMAN_GetString( man, DEBUG_ZUKAN_00, str );
	GF_STR_PrintColor( p_bmp,
			FONT_SYSTEM, str, ZKN_BIGDEBUG_POKEHERO_HIRITSU_X, ZKN_BIGDEBUG_POKEHERO_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
		
	// �Ђ�̐���
	ZknBigDebug0xNumMake( p_bmp, ZKN_BIGDEBUG_POKEHERO_HIRITSU_X, ZKN_BIGDEBUG_POKEHERO_NUM_Y, str, (u32)scale, ZKN_BIGDEBUG_STRNUM_KETA, man, DEBUG_ZUKAN_04 );

	// ������
	MSGMAN_GetString( man, DEBUG_ZUKAN_01, str );
	GF_STR_PrintColor( p_bmp,
			FONT_SYSTEM, str, ZKN_BIGDEBUG_POKEHERO_TAKASA_X, ZKN_BIGDEBUG_POKEHERO_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// �������̐���
	ZknBigDebug0xNumMake( p_bmp, ZKN_BIGDEBUG_POKEHERO_TAKASA_X, ZKN_BIGDEBUG_POKEHERO_NUM_Y, str, (u32)yofs, ZKN_BIGDEBUG_STRNUM_KETA, man, DEBUG_ZUKAN_04 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	16�i���̐������쐬
 *
 *	@param	p_bmp	�������ރr�b�g�}�b�v
 *	@param	x		�����W�@�i�h�b�g�j
 *	@param	y		�����W	�i�h�b�g�j
 *	@param	str		������o�b�t�@
 *	@param	num		����
 *	@param	keta	��
 *	@param	man		���b�Z�[�W�}�l�[�W��
 *	@param	start_msg_idx	���b�Z�[�W���ޯ��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigDebug0xNumMake( GF_BGL_BMPWIN* p_bmp, u32 x, u32 y, STRBUF* str, u32 num, u32 keta, MSGDATA_MANAGER* man, u32 start_msg_idx )
{
	int i;
	int draw_num;

	for( i=0; i<keta; i++ ){

		draw_num = num % 0x10;


		MSGMAN_GetString( man, start_msg_idx + draw_num, str );
		
		GF_STR_PrintColor( p_bmp,
				FONT_SYSTEM, str, 
				x + (((keta - 1) - i)*9), y,
				0, ZKN_BG_FONT_COLOR_MSK, NULL );

		num /= 16;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g�k�l�@Y���W������
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigDebugObjDataReset( ZKN_BIG_DEBUG_WORK* p_work )
{
	p_work->scale[ ZKN_BIGDEBUG_SELE_POKE ] = 0x100;
	p_work->scale[ ZKN_BIGDEBUG_SELE_HERO ] = 0x100;
	p_work->yofs[ ZKN_BIGDEBUG_SELE_POKE ] = 0;
	p_work->yofs[ ZKN_BIGDEBUG_SELE_HERO ] = 0;
}

#endif // PM_DEBUG


