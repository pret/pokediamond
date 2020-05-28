//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_common.c
 *	@brief		�}�Ӌ���
 *	@author		tomoya takahashi 
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/system/brightness.h"
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/gflib/calctool.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_zukan.h"
#include "include/application/zukanlist/zkn_zukan_graver.h"
#include "include/application/zukanlist/zkn_zukan_textver.h"
#include "include/application/zukanlist/zkn_range.h"
#include "include/application/zukanlist/zkn_sound.h"
#include "include/application/zukanlist/zkn_big_sub.h"
#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_cursor.h"


// �G�t�F�N�g�ō��W��Link�����邽�߁A�d���Ȃ��C���N���[�h
#include "include/application/zukanlist/zkn_pokelist.h"
#include "include/application/zukanlist/zkn_pokelist_sub.h"


#define	__ZKN_ZUKAN_COMMON_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan_common.h"

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
#define ZKN_ZUKAN_COMMON_EVENT_NUM ( 8 )	// �C�x���g��
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_POKELIST	( 0x1 << 1 )	// �|�P�������X�g�ɕύX
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_ZUKAN	( 0x1 << 2 )		// �}�ӂ�
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_RANGE	( 0x1 << 3 )		// ���z��
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_SOUND	( 0x1 << 4 )		// ��������
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG	( 0x1 << 5 )		// �傫����ׂ�
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_HEIGHT	( 0x1 << 6 )		// �傫����ׂ�
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_WEIGHT	( 0x1 << 7 )		// �傫����ׂ�
#define ZKN_ZUKAN_COMMON_EVENT_CHANGE_GRAPHIC	( 0x1 << 8 )		// �傫����ׂ�

#define ZKN_ZUKAN_COMMON_RESOBJ_NUM			( 4 )		// ���\�[�X�I�u�W�F�i�[�̈搔

#define ZKN_ZUKAN_COMMON_ICON_Y			( 8 * FX32_ONE )
#define ZKN_ZUKAN_COMMON_ICON_X			( 168 * FX32_ONE )
#define ZKN_ZUKAN_COMMON_ICON_X_ADD		( 24 * FX32_ONE )


#define ZKN_ZUKAN_COMMON_ICON_SEQ		( 0 )	// ICON�A�j���V�[�P���X


// �^�C�g��
#define ZKN_ZUKAN_TITLE_DRAW_X		( 16 )
#define ZKN_ZUKAN_TITLE_DRAW_Y		( 0 )
#define ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CX	(8)
#define ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CY	(2)

//-------------------------------------
//	�A�v���P�[�V�����f�[�^
//=====================================
enum{
	ZKN_ZUKAN_COMMON_APL_ZUKAN00,
	ZKN_ZUKAN_COMMON_APL_RANGE,
	ZKN_ZUKAN_COMMON_APL_SOUND,
	ZKN_ZUKAN_COMMON_APL_BIG,
	ZKN_ZUKAN_COMMON_APL_GRAPHIC,
	ZKN_ZUKAN_COMMON_APL_NUM,
};

//-------------------------------------
//	�}�ӕ`�揉�����V�[�P���X
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SEQINIT_ALLOC,
	ZKN_ZUKAN_COMMON_SEQINIT_LOAD,
	ZKN_ZUKAN_COMMON_SEQINIT_FADEIN,
	ZKN_ZUKAN_COMMON_SEQINIT_END,
};

//-------------------------------------
//	�}�ӕ`��j���V�[�P���X
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKAN_COMMON_SEQDELETE_FADEOUT,
	ZKN_ZUKAN_COMMON_SEQDELETE_RELEASE,
	ZKN_ZUKAN_COMMON_SEQDELETE_FREE,
	ZKN_ZUKAN_COMMON_SEQDELETE_END,
};



//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�}�Ӌ��ʉ�ʁ@�O���[�o���ϐ�
//=====================================
typedef struct _ZKN_ZUKAN_COMMON_GLB{
	int*				p_event_key;		// �C�x���g�L�[
	ZKN_GLB_DATA*		p_glb;				// �O���[�o���f�[�^
	int					now_apply;			// ���̃A�v���P�[�V����
	ZKN_POKELIST_GLB_DATA* p_pokelist_glb;	// �|�P�������X�g�O���[�o��
	ZKN_ZUKAN_GLB*		p_zkn_data_glb;		// �}�Ӄf�[�^�O���[�o���f�[�^
	ZKN_APL_DATA* p_zkn_datagraver_glb;		// �}�ӃO���t�B�b�Nver�̃O���[�o��
	ZKN_APL_DATA* p_zkn_datatextver_glb;	// �}�ӌ���ver�̃O���[�o��
	ZKN_APL_DATA* p_range_glb;				// ���z�}�̃O���[�o��
	ZKN_APL_DATA* p_sound_glb;				// �������̃O���[�o��
	ZKN_APL_DATA* p_big_sub_glb;			// �d����׃T�u���
	
	BOOL sub_apply_brightness_on;	// �T�u�A�v���Ƀu���C�g�l�X�g�p������
	BOOL fade_mode;		// TREU	�����̃u���C�g�l�X FALSE	�������ݒ肠��
	BOOL pal_load_flag;	// �p���b�g�ǂݍ��݃t���O
} ZKN_ZUKAN_COMMON_GLB;

//-------------------------------------
//	�}�Ӌ��ʉ��	�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// �`��O���[�o���f�[�^
} ZKN_ZUKAN_COMMON_DRAWGLB;


//-------------------------------------
//	�}�Ӌ��ʉ�ʁ@�������[�N
//=====================================
typedef struct {
	int dummy;
} ZKN_ZUKAN_COMMON_WORK;

//-------------------------------------
//	�}�Ӌ��ʉ�ʁ@�`�惏�[�N
//=====================================
typedef struct{
//	CLACT_WORK_PTR icon;		// �A�C�R��
	int local_apl_tmp;			// ���̃A�C�R�����\������Ă���A�v���ʒu

	ZKN_FONTOAM_DATA* p_title[ZKN_ZUKAN_COMMON_APL_NUM];	// �^�C�g���t�H���gOAM
	
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_ZUKAN_COMMON_RESOBJ_NUM ];	// Resource�I�u�W�F�|�C���^

} ZKN_ZUKAN_COMMON_DRAW;

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
static ZKN_ZUKAN_COMMON_GLB* MakeZukanCommonGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKAN_COMMON_DRAWGLB* MakeZukanCommonDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeZukanCommonEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanCommonGlb( ZKN_ZUKAN_COMMON_GLB* p_glb );
static void DeleteZukanCommonDrawGlb( ZKN_ZUKAN_COMMON_DRAWGLB* p_glb );
static void DeleteZukanCommonEvent( ZKN_EVENT_DATA* p_event );


static int ZukanCommonEventDataNumGet( void );

//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknZukanCommonProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanCommonProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanCommonProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

static void ZknZukanCommonProcDoFuncMainInit( ZKN_ZUKAN_COMMON_GLB* p_glb );
// �A�v���P�[�V�����ύX
static BOOL ZknZukanCommonGetFadeModeOther( int apply );
static BOOL ZknZukanCommonChangeApply( ZKN_ZUKAN_COMMON_GLB* p_glb, int apply, int last_apply );
static void ZknZukanCommonResetMainApply( ZKN_ZUKAN_COMMON_GLB* p_glb );
static void ZknZukanCommonChangePokeList( ZKN_ZUKAN_COMMON_GLB* p_glb );
static void ZknZukanCommon_MainChangePokelist( ZKN_ZUKAN_COMMON_GLB* p_glb );

// ���\�[�X�ǂݍ���
static void ZknZukanCommonLoadResource( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, const ZKN_ZUKAN_COMMON_GLB* cp_glb, int heap );
static void ZknZukanCommonDeleteResource( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw );
static void ZknZukanCommonSetUpBg( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_GLB* cp_glb, int heap );
static void ZknZukanCommonLoadCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap );
static void ZknZukanCommonReleaseCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw );
static void ZknZukanCommonAddCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap );
static void ZknZukanCommonDeleteCell( ZKN_ZUKAN_COMMON_DRAW* p_draw );
static void ZknZukanCommonIconMatSet( ZKN_ZUKAN_COMMON_DRAW* p_draw, int apl );
static void ZknZukanCommonAddFontOam( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap );
static void ZknZukanCommonDeleteFontOam( ZKN_ZUKAN_COMMON_DRAW* p_draw );

static void ZknZukanCommonFontOamChg( ZKN_ZUKAN_COMMON_DRAW* p_draw, int apl, int old_apl  );

static void ZknZukanCommonOamFadeInit( ZKN_ZUKAN_COMMON_DRAW* p_draw );
static void ZknZukanCommonOamFadeDelete( ZKN_ZUKAN_COMMON_DRAW* p_draw );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�A�v���쐬
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
void ZKN_ZukanCommonAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKAN_COMMON_GLB*		p_glb;
	ZKN_ZUKAN_COMMON_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanCommonGlb( heap, zkn_sys );
	p_drawglb = MakeZukanCommonDrawGlb( heap, zkn_sys );
	p_event = MakeZukanCommonEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanCommonEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanCommonProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanCommonProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanCommonProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanCommonProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanCommonProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanCommonProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g	�@���j���[�A�v���j��
 *
 *	@param	p_data	�A�v���P�[�V�����f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanCommonAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanCommonGlb( p_data->p_glb_data ); 
	DeleteZukanCommonDrawGlb( p_data->p_glb_draw ); 
	DeleteZukanCommonEvent( p_data->p_event_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�u���C�g�l�X���悤�t���O�`�F�b�N
 *	
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@retval	TRUE	�g�p����
 *	@retval	FALSE	�g�p�s�\
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanCommonBrightnessOnFlagGet( const ZKN_APL_DATA* cp_glb )
{
	const ZKN_ZUKAN_COMMON_GLB * cp_glbdata = cp_glb->p_glb_data;
	return cp_glbdata->sub_apply_brightness_on;
}



//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_COMMON_GLB* MakeZukanCommonGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_COMMON_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_COMMON_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_COMMON_GLB) );

	// main��ʂ���̃C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMainCommon( zkn_sys ); 

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// �ŏ��̃A�v���P�[�V����
	p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_ZUKAN00;

	// �}�ӃO���[�o���f�[�^
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN );
	p_glb->p_zkn_data_glb = p_apl->p_glb_data;

	// �}�ӃO���t�B�b�N�o�[�W�����O���[�o���f�[�^
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_GRA );
	p_glb->p_zkn_datagraver_glb = p_apl;

	// �}�ӌ���o�[�W�����O���[�o���f�[�^
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_TEXT );
	p_glb->p_zkn_datatextver_glb = p_apl;

	// ���z�O���[�o���f�[�^
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_RANGE );
	p_glb->p_range_glb = p_apl;

	// �������O���[�o���f�[�^
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_SOUND );
	p_glb->p_sound_glb = p_apl;

	// �d����׃T�u��ʃO���[�o���f�[�^
	p_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_BIG );
	p_glb->p_big_sub_glb = p_apl;

	// �|�P�������X�g�O���[�o���f�[�^
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_POKELIST );
	p_glb->p_pokelist_glb = p_apl->p_glb_data;


	// �t�F�[�h���[�h�擾
	p_glb->fade_mode = TRUE;
	
	// �p���b�g�ǂݍ��݃t���O
	p_glb->pal_load_flag = TRUE;
	
	return p_glb;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�`��O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�Ӄf�[�^
 *
 *	@return	�`��O���[�o���f�[�^
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_COMMON_DRAWGLB* MakeZukanCommonDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_COMMON_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_COMMON_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_COMMON_DRAWGLB) );

	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeZukanCommonEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = ZukanCommonEventDataNumGet();

	// �C�x���g�f�[�^�e�[�u���쐬
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangePokeList( heap, &p_event_tbl[0], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_POKELIST );
	ZKN_EVENT_MakeChangeZukanOnly( heap, &p_event_tbl[1], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_ZUKAN );
	ZKN_EVENT_MakeChangeRange( heap, &p_event_tbl[2], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_RANGE );
	ZKN_EVENT_MakeChangeSound( heap, &p_event_tbl[3], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_SOUND );
	ZKN_EVENT_MakeChangeBig( heap, &p_event_tbl[4], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG );
	ZKN_EVENT_MakeChangeBigMain( heap, &p_event_tbl[5], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_HEIGHT );
	ZKN_EVENT_MakeChangeBigWeightMain( heap, &p_event_tbl[6], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_WEIGHT );

	ZKN_EVENT_MakeChangeZukanGraphic( heap, &p_event_tbl[7], zkn_sys, ZKN_ZUKAN_COMMON_EVENT_CHANGE_GRAPHIC );

	return p_event_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonGlb( ZKN_ZUKAN_COMMON_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�`��O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonDrawGlb( ZKN_ZUKAN_COMMON_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );
	ZKN_EVENT_DeleteData( &p_event[1] );
	ZKN_EVENT_DeleteData( &p_event[2] );
	ZKN_EVENT_DeleteData( &p_event[3] );
	ZKN_EVENT_DeleteData( &p_event[4] );
	ZKN_EVENT_DeleteData( &p_event[5] );
	ZKN_EVENT_DeleteData( &p_event[6] );
	ZKN_EVENT_DeleteData( &p_event[7] );

	sys_FreeMemoryEz( p_event );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʃA�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	�}�Ӌ��ʃA�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZukanCommonEventDataNumGet( void )
{
	return ZKN_ZUKAN_COMMON_EVENT_NUM;
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
static int ZknZukanCommonProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_WORK*	p_work = p_dodata->p_work;

	// �|�P�����̐���炷
	p_glb->p_zkn_data_glb->mons_snd_req = TRUE;
	
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
static int ZknZukanCommonProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_WORK*	p_work = p_dodata->p_work;

	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// seq0 == ������
	if( p_dodata->seq == 0 ){
		ZknZukanCommonProcDoFuncMainInit( p_glb );
		p_dodata->seq++;
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
static int ZknZukanCommonProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_WORK*	p_work = p_dodata->p_work;

	// �A�v���P�[�V����������
	p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_ZUKAN00;
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
static int ZknZukanCommonProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_GLB* cp_glb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_DRAW*		p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_ZUKAN_COMMON_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_ZUKAN_COMMON_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKAN_COMMON_DRAW) );
		p_drawwork = p_drawdata->p_work;
		p_drawwork->local_apl_tmp = cp_glb->now_apply;	// ���\�����̈ʒu
		p_drawdata->seq ++;
		break;
		
	case ZKN_ZUKAN_COMMON_SEQINIT_LOAD:
		ZknZukanCommonLoadResource( p_drawglb, p_drawwork, cp_glb, p_drawdata->heap );
		// ������OAM�ݒ�
		ZknZukanCommonOamFadeInit( p_drawwork );

		// ������OAM�ɂ���΁A�t�F�[�h�C���A�E�g����ݒ�Ńu���C�g�l�X�t�F�[�h
		ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_LONG_COMMON,
				BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_BRIGHTNESS_MSK_ALL, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SEQINIT_FADEIN:
		if( ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_SEQINIT_END:
		// ������OAM�ݒ����
		ZknZukanCommonOamFadeDelete( p_drawwork );
		return ZKN_PROC_TRUE;

	default:
		GF_ASSERT(0);
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
static int ZknZukanCommonProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_GLB* cp_glb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_DRAW*		p_drawwork = p_drawdata->p_work;


	// �A�v���P�[�V�������ς������A�C�R���̕\���ʒu��ύX
	if( p_drawwork->local_apl_tmp != cp_glb->now_apply ){
		ZknZukanCommonIconMatSet( p_drawwork, cp_glb->now_apply );
		ZknZukanCommonFontOamChg( p_drawwork, cp_glb->now_apply, p_drawwork->local_apl_tmp );
		p_drawwork->local_apl_tmp = cp_glb->now_apply;
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
static int ZknZukanCommonProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_GLB* cp_glb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_ZUKAN_COMMON_SEQDELETE_FADEOUT_INIT:
		// �傫����׏d����ׂ̂��߂����̃u���b�N�t�F�[�h���[�h���쐬
		if( cp_glb->fade_mode ){
			
			// ������OAM�ݒ�
			ZknZukanCommonOamFadeInit( p_drawwork );
			
			
			// ������OAM�ɂ���΁A�t�F�[�h�C���A�E�g����ݒ�Ńu���C�g�l�X�t�F�[�h
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_LONG_COMMON,

					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_BRIGHTNESS_MSK_ALL, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�C���A�E�g����ݒ�őS�ău���C�g�l�X�t�F�[�h
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_LONG_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, PLANEMASK_ALL, 0, ZKN_UTIL_FADE_MAIN );
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SEQDELETE_FADEOUT:
		if( ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_SEQDELETE_RELEASE:
		ZknZukanCommonDeleteResource( p_drawglb, p_drawwork );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SEQDELETE_FREE:		
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SEQDELETE_END:
		return ZKN_PROC_TRUE;
			
	default:
		GF_ASSERT(0);
		break;
	}

	return ZKN_PROC_FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�ɖ߂鎞�̏����@�����̏������p�b�N
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommon_MainChangePokelist( ZKN_ZUKAN_COMMON_GLB* p_glb )
{
	ZknZukanCommonChangePokeList( p_glb );

	p_glb->pal_load_flag = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P���X�g�ɖ߂�Ƃ��̏���
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonChangePokeList( ZKN_ZUKAN_COMMON_GLB* p_glb )
{
	// �C�x���g���s
	// �|�P���X�g�ɕ���
	*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_POKELIST;
	
	// ���̃V�X�e���̉��œ����S�ẴA�v���̃u���C�g�l�X
	// �g�p�������Ȃ�
	p_glb->sub_apply_brightness_on = FALSE;

	// �}�ӂ̃t�F�[�h��ނ�����������
	p_glb->p_zkn_data_glb->fade_mode = ZKN_ZUKAN_FADE_MODE_CHPOKELIST;	
	ZKN_ZukanTextverFadeModeSet( p_glb->p_zkn_datatextver_glb, ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST );


	// ���C���œ��삵�Ă�����̂̃t�F�[�h�A�E�g����
	switch( p_glb->now_apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		p_glb->p_zkn_data_glb->poke_gra_move_x = ZKN_POKELIST_POKEGRA_X;
		p_glb->p_zkn_data_glb->poke_gra_move_y = ZKN_POKELIST_POKEGRA_Y;

		ZKN_ZukanTextverPokeGraFadeOutSet( p_glb->p_zkn_datatextver_glb, ZKN_POKELIST_POKEGRA_X, ZKN_POKELIST_POKEGRA_Y );
		p_glb->p_pokelist_glb->fade_zukan_data = TRUE;	// �}��->pokelist�G�t�F�N�g

		// �t�F�[�h���[�h
		p_glb->fade_mode = TRUE;	// �������ݒ�OAM�t�F�[�h
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_OTHER );
		ZKN_RangeFadeModeSync( p_glb->p_range_glb, ZKN_FADE_SYNC_LONG_COMMON );
		ZKN_RangePokeGraFadeOutSet( p_glb->p_range_glb, ZKN_POKELIST_POKEGRA_X, ZKN_POKELIST_POKEGRA_Y );
		p_glb->p_pokelist_glb->fade_zukan_data = TRUE;	// �}��->pokelist

		// �t�F�[�h���[�h
		p_glb->fade_mode = TRUE;	// �������ݒ�OAM�t�F�[�h
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_OTHER );
		ZKN_SoundFadeModeSync( p_glb->p_sound_glb, ZKN_FADE_SYNC_LONG_COMMON );
		ZKN_SoundPokeGraFadeOutSet( p_glb->p_sound_glb, ZKN_POKELIST_POKEGRA_X, ZKN_POKELIST_POKEGRA_Y );
		p_glb->p_pokelist_glb->fade_zukan_data = TRUE;	// �}��->pokelist

		// �t�F�[�h���[�h
		p_glb->fade_mode = TRUE;	// �������ݒ�OAM�t�F�[�h
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:
		p_glb->p_pokelist_glb->fade_zukan_data = FALSE;	// �ʏ�

		// �t�F�[�h���[�h
		p_glb->fade_mode = FALSE;	// �S�̃u���C�g�l�X�t�F�[�h
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:
		p_glb->p_pokelist_glb->fade_zukan_data = FALSE;	// �ʏ�
		// �t�F�[�h���[�h
		p_glb->fade_mode = FALSE;	// �S�̃u���C�g�l�X�t�F�[�h
		break;

	default:
		break;
	}
}

// �t�F�[�h���[�h�������[�ɂ��邩�`�F�b�N
static BOOL ZknZukanCommonGetFadeModeOther( int apply )
{
// �S�����u���b�N�t�F�[�h�ɂ���		03/16
	
/*	if( (apply != ZKN_ZUKAN_COMMON_APL_BIG) &&
		(apply != ZKN_ZUKAN_COMMON_APL_GRAPHIC) ){
		return TRUE;
	}//*/

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�v���P�[�V�����ύX
 *
 *	@param	p_glb
 *	@param	apply
 *	@param	last_apply 
 *
 *	@retval	TRUE	�ύX���܂�
 *	@retval FALSE	�ύX���܂���
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanCommonChangeApply( ZKN_ZUKAN_COMMON_GLB* p_glb, int apply, int last_apply )
{
	int pokegra_x, pokegra_y;
	BOOL ret = TRUE;

	switch( apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		if( ZknZukanCommonGetFadeModeOther( last_apply ) ){
			p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_OTHER;
		}else{
			p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_NORMAL;
		}
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_ZUKAN;
		p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_ZUKAN00;
		pokegra_x = ZKN_ZUKAN_POKEGRA_MAT_X;
		pokegra_y = ZKN_ZUKAN_POKEGRA_MAT_Y;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		if( ZknZukanCommonGetFadeModeOther( last_apply ) ){
			ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_OTHER );
			ZKN_RangeFadeModeSync( p_glb->p_range_glb, ZKN_FADE_SYNC_COMMON );
		}else{
			ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_MY );
		}
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_RANGE;
		p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_RANGE;
		pokegra_x = ZKN_RANGE_POKEGRA_DRAW_X;
		pokegra_y = ZKN_RANGE_POKEGRA_DRAW_Y;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		if( ZknZukanCommonGetFadeModeOther( last_apply ) ){
			ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_OTHER );
			ZKN_SoundFadeModeSync( p_glb->p_sound_glb, ZKN_FADE_SYNC_COMMON );
		}else{
			ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_MY );
		}
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_SOUND;
		p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_SOUND;
		pokegra_x = ZKN_SOUND_POKEGRA_DRAW_X;
		pokegra_y = ZKN_SOUND_POKEGRA_DRAW_Y;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:

		// �ߊl�����|�P�������`�F�b�N
		if( ZKN_GLBDATA_PokeMonsTypeGet( p_glb->p_glb ) == ZKN_POKELIST_TYPE_GET ){
			*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG;
			p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_BIG;
		}else{
			ret = FALSE;
		}
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:

		// �O���t�B�b�N���[�h�ɂȂ��Ă��邩�`�F�b�N
		if( ZKN_GLBDATA_PokeGraphicVersionFlagGet( p_glb->p_glb ) == TRUE ){
			*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_GRAPHIC;
			p_glb->now_apply = ZKN_ZUKAN_COMMON_APL_GRAPHIC;
		}else{
			ret = FALSE;
		}
		break;
		
	default:
		// ��������
		GF_ASSERT(0);
		break;
	}

	switch( last_apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		if( ZknZukanCommonGetFadeModeOther( apply ) ){
			p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_OTHER;
			ZKN_ZukanTextverFadeModeSet( p_glb->p_zkn_datatextver_glb, ZKK_ZUKANTEXTVER_FADE_MODE_OTHER );
		}else{
			p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_NORMAL;
			ZKN_ZukanTextverFadeModeSet( p_glb->p_zkn_datatextver_glb, ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL );
		}
		p_glb->p_zkn_data_glb->poke_gra_move_x = pokegra_x;
		p_glb->p_zkn_data_glb->poke_gra_move_y = pokegra_y;
		ZKN_ZukanTextverPokeGraFadeOutSet( p_glb->p_zkn_datatextver_glb, pokegra_x, pokegra_y );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		if( ZknZukanCommonGetFadeModeOther( apply ) ){
			ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_OTHER );
			ZKN_RangeFadeModeSync( p_glb->p_range_glb, ZKN_FADE_SYNC_COMMON );
		}else{
			ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_MY );
		}
		ZKN_RangePokeGraFadeOutSet( p_glb->p_range_glb, pokegra_x, pokegra_y );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		if( ZknZukanCommonGetFadeModeOther( apply ) ){
			ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_OTHER );
			ZKN_SoundFadeModeSync( p_glb->p_sound_glb, ZKN_FADE_SYNC_COMMON );
		}else{
			ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_MY );
		}
		ZKN_SoundPokeGraFadeOutSet( p_glb->p_sound_glb, pokegra_x, pokegra_y );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:
		break;
		
	default:
		// ��������
		GF_ASSERT(0);
		break;
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C����ʂ݂̂̕ύX
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonResetMainApply( ZKN_ZUKAN_COMMON_GLB* p_glb )
{
	// �u���C�g�l�X�g�p������
	p_glb->sub_apply_brightness_on = TRUE;


	switch( p_glb->now_apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		ZKN_ZukanTextverFadeModeSet( p_glb->p_zkn_datatextver_glb, ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL );
		p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_NORMAL;
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_ZUKAN;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		ZKN_RangeFadeModeSet( p_glb->p_range_glb, ZKN_RANGE_FADE_MODE_MY );
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_RANGE;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_MY );
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_SOUND;
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:
		// �����d����׃`�F�b�N
		if( ZKN_BigSubNowAplTypeGet( p_glb->p_big_sub_glb ) == ZKN_BIGSUB_CONTROL_HEIGHT ){
			*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_HEIGHT;
		}else{
			*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_BIG_WEIGHT;
		}
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:
/*		ZKN_SoundFadeModeSet( p_glb->p_sound_glb, ZKN_SOUND_FADE_MODE_MY );
		*p_glb->p_event_key |= ZKN_ZUKAN_COMMON_EVENT_CHANGE_SOUND;//*/
		break;
		
	default:
		// ��������
		GF_ASSERT(0);
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	Resource�ǂݍ���
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	p_draw		�`�惏�[�N
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonLoadResource( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, const ZKN_ZUKAN_COMMON_GLB* cp_glb, int heap )
{
	// BG�ǂݍ���
	ZknZukanCommonSetUpBg( p_drawglb, cp_glb, heap );
	
	// OAM�ǂݍ���
	ZknZukanCommonLoadCell( p_drawglb, p_draw, heap );

	// �Z���A�N�^�[�o�^
	ZknZukanCommonAddCell( p_drawglb, p_draw, heap );

	// FONTOAM
	ZknZukanCommonAddFontOam( p_drawglb, p_draw, heap );
	ZknZukanCommonFontOamChg( p_draw, ZKN_ZUKAN_COMMON_APL_ZUKAN00, ZKN_ZUKAN_COMMON_APL_RANGE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Resource�j��
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	p_draw		�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonDeleteResource( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw )
{
	ZknZukanCommonDeleteCell( p_draw );
	ZknZukanCommonReleaseCell( p_drawglb, p_draw );
	ZknZukanCommonDeleteFontOam( p_draw );

	// ���[�e�B���e�B�ʃX�N���[���f�[�^������
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�ʃZ�b�g�A�b�v
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSetUpBg( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �p���b�g�f�[�^�]��
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_NCLR, PALTYPE_MAIN_BG, 0, 0, heap );

	// �S���}�ӂ̎��͐F��ς���
	if( ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_glb ) == ZKN_MODE_ZENKOKU ){
		ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_zen_NCLR, PALTYPE_MAIN_BG, 0, 32, heap );
	}
	
	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main2_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z��Resource�ǂݍ���
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonLoadCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main1_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_main1_lzh_NCGR + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_data_oam1_NCLR, FALSE, 
			NARC_zukan_zkn_data_oam1_NCLR + ZKN_ZUKAN_COMMON_RES_ID_OFS, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_ZUKAN_COMMON_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main1_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_main1_lzh_NCER + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_main1_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_main1_lzh_NANR + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMResource�f�[�^�j��
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	p_draw		�`��f�[�^
 *
 *	@return	none	
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonReleaseCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw )
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
 *	@brief	�Z���A�N�^�[�o�^
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	p_draw		�`��f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonAddCell( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap )
{
/*	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_main1_lzh_NCGR + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			NARC_zukan_zkn_data_oam1_NCLR + ZKN_ZUKAN_COMMON_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_main1_lzh_NCER + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			NARC_zukan_zkn_data_oam_main1_lzh_NANR + ZKN_ZUKAN_COMMON_RES_ID_OFS,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 0;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// �A�C�R����o�^
	add.mat.x = 0;
	add.mat.y = 0;
	p_draw->icon = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->icon, ZKN_ZUKAN_COMMON_ICON_SEQ );

	// ���W�ݒ�
	ZknZukanCommonIconMatSet( p_draw, p_draw->local_apl_tmp );//*/
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
static void ZknZukanCommonDeleteCell( ZKN_ZUKAN_COMMON_DRAW* p_draw )
{
//	CLACT_Delete( p_draw->icon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�o�^
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	p_draw		�`�惏�[�N
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonAddFontOam( ZKN_ZUKAN_COMMON_DRAWGLB* p_drawglb, ZKN_ZUKAN_COMMON_DRAW* p_draw, int heap )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	ZKN_FONTOAM_INIT fontoam_init;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// �p���b�g�A�h���X
	int	i;
		

	// �������f�[�^�̋��ʕ������쐬
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( p_draw->res_obj[ CLACT_U_PLTT_RES ], NULL );
	fontoam_init.x			 = ZKN_ZUKAN_TITLE_DRAW_X;
	fontoam_init.y			 = ZKN_ZUKAN_TITLE_DRAW_Y;
	fontoam_init.bg_pri		 = 0;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.parent		 = NULL;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DMAIN );

	for( i=0; i<ZKN_ZUKAN_COMMON_APL_NUM; i++ ){
		
		// �r�b�g�}�b�v�E�B���h�E�쐬
		win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
				ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CX,
				ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CY );

		// comment
		ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
				NARC_msg_zkn_dat,ZNK_TITLE_00 + i, 0, 0 );
		fontoam_init.p_bmp		 = win;
		p_draw->p_title[ i ] = ZKN_FONTOAM_Make( &fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->p_title[ i ]->p_fontoam, pltt_ofs );
		FONTOAM_SetDrawFlag( p_draw->p_title[ i ]->p_fontoam, FALSE );

		// �r�b�g�}�b�v�E�B���h�E�j��
		ZKN_FONTOAM_DeleteBmp( win );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonDeleteFontOam( ZKN_ZUKAN_COMMON_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKAN_COMMON_APL_NUM; i++ ){
		ZKN_FONTOAM_Delete( p_draw->p_title[ i ] );
	}	
}


//----------------------------------------------------------------------------
/**
 *	@brief	�A�v���i���o�[�̍��W�ɐݒ�
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	apl		�A�v���i���o�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonIconMatSet( ZKN_ZUKAN_COMMON_DRAW* p_draw, int apl )
{
/*	VecFx32 mat;

	mat.x = ZKN_ZUKAN_COMMON_ICON_X + (ZKN_ZUKAN_COMMON_ICON_X_ADD * apl);
	mat.y = ZKN_ZUKAN_COMMON_ICON_Y;

	CLACT_SetMatrix( p_draw->icon, &mat );//*/
}


//----------------------------------------------------------------------------
/**
 *	@brief	���C���֐�������
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonProcDoFuncMainInit( ZKN_ZUKAN_COMMON_GLB* p_glb )
{
	// �u���C�g�l�X�g�p������
	p_glb->sub_apply_brightness_on = TRUE;

	// �A�v���t�F�[�h���[�h�ݒ�
	p_glb->p_zkn_data_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_NORMAL;
}





//-----------------------------------------------------------------------------
/**
 *			�T�u���
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define ZKN_ZUKAN_COMMON_SUB_EVENT_NUM ( 0 )	// �C�x���g��

//-------------------------------------
//	���샂�[�h
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_MODE_CLOSE,
	ZKN_ZUKAN_COMMON_SUB_MODE_OPEN,
};


//-------------------------------------
//	�T�u��ʏ������V�[�P���X
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_SEQINIT_ALLOC,
	ZKN_ZUKAN_COMMON_SUB_SEQINIT_LOAD,
	ZKN_ZUKAN_COMMON_SUB_SEQINIT_FADEIN_INIT,
	ZKN_ZUKAN_COMMON_SUB_SEQINIT_FADEIN,
	ZKN_ZUKAN_COMMON_SUB_SEQINIT_END,
};

//-------------------------------------
//	�T�u��ʔj���V�[�P���X
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FADEOUT,
	ZKN_ZUKAN_COMMON_SUB_SEQDELETE_RELEASE,
	ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FREE,
	ZKN_ZUKAN_COMMON_SUB_SEQDELETE_END,
};


//-------------------------------------
//	�T�u�R�����{�^����	�����[�h
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_BUTTON_CLOSE,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_CLOSE_NUM,
};
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_CLOSE_R	( 32 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_CLOSE_X	( 128 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_CLOSE_Y	( 96 )


//-------------------------------------
//	�T�u�R�����{�^����
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK,
	ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM,
};
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX		( 40 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY		( 32 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_Y			( 24 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA_X		( 28 )	
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK_X		( 228 )	
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE_X		( 68 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND_X		( 108 )	
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG_X		( 148 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC_X	( 188 )


// FONTOAM
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_BMP_SIZE_CX	( 8 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_BMP_SIZE_CY	( 2 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_OFS_3_X		( -20 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_OFS_4_X		( -24 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_OFS_Y		( -6 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_PLTOFS	( 0 )
#define ZKN_ZUKAN_COMMON_SUB_BUTTONFONT_PUSHPLTOFS	( 1 )

//-------------------------------------
//	�J�[�\���f�[�^
//=====================================
enum{
	ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA  = ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE = ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND = ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG   = ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC  = ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK  = ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK,

	ZKN_ZUKAN_COMMON_SUB_CURSOR_NUM,
};
enum{
	ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA_X  = ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA_X,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE_X = ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE_X,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND_X = ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND_X,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG_X   = ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG_X,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC_X   = ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC_X,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK_X  = ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK_X,

	ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA_Y  = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,
	ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE_Y = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND_Y = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG_Y   = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC_Y = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,	
	ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK_Y  = ZKN_ZUKAN_COMMON_SUB_BUTTON_Y,
};
#define ZKN_ZUKAN_COMMMON_SUB_CURSOR_MAX_X	( ZKN_ZUKAN_COMMON_SUB_CURSOR_NUM )
#define ZKN_ZUKAN_COMMMON_SUB_CURSOR_MAX_Y	( 1 )
#define ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX		( 24 )
#define ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY		( 16 )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�}�Ӌ��ʉ�ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	int*				p_event_key;		// �C�x���g�L�[
	ZKN_ZUKAN_COMMON_GLB* p_main_common_glb;// ���C����ʃR�����O���[�o���f�[�^
	ZKN_GLB_DATA* p_glb;					// �O���[�o���f�[�^
	int button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM ];	// �{�^���C�x���g�f�[�^

	BOOL sub_apply_brightness_on;	// �T�u�A�v���Ƀu���C�g�l�X�g�p������

	int sub_common_sub_mode_flag;	// common�̉��œ����A�v�������삵�Ă悢�����샂�[�h

	BOOL back_key_push;				// �߂�{�^���̋@�\�́A�L�[�ł��o����̂ŃA�j���𓯊������邽��

	BOOL sub_cursor_flag;	// �J�[�\��������T�u�A�v�����s���̂����ʃA�v�����s���̂�
} ZKN_ZUKAN_COMMON_SUB_GLB;

//-------------------------------------
//	�}�Ӌ��ʉ�ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// �`��O���[�o���f�[�^
} ZKN_ZUKAN_COMMON_SUB_DRAWGLB;

//-------------------------------------
//	�{�^���p���[�N
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_ZUKAN_COMMON_SUB_BUTTON_WORK;


//-------------------------------------
//	�}�Ӌ��ʉ�ʁ@�������[�N
//=====================================
typedef struct {
	// �{�^���}�l�[�W��
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// �{�^���f�[�^
	ZKN_ZUKAN_COMMON_SUB_BUTTON_WORK button_work;
	int button_cancel_flg;


	// �J�[�\���V�X�e��
	ZKN_CURSOR* p_cursor;
	ZKN_CURSOR_ONEDATA* p_cursor_tbl;
} ZKN_ZUKAN_COMMON_SUB_WORK;

//-------------------------------------
//	�}�Ӌ��ʉ�ʁ@�`��������[�N
//=====================================
typedef struct {
	CLACT_WORK_PTR clact[ ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM ];

	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_ZUKAN_COMMON_RESOBJ_NUM ];	// Resource�I�u�W�F�|�C���^
} ZKN_ZUKAN_COMMON_SUB_DRAW;


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
static ZKN_ZUKAN_COMMON_SUB_GLB* MakeZukanCommonSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKAN_COMMON_SUB_DRAWGLB* MakeZukanCommonSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeZukanCommonSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanCommonSubGlb( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void DeleteZukanCommonSubDrawGlb( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_glb );
static void DeleteZukanCommonSubEvent( ZKN_EVENT_DATA* p_event );

static int ZukanCommonSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknZukanCommonSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanCommonSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanCommonSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanCommonSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// �A�v���P�[�V�����ύX����
static BOOL ZknZukanCommonSubApplyChange( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int apply, int last_apply );

// �{�^������
static void ZknZukanCommonSubButtonMake( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int heap );
static void ZknZukanCommonSubButtonEventBuffInit( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZukanCommonSubButtonMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZukanCommonSubButtonDelete( ZKN_ZUKAN_COMMON_SUB_WORK* p_work );
static void ZknZukanCommonSubButtonCallBack( u32 button_no, u32 event, void* p_work );

// �J�[�\������
static void ZknZukanCommonSubCursorMake( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int heap );
static void ZknZukanCommonSubCursorMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZukanCommonSubCursorDelete( ZKN_ZUKAN_COMMON_SUB_WORK* p_work );

static void ZknZukanCommonSubCursorInit( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZukanCommonSubCursorKeyMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
	
static void ZknZukanCommonSubCursorDrawInit( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb );
static void ZknZukanCommonSubCursorDrawPack( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb );
static void ZknZukanCommonSubCursorDraw( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work );
static BOOL ZknZukanCommonSubCursorOnOff( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb,  BOOL flag );


static void ZknZukanCommonSubProcDoFuncMainMain( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZukanCommonSubOtherDoMain( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );
static void ZknZUkanCommonSubKeyFlagReset( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb );


// Resource�ǂݍ��ݏ���
static void ZknZukanCommonSubResourceLoad( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb, int heap );
static void ZknZukanCommonSubResourceDelete( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb );
static void ZknZukanCommonSubSetUpBG( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb, int heap );
static void ZknZukanCommonSubLoadOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanCommonSubReleaseOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb );

// �Z���A�N�^�[�o�^
static void ZknZukanCommonSubAddClact( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanCommonSubDeleteClact( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw );

// �O���t�B�b�N�p�^�[���{�^���̕`��ONOFF
static void ZknZukanCommonSubSetGraVerButtonDrawFlag( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb );

// FONTOAM�쐬
static void ZknZukanCommonSubAddFontOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanCommonSubDeleteFontOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�A�v���쐬
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
void ZKN_ZukanCommonSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKAN_COMMON_SUB_GLB*	p_glb;
	ZKN_ZUKAN_COMMON_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanCommonSubGlb( heap, zkn_sys );
	p_drawglb = MakeZukanCommonSubDrawGlb( heap, zkn_sys );
	p_event = MakeZukanCommonSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanCommonSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanCommonSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanCommonSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanCommonSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanCommonSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanCommonSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanCommonSubProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g	�@���j���[�A�v���j��
 *
 *	@param	p_data	�A�v���P�[�V�����f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanCommonSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanCommonSubGlb( p_data->p_glb_data ); 
	DeleteZukanCommonSubDrawGlb( p_data->p_glb_draw ); 
	DeleteZukanCommonSubEvent( p_data->p_event_data );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�u���C�g�l�X���悤�t���O�`�F�b�N
 *	
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@retval	TRUE	�g�p����
 *	@retval	FALSE	�g�p�s�\
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanCommonSubBrightnessOnFlagGet( const ZKN_APL_DATA* cp_glb )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB * cp_glbdata = cp_glb->p_glb_data;
	return cp_glbdata->sub_apply_brightness_on;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���삵�Ă悢���`�F�b�N
 *
 *	@param	cp_glb	�A�v���P�[�V�����f�[�^
 *
 *	@retval	TRUE	����OK
 *	@retval	FALSE	����NG
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanCommonSubMoveFlagGet( const ZKN_APL_DATA* cp_glb )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB * cp_glbdata = cp_glb->p_glb_data;
	
	return cp_glbdata->sub_common_sub_mode_flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\�����삵�Ă悢���`�F�b�N
 *
 *	@param	cp_glb	�A�v���P�[�V�����f�[�^
 *
 *	@retval	TRUE	����OK
 *	@retval	FALSE	����NG
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanCommonSubCursorFlagGet( const ZKN_APL_DATA* cp_glb )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB * cp_glbdata = cp_glb->p_glb_data;
	
	return cp_glbdata->sub_cursor_flag;
}


//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_COMMON_SUB_GLB* MakeZukanCommonSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_COMMON_SUB_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_COMMON_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_COMMON_SUB_GLB) );

	// �C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSubCommon( zkn_sys );		

	// ���C����ʃR�����O���[�o���f�[�^
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );
	p_glb->p_main_common_glb = p_apl->p_glb_data;							

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�`��O���[�o���f�[�^
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_COMMON_SUB_DRAWGLB* MakeZukanCommonSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_COMMON_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_COMMON_SUB_DRAWGLB) );


	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeZukanCommonSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonSubGlb( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�`��O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonSubDrawGlb( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʁ@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanCommonSubEvent( ZKN_EVENT_DATA* p_event )
{
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӌ��ʃA�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	�}�Ӌ��ʃA�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZukanCommonSubEventDataNumGet( void )
{
	return ZKN_ZUKAN_COMMON_SUB_EVENT_NUM;
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
static int ZknZukanCommonSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_SUB_WORK* p_work = p_dodata->p_work;
	int i;
	// ���[�N�̍쐬
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_ZUKAN_COMMON_SUB_WORK) );
	memset( p_work, 0, sizeof(ZKN_ZUKAN_COMMON_SUB_WORK) );


	// �{�^���J�[�\�����쐬
	ZknZukanCommonSubButtonMake( p_work, p_glb, p_dodata->heap );
	ZknZukanCommonSubCursorMake( p_work, p_glb, p_dodata->heap );
	ZknZukanCommonSubCursorInit( p_work, p_glb );


	// �{�^���C�x���g�f�[�^
	for( i=0; i<ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM; i++ ){
		p_glb->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;	// �{�^���C�x���g�f�[�^
	}


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
static int ZknZukanCommonSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_SUB_WORK* p_work = p_dodata->p_work;


	// �I����
	if( p_dodata->end_req == TRUE ){
		// �T�u�A�v���̃u���C�g�l�X�g�p��񋖉�
		p_glb->sub_apply_brightness_on = FALSE;

		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// seq==0������
	if( p_dodata->seq == 0 ){
		// �T�u�A�v���̃u���C�g�l�X�g�p������
		p_glb->sub_apply_brightness_on = TRUE;

		// �p���b�g�ǂݍ��ݍς�
		p_glb->p_main_common_glb->pal_load_flag = FALSE;

		// ����t���O�ݒ�
		p_glb->sub_common_sub_mode_flag = TRUE;	// ���싖��

		
		p_dodata->seq++;
	}else{

		// �������򓮍�
		ZknZukanCommonSubProcDoFuncMainMain( p_glb );

		// �J�[�\�������C���A�v���@�T�u�A�v���ɑ�����������򏈗�
		ZknZukanCommonSubCursorKeyMove( p_work, p_glb );

		// �{�^���C�x���g�o�b�t�@������
		ZknZukanCommonSubButtonEventBuffInit( p_glb );

		// �J�[�\������
		if( (ZKN_GLBDATA_TouchCursorFlagGet( p_glb->p_glb ) == TRUE) &&
			(p_glb->sub_cursor_flag == FALSE) ){

			ZknZukanCommonSubCursorMove( p_work, p_glb );
		}

		// �{�^������
		ZknZukanCommonSubButtonMove( p_work, p_glb );
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
static int ZknZukanCommonSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_COMMON_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_COMMON_SUB_WORK* p_work = p_dodata->p_work;

	// �{�^���J�[�\���j��
	ZknZukanCommonSubButtonDelete( p_work );
	ZknZukanCommonSubCursorDelete( p_work );
	

	// ���[�N�j��
	sys_FreeMemoryEz( p_dodata->p_work );
	p_dodata->p_work = NULL;
	
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
 */
//-----------------------------------------------------------------------------
static int ZknZukanCommonSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_ZUKAN_COMMON_SUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof( ZKN_ZUKAN_COMMON_SUB_DRAW ) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKAN_COMMON_SUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SUB_SEQINIT_LOAD:

		//�@���[�h�`�F�b�N
		ZknZukanCommonSubResourceLoad( p_drawwork, p_drawglb, cp_dataglb,  p_drawdata->heap );

		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SUB_SEQINIT_FADEIN_INIT:
		ChangeBrightnessRequest( ZKN_FADE_SYNC_LONG_COMMON,
				BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_SUB_DISPLAY );

		// �J�[�\��������
		ZknZukanCommonSubCursorDrawInit( p_drawglb, cp_datawork, cp_dataglb );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SUB_SEQINIT_FADEIN:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_SUB_SEQINIT_END:
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
 */
//-----------------------------------------------------------------------------
static int ZknZukanCommonSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_SUB_DRAW*		p_drawwork = p_drawdata->p_work;
	int i;		// ���[�v�p

	// �{�^������
	for( i=0; i<ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM; i++ ){
		ZKN_UTIL_ButtonMove( p_drawwork->clact[ i ],
				cp_dataglb->button_event[ i ] );
	}
	
	// �J�[�\������
	ZknZukanCommonSubCursorDrawPack( p_drawglb, cp_datawork, cp_dataglb );
	
	
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
 */
//-----------------------------------------------------------------------------
static int ZknZukanCommonSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_COMMON_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_COMMON_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_COMMON_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_COMMON_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
		
	case ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FADEOUT_INIT:
		ChangeBrightnessRequest( ZKN_FADE_SYNC_LONG_COMMON,
				BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_SUB_DISPLAY );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FADEOUT:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_ZUKAN_COMMON_SUB_SEQDELETE_RELEASE:
		ZknZukanCommonSubResourceDelete( p_drawwork, p_drawglb );

		// �J�[�\����\��
		ZKN_UTIL_CursorSetDrawFlag( &p_drawglb->p_drawglb->cursor, FALSE );
		p_drawdata->seq++;
		break;

	case ZKN_ZUKAN_COMMON_SUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_ZUKAN_COMMON_SUB_SEQDELETE_END:
		return ZKN_PROC_TRUE;	

	default:
		break;
	}
	
	return ZKN_PROC_FALSE;
}




//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���^�b�`�f�[�^�쐬
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubButtonMake( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int heap )
{
	// �e�[�u���쐬
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM );

	// �e�[�u���f�[�^�ݒ�
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );
	
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC ],
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_Y + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZY/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC_X - (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2),
			ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC_X + (ZKN_ZUKAN_COMMON_SUB_BUTTON_SIZX/2) );

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// �{�^���}�l�[�W���쐬
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM,
			ZknZukanCommonSubButtonCallBack,
			&p_work->button_work,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�C�x���g�o�b�t�@����������
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubButtonEventBuffInit( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM; i++ ){
		p_glb->button_event[ i ] = BMN_EVENT_SLIDEOUT;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^������
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubButtonMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	
	// ���łɏI���L�[��������Ă����ꍇ�A
	// �{�^���̃^�b�`�͔��f���Ȃ�
	if( p_glb->back_key_push == FALSE ){
		BMN_Main( p_work->p_button_man );
	}

	// �L�[�ŏI��镪��ɍs������I���̃{�^������������Ԃɂ���
	if( p_glb->back_key_push ){
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK ] = BMN_EVENT_RELEASE;
		}
	}

	// ���I�𒆂̃A�v���P�[�V�����̃{�^���͉������ςȂ��ɂ���
	switch( p_glb->p_main_common_glb->now_apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG ] = BMN_EVENT_RELEASE;
		}
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:
		if( p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC ] != BMN_EVENT_HOLD ){
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC ] = BMN_EVENT_RELEASE;
		}
		break;

	default:
		// ��������
		GF_ASSERT(0);
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
static void ZknZukanCommonSubButtonDelete( ZKN_ZUKAN_COMMON_SUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );

	// �e�[�u�����[�N�j��
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���C�x���g�R�[���o�b�N
 *
 *	@param	button_no	�{�^���i���o�[
 *	@param	event		�C�x���g�^�C�v
 *	@param	p_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_ZUKAN_COMMON_SUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_ZUKAN_COMMON_SUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_ZUKAN_COMMON_SUB_WORK* p_subwork = p_button_work->p_work;
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;

	// �{�^���C�x���g�i�[
	p_glb->button_event[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_TOUCH:
		p_subwork->button_cancel_flg = 0;
		break;
		
	case BMN_EVENT_HOLD:
		switch( button_no ){
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK:
			// �|�P�������X�g��ʂɖ߂�
			// �|�P�������X�g��
			ZknZukanCommon_MainChangePokelist( p_main_glb );
			// �I���ړ���
			Snd_SePlay( ZKN_SND_CANCEL );
			break;

		case ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_ZUKAN00 ){	
				ZknZukanCommonSubApplyChange( p_glb, ZKN_ZUKAN_COMMON_APL_ZUKAN00, p_main_glb->now_apply );
				
				ZknZukanCommonSubCursorInit( p_subwork, p_glb );
				// �I���ړ���
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_RANGE ){	
				ZknZukanCommonSubApplyChange( p_glb, ZKN_ZUKAN_COMMON_APL_RANGE, p_main_glb->now_apply );
				ZknZukanCommonSubCursorInit( p_subwork, p_glb );
				// �I���ړ���
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){	
				ZknZukanCommonSubApplyChange( p_glb, ZKN_ZUKAN_COMMON_APL_SOUND, p_main_glb->now_apply );
				ZknZukanCommonSubCursorInit( p_subwork, p_glb );
				// �I���ړ���
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_BIG ){	

				// �����ƕύX����邩�`�F�b�N
				if( ZknZukanCommonSubApplyChange( p_glb, ZKN_ZUKAN_COMMON_APL_BIG, p_main_glb->now_apply ) ){
					ZknZukanCommonSubCursorInit( p_subwork, p_glb );
					// �I���ړ���
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}else{
					if( p_subwork->button_cancel_flg == 0 ){
						
						if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){	// ������ʂȂ�Ȃ炳�Ȃ�
							// �L�����Z����
							Snd_SePlay( ZKN_SND_CANCEL );
						}
						p_subwork->button_cancel_flg = 1;
					}
				}
			}
			break;

		case ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_GRAPHIC ){

				// �����ƕύX����邩�`�F�b�N
				if( ZknZukanCommonSubApplyChange( p_glb, ZKN_ZUKAN_COMMON_APL_GRAPHIC, p_main_glb->now_apply ) ){
					ZknZukanCommonSubCursorInit( p_subwork, p_glb );
					// �I���ړ���
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}else{
					if( p_subwork->button_cancel_flg == 0 ){

						// �o�[�W�����A�b�v�`�F�b�N
						if( ZKN_GLBDATA_PokeGraphicVersionFlagGet( p_main_glb->p_glb ) == TRUE ){

							if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){	// ������ʂȂ�Ȃ炳�Ȃ�
								// �L�����Z����
								Snd_SePlay( ZKN_SND_CANCEL );
							}
						}

						
						p_subwork->button_cancel_flg = 0;
					}
				}
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
 *	@brief	�T�u���Resource�ǂݍ���
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	heap			�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubResourceLoad( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb, int heap )
{
	// BG�Z�b�g�A�b�v
	ZknZukanCommonSubSetUpBG( p_drawglb, cp_glb, heap );

	// OAM�Z�b�g�A�b�v
	ZknZukanCommonSubLoadOam( p_draw, p_drawglb, heap );


	// �Z���o�^
	ZknZukanCommonSubAddClact( p_draw, p_drawglb, heap );

	// FONTOAM�o�^
	ZknZukanCommonSubAddFontOam( p_draw, p_drawglb, heap );

	// �O���t�B�b�N�o�[�W�����{�^���̔�\��
	ZknZukanCommonSubSetGraVerButtonDrawFlag( p_draw, cp_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u���Resource�j��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubResourceDelete( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb )
{
	// FONTOAM�j��
	ZknZukanCommonSubDeleteFontOam( p_draw );
	
	// �Z���j��
	ZknZukanCommonSubDeleteClact( p_draw );
	
	// OAMResourcey�j��
	ZknZukanCommonSubReleaseOam( p_draw, p_drawglb );

	// ���[�e�B���e�B�ʃX�N���[���f�[�^������
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u��ʋ��ʕ���BG�Z�b�g�A�b�v
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb
 *	@param	heap		�q�[�v 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubSetUpBG( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	if( cp_glb->p_main_common_glb->pal_load_flag ){
		// �p���b�g�f�[�^�]��
		ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_NCLR, PALTYPE_SUB_BG, 0, 0, heap );

		// �S���}�ӂ̎��͐F��ς���
		if( ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_glb ) == ZKN_MODE_ZENKOKU ){
			ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_zen_NCLR, PALTYPE_SUB_BG, 0, 32, heap );
		}
	}
	

	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_S, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u���OAMResource�ǂݍ���
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�΂�
 *	@param	heap			�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubLoadOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub_lzh_NCGR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub_NCLR, FALSE, 
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NNS_G2D_VRAM_TYPE_2DSUB, 
			ZKN_ZUKAN_COMMON_PLTT_SUB_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub_lzh_NCER + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub_lzh_NANR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u���OAMResource�j��
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubReleaseOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb )
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
 *	@brief	�A�N�^�[�o�^
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubAddClact( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// �e�{�^����o�^
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub_lzh_NCGR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub_lzh_NCER + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			NARC_zukan_zkn_data_oam_sub_lzh_NANR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 32;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	add.mat.y		= (ZKN_ZUKAN_COMMON_SUB_BUTTON_Y * FX32_ONE) + SUB_SURFACE_Y;
	
	// �{�^���쐬
	for( i=0; i<ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM; i++ ){
		// �o�^���W�ݒ�
		switch( i ){
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK_X * FX32_ONE;
			break;

		case ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA_X * FX32_ONE;
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE_X * FX32_ONE;
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND_X * FX32_ONE;
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG_X * FX32_ONE;
			break;

		case ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC:
			add.mat.x		= ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC_X * FX32_ONE;
			break;
		}

		// �o�^�@�A�j���[�V�����ݒ�
		p_draw->clact[ i ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_draw->clact[ i ], i );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[�j��
 *
 *	@param	p_draw		�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubDeleteClact( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKAN_COMMON_SUB_BUTTON_NUM; i++ ){
		CLACT_Delete( p_draw->clact[i] );
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
static void ZknZukanCommonSubAddFontOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, int heap )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubDeleteFontOam( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw )
{
}


//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�C���A�E�g�̂��߂ɔ�����OAM�ɂ���
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonOamFadeInit( ZKN_ZUKAN_COMMON_DRAW* p_draw )
{
//	CLACT_ObjModeSet( p_draw->icon, GX_OAM_MODE_XLU );
	int i;

	for( i=0; i<ZKN_ZUKAN_COMMON_APL_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->p_title[ i ]->p_fontoam, GX_OAM_MODE_XLU );
	}	
}

//----------------------------------------------------------------------------
/**
 *	@brief	������OAM�ݒ��j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonOamFadeDelete( ZKN_ZUKAN_COMMON_DRAW* p_draw )
{
//	CLACT_ObjModeSet( p_draw->icon, GX_OAM_MODE_NORMAL );
	int i;

	for( i=0; i<ZKN_ZUKAN_COMMON_APL_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->p_title[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
	}	
}


//----------------------------------------------------------------------------
/**
 *	@brief	�T�u��ʃA�v���P�[�V�����ύX����
 *
 *	@param	p_glb	�O���[�o��
 *	@param	apply	�ύX�A�v���P�[�V����
 *	@param	last_apply	�O�̃A�v���P�[�V����
 *
 *	@retval	TRUE	�ύX���܂�
 *	@retval	FALSE	�ύX���܂���
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanCommonSubApplyChange( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int apply, int last_apply )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;
	BOOL ret;
	
	ret = ZknZukanCommonChangeApply( p_main_glb, apply, last_apply );
	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C���֐��@���C��
 *
 *	@param	p_glb		�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubProcDoFuncMainMain( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;

	ZknZukanCommonSubOtherDoMain( p_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���̑����ʃA�v���̃��C������
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubOtherDoMain( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;
	int last_apply;
	int next_apply;

	//�@�L�[�{�^���t���O���Z�b�g
	ZknZUkanCommonSubKeyFlagReset( p_glb );


	if( sys.trg & PAD_BUTTON_B ){
		// �|�P�������X�g��
		ZknZukanCommon_MainChangePokelist( p_main_glb );
		// �߂�L�[�{�^����������
		p_glb->back_key_push = TRUE;
		// �L�����Z����
		Snd_SePlay( ZKN_SND_CANCEL );
		return;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L�[�{�^���t���O���Z�b�g
 *
 *	@param	p_glb 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZUkanCommonSubKeyFlagReset( ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	// �߂�L�[�{�^������������������
	p_glb->back_key_push = FALSE;

}


//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���f�[�^�쐬
 *	
 *	@param	p_work	���[�N
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorMake( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb, int heap )
{
	int move_mode;

	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * ZKN_ZUKAN_COMMON_SUB_CURSOR_NUM );

	// �J�[�\���ړ��f�[�^�ݒ�
	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA );

	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE );

	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND );

	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG );

	if( ZKN_GLBDATA_PokeGraphicVersionFlagGet( p_glb->p_glb ) == TRUE ){
		move_mode = ZKN_CURSOR_MOVE_NORMAL;
	}else{
		move_mode = ZKN_CURSOR_MOVE_SKIP;
	}
	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			move_mode,
			move_mode,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC );

	ZKN_CURSOR_SetOneData( 
			&p_work->p_cursor_tbl[ ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK ],
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK_X, 
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK_Y,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZX,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_SIZY,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK );

	// �J�[�\���f�[�^�ݒ�
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_ZUKAN_COMMMON_SUB_CURSOR_MAX_X,
			ZKN_ZUKAN_COMMMON_SUB_CURSOR_MAX_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\������
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;

	// B�{�^����������Ă�������s���Ȃ�
	if( p_glb->back_key_push ){
		return ;
	}
	
	if( sys.trg & PAD_KEY_RIGHT ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_X, 1 );
//		Snd_SePlay( ZKN_SND_SELECT );
	}

	if( sys.trg & PAD_KEY_LEFT ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_X, -1 );
//		Snd_SePlay( ZKN_SND_SELECT );
	}

	// �J�[�\���ʒu�̋@�\�����s
	if( sys.trg & PAD_BUTTON_A ){

		switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
		case ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_ZUKAN00 ){
				ZknZukanCommonChangeApply( p_main_glb, ZKN_ZUKAN_COMMON_APL_ZUKAN00, p_main_glb->now_apply );
				p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_DATA ] = BMN_EVENT_HOLD;

				// �I���ړ���
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_RANGE ){
				ZknZukanCommonChangeApply( p_main_glb, ZKN_ZUKAN_COMMON_APL_RANGE, p_main_glb->now_apply );
				p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_RANGE ] = BMN_EVENT_HOLD;

				// �I���ړ���
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){
				ZknZukanCommonChangeApply( p_main_glb, ZKN_ZUKAN_COMMON_APL_SOUND, p_main_glb->now_apply );
				p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_SOUND ] = BMN_EVENT_HOLD;

				// �I���ړ���
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_BIG ){

				// �����ƕύX����邩�`�F�b�N
				if( ZknZukanCommonChangeApply( p_main_glb, ZKN_ZUKAN_COMMON_APL_BIG, p_main_glb->now_apply ) ){
					p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BIG ] = BMN_EVENT_HOLD;
	
					// �I���ړ���
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}else{

					if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){	// ������ʂȂ�Ȃ炳�Ȃ�
						// �L�����Z����
						Snd_SePlay( ZKN_SND_CANCEL );
					}
				}
			}
			break;

		case ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC:
			if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_GRAPHIC ){
				// �����ƕύX����邩�`�F�b�N
				if( ZknZukanCommonChangeApply( p_main_glb, ZKN_ZUKAN_COMMON_APL_GRAPHIC, p_main_glb->now_apply ) ){
					p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC ] = BMN_EVENT_HOLD;	
	
					// �I���ړ���
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}else{

					if( p_main_glb->now_apply != ZKN_ZUKAN_COMMON_APL_SOUND ){	// ������ʂȂ�Ȃ炳�Ȃ�
						// �L�����Z����
						Snd_SePlay( ZKN_SND_CANCEL );
					}
				}
			}
			break;
			
		case ZKN_ZUKAN_COMMON_SUB_CURSOR_BACK:
			// �|�P�������X�g��
			ZknZukanCommon_MainChangePokelist( p_main_glb );
			// �߂�L�[�{�^����������
			p_glb->back_key_push = TRUE;
			p_glb->button_event[ ZKN_ZUKAN_COMMON_SUB_BUTTON_BACK ] = BMN_EVENT_HOLD;
			// �L�����Z����
			Snd_SePlay( ZKN_SND_CANCEL );
			break;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���f�[�^�j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorDelete( ZKN_ZUKAN_COMMON_SUB_WORK* p_work )
{
	sys_FreeMemoryEz( p_work->p_cursor_tbl );
	ZKN_CURSOR_Free( p_work->p_cursor );
	p_work->p_cursor = NULL;
	p_work->p_cursor_tbl = NULL;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\������������
 *
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorInit( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;

	// �J�[�\���̑���͋��ʃA�v���i�����j������
	p_glb->sub_cursor_flag = FALSE;

	switch( p_main_glb->now_apply ){
	case ZKN_ZUKAN_COMMON_APL_ZUKAN00:
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, ZKN_ZUKAN_COMMON_SUB_CURSOR_DATA );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_RANGE:
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, ZKN_ZUKAN_COMMON_SUB_CURSOR_RANGE );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_SOUND:
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, ZKN_ZUKAN_COMMON_SUB_CURSOR_SOUND );
		break;
		
	case ZKN_ZUKAN_COMMON_APL_BIG:
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, ZKN_ZUKAN_COMMON_SUB_CURSOR_BIG );
		break;

	case ZKN_ZUKAN_COMMON_APL_GRAPHIC:
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, ZKN_ZUKAN_COMMON_SUB_CURSOR_GRAPHIC );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\�������̃��C���T�u��؂�ւ���
 *
 *	@param	p_work	�@���[�N
 *	@param	p_glb	�@�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorKeyMove( ZKN_ZUKAN_COMMON_SUB_WORK* p_work, ZKN_ZUKAN_COMMON_SUB_GLB* p_glb )
{
	ZKN_ZUKAN_COMMON_GLB* p_main_glb = p_glb->p_main_common_glb;


	// �ȉ��̃A�v���̂Ƃ��̓T�u�A�v�����J�[�\�����삵�Ȃ�
	if( (p_main_glb->now_apply == ZKN_ZUKAN_COMMON_APL_ZUKAN00) ){
		return ;
	}
	
	// ���ǂ������̑���ɑΉ����Ă���̂��`�F�b�N
	if( (p_glb->sub_cursor_flag == FALSE) ){
		
		// ���ʃA�v�������삵�Ă���
		if( sys.trg & PAD_KEY_DOWN ){
			p_glb->sub_cursor_flag = TRUE;
		}
	}else{

		// �T�u�A�v�������삵�Ă���
		if( sys.trg & PAD_KEY_UP ){
			p_glb->sub_cursor_flag = FALSE;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\��������
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_work		�f�[�^���[�N
 *	@param	cp_glb		�f�[�^�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorDrawInit( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb )
{
	// �J�[�\�����������W�ݒ�
	ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( cp_work->p_cursor, p_drawglb->p_drawglb );
	// �J�[�\������
	ZknZukanCommonSubCursorDrawPack( p_drawglb, cp_work, cp_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���`�揈���p�b�N�֐�
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_work		�f�[�^���[�N
 *	@param	cp_glb		�f�[�^�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorDrawPack( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb )
{
	BOOL check;
	
	//�@�\���n�m�n�e�e�ƃJ�[�\������
	if( (ZKN_GLBDATA_TouchCursorFlagGet( cp_glb->p_glb ) == TRUE) ){

		check = ZknZukanCommonSubCursorOnOff( p_drawglb, TRUE );

		// �������J�[�\���𓮂����ėǂ��Ƃ��̂ݓ��삳����
		if( (cp_glb->sub_cursor_flag == FALSE) ){

			if( check ){
				// �ĕ`�悳�ꂽ�Ƃ���,�J�[�\���`����W��������
				// �J�[�\�����������W�ݒ�
				ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( cp_work->p_cursor, p_drawglb->p_drawglb );
			}

			ZknZukanCommonSubCursorDraw( p_drawglb, cp_work );
		}
	}else{
		ZknZukanCommonSubCursorOnOff( p_drawglb, FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӃJ�[�\���`�揈��
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	p_work		�f�[�^���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubCursorDraw( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_COMMON_SUB_WORK* cp_work )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	ZKN_UTIL_CursorSetMatrixCursorSys( cp_work->p_cursor, p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���`��ONOFF
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	flag	ONOFF�t���O
 *	
 *	@retval	TRUE	�l�ύX
 *	@retval	FALSE	�ύX���Ȃ�����
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanCommonSubCursorOnOff( ZKN_ZUKAN_COMMON_SUB_DRAWGLB* p_drawglb,  BOOL flag )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	if( ZKN_UTIL_CursorGetDrawFlag( &p_draw->cursor ) != flag ){
		ZKN_UTIL_CursorSetDrawFlag( &p_draw->cursor, flag );
		return TRUE;
	}
	
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄt�H���gOAM�ύX
 *
 *	@param	p_draw
 *	@param	apl		�A�v�����ް
 *	@param	old_apl	1�O�̃A�v��
 * 
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonFontOamChg( ZKN_ZUKAN_COMMON_DRAW* p_draw, int apl, int old_apl  )
{
	FONTOAM_SetDrawFlag( p_draw->p_title[ old_apl ]->p_fontoam, FALSE );
	FONTOAM_SetDrawFlag( p_draw->p_title[ apl ]->p_fontoam, TRUE );
}

// �O���t�B�b�N�p�^�[���{�^���̕`��ONOF
//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�o�[�W�����{�^���̕\��ONOFF
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	cp_glb		�O���[�o���ް�
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanCommonSubSetGraVerButtonDrawFlag( ZKN_ZUKAN_COMMON_SUB_DRAW* p_draw, const ZKN_ZUKAN_COMMON_SUB_GLB* cp_glb )
{
	if( ZKN_GLBDATA_PokeGraphicVersionFlagGet( cp_glb->p_glb ) == FALSE ){
		CLACT_SetDrawFlag( p_draw->clact[ ZKN_ZUKAN_COMMON_SUB_BUTTON_GRAPHIC ], FALSE );
	}
}
