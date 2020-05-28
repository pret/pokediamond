//============================================================================================
/**
 * @file	b_bag_bmp_def.h
 * @brief	�퓬�p�o�b�O��� BMP��`
 * @author	Hiroyuki Nakamura
 * @date	05.02.13
 */
//============================================================================================
#define TALK_WIN_CGX_POS	( 1024-TALK_WIN_CGX_SIZ )	// ��b�E�B���h�ECGX�ʒu

// ���b�Z�[�W�\��
#define	WIN_TALK_FRM		( GF_BGL_FRAME0_S )
#define	WIN_TALK_PX			( 2 )
#define	WIN_TALK_PY			( 19 )
#define	WIN_TALK_SX			( 27 )
#define	WIN_TALK_SY			( 4 )
#define	WIN_TALK_PAL		( BBAG_PAL_TALK_FONT )
#define	WIN_TALK_CGX		( TALK_WIN_CGX_POS - WIN_TALK_SX * WIN_TALK_SY )


//============================================================================================
//	�y�[�W�P
//============================================================================================
// �u���傤���������ӂ��v
#define	WIN_P1_ZYOUTAI_FRM	( GF_BGL_FRAME0_S )
#define	WIN_P1_ZYOUTAI_PX	( 2 )
#define	WIN_P1_ZYOUTAI_PY	( 13 )
#define	WIN_P1_ZYOUTAI_SX	( 12 )
#define	WIN_P1_ZYOUTAI_SY	( 5 )
#define	WIN_P1_ZYOUTAI_PAL	( BBAG_PAL_BTN_FONT )
#define	WIN_P1_ZYOUTAI_CGX	( WIN_TALK_CGX - WIN_TALK_SX * WIN_TALK_SY )
// �uHP/PP�����ӂ��v
#define	WIN_P1_HP_FRM		( GF_BGL_FRAME0_S )
#define	WIN_P1_HP_PX		( 2 )
#define	WIN_P1_HP_PY		( 4 )
#define	WIN_P1_HP_SX		( 12 )
#define	WIN_P1_HP_SY		( 5 )
#define	WIN_P1_HP_PAL		( BBAG_PAL_BTN_FONT )
#define	WIN_P1_HP_CGX		( WIN_P1_ZYOUTAI_CGX - WIN_P1_HP_SX * WIN_P1_HP_SY )
// �u����Ƃ��悤�v
#define	WIN_P1_BATTLE_FRM	( GF_BGL_FRAME0_S )
#define	WIN_P1_BATTLE_PX	( 18 )
#define	WIN_P1_BATTLE_PY	( 14 )
#define	WIN_P1_BATTLE_SX	( 12 )
#define	WIN_P1_BATTLE_SY	( 3 )
#define	WIN_P1_BATTLE_PAL	( BBAG_PAL_BTN_FONT )
#define	WIN_P1_BATTLE_CGX	( WIN_P1_HP_CGX - WIN_P1_BATTLE_SX * WIN_P1_BATTLE_SY )
// �u�{�[���v
#define	WIN_P1_BALL_FRM		( GF_BGL_FRAME0_S )
#define	WIN_P1_BALL_PX		( 18 )
#define	WIN_P1_BALL_PY		( 5 )
#define	WIN_P1_BALL_SX		( 12 )
#define	WIN_P1_BALL_SY		( 3 )
#define	WIN_P1_BALL_PAL		( BBAG_PAL_BTN_FONT )
#define	WIN_P1_BALL_CGX		( WIN_P1_BATTLE_CGX - WIN_P1_BALL_SX * WIN_P1_BALL_SY )
// �u�������ɂ������ǂ����v
#define	WIN_P1_LASTITEM_FRM	( GF_BGL_FRAME0_S )
#define	WIN_P1_LASTITEM_PX	( 5 )
#define	WIN_P1_LASTITEM_PY	( 20 )
#define	WIN_P1_LASTITEM_SX	( 20 )
#define	WIN_P1_LASTITEM_SY	( 3 )
#define	WIN_P1_LASTITEM_PAL	( BBAG_PAL_BTN_FONT )
#define	WIN_P1_LASTITEM_CGX	( WIN_P1_BALL_CGX - WIN_P1_LASTITEM_SX * WIN_P1_LASTITEM_SY )

//============================================================================================
//	�y�[�W�Q
//============================================================================================
// ����P
#define	WIN_P2_NAME1_FRM	( GF_BGL_FRAME1_S )
#define	WIN_P2_NAME1_PX		( 1 )
#define	WIN_P2_NAME1_PY		( 1 )
#define	WIN_P2_NAME1_SX		( 14 )
#define	WIN_P2_NAME1_SY		( 3 )
#define	WIN_P2_NAME1_PAL	( BBAG_PAL_BTN_FONT )
#define	WIN_P2_NAME1_CGX	( 1 )
// ����P
#define	WIN_P2_NUM1_FRM		( GF_BGL_FRAME1_S )
#define	WIN_P2_NUM1_PX		( 8 )
#define	WIN_P2_NUM1_PY		( 4 )
#define	WIN_P2_NUM1_SX		( 4 )
#define	WIN_P2_NUM1_SY		( 3 )
#define	WIN_P2_NUM1_PAL		( BBAG_PAL_SYS_FONT )
#define	WIN_P2_NUM1_CGX		( WIN_P2_NAME1_CGX + WIN_P2_NAME1_SX * WIN_P2_NAME1_SY )
// ����Q
#define	WIN_P2_NAME2_FRM	( GF_BGL_FRAME1_S )
#define	WIN_P2_NAME2_PX		( 17 )
#define	WIN_P2_NAME2_PY		( 1 )
#define	WIN_P2_NAME2_SX		( 14 )
#define	WIN_P2_NAME2_SY		( 3 )
#define	WIN_P2_NAME2_PAL	( BBAG_PAL_BTN_FONT )
#define	WIN_P2_NAME2_CGX	( WIN_P2_NUM1_CGX + WIN_P2_NUM1_SX * WIN_P2_NUM1_SY )
// ����Q
#define	WIN_P2_NUM2_FRM		( GF_BGL_FRAME1_S )
#define	WIN_P2_NUM2_PX		( 24 )
#define	WIN_P2_NUM2_PY		( 4 )
#define	WIN_P2_NUM2_SX		( 4 )
#define	WIN_P2_NUM2_SY		( 3 )
#define	WIN_P2_NUM2_PAL		( BBAG_PAL_SYS_FONT )
#define	WIN_P2_NUM2_CGX		( WIN_P2_NAME2_CGX + WIN_P2_NAME2_SX * WIN_P2_NAME2_SY )
// ����R
#define	WIN_P2_NAME3_FRM	( GF_BGL_FRAME1_S )
#define	WIN_P2_NAME3_PX		( 1 )
#define	WIN_P2_NAME3_PY		( 7 )
#define	WIN_P2_NAME3_SX		( 14 )
#define	WIN_P2_NAME3_SY		( 3 )
#define	WIN_P2_NAME3_PAL	( BBAG_PAL_BTN_FONT )
#define	WIN_P2_NAME3_CGX	( WIN_P2_NUM2_CGX + WIN_P2_NUM2_SX * WIN_P2_NUM2_SY )
// ����R
#define	WIN_P2_NUM3_FRM		( GF_BGL_FRAME1_S )
#define	WIN_P2_NUM3_PX		( 8 )
#define	WIN_P2_NUM3_PY		( 10 )
#define	WIN_P2_NUM3_SX		( 4 )
#define	WIN_P2_NUM3_SY		( 3 )
#define	WIN_P2_NUM3_PAL		( BBAG_PAL_SYS_FONT )
#define	WIN_P2_NUM3_CGX		( WIN_P2_NAME3_CGX + WIN_P2_NAME3_SX * WIN_P2_NAME3_SY )
// ����S
#define	WIN_P2_NAME4_FRM	( GF_BGL_FRAME1_S )
#define	WIN_P2_NAME4_PX		( 17 )
#define	WIN_P2_NAME4_PY		( 7 )
#define	WIN_P2_NAME4_SX		( 14 )
#define	WIN_P2_NAME4_SY		( 3 )
#define	WIN_P2_NAME4_PAL	( BBAG_PAL_BTN_FONT )
#define	WIN_P2_NAME4_CGX	( WIN_P2_NUM3_CGX + WIN_P2_NUM3_SX * WIN_P2_NUM3_SY )
// ����S
#define	WIN_P2_NUM4_FRM		( GF_BGL_FRAME1_S )
#define	WIN_P2_NUM4_PX		( 24 )
#define	WIN_P2_NUM4_PY		( 10 )
#define	WIN_P2_NUM4_SX		( 4 )
#define	WIN_P2_NUM4_SY		( 3 )
#define	WIN_P2_NUM4_PAL		( BBAG_PAL_SYS_FONT )
#define	WIN_P2_NUM4_CGX		( WIN_P2_NAME4_CGX + WIN_P2_NAME4_SX * WIN_P2_NAME4_SY )
// ����T
#define	WIN_P2_NAME5_FRM	( GF_BGL_FRAME1_S )
#define	WIN_P2_NAME5_PX		( 1 )
#define	WIN_P2_NAME5_PY		( 13 )
#define	WIN_P2_NAME5_SX		( 14 )
#define	WIN_P2_NAME5_SY		( 3 )
#define	WIN_P2_NAME5_PAL	( BBAG_PAL_BTN_FONT )
#define	WIN_P2_NAME5_CGX	( WIN_P2_NUM4_CGX + WIN_P2_NUM4_SX * WIN_P2_NUM4_SY )
// ����T
#define	WIN_P2_NUM5_FRM		( GF_BGL_FRAME1_S )
#define	WIN_P2_NUM5_PX		( 8 )
#define	WIN_P2_NUM5_PY		( 16 )
#define	WIN_P2_NUM5_SX		( 4 )
#define	WIN_P2_NUM5_SY		( 3 )
#define	WIN_P2_NUM5_PAL		( BBAG_PAL_SYS_FONT )
#define	WIN_P2_NUM5_CGX		( WIN_P2_NAME5_CGX + WIN_P2_NAME5_SX * WIN_P2_NAME5_SY )
// ����U
#define	WIN_P2_NAME6_FRM	( GF_BGL_FRAME1_S )
#define	WIN_P2_NAME6_PX		( 17 )
#define	WIN_P2_NAME6_PY		( 13 )
#define	WIN_P2_NAME6_SX		( 14 )
#define	WIN_P2_NAME6_SY		( 3 )
#define	WIN_P2_NAME6_PAL	( BBAG_PAL_BTN_FONT )
#define	WIN_P2_NAME6_CGX	( WIN_P2_NUM5_CGX + WIN_P2_NUM5_SX * WIN_P2_NUM5_SY )
// ����U
#define	WIN_P2_NUM6_FRM		( GF_BGL_FRAME1_S )
#define	WIN_P2_NUM6_PX		( 24 )
#define	WIN_P2_NUM6_PY		( 16 )
#define	WIN_P2_NUM6_SX		( 4 )
#define	WIN_P2_NUM6_SY		( 3 )
#define	WIN_P2_NUM6_PAL		( BBAG_PAL_SYS_FONT )
#define	WIN_P2_NUM6_CGX		( WIN_P2_NAME6_CGX + WIN_P2_NAME6_SX * WIN_P2_NAME6_SY )

// ����P�i�X���b�v�p�j
#define	WIN_P2_NAME1_S_CGX	( WIN_P2_NUM6_CGX + WIN_P2_NUM6_SX * WIN_P2_NUM6_SY )
// ����P�i�X���b�v�p�j
#define	WIN_P2_NUM1_S_CGX	( WIN_P2_NAME1_S_CGX + WIN_P2_NAME1_SX * WIN_P2_NAME1_SY )
// ����Q�i�X���b�v�p�j
#define	WIN_P2_NAME2_S_CGX	( WIN_P2_NUM1_S_CGX + WIN_P2_NUM1_SX * WIN_P2_NUM1_SY )
// ����Q�i�X���b�v�p�j
#define	WIN_P2_NUM2_S_CGX	( WIN_P2_NAME2_S_CGX + WIN_P2_NAME2_SX * WIN_P2_NAME2_SY )
// ����R�i�X���b�v�p�j
#define	WIN_P2_NAME3_S_CGX	( WIN_P2_NUM2_S_CGX + WIN_P2_NUM2_SX * WIN_P2_NUM2_SY )
// ����R�i�X���b�v�p�j
#define	WIN_P2_NUM3_S_CGX	( WIN_P2_NAME3_S_CGX + WIN_P2_NAME3_SX * WIN_P2_NAME3_SY )
// ����S�i�X���b�v�p�j
#define	WIN_P2_NAME4_S_CGX	( WIN_P2_NUM3_S_CGX + WIN_P2_NUM3_SX * WIN_P2_NUM3_SY )
// ����S�i�X���b�v�p�j
#define	WIN_P2_NUM4_S_CGX	( WIN_P2_NAME4_S_CGX + WIN_P2_NAME4_SX * WIN_P2_NAME4_SY )
// ����T�i�X���b�v�p�j
#define	WIN_P2_NAME5_S_CGX	( WIN_P2_NUM4_S_CGX + WIN_P2_NUM4_SX * WIN_P2_NUM4_SY )
// ����T�i�X���b�v�p�j
#define	WIN_P2_NUM5_S_CGX	( WIN_P2_NAME5_S_CGX + WIN_P2_NAME5_SX * WIN_P2_NAME5_SY )
// ����U�i�X���b�v�p�j
#define	WIN_P2_NAME6_S_CGX	( WIN_P2_NUM5_S_CGX + WIN_P2_NUM5_SX * WIN_P2_NUM5_SY )
// ����U�i�X���b�v�p�j
#define	WIN_P2_NUM6_S_CGX	( WIN_P2_NAME6_S_CGX + WIN_P2_NAME6_SX * WIN_P2_NAME6_SY )
// �|�P�b�g��
#define	WIN_P2_POCKET_FRM	( GF_BGL_FRAME1_S )
#define	WIN_P2_POCKET_PX	( 11 )
#define	WIN_P2_POCKET_PY	( 19 )
#define	WIN_P2_POCKET_SX	( 10 )
#define	WIN_P2_POCKET_SY	( 5 )
#define	WIN_P2_POCKET_PAL	( BBAG_PAL_SYS_FONT )
#define	WIN_P2_POCKET_CGX	( WIN_P2_NUM6_S_CGX + WIN_P2_NUM6_SX * WIN_P2_NUM6_SY )
// �y�[�W���i�A�C�e�����j
#define	WIN_P2_PAGENUM_FRM	( GF_BGL_FRAME1_S )
#define	WIN_P2_PAGENUM_PX	( 22 )
#define	WIN_P2_PAGENUM_PY	( 20 )
#define	WIN_P2_PAGENUM_SX	( 4 )
#define	WIN_P2_PAGENUM_SY	( 3 )
#define	WIN_P2_PAGENUM_PAL	( BBAG_PAL_SYS_FONT )
#define	WIN_P2_PAGENUM_CGX	( WIN_P2_POCKET_CGX + WIN_P2_POCKET_SX * WIN_P2_POCKET_SY )


//============================================================================================
//	�y�[�W�R
//============================================================================================
// ���
#define	WIN_P3_NAME_FRM		( GF_BGL_FRAME1_S )
#define	WIN_P3_NAME_PX		( 7 )
#define	WIN_P3_NAME_PY		( 4 )
#define	WIN_P3_NAME_SX		( 12 )
#define	WIN_P3_NAME_SY		( 2 )
#define	WIN_P3_NAME_PAL		( BBAG_PAL_SYS_FONT )
#define	WIN_P3_NAME_CGX		( WIN_P2_PAGENUM_CGX + WIN_P2_PAGENUM_SX * WIN_P2_PAGENUM_SY )
// ��
#define	WIN_P3_NUM_FRM		( GF_BGL_FRAME1_S )
#define	WIN_P3_NUM_PX		( 20 )
#define	WIN_P3_NUM_PY		( 4 )
#define	WIN_P3_NUM_SX		( 4 )
#define	WIN_P3_NUM_SY		( 2 )
#define	WIN_P3_NUM_PAL		( BBAG_PAL_SYS_FONT )
#define	WIN_P3_NUM_CGX		( WIN_P3_NAME_CGX + WIN_P3_NAME_SX * WIN_P3_NAME_SY )
// ����
#define	WIN_P3_INFO_FRM		( GF_BGL_FRAME1_S )
#define	WIN_P3_INFO_PX		( 2 )
#define	WIN_P3_INFO_PY		( 9 )
#define	WIN_P3_INFO_SX		( 28 )
#define	WIN_P3_INFO_SY		( 6 )
#define	WIN_P3_INFO_PAL		( BBAG_PAL_SYS_FONT )
#define	WIN_P3_INFO_CGX		( WIN_P3_NUM_CGX + WIN_P3_NUM_SX * WIN_P3_NUM_SY )
// �u�����v
#define	WIN_P3_USE_FRM		( GF_BGL_FRAME1_S )
#define	WIN_P3_USE_PX		( 10 )
#define	WIN_P3_USE_PY		( 20 )
#define	WIN_P3_USE_SX		( 6 )
#define	WIN_P3_USE_SY		( 3 )
#define	WIN_P3_USE_PAL		( BBAG_PAL_BTN_FONT )
#define	WIN_P3_USE_CGX		( WIN_P3_INFO_CGX + WIN_P3_INFO_SX * WIN_P3_INFO_SY )
