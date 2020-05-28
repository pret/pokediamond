//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_graver.c
 *	@brief		�}�ӃO���t�B�b�N�o�[�W����
 *	@author		tomoya takahashi
 *	@data		2006.02.21
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
#include "include/poketool/pokefoot.h"

#include "include/battle/battle_common.h"

#include "include/application/zukanlist/zukan.naix"
#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"

#define	__ZKN_ZUKANGRAVER_GRAVER_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan_graver.h"

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
#define ZKN_ZUKANGRAVER_EVENT_NUM ( 0 )	// �C�x���g��
#define ZKN_ZUKANGRAVER_OAM_BG_PRI	( 3 )
#define ZKN_ZUKANGRAVER_OAM_SOFT_PRI	( 32 )

// BG�u���C�g�l�X�t�F�[�h��
#define ZKN_ZUKANGRAVER_BRIGHTNESS_MSK	( GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )



enum{
	// �`��^�C�v�t���O
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_NORMAL = 0,	// �ʏ�`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MANONLY,		// �I�X�̂ݕ`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_GIRLONLY,		// ���X�̂ݕ`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWNONLY,	// �s���̂ݕ`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIUSI,		// �V�[�E�V�`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIDORUGO,	// �V�[�h���S�`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMUTTI,	// �~�m���b�`�`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMESU,		// �~�m���X�`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWN_POKE,	// �A���m�[���`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_DEOKISISU_POKE,// �f�I�L�V�X�`��^�C�v

	// �ʏ�`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_MAN = 0,	// �j
	ZKN_ZUKANGRAVER_DRAW_TYPE_GIRL,		// ��
	ZKN_ZUKANGRAVER_DRAW_TYPE_NORM_NUM,

	// �I�X���X�̂ݕ`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_ONLY = 0,
	ZKN_ZUKANGRAVER_DRAW_TYPE_ONLY_NUM,

	// �~�m���b�` �~�m���X�`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_MINOMUTTI_NUM = ZUKAN_WORK_MINOMUSHI_FORM_NUM,
	ZKN_ZUKANGRAVER_DRAW_TYPE_MINOMESU_NUM = ZUKAN_WORK_MINOMUSHI_FORM_NUM,

	// �E�~�E�V�`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_SIIUSI_NUM = ZUKAN_WORK_UMIUSHI_FORM_NUM,
	ZKN_ZUKANGRAVER_DRAW_TYPE_SIIDORUGO_NUM = ZUKAN_WORK_UMIUSHI_FORM_NUM,

	// �A���m�[���`��^�C�v
	ZKN_ZUKANGRAVER_DRAW_TYPE_UNKNOWN_POKE_NUM = 28,
};


//-------------------------------------
//	�|�P�����O���t�B�b�N��
//=====================================
enum{
	ZKN_ZUKANGRAVER_GRA_FRONT,			// ���̕\�̊G
	ZKN_ZUKANGRAVER_GRA_BACK,			// ���̌��̊G
	ZKN_ZUKANGRAVER_GRA_FRONT_NEXT,		// ���̕\�̊G
	ZKN_ZUKANGRAVER_GRA_BACK_NEXT,		// ���̌��̊G
	ZKN_ZUKANGRAVER_GRA_NUM,
};
#define ZKN_ZUKANGRAVER_GRA_DRAW_Y			( 88 )
#define ZKN_ZUKANGRAVER_GRA_OAM_DRAW_Y_OFS	( 8 )
#define ZKN_ZUKANGRAVER_GRA_DRAW_FRONT_X	( 72 )
#define ZKN_ZUKANGRAVER_GRA_DRAW_BACK_X_OFS	( 112 )
#define ZKN_ZUKANGRAVER_GRA_DRAW_FRONT_NEXT_X	( ZKN_ZUKANGRAVER_GRA_DRAW_FRONT_X + 256 )

// FONTOAM
#define ZKN_GRAPHIC_BUTTONFONT_NUM			( 2 )
#define ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CX ( 10 )
#define ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CY ( 2 )
#define ZKN_GRAPHIC_BUTTON_PAL_OFS			( 4 )
#define ZKN_GRAPHIC_BUTTON_PAL_OFS_ON		( 1 )
#define ZKN_GRAPHIC_BUTTON_FONT_OFS_X		( -40 )
#define ZKN_GRAPHIC_BUTTON_FONT_OFS_Y		( 40 )

// �|�P�������싗��
#define ZKN_GRAPHIC_MOVE_X	( -256 )
#define ZKN_GRAPHIC_MOVE_Y	( 0 )
#define ZKN_GRAPHIC_MOVE_SYNC	( 16 )

// �A�C�R���`��܂ł̃^�C��
#define ZKN_GRAPHIC_MOVE_ICON_OFF_SYNC	( ZKN_GRAPHIC_MOVE_SYNC + 8 )

//-------------------------------------
//	�`�揉�����V�[�P���X
//=====================================
enum
{
	ZKN_ZUKANGRAVER_SEQINIT_ALLOC,
	ZKN_ZUKANGRAVER_SEQINIT_LOAD,
	ZKN_ZUKANGRAVER_SEQINIT_FADEIN,
	ZKN_ZUKANGRAVER_SEQINIT_END,
};

//-------------------------------------
//	�}�Ӕj���V�[�P���X
//=====================================
enum{
	ZKN_ZUKANGRAVER_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKANGRAVER_SEQDELETE_FADEOUT,
	ZKN_ZUKANGRAVER_SEQDELETE_RELEASE,
	ZKN_ZUKANGRAVER_SEQDELETE_FREE,
	ZKN_ZUKANGRAVER_SEQDELETE_END,
};


//-------------------------------------
//	OAM�A�j���V�[�P���X
//=====================================
enum{
	ZKN_ZUKANGRAVER_CELL_ANM_SEQ_BACK,
	ZKN_ZUKANGRAVER_CELL_ANM_SEQ_ICON,
	ZKN_ZUKANGRAVER_CELL_ANM_SEQ_BACK_2,
};

// �A�C�R�����W
#define ZKN_ZUKANGRAVER_ICON_X	( 248 )
#define ZKN_ZUKANGRAVER_ICON_Y	( 96 )


// �|�P�O���_�u���o�b�t�@���ݕ\��
enum{
	ZKN_ZUKANGRAVER_GRA_NOW_DRAW_01,
	ZKN_ZUKANGRAVER_GRA_NOW_DRAW_23,
	ZKN_ZUKANGRAVER_GRA_NOW_NUM
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�}�Ӊ�ʁ@�O���[�o���ϐ�
//=====================================
typedef struct {
	int*				p_event_key;		// �C�x���g�L�[
	ZKN_GLB_DATA*		p_glb;				// �O���[�o���f�[�^

	// �}�ӃR�����A�v���f�[�^
	const ZKN_APL_DATA* cp_zukan_common_apl;

	int					draw_type_flag;		// �`��^�C�v�t���O
	int					draw_type_max;		// �`��^�C�v��
	int					draw_type;			// �`��^�C�v
} ZKN_ZUKANGRAVER_GLB;

//-------------------------------------
//	�}�Ӊ�ʁ@�`��O���[�o���ϐ�
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// �`��O���[�o���f�[�^
	BOOL pokegra_move_flag;	// ����t���O
	BOOL pokegra_move_end;	// �|�P�����O���t�B�b�N����I��
} ZKN_ZUKANGRAVER_DRAWGLB;

//-------------------------------------
//	�}�Ӊ�ʁ@�`�惏�[�N
//=====================================
typedef struct {
	// �|�P�O���`��p
	CLACT_WORK_PTR	pokegra_back[ ZKN_ZUKANGRAVER_GRA_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];
	ZKN_FONTOAM_DATA*	p_pokegra_font[ ZKN_GRAPHIC_BUTTONFONT_NUM ];
	ZKN_UTIL_MOVE_WORK pokegra_move[ ZKN_ZUKANGRAVER_GRA_NUM ];
	int pokegra_y[ ZKN_ZUKANGRAVER_GRA_NUM ];	// �|�P�����O���t�B�b�NY
	int now_draw_buff;		// ���ݕ\�����̃o�b�t�@IDX	0:(0��1) 1:(2��3)

	// ���̃|�P�O����..�̃A�C�R��
	CLACT_WORK_PTR next_icon;

	// �A�C�R���\���^�C�������ƃt���O
	int icon_draw_s_time;
	BOOL icon_draw_flag;

	// drawtype
	int		draw_type_flag;		// �`��^�C�v�t���O
	int		draw_type;			// �`��^�C�v
} ZKN_ZUKANGRAVER_DRAW;


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
static ZKN_ZUKANGRAVER_GLB* MakeZukanGraverGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKANGRAVER_DRAWGLB* MakeZukanGraverDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
//static ZKN_EVENT_DATA* MakeZukanGraverEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanGraverGlb( ZKN_ZUKANGRAVER_GLB* p_glb );
static void DeleteZukanGraverDrawGlb( ZKN_ZUKANGRAVER_DRAWGLB* p_glb );
//static void DeleteZukanGraverEvent( ZKN_EVENT_DATA* p_event );


static int ZukanGraverEventDataNumGet( void );

static int ZknGraverAddDrawTypeGet( int draw_type_flag, int now, int num, int max );

//-----------------------------------------------------------------------------
/**
 *		�v���Z�X�֌W
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanGraverProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanGraverProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanGraverProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanGraverProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanGraverProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// �t�F�[�h�C���A�E�g
static void ZknZukanGraverDefaultFadeReq( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanGraverDefaultFadeEndCheck( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb , BOOL fadein_out );

static void ZknZukanGraverSpritePokeGraPalFade( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );

static void ZknZukanGraverOamFadeInit( ZKN_ZUKANGRAVER_DRAW* p_draw );
static void ZknZukanGraverOamFadeDelete( ZKN_ZUKANGRAVER_DRAW* p_draw );


static void ZknZukanGraverPokeGraFadeInit_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );
static BOOL ZknZukanGraverPokeGraFadeMain_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );
static void ZknZukanGraverPokeGraFadeInit( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int move_x, int move_y, int idx );
static BOOL ZknZukanGraverPokeGraFadeMain( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int idx );


// �`��^�C�v�֌W
static int ZknZukanGraverPokeDrawTypeFlagGet( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb );
static int ZknZukanGraverPokeDrawTypeNumGet( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb );
static int ZknZukanGraverPokeDrawTypeFlagNormal( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb );



// BG�ݒ�
static void ZknZukanGraverLoadResource( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap );
static void ZknZukanGraverReleaseResource( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );
static void ZknZukanGraverSetUpBackGround( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int heap );


// ���ՈȊO�̃A�N�^�[
static void ZknZukanGraverClactResLoad( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int heap );
static void ZknZukanGraverClactResDelete( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );
static void ZknZukanGraverClactAdd( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap );
static void ZknZukanGraverClactDelete( ZKN_ZUKANGRAVER_DRAW* p_draw );
static int ZknZukanGraverClactTypeNoChg( int type );

// �|�P�����O���t�B�b�N
static void ZknZukanGraverPokeGraDrawInit( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb );
static void ZknZukanGraverPokeGraDrawOn( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb );
static void ZknZukanGraverPoke_GraSet( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type_flag, int draw_type, int idx );
static void ZknZukanGraverPokeGraDrawOnTypeNormal( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeMinomutti( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeMinomesu( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeSiiusi( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeSiidorugo( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeAnnoon( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );
static void ZknZukanGraverPokeGraDrawOnTypeDeokisisu( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx );

static void ZknZukanGraverPokeGraMatGet( int idx, int* x, int* y );
static void ZknZukanGraverPokeGraDrawOff( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb );
static inline int ZknZukanGraverGetBuffIdx_PokeGraIdx( int buff_idx, int idx );

// �|�P�����O���t�B�b�N�e�L�X�g
static void ZknZukanGraverFontInitGraphicType_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type );
static void ZknZukanGraverFontSetUpGraphicType_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type );
static void ZknZukanGraverFontSetUpGraphicType( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type, int parent_idx, int fontoam_idx );
static int ZknZukanGraverFontSetUpGraphicTypeNormal( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeManOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeGirlOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeUnknownOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeMinomutti( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeMinomesu( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeSiiusi( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeSiidorugo( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeAnnoon( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );
static int ZknZukanGraverFontSetUpGraphicTypeDeokisisu( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type );

static int ZknZukanGraverFontGet(ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type_flag, int draw_type);
static void ZknZukanGraverFontOamDelete( ZKN_ZUKANGRAVER_DRAW* p_draw );


// �A�C�R��
static void ZknZukanGraverIconDrawAnm_S( ZKN_ZUKANGRAVER_DRAW* p_draw );
static void ZknZukanGraverIconDrawAnm_Main( ZKN_ZUKANGRAVER_DRAW* p_draw );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�A�v���쐬
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
void ZKN_ZukanGraverAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKANGRAVER_GLB*	p_glb;
	ZKN_ZUKANGRAVER_DRAWGLB*	p_drawglb;
//	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanGraverGlb( heap, zkn_sys );
	p_drawglb = MakeZukanGraverDrawGlb( heap, zkn_sys );
//	p_event = MakeZukanGraverEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= NULL;
//	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanGraverEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanGraverProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanGraverProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanGraverProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanGraverProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanGraverProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanGraverProcDrawFuncDelete;
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
void ZKN_ZukanGraverAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanGraverGlb( p_data->p_glb_data ); 
	DeleteZukanGraverDrawGlb( p_data->p_glb_draw );
//	DeleteZukanGraverEvent( p_data->p_event_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��^�C�v�����Z
 *
 *	@param	p_data			�A�v���f�[�^
 *	@param	num				�����l
 *
 *	@retval	TRUE	�l�ύX����
 *	@retval	FALSE	�ύX�ł��Ȃ�����
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanGraverDrawTypeAdd( ZKN_APL_DATA* p_data, int num )
{
	ZKN_ZUKANGRAVER_GLB* p_glb = p_data->p_glb_data;
	ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb = p_data->p_glb_draw;
	int last_num;

	// ���X�g���쒆�͕ύX�ł��Ȃ�
	if( p_drawglb->pokegra_move_flag == TRUE ){
		return FALSE;
	}
	
	last_num = p_glb->draw_type;

	// �v�Z���ʕ`��^�C�v���擾
	p_glb->draw_type = ZknGraverAddDrawTypeGet( p_glb->draw_type_flag, p_glb->draw_type, num, p_glb->draw_type_max );

	// �ύX���ꂽ���`�F�b�N
	if( last_num != p_glb->draw_type ){
		return TRUE;
	}

	return FALSE;
}


//-----------------------------------------------------------------------------
/**
 *		�v���C�x�[�g�֐�
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�O���[�o���f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKANGRAVER_GLB* MakeZukanGraverGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKANGRAVER_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKANGRAVER_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKANGRAVER_GLB) );

	// main��ʂ���̃C�x���g�L�[
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys ); 

	// �O���[�o���f�[�^
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// �}�ӃR�����A�v���O���[�o���f�[�^
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );
	p_glb->cp_zukan_common_apl = p_apl;
	

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}��	�`��O���[�o���f�[�^�쐬
 *
 *	@param	heap		�q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�`��O���[�o���f�[�^
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKANGRAVER_DRAWGLB* MakeZukanGraverDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKANGRAVER_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKANGRAVER_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKANGRAVER_DRAWGLB) );

	// �`��f�[�^
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );
	
	return p_glb;
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�C�x���g�쐬
 *
 *	@param	heap		�g�p����q�[�v
 *	@param	zkn_sys		�}�ӃV�X�e��
 *
 *	@return	�C�x���g�f�[�^
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeZukanGraverEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = ZukanGraverEventDataNumGet();

	// �C�x���g�f�[�^�e�[�u���쐬
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeRange( heap, &p_event_tbl[0], zkn_sys, ZKN_ZUKNA_EVENT_CHANGE_RANGE );

	return p_event_tbl;
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanGraverGlb( ZKN_ZUKANGRAVER_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�`��O���[�o���f�[�^�j��
 *
 *	@param	p_glb		�O���[�o���f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanGraverDrawGlb( ZKN_ZUKANGRAVER_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�Ӂ@�C�x���g�f�[�^�j��
 *
 *	@param	p_event	�C�x���g�f�[�^
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanGraverEvent( ZKN_EVENT_DATA* p_event )
{

	GF_ASSERT( p_event );
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );//*/
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�}�ӃA�v���@�C�x���g���擾
 *	
 *	@param	none	
 *
 *	@return	�}�ӃA�v���@�C�x���g��
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZukanGraverEventDataNumGet( void )
{
	return ZKN_ZUKANGRAVER_EVENT_NUM;
}



// �����Z�R�A����
static inline int ZknGraverDrawTypeAddCore( int now, int max, int add )
{
	int ret;
	
	if( add > 0 ){
		if( (now + add) < max ){
			ret = now + add;
		}else{
			ret = 0;
		}
	}else{
		if( (now + add) >= 0 ){
			ret = add;
		}else{
			ret = max - 1;
		}
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��^�C�v�t���O�ʁ@���̕`��^�C�v�擾�֐�
 *
 *	@param	draw_type_flag	�`��^�C�v�t���O
 *	@param	now				���̕`��^�C�v
 *	@param	num				�����l
 *	@param	max				�ő吔
 *
 *	@return	�ړ���`��^�C�v
 */
//-----------------------------------------------------------------------------
static int ZknGraverAddDrawTypeGet( int draw_type_flag, int now, int num, int max )
{
	int ret;

	ret = ZknGraverDrawTypeAddCore( now, max, num );

	return ret;
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
static int ZknZukanGraverProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKANGRAVER_GLB* p_glb = p_glbdata;
	int monsno;

	
	// �|�P�����i���o�[�擾
	monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );
	
	// �|�P��������O���t�B�b�N�؂�ւ��^�C�v��ݒ�
	p_glb->draw_type_flag = ZknZukanGraverPokeDrawTypeFlagGet( monsno, p_glb );
	p_glb->draw_type_max = ZknZukanGraverPokeDrawTypeNumGet( monsno, p_glb );
	p_glb->draw_type = 0;

	
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
static int ZknZukanGraverProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKANGRAVER_GLB* p_glb = p_glbdata;
	
	
	// �I����
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
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
static int ZknZukanGraverProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
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
static int ZknZukanGraverProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKANGRAVER_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKANGRAVER_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_ZUKANGRAVER_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_ZUKANGRAVER_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKANGRAVER_DRAW) );
		p_drawwork = p_drawdata->p_work;
		p_drawwork->draw_type_flag = cp_glb->draw_type_flag;

		// �`��O���[�o���ϐ�������
		p_drawglb->pokegra_move_flag = FALSE;
		p_drawglb->pokegra_move_end = FALSE;
		
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANGRAVER_SEQINIT_LOAD:
		ZknZukanGraverLoadResource( p_drawwork, p_drawglb, cp_glb, p_drawdata->heap );

		ZknZukanGraverDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANGRAVER_SEQINIT_FADEIN:

		check = ZknZukanGraverDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );

		if( check ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKANGRAVER_SEQINIT_END:
		G2_BlendNone();
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
static int ZknZukanGraverProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKANGRAVER_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKANGRAVER_DRAW*	p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case 0:	
		// �t���O���؂�ւ������`��ύX
		if( cp_glb->draw_type != p_drawwork->draw_type ){

			// �X�V
			p_drawwork->draw_type = cp_glb->draw_type;
			p_drawwork->now_draw_buff = (p_drawwork->now_draw_buff + 1) % ZKN_ZUKANGRAVER_GRA_NOW_NUM;		// �\���o�b�t�@�C���f�b�N�X�ύX

			// �O���t�B�b�N���쏈��������
			ZknZukanGraverPokeGraFadeInit_Pack( p_drawwork, p_drawglb );
			ZknZukanGraverIconDrawAnm_S( p_drawwork );

			// �߹��ד��쒆
			p_drawglb->pokegra_move_flag = TRUE;

			// �{�^���Ƀ^�b�`
			Snd_SePlay( ZKN_SND_SLIDE );
			p_drawdata->seq ++;
		}
		break;

	case 1:
		if( ZknZukanGraverPokeGraFadeMain_Pack( p_drawwork, p_drawglb ) == TRUE ){
			p_drawglb->pokegra_move_end = TRUE;
			p_drawdata->seq ++;
		}
		break;

	case 2:
		// �P�V���N�O�Ł@���삪�I�������O���t�B�b�N�ύX
		if( (p_drawglb->pokegra_move_end == TRUE) ){
			// �t�H���g�؂�ւ�
			ZknZukanGraverFontSetUpGraphicType_Pack( p_drawwork, p_drawglb, cp_glb, p_drawdata->heap, cp_glb->draw_type_flag, cp_glb->draw_type );
			// �\���ؑ�
			ZknZukanGraverPokeGraDrawOn( p_drawwork, p_drawglb, cp_glb );
			p_drawglb->pokegra_move_end = FALSE;

			// �߹��ד��슮��
			p_drawglb->pokegra_move_flag = FALSE;

			// �ŏ��ɖ߂�
			p_drawdata->seq = 0;
		}
		break;

	default:
		// ��������
		GF_ASSERT( 0 );
		break;
	}

	// �A�C�R���`��ONOFF����
	ZknZukanGraverIconDrawAnm_Main( p_drawwork );

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
static int ZknZukanGraverProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKANGRAVER_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKANGRAVER_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
		
	case ZKN_ZUKANGRAVER_SEQDELETE_FADEOUT_INIT:
		ZknZukanGraverDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANGRAVER_SEQDELETE_FADEOUT:
		check = ZknZukanGraverDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );

		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_ZUKANGRAVER_SEQDELETE_RELEASE:
		ZknZukanGraverReleaseResource( p_drawwork, p_drawglb );
		p_drawdata->seq++;
		break;

	case ZKN_ZUKANGRAVER_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANGRAVER_SEQDELETE_END:
		return ZKN_PROC_TRUE;

	default:
		break;
	}
	
	return ZKN_PROC_FALSE;
}






//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�ǂݍ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverLoadResource(  ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap  )
{

	// �|�P�����O���t�B�b�N�\��ON
	ZknZukanGraverPokeGraDrawInit( p_draw, p_drawglb, cp_glb );

	// �A�N�^�[���\�[�X�ǂݍ���
	ZknZukanGraverClactResLoad( p_draw, p_drawglb, heap );

	// �w�i�ݒ�
	ZknZukanGraverSetUpBackGround( p_drawglb, heap );

	// �A�N�^�[�o�^
	ZknZukanGraverClactAdd( p_draw, p_drawglb, cp_glb, heap );

	// FONTOAM�ݒ�
	ZknZukanGraverFontInitGraphicType_Pack( p_draw, p_drawglb, cp_glb, heap,cp_glb->draw_type_flag, cp_glb->draw_type );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���\�[�X�̔j��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverReleaseResource(  ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
{
	// FONTOAM�j��
	ZknZukanGraverFontOamDelete( p_draw );
	
	// �A�N�^�[�j��
	ZknZukanGraverClactDelete( p_draw );	

	// �A�N�^�[���\�[�X�j��
	ZknZukanGraverClactResDelete( p_draw, p_drawglb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�w�i�ݒ�
 *
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverSetUpBackGround( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	
	// �L�����N�^�f�[�^�]��
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );

	// �X�N���[���f�[�^�ǂݍ���
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
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
 *	@brief	�`��ON������
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�f�[�^�O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawInit( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb )
{
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	int i;
	int next_type;

	// ���̃|�P����
	ZknZukanGraverPoke_GraSet( p_draw, p_drawglb, cp_glb, monsno, cp_glb->draw_type_flag, cp_glb->draw_type, ZKN_ZUKANGRAVER_GRA_FRONT );

	// ���̃|�P�����ݒ�
	next_type = ZknGraverAddDrawTypeGet( cp_glb->draw_type_flag, cp_glb->draw_type, 1, cp_glb->draw_type_max );
	ZknZukanGraverPoke_GraSet( p_draw, p_drawglb, cp_glb, monsno, cp_glb->draw_type_flag, next_type, ZKN_ZUKANGRAVER_GRA_FRONT_NEXT );

	// �\��
	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		ZKN_GlbPokemonGraphicDrawFlagSet_Idx( p_drawglb->p_drawglb, TRUE, i );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�\��ON
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOn( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb )
{
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	int i;
	int next_type;

	// ���̃|�P�����ݒ�
	next_type = ZknGraverAddDrawTypeGet( cp_glb->draw_type_flag, cp_glb->draw_type, 1, cp_glb->draw_type_max );
	ZknZukanGraverPoke_GraSet( p_draw, p_drawglb, cp_glb, monsno, cp_glb->draw_type_flag, next_type, ZKN_ZUKANGRAVER_GRA_FRONT_NEXT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�\���O���t�B�b�N�ݒ�
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	monsno			�����X�^�[�i���o�[
 *	@param	draw_type_flag	�`��^�C�v�t���O
 *	@param	draw_type		�`��^�C�v
 *	@param	idx				�C���f�b�N�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPoke_GraSet( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type_flag, int draw_type, int idx )
{
	GF_ASSERT( idx <= 2 );
	
	switch( draw_type_flag ){
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_NORMAL:	// �ʏ�`��^�C�v
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MANONLY:		// �I�X�̂ݕ`��^�C�v
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_GIRLONLY:		// ���X�̂ݕ`��^�C�v
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWNONLY:	// �s���̂ݕ`��^�C�v
		ZknZukanGraverPokeGraDrawOnTypeNormal( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMUTTI:		// �~�m�b�`�`��^�C�v
		ZknZukanGraverPokeGraDrawOnTypeMinomutti( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMESU:	// �~�m���X�`��^�C�v
		ZknZukanGraverPokeGraDrawOnTypeMinomesu( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIUSI:		// �V�[�E�V�`��^�C�v
		ZknZukanGraverPokeGraDrawOnTypeSiiusi( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIDORUGO:		// �V�[�h���S�`��^�C�v
		ZknZukanGraverPokeGraDrawOnTypeSiidorugo( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWN_POKE:		// �A���m�[���`��^�C�v
		ZknZukanGraverPokeGraDrawOnTypeAnnoon( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_DEOKISISU_POKE:
		ZknZukanGraverPokeGraDrawOnTypeDeokisisu( p_draw, p_drawglb, cp_glb, monsno, draw_type, idx );
		break;

	default:
		GF_ASSERT(0);
		break;
	}
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
static void ZknZukanGraverPokeGraDrawOff( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
{
	int i;
	
	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		ZKN_GlbPokemonGraphicDrawFlagSet_Idx( p_drawglb->p_drawglb, FALSE, i );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�̃��\�[�X�ǂݍ���
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverClactResLoad( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_sugata_oam_lzh_NCGR, TRUE,
			NARC_zukan_zkn_sugata_oam_lzh_NCGR + ZKN_GRAPHIC_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_sugata_oam_NCLR, FALSE, 
			NARC_zukan_zkn_sugata_oam_NCLR + ZKN_GRAPHIC_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_GRAPHIC_PLTT_LOAD, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_sugata_oam_lzh_NCER, TRUE,
			NARC_zukan_zkn_sugata_oam_lzh_NCER + ZKN_GRAPHIC_RES_ID,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_sugata_oam_lzh_NANR, TRUE,
			NARC_zukan_zkn_sugata_oam_lzh_NANR + ZKN_GRAPHIC_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[���\�[�X�j��
 *	
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverClactResDelete( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
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
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverClactAdd( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int x, y;
	int i;

	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_sugata_oam_lzh_NCGR + ZKN_GRAPHIC_RES_ID,
			NARC_zukan_zkn_sugata_oam_NCLR + ZKN_GRAPHIC_RES_ID, 
			NARC_zukan_zkn_sugata_oam_lzh_NCER + ZKN_GRAPHIC_RES_ID,
			NARC_zukan_zkn_sugata_oam_lzh_NANR + ZKN_GRAPHIC_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKANGRAVER_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// �o�^���ʕ�����ݒ�
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKANGRAVER_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	add.mat.x = 0;
	add.mat.y = 0;
	
	// �w�i
	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){

		// ���W
		ZknZukanGraverPokeGraMatGet( i, &x, &y );
		add.mat.x = x << FX32_SHIFT;
		add.mat.y = (y + ZKN_ZUKANGRAVER_GRA_OAM_DRAW_Y_OFS) << FX32_SHIFT;


		p_draw->pokegra_back[ i ] = CLACT_AddSimple( &add );
		if( (i % 2) == 0 ){
			CLACT_AnmChg( p_draw->pokegra_back[ i ], ZKN_ZUKANGRAVER_CELL_ANM_SEQ_BACK );
		}else{
			CLACT_AnmChg( p_draw->pokegra_back[ i ], ZKN_ZUKANGRAVER_CELL_ANM_SEQ_BACK_2 );
		}
	}

	// �A�C�R��
	add.mat.x = ZKN_ZUKANGRAVER_ICON_X << FX32_SHIFT;
	add.mat.y = ZKN_ZUKANGRAVER_ICON_Y << FX32_SHIFT;
	add.pri	  = 0;
	p_draw->next_icon = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->next_icon, ZKN_ZUKANGRAVER_CELL_ANM_SEQ_ICON );
	CLACT_SetAnmFlag( p_draw->next_icon, TRUE );
	CLACT_BGPriorityChg( p_draw->next_icon, 0 );
	// �`��ONOFF�ݒ�
	if( cp_glb->draw_type_max <= 1 ){
		CLACT_SetDrawFlag( p_draw->next_icon, FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�N�^�[��j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverClactDelete( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	int i;
	
	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		CLACT_Delete( p_draw->pokegra_back[ i ] );
	}

	CLACT_Delete( p_draw->next_icon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄf�t�H���g�t�F�[�h����
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C���A�E�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverDefaultFadeReq( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, BOOL fadein_out )
{
	// ������OAM�ݒ�
	ZknZukanGraverOamFadeInit( p_draw );

	// �u���C�g�l�X���g���ėǂ�������
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// �t�F�[�h�C��
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKANGRAVER_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );
		}else{
			// �t�F�[�h�A�E�g
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKANGRAVER_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );

		}
	}

	// �|�P�O���p���b�g�t�F�[�h�ݒ�
	ZknZukanGraverSpritePokeGraPalFade( p_drawglb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄf�t�H���g�t�F�[�h�����@�I���`�F�b�N
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	fadein_out	�t�F�[�h�C�� TRUE �A�E�g FALSE
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanGraverDefaultFadeEndCheck( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;
	
	// �t�F�[�h���[�N��}�Ӄf�[�^���������Ă悢���`�F�b�N
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}
	

	if( check == TRUE ){

		// �t�F�[�h�C���̂Ƃ��͔������j��
		if( fadein_out == TRUE ){
			// OAM�������ݒ�j��
			ZknZukanGraverOamFadeDelete( p_draw );
		}else{
			// �|�P�����O���t�B�b�N�\��OFF
			ZknZukanGraverPokeGraDrawOff( p_drawglb );
		}
	}else{
		// �|�P�O���p���b�g�t�F�[�h�ݒ�
		ZknZukanGraverSpritePokeGraPalFade( p_drawglb );
	}

	return check;
}


//----------------------------------------------------------------------------
/**
 *	@brief	OAM�̃t�F�[�h����������
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverOamFadeInit( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->pokegra_back[ i ], GX_OAM_MODE_XLU );
	}

	CLACT_ObjModeSet( p_draw->next_icon, GX_OAM_MODE_XLU );

	// �t�H���gOAM
	for( i=0; i<ZKN_GRAPHIC_BUTTONFONT_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->p_pokegra_font[ i ]->p_fontoam, GX_OAM_MODE_XLU );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�̃t�F�[�h�������Z�b�g
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverOamFadeDelete( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->pokegra_back[ i ], GX_OAM_MODE_NORMAL );
	}
	CLACT_ObjModeSet( p_draw->next_icon, GX_OAM_MODE_NORMAL );

	// �t�H���gOAM
	for( i=0; i<ZKN_GRAPHIC_BUTTONFONT_NUM; i++ ){
		FONTOAM_ObjModeSet( p_draw->p_pokegra_font[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�p���b�g�t�F�[�h�l�ݒ�
 *
 *	@param	p_drawglb	�`��O���[�o���f�[�^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverSpritePokeGraPalFade( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
{
	int i;

	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		// �u���C�g�l�X�l�ݒ�
		ZKN_GLB_SpritePokeGraPalFade_Idx( p_drawglb->p_drawglb, &p_drawglb->p_drawglb->fade, i );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N���쏉�����@�p�b�N
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraFadeInit_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
{
	int i;

	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		ZknZukanGraverPokeGraFadeInit( p_draw, p_drawglb, ZKN_GRAPHIC_MOVE_X, ZKN_GRAPHIC_MOVE_Y, i );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N���상�C���@�p�b�N
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�I����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanGraverPokeGraFadeMain_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb )
{
	int i;
	BOOL check;

	// ���������Ă��Ȃ��Ƃ��͉������Ȃ�
	if( p_drawglb->pokegra_move_flag == FALSE ){
		return TRUE;
	}

	for( i=0; i<ZKN_ZUKANGRAVER_GRA_NUM; i++ ){
		check = ZknZukanGraverPokeGraFadeMain( p_draw, p_drawglb, i );
	}

	// FONT_OAM��ύX
	for( i=0; i<ZKN_GRAPHIC_BUTTONFONT_NUM; i++ ){
		FONTOAM_ReflectParentMat( p_draw->p_pokegra_font[ i ]->p_fontoam );
	}

	return check;	// �S�������V���N���œ����̂ł���ł悢
}

//----------------------------------------------------------------------------
/**
 * [�|�P�������X�g��ʃt�F�[�h]
 *	@brief	�|�P�����O���t�B�b�N�t�F�[�h������
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	move_x		���J�n���W�܂ł̋���
 *	@param	move_y		���J�n���W�܂ł̋���
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraFadeInit( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int move_x, int move_y, int idx )
{
	int x;
	int y;
	int def_x;
	int def_y;
	int poke_arry_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, idx );

	// �f�t�H���g���W�̎擾
	ZknZukanGraverPokeGraMatGet( idx, &def_x, &def_y );
	
	// ���̍��W�擾
	ZKN_GlbPokemonGraphicGetMatrix_Idx( p_drawglb->p_drawglb, &x, &y, poke_arry_idx );

	// ���W��ݒ�
	ZKN_UTIL_MoveReq( &p_draw->pokegra_move[idx], def_x + move_x, def_x, def_y + move_y, def_y, ZKN_GRAPHIC_MOVE_SYNC );

	// �X�v���C�g�̃|�P�����͍������ύX����Ă���\��������̂ŕۑ�
	p_draw->pokegra_y[idx] = y - def_y;
}

//----------------------------------------------------------------------------
/**
 * [�|�P�������X�g��ʃt�F�[�h]
 *	@brief	�|�P�����O���t�B�b�N�t�F�[�h
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanGraverPokeGraFadeMain( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, int idx )
{
	BOOL check;
	VecFx32 mat;
	int poke_arry_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, idx );
	
	check = ZKN_UTIL_MoveMain( &p_draw->pokegra_move[ idx ] );

	// ���W�ݒ�
	ZKN_GlbPokemonGraphicSetMatrix_Idx( p_drawglb->p_drawglb, p_draw->pokegra_move[ idx ].x, p_draw->pokegra_move[ idx ].y + p_draw->pokegra_y[idx], poke_arry_idx );

	// OAM���W�ݒ�
	mat.x = p_draw->pokegra_move[ idx ].x << FX32_SHIFT;
	mat.y = (p_draw->pokegra_move[ idx ].y + ZKN_ZUKANGRAVER_GRA_OAM_DRAW_Y_OFS) << FX32_SHIFT;
	CLACT_SetMatrix( p_draw->pokegra_back[ poke_arry_idx ], &mat );

	return check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����`��^�C�v�t���O�ݒ�
 *
 *	@param	monsno	�����X�^�[�i���o�[
 *	@param	cp_glb	�O���[�o���f�[�^
 *
 *	@return	�`��^�C�v�t���O
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverPokeDrawTypeFlagGet( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb )
{
#if 1	// 1�ɂ���ƃ~�m���b�`�Ȃǂ����f
	// �~�m���b�`
	if( monsno == MONSNO_MINOMUTTI ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMUTTI;
	}

	// �~�m���X
	if( monsno == MONSNO_MINOMESU ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMESU;
	}

	// �V�[�E�V
	if( monsno == MONSNO_SIIUSI ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIUSI;
	}

	// �V�[�h���S
	if( monsno == MONSNO_SIIDORUGO ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIDORUGO;
	}
#endif

	// �A���m�[��
	if( monsno == MONSNO_ANNOON ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWN_POKE;
	}

	// �f�I�L�V�X
	if( monsno == MONSNO_DEOKISISU ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_DEOKISISU_POKE;
	}

	// ���̑��̓m�[�}���Œ��ׂ�
	return ZknZukanGraverPokeDrawTypeFlagNormal( monsno, cp_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��^�C�v�̐����擾
 *
 *	@param	monsno	�����X�^�[�i���o�[
 *	@param	cp_glb	�O���[�o��
 *
 *	@return	�`��^�C�v��
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverPokeDrawTypeNumGet( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb )
{
#if 1	// 1�ɂ���ƃ~�m���b�`�Ȃǂ����f
	// �~�m���b�`
	if( monsno == MONSNO_MINOMUTTI ){
		return ZKN_GLBDATA_SaveData_MinomuttiNumGet( cp_glb->p_glb );
	}

	// �~�m���X
	if( monsno == MONSNO_MINOMESU ){
		return ZKN_GLBDATA_SaveData_MinomesuNumGet( cp_glb->p_glb );
	}

	// �V�[�E�V
	if( monsno == MONSNO_SIIUSI ){
		return ZKN_GLBDATA_SaveData_SiiusiNumGet( cp_glb->p_glb );
	}

	// �V�[�h���S
	if( monsno == MONSNO_SIIDORUGO ){
		return ZKN_GLBDATA_SaveData_SiidorugoNumGet( cp_glb->p_glb );
	}
#endif

	// �A���m�[��
	if( monsno == MONSNO_ANNOON ){
		return ZKN_GLBDATA_SaveData_AnoonNumGet( cp_glb->p_glb );
	}

	// �f�I�L�V�X
	if( monsno == MONSNO_DEOKISISU ){
		return ZKN_GLBDATA_SaveData_DeokisisuFormSeeNumGet( cp_glb->p_glb );
	}

	// ���̑��̓m�[�}���Œ��ׂ�
	return ZKN_GLBDATA_SaveData_SexNumGet( cp_glb->p_glb, monsno );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ʏ�|�P�����̕`��^�C�v�t���O���擾
 *
 *	@param	monsno		�����X�^�[�i���o�[
 *	@param	cp_glb		�O���[�o��
 *
 *	@return	�`��^�C�v�t���O
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverPokeDrawTypeFlagNormal( int monsno, const ZKN_ZUKANGRAVER_GLB* cp_glb )
{
	int sex;
	int type_num;
	sex = PokePersonalParaGet( monsno, ID_PER_sex );

	if( sex == MONS_MALE ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MANONLY;
	}
	if( sex == MONS_FEMALE ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_GIRLONLY;
	}
	if( sex == MONS_UNKNOWN ){
		return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWNONLY;
	}

	// ��������1�����Ȃ��Ƃ����`ONLY�^�C�v�ɂ���
	type_num = ZKN_GLBDATA_SaveData_SexNumGet( cp_glb->p_glb, monsno );
	if( type_num == 1 ){
		sex = ZKN_GLBDATA_SaveData_SexGet( cp_glb->p_glb, monsno, ZUKAN_WORK_SEX_FIRST );
		GF_ASSERT( sex != ZUKAN_WORK_GET_SEX_ERR );
		if( sex == MONS_MALE ){
			return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MANONLY;
		}
		if( sex == MONS_FEMALE ){
			return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_GIRLONLY;
		}
		if( sex == MONS_UNKNOWN ){
			return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWNONLY;
		}
	}
	
	return ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_NORMAL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����`��	�`��^�C�v�@����
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o���f�[�^
 *	@param	monsno			�����X�^�[�i���o�[
 *	@param	draw_type		�`��^�C�v
 *	@param	s_idx			�C���f�b�N�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeNormal( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int sex;
	int x, y;
	int buff_idx;

	// �\
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	sex = ZKN_UTIL_PokemonGraphicSet_FS_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			monsno, PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( sex != ZUKAN_WORK_GET_SEX_ERR );

	// ��
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	sex = ZKN_UTIL_PokemonGraphicSet_FS_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			monsno, PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( sex != ZUKAN_WORK_GET_SEX_ERR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����`��	�`��^�C�v�@�~�m���b�`
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o���f�[�^
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	monsno			�����X�^�[�i���o�[
 *	@param	draw_type		�`������
 *	@param	s_idx			�|�P�����O���t�B�b�N�C���f�b�N�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeMinomutti( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int area_type;
	int buff_idx;
	
	// �\
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	area_type = ZKN_UTIL_PokemonGraphicSet_Minomutti_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );

	// ��
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	area_type = ZKN_UTIL_PokemonGraphicSet_Minomutti_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����`��	�`��^�C�v�@�~�m���X
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o���f�[�^
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	monsno			�����X�^�[�i���o�[
 *	@param	draw_type		�`������
 *	@param	s_idx			�|�P�����O���t�B�b�N�C���f�b�N�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeMinomesu( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int area_type;
	int buff_idx;
	
	// �\
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	area_type = ZKN_UTIL_PokemonGraphicSet_Minomesu_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );

	// ��
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	area_type = ZKN_UTIL_PokemonGraphicSet_Minomesu_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����`��	�`��^�C�v�@�V�[�E�V
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o���f�[�^
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	monsno			�����X�^�[�i���o�[
 *	@param	draw_type		�`������
 *	@param	s_idx			�|�P�����O���t�B�b�N�C���f�b�N�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeSiiusi( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int area_type;
	int buff_idx;
	
	// �\
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	area_type = ZKN_UTIL_PokemonGraphicSet_Siiusi_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );

	// ��
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	area_type = ZKN_UTIL_PokemonGraphicSet_Siiusi_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����`��	�`��^�C�v�@�V�[�V�[�h���S
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o���f�[�^
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	monsno			�����X�^�[�i���o�[
 *	@param	draw_type		�`������
 *	@param	s_idx			�|�P�����O���t�B�b�N�C���f�b�N�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeSiidorugo( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int area_type;
	int buff_idx;
	
	// �\
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	area_type = ZKN_UTIL_PokemonGraphicSet_Siidorugo_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );

	// ��
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	area_type = ZKN_UTIL_PokemonGraphicSet_Siidorugo_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( area_type != ZUKAN_WORK_GET_SEX_ERR );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����`��	�`��^�C�v�@�A���m�[��
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o���f�[�^
 *	@param	monsno			�����X�^�[�i���o�[
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeAnnoon( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int form;
	int buff_idx;
	
	// �\
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	form = ZKN_UTIL_PokemonGraphicSet_Anoon_Idx(	
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( form != ZUKAN_WORK_GET_SEX_ERR );

	// ��
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	form = ZKN_UTIL_PokemonGraphicSet_Anoon_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( form != ZUKAN_WORK_GET_SEX_ERR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�I�L�V�X�@�`��
 *
 *	@param	p_draw		�`�惏�[�N
 *	@param	p_drawglb	�`��O���[�o��
 *	@param	cp_glb		�O���[�o���f�[�^
 *	@param	monsno		�����X�^�[�i���o�[
 *	@param	draw_type	�`��^�C�v
 *	@param	s_idx		�O���t�B�b�N�C���f�b�N�X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraDrawOnTypeDeokisisu( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int monsno, int draw_type, int s_idx )
{
	int x, y;
	int form;
	int buff_idx;
	
	// �\
	ZknZukanGraverPokeGraMatGet( s_idx, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx );
	form = ZKN_UTIL_PokemonGraphicSet_Deokisisu_Idx(	
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_FRONT,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( form != POKEZUKAN_DEOKISISU_INIT );

	// ��
	ZknZukanGraverPokeGraMatGet( s_idx+1, &x, &y );
	buff_idx = ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, s_idx + 1 );
	form = ZKN_UTIL_PokemonGraphicSet_Deokisisu_Idx(
			p_drawglb->p_drawglb,
			cp_glb->p_glb,
			PARA_BACK,
			x, y,
			draw_type, buff_idx );
	GF_ASSERT( form != POKEZUKAN_DEOKISISU_INIT );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�ӂ����OAM�̏������p�b�N�֐�
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��	
 *	@param	heap			�q�[�v
 *	@param	draw_type_flag	�`��^�C�v�t���O
 *	@param	draw_type		�`��^�C�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverFontInitGraphicType_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type )
{
	int next_draw_type;
	int pearent_idx;
	
	
	// ���\�����̂��̂̃e�L�X�g
	pearent_idx		= ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, ZKN_ZUKANGRAVER_GRA_FRONT );
	ZknZukanGraverFontSetUpGraphicType( p_draw, p_drawglb, cp_glb, heap,  draw_type_flag, draw_type, pearent_idx, 0 );

	// ���\��������̂̃e�L�X�g
	next_draw_type	= ZknGraverAddDrawTypeGet( draw_type_flag, draw_type, 1, cp_glb->draw_type_max );	
	pearent_idx		= ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, ZKN_ZUKANGRAVER_GRA_FRONT_NEXT );
	ZknZukanGraverFontSetUpGraphicType( p_draw, p_drawglb, cp_glb, heap,  draw_type_flag, next_draw_type, pearent_idx, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ӂ����OAM�̐ݒ�p�b�N�֐�
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��	
 *	@param	heap			�q�[�v
 *	@param	draw_type_flag	�`��^�C�v�t���O
 *	@param	draw_type		�`��^�C�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverFontSetUpGraphicType_Pack( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type )
{
	int next_draw_type;
	int pearent_idx;
	int fontoam_idx;
	
	// ���\��������̂̃e�L�X�g
	next_draw_type	= ZknGraverAddDrawTypeGet( draw_type_flag, draw_type, 1, cp_glb->draw_type_max );	
	pearent_idx		= ZknZukanGraverGetBuffIdx_PokeGraIdx( p_draw->now_draw_buff, ZKN_ZUKANGRAVER_GRA_FRONT_NEXT );
	fontoam_idx	= (p_draw->now_draw_buff + 1) % ZKN_ZUKANGRAVER_GRA_NOW_NUM;

	// �j�����Ă�����
	ZKN_FONTOAM_Delete( p_draw->p_pokegra_font[ fontoam_idx ] );
	ZknZukanGraverFontSetUpGraphicType( p_draw, p_drawglb, cp_glb, heap,  draw_type_flag, next_draw_type, pearent_idx, fontoam_idx );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�`��^�C�v������̕`��
 *
 *	@param	p_draw			�`�惏�[�N
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	heap			�q�[�v
 *	@param	draw_type_flag	�`��^�C�v�t���O
 *	@param	draw_type		�`��^�C�v
 *	@param  pearent_idx		�e�A�N�^�[IDX
 *	@param	fontoam_idx		�t�H���gOAMIDX
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverFontSetUpGraphicType( ZKN_ZUKANGRAVER_DRAW* p_draw, ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int heap, int draw_type_flag, int draw_type, int parent_idx, int fontoam_idx )
{
	GF_BGL_BMPWIN* win;	// �����񏑂����ݐ�
	ZKN_FONTOAM_INIT fontoam_init;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// �p���b�g�A�h���X
	int comment;

	// ���CLACT��o�^���Ă���K�v������
	GF_ASSERT( p_draw->pokegra_back[ parent_idx ] );


	// BMM�f�[�^IDX�擾
	comment = ZknZukanGraverFontGet( p_drawglb, cp_glb, draw_type_flag, draw_type );

	// �������f�[�^�̋��ʕ������쐬
	// ���ʃf�[�^���
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( p_draw->res_obj[ CLACT_U_PLTT_RES ], NULL );
	fontoam_init.x			 = ZKN_GRAPHIC_BUTTON_FONT_OFS_X;
	fontoam_init.y			 = ZKN_GRAPHIC_BUTTON_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_ZUKANGRAVER_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;

	// �p���b�g�]����A�h���X�擾
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DMAIN );

	// �r�b�g�}�b�v�E�B���h�E�쐬
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CX,
			ZKN_GRAPHIC_BUTTONFONT_BMP_SIZE_CY );

	// comment
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, comment, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->pokegra_back[ parent_idx ];
	p_draw->p_pokegra_font[ fontoam_idx ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_pokegra_font[ fontoam_idx ]->p_fontoam, pltt_ofs );

	// �r�b�g�}�b�v�E�B���h�E�j��
	ZKN_FONTOAM_DeleteBmp( win );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�`��^�C�v������̕`��	�`��^�C�v�@����
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	heap			�q�[�v
 *	@param	draw_type		�`��^�C�v 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeNormal( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int sex;
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// ���ʎ擾
	sex = ZKN_GLBDATA_SaveData_SexGet( cp_glb->p_glb, monsno, draw_type );
	GF_ASSERT( sex != ZUKAN_WORK_GET_SEX_ERR );
	
	switch( sex ){
	case PARA_MALE:
		comment = ZNK_ZUKAN_GRAPH_00;
		break;
		
	case PARA_FEMALE:
		comment = ZNK_ZUKAN_GRAPH_01;
		break;
		
	default:
		GF_ASSERT(0);		// ��������
		break;
	}
	
	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��^�C�v������̕`��	�`��^�C�v�@�j�̂�
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	draw_type		�`��^�C�v 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeManOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;

	comment = ZNK_ZUKAN_GRAPH_00;

	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��^�C�v������̕`��	�`��^�C�v�@���̂�
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	draw_type		�`��^�C�v 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeGirlOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;

	comment = ZNK_ZUKAN_GRAPH_01;
	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��^�C�v������̕`��	�`��^�C�v�@�s���̂�
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	draw_type		�`��^�C�v 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeUnknownOnly( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment = ZNK_ZUKAN_GRAPH_08;

	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��^�C�v������̕`��	�`��^�C�v�@�~�m���V
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	draw_type		�`��^�C�v 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeMinomutti( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int form = ZKN_GLBDATA_SaveData_MinomuttiFormGet( cp_glb->p_glb, draw_type );

	comment = ZNK_ZUKAN_GRAPH_04 + form;
	return comment;
}

static int ZknZukanGraverFontSetUpGraphicTypeMinomesu( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int form = ZKN_GLBDATA_SaveData_MinomesuFormGet( cp_glb->p_glb, draw_type );

	comment = ZNK_ZUKAN_GRAPH_04 + form;

	return comment;
}

static int ZknZukanGraverFontSetUpGraphicTypeSiiusi( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int form = ZKN_GLBDATA_SaveData_SiiusiFormGet( cp_glb->p_glb, draw_type );

	comment = ZNK_ZUKAN_GRAPH_02 + form;

	return comment;
}

static int ZknZukanGraverFontSetUpGraphicTypeSiidorugo( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int form = ZKN_GLBDATA_SaveData_SiidorugoFormGet( cp_glb->p_glb, draw_type );

	comment = ZNK_ZUKAN_GRAPH_02 + form;

	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��^�C�v������̕`��	�`��^�C�v�@�A���m�[��
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	draw_type		�`��^�C�v 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeAnnoon( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment = ZNK_ZUKAN_GRAPH_07;

	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�I�L�V�X�R�����g���擾
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	cp_glb			�O���[�o���f�[�^
 *	@param	draw_type		�`��^�C�v 
 *
 *	@return	�R�����g�f�[�^
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontSetUpGraphicTypeDeokisisu( ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type )
{
	int comment;
	int form = ZKN_GLBDATA_SaveData_DeokisisuFormGet( cp_glb->p_glb, draw_type );

	comment = ZKN_DNA_00 + form;
	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�o�b�t�@�C���f�b�N�X�Ƃ��̒��̃C���f�b�N�X����
 *			���ۂ̃|�P�����`��C���f�b�N�X���擾����
 *
 *	@param	buff_idx		�o�b�t�@IDX
 *	@param	idx				IDX
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static inline int ZknZukanGraverGetBuffIdx_PokeGraIdx( int buff_idx, int idx )
{
	if( buff_idx == ZKN_ZUKANGRAVER_GRA_NOW_DRAW_01 ){
		// ���\�� 01 ��23
		return idx;	
	}
	
	// ���\��23 ��01
	idx -= ZKN_ZUKANGRAVER_GRA_FRONT_NEXT;	
	if( idx < 0 ){
		idx += ZKN_ZUKANGRAVER_GRA_NUM;
	}
	return idx;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N���W�擾
 *
 *	@param	idx			�C���f�b�N�X
 * 
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverPokeGraMatGet( int idx, int* x, int* y )
{
	int set_x = 0;
	int set_y = 0;
	
	switch( idx ){
	case ZKN_ZUKANGRAVER_GRA_BACK:			// ���̌��̊G
		set_x = ZKN_ZUKANGRAVER_GRA_DRAW_BACK_X_OFS;
		
	case ZKN_ZUKANGRAVER_GRA_FRONT:			// ���̕\�̊G
		set_x += ZKN_ZUKANGRAVER_GRA_DRAW_FRONT_X;
		set_y = ZKN_ZUKANGRAVER_GRA_DRAW_Y;
		break;
		
	case ZKN_ZUKANGRAVER_GRA_BACK_NEXT:		// ���̌��̊G
		set_x = ZKN_ZUKANGRAVER_GRA_DRAW_BACK_X_OFS;
		
	case ZKN_ZUKANGRAVER_GRA_FRONT_NEXT:		// ���̕\�̊G
		set_x += ZKN_ZUKANGRAVER_GRA_DRAW_FRONT_NEXT_X;
		set_y = ZKN_ZUKANGRAVER_GRA_DRAW_Y;
		break;

	default:
		GF_ASSERT(0);
		break;
	}

	*x = set_x;
	*y = set_y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	GMM���߂��IDX�擾
 *
 *	@param	p_drawglb		�`��O���[�o��
 *	@param	draw_type_flag	�`��^�C�v�t���O
 *	@param	draw_type		�`��^�C�v
 *
 *	@return	GMMIDX
 */
//-----------------------------------------------------------------------------
static int ZknZukanGraverFontGet(ZKN_ZUKANGRAVER_DRAWGLB* p_drawglb, const ZKN_ZUKANGRAVER_GLB* cp_glb, int draw_type_flag, int draw_type)
{
	int comment;

	switch( draw_type_flag ){
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_NORMAL:	// �ʏ�`��^�C�v
		comment = ZknZukanGraverFontSetUpGraphicTypeNormal( p_drawglb, cp_glb, draw_type );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MANONLY:		// �I�X�̂ݕ`��^�C�v
		comment = ZknZukanGraverFontSetUpGraphicTypeManOnly( p_drawglb, cp_glb, draw_type );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_GIRLONLY:		// ���X�̂ݕ`��^�C�v
		comment = ZknZukanGraverFontSetUpGraphicTypeGirlOnly( p_drawglb, cp_glb, draw_type );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWNONLY:	// �s���̂ݕ`��^�C�v
		comment = ZknZukanGraverFontSetUpGraphicTypeUnknownOnly( p_drawglb, cp_glb, draw_type );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMUTTI:	// �~�m�����`�`��^�C�v
		comment = ZknZukanGraverFontSetUpGraphicTypeMinomutti( p_drawglb, cp_glb, draw_type );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_MINOMESU:	// �~�m���X�`��^�C�v
		comment = ZknZukanGraverFontSetUpGraphicTypeMinomesu( p_drawglb, cp_glb, draw_type );
		break;
		
	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIUSI:		// �V�[�E�V�`��^�C�v
		comment = ZknZukanGraverFontSetUpGraphicTypeSiiusi( p_drawglb, cp_glb, draw_type );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_SIIDORUGO:	// �V�[�h���S�`��^�C�v
		comment = ZknZukanGraverFontSetUpGraphicTypeSiidorugo( p_drawglb, cp_glb, draw_type );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_UNKNOWN_POKE:		// �A���m�[���`��^�C�v
		comment = ZknZukanGraverFontSetUpGraphicTypeAnnoon( p_drawglb, cp_glb, draw_type );
		break;

	case ZKN_ZUKANGRAVER_DRAW_TYPE_FLG_DEOKISISU_POKE:
		comment = ZknZukanGraverFontSetUpGraphicTypeDeokisisu( p_drawglb, cp_glb, draw_type );
		break;

	default:
		break;
	}

	return comment;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�H���gOAM�̔j��
 *
 *	@param	p_draw	�`�惏�[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverFontOamDelete( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_GRAPHIC_BUTTONFONT_NUM; i++ ){
		ZKN_FONTOAM_Delete( p_draw->p_pokegra_font[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�o�[�W�����A�C�R���`��A�j���@�X�^�[�g
 *
 *	@param	p_draw	�`�惏�[�N 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverIconDrawAnm_S( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	CLACT_SetDrawFlag( p_draw->next_icon, FALSE );

	p_draw->icon_draw_s_time = ZKN_GRAPHIC_MOVE_ICON_OFF_SYNC;
	p_draw->icon_draw_flag = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�o�[�V�����A�C�R���`��ON�A�j���@���C��
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanGraverIconDrawAnm_Main( ZKN_ZUKANGRAVER_DRAW* p_draw )
{
	if( p_draw->icon_draw_flag ){
		
		p_draw->icon_draw_s_time --;

		if( p_draw->icon_draw_s_time <= 0 ){
			CLACT_SetDrawFlag( p_draw->next_icon, TRUE );
			p_draw->icon_draw_flag = FALSE;
		}
	}
}

