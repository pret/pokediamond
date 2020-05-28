//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sys.c
 *	@brief		�}�ӃV�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.01.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "calctool.h"
#include "calc2d.h"
#include <string.h>
#include <nnsys.h>
#include "touchpanel_system.h"
#include "include/system/heapdefine.h"
#include "include/gflib/display.h"
#include "include/gflib/vram_transfer_manager.h"
#include "include/system/wipe.h"

#include "include/application/zukanlist/zkn_defain.h"
#include "include/application/zukanlist/zkn_snd_def.h"

// �`��֌W
#include "include/system/render_oam.h"
#include "include/gflib/char_manager.h"
#include "include/gflib/pltt_manager.h"
#include "gf_gx.h"

#include "button_man.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_sys_static.h"


#include "include/application/zukanlist/zkn_pokelist.h"
#include "include/application/zukanlist/zkn_pokelist_sub.h"
#include "include/application/zukanlist/zkn_sortsearch.h"
#include "include/application/zukanlist/zkn_sortsearch_sub.h"
#include "include/application/zukanlist/zkn_range.h"
#include "include/application/zukanlist/zkn_range_sub.h"
#include "include/application/zukanlist/zkn_zukan.h"
#include "include/application/zukanlist/zkn_zukan_graver.h"
#include "include/application/zukanlist/zkn_zukan_textver.h"
#include "include/application/zukanlist/zkn_zukan_sub.h"
#include "include/application/zukanlist/zkn_zukan_common.h"
#include "include/application/zukanlist/zkn_big.h"
#include "include/application/zukanlist/zkn_big_weight.h"
#include "include/application/zukanlist/zkn_big_sub.h"
#include "include/application/zukanlist/zkn_sound.h"
#include "include/application/zukanlist/zkn_sound_sub.h"
#include "include/application/zukanlist/zkn_event_func.h"
#include "include/application/zukanlist/zkn_world_text_sys.h"
#include "include/application/zukanlist/zkn_zukan_graver_sub.h"

#include "include/communication/wm_icon.h"

#ifdef PM_DEBUG
#include "include/application/zukanlist/zkn_big_debug_sub.h"
#endif

#define __ZKN_SYS_H_GLOBAL
#include "include/application/zukanlist/zkn_sys.h"

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
 *	�}�Ӄv���b�N
 */
//-----------------------------------------------------------------------------
#define ZKN_VRAMTRANSFER_MANAGER_NUM	( 8 )

#define ZKN_PROC_FADE_DIV	( 6 )
#define ZKN_PROC_FADE_SYNC	( 1 )


//-------------------------------------
//	
//	�}�Ӄv���b�N���[�N
//	
//=====================================
typedef struct {
	// �}�ӃV�X�e��
	ZKN_SYS_PTR		zkn_sys;
} ZKN_PROC_WORK;



//-----------------------------------------------------------------------------
/**
 *		�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
static void ZknVBlankFunc( void* work );

static void ZknFadeInReq( ZKN_PROC_WORK* p_work );
static void ZknFadeOutReq( ZKN_PROC_WORK* p_work );
static BOOL ZknFadeMain( ZKN_PROC_WORK* p_work );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӄv���b�N����
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT ZKN_ProcInit( PROC* proc, int* seq )
{
	ZKN_PROC_WORK* zkn_w;
	ZKN_PEARENT_DATA* zkn_pearent;
	ZKN_SYS_INIT_DATA zkn_init;
	BOOL check;

	// ��
	Snd_DataSetByScene( SND_SCENE_SUB_ZUKAN, 0, 0 );	// �T�E���h�f�[�^���[�h�i�}�Ӂj�iBGM���p���j

	// �q�[�v�쐬
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_ZUKAN, 0x40000 );

	// �}�Ӄ��[�N�쐬
	zkn_w = PROC_AllocWork( proc, sizeof(ZKN_PROC_WORK), HEAPID_ZUKAN );
	GF_ASSERT( zkn_w );
	memset( zkn_w, 0, sizeof(ZKN_PROC_WORK) );

	// VramTransferManager������
	initVramTransferManagerHeap( ZKN_VRAMTRANSFER_MANAGER_NUM, HEAPID_ZUKAN );

	// �}�ӊǗ��҃f�[�^���擾
	zkn_pearent = PROC_GetParentWork( proc );

	// VBlank HBlank�ݒ�
	sys_VBlankFuncChange( ZknVBlankFunc, zkn_w );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	// �^�b�`�p�l���I�[�g�T���v�����O�J�n
	InitTPSystem();
	check = InitTPNoBuff( 4 );
	GF_ASSERT( check == TP_OK );

	// �`��Z�b�g�A�b�v
	ZKN_SYS_SetUpDraw( HEAPID_ZUKAN );

	// �}�ӃV�X�e���쐬
	zkn_init.cp_zukansave_data	= zkn_pearent->cp_zukansave_data;
	zkn_init.cp_hero_data		= zkn_pearent->cp_hero_data;
	zkn_init.time_zone			= zkn_pearent->time_zone;
	zkn_init.hidemap_id_D15		= zkn_pearent->hidemap_id_D15;
	zkn_init.hidemap_id_D18		= zkn_pearent->hidemap_id_D18;
	zkn_init.hidemap_id_D30		= zkn_pearent->hidemap_id_D30;
	zkn_init.hidemap_id_L04		= zkn_pearent->hidemap_id_L04;
	zkn_init.p_zkn_work			= zkn_pearent->p_zkn_work;
	zkn_w->zkn_sys = ZKN_SYS_Init( HEAPID_ZUKAN, &zkn_init );

	// �����i��
	//Snd_BgmFadeOut( BGM_VOL_ZUKAN, BGM_FADE_ZUKAN_TIME );		//�t�F�[�h�A�E�g
	Snd_PlayerSetPlayerVolume( PLAYER_FIELD, BGM_VOL_ZUKAN );
	
	return PROC_RES_FINISH;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӄv���b�N���C��
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT ZKN_ProcMain( PROC* proc, int* seq )
{
	ZKN_PROC_WORK* zkn_w = PROC_GetWork( proc );
	BOOL ret;

#if 1
	switch( *seq ){
	// �t�F�[�h�C��
	case 0:
		ZknFadeInReq( zkn_w );
		SetBrightness( BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );
		(*seq)++;
		break;
/*	case 1:
		if( ZknFadeMain( zkn_w ) ){
			(*seq)++;
		}
		break;//*/
		
	// ���C������
	case 1:
		ret = ZKN_SYS_Main( zkn_w->zkn_sys );

		// �I���`�F�b�N
		if( ret == TRUE ){
			zkn_w->zkn_sys = NULL;
			(*seq)++;
		}
		break;

	// �t�F�[�h�A�E�g
	case 2:
		ZknFadeOutReq( zkn_w );
		(*seq)++;
		break;
	case 3:
		if( ZknFadeMain( zkn_w ) ){
			WIPE_ResetWndMask( WIPE_DISP_MAIN );
			WIPE_ResetWndMask( WIPE_DISP_SUB );
			G2_BlendNone();
			G2S_BlendNone();
			return PROC_RES_FINISH;
		}
		break;
	}
#else
	ret = ZKN_SYS_Main( zkn_w->zkn_sys );

	// �I���`�F�b�N
	if( ret == TRUE ){
		zkn_w->zkn_sys = NULL;
		return PROC_RES_FINISH;
	}
#endif

	return PROC_RES_CONTINUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӄv���b�N�I��
 *
 *	@param	proc		�v���b�N�f�[�^	
 *	@param	seq			�V�[�P���X
 *
 *	@return	������
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<����p����
 *		PROC_RES_FINISH,			///<����I��
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT ZKN_ProcEnd( PROC* proc, int* seq )
{
	ZKN_PROC_WORK* zkn_w = PROC_GetWork( proc );
	BOOL check;

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g

	// �^�b�`�p�l���T���v�����O�I��
	check = StopTP();
	GF_ASSERT( check == TP_OK );
	
	// �\���f�[�^�j��
	ZKN_SYS_ReleaseDraw();

	// VramTransferManager�j��
	DellVramTransferManager();

	// ���[�N�j��
	PROC_FreeWork( proc );

	// �q�[�v�j��
	sys_DeleteHeap( HEAPID_ZUKAN );

	// ����߂�
	//Snd_BgmFadeIn( BGM_VOL_MAX, BGM_FADE_ZUKAN_TIME, BGM_FADEIN_START_VOL_NOW );
	Snd_PlayerSetPlayerVolume( PLAYER_FIELD, BGM_VOL_MAX );

	return PROC_RES_FINISH;
}


//-----------------------------------------------------------------------------
/**
 *			�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	VBlank�֐�
 *
 *	@param	work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknVBlankFunc( void* work )
{
	ZKN_PROC_WORK* zkn_w = work;

	if( zkn_w->zkn_sys ){
		ZKN_Vblank( zkn_w->zkn_sys  );
	}

	// Vram�]���^�X�N
	DoVramTransferManager();
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�C���ݒ�
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFadeInReq( ZKN_PROC_WORK* p_work )
{
	WIPE_SYS_Start(
			WIPE_PATTERN_WMS,
			WIPE_TYPE_FADEIN,
			WIPE_TYPE_FADEIN,
			WIPE_FADE_BLACK,
			ZKN_PROC_FADE_DIV,
			ZKN_PROC_FADE_SYNC,
			HEAPID_ZUKAN
			);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�A�E�g�ݒ�
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknFadeOutReq( ZKN_PROC_WORK* p_work )
{
	WIPE_SYS_Start(
			WIPE_PATTERN_WMS,
			WIPE_TYPE_FADEOUT,
			WIPE_TYPE_FADEOUT,
			WIPE_FADE_BLACK,
			ZKN_PROC_FADE_DIV,
			ZKN_PROC_FADE_SYNC,
			HEAPID_ZUKAN
			);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�`�F�b�N
 *
 *	@param	p_work	���[�N
 *
 *	@retval	TRUE		�t�F�[�h�I��
 *	@retval	FALSE		�t�F�[�h��
 */
//-----------------------------------------------------------------------------
static BOOL ZknFadeMain( ZKN_PROC_WORK* p_work )
{
	return WIPE_SYS_EndCheck();
}















//-----------------------------------------------------------------------------
/**
 *		�}�ӃV�X�e��
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *			�}�ӃV�X�e���f�[�^
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�}�ӃV�X�e���\����
//=====================================
typedef struct _ZKN_SYS{
	// �I���t���O
	BOOL				zkn_delete;
	// �q�[�v
	int					heap;

	// �}�Ӄ��[�N
	ZKN_DATA_WORK*		p_zkn_work;

	// �O���[�o���f�[�^
	ZKN_GLB_DATA	glb;
	
	// �`��O���[�o���f�[�^
	ZKN_GLB_DRAWDATA draw_glb;
	

	//-----------------------------------------------------------------------------
	/**
	 *		�C�x���g�֌W		�i��������j
	 */
	//-----------------------------------------------------------------------------
	// �C�x���g�L�[
	// �e�A�v���P�[�V�����p�C�x���g�L�[
	int					event_key_main;	
	int					event_key_sub;	
	// �����A�v���P�[�V�������ʂœ����A�v���P�[�V�����p�C�x���g�L�[�i�D��x�����j
	int					event_key_common_main;
	int					event_key_common_sub;
	
	// �C�x���g�Ǘ�
	// �e�A�v���P�[�V�����p
	ZKN_EVENT_SYS_PTR	event_main;	
	ZKN_EVENT_SYS_PTR	event_sub;
	// �����A�v���P�[�V�������ʂœ����A�v���P�[�V�����p
	ZKN_EVENT_SYS_PTR	event_main_common;
	ZKN_EVENT_SYS_PTR	event_sub_common;

	// �A�v���P�[�V�����J�n�C�x���g�f�[�^
	ZKN_EVENT_DATA	event_apl_start_main;

	//-----------------------------------------------------------------------------
	/**
	 *		�A�v���P�[�V�����֌W
	 */
	//-----------------------------------------------------------------------------
	// �e�A�v���P�[�V�����f�[�^
	ZKN_APL_DATA	main_apl_data[ ZKN_SYS_APLMAIN_NUM ];
	ZKN_APL_DATA	sub_apl_data[ ZKN_SYS_APLSUB_NUM ];
	
	//-------------------------------------
	//	�؂�ւ��A�v���P�[�V����
	//=====================================
	// ���C���@�T�u�@�v���Z�X�Ǘ�
	ZKN_PROC_SYS_PTR	main_proc;
	ZKN_PROC_SYS_PTR	sub_proc;

	//-------------------------------------
	//	�����ƕ\������Ă���A�v���P�[�V����
	//=====================================
	// �e�A�v���P�[�V�������ʕ����v���b�N
	ZKN_PROC_SYS_PTR	main_common_proc;
	ZKN_PROC_SYS_PTR	sub_common_proc;
	
} ZKN_SYS;




//-----------------------------------------------------------------------------
/**
 *				�֐��|�C���^�e�[�u��
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//		�A�v���P�[�V�����f�[�^�쐬
//=====================================
// ���C����ʃA�v��
const static ZKN_APL_DATA_MAKE_FUNC ZknAplMainDataMakeFunc[ ZKN_SYS_APLMAIN_NUM ] = {
	ZKN_PokeListAplMake,
	ZKN_SortSearchAplMake,
	ZKN_ZukanAplMake,
	ZKN_ZukanGraverAplMake,
	ZKN_ZukanTextverAplMake,
	ZKN_ZukanCommonAplMake,
	ZKN_RangeAplMake,
	ZKN_SoundAplMake,
	ZKN_BigAplMake,
	ZKN_BigWeAplMake,
};
// �T�u��ʃA�v��
const static ZKN_APL_DATA_MAKE_FUNC ZknAplSubDataMakeFunc[ ZKN_SYS_APLSUB_NUM ] = {
	ZKN_PokeListSubAplMake,
	ZKN_SortSearchSubAplMake,
	ZKN_ZukanSubAplMake,
	ZKN_ZukanCommonSubAplMake,
	ZKN_RangeSubAplMake,
	ZKN_SoundSubAplMake,
	ZKN_BigSubAplMake,
	ZKN_GraphicSubAplMake,

#ifdef PM_DEBUG
	ZKN_BigDebugAplMake,
#endif
};

//-------------------------------------
//		�A�v���P�[�V�����f�[�^�j��
//=====================================
// ���C����ʃA�v��
const static ZKN_APL_DATA_DELETE_FUNC ZknAplMainDataDeleteFunc[ ZKN_SYS_APLMAIN_NUM ] = {
	ZKN_PokeListAplDelete,
	ZKN_SortSearchAplDelete,
	ZKN_ZukanAplDelete,
	ZKN_ZukanGraverAplDelete,
	ZKN_ZukanTextverAplDelete,
	ZKN_ZukanCommonAplDelete,
	ZKN_RangeAplDelete,
	ZKN_SoundAplDelete,
	ZKN_BigAplDelete,
	ZKN_BigWeAplDelete,
};
// �T�u��ʃA�v��
const static ZKN_APL_DATA_DELETE_FUNC ZknAplSubDataDeleteFunc[ ZKN_SYS_APLSUB_NUM ] = {
	ZKN_PokeListSubAplDelete,
	ZKN_SortSearchSubAplDelete,
	ZKN_ZukanSubAplDelete,
	ZKN_ZukanCommonSubAplDelete,
	ZKN_RangeSubAplDelete,
	ZKN_SoundSubAplDelete,
	ZKN_BigSubAplDelete,
	ZKN_GraphicSubAplDelete,

#ifdef PM_DEBUG
	ZKN_BigDebugAplDelete,
#endif
};

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void DeleteZkn( ZKN_SYS_PTR zkn );

static void VramBankSet( void );
static void OamSet( int heap );
static void setup_3d( void );
static void putback_3d( void );


static void StartAlp( ZKN_SYS_PTR zkn );

static void MakeMainAplStartEvent( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys );
static void DeleteMainAplStartEvent( ZKN_EVENT_DATA* p_event_data );

static void MakeSubAplStartEvent( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys );
static void DeleteSubAplStartEvent( ZKN_EVENT_DATA* p_event_data );

//-----------------------------------------------------------------------------
/**
 *			�A�v���P�[�V�����J�n�C�x���g
 */
//-----------------------------------------------------------------------------
#define ZKN_SYS_EVENT_MSK_APL_START  ( 1 )	// �A�v���P�[�V�����X�^�[�g



//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃV�X�e��������
 *
 *	@param	heap	�g�p����q�[�v
 *	@param	p_init	�V�X�e���������f�[�^
 *
 *	@return	�쐬�����}�ӃV�X�e��
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_SYS_PTR ZKN_SYS_Init( int heap, const ZKN_SYS_INIT_DATA* p_init )
{
	ZKN_SYS_PTR zkn_sys;
	int i;
	ZKN_GLB_DATA_INIT glb_init;

	// ���C���V�X�e�����[�N�쐬
	zkn_sys = sys_AllocMemory( heap, sizeof(ZKN_SYS) );
	GF_ASSERT( zkn_sys );
	memset( zkn_sys, 0, sizeof(ZKN_SYS) );

	// �q�[�v
	zkn_sys->heap	= heap;
	
	// �}�ӃO���[�o�����[�N�ݒu
	zkn_sys->p_zkn_work = p_init->p_zkn_work;

	// �C�x���g�V�X�e���쐬
	zkn_sys->event_main	= ZKN_EVENT_MemoryAlloc( heap );
	zkn_sys->event_sub	= ZKN_EVENT_MemoryAlloc( heap );
	zkn_sys->event_main_common = ZKN_EVENT_MemoryAlloc( heap );
	zkn_sys->event_sub_common  = ZKN_EVENT_MemoryAlloc( heap );

	// �v���Z�X�Ǘ��V�X�e���쐬
	zkn_sys->main_proc = ZKN_PROC_MemoryAlloc( heap );
	zkn_sys->sub_proc = ZKN_PROC_MemoryAlloc( heap );
	zkn_sys->main_common_proc = ZKN_PROC_MemoryAlloc( heap );
	zkn_sys->sub_common_proc = ZKN_PROC_MemoryAlloc( heap );

	
	// �O���[�o���f�[�^������
	glb_init.cp_zukansave_data = p_init->cp_zukansave_data;
	glb_init.cp_hero_data = p_init->cp_hero_data;
	glb_init.time_zone = p_init->time_zone;
	glb_init.hidemap_id_D15 = p_init->hidemap_id_D15;
	glb_init.hidemap_id_D30 = p_init->hidemap_id_D30;
	glb_init.hidemap_id_L04 = p_init->hidemap_id_L04;
	glb_init.hidemap_id_D18 = p_init->hidemap_id_D18;
	glb_init.init_list_monsno = ZKN_DW_GetListMonsNo( p_init->p_zkn_work );
	glb_init.zkn_mode = ZKN_DW_GetZknMode( p_init->p_zkn_work );
	ZKN_GLBDATA_Init( &zkn_sys->glb, &glb_init, heap );

	// �`��O���[�o���f�[�^������
	ZKN_GlbDrawDataInit( &zkn_sys->draw_glb, heap );

	

	// �A�v���P�[�V�����f�[�^�쐬
	for( i=0; i<ZKN_SYS_APLMAIN_NUM; i++ ){
		if( ZknAplMainDataMakeFunc[ i ] ){
			ZknAplMainDataMakeFunc[ i ]( &zkn_sys->main_apl_data[ i ], zkn_sys, heap );
		}
	}
	for( i=0; i<ZKN_SYS_APLSUB_NUM; i++ ){
		if( ZknAplSubDataMakeFunc[ i ] ){
			ZknAplSubDataMakeFunc[ i ]( &zkn_sys->sub_apl_data[ i ], zkn_sys, heap );
		}
	}

	// �A�v���P�[�V�����J�n�C�x���g�쐬
	ZKN_EVENT_MakeChangePokeList( heap, &zkn_sys->event_apl_start_main, zkn_sys, ZKN_SYS_EVENT_MSK_APL_START );

	// �ŏ��̃A�v���P�[�V�����C�x���g���s
	StartAlp( zkn_sys );

	// �ʐM�A�C�R���ݒ�
/*	
	WirelessIconEasy();	


	CLACT_U_WmIcon_SetReserveAreaCharManager( NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_128K );
	CLACT_U_WmIcon_SetReserveAreaPlttManager( NNS_G2D_VRAM_TYPE_2DMAIN );
//*/

	return zkn_sys;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӄ��C��
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *
 *	@retval	TRUE	�I��	�������̂͂����I��
 *	@retval	FALSE	���s
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_SYS_Main( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );


	// �^�b�`�p�l���J�[�\���t���O�ݒ�
	ZKN_GLBDATA_TouchCursorFlagSet( &zkn->glb );


	// �C�x���g���͓����Ȃ�
	if( (ZKN_EVENT_DoCheck( zkn->event_main_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_main ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub ) == FALSE) ){
		
		ZKN_PROC_MoveLock( zkn->main_common_proc, FALSE );		// ���C����ʁ@�����A�v������
		ZKN_PROC_MoveLock( zkn->sub_common_proc, FALSE );		// �T�u��ʁ@�����A�v������
		ZKN_PROC_MoveLock( zkn->main_proc, FALSE );			// ���C�����
		ZKN_PROC_MoveLock( zkn->sub_proc, FALSE );				// �T�u���
	}else{
		ZKN_PROC_MoveLock( zkn->main_common_proc, TRUE );		// ���C����ʁ@�����A�v������
		ZKN_PROC_MoveLock( zkn->sub_common_proc, TRUE );		// �T�u��ʁ@�����A�v������
		ZKN_PROC_MoveLock( zkn->main_proc, TRUE );			// ���C�����
		ZKN_PROC_MoveLock( zkn->sub_proc, TRUE );				// �T�u���
	}


	// �v���Z�X����
	ZKN_PROC_Main( zkn->main_common_proc );		// ���C����ʁ@�����A�v������
	ZKN_PROC_Main( zkn->sub_common_proc );		// �T�u��ʁ@�����A�v������
	ZKN_PROC_Main( zkn->main_proc );			// ���C�����
	ZKN_PROC_Main( zkn->sub_proc );				// �T�u���

	ZKN_PROC_Draw( zkn->main_common_proc );		// ���C����ʁ@�����A�v������
	ZKN_PROC_Draw( zkn->sub_common_proc );		// �T�u��ʁ@�����A�v������
	ZKN_PROC_Draw( zkn->main_proc );			// ���C�����
	ZKN_PROC_Draw( zkn->sub_proc );				// �T�u���

	//-----------------------------------------------------------------------------
	/**
	 *			�C�x���g����		(��������)
	 *			common�̕��̔����D�悷��
	 *			�����P���삵�Ă���C�x���g������Α��͓����Ȃ�
	 */
	//-----------------------------------------------------------------------------
	// �����A�v�����ʃA�v���C�x���g�Ǘ�
	// ���C����ʃC�x���g
	if( (ZKN_EVENT_DoCheck( zkn->event_main ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub ) == FALSE) ){

		ZKN_EVENT_Main( zkn->event_main_common, zkn->event_key_common_main );	
	}
	if( (ZKN_EVENT_DoCheck( zkn->event_main_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub ) == FALSE) ){
		ZKN_EVENT_Main( zkn->event_main, zkn->event_key_main );
	}

	// �e�A�v���C�x���g�Ǘ�
	if( (ZKN_EVENT_DoCheck( zkn->event_main_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_main ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub ) == FALSE) ){
		ZKN_EVENT_Main( zkn->event_sub_common, zkn->event_key_common_sub );
	}
	if( (ZKN_EVENT_DoCheck( zkn->event_main_common ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_main ) == FALSE) &&
		(ZKN_EVENT_DoCheck( zkn->event_sub_common ) == FALSE) ){
		ZKN_EVENT_Main( zkn->event_sub, zkn->event_key_sub );
	}

	// �`��main
	GF_G3X_Reset();
	
	ZKN_GlbDrawDataMain( &zkn->draw_glb );
	
	/* �W�I���g���������_�����O�G���W���֘A�������̃X���b�v */
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);

	// �C�x���g�L�[�N���A
	zkn->event_key_common_main = 0;
	zkn->event_key_common_sub = 0;
	zkn->event_key_main = 0;
	zkn->event_key_sub	= 0;


	// �I���`�F�b�N
	if( zkn->zkn_delete == TRUE ){

		// �j��
		DeleteZkn( zkn );
		zkn = NULL;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��֌W�̃Z�b�g�A�b�v
 *
 *	@param	heap	�g�p�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SYS_SetUpDraw( int heap )
{
	// �o���N�Z�b�g�A�b�v
	VramBankSet();
	
	// oam�֌W�Z�b�g�A�b�v
	OamSet( heap );


	// 3D��
	setup_3d();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��֌W�̔j��
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SYS_ReleaseDraw( void )
{
	// �����_���[���LOAM�}�l�[�W���j��
	REND_OAM_Delete();
	
	// �L�����N�^�f�[�^�j��
	DeleteCharManager();
	// �p���b�g�f�[�^�j��
	DeletePlttManager();

	// 3D��
	putback_3d();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	V�u�����N���Ԋ֐�
 *
 *	@param	zkn		�}�ӃV�X�e�� 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_Vblank( ZKN_SYS_PTR zkn )
{
	ZKN_GlbDrawDataVBlank( &zkn->draw_glb );

	// �����_���[OAM�]��
	REND_OAMTrans();
}



//-----------------------------------------------------------------------------
/**
 *		�}�ӃV�X�e���̂ݎQ�Ɖ\
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	���C����ʃv���Z�X�V�X�e���擾
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *	@return	�v���Z�X�V�X�e��
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_PROC_SYS_PTR ZKN_SYS_GetProcSysMain( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->main_proc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�u��ʃv���Z�X�V�X�e���擾
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *	@return	�v���Z�X�V�X�e��
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_PROC_SYS_PTR ZKN_SYS_GetProcSysSub( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->sub_proc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���C����ʋ��ʃv���Z�X�V�X�e��
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *	@return	�v���Z�X�V�X�e��
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_PROC_SYS_PTR ZKN_SYS_GetProcSysMainCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->main_common_proc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�u��ʋ��ʃv���Z�X�V�X�e��
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *	@return	�v���Z�X�V�X�e��
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_PROC_SYS_PTR ZKN_SYS_GetProcSysSubCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->sub_common_proc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���C����� �C�x���g�V�X�e���|�C���^�擾
 *
 *	@param	zkn �}�ӃV�X�e��
 *
 *	@return	�C�x���g�V�X�e���|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysMain( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->event_main;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�u��� �C�x���g�V�X�e���|�C���^�擾
 *
 *	@param	zkn �}�ӃV�X�e��
 *
 *	@return	�C�x���g�V�X�e���|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysSub( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->event_sub;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���C����� ���ʃA�v�� �C�x���g�V�X�e���|�C���^�擾
 *
 *	@param	zkn �}�ӃV�X�e��
 *
 *	@return	�C�x���g�V�X�e���|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysMainCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->event_main_common;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�u��� ���ʃA�v�� �C�x���g�V�X�e���|�C���^�擾
 *
 *	@param	zkn �}�ӃV�X�e��
 *
 *	@return	�C�x���g�V�X�e���|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysSubCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return zkn->event_sub_common;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C�x���g�L�[�|�C���^�擾
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�L�[�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
int* ZKN_SYS_GetEventKeyPtrMain( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->event_key_main;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C�x���g�L�[�|�C���^�擾
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�L�[�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
int* ZKN_SYS_GetEventKeyPtrSub( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->event_key_sub;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C�x���g�L�[�|�C���^�擾
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�L�[�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
int* ZKN_SYS_GetEventKeyPtrMainCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->event_key_common_main;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C�x���g�L�[�|�C���^�擾
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�L�[�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
int* ZKN_SYS_GetEventKeyPtrSubCommon( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->event_key_common_sub;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӕj���t���O�擾
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *	@return	�}�Ӕj���t���O
 *
 * �}�Ӕj���t���O�́A���S�Ƀ�������j�����Ă����v��
 * ��ԂɂȂ��Ă���TRUE�ɂ���
 *
 */
//-----------------------------------------------------------------------------
BOOL* ZKN_SYS_GetZknDeleteFlag( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->zkn_delete;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�O���[�o���f�[�^�擾
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *	@return	�}�ӃO���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_GLB_DATA* ZKN_SYS_GetGlbData( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӕ`��O���[�o���f�[�^
 *
 *	@param	zkn		�}�ӃV�X�e��
 *
 *	@return	�}�ӕ`��O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_GLB_DRAWDATA* ZKN_SYS_GetGlbDrawData( ZKN_SYS_PTR zkn )
{
	GF_ASSERT( zkn );

	return &zkn->draw_glb;
}

//----------------------------------------------------------------------------
/**
 *[main���]
 *	@brief	�}�ӃA�v���P�[�V�����f�[�^�擾
 *
 *	@param	zkn			�}�ӃV�X�e��
 *	@param	apl_no		�A�v���P�[�V�����f�[�^
 *
 *	@return	�A�v���P�[�V�����f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_APL_DATA* ZKN_GetAplDataMain( ZKN_SYS_PTR zkn, int apl_no )
{
	GF_ASSERT( apl_no < ZKN_SYS_APLMAIN_NUM );

	return &zkn->main_apl_data[ apl_no ];
}

//----------------------------------------------------------------------------
/**
 *[sub���]
 *	@brief	�}�ӃA�v���P�[�V�����f�[�^�擾
 *
 *
 *	@param	zkn			�}�ӃV�X�e��
 *	@param	apl_no		�A�v���P�[�V�����f�[�^
 *
 *	@return	�A�v���P�[�V�����f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_APL_DATA* ZKN_GetAplDataSub( ZKN_SYS_PTR zkn, int apl_no )
{
	GF_ASSERT( apl_no < ZKN_SYS_APLSUB_NUM );

	return &zkn->sub_apl_data[ apl_no ];
}



//-----------------------------------------------------------------------------
/**
 *		�����ȃA�v���P�[�V���������ʂ��Ďg�p�ł������
 */
//-----------------------------------------------------------------------------
#define ZKN_UTIL_BUTTON_ANIM_SPEED	( FX32_ONE * 2 )

#define ZKN_UTIL_FONTBUTTON_ANIM_PUSH1	( -2 )
#define ZKN_UTIL_FONTBUTTON_ANIM_PUSH2	( -4 )
#define ZKN_UTIL_FONTBUTTON_ANIM_SELECT	( -2 )

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���O���t�B�b�N���ʓ���
 *
 *	@param	act				�A�N�^�[
 *	@param	button_event	�{�^���C�x���g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_ButtonMove( CLACT_WORK_PTR act, int button_event )
{

	// �����ꂽ�Ƃ��A������Ă���Ƃ��̓A�j��
	switch( button_event ){
	case BMN_EVENT_TOUCH:		///< �G�ꂽ�u��
		CLACT_AnmFrameSet( act, ZKN_UTIL_BUTTON_FRAME_PUSH1 );
		break;

	case BMN_EVENT_HOLD:			///< �G��Â��Ă���
		// �v�b�V���Q�t���[���ڂ܂ŃA�j��
		CLACT_AnmFrameSet( act, ZKN_UTIL_BUTTON_FRAME_PUSH2 );
		break;
		
	case BMN_EVENT_RELEASE:		///< �����ꂽ�u��
		// �I���t���[����ݒ�
		CLACT_AnmFrameSet( act, ZKN_UTIL_BUTTON_FRAME_SELECT );
		break;//*/
		
	case BMN_EVENT_SLIDEOUT:		///< ��ʃ^�b�`�����܂܃{�^���̈悩��O�ꂽ�u��
	case ZKN_UTIL_BUTTON_PUSH_NONE:	///< ��������Ă��Ȃ��Ƃ�
		// �擪�܂ł��ǂ�
		if( CLACT_AnmFrameGet( act ) > ZKN_UTIL_BUTTON_FRAME_NONE ){
			CLACT_AnmFrameChg( act, -ZKN_UTIL_BUTTON_ANIM_SPEED );
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���t�H���g�̃{�^���A�j��
 *
 *	@param	act				�e�A�N�^�[
 *	@param	p_fontoam		�t�H���gOAM
 *	@param	def_y			������Y�ʒu
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_ButtonFontMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y )
{
	int button_anm = CLACT_AnmFrameGet( act );
	int x, y;

	switch( button_anm ){
	case ZKN_UTIL_BUTTON_FRAME_NONE:		// ����
		FONTOAM_GetMat( p_fontoam->p_fontoam, &x, &y );

		y = def_y;
		FONTOAM_SetMat( p_fontoam->p_fontoam, x, y );
		break;
		
	case ZKN_UTIL_BUTTON_FRAME_PUSH1:	// �v�b�V���A�j���P�t���[����
		FONTOAM_GetMat( p_fontoam->p_fontoam, &x, &y );

		y = def_y + ZKN_UTIL_FONTBUTTON_ANIM_PUSH1;
		FONTOAM_SetMat( p_fontoam->p_fontoam, x, y );
		break;
		
	case ZKN_UTIL_BUTTON_FRAME_PUSH2:	// �v�b�V���A�j���Q�t���[����
		FONTOAM_GetMat( p_fontoam->p_fontoam, &x, &y );

		y = def_y + ZKN_UTIL_FONTBUTTON_ANIM_PUSH2;
		FONTOAM_SetMat( p_fontoam->p_fontoam, x, y );
		break;
		
	case ZKN_UTIL_BUTTON_FRAME_SELECT:	// �I��
		FONTOAM_GetMat( p_fontoam->p_fontoam, &x, &y );

		y = def_y + ZKN_UTIL_FONTBUTTON_ANIM_SELECT;
		FONTOAM_SetMat( p_fontoam->p_fontoam, x, y );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���t�H���g�J���[�ύX����
 *
 *	@param	act				�A�N�^�[
 *	@param	p_fontoam		�{�^���t�H���g
 *	@param	def_y			�f�t�H���gY�ʒu
 *	@param	off_pltt		�I�t�J���[�p���b�g���ް
 *	@param	on_pltt			�I���J���[�p���b�g���ް
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_ButtonFontMove_Col( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt )
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
 *	@brief	�����蔻��e�[�u���f�[�^�ݒ�
 *
 *	@param	p_tbl		�e�[�u��
 *	@param	top			��
 *	@param	bottom		��
 *	@param	left		��
 *	@param	right		�E
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_HitTblDataSet( TP_HIT_TBL* p_tbl, int top, int bottom, int left, int right )
{
	p_tbl->rect.top = top;
	p_tbl->rect.bottom = bottom;
	p_tbl->rect.left = left;
	p_tbl->rect.right = right;
}


//----------------------------------------------------------------------------
/**
 *	@brief	BG�t�F�[�h�A�E�g������
 *
 *	@param	p_data		�t�F�[�h�f�[�^
 *	@param	p_bg		BG�V�X�e��
 *	@param	frm			�t���[���i���o�[
 *	@param	p_scrn		�X�N���[���f�[�^
 *	@param	top_cs		�t�F�[�h�J�n��̈ʒu
 *	@param	top_ce		�t�F�[�h�I����̈ʒu
 *	@param	bottom_cs	�t�F�[�h�J�n�����̈ʒu
 *	@param	bottom_ce	�t�F�[�h�I�������̈ʒu
 *	@param	count_max	�J�E���g�ő吔
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_BgShutterFadeInit( ZKN_UTIL_BGSHTTER_DADE* p_data, GF_BGL_INI* p_bg, int frm, NNSG2dScreenData* p_scrn, int top_cs, int top_ce, int bottom_cs, int bottom_ce, int count_max )
{
	p_data->p_bg		= p_bg;
	p_data->frm			= frm;
	p_data->p_scrn		= p_scrn;
	p_data->top_start	= top_cs;
	p_data->top_dis		= top_ce - top_cs;
	p_data->bottom_start= bottom_cs;
	p_data->bottom_dis	= bottom_ce - bottom_cs;
	p_data->move_count_max	= count_max;
	p_data->move_count	= 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�V���b�^�[�t�F�[�h
 *
 *	@param	p_data	�t�F�[�h�f�[�^
 *
 *	@retval	TRUE�@	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
BOOL ZKN_UTIL_BgShutterFade( ZKN_UTIL_BGSHTTER_DADE* p_data )
{
	int top_w_size;
	int bottom_w_size;

	
	if( p_data->move_count <= p_data->move_count_max ){

		// �X�N���[�����N���[��
		GF_BGL_ScrFill( p_data->p_bg, p_data->frm,
				0, 0, 0, 32, 24, GF_BGL_SCRWRT_PALNL );
		
		// �������݃T�C�Y�����߂�
		top_w_size = (p_data->top_dis * p_data->move_count) / p_data->move_count_max;
		bottom_w_size = (p_data->bottom_dis * p_data->move_count) / p_data->move_count_max;
		top_w_size += p_data->top_start;
		bottom_w_size += p_data->bottom_start;
		
		// �X�N���[���f�[�^��������
		if( top_w_size > 0 ){
			GF_BGL_ScrWriteExpand( p_data->p_bg, p_data->frm,
					0, 0,
					32, top_w_size,
					p_data->p_scrn->rawData,
					0, 32 - top_w_size,
					32, 32 );
		}

		// �X�N���[���f�[�^��������
		if( (32 - bottom_w_size) > 0 ){
			GF_BGL_ScrWriteExpand( p_data->p_bg, p_data->frm,
					0, 32 - bottom_w_size,
					32, bottom_w_size,
					p_data->p_scrn->rawData,
					0, 0,
					32, 32 );
		}
		
		// �X�N���[���f�[�^�]��
		GF_BGL_LoadScreenV_Req(p_data->p_bg, p_data->frm );


		p_data->move_count++;

		return FALSE;
	}
	
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�r�b�g�}�b�v�̈�ɐ����̖��O��z�u����
 *
 *	@param	p_bmp		�r�b�g�}�b�v�̈�
 *	@param	num			�����X�^�[�i���o�[
 *	@param	monsno		�����X�^�[ID
 *	@param	heap		�g�p�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_PokeListPokeNameBmpMake( GF_BGL_BMPWIN* p_bmp, int num, int monsno, int heap )
{
	STRBUF*	p_num;		// �|�P�����i���o�[
	STRBUF*	p_name;		// �|�P������


	// �����pSTR�o�b�t�@�쐬
	p_num = STRBUF_Create( ZKN_POKELIST_POKENAME_NO_NUM, heap );

	// �����쐬
	STRBUF_SetNumber( p_num, num, ZKN_POKELIST_POKENAME_NO_KETA,
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );

	// ���O�o�b�t�@�쐬
	p_name = ZKN_WT_GetPokeName( monsno, PM_LANG, heap );

	// ��������
	GF_STR_PrintColor( p_bmp, FONT_BUTTON, p_num, ZKN_POKELIST_POKENAME_NO_MAT_X, ZKN_POKELIST_POKENAME_MAT_Y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );
	GF_STR_PrintColor( p_bmp, FONT_BUTTON, p_name, ZKN_POKELIST_POKENAME_NAME_MAT_X, ZKN_POKELIST_POKENAME_MAT_Y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );
		
	// STRBUF�j��
	STRBUF_Delete( p_num );
	ZKN_WT_DeleteStrBuf( p_name );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g���r�b�g�}�b�v�f�[�^�쐬
 *
 *	@param	p_drawglb			�`��O���[�o��
 *	@param	cp_glb				�f�[�^�O���[�o��
 *	@param	heap				�q�[�v
 *	@param	mons_no				�����X�^�[�i���o�[
 *
 *	@return
	// BMP�̈�j��
	ZKN_FONTOAM_DeleteBmp( p_bmp );	�Ŕj�����Ă�������
 */
//-----------------------------------------------------------------------------
GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_GLB_DATA* cp_glb, int heap, int mons_no  )
{
	GF_BGL_BMPWIN* p_bmp;	

	// �����X�^�[�i���o�[�ύX����
	if( ZKN_GLBDATA_PokeZknModeGet( cp_glb ) == ZKN_MODE_SHINOH ){
		p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake_Shinou( p_drawglb->fontoam_sys, heap, mons_no );
	}else{
		p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake_Zenkoku( p_drawglb->fontoam_sys, heap, mons_no );
	}
	return p_bmp;
}

//----------------------------------------------------------------------------
/**
 * [��������mons_no�̒l�ŏ������ރo�[�W����]
 *	@brief	�|�P�������X�g���r�b�g�}�b�v�f�[�^�쐬	
 *
 *	@param	p_drawglb			�`��O���[�o��
 *	@param	heap				�q�[�v
 *	@param	mons_no				�����X�^�[�i���o�[
 *
 *	@return
	// BMP�̈�j��
	ZKN_FONTOAM_DeleteBmp( p_bmp );	�Ŕj�����Ă�������
 */
//-----------------------------------------------------------------------------
GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake_Zenkoku( ZKN_FONTOAM_SYS_PTR fontoam_sys, int heap, int mons_no )
{
	GF_BGL_BMPWIN* p_bmp;	// �������ݗ̈�

	// �����񏑂����ݗ̈�쐬
	p_bmp = ZKN_FONTOAM_GetBmp( fontoam_sys, ZKN_POKELIST_POKENAME_BMP_SIZE_CX, ZKN_POKELIST_POKENAME_BMP_SIZE_CY );

	// �r�b�g�}�b�v�̈�ɏ�������
	ZKN_UTIL_PokeListPokeNameBmpMake( p_bmp, mons_no, mons_no, heap );

	return p_bmp;
}

//----------------------------------------------------------------------------
/**
 * [mons_no�̒l���V���I�E�ɂ��Ȃ����ď������ރo�[�W����]
 *	@brief	�|�P�������X�g���r�b�g�}�b�v�f�[�^�쐬	
 *
 *	@param	p_drawglb			�`��O���[�o��
 *	@param	heap				�q�[�v
 *	@param	mons_no				�����X�^�[�i���o�[
 *
 *	@return
	// BMP�̈�j��
	ZKN_FONTOAM_DeleteBmp( p_bmp );	�Ŕj�����Ă�������
 */
//-----------------------------------------------------------------------------
GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake_Shinou( ZKN_FONTOAM_SYS_PTR fontoam_sys, int heap, int mons_no )
{
	GF_BGL_BMPWIN* p_bmp;	// �������ݗ̈�
	int mons_num;

	// �V���I�E�ɕύX
	mons_num = PokeZenkokuNo2ShinouNo( mons_no );

	// �����X�^�[�i���o�[���s���@�V���I�E�̃|�P��������Ȃ�
	GF_ASSERT_MSG( mons_num > 0, "mons_no[%d] not shinou poke", mons_no );

	// �����񏑂����ݗ̈�쐬
	p_bmp = ZKN_FONTOAM_GetBmp( fontoam_sys, ZKN_POKELIST_POKENAME_BMP_SIZE_CX, ZKN_POKELIST_POKENAME_BMP_SIZE_CY );

	// �r�b�g�}�b�v�̈�ɏ�������
	ZKN_UTIL_PokeListPokeNameBmpMake( p_bmp, mons_num, mons_no, heap );

	return p_bmp;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�`��O���[�o���G���A�Ƀ|�P���������X�g�f�[�^���쐬����
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *	@param	poke_tbl_no	�|�P�����e�[�u���i���o�[�iZKN_GLB_DATA���j
 *	@param	x			���X�g�e�[�u�����W
 *	@param	y			���X�g�e�[�u�����p
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_PokeListPokeNameMakeGlb( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_GLB_DATA* cp_glb, int heap, int poke_tbl_no, fx32 x, fx32 y )
{
	CLACT_WORK_PTR glb_act;
	CLACT_WORK_PTR glbicon_act;
	ZKN_FONTOAM_INIT fontoam_init;
	GF_BGL_BMPWIN* p_bmp;	// �������ݗ̈�
	CLACT_U_RES_OBJ_PTR pltt_obj;	// �p���b�g�v���N�V�擾�p
	VecFx32 mat;
	const ZKN_POKELIST_DATA* cp_pokedata;
	u32 zkn_mode = ZKN_GLBDATA_PokeZknModeGet( cp_glb );

	//�@�|�P�����f�[�^
	cp_pokedata = ZKN_GLBDATA_PokeListTblGet( cp_glb, poke_tbl_no );
	
	// �O���[�o���̈�ɂ���A�N�^�[�擾
	glb_act = ZKN_GlbPokeNameTblClactGet( p_drawglb );	
	glbicon_act = ZKN_GlbPokeNameIconClactGet( p_drawglb );
	
	// �|�P�������X�g�e�[�u���̍��W��ݒ�
	mat.x = x;
	mat.y = y;
	CLACT_SetMatrix( glb_act, &mat );
	CLACT_SetDrawFlag( glb_act, TRUE );	// �\��
	
	// �߂܂����|�P�����Ȃ�A�C�R���쐬
	if( cp_pokedata->type == ZKN_POKELIST_TYPE_GET ){
		mat.x = x + ZKN_POKELIST_ICON_X_OFS;
		mat.y = y;
		CLACT_SetMatrix( glbicon_act, &mat );
		CLACT_SetDrawFlag( glbicon_act, TRUE );	// �\��
	}else{
		CLACT_SetDrawFlag( glbicon_act, FALSE );	// �\��
	}
	

	// �|�P�������A�N�^�[�Ɏg�p����p���b�g�v���N�V�擾
	pltt_obj = ZKN_GlbPokeNameTblResObjGet( p_drawglb, CLACT_U_PLTT_RES );
		
	// �|�P�������A�N�^�[�쐬
	fontoam_init.zkn_fontoam = p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( pltt_obj, NULL );
	fontoam_init.parent		 = glb_act;
	fontoam_init.x			 = -(ZKN_POKELIST_POKENAME_BMP_SIZE_X / 2);
	fontoam_init.y			 = -(ZKN_POKELIST_POKENAME_BMP_SIZE_Y / 2);
	fontoam_init.bg_pri		 = 0;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;


	// �����񏑂����ݗ̈�쐬
	p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake( p_drawglb, cp_glb, heap, cp_pokedata->mons_no );			

	// FONTOAM�o�^
	fontoam_init.p_bmp = p_bmp;
	ZKN_GlbPokeNameTblSet( p_drawglb, &fontoam_init, 0, cp_pokedata->mons_no, zkn_mode );
	// BMP�̈�j��
	ZKN_FONTOAM_DeleteBmp( p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�\�����W��ݒ�
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	x			�����W
 *	@param	y			�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_PokeListPokeNameGlbMatrixSet(  ZKN_GLB_DRAWDATA* p_drawglb, int x, int y )
{
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet_Minute( &p_drawglb->pokelist_data_draw, x, y );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P���������X�g���W��ݒ�
 *
 *	@param	p_data
 *	@param	x
 *	@param	y 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_PokeListPokeNameGlbMatrixSet_Minute(  ZKN_POKELIST_DATA_OAM_DATA* p_data, int x, int y )
{
	VecFx32 mat;

	// �|�P�������X�g�e�[�u���̍��W��ݒ�
	mat.x = x << FX32_SHIFT;
	mat.y = y << FX32_SHIFT;
	CLACT_SetMatrix( p_data->pokelist_tbl, &mat );
	
	mat.x += ZKN_POKELIST_ICON_X_OFS;
	CLACT_SetMatrix( p_data->pokelist_icon, &mat );

	if( p_data->p_pokename->p_fontoam ){
		FONTOAM_ReflectParentMat( p_data->p_pokename->p_fontoam );	
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�ݒ�	���ʂ͎���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_glb		�`��O���[�o��
 *	@param	mons_no		�����X�^�[�i���o�[
 *	@param	dir			����
 *	@param	x			�����W
 *	@param	y			�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_UTIL_PokemonGraphicSet( ZKN_GLB_DRAWDATA* p_draw, ZKN_GLB_DATA* p_glb, int mons_no, int dir, int x, int y )
{
	// ����|�P�����ݒ肩�`�F�b�N
	if( mons_no == MONSNO_ANNOON ){
		// �A���m�[��
		ZKN_UTIL_PokemonGraphicSet_Anoon_Idx( p_draw, p_glb, dir, x, y, 0, 0 );
	}else if( mons_no == MONSNO_MINOMUTTI ){
		// �~�m���b�`
		ZKN_UTIL_PokemonGraphicSet_Minomutti_Idx( p_draw, p_glb, dir, x, y, 0, 0 );
	}else if( mons_no == MONSNO_MINOMESU ){
		// �~�m���X
		ZKN_UTIL_PokemonGraphicSet_Minomesu_Idx( p_draw, p_glb, dir, x, y, 0, 0 );
	}else if( mons_no == MONSNO_SIIUSI ){
		// �V�[�E�V	
		ZKN_UTIL_PokemonGraphicSet_Siiusi_Idx( p_draw, p_glb, dir, x, y, 0, 0 );
	}else if( mons_no == MONSNO_SIIDORUGO ){
		// �V�[�h���S
		ZKN_UTIL_PokemonGraphicSet_Siidorugo_Idx( p_draw, p_glb, dir, x, y, 0, 0 );

	}else if( mons_no == MONSNO_DEOKISISU ){
		// �f�I�L�V�X
		ZKN_UTIL_PokemonGraphicSet_Deokisisu_Idx( p_draw, p_glb, dir, x, y, 0, 0 );
	}else{
		// �ʏ�
		ZKN_UTIL_PokemonGraphicSet_FS_Idx( p_draw, p_glb, mons_no, dir, x, y,  ZUKAN_WORK_SEX_FIRST, 0 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�ݒ�@�������ݒ�p
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_glb		�`��O���[�o��
 *	@param	mons_no		�����X�^�[�i���o�[
 *	@param	dir			����
 *	@param	x			�����W
 *	@param	y			�����W
 *	@param	count		ZUKAN_WORK_SEX_FIRST�@ZUKAN_WORK_SEX_SECOND
 *	@param	idx			�|�P�����X�v���C�g�C���f�b�N�X
 *
 *	@retval	�ݒ肵�����ʃi���o�[
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	�G���[
 */
//-----------------------------------------------------------------------------
u32 ZKN_UTIL_PokemonGraphicSet_FS_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int mons_no, int dir, int x, int y, int count, int idx )
{
	int sex;
	u32 rnd = 0;

	if( mons_no == MONSNO_PATTIIRU ){
		// �p�b�`�[���̂Ƃ��́A�ő̗������擾
		rnd = ZKN_GLBDATA_SaveData_PattiruRndGet( cp_glb );
	}
	
	//�@���ʎ擾
	sex = ZKN_GLBDATA_SaveData_SexGet( cp_glb, mons_no, count );

	// ���ʂ���������ݒ�
	if( sex != ZUKAN_WORK_GET_SEX_ERR ){
		// �|�P�����ݒ�
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, mons_no,
				sex, dir, PARA_NORMAL, 0, rnd, x, y, idx );
	}
	
	return sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�A���m�[���ݒ�
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_glb		�`��O���[�o��
 *	@param	dir			����
 *	@param	x			X���W
 *	@param	y			Y���W
 *	@param	count		�J�E���g	�i0�`27�j
 *	@param	idx			�X�v���C�g�C���f�b�N�X
 *
 *	@retval	�ݒ肵���t�H�[���i���o�[
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	�G���[
 */
//-----------------------------------------------------------------------------
u32 ZKN_UTIL_PokemonGraphicSet_Anoon_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	
	form = ZKN_GLBDATA_SaveData_AnoonFormGet( cp_glb, count );
	
	// �t�H��������������ݒ�
	if( form != ZUKAN_WORK_GET_SEX_ERR ){

		// �|�P�����ݒ�
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_ANNOON,
				PARA_UNK, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�E�~�E�V�~�m���V�|�P�����ݒ�
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_glb		�`��O���[�o��
 *	@param	dir			����
 *	@param	x			X���W
 *	@param	y			Y���W
 *	@param	count		���Ԑ�	�i0�`2�j
 *	@param	idx			�X�v���C�g�z��C���f�b�N�X 
 *
 *	@retval	�ݒ肵���t�H�[��
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	�G���[
 */
//-----------------------------------------------------------------------------
u32 ZKN_UTIL_PokemonGraphicSet_Siiusi_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	form = ZKN_GLBDATA_SaveData_SiiusiFormGet( cp_glb, count );
	// �G���A����������ݒ�
	if( form != ZUKAN_WORK_GET_SEX_ERR ){
		// �|�P�����ݒ�
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_SIIUSI,
				PARA_MALE, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	return form;
}
u32 ZKN_UTIL_PokemonGraphicSet_Siidorugo_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	form = ZKN_GLBDATA_SaveData_SiidorugoFormGet( cp_glb, count );
	// �G���A����������ݒ�
	if( form != ZUKAN_WORK_GET_SEX_ERR ){
		// �|�P�����ݒ�
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_SIIDORUGO,
				PARA_MALE, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	return form;
}
u32 ZKN_UTIL_PokemonGraphicSet_Minomutti_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	form = ZKN_GLBDATA_SaveData_MinomuttiFormGet( cp_glb, count );
	// �G���A����������ݒ�
	if( form != ZUKAN_WORK_GET_SEX_ERR ){
		// �|�P�����ݒ�
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_MINOMUTTI,
				PARA_MALE, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	return form;
}
u32 ZKN_UTIL_PokemonGraphicSet_Minomesu_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	form = ZKN_GLBDATA_SaveData_MinomesuFormGet( cp_glb, count );
	// �G���A����������ݒ�
	if( form != ZUKAN_WORK_GET_SEX_ERR ){
		// �|�P�����ݒ�
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_MINOMESU,
				PARA_FEMALE, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	return form;
}
u32 ZKN_UTIL_PokemonGraphicSet_Deokisisu_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx )
{
	int form;
	form = ZKN_GLBDATA_SaveData_DeokisisuFormGet( cp_glb, count );
	// �G���A����������ݒ�
	if( form != POKEZUKAN_DEOKISISU_INIT ){
		// �|�P�����ݒ�
		ZKN_GlbPokemonGraphicSet_Idx( p_draw, MONSNO_DEOKISISU,
				PARA_FEMALE, dir, PARA_NORMAL, form, 0, x, y, idx );
	}
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}��GMM���當������擾
 *
 *	@param	data_idx		�ް�IDX
 *	@param	heap			�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
STRBUF* ZKN_UTIL_ZknGmmGet( int data_idx, int heap )
{
	STRBUF* str;
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	str = MSGMAN_AllocString( man, data_idx );

	MSGMAN_Delete(man);

	return str;
}




//-----------------------------------------------------------------------------
/**
 *			�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	�}�Ӕj��
 *
 *	@param	zkn 
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZkn( ZKN_SYS_PTR zkn )
{
	int i;

	// �}�ӃV�X�e���A�v���J�n�C�x���g�f�[�^�j��
	ZKN_EVENT_DeleteData( &zkn->event_apl_start_main );
	
	//�@�C�x���g�f�[�^�j��
	GF_ASSERT(zkn->event_main);
	sys_FreeMemoryEz( zkn->event_main );
	GF_ASSERT(zkn->event_sub);
	sys_FreeMemoryEz( zkn->event_sub );
	GF_ASSERT(zkn->event_main_common);
	sys_FreeMemoryEz( zkn->event_main_common );
	GF_ASSERT(zkn->event_sub_common);
	sys_FreeMemoryEz( zkn->event_sub_common );

	// �v���Z�X�f�[�^�j��
	GF_ASSERT(zkn->main_proc);
	sys_FreeMemoryEz( zkn->main_proc );
	GF_ASSERT(zkn->sub_proc);
	sys_FreeMemoryEz( zkn->sub_proc );
	GF_ASSERT(zkn->main_common_proc);
	sys_FreeMemoryEz( zkn->main_common_proc );
	GF_ASSERT(zkn->sub_common_proc);
	sys_FreeMemoryEz( zkn->sub_common_proc );

	// �A�v���P�[�V�����f�[�^�j��
	for( i=0; i<ZKN_SYS_APLMAIN_NUM; i++ ){
		if(ZknAplMainDataDeleteFunc[i]){
			ZknAplMainDataDeleteFunc[i]( &zkn->main_apl_data[ i ] );
		}
	}
	for( i=0; i<ZKN_SYS_APLSUB_NUM; i++ ){
		if(ZknAplSubDataDeleteFunc[i]){
			ZknAplSubDataDeleteFunc[i]( &zkn->sub_apl_data[ i ] );
		}
	}

	// �O���[�o���f�[�^�ۑ�
	ZKN_DW_SetListMonsNo( zkn->p_zkn_work, ZKN_GLBDATA_PokeTextSeeGetMonsno( &zkn->glb ) );	// ���X�g�̃����X�^�[�i���o�[
	// �[���R�N�}�ӕێ����Ă��邩�`�F�b�N
	if( ZKN_GLBDATA_PokeZknModeChengeCheck( &zkn->glb, ZKN_MODE_ZENKOKU ) == TRUE ){
		ZKN_DW_SetZknMode( zkn->p_zkn_work, ZKN_GLBDATA_PokeTextSeeGetZknMode( &zkn->glb ) );
	}else{
		// �܂��[���R�N�}�ӂ������Ă��Ȃ����́ANAZO
		ZKN_DW_SetZknMode( zkn->p_zkn_work, ZKN_MODE_NAZO );
	}

	// �O���[�o���f�[�^�j��
	ZKN_GLBDATA_Delete( &zkn->glb );
	// �`��O���[�o���f�[�^�j��
	ZKN_GlbDrawDataDelete( &zkn->draw_glb );

	sys_FreeMemoryEz( zkn );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VramBank�Z�b�g�A�b�v
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void VramBankSet( void )
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_B,				// ���C��2D�G���W����BG
		GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
		GX_VRAM_SUB_BG_128_C,			// �T�u2D�G���W����BG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// �T�u2D�G���W����BG�g���p���b�g
		GX_VRAM_OBJ_80_EF,				// ���C��2D�G���W����OBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
		GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
		GX_VRAM_TEX_0_A,				// �e�N�X�`���C���[�W�X���b�g
		GX_VRAM_TEXPLTT_0_G				// �e�N�X�`���p���b�g�X���b�g
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAM�Z�b�g�A�b�v
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void OamSet( int heap )
{
	// OAM�}�l�[�W���[�̏�����
	NNS_G2dInitOamManagerModule();

	// ���LOAM�}�l�[�W���쐬
	// �����_���pOAM�}�l�[�W���쐬
	// �����ō쐬����OAM�}�l�[�W�����݂�Ȃŋ��L����
	REND_OAMInit( 
			OAM_OAM_MAIN_S, OAM_OAM_MAIN_E,	// ���C�����OAM�Ǘ��̈�
			OAM_AFF_MAIN_S, OAM_AFF_MAIN_E,		// ���C����ʃA�t�B���Ǘ��̈�
			OAM_OAM_SUB_S, OAM_OAM_SUB_E,		// �T�u���OAM�Ǘ��̈�
			OAM_AFF_SUB_S, OAM_AFF_SUB_E,		// �T�u��ʃA�t�B���Ǘ��̈�
			heap);
	
	// �L�����N�^�}�l�[�W���[������
	{
		CHAR_MANAGER_MAKE cm = {
			OAM_CHAR_ENTRY_NUM,
			OAM_CHAR_VRAMTRANS_MAIN_SIZE,
			OAM_CHAR_VRAMTRANS_SUB_SIZE,
		};
		cm.heap = heap;
		
		InitCharManagerReg(&cm, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K );
	}
	// �p���b�g�}�l�[�W���[������
	InitPlttManager(OAM_PLTT_ENTRY_NUM, heap);

	// �ǂݍ��݊J�n�ʒu��������
	CharLoadStartAll();
	PlttLoadStartAll();

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�v���P�[�V�������J�n
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void StartAlp( ZKN_SYS_PTR zkn )
{
	ZKN_EVENT_Init( zkn->event_main, &zkn->event_apl_start_main, 1 );
	zkn->event_key_main = ZKN_SYS_EVENT_MSK_APL_START;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	3D�ʐݒ�
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setup_3d( void )
{
	// NitroSystem:�R�c�G���W���̏�����
	NNS_G3dInit();
	// �}�g���N�X�X�^�b�N�̏�����
    G3X_InitMtxStack();

	// �e��`�惂�[�h�̐ݒ�(�V�F�[�h���A���`�G�C���A�X��������)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
	G3X_AlphaTest(FALSE, 0);	// �A���t�@�e�X�g�@�@�I�t
	G3X_AlphaBlend(TRUE);		// �A���t�@�u�����h�@�I��

	// �N���A�J���[�̐ݒ�
    G3X_SetClearColor(GX_RGB(0, 0, 0),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// �W�I���g���G���W���N����K���Ă΂�Ȃ���΂Ȃ�Ȃ�
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// �r���[�|�[�g�̐ݒ�
    G3_ViewPort(0, 0, 255, 191);

	// �}�l�[�W�����e�N�X�`���C���[�W�X���b�g���w��X���b�g���Ǘ��ł���悤�ɂ���
	// �f�t�H���g�}�l�[�W���ɂ���B
	NNS_GfdInitFrmTexVramManager(1, TRUE);
		
	// �}�l�[�W�����p���b�g��16KB���Ǘ��ł���悤�ɂ���
	// �f�t�H���g�}�l�[�W���ɂ���B
	NNS_GfdInitFrmPlttVramManager(0x4000, TRUE);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�RD�ݒ�Ŏg�p������������j��
 *
 *	@param	none 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void putback_3d( void )
{
	NNS_GfdResetFrmTexVramState();
	NNS_GfdResetFrmPlttVramState();
}

