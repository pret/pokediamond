//****************************************************************************
/**
 *
 *@file		touchpanel.c
 *@brief	矩形とタッチパネルシステム情報との当たり判定処理
 *@author	taya
 *@data		2005.07.29
 *
 */
//****************************************************************************

#include "common.h"

#define __TOUCHPANEL_H_GLOBAL__
#include "gflib/touchpanel.h"


//==============================================================
// Prototype
//==============================================================
static int recthit( const RECT_HIT_TBL* pTbl, u32 x, u32 y );
static BOOL circle_hitcheck( const TP_HIT_TBL *tbl, u32 x, u32 y );
static BOOL rect_hitcheck( const TP_HIT_TBL *tbl, u32 x, u32 y );


//----------------------------------------------------------------------------
/**
 *
 *@brief	矩形の当たり判定	
 *
 *@param	pTbl		当たり判定テーブル
 *@param	u32	x		タッチパネルx座標
 *@param	u32 y		タッチパネルy座標
 *
 *@return	int	ヒットしたテーブルのインデックスナンバー
 *				ヒットするデータが無いときはRECT_HIT_NONE
 *
 */
//-----------------------------------------------------------------------------
static int recthit( const RECT_HIT_TBL* pTbl, u32 x, u32 y )
{
	int c;

	for(c = 0; pTbl[c].rect.top != RECT_HIT_END; c++)
	{
		if( ((u32)( x - pTbl[c].rect.left) < (u32)(pTbl[c].rect.right - pTbl[c].rect.left))
		&	((u32)( y - pTbl[c].rect.top) < (u32)(pTbl[c].rect.bottom - pTbl[c].rect.top))
		){
			return c;
		}
	}

	return RECT_HIT_NONE;
}

//------------------------------------------------------------------
/**
 * 円形としての当たり判定（単発）
 *
 * @param   tbl		当たり判定テーブル
 * @param   x		X座標
 * @param   y		Y座標
 *
 * @retval  BOOL	TRUEで当たり
 */
//------------------------------------------------------------------
static BOOL circle_hitcheck( const TP_HIT_TBL *tbl, u32 x, u32 y )
{
	x = (tbl->circle.x - x) * (tbl->circle.x - x);
	y = (tbl->circle.y - y) * (tbl->circle.y - y);

	if( x + y < (tbl->circle.r * tbl->circle.r) )
	{
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * 矩形としての当たり判定（単発）
 *
 * @param   tbl		当たり判定テーブル
 * @param   x		Ｘ座標
 * @param   y		Ｙ座標
 *
 * @retval  BOOL		TRUEで当たり
 */
//------------------------------------------------------------------
static BOOL rect_hitcheck( const TP_HIT_TBL *tbl, u32 x, u32 y )
{
	if( ((u32)( x - tbl->rect.left) < (u32)(tbl->rect.right - tbl->rect.left))
	&	((u32)( y - tbl->rect.top) < (u32)(tbl->rect.bottom - tbl->rect.top))
	){
		return TRUE;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * 矩形当たり判定（テーブル使用、ベタ入力）
 *
 * @param   pRectTbl		当たり判定テーブル（終端コードあり）
 *
 * @retval  int		テーブル中、ヒットした要素のインデックスナンバー
 *					ヒットがなければ RECT_HIT_NONE
 */
//------------------------------------------------------------------
int GF_TP_RectHitCont( const RECT_HIT_TBL* pRectTbl )
{
	if( sys.tp_cont ){
		return recthit( pRectTbl, sys.tp_x, sys.tp_y );
	}
	return RECT_HIT_NONE;
}
//------------------------------------------------------------------
/**
 * 矩形当たり判定（テーブル使用、トリガ入力）
 *
 * @param   pRectTbl		当たり判定テーブル（終端コードあり）
 *
 * @retval  int		テーブル中、ヒットした要素のインデックスナンバー
 *					ヒットがなければ RECT_HIT_NONE
 */
//------------------------------------------------------------------
int GF_TP_RectHitTrg( const RECT_HIT_TBL *pRectTbl )
{
	if( sys.tp_trg ){
		return recthit( pRectTbl, sys.tp_x, sys.tp_y );
	}
	return RECT_HIT_NONE;
}
//------------------------------------------------------------------
/**
 * 両タイプ（矩形・円形）を見ながら判定する（ベタ入力）
 *
 * @param   tbl		当たり判定テーブル（終端コードあり）
 *
 * @retval  int		当たりがあればその要素番号、なければ TP_HIT_NONE
 */
//------------------------------------------------------------------
int GF_TP_HitCont( const TP_HIT_TBL *tbl )
{
	if( sys.tp_cont ){
		int i;

		for(i = 0; i < tbl[i].circle.code != TP_HIT_END; i++)
		{
			if( tbl[i].circle.code == TP_USE_CIRCLE )
			{
				if( circle_hitcheck( &tbl[i], sys.tp_x, sys.tp_y ) ){
					return i;
				}
			}
			else
			{
				if( rect_hitcheck( &tbl[i], sys.tp_x, sys.tp_y ) ){
					return i;
				}
			}
		}
	}
	return TP_HIT_NONE;
}
//------------------------------------------------------------------
/**
 * 両タイプ（矩形・円形）を見ながら判定する（トリガ入力）
 *
 * @param   tbl		当たり判定テーブル（終端コードあり）
 *
 * @retval  int		当たりがあればその要素番号、なければ TP_HIT_NONE
 */
//------------------------------------------------------------------
int GF_TP_HitTrg( const TP_HIT_TBL *tbl )
{
	if( sys.tp_trg ){
		int i;

		for(i = 0; i < tbl[i].circle.code != TP_HIT_END; i++)
		{
			if( tbl[i].circle.code == TP_USE_CIRCLE )
			{
				if( circle_hitcheck( &tbl[i], sys.tp_x, sys.tp_y ) ){
					return i;
				}
			}
			else
			{
				if( rect_hitcheck( &tbl[i], sys.tp_x, sys.tp_y ) ){
					return i;
				}
			}
		}
	}
	return TP_HIT_NONE;
}

//------------------------------------------------------------------
/**
 * 両タイプ（矩形・円形）を見ながら判定する（ベタ入力）
 *
 * @param   tbl		当たり判定テーブル（単発）
 *
 * @retval  BOOL	当たりならTRUE
 */
//------------------------------------------------------------------
BOOL GF_TP_SingleHitCont( const TP_HIT_TBL *tbl )
{
	if( sys.tp_cont ){
		if( tbl->circle.code == TP_USE_CIRCLE )
		{
			return circle_hitcheck( tbl, sys.tp_x, sys.tp_y );
		}
		else
		{
			return rect_hitcheck( tbl, sys.tp_x, sys.tp_y );
		}
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * 両タイプ（矩形・円形）を見ながら判定する（トリガ入力）
 *
 * @param   tbl		当たり判定テーブル（単発）
 *
 * @retval  BOOL	当たりならTRUE
 */
//------------------------------------------------------------------
BOOL GF_TP_SingleHitTrg( const TP_HIT_TBL *tbl )
{
	if( sys.tp_trg ){
		if( tbl->circle.code == TP_USE_CIRCLE )
		{
			return circle_hitcheck( tbl, sys.tp_x, sys.tp_y );
		}
		else
		{
			return rect_hitcheck( tbl, sys.tp_x, sys.tp_y );
		}
	}
	return FALSE;
}


//------------------------------------------------------------------
/**
 * タッチパネルに触れているか
 *
 * @retval  BOOL		TRUEで触れている
 */
//------------------------------------------------------------------
BOOL GF_TP_GetCont( void )
{
	return sys.tp_cont;
}
//------------------------------------------------------------------
/**
 * タッチパネルに触れているか（トリガ）
 *
 * @retval  BOOL		TRUEで触れた
 */
//------------------------------------------------------------------
BOOL GF_TP_GetTrg( void )
{
	return sys.tp_trg;
}

//------------------------------------------------------------------
/**
 * タッチパネルに触れているならその座標取得（ベタ入力）
 *
 * @param   x		Ｘ座標受け取り変数アドレス
 * @param   y		Ｙ座標受け取り変数アドレス
 *
 * @retval  BOOL	TRUEで触れている。FALSEが返った場合、引数には何もしない。
 */
//------------------------------------------------------------------
BOOL GF_TP_GetPointCont( u32* x, u32* y )
{
	if( sys.tp_cont )
	{
		*x = sys.tp_x;
		*y = sys.tp_y;
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * タッチパネルに触れているならその座標取得（トリガ入力）
 *
 * @param   x		Ｘ座標受け取り変数アドレス
 * @param   y		Ｙ座標受け取り変数アドレス
 *
 * @retval  BOOL	TRUEで触れている。FALSEが返った場合、引数には何もしない。
 */
//------------------------------------------------------------------
BOOL GF_TP_GetPointTrg( u32* x, u32* y )
{
	if( sys.tp_trg )
	{
		*x = sys.tp_x;
		*y = sys.tp_y;
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	指定した座標で、当たり判定を行います。	複数
 *
 *	@param	tbl		当たり判定テーブル（配列）
 *	@param	x		判定ｘ座標
 *	@param	y		判定ｙ座標
 *
 *	@retval  int		当たりがあればその要素番号、なければ TP_HIT_NONE
 *
 *
 */
//-----------------------------------------------------------------------------
int GF_TP_HitSelf( const TP_HIT_TBL *tbl, u32 x, u32 y )
{
	int i;
	
	for(i = 0; i < tbl[i].circle.code != TP_HIT_END; i++)
	{
		if( tbl[i].circle.code == TP_USE_CIRCLE )
		{
			if( circle_hitcheck( &tbl[i], x, y ) ){
				return i;
			}
		}
		else
		{
			if( rect_hitcheck( &tbl[i], x, y ) ){
				return i;
			}
		}
	}
	return TP_HIT_NONE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	自分で指定した座標で当たり判定を行います。　単発
 *
 *	@param	tbl		当たり判定テーブル（単発）
 *	@param	x		当たり判定ｘ座標
 *	@param	y		当たり判定ｙ座標
 *
 *	@retval	TURE	あたった
 *	@retval	FALSE	あたらなかった
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL GF_TP_SingleHitSelf( const TP_HIT_TBL *tbl, u32 x, u32 y )
{
	if( tbl->circle.code == TP_USE_CIRCLE )
	{
		return circle_hitcheck( tbl, x, y );
	}
	else
	{
		return rect_hitcheck( tbl, x, y );
	}

	return FALSE;
}

