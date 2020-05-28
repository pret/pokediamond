//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_pokelist_sub.c
 *	@brief		�|�P�������X�g�T�u���
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 *
 *	2006.08.02	���X�g�𓮂����p�����[�^�̒l��S�Ċp�x����x�N�g���̓����������ɕύX�@�萔�𒲐����܂����B
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/gflib/button_man.h"
#include "include/gflib/calctool.h"


#include "include/application/zukanlist/zkn_pokelist.h"
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/application/zukanlist/zkn_snd_def.h"

#include "include/system/brightness.h"
#include "include/system/arc_util.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zukan.naix"

#include "include/application/zukanlist/zkn_pokelist_sub.h"


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
#define ZKN_POKELIST_SUB_LIST_PAR_SET	// �߹��ؽĂɏd������������


//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

#define ZKN_POKELIST_SUB_EVENT_NUM	( 1 )


#define ZKN_POKELIST_SUB_FADEIN_COUNT	( ZKN_FADE_SYNC_LONG_COMMON)
#define ZKN_POKELIST_SUB_FADEOUT_COUNT	( ZKN_FADE_SYNC_LONG_COMMON)



#define ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CX	( 10 )
#define ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CY	( 4 )

//-------------------------------------
//	�z�C�[���ʗp�萔
//=====================================
#define ZKN_POKELIST_SUB_EVENT_POKELIST		( 0x1 << 0 )	// �}�ӎ�ޕϊ�

#define ZKN_POKELIST_SUB_SEARCH_BUTTON_X	( 48 )
#define ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_X	( 48 )
#define ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_X	( 48 )
#define ZKN_POKELIST_SUB_LISTSTART_BUTTON_X	( 124 )
#define ZKN_POKELIST_SUB_LISTEND_BUTTON_X	( 124 )

#define ZKN_POKELIST_SUB_SEARCH_BUTTON_Y	( 40 )
#define ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_Y	( 88 )
#define ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_Y	( 152 )
#define ZKN_POKELIST_SUB_LISTSTART_BUTTON_Y	( 64 )
#define ZKN_POKELIST_SUB_LISTEND_BUTTON_Y	( 146 )

#define ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_X		( 96 )
#define ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_Y		( 48 )
#define ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_X		( 96 )
#define ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_Y		( 48 )
#define ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_X		( 96 )
#define ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_Y		( 80 )
#define ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_X	( 16 )
#define ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_Y	( 16 )
#define ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_X	( 16 )
#define ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_Y	( 16 )

#define ZKN_POKELSIT_SUB_SEARCH_BUTTON_SEQ	( 2 )	// ���X�g���Z�b�g�{�^���V�[�P���X
#define ZKN_POKELSIT_SUB_ZUKANCHG_BUTTON_SEQ	( 0 )	// ���X�g�̐擪�փ{�^���V�[�P���X
#define ZKN_POKELSIT_SUB_ZUKANSEE_BUTTON_SEQ	( 1 )	// ���X�g�̍Ō�փ{�^���V�[�P���X
#define ZKN_POKELSIT_SUB_LISTSTART_BUTTON_SEQ	( 3 )
#define ZKN_POKELSIT_SUB_LISTEND_BUTTON_SEQ	( 4 )

#define ZKN_POKELIST_SUB_BUTTON_FONT_COL		( 3 )
#define ZKN_POKELIST_SUB_BUTTON_FONT_COL_ZUKAN	( 2 )
#define ZKN_POKELIST_SUB_BUTTON_FONT_COL_CLOSE	( 1 )
#define ZKN_POKELIST_SUB_BUTTON_FONT_PUSH_COL	( 5 )

#define ZKN_POKELIST_SUB_FADE_DEF_X	( ZKN_POKELIST_SUB_BUTTON_X )

#define ZKN_POKELSIT_SUB_MAT_X	( -120 )
#define ZKN_POKELSIT_SUB_MAT_Y	( 0 )
#define ZKN_POKELIST_SUB_BGCX	( 128 )		// BG�A�t�B���ϊ��p���S
#define ZKN_POKELIST_SUB_BGCY	( 104 )		// BG�A�t�B���ϊ��p���S
#define ZKN_POKELIST_SUB_CX		( ZKN_POKELIST_SUB_BGCX + (-ZKN_POKELSIT_SUB_MAT_X) )	// ���S
#define ZKN_POKELIST_SUB_CY		( ZKN_POKELIST_SUB_BGCY + (-ZKN_POKELSIT_SUB_MAT_Y) )	// ���S
#define ZKN_POKELSIT_SUB_R		( 104 )		// ���a

// ���X�g���쐧��p��
#define ZKN_POKELIST_SUB_MOVE_CACL_R	( 524 )	// ���������߂�ׂ̉~���a��l
#define ZKN_POKELIST_SUB_MOVE_CACL_MUL	( 10 )	// �����Ɋ|����l
#define ZKN_POKELIST_SUB_LOCK_MOVE_MAX	( 1024 )	// �L�[����̂Ƃ���1�̃��X�g����������
#define ZKN_POKELIST_SUB_COUNT_R	( ZKN_POKELIST_SUB_LOCK_MOVE_MAX / ZKN_POKELIST_MOVE_END_COUNT )	// ���̒l�ŁA���쑬�x�������ă��X�g�����𓮂���
#define ZKN_POKELIST_SUB_SUB_R	( 2 )	// ���x���炵�Ă���������
#define ZKN_POKELIST_SUB_SUBLIMIT_R	( ZKN_POKELIST_SUB_COUNT_R + 32 )// �l�𔽉f�����Ȃ����~�b�g
#define ZKN_POKELIST_SUB_SUBDRAWLIMIT_R	( 4 )// �l�𔽉f�����Ȃ����~�b�g
#define ZKN_POKELIST_SUB_SUB_MIN_SP	( 16 )// ����ȉ��̃X�s�[�h�̂Ƃ��͔������Ȃ�

// �z�C�[���`�搧��萔
#define ZKN_POKELIST_SUB_LOCK_MOVE_DRAW_MAX	( FX_GET_ROTA_NUM( 25 ) )	// �L�[����̂Ƃ���1�̃��X�g�������Ƃ��ɉ��z�C�[���̊p�x�@�`�攽�f�p�x

#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
/////////////////////////////////////////////////////
#define ZKN_POKELIST_SUB_LIST_PAR_ADD_LIMIT	( 64 )
#define ZKN_POKELIST_SUB_LIST_PAR_MIN	( FX32_CONST( 0.30f ) )
#define ZKN_POKELIST_SUB_LIST_PAR_MAX	( FX32_CONST( 1.0f ) )
#define ZKN_POKELIST_SUB_LIST_PAR_ADD	( FX32_CONST( 0.20f ) )
#define ZKN_POKELIST_SUB_LIST_PAR_SUB	( FX32_CONST( 0.01f ) )
//////////////////////////////////////////////////////
#endif


#define ZKN_POKELIST_SUB_BGFADE_DEF_X	( ZKN_POKELSIT_SUB_MAT_X )

#define ZKN_POKELIST_SUB_FONTOAM_OFS_X	( -40 )
#define ZKN_POKELIST_SUB_FONTOAM_OFS_Y	( -14 )

#define ZKN_POKELIST_SUB_CLACT_NUM	( 3 )


// B�{�^��
#define ZKN_POKELIST_SUB_BUTTON_B_X	( 124 )
#define ZKN_POKELIST_SUB_BUTTON_B_Y	( 8 )
#define ZKN_POKELIST_SUB_BUTTON_B_ANM	( 5 )
#define ZKN_POKELIST_SUB_FONT_B_OFS		( 10 )
#define ZKN_POKELIST_SUB_FONT_B_OFS_Y	( -8 )
#define ZKN_POKELIST_SUB_FONT_B_BMP_CX	( 14 )
#define ZKN_POKELIST_SUB_FONT_B_BMP_CY	( 2 )

#define ZKN_POKELIST_SUB_BUTTON_HIT_X	( ZKN_POKELIST_SUB_BUTTON_B_X - 8 )
#define ZKN_POKELIST_SUB_BUTTON_HIT_Y	( ZKN_POKELIST_SUB_BUTTON_B_Y - 8 )
#define ZKN_POKELIST_SUB_BUTTON_HIT_WIDHT	( 64 )
#define ZKN_POKELIST_SUB_BUTTON_HIT_HEIGHT	( 16 )

// �T�u��ʂ̃p���b�g�ʒu
#define ZKN_POKELIST_SUB_BACK_PL		( 3 )

// �{�^���萔
enum{
	ZKN_POKELIST_SUB_BUTTON_SEARCH,
	ZKN_POKELIST_SUB_BUTTON_ZUKANCHG,
	ZKN_POKELIST_SUB_BUTTON_ZUKANSEE,
	ZKN_POKELIST_SUB_BUTTON_LISTSTART,
	ZKN_POKELIST_SUB_BUTTON_LISTEND,
	ZKN_POKELIST_SUB_BUTTON_WHEEL,		// �z�C�[��
	ZKN_POKELIST_SUB_BUTTON_CANCEL,
	ZKN_POKELIST_SUB_BUTTON_NUM,
};

// �������V�[�P���X
enum{
	ZKN_POKELIST_SUB_SEQINIT_ALLOC,
	ZKN_POKELIST_SUB_SEQINIT_LOAD,
	ZKN_POKELIST_SUB_SEQINIT_FADEIN_INIT,
	ZKN_POKELIST_SUB_SEQINIT_FADEIN,
	ZKN_POKELIST_SUB_SEQINIT_END,
};

// �j���V�[�P���X
enum{
	ZKN_POKELIST_SUB_SEQDELETE_FADEOUT_INIT,
	ZKN_POKELIST_SUB_SEQDELETE_FADEOUT,
	ZKN_POKELIST_SUB_SEQDELETE_RELEASE,
	ZKN_POKELIST_SUB_SEQDELETE_FREE,
	ZKN_POKELIST_SUB_SEQDELETE_END,
};



//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	�|�P�������X�g�@�T�u���
//	�z�C�[���A�v���@�O���[�o���f�[�^
//=====================================
typedef struct {
	int button_event[ ZKN_POKELIST_SUB_BUTTON_NUM ];	// �{�^���C�x���g�f�[�^
	ZKN_POKELIST_GLB_DATA* p_pokelist_glb;		// �|�P�������X�gmain�f�[�^
	int* p_event_key;		// �C�x���g�L�[
	int heap;
} ZKN_POKELIST_SUB_GLB;

//-------------------------------------
//	�|�P�������X�g�@�T�u���
//	�z�C�[���A�v���@�O���t�B�b�N�O���[�o���f�[�^
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_glb_draw;
} ZKN_POKELIST_SUB_GLBDRAW;

//-------------------------------------
//	�|�P�������X�g�@�T�u���
//	�z�C�[���A�v���@�������[�N
//=====================================
typedef struct {
	// �{�^���}�l�[�W��
	BUTTON_MAN* p_button_man;
	void* p_button_work;
	TP_HIT_TBL *hit_tbl;	// �{�^���f�[�^

	int move_dist;		// �ړ���������
	int move_dist_list;	// �ړ����������l���f�p
	int tp_last_x;
	int tp_last_y;

	fx32 wheel_rota_par;// ��]�p�x���f��

	BOOL touch_hold;
} ZKN_POKELIST_SUB_WORK;

//-------------------------------------
//	�{�^���p���[�N
//=====================================
typedef struct {
	ZKN_POKELIST_SUB_WORK* p_work;
	ZKN_POKELIST_SUB_GLB* p_glb;

} ZKN_POKELIST_SUB_BUTTON_WORK;


//-------------------------------------
//	�|�P�������X�g�@�T�u���
//	�z�C�[���A�v���@�`��������[�N
//=====================================
typedef struct {
	CLACT_WORK_PTR clact[ ZKN_POKELIST_SUB_CLACT_NUM ];
	ZKN_FONTOAM_DATA* p_fontoam[ ZKN_POKELIST_SUB_CLACT_NUM ];

	CLACT_WORK_PTR list_start;
	CLACT_WORK_PTR list_end;

	CLACT_WORK_PTR act_B;
	ZKN_FONTOAM_DATA* p_fontoam_B;

	u16 wheel_rota;		// �z�C�[���̌��݉�]�p
	u16 save_wheel_rota;// �z�C�[���̊p�x�ۑ��̈�

	// ���\�[�X�I�u�W�F
	CLACT_U_RES_OBJ_PTR		res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

} ZKN_POKELIST_SUB_DRAWWORK;





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

static ZKN_POKELIST_SUB_GLB* MakePokeListSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_POKELIST_SUB_GLBDRAW* MakePokeListSubGlbDraw( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakePokeListSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeletePokeListSubGlb( ZKN_POKELIST_SUB_GLB* p_glb );
static void DeletePokeListSubGlbDraw( ZKN_POKELIST_SUB_GLBDRAW* p_glb );
static void DeletePokeListSubEvent( ZKN_EVENT_DATA* p_event );

static int EventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------

static int ZknPokeListSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknPokeListSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknPokeListSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// �{�^���̓���
static void ZknPokelistSubButtonFontMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt );

static void ZknPokeListSubButtonMake( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb, int heap );
static void ZknPokeListSubButtonMove( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb );
static void ZknPokeListSubButtonDelete( ZKN_POKELIST_SUB_WORK* p_work );
static void ZknPokeListSubButtonCallBack( u32 button_no, u32 event, void* p_work );
static void ZknPokeListSubButton_KeyMove( ZKN_POKELIST_SUB_GLB* p_glb );

// ���\�[�X�ǂݍ���
static void ZknPokeListSubResLoad( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap );
static void ZknPokeListSubResDelete( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap );
static void ZknPokeListSubBgLoad( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap );
static void ZknPokeListSubOamResLoad( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap );
static void ZknPokeListSubOamResRelease( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb );
static void ZknPokeListSubAddClact( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap );
static void ZknPokeListSubDeleteClact( ZKN_POKELIST_SUB_DRAWWORK* p_work );
static void ZknPokeListSubFontMake( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap );
static void ZknPokeListSubFontDelete( ZKN_POKELIST_SUB_DRAWWORK* p_work );

static void ZknPokeListSubBgSetUp( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap );
static void ZknPokeListSubBgDelete( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap );

static void ZknPokeListSub_ListNoChange( ZKN_POKELIST_SUB_GLB* p_glb, int no );

// ����
static void ZknPokeListSubListCount( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb );
static void ZknPokeListSubMoveDistGet( ZKN_POKELIST_SUB_WORK* p_work );
static void ZknPokeListSubDrawMove( ZKN_POKELIST_SUB_DRAWWORK* p_drawwork, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int add_num, fx32 draw_ref_par );
static void ZknPokeListSubDrawMoveLockTime( ZKN_POKELIST_SUB_DRAWWORK* p_drawwork, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb );
static void ZknPokeListSubResist( ZKN_POKELIST_SUB_WORK* p_work, int move_count, int move_way );

static BOOL ZknPokeListSubListMoveOkCheck( ZKN_POKELIST_SUB_WORK* p_work, ZKN_GLB_DATA* p_glb );
static BOOL ZknPokeListSubListAdd( ZKN_POKELIST_SUB_WORK* p_work, ZKN_GLB_DATA* p_glb );
static void ZknPokeListSubListMoveStop( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb );

#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
static fx32 ZknPokeListSubDrawRefParCalc( fx32 now_par, s32 now_rota );
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�@�T�u��ʁ@�z�C�[���A�v���P�[�V�����쐬
 *	
 *	@param	p_data		�A�v���P�[�V�����f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_PokeListSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_POKELIST_SUB_GLB*		p_glb;
	ZKN_POKELIST_SUB_GLBDRAW*	p_glbdraw;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakePokeListSubGlb( heap, zkn_sys );
	p_glbdraw = MakePokeListSubGlbDraw( heap, zkn_sys );
	p_event = MakePokeListSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_glbdraw;
	p_data->p_event_data	= p_event;
	p_data->event_num		= EventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknPokeListSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknPokeListSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknPokeListSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknPokeListSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknPokeListSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknPokeListSubProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�@�T�u��ʁ@�z�C�[���A�v���f�[�^�j��
 *
 *	@param	p_data	�A�v���P�[�V�����f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_PokeListSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeletePokeListSubGlb( p_data->p_glb_data ); 
	DeletePokeListSubGlbDraw( p_data->p_glb_data ); 
	DeletePokeListSubEvent( p_data->p_event_data );
}


//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�@�T�u��ʁ@�z�C�[���@�O���[�o���f�[�^�쐬�@
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_POKELIST_SUB_GLB* MakePokeListSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_POKELIST_SUB_GLB* p_glb;
	ZKN_APL_DATA* p_apl;
	int i;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_POKELIST_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_POKELIST_SUB_GLB) );

	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_POKELIST );
	p_glb->p_pokelist_glb = p_apl->p_glb_data;

	// ������
	for( i=0; i<ZKN_POKELIST_SUB_BUTTON_NUM; i++ ){
		p_glb->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;
	}

	// �C�x���g�L�[�|�C���^
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );

	// �q�[�v
	p_glb->heap = heap;

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�@�T�u��ʁ@�z�C�[���@�O���[�o���f�[�^�쐬�@
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *	
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_POKELIST_SUB_GLBDRAW* MakePokeListSubGlbDraw( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_POKELIST_SUB_GLBDRAW* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_POKELIST_SUB_GLBDRAW) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_POKELIST_SUB_GLBDRAW) );

	p_glb->p_glb_draw = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�@�T�u��ʁ@�z�C�[���@�C�x���g�f�[�^�쐬�@
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakePokeListSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;	// �C�x���g�e�[�u���쐬��
	int event_num = EventDataNumGet();

	// �C�x���g�e�[�u���������m��
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );

	
	// �C�x���g�f�[�^�쐬
	ZKN_EVENT_MakeStartMainPokeList( &p_event_tbl[0], zkn_sys, heap, ZKN_POKELIST_SUB_EVENT_POKELIST );

	return p_event_tbl;
}	

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�@�T�u��ʁ@�z�C�[���@	�O���[�o���f�[�^�j��
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeletePokeListSubGlb( ZKN_POKELIST_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );

	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�@�T�u��ʁ@�z�C�[���@	�O���[�o���f�[�^�j��
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeletePokeListSubGlbDraw( ZKN_POKELIST_SUB_GLBDRAW* p_glb )
{
	GF_ASSERT( p_glb );

	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�@�T�u��ʁ@�z�C�[���@	�C�x���g�f�[�^�j��
 *
 *	@param	p_event		�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeletePokeListSubEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	// �C�x���g�f�[�^�j��
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�z�C�[���A�v���C�x���g���擾
 *
 *	@param	none
 *
 *	@return	�z�C�[���A�v���C�x���g�f�[�^��
 *
 *
 */
//-----------------------------------------------------------------------------
static int EventDataNumGet( void )
{
	return ZKN_POKELIST_SUB_EVENT_NUM;
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
static int ZknPokeListSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_POKELIST_SUB_GLB*  p_glb = p_glbdata;
	ZKN_POKELIST_SUB_WORK* p_work;
	int i;

	p_dodata->p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_POKELIST_SUB_WORK) );
	GF_ASSERT(p_dodata->p_work);
	memset( p_dodata->p_work, 0, sizeof(ZKN_POKELIST_SUB_WORK) );

#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
		p_work = p_dodata->p_work;
		p_work->wheel_rota_par = ZKN_POKELIST_SUB_LIST_PAR_MIN;
#endif

	// �{�^���C�x���g���[�N������
	for( i=0; i<ZKN_POKELIST_SUB_BUTTON_NUM; i++ ){
		p_glb->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;
	}
		
	// �{�^���f�[�^�쐬
	ZknPokeListSubButtonMake( p_dodata->p_work, p_glb, p_dodata->heap );
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
static int ZknPokeListSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_POKELIST_SUB_GLB*  p_glb = p_glbdata;
	ZKN_POKELIST_SUB_WORK* p_work = p_dodata->p_work;
	

	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// ����X�s�[�h�����炵�Ă�
	ZknPokeListSubResist( p_work, p_glb->p_pokelist_glb->move_count, p_glb->p_pokelist_glb->move_way );


	// �{�^���C�x���g����
	ZknPokeListSubButtonMove( p_work, p_glb );


	// ���X�g�J�E���g
	if( p_glb->p_pokelist_glb->sub_wheel_lock == ZKN_POKELIST_WHEEL_LOCK_NONE ){		
		// ���C����ʂ��T�u�z�C�[����lock���Ă��Ȃ���Γ���
		ZknPokeListSubListCount( p_work, p_glb );
	}else{
		p_work->move_dist = 0;	// lock���ꂽ��Ƃ߂�
		p_work->move_dist_list = 0;
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
static int ZknPokeListSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	// �{�^���f�[�^�j��
	ZknPokeListSubButtonDelete( p_dodata->p_work );
	
	// �������j��
	sys_FreeMemoryEz( p_dodata->p_work );
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
static int ZknPokeListSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_POKELIST_SUB_GLB* cp_glb = cp_glbdata;
	const ZKN_POKELIST_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_SUB_GLBDRAW* p_drawglb = p_glbdraw;
	ZKN_POKELIST_SUB_DRAWWORK* p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_POKELIST_SUB_SEQINIT_ALLOC:
		// �������m��
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_POKELIST_SUB_DRAWWORK) );
		GF_ASSERT( p_drawdata->p_work );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_POKELIST_SUB_DRAWWORK) );


		p_drawdata->seq++;
		break;

	case ZKN_POKELIST_SUB_SEQINIT_LOAD:
		ZknPokeListSubResLoad( p_drawwork, p_drawglb, cp_glb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_SUB_SEQINIT_FADEIN_INIT:
		ChangeBrightnessRequest( ZKN_POKELIST_SUB_FADEIN_COUNT, 
				BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_SUB_DISPLAY );

		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_SUB_SEQINIT_FADEIN:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_POKELIST_SUB_SEQINIT_END:
		p_drawdata->seq++;
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
static int ZknPokeListSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_POKELIST_SUB_GLB* cp_glb = cp_glbdata;
	const ZKN_POKELIST_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_SUB_GLBDRAW* p_drawglb = p_glbdraw;
	ZKN_POKELIST_SUB_DRAWWORK* p_drawwork = p_drawdata->p_work;

	
	// �{�^������
	ZKN_UTIL_ButtonMove( p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ],
			cp_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] );
	ZKN_UTIL_ButtonMove( p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ], cp_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] );
	ZKN_UTIL_ButtonMove( p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ], cp_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] );
	ZKN_UTIL_ButtonMove( p_drawwork->list_start, cp_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_LISTSTART ] );
	ZKN_UTIL_ButtonMove( p_drawwork->list_end, cp_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_LISTEND ] );

	// ������{�^������
	ZknPokelistSubButtonFontMove( 
			p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ],
			p_drawwork->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_SEARCH ],
			ZKN_POKELIST_SUB_FONTOAM_OFS_Y,
			ZKN_POKELIST_SUB_BUTTON_FONT_COL,
			ZKN_POKELIST_SUB_BUTTON_FONT_PUSH_COL );
	ZknPokelistSubButtonFontMove( p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ], p_drawwork->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ],
			ZKN_POKELIST_SUB_FONTOAM_OFS_Y,
			ZKN_POKELIST_SUB_BUTTON_FONT_COL,
			ZKN_POKELIST_SUB_BUTTON_FONT_PUSH_COL );
	ZknPokelistSubButtonFontMove( p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ], p_drawwork->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ],
			ZKN_POKELIST_SUB_FONTOAM_OFS_Y,
			ZKN_POKELIST_SUB_BUTTON_FONT_COL_ZUKAN,
			ZKN_POKELIST_SUB_BUTTON_FONT_PUSH_COL );

	// �z�C�[������
	if( cp_glb->p_pokelist_glb->sub_wheel_lock == ZKN_POKELIST_WHEEL_LOCK_NONE ){
		ZknPokeListSubDrawMove( p_drawwork, p_drawglb,
				CalcTool_CircleVectroDistRotaGet( ZKN_POKELIST_SUB_MOVE_CACL_R, cp_datawork->move_dist ), // �ړ���������]�p�x�ɕύX
				cp_datawork->wheel_rota_par );		
	}else if( cp_glb->p_pokelist_glb->sub_wheel_lock == ZKN_POKELIST_WHEEL_LOCK_NORMAL ){
		// lock����Ă���Ƃ��̓���
		ZknPokeListSubDrawMoveLockTime( p_drawwork, p_drawglb, cp_glb );
	}else{
		// ���Slock�������܂���
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
static int ZknPokeListSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_POKELIST_SUB_GLB* cp_glb = cp_glbdata;
	const ZKN_POKELIST_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_SUB_GLBDRAW* p_drawglb = p_glbdraw;
	ZKN_POKELIST_SUB_DRAWWORK* p_drawwork = p_drawdata->p_work;
	BOOL check;

	
	switch( p_drawdata->seq ){
	case ZKN_POKELIST_SUB_SEQDELETE_FADEOUT_INIT:
		ChangeBrightnessRequest( ZKN_POKELIST_SUB_FADEIN_COUNT, 
				BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_SUB_DISPLAY );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_SUB_SEQDELETE_FADEOUT:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_POKELIST_SUB_SEQDELETE_RELEASE:
		ZknPokeListSubResDelete( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_SUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_SUB_SEQDELETE_END:
		return ZKN_PROC_TRUE;
	}
	
	return ZKN_PROC_FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�z�C�[���ʃ{�^���쐬
 *
 *	@param	p_work	�z�C�[�����[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubButtonMake( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb, int heap )
{
	ZKN_POKELIST_SUB_BUTTON_WORK* p_button_work;
	
	// �e�[�u���쐬
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_POKELIST_SUB_BUTTON_NUM );

	// �e�[�u���f�[�^�ݒ�
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_SEARCH ],
			ZKN_POKELIST_SUB_SEARCH_BUTTON_Y - (ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_SEARCH_BUTTON_Y + (ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_SEARCH_BUTTON_X - (ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_X/2),
			ZKN_POKELIST_SUB_SEARCH_BUTTON_X + (ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ],
			ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_Y - (ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_Y + (ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_X - (ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_X/2),
			ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_X + (ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ],
			ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_Y - (ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_Y + (ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_X - (ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_X/2),
			ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_X + (ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_LISTSTART ],
			ZKN_POKELIST_SUB_LISTSTART_BUTTON_Y - (ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_LISTSTART_BUTTON_Y + (ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_LISTSTART_BUTTON_X - (ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_X/2),
			ZKN_POKELIST_SUB_LISTSTART_BUTTON_X + (ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_LISTEND ],
			ZKN_POKELIST_SUB_LISTEND_BUTTON_Y - (ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_LISTEND_BUTTON_Y + (ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_LISTEND_BUTTON_X - (ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_X/2),
			ZKN_POKELIST_SUB_LISTEND_BUTTON_X + (ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_X/2) );

	p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_WHEEL ].circle.code = TP_USE_CIRCLE;
	p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_WHEEL ].circle.x	 = ZKN_POKELIST_SUB_CX;
	p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_WHEEL ].circle.y	 = ZKN_POKELIST_SUB_CY;
	p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_WHEEL ].circle.r	 = ZKN_POKELSIT_SUB_R;


	// CANCEL�{�^���p
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_CANCEL ],
			ZKN_POKELIST_SUB_BUTTON_HIT_Y,
			ZKN_POKELIST_SUB_BUTTON_HIT_Y + ZKN_POKELIST_SUB_BUTTON_HIT_HEIGHT,
			ZKN_POKELIST_SUB_BUTTON_HIT_X,
			ZKN_POKELIST_SUB_BUTTON_HIT_X + ZKN_POKELIST_SUB_BUTTON_HIT_WIDHT);

	// �{�^���p���[�N�쐬
	p_button_work = sys_AllocMemory( heap, sizeof(ZKN_POKELIST_SUB_BUTTON_WORK) );	
	p_button_work->p_work = p_work;
	p_button_work->p_glb  = p_glb;
	p_work->p_button_work = p_button_work;


	// �{�^���}�l�[�W���쐬
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_POKELIST_SUB_BUTTON_NUM,
			ZknPokeListSubButtonCallBack,
			p_button_work,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�z�C�[���{�^������
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubButtonMove( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb )
{
	int i;
	
	// �����ꂽ��S�Ẵ{�^�������̊G�ɖ߂�
	for( i = 0; i < ZKN_POKELIST_SUB_BUTTON_NUM; i++ ){
		p_glb->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;
	}

	// �L�[�ɂ��{�^������
	ZknPokeListSubButton_KeyMove( p_glb );
	
	// �^�b�`�p�l���ɂ��{�^������
	BMN_Main( p_work->p_button_man );

	// ���̃��X�g�ɐi�߂邩�`�F�b�N����
	if( ZknPokeListSubListMoveOkCheck( p_work, p_glb->p_pokelist_glb->p_glb ) == FALSE ){
		p_work->move_dist = 0;
	}

	// �z�C�[���`�攽�f�p�[�Z���g�v�Z
#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
	if( p_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_WHEEL ] != ZKN_UTIL_BUTTON_PUSH_NONE ){
		// �^�b�`�p�l���ɐG�����Ƃ��́A���������p�x�Ŕ��f����ύX������
		p_work->wheel_rota_par = ZknPokeListSubDrawRefParCalc( p_work->wheel_rota_par, p_work->move_dist );
	}else{
		// �^�b�`�p�l���ɐG���Ă��Ȃ��Ƃ��́A�������Ă��Ȃ��Ƃ���
		// �O�Ōv�Z����
		p_work->wheel_rota_par = ZknPokeListSubDrawRefParCalc( p_work->wheel_rota_par, 0 );
	}
#endif
}

//----------------------------------------------------------------------------
/**
 *	@brief	�z�C�[���{�^���j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubButtonDelete( ZKN_POKELIST_SUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );

	sys_FreeMemoryEz( p_work->p_button_work );

	// �e�[�u�����[�N�j��
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�z�C�[���{�^���R�[���o�b�N
 *
 *	@param	button_no	�{�^���i���o�[
 *	@param	event		�C�x���g�i���o�[
 *	@param	p_work		���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_POKELIST_SUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_POKELIST_SUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_POKELIST_SUB_WORK* p_datawork = p_button_work->p_work;
	ZKN_GLB_DATA* p_zkn_glb = p_glb->p_pokelist_glb->p_glb;
	int poketbl_num;
	int zkn_mode;


	// �{�^���C�x���g�f�[�^�ݒ�
	p_glb->button_event[ button_no ] = event;

	switch( event ){
	case BMN_EVENT_TOUCH:
		p_datawork->tp_last_x = sys.tp_x;
		p_datawork->tp_last_y = sys.tp_y;
		break;

	case BMN_EVENT_HOLD:
		switch( button_no ){
		case ZKN_POKELIST_SUB_BUTTON_SEARCH:
			p_glb->p_pokelist_glb->sort_chg = TRUE;
			break;

		case ZKN_POKELIST_SUB_BUTTON_ZUKANCHG:
			p_glb->p_pokelist_glb->zukan_chg = TRUE;
			break;
				
		case ZKN_POKELIST_SUB_BUTTON_ZUKANSEE:
			p_glb->p_pokelist_glb->zukan_see = TRUE;
			break;
			
		case ZKN_POKELIST_SUB_BUTTON_LISTSTART:
			if( p_datawork->touch_hold == FALSE ){
				ZknPokeListSub_ListNoChange( p_glb, 0 );
			}
			break;
			
		case ZKN_POKELIST_SUB_BUTTON_LISTEND:
			if( p_datawork->touch_hold == FALSE ){
				poketbl_num = ZKN_GLBDATA_PokeListTblNumGet( p_zkn_glb );
				ZknPokeListSub_ListNoChange( p_glb, poketbl_num - 1 );
			}
			break;

		case ZKN_POKELIST_SUB_BUTTON_CANCEL:
			// CANCEL�܂��́A���z�}OFF
			if(  p_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_NONE ){
				p_glb->p_pokelist_glb->zukan_end = TRUE;
			}else{
				p_glb->p_pokelist_glb->zukan_sort_end = TRUE;
			}
			break;

		default:
			break;
		}

		if( button_no == ZKN_POKELIST_SUB_BUTTON_WHEEL ){
 
			// ���C����ʑ��Ń^�b�`�p�l��������z�[���h���Ă��Ȃ����`�F�b�N
			if( p_glb->p_pokelist_glb->sub_wheel_lock == ZKN_POKELIST_WHEEL_LOCK_NONE ){
				// �ړ��������������߂�
				ZknPokeListSubMoveDistGet( p_datawork );	

				// ������ZKN_POKELIST_SUB_SUB_MIN_SP�����Ȃ�O�ɂ���
				if( (p_datawork->move_dist <= ZKN_POKELIST_SUB_SUB_MIN_SP) &&
					(p_datawork->move_dist >= -ZKN_POKELIST_SUB_SUB_MIN_SP) ){
					p_datawork->move_dist = 0;
				}

			}

			p_datawork->tp_last_x = sys.tp_x;
			p_datawork->tp_last_y = sys.tp_y;
		}
		p_datawork->touch_hold = TRUE;
		break;

	default:
		p_datawork->touch_hold = FALSE;
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�T�u��ʁ@���\�[�X�ǂݍ���
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubResLoad( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap )
{
	// �w�i
	ZknPokeListSubBgLoad( p_drawglb, cp_glb, heap );

	// �z�C�[��
	ZknPokeListSubBgSetUp( p_drawglb, heap );

	// OAM
	ZknPokeListSubOamResLoad( p_work, p_drawglb, heap );

	// �Z���A�N�^�[�o�^
	ZknPokeListSubAddClact( p_work, p_drawglb, cp_glb, heap );

	// FONTOAM�o�^
	ZknPokeListSubFontMake( p_work, p_drawglb, cp_glb, heap );

	// BG�D�揇�ʕύX
	GF_BGL_PrioritySet( ZKN_BG_FRM_AFFINE_S, 3 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�T�u��ʁ@���\�[�X�j��
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubResDelete( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap )
{
	// FONTOAM
	ZknPokeListSubFontDelete( p_work );

	// CLACT
	ZknPokeListSubDeleteClact( p_work );

	// OAM
	ZknPokeListSubOamResRelease( p_work, p_drawglb );

	// BG
	ZknPokeListSubBgDelete( p_drawglb, heap );

	// BG�D�揇�ʕύX
	GF_BGL_PrioritySet( ZKN_BG_FRM_AFFINE_S, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�T�u��ʁ@BG�ʂ̐ݒ�
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubBgLoad( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	GF_BGL_INI* p_bg = p_drawglb->p_glb_draw->p_bg;

	
	
	// �p���b�g�f�[�^�]��
	ZKN_GLBDATA_PalSet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list_NCLR, PALTYPE_SUB_BG, 0, 0, heap );

	// ���Ӱ�ނ̎��͐F�ύX
	if( cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT ){

		ZKN_GLBDATA_PalSet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list2_NCLR, PALTYPE_SUB_BG, ZKN_POKELIST_SUB_BACK_PL * 32, 32, heap );
	}else{

		// �S���}�ӂ̂Ƃ��͐F��ς���
		if( ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_pokelist_glb->p_glb ) == ZKN_MODE_ZENKOKU ){
			ZKN_GLBDATA_PalSet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list4_NCLR, PALTYPE_SUB_BG, ZKN_POKELIST_SUB_BACK_PL * 32, 32, heap );
		}
	}

	
	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list_sub_lzh_NCGR, p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list_bg_sub1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );
	
	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_bg, ZKN_BG_FRM_BACK_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�T�u��ʁ@OAM���\�[�X�ǂݍ���
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubOamResLoad( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_glb_draw;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_glb_draw );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_work->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_list_oam_sub_lzh_NCGR, TRUE,
			NARC_zukan_zkn_list_oam_sub_lzh_NCGR + ZKN_POKELIST_SUB_RES_ID_OFS,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_work->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_work->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_work->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_list_oam_NCLR, FALSE, 
			NARC_zukan_zkn_list_oam_NCLR + ZKN_POKELIST_SUB_RES_ID_OFS, 
			NNS_G2D_VRAM_TYPE_2DSUB, 
			ZKN_POKELIST_SUB_TBL_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_work->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_work->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_work->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_list_oam_sub_lzh_NCER, TRUE,
			NARC_zukan_zkn_list_oam_sub_lzh_NCER + ZKN_POKELIST_SUB_RES_ID_OFS,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_work->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_list_oam_sub_lzh_NANR, TRUE,
			NARC_zukan_zkn_list_oam_sub_lzh_NANR + ZKN_POKELIST_SUB_RES_ID_OFS,
			CLACT_U_CELLANM_RES, heap );

}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�T�u��ʁ@OAM���\�[�X�j��
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubOamResRelease( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_glb_draw;


	CLACT_U_CharManagerDelete( p_work->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_work->res_obj[ CLACT_U_PLTT_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_work->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_work->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_work->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_work->res_obj[ CLACT_U_CELLANM_RES ] );

}

//----------------------------------------------------------------------------
/**
 *	@brief	�z�C�[���Z���A�N�^�[�o�^
 *
 *	@param	p_work		���[�N
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubAddClact( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_glb_draw;
	
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_list_oam_sub_lzh_NCGR + ZKN_POKELIST_SUB_RES_ID_OFS,
			NARC_zukan_zkn_list_oam_NCLR + ZKN_POKELIST_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_list_oam_sub_lzh_NCER + ZKN_POKELIST_SUB_RES_ID_OFS,
			NARC_zukan_zkn_list_oam_sub_lzh_NANR + ZKN_POKELIST_SUB_RES_ID_OFS,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 8;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	
	// �|�P������T��
	add.mat.x = ZKN_POKELIST_SUB_SEARCH_BUTTON_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_SEARCH_BUTTON_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ],
			ZKN_POKELSIT_SUB_SEARCH_BUTTON_SEQ );
	// ���Ӱ�ނ̎��͔�\��
	if( cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT ){
		CLACT_SetDrawFlag( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ], FALSE );
	}

	// �}�ӂ�؂�ւ���
	add.mat.x = ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ], ZKN_POKELSIT_SUB_ZUKANCHG_BUTTON_SEQ );

	// �}�ӂ�؂�ւ����Ȃ��Ƃ��͔�\���ɂ���
	// ���Ӱ�ނ̎��͔�\��
	if( (ZKN_GLBDATA_PokeZknModeChengeCheck( cp_glb->p_pokelist_glb->p_glb, ZKN_MODE_ZENKOKU ) == FALSE) ||
		(cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT) ){
		CLACT_SetDrawFlag( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ], FALSE );
	}

	// �}�ӂ�����
	add.mat.x = ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ], ZKN_POKELSIT_SUB_ZUKANSEE_BUTTON_SEQ );

	// ���X�g�̐擪��
	add.mat.x = ZKN_POKELIST_SUB_LISTSTART_BUTTON_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_LISTSTART_BUTTON_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->list_start = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->list_start, ZKN_POKELSIT_SUB_LISTSTART_BUTTON_SEQ );

	// ���X�g�̍Ō����
	add.mat.x = ZKN_POKELIST_SUB_LISTEND_BUTTON_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_LISTEND_BUTTON_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->list_end = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->list_end, ZKN_POKELSIT_SUB_LISTEND_BUTTON_SEQ );


	// B�Ƃ����{�^��
	add.mat.x = ZKN_POKELIST_SUB_BUTTON_B_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_BUTTON_B_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->act_B = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->act_B, ZKN_POKELIST_SUB_BUTTON_B_ANM );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubDeleteClact( ZKN_POKELIST_SUB_DRAWWORK* p_work )
{
	CLACT_Delete( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] );
	CLACT_Delete( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] );
	CLACT_Delete( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] );
	CLACT_Delete( p_work->list_start );
	CLACT_Delete( p_work->list_end );
	CLACT_Delete( p_work->act_B );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�쐬
 *
 *	@param	p_work		���[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubFontMake( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_glb_draw;
	int pltt_ofs;	// �p���b�g�A�h���X

	// ���CLACT��o�^���Ă���K�v������
	GF_ASSERT( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] );

	// �p���b�g�̃��\�[�X�f�[�^�擾
	// �p���b�g�v���N�V�擾�p
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_list_oam_NCLR + ZKN_POKELIST_SUB_RES_ID_OFS );

	// �������f�[�^�̋��ʕ������쐬
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.x			 = ZKN_POKELIST_SUB_FONTOAM_OFS_X;
	fontoam_init.y			 = ZKN_POKELIST_SUB_FONTOAM_OFS_Y;
	fontoam_init.bg_pri		 = 0;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	
	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CX,
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CY );

	// SORT��ʂ�
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_POKELIST_BUTTON_05, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ];
	p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_SEARCH ]->p_fontoam, pltt_ofs + ZKN_POKELIST_SUB_BUTTON_FONT_COL );
	// ���Ӱ�ނ̎��͔�\��
	if( cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT ){
		FONTOAM_SetDrawFlag( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_SEARCH ]->p_fontoam, FALSE );
	}

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );


	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CX,
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CY );

	// �}�Ӑ؂�ւ�
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_POKELIST_BUTTON_03, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ];
	p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ]->p_fontoam, pltt_ofs + ZKN_POKELIST_SUB_BUTTON_FONT_COL );

	// �}�ӂ�؂�ւ����Ȃ��Ƃ��͔�\���ɂ���
	if( (ZKN_GLBDATA_PokeZknModeChengeCheck( cp_glb->p_pokelist_glb->p_glb, ZKN_MODE_ZENKOKU ) == FALSE) ||
		(cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT) ){
		FONTOAM_SetDrawFlag( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ]->p_fontoam, FALSE );
	}
	
	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );


	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CX,
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CY );
	
	// �}�ӂ�����
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_BUTTON_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ];
	p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ]->p_fontoam, pltt_ofs + ZKN_POKELIST_SUB_BUTTON_FONT_COL_ZUKAN );

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );


	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_POKELIST_SUB_FONT_B_BMP_CX,
			ZKN_POKELIST_SUB_FONT_B_BMP_CY );

	// B�{�^���̉��̃t�H���gOAM
	if( cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_NONE ){
		ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
				NARC_msg_zkn_dat, ZNK_BACK_00, 0, 0 );
	}else{
		ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
				NARC_msg_zkn_dat, ZNK_BACK_01, 0, 0 );
	}
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_work->act_B;
	fontoam_init.x			 = ZKN_POKELIST_SUB_FONT_B_OFS;
	fontoam_init.y			 = ZKN_POKELIST_SUB_FONT_B_OFS_Y;
	p_work->p_fontoam_B = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_work->p_fontoam_B->p_fontoam, pltt_ofs + ZKN_POKELIST_SUB_BUTTON_FONT_COL_CLOSE );

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubFontDelete( ZKN_POKELIST_SUB_DRAWWORK* p_work )
{
	ZKN_FONTOAM_Delete( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] );
	ZKN_FONTOAM_Delete( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] );
	ZKN_FONTOAM_Delete( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] );
	ZKN_FONTOAM_Delete( p_work->p_fontoam_B );
}



//----------------------------------------------------------------------------
/**
 *	@brief	�z�C�[���ʂ̕\��	
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubBgSetUp( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	GF_BGL_INI* p_bg = p_drawglb->p_glb_draw->p_bg;
	
	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list_disk_lzh_NCGR, p_bg, ZKN_BG_FRM_AFFINE_S, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list_bg_disk_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_AFFINE_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );
	
	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_bg, ZKN_BG_FRM_AFFINE_S );

	// �X�N���[�����W��ݒ�
	GF_BGL_ScrollSet( p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_SCROLL_X_SET, ZKN_POKELIST_SUB_BGFADE_DEF_X );
	GF_BGL_ScrollSet( p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_SCROLL_Y_SET, ZKN_POKELSIT_SUB_MAT_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�N���[����������
 *
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubBgDelete( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap )
{
	GF_BGL_INI* p_bg = p_drawglb->p_glb_draw->p_bg;
	GF_BGL_ClearCharSet( ZKN_BG_FRM_AFFINE_S, 64, 0, heap );
	GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_AFFINE_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���X�g�J�E���g����
 *
 *	@param	p_work	���[�N
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubListCount( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb )
{
	int rota;
	ZKN_GLB_DATA* p_zkn_glb = p_glb->p_pokelist_glb->p_glb;

	// ���J�E���g���łȂ��Ȃ瑫��
	if( p_glb->p_pokelist_glb->move_count <= 0 ){
		
		// �J�E���g�l������
		if( p_work->move_dist_list != 0 ){
			
			// �o�^
			// ���s�����瓮���~
			if( ZknPokeListSubListAdd( p_work, p_zkn_glb ) == FALSE ){

				ZknPokeListSubListMoveStop( p_work, p_glb );
			}else{
				p_glb->p_pokelist_glb->move_count = ZKN_POKELIST_MOVE_END_COUNT;
			
				// �I���ړ���
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}

		}else{

			// ����������J�E���g���O�Ȃ�I���
			p_glb->p_pokelist_glb->move_way = ZKN_POKE_LIST_NO_MOVE;
		}
	}

	// �����ݒ�
	if( p_work->move_dist_list < 0 ){
		p_glb->p_pokelist_glb->move_way = ZKN_POKE_LIST_UP;
	}else{
		if( p_work->move_dist_list > 0 ){
			p_glb->p_pokelist_glb->move_way = ZKN_POKE_LIST_DOWN;
		}
	}

	// ���X�g����
	if( p_glb->p_pokelist_glb->move_way != ZKN_POKE_LIST_NO_MOVE ){
		
		// ��Βl�ɂ���
		if( p_work->move_dist_list < 0 ){
			rota = -p_work->move_dist_list;
		}else{
			rota = p_work->move_dist_list;
		}

		// �J�E���g�l���擾
		rota /= ZKN_POKELIST_SUB_COUNT_R;

		// �J�E���g����
		p_glb->p_pokelist_glb->move_count -= rota;
		// �J�E���^���Ō�܂ōs�������`�F�b�N
		if( p_glb->p_pokelist_glb->move_count < 0 ){	
			p_glb->p_pokelist_glb->move_count = 0;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	��]�����������擾		06.08.02�ړ������ɕύX
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubMoveDistGet( ZKN_POKELIST_SUB_WORK* p_work )
{
	int last_y, last_x;
	int now_y, now_x;

	// �z�C�[���̒��S���W����̒l�ɂ���
	last_x = p_work->tp_last_x - ZKN_POKELIST_SUB_CX;
	last_y = p_work->tp_last_y - ZKN_POKELIST_SUB_CY;
	now_x = sys.tp_x - ZKN_POKELIST_SUB_CX;
	now_y = sys.tp_y - ZKN_POKELIST_SUB_CY;

	// �����l�����߂�
//	p_work->move_dist = CalcTool_CircleVectorMove( last_x, last_y, now_x, now_y );
	p_work->move_dist = CalcTool_CircleVectorDistance( last_x, last_y, now_x, now_y, ZKN_POKELIST_SUB_MOVE_CACL_R );
	p_work->move_dist *= ZKN_POKELIST_SUB_MOVE_CACL_MUL;

#if 0
	last_rota = FX_Atan2Idx( last_y, last_x );
	now_rota = FX_Atan2Idx( now_y, now_x );

	p_work->move_dist = now_rota - last_rota;

	// ��Βl�����߂�
	if( p_work->move_dist < 0 ){
		zettai = -p_work->move_dist;
	}else{
		zettai = p_work->move_dist;
	}

	// 180�ȏ�ɂȂ邱�Ƃ͍l���ɂ������̏ꍇ��,�O���R�U�O�Ƃ��čl����
	if( zettai >= FX_GET_ROTA_NUM(180) ){
		zettai = FX_GET_ROTA_NUM(360) - zettai;
		zettai = -zettai;		// 0->360�Ƃ����l���ɂȂ邩��x�N�g����ς���K�v������
	}

	// �ݒ�
	if( p_work->move_dist < 0 ){
		p_work->move_dist = -zettai;
	}else{
		p_work->move_dist = zettai;
	}
#endif
}

//----------------------------------------------------------------------------
/**
 *	@brief	�z�C�[���̕`�擮��
 *
 *	@param	p_drawwork	�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	add_num		��]�p�𓮂����l
 *	@param	draw_ref_par	�`���]�p���f�p�[�Z���g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubDrawMove( ZKN_POKELIST_SUB_DRAWWORK* p_drawwork, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int add_num, fx32 draw_ref_par )
{
#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
	int add_rot_num;
	add_rot_num = FX_Mul( add_num*FX32_ONE, draw_ref_par ) >> FX32_SHIFT;
	
	// ��]�p�x�����߂�
	p_drawwork->wheel_rota += add_rot_num;
	p_drawwork->wheel_rota &= 0xffff;
#else

	// ��]�p�x�����߂�
	p_drawwork->wheel_rota += add_num;
	p_drawwork->wheel_rota &= 0xffff;
#endif

	// ��]�p�x�̐ݒ�
	GF_BGL_RadianSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_RADION_SET, p_drawwork->wheel_rota / 182 );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_X_SET, ZKN_POKELIST_SUB_BGCX );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_Y_SET, ZKN_POKELIST_SUB_BGCY );

	// lock���ꂽ�ƋN�p�Ɋp�x��ۑ�
	p_drawwork->save_wheel_rota = p_drawwork->wheel_rota;
}

//----------------------------------------------------------------------------
/**
 *	@brief	lock����Ă���Ƃ��Ƀz�C�[���̊G�𓮂���
 *
 *	@param	p_drawwork		�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb			�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubDrawMoveLockTime( ZKN_POKELIST_SUB_DRAWWORK* p_drawwork, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb )
{
	int rota_num;
	int calc;
	int count = ZKN_POKELIST_MOVE_END_COUNT - cp_glb->p_pokelist_glb->move_count;
	
	//�@���̊p�x�v�Z
	calc = ZKN_POKELIST_SUB_LOCK_MOVE_DRAW_MAX * count;
	rota_num = calc / ZKN_POKELIST_MOVE_END_COUNT;
	
	// -�����ݒ�
	if( cp_glb->p_pokelist_glb->move_way == ZKN_POKE_LIST_UP ){
		rota_num = -rota_num;
	}

	// ��]�p�x�����߂�
	p_drawwork->wheel_rota = p_drawwork->save_wheel_rota + rota_num;
	p_drawwork->wheel_rota &= 0xffff;

	// ��]�p�x�̐ݒ�
	GF_BGL_RadianSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_RADION_SET, p_drawwork->wheel_rota / 182 );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_X_SET, ZKN_POKELIST_SUB_BGCX );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_Y_SET, ZKN_POKELIST_SUB_BGCY );


	// ����J�E���^��0�̎���]�p���Z�[�u����
	if( cp_glb->p_pokelist_glb->move_count == 0 ){
		p_drawwork->save_wheel_rota = p_drawwork->wheel_rota;
	} 
}


//----------------------------------------------------------------------------
/**
 *	@brief	�z�C�[���̃X�s�[�h�𗎂Ƃ�
 *
 *	@param	p_work	���[�N
 *	@param	move_count ����J�E���^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubResist( ZKN_POKELIST_SUB_WORK* p_work, int move_count, int move_way )
{
	// �`��p��]�p�v�Z
	if( p_work->move_dist > 0 ){
		if( p_work->move_dist - ZKN_POKELIST_SUB_SUB_R >= ZKN_POKELIST_SUB_SUBDRAWLIMIT_R ){

			p_work->move_dist -= ZKN_POKELIST_SUB_SUB_R;
		}else{
			p_work->move_dist = ZKN_POKELIST_SUB_SUBDRAWLIMIT_R;
		}
	}else{

		if( p_work->move_dist + ZKN_POKELIST_SUB_SUB_R <= -ZKN_POKELIST_SUB_SUBDRAWLIMIT_R ){
			p_work->move_dist += ZKN_POKELIST_SUB_SUB_R;
		}else{
			p_work->move_dist = -ZKN_POKELIST_SUB_SUBDRAWLIMIT_R;
		}
	}

	// ������l���f�p�����ɐݒ�
	p_work->move_dist_list = p_work->move_dist;


	// ���싗�����@ZKN_POKELIST_SUB_COUNT_R�̂Ƃ���
	// move_count��0�Ȃ��]���~�߂�
	if( (p_work->move_dist <= ZKN_POKELIST_SUB_SUBLIMIT_R) && 
		(p_work->move_dist >= -ZKN_POKELIST_SUB_SUBLIMIT_R)){
		if( move_count == 0 ){
			p_work->move_dist_list = 0;

			// �����ZKN_POKELIST_SUB_SUBDRAWLIMIT_R�ȉ��Ȃ�`��p
			// �������Ƃ߂�
			if( (p_work->move_dist <= ZKN_POKELIST_SUB_SUBDRAWLIMIT_R) && 
				(p_work->move_dist >= -ZKN_POKELIST_SUB_SUBDRAWLIMIT_R)){
				p_work->move_dist = 0;

#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
				p_work->wheel_rota_par = ZKN_POKELIST_SUB_LIST_PAR_MIN;
#endif
			}
		}else{

			// �J�E���g���Ƃ܂�Ȃ��悤��
			// ZKN_POKELIST_SUB_COUNT_R�����ɂ��Ȃ�
			if( move_way == ZKN_POKE_LIST_UP ){
				p_work->move_dist_list = -ZKN_POKELIST_SUB_SUBLIMIT_R;
				p_work->move_dist = -ZKN_POKELIST_SUB_SUBLIMIT_R;
			}else{
				p_work->move_dist_list = ZKN_POKELIST_SUB_SUBLIMIT_R;
				p_work->move_dist = ZKN_POKELIST_SUB_SUBLIMIT_R;
			}
		}
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
static void ZknPokelistSubButtonFontMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt )
{
	ZKN_UTIL_ButtonFontMove_Col( act, p_fontoam, def_y, off_pltt, on_pltt );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���C����ʂ̊Ǘ����Ă���L�[����ɂ��{�^���̓���
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubButton_KeyMove( ZKN_POKELIST_SUB_GLB* p_glb )
{
	ZKN_POKELIST_GLB_DATA* p_main_glb = p_glb->p_pokelist_glb;
	
	// �}�Ӊ�ʂ�
	if( p_main_glb->zukan_see ){
		p_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] = BMN_EVENT_HOLD;
		return;
	}//*/

	// SORT��ʂ�
	if( p_main_glb->sort_chg ){
		p_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] = BMN_EVENT_HOLD;
		return;
	}

	// �}�ӂ�؂�ւ���
	if( p_main_glb->zukan_chg ){
		p_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] = BMN_EVENT_HOLD;
		return;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�z�C�[���̐i��ł�����������āA���̕����ɐi�߂邩�`�F�b�N
 *
 *	@param  p_work		���[�N
 *	@param	p_glb		�}�ӃO���[�o���f�[�^
 *
 *	@retval	TRUE	�܂������OK
 *	@retval	FALSE	������Ⴞ��
 */
//-----------------------------------------------------------------------------
static BOOL ZknPokeListSubListMoveOkCheck( ZKN_POKELIST_SUB_WORK* p_work, ZKN_GLB_DATA* p_glb )
{
	int add_count;

	if( p_work->move_dist != 0 ){

		// ���X�g�𑫂����Ƃ��ł���̂��`�F�b�N
		// �����l����
		if( p_work->move_dist < 0 ){
			add_count = 1;
		}else{
			add_count = -1;
		}
		// ���s�����瓮���~
		if( ZKN_GLBDATA_PokeListDrawTblNoAddCheck( p_glb, add_count ) == FALSE ){
			return FALSE;
		}
	}
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���X�g�����Z
 *
 *	@param  p_work		���[�N
 *	@param	p_glb		�}�ӃO���[�o���f�[�^
 *
 *	@retval	TRUE	�܂������OK
 *	@retval	FALSE	������Ⴞ��
 */
//-----------------------------------------------------------------------------
static BOOL ZknPokeListSubListAdd( ZKN_POKELIST_SUB_WORK* p_work, ZKN_GLB_DATA* p_glb )
{
	int add_count;

	if( p_work->move_dist_list != 0 ){

		// ���X�g�𑫂����Ƃ��ł���̂��`�F�b�N
		// �����l����
		if( p_work->move_dist_list < 0 ){
			add_count = 1;
		}else{
			add_count = -1;
		}
		// ���s�����瓮���~
		if( ZKN_GLBDATA_PokeListDrawTblNoAdd( p_glb, add_count ) == FALSE ){
			return FALSE;
		}
	}
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�z�C�[�������I��
 *
 *	@param	p_work
 *	@param	p_glb 
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubListMoveStop( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb )
{
	p_work->move_dist_list = 0;
	p_work->move_dist = 0;
	p_glb->p_pokelist_glb->move_way = ZKN_POKE_LIST_NO_MOVE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���X�g�i���o�[�ݒ�
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *	@param	no		���X�g�i���o�[
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSub_ListNoChange( ZKN_POKELIST_SUB_GLB* p_glb, int no )
{
	// ���̑���ʐ؂�ւ����N�G�X�g�����Ă����珈�����Ȃ�
	if( ZKN_PokeList_SubEventSetOkCheck( p_glb->p_pokelist_glb ) == FALSE ){
		return ;
	}
	
	ZKN_GLBDATA_PokeListTblNoSet( p_glb->p_pokelist_glb->p_glb, no );

	(*p_glb->p_event_key) |= ZKN_POKELIST_SUB_EVENT_POKELIST;
	// ����J�E���^��������
	 p_glb->p_pokelist_glb->move_count = 0;	
	// �z�C�[���̓������~�߂�
	 p_glb->p_pokelist_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;	
	// �t�F�[�h�C�����[�h�ύX
	p_glb->p_pokelist_glb->fade_mode = ZKN_POKELIST_BG_FADE_SHUTTER;
	p_glb->p_pokelist_glb->fade_zukan_data = FALSE;
	// �������Ȃ�
	p_glb->p_pokelist_glb->move_way = ZKN_POKE_LIST_NO_MOVE;
	// �\���̕ύX�̓t�F�[�h�I�����Ă���
	p_glb->p_pokelist_glb->move_draw = FALSE;
}

#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
//----------------------------------------------------------------------------
/**
 *	@brief	�߹��ؽĕ`��@�z�C�[����]�p���f�p�[�Z���g�v�Z�֐�
 *
 *	@param	now_par		���݂̔��f�p�[�Z���g
 *	@param	now_rota	���v���C���[�����͂�����]�p
 *
 *	@return	�v�Z��̔��f�p�[�Z���g
 */
//-----------------------------------------------------------------------------
static fx32 ZknPokeListSubDrawRefParCalc( fx32 now_par, s32 now_rota )
{
	int abs_add;
	
	abs_add = MATH_ABS( now_rota );

	// �����l�̔��f����ύX
	if( abs_add < ZKN_POKELIST_SUB_LIST_PAR_ADD_LIMIT ){
		if( (now_par - ZKN_POKELIST_SUB_LIST_PAR_SUB) >= ZKN_POKELIST_SUB_LIST_PAR_MIN){
			now_par -= ZKN_POKELIST_SUB_LIST_PAR_SUB;
		}
	}else{
		if( (now_par + ZKN_POKELIST_SUB_LIST_PAR_ADD) <= ZKN_POKELIST_SUB_LIST_PAR_MAX ){
			now_par += ZKN_POKELIST_SUB_LIST_PAR_ADD;
		}
	}

	return now_par;
}
#endif
