//*****************************************************************************
/**
 *
 *@file		touchpanel.h
 *@brief	�^�b�`�p�l���f�[�^����
 *@author	tomoya takahashi
 *@data		2005.03.16
 */
//*****************************************************************************

#ifndef __TOUCHPANEL_H__
#define	__TOUCHPANEL_H__

#undef	GLOBAL
#ifdef	__TOUCHPANEL_H_GLOBAL__
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------
#define		RECT_HIT_END	(0xff)			// �I���R�[�h
#define		RECT_HIT_NONE	(0xffffffff)	// ���������e�[�u���Ȃ�

#define		TP_HIT_END		(0xff)			// ���������e�[�u���Ȃ�
#define		TP_USE_CIRCLE	(0xfe)			// �~�`�Ƃ��Ďg��
#define		TP_HIT_NONE		(0xffffffff)	// ���������e�[�u���Ȃ��iRECT_HIT_NONE�͂���������j

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	��`�f�[�^�\����
//=====================================
typedef union{
	struct {
		u8	top;	// ��i�������͓���R�[�h�j
		u8	bottom;	// ��
		u8	left;	// ��
		u8	right;	// �E
	}rect;

	struct {
		u8	code;	// TP_USE_CIRCLE ���w��
		u8	x;
		u8	y;
		u8	r;
	}circle;

}RECT_HIT_TBL, TP_HIT_TBL;

/*
 * �g�p��
 *
 * RECT_HIT_TBL rect_data[] ={
 *		{0,64,0,128},				// �z��v�f�D�揇��:0>1>2>3>4>.....�ł�
 *		{128,191,0,64},
 *		{32,94,129,200},
 *		{0,191,0,255},
 *      {TP_USE_CIRCLE, 100, 80, 16 },	// �~�`�Ƃ��Ďg���B
 *		{TP_HIT_END,0,0,0},		// �I���f�[�^
 * };
 * 
 */


//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//----------------------------------------------------------------------------
GLOBAL int GF_TP_RectHitCont( const RECT_HIT_TBL* pRectTbl );
GLOBAL int GF_TP_RectHitTrg( const RECT_HIT_TBL *pRectTbl );
GLOBAL int GF_TP_HitCont( const TP_HIT_TBL *tbl );
GLOBAL int GF_TP_HitTrg( const TP_HIT_TBL *tbl );
GLOBAL BOOL GF_TP_SingleHitCont( const TP_HIT_TBL *tbl );
GLOBAL BOOL GF_TP_SingleHitTrg( const TP_HIT_TBL *tbl );
GLOBAL BOOL GF_TP_GetCont( void );
GLOBAL BOOL GF_TP_GetTrg( void );
GLOBAL int GF_TP_RectHitContSelf( const RECT_HIT_TBL* pRectTbl, u32 x, u32 y );
GLOBAL int GF_TP_HitSelf( const TP_HIT_TBL *tbl, u32 x, u32 y );
GLOBAL BOOL GF_TP_SingleHitSelf( const TP_HIT_TBL *tbl, u32 x, u32 y );
GLOBAL BOOL GF_TP_GetPointCont( u32* x, u32* y );
GLOBAL BOOL GF_TP_GetPointTrg( u32* x, u32* y );


#undef	GLOBAL
#endif

