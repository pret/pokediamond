//============================================================================================
/**
 * @file	point_sel.c
 * @brief	位置インデックス選択処理
 * @author	Hiroyuki Nakamura
 * @date	2004.11.12
 */
//============================================================================================
#define	POINT_SEL_H_GLOBAL

#include "system.h"
#include "point_sel.h"


//============================================================================================
//	シンボル定義
//============================================================================================


//============================================================================================
//	プロトタイプ宣言
//============================================================================================


//============================================================================================
//	グローバル変数
//============================================================================================


//--------------------------------------------------------------------------------------------
/**
 * パラメータ取得
 *
 * @param	pw		ワーク
 * @param	flg		取得フラグ
 *
 * @return	指定パラメータ
 */
//--------------------------------------------------------------------------------------------
u8 PointerWorkGet( const POINTER_WORK * pw, u8 flg )
{
	switch( flg ){
	case POINT_WK_PX:
		return pw->px;
	case POINT_WK_PY:
		return pw->py;
	case POINT_WK_SX:
		return pw->sx;
	case POINT_WK_SY:
		return pw->sy;
	case POINT_WK_UP:
		return pw->up;
	case POINT_WK_DOWN:
		return pw->down;
	case POINT_WK_LEFT:
		return pw->left;
	case POINT_WK_RIGHT:
		return pw->right;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 座標取得
 *
 * @param	pw		ワーク
 * @param	x		X座標格納場所
 * @param	y		Y座標格納場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PointerWkPosGet( const POINTER_WORK * pw, u8 * x, u8 * y )
{
	*x = pw->px;
	*y = pw->py;
}

//--------------------------------------------------------------------------------------------
/**
 * サイズ取得
 *
 * @param	pw		ワーク
 * @param	x		Xサイズ格納場所
 * @param	y		Yサイズ格納場所
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PointerWkSizeGet( const POINTER_WORK * pw, u8 * x, u8 * y )
{
	*x = pw->sx;
	*y = pw->sy;
}

//--------------------------------------------------------------------------------------------
/**
 * 移動方向を指定し、座標、サイズ、インデックスを取得する
 *
 * @param	pw		ワーク
 * @param	px		X座標格納場所
 * @param	py		Y座標格納場所
 * @param	sx		Xサイズ格納場所
 * @param	sy		Yサイズ格納場所
 * @param	now		現在のインデックス
 * @param	mv		移動方向
 *
 * @return	移動先のインデックス
 */
//--------------------------------------------------------------------------------------------
u8 PointerWkMoveSel(
		const POINTER_WORK * pw, u8 * px, u8 * py, u8 * sx, u8 * sy, u8 now, u8 mv )
{
	u8	next = now;

	switch( mv ){
	case POINT_MV_UP:
		next = pw[now].up;
		break;
	case POINT_MV_DOWN:
		next = pw[now].down;
		break;
	case POINT_MV_LEFT:
		next = pw[now].left;
		break;
	case POINT_MV_RIGHT:
		next = pw[now].right;
		break;
	}
	if( px != NULL ){ *px = pw[next].px; }
	if( py != NULL ){ *py = pw[next].py; }
	if( sx != NULL ){ *sx = pw[next].sx; }
	if( sy != NULL ){ *sy = pw[next].sy; }

	return next;
}

//--------------------------------------------------------------------------------------------
/**
 * 十字キーの情報から、座標、サイズ、インデックスを取得する
 *
 * @param	pw		ワーク
 * @param	px		X座標格納場所
 * @param	py		Y座標格納場所
 * @param	sx		Xサイズ格納場所
 * @param	sy		Yサイズ格納場所
 * @param	now		現在のインデックス
 *
 * @return	移動先のインデックス（十字キーが押されていない場合はPOINT_SEL_NOMOVE）
 *
 * @li	sys.trgを使用
 */
//--------------------------------------------------------------------------------------------
u8 PointerWkMoveSelTrg( const POINTER_WORK * pw, u8 * px, u8 * py, u8 * sx, u8 * sy, u8 now )
{
	if( sys.trg & PAD_KEY_UP ){
		return PointerWkMoveSel( pw, px, py, sx, sy, now, POINT_MV_UP );
	}
	if( sys.trg & PAD_KEY_DOWN ){
		return PointerWkMoveSel( pw, px, py, sx, sy, now, POINT_MV_DOWN );
	}
	if( sys.trg & PAD_KEY_LEFT ){
		return PointerWkMoveSel( pw, px, py, sx, sy, now, POINT_MV_LEFT );
	}
	if( sys.trg & PAD_KEY_RIGHT ){
		return PointerWkMoveSel( pw, px, py, sx, sy, now, POINT_MV_RIGHT );
	}
	return POINT_SEL_NOMOVE;
}

//--------------------------------------------------------------------------------------------
/**
 * 座標を指定し、インデックスを取得する
 *
 * @param	pw		ワーク
 * @param	px		X座標
 * @param	py		Y座標
 * @param	siz		データサイズ
 *
 * @return	指定座標のインデックス
 */
//--------------------------------------------------------------------------------------------
u8 PointerWkMovePos( const POINTER_WORK * pw, u8 px, u8 py, u8 siz )
{
	u16	i;

	for( i=0; i<siz; i++ ){
		if( pw[i].px <= px && pw[i].px+pw[i].sx > px &&
			pw[i].py <= py && pw[i].py+pw[i].sy > py ){
			break;
		}
	}
	return (u8)i;
}
