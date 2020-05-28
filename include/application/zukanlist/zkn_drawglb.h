//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_drawglb.h
 *	@brief		�}�ӕ`��O���[�o���f�[�^
 *	@author		tomoya takahashi
 *	@data		2006.01.19
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_DRAWGLB_H__
#define __ZKN_DRAWGLB_H__

#include "include/application/zukanlist/zkn_defain.h"


// �`��֌W
#include "include/gflib/bg_system.h"
#include "include/system/clact_util.h"
#include "include/system/softsprite.h"
#include "include/system/brightness.h"
#include "include/system/swsprite.h"
#include "include/system/arc_tool.h"
#include "include/system/arc_util.h"
#include "include/application/zukanlist/zkn_fontoam.h"
#include "include/application/zukanlist/zkn_cursor.h"


#undef GLOBAL
#ifdef	__ZKN_DRAWGLB_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	3D�|�P�����O���t�B�b�N�f�[�^	
//=====================================
#define ZKN_DRAWGLB_POKEGRA_NUM		(4)		// ��������ʂłS�K�v

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	���W�������샏�[�N
//=====================================
typedef struct {
	int x;
	int y;
	int s_x;
	int s_y;
	int dis_x;
	int dis_y;
	int count;
	int count_max;
} ZKN_UTIL_MOVE_WORK;





//-------------------------------------
//	�|�P�������X�g��ʂƐ}�Ӄf�[�^��ʂŋ��ʂɎg�p����
//	�O���t�B�b�N�f�[�^�\����
//=====================================
typedef struct {
	// �|�P�������X�g�A�}�Ӄf�[�^���
	// ���X�gOAM�f�[�^
	CLACT_WORK_PTR pokelist_tbl;	// �e�[�u������
	CLACT_WORK_PTR pokelist_icon;	// �A�C�R��
	ZKN_FONTOAM_DATA* p_pokename;	// ���OOAM	
	CLACT_U_RES_OBJ_PTR pokelist_res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// ���\�[�X�I�u�W�F��

	VecFx32		matrix;				// �S�̂𓮂�������W

	int mons_no;		// ���ݐݒ肳��Ă��郂���X�^�[�i���o�[�i�S���j
	u32 zkn_mode;
} ZKN_POKELIST_DATA_OAM_DATA;


//-------------------------------------
//	�t�F�[�h�C���A�E�g�u�����h�V�X�e��
//=====================================
enum{
	ZKN_UTIL_FADE_MAIN,
	ZKN_UTIL_FADE_SUB,
};
typedef struct {
	int disp_flag;		// ���C���T�u
	
	u32	plane1;			// ��P�Ώ̖�
	u32	plane2;			// ��Q�Ώ̖�	��������BD�͉������܂�
	int	brightness_s;	// �u���C�g�l�X�J�n
	int brightness_dis;	// �u���C�g�l�X�I��
	int alpha_s;		// �J�n���l
	int alpha_dis;		// �I���܂ł̒l
	int count_max;		// �ő�J�E���g��
	int count;			// ���݃J�E���g�l
} ZKN_UTIL_FADE_SYS;

//-------------------------------------
//	�J�[�\���I�u�W�F�N�g
//=====================================
typedef struct {
	CLACT_WORK_PTR cursor[ ZKN_CURROS_MAT_RECT_NUM ];	// �J�[�\��
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// ���\�[�X�I�u�W�F
	int x;	// �w���W
	int y;	// �x���W
	int size_x;	// �w�T�C�Y
	int size_y;	// �x�T�C�Y

	BOOL anm_stop;	// �A�j���X�g�b�v�t���O
	int anm_count;	// �A�j���J�E���g
} ZKN_UTIL_CURSOR_OBJ;

//-------------------------------------
//	�J�[�\���I�u�W�F�N�g�@���W�ύX����A�j�����[�N
//=====================================
typedef struct {
	ZKN_UTIL_CURSOR_OBJ* p_cursor;		// �J�[�\���I�u�W�F�N�g
	ZKN_UTIL_MOVE_WORK mat_move;		// ���W����p
	ZKN_UTIL_MOVE_WORK size_move;		// �T�C�Y����p

	int ta_x;		// ���̃^�[�Q�b�g�����W
	int ta_y;		// ���̃^�[�Q�b�g�����W
	int ta_size_x;	// ���̃^�[�Q�b�g���T�C�Y
	int ta_size_y;	// ���̃^�[�Q�b�g���T�C�Y

	BOOL move_stop;	// ����X�g�b�v
} ZKN_UTIL_CURSOR_OBJ_MOVE;


//-------------------------------------
//	�}�ӕ`��O���[�o���f�[�^
//
//	�S�̂Ŏg�p������́@
//	�����A�v���P�[�V�����Ԃŋ��L���������\�[�X�f�[�^
//	�Ȃǂ��i�[
//=====================================
typedef struct {
	// BGL
	GF_BGL_INI*	p_bg;					// �����Ǘ�
	GF_BGL_BMPWIN bmp_mfont;			// ���C����ʃt�H���g�`��p
	
	// OAM
	CLACT_U_EASYRENDER_DATA	oam_rend;	// oam�����_���[�f�[�^
	CLACT_SET_PTR			clact_set;	// �Z���A�N�^�[�Z�b�g
	CLACT_U_RES_MANAGER_PTR	res_manager[ ZKN_CLACT_RES_MANAGER_NUM ];	// ���\�[�X�}�l�[�W��

	// FONTOAM
	ZKN_FONTOAM_SYS_PTR fontoam_sys;
	
	// 3D�|�P����
	SOFT_SPRITE_MANAGER* soft_sprite_man;	// �\�t�g�E�F�A�X�v���C�g�}�l�[�W��
	SOFT_SPRITE*		 soft_sprite[ ZKN_DRAWGLB_POKEGRA_NUM ];	// �I�𒆂̃|�P�����̃\�t�g�E�F�A�X�v���C�g

	// �\�t�g�E�F�A�X�v���C�g
	SWSP_SYS_PTR	swsp_sys;

	// fade�V�X�e��
	ZKN_UTIL_FADE_SYS	fade;
	ZKN_UTIL_FADE_SYS	fade_sub;

//	�|�P�������X�g��ʂƐ}�Ӄf�[�^��ʂŋ��ʂɎg�p����
//	�O���t�B�b�N�f�[�^�\����
	ZKN_POKELIST_DATA_OAM_DATA pokelist_data_draw;

	// �}�ӃJ�[�\���`��f�[�^
	ZKN_UTIL_CURSOR_OBJ cursor;
	ZKN_UTIL_CURSOR_OBJ_MOVE cursor_move;	// ���W�ύX���샏�[�N
	TCB_PTR	cursor_anm_tcb;		// �A�j��
	TCB_PTR cursor_move_tcb;	// ���W�ύX����

	// �O���t�B�b�N�f�[�^�A�[�J�C�u�n���h��
	ARCHANDLE* p_graphic_arc_handl;
} ZKN_GLB_DRAWDATA;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_GlbDrawDataInit( ZKN_GLB_DRAWDATA* p_draw, int heap );
GLOBAL void ZKN_GlbDrawDataDelete( ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void ZKN_GlbDrawDataMain( ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void ZKN_GlbDrawDataVBlank( ZKN_GLB_DRAWDATA* p_draw );

void ZKN_GlbPokemonGraphicSet( ZKN_GLB_DRAWDATA* p_draw, int mons_no, int sex, int dir, int col, u8 form_no, u32 rnd, int x, int y );
GLOBAL void ZKN_GlbPokemonGraphicSetMatrix( ZKN_GLB_DRAWDATA* p_draw, int x, int y );
GLOBAL void ZKN_GlbPokemonGraphicGetMatrix( ZKN_GLB_DRAWDATA* p_draw, int* x, int* y );
GLOBAL SOFT_SPRITE* ZKN_GlbPokemonGraphicGet( const ZKN_GLB_DRAWDATA* cp_draw );
GLOBAL void ZKN_GlbPokemonGraphicDrawFlagSet( const ZKN_GLB_DRAWDATA* cp_draw, BOOL flag );
GLOBAL void ZKN_GLB_SpritePokeGraPalFade( const ZKN_GLB_DRAWDATA* p_draw, ZKN_UTIL_FADE_SYS* p_fade );

GLOBAL void ZKN_GlbPokemonGraphicSet_Idx( ZKN_GLB_DRAWDATA* p_draw, int mons_no, int sex, int dir, int col, u8 form_no, u32 rnd, int x, int y, int idx );
GLOBAL void ZKN_GlbPokemonGraphicSetMatrix_Idx( ZKN_GLB_DRAWDATA* p_draw, int x, int y, int idx );
GLOBAL void ZKN_GlbPokemonGraphicGetMatrix_Idx( ZKN_GLB_DRAWDATA* p_draw, int* x, int* y, int idx );
GLOBAL SOFT_SPRITE* ZKN_GlbPokemonGraphicGet_Idx( const ZKN_GLB_DRAWDATA* cp_draw, int idx );
GLOBAL void ZKN_GlbPokemonGraphicDrawFlagSet_Idx( const ZKN_GLB_DRAWDATA* cp_draw, BOOL flag, int idx );
GLOBAL void ZKN_GLB_SpritePokeGraPalFade_Idx( const ZKN_GLB_DRAWDATA* p_draw, ZKN_UTIL_FADE_SYS* p_fade, int idx );


GLOBAL CLACT_WORK_PTR ZKN_GlbPokeNameTblClactGet( const ZKN_GLB_DRAWDATA* p_draw );
GLOBAL CLACT_WORK_PTR ZKN_GlbPokeNameIconClactGet( const ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void ZKN_GlbPokeNameTblSet( ZKN_GLB_DRAWDATA* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, int char_size, int mons_no, u32 zkn_mode );
GLOBAL ZKN_FONTOAM_DATA* ZKN_GlbPokeNameTblGet( const ZKN_GLB_DRAWDATA* p_draw );
GLOBAL CLACT_U_RES_OBJ_PTR ZKN_GlbPokeNameTblResObjGet( const ZKN_GLB_DRAWDATA* p_draw, int res_type );
GLOBAL void ZKN_GlbPokeNameTblObjModeSet( const ZKN_GLB_DRAWDATA* p_draw, GXOamMode mode );
GLOBAL void ZKN_GlbPokeNameTblBGPriSet( const ZKN_GLB_DRAWDATA* p_draw, int pri );
GLOBAL void ZKN_GlbPokeNameTblDrawFlagSet( const ZKN_GLB_DRAWDATA* p_draw, BOOL flag );

// �퓬��}�Ӊ�ʗp�̊֐�
GLOBAL void ZKN_GlbPokeNameTblSet_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, ZKN_FONTOAM_INIT* p_fontoam_init, int char_size, int mons_no, u32 zkn_mode );
GLOBAL void ZKN_GlbPokeNameTblResLoad_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap );
GLOBAL void ZKN_GlbPokeNameTblResRelease_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_U_RES_MANAGER_PTR* pp_res_manager );
GLOBAL void ZKN_GlbPokeNameTblActAdd_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int bg_pri );
GLOBAL void ZKN_GlbPokeNameTblActDelete_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data );
GLOBAL void ZKN_GlbPokeNameTblDrawFlagSet_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, BOOL flag );
 

GLOBAL void ZKN_GLB_ChangeFadeRequest( ZKN_UTIL_FADE_SYS* p_fade, u8 sync, int brightness_s, int brightness_e, int s_alpha, int e_alpha, BRIGHT_PLANEMASK plane1, BRIGHT_PLANEMASK plane2, int disp_flag );
GLOBAL BOOL ZKN_GLB_ChangeFadeMain( ZKN_UTIL_FADE_SYS* p_fade );
GLOBAL int ZKN_GLB_GetFadeAlpha( ZKN_UTIL_FADE_SYS* p_fade );
GLOBAL int ZKN_GLB_GetFadeBrightness( ZKN_UTIL_FADE_SYS* p_fade );
GLOBAL BOOL ZKN_GLB_ChangeFadeEndCheck( ZKN_UTIL_FADE_SYS* p_fade );



GLOBAL void ZKN_UTIL_CursorSetMatrixCursorSys( const ZKN_CURSOR* cp_cursor, ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void ZKN_UTIL_CursorSetMatrix( ZKN_GLB_DRAWDATA* p_draw, int def_x, int def_y, int size_x, int size_y );
GLOBAL void ZKN_UTIL_CursorSetDrawFlag( ZKN_UTIL_CURSOR_OBJ* p_obj, int flag );
GLOBAL BOOL ZKN_UTIL_CursorGetDrawFlag( ZKN_UTIL_CURSOR_OBJ* p_obj );
GLOBAL void ZKN_UTIL_CursorSetAnimeStopFlag( ZKN_UTIL_CURSOR_OBJ* p_obj, BOOL anm );
GLOBAL void ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( const ZKN_CURSOR* cp_cursor, ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void ZKN_UTIL_CursorSetMatrixNotAnm( ZKN_GLB_DRAWDATA* p_draw, int def_x, int def_y, int size_x, int size_y );


GLOBAL void ZKN_UTIL_MoveReq( ZKN_UTIL_MOVE_WORK* p_work, int s_x, int e_x, int s_y, int e_y, int count_max );
GLOBAL BOOL ZKN_UTIL_MoveMain( ZKN_UTIL_MOVE_WORK* p_work );

// �A�[�J�C�u�n���h�����g�p�����ǂݍ���
// �ǂݍ��ݏ����������̂���
GLOBAL ARCHANDLE* ZKN_GLBDATA_ArcHandlGet( ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void* ZKN_GLBDATA_Arc_Load(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, u32 heapID);
GLOBAL u32 ZKN_GLBDATA_BgCharSet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID);
GLOBAL void ZKN_GLBDATA_PalSet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID );
GLOBAL void* ZKN_GLBDATA_CharDataGet( ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, NNSG2dCharacterData** charData, u32 heapID );
GLOBAL void* ZKN_GLBDATA_PalDataGet( ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, NNSG2dPaletteData** palData, u32 heapID );
GLOBAL void* ZKN_GLBDATA_ScrnDataGet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, NNSG2dScreenData** scrnData, u32 heapID);


#undef	GLOBAL
#endif		// __ZKN_DRAWGLB_H__

