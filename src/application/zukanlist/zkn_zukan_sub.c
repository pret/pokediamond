//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_sub.c
 *	@brief		�}�ӃT�u���
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
#include "include/application/zukanlist/zkn_zukan.h"
#include "include/application/zukanlist/zkn_zukan_graver.h"
#include "include/application/zukanlist/zkn_zukan_textver.h"
#include "include/application/zukanlist/zkn_world_text_sys.h"
#include "include/application/zukanlist/zkn_world_text_data.h"

#define	__ZKN_ZUKAN_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan_sub.h"

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
#define ZKN_ZUKAN_SUB_EVENT_NUM ( 3 )	// �C�x���g��
#define ZKN_ZUKAN_SUB_EVENT_CHANGE_NORMAL		(1<<0)
#define ZKN_ZUKAN_SUB_EVENT_CHANGE_TEXT			(1<<1)
#define ZKN_ZUKAN_SUB_EVENT_CHANGE_DATA_MAIN	(1<<2)


#define ZKN_ZUKAN_SUB_OAM_SF_PRI	( 31 )
#define ZKN_ZUKAN_SUB_OAM_BG_PRI	( 2 )

enum{
	ZKN_ZUKANSUB_SEQINIT_ALLOC,
	ZKN_ZUKANSUB_SEQINIT_LOAD,
	ZKN_ZUKANSUB_SEQINIT_FADEIN,
	ZKN_ZUKANSUB_SEQINIT_END,
};
enum{
	ZKN_ZUKANSUB_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKANSUB_SEQDELETE_FADEOUT,
	ZKN_ZUKANSUB_SEQDELETE_RELEASE,
	ZKN_ZUKANSUB_SEQDELETE_FREE,
	ZKN_ZUKANSUB_SEQDELETE_END,
};

// �T�u��ʂŕύX����A�v���P�[�V�����^�C�v
enum{
	ZKN_ZUKANSUB_CONTROL_NORMAL,	// �m�[�}���^�C�v�}�ӂ����\����
	ZKN_ZUKANSUB_CONTROL_TEXT00,		// �e�L�X�g�o�[�W����
	ZKN_ZUKANSUB_CONTROL_TEXT01,		// �e�L�X�g�o�[�W����
	ZKN_ZUKANSUB_CONTROL_TEXT02,		// �e�L�X�g�o�[�W����
	ZKN_ZUKANSUB_CONTROL_TEXT03,		// �e�L�X�g�o�[�W����
	ZKN_ZUKANSUB_CONTROL_TEXT04,		// �e�L�X�g�o�[�W����
};

// �{�^��
enum{
	ZKN_ZUKANSUB_BUTTON_NEXT,
	ZKN_ZUKANSUB_BUTTON_BACK,
	ZKN_ZUKANSUB_BUTTON_MY_COUNTRY,		// �����{�^��
	ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00,	// �O��00�{�^��
	ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01,	// �O��01�{�^��
	ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02,	// �O��02�{�^��
	ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03,	// �O��03�{�^��
	ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04,	// �O��04�{�^��
	ZKN_ZUKANSUB_BUTTON_NUM,
};
#define ZKN_ZUKANSUB_BUTTON_SIZE_X	( 160 )
#define ZKN_ZUKANSUB_BUTTON_SIZE_Y	( 40 )
#define ZKN_ZUKANSUB_BUTTON_DEF_X	( 128 )
#define ZKN_ZUKANSUB_BUTTON_NEXT_Y	( 132 )
#define ZKN_ZUKANSUB_BUTTON_BACK_Y		( 76 )
#define ZKN_ZUKANSUB_BUTTON_FONT_OFS_Y	( -6 )
#define ZKN_ZUKANSUB_BUTTON_FONT_NEXT_OFS_X	( -32 )
#define ZKN_ZUKANSUB_BUTTON_FONT_BACK_OFS_X	( -16 )
#define ZKN_ZUKANSUB_BUTTON_ANM_SEQ		( 0 )
#define ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CX	( 8 )
#define ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CY	( 4 )
#define ZKN_ZUKANSUB_BUTTON_NEXTBG_PLTT_NO	(4)
#define ZKN_ZUKANSUB_BUTTON_BACKBG_PLTT_NO	(5)

#define ZKN_ZUKANSUB_BUTTON_MY_C_X	( 28 )
#define ZKN_ZUKANSUB_BUTTON_O_C00_X	( 68 )
#define ZKN_ZUKANSUB_BUTTON_O_C01_X	( 108 )
#define ZKN_ZUKANSUB_BUTTON_O_C02_X	( 148 )
#define ZKN_ZUKANSUB_BUTTON_O_C03_X	( 188 )
#define ZKN_ZUKANSUB_BUTTON_O_C04_X	( 228 )
#define ZKN_ZUKANSUB_BUTTON_DEF_Y	( 176 )
#define ZKN_ZUKANSUB_BUTTON_C_SIZE_X	( 40 )
#define ZKN_ZUKANSUB_BUTTON_C_SIZE_Y	( 32 )
enum{
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_JPN_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_JPN_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_E_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_E_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_FRA_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_FRA_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_GER_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_GER_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_ITA_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_ITA_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_SPA_OFF,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_SPA_ON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_BACK_ICON,
	ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_NEXT_ICON,
};


#define ZKN_ZUKANSUB_BUTTON_PAL_OFS		( 4 )
#define ZKN_ZUKANSUB_BUTTON_PAL_OFS_ON		( 1 )

#define ZKN_ZUKANSUB_BUTTON_BG_DEF_X	( (ZKN_ZUKANSUB_BUTTON_DEF_X - (ZKN_ZUKANSUB_BUTTON_SIZE_X / 2)) / 8 )
#define ZKN_ZUKANSUB_BUTTON_BG_GRA_Y	( ((ZKN_ZUKANSUB_BUTTON_NEXT_Y - (ZKN_ZUKANSUB_BUTTON_SIZE_Y / 2)) / 8) )
#define ZKN_ZUKANSUB_BUTTON_BG_TEXT_Y	( ((ZKN_ZUKANSUB_BUTTON_BACK_Y - (ZKN_ZUKANSUB_BUTTON_SIZE_Y / 2)) / 8) )

// �{�^���A�C�R��
#define ZKN_ZUKANSUB_BUTTON_ICON_NEXT_OFS_X	( +32 )
#define ZKN_ZUKANSUB_BUTTON_ICON_BACK_OFS_X	( -32 )
#define ZKN_ZUKANSUB_BUTTON_ICON_NEXT_Y		( ZKN_ZUKANSUB_BUTTON_NEXT_Y + 2 )
#define ZKN_ZUKANSUB_BUTTON_ICON_BACK_Y		( ZKN_ZUKANSUB_BUTTON_BACK_Y + 2 )


//-------------------------------------
//	�ǂ̍��̌�����o���邩�̃}�X�N	
//=====================================
enum{
	ZKN_ZUKANSUB_COUNTRY_HOME = 1 << 0,
	ZKN_ZUKANSUB_COUNTRY_OUT00 = 1 << 1,
	ZKN_ZUKANSUB_COUNTRY_OUT01 = 1 << 2,
	ZKN_ZUKANSUB_COUNTRY_OUT02 = 1 << 3,
	ZKN_ZUKANSUB_COUNTRY_OUT03 = 1 << 4,
	ZKN_ZUKANSUB_COUNTRY_OUT04 = 1 << 5,
	ZKN_ZUKANSUB_COUNTRY_ALL = ZKN_ZUKANSUB_COUNTRY_HOME| ZKN_ZUKANSUB_COUNTRY_OUT00 | ZKN_ZUKANSUB_COUNTRY_OUT01 | ZKN_ZUKANSUB_COUNTRY_OUT02 | ZKN_ZUKANSUB_COUNTRY_OUT03 | ZKN_ZUKANSUB_COUNTRY_OUT04,
};
	


#define ZKN_ZUKANSUB_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�}�ӃT�u��ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	int* p_event_key;		// �C�x���g�L�[

	ZKN_GLB_DATA* p_glb;		// �O���[�o���f�[�^
	ZKN_ZUKAN_GLB* p_zukan_glb;	// �}�ӃO���[�o��
	ZKN_APL_DATA* p_zukan_graver_apl;	// �}�ӃO���t�B�b�N�o�[�W����
	ZKN_APL_DATA* p_zukan_textver_apl;	// �}�ӃO���t�B�b�N�o�[�W����

	// �}�ӃR�����T�u�A�v���f�[�^
	const ZKN_APL_DATA* cp_zukan_common_apl;
} ZKN_ZUKAN_SUB_GLB;


//-------------------------------------
//	�}�ӃT�u��ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_ZUKAN_SUB_DRAWGLB;

//-------------------------------------
//	�{�^���R�[���o�b�N�ւ̃��[�N
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_ZUKAN_BUTTON_CALLBACK;


//-------------------------------------
//	�}�ӃT�u��ʁ@�������[�N
//=====================================
typedef struct {
	// �{�^���}�l�[�W��
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// �{�^���f�[�^
	ZKN_ZUKAN_BUTTON_CALLBACK callcack;

	// �A�v���f�[�^
	int now_apply;
	int button_event[ ZKN_ZUKANSUB_BUTTON_NUM ];	// �{�^���C�x���g�f�[�^

	int poke_tbl_move;		// NEXT:ZKN_ZUKANSUB_BUTTON_NEXT  BACK:ZKN_ZUKANSUB_BUTTON_BACK  NONE:ZKN_ZUKANSUB_BUTTON_NUM

	u32 poke_country_msk;	// �ǂ̍��̃e�L�X�g�Ȃ�o���邩
} ZKN_ZUKAN_SUB_WORK;

//-------------------------------------
//	�}�ӃT�u��ʁ@�`�惏�[�N
//=====================================
typedef struct {
	// �{�^���O���t�B�b�N
	CLACT_WORK_PTR button[ ZKN_ZUKANSUB_BUTTON_NUM ];
	ZKN_FONTOAM_DATA* p_button_font[ ZKN_ZUKANSUB_BUTTON_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// �{�^���A�C�R��
	CLACT_WORK_PTR button_icon[ ZKN_ZUKANSUB_BUTTON_NUM ];

	// �O����{�^���O���t�B�b�N
	CLACT_U_RES_OBJ_PTR res_obj_world[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	int	bgpltt_no[ ZKN_ZUKANSUB_BUTTON_NUM ];

	void* pltt_buff[ ZKN_ZUKANSUB_BUTTON_NUM ];


	u32 local_poke_country_msk;	// �ǂ̍��̃e�L�X�g�Ȃ�o���邩
} ZKN_ZUKAN_SUB_DRAW;

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
static ZKN_ZUKAN_SUB_GLB* MakeZukanSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKAN_SUB_DRAWGLB* MakeZukanSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeZukanSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanSubGlb( ZKN_ZUKAN_SUB_GLB* p_glb );
static void DeleteZukanSubDrawGlb( ZKN_ZUKAN_SUB_DRAWGLB* p_glb );
static void DeleteZukanSubEvent( ZKN_EVENT_DATA* p_event );


static int ZukanSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknZukanSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// �t�F�[�h����
static void ZknZukanSubOamFadeInit( ZKN_ZUKAN_SUB_DRAW* p_draw );
static void ZknZukanSubOamFadeDelete( ZKN_ZUKAN_SUB_DRAW* p_draw );
static void ZknZukanSubFadeInit( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_SUB_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanSubFadeMain( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_SUB_GLB* cp_glb, BOOL fadein_out );

// �{�^������
static void ZknZukanSubButtonMake( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int heap );
static void ZknZukanSubButtonMove( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb );
static void ZknZukanSubButtonDelete( ZKN_ZUKAN_SUB_WORK* p_work );
static void ZknZukanSubButtonCallBack( u32 button_no, u32 event, void* p_work );

// �{�^���`�搧��
static void ZknZukanSubButtonControl( ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff );

static void ZknZukanSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt );

// �O����{�^���\����\���ݒ�
static void ZknZukanSubWorldTextButtonDrawSet( ZKN_ZUKAN_SUB_DRAW* p_draw, const ZKN_ZUKAN_SUB_WORK* cp_work );
// �O����{�^���A�j��
static void ZknZUkanSubWorldTextButtonAnm( CLACT_WORK_PTR act, int button_event, int world );

// �O����e�L�X�g�}�X�N�ݒ�
static void ZknZukanSubWorldTextMskSet( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb );


// �ǂݍ��ݏ���
static void ZknZukanSubLoadResource( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubReleaseResource( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubSetUpBg( ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubLoadOamData( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubReleaseOamData( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb );
static void ZknZukanSubAddClact( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubDeleteClact( ZKN_ZUKAN_SUB_DRAW* p_draw );
static void ZknZukanSubAddFontOam( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSubDeleteFontOam( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb );

// �A�v���P�[�V�����ύX
static void ZknZukanSubChangMons( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int now_apply );
static void ZknZukanSubApplyChange( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int now_apply, int next_apply );


// �|�P�����؂�ւ�����
static void ZknZukanSubPokeTblMove(  ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb );
static void ZKnZukanSubKeyMove( ZKN_ZUKAN_SUB_WORK* p_work );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃT�u��ʁ@�A�v���쐬
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
void ZKN_ZukanSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKAN_SUB_GLB*	p_glb;
	ZKN_ZUKAN_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanSubGlb( heap, zkn_sys );
	p_drawglb = MakeZukanSubDrawGlb( heap, zkn_sys );
	p_event = MakeZukanSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanSubProcDrawFuncDelete;
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
void ZKN_ZukanSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanSubGlb( p_data->p_glb_data ); 
	DeleteZukanSubDrawGlb( p_data->p_glb_data ); 
	DeleteZukanSubEvent( p_data->p_event_data );
}



//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃT�u��ʁ@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_SUB_GLB* MakeZukanSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_SUB_GLB* p_glb;
	ZKN_APL_DATA* p_apl;
	ZKN_GLB_DATA* p_glbdata;
	int i;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_SUB_GLB) );

	// �ϐ�������
	// �C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );		

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// �}�ӃR�����A�v���O���[�o���f�[�^
	p_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );
	p_glb->cp_zukan_common_apl = p_apl;

	// �}�ӃO���[�o���ϐ�
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN );
	p_glb->p_zukan_glb = p_apl->p_glb_data;

	// �}�ӃO���t�B�b�N�o�[�W�����ϐ�
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_GRA );
	p_glb->p_zukan_graver_apl = p_apl;

	// �}�ӌ���O���t�B�b�N�o�[�W�����ϐ�
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_TEXT );
	p_glb->p_zukan_textver_apl = p_apl;
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u��ʕ`��O���[�o���쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�T�u��ʕ`��O���[�o��
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKAN_SUB_DRAWGLB* MakeZukanSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_SUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_SUB_DRAWGLB) );


	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃT�u��ʁ@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeZukanSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = ZukanSubEventDataNumGet();

	// �C�x���g�f�[�^�e�[�u���쐬
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeZukanOnly( heap, &p_event_tbl[0], zkn_sys, ZKN_ZUKAN_SUB_EVENT_CHANGE_NORMAL );
	ZKN_EVENT_MakeChangeZukanTextMainOnly( heap, &p_event_tbl[1], zkn_sys, ZKN_ZUKAN_SUB_EVENT_CHANGE_TEXT );
	ZKN_EVENT_MakeChangeZukanNormalMainOnly( heap, &p_event_tbl[2], zkn_sys, ZKN_ZUKAN_SUB_EVENT_CHANGE_DATA_MAIN );

	return p_event_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃT�u��ʁ@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanSubGlb( ZKN_ZUKAN_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�u��ʕ`��O���[�o���j��
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void DeleteZukanSubDrawGlb( ZKN_ZUKAN_SUB_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃT�u��ʁ@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanSubEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );
	ZKN_EVENT_DeleteData( &p_event[1] );
	ZKN_EVENT_DeleteData( &p_event[2] );

	sys_FreeMemoryEz( p_event );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃT�u��ʃA�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	�}�ӃT�u��ʃA�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZukanSubEventDataNumGet( void )
{
	return ZKN_ZUKAN_SUB_EVENT_NUM;
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
static int ZknZukanSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_SUB_WORK* p_work = p_dodata->p_work;
	int i;

	// ���[�N�̍쐬
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_ZUKAN_SUB_WORK) );
	memset( p_work, 0, sizeof(ZKN_ZUKAN_SUB_WORK) );

	// �{�^���C�x���g�f�[�^
	for( i=0; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;	// �{�^���C�x���g�f�[�^
	}

	// ���̃A�v���P�[�V����
	p_work->now_apply = ZKN_ZUKANSUB_CONTROL_NORMAL;

	// �{�^�����쐬
	ZknZukanSubButtonMake( p_work, p_glb, p_dodata->heap );

	// �O����e�L�X�g���o���邩�`�F�b�N
	ZknZukanSubWorldTextMskSet( p_work, p_glb );
	
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
static int ZknZukanSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_SUB_WORK* p_work = p_dodata->p_work;

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

		// �L�[����
		ZKnZukanSubKeyMove( p_work );
		
		// �{�^������
		ZknZukanSubButtonMove( p_work, p_glb );

		// �|�P�����؂�ւ�
		ZknZukanSubPokeTblMove( p_work, p_glb );
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
static int ZknZukanSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_SUB_GLB* p_glb = p_glbdata;
	ZKN_ZUKAN_SUB_WORK* p_work = p_dodata->p_work;

	// �{�^���j��
	ZknZukanSubButtonDelete( p_work );

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
static int ZknZukanSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_ZUKANSUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_ZUKAN_SUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKAN_SUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANSUB_SEQINIT_LOAD:
		// Resource�ǂݍ���
		ZknZukanSubLoadResource( p_drawwork, p_drawglb, p_drawdata->heap );

		// �O����{�^���\����\���ݒ�
		ZknZukanSubWorldTextButtonDrawSet( p_drawwork, cp_datawork );
		
		// �t�F�[�h����
		ZknZukanSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANSUB_SEQINIT_FADEIN:
		if( ZknZukanSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKANSUB_SEQINIT_END:
		
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
static int ZknZukanSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_SUB_DRAW*		p_drawwork = p_drawdata->p_work;
	int i;	// ���[�v�p
	int bgpltt_no;
	BOOL move;


	// �}�X�N���ύX���ꂽ��{�^���̕\����ύX����
	if( p_drawwork->local_poke_country_msk != cp_datawork->poke_country_msk ){
		
		ZknZukanSubWorldTextButtonDrawSet( p_drawwork, cp_datawork );

		p_drawwork->local_poke_country_msk = cp_datawork->poke_country_msk;
	}

	// �{�^���\������
	for( i=0; i<=ZKN_ZUKANSUB_BUTTON_BACK; i++ ){
		move = FALSE;
		
		if( i==0 ){	
			move = TRUE;
		}else{
			move = TRUE;
		}
		
		if( move ){
			if( i == ZKN_ZUKANSUB_BUTTON_NEXT ){
				bgpltt_no = ZKN_ZUKANSUB_BUTTON_NEXTBG_PLTT_NO;
			}else{
				bgpltt_no = ZKN_ZUKANSUB_BUTTON_BACKBG_PLTT_NO;
			}
			
			ZknZukanSubButtonControl( p_drawglb, p_drawwork->button[i],
					p_drawwork->p_button_font[i], cp_datawork->button_event[i],
					ZKN_ZUKANSUB_BUTTON_FONT_OFS_Y, bgpltt_no,
					&p_drawwork->bgpltt_no[i], p_drawdata->heap,
					ZKN_ZUKANSUB_BUTTON_PAL_OFS, 
					ZKN_ZUKANSUB_BUTTON_PAL_OFS_ON,
					&p_drawwork->pltt_buff[i] );

			// �A�C�R���������ɓ�����
			ZKN_UTIL_ButtonMove( p_drawwork->button_icon[i],
			cp_datawork->button_event[i] );

		}
	}

	// �O����p�{�^��
	for( i=ZKN_ZUKANSUB_BUTTON_MY_COUNTRY; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		// �{�^������
		ZknZUkanSubWorldTextButtonAnm( p_drawwork->button[i],
				cp_datawork->button_event[i],
				i );

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
static int ZknZukanSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_ZUKAN_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_ZUKAN_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_ZUKAN_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_ZUKANSUB_SEQDELETE_FADEOUT_INIT:

		// �J�[�\���A�j����~
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, TRUE );
		// �t�F�[�h����
		ZknZukanSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANSUB_SEQDELETE_FADEOUT:
		if( ZknZukanSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_ZUKANSUB_SEQDELETE_RELEASE:
		// Resource�ǂݍ���
		ZknZukanSubReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANSUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_ZUKANSUB_SEQDELETE_END:
		return ZKN_PROC_TRUE;
		
	default:
		break;
	}
	return ZKN_PROC_FALSE;
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
static void ZknZukanSubButtonMake( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int heap )
{
	// �e�[�u���쐬
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_ZUKANSUB_BUTTON_NUM );

	// �e�[�u���f�[�^�ݒ�
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_NEXT ],
			ZKN_ZUKANSUB_BUTTON_NEXT_Y - (ZKN_ZUKANSUB_BUTTON_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_NEXT_Y + (ZKN_ZUKANSUB_BUTTON_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_X - (ZKN_ZUKANSUB_BUTTON_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_DEF_X + (ZKN_ZUKANSUB_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_BACK ],
			ZKN_ZUKANSUB_BUTTON_BACK_Y - (ZKN_ZUKANSUB_BUTTON_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_BACK_Y + (ZKN_ZUKANSUB_BUTTON_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_X - (ZKN_ZUKANSUB_BUTTON_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_DEF_X + (ZKN_ZUKANSUB_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_MY_C_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_MY_C_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_O_C00_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_O_C00_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_O_C01_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_O_C01_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_O_C02_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_O_C02_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_O_C03_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_O_C03_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ],
			ZKN_ZUKANSUB_BUTTON_DEF_Y - (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_DEF_Y + (ZKN_ZUKANSUB_BUTTON_C_SIZE_Y/2),
			ZKN_ZUKANSUB_BUTTON_O_C04_X - (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2),
			ZKN_ZUKANSUB_BUTTON_O_C04_X + (ZKN_ZUKANSUB_BUTTON_C_SIZE_X/2) );


	p_work->callcack.p_glb = p_glb;
	p_work->callcack.p_work = p_work;

	// �{�^���}�l�[�W���쐬
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_ZUKANSUB_BUTTON_NUM,
			ZknZukanSubButtonCallBack,
			&p_work->callcack,
			heap );
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
static void ZknZukanSubButtonMove( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = BMN_EVENT_SLIDEOUT;
	}

	BMN_Main( p_work->p_button_man );
	
	// ������Ă���O����{�^���́A�������ςȂ�
	switch( p_work->now_apply ){
	case ZKN_ZUKANSUB_CONTROL_NORMAL:	// �m�[�}���^�C�v�}�ӂ����\����
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ] = BMN_EVENT_RELEASE;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT00:		// �e�L�X�g�o�[�W����
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ] = BMN_EVENT_RELEASE;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT01:		// �e�L�X�g�o�[�W����
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ] = BMN_EVENT_RELEASE;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT02:		// �e�L�X�g�o�[�W����
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ] = BMN_EVENT_RELEASE;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT03:		// �e�L�X�g�o�[�W����
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ] = BMN_EVENT_RELEASE;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT04:		// �e�L�X�g�o�[�W����
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ] = BMN_EVENT_RELEASE;
		break;

	default:
		break;
	}


	// �|�P�����ύX������������Ή�����
	// �{�^���𔽉�������
	switch( p_work->poke_tbl_move ){
		
	case ZKN_ZUKANSUB_BUTTON_NEXT:
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_NEXT ] = BMN_EVENT_HOLD;
		break;

	case ZKN_ZUKANSUB_BUTTON_BACK:
		p_work->button_event[ ZKN_ZUKANSUB_BUTTON_BACK ] = BMN_EVENT_HOLD;
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
static void ZknZukanSubButtonDelete( ZKN_ZUKAN_SUB_WORK* p_work )
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
static void ZknZukanSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_ZUKAN_BUTTON_CALLBACK* p_work_data = p_work;
	ZKN_ZUKAN_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_ZUKAN_SUB_WORK* p_subwork = p_work_data->p_work;
	BOOL check;

	// �{�^���C�x���g�i�[
	p_subwork->button_event[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		switch( button_no ){
		case ZKN_ZUKANSUB_BUTTON_NEXT:
			p_subwork->poke_tbl_move = ZKN_ZUKANSUB_BUTTON_NEXT;
			break;
			
		case ZKN_ZUKANSUB_BUTTON_BACK:
			p_subwork->poke_tbl_move = ZKN_ZUKANSUB_BUTTON_BACK;
			break;

		case ZKN_ZUKANSUB_BUTTON_MY_COUNTRY:		// �����{�^��
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_HOME ){
				// �O���ꃂ�[�h�̂Ƃ��́A�����ꃂ�[�h�ɂ���
				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_NORMAL ){
					// �y�[�W����
					check = ZKN_ZukanAplPageAdd( p_glb->p_zukan_glb, 1 );
				}else{
					// �y�[�W������
					ZKN_ZukanAplPageSet( p_glb->p_zukan_glb, 0 );

					check = TRUE;	// �t�F�[�h�͂���
				}

				// �A�v���P�[�V�����ύX�ō��̃A�v���P�[�V���������Z�b�g
				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_NORMAL );

					// �I���ړ���
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}
			}
			break;
			
		case ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00:	// �O��00�{�^��
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT00 ){

				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_TEXT00 ){
					// �y�[�W����
					check = ZKN_ZukanTexverPageAdd( p_glb->p_zukan_textver_apl );
				}else{
					// �y�[�W������
					ZKN_ZukanTexverPageSet( p_glb->p_zukan_textver_apl, 0 );
					check = TRUE;	// �t�F�[�h�͂���
				}

				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_TEXT00 );

					// �I���ړ���
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );

				}
			}
			break;
			
		case ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01:	// �O��01�{�^��
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT01 ){
				// �O���ꃂ�[�h�̂Ƃ��́A�����ꃂ�[�h�ɂ���
				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_TEXT01 ){
					// �y�[�W����
					check = ZKN_ZukanTexverPageAdd( p_glb->p_zukan_textver_apl );
				}else{
					// �y�[�W������
					ZKN_ZukanTexverPageSet( p_glb->p_zukan_textver_apl, 0 );
					check = TRUE;	// �t�F�[�h�͂���
				}

				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_TEXT01 );

					// �I���ړ���
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}
			}
			break;
			
		case ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02:	// �O��02�{�^��
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT02 ){

				// �O���ꃂ�[�h�̂Ƃ��́A�����ꃂ�[�h�ɂ���
				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_TEXT02 ){
					// �y�[�W����
					check = ZKN_ZukanTexverPageAdd( p_glb->p_zukan_textver_apl );
				}else{
					// �y�[�W������
					ZKN_ZukanTexverPageSet( p_glb->p_zukan_textver_apl, 0 );
					check = TRUE;	// �t�F�[�h�͂���
				}
				// �A�v���P�[�V�����ύX�ō��̃A�v���P�[�V���������Z�b�g
				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_TEXT02 );

					// �I���ړ���
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}
			}
			break;
			
		case ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03:	// �O��03�{�^��
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT03 ){

				// �O���ꃂ�[�h�̂Ƃ��́A�����ꃂ�[�h�ɂ���
				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_TEXT03 ){
					// �y�[�W����
					check = ZKN_ZukanTexverPageAdd( p_glb->p_zukan_textver_apl );
				}else{
					// �y�[�W������
					ZKN_ZukanTexverPageSet( p_glb->p_zukan_textver_apl, 0 );
					check = TRUE;	// �t�F�[�h�͂���
				}
				// �A�v���P�[�V�����ύX�ō��̃A�v���P�[�V���������Z�b�g
				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_TEXT03 );

					// �I���ړ���
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
				}
			}
			break;
			
		case ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04:	// �O��04�{�^��
			if( p_subwork->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT04 ){

				// �O���ꃂ�[�h�̂Ƃ��́A�����ꃂ�[�h�ɂ���
				if( p_subwork->now_apply == ZKN_ZUKANSUB_CONTROL_TEXT04 ){
					// �y�[�W����
					check = ZKN_ZukanTexverPageAdd( p_glb->p_zukan_textver_apl );
				}else{
					// �y�[�W������
					ZKN_ZukanTexverPageSet( p_glb->p_zukan_textver_apl, 0 );
					check = TRUE;	// �t�F�[�h�͂���
				}

				// �A�v���P�[�V�����ύX�ō��̃A�v���P�[�V���������Z�b�g
				if( check ){
					ZknZukanSubApplyChange( p_subwork, p_glb, p_subwork->now_apply, ZKN_ZUKANSUB_CONTROL_TEXT04 );

					// �I���ړ���
					Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
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
 *	@brief	�O���t�B�b�N����������
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubLoadResource( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	// �w�i
	ZknZukanSubSetUpBg( p_drawglb, heap );

	// OAM
	ZknZukanSubLoadOamData( p_draw, p_drawglb, heap );

	// �Z���A�N�^�[�o�^
	ZknZukanSubAddClact( p_draw, p_drawglb, heap );

	// FONTOAM�o�^
	ZknZukanSubAddFontOam( p_draw, p_drawglb, heap );
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
static void ZknZukanSubReleaseResource( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	int i;


	// �p���b�g�����Z�b�g
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_4_NCLR, PALTYPE_SUB_BG, ZKN_ZUKANSUB_BUTTON_NEXTBG_PLTT_NO*32, 32, heap );
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_4_NCLR, PALTYPE_SUB_BG, ZKN_ZUKANSUB_BUTTON_BACKBG_PLTT_NO*32, 32, heap );
	
	// �Z���A�N�^�[�j��
	ZknZukanSubDeleteClact( p_draw );

	// FONTOAM�j��
	ZknZukanSubDeleteFontOam( p_draw, p_drawglb );

	// OAM
	ZknZukanSubReleaseOamData( p_draw, p_drawglb );

	// �p���b�g�o�b�t�@�j��
	for( i=0;i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
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
static void ZknZukanSubSetUpBg( ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub2_c_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub2_a_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �{�^���P	
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, ZKN_ZUKANSUB_BUTTON_BG_DEF_X, ZKN_ZUKANSUB_BUTTON_BG_GRA_Y,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );


	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub2_d_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �{�^��2
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, ZKN_ZUKANSUB_BUTTON_BG_DEF_X, ZKN_ZUKANSUB_BUTTON_BG_TEXT_Y,
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
static void ZknZukanSubLoadOamData( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw_glb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_ZUKAN_SUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_ZUKAN_SUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_ZUKAN_SUB_RES_ID,
			CLACT_U_CELLANM_RES, heap );


	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj_world[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub2_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub2_lzh_NCGR + ZKN_ZUKAN_SUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj_world[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj_world[ CLACT_U_CHAR_RES ] );

	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj_world[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub2_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub2_lzh_NCER + ZKN_ZUKAN_SUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj_world[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub2_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub2_lzh_NANR + ZKN_ZUKAN_SUB_RES_ID,
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
static void ZknZukanSubReleaseOamData( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb )
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


	// ���E�̌���{�^��
	CLACT_U_CharManagerDelete( p_draw->res_obj_world[ CLACT_U_CHAR_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj_world[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj_world[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj_world[ CLACT_U_CELLANM_RES ] );
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
static void ZknZukanSubAddClact( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_ZUKAN_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_ZUKAN_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_ZUKAN_SUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKAN_SUB_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKAN_SUB_OAM_SF_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	
	// �O���t�B�b�N�^�C�v�ύX�{�^��
	add.mat.x = ZKN_ZUKANSUB_BUTTON_DEF_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_NEXT_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_NEXT ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_NEXT ], ZKN_ZUKANSUB_BUTTON_ANM_SEQ );	

	// �e�L�X�g�^�C�v�ύX�{�^��
	add.mat.x = ZKN_ZUKANSUB_BUTTON_DEF_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_BACK_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_BACK ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_BACK ], ZKN_ZUKANSUB_BUTTON_ANM_SEQ );	


	// �O����{�^���p
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub2_lzh_NCGR + ZKN_ZUKAN_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub2_lzh_NCER + ZKN_ZUKAN_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub2_lzh_NANR + ZKN_ZUKAN_SUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKAN_SUB_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActHeader = &clact_head;

	// �����}�ӊJ���悤�A�N�^�[
	add.mat.x = ZKN_ZUKANSUB_BUTTON_MY_C_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_JPN_OFF );	

	// �O����00�ӊJ���悤�A�N�^�[
	add.mat.x = ZKN_ZUKANSUB_BUTTON_O_C00_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_E_OFF );	

	// �O����01�ӊJ���悤�A�N�^�[
	add.mat.x = ZKN_ZUKANSUB_BUTTON_O_C01_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_FRA_OFF );	

	// �O����02�ӊJ���悤�A�N�^�[
	add.mat.x = ZKN_ZUKANSUB_BUTTON_O_C02_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_GER_OFF );	

	// �O����03�ӊJ���悤�A�N�^�[
	add.mat.x = ZKN_ZUKANSUB_BUTTON_O_C03_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_ITA_OFF );	

	// �O����04�ӊJ���悤�A�N�^�[
	add.mat.x = ZKN_ZUKANSUB_BUTTON_O_C04_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_SPA_OFF );	

	add.pri = ZKN_ZUKAN_SUB_OAM_SF_PRI - 1;
	
	// �{�^���A�C�R��
	add.mat.x = (ZKN_ZUKANSUB_BUTTON_DEF_X + ZKN_ZUKANSUB_BUTTON_ICON_NEXT_OFS_X) << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_ICON_NEXT_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button_icon[ ZKN_ZUKANSUB_BUTTON_NEXT ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button_icon[ ZKN_ZUKANSUB_BUTTON_NEXT ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_NEXT_ICON );	

	// �{�^���A�C�R��
	add.mat.x = (ZKN_ZUKANSUB_BUTTON_DEF_X + ZKN_ZUKANSUB_BUTTON_ICON_BACK_OFS_X) << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANSUB_BUTTON_ICON_BACK_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button_icon[ ZKN_ZUKANSUB_BUTTON_BACK ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button_icon[ ZKN_ZUKANSUB_BUTTON_BACK ], ZKN_ZUKANSUB_BUTTON_WORLD_SEQ_BACK_ICON );
	
	// �{�^���A�C�R���Ȃ�
	for( i=ZKN_ZUKANSUB_BUTTON_BACK + 1; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		p_draw->button_icon[ i ] = NULL;
	}
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
static void ZknZukanSubDeleteClact( ZKN_ZUKAN_SUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		CLACT_Delete( p_draw->button[ i ] );
		if( p_draw->button_icon[ i ] ){
			CLACT_Delete( p_draw->button_icon[ i ] );
		}
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
static void ZknZukanSubAddFontOam( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, int heap )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// �p���b�g�A�h���X
	int i;

	// ���CLACT��o�^���Ă���K�v������
	GF_ASSERT( p_draw->button[ ZKN_ZUKANSUB_BUTTON_NEXT ] );

	// �p���b�g�̃��\�[�X�f�[�^�擾
	// �p���b�g�v���N�V�擾�p
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS );

	// �������f�[�^�̋��ʕ������쐬
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.y			 = ZKN_ZUKANSUB_BUTTON_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_ZUKAN_SUB_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CY );

	// ������
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_ZUKAN_BUTTON_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->button[ ZKN_ZUKANSUB_BUTTON_NEXT ];
	fontoam_init.x		= ZKN_ZUKANSUB_BUTTON_FONT_NEXT_OFS_X;
	p_draw->p_button_font[ ZKN_ZUKANSUB_BUTTON_NEXT ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_button_font[ ZKN_ZUKANSUB_BUTTON_NEXT ]->p_fontoam, pltt_ofs + ZKN_ZUKANSUB_BUTTON_PAL_OFS );

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );


	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_ZUKANSUB_BUTTONFONT_BMP_SIZE_CY );

	// ���߂�
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_ZUKAN_BUTTON_01, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->button[ ZKN_ZUKANSUB_BUTTON_BACK ];
	fontoam_init.x		= ZKN_ZUKANSUB_BUTTON_FONT_BACK_OFS_X;
	p_draw->p_button_font[ ZKN_ZUKANSUB_BUTTON_BACK ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_button_font[ ZKN_ZUKANSUB_BUTTON_BACK ]->p_fontoam, pltt_ofs + ZKN_ZUKANSUB_BUTTON_PAL_OFS );

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );


	// �����͏o���Ȃ�
	for( i=ZKN_ZUKANSUB_BUTTON_MY_COUNTRY; i< ZKN_ZUKANSUB_BUTTON_NUM; i++){
		p_draw->p_button_font[ i ] = NULL;
	}
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
static void ZknZukanSubDeleteFontOam( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb )
{
	int i;

	for( i=0; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		if(p_draw->p_button_font[ i ]){
			ZKN_FONTOAM_Delete( p_draw->p_button_font[ i ] );
		}
	}
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
static void ZknZukanSubOamFadeInit( ZKN_ZUKAN_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODE�𔼓����ɂ���
	for( i=0; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->button[ i ], GX_OAM_MODE_XLU );
		if(p_draw->p_button_font[ i ]){
			FONTOAM_ObjModeSet( p_draw->p_button_font[ i ]->p_fontoam, GX_OAM_MODE_XLU );
		}
		if(p_draw->button_icon[ i ]){
			CLACT_ObjModeSet( p_draw->button_icon[ i ], GX_OAM_MODE_XLU );
		}
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
static void ZknZukanSubOamFadeDelete( ZKN_ZUKAN_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODE���m�[�}���ɂ���
	for( i=0; i<ZKN_ZUKANSUB_BUTTON_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->button[ i ], GX_OAM_MODE_NORMAL );
		if(p_draw->p_button_font[ i ]){
			FONTOAM_ObjModeSet( p_draw->p_button_font[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
		}
		if(p_draw->button_icon[ i ]){
			CLACT_ObjModeSet( p_draw->button_icon[ i ], GX_OAM_MODE_NORMAL );
		}
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
static void ZknZukanSubFadeInit( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_SUB_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknZukanSubOamFadeInit( p_draw );

	// �u���C�g�l�X�������s���Ă悢��
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKANSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKANSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
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
static BOOL ZknZukanSubFadeMain( ZKN_ZUKAN_SUB_DRAW* p_draw, ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, const ZKN_ZUKAN_SUB_GLB* cp_glb, BOOL fadein_out )
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
			ZknZukanSubOamFadeDelete( p_draw );
		}

		return TRUE;
	}

	return FALSE;
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
static void ZknZukanSubButtonControl( ZKN_ZUKAN_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff )
{
	int now_frm;
	NNSG2dPaletteData* p_plt;
	BOOL check;
	BOOL chenge = FALSE;
	int arc_data_idx;

	// �{�^������
	ZKN_UTIL_ButtonMove( button,
			event );


	ZknZukanSubFontButtonMove( 
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
static void ZknZukanSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt )
{
	ZKN_UTIL_ButtonFontMove_Col( act, p_fontoam, def_y, off_pltt, on_pltt );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����X�^�[��ύX����
 *
 *	@param	p_work		���[�N
 *	@param	p_glb		�O���[�o��
 *	@param	now_apply	���̃A�v���P�[�V����
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubChangMons( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int now_apply )
{
	int gra_x, gra_y;
	
	// �|�P�����̐����o��
	p_glb->p_zukan_glb->mons_snd_req = TRUE;
		
	// ���̃A�v���t�F�[�h���[�h�ݒ�
	*p_glb->p_event_key |= ZKN_ZUKAN_SUB_EVENT_CHANGE_DATA_MAIN;
	p_work->now_apply = ZKN_ZUKANSUB_CONTROL_NORMAL;
	gra_x = ZKN_ZUKAN_POKEGRA_MAT_X;
	gra_y = ZKN_ZUKAN_POKEGRA_MAT_Y;
	p_glb->p_zukan_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_OTHER;


	// ���̃A�v���t�F�[�h�ݒ�
	switch( now_apply ){
	case ZKN_ZUKANSUB_CONTROL_NORMAL:	// �m�[�}���^�C�v�}�ӂ����\����
		p_glb->p_zukan_glb->poke_gra_move_x = gra_x;
		p_glb->p_zukan_glb->poke_gra_move_y = gra_y;
		p_glb->p_zukan_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_NORMAL;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT00:		// �O����00
	case ZKN_ZUKANSUB_CONTROL_TEXT01:		// �O����01
	case ZKN_ZUKANSUB_CONTROL_TEXT02:		// �O����02
	case ZKN_ZUKANSUB_CONTROL_TEXT03:		// �O����03
	case ZKN_ZUKANSUB_CONTROL_TEXT04:		// �O����04
		ZKN_ZukanTextverPokeGraFadeOutSet( p_glb->p_zukan_textver_apl, gra_x, gra_y );
		ZKN_ZukanTextverFadeModeSet( p_glb->p_zukan_textver_apl, ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL );
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�A�v���P�[�V�����ύX
 *	
 *	@param	p_work			���[�N
 *	@param	p_glb			�O���[�o��
 *	@param	now_apply		���̃A�v��
 *	@param	next_apply		���̃A�v��
 *	@param	fade_mode		�t�F�[�h���[�h	TRUE:�|�P�����c�����܂� FALSE:�S�����t�F�[�h
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubApplyChange( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb, int now_apply, int next_apply )
{
	int gra_x, gra_y;
	int lang_code;

	// �|�P�����̐���炷
	
	// ���̃A�v���t�F�[�h���[�h�ݒ�
	switch( next_apply ){
	case ZKN_ZUKANSUB_CONTROL_NORMAL:	// �m�[�}���^�C�v�}�ӂ����\����
		*p_glb->p_event_key |= ZKN_ZUKAN_SUB_EVENT_CHANGE_DATA_MAIN;
		p_work->now_apply = ZKN_ZUKANSUB_CONTROL_NORMAL;
		gra_x = ZKN_ZUKAN_POKEGRA_MAT_X;
		gra_y = ZKN_ZUKAN_POKEGRA_MAT_Y;
		p_glb->p_zukan_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_OTHER;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT00:		// �O����00
	case ZKN_ZUKANSUB_CONTROL_TEXT01:		// �O����01
	case ZKN_ZUKANSUB_CONTROL_TEXT02:		// �O����02
	case ZKN_ZUKANSUB_CONTROL_TEXT03:		// �O����03
	case ZKN_ZUKANSUB_CONTROL_TEXT04:		// �O����04
		*p_glb->p_event_key |= ZKN_ZUKAN_SUB_EVENT_CHANGE_TEXT;
		p_work->now_apply = next_apply;
		gra_x = ZKN_ZUKANTEXTVER_POKEGRA_MAT_X;
		gra_y = ZKN_ZUKANTEXTVER_POKEGRA_MAT_Y;

		ZKN_ZukanTextverFadeModeSet( p_glb->p_zukan_textver_apl, ZKK_ZUKANTEXTVER_FADE_MODE_OTHER );

		// ���R�[�h�ݒ�
		lang_code = ZKN_WT_WORLD_TEXT_GMM_Idx_LANG_Code( next_apply - ZKN_ZUKANSUB_CONTROL_TEXT00 );
		ZKN_ZukanTexverTypeSet( p_glb->p_zukan_textver_apl, lang_code );

		break;

	default:
		break;
	}

	// ���̃A�v���t�F�[�h�ݒ�
	switch( now_apply ){
	case ZKN_ZUKANSUB_CONTROL_NORMAL:	// �m�[�}���^�C�v�}�ӂ����\����
		p_glb->p_zukan_glb->poke_gra_move_x = gra_x;
		p_glb->p_zukan_glb->poke_gra_move_y = gra_y;
		p_glb->p_zukan_glb->fade_mode = ZKK_ZUKAN_FADE_MODE_OTHER;
		break;
		
	case ZKN_ZUKANSUB_CONTROL_TEXT00:		// �O����00
	case ZKN_ZUKANSUB_CONTROL_TEXT01:		// �O����01
	case ZKN_ZUKANSUB_CONTROL_TEXT02:		// �O����02
	case ZKN_ZUKANSUB_CONTROL_TEXT03:		// �O����03
	case ZKN_ZUKANSUB_CONTROL_TEXT04:		// �O����04
		ZKN_ZukanTextverPokeGraFadeOutSet( p_glb->p_zukan_textver_apl, gra_x, gra_y );

		ZKN_ZukanTextverFadeModeSet( p_glb->p_zukan_textver_apl, ZKK_ZUKANTEXTVER_FADE_MODE_OTHER );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����؂�ւ�����
 *
 *	@param	p_work		���[�N
 *	@param	p_glb		�O���[�o��
 *	@param	up_down		��ɍs�������ɍs����
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubPokeTblMove( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb )
{
	BOOL check;

	if( p_work->poke_tbl_move != ZKN_ZUKANSUB_BUTTON_NUM ){
		
		// �}�Ӄf�[�^��ʂŏ㉺�������ꂽ��|�P���������ւ���
		if( p_work->poke_tbl_move == ZKN_ZUKANSUB_BUTTON_BACK ){
			// �|�P�������X�g��i�߂�
			check = ZKN_GLBDATA_PokeListTblNoAdd( p_glb->p_glb, -1 );
		}else{
			// �|�P�������X�g��i�߂�
			check = ZKN_GLBDATA_PokeListTblNoAdd( p_glb->p_glb, 1 );
		}
		
		if( check == TRUE ){
			// �A�v���P�[�V�����ύX�ō��̃A�v���P�[�V���������Z�b�g
			ZknZukanSubChangMons( p_work, p_glb, p_work->now_apply );

			// �O����e�L�X�g���o���邩�`�F�b�N
			ZknZukanSubWorldTextMskSet( p_work, p_glb );

			// �I���ړ���
			Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�L�[����ɂ��ύX
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZKnZukanSubKeyMove( ZKN_ZUKAN_SUB_WORK* p_work )
{

	if( sys.trg & PAD_KEY_UP ){
		p_work->poke_tbl_move = ZKN_ZUKANSUB_BUTTON_BACK;
		return ;
	}

	if( sys.trg & PAD_KEY_DOWN ){
		p_work->poke_tbl_move = ZKN_ZUKANSUB_BUTTON_NEXT;
		return ;
	}

	p_work->poke_tbl_move = ZKN_ZUKANSUB_BUTTON_NUM;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O����e�L�X�g�̃{�^��ONOFF�ݒ�
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	cp_work		�f�[�^���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubWorldTextButtonDrawSet( ZKN_ZUKAN_SUB_DRAW* p_draw, const ZKN_ZUKAN_SUB_WORK* cp_work )
{
	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_HOME) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_MY_COUNTRY ], TRUE );
	}

	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT00) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_00 ], TRUE );
	}

	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT01) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_01 ], TRUE );
	}

	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT02) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_02 ], TRUE );
	}

	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT03) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_03 ], TRUE );
	}

	if( (cp_work->poke_country_msk & ZKN_ZUKANSUB_COUNTRY_OUT04) == 0 ){
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->button[ ZKN_ZUKANSUB_BUTTON_OUT_COUNTRY_04 ], TRUE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O����}�X�N�ݒ�
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanSubWorldTextMskSet( ZKN_ZUKAN_SUB_WORK* p_work, ZKN_ZUKAN_SUB_GLB* p_glb )
{
	BOOL ret;
	int i;
	int lang;
	
	p_work->poke_country_msk = 0;

	// ���̃|�P�����̊O���t���O���ݒ肳��Ă��邩�`�F�b�N
	for( i=0; i<ZKN_WORLD_TEXT_OUTWORLD_NUM; i++ ){
		// i�̒l�͊O���p���R�[�h�ł͂Ȃ�GMMIDX�l�Ȃ̂�
		// �O���p���R�[�h�ɕϊ�����
		lang = ZKN_WT_WORLD_TEXT_GMM_Idx_LANG_Code( i );
		ret = ZKN_GLBDATA_PokeTextVersionFlagGet( p_glb->p_glb, lang );
		if( ret ){
			p_work->poke_country_msk |= ZKN_ZUKANSUB_COUNTRY_HOME;
			p_work->poke_country_msk |= 1 << (i + 1);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�{�^���A�j��
 *	
 *	@param	act				�A�N�^�[
 *	@param	button_event	�{�^���C�x���g
 *	@param  world			�{�^���i���o�[	ZKN_ZUKANSUB_BUTTON�`�萔�ƃ����N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZUkanSubWorldTextButtonAnm( CLACT_WORK_PTR act, int button_event, int world )
{
	int anm_seq;

	GF_ASSERT( (world >= ZKN_ZUKANSUB_BUTTON_MY_COUNTRY) && (world < ZKN_ZUKANSUB_BUTTON_NUM) );

	// world����A�j���V�[�P���X�i���o�[�擾
	anm_seq = (world - ZKN_ZUKANSUB_BUTTON_MY_COUNTRY) * 2;
	
	if( button_event == BMN_EVENT_RELEASE ){
		
		// �������{�^���ɂ���
		CLACT_AnmChg( act, anm_seq + 1 );
	}else{

		// �����ĂȂ��{�^���ɂ���
		CLACT_AnmChg( act, anm_seq );
	}
}
