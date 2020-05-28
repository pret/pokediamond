//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		ev_poke_select.c
 *	@brief
 *	@author	 
 *	@data		2006.03.13
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include <nnsys.h>
#include "gf_gx.h"
#include "include/gflib/calc2D.h"
#include "include/gflib/calctool.h"
#include "include/gflib/display.h"
#include "include/gflib/vram_transfer_manager.h"
#include "include/gflib/touchpanel_system.h"
#include "include/gflib/camera.h"
#include "include/gflib/char_manager.h"
#include "include/gflib/pltt_manager.h"
#include "include/gflib/simple_3dgraphics.h"
#include "include/gflib/strbuf.h"
#include "include/gflib/msg_print.h"
#include "include/system/heapdefine.h"
#include "include/system/wipe.h"
#include "include/system/clact_util.h"
#include "include/system/clact_util_res.h"
#include "include/system/clact_util_vram.h"
#include "include/system/arc_util.h"
#include "include/system/softsprite.h"
#include "include/system/render_oam.h"
#include "include/system/msgdata.h"
#include "include/system/fontproc.h"
#include "include/system/bmp_menu.h"
#include "include/system/window.h"
#include "include/system/tcbman.h"
#include "include/system/swsprite.h"

#include "include/poketool/poke_tool.h"
#include "include/poketool/monsno.h"

#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_ev_pokeselect.h"


#include "src/demo/ev_pokeselect.naix"


#include "include/system/snd_tool.h"


#define	__EV_POKE_SELECT_H_GLOBAL
#include "include/demo/ev_poke_select.h"


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
 *		���p�萔
 */
//-----------------------------------------------------------------------------
#define EV_POKESELE_SND_SELECT	( SE_DECIDE )		// �I��
#define EV_POKESELE_SND_DECIDE	( SE_DECIDE )		// ����
#define EV_POKESELE_SND_BAGOPEN	( SEQ_SE_DP_BAG_030 ) // �o�b�O�J��





//-----------------------------------------------------------------------------
/**
 *	�v���b�N
 */
//-----------------------------------------------------------------------------
// �`��V�X�e���֌W
#define EV_POKESELECT_VRAMTRANSFER_MANAGER_NUM	( 8 )
#define OAM_OAM_MAIN_S			(0)			// ���C����� OAM�g�p�̈�J�n
#define OAM_OAM_MAIN_E			(128)		// ���C����� OAM�g�p�̈�I��
#define OAM_AFF_MAIN_S			(0)			// ���C����� �A�t�B���g�p�̈�J�n
#define OAM_AFF_MAIN_E			(32)		// ���C����� �A�t�B���g�p�̈�I��
#define OAM_OAM_SUB_S			(0)			// �T�u��� OAM�g�p�̈�J�n
#define OAM_OAM_SUB_E			(128)		// �T�u��� OAM�g�p�̈�I��
#define OAM_AFF_SUB_S			(0)			// �T�u��� �A�t�B���g�p�̈�J�n
#define OAM_AFF_SUB_E			(32)		// �T�u��� �A�t�B���g�p�̈�I��
#define OAM_CHAR_ENTRY_NUM		(32)		// �L�����N�^�}�l�[�W���G���g���[��
#define OAM_CHAR_VRAMTRANS_MAIN_SIZE	(0x14000)// ���C����� �L�����N�^�}�l�[�W��Vram�Ǘ��̈�
#define OAM_CHAR_VRAMTRANS_SUB_SIZE		(0x4000)// �T�u��� �L�����N�^�}�l�[�W��Vram�Ǘ��̈�
#define OAM_PLTT_ENTRY_NUM		(32)		// �p���b�g�}�l�[�W���G���g���[��
#define CLACT_SET_WORK_NUM		( 2 )	// �Z���A�N�^�[�Z�b�g���[�N��
#define CLACT_RES_DATA_TBL_NUM	( 2 )	// �e���\�[�X�}�l�[�W���ɓo�^�ł���f�[�^��
#define CLACT_BG_PRI			( 1 )
#define SWSP_OBJNUM		(1)		// SWSP�I�u�W�F�N�g��
#define SWSP_CHARNUM	(1)		// SWSP�I�u�W�F�N�g��
#define SWSP_PLTTNUM	(1)		// SWSP�I�u�W�F�N�g��

#define BG_FONTBMP_X	( 4 )			// �����ʃr�b�g�}�b�vsize
#define BG_FONTBMP_Y	( 19 )			// �����ʃr�b�g�}�b�vsize
#define BG_FONTBMP_CX	( 23 )			// �����ʃr�b�g�}�b�vsize
#define BG_FONTBMP_CY	( 4 )			// �����ʃr�b�g�}�b�vsize
#define BG_FONT_COLOR		( 0 )		// �g�p�J���[�p���b�g
#define BG_FONT_CG_OFS		( 512 )
#define BG_FONT_STR_COLOR	( 2 )		// �t�H���g�p�J���[�p���b�g
#define BG_FONTBMP_PRICOLOR	( GF_PRINTCOLOR_MAKE(1,2,15) )

#define BG_YESNOBMP_X	( 23 )			// �����ʃr�b�g�}�b�vsize
#define BG_YESNOBMP_Y	( 12 )			// �����ʃr�b�g�}�b�vsize
#define BG_YESNOBMP_CX	( 5 )			// �����ʃr�b�g�}�b�vsize
#define BG_YESNOBMP_CY	( 4 )			// �����ʃr�b�g�}�b�vsize
#define BG_YESNOBMP_CG_CHR_OFS	( BG_FONT_CG_OFS + TALK_WIN_CGX_SIZ + 128 )
#define BG_YESNOBMP_CG_OFS	( TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ + 128 )
#define BG_YESNOBMP_COLOR		( 1 )	// �g�p
#define BG_YESNOBMP_STR_COLOR	( 3 )	// �����p

#define BG_BACK_COLOR	( 4 )

#define BG_FONTSUBBMP_0X		( 12 )			// �����ʃr�b�g�}�b�v�ʒu
#define BG_FONTSUBBMP_0Y		( 4 )			// �����ʃr�b�g�}�b�v�ʒu
#define BG_FONTSUBBMP_1X		( 4 )			// �����ʃr�b�g�}�b�v�ʒu
#define BG_FONTSUBBMP_1Y		( 14 )			// �����ʃr�b�g�}�b�v�ʒu
#define BG_FONTSUBBMP_2X		( 20 )			// �����ʃr�b�g�}�b�v�ʒu
#define BG_FONTSUBBMP_2Y		( 13 )			// �����ʃr�b�g�}�b�v�ʒu
#define BG_FONTSUBBMP_CX	( 11 )			// �����ʃr�b�g�}�b�vsize
#define BG_FONTSUBBMP_CY	( 4 )			// �����ʃr�b�g�}�b�vsize
#define BG_FONTSUB_COLOR		( 5 )		// �J���[�p���b�g
#define BG_FONTSUB_CGX_OFS		( 64 )		// �J���[�p���b�g
#define BG_FONTSUBBMP_ALPHA	( 10 )
#define BG_FONTSUBBMP_PRICOLOR	( GF_PRINTCOLOR_MAKE(1,2,0xa) )

// �|�P�����O���t�B�b�N
#define POKEGRA_TEX_SIZE	(0x8000)	// �|�P����4�̕�
#define POKEGRA_PLTT_SIZE	(0x80)

// �J�����ݒ�
#define CAMERA_TARGET_X	( 0 )
#define CAMERA_TARGET_Y	( 0 )
#define CAMERA_TARGET_Z	( 0 )
#define CAMERA_ANGLE_X	( FX_GET_ROTA_NUM( -30 ) )
#define CAMERA_ANGLE_Y	( FX_GET_ROTA_NUM( 0 ) )
#define CAMERA_ANGLE_Z	( FX_GET_ROTA_NUM( 0 ) )
#define CAMERA_PEARCE	( FX_GET_ROTA_NUM( 22 ) )
#define CAMERA_DISTANCE	( 300 << FX32_SHIFT )

//-------------------------------------
//	�J���������
//=====================================
#define CAMERA_TARGET_AF_Z	( 36 * FX32_ONE )
#define CAMERA_ANGLE_AF_X	( FX_GET_ROTA_NUM( -50 ) )
#define CAMERA_DISTANCE_AF	( 200 << FX32_SHIFT )
#define CAMERA_MOVE_AF_COUNT	( 6 )
 

// �t�F�[�h�����֌W
#define EV_POKESELECT_PROC_FADE_DIV		( 6 )
#define EV_POKESELECT_PROC_FADE_SYNC	( 1 )


// �I��
enum{
	POKESELECT_LEFT_BALL,
	POKESELECT_CENTER_BALL,
	POKESELECT_RIGHT_BALL,
	EV_POKESELECT_MONSNUM,
};

// 3D�I�u�W�F�N�g��
enum{
	POKESELECT_AUTOANM,
	POKESELECT_BAG,
	POKESELECT_BALL_LEFT,
	POKESELECT_BALL_CENTER,
	POKESELECT_BALL_RIGHT,
	POKESELECT_GROUND,
	POKESELECT_3DOBJ_NUM
};
// 3D�{�^���ʒu�ł�
#define EV_POKESELECT_DRAW_MAT_BALL_LEFT_X	( -44 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_LEFT_Y	( -4 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_LEFT_Z	( 32 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_CENTER_X	( 0 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_CENTER_Y	( -4 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_CENTER_Z	( 62 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_RIGHT_X	( 38 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_RIGHT_Y	( -4 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_RIGHT_Z	( 26 ) 

// �n�`�ʒu�ł�
#define EV_POKESELECT_DRAW_GRUND_X	( 0 )
#define EV_POKESELECT_DRAW_GRUND_Y	( -28 * FX32_ONE )
#define EV_POKESELECT_DRAW_GRUND_Z	( 40 * FX32_ONE )
#define EV_POKESELECT_DRAW_GRUND_SCA_X	( FX32_CONST( 3.50f ) )
#define EV_POKESELECT_DRAW_GRUND_SCA_Y	( FX32_ONE )
#define EV_POKESELECT_DRAW_GRUND_SCA_Z	( FX32_CONST( 3.50f ) )
#define EV_POKESELECT_DRAW_GRUND_ROTA_X	( FX_GET_ROTA_NUM(0) )
#define EV_POKESELECT_DRAW_GRUND_ROTA_Y	( FX_GET_ROTA_NUM(180) )
#define EV_POKESELECT_DRAW_GRUND_ROTA_Z	( FX_GET_ROTA_NUM(0) )

// ���ʒu�ł�
#define EV_POKESELECT_DRAW_MAT_BALL_LEFT_2X		( 78 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_LEFT_2Y		( 55 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_CENTER_2X	( 130 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_CENTER_2Y	( 82 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_RIGHT_2X	( 172 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_RIGHT_2Y	( 50 ) 

//-------------------------------------
//	�����V�[�P���X
//=====================================
enum{
	POKESELECT_SEQ_INIT,
	POKESELECT_SEQ_WAIT,
	POKESELECT_SEQ_AUTOANM,		// AUTO�A�j��
	POKESELECT_SEQ_SELECT,		// �I��
	POKESELECT_SEQ_QUESTION,	// �m�F
	POKESELECT_SEQ_END,	// �I��
};


//-------------------------------------
//	�J�n�܂ł̑҂�
//=====================================
#define POKESELECT_MONNSUTA_START_WAIT ( 36 )

//-------------------------------------
//	���b�Z�[�W���o��܂ł̂܂�
//=====================================
#define POKESELECT_MSSAGE_WAIT ( 6 )



//-------------------------------------
//	�J�[�\������
//=====================================
#define CURSOR_MOVE_Y		( 8 * FX32_ONE )
#define CURSOR_MOVE_COUNT	( 32 )

//-------------------------------------
//	�m�F��ʴ̪��
//=====================================
#define QUESTION_FADE_SYNC	( 6 )	// �V���N��
#define QUESTION_FADE_SCALE_S	( FX32_CONST( 0.40f ) )
#define QUESTION_FADE_SCALE_E	( FX32_CONST( 1.0f ) )
#define QUESTION_CIRCLE_SIZE	( 128 )
#define QUESTION_CIRCLE_Y_OFS	( 48 )
// �߹��ו\���ʒu
#define EV_POKESELECT_POKEGRA_X		( 128 )
#define EV_POKESELECT_POKEGRA_Y		( 96 )

#define QUESTION_CIRCLE_RET_ADD	( -2 )





//-------------------------------------
//	�I�[�g�A�j���I�u�W�F�N�g
//=====================================
typedef struct {
	NNSG3dRenderObj			RenderObj;		// �����_�[�I�u�W�F�N�g
	void*					pResMdl;		// ���f���ް�
	NNSG3dResMdlSet*		pModelSet;		// ���f���Z�b�g
	NNSG3dResMdl*			pModel;			// ���f�����\�[�X
	NNSG3dResTex*			pMdlTex;		// ���f���ɓ\��t����e�N�X�`��
	void*					pResAnm;		// �A�j�����\�[�X
	void*					pOneResAnm;		// 1�؂��������\�[�X
	NNSG3dAnmObj*			pAnmObj;			// �A�j���[�V�����I�u�W�F
	fx32 frame;

	BOOL draw_flag;
	VecFx32 mat;
	VecFx32 scal;
	u16 rota_x;		// x����]
	u16 rota_y;		// y����]
	u16 rota_z;		// z����]
} EV_3D_ANM_OBJ;

//-------------------------------------
//	���샏�[�N
//=====================================
typedef struct {
	s32 data;
	s32 s_data;
	s32 add_data;
	s32 count_max;
} EV_MOVE_PARAM;


//-------------------------------------
//	�J��������^�X�N
//=====================================
typedef struct {
	EV_MOVE_PARAM x_rota;
	EV_MOVE_PARAM dist;
//	EV_MOVE_PARAM target_x;
//	EV_MOVE_PARAM target_y;
	EV_MOVE_PARAM target_z;
	GF_CAMERA_PTR p_camera;
	VecFx32* p_target;
	s32 count;
	BOOL end_flag;
	TCB_PTR	tcb;
} EV_CAMERA_MOVE;

//-------------------------------------
//	�J�[�\������@�i��]����j
//	sin��]�ł��B
//=====================================
typedef struct {
	fx32 num;		// ���̒l
	fx32 r;			// ����l
	int count_max;	// �����ő�l�@1��]�ɂ�����l
	int count;
} EV_ROTA_MOVE_ONE;

//-------------------------------------
//	�J�[�\���I�u�W�F�N�g
//=====================================
typedef struct {
	CLACT_WORK_PTR cursor;
	CLACT_U_RES_OBJ_PTR res_obj[ CLACT_U_RES_MAX ];
	VecFx32 mat;

	TCB_PTR tcb;
	EV_ROTA_MOVE_ONE move_param;
} EV_CURSOR_OBJ;

//-------------------------------------
//	�~�n�E�B���h�E�I�u�W�F�N�g�@����p�����[�^
//=====================================
typedef struct {
	EV_MOVE_PARAM x;
	EV_MOVE_PARAM y;
	EV_MOVE_PARAM scale;
	int count;
	int count_add;
} EV_CIRCLE_MOVE_PARAM;


//-------------------------------------
//	CIRCLE�E�B���h�E�I�u�W�F�N�g
//=====================================
typedef struct {
	SWSP_CHAR_PTR swsp_char;
	SWSP_PLTT_PTR swsp_pltt;
	SWSP_OBJ_PTR  swsp_obj;
	void* swsp_char_buff;
	void* swsp_pltt_buff;
	NNSG2dCharacterData* p_chardata;
	NNSG2dPaletteData* p_plttdata;

	// ����p�����[�^
	EV_CIRCLE_MOVE_PARAM param;
	TCB_PTR tcb;
} EV_CIRCLE_WND;

//-------------------------------------
//	�|�P�����O���t�B�b�N�I�u�W�F�A�j��
//=====================================
typedef struct {
	SOFT_SPRITE* p_soft_sprite;
	
	// ����p�����[�^
	EV_CIRCLE_MOVE_PARAM param;
	TCB_PTR tcb;
} EV_POKEOBJ_ANM;



//-------------------------------------
//	
//	�}�Ӄv���b�N���[�N
//	
//=====================================
typedef struct {
	// ����V�[�P���X
	int seq;

	// �`���ް�
	int draw_seq;		// �`��p�V�[�P���X
	BOOL move_lock;		// ����lock	(�`�摤������)
	int draw_count;
	EV_CAMERA_MOVE camera_move;	// �J��������p�����[�^
	
	// �����ް�
	int now_select_no;
	int select_matrix[ EV_POKESELECT_MONSNUM ][3];
	int select_2_matrix[ EV_POKESELECT_MONSNUM ][2];

	// �`���ް�
	// BGL
	GF_BGL_INI*	p_bg;					// �����Ǘ�
	GF_BGL_BMPWIN* p_bmp_mfont;			// ���C����ʃt�H���g�`��p
	GF_BGL_BMPWIN* p_bmp_subfont[ EV_POKESELECT_MONSNUM ];		// ���C����ʃT�u�t�H���g�`��p
	int local_select_no;
	STRBUF* p_glb_str_buff;


	// �r�b�g�}�b�v�E�B���h�E�ް�
	BMPWIN_DAT bmp_data;
	BMPMENU_WORK* p_yes_no_menu;
	
	// OAM
	CLACT_U_EASYRENDER_DATA	oam_rend;	// oam�����_���[�f�[�^
	CLACT_SET_PTR			clact_set;	// �Z���A�N�^�[�Z�b�g
	CLACT_U_RES_MANAGER_PTR	res_manager[ CLACT_U_RES_MAX ];	// ���\�[�X�}�l�[�W��

	// 3D�|�P����
	SOFT_SPRITE_MANAGER* soft_sprite_man;	// �\�t�g�E�F�A�X�v���C�g�}�l�[�W��
	SOFT_SPRITE*		 soft_sprite[ EV_POKESELECT_MONSNUM ];	// �I�𒆂̃|�P�����̃\�t�g�E�F�A�X�v���C�g
	EV_POKEOBJ_ANM	soft_sprite_anm;	// �A�j���ް�

	// �RD�A�j���[�V�����I�u�W�F
	NNSFndAllocator allocator;
	EV_3D_ANM_OBJ	ev_3d_obj[ POKESELECT_3DOBJ_NUM ];

	// �J����
	GF_CAMERA_PTR p_camera;
	VecFx32 camera_target;

	// �J�[�\���I�u�W�F�N�g
	EV_CURSOR_OBJ	cursor;

	// 3D�G�b�W�}�[�L���O�ް�
	GXRgb edge_marking[ 8 ];

	// �\�t�g�E�F�A�X�v���C�g
	SWSP_SYS_PTR	swsp_sys;
	
	// �~�`�E�B���h�E�I�u�W�F�N�g
	EV_CIRCLE_WND	circle_wnd;

	// �R���t�B�O�f�[�^
	WINTYPE wintype;
	u32 msg_speed;

	u8 msg_index;
	u8 dummy[3];
} EV_POKESELECT_PROC_WORK;



//-----------------------------------------------------------------------------
/**
 *		�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_VBlankFunc( void* work );

static void EV_PokeSelect_FadeInReq( EV_POKESELECT_PROC_WORK* p_work );
static void EV_PokeSelect_FadeOutReq( EV_POKESELECT_PROC_WORK* p_work );
static BOOL EV_PokeSelect_FadeMain( EV_POKESELECT_PROC_WORK* p_work );

static u16 EV_PokeSelect_SelectNoMonsnoGet( u16 no );

#ifdef PM_DEBUG
//#define DEBUG_EV_POKESELE
#endif

#ifdef DEBUG_EV_POKESELE
//-------------------------------------
//	�f�o�b�N�֐�
//=====================================
static void EV_PokeSelect_Deback_Anm( EV_POKESELECT_PROC_WORK* p_psl );
#endif


//-------------------------------------
// ����`�惁�C���֐�
//=====================================
static BOOL EV_PokeSelect_MoveData( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void EV_PokeSelect_MoveDraw( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void EV_PokeSelect_Draw( EV_POKESELECT_PROC_WORK* p_psl );


//-------------------------------------
//	�`��֌W
//=====================================
static void EV_PokeSelect_SetUpDraw( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void EV_PokeSelect_PutDownDraw( void );
static void VramBankSet( void );
static void OamSet( int heap );
static void Setup_3d( EV_POKESELECT_PROC_WORK* p_psl );
static void Putback_3d( void );
static void Bg_setup( GF_BGL_INI* p_bg, int heap );
static void Bg_putdown( GF_BGL_INI* p_bg );
static void Fontbg_bmpwin_make( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Fontbg_bmpwin_delete( EV_POKESELECT_PROC_WORK* p_psl );
static u8 Fontbg_bmpwin_str( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color, u32 wait );
static u8 Fontbg_bmpwin_str_buff( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color, u32 wait, STRBUF** pp_glb_str );
static void Fontbg_bmpwin_strbuff_clear( EV_POKESELECT_PROC_WORK* p_psl );

static void FontSubbg_bmpwin_make( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void FontSubbg_bmpwin_delete( EV_POKESELECT_PROC_WORK* p_psl );
static void FontSubbg_bmpwin_str( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color );
static void FontSubbg_bmpwin_select( EV_POKESELECT_PROC_WORK* p_psl );
static void FontSubbg_bmpwin_clean( EV_POKESELECT_PROC_WORK* p_psl );

static void Fontbg_yesno_bmp_dat_make( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Bg_Back_Set( GF_BGL_INI* p_bg, int heap );
static void Softsprite_init( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Softsprite_delete( EV_POKESELECT_PROC_WORK* p_psl );
static void SwspSprite_init( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void SwspSprite_delete( EV_POKESELECT_PROC_WORK* p_psl );
static void Clact_init( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Clact_delete( EV_POKESELECT_PROC_WORK* p_psl );
static void Camera_init( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Camera_init_param( GF_CAMERA_PTR p_camera, VecFx32* p_target );
static void Camera_delete( EV_POKESELECT_PROC_WORK* p_psl );

static void Ev3dobj_make( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Ev3dobj_delete( EV_POKESELECT_PROC_WORK* p_psl );
static void Ev3dobj_draw( EV_POKESELECT_PROC_WORK* p_psl );

static void Cursor_oam_load( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data, int heap );
static void Cursor_oam_delete( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data );
static void Cursor_clact_add( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data, int heap );
static void Cursor_clact_delete( EV_CURSOR_OBJ* p_data );
static void Cursor_clact_set_draw_flag( EV_CURSOR_OBJ* p_data, BOOL flag );
static void Cursor_clact_set_matrix( EV_CURSOR_OBJ* p_data, int x, int y );

static void Select_matrix_make( EV_POKESELECT_PROC_WORK* p_psl );
static void Select_matrix_set_3dobj( EV_POKESELECT_PROC_WORK* p_psl );

static void DrawMoveSelect( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Draw_move_select_monsball( EV_POKESELECT_PROC_WORK* p_psl );
static void Draw_move_select_cursor( EV_POKESELECT_PROC_WORK* p_psl );

static void DrawMoveQuestion( EV_POKESELECT_PROC_WORK* p_psl, int heap );

static void PokeGra_set( SOFT_SPRITE** p_soft_sprite, EV_POKESELECT_PROC_WORK* p_psl, int monsno );

//3D�I�u�W�F�N�g
static void Init_ev_3d_obj( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int anm_dataidx, int heap, NNSFndAllocator* pallocator );
static void Init_ev_3d_obj_no_anm( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap );
static void Delete_ev_3d_obj( EV_3D_ANM_OBJ* p_obj, NNSFndAllocator* pallocator );
static void Draw_ev_3d_obj( EV_3D_ANM_OBJ* p_obj );
static void Set_ev_3d_obj_draw( EV_3D_ANM_OBJ* p_obj, BOOL flag );
static void Set_ev_3d_obj_mat( EV_3D_ANM_OBJ* p_obj, fx32 x, fx32 y, fx32 z );
static void Set_ev_3d_obj_scal( EV_3D_ANM_OBJ* p_obj, fx32 x, fx32 y, fx32 z );
static void Set_ev_3d_obj_rota( EV_3D_ANM_OBJ* p_obj, u16 x, u16 y, u16 z );
static BOOL Anm_ev_3d_obj( EV_3D_ANM_OBJ* p_obj );
static void Anm_ev_3d_obj_loop( EV_3D_ANM_OBJ* p_obj );
static void Anm_ev_3d_obj_set( EV_3D_ANM_OBJ* p_obj, fx32 anm );
static fx32 Anm_ev_3d_obj_get( EV_3D_ANM_OBJ* p_obj );
static void Load_ev_3d_obj_mdl( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap );
static void Load_ev_3d_obj_anm( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap, NNSFndAllocator* pallocator );

static void CircleWnd_Gra_Init( EV_CIRCLE_WND* p_data, EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void CircleWnd_Gra_Delete( EV_CIRCLE_WND* p_data );
static void CircleWnd_Gra_Draw( EV_CIRCLE_WND* p_data, BOOL flag );
static void CircleWnd_Move_Req( EV_CIRCLE_WND* p_data, fx32 s_x, fx32 e_x, fx32 s_y, fx32 e_y, fx32 s_s, fx32 e_s, int sync );
static void CircleWnd_ReMove_Req( EV_CIRCLE_WND* p_data );
static void CircleWnd_Move_Tcb( TCB_PTR tcb, void* work );
static BOOL CircleWnd_Move_EndCheck( EV_CIRCLE_WND* p_data );

static void QuestionFade_Req( EV_POKESELECT_PROC_WORK* p_psl );
static void QuestionReFade_Req( EV_POKESELECT_PROC_WORK* p_psl );
static BOOL QuestionFade_EndCheck( EV_POKESELECT_PROC_WORK* p_psl );

static void PokeGra_Move_Req( EV_POKEOBJ_ANM* p_data, SOFT_SPRITE* p_soft_sprit, fx32 s_x, fx32 e_x, fx32 s_y, fx32 e_y, fx32 s_s, fx32 e_s, int sync );
static void PokeGra_ReMove_Req( EV_POKEOBJ_ANM* p_data );
static void PokeGra_Move_Tcb( TCB_PTR tcb, void* work );
static BOOL PokeGra_Move_EndCheck( EV_POKEOBJ_ANM* p_data );



//-------------------------------------
//	����֌W
//=====================================
static void Move_select( EV_POKESELECT_PROC_WORK* p_psl );
static void Move_seq_add( EV_POKESELECT_PROC_WORK* p_psl, int no );
static void Move_seq_set( EV_POKESELECT_PROC_WORK* p_psl, int no );
static int Move_seq_get( EV_POKESELECT_PROC_WORK* p_psl );
static void EvMoveInit( EV_MOVE_PARAM* p_data, s32 s_num, s32 e_num, s32 count );
static BOOL EvMoveMain( EV_MOVE_PARAM* p_data, s32 count );
static void EvRotaMoveInit( EV_ROTA_MOVE_ONE* p_data, fx32 r, int count );
static void EvRotaMoveMain( EV_ROTA_MOVE_ONE* p_data );

static void EvCameraMoveReq( EV_CAMERA_MOVE* p_camera_move, GF_CAMERA_PTR p_camera, VecFx32* p_target );
static void EvCameraMoveTcb( TCB_PTR tcb, void* work );
static BOOL EvCameraMoveEndCheck( EV_CAMERA_MOVE* p_camera_move );

static void EvCursorMoveReq( EV_CURSOR_OBJ* p_cursor );
static void EvCursorMoveTcb( TCB_PTR tcb, void* work );
static void EvCursorMoveDelete( EV_CURSOR_OBJ* p_cursor );


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
PROC_RESULT EV_PokeSelect_ProcInit( PROC* proc, int* seq )
{
	EV_POKESELECT_PROC_WORK* p_pls;
	EV_POKESELECT_PEARENT_DATA* p_pearent;
	GF_BGL_SYS_HEADER bg_header;
	BOOL check;

	// ��
//	Snd_DataSetByScene( SND_SCENE_SUB_ZUKAN, 0, 0 );	// �T�E���h�f�[�^���[�h�i�}�Ӂj�iBGM���p���j

	// �q�[�v�쐬
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_EV_POKESELECT, 0x40000 );

	// �}�Ӄ��[�N�쐬
	p_pls = PROC_AllocWork( proc, sizeof(EV_POKESELECT_PROC_WORK), HEAPID_EV_POKESELECT );
	GF_ASSERT( p_pls );
	memset( p_pls, 0, sizeof(EV_POKESELECT_PROC_WORK) );

	// �A���P�[�^�[�쐬
	sys_InitAllocator( &p_pls->allocator, HEAPID_EV_POKESELECT, 32 );

	// �O������̃f�[�^�擾
	p_pearent = PROC_GetParentWork( proc );
	p_pls->wintype = CONFIG_GetWindowType( p_pearent->cp_config );
	p_pls->msg_speed = CONFIG_GetMsgPrintSpeed( p_pearent->cp_config );


	// VramTransferManager������
	initVramTransferManagerHeap( EV_POKESELECT_VRAMTRANSFER_MANAGER_NUM, HEAPID_EV_POKESELECT );

	// VBlank HBlank�ݒ�
	sys_VBlankFuncChange( EV_PokeSelect_VBlankFunc, p_pls );	// VBlank�Z�b�g
	sys_HBlankIntrStop();	//HBlank���荞�ݒ�~

	// �^�b�`�p�l���I�[�g�T���v�����O�J�n
	InitTPSystem();
	check = InitTPNoBuff( 4 );
	GF_ASSERT( check == TP_OK );


	// �`��ݒ�
	EV_PokeSelect_SetUpDraw( p_pls, HEAPID_EV_POKESELECT );


	// BG�ʐݒ�
	p_pls->p_bg = GF_BGL_BglIniAlloc( HEAPID_EV_POKESELECT );
	bg_header.dispMode	= GX_DISPMODE_GRAPHICS;
	bg_header.bgMode	= GX_BGMODE_0;
	bg_header.bgModeSub	= GX_BGMODE_1;
	bg_header.bg0_2Dor3D= GX_BG0_AS_3D;
	GF_BGL_InitBG( &bg_header );
	Bg_setup( p_pls->p_bg, HEAPID_EV_POKESELECT );
	// �\��
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF );

	// ������ʍ쐬
	Fontbg_bmpwin_make( p_pls, HEAPID_EV_POKESELECT );

	// yesno_data�쐬
	Fontbg_yesno_bmp_dat_make( p_pls, HEAPID_EV_POKESELECT );
	FontSubbg_bmpwin_make( p_pls, HEAPID_EV_POKESELECT );

	// �\�t�g�E�F�A�X�v���C�g������
	Softsprite_init( p_pls, HEAPID_EV_POKESELECT );
	SwspSprite_init( p_pls, HEAPID_EV_POKESELECT );

	// �Z���A�N�^�[
	Clact_init( p_pls, HEAPID_EV_POKESELECT );	

	// 3D���f������
	Ev3dobj_make( p_pls, HEAPID_EV_POKESELECT );

	// �J�����쐬
	Camera_init( p_pls, HEAPID_EV_POKESELECT );

	// �I�����W�ݒ�
	Select_matrix_make( p_pls );

	// 3D�I�u�W�F�N�g�ɍ��W��ݒ�
	Select_matrix_set_3dobj( p_pls );

	// �J�[�\��������
	Cursor_oam_load( p_pls, &p_pls->cursor, HEAPID_EV_POKESELECT );
	Cursor_clact_add( p_pls, &p_pls->cursor, HEAPID_EV_POKESELECT );
	EvCursorMoveReq( &p_pls->cursor );

	// �T�[�N���E�B���h�E������
	CircleWnd_Gra_Init( &p_pls->circle_wnd, p_pls, HEAPID_EV_POKESELECT );


	// ���֌W
	Snd_DataSetByScene( SND_SCENE_SUB_FIRSTPOKE, 0, 0 );	// sound_load(�ŏ��̃|�P�����I��)(BGM���p��)

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
PROC_RESULT EV_PokeSelect_ProcMain( PROC* proc, int* seq )
{
	EV_POKESELECT_PROC_WORK* p_pls = PROC_GetWork( proc );
	BOOL ret;
	short num = 0x08c3;

	switch( *seq ){
	// �t�F�[�h�C��
	case 0:
		EV_PokeSelect_FadeInReq( p_pls );
		GX_LoadBGPltt( &num, 0, sizeof(short) );
		(*seq)++;
		break;
	case 1:
		if( EV_PokeSelect_FadeMain( p_pls ) ){
			WIPE_ResetWndMask( WIPE_DISP_MAIN );
			WIPE_ResetWndMask( WIPE_DISP_SUB );
			(*seq)++;
		}
		break;

		
	//-------------------------------------
	//	
	// ���C������	
	//	
	//=====================================
	case 2:
		ret = EV_PokeSelect_MoveData( p_pls, HEAPID_EV_POKESELECT );
		EV_PokeSelect_MoveDraw( p_pls, HEAPID_EV_POKESELECT );

		// �I���`�F�b�N
		if( ret == TRUE ){
			(*seq)++;
		}
		break;


	// �t�F�[�h�A�E�g
	case 3:
		EV_PokeSelect_FadeOutReq( p_pls );
		(*seq)++;
		break;
	case 4:
		if( EV_PokeSelect_FadeMain( p_pls ) ){
			WIPE_ResetWndMask( WIPE_DISP_MAIN );
			WIPE_ResetWndMask( WIPE_DISP_SUB );

			return PROC_RES_FINISH;
		}
		break;
	}

	//�@�`�揈��
	EV_PokeSelect_Draw( p_pls );

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
PROC_RESULT EV_PokeSelect_ProcEnd( PROC* proc, int* seq )
{
	EV_POKESELECT_PROC_WORK* p_pls = PROC_GetWork( proc );
	EV_POKESELECT_PEARENT_DATA* p_pearent =PROC_GetParentWork( proc );
	BOOL check;

	sys_VBlankFuncChange( NULL, NULL );	// VBlank�Z�b�g

	// �e�ɑI�������|�P�������ް��ݒ肷��
	p_pearent->select_monsno = EV_PokeSelect_SelectNoMonsnoGet( p_pls->now_select_no );

	// �^�b�`�p�l���T���v�����O�I��
	check = StopTP();
	GF_ASSERT( check == TP_OK );

	// CIRCLE�E�B���h�E�ް��j��
	CircleWnd_Gra_Delete( &p_pls->circle_wnd );

	// �J�[�\���j��
	Cursor_clact_delete( &p_pls->cursor );
	Cursor_oam_delete( p_pls, &p_pls->cursor );
	EvCursorMoveDelete( &p_pls->cursor );

	// �J�����j��
	Camera_delete( p_pls );

	// 3D���f���j��
	Ev3dobj_delete( p_pls );
	
	// �Z���A�N�^�[�j��
	Clact_delete( p_pls );
	
	// �\�t�g�E�F�A�X�v���C�g�j��
	Softsprite_delete( p_pls );
	SwspSprite_delete( p_pls );
	
	// ������ʔj��
	Fontbg_bmpwin_delete( p_pls );
	FontSubbg_bmpwin_delete( p_pls );
	
	// BG�j��
	Bg_putdown( p_pls->p_bg );

	// BG�V�X�e��
	sys_FreeMemoryEz( p_pls->p_bg );
	
	// �\���f�[�^�j��
	EV_PokeSelect_PutDownDraw();

	// VramTransferManager�j��
	DellVramTransferManager();

	// ���[�N�j��
	PROC_FreeWork( proc );

	// �q�[�v�j��
	sys_DeleteHeap( HEAPID_EV_POKESELECT );

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
static void EV_PokeSelect_VBlankFunc( void* work )
{
	EV_POKESELECT_PROC_WORK* p_psl = work;

	// �����_���[OAM�]��
	REND_OAMTrans();

	GF_BGL_VBlankFunc( p_psl->p_bg );

	// �\�t�g�E�F�A�X�v���C�g
	SoftSpriteTextureTrans( p_psl->soft_sprite_man );

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
static void EV_PokeSelect_FadeInReq( EV_POKESELECT_PROC_WORK* p_work )
{
	WIPE_SYS_Start(
			WIPE_PATTERN_WMS,
			WIPE_TYPE_FADEIN,
			WIPE_TYPE_FADEIN,
			WIPE_FADE_BLACK,
			EV_POKESELECT_PROC_FADE_DIV,
			EV_POKESELECT_PROC_FADE_SYNC,
			HEAPID_EV_POKESELECT );
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
static void EV_PokeSelect_FadeOutReq( EV_POKESELECT_PROC_WORK* p_work )
{
	WIPE_SYS_Start(
			WIPE_PATTERN_WMS,
			WIPE_TYPE_FADEOUT,
			WIPE_TYPE_FADEOUT,
			WIPE_FADE_BLACK,
			EV_POKESELECT_PROC_FADE_DIV,
			EV_POKESELECT_PROC_FADE_SYNC,
			HEAPID_EV_POKESELECT );
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
static BOOL EV_PokeSelect_FadeMain( EV_POKESELECT_PROC_WORK* p_work )
{
	return WIPE_SYS_EndCheck();
}


//----------------------------------------------------------------------------
/**
 *	@brief	�`��Z�b�g�A�b�v
 *
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_SetUpDraw( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	// �o���N�Z�b�g�A�b�v
	VramBankSet();
	
	// oam�֌W�Z�b�g�A�b�v
	OamSet( heap );


	// 3D��
	Setup_3d( p_psl );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��v�b�g�_�E��
 *
 *	@param	none
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_PutDownDraw( void )
{
	// �����_���[���LOAM�}�l�[�W���j��
	REND_OAM_Delete();
	
	// �L�����N�^�f�[�^�j��
	DeleteCharManager();
	// �p���b�g�f�[�^�j��
	DeletePlttManager();

	// 3D��
	Putback_3d();
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
 *	@brief	3D�ʐݒ�
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void Setup_3d( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;
	
	// NitroSystem:�R�c�G���W���̏�����
	NNS_G3dInit();
	// �}�g���N�X�X�^�b�N�̏�����
    G3X_InitMtxStack();

	// �e��`�惂�[�h�̐ݒ�(�V�F�[�h���A���`�G�C���A�X��������)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
	G3X_AlphaTest(FALSE, 0);	// �A���t�@�e�X�g�@�@�I�t
	G3X_AlphaBlend(TRUE);		// �A���t�@�u�����h�@�I��

	// �G�b�W�}�[�L���O
	G3X_EdgeMarking(TRUE);
	for( i=0; i<8; i++ ){
		p_psl->edge_marking[i] = GX_RGB( 4, 4, 4 );
	}
	G3X_SetEdgeColorTable( p_psl->edge_marking );

	
	// �N���A�J���[�̐ݒ�
    G3X_SetClearColor(GX_RGB(31, 31, 16),	// clear color
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
static void Putback_3d( void )
{
	NNS_GfdResetFrmTexVramState();
	NNS_GfdResetFrmPlttVramState();
}


//----------------------------------------------------------------------------
/**
 *	@brief	BG�ʐݒ�
 *
 *	@param	p_bg	�����ް�
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Bg_setup( GF_BGL_INI* p_bg, int heap )
{
	// BG0�̗D�揇��
	G2_SetBG0Priority( 1 );
	
	// ���C����� BG1��		�����񏑂����ݖ�
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, GF_BGL_FRAME1_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, GF_BGL_FRAME1_M );
	}

	// ���C����� BG2��		�w�i��
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x0c000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, GF_BGL_FRAME2_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, GF_BGL_FRAME2_M );
	}

	// ���C����� BG3��		�T�u������
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, GF_BGL_FRAME3_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME3_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, GF_BGL_FRAME3_M );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG�ʐݒ�j��
 *
 *	@param	p_bg 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Bg_putdown( GF_BGL_INI* p_bg )
{
	GF_BGL_BGControlExit( p_bg, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( p_bg, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( p_bg, GF_BGL_FRAME3_M );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E�쐬
 *
 *	@param	p_bmp_mfont	�r�b�g�}�b�v�E�B���h�E
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Fontbg_bmpwin_make( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	p_psl->p_bmp_mfont = GF_BGL_BmpWinAllocGet( heap, 1 );
	GF_BGL_BmpWinInit( p_psl->p_bmp_mfont );
	
	// �r�b�g�}�b�v�E�B���h�E�o�^
	GF_BGL_BmpWinAdd( p_psl->p_bg, p_psl->p_bmp_mfont,
			GF_BGL_FRAME1_M, BG_FONTBMP_X, BG_FONTBMP_Y, BG_FONTBMP_CX, BG_FONTBMP_CY, BG_FONT_STR_COLOR, TALK_WIN_CGX_SIZ + 1 );

	// �N���[��
	GF_BGL_BmpWinDataFill( p_psl->p_bmp_mfont, 15 );

	// �g��`��
	TalkWinGraphicSet( p_psl->p_bg, GF_BGL_FRAME1_M, BG_FONT_CG_OFS, BG_FONT_COLOR, p_psl->wintype, heap );

	// ��b�t�H���g�p���b�g�ǂݍ���
	ArcUtil_PalSet( ARC_EV_POKESELECT_GRA, NARC_ev_pokeselect_font_talk_NCLR, PALTYPE_MAIN_BG, BG_FONT_STR_COLOR * 32, 32, heap );

	BmpTalkWinWrite( p_psl->p_bmp_mfont, WINDOW_TRANS_ON, BG_FONT_CG_OFS, BG_FONT_COLOR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E�j��
 *
 *	@param	p_bmp_mfont 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Fontbg_bmpwin_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	GF_BGL_BmpWinDel( p_psl->p_bmp_mfont );
	sys_FreeMemoryEz( p_psl->p_bmp_mfont );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�X�v���C�g�}�l�[�W��������
 *	
 *	@param	p_psl		���[�N
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Softsprite_init( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	NNSGfdTexKey	texKey;
	NNSGfdPlttKey	plttKey;
	int i;

	// �|�P�����f�[�^�]���̈��Vram���m�ہ��]���A�h���X�ƃT�C�Y��ݒ�
	p_psl->soft_sprite_man = SoftSpriteInit( heap );	
	texKey = NNS_GfdAllocTexVram(POKEGRA_TEX_SIZE, FALSE, 0);
	plttKey = NNS_GfdAllocPlttVram(POKEGRA_PLTT_SIZE, FALSE, NNS_GFD_ALLOC_FROM_LOW);
	SoftSpriteTextureTransParamSet( 
			p_psl->soft_sprite_man,
			NNS_GfdGetTexKeyAddr(texKey),
			NNS_GfdGetTexKeySize(texKey) );
	SoftSpritePaletteTransParamSet( 
			p_psl->soft_sprite_man,
			NNS_GfdGetPlttKeyAddr(plttKey),
			NNS_GfdGetPlttKeySize(plttKey) );

	//������
	PokeGra_set( &p_psl->soft_sprite[0], p_psl, MONSNO_NAETORU );
	PokeGra_set( &p_psl->soft_sprite[1], p_psl, MONSNO_HIKOZARU );
	PokeGra_set( &p_psl->soft_sprite[2], p_psl, MONSNO_POTTYAMA );

	// ���ꂼ���\��
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		SoftSpriteParaSet( p_psl->soft_sprite[ i ], SS_PARA_VANISH, 1 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�o�^
 *
 *	@param	p_soft_sprite
 *	@param	p_psl
 *	@param	monsno 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeGra_set( SOFT_SPRITE** p_soft_sprite, EV_POKESELECT_PROC_WORK* p_psl, int monsno )
{
	SOFT_SPRITE_ARC arc_data;
	int sex;

	sex = PokeSexGetMonsNo( monsno, 0 );
	//�Ō�̈����́AFormNo�ƌ������ł� by soga 2006.05.01
	PokeGraArcDataGet( &arc_data, monsno, sex, PARA_FRONT, PARA_NORMAL, NULL, NULL );
	*p_soft_sprite = SoftSpriteAdd( 
			p_psl->soft_sprite_man,
			&arc_data,
			EV_POKESELECT_POKEGRA_X, EV_POKESELECT_POKEGRA_Y, 1023,
			0, NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�X�v���C�g�}�l�[�W���j��
 *
 *	@param	p_psl 
  *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Softsprite_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;
	
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){

		if( p_psl->soft_sprite[i] ){
			SoftSpriteDel( p_psl->soft_sprite[i] );
		}
	}
	
	// �|�P�����`��X�v���C�g�f�[�^�j��
	SoftSpriteEnd( p_psl->soft_sprite_man );
}

//----------------------------------------------------------------------------
/**
 *	@brief	swsp�V�X�e���쐬
 *
 *	@param	p_psl
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void SwspSprite_init( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	SWSP_SYSDATA swsp_sys_data = {
		SWSP_OBJNUM,
		SWSP_CHARNUM,			
		SWSP_PLTTNUM,
		0
	};
	swsp_sys_data.heap = heap;

	p_psl->swsp_sys = SWSP_SysInit( &swsp_sys_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	swsp�V�X�e���j��
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void SwspSprite_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	// �\�t�g�E�F�A�X�v���C�g
	SWSP_SysDelete( p_psl->swsp_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[������
 *
 *	@param	p_psl		���[�N
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Clact_init( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	// �Z���A�N�^�[�Z�b�g
	p_psl->clact_set = CLACT_U_SetEasyInit( CLACT_SET_WORK_NUM, &p_psl->oam_rend, heap );

	// �Z���A�N�^�[�p���\�[�X�Ǘ��V�X�e��
	p_psl->res_manager[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerInit( CLACT_RES_DATA_TBL_NUM, CLACT_U_CHAR_RES, heap );
	p_psl->res_manager[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerInit( CLACT_RES_DATA_TBL_NUM, CLACT_U_PLTT_RES, heap );
	p_psl->res_manager[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerInit( CLACT_RES_DATA_TBL_NUM, CLACT_U_CELL_RES, heap );
	p_psl->res_manager[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerInit( CLACT_RES_DATA_TBL_NUM, CLACT_U_CELLANM_RES, heap );

	// OBJON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�j��
 *
 *	@param	p_psl 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Clact_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	// �Z���A�N�^�[�Z�b�g
	CLACT_DestSet( p_psl->clact_set );

	// �Z���A�N�^�[�p���\�[�X�Ǘ��V�X�e��
	CLACT_U_ResManagerDelete( p_psl->res_manager[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerDelete( p_psl->res_manager[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerDelete( p_psl->res_manager[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerDelete( p_psl->res_manager[ CLACT_U_CELLANM_RES ] );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�RD�I�u�W�F�N�g�ݒ�
 *
 *	@param	p_obj			�I�u�W�F�N�g�|�C���^
 *	@param	mdl_dataidx		���f���A�[�J�C�u�ް����ޯ��
 *	@param	anm_dataidx		���f���A�j���A�[�J�C�u�ް����ޯ��
 *	@param	heap			�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Init_ev_3d_obj( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int anm_dataidx, int heap, NNSFndAllocator* pallocator )
{
	memset( p_obj, 0, sizeof(EV_3D_ANM_OBJ) );
	Load_ev_3d_obj_mdl( p_obj, mdl_dataidx, heap );
	Load_ev_3d_obj_anm( p_obj, anm_dataidx, heap, pallocator );

	Set_ev_3d_obj_scal( p_obj, FX32_ONE, FX32_ONE, FX32_ONE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���̂Ȃ��I�u�W�F�N�g�̓o�^
 *
 *	@param	p_obj			�I�u�W�F�N�g
 *	@param	mdl_dataidx		���f���ް����ޯ��
 *	@param	heap			�q�[�v
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Init_ev_3d_obj_no_anm( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap )
{
	memset( p_obj, 0, sizeof(EV_3D_ANM_OBJ) );
	Load_ev_3d_obj_mdl( p_obj, mdl_dataidx, heap );
	Set_ev_3d_obj_scal( p_obj, FX32_ONE, FX32_ONE, FX32_ONE );
}
// ���f���ް��ǂݍ��݁��ݒ�
static void Load_ev_3d_obj_mdl( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap )
{
	// ���f���ް��ǂݍ���
	p_obj->pResMdl = ArcUtil_Load( ARC_EV_POKESELECT_GRA, mdl_dataidx, FALSE, heap, ALLOC_TOP );

	// ���f���ް��擾
	p_obj->pModelSet	= NNS_G3dGetMdlSet( p_obj->pResMdl );
	p_obj->pModel		= NNS_G3dGetMdlByIdx( p_obj->pModelSet, 0 );
	p_obj->pMdlTex		= NNS_G3dGetTex( p_obj->pResMdl );
	
	// ���f���ް���]��
	LoadVRAMTexture( p_obj->pMdlTex );
	BindTexture( p_obj->pResMdl, p_obj->pMdlTex );

	// �����_�[�I�u�W�F�N�g�ɓo�^
	NNS_G3dRenderObjInit( &p_obj->RenderObj, p_obj->pModel );
}
// �A�j���ް��ǂݍ��݁��ݒ�		load_ev_3d_obj_mdl�̌�ɌĂԕK�v����
static void Load_ev_3d_obj_anm( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap, NNSFndAllocator* pallocator )
{
	// �A�j���ް��ǂݍ���
	p_obj->pResAnm = ArcUtil_Load( ARC_EV_POKESELECT_GRA, mdl_dataidx, FALSE, heap, ALLOC_TOP );

	//���\�[�X�擾
	p_obj->pOneResAnm = NNS_G3dGetAnmByIdx(p_obj->pResAnm,0);

	// �A�j���I�u�W�F�̃������m��
	p_obj->pAnmObj = NNS_G3dAllocAnmObj( 
			pallocator,
			p_obj->pOneResAnm,
			p_obj->pModel );

	// �A�j���I�u�W�F������
	NNS_G3dAnmObjInit(
		p_obj->pAnmObj,
		p_obj->pOneResAnm,
		p_obj->pModel,
		p_obj->pMdlTex );

	// �����_�[�I�u�W�F�N�g�ɓo�^
	NNS_G3dRenderObjAddAnmObj( &p_obj->RenderObj, p_obj->pAnmObj );
}

//----------------------------------------------------------------------------
/**
 *	@brief	3D�I�u�W�F�N�g�̔j��
 *
 *	@param	p_obj	�I�u�W�F�N�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Delete_ev_3d_obj( EV_3D_ANM_OBJ* p_obj, NNSFndAllocator* pallocator )
{
	// �S���\�[�X�j��
	if(p_obj->pResMdl){
		sys_FreeMemoryEz( p_obj->pResMdl );
	}
	if(p_obj->pResAnm){
		NNS_G3dFreeAnmObj( pallocator, p_obj->pAnmObj );
		sys_FreeMemoryEz( p_obj->pResAnm );
	}

	memset( p_obj, 0, sizeof(EV_3D_ANM_OBJ) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�揈��
 *
 *	@param	p_obj 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Draw_ev_3d_obj( EV_3D_ANM_OBJ* p_obj )
{
	MtxFx33 mtx;
	MtxFx33 calc_mtx;


	// ��]�s��쐬
	MTX_Identity33( &mtx );
	MTX_RotX33( &calc_mtx, FX_SinIdx( p_obj->rota_x ), FX_CosIdx( p_obj->rota_x ) );
	MTX_Concat33( &calc_mtx, &mtx, &mtx );
	MTX_RotY33( &calc_mtx, FX_SinIdx( p_obj->rota_y ), FX_CosIdx( p_obj->rota_y ) );
	MTX_Concat33( &calc_mtx, &mtx, &mtx );
	MTX_RotZ33( &calc_mtx, FX_SinIdx( p_obj->rota_z ), FX_CosIdx( p_obj->rota_z ) );
	MTX_Concat33( &calc_mtx, &mtx, &mtx );

	
	if( p_obj->draw_flag ){
		simple_3DModelDraw( &p_obj->RenderObj, &p_obj->mat, &mtx, &p_obj->scal );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`��t���O�̐ݒ�
 *
 *	@param	p_obj	�I�u�W�F�N�g
 *	@param	flag	�t���O		TRUE�`�� 
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Set_ev_3d_obj_draw( EV_3D_ANM_OBJ* p_obj, BOOL flag )
{
	p_obj->draw_flag = flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���W�ݒ�
 *	
 *	@param	p_obj	�I�u�W�F�N�g
 *	@param	x		�����W
 *	@param	y		�����W
 *	@param	z		�����W
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Set_ev_3d_obj_mat( EV_3D_ANM_OBJ* p_obj, fx32 x, fx32 y, fx32 z )
{
	p_obj->mat.x = x;
	p_obj->mat.y = y;
	p_obj->mat.z = z;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�g�k�l
 *
 *	@param	p_obj	�I�u�W�F�N�g
 *	@param	x		X�g��l
 *	@param	y		Y�g��l
 *	@param	z		Z�g��l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Set_ev_3d_obj_scal( EV_3D_ANM_OBJ* p_obj, fx32 x, fx32 y, fx32 z )
{
	p_obj->scal.x = x;
	p_obj->scal.y = y;
	p_obj->scal.z = z;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��]�p�x�ݒ�
 *
 *	@param	p_obj	�I�u�W�F�N�g
 *	@param	x	������]
 *	@param	y	������]
 *	@param	z	������]
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Set_ev_3d_obj_rota( EV_3D_ANM_OBJ* p_obj, u16 x, u16 y, u16 z )
{
	p_obj->rota_x = x;
	p_obj->rota_y = y;
	p_obj->rota_z = z;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���[�V����
 *
 *	@param	p_obj 
 *
 *	@return	TRUE	�I��
 */
//-----------------------------------------------------------------------------
static BOOL Anm_ev_3d_obj( EV_3D_ANM_OBJ* p_obj )
{
	fx32 end_frame = NNS_G3dAnmObjGetNumFrame( p_obj->pAnmObj );
	BOOL ret;
	
	if( (p_obj->frame + FX32_ONE) < end_frame ){
		p_obj->frame += FX32_ONE;
		ret = FALSE;
	}else{
		p_obj->frame = end_frame;
		ret = TRUE;
	}
	NNS_G3dAnmObjSetFrame( p_obj->pAnmObj, p_obj->frame );

	return ret;
}
static void Anm_ev_3d_obj_loop( EV_3D_ANM_OBJ* p_obj )
{
	fx32 end_frame = NNS_G3dAnmObjGetNumFrame( p_obj->pAnmObj );
	
	p_obj->frame = (p_obj->frame + FX32_ONE) % end_frame;

	NNS_G3dAnmObjSetFrame( p_obj->pAnmObj, p_obj->frame );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���[�V�������ݒ�
 *
 *	@param	p_obj
 *	@param	anm			�ڰѐ�
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Anm_ev_3d_obj_set( EV_3D_ANM_OBJ* p_obj, fx32 anm )
{
	p_obj->frame = anm;
	NNS_G3dAnmObjSetFrame( p_obj->pAnmObj, anm );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A�j���[�V�����ڰѐ��擾
 *
 *	@param	p_obj 
 *
 *	@return	�ڰѐ�	
 */
//-----------------------------------------------------------------------------
static fx32 Anm_ev_3d_obj_get( EV_3D_ANM_OBJ* p_obj )
{
	return p_obj->frame;
;
}

//----------------------------------------------------------------------------
/**
 *	@brief	3d�I�u�W�F���쐬����
 *
 *	@param	p_psl	���[�N
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Ev3dobj_make( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	int i;

	// AUTO�A�j���f��
	Init_ev_3d_obj( &p_psl->ev_3d_obj[ POKESELECT_AUTOANM ],
			NARC_ev_pokeselect_psel_all_nsbmd, NARC_ev_pokeselect_psel_all_nsbca,
			heap, &p_psl->allocator );
	Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_AUTOANM ], TRUE );

	// ���΂񃂃f��
	Init_ev_3d_obj_no_anm( &p_psl->ev_3d_obj[ POKESELECT_BAG ],
			NARC_ev_pokeselect_psel_trunk_nsbmd, heap );
	Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BAG ], FALSE );

	// �ݽ���{�[�����f��
	for( i=POKESELECT_BALL_LEFT; i<=POKESELECT_BALL_RIGHT; i++ ){
		Init_ev_3d_obj( &p_psl->ev_3d_obj[ i ],
				NARC_ev_pokeselect_psel_mb_a_nsbmd + (i-POKESELECT_BALL_LEFT) * 2,
				NARC_ev_pokeselect_psel_mb_a_nsbca + (i-POKESELECT_BALL_LEFT) * 2,
				heap, &p_psl->allocator );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ i ], FALSE );
	}

	// �n�`���f��
	Init_ev_3d_obj_no_anm( &p_psl->ev_3d_obj[ POKESELECT_GROUND ],
			NARC_ev_pokeselect_pmsel_bg_nsbmd, heap );
	Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_GROUND ], TRUE );
	
	Set_ev_3d_obj_mat( &p_psl->ev_3d_obj[ POKESELECT_GROUND ],
			EV_POKESELECT_DRAW_GRUND_X,
			EV_POKESELECT_DRAW_GRUND_Y,
			EV_POKESELECT_DRAW_GRUND_Z);
	Set_ev_3d_obj_scal( &p_psl->ev_3d_obj[ POKESELECT_GROUND ],
			EV_POKESELECT_DRAW_GRUND_SCA_X,
			EV_POKESELECT_DRAW_GRUND_SCA_Y,
			EV_POKESELECT_DRAW_GRUND_SCA_Z);
	Set_ev_3d_obj_rota(  &p_psl->ev_3d_obj[ POKESELECT_GROUND ],
			EV_POKESELECT_DRAW_GRUND_ROTA_X,
			EV_POKESELECT_DRAW_GRUND_ROTA_Y,
			EV_POKESELECT_DRAW_GRUND_ROTA_Z);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�RD�I�u�W�F�j��
 *
 *	@param	p_psl
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Ev3dobj_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;

	for( i=0; i<POKESELECT_3DOBJ_NUM; i++ ){
		Delete_ev_3d_obj( &p_psl->ev_3d_obj[ i ], &p_psl->allocator );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	3D�I�u�W�F�N�g�`�揈��
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Ev3dobj_draw( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;

	// ���C�g�ƃA���r�G���g
	NNS_G3dGlbLightVector( 0, 0, -FX32_ONE, 0 );
	NNS_G3dGlbLightColor( 0, GX_RGB( 31,31,31 ) );
	NNS_G3dGlbMaterialColorDiffAmb( GX_RGB( 31,31,31 ), GX_RGB( 31,31,31 ), FALSE );
	NNS_G3dGlbMaterialColorSpecEmi( GX_RGB( 31,31,31 ), GX_RGB( 31,31,31 ), FALSE );
	
	
	for( i=0; i<POKESELECT_3DOBJ_NUM; i++ ){
		Draw_ev_3d_obj( &p_psl->ev_3d_obj[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	���상�C��
 *
 *	@param	p_psl 
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�Â�
 */
//-----------------------------------------------------------------------------
static BOOL EV_PokeSelect_MoveData( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	if( p_psl->move_lock == TRUE ){
		return FALSE;
	}
	
	switch( Move_seq_get( p_psl ) ){
	case POKESELECT_SEQ_INIT:
		break;

	case POKESELECT_SEQ_WAIT:
		break;

	case POKESELECT_SEQ_AUTOANM:		// AUTO�A�j��
		break;
		
	case POKESELECT_SEQ_SELECT:		// �I��
		Move_select( p_psl );
		if( sys.trg & PAD_BUTTON_A ){
			Move_seq_add( p_psl, 1 );

			Snd_SePlay( EV_POKESELE_SND_DECIDE );
		}

#ifdef DEBUG_EV_POKESELE
		// �f�o�b�N
		EV_PokeSelect_Deback_Anm( p_psl );
#endif
		break;
		
	case POKESELECT_SEQ_QUESTION:	// �m�F
		break;

	case POKESELECT_SEQ_END:
		return TRUE;

	default:
		break;
	}
	return FALSE;
}

#ifdef DEBUG_EV_POKESELE
static void EV_PokeSelect_Deback_Anm( EV_POKESELECT_PROC_WORK* p_psl )
{
	CAMERA_ANGLE angle;
	
	// �f�o�b�N�@�\
	if( sys.trg & PAD_BUTTON_B ){
		Move_seq_set( p_psl, 0 );
		Anm_ev_3d_obj_set( &p_psl->ev_3d_obj[POKESELECT_AUTOANM], 0 );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_AUTOANM ], TRUE );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BAG ], FALSE );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_LEFT ], FALSE );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_CENTER ], FALSE );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_RIGHT ], FALSE );

		angle.x = CAMERA_ANGLE_X;
		angle.y = CAMERA_ANGLE_Y;
		angle.z = CAMERA_ANGLE_Z;
		GFC_SetCameraAngleRev( &angle, p_psl->p_camera );
		GFC_SetCameraDistance( CAMERA_DISTANCE, p_psl->p_camera );
		p_psl->camera_target.z = CAMERA_TARGET_Z;

		// �J�[�\�������킹��
		Cursor_clact_set_draw_flag( &p_psl->cursor, FALSE );

		// �N���[��
		GF_BGL_BmpWinOff( p_psl->p_bmp_mfont );
		FontSubbg_bmpwin_clean( p_psl );
	}
}
#endif

//----------------------------------------------------------------------------
/**
 *	@brief	�`�擮�상�C��
 *
 *	@param	p_psl 
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_MoveDraw( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	
	switch( Move_seq_get( p_psl ) ){
	case POKESELECT_SEQ_INIT:
		// ����lock����
		p_psl->move_lock = TRUE;
		p_psl->draw_count = POKESELECT_MONNSUTA_START_WAIT;
		Move_seq_add( p_psl, 1 );
		//�������ݒ肷��
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ, BG_FONTSUBBMP_ALPHA, 16 - BG_FONTSUBBMP_ALPHA );
		break;

	case POKESELECT_SEQ_WAIT:
		p_psl->draw_count --;
		if( p_psl->draw_count < 0 ){
			Move_seq_add( p_psl, 1 );

			Snd_SePlay( EV_POKESELE_SND_BAGOPEN );
		}
		break;

	case POKESELECT_SEQ_AUTOANM:		// AUTO�A�j��
		// �A�j���[�V����������
		// �A�j���I����I����
		if( Anm_ev_3d_obj( &p_psl->ev_3d_obj[POKESELECT_AUTOANM] ) ){
			// �����������A�΂�΂�ȃI�u�W�F���o��
			Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_AUTOANM ], FALSE );
			Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BAG ], TRUE );
			Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_LEFT ], TRUE );
			Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_CENTER ], TRUE );
			Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_RIGHT ], TRUE );

			Move_seq_add( p_psl, 1 );
		}
		break;
		
	case POKESELECT_SEQ_SELECT:		// �I��
		DrawMoveSelect( p_psl, heap );
		break;
		
	case POKESELECT_SEQ_QUESTION:	// �m�F
		DrawMoveQuestion( p_psl, heap );
		break;

	case POKESELECT_SEQ_END:
		G2_BlendNone();
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�`�惁�C��
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_Draw( EV_POKESELECT_PROC_WORK* p_psl )
{
	//�R�c�`��J�n
	GF_G3X_Reset();

	NNS_G3dGePushMtx();
	{
		NNS_G3dGeFlushBuffer();

		// �\�t�g�E�F�A�X�v���C�g�̕`��
		// �J�����Z�b�g�A�b�v
		NNS_G2dSetupSoftwareSpriteCamera();
		// �\�t�g�E�F�A�X�v���C�g�`��
		SoftSpriteMain( p_psl->soft_sprite_man );
		SWSP_SysDraw( p_psl->swsp_sys );
	}
	NNS_G3dGePopMtx(1);


	NNS_G3dGePushMtx();
	{
		// �J�����ݒ�
		GFC_CameraLookAt();

		//�@���f���̕`��
		Ev3dobj_draw( p_psl );
	}
	NNS_G3dGePopMtx(1);
	

	/* �W�I���g���������_�����O�G���W���֘A�������̃X���b�v */
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);

	// �Z���A�N�^�[�`��
	CLACT_Draw( p_psl->clact_set );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�����쐬��������
 *
 *	@param	p_psl		���[�N
 *	@param	heap		�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Camera_init( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	// �J�����A���b�N
	p_psl->p_camera = GFC_AllocCamera( heap );

	// ������
	Camera_init_param( p_psl->p_camera, &p_psl->camera_target );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J���������ݒ�
 *
 *	@param	p_camera	�J����
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Camera_init_param( GF_CAMERA_PTR p_camera, VecFx32* p_target )
{
	CAMERA_ANGLE angle;
	VecFx32 up;
	
	p_target->x = CAMERA_TARGET_X;
	p_target->y = CAMERA_TARGET_Y;
	p_target->z = CAMERA_TARGET_Z;

	angle.x = CAMERA_ANGLE_X;
	angle.y = CAMERA_ANGLE_Y;
	angle.z = CAMERA_ANGLE_Z;

	
	GFC_InitCameraTDA( 
			p_target, CAMERA_DISTANCE,
			&angle, CAMERA_PEARCE,
			GF_CAMERA_PERSPECTIV,
			TRUE,	
			p_camera
			);

	up.x = 0;
	up.y = FX32_ONE;
	up.z = 0;
	GFC_SetCamUp( &up, p_camera );
	
	GFC_AttachCamera( p_camera );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�����j��
 *
 *	@param	p_psl		���[�N
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Camera_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	GFC_FreeCamera( p_psl->p_camera );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���W�Z���N�g
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Select_matrix_make( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;
	
	// ���W�ʒu���[�N�쐬
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		switch( i ){
		case POKESELECT_LEFT_BALL:
			p_psl->select_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_LEFT_X;
			p_psl->select_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_LEFT_Y;
			p_psl->select_matrix[ i ][2] = EV_POKESELECT_DRAW_MAT_BALL_LEFT_Z;
			break;
		case POKESELECT_CENTER_BALL:
			p_psl->select_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_CENTER_X;
			p_psl->select_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_CENTER_Y;
			p_psl->select_matrix[ i ][2] = EV_POKESELECT_DRAW_MAT_BALL_CENTER_Z;
			break;
		case POKESELECT_RIGHT_BALL:
			p_psl->select_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_RIGHT_X;
			p_psl->select_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_RIGHT_Y;
			p_psl->select_matrix[ i ][2] = EV_POKESELECT_DRAW_MAT_BALL_RIGHT_Z;
			break;
		}
	}

	// 2d���W
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		switch( i ){
		case POKESELECT_LEFT_BALL:
			p_psl->select_2_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_LEFT_2X;
			p_psl->select_2_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_LEFT_2Y;
			break;
		case POKESELECT_CENTER_BALL:
			p_psl->select_2_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_CENTER_2X;
			p_psl->select_2_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_CENTER_2Y;
			break;
		case POKESELECT_RIGHT_BALL:
			p_psl->select_2_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_RIGHT_2X;
			p_psl->select_2_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_RIGHT_2Y;
			break;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	3d�I�u�W�F�̍��W��ݒ�
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Select_matrix_set_3dobj( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		Set_ev_3d_obj_mat( &p_psl->ev_3d_obj[i + POKESELECT_BALL_LEFT], 
				p_psl->select_matrix[i][0] << FX32_SHIFT,
				p_psl->select_matrix[i][1] << FX32_SHIFT,
				p_psl->select_matrix[i][2] << FX32_SHIFT );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�Z���N�g�|�P������ύX���铮��
 *
 *	@param	p_psl	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Move_select( EV_POKESELECT_PROC_WORK* p_psl )
{
	if( sys.trg & PAD_KEY_LEFT ){
		if( p_psl->now_select_no - 1 >= 0 ){
			p_psl->now_select_no -= 1;
			Snd_SePlay( EV_POKESELE_SND_SELECT );
		}
	}

	if( sys.trg & PAD_KEY_RIGHT ){
		if( p_psl->now_select_no + 1 < EV_POKESELECT_MONSNUM ){
			p_psl->now_select_no += 1;
			Snd_SePlay( EV_POKESELE_SND_SELECT );
		}
	}
}


//-----------------------------------------------------------------------------
/**
 *		�V�[�P���X����
 */
//-----------------------------------------------------------------------------
static void Move_seq_add( EV_POKESELECT_PROC_WORK* p_psl, int no )
{
	p_psl->seq += no;
	p_psl->draw_seq = 0;
}
static void Move_seq_set( EV_POKESELECT_PROC_WORK* p_psl, int no )
{
	p_psl->seq = no;
	p_psl->draw_seq = 0;
}
static int Move_seq_get( EV_POKESELECT_PROC_WORK* p_psl )
{
	return p_psl->seq;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�I���ݽ���{�[������
 *
 *	@param	p_psl	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void DrawMoveSelect( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	switch( p_psl->draw_seq ){
	case 0:
		//	�J��������
		EvCameraMoveReq( &p_psl->camera_move, p_psl->p_camera, &p_psl->camera_target );
		
		// �r�b�g�}�b�v�ʂ�\���������肷��
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_ON );
		p_psl->draw_seq++;
		break;

	case 1:	// �ҋ@
		if( EvCameraMoveEndCheck( &p_psl->camera_move ) ){
			p_psl->draw_count = POKESELECT_MSSAGE_WAIT;	
			p_psl->draw_seq ++;
		}
		break;

	case 2:		// �����e���|
		p_psl->draw_count --;

		if( p_psl->draw_count < 0 ){
			Draw_move_select_cursor( p_psl );
			p_psl->draw_seq ++;
		}
		break;

	case 3:

		// �����X�^�[�{�[�����I����ł���������
		p_psl->msg_index = Fontbg_bmpwin_str_buff( p_psl->p_bmp_mfont, heap, NARC_msg_ev_pokeselect_dat, EV_POKESELECT_00, BG_FONTBMP_PRICOLOR, p_psl->msg_speed, &p_psl->p_glb_str_buff );

		p_psl->draw_seq ++;
		break;

	case 4:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( p_psl->msg_index ) == 0 ){
			Fontbg_bmpwin_strbuff_clear( p_psl );
			p_psl->draw_seq ++;
		}
		break;

	case 5:
		// �ǂ�ɂ���H
		p_psl->msg_index = Fontbg_bmpwin_str_buff( p_psl->p_bmp_mfont, heap, NARC_msg_ev_pokeselect_dat, EV_POKESELECT_08, BG_FONTBMP_PRICOLOR, p_psl->msg_speed, &p_psl->p_glb_str_buff );
		p_psl->draw_seq ++;
		break;

	case 6:
		//���b�Z�[�W�I���҂�
		if( GF_MSG_PrintEndCheck( p_psl->msg_index ) == 0 ){
			Fontbg_bmpwin_strbuff_clear( p_psl );
			p_psl->draw_seq ++;
		}
		break;

	case 7:
		// �J�[�\���`��
		Cursor_clact_set_draw_flag( &p_psl->cursor, TRUE );
		p_psl->move_lock = FALSE;	// lock����
		p_psl->draw_seq ++;
		break;
	
	case 8:
		// �I�����ꂽ�ݽ���{�[���𓮂���
		Draw_move_select_monsball( p_psl );		

		// �J�[�\�������킹��
		Draw_move_select_cursor( p_psl );

		// �J�[�\���̈ʒu�̃|�P�������`��
//		FontSubbg_bmpwin_select( p_psl );	��\���ɂ��܂����B
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I�������ݽ���{�[���𓮂���
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Draw_move_select_monsball( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		if( p_psl->now_select_no == i ){
			Anm_ev_3d_obj_loop( &p_psl->ev_3d_obj[ POKESELECT_BALL_LEFT + i ] );
		}else{
			Anm_ev_3d_obj_set( &p_psl->ev_3d_obj[ POKESELECT_BALL_LEFT + i ], 0 );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\�������킹��
 *
 *	@param	p_psl	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Draw_move_select_cursor( EV_POKESELECT_PROC_WORK* p_psl )
{
	Cursor_clact_set_matrix( &p_psl->cursor, p_psl->select_2_matrix[ p_psl->now_select_no ][0], p_psl->select_2_matrix[ p_psl->now_select_no ][1] );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�m�F��ʕ`��
 *
 *	@param	p_psl
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void DrawMoveQuestion( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	u32 ret;
	
	switch( p_psl->draw_seq ){
	case 0:

		// �J�[�\����`��
		Cursor_clact_set_draw_flag( &p_psl->cursor, FALSE );

		// �J�[�\�������킹��
		Draw_move_select_cursor( p_psl );
		
		// ������
		FontSubbg_bmpwin_clean( p_psl );
		
		// �t�F�[�h����
		QuestionFade_Req( p_psl );

		p_psl->draw_seq++;
		p_psl->move_lock = TRUE;	// lock
		break;

	case 1:	// �ҋ@
		CircleWnd_Gra_Draw( &p_psl->circle_wnd, TRUE );
		SoftSpriteParaSet( p_psl->soft_sprite[ p_psl->now_select_no ], SS_PARA_VANISH, 0 );
		if( QuestionFade_EndCheck( p_psl ) ){

			// �|�P���������𗬂�
			Snd_PMVoicePlay( EV_PokeSelect_SelectNoMonsnoGet( p_psl->now_select_no ) );
		
			p_psl->draw_seq ++;
		}
		break;

	case 2:	// WND�������Ƒ傫���Ȃ��Ă��當����ύX
		// ���̂ۂ�����ł悢�ł����H 
		Fontbg_bmpwin_str( p_psl->p_bmp_mfont, heap, NARC_msg_ev_pokeselect_dat, EV_POKESELECT_02 + p_psl->now_select_no, BG_FONTBMP_PRICOLOR, MSG_NO_PUT );

		// �n�C�A�������쐬
		p_psl->p_yes_no_menu = BmpYesNoSelectInit( p_psl->p_bg, &p_psl->bmp_data, BG_YESNOBMP_CG_CHR_OFS, BG_YESNOBMP_COLOR, heap );

		p_psl->move_lock = FALSE;	// lock����
		p_psl->draw_seq ++;
		break;

	case 3:
		ret = BmpYesNoSelectMain( p_psl->p_yes_no_menu, heap );

		switch( ret ){
		case BMPMENU_NULL:
			break;
			
		case 0:
			// �ŏI�����
			Move_seq_add( p_psl, 1 );
			break;
			
		case BMPMENU_CANCEL:
			p_psl->draw_seq++;

			// �t�t�F�[�h
			QuestionReFade_Req( p_psl );
			break;
		}
		break;

	case 4:		// �I����ʂɖ߂�
		if( QuestionFade_EndCheck( p_psl ) ){
			// �O�ɖ߂�
			Move_seq_add( p_psl, -1 );

			// �����I����ʂ̏�Ԃɂ���
			p_psl->draw_seq = 7;

			CircleWnd_Gra_Draw( &p_psl->circle_wnd, FALSE );
			SoftSpriteParaSet( p_psl->soft_sprite[ p_psl->now_select_no ], SS_PARA_VANISH, 1 );

			// �ǂǂ�ɂ���H
			p_psl->msg_index = Fontbg_bmpwin_str( p_psl->p_bmp_mfont, heap, NARC_msg_ev_pokeselect_dat, EV_POKESELECT_08, BG_FONTBMP_PRICOLOR, MSG_NO_PUT );
		}
		break;

	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	������̕`��
 *
 *	@param	p_psl
 *	@param	heap
 *	@param	arcidx
 *	@param	
 *
 *	@return	msg_index
 */
//-----------------------------------------------------------------------------
static u8 Fontbg_bmpwin_str( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color, u32 wait )
{
	MSGDATA_MANAGER* msg_data;
	STRBUF* str;
	u8 msg_index;

	// ������擾
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, arcidx, heap );
	GF_ASSERT( msg_data );
	str = MSGMAN_AllocString( msg_data, msgidx );

	// �r�b�g�}�b�v������
	GF_BGL_BmpWinDataFill( p_bmp, 15 );

	// �����񏑂�����
	msg_index = GF_STR_PrintColor( p_bmp, FONT_TALK, str, 0, 0, wait, color, NULL );
												// ���`��ʒu
	BmpTalkWinWrite( p_bmp, WINDOW_TRANS_ON, BG_FONT_CG_OFS, BG_FONT_COLOR );

	STRBUF_Delete( str );
	MSGMAN_Delete( msg_data );

	return msg_index;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�E�G�C�g������`��p�@�֐��@STRBUF�ۑ�
 *	
 *	@param	p_bmp		�r�b�g�}�b�v
 *	@param	heap		�q�[�v
 *	@param	arcidx		�A�[�J�C�uIDX
 *	@param	msgidx		���b�Z�[�WIDX
 *	@param	color		�J���[
 *	@param	wait		�E�G�C�g
 *	@param	pp_glb_str	������o�b�t�@�|�C���^�i�[��
 *
 *	@return	���b�Z�[�W�C���f�b�N�X
 */
//-----------------------------------------------------------------------------
static u8 Fontbg_bmpwin_str_buff( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color, u32 wait, STRBUF** pp_glb_str )
{
	MSGDATA_MANAGER* msg_data;
	u8 msg_index;

	GF_ASSERT( (*pp_glb_str) == NULL );

	// ������擾
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, arcidx, heap );
	GF_ASSERT( msg_data );
	*pp_glb_str = MSGMAN_AllocString( msg_data, msgidx );

	// �r�b�g�}�b�v������
	GF_BGL_BmpWinDataFill( p_bmp, 15 );

	// �����񏑂�����
	msg_index = GF_STR_PrintColor( p_bmp, FONT_TALK, *pp_glb_str, 0, 0, wait, color, NULL );
												// ���`��ʒu
	BmpTalkWinWrite( p_bmp, WINDOW_TRANS_ON, BG_FONT_CG_OFS, BG_FONT_COLOR );

	MSGMAN_Delete( msg_data );

	return msg_index;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���[�o��STRBUFF�̃N���A
 *
 *	@param	p_psl	���[�N
 */
//-----------------------------------------------------------------------------
static void Fontbg_bmpwin_strbuff_clear( EV_POKESELECT_PROC_WORK* p_psl )
{
	STRBUF_Delete( p_psl->p_glb_str_buff );
	p_psl->p_glb_str_buff = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	YES�@NO�@�ް��쐬
 *
 *	@param	p_psl
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Fontbg_yesno_bmp_dat_make( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	p_psl->bmp_data.frm_num = GF_BGL_FRAME1_M;
	p_psl->bmp_data.pos_x	= BG_YESNOBMP_X;
	p_psl->bmp_data.pos_y	= BG_YESNOBMP_Y;
	p_psl->bmp_data.siz_x	= BG_YESNOBMP_CX;
	p_psl->bmp_data.siz_y	= BG_YESNOBMP_CY;
	p_psl->bmp_data.palnum	= BG_YESNOBMP_STR_COLOR;
	p_psl->bmp_data.chrnum	= BG_YESNOBMP_CG_OFS;


	// �g��]��
	MenuWinGraphicSet( p_psl->p_bg, GF_BGL_FRAME1_M, BG_YESNOBMP_CG_CHR_OFS, BG_YESNOBMP_COLOR, 0, heap );

	// �V�X�e���t�H���g�J���[�p���b�g�ǂݍ���
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, BG_YESNOBMP_STR_COLOR*32, heap );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	����p�����[�^
 *
 *	@param	p_data	���[�N
 *	@param	s_num	�J�n�l
 *	@param	e_num	�I���l
 *	@param	count	�ő�J�E���g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EvMoveInit( EV_MOVE_PARAM* p_data, s32 s_num, s32 e_num, s32 count )
{
	p_data->data		= s_num;
	p_data->s_data		= s_num;
	p_data->add_data	= e_num - s_num;
	p_data->count_max	= count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	����v�Z����
 *
 *	@param	p_data
 *	@param	count	���݃J�E���g
 *
 *	@retval TRUE	�I��
 *	@retval	FALSE	�����傤
 */
//-----------------------------------------------------------------------------
static BOOL EvMoveMain( EV_MOVE_PARAM* p_data, s32 count )
{
	s32 local_count;
	BOOL ret;
	s32 num;
	
	if( count >= p_data->count_max ){
		local_count = p_data->count_max;
		ret = TRUE;
	}else{
		local_count = count;
		ret = FALSE;
	}

	// �v�Z
	num = p_data->add_data * count;
	num = num / p_data->count_max;
	num += p_data->s_data;

	// �ݒ�
	p_data->data = num;

	return ret;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�J��������ݒ�
 *
 *	@param	p_camera_move	�J��������p�����[�^
 *	@param	p_camera		�J�������[�N
 *	@param	p_target		�^�[�Q�b�g���W���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EvCameraMoveReq( EV_CAMERA_MOVE* p_camera_move, GF_CAMERA_PTR p_camera, VecFx32* p_target )
{
	// �o�^�ς݃`�F�b�N
	GF_ASSERT( p_camera_move->tcb == NULL );
	
	EvMoveInit( &p_camera_move->x_rota, CAMERA_ANGLE_X, CAMERA_ANGLE_AF_X, CAMERA_MOVE_AF_COUNT );
	EvMoveInit( &p_camera_move->dist, CAMERA_DISTANCE, CAMERA_DISTANCE_AF, CAMERA_MOVE_AF_COUNT );
	EvMoveInit( &p_camera_move->target_z, CAMERA_TARGET_Z, CAMERA_TARGET_AF_Z, CAMERA_MOVE_AF_COUNT );

	p_camera_move->end_flag = FALSE;
	p_camera_move->p_camera	= p_camera;
	p_camera_move->p_target = p_target;

	p_camera_move->count = 0;
 
	TCB_Add( EvCameraMoveTcb, p_camera_move, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void EvCameraMoveTcb( TCB_PTR tcb, void* work )
{
	EV_CAMERA_MOVE* p_data = work;
	BOOL check;
	CAMERA_ANGLE angle;
	
	check = EvMoveMain( &p_data->x_rota, p_data->count );
	EvMoveMain( &p_data->dist, p_data->count );
	EvMoveMain( &p_data->target_z, p_data->count );

	// �J�����ɔ��f
	angle.x = p_data->x_rota.data;
	angle.y = CAMERA_ANGLE_Y;
	angle.z = CAMERA_ANGLE_Z;
	GFC_SetCameraAngleRev( &angle, p_data->p_camera );
	GFC_SetCameraDistance( p_data->dist.data, p_data->p_camera );
	p_data->p_target->z = p_data->target_z.data;

	// �J�E���g
	p_data->count ++;
	
	// �I���`�F�b�N
	if( check == TRUE ){
		TCB_Delete( tcb );
		p_data->tcb = NULL;
		p_data->end_flag = TRUE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J��������I���`�F�b�N
 *	
 *	@param	p_camera_move 
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	���s��
 */
//-----------------------------------------------------------------------------
static BOOL EvCameraMoveEndCheck( EV_CAMERA_MOVE* p_camera_move )
{
	return p_camera_move->end_flag;
}


//----------------------------------------------------------------------------
/**
 *	@brief	OAM���\�[�X�ǂݍ���
 *
 *	@param	p_psl	���[�N
 *	@param	heap	�q�[�v
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Cursor_oam_load( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data, int heap )
{
	
	// �L�����N�^�f�[�^�ǂݍ���
	p_data->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( 
			p_psl->res_manager[ CLACT_U_CHAR_RES ], ARC_EV_POKESELECT_GRA,
			NARC_ev_pokeselect_psel_cursol_NCGR, FALSE,
			NARC_ev_pokeselect_psel_cursol_NCGR,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// �]��
	CLACT_U_CharManagerSetAreaCont( p_data->res_obj[ CLACT_U_CHAR_RES ] );
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_data->res_obj[ CLACT_U_CHAR_RES ] );

	// �p���b�g�f�[�^�ǂݍ���
	p_data->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( 
			p_psl->res_manager[ CLACT_U_PLTT_RES ], ARC_EV_POKESELECT_GRA,
			NARC_ev_pokeselect_psel_cursol_NCLR, FALSE, 
			NARC_ev_pokeselect_psel_cursol_NCLR, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			1, heap );
	// �]��
	CLACT_U_PlttManagerSetCleanArea( p_data->res_obj[ CLACT_U_PLTT_RES ] );	
	// �O���t�B�b�N�f�[�^�����j��
	CLACT_U_ResManagerResOnlyDelete( p_data->res_obj[ CLACT_U_PLTT_RES ] );


	// �Z���f�[�^�ǂݍ���
	p_data->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			p_psl->res_manager[ CLACT_U_CELL_RES ], ARC_EV_POKESELECT_GRA,
			NARC_ev_pokeselect_psel_cursol_NCER, FALSE,
			NARC_ev_pokeselect_psel_cursol_NCER,
			CLACT_U_CELL_RES, heap );

	// �Z���A�j���f�[�^�ǂݍ���
	p_data->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			p_psl->res_manager[ CLACT_U_CELLANM_RES ], ARC_EV_POKESELECT_GRA, 
			NARC_ev_pokeselect_psel_cursol_NANR, FALSE,
			NARC_ev_pokeselect_psel_cursol_NANR,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAM���\�[�X�j��
 *
 *	@param	p_psl	���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Cursor_oam_delete( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data )
{
	CLACT_U_CharManagerDelete( p_data->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_data->res_obj[ CLACT_U_PLTT_RES ] );

	// ���\�[�X�j��
	CLACT_U_ResManagerResDelete( 
			p_psl->res_manager[ CLACT_U_CHAR_RES ],
			p_data->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_psl->res_manager[ CLACT_U_PLTT_RES ],
			p_data->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_psl->res_manager[ CLACT_U_CELL_RES ],
			p_data->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_psl->res_manager[ CLACT_U_CELLANM_RES ],
			p_data->res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�o�^
 *
 *	@param	p_psl	���[�N
 *	@param	heap	�q�[�v
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Cursor_clact_add( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	
	// �e�{�^����o�^
	// �A�N�^�[�w�b�_�[�쐬
	CLACT_U_MakeHeader( &clact_head,
			NARC_ev_pokeselect_psel_cursol_NCGR,
			NARC_ev_pokeselect_psel_cursol_NCLR,
			NARC_ev_pokeselect_psel_cursol_NCER,
			NARC_ev_pokeselect_psel_cursol_NANR,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, CLACT_BG_PRI,
			p_psl->res_manager[ CLACT_U_CHAR_RES ],
			p_psl->res_manager[ CLACT_U_PLTT_RES ],
			p_psl->res_manager[ CLACT_U_CELL_RES ],
			p_psl->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	add.ClActSet	= p_psl->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 32;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;

	// �J�[�\���o�^
	add.mat.x = 0;
	add.mat.y = 0;
	p_data->cursor = CLACT_AddSimple( &add );
	CLACT_SetDrawFlag( p_data->cursor, FALSE );

	p_data->mat.x = 0;
	p_data->mat.y = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Z���A�N�^�[�j��
 *
 *	@param	p_data	�J�[�\���I�u�W�F	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Cursor_clact_delete( EV_CURSOR_OBJ* p_data )
{
	CLACT_Delete( p_data->cursor );
}

//----------------------------------------------------------------------------
/**
 *	@brief	��]���샏�[�N������
 *
 *	@param	p_data	�ް��i�[��
 *	@param	r		���a�̑傫��
 *	@param	count	�����ő�l
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EvRotaMoveInit( EV_ROTA_MOVE_ONE* p_data, fx32 r, int count )
{
	p_data->num			= 0;
	p_data->r			= r;
	p_data->count_max	= count;
	p_data->count		= 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	��]���상�C��
 *
 *	@param	p_data	���[�N
 */
//-----------------------------------------------------------------------------
static void EvRotaMoveMain( EV_ROTA_MOVE_ONE* p_data )
{
	u16 rota;
	int calc;

	// ���݉�]�p�����߂�
	calc = FX_GET_ROTA_NUM( 360 ) * p_data->count;
	calc = calc / p_data->count_max;
	rota = calc;

	// ���ݓ���ʒu
	p_data->num = FX_Mul( FX_SinIdx( rota ), p_data->r );


	// �J�E���g����
	p_data->count = (p_data->count + 1) % p_data->count_max;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\������J�n
 *
 *	@param	p_cursor	�J�[�\���I�u�W�F�N�g
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EvCursorMoveReq( EV_CURSOR_OBJ* p_cursor )
{
	// ���������݃`�F�b�N
	GF_ASSERT( p_cursor->tcb == NULL );
	
	EvRotaMoveInit( &p_cursor->move_param, CURSOR_MOVE_Y, CURSOR_MOVE_COUNT );
	
	p_cursor->tcb = TCB_Add( EvCursorMoveTcb, p_cursor, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\���^�X�N
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void EvCursorMoveTcb( TCB_PTR tcb, void* work )
{
	EV_CURSOR_OBJ* p_cursor = work;
	VecFx32 set_mat;
	
	EvRotaMoveMain( &p_cursor->move_param );

	// ���W�ݒ�
	set_mat = p_cursor->mat;
	set_mat.y += p_cursor->move_param.num;
	CLACT_SetMatrix( p_cursor->cursor, &set_mat );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�J�[�\������j��
 *
 *	@param	p_cursor 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void EvCursorMoveDelete( EV_CURSOR_OBJ* p_cursor )
{
	if(p_cursor->tcb){
		TCB_Delete( p_cursor->tcb );
		p_cursor->tcb = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�\��ONOFF
 *
 *	@param	p_data
 *	@param	flag 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Cursor_clact_set_draw_flag( EV_CURSOR_OBJ* p_data, BOOL flag )
{
	CLACT_SetDrawFlag( p_data->cursor, flag );
}

static void Cursor_clact_set_matrix( EV_CURSOR_OBJ* p_data, int x, int y )
{
	p_data->mat.x = x << FX32_SHIFT;
	p_data->mat.y = y << FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~�`�E�B���h�E����ӂ�����������
 *
 *	@param	p_data		�ް��i�[��
 *	@param	p_psl		�ް����[�N
 *	@param	heap		�q�[�v
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_Gra_Init( EV_CIRCLE_WND* p_data, EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	SWSP_CHARDATA char_ent;
	SWSP_PLTTDATA pltt_ent;
	SWSP_ADDDATA add;
	
	// �L�����N�^�f�[�^
	p_data->swsp_char_buff = ArcUtil_CharDataGet( 
			ARC_EV_POKESELECT_GRA, NARC_ev_pokeselect_psel_circle_NCBR, FALSE,
			&p_data->p_chardata, heap );
	
	// �p���b�g�f�[�^�ǂݍ���
	p_data->swsp_pltt_buff = ArcUtil_PalDataGet( 
			ARC_EV_POKESELECT_GRA, NARC_ev_pokeselect_psel_circle_NCLR,
			&p_data->p_plttdata, heap );

	// �L�����N�^�f�[�^�]��
	char_ent.s_sys		= p_psl->swsp_sys;
	char_ent.res_file	= p_data->p_chardata;
	p_data->swsp_char = SWSP_CharLoad( &char_ent );

	// �p���b�g�f�[�^�]��
	pltt_ent.s_sys		= p_psl->swsp_sys;
	pltt_ent.res_file	= p_data->p_plttdata;
	pltt_ent.load_num	= 1;
	p_data->swsp_pltt = SWSP_PlttLoad( &pltt_ent );


	//-------------------------------------
	//	�o�^
	//=====================================
	add.s_sys	= p_psl->swsp_sys;
	add.p_char	= p_data->swsp_char;
	add.p_pltt	= p_data->swsp_pltt;

	// �o�^�f�[�^�i�[
	add.m_x = 0;
	add.m_y = 0;
	add.rota = 0;
	add.alpha = 31;
	add.pri = 1022;
	add.pltt_offs = 0; 

	// �o�^
	p_data->swsp_obj = SWSP_Add( &add );

	// ��荇������\��
	SWSP_SetSpriteDraw( p_data->swsp_obj, FALSE );

	// ���S���W
	SWSP_SetSpriteCenterPos( p_data->swsp_obj, QUESTION_CIRCLE_SIZE / 2, QUESTION_CIRCLE_SIZE / 2 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	CIRCLE�O���t�B�b�N�ް��j��
 *
 *	@param	p_data
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_Gra_Delete( EV_CIRCLE_WND* p_data )
{
	// �I�u�W�F�N�g�j��
	SWSP_Delete( p_data->swsp_obj );
	
	// Vram����j��
	SWSP_CharDelete( p_data->swsp_char );
	SWSP_PlttDelete( p_data->swsp_pltt );
	// ����������j��
	sys_FreeMemoryEz( p_data->swsp_char_buff );
	sys_FreeMemoryEz( p_data->swsp_pltt_buff );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�[�N���@�`��ONOFF
 *
 *	@param	p_data 
 *	@param	flag
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_Gra_Draw( EV_CIRCLE_WND* p_data, BOOL flag )
{
	SWSP_SetSpriteDraw( p_data->swsp_obj, flag );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�[�N���E�B���h�E���샊�N�G�X�g
 *
 *	@param	p_data 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_Move_Req( EV_CIRCLE_WND* p_data, fx32 s_x, fx32 e_x, fx32 s_y, fx32 e_y, fx32 s_s, fx32 e_s, int sync )
{
	// �������݃`�F�b�N
	GF_ASSERT( p_data->tcb == NULL );
	
	// X���W����
	EvMoveInit( &p_data->param.x, s_x, e_x, sync );

	// Y���W����
	EvMoveInit( &p_data->param.y, s_y, e_y, sync );

	// scale���W����
	EvMoveInit( &p_data->param.scale, s_s, e_s, sync );

	// ����������
	p_data->param.count = 0;
	p_data->param.count_add = 1;

	p_data->tcb = TCB_Add( CircleWnd_Move_Tcb, p_data, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�p�����[�^������Ă����āA�t�Đ�������
 *
 *	@param	p_data		�ް�
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_ReMove_Req( EV_CIRCLE_WND* p_data )
{
	// �������݃`�F�b�N
	GF_ASSERT( p_data->tcb == NULL );

	// ����������
	p_data->param.count_add = QUESTION_CIRCLE_RET_ADD;
	

	// ������������Ⴄ�̉��
	if( p_data->param.count >= p_data->param.x.count_max  ){
		p_data->param.count = p_data->param.x.count_max + p_data->param.count_add;
	}

	p_data->tcb = TCB_Add( CircleWnd_Move_Tcb, p_data, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�[�N���E�B���h�E����^�X�N
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_Move_Tcb( TCB_PTR tcb, void* work )
{
	EV_CIRCLE_WND* p_data = work;
	BOOL check;
	fx32 x, y;

	// ���삳����
	check = EvMoveMain( &p_data->param.x, p_data->param.count );
	EvMoveMain( &p_data->param.y, p_data->param.count );
	EvMoveMain( &p_data->param.scale, p_data->param.count );

	// ������W�ɂ��Ēl��ݒ�
	x = p_data->param.x.data - ((QUESTION_CIRCLE_SIZE/2)*FX32_ONE);	
	y = p_data->param.y.data - ((QUESTION_CIRCLE_SIZE/2)*FX32_ONE);	
	SWSP_SetSpritePos( p_data->swsp_obj, 
			x >> FX32_SHIFT, y >> FX32_SHIFT );

	// �g�k�l
	SWSP_SetSpriteScale( p_data->swsp_obj, p_data->param.scale.data, p_data->param.scale.data );

	if( (check == TRUE) || (p_data->param.count < 0) ){
		// �I��
		TCB_Delete( tcb );
		p_data->tcb = NULL;
	}

	// �J�E���g����
	p_data->param.count += p_data->param.count_add;

}

//----------------------------------------------------------------------------
/**
 *	@brief	�T�[�N���E�B���h�E����I���`�F�b�N
 *
 *	@param	p_data 
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL CircleWnd_Move_EndCheck( EV_CIRCLE_WND* p_data )
{
	if( p_data->tcb ){
		return  FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�m�F��ʃt�F�[�h���N�G�X�g
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void QuestionFade_Req( EV_POKESELECT_PROC_WORK* p_psl )
{
	fx32 s_x, s_y;

	// �J�n�ʒu�����߂�
	s_x = p_psl->select_2_matrix[ p_psl->now_select_no ][ 0 ] << FX32_SHIFT;
	s_y = (p_psl->select_2_matrix[ p_psl->now_select_no ][ 1 ] + QUESTION_CIRCLE_Y_OFS) << FX32_SHIFT;
	CircleWnd_Move_Req( &p_psl->circle_wnd, 
			s_x, EV_POKESELECT_POKEGRA_X << FX32_SHIFT,
			s_y, EV_POKESELECT_POKEGRA_Y << FX32_SHIFT,
			QUESTION_FADE_SCALE_S, QUESTION_FADE_SCALE_E,
			QUESTION_FADE_SYNC );

	// �߹���
	PokeGra_Move_Req( &p_psl->soft_sprite_anm, 
			p_psl->soft_sprite[ p_psl->now_select_no ],
			s_x, EV_POKESELECT_POKEGRA_X << FX32_SHIFT,
			s_y, EV_POKESELECT_POKEGRA_Y << FX32_SHIFT,
			QUESTION_FADE_SCALE_S, QUESTION_FADE_SCALE_E,
			QUESTION_FADE_SYNC );

}

//----------------------------------------------------------------------------
/**
 *	@brief	�m�F��ʂ���߂�t�F�[�h���N�G�X�g
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void QuestionReFade_Req( EV_POKESELECT_PROC_WORK* p_psl )
{
	CircleWnd_ReMove_Req( &p_psl->circle_wnd );
	PokeGra_ReMove_Req( &p_psl->soft_sprite_anm );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�F�[�h�I���҂�
 *
 *	@param	p_psl 
 *
 *	@retval	TRUE	�I��
 *	@retval	FALSE	�r��
 */
//-----------------------------------------------------------------------------
static BOOL QuestionFade_EndCheck( EV_POKESELECT_PROC_WORK* p_psl )
{
	return CircleWnd_Move_EndCheck( &p_psl->circle_wnd );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N����
 *
 *	@param	p_data
 *	@param	p_soft_sprit
 *	@param	s_x
 *	@param	e_x
 *	@param	s_y
 *	@param	e_y
 *	@param	s_s
 *	@param	e_s
 *	@param	sync 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeGra_Move_Req( EV_POKEOBJ_ANM* p_data, SOFT_SPRITE* p_soft_sprit, fx32 s_x, fx32 e_x, fx32 s_y, fx32 e_y, fx32 s_s, fx32 e_s, int sync )
{
	// �������݃`�F�b�N
	GF_ASSERT( p_data->tcb == NULL );
	
	// X���W����
	EvMoveInit( &p_data->param.x, s_x, e_x, sync );

	// Y���W����
	EvMoveInit( &p_data->param.y, s_y, e_y, sync );

	// scale���W����
	EvMoveInit( &p_data->param.scale, s_s, e_s, sync );

	// �X�v���C�g���[�N
	p_data->p_soft_sprite = p_soft_sprit;

	// ����������
	p_data->param.count = 0;
	p_data->param.count_add = 1;

	p_data->tcb = TCB_Add( PokeGra_Move_Tcb, p_data, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�t�Đ�
 *
 *	@param	p_data 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeGra_ReMove_Req( EV_POKEOBJ_ANM* p_data )
{
	// �������݃`�F�b�N
	GF_ASSERT( p_data->tcb == NULL );

	// ����������
	p_data->param.count_add = QUESTION_CIRCLE_RET_ADD;
	

	// ������������Ⴄ�̉��
	if( p_data->param.count >= p_data->param.x.count_max  ){
		p_data->param.count = p_data->param.x.count_max + p_data->param.count_add;
	}

	p_data->tcb = TCB_Add( PokeGra_Move_Tcb, p_data, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P�����O���t�B�b�N�ɔ��f
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeGra_Move_Tcb( TCB_PTR tcb, void* work )
{
	EV_POKEOBJ_ANM* p_data = work;
	BOOL check;
	u32 scale_num;

	// ���삳����
	check = EvMoveMain( &p_data->param.x, p_data->param.count );
	EvMoveMain( &p_data->param.y, p_data->param.count );
	EvMoveMain( &p_data->param.scale, p_data->param.count );

	// 0x100��1�̊g��k���ɂ���
	scale_num = FX_Mul( 0x100*FX32_ONE, p_data->param.scale.data ) >> FX32_SHIFT;

	SoftSpriteParaSet( p_data->p_soft_sprite, SS_PARA_POS_X, p_data->param.x.data >> FX32_SHIFT );
	SoftSpriteParaSet( p_data->p_soft_sprite, SS_PARA_POS_Y, p_data->param.y.data >> FX32_SHIFT );
	SoftSpriteParaSet( p_data->p_soft_sprite, SS_PARA_AFF_X, scale_num );
	SoftSpriteParaSet( p_data->p_soft_sprite, SS_PARA_AFF_Y, scale_num );

	if( (check == TRUE) || (p_data->param.count < 0) ){
		// �I��
		TCB_Delete( tcb );
		p_data->tcb = NULL;
	}

	// �J�E���g����
	p_data->param.count += p_data->param.count_add;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I���`�F�b�N
 *
 *	@param	p_data 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static BOOL PokeGra_Move_EndCheck( EV_POKEOBJ_ANM* p_data )
{
	if( p_data->tcb ){
		return  FALSE;
	}

	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�T�u�ʃr�b�g�}�b�v�E�B���h�E�쐬
 *
 *	@param	p_psl	���[�N
 *	@param	heap	�q�[�v
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void FontSubbg_bmpwin_make( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	int i;
	int x, y;

	// �p���b�g�]��
	ArcUtil_PalSet( ARC_EV_POKESELECT_GRA, NARC_ev_pokeselect_font_system_NCLR, PALTYPE_MAIN_BG, BG_FONTSUB_COLOR * 32, 32, heap );
	
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		p_psl->p_bmp_subfont[i] = GF_BGL_BmpWinAllocGet( heap, 1 );
		GF_BGL_BmpWinInit( p_psl->p_bmp_subfont[i] );

		switch( i ){
		case POKESELECT_LEFT_BALL:
			x = BG_FONTSUBBMP_0X;
			y = BG_FONTSUBBMP_0Y;
			break;
		case POKESELECT_CENTER_BALL:
			x = BG_FONTSUBBMP_1X;
			y = BG_FONTSUBBMP_1Y;
			break;
		case POKESELECT_RIGHT_BALL:
			x = BG_FONTSUBBMP_2X;
			y = BG_FONTSUBBMP_2Y;
			break;
		}
	
		// �r�b�g�}�b�v�E�B���h�E�o�^
		GF_BGL_BmpWinAdd( p_psl->p_bg, p_psl->p_bmp_subfont[i],
				GF_BGL_FRAME3_M, x, y, BG_FONTSUBBMP_CX, BG_FONTSUBBMP_CY, BG_FONTSUB_COLOR, 1 + (BG_FONTSUB_CGX_OFS * i) );

		// ������`��
		FontSubbg_bmpwin_str( p_psl->p_bmp_subfont[i], heap, NARC_msg_ev_pokeselect_dat, EV_POKESELECT_05 + i, BG_FONTSUBBMP_PRICOLOR );
	}

}
//----------------------------------------------------------------------------
/**
 *	@brief	�r�b�g�}�b�v�E�B���h�E�j��
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void FontSubbg_bmpwin_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;

	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		GF_BGL_BmpWinDel( p_psl->p_bmp_subfont[i] );
		sys_FreeMemoryEz( p_psl->p_bmp_subfont[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	������`��
 *
 *	@param	p_bmp
 *	@param	heap
 *	@param	arcidx
 *	@param	msgidx
 *	@param	color 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void FontSubbg_bmpwin_str( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color )
{
	MSGDATA_MANAGER* msg_data;
	STRBUF* str;

	// ������擾
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, arcidx, heap );
	GF_ASSERT( msg_data );
	str = MSGMAN_AllocString( msg_data, msgidx );

	// �r�b�g�}�b�v������
	GF_BGL_BmpWinDataFill( p_bmp, GF_PRINTCOLOR_GET_GROUND( color ) );

	// �����񏑂�����
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, 1, 0, MSG_NO_PUT, color, NULL );
												// ���`���
	STRBUF_Delete( str );

	MSGMAN_Delete( msg_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I������Ă��郁�b�Z�[�W���o��
 *
 *	@param	p_psl ���[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FontSubbg_bmpwin_select( EV_POKESELECT_PROC_WORK* p_psl )
{
	// ���܂ł̂��̂��N���A
	GF_BGL_BmpWinOff( p_psl->p_bmp_subfont[ p_psl->local_select_no ] );

	// ���̂�ON
	GF_BGL_BmpWinOn( p_psl->p_bmp_subfont[ p_psl->now_select_no ] );
	p_psl->local_select_no = p_psl->now_select_no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���S�ɏ���
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void FontSubbg_bmpwin_clean( EV_POKESELECT_PROC_WORK* p_psl )
{
	GF_BGL_BmpWinOff( p_psl->p_bmp_subfont[ p_psl->local_select_no ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�I���i���o�[����I�������|�P�����i���o�[���擾
 *
 *	@param	no	�I���i���o�[
 *
 *	@return	�����X�^�[�i���o�[
 */
//-----------------------------------------------------------------------------
static u16 EV_PokeSelect_SelectNoMonsnoGet( u16 no )
{
	// �e�ɑI�������|�P�������ް��ݒ肷��
	switch( no ){
	case POKESELECT_LEFT_BALL:
		return MONSNO_NAETORU;
	case POKESELECT_CENTER_BALL:
		return MONSNO_HIKOZARU;
	case POKESELECT_RIGHT_BALL:
		return MONSNO_POTTYAMA;
	default:
		GF_ASSERT(0);
		break;
	}
	return 0;
}
