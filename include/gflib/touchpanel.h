//*****************************************************************************
/**
 *
 *@file		touchpanel.h
 *@brief	タッチパネルデータ処理
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
 *					定数宣言
 */
//-----------------------------------------------------------------------------
#define		RECT_HIT_END	(0xff)			// 終了コード
#define		RECT_HIT_NONE	(0xffffffff)	// あたったテーブルなし

#define		TP_HIT_END		(0xff)			// あたったテーブルなし
#define		TP_USE_CIRCLE	(0xfe)			// 円形として使う
#define		TP_HIT_NONE		(0xffffffff)	// あたったテーブルなし（RECT_HIT_NONEはいずれ消す）

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	矩形データ構造体
//=====================================
typedef union{
	struct {
		u8	top;	// 上（もしくは特殊コード）
		u8	bottom;	// 下
		u8	left;	// 左
		u8	right;	// 右
	}rect;

	struct {
		u8	code;	// TP_USE_CIRCLE を指定
		u8	x;
		u8	y;
		u8	r;
	}circle;

}RECT_HIT_TBL, TP_HIT_TBL;

/*
 * 使用例
 *
 * RECT_HIT_TBL rect_data[] ={
 *		{0,64,0,128},				// 配列要素優先順位:0>1>2>3>4>.....です
 *		{128,191,0,64},
 *		{32,94,129,200},
 *		{0,191,0,255},
 *      {TP_USE_CIRCLE, 100, 80, 16 },	// 円形として使う。
 *		{TP_HIT_END,0,0,0},		// 終了データ
 * };
 * 
 */


//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
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

