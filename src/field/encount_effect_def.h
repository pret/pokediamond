//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		eccount_effect_def.h
 *@brief	�G���J�E���g�G�t�F�N�g�̃^�X�N�쐬�ɕK�v�ȃf�[�^
 *@author	tomoya takahashi
 *@data		2005.07.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ECCOUNT_EFFECT_DEF_H__
#define __ECCOUNT_EFFECT_DEF_H__

#include "field_hblank.h"
#include "system/clact_util.h"

#undef GLOBAL
#ifdef	__ECCOUNT_EFFECT_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif



#define TCB_TSK_PRI	(5)
#define TCB_VWAIT_BR_TSK_PRI	(10)


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�ėp����
//=====================================
typedef struct {
	int x;
	int s_x;
	int dis_x;
	int count;
	int count_max;
} ENC_MOVE_WORK;
GLOBAL void ENC_MoveReq( ENC_MOVE_WORK* p_work, int s_x, int e_x, int count_max );
GLOBAL BOOL	ENC_MoveMain( ENC_MOVE_WORK* p_work );

//-------------------------------------
//	�ėp����
//=====================================
typedef struct {
	fx32 x;
	fx32 s_x;
	fx32 dis_x;
	int count;
	int count_max;
} ENC_MOVE_WORK_FX;
GLOBAL void ENC_MoveReqFx( ENC_MOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, int count_max );
GLOBAL BOOL	ENC_MoveMainFx( ENC_MOVE_WORK_FX* p_work );

//-------------------------------------
//	�ėp��������
//=====================================
typedef struct {
	fx32 x;
	fx32 s_x;
	fx32 s_s;	// �����x
	fx32 s_a;	// �����x
	int count;
	int count_max;
} ENC_ADDMOVE_WORK_FX;
GLOBAL void ENC_AddMoveReqFx( ENC_ADDMOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, fx32 s_s, int count_max );
GLOBAL BOOL	ENC_AddMoveMainFx( ENC_ADDMOVE_WORK_FX* p_work );




//-------------------------------------
//
//	�G���J�E���g�G�t�F�N�g���[�N
//
//=====================================
typedef struct{
	int seq;
	int wait;
	int count;
	void* work;		// �e���A���R�Ɏg�p
	FIELDSYS_WORK *fsw;
	BOOL* end;		// �I�������p
	BOOL hblank_flg;// H�u�����N�t���O
	BOOL wipe_flag;
}ENCOUNT_EFFECT_WORK;



//----------------------------------------------------------------------------
/**
 *
 *@brief	�ŏ��̃t���b�V���̕\��������^�X�N�����s����
 *				�u���C�g�l�X���g�p���A��ʂ��s�J�s�J�_�ł��܂��B
 *
 *@param	disp	���C����ʂɂ�����:MASK_MAIN_DISPLAY
 *					�T�u��ʂɂ�����:MASK_SUB_DISPLAY
 *					����ʂɂ�����:MASK_DOUBLE_DISPLAY
 *@param	bright_color		��ײ�Ƚ�J���[
 *@param	sub_bright_color	�T�u����ײ�Ƚ�J���[
 *@param	end		�I��������TRUE��Ԃ��t���O
 *@param	flash_num			�t���b�V����
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void EncountFlashTask(int disp, u32 bright_color, u32 sub_bright_color, BOOL* end, u32 flash_num);

//-------------------------------------
//
//	H�u�����N�p�֐��S
//
//=====================================
// H�u�����N�I���`�F�b�N
GLOBAL BOOL ENC_HBlankEndCheck( ENCOUNT_EFFECT_WORK* p_work );

// ���ɉ�ʂ�����
GLOBAL void ENC_BG_Cut_Start(ENCOUNT_EFFECT_WORK* p_ew);

// �h�b�g�P�ʂŉ�ʂ����ɐ؂�
typedef struct _ENC_HB_BG_SLICE ENC_HB_BG_SLICE;

GLOBAL ENC_HB_BG_SLICE* ENC_BG_Slice_Alloc( void );
GLOBAL void ENC_BG_Slice_Delete( ENC_HB_BG_SLICE* p_work );
GLOBAL void ENC_BG_Slice_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_SLICE* p_eff, u8 dot, u32 sync, int s_x, int e_x, fx32 s_s );
GLOBAL void ENC_BG_Slice_Change( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_SLICE* p_eff, u8 dot, u32 sync, int s_x, int e_x, fx32 s_s );

// �E�B���h�E�Ŏ΂߂ɉ�ʂ��B���Ă���
typedef struct _ENC_HB_BG_WND_SLANT ENC_HB_BG_WND_SLANT;

GLOBAL ENC_HB_BG_WND_SLANT* ENC_BG_WndSlant_Alloc( void );
GLOBAL void ENC_BG_WndSlant_Delete( ENC_HB_BG_WND_SLANT* p_work );
GLOBAL void ENC_BG_WndSlant_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_WND_SLANT* p_eff, u32 sync, fx32 x_ss, fx32 y_ss );

// �J�b�g�C���p�@�W�O�U�O�E�B���h�E
typedef struct _ENC_HB_BG_WND_ZIGUZAGU	ENC_HB_BG_WND_ZIGUZAGU;

GLOBAL ENC_HB_BG_WND_ZIGUZAGU* ENC_BG_WndZiguzagu_Alloc( void );
GLOBAL void ENC_BG_WndZiguzagu_Delete( ENC_HB_BG_WND_ZIGUZAGU* p_work );
GLOBAL void ENC_BG_WndZiguzagu_Start( ENCOUNT_EFFECT_WORK* p_ew, ENC_HB_BG_WND_ZIGUZAGU* p_eff, u32 sync, u32 dot, u32 width, u32 wnd_msk_in, u32 wnd_msk_out );



//-------------------------------------
//	
//	Ͻ���u���C�g�l�X�֘A
//	
//=====================================
typedef struct {
	ENC_MOVE_WORK brightness;
	int disp;
} BR_BRIGHTNESS_FADE;
GLOBAL void ENC_SetMstBrightness( int disp, int no );
GLOBAL void ENC_ChangeMstBrightness( BR_BRIGHTNESS_FADE* p_data, int start, int end, int disp, int sync );
GLOBAL BOOL ENC_ChangeMstBrightnessMain( BR_BRIGHTNESS_FADE* p_data );
GLOBAL void ENC_V_SetMstBrightness( int disp, int no );


//-----------------------------------------------------------------------------
/**
 *
 *		BG�ݒ�֘A
 *
 */
//-----------------------------------------------------------------------------
#define ENC_BG_AFFINE_FRAME		( GF_BGL_FRAME3_M )

GLOBAL void ENC_BG_SetAffineCont( GF_BGL_INI* p_bgl );	// ����ŃA�t�B��BG�����悤�ł���悤�ɕύX����@�ύX��1�V���N�g�p����
GLOBAL void ENC_BG_SetAffineBG( u32 scrn_idx, u32 char_idx, u32 pltt_idx, GF_BGL_INI* p_bgl );
GLOBAL void ENC_BG_SetNormalBG( u32 scrn_idx, u32 char_idx, u32 pltt_idx, u32 pltt_no, u32 pltt_num, GF_BGL_INI* p_bgl, u32 frame );

typedef struct {
	GF_BGL_INI* p_bgl;
	MtxFx22 mtx;
	u32 frame;
	int cx;
	int cy;
	int sc_x;
} ENC_BG_SET_AFFINEPARAM;
#define ENC_BG_SET_AFFINE_MTX_PRI	( 1024 )
GLOBAL void ENC_BG_SetAffineMtx( ENC_BG_SET_AFFINEPARAM* p_work, GF_BGL_INI* p_bgl, u32 frame, fx32 scale_x, fx32 scale_y, u16 rota, int cx, int cy, int sc_x );


// �r�b�g�}�b�v�E�B���h�E�h��Ԃ��I�u�W�F�N�g
typedef struct _ENC_BMP_FILL_OBJ ENC_BMP_FILL_OBJ;

GLOBAL ENC_BMP_FILL_OBJ* ENC_BMP_FillObjAlloc( u32 heapID );
GLOBAL void ENC_BMP_FillObjDelete( ENC_BMP_FILL_OBJ* p_work );
GLOBAL void ENC_BMP_FillObjStart( ENC_BMP_FILL_OBJ* p_work, int s_x, int e_x, int s_y, int e_y, int sync, GF_BGL_BMPWIN* p_bmp, u32 width, u32 height, u8 col );
GLOBAL BOOL ENC_BMP_FillObjMain( ENC_BMP_FILL_OBJ* p_work );

// �r�b�g�}�b�v�u���b�N��h��Ԃ��I�u�W�F�N�g
typedef struct _ENC_BMP_FILL_BLOCK ENC_BMP_FILL_BLOCK;

GLOBAL ENC_BMP_FILL_BLOCK* ENC_BMP_FillBlockAlloc( u32 heapID );
GLOBAL void ENC_BMP_FillBlockDelete( ENC_BMP_FILL_BLOCK* p_work );
GLOBAL void ENC_BMP_FillBlockStart( ENC_BMP_FILL_BLOCK* p_work, int s_x, int e_x, int s_y, int e_y, int sync, GF_BGL_BMPWIN* p_bmp, u32 width, u32 height, u8 col );
GLOBAL BOOL ENC_BMP_FillBlockMain( ENC_BMP_FILL_BLOCK* p_work );

// �r�b�g�}�b�v�u���b�N���ߐs�����V�X�e��
typedef struct _ENC_BMP_FILL_BLOCK_MOVE ENC_BMP_FILL_BLOCK_MOVE;

GLOBAL ENC_BMP_FILL_BLOCK_MOVE* ENC_BMP_FillBlockMoveAlloc( u32 heapID );
GLOBAL void ENC_BMP_FillBlockMoveDelete( ENC_BMP_FILL_BLOCK_MOVE* p_work );
GLOBAL void ENC_BMP_FillBlockMoveStart( ENC_BMP_FILL_BLOCK_MOVE* p_work, u8 sync, u8 start, GF_BGL_BMPWIN* p_bmp, u8 col );
GLOBAL BOOL ENC_BMP_FillBlockMoveMain( ENC_BMP_FILL_BLOCK_MOVE* p_work );

// �~�`BMP�h��Ԃ��I�u�W�F�N�g
typedef struct _ENC_BMP_CIRCLE_FILL ENC_BMP_CIRCLE_FILL;

GLOBAL ENC_BMP_CIRCLE_FILL* ENC_BMP_CircleFillAlloc( u32 heapID );
GLOBAL void ENC_BMP_CircleFillDelete( ENC_BMP_CIRCLE_FILL* p_work );
GLOBAL void ENC_BMP_CircleFillStart( ENC_BMP_CIRCLE_FILL* p_work, u8 sync, u16 s_rota, u16 e_rota, GF_BGL_BMPWIN* p_bmp, u8 col );
GLOBAL BOOL ENC_BMP_CircleFillMain( ENC_BMP_CIRCLE_FILL* p_work );


// �t���b�V���A�E�g�@�I�u�W�F
typedef struct _ENC_BMP_FLASH_OUT ENC_BMP_FLASH_OUT;
GLOBAL ENC_BMP_FLASH_OUT* ENC_BMP_FlashOutAlloc( u32 heapID );
GLOBAL void ENC_BMP_FlashOutDelete( ENC_BMP_FLASH_OUT* p_work );
GLOBAL void ENC_BMP_FlashOutStart( ENC_BMP_FLASH_OUT* p_work, u8 sync, GF_BGL_BMPWIN* p_bmp, u8 col );
GLOBAL BOOL ENC_BMP_FlashOutMain( ENC_BMP_FLASH_OUT* p_work );


//-----------------------------------------------------------------------------
/**
 *
 *		OAM�ݒ�֘A
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�Z���A�N�^�[�p�b�N
//=====================================
typedef struct {
	CLACT_SET_PTR	cas;
	CLACT_U_EASYRENDER_DATA	renddata;	// �ȈՃ����_�[�f�[�^
	CLACT_U_RES_MANAGER_PTR	resMan[4];	// ���\�[�X�}�l�[�W��
} ENC_CLACT_SYS;
//-------------------------------------
//	�Z���A�N�^�[���\�[�X�I�u�W�F�p�b�N
//=====================================
typedef struct {
	CLACT_U_RES_OBJ_PTR resobj[4];
	CLACT_HEADER head;
} ENC_CLACT_RES_WORK;

// �V�X�e��������
GLOBAL void ENC_CLACT_Init( ENC_CLACT_SYS* p_sys, int work_num, int res_num );
GLOBAL void ENC_CLACT_Delete( ENC_CLACT_SYS* p_sys );

// �ȒP���\�[�X�ǂݍ���
GLOBAL void ENC_CLACT_ResLoadEasy( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work, u32 pltt_idx, u32 pltt_num, u32 char_idx, u32 cel_idx, u32 anm_idx, u32 cont_id );
GLOBAL void ENC_CLACT_ResDeleteEasy( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work );
GLOBAL void ENC_CLACT_ResColorChange( CLACT_WORK_PTR clact, u32 heap, u32 tr_type, u8 evy, u16 next_rgb );

// �A�N�^�[�o�^
GLOBAL CLACT_WORK_PTR ENC_CLACT_Add( ENC_CLACT_SYS* p_sys, ENC_CLACT_RES_WORK* p_work, fx32 x, fx32 y, fx32 z, int pri );

// OAM�ėp
GLOBAL VecFx32 ENC_MakeVec( fx32 x, fx32 y, fx32 z );

// �\�t�g�E�F�A�X�v���C�g�L�����N�^�f�[�^�̓]��
#define ENC_OAM_TR_CHAR_CUT_CX	( 1 )	// ���ꂾ�����炵���Ƃ��납�甲���o��
GLOBAL void ENC_CLACT_ResSetSoftSpriteDataTrOam( CLACT_WORK_PTR clact, u32 heap, u32 tr_type, u8 evy, u16 next_rgb, u32 ofs_cx );

// OAM�ʂ��E�B���h�E����`�Őݒ�
typedef struct{
	u8 x1;
	u8 x2;
	u8 y1;
	u8 y2;
	u8 wnd_no;
	u8 dummy[3];
} ENC_WND_SETPOSITION;
#define ENC_SET_WND_SCALE_TCB_PRI	( 1024 )
GLOBAL void ENC_WND_SetScaleWnd( fx32 y, int bottom_y, fx32 scale, int height, int wndno, ENC_WND_SETPOSITION* p_work );
GLOBAL int ENC_WND_SetScaleWndToolMakeBottomY( fx32 scale, int c_y, int half_height );

// V�u�����NMaster�P�x����^�X�N
#define ENC_SET_MSTBRI_TCB_PRI	( 1024 )
GLOBAL void ENC_SetMasterBrightnessVblank( int* p_setnum );


#undef	GLOBAL
#endif		// __ECCOUNT_EFFECT_DEF_H__

