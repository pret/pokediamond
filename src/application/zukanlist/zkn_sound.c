//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sound.c
 *	@brief		�������A�v���P�[�V����
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/system/snd_tool.h"


#include "include/gflib/display.h"
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
#include "include/application/zukanlist/zkn_sound_sub.h"

#define	__ZKN_SOUND_H_GLOBAL
#include "include/application/zukanlist/zkn_sound.h"


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
#define ZKN_SOUND_EVENT_NUM ( 0 )	// �C�x���g��
//#define ZKN_SOUND_EVENT_CHANGE_BIG ( 0x1 << 0 )	// �傫������ׂ�

#define ZKN_SOUND_OAM_BG_PRI	(0)
#define ZKN_SOUND_OAM_PRI	(17)

//-------------------------------------
//	�V�[�P���X
//=====================================
enum{
	ZKN_SOUND_SEQINIT_ALLOC,
	ZKN_SOUND_SEQINIT_LOAD,
	ZKN_SOUND_SEQINIT_FADEIN,
	ZKN_SOUND_SEQINIT_END,
};
enum{
	ZKN_SOUND_SEQDELETE_FADEOUT_INIT,
	ZKN_SOUND_SEQDELETE_FADEOUT,
	ZKN_SOUND_SEQDELETE_RELEASE,
	ZKN_SOUND_SEQDELETE_FREE,
	ZKN_SOUND_SEQDELETE_END,
};



// �g�`�f�[�^�`��
#define ZKN_SOUND_DRAW_BMP_ONE_SIZE_X	( 1 )
#define ZKN_SOUND_DRAW_BMP_ONE_SIZE_Y	( 1 )
#define ZKN_SOUND_DRAW_BMP_Y_MAX		( 32 )
#define ZKN_SOUND_DRAW_BMP_DEF_Y		( 151 )
#define ZKN_SOUND_DRAW_BMP_PL_TBL		(9)
#define ZKN_SOUND_DRAW_BMP_PL			(6)


// �g�`�f�[�^�X�N���[��
#define ZKN_SOUND_SCRL_BMP_SPEED	( 4 )


// �_�O���t
#define ZKN_SOUND_GRAPH_NUM			( 9 )		// �O���t�̉��v�f��
#define ZKN_SOUND_GRAPH_ZANZOU_NUM	( 9 )		// �c���̏c�v�f��
#define ZKN_SOUND_GRAPH_MAT_DEF_X	( 112 )
#define ZKN_SOUND_GRAPH_MAT_DEF_Y	( 96 )
#define ZKN_SOUND_GRAPH_MAT_OFS_X	( 16 )
#define ZKN_SOUND_GRAPH_MAT_OFS_Y	( -8 )
#define ZKN_SOUND_GRAPH_DES_COUNT	( 2 )
#define ZKN_SOUND_GRAPH_DOWN_COUNT	( 16 )

// �t�F�[�h�p
#define ZKN_SOUND_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	��������ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	int*				p_event_key;		// �C�x���g�L�[
	ZKN_GLB_DATA*		p_glb;				// �O���[�o���f�[�^

	// ���C���R�����O���[�o��
	ZKN_APL_DATA*	p_main_common;	// �A�v���f�[�^

	// �T�u�T�E���h�A�v���f�[�^
	ZKN_APL_DATA*	p_sub_sound;	// �A�v���f�[�^
} ZKN_SOUND_GLB;

//-------------------------------------
//	��������ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// �`��O���[�o���f�[�^

	int pokegra_move_x;
	int pokegra_move_y;

	int fade_mode;		// �t�F�[�h���[�h
	int fade_sync;		// �t�F�[�h�V���N��
} ZKN_SOUND_DRAWGLB;


//-------------------------------------
//	��������ʁ@�������[�N
//=====================================
typedef struct {
	// �����f�[�^
	const SNDWaveData* cp_snd_data;
	int tick;
	int data_num;
	u8 snd_graph_data[ ZKN_SOUND_GRAPH_NUM ];

} ZKN_SOUND_WORK;

//-------------------------------------
//	�O���t�c���f�[�^
//=====================================
typedef struct {
	CLACT_WORK_PTR act;
	int dess_count;		// ��\���J�E���^
} ZKN_GRAPH_ZANZOU;

//-------------------------------------
//	�O���t�擪
//=====================================
typedef struct {
	CLACT_WORK_PTR act;
	int level;			// �����郌�x��
	int down_count;	// ������܂ł̃J�E���^

} ZKNGRAPH_TOP;


//-------------------------------------
//	�O���t�P�v�f�f�[�^
//=====================================
typedef struct {
	ZKN_GRAPH_ZANZOU zanzou[ ZKN_SOUND_GRAPH_ZANZOU_NUM ];
	ZKNGRAPH_TOP	top;
} ZKN_GRAPH_ONE_DATA;


//-------------------------------------
//	��������ʁ@�������[�N
//=====================================
typedef struct {
	// �|�P�O���t�F�[�h�p���샏�[�N
	ZKN_UTIL_MOVE_WORK pokegra_move;

	// �O���t�f�[�^
	ZKN_GRAPH_ONE_DATA snd_graph_act[ ZKN_SOUND_GRAPH_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// BMP�X�N���[������
	int scrl_num;
	int last_y;
	int last_tick;

} ZKN_SOUND_DRAW;

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
static ZKN_SOUND_GLB* MakeSoundGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_SOUND_DRAWGLB* MakeSoundDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
//static ZKN_EVENT_DATA* MakeSoundEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteSoundGlb( ZKN_SOUND_GLB* p_glb );
static void DeleteSoundDrawGlb( ZKN_SOUND_DRAWGLB* p_glb );
//static void DeleteSoundEvent( ZKN_EVENT_DATA* p_event );


static int SoundEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknSoundProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSoundProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSoundProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// �|�P�O��
static void ZknSoundPokeGraOn( ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb );
static void ZknSoundPokeGraOff( ZKN_SOUND_DRAWGLB* p_drawglb );

// �t�F�[�h����
static void ZknSoundOamFadeInit( ZKN_SOUND_DRAW* p_draw );
static void ZknSoundOamFadeDelete( ZKN_SOUND_DRAW* p_draw );
static void ZknSoundFadeInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknSoundFadeMain( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out );
static void ZknSoundFadeOtherInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknSoundFadeOtherMain( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out );

// Resource�ǂݍ���
static void ZknSoundLoadRes( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, const ZKN_SOUND_WORK* cp_datawork, int heap );
static void ZknSoundDeleteRes( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb );
static void ZknSoundSetUpBg( ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, int heap );
static void ZknSoundPutBackBg( ZKN_SOUND_DRAWGLB* p_drawglb );
static void ZknSoundOamResLoad( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, int heap );
static void ZknSoundOamResDelete( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb );
static void ZknSoundOamInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, int heap );
static void ZknSoundOamDelete( ZKN_SOUND_DRAW* p_draw );
static void ZknSoundFontOamInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, int heap );
static void ZknSoundFontOamDelete( ZKN_SOUND_DRAW* p_draw );


static void ZknSoundGetTich( ZKN_SOUND_WORK* p_work, ZKN_SOUND_GLB* p_glb );


static void ZknSoundBmpScrollSetUp( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb );
static void ZknSoundBmpScroll( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_WORK* cp_work );
static void ZknSoundBmpDraw( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const SNDWaveData* cp_snd_data, int start, int end, int draw_xnum, int x, int def_y, int* p_set_y );
static void ZknSoundBmpDammyDraw( ZKN_SOUND_DRAWGLB* p_drawglb, int start, int end, int x, int def_y, int* p_set_y );
static void ZknSoundBmpDrawOne( GF_BGL_BMPWIN* p_bmp, u8 data, int x, int def_y, int* p_set_y );

// �_�O���t
static void ZknSoundGraphLevelSet( ZKN_SOUND_WORK* p_work, ZKN_SOUND_GLB* p_glb );
static void ZknSoundGraphInit( ZKN_SOUND_DRAW* p_draw );
static void ZknSoundGraphMove( ZKN_SOUND_DRAW* p_draw, const ZKN_SOUND_WORK* cp_work );

static void ZknSoundGraphInitData( ZKN_GRAPH_ONE_DATA* p_data, int x_num );
static void ZknSoundGraphMoveData( ZKN_GRAPH_ONE_DATA* p_data, int level );
static void ZknSoundGraphSetLevelMatrixTop( CLACT_WORK_PTR act, int level );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������@�A�v���쐬
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
void ZKN_SoundAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_SOUND_GLB*	p_glb;
	ZKN_SOUND_DRAWGLB*	p_drawglb;
//	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeSoundGlb( heap, zkn_sys );
	p_drawglb = MakeSoundDrawGlb( heap, zkn_sys );
//	p_event = MakeSoundEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= NULL;
//	p_data->p_event_data	= p_event;
	p_data->event_num		= SoundEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknSoundProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknSoundProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknSoundProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknSoundProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknSoundProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknSoundProcDrawFuncDelete;
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
void ZKN_SoundAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteSoundGlb( p_data->p_glb_data ); 
	DeleteSoundDrawGlb( p_data->p_glb_draw ); 
//	DeleteSoundEvent( p_data->p_event_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�O���t�F�[�h�A�E�g��ݒ�
 *
 *	@param	p_data	�A�v���P�[�V�����f�[�^
 *	@param	x		�w���W
 *	@param	y		�x���W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_SoundPokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y )
{
	ZKN_SOUND_DRAWGLB* p_glb = p_data->p_glb_draw;

	p_glb->pokegra_move_x = x;
	p_glb->pokegra_move_y = y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h���[�h�ݒ�
 *
 *	@param	p_data		�A�v���P�[�V�����f�[�^
 *	@param	fade_mode	�t�F�[�h���[�h
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_SoundFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode )
{
	ZKN_SOUND_DRAWGLB* p_glb = p_data->p_glb_draw;

	p_glb->fade_mode = fade_mode;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�V���N���ݒ�
 *
 *	@param	p_data		�A�v���P�[�V�����f�[�^
 *	@param	fade_mode	�t�F�[�h�V���N��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_SoundFadeModeSync( ZKN_APL_DATA* p_data, int fade_sync )
{
	ZKN_SOUND_DRAWGLB* p_glb = p_data->p_glb_draw;

	p_glb->fade_sync = fade_sync;
}


//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SOUND_GLB* MakeSoundGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SOUND_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SOUND_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SOUND_GLB) );

	// main��ʂ���̃C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys ); 

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );
	
	// �߂���O���[�o���A�v���f�[�^�擾
	p_glb->p_main_common = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );

	// �T�u�����O���[�o���A�v���f�[�^�擾
	p_glb->p_sub_sound = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_SOUND );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SOUND_DRAWGLB* MakeSoundDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SOUND_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SOUND_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SOUND_DRAWGLB) );

	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}
#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeSoundEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = SoundEventDataNumGet();

	// �C�x���g�f�[�^�e�[�u���쐬
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	MakeSoundChangeBig( heap, &p_event_tbl[0], zkn_sys );

	return p_event_tbl;
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundGlb( ZKN_SOUND_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundDrawGlb( ZKN_SOUND_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}
#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	DeleteSoundChangeBig( &p_event[0] );

	sys_FreeMemoryEz( p_event );
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������A�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	�������A�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int SoundEventDataNumGet( void )
{
	return ZKN_SOUND_EVENT_NUM;
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
static int ZknSoundProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SOUND_GLB* p_glb = p_glbdata;
	ZKN_SOUND_WORK* p_work;
	int mons_no = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );
	
	// ���[�N�쐬
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_SOUND_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_SOUND_WORK) );
	p_dodata->p_work = p_work;
	

	// �T�E���h�f�[�^�擾
	p_work->cp_snd_data = Snd_ZukanWaveDataSet( mons_no );

	// �f�[�^�z�񐔎擾
	p_work->data_num = Snd_WaveDataSampleSizeGet( p_work->cp_snd_data );

	// �`�b�N���擾
	ZknSoundGetTich( p_work, p_glb );
	
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
static int ZknSoundProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SOUND_GLB* p_glb = p_glbdata;
	ZKN_SOUND_WORK*	p_work = p_dodata->p_work;
	
	
	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// �`�b�N�����擾
	ZknSoundGetTich( p_work, p_glb );

	// �g�`���x���ݒ�
	ZknSoundGraphLevelSet( p_work, p_glb );

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
static int ZknSoundProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SOUND_WORK* p_work = p_dodata->p_work;

	
	sys_FreeMemoryEz( p_work );
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
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSoundProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SOUND_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_SOUND_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_SOUND_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_SOUND_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUND_SEQINIT_LOAD:
		ZknSoundLoadRes( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );

		
		// �t�F�[�h������
		if( p_drawglb->fade_mode == ZKN_SOUND_FADE_MODE_MY ){
			ZknSoundFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}else{
			ZknSoundFadeOtherInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}

		// ���̃t�F�[�h
		Snd_BgmFadeOut( 0, BGM_FADE_ZUKAN_NAKIGOE_TIME );		//�t�F�[�h�A�E�g
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUND_SEQINIT_FADEIN:
		if( p_drawglb->fade_mode == ZKN_SOUND_FADE_MODE_MY ){
			check = ZknSoundFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}else{
			check = ZknSoundFadeOtherMain( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		}

		if( (check == TRUE) && ( Snd_FadeCheck() == 0 ) ){
			Snd_PlayerPause( PLAYER_FIELD, TRUE );		//�t�B�[���hBGM�|�[�Y
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_SOUND_SEQINIT_END:
		return ZKN_PROC_TRUE;
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
static int ZknSoundProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SOUND_DRAW* p_drawwork = p_drawdata->p_work;

	// �g�`�f�[�^����
	ZknSoundBmpScroll( p_drawwork, p_drawglb, cp_datawork );

	// �O���t����
	ZknSoundGraphMove( p_drawwork, cp_datawork );

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
static int ZknSoundProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SOUND_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;


	switch( p_drawdata->seq ){
	case ZKN_SOUND_SEQDELETE_FADEOUT_INIT:
		if( p_drawglb->fade_mode == ZKN_SOUND_FADE_MODE_MY ){
			ZknSoundFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}else{
			ZknSoundFadeOtherInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}

		Snd_PlayerPause( PLAYER_FIELD, FALSE );			//�t�B�[���hBGM�ĊJ
		Snd_BgmFadeIn( BGM_VOL_MAX, BGM_FADE_ZUKAN_NAKIGOE_TIME, BGM_FADEIN_START_VOL_MIN );	//�t�F�[�h�C��

		p_drawdata->seq++;
		break;
		
	case ZKN_SOUND_SEQDELETE_FADEOUT:
		if( p_drawglb->fade_mode == ZKN_SOUND_FADE_MODE_MY ){
			check = ZknSoundFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}else{
			check = ZknSoundFadeOtherMain( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		}
		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_SOUND_SEQDELETE_RELEASE:
		
		ZknSoundDeleteRes( p_drawwork, p_drawglb );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUND_SEQDELETE_FREE:

		sys_FreeMemoryEz(p_drawdata->p_work);
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_SOUND_SEQDELETE_END:
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�\��ON
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundPokeGraOn( ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// �|�P�����ݒ�
	ZKN_UTIL_PokemonGraphicSet( p_drawglb->p_drawglb, cp_glb->p_glb, monsno,
			PARA_FRONT, ZKN_SOUND_POKEGRA_DRAW_X, ZKN_SOUND_POKEGRA_DRAW_Y );
	
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
static void ZknSoundPokeGraOff( ZKN_SOUND_DRAWGLB* p_drawglb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );

	// �\��OFF
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, TRUE );

	// �\�t�g�p���b�g�t�F�[�h���������Ă���\��������̂�OFF
	SoftSpritePalFadeOff( p_pokegra );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�t�F�[�h������
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamFadeInit( ZKN_SOUND_DRAW* p_draw )
{
	int i, j;

	// �S�O���t�A�N�^�[����
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){

		for( j=0; j<ZKN_SOUND_GRAPH_ZANZOU_NUM; j++ ){
			CLACT_ObjModeSet( p_draw->snd_graph_act[i].zanzou[ j ].act, GX_OAM_MODE_XLU );
		}
		CLACT_ObjModeSet( p_draw->snd_graph_act[i].top.act, GX_OAM_MODE_XLU );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�t�F�[�h���Z�b�g
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamFadeDelete( ZKN_SOUND_DRAW* p_draw )
{
	int i, j;

	// �S�O���t�A�N�^�[����
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){

		for( j=0; j<ZKN_SOUND_GRAPH_ZANZOU_NUM; j++ ){
			CLACT_ObjModeSet( p_draw->snd_graph_act[i].zanzou[ j ].act, GX_OAM_MODE_NORMAL );
		}
		CLACT_ObjModeSet( p_draw->snd_graph_act[i].top.act, GX_OAM_MODE_NORMAL );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h����������
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���A�E�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundFadeInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknSoundOamFadeInit( p_draw );

	// �u���C�g�l�X�������s���Ă悢��
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_SOUND_FADE_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_SOUND_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_SOUND_FADE_SYNC, 
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_SOUND_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}
	}

	// �u���C�g�l�X�l�ݒ�
	ZKN_GLB_SpritePokeGraPalFade( p_drawglb->p_drawglb, &p_drawglb->p_drawglb->fade );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�������C��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���A�E�g
 *
 *	@retval	TRUE	�t�F�[�h�I��
 *	@retval	FALSE	�t�F�[�h�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknSoundFadeMain( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;

	// �u���C�g�l�X���悤���łĂ邩�`�F�b�N
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}

	// �I�������I������
	if( check ){
		if( fadein_out ){
			// ������OAM�j��
			ZknSoundOamFadeDelete( p_draw );
		}

		return TRUE;
	}else{
		// �u���C�g�l�X�l�ݒ�
		ZKN_GLB_SpritePokeGraPalFade( p_drawglb->p_drawglb, &p_drawglb->p_drawglb->fade );
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���A�v���P�[�V�����ւ̃t�F�[�h����
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���@�A�E�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundFadeOtherInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknSoundOamFadeInit( p_draw );


	// �t�F�[�h�A�E�g�̎������̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N�t�F�[�h
		ZKN_UTIL_MoveReq( &p_draw->pokegra_move, ZKN_SOUND_POKEGRA_DRAW_X, p_drawglb->pokegra_move_x, ZKN_SOUND_POKEGRA_DRAW_Y, p_drawglb->pokegra_move_y, p_drawglb->fade_sync );
	}

	// �u���C�g�l�X���g���ėǂ�������
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, p_drawglb->fade_sync, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_SOUND_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, p_drawglb->fade_sync, 
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_SOUND_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}
	}
}
//----------------------------------------------------------------------------
/**
 *	@brief	���A�v���P�[�V�����ւ̃t�F�[�h�������C��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���@�A�E�g
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknSoundFadeOtherMain( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check[ 2 ];
	int i;
	

	// �t�F�[�h�A�E�g�̂Ƃ��݂̂̏���
	if( fadein_out == FALSE ){
		// �|�P�����O���t�B�b�N
		check[0] = ZKN_UTIL_MoveMain( &p_draw->pokegra_move );

		// ���W�ݒ�
		ZKN_GlbPokemonGraphicSetMatrix( p_drawglb->p_drawglb, p_draw->pokegra_move.x, p_draw->pokegra_move.y );

	}else{
		check[0] = TRUE;
	}
	
	// �u���C�g�l�X���g�p���Ă悢�Ƃ��͎�����fade�𓮂���
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
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
			ZknSoundOamFadeDelete( p_draw );
		}
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	Resource�ǂݍ��݁���ʍ\�z
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	cp_datawork	�f�[�^���[�N
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundLoadRes( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, const ZKN_SOUND_WORK* cp_datawork, int heap )
{
	
	// BG�ݒ�
	ZknSoundSetUpBg( p_drawglb, cp_glb, heap );


	// OAM���\�[�X�ǂݍ���
	ZknSoundOamResLoad( p_draw, p_drawglb, heap );

	// �A�N�^�[�o�^
	ZknSoundOamInit( p_draw, p_drawglb, heap );

	// FONTOAM
	ZknSoundFontOamInit( p_draw, p_drawglb, cp_glb, heap );

	// �|�P�O��ON
	ZknSoundPokeGraOn( p_drawglb, cp_glb );

	// �X�N���[���ݒ�
	ZknSoundBmpScrollSetUp( p_draw, p_drawglb );

	// �O���t������
	ZknSoundGraphInit( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Resource�j��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundDeleteRes( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb )
{
	// FONTOAM
	ZknSoundFontOamDelete( p_draw );
	
	// �A�N�^�[�j��
	ZknSoundOamDelete( p_draw );

	// OAM���\�[�X�j��
	ZknSoundOamResDelete( p_draw, p_drawglb );

	// BG�ݒ胊�Z�b�g
	ZknSoundPutBackBg( p_drawglb );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�w�i�ʃZ�b�g	
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSetUpBg( ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �L�����N�^�f�[�^�]
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );
	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_voice_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�ʂ����ɖ߂�
 *
 *	@param	p_drawglb
 *	@param	cp_glb 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundPutBackBg( ZKN_SOUND_DRAWGLB* p_drawglb )
{
	GF_BGL_ScrollReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M, GF_BGL_SCROLL_X_SET, 0 );

	// �`��G���A�̃L�����N�^��������
	GF_BGL_BmpWinFill( &p_drawglb->p_drawglb->bmp_mfont,
			0 , 
			0,
			0,
			256,
			192 );
	

	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );

	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, ZKN_BG_FONT_COLOR );
}


//----------------------------------------------------------------------------
/**
 *	@brief	OAMResource�ǂݍ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamResLoad(  ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );

	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_main_lzh_NCGR, TRUE,
			NARC_zukan_zkn_voice_oam_main_lzh_NCGR + ZKN_SOUND_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_main_NCLR, FALSE, 
			NARC_zukan_zkn_voice_oam_main_NCLR + ZKN_SOUND_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_SOUND_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_main_lzh_NCER, TRUE,
			NARC_zukan_zkn_voice_oam_main_lzh_NCER + ZKN_SOUND_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_voice_oam_main_lzh_NANR, TRUE,
			NARC_zukan_zkn_voice_oam_main_lzh_NANR + ZKN_SOUND_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMResource�j��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamResDelete( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb )
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
 *	@brief	OAM�A�N�^�[�o�b�t�@�쐬
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i, j;
	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_voice_oam_main_lzh_NCGR + ZKN_SOUND_RES_ID,
			NARC_zukan_zkn_voice_oam_main_NCLR + ZKN_SOUND_RES_ID, 
			NARC_zukan_zkn_voice_oam_main_lzh_NCER + ZKN_SOUND_RES_ID,
			NARC_zukan_zkn_voice_oam_main_lzh_NANR + ZKN_SOUND_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_SOUND_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_SOUND_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	add.mat.x		= 0;
	add.mat.y		= 0;

	// �S�O���t�A�N�^�[����
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){

		for( j=0; j<ZKN_SOUND_GRAPH_ZANZOU_NUM; j++ ){
			p_draw->snd_graph_act[ i ].zanzou[ j ].act = CLACT_AddSimple( &add );
		}
		p_draw->snd_graph_act[ i ].top.act = CLACT_AddSimple( &add );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�A�N�^�[�o�b�t�@�j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundOamDelete( ZKN_SOUND_DRAW* p_draw )
{
	int i, j;

	// �S�O���t�A�N�^�[����
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){

		for( j=0; j<ZKN_SOUND_GRAPH_ZANZOU_NUM; j++ ){
			CLACT_Delete( p_draw->snd_graph_act[ i ].zanzou[ j ].act );
		}
		CLACT_Delete( p_draw->snd_graph_act[ i ].top.act );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�쐬
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	p_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundFontOamInit( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_GLB* cp_glb, int heap )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�j��
 *
 *	@param	p_draw �`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundFontOamDelete( ZKN_SOUND_DRAW* p_draw )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�b�N���擾
 *
 *	@param	p_work	���[�N
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundGetTich( ZKN_SOUND_WORK* p_work, ZKN_SOUND_GLB* p_glb )
{
	int pitch = ZKN_SoundSubAplGetPitchNum( p_glb->p_sub_sound );
	
	// �`�b�N���擾
	p_work->tick = Snd_ZukanPlayerGetSampleTick( SND_HANDLE_PMVOICE, p_work->cp_snd_data, pitch );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�g�`�f�[�^���r�b�g�}�b�v�ɏ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_snd_data	���f�[�^
 *	@param	start		�`��f�[�^�z��J�n�ʒu
 *	@param	end			�`��f�[�^�z��I���ʒu
 *	@param	draw_xnum	�`�悷�邘�l		���̐����ɏ�������
 *	@param	x			�`�悘���W
 *	@param	def_y		�f�t�H���gY�ʒu
 *	@param	p_set_y		�Ō�ɐݒ肵��Y���W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundBmpDraw( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const SNDWaveData* cp_snd_data, int start, int end, int draw_xnum, int x, int def_y, int* p_set_y )
{
	const u8* p_snd_wave = Snd_WaveDataSampleAdrsGet( cp_snd_data );
	int i;
	int arry_idx;		// �Q�Ɣz��C���f�b�N�X
	int arry_num;		// �z��v�f��

	// �`��G���A�̃L�����N�^��������
	GF_BGL_BmpWinFill( &p_drawglb->p_drawglb->bmp_mfont,
			0 , x,
			def_y - ZKN_SOUND_DRAW_BMP_Y_MAX,
			ZKN_SOUND_DRAW_BMP_ONE_SIZE_X * (draw_xnum),
			ZKN_SOUND_DRAW_BMP_Y_MAX * 2 );
	
	arry_num = end - start;
	
	for( i=0; i<draw_xnum; i++ ){
		arry_idx = FX_Mul( arry_num << FX32_SHIFT, i << FX32_SHIFT );
		arry_idx = FX_Div( arry_idx, draw_xnum << FX32_SHIFT ) >> FX32_SHIFT;
		
		
		arry_idx += start;

		ZknSoundBmpDrawOne( &p_drawglb->p_drawglb->bmp_mfont, 
				p_snd_wave[ arry_idx ], x, def_y, p_set_y );

		x += ZKN_SOUND_DRAW_BMP_ONE_SIZE_X;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�P�̃f�[�^���r�b�g�}�b�v�ɏ�������
 *
 *	@param	p_bmp
 *	@param	data
 *	@param	x
 *	@param	def_y
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundBmpDrawOne( GF_BGL_BMPWIN* p_bmp, u8 data, int x, int def_y, int* p_set_y )
{
	int y;
	int draw_st_y;
	int draw_y, draw_y2;

	// y���W�ɕύX
	if( data > 127 ){
		y = data - 255;
	}else{
		y = data;
	}

	if( y != 0 ){
		// ���������킹��		-32�`32�̒l�ɕύX
		y = FX_Mul( ZKN_SOUND_DRAW_BMP_Y_MAX << FX32_SHIFT, y << FX32_SHIFT );	
		y = FX_Div( y, 127 << FX32_SHIFT ) >> FX32_SHIFT;
	}

	//�@�`��c���@�ƕ`��J�n���W�擾
	draw_y = (def_y + y);
	draw_y2 = (def_y + (*p_set_y));
	if( draw_y > draw_y2 ){

		draw_st_y = draw_y2;

		draw_y = draw_y - draw_y2;		
		
	}else{
		draw_st_y = draw_y;

		draw_y = draw_y2 - draw_y;		
	}
	draw_y ++;
	draw_y *= ZKN_SOUND_DRAW_BMP_ONE_SIZE_Y;

	GF_BGL_BmpWinFill( p_bmp, ZKN_SOUND_DRAW_BMP_PL, x, draw_st_y, ZKN_SOUND_DRAW_BMP_ONE_SIZE_X, draw_y );

	// ���ݒ肵���_��ۑ�
	*p_set_y = y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�_�~�[�f�[�^��`�悷��
 *
 *	@param	p_drawglb
 *	@param	start
 *	@param	end
 *	@param	x
 *	@param	def_y 
 *	@param	p_set_y
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundBmpDammyDraw( ZKN_SOUND_DRAWGLB* p_drawglb, int start, int end, int x, int def_y, int* p_set_y )
{
	int i;
	
	// �`��G���A�̃L�����N�^��������
	GF_BGL_BmpWinFill( &p_drawglb->p_drawglb->bmp_mfont,
			0, x, def_y - ZKN_SOUND_DRAW_BMP_Y_MAX,
			ZKN_SOUND_DRAW_BMP_ONE_SIZE_X * (end - start),
			ZKN_SOUND_DRAW_BMP_Y_MAX * 2 );
	
	for( i=start; i<end; i++ ){
		ZknSoundBmpDrawOne( &p_drawglb->p_drawglb->bmp_mfont, 
				0, x, def_y, p_set_y );

		x += ZKN_SOUND_DRAW_BMP_ONE_SIZE_X;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E�̃X�N���[������
 *
 *	@param	p_draw
 *	@param	p_drawglb
 *	@param	cp_work 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundBmpScroll( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb, const ZKN_SOUND_WORK* cp_work )
{
	int draw_x;

	// ���X�s�[�h�ŃX�N���[��
	p_draw->scrl_num += ZKN_SOUND_SCRL_BMP_SPEED;
	p_draw->scrl_num %= 256;

	// �`��J�n�ʒu����
	draw_x = p_draw->scrl_num - (ZKN_SOUND_SCRL_BMP_SPEED * 2);
	if( draw_x < 0 ){
		draw_x += 256;
	}

	// �X�N���[�����W�ƃX�s�[�h����g�`�f�[�^�`��
	if( p_draw->last_tick != cp_work->tick ){
		ZknSoundBmpDraw( p_draw, p_drawglb, 
				cp_work->cp_snd_data, 
				p_draw->last_tick, cp_work->tick, ZKN_SOUND_SCRL_BMP_SPEED,
				draw_x, ZKN_SOUND_DRAW_BMP_DEF_Y, &p_draw->last_y );
	}else{
		ZknSoundBmpDammyDraw( p_drawglb, 
				0, ZKN_SOUND_SCRL_BMP_SPEED,
				draw_x, ZKN_SOUND_DRAW_BMP_DEF_Y, &p_draw->last_y );
	}

	// �X�N���[���ݒ�
	GF_BGL_ScrollReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M, GF_BGL_SCROLL_X_SET, p_draw->scrl_num );
	
	// CG�]���ݒ�
	GF_BGL_BmpWinOnVReq( &p_drawglb->p_drawglb->bmp_mfont );

	// �`�b�N�ۑ�
	p_draw->last_tick = cp_work->tick;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����g�`�f�[�^�̏�����
 *
 *	@param	p_draw		�`�惏�[�N	
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundBmpScrollSetUp( ZKN_SOUND_DRAW* p_draw, ZKN_SOUND_DRAWGLB* p_drawglb )
{
	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, ZKN_SOUND_DRAW_BMP_PL_TBL );
	
	ZknSoundBmpDammyDraw( p_drawglb, 
			0, 256,
			0, ZKN_SOUND_DRAW_BMP_DEF_Y, &p_draw->last_y );
	
	GF_BGL_BmpWinOn( &p_drawglb->p_drawglb->bmp_mfont );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�̃f�[�^�S��������
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphInit( ZKN_SOUND_DRAW* p_draw )
{
	int i;

	// �O���t�f�[�^������
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){
		ZknSoundGraphInitData( &p_draw->snd_graph_act[i], i );
	}
}

//----------------------------------------------------------------------------
/**	
 *	@brief	�O���t����
 *
 *	@param	p_draw	�`�惏�[�N
 *	@param	cp_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphMove( ZKN_SOUND_DRAW* p_draw, const ZKN_SOUND_WORK* cp_work )
{
	int i;

	// �O���t�f�[�^����
	for( i=0; i<ZKN_SOUND_GRAPH_NUM; i++ ){
		ZknSoundGraphMoveData( &p_draw->snd_graph_act[i], cp_work->snd_graph_data[ i ] );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�f�[�^������
 *
 *	@param	p_data	�f�[�^
 *	@param	x_num	���v�f��	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphInitData( ZKN_GRAPH_ONE_DATA* p_data, int x_num )
{
	int i;
	VecFx32 mat;

	// ���W��ݒ聕��\���ɂ���
	mat.x = (ZKN_SOUND_GRAPH_MAT_DEF_X + ( ZKN_SOUND_GRAPH_MAT_OFS_X*x_num )) << FX32_SHIFT;
	mat.y = ZKN_SOUND_GRAPH_MAT_DEF_Y << FX32_SHIFT;
	for( i=0; i<ZKN_SOUND_GRAPH_ZANZOU_NUM; i++ ){
		CLACT_SetMatrix( p_data->zanzou[ i ].act, &mat );
		CLACT_SetDrawFlag( p_data->zanzou[ i ].act, FALSE );
		mat.y += ZKN_SOUND_GRAPH_MAT_OFS_Y << FX32_SHIFT;
		CLACT_AnmChg( p_data->zanzou[ i ].act, 1 );
	}

	// �擪�̃A�N�^�[�̍��W�Ə������[�N��ݒ�
	mat.y = ZKN_SOUND_GRAPH_MAT_DEF_Y << FX32_SHIFT;
	CLACT_SetMatrix( p_data->top.act, &mat );
	CLACT_SetDrawFlag( p_data->top.act, FALSE );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�O���t����
 *
 *	@param	p_data	�O���t�f�[�^
 *	@param	level	���̃��x��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphMoveData( ZKN_GRAPH_ONE_DATA* p_data, int level )
{
	int i;
	int now_max_level = 0;
	
	// level�ɂ��e���[�N�̐ݒ�
	for( i=0; i<level; i++ ){
		CLACT_SetDrawFlag( p_data->zanzou[i].act, TRUE );
		p_data->zanzou[i].dess_count = ZKN_SOUND_GRAPH_DES_COUNT * (i + 1);
	}

	// �c������
	for( i=0; i<ZKN_SOUND_GRAPH_ZANZOU_NUM; i++ ){
		// �`�悵�Ă���Ȃ�
		// �j���J�E���^��0�ɂȂ�܂ŕ`�悷��
		if( CLACT_GetDrawFlag( p_data->zanzou[i].act ) ){
			if( (p_data->zanzou[i].dess_count - 1) > 0 ){
				p_data->zanzou[i].dess_count--;
				now_max_level = i + 1;	// ���̍ő僌�x��
			}else{

				CLACT_SetDrawFlag( p_data->zanzou[i].act, FALSE );
			}

		}
	}
	
	// level�̍��W�ɒ��_�������Ă���
	if( p_data->top.level <= now_max_level ){
		
		ZknSoundGraphSetLevelMatrixTop( p_data->top.act, now_max_level );
		p_data->top.down_count = ZKN_SOUND_GRAPH_DOWN_COUNT;

		// �������邱�Ƃɂ���ԉ��̎��͂O�ł���\����
		// �Ȃɂ��㏸����Ƃ��ɂ̂ݕ`��J�n�Ƃ��������ɂȂ�͂�
		if( p_data->top.level < now_max_level ){
			// �\����
			CLACT_SetDrawFlag( p_data->top.act, TRUE );
		}

		p_data->top.level = now_max_level;

	}



	// �擪����
	if( p_data->top.level > 0 ){

		// �_�E���J�E���g��0��菬�����Ȃ����痎���Ă���
		if( p_data->top.down_count < 0 ){
			p_data->top.level --;
			ZknSoundGraphSetLevelMatrixTop( p_data->top.act, p_data->top.level );
		}else{
			p_data->top.down_count --;
		}
	}else{

		// ��\����
		CLACT_SetDrawFlag( p_data->top.act, FALSE );
	}
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[�Ɉ������x����Y���W��ݒ肷��
 *
 *	@param	act
 *	@param	level 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphSetLevelMatrixTop( CLACT_WORK_PTR act, int level )
{
	VecFx32 mat;
	const VecFx32* cp_mat;
	
	cp_mat = CLACT_GetMatrix( act );
	mat = *cp_mat;
	mat.y = (ZKN_SOUND_GRAPH_MAT_DEF_Y + ( ZKN_SOUND_GRAPH_MAT_OFS_Y*level)) << FX32_SHIFT;
	CLACT_SetMatrix( act, &mat );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�_���O���t�f�[�^�擾�֐�
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundGraphLevelSet( ZKN_SOUND_WORK* p_work, ZKN_SOUND_GLB* p_glb )
{
	int pitch = ZKN_SoundSubAplGetPitchNum( p_glb->p_sub_sound );
	
	memset( p_work->snd_graph_data, 0, sizeof(u8)* ZKN_SOUND_GRAPH_NUM);

	if( Snd_PMVoicePlayCheck() != 0 ){	// �Đ����̂ݎ擾
		Snd_ZukanWaveLevelSet_New( p_work->cp_snd_data, p_work->snd_graph_data, ZKN_SOUND_GRAPH_NUM, pitch );
	}
}
