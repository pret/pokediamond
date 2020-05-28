//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_pokelist.c
 *	@brief		�|�P�������X�g
 *	@author		tomoya takahashi
 *	@data		2006.01.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "include/application/zukanlist/zkn_event_func.h"
#include "include/system/brightness.h"
#include "include/system/arc_util.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"
#include "include/application/zukanlist/zkn_snd_def.h"

#include "include/application/zukanlist/zukan.naix"

#define __ZKN_POKELIST_H_GLOBAL
#include "include/application/zukanlist/zkn_pokelist.h"

// �G�t�F�N�g�ō��W��Link�����邽�߁A�d���Ȃ��C���N���[�h
#include "include/application/zukanlist/zkn_zukan.h"


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
//-------------------------------------
// �|�P�������X�g�`�揈���������V�[�P���X
//=====================================
enum{
	ZKN_POKELIST_DRAWINIT_SEQ_GRA_LOAD,
	ZKN_POKELIST_DRAWINIT_SEQ_FADEIN,
	ZKN_POKELIST_DRAWINIT_SEQ_FADEIN_WAIT,
	ZKN_POKELIST_DRAWINIT_SEQ_END,
};

//-------------------------------------
// �|�P�������X�g�`�揈�����C���V�[�P���X
//=====================================
enum{
	ZKN_POKELIST_DRAWMAIN_SEQ_END,
};

//-------------------------------------
// �|�P�������X�g�`�揈���j���V�[�P���X
//=====================================
enum{
	ZKN_POKELIST_DRAWEND_SEQ_FADEOUT,
	ZKN_POKELIST_DRAWEND_SEQ_FADEOUT_WAIT,
	ZKN_POKELIST_DRAWEND_SEQ_GRA_RELEASE,
	ZKN_POKELIST_DRAWEND_SEQ_END,
};


#define EVENT_DATA_NUM		( 5 )

// �C�x���g�萔
#define EVENT_MSK_POKELIST_CHENGE_SORTSEARCH	( 1 << 0 )
#define EVENT_MSK_POKELIST_CHENGE_ZUKAN			( 1 << 1 )
#define EVENT_MSK_POKELIST_ZUKAN_END			( 1 << 2 )
#define EVENT_MSK_POKELIST_MAIN_CHANGE			( 1 << 3 )
#define EVENT_MSK_POKELIST_CHANGE				( 1 << 4 )

// ����萔
#define ZKN_POKE_LIST_MOVE_CHENGE_NUM		( 4 )	// �X�s�[�h��ύX�����
#define ZKN_POKE_LIST_MOVE_CHENGE_TIMING	( 4 )	// ���̉񐔃|�P�����f�[�^�i���o�[��ύX������X�s�[�h��ύX
#define ZKN_POKE_LIST_MOVE_COUNT_S		( 60 )	// 1=10�̒P��
#define ZKN_POKE_LIST_MOVE_COUNT_MUL	( 1.60f )	// �J�E���g�A�b�v�����Z�l

#define ZKN_POKE_LIST_MOVE_SKIP_NUM	( 5 )		// �X�L�b�v��


// �t�F�[�h�C���萔
#define ZKN_POKELIST_FADEIN_SYNC	( ZKN_FADE_SYNC_LONG_COMMON)		// �t�F�[�h�C���V���N��
// �t�F�[�h�A�E�g�萔
#define ZKN_POKELIST_FADEOUT_SYNC	( ZKN_FADE_SYNC_LONG_COMMON)		// �t�F�[�h�C���V���N��

// BG�u���C�g�l�X�t�F�[�h��
#define ZKN_POKELSIT_BRIGHTNESS_MSK	( GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_OBJ|GX_BLEND_PLANEMASK_BD )	// �ʏ�
#define ZKN_POKELSIT_BRIGHTNESS_ZUKAN_MSK	( GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )	// �}�Ӄt�F�[�h�p
#define ZKN_POKELIST_BRIGHTNESS_ZUKAN_END_MSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )



// �w�i
#define ZKN_POKELIST_BACK_POKEFRAME_CX	( 1 )
#define ZKN_POKELIST_BACK_POKEFRAME_CY	( 4 )


// ������
#define ZKN_POKELIST_STR_Y			( 152 )
#define ZKN_POKELIST_SEE_STR_X		( 8 )
#define ZKN_POKELIST_GET_STR_X		( 128 )
#define ZKN_POKELIST_SEE_NUM_X		( 48 )
#define ZKN_POKELIST_SEE_NUM_Y		( 170 )
#define ZKN_POKELIST_GET_NUM_X		( 180 )
#define ZKN_POKELIST_GET_NUM_Y		( 170 )
#define ZKN_POKELIST_NUM_STR		( 32 )	// �o�b�t�@�T�C�Y
#define ZKN_POKELIST_PLACE			( 3 )	// ��




// �Z���A�N�^�[���\�[�X��
#define ZKN_POKELIST_CELL_CG_NUM	( 2 )
#define ZKN_POKELIST_CELL_CL_NUM	( 2 )
#define ZKN_POKELIST_CELL_CE_NUM	( 2 )
#define ZKN_POKELIST_CELL_AN_NUM	( 2 )


// �|�P�����e�[�u���萔
#define ZKN_POKELIST_POKETBL_NUM	(9)		// �\���p�|�P�����e�[�u����
#define ZKN_POKELIST_POKETBL_CHECK	(4)		// �I���|�P�����̈ʒu
#define ZKN_POKELIST_POKETBL_TBL_DEFX	( 180 * FX32_ONE )
#define ZKN_POKELIST_POKETBL_TBL_CHECKX	( ZKN_POKELIST_TBL_MAT_X * FX32_ONE )
const static ZknPokeListPokeTblMoveX[] = {		// ����e�[�u��
	ZKN_POKELIST_POKETBL_TBL_DEFX + 9*FX32_ONE,		// �T��
	ZKN_POKELIST_POKETBL_TBL_DEFX + 5*FX32_ONE,		// �`�� 
	ZKN_POKELIST_POKETBL_TBL_DEFX + 1*FX32_ONE,		// �`�� 
	ZKN_POKELIST_POKETBL_TBL_DEFX - 3*FX32_ONE,		// �`�� 
	ZKN_POKELIST_POKETBL_TBL_DEFX - 5*FX32_ONE,		// �`��
	ZKN_POKELIST_POKETBL_TBL_CHECKX,	// �I��
	ZKN_POKELIST_POKETBL_TBL_DEFX - 5*FX32_ONE,		// �`��
	ZKN_POKELIST_POKETBL_TBL_DEFX - 3*FX32_ONE,		// �`��
	ZKN_POKELIST_POKETBL_TBL_DEFX + 1*FX32_ONE,		// �`��
	ZKN_POKELIST_POKETBL_TBL_DEFX + 5*FX32_ONE,		// �`��
	ZKN_POKELIST_POKETBL_TBL_DEFX + 9,		// �T��
};
const static ZknPokeListPokeTblMoveY[] = {		// ����e�[�u��
	12 * FX32_ONE,
	22 * FX32_ONE,		// ��������`��
	26 * FX32_ONE,
	42 * FX32_ONE, 
	58 * FX32_ONE,
	82 * FX32_ONE,		// �I��
	106 * FX32_ONE,
	122 * FX32_ONE,
	138 * FX32_ONE,
	142 * FX32_ONE,		// �����܂�
	152 * FX32_ONE,
};
#if 0
const static ZknPokeListPokeTblMoveX[] = {		// ����e�[�u��
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// �\��
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// �T��
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// �`�� 
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// �`��
	ZKN_POKELIST_POKETBL_TBL_CHECKX,	// �I��
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// �`��
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// �`��
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// �T��
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// �\��
};
const static ZknPokeListPokeTblMoveY[] = {		// ����e�[�u��
	7 * FX32_ONE,	// 5
	12 * FX32_ONE,	// 10
	22 * FX32_ONE,	// 26
	48 * FX32_ONE,  // 34
	82 * FX32_ONE,
	116 * FX32_ONE,
	142 * FX32_ONE,
	152 * FX32_ONE,
	157 * FX32_ONE,
};
#endif
#define ZKN_POKELIST_PLTT_SELECT	(0)		// �����̃��X�g�̃J���[
#define ZKN_POKELIST_PLTT_OTHER0	(7)		// ���̑��̃��X�g�̃J���[
#define ZKN_POKELIST_PLTT_OTHER1	(8)		// ���̑��̃��X�g�̃J���[
#define ZKN_POKELIST_PLTT_OTHER2	(9)		// ���̑��̃��X�g�̃J���[

#define ZKN_POKELIST_OAM_BG_PRI	( 2 )


// Cursor�萔
#define ZKN_POKELIST_CURSOR_X		( 248 * FX32_ONE )	// X���W
#define ZKN_POKELIST_CURSOR_YMIN	( 58 * FX32_ONE )	// �ŏ�Y���W
#define ZKN_POKELIST_CURSOR_YDIS	( 54 * FX32_ONE )	// Y�ړ�����


// �|�P����OAM�萔
#define ZKN_POKELIST_ICON_ANMSEQ	( 1 )
#define ZKN_POKELIST_ICON_PRI		( 0 )
#define ZKN_POKELIST_POKETBL_ANMSEQ	( 0 )
#define ZKN_POKELIST_POKETBL_PRI	( 32 )
#define ZKN_POKELIST_CURSOR_ANMSEQ	( 2 )
#define ZKN_POKELIST_CURSOR_PRI		( 0 )





//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�|�P�������X�g�`��O���[�o���f�[�^
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// �`��O���[�o���f�[�^
} ZKN_POKELIST_GLB_DRAW;


//-------------------------------------
//	�|�P�������X�g���[�N
//=====================================
typedef struct {
	int move_way;			// ��������ۑ�
	int move_count_add_num;	// �O���[�o���f�[�^��move_count���Z��
	int move_speed_chg_timing;	// �X�s�[�h��ύX����^�C�~���O
	int move_speed_chg_num;	// �X�s�[�h��ύX������

	int sub_seq;		// �T�u�œ��������p�̃V�[�P���X
	
	BOOL skip_flag;		// �X�L�b�v�t���O
	int skip_count;		// �X�L�b�v�J�E���^
	int skip_add;		// 1��̑����Z�l
	int skip_way;		// �X�L�b�v����

} ZKN_POKELIST_WORK;

//-------------------------------------
//	�|�P�������X�g�O���t�B�b�N���[�N
//=====================================
typedef struct {
	CLACT_WORK_PTR	poke_tbl[ ZKN_POKELIST_POKETBL_NUM ];// �|�P�������e�[�u��
	int poke_tbl_start;				// �|�P�������e�[�u���̍��W�O�̗v�f��
	ZKN_FONTOAM_DATA* poke_name[ ZKN_POKELIST_POKETBL_NUM ];// �|�P������OAM
	int poke_name_char_size;		// �|�P�������̃L�����N�^�f�[�^��]������̈�̃T�C�Y

	CLACT_WORK_PTR	icon[ ZKN_POKELIST_POKETBL_NUM ];// �|�P�������e�[�u���w��A�C�R��
	CLACT_WORK_PTR	cursor;			// �S�̂̌��݂̈ʒu�J�[�\��
	fx32	onepoke_move_dis;		// 1�̃|�P����������������Cursor�̈ړ��l

	CLACT_WORK_PTR dummy_poke;	// �|�P�����O���t�B�b�N�_�~�[
	
	// ���\�[�X�}�l�[�W��
	CLACT_U_RES_MANAGER_PTR	res_manager[ ZKN_CLACT_RES_MANAGER_NUM ];	
	
	// �Z���A�N�^�[�o�^�w�b�_
	CLACT_HEADER		clheader;
	CLACT_HEADER		clheader_dummy_poke;

	void*			p_util_scrn_buff;
	NNSG2dScreenData* p_util_scrn;	// ���[�e�B���e�B�ʂ̃X�N���[���f�[�^
	ZKN_UTIL_BGSHTTER_DADE bg_fade;	// BG�ʃt�F�[�h�f�[�^

	// �}�Ӄt�F�[�h�p���샏�[�N
	ZKN_UTIL_MOVE_WORK pokegra_move;
	ZKN_UTIL_MOVE_WORK pokelist_move;


	// �������ɕ\������Ă���|�P�����̃e�[�u���v�f���iZKN_GLBDATA.ZKN_POKELIST_TBL�̔z��̗v�f�� �j
	int draw_poke_name;				
} ZKN_POKELIST_GRAWORK;


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
static ZKN_POKELIST_GLB_DATA* MakeGlbData( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteGlbData( ZKN_POKELIST_GLB_DATA* p_glb );

static ZKN_POKELIST_GLB_DRAW* MakeGlbDraw( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteGlbDraw( ZKN_POKELIST_GLB_DRAW* p_glb );

// �C�x���g�f�[�^�֌W
static ZKN_EVENT_DATA* MakeEventData( int heap, ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys );
static void DeleteEventData( ZKN_EVENT_DATA* p_event_data );
static int EventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		�A�v���P�[�V�����v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
// �v���Z�X�֐�
static int ZknPokeListProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknPokeListProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknPokeListProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// FadeInOut
static void ZknPokeListDefaultFadeReq( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );
static BOOL ZknPokeListDefaultFadeEndCheck( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );
static void ZknPokeListChZukanFadeReq( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );
static BOOL ZknPokeListChZukanFadeEndCheck( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );

static void PokeListBgFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );
static BOOL PokeListBgFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb );
static void PokeListBgFadeDel( ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );

static void PokeListPokeGraFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb );
static BOOL PokeListPokeGraFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb );
static void PokeListPokeListFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb );
static BOOL PokeListPokeListFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb );


// ���암��
static void PokeListMoveMain( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int heap );
static BOOL PokeListMoveIf( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int heap );
static void PokeListMoveIfFlagReset( ZKN_POKELIST_GLB_DATA* p_glb );
static void PokeListMoveIfKey( ZKN_POKELIST_GLB_DATA* p_glb );
static void PokeListMoveInit( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work );
static void PokeListMoveUp( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work );
static void PokeListMoveReq( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int way );
static BOOL PokeListMoveAdd( ZKN_POKELIST_GLB_DATA* p_glb, int num );

static BOOL PokeListListReset( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );
static BOOL PokeListListStart( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );
static BOOL PokeListListEnd( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );

static void PokeListSkipMoveInit( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work );

static void PokeListZukanDel( ZKN_POKELIST_GLB_DATA* p_glb );
static void PokeListZukanChg( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );
static BOOL PokeListSortChg( ZKN_POKELIST_GLB_DATA* p_glb );
static BOOL PokeListZukanModeChg( ZKN_POKELIST_GLB_DATA* p_glb, int heap );
static void PokeListZukanReset( ZKN_POKELIST_GLB_DATA* p_glb, int heap );
static void PokeListSkipMove( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );
static void PokeListKeyMove( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );

// �������[�N�쐬
static void PokeListDrawWorkInit( ZKN_POKELIST_GRAWORK*	p_work, const ZKN_POKELIST_GLB_DATA* cp_dataglb );

// �t�@�C���ǂݍ��݁���ʍ쐬
static void PokeListLoadGraphicFile( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );
static void PokeListReleaseGraphicFile( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb );
static void PokeListLoadGraphicFileSortMode( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );
static void PokeListReleaseGraphicFileSortMode( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb );

static void PokeListBackGroundSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void PokeListUtilSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap, int zkn_mode );
static void PokeListUtilDelete( ZKN_POKELIST_GRAWORK* p_work );
static void PokeListFontSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap, int see_num, int get_num );
static void PokeListSortVerFontSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap, int list_num );
static void PokeListResManagerMake( ZKN_POKELIST_GRAWORK* p_work, int heap );
static void PokeListResManagerDelete( ZKN_POKELIST_GRAWORK* p_work );
static void PokeListClActResLoad( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void PokeListClActAdd( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void PokeListClActDelete( ZKN_POKELIST_GRAWORK* p_work );

static int PokeListPokeNameCharTransSizeGet( ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void PokeListPokeNameSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );
static void PokeListPokeNameDelete( ZKN_POKELIST_GRAWORK* p_work );
static void PokeGraphicSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb );


static void PokeListOamFadeInit( ZKN_POKELIST_GRAWORK* p_work );
static void PokeListOamFadeDelete( ZKN_POKELIST_GRAWORK* p_work );

// CLACT_OBJ�p�����[�^�v�Z���ݒ�֐��S
static void PokeListPokeTblInit( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListPokeTblMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListPokeTblDrawFlagSetUp( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListPokeTblListStartNumChenge( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListIconMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListCursorInit( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListCursorMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );

static void PokeListPokeNameMove( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );
static void PokeListPokeNameMoveNameChange( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );
static void PokeListPokeNameChange( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap, int pokename_tbl_no, int pokelist_tbl_no );
static void PokeListPokeNameDummySet( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap, int pokename_tbl_no, int pokenum );
static void PokeListPokeNameMoveMatGet( CLACT_WORK_PTR target_act, int* x, int* y );
static fx32 PokeListPokeTblMoveCalc( fx32 s, fx32 e, int max_count, int count );
static void PokeListPokeGraMove( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListDummyPokeGraMove( const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListPokeGraAlphaInit( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListSelectPokeDataGlbSet( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�v���P�[�V�����f�[�^	�쐬
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
void ZKN_PokeListAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_POKELIST_GLB_DATA* p_glb;
	ZKN_POKELIST_GLB_DRAW* p_glb_draw;
	ZKN_EVENT_DATA*	p_event_data_tbl;

	p_glb = MakeGlbData( heap, zkn_sys );
	p_glb_draw = MakeGlbDraw( heap, zkn_sys );
	p_event_data_tbl = MakeEventData( heap, p_data, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_glb_draw;
	p_data->p_event_data	= p_event_data_tbl;
	p_data->event_num		= EventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknPokeListProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknPokeListProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknPokeListProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknPokeListProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknPokeListProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknPokeListProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�v���P�[�V�����f�[�^�j��
 *
 *	@param	p_data	�A�v���P�[�V�����f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_PokeListAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteGlbData( p_data->p_glb_data );
	DeleteGlbDraw( p_data->p_glb_draw );
	DeleteEventData( p_data->p_event_data );
}



//----------------------------------------------------------------------------
/**
 *	@brief	�߹��ؽăC�x���g��ݒ肵�đ��v���`�F�b�N
 *
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@retval	TRUE	�悢
 *	@retval	FALSE	����
 */
//-----------------------------------------------------------------------------
BOOL ZKN_PokeList_SubEventSetOkCheck( const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	if( (cp_glb->zukan_sort_end == TRUE) ||		
		(cp_glb->zukan_end == TRUE) ||
		(cp_glb->zukan_see == TRUE) ||
		(cp_glb->zukan_chg == TRUE) ||
		(cp_glb->sort_chg  == TRUE) ){

		return FALSE;
	}
	return TRUE;
}




//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		�A�v���P�[�V�����f�[�^�쐬�֌W
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�̃O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v	
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_POKELIST_GLB_DATA* MakeGlbData( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_POKELIST_GLB_DATA*	p_glb;

	// �������m��
	p_glb = sys_AllocMemory( heap, sizeof(ZKN_POKELIST_GLB_DATA) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_POKELIST_GLB_DATA) );
	
	// �C�x���g�L�[�|�C���^�擾
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys );

	// �}�ӂ̊e�A�v���P�[�V�������L�f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );


	// �t�F�[�h�C�����[�h�ύX
	p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;

	// �}�Ӄf�[�^��ʂւ̃t�F�[�h�`�F�b�N�t���O
	p_glb->fade_zukan_data = FALSE;

	// �`��X�V�t���O
	p_glb->move_draw = TRUE;
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�O���[�o���f�[�^�j��
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteGlbData( ZKN_POKELIST_GLB_DATA* p_glb )
{
	GF_ASSERT( p_glb );
	
	sys_FreeMemoryEz(p_glb);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�̃O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v	
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_POKELIST_GLB_DRAW* MakeGlbDraw( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_POKELIST_GLB_DRAW*	p_glb;

	// �������m��
	p_glb = sys_AllocMemory( heap, sizeof(ZKN_POKELIST_GLB_DRAW) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_POKELIST_GLB_DRAW) );
	

	// �}�ӂ̊e�A�v���P�[�V�������L�O���t�B�b�N�f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�O���[�o���f�[�^�j��
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteGlbDraw( ZKN_POKELIST_GLB_DRAW* p_glb )
{
	GF_ASSERT( p_glb );
	
	sys_FreeMemoryEz(p_glb);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C�x���g�f�[�^�e�[�u���쐬
 *
 *	@param	heap		�q�[�v
 *	@param	p_data		�A�v���P�[�V�����f�[�^
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^�e�[�u��
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeEventData( int heap, ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_data;

	p_event_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) *  EventDataNumGet() );
	ZKN_EVENT_MakeChangeSortSearch( heap, &p_event_data[0], zkn_sys, EVENT_MSK_POKELIST_CHENGE_SORTSEARCH );
	ZKN_EVENT_MakeChangeZukan( heap, &p_event_data[1], zkn_sys, EVENT_MSK_POKELIST_CHENGE_ZUKAN );
	ZKN_EVENT_MakeZukanEnd( heap, &p_event_data[2], zkn_sys, EVENT_MSK_POKELIST_ZUKAN_END );
	ZKN_EVENT_MakeStartMainPokeList( &p_event_data[3], zkn_sys, heap, EVENT_MSK_POKELIST_MAIN_CHANGE );
	ZKN_EVENT_MakeChangePokeList( heap, &p_event_data[4], zkn_sys, EVENT_MSK_POKELIST_CHANGE );

	return p_event_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C�x���g�f�[�^�j��
 *
 *	@param	p_event_data		�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteEventData( ZKN_EVENT_DATA* p_event_data )
{
	GF_ASSERT( p_event_data );
	
	ZKN_EVENT_DeleteData( &p_event_data[0] );
	ZKN_EVENT_DeleteData( &p_event_data[1] );
	ZKN_EVENT_DeleteData( &p_event_data[2] );
	ZKN_EVENT_DeleteData( &p_event_data[3] );
	ZKN_EVENT_DeleteData( &p_event_data[4] );

	sys_FreeMemoryEz( p_event_data );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�C�x���g���擾
 *
 *	@param	none
 *
 *	@return	�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int EventDataNumGet( void )
{
	return	EVENT_DATA_NUM;
}




//-----------------------------------------------------------------------------
/**
 *		�A�v���P�[�V�����v���Z�X�֌W
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
static int ZknPokeListProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_POKELIST_GLB_DATA* p_glb = p_glbdata;
	
	// �������[�N������
	p_dodata->p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_POKELIST_WORK) );
	GF_ASSERT( p_dodata->p_work );
	memset( p_dodata->p_work, 0, sizeof(ZKN_POKELIST_WORK) );

	// ����f�[�^�ݒ�
	PokeListMoveInit( p_glb, p_dodata->p_work );

	// ���̃|�P���X�g�ʒu�ɕ`��ʒu�����킹��
	ZKN_GLBDATA_PokeListDrawTblSetNowTblNo( p_glb->p_glb );
	
	// �`��X�V�t���O
	p_glb->move_draw = TRUE;

	// �z�C�[�����b�N�t���O
	p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NONE;


	// ���Ӱ�ނ̂Ƃ��̓t�F�[�h���߂��V���b�^�[�ɂ���
	if( p_glb->fade_sort_data == TRUE ){
		p_glb->fade_mode = ZKN_POKELIST_BG_FADE_SHUTTER;
	}

	// ����t���O�̏�����
	PokeListMoveIfFlagReset( p_glb );

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
static int ZknPokeListProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_POKELIST_GLB_DATA* p_glb = p_glbdata;
	ZKN_POKELIST_WORK*	p_work = p_dodata->p_work;


	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	if( p_dodata->seq == 0 ){		//�@������
		p_glb->fade_sort_data = FALSE;
		p_dodata->seq = 1;
	}else{		// ���C��

		// ���C�����X�g����
		PokeListMoveMain( p_glb, p_work, p_dodata->heap );
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
static int ZknPokeListProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	// �������[�N�j��
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
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknPokeListProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	ZKN_POKELIST_GLB_DRAW* p_drawglb = p_glbdraw;
	const ZKN_POKELIST_GLB_DATA* cp_dataglb = cp_glbdata;
	const ZKN_POKELIST_WORK*	cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_GRAWORK*		p_work = p_drawdata->p_work;
	BOOL check;

	// �f�[�^�t�@�C���ǂݍ��ݏ����@�t�F�[�h����
	switch( p_drawdata->seq ){
	case ZKN_POKELIST_DRAWINIT_SEQ_GRA_LOAD:
		// �������[�N�쐬
		p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_POKELIST_GRAWORK) );
		GF_ASSERT(p_work);
		p_drawdata->p_work = p_work;
		PokeListDrawWorkInit( p_work, cp_dataglb );

		// �|�P�����O���t�B�b�N�Z�b�g�A�b�v
		PokeGraphicSetUp( p_work, p_drawglb->p_drawglb, cp_dataglb );

		
		p_drawdata->seq++;
		break;

	case  ZKN_POKELIST_DRAWINIT_SEQ_FADEIN:
		// �|�P�����̃O���t�B�b�N���]�������̂��܂�
		// �O���t�B�b�N�f�[�^�ǂݍ���
		if( cp_dataglb->p_glb->sort_search_flag == ZKN_SORTSEARCH_NONE ){
			// �ʏ�
			PokeListLoadGraphicFile( p_work, p_drawglb->p_drawglb, cp_dataglb, p_drawdata->heap );
		}else{
			// ���Ӱ��
			PokeListLoadGraphicFileSortMode( p_work, p_drawglb->p_drawglb, cp_dataglb, p_drawdata->heap );
		}

		// �}�ӗp�t�F�[�h���ʏ�t�F�[�h���`�F�b�N
		if( cp_dataglb->fade_zukan_data ){

			ZknPokeListChZukanFadeReq( p_work, p_drawglb, cp_dataglb, TRUE );
		}else{
			ZknPokeListDefaultFadeReq( p_work, p_drawglb, cp_dataglb, TRUE );
		}

		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_DRAWINIT_SEQ_FADEIN_WAIT:
	
		// �}�ӗp�t�F�[�h���ʏ�t�F�[�h���`�F�b�N
		if( cp_dataglb->fade_zukan_data ){
			check = ZknPokeListChZukanFadeEndCheck( p_work, p_drawglb, cp_dataglb, TRUE );
		}else{
			check = ZknPokeListDefaultFadeEndCheck( p_work, p_drawglb, cp_dataglb, TRUE );
		}
		if( check ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_POKELIST_DRAWINIT_SEQ_END:
		// ���l�̐ݒ�
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG0, GX_BLEND_PLANEMASK_BG3, 0, 16 );
		return ZKN_PROC_TRUE;

	default:
		// �����ɂ���̂͂�������
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
static int ZknPokeListProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	ZKN_POKELIST_GLB_DRAW* p_drawglb = p_glbdraw;
	const ZKN_POKELIST_GLB_DATA* cp_glb = cp_glbdata;
	const ZKN_POKELIST_WORK*	cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_GRAWORK*		p_work = p_drawdata->p_work;
	int tbl_no;

	// �`��X�VONOFF
	if( cp_glb->move_draw == FALSE ){
		return ZKN_PROC_FALSE;
	}

	// ���ݕ\�����̑I���|�P�����i���o�[���X�V
	tbl_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	if( p_work->draw_poke_name != tbl_no ){
		// �Z���^�[�\���e�[�u���i���o�[�ݒ�
		p_work->draw_poke_name = tbl_no;

		// ���X�g�ύX����
		// �|�P�������X�g�e�[�u���̐擪��ύX���鏈��
		// ���X�g�̕\����\�����Ǘ�
		PokeListPokeTblListStartNumChenge( p_work, cp_glb );
	
		// �|�P�������L�����N�^�f�[�^�ύX����
		PokeListPokeNameMoveNameChange( p_work, p_drawglb->p_drawglb, cp_glb, p_drawdata->heap );

		// �|�P�����O���t�B�b�N�̕ύX����
		PokeGraphicSetUp( p_work, p_drawglb->p_drawglb, cp_glb );
	}
	
	// ���X�g�`����W�ݒ�
	PokeListPokeTblMove( p_work, cp_glb );
	PokeListIconMove( p_work, cp_glb );
	PokeListCursorMove( p_work, cp_glb );
	PokeListPokeNameMove( p_work, p_drawglb->p_drawglb, cp_glb, p_drawdata->heap );
	PokeListPokeGraMove( p_work, p_drawglb->p_drawglb, cp_glb );
	PokeListDummyPokeGraMove( cp_glb );

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
static int ZknPokeListProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	ZKN_POKELIST_GLB_DRAW* p_drawglb = p_glbdraw;
	const ZKN_POKELIST_GLB_DATA* cp_dataglb = cp_glbdata;
	const ZKN_POKELIST_WORK*	cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_GRAWORK*		p_work = p_drawdata->p_work;
	BOOL check;

	// �f�[�^�t�@�C���ǂݍ��ݏ����@�t�F�[�h����
	switch( p_drawdata->seq ){
	case ZKN_POKELIST_DRAWEND_SEQ_FADEOUT:
		G2_BlendNone();

		// �}�ӗp�t�F�[�h���ʏ�t�F�[�h���`�F�b�N
		if( cp_dataglb->fade_zukan_data ){
			// �O���[�o���G���A�Ƀ|�P�������X�g�쐬
			PokeListSelectPokeDataGlbSet( p_work, p_drawglb->p_drawglb, cp_dataglb, p_drawdata->heap );

			// �|�P�����O���t�B�b�N���l���Z�b�g
			PokeListPokeGraAlphaInit( p_drawglb->p_drawglb, cp_dataglb );

			ZknPokeListChZukanFadeReq( p_work, p_drawglb, cp_dataglb, FALSE );
		}else{
			ZknPokeListDefaultFadeReq( p_work, p_drawglb, cp_dataglb, FALSE );
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_DRAWEND_SEQ_FADEOUT_WAIT:
		// �}�ӗp�t�F�[�h���ʏ�t�F�[�h���`�F�b�N
		if( cp_dataglb->fade_zukan_data ){
			check = ZknPokeListChZukanFadeEndCheck( p_work, p_drawglb, cp_dataglb, FALSE );
		}else{
			check = ZknPokeListDefaultFadeEndCheck( p_work, p_drawglb, cp_dataglb, FALSE );
		}
		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_POKELIST_DRAWEND_SEQ_GRA_RELEASE:
		PokeListReleaseGraphicFile( p_work, p_drawglb->p_drawglb );

		// �p�����[�N�j��
		sys_FreeMemoryEz( p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_POKELIST_DRAWEND_SEQ_END:
		return ZKN_PROC_TRUE;

	default:
		// �����ɂ���̂͂�������
		GF_ASSERT(0);
		break;
	}
	
	return ZKN_PROC_FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g���쏉����
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *	@param	p_work	�������[�N
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListMoveInit( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work )
{
	p_glb->move_way					= ZKN_POKE_LIST_NO_MOVE;
	p_work->move_way				= ZKN_POKE_LIST_NO_MOVE;
	p_work->move_count_add_num		= ZKN_POKE_LIST_MOVE_COUNT_S;
	p_work->move_speed_chg_timing	= ZKN_POKE_LIST_MOVE_CHENGE_TIMING;
	p_work->move_speed_chg_num		= ZKN_POKE_LIST_MOVE_CHENGE_NUM;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�L�b�v���쏉����
 *
 *	@param	p_glb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListSkipMoveInit( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work )
{
	p_work->move_count_add_num		= ZKN_POKELIST_MOVE_END_COUNT;
	p_work->move_speed_chg_timing	= 0;
	p_work->move_speed_chg_num		= 0;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g���C������
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListMoveMain( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int heap )
{
	// ���򏈗�
	if( PokeListMoveIf( p_glb, p_work, heap ) == TRUE ){
		return ;	// ��ʐ؂�ւ��������s��ꂽ�̂ŁA���̂܂ܔ�����
		// ������͂����āA����MoveIfFlagReset�����s�����
		// pokelist_sub�̃��X�g�擪�A�ŏI�W�����v�����s�ł���悤�ɂȂ����Ⴂ�܂�
	}

	// ����t���O�̏�����
	PokeListMoveIfFlagReset( p_glb );


	// �����~���Ă�����
	if( p_work->move_way == ZKN_POKE_LIST_NO_MOVE ){

		// �X�L�b�v����
		if( p_work->skip_flag == TRUE ){

			// �X�L�b�v����
			PokeListSkipMove( p_work, p_glb );
		}else{

			// �X�L�b�v���łȂ��Ƃ��̏���
			PokeListKeyMove( p_work, p_glb );
		}
	}


	// ����
	if( p_glb->sub_wheel_lock != ZKN_POKELIST_WHEEL_LOCK_NONE ){
		PokeListMoveUp( p_glb, p_work );
	}

	// �^�b�`�p�l���ƕ���^�C�~���O�������ɂȂ�悤��
	// ���̈ʒu�ŕ���L�[����
	PokeListMoveIfKey( p_glb );
	
}


//----------------------------------------------------------------------------
/**
 *	@brief	����t���O���Z�b�g
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListMoveIfFlagReset( ZKN_POKELIST_GLB_DATA* p_glb )
{
	p_glb->zukan_sort_end = FALSE;			// SORT���[�h�I��
	p_glb->zukan_end = FALSE;				// �}�ӏI��
	p_glb->zukan_see = FALSE;				// �}�Ӄf�[�^������
	p_glb->zukan_chg = FALSE;				// �}�Ӄ��[�h�ύX
	p_glb->sort_chg = FALSE;				// SORT��ʂ֕ύX
}

//----------------------------------------------------------------------------
/**
 *	@brief	���z�L�[����
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListMoveIfKey( ZKN_POKELIST_GLB_DATA* p_glb )
{
	if( sys.trg & PAD_BUTTON_B ){
		if(  p_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_NONE ){
			p_glb->zukan_end = TRUE;
		}else{
			p_glb->zukan_sort_end = TRUE;
		}
		return ;
	}

	if( sys.trg & PAD_BUTTON_A ){
		p_glb->zukan_see = TRUE;
		return ;
	}

//	if( sys.trg & PAD_BUTTON_START ){
	if( sys.trg & PAD_BUTTON_X ){
		p_glb->sort_chg = TRUE;
		return ;
	}

	if( sys.trg & PAD_BUTTON_SELECT ){
		p_glb->zukan_chg = TRUE;
		return ;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���򏈗�
 *
 *	@param	p_glb
 *	@param	p_work
 *	@param	heap 
 *
 *	@retval	TRUE	������������
 *	@retval	FALSE	�������Ȃ�����
 */
//-----------------------------------------------------------------------------
static BOOL PokeListMoveIf( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int heap )
{
	// �}�Ӕj���C�x���g��
	if( p_glb->zukan_end ){

		PokeListZukanDel( p_glb );
		
		// �L�����Z����
		Snd_SePlay( ZKN_SND_CANCEL );
		return TRUE;
	}

	// SORT���[�h���Z�b�g
	if( p_glb->zukan_sort_end ){

		PokeListZukanReset( p_glb, heap );
		// �L�����Z����
		Snd_SePlay( ZKN_SND_CANCEL );
		return TRUE;
	}

	// �}�Ӊ�ʂ�
	if( p_glb->zukan_see ){
		int draw_tbl_no = ZKN_GLBDATA_PokeListDrawTblNoGet( p_glb->p_glb );
		// �����邩�`�F�b�N
		if( ZKN_GLBDATA_PokeListDrawTblDataGet( p_glb->p_glb, draw_tbl_no ) != POKEMON_LIST_DRAWTBL_DUMMY ){
			
			PokeListZukanChg( p_work, p_glb );

			// �I����
			Snd_SePlay( ZKN_SND_SELECT );
			return TRUE;
		}

	}//*/

	// SORT��ʂ�
	if( p_glb->sort_chg ){
		return PokeListSortChg( p_glb );
	}

	// �}�ӂ�؂�ւ���
	if( p_glb->zukan_chg ){
		return PokeListZukanModeChg( p_glb, heap );
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�s�[�h�A�b�v����
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *	@param	p_work		�������[�N
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListMoveUp( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work )
{
	// �����Ă��Ȃ��Ȃ甲����
	if( p_work->move_way == ZKN_POKE_LIST_NO_MOVE ){
		return;
	}

	// ����V���N���ύX
	if( (p_glb->move_count - p_work->move_count_add_num) > 0 ){
		// �J�E���g
		p_glb->move_count -= p_work->move_count_add_num;
	}else{
		// �J�E���g�I��
		p_glb->move_count = 0;
		p_work->move_way = ZKN_POKE_LIST_NO_MOVE;

		if( p_work->move_speed_chg_num > 0 ){
			// �J�E���g�A�b�v�X�s�[�h��ύX���邩�`�F�b�N
			if( (p_work->move_speed_chg_timing - 1) > 0 ){
				p_work->move_speed_chg_timing--;
			}else{
				p_work->move_count_add_num *= ZKN_POKE_LIST_MOVE_COUNT_MUL;
				p_work->move_speed_chg_num --;

				// �ύX���邽�тɃX�s�[�h�A�b�v�Ԋu��傫������
				p_work->move_speed_chg_timing = ZKN_POKE_LIST_MOVE_CHENGE_TIMING * (ZKN_POKE_LIST_MOVE_CHENGE_NUM - p_work->move_speed_chg_num);
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	����J�n���N�G�X�g���o��
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *	@param	p_work	�������[�N
 *	@param	way		�������
 *	
 *	@return	none
 *
	ZKN_POKE_LIST_UP,			// ��Ɉړ�
	ZKN_POKE_LIST_DOWN,			// ���Ɉړ�
 *
 */
//-----------------------------------------------------------------------------
static void PokeListMoveReq( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int way )
{
	p_glb->move_count			= ZKN_POKELIST_MOVE_END_COUNT;
	p_work->move_way			= way;
	p_glb->move_way				= way;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�w��|�P�������|�P�����������i�߂�
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *	@param	num		�i�߂�l
 *
 *	@retval	TRUE	�X�V���ꂽ
 *	@retval	FALSE	�l�͕ς��Ȃ�����
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL PokeListMoveAdd( ZKN_POKELIST_GLB_DATA* p_glb, int num )
{
	return ZKN_GLBDATA_PokeListDrawTblNoAdd( p_glb->p_glb, num );
}




//----------------------------------------------------------------------------
/**
 *
 *	@brief	�`��t�@�C���ǂݍ��݁�����
 *
 *	@param	p_work			�f�[�^�i�[���[�N
 *	@param	p_drawglb		�`��O���[�o���f�[�^
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	heap			�g�p�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListLoadGraphicFile( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	// BG��
	// �p���b�g�f�[�^�]��
	ZKN_GLBDATA_PalSet( p_drawglb, NARC_zukan_zkn_list_NCLR, PALTYPE_MAIN_BG, 0, 0, heap );

	// �w�i�ʐݒ�
	PokeListBackGroundSetUp( p_drawglb, heap );

	// ���[�e�B���e�B��
	PokeListUtilSetUp( p_work, p_drawglb, heap, ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_glb ) );

	// �������
	PokeListFontSetUp( p_drawglb, heap, 
			ZKN_GLBDATA_PokeSeeNumGet( cp_glb->p_glb ),
			ZKN_GLBDATA_PokeGetNumGet( cp_glb->p_glb ) );


	// �Z���f�[�^�ǂݍ���
	// ���\�[�X�}�l�[�W��������
	PokeListResManagerMake( p_work, heap );

	// ���\�[�X�ǂݍ���
	PokeListClActResLoad( p_work, p_drawglb, heap );

	// �A�N�^�[�o�^
	PokeListClActAdd( p_work, p_drawglb, heap );

	// ������OAM�o�^
	// �|�P�����e�[�u����]������̈�̃L�����N�^�T�C�Y�����߂�
	p_work->poke_name_char_size = PokeListPokeNameCharTransSizeGet( p_drawglb, heap );

	// �̈�쐬
	PokeListPokeNameSetUp( p_work, p_drawglb, cp_glb, heap );


	// �A�N�^�[���W�̃Z�b�g�A�b�v
	PokeListPokeTblInit( p_work, cp_glb );
	PokeListPokeTblMove( p_work, cp_glb );
	PokeListIconMove( p_work, cp_glb );
	PokeListCursorInit( p_work, cp_glb );
	PokeListCursorMove( p_work, cp_glb );

	// �����񓮍�
	PokeListPokeNameMove(p_work, p_drawglb, cp_glb, heap);

	// �|�P�����̃��l�Z�b�g�A�b�v
	PokeListPokeGraMove( p_work, p_drawglb, cp_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ǂݍ��݃f�[�^�j������
 *
 *	@param	p_work			���[�N�f�[�^
 *	@param	p_drawglb		�`��O���[�o���f�[�^
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListReleaseGraphicFile( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb )
{
	// �Z���f�[�^
	// �S�Z���A�N�^�[�̔j��
	PokeListClActDelete( p_work );	
	
	// ���\�[�X�}�l�[�W���̂͂�
	PokeListResManagerDelete( p_work );

	// ������OAM�j��
	PokeListPokeNameDelete( p_work );

	// ���[�e�B���e�B�ʃf�[�^�j��
	PokeListUtilDelete( p_work );

}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�̓ǂݍ��ݿ�ă��[�h
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���ް�
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListLoadGraphicFileSortMode( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	void* p_palBuff;
	NNSG2dPaletteData* p_palData;
	u8* p_pal_data;
	
	// BG��
	// �J���[�p���b�g��]��
	ZKN_GLBDATA_PalSet( p_drawglb, NARC_zukan_zkn_sort1_NCLR, PALTYPE_MAIN_BG, 0, 32, heap );
	// �p���b�g�f�[�^�]��
	p_palBuff = ZKN_GLBDATA_PalDataGet( p_drawglb, NARC_zukan_zkn_list_NCLR, &p_palData, heap );

	// �v�Z���₷���̂�u8*�ɃL���X�g
	p_pal_data = (u8*)p_palData->pRawData;
	DC_FlushRange( p_pal_data, 16*32 );
	GX_LoadBGPltt( p_pal_data + 32, 32, 15*32 );
	sys_FreeMemoryEz( p_palBuff );

	// �w�i�ʐݒ�
	PokeListBackGroundSetUp( p_drawglb, heap );

	// ���[�e�B���e�B��
	PokeListUtilSetUp( p_work, p_drawglb, heap, ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_glb ) );

	// �Z���f�[�^�ǂݍ���
	// ���\�[�X�}�l�[�W��������
	PokeListResManagerMake( p_work, heap );

	// ���\�[�X�ǂݍ���
	PokeListClActResLoad( p_work, p_drawglb, heap );

	// �A�N�^�[�o�^
	PokeListClActAdd( p_work, p_drawglb, heap );

	// ������OAM�o�^
	// �|�P�����e�[�u����]������̈�̃L�����N�^�T�C�Y�����߂�
	p_work->poke_name_char_size = PokeListPokeNameCharTransSizeGet( p_drawglb, heap );

	// �̈�쐬
	PokeListPokeNameSetUp( p_work, p_drawglb, cp_glb, heap );

	// �������
	PokeListSortVerFontSetUp( p_drawglb, heap, 
			ZKN_GLBDATA_PokeSeeNumGet( cp_glb->p_glb ) );


	// �A�N�^�[���W�̃Z�b�g�A�b�v
	PokeListPokeTblInit( p_work, cp_glb );
	PokeListPokeTblMove( p_work, cp_glb );
	PokeListIconMove( p_work, cp_glb );
	PokeListCursorInit( p_work, cp_glb );
	PokeListCursorMove( p_work, cp_glb );

	// �����񓮍�
	PokeListPokeNameMove(p_work, p_drawglb, cp_glb, heap);

	// �|�P�����̃��l�Z�b�g�A�b�v
	PokeListPokeGraMove( p_work, p_drawglb, cp_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG�ʂ̃Z�b�g�A�b�v
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	heap		�g�p�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListBackGroundSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	
	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb, NARC_zukan_zkn_list_main_lzh_NCGR, p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb, NARC_zukan_zkn_list_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// �|�P�����̕\���g��w�i�ɓ\��t��	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb, NARC_zukan_zkn_list_bg_main1a_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// �X�N���[���f�[�^��������
	GF_BGL_ScrWrite( p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_POKELIST_BACK_POKEFRAME_CX, ZKN_POKELIST_BACK_POKEFRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );
	
	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�̐}�Ӗ��\���ʐݒ�
 *
 *	@param	p_work			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o���f�[�^
 *	@param	heap			�q�[�v 
 *	@param	zkn_mode		�}�Ӄ��[�h
 *
 *	@return	none
 *
 * zkn_mode
	ZKN_MODE_SHINOH,	// �V���I�E�}��
	ZKN_MODE_ZENKOKU,	// �S���}��
 *
 */
//-----------------------------------------------------------------------------
static void PokeListUtilSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap, int zkn_mode )
{
	int dataidx;
	
	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb, NARC_zukan_zkn_list_main_lzh_NCGR, p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M, 0, 0, TRUE, heap );

	// �S���ƃV���I�E�Ńf�[�^idx��ύX
	if( zkn_mode == ZKN_MODE_ZENKOKU ){
		dataidx = NARC_zukan_zkn_list_bg_zen_lzh_NSCR;
	}else{
		dataidx = NARC_zukan_zkn_list_bg_sin_lzh_NSCR;
	}
	
	// �X�N���[���f�[�^�ǂݍ���
	p_work->p_util_scrn_buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb, dataidx, TRUE, &p_work->p_util_scrn, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���[�e�B���e�B�ʃf�[�^�j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListUtilDelete( ZKN_POKELIST_GRAWORK* p_work )
{
	sys_FreeMemoryEz( p_work->p_util_scrn_buff );
	p_work->p_util_scrn_buff = NULL;
	p_work->p_util_scrn = NULL;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P���X�g�t�H���g�ʐݒ�
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	heap		�q�[�vID
 *	@param	see_num		������
 *	@param	get_num		�ߊl��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListFontSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap, int see_num, int get_num )
{
	STRBUF* str = STRBUF_Create(ZKN_POKELIST_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	// �݂��������Ƃ���������
	MSGMAN_GetString( man, ZNK_POKELIST_00, str );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_SEE_STR_X, ZKN_POKELIST_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	// ���܂��������Ƃ���������
	MSGMAN_GetString( man, ZNK_POKELIST_01, str );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_GET_STR_X, ZKN_POKELIST_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// ������
	STRBUF_SetNumber( str, see_num, ZKN_POKELIST_PLACE, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_SEE_NUM_X, ZKN_POKELIST_SEE_NUM_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// �ߊl��
	STRBUF_SetNumber( str, get_num, ZKN_POKELIST_PLACE, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_GET_NUM_X, ZKN_POKELIST_GET_NUM_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	STRBUF_Delete(str);

	MSGMAN_Delete(man);

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��Ă̎��̓��X�g���̂ݏo��
 *
 *	@param	p_drawglb		�O���[�o���ް�
 *	@param	heap			�q�[�v
 *	@param	list_num		�\�����X�g�� 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListSortVerFontSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap, int list_num )
{
	STRBUF* str = STRBUF_Create(ZKN_POKELIST_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	// �݂��������Ƃ���������
	MSGMAN_GetString( man, ZNK_SORT_NUM, str );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_SEE_STR_X, ZKN_POKELIST_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	// ������
	STRBUF_SetNumber( str, list_num, ZKN_POKELIST_PLACE, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_SEE_NUM_X, ZKN_POKELIST_SEE_NUM_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	STRBUF_Delete(str);

	MSGMAN_Delete(man);

	// �X�N���[���f�[�^�]��
	GF_BGL_LoadScreenV_Req(p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�p���\�[�X�}�l�[�W���̍쐬
 *
 *	@param	p_work	���[�N
 *	@param	heap	�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListResManagerMake( ZKN_POKELIST_GRAWORK* p_work, int heap )
{
	// �Z���A�N�^�[�p���\�[�X�Ǘ��V�X�e��
	p_work->res_manager[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerInit( ZKN_POKELIST_CELL_CG_NUM, CLACT_U_CHAR_RES, heap );
	p_work->res_manager[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerInit( ZKN_POKELIST_CELL_CL_NUM, CLACT_U_PLTT_RES, heap );
	p_work->res_manager[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerInit( ZKN_POKELIST_CELL_CE_NUM, CLACT_U_CELL_RES, heap );
	p_work->res_manager[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerInit( ZKN_POKELIST_CELL_AN_NUM, CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�p���\�[�X�}�l�[�W���j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListResManagerDelete( ZKN_POKELIST_GRAWORK* p_work )
{
	CLACT_U_RES_OBJ_PTR res_obj;
	// �p���b�g�ƃL�����N�^�̊Ǘ��̈��j��
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_work->res_manager[ CLACT_U_CHAR_RES ], NARC_zukan_zkn_list_oam_main_lzh_NCGR );
	CLACT_U_CharManagerDelete( res_obj );
	
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_work->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_list_oam_NCLR );
	CLACT_U_PlttManagerDelete( res_obj );


	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_work->res_manager[ CLACT_U_CHAR_RES ], NARC_zukan_zkn_hatena_oam_lzh_NCGR );
	CLACT_U_CharManagerDelete( res_obj );
	

	
	// �Z���A�N�^�[�p���\�[�X�Ǘ��V�X�e��
	CLACT_U_ResManagerDelete( p_work->res_manager[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerDelete( p_work->res_manager[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerDelete( p_work->res_manager[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerDelete( p_work->res_manager[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�p���\�[�X�ǂݍ���
 *
 *	@param	p_work	���[�N
 *	@param	heap	�q�[�v
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListClActResLoad( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	CLACT_U_RES_OBJ_PTR res_obj;
	ARCHANDLE* p_handle =ZKN_GLBDATA_ArcHandlGet( p_drawglb ); 
	
	// �L�����N�^�f�[�^�ǂݍ���
	res_obj = CLACT_U_ResManagerResAddArcChar_ArcHandle( p_work->res_manager[ CLACT_U_CHAR_RES ], 
			p_handle, NARC_zukan_zkn_list_oam_main_lzh_NCGR,
			TRUE, NARC_zukan_zkn_list_oam_main_lzh_NCGR,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( res_obj );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( res_obj );

	// �p���b�g�f�[�^�ǂݍ���
	res_obj = CLACT_U_ResManagerResAddArcPltt_ArcHandle( p_work->res_manager[ CLACT_U_PLTT_RES ],
			p_handle, NARC_zukan_zkn_list_oam_NCLR,
			FALSE, NARC_zukan_zkn_list_oam_NCLR, NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_POKELIST_TBL_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( res_obj );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( res_obj );



	// �Z���f�[�^�ǂݍ���
	CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_work->res_manager[ CLACT_U_CELL_RES ],
			p_handle, NARC_zukan_zkn_list_oam_main_lzh_NCER,
			TRUE, NARC_zukan_zkn_list_oam_main_lzh_NCER,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_work->res_manager[ CLACT_U_CELLANM_RES ],
			p_handle, NARC_zukan_zkn_list_oam_main_lzh_NANR,
			TRUE, NARC_zukan_zkn_list_oam_main_lzh_NANR,
			CLACT_U_CELLANM_RES, heap );

	// �Z���A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &p_work->clheader,
			NARC_zukan_zkn_list_oam_main_lzh_NCGR,
			NARC_zukan_zkn_list_oam_NCLR,
			NARC_zukan_zkn_list_oam_main_lzh_NCER,
			NARC_zukan_zkn_list_oam_main_lzh_NANR,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, ZKN_POKELIST_OAM_BG_PRI,
			p_work->res_manager[ CLACT_U_CHAR_RES ],
			p_work->res_manager[ CLACT_U_PLTT_RES ],
			p_work->res_manager[ CLACT_U_CELL_RES ],
			p_work->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );


	// �L�����N�^�f�[�^�ǂݍ���
	res_obj = CLACT_U_ResManagerResAddArcChar_ArcHandle( p_work->res_manager[ CLACT_U_CHAR_RES ], 
			p_handle, NARC_zukan_zkn_hatena_oam_lzh_NCGR,
			TRUE, NARC_zukan_zkn_hatena_oam_lzh_NCGR,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( res_obj );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( res_obj );

	// �Z���f�[�^�ǂݍ���
	CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_work->res_manager[ CLACT_U_CELL_RES ],
			p_handle, NARC_zukan_zkn_hatena_oam_lzh_NCER,
			TRUE, NARC_zukan_zkn_hatena_oam_lzh_NCER,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_work->res_manager[ CLACT_U_CELLANM_RES ],
			p_handle, NARC_zukan_zkn_hatena_oam_lzh_NANR,
			TRUE, NARC_zukan_zkn_hatena_oam_lzh_NANR,
			CLACT_U_CELLANM_RES, heap );

	// �Z���A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &p_work->clheader_dummy_poke,
			NARC_zukan_zkn_hatena_oam_lzh_NCGR,
			NARC_zukan_zkn_list_oam_NCLR,
			NARC_zukan_zkn_hatena_oam_lzh_NCER,
			NARC_zukan_zkn_hatena_oam_lzh_NANR,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, ZKN_POKELIST_OAM_BG_PRI,
			p_work->res_manager[ CLACT_U_CHAR_RES ],
			p_work->res_manager[ CLACT_U_PLTT_RES ],
			p_work->res_manager[ CLACT_U_CELL_RES ],
			p_work->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�o�^
 *
 *	@param	p_work		���[�N
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListClActAdd( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	CLACT_ADD_SIMPLE	add;
	int i;

	// �o�^�f�[�^�e���v���[�g�쐬
	memset( &add, 0, sizeof(CLACT_ADD_SIMPLE) );
	add.ClActSet		= p_drawglb->clact_set;
	add.ClActHeader		= &p_work->clheader;
	add.DrawArea		= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap			= heap;

	
	// ���X�g�I�u�W�F�N�g
	add.pri		= ZKN_POKELIST_POKETBL_PRI;
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		p_work->poke_tbl[ i ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_work->poke_tbl[ i ], ZKN_POKELIST_POKETBL_ANMSEQ );
	}
	
	// �A�C�R��
	add.pri		= ZKN_POKELIST_ICON_PRI;
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		p_work->icon[ i ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_work->icon[ i ], ZKN_POKELIST_ICON_ANMSEQ );
	}

	// �J�[�\��
	add.pri			= ZKN_POKELIST_CURSOR_PRI;
	p_work->cursor	= CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->cursor, ZKN_POKELIST_CURSOR_ANMSEQ );

	// �_�~�[�|�P����
	add.pri			= 0;
	add.mat.x		= ZKN_POKELIST_POKEGRA_X << FX32_SHIFT;
	add.mat.y		= ZKN_POKELIST_POKEGRA_Y << FX32_SHIFT;
	add.ClActHeader		= &p_work->clheader_dummy_poke;
	p_work->dummy_poke = CLACT_AddSimple( &add );
	CLACT_SetDrawFlag( p_work->dummy_poke, FALSE );
	CLACT_ObjModeSet( p_work->dummy_poke, GX_OAM_MODE_XLU );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������O�e�[�u���쐬
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	int i;	// ���[�v�p
	int pokelist_s;	// �|�P�������X�g�̕\���v�f�̊J�n�ԍ�
	int poketbl_s;	// �|�P�����e�[�u���̕\���v�f�̊J�n�ԍ�
	int pokelist_tbl_num;	// �|�P�������X�g�e�[�u����
	ZKN_FONTOAM_INIT fontoam_init;
	GF_BGL_BMPWIN* p_bmp;	// �������ݗ̈�
	const ZKN_POKELIST_DATA* p_poke_data;	// �|�P�����f�[�^
	int poke_listdraw_link_list_idx;

	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = p_work->clheader.pPaletteProxy;
	fontoam_init.parent		 = NULL;
	fontoam_init.x			 = 0;
	fontoam_init.y			 = 0;
	fontoam_init.bg_pri		 = ZKN_POKELIST_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;


	// �|�P�������e�[�u����ZKN_POKELIST_POKETBL_NUM���쐬
	pokelist_s = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb ) - ZKN_POKELIST_POKETBL_CHECK;
	poketbl_s = p_work->poke_tbl_start;
	pokelist_tbl_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){

		// �j��
		if( p_work->poke_name[ poketbl_s ] ){
			ZKN_FONTOAM_Delete( p_work->poke_name[ poketbl_s ] );
			p_work->poke_name[ poketbl_s ] = NULL;
		}
		
		// �l���L�����`�F�b�N
		if( (pokelist_s >= 0) && (pokelist_s < pokelist_tbl_num) ){
			
			// �|�P�������X�g�`��z��idx����|�P�������X�g�f�[�^�z��idx���擾
			poke_listdraw_link_list_idx = ZKN_GLBDATA_PokeListDrawTblDataGet( cp_glb->p_glb, pokelist_s );
			// �_�~�[�łȂ���΃|�P��������������
			if( poke_listdraw_link_list_idx != POKEMON_LIST_DRAWTBL_DUMMY ){

				p_poke_data = ZKN_GLBDATA_PokeListTblGet( cp_glb->p_glb, poke_listdraw_link_list_idx );

#if 0
				// �����񏑂����ݗ̈�쐬
				p_bmp = ZKN_FONTOAM_GetBmp( p_drawglb->fontoam_sys, ZKN_POKELIST_POKENAME_BMP_SIZE_CX, ZKN_POKELIST_POKENAME_BMP_SIZE_CY );


				// �r�b�g�}�b�v�̈�ɏ�������
				ZKN_UTIL_PokeListPokeNameBmpMake( p_bmp, p_poke_data->mons_no, heap );
#endif
				// �r�b�g�}�b�v�̈�ɏ�������
				p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake( p_drawglb, cp_glb->p_glb, heap, p_poke_data->mons_no );

				
				// FONTOAM�o�^
				fontoam_init.p_bmp = p_bmp;
				p_work->poke_name[ poketbl_s ] = ZKN_FONTOAM_MakeCharOfs( &fontoam_init, p_work->poke_name_char_size );

				// BMP�̈�j��
				ZKN_FONTOAM_DeleteBmp( p_bmp );
			}else{

				// �_�~�[�̖��O�ݒ�
				PokeListPokeNameDummySet( p_work, p_drawglb, heap, poketbl_s, pokelist_s + 1 );
			}
		}else{

			p_work->poke_name[ poketbl_s ] = NULL;
		}

		poketbl_s = (poketbl_s + 1) % ZKN_POKELIST_POKETBL_NUM;
		pokelist_s ++;
	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�t�@�C���ݒ�
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	cp_glb		�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeGraphicSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	int pokelist_no;
	int drawpokelist_no;
	const ZKN_POKELIST_DATA* cp_pokedata;

	drawpokelist_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );

	pokelist_no = ZKN_GLBDATA_PokeListTblNoGet( cp_glb->p_glb );
	cp_pokedata = ZKN_GLBDATA_PokeListTblGet( cp_glb->p_glb , pokelist_no );

	// �\�����邩�`�F�b�N
	if( ZKN_GLBDATA_PokeListDrawTblDataGet( cp_glb->p_glb, drawpokelist_no ) == POKEMON_LIST_DRAWTBL_DUMMY ){
		// �`��OFF
		ZKN_GlbPokemonGraphicDrawFlagSet( p_drawglb,FALSE ); 
	
		// �_�~�[�`��ON
		if( p_work->dummy_poke ){
			CLACT_SetDrawFlag( p_work->dummy_poke, TRUE );
		}
	}else{

		// �|�P�����O���t�B�b�N�f�[�^�ݒ�
		ZKN_UTIL_PokemonGraphicSet( p_drawglb, cp_glb->p_glb, cp_pokedata->mons_no,
				PARA_FRONT, ZKN_POKELIST_POKEGRA_X, ZKN_POKELIST_POKEGRA_Y );

		// �`��ON
		ZKN_GlbPokemonGraphicDrawFlagSet( p_drawglb,TRUE ); 

		// �_�~�[�`��OFF
		if( p_work->dummy_poke ){
			CLACT_SetDrawFlag( p_work->dummy_poke, FALSE );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������O�e�[�u���j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameDelete( ZKN_POKELIST_GRAWORK* p_work )
{
	int i;

	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		if( p_work->poke_name[ i ] ){
			ZKN_FONTOAM_Delete( p_work->poke_name[ i ] );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�Z���A�N�^�[�j��
 *
 *	@param	p_work	���[�N
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListClActDelete( ZKN_POKELIST_GRAWORK* p_work )
{
	int i;

	// �|�P�����e�[�u��
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		CLACT_Delete( p_work->poke_tbl[ i ] );
	}

	// �A�C�R��
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		CLACT_Delete( p_work->icon[ i ] );
	}

	// �J�[�\��
	CLACT_Delete( p_work->cursor );

	//�@�_�~�[�ۂ����� 
	CLACT_Delete( p_work->dummy_poke );
}

// CLACT_OBJ�p�����[�^�v�Z���ݒ�֐��S
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P���X�g�e�[�u������O������
 *
 *	@param	p_work	�`�惏�[�N
 *	@param	cp_glb	�O���[�o���f�[�^
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeTblInit( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	p_work->poke_tbl_start = 0;

	// �\����\���ݒ�
	PokeListPokeTblDrawFlagSetUp( p_work, cp_glb );
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������O�e�[�u������
 *
 *	@param	p_work	�`�惏�[�N
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return none;
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeTblMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	int tbl_count;
	VecFx32 mat;
	int i;
	int tbl_s, tbl_e;
	int center_dis;		// ��������̋���
	int pri;			// �\���v���C�I���e�B
	int col;			// �J���[�p���b�g

	// move_count�ɂ����W��ݒ�
	tbl_count = p_work->poke_tbl_start;
	// �擪������W��ݒ肷��
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){

		// �J�n�e�[�u���ƏI���e�[�u���i���o�[�𓮂��Ă�������ɂ���ĕω�������
		if( cp_glb->move_way == ZKN_POKE_LIST_UP ){
			tbl_s = i + 2;		// �ЂƂ������玩���̍��W��
			tbl_e = i + 1;
		}else{
			tbl_s = i;			// �ЂƂ������玩���̍��W��
			tbl_e = i + 1;
		}
		
		mat.x = PokeListPokeTblMoveCalc( ZknPokeListPokeTblMoveX[ tbl_s ], ZknPokeListPokeTblMoveX[ tbl_e ], ZKN_POKELIST_MOVE_END_COUNT, ZKN_POKELIST_MOVE_END_COUNT - cp_glb->move_count );	// X���W�v�Z
		mat.y = PokeListPokeTblMoveCalc( ZknPokeListPokeTblMoveY[ tbl_s ], ZknPokeListPokeTblMoveY[ tbl_e ], ZKN_POKELIST_MOVE_END_COUNT, ZKN_POKELIST_MOVE_END_COUNT - cp_glb->move_count );	// Y���W�v�Z

		
		// ���W�ݒ�
		CLACT_SetMatrix( p_work->poke_tbl[ tbl_count ], &mat );

		// ���S����̋��������߂�
		center_dis = ZKN_POKELIST_POKETBL_CHECK - i;
		if( center_dis < 0 ){
			center_dis = -center_dis;
		}
		
		// �\���D�揇�ʌv�Z
		pri = center_dis * 2;
		if( pri < 0 ){
			pri = -pri;
		}
		pri += ZKN_POKELIST_POKETBL_PRI;
		CLACT_DrawPriorityChg( p_work->poke_tbl[ tbl_count ], pri );

		// �J���[�p���b�g
		// ����������ȊO�ŃJ���[�p���b�g�ύX
		if( i == ZKN_POKELIST_POKETBL_CHECK ){
			CLACT_PaletteOffsetChgAddTransPlttNo( p_work->poke_tbl[ tbl_count ], ZKN_POKELIST_PLTT_SELECT );
		}else{
			if( ZKN_POKELIST_PLTT_OTHER0 + (center_dis - 1) < ZKN_POKELIST_PLTT_OTHER2 ){
				CLACT_PaletteOffsetChgAddTransPlttNo( p_work->poke_tbl[ tbl_count ], ZKN_POKELIST_PLTT_OTHER0 + (center_dis - 1) );
			}else{
				CLACT_PaletteOffsetChgAddTransPlttNo( p_work->poke_tbl[ tbl_count ], ZKN_POKELIST_PLTT_OTHER2 );
			}
		}
		
		// ���̔z���
		tbl_count = (tbl_count + 1) % ZKN_POKELIST_POKETBL_NUM;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g�e�[�u���J�n�i���o�[�ύX����
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	cp_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeTblListStartNumChenge( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	int poke_last;
	int pokelist_no;
	int pokelist_num;
	
	pokelist_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	pokelist_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );
	
	// �ǂ̕����ɓ��삵�Ă��邩�`�F�b�N
	if( cp_glb->move_way == ZKN_POKE_LIST_UP ){
		// ��Ɉړ�	
		// �ύX
		if( (p_work->poke_tbl_start + 1) < ZKN_POKELIST_POKETBL_NUM ){
			p_work->poke_tbl_start ++;
		}else{
			p_work->poke_tbl_start = 0;
		}

		// �擪�����Ԍ���ɍs�����e�[�u���i���o�[�擾
		poke_last = p_work->poke_tbl_start + (ZKN_POKELIST_POKETBL_NUM - 1);
		poke_last %= ZKN_POKELIST_POKETBL_NUM;

		// ��\���e�[�u���`�F�b�N
		// ����ZKN_POKELIST_POKETBL_CHECK�Ȃ����`�F�b�N
		if( (pokelist_no + ZKN_POKELIST_POKETBL_CHECK) >= pokelist_num ){
			// ��ԉ��̃e�[�u�����\���ɂ���
			CLACT_SetDrawFlag( p_work->poke_tbl[ poke_last ], FALSE );
		}else{
			// ��ԉ��̃e�[�u����\���ɂ���
			CLACT_SetDrawFlag( p_work->poke_tbl[ poke_last ], TRUE );
		}
	}else{
		
		// ���Ɉړ�
		if( cp_glb->move_way == ZKN_POKE_LIST_DOWN ){
			if( (p_work->poke_tbl_start - 1) >= 0 ){
				p_work->poke_tbl_start --;
			}else{
				p_work->poke_tbl_start = ZKN_POKELIST_POKETBL_NUM - 1;
			}
		
			// ��������Ԑ擪�ɍs�����e�[�u���i���o�[�擾
			poke_last = p_work->poke_tbl_start;

			// ���ZKN_POKELIST_POKETBL_CHECK�Ȃ����`�F�b�N
			if( (pokelist_no - ZKN_POKELIST_POKETBL_CHECK) < 0 ){
				// ��ԏ�̃e�[�u�����W���ɂ���
				CLACT_SetDrawFlag( p_work->poke_tbl[ poke_last ], FALSE );
			}else{
				// ��ԏ�̃e�[�u����\���ɂ���
				CLACT_SetDrawFlag( p_work->poke_tbl[ poke_last ], TRUE );
			}
		}else{
			// ��ł����ł��Ȃ��l���ύX����Ă����Ƃ��͕\����ONOFF�ݒ�̂ݍs��
			PokeListPokeTblDrawFlagSetUp( p_work, cp_glb );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�C�R���̓���
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	cp_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListIconMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	const VecFx32* cp_mat;
	VecFx32 mat;
	int i;
	int tbl_no;
	BOOL draw_on_off;
	int pokelist_no_work;
	int pokelist_no;
	int pokelist_num;
	const ZKN_POKELIST_DATA* cp_poke_data;
	int pri;
	int pltt_no;
	int poke_listdraw_link_list_idx;

	pokelist_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	pokelist_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );
	
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		tbl_no = (p_work->poke_tbl_start + i) % ZKN_POKELIST_POKETBL_NUM;

		// �\��ONOFF�ݒ�
		draw_on_off = FALSE;
		pokelist_no_work = ((pokelist_no - ZKN_POKELIST_POKETBL_CHECK) + i);
		// ���̃|�P�����͕߂܂����|�P�������������|�P������
		if( (pokelist_no_work >= 0) && (pokelist_no_work < pokelist_num) ){
			// �|�P�������X�g�`��z��idx����|�P�������X�g�f�[�^�z��idx���擾
			poke_listdraw_link_list_idx = ZKN_GLBDATA_PokeListDrawTblDataGet( cp_glb->p_glb, pokelist_no_work );
			
			// �_�~�[�f�[�^�o�Ȃ����`�F�b�N
			if( poke_listdraw_link_list_idx != POKEMON_LIST_DRAWTBL_DUMMY ){
			
				cp_poke_data = ZKN_GLBDATA_PokeListTblGet( cp_glb->p_glb, poke_listdraw_link_list_idx );

				// �߂܂����|�P�������`�F�b�N
				if( cp_poke_data->type == ZKN_POKELIST_TYPE_GET ){
					draw_on_off = TRUE;
				}
			}
			
		}

		// �\���ݒ�
		CLACT_SetDrawFlag( p_work->icon[ tbl_no ], draw_on_off );

		// �\���Ȃ�ݒ�		
		if( draw_on_off ){
			
			// �|�P�����e�[�u���̃Z���^�[�e�[�u�����W�ɒǏ]
			cp_mat = CLACT_GetMatrix( p_work->poke_tbl[ tbl_no ] );

			mat.x = cp_mat->x + ZKN_POKELIST_ICON_X_OFS;
			mat.y = cp_mat->y;

			CLACT_SetMatrix( p_work->icon[ tbl_no ], &mat );

			// �e�e�[�u���Ɠ����J���[�p���b�g�ݒ�
			pltt_no = CLACT_PaletteOffsetGet( p_work->poke_tbl[ tbl_no ] );
			CLACT_PaletteOffsetChg( p_work->icon[ tbl_no ], pltt_no );

			// �\���D�揇�ʂ�ݒ�
			pri = CLACT_DrawPriorityGet( p_work->poke_tbl[ tbl_no ] );
			pri--;
			CLACT_DrawPriorityChg( p_work->icon[ tbl_no ], pri );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Cursor���쏉����
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	cp_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListCursorInit( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	int pokelist_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );
	
	p_work->onepoke_move_dis = FX_Div( ZKN_POKELIST_CURSOR_YDIS, pokelist_num << FX32_SHIFT );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Cursor����
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	cp_glb		�O���[�o���f�[�^
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListCursorMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	VecFx32	mat;
	int pokelist_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	
	// �S�̂̃|�P�������X�g�ł̍��̑I���|�P�����̈ʒu�ɂ����W�����߂�
	mat.y = FX_Mul( p_work->onepoke_move_dis, pokelist_no  << FX32_SHIFT );
	mat.y += ZKN_POKELIST_CURSOR_YMIN;
	mat.x = ZKN_POKELIST_CURSOR_X;

	CLACT_SetMatrix( p_work->cursor, &mat );
}



//----------------------------------------------------------------------------
/**
 *
 *	@brief	�|�P�������X�g���W�v�Z
 *
 *	@param	s				�J�n���W
 *	@param	e				�I�_���W
 *	@param	max_count		�ő�J�E���g��
 *	@param	count			���̃J�E���g�l
 *
 *	@return	���W
 *
 *
 */
//-----------------------------------------------------------------------------
static fx32 PokeListPokeTblMoveCalc( fx32 s, fx32 e, int max_count, int count )
{
	fx32 work;

	work = (e - s);

	work = FX_Mul( work, count << FX32_SHIFT );
	work = FX_Div( work, max_count << FX32_SHIFT );	// ���W

	return work + s;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�������[�N�̏�����
 *
 *	@param	p_work			���[�N
 *	@param	cp_dataglb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListDrawWorkInit( ZKN_POKELIST_GRAWORK*	p_work, const ZKN_POKELIST_GLB_DATA* cp_dataglb )
{
	memset( p_work, 0, sizeof(ZKN_POKELIST_GRAWORK) );
	p_work->draw_poke_name = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_dataglb->p_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������O�e�[�u������
 *
 *	@param	p_work		���[�N
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 *
 *
 *	��Ƀ|�P�������X�g�𓮂����Ă�������
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameMove( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	int i;
	int x, y;
	VecFx32 mat;
	int poke_tbl_no;
	int pri;
	int col;
	
	// �|�P�������X�g�̊e�e�[�u�����W�ɂ��킹��
	poke_tbl_no = p_work->poke_tbl_start;
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		if( p_work->poke_name[ poke_tbl_no ] ){
			// ���W�擾
			PokeListPokeNameMoveMatGet( p_work->poke_tbl[ poke_tbl_no ], &x, &y );
			// ���W�ݒ�
			FONTOAM_SetMat( p_work->poke_name[ poke_tbl_no ]->p_fontoam, 
					x, y );

			// �\���D�揇�ʐݒ�
			pri = CLACT_DrawPriorityGet( p_work->poke_tbl[ poke_tbl_no ] );
			pri--;
			FONTOAM_SetDrawPriority( p_work->poke_name[ poke_tbl_no ]->p_fontoam, pri );

			// �J���[�p���b�g
			col = CLACT_PaletteOffsetGet( p_work->poke_tbl[ poke_tbl_no ] );
			FONTOAM_SetPaletteOffset( p_work->poke_name[ poke_tbl_no ]->p_fontoam, col );
		}

		// ���̃e�[�u����
		poke_tbl_no = (poke_tbl_no + 1) % ZKN_POKELIST_POKETBL_NUM;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[���W�����ɏ��t�H���gOAM�̍��W�����߂�
 *
 *	@param	target_act	�^�[�Q�b�g�A�N�^�[
 *	@param	x			X���W
 *	@param	y			Y���W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameMoveMatGet( CLACT_WORK_PTR target_act, int* x, int* y )
{
	const VecFx32* p_mat;

	// ���W�擾
	p_mat = CLACT_GetMatrix( target_act );

	*x = p_mat->x >> FX32_SHIFT;
	*y = p_mat->y >> FX32_SHIFT;
	*x -= (ZKN_POKELIST_POKENAME_BMP_SIZE_X / 2);	// ������W�ɂ���
	*y -= (ZKN_POKELIST_POKENAME_BMP_SIZE_Y / 2);			
}

//----------------------------------------------------------------------------
/**
 *	@brief	���O�ύX�f�[�^�ύX�`�F�b�N�����s����
 *
 *	@param	p_work			���[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb			�O���[�o��
 *	@param	heap			�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameMoveNameChange( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	int pokelisttbl_no;
	int pokelisttbl_num;
	int chg_name_no;	// �ύX���閼�O�e�[�u���i���o�[
	int poke_list_no;	// �ύX����|�P�������X�g�i���o�[
	int poke_listdraw_link_list_idx;

	pokelisttbl_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	pokelisttbl_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );

	// �ǂ̕����ɓ��삵�Ă��邩�`�F�b�N
	switch( cp_glb->move_way ){
	case ZKN_POKE_LIST_UP:
		// ��Ԃ����̃e�[�u���̃|�P��������I�����ꂽ�|�P���� + ZKN_POKELIST_POKETBL_CHECK�̃e�[�u���|�P�����ŕύX
		chg_name_no = p_work->poke_tbl_start + ZKN_POKELIST_POKETBL_NUM - 1;
		poke_list_no = pokelisttbl_no + ZKN_POKELIST_POKETBL_CHECK;
		break;
		
	case ZKN_POKE_LIST_DOWN:
		// ��Ԑ擪�̃e�[�u���̃|�P��������I�����ꂽ�|�P���� - ZKN_POKELIST_POKETBL_CHECK�̃e�[�u���|�P�����ŕύX
		chg_name_no = p_work->poke_tbl_start;
		poke_list_no = pokelisttbl_no - ZKN_POKELIST_POKETBL_CHECK;

		break;

	default:
		break;
	}
	
	// ��ł����ł������Ƃ��͑S���ύX(�X�L�b�v���R�[�����ꂽ)
	if( (cp_glb->move_way == ZKN_POKE_LIST_NO_MOVE) ){
		// �S�ύX
		PokeListPokeNameSetUp( p_work, p_drawglb, cp_glb, heap );
	}else{
		// �P�����ύX
		chg_name_no %= ZKN_POKELIST_POKETBL_NUM;

		// �͈͓��Ȃ�ύX
		if( (poke_list_no < pokelisttbl_num) &&
			(poke_list_no >= 0) ){
			
			// �|�P�������X�g�`��z��idx����|�P�������X�g�f�[�^�z��idx���擾
			poke_listdraw_link_list_idx = ZKN_GLBDATA_PokeListDrawTblDataGet( cp_glb->p_glb, poke_list_no );
			
			// �_�~�[�f�[�^�łȂ����`�F�b�N
			if( poke_listdraw_link_list_idx != POKEMON_LIST_DRAWTBL_DUMMY ){
			
				PokeListPokeNameChange( p_work, p_drawglb, cp_glb, heap, chg_name_no, poke_listdraw_link_list_idx );
			}else{

				// ���݁[���O�ݒ�
				PokeListPokeNameDummySet( p_work, p_drawglb, heap, chg_name_no, poke_list_no + 1 );
			}
		}else{
			// �͈͊O�Ȃ�j��
			if( p_work->poke_name[ chg_name_no ] ){
				ZKN_FONTOAM_Delete( p_work->poke_name[ chg_name_no ] );
				p_work->poke_name[ chg_name_no ] = NULL;
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������L�����N�^�f�[�^�ύX
 *
 *	@param	p_work				�`�惏�[�N
 *	@param	p_drawglb			�`��O���[�o���f�[�^
 *	@param	cp_glb				�O���[�o���f�[�^
 *	@param	heap				�q�[�v
 *	@param	pokename_tbl_no		�|�P�������O�e�[�u���̉��Ԗڂ�ύX����̂�
 *	@param	pokelist_tbl_no		�ύX����|�P�����̃f�[�^�e�[�u���i���o�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameChange( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap, int pokename_tbl_no, int pokelist_tbl_no )
{
	ZKN_FONTOAM_INIT fontoam_init;
	GF_BGL_BMPWIN* p_bmp;	// �������ݗ̈�
	const ZKN_POKELIST_DATA* cp_pokedata;

	//�@�|�P�����f�[�^
	cp_pokedata = ZKN_GLBDATA_PokeListTblGet( cp_glb->p_glb, pokelist_tbl_no );
	GF_ASSERT_MSG( cp_pokedata, " %d\n", pokelist_tbl_no );

	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = p_work->clheader.pPaletteProxy;
	fontoam_init.parent		 = NULL;
	fontoam_init.x			 = 0;
	fontoam_init.y			 = 0;
	fontoam_init.bg_pri		 = ZKN_POKELIST_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;

	// �����񏑂����ݗ̈�쐬
	p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake( p_drawglb, cp_glb->p_glb, heap, cp_pokedata->mons_no );
	

	// �j��
	if( p_work->poke_name[ pokename_tbl_no ] ){
		ZKN_FONTOAM_Delete( p_work->poke_name[ pokename_tbl_no ] );
	}
	
	// FONTOAM�o�^
	fontoam_init.p_bmp = p_bmp;
	p_work->poke_name[ pokename_tbl_no ] = ZKN_FONTOAM_MakeCharOfs( &fontoam_init, p_work->poke_name_char_size );

	// BMP�̈�j��
	ZKN_FONTOAM_DeleteBmp( p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�_�~�[�f�[�^�ݒ�
 *
 *	@param	p_work			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	heap			�q�[�v
 *	@param	pokename_tbl_no	�l�[���e�[�u���i���o�[
 *	@param	pokenum
 *
 *	@return	none
 */	
//-----------------------------------------------------------------------------
static void PokeListPokeNameDummySet( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap, int pokename_tbl_no, int pokenum )
{
	ZKN_FONTOAM_INIT fontoam_init;
	GF_BGL_BMPWIN* p_bmp;	// �������ݗ̈�
	STRBUF* str = STRBUF_Create(ZKN_POKELIST_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);


	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = p_work->clheader.pPaletteProxy;
	fontoam_init.parent		 = NULL;
	fontoam_init.x			 = 0;
	fontoam_init.y			 = 0;
	fontoam_init.bg_pri		 = ZKN_POKELIST_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;

	// �����񏑂����ݗ̈�쐬
	p_bmp = ZKN_FONTOAM_GetBmp( p_drawglb->fontoam_sys, ZKN_POKELIST_POKENAME_BMP_SIZE_CX, ZKN_POKELIST_POKENAME_BMP_SIZE_CY );

	// �����쐬
	STRBUF_SetNumber( str, pokenum, ZKN_POKELIST_POKENAME_NO_KETA,
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( p_bmp, FONT_BUTTON, str, ZKN_POKELIST_POKENAME_NO_MAT_X, ZKN_POKELIST_POKENAME_MAT_Y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );

	// �Ȃ��|�P�������� 
	MSGMAN_GetString( man, ZNK_UNKNOWN_00, str );
	GF_STR_PrintColor( p_bmp, FONT_BUTTON, str, ZKN_POKELIST_POKENAME_NAME_MAT_X, ZKN_POKELIST_POKENAME_MAT_Y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );
	
	// �j��
	if( p_work->poke_name[ pokename_tbl_no ] ){
		ZKN_FONTOAM_Delete( p_work->poke_name[ pokename_tbl_no ] );
	}
	
	// FONTOAM�o�^
	fontoam_init.p_bmp = p_bmp;
	p_work->poke_name[ pokename_tbl_no ] = ZKN_FONTOAM_MakeCharOfs( &fontoam_init, p_work->poke_name_char_size );

	// BMP�̈�j��
	ZKN_FONTOAM_DeleteBmp( p_bmp );


	STRBUF_Delete(str);

	MSGMAN_Delete(man);

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�e�[�u���̕`��I���I�t�ݒ�	��C�ɑS�e�[�u����ݒ肵�܂��B
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	cp_glb		�O���[�o���f�[�^	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeTblDrawFlagSetUp( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	int poke_list_no;
	int poke_tbl_no;
	int i;		// ���[�v�p
	int pokelisttbl_no;
	int pokelisttbl_num;

	pokelisttbl_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	pokelisttbl_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );

	poke_list_no = pokelisttbl_no - ZKN_POKELIST_POKETBL_CHECK;
	poke_tbl_no = p_work->poke_tbl_start;
	
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){

		if( (poke_list_no >= 0) &&
			(poke_list_no < pokelisttbl_num) ){
			CLACT_SetDrawFlag( p_work->poke_tbl[ poke_tbl_no ], TRUE );
		}else{
			CLACT_SetDrawFlag( p_work->poke_tbl[ poke_tbl_no ], FALSE );
		}

		poke_tbl_no = (poke_tbl_no + 1) % ZKN_POKELIST_POKETBL_NUM;
		poke_list_no++;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N����
 *
 *	@param	p_work			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb			�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeGraMove( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	fx32 calc;
	int alpha;
	SOFT_SPRITE* ssp;
	
	// �J�E���g�l���烿��ύX
	// 0�`31�ɏ��X�ɕς���Ă���
	calc = FX_Mul( 31 << FX32_SHIFT, (ZKN_POKELIST_MOVE_END_COUNT - cp_glb->move_count) << FX32_SHIFT );
	calc = FX_Div( calc, ZKN_POKELIST_MOVE_END_COUNT << FX32_SHIFT );
	alpha = calc >> FX32_SHIFT;

	// softsprite
	ssp = ZKN_GlbPokemonGraphicGet( p_drawglb );
	SoftSpriteParaSet( ssp, SS_PARA_ALPHA, alpha );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�̃��l���Z�b�g
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeGraAlphaInit( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	SOFT_SPRITE* ssp;
	
	// softsprite
	ssp = ZKN_GlbPokemonGraphicGet( p_drawglb );
	SoftSpriteParaSet( ssp, SS_PARA_ALPHA, 31 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�_�~�[�|�P�����O���t�B�b�N�̓���
 *
 *	@param	cp_glb			�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListDummyPokeGraMove( const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	fx32 calc;
	int alpha;
	
	// �J�E���g�l���烿��ύX
	// 0�`16�ɏ��X�ɕς���Ă���
	calc = FX_Mul( 16 << FX32_SHIFT, (ZKN_POKELIST_MOVE_END_COUNT - cp_glb->move_count) << FX32_SHIFT );
	calc = FX_Div( calc, ZKN_POKELIST_MOVE_END_COUNT << FX32_SHIFT );
	alpha = calc >> FX32_SHIFT;

	// OAM��
	G2_ChangeBlendAlpha( alpha, 16 - alpha );
}


//----------------------------------------------------------------------------
/**
 *	@brief	BG�ʃt�F�[�h������
 *
 *	@param	p_work			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o���f�[�^
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	fadein_out		�t�F�[�h�C��TRUE�@�A�E�gFALSE�t���O
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListBgFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	int top_s, top_e;
	int bottom_s, bottom_e;
	int fade_sync;

	
	// �V���b�^�[��
	Snd_SePlay( ZKN_SND_SHUTTER );

	// font�ʃ}�X�N
/*	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );
	G2_SetWnd0Position( 0, 0, 255, 192 );//*/

	
	// �t�F�[�h�f�[�^�������f�[�^�ݒ�
	if( cp_glb->fade_mode == ZKN_POKELIST_BG_FADE_NORMAL ){
		
		if( fadein_out ){
			top_s = ZKN_POKELIST_BGSHUTTER_FADE00_TOP_S;
			bottom_s = ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_S;
			top_e = ZKN_POKELIST_BGSHUTTER_FADE00_TOP_E;
			bottom_e = ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_E;
			fade_sync = ZKN_POKELIST_FADEIN_SYNC;

			// �����ʂ̕\���I�t�Z�b�g�ݒ�
			GF_BGL_ScrollSet( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M, GF_BGL_SCROLL_Y_SET, 192 );

		}else{
			top_s = ZKN_POKELIST_BGSHUTTER_FADE00_TOP_E;
			bottom_s = ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_E;
			top_e = ZKN_POKELIST_BGSHUTTER_FADE00_TOP_S;
			bottom_e = ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_S;
			fade_sync = ZKN_POKELIST_FADEOUT_SYNC;
		}
		
	}else{
		
		if( fadein_out ){
			top_s = ZKN_POKELIST_BGSHUTTER_FADE01_TOP_S;
			bottom_s = ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_S;
			top_e = ZKN_POKELIST_BGSHUTTER_FADE01_TOP_E;
			bottom_e = ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_E;
			fade_sync = ZKN_POKELIST_FADEIN_SYNC;
		}else{
			top_s = ZKN_POKELIST_BGSHUTTER_FADE01_TOP_E;
			bottom_s = ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_E;
			top_e = ZKN_POKELIST_BGSHUTTER_FADE01_TOP_S;
			bottom_e = ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_S;
			fade_sync = ZKN_POKELIST_FADEOUT_SYNC;
		}
	}


	// �t�F�[�h�f�[�^������
	ZKN_UTIL_BgShutterFadeInit( &p_work->bg_fade,
			p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M,
			p_work->p_util_scrn, 
			top_s, top_e, bottom_s, bottom_e,
			fade_sync );

}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�t�F�[�h�֐�
 *
 *	@param	p_work 
 *	@param	p_drawglb
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL PokeListBgFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb )
{
	BOOL check;
	int bottom_w_size;
	
	check = ZKN_UTIL_BgShutterFade( &p_work->bg_fade );

	// ������ʃX�N���[��
	if( check == FALSE ){
		bottom_w_size = (p_work->bg_fade.bottom_dis * (p_work->bg_fade.move_count - 1)) / p_work->bg_fade.move_count_max;
		bottom_w_size += p_work->bg_fade.bottom_start;
		bottom_w_size = bottom_w_size;			// ������̃L�����N�^�T�C�Y
		bottom_w_size *= 8;						// ������̃s�N�Z���T�C�Y
		bottom_w_size = bottom_w_size - ZKN_POKELIST_SCR_START_DOWN_YSIZ; // �����̕\���ʒu

		// ZKN_POKELIST_BGSHUTTER_FADE_FONTBG_LIMIT���傫���l�ɂ����Ȃ�
		if( bottom_w_size < ZKN_POKELIST_BGSHUTTER_FADE_FONTBG_LIMIT ){
			bottom_w_size = ZKN_POKELIST_BGSHUTTER_FADE_FONTBG_LIMIT;
		}
		
		// ���ꂪBG�̈ړ��l�ɂȂ�
		GF_BGL_ScrollReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M, GF_BGL_SCROLL_Y_SET, bottom_w_size );

	}

	return check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	SHUTTER�t�F�[�h�㏈��
 *
 *	@param	p_drawglb		�`��O���[�o���f�[�^
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	fadein_out		�t�F�[�h�C��TRUE�@�A�E�gFALSE
 *	@param	set_blend_msk	�ݒ�u���C�g�l�X�}�X�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListBgFadeDel( ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	if( cp_glb->fade_mode == ZKN_POKELIST_BG_FADE_NORMAL ){
		
		if( fadein_out == FALSE ){
			
			// �S���̖ʂɃu���C�g�l�X�������A�X�N���[�����W�����Z�b�g
			GF_BGL_ScrollSet( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M, GF_BGL_SCROLL_Y_SET, 0 );
		}
	}

	GX_SetVisibleWnd( GX_WNDMASK_NONE );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g�̃|�P�������������]���T�C�Y�����߂�
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	�]���T�C�Y
 */
//-----------------------------------------------------------------------------
static int PokeListPokeNameCharTransSizeGet( ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	GF_BGL_BMPWIN* p_bmp;	// �������ݗ̈�
	int char_size;

	p_bmp = ZKN_FONTOAM_GetBmp( p_drawglb->fontoam_sys, ZKN_POKELIST_POKENAME_BMP_SIZE_CX, ZKN_POKELIST_POKENAME_BMP_SIZE_CY );
	char_size = FONTOAM_NeedCharSize( p_bmp, NNS_G2D_VRAM_TYPE_2DMAIN, heap ); 
	ZKN_FONTOAM_DeleteBmp( p_bmp );

	return char_size;
}


//----------------------------------------------------------------------------
/**
 *	@brief	OAM�̃t�F�[�h������
 *
 *	@param	p_work	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListOamFadeInit( ZKN_POKELIST_GRAWORK* p_work )
{
	int i;


	CLACT_ObjModeSet( p_work->cursor, GX_OAM_MODE_XLU );
	
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		CLACT_ObjModeSet( p_work->poke_tbl[ i ], GX_OAM_MODE_XLU );
		CLACT_ObjModeSet( p_work->icon[ i ], GX_OAM_MODE_XLU );
		if(p_work->poke_name[ i ]){
			FONTOAM_ObjModeSet( p_work->poke_name[ i ]->p_fontoam, GX_OAM_MODE_XLU );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�̃t�F�[�h�����j��
 *
 *	@param	p_work	�`�惏�[�N
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListOamFadeDelete( ZKN_POKELIST_GRAWORK* p_work )
{
	int i;


	CLACT_ObjModeSet( p_work->cursor, GX_OAM_MODE_NORMAL );
	
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		CLACT_ObjModeSet( p_work->poke_tbl[ i ], GX_OAM_MODE_NORMAL );
		CLACT_ObjModeSet( p_work->icon[ i ], GX_OAM_MODE_NORMAL );
		if(p_work->poke_name[ i ]){
			FONTOAM_ObjModeSet( p_work->poke_name[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���N�g�|�P�����̃��X�g�f�[�^���O���[�o���̃f�[�^�ɔ��f
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListSelectPokeDataGlbSet( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	const VecFx32* p_mat;
	int select_work_no;
	
	// �I������Ă���e�[�u��idx�擾
	select_work_no = (p_work->poke_tbl_start + ZKN_POKELIST_POKETBL_CHECK) % ZKN_POKELIST_POKETBL_NUM;

	// �|�P�������X�g�e�[�u���̍��W��ݒ�
	p_mat = CLACT_GetMatrix( p_work->poke_tbl[ select_work_no ] );

	// �|�P���������X�g�f�[�^�쐬
	ZKN_UTIL_PokeListPokeNameMakeGlb( p_drawglb, cp_glb->p_glb, heap, ZKN_GLBDATA_PokeListTblNoGet( cp_glb->p_glb ), p_mat->x, p_mat->y );
	ZKN_GlbPokeNameTblBGPriSet( p_drawglb, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�m�[�}���t�F�[�h����	�����ʂƃ��[�e�B���e�B�ʂ�SLIDE�C���@���̑��u���C�g�l�X
 *
 *	@param	p_work			�`�惏�[�N
 *	@param	cp_dataglb		�`��O���[�o��
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknPokeListDefaultFadeReq( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	// BG��
	PokeListBgFadeInit( p_work, p_drawglb, cp_glb, fadein_out );

	// BG�t�F�[�h���[�h��ZKN_POKELIST_BG_FADE_SHUTTER�̎��̓u���C�g�l�X���g�p���Ȃ�
	if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){
	
		if( fadein_out ){
			// �t�F�[�h�C��
			ChangeBrightnessRequest( ZKN_POKELIST_FADEIN_SYNC, 
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, ZKN_POKELSIT_BRIGHTNESS_MSK, MASK_MAIN_DISPLAY );
		}else{
			// �t�F�[�h�A�E�g
			ChangeBrightnessRequest( ZKN_POKELIST_FADEIN_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, ZKN_POKELSIT_BRIGHTNESS_MSK, MASK_MAIN_DISPLAY );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�I���`�F�b�N
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���A�E�g
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknPokeListDefaultFadeEndCheck( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	BOOL check[2];

	// BG�ʂ�SHUTTER�t�F�[�h
	check[0] = PokeListBgFadeMain( p_work, p_drawglb );
	
	// BG�t�F�[�h���[�h��ZKN_POKELIST_BG_FADE_SHUTTER�̎��̓u���C�g�l�X���g�p���Ȃ�
	if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){
		check[1] = IsFinishedBrightnessChg( MASK_MAIN_DISPLAY );
	}else{
		check[1] = TRUE;
	}

	// �u���C�g�l�X�t�F�[�h
	if( (check[0] == TRUE) &&
		(check[1] == TRUE) ){

		// BG�t�F�[�h���[�h��ZKN_POKELIST_BG_FADE_SHUTTER�̎��̓u���C�g�l�X���g�p���Ȃ�
		if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){
			// �^���Âɂ���
			if( fadein_out == FALSE ){
				SetBrightness( BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_MAIN_DISPLAY );
				// BG�ʂ̏�����
				GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
				// ������ʏ�����
				GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
			}
		}

		PokeListBgFadeDel( p_drawglb, cp_glb, fadein_out );

		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӊ�ʂƂ̃t�F�[�h����
 *
 *	@param	p_work			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	fadein_out		�t�F�[�h�C�� TRUE �A�E�g FALSE 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListChZukanFadeReq( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	// �t�F�[�h����I�u�W�F���[�h�𔼓�����
	PokeListOamFadeInit( p_work );

	// BG��
	PokeListBgFadeInit( p_work, p_drawglb, cp_glb, fadein_out );

	// �t�F�[�h�A�E�g�݂̂̏���
	if( fadein_out == FALSE ){
		// �|�P�O���t�F�[�h
		PokeListPokeGraFadeInit( p_work, p_drawglb );

		// �|�P���X�g�t�F�[�h
		PokeListPokeListFadeInit( p_work, p_drawglb );
	}

	// BG�t�F�[�h���[�h��ZKN_POKELIST_BG_FADE_SHUTTER�̎��̓u���C�g�l�X���g�p���Ȃ�
	if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){


		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_POKELIST_FADEIN_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_POKELSIT_BRIGHTNESS_ZUKAN_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_POKELIST_FADEIN_SYNC, 
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_POKELSIT_BRIGHTNESS_ZUKAN_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӊ�ʂƂ̃t�F�[�h�����I���`�F�b�N
 *
 *	@param	p_work			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	fadein_out		�t�F�[�h�C�� TRUE�@�A�E�g FALSE
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknPokeListChZukanFadeEndCheck( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	BOOL check[4];
	int i;

	// BG�ʂ�SHUTTER�t�F�[�h
	check[0] = PokeListBgFadeMain( p_work, p_drawglb );


	// BG�t�F�[�h���[�h��ZKN_POKELIST_BG_FADE_SHUTTER�̎��̓u���C�g�l�X���g�p���Ȃ�
	if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){
		// �u���C�g�l�X�t�F�[�h
		check[1] = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}

	// �t�F�[�h�A�E�g�݂̂̏���
	if( fadein_out == FALSE ){

		// �|�P�O��
		check[2] = PokeListPokeGraFadeMain( p_work, p_drawglb );

		// �|�P���X�g
		check[3] = PokeListPokeListFadeMain( p_work, p_drawglb );
	}else{
		check[2] = TRUE;
		check[3] = TRUE;
	}

	
	for( i=0; i<4; i++ ){
		if( check[i] == FALSE ){
			break;
		}
	}
	
	if( i == 4 ){
		// �t�F�[�h�A�E�g�̂Ƃ�
		if( fadein_out == FALSE ){
			// BG�t�F�[�h���[�h��ZKN_POKELIST_BG_FADE_SHUTTER�̎��̓u���C�g�l�X���g�p���Ȃ�
			if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){
				// �^���Âɂ���
				G2_SetBlendBrightnessExt( ZKN_POKELIST_BRIGHTNESS_ZUKAN_END_MSK, PLANEMASK_BG3, 0, 0, BRIGHTNESS_BLACK );

				// BG�ʂ̏�����
				GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
				// ������ʏ�����
				GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
			}
			
		}else{
			// �t�F�[�h�C���̂Ƃ�
			// OAM�̔��������[�h�j��
			PokeListOamFadeDelete( p_work );

			// �O���[�o���|�P���X�g�\��OFF
			ZKN_GlbPokeNameTblDrawFlagSet( p_drawglb->p_drawglb, FALSE );
			ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
		}
		
		// BG�t�F�[�h���Z�b�g
		PokeListBgFadeDel( p_drawglb, cp_glb, fadein_out );
		
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 * [�}�Ӄt�F�[�h�G�t�F�N�g]
 *	@brief	�|�P�����O���t�B�b�N���쏉����
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeGraFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb )
{
	ZKN_UTIL_MoveReq( &p_work->pokegra_move, ZKN_POKELIST_POKEGRA_X, ZKN_ZUKAN_POKEGRA_MAT_X, ZKN_POKELIST_POKEGRA_Y, ZKN_ZUKAN_POKEGRA_MAT_Y, ZKN_POKELIST_FADEIN_SYNC );

	// ���W�ݒ�
	ZKN_GlbPokemonGraphicSetMatrix( p_drawglb->p_drawglb, p_work->pokegra_move.x, p_work->pokegra_move.y );
}

//----------------------------------------------------------------------------
/**
 * [�}�Ӄt�F�[�h�G�t�F�N�g]
 *	@brief	�|�P�����O���t�B�b�N����
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL PokeListPokeGraFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb )
{
	BOOL check;
	
	check = ZKN_UTIL_MoveMain( &p_work->pokegra_move );

	// ���W�ݒ�
	ZKN_GlbPokemonGraphicSetMatrix( p_drawglb->p_drawglb, p_work->pokegra_move.x, p_work->pokegra_move.y );

	return check;
}

//----------------------------------------------------------------------------
/**
 * [�}�Ӄt�F�[�h�G�t�F�N�g]
 *	@brief	�|�P�������X�g���쏉����
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeListFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb )
{
	ZKN_UTIL_MoveReq( &p_work->pokelist_move, ZKN_POKELIST_TBL_MAT_X, ZKN_ZUKAN_POKELIST_MAT_IX, ZKN_POKELIST_TBL_MAT_Y, ZKN_ZUKAN_POKELIST_MAT_IY, ZKN_POKELIST_FADEIN_SYNC );

	// ���W�ݒ�
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet( p_drawglb->p_drawglb, p_work->pokelist_move.x, p_work->pokelist_move.y );
}

//----------------------------------------------------------------------------
/**
 * [�}�Ӄt�F�[�h�G�t�F�N�g]
 *	@brief	�|�P�������X�g���쏉����
 *
 *	@param	p_work		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static BOOL PokeListPokeListFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb )
{
	BOOL check;
	
	check = ZKN_UTIL_MoveMain( &p_work->pokelist_move );

	// ���W�ݒ�
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet( p_drawglb->p_drawglb, p_work->pokelist_move.x, p_work->pokelist_move.y );

	return check;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӕj������
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListZukanDel( ZKN_POKELIST_GLB_DATA* p_glb )
{
	*p_glb->p_event_key	|= EVENT_MSK_POKELIST_ZUKAN_END;
	// �t�F�[�h�C�����[�h�ύX
	p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;
	p_glb->fade_zukan_data = FALSE;

	p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄf�[�^��ʂɈڍs
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListZukanChg( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb )
{
	*p_glb->p_event_key	|= EVENT_MSK_POKELIST_CHENGE_ZUKAN;
	// �t�F�[�h�C�����[�h�ύX
	p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;
	p_glb->fade_zukan_data = TRUE;

	// �O���[�o���ϐ�������
	p_glb->move_count = 0;
//	PokeListMoveInit( p_glb, p_work );	
	p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�������X�g����SORT��ʂɕ���
 *
 *	@param	p_glb 
 *
 *	@retval	TRUE	���������ꂽ
 *	@retval	FALSE	�������Ȃ���Ȃ�����
 */
//-----------------------------------------------------------------------------
static BOOL PokeListSortChg( ZKN_POKELIST_GLB_DATA* p_glb )
{
	if( p_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_NONE ){
		
		// �\�[�g�ʒu�ɃJ�[�\���ړ����Č����\�[�g��ʊJ�n
		*p_glb->p_event_key |= EVENT_MSK_POKELIST_CHENGE_SORTSEARCH;//*/

		// �t�F�[�h���[�h
		p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;
		p_glb->fade_zukan_data = FALSE;

		p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;

		// �I����
		Snd_SePlay( ZKN_SND_SELECT );
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄ��[�h��؂�ւ���
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@retval	TRUE	���������ꂽ
 *	@retval	FALSE	����������Ȃ�����
 */
//-----------------------------------------------------------------------------
static BOOL PokeListZukanModeChg( ZKN_POKELIST_GLB_DATA* p_glb, int heap )
{
	int zkn_mode;

	// ���Ӱ�ނ̎��͂������Ȃ�
	if( p_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT ){
		return FALSE;
	}
		

	// �}�Ӄ��[�h��ύX����
	zkn_mode = ZKN_GLBDATA_PokeZknModeGet(p_glb->p_glb);
	if( zkn_mode == ZKN_MODE_SHINOH ){
		zkn_mode = ZKN_MODE_ZENKOKU;
	}else{
		zkn_mode = ZKN_MODE_SHINOH;
	}
	
	// �}�Ӄ��[�h��ύX�ł��邩�`�F�b�N
	if( ZKN_GLBDATA_PokeZknModeChengeCheck( p_glb->p_glb, zkn_mode ) ){
		// �ύX
		ZKN_GLBDATA_PokeZknModeChenge( p_glb->p_glb, zkn_mode );

		// �I����
		Snd_SePlay( ZKN_SND_SELECT );

		// ���X�g�ݒ�
		ZKN_GLBDATA_PokeListTblMake( p_glb->p_glb, 
				ZKN_POKELIST_SORT_NORMAL, 
				ZKN_POKELIST_SEARCH_NAME_NONE,
				ZKN_POKELIST_SEARCH_TYPE_NONE,
				ZKN_POKELIST_SEARCH_TYPE_NONE,
				ZKN_POKELIST_SEARCH_FORM_NONE,
				zkn_mode, heap );

		// ���X�g�i���o�[������
		ZKN_GLBDATA_PokeListTblNoSet( p_glb->p_glb, 0 );

		// ����J�E���^��������
		p_glb->move_count = 0;	

		// �|�P���X�g��ʍč쐬
		*p_glb->p_event_key |= EVENT_MSK_POKELIST_CHANGE;
		// �t�F�[�h�C�����[�h�ύX
		p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;
		p_glb->fade_zukan_data = FALSE;

		p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;

		// �`��s�iOFF
		p_glb->move_draw = FALSE;

		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӂ�SORT�ݒ胊�Z�b�g
 *
 *	@param	p_glb	�O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListZukanReset( ZKN_POKELIST_GLB_DATA* p_glb, int heap )
{
	// �����X�^�[�i���o�[�ۑ�
	u32 monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );
	
	// �}�Ӄ��X�g���Z�b�g
	ZKN_GLBDATA_PokeListTblMake( p_glb->p_glb, 
			ZKN_POKELIST_SORT_NORMAL, 
			ZKN_POKELIST_SEARCH_NAME_NONE,
			ZKN_POKELIST_SEARCH_TYPE_NONE,
			ZKN_POKELIST_SEARCH_TYPE_NONE,
			ZKN_POKELIST_SEARCH_FORM_NONE,
			ZKN_GLBDATA_PokeZknModeGet( p_glb->p_glb ), heap );
	(*p_glb->p_event_key) |= EVENT_MSK_POKELIST_CHANGE;

	// ���X�g�i���o�[������
	ZKN_GLBDATA_PokeListTblNoSet_Monsno( p_glb->p_glb, monsno );

	// ����J�E���^��������
	p_glb->move_count = 0;	

	// ��ă��[�h���ύX
	p_glb->p_glb->sort_search_flag = ZKN_SORTSEARCH_NONE;

	// �t�F�[�h�C�����[�h�ύX
	p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;
	p_glb->fade_zukan_data = FALSE;
	// �������Ȃ�
	p_glb->move_way = ZKN_POKE_LIST_NO_MOVE;

	p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;

	// �`��s�iOFF
	p_glb->move_draw = FALSE;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�X�L�b�v����
 *
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListSkipMove( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb )
{
	p_work->skip_count--;
	
	if( p_work->skip_count >= 0 ){
		if( PokeListMoveAdd( p_glb, p_work->skip_add ) ){

			PokeListMoveReq( p_glb, p_work, p_work->skip_way );
			p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NORMAL;	// �T�u��ʃz�C�[�������~
			// �I���ړ���
			Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
		}else{
			p_work->skip_count = 0;		// �ŏI�V���ڂ܂ł�����
		}
	}else{

		// �X�L�b�v�I��
		PokeListMoveInit( p_glb, p_work );	
		p_work->skip_flag = FALSE;		// �X�L�b�v�I��
		p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NONE;	// �T�u�ʃz�C�[�����b�N����
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�L�[����
 *
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListKeyMove( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb )
{

	// �J�[�\���A�b�v
	if( sys.cont & PAD_KEY_UP ){
		// �l���X�V���ꂽ�瓮����
		if( PokeListMoveAdd( p_glb, -1 ) ){
			PokeListMoveReq( p_glb, p_work, ZKN_POKE_LIST_DOWN );
			p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NORMAL;	// �T�u��ʃz�C�[�������~
			
			// �I���ړ���
			Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
		}else{
			PokeListMoveInit( p_glb, p_work );	
			p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NONE;	// �T�u��ʃz�C�[�������~����
		}
		return ;
	}

	// �J�[�\��
	if( sys.cont & PAD_KEY_DOWN ){
		// �l���X�V���ꂽ�瓮����
		if( PokeListMoveAdd( p_glb, 1 ) ){
			PokeListMoveReq( p_glb, p_work, ZKN_POKE_LIST_UP );
			p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NORMAL;	// �T�u��ʃz�C�[�������~

			// �I���ړ���
			Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
		}else{
			PokeListMoveInit( p_glb, p_work );	
			p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NONE;	// �T�u��ʃz�C�[�������~����
		}
		return ;
	}

	//�X�L�b�v����
	if( sys.trg & PAD_KEY_LEFT ){
		p_work->skip_flag = TRUE;
		p_work->skip_count = ZKN_POKE_LIST_MOVE_SKIP_NUM;
		p_work->skip_add = -1;
		p_work->skip_way = ZKN_POKE_LIST_DOWN;
		// ���x����
		PokeListSkipMoveInit( p_glb, p_work );
		return ;
	}
	if( sys.trg & PAD_KEY_RIGHT ){
		p_work->skip_flag = TRUE;
		p_work->skip_count = ZKN_POKE_LIST_MOVE_SKIP_NUM;
		p_work->skip_add = 1;
		p_work->skip_way = ZKN_POKE_LIST_UP;
		// ���x����
		PokeListSkipMoveInit( p_glb, p_work );
		return ;
	}

	// �S�ĂɈ���������Ȃ��Ƃ��͉������Ȃ�
	// ���d�ɏ���������ƃT�u��ʂŃf�[�^�X�V����
	// ���������Ă��܂�
	if( p_glb->sub_wheel_lock == ZKN_POKELIST_WHEEL_LOCK_NORMAL ){
		PokeListMoveInit( p_glb, p_work );	
		p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NONE;	// �T�u��ʃz�C�[�������~����
	}
}

