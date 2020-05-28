//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_big.c
 *	@brief		�傫����׃A�v���P�[�V����	�������
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
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"


#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"

#define	__ZKN_BIG_H_GLOBAL
#include "include/application/zukanlist/zkn_big.h"


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
#ifdef PM_DEBUG
#define ZKN_BIG_EVENT_NUM ( 1 )	// �C�x���g��
#define ZKN_BIG_EVENT_CHANGE_DEBUG	(0x1 << 1)	// DEBUG���߂��
#else
#define ZKN_BIG_EVENT_NUM ( 0 )	// �C�x���g��
//#define ZKN_BIG_EVENT_CHANGE_ZUKAN	(0x1 << 1)	// �}�ӂ�
#endif

#define ZKN_BIG_OAM_BG_PRI	( 1 )
#define ZKN_BIG_OAM_PRI	( 31 )

// �t�F�[�h�p
#define ZKN_BIG_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-------------------------------------
//	�V�[�P���X
//=====================================
enum{
	ZKN_BIG_SEQINIT_ALLOC,
	ZKN_BIG_SEQINIT_LOAD,
	ZKN_BIG_SEQINIT_FADEIN,
	ZKN_BIG_SEQINIT_END,
};
enum{
	ZKN_BIG_SEQDELETE_FADEOUT_INIT,
	ZKN_BIG_SEQDELETE_FADEOUT,
	ZKN_BIG_SEQDELETE_RELEASE,
	ZKN_BIG_SEQDELETE_FREE,
	ZKN_BIG_SEQDELETE_END,
};

// �m�ە�����o�b�t�@�T�C�Y
#define ZKN_BIG_HEIGHT_NUM_STR	( 32 )

// ������`��ʒu
#define ZKN_BIG_HEIGHT_TITLE_X	( 96 )		// �^�C�g��
#define ZKN_BIG_HEIGHT_TITLE_Y	( 24 )
#define ZKN_BIG_HEIGHT_TAKASA_Y	( 168 )		// "����"
#define ZKN_BIG_HEIGHT_TAKASA1_X	( 32 )
#define ZKN_BIG_HEIGHT_TAKASA2_X	( 152 )
#define ZKN_BIG_HEIGHT_NUM_OFS_X	( 32 )	// ���ۂ̒l��\�����鍂������̈ʒu
#define ZKN_BIG_HEIGHT__M__OFS_X	( 30 )	// M��\������l����̈ʒu
#define ZKN_BIG_HEIGHT_NAME_Y		( 152 )
#define ZKN_BIG_HEIGHT_MONSNAME_X	( 24 )
#define ZKN_BIG_HEIGHT_HERO_X		( 146 )

// ��l����{�\���ʒu
#define ZKN_BIG_HEIGHT_HERO_DEF_X	( 168 )
#define ZKN_BIG_HEIGHT_HERO_DEF_Y	( 88 )
#define ZKN_BIG_HEIGHT_HERO_ANM_SEQ_MAN		( 5 )
#define ZKN_BIG_HEIGHT_HERO_ANM_SEQ_GIRL	( 6 )

// �|�P�����O���t�B�b�N
#define ZKN_BIG_HEIGHT_POKEGRA_DEF_X	( 88 )
#define ZKN_BIG_HEIGHT_POKEGRA_DEF_Y	( ZKN_BIG_HEIGHT_HERO_DEF_Y )


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�傫����׉�ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	int* p_event_key;		// �C�x���g�L�[
	
	ZKN_GLB_DATA*		p_glb;				// �O���[�o���f�[�^

	// ���C���R�����O���[�o��
	ZKN_APL_DATA*	p_main_common;	// �A�v���f�[�^
} ZKN_BIG_GLB;

//-------------------------------------
//	�傫����׉��	�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// �`��O���[�o���f�[�^

#ifdef PM_DEBUG
	short hero_scale;
	BOOL reflect_scale;
	short hero_yofs;
	BOOL reflect_yofs;
#endif
} ZKN_BIG_DRAWGLB;

//-------------------------------------
//	�傫����׉�ʁ@�������[�N
//=====================================
typedef struct {
	int dummy;
} ZKN_BIG_WORK;

//-------------------------------------
//	�傫����׉�ʁ@�������[�N
//=====================================
typedef struct {
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resource�I�u�W�F�|�C���^
	CLACT_WORK_PTR hero;
} ZKN_BIG_DRAW;

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
static ZKN_BIG_GLB* MakeBigGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_BIG_DRAWGLB* MakeBigDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeBigEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteBigGlb( ZKN_BIG_GLB* p_glb );
static void DeleteBigDrawGlb( ZKN_BIG_DRAWGLB* p_glb );
static void DeleteBigEvent( ZKN_EVENT_DATA* p_event );


static int BigEventDataNumGet( void );

//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknBigProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// �t�F�[�h����
static void ZknBigOamFadeInit( ZKN_BIG_DRAW* p_draw );
static void ZknBigOamFadeDelete( ZKN_BIG_DRAW* p_draw );
static void ZknBigFadeInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknBigFadeMain( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, BOOL fadein_out );

// �ǂݍ��ݏ���
static void ZknBigLoadRes( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, const ZKN_BIG_WORK* cp_datawork, int heap );
static void ZknBigDeleteRes( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb );
static void ZknBigSetUpBg( ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap );
static void ZknBigOamResLoad( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, int heap );
static void ZknBigOamResDelete( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb );
static void ZknBigOamInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap );
static void ZknBigOamDelete( ZKN_BIG_DRAW* p_draw );
static void ZknBigFontOamInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap );
static void ZknBigFontOamDelete( ZKN_BIG_DRAW* p_draw );
static void ZknBigSetUpFontBgNormal( ZKN_BIG_DRAWGLB* p_drawglb, int heap );
static void ZknBigSetUpFontBgHeroPokeData( ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap );

static void ZknBigPokeGraOn( ZKN_BIG_DRAWGLB* p_draw, const ZKN_BIG_GLB* cp_glb );
static void ZknBigPokeGraOff( ZKN_BIG_DRAWGLB* p_draw );

// �g�k�l�ݒ�p�֐��S
static void ZknBigHeroYOfsSet( CLACT_WORK_PTR p_act, short yofs );
static void ZknBigPokeGraYOfsSet( SOFT_SPRITE* p_pokegra, short yofs );
static void ZknBigHeroScaleSet( CLACT_WORK_PTR p_act, short scale );
static void ZknBigPokeGraScaleSet( SOFT_SPRITE* p_pokegra, short scale );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�A�v���쐬
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
void ZKN_BigAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_BIG_GLB*	p_glb;
	ZKN_BIG_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeBigGlb( heap, zkn_sys );
	p_drawglb = MakeBigDrawGlb( heap, zkn_sys );
	p_event = MakeBigEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= BigEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknBigProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknBigProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigProcDrawFuncDelete;
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
void ZKN_BigAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteBigGlb( p_data->p_glb_data ); 
	DeleteBigDrawGlb( p_data->p_glb_draw ); 
	DeleteBigEvent( p_data->p_event_data );
}



#ifdef PM_DEBUG
//----------------------------------------------------------------------------
/**
 *	@brief	�߹��׊g�k�l��ݒ�
 *
 *	@param	p_data
 *	@param	scale 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_BigAplPokeGraScaleSet( ZKN_APL_DATA* p_data, short scale )
{
	ZKN_BIG_DRAWGLB* p_drawglb = p_data->p_glb_draw;
	SOFT_SPRITE* pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	ZknBigPokeGraScaleSet( pokegra, scale );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��l���g�k�l��ݒ�
 *
 *	@param	p_data	
 *	@param	scale 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_BigAplHeroGraScaleSet( ZKN_APL_DATA* p_data, short scale )
{
	ZKN_BIG_DRAWGLB* p_drawglb = p_data->p_glb_draw;

	p_drawglb->hero_scale = scale;
	p_drawglb->reflect_scale = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�߹���Y�I�t�Z�b�g�ݒ�
 *
 *	@param	p_data
 *	@param	yofs 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_BigAplPokeGraYofsSet( ZKN_APL_DATA* p_data, short yofs )
{
	ZKN_BIG_DRAWGLB* p_drawglb = p_data->p_glb_draw;
	SOFT_SPRITE* pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	ZknBigPokeGraYOfsSet( pokegra, yofs );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��l��Y�I�t�Z�b�g�ݒ�
 *
 *	@param	p_data
 *	@param	yofs 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_BigAplHeroGraYofsSet( ZKN_APL_DATA* p_data, short yofs )
{
	ZKN_BIG_DRAWGLB* p_drawglb = p_data->p_glb_draw;

	p_drawglb->hero_yofs = yofs;
	p_drawglb->reflect_yofs = TRUE;
}
#endif


//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_BIG_GLB* MakeBigGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_GLB) );

	// �C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys );

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// �߂���O���[�o���A�v���f�[�^�擾
	p_glb->p_main_common = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��O���[�o���쐬
 *
 *	@param	heap	�q�[�v
 *	@param	zkn_sys	�}�ӃV�X�e��
 *
 *	@return	�쐬�f�[�^
 */
//-----------------------------------------------------------------------------
ZKN_BIG_DRAWGLB* MakeBigDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_DRAWGLB) );

	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeBigEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
#ifdef PM_DEBUG
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = BigEventDataNumGet();

	// �C�x���g�f�[�^�e�[�u���쐬
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_BigHeightDebugApl( &p_event_tbl[0], zkn_sys, heap, ZKN_BIG_EVENT_CHANGE_DEBUG );

	return p_event_tbl;
#else
	return NULL;
#endif
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteBigGlb( ZKN_BIG_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteBigDrawGlb( ZKN_BIG_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteBigEvent( ZKN_EVENT_DATA* p_event )
{
#ifdef PM_DEBUG
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );
#endif
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�����\�[�g�A�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	�����\�[�g�A�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int BigEventDataNumGet( void )
{
	return ZKN_BIG_EVENT_NUM;
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
static int ZknBigProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_GLB* p_glb = p_glbdata;
	ZKN_BIG_WORK* p_work;
	
	// ���[�N�쐬
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_BIG_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_BIG_WORK) );
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
static int ZknBigProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_GLB* p_glb = p_glbdata;
	ZKN_BIG_WORK*	p_work = p_dodata->p_work;
	
	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

#ifdef PM_DEBUG
	// LR����������DEBUG���߂��
	if( ((sys.cont & PAD_BUTTON_L) != 0) &&
		((sys.cont & PAD_BUTTON_R) != 0) ){
		*p_glb->p_event_key |= ZKN_BIG_EVENT_CHANGE_DEBUG;
	}
#endif

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
static int ZknBigProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_GLB* p_glb = p_glbdata;
	ZKN_BIG_WORK*	p_work = p_dodata->p_work;

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
static int ZknBigProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_BIG_DRAW* p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_BIG_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_BIG_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_BIG_DRAW) );

		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_SEQINIT_LOAD:
		ZknBigLoadRes( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );

		// �t�F�[�h������
		ZknBigFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_SEQINIT_FADEIN:
		if( ZknBigFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_BIG_SEQINIT_END:
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
static int ZknBigProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_BIG_DRAW* p_drawwork = p_drawdata->p_work;


#ifdef PM_DEBUG
	if( p_drawglb->reflect_scale ){
		ZknBigHeroScaleSet( p_drawwork->hero, p_drawglb->hero_scale );
		p_drawglb->reflect_scale = FALSE;
	}
	if( p_drawglb->reflect_yofs ){
		ZknBigHeroYOfsSet( p_drawwork->hero, p_drawglb->hero_yofs );
		p_drawglb->reflect_yofs = FALSE;
	}
#endif
	
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
static int ZknBigProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_BIG_DRAW* p_drawwork = p_drawdata->p_work;


	switch( p_drawdata->seq ){
	case ZKN_BIG_SEQDELETE_FADEOUT_INIT:
		ZknBigFadeInit( p_drawwork, p_drawglb, cp_glbdata, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_SEQDELETE_FADEOUT:
		if( ZknBigFadeMain( p_drawwork, p_drawglb, cp_glbdata, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_BIG_SEQDELETE_RELEASE:
		ZknBigDeleteRes( p_drawwork, p_drawglb );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_SEQDELETE_FREE:
		sys_FreeMemoryEz(p_drawdata->p_work);
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_BIG_SEQDELETE_END:
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
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
static void ZknBigOamFadeInit( ZKN_BIG_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->hero, GX_OAM_MODE_XLU );
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
static void ZknBigOamFadeDelete( ZKN_BIG_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->hero, GX_OAM_MODE_NORMAL );
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
static void ZknBigFadeInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknBigOamFadeInit( p_draw );

	// �u���C�g�l�X�������s���Ă悢��
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_BIG_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_BIG_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}
	}
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
static BOOL ZknBigFadeMain( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, BOOL fadein_out )
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
			ZknBigOamFadeDelete( p_draw );
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
static void ZknBigLoadRes( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, const ZKN_BIG_WORK* cp_datawork, int heap )
{
	// BG�ݒ�
	ZknBigSetUpBg( p_drawglb, cp_glb, heap );

	// �t�H���gBG�ݒ�
	ZknBigSetUpFontBgNormal( p_drawglb, heap );	// ���ʂ̕�����
	ZknBigSetUpFontBgHeroPokeData( p_drawglb, cp_glb, heap );	// �f�[�^

	// OAM���\�[�X�ǂݍ���
	ZknBigOamResLoad( p_draw, p_drawglb, heap );

	// �A�N�^�[�o�^
	ZknBigOamInit( p_draw, p_drawglb, cp_glb, heap );

	// FONTOAM
	ZknBigFontOamInit( p_draw, p_drawglb, cp_glb, heap );

	// �|�P�O���\��
	ZknBigPokeGraOn( p_drawglb, cp_glb );
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
static void ZknBigDeleteRes( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb )
{

	// FONTOAM
	ZknBigFontOamDelete( p_draw );
	
	// �A�N�^�[�j��
	ZknBigOamDelete( p_draw );

	// OAM���\�[�X�j��
	ZknBigOamResDelete( p_draw, p_drawglb );

	// bmp�j��
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );

	// �|�P�O����\��
	ZknBigPokeGraOff( p_drawglb );
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
 *
 * [�C�x���g�ŏo�Ă��铇�̃X�N���[���f�[�^�������������̒�]
 */
//-----------------------------------------------------------------------------
static void ZknBigSetUpBg( ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �L�����N�^�f�[�^�]
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );
	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_height_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
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
 *	@brief	OAMResource�ǂݍ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigOamResLoad(  ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw_glb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR + ZKN_BIG_WEIGHT_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_data_oam3_NCLR, FALSE, 
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_BIG_WEIGHT_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_BIG_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main3_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NCER + ZKN_BIG_WEIGHT_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_main3_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NANR + ZKN_BIG_WEIGHT_RES_ID,
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
static void ZknBigOamResDelete( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb )
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
static void ZknBigOamInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	VecFx32				scale;
	short				ofs_y;
	short				scale_num;	
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR + ZKN_BIG_WEIGHT_RES_ID,
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_BIG_WEIGHT_RES_ID, 
			NARC_zukan_zkn_data_oam_main3_lzh_NCER + ZKN_BIG_WEIGHT_RES_ID,
			NARC_zukan_zkn_data_oam_main3_lzh_NANR + ZKN_BIG_WEIGHT_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_BIG_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_BIG_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	

	// ��l���f�[�^�擾
	ofs_y = ZKN_HEIGHTGRAM_GetHeightY_hero( cp_glb->p_glb->height_gram, monsno );
	scale_num = ZKN_HEIGHTGRAM_GetHeightScale_hero( cp_glb->p_glb->height_gram, monsno );	

	// ��l��
	add.mat.x = ZKN_BIG_HEIGHT_HERO_DEF_X << FX32_SHIFT;
	add.mat.y = (ZKN_BIG_HEIGHT_HERO_DEF_Y + ofs_y) << FX32_SHIFT;
	p_draw->hero = CLACT_AddSimple( &add );

	if( ZKN_GLBDATA_HeroSexGet( cp_glb->p_glb ) == 0 ){
		CLACT_AnmChg( p_draw->hero, ZKN_BIG_HEIGHT_HERO_ANM_SEQ_MAN );
	}else{
		CLACT_AnmChg( p_draw->hero, ZKN_BIG_HEIGHT_HERO_ANM_SEQ_GIRL );
	}

	// �g�k�l�ƍ��W��ݒ�
	ZknBigHeroYOfsSet( p_draw->hero, ofs_y );
	ZknBigHeroScaleSet( p_draw->hero, scale_num );
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
static void ZknBigOamDelete( ZKN_BIG_DRAW* p_draw )
{
	CLACT_Delete( p_draw->hero );
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
static void ZknBigFontOamInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap )
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
static void ZknBigFontOamDelete( ZKN_BIG_DRAW* p_draw )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	FONTBG�̃Z�b�g�A�b�v
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigSetUpFontBgNormal( ZKN_BIG_DRAWGLB* p_drawglb, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIG_HEIGHT_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	// �����������
	MSGMAN_GetString( man, ZNK_BIG_00, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TITLE_X, ZKN_BIG_HEIGHT_TITLE_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	// ������
	MSGMAN_GetString( man, ZNK_ZUKAN_01, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TAKASA1_X, ZKN_BIG_HEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// ������
	MSGMAN_GetString( man, ZNK_ZUKAN_01, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TAKASA2_X, ZKN_BIG_HEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	
	STRBUF_Delete(str);

	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������@��l�����@�����f�[�^�@�\��
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigSetUpFontBgHeroPokeData( ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIG_HEIGHT_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_height_dat, heap);
	int mons_no =  ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	STRBUF* monsname_str = MSGDAT_UTIL_GetMonsName( mons_no, heap );
	
	// �|�P������
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, monsname_str, ZKN_BIG_HEIGHT_MONSNAME_X, ZKN_BIG_HEIGHT_NAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	//	�|�P�����̍���
	MSGMAN_GetString( man, mons_no, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TAKASA1_X + ZKN_BIG_HEIGHT_NUM_OFS_X, ZKN_BIG_HEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	STRBUF_Delete(monsname_str);

	MSGMAN_Delete(man);

	// �Ⴄ���b�Z�[�W�}�l�[�W���I�[�v��
	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	// ��l����
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, 
			ZKN_GLBDATA_HeroNameGet( cp_glb->p_glb ),
			ZKN_BIG_HEIGHT_HERO_X, ZKN_BIG_HEIGHT_NAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	
	// ��l���̍���
	if( ZKN_GLBDATA_HeroSexGet( cp_glb->p_glb ) == 0 ){
		MSGMAN_GetString( man, ZNK_HEIGHT_00, str );
	}else{
		MSGMAN_GetString( man, ZNK_HEIGHT_01, str );
	}
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TAKASA2_X + ZKN_BIG_HEIGHT_NUM_OFS_X, ZKN_BIG_HEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	// M
	MSGMAN_GetString( man, ZNK_ZUKAN_03, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TAKASA2_X + ZKN_BIG_HEIGHT_NUM_OFS_X + ZKN_BIG_HEIGHT__M__OFS_X, ZKN_BIG_HEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	

	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�\��
 *
 *	@param	p_draw	�`��O���[�o��
 *	@param	cp_glb	�O���[�o���f�[�^
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigPokeGraOn( ZKN_BIG_DRAWGLB* p_draw, const ZKN_BIG_GLB* cp_glb )
{
	// �^�������|�P�O���\��
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_draw->p_drawglb );
	short ofs_y;
	short scale_num;
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );


	// �|�P�����\���f�[�^�擾
	ofs_y = ZKN_HEIGHTGRAM_GetHeightY_poke( cp_glb->p_glb->height_gram, monsno );
	scale_num = ZKN_HEIGHTGRAM_GetHeightScale_poke( cp_glb->p_glb->height_gram, monsno );
	
	
	// �|�P�����ݒ�
	ZKN_UTIL_PokemonGraphicSet( p_draw->p_drawglb, cp_glb->p_glb, monsno,
			PARA_FRONT, ZKN_BIG_HEIGHT_POKEGRA_DEF_X, ZKN_BIG_HEIGHT_POKEGRA_DEF_Y + ofs_y );
	
	// �\��
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, FALSE );

	// �p���b�g�ϊ��Ő^������
	SoftSpritePalFadeSet( p_pokegra, 15, 15, 0, 0 );

	// Y�I�t�Z�b�g�Ɗg��k���l�ݒ�
	ZknBigPokeGraYOfsSet( p_pokegra, ofs_y );
	ZknBigPokeGraScaleSet( p_pokegra, scale_num );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N��\��
 *
 *	@param	p_draw	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigPokeGraOff( ZKN_BIG_DRAWGLB* p_draw )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_draw->p_drawglb );

	// �\��OFF
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, TRUE );

	// �\�t�g�p���b�g�t�F�[�h���������Ă���\��������̂�OFF
	SoftSpritePalFadeOff( p_pokegra );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Y�I�t�Z�b�g�ƃX�P�[����ݒ�
 *
 *	@param	p_act		�A�N�^�[
 *	@param	yofs		Y�I�t�Z�b�g
 *	@param	scale		�g�k�l�p�����[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigHeroYOfsSet( CLACT_WORK_PTR p_act, short yofs )
{
	VecFx32				matrix;

	// ���W
	matrix.x = ZKN_BIG_HEIGHT_HERO_DEF_X << FX32_SHIFT;
	matrix.y = (ZKN_BIG_HEIGHT_HERO_DEF_Y + yofs) << FX32_SHIFT;
	CLACT_SetMatrix( p_act, &matrix );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Y�I�t�Z�b�g�ƃX�P�[����ݒ�
 *
 *	@param	p_pokegra	�|�P�����O���t�B�b�N
 *	@param	yofs		Y�I�t�Z�b�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigPokeGraYOfsSet( SOFT_SPRITE* p_pokegra, short yofs )
{
	// Y���W
	SoftSpriteParaSet( p_pokegra, SS_PARA_POS_Y, ZKN_BIG_HEIGHT_POKEGRA_DEF_Y + yofs );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��l���Ɋg�k�l��ݒ�
 *
 *	@param	p_act
 *	@param	scale 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigHeroScaleSet( CLACT_WORK_PTR p_act, short scale )
{
	VecFx32				vec_scale;

	// �g�k�l��ݒ�
	vec_scale.x = FX_Div( ZKN_HEIGHT_SCALDE_DEF << FX32_SHIFT, scale << FX32_SHIFT );
	vec_scale.y = vec_scale.x;
	CLACT_SetScaleAffine( p_act, &vec_scale, CLACT_AFFINE_DOUBLE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�߹��ׂɊg�k�l��ݒ�
 *
 *	@param	p_pokegra
 *	@param	scale 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigPokeGraScaleSet( SOFT_SPRITE* p_pokegra, short scale )
{
	fx32 fx_scale;

	// scale_num��0x100�����鐔�ɂȂ��Ă���iOAM�p�̊g�k�j
	// �����0x100�Ŋ��鐔�ɕύX
	fx_scale = FX_Div( ZKN_HEIGHT_SCALDE_DEF << FX32_SHIFT, scale << FX32_SHIFT );
	scale = FX_Mul( fx_scale, ZKN_HEIGHT_SCALDE_DEF << FX32_SHIFT ) >> FX32_SHIFT;
	
	// �g�k�ݒ�
	SoftSpriteParaSet( p_pokegra, SS_PARA_AFF_X, scale );
	SoftSpriteParaSet( p_pokegra, SS_PARA_AFF_Y, scale );
}

