//============================================================================================
/**
 * @file	bmp_cursor.h
 * @brief	BitmapWindowにメニュー選択用のカーソルを描画する仕組み
 * @author	taya
 * @date	2006.01.12
 */
//============================================================================================
#ifndef __BMP_CURSOR_H__
#define __BMP_CURSOR_H__

#include "gflib\msg_print.h"

typedef struct _BMPCURSOR	BMPCURSOR;


//------------------------------------------------------------------
/**
 * Bitmapカーソルを作成
 *
 * @param   heapID		作成先ヒープＩＤ
 *
 * @retval  BMPCURSOR*		作成されたカーソルオブジェクトへのポインタ
 */
//------------------------------------------------------------------
extern BMPCURSOR* BMPCURSOR_Create( u32 heapID );

//------------------------------------------------------------------
/**
 * Bitmapカーソルを破棄
 *
 * @param   bmpCursor		Bitmapカーソルオブジェクトへのポインタ
 */
//------------------------------------------------------------------
extern void BMPCURSOR_Delete( BMPCURSOR* bmpCursor );

//------------------------------------------------------------------
/**
 * Bitmapカーソルのカラー変更
 *
 * @param   bmpCursor		Bitmapカーソルオブジェクトへのポインタ
 * @param   color			カラー値（GF_PRINTCOLOR_MAKEマクロを使用）
 *
 */
//------------------------------------------------------------------
extern void BMPCURSOR_ChangeColor( BMPCURSOR* bmpCursor, GF_PRINTCOLOR color );

//------------------------------------------------------------------
/**
 * BitmapカーソルをBitmapWindowに描画する
 *
 * @param   bmpCursor	Bitmapカーソルオブジェクトへのポインタ
 * @param   win			BitmapWindow
 * @param   x			描画Ｘ座標（ドット単位）
 * @param   y			描画Ｙ座標（ドット単位）
 *
 */
//------------------------------------------------------------------
extern void BMPCURSOR_Print( const BMPCURSOR* bmpCursor, GF_BGL_BMPWIN* win, u32 x, u32 y );



#endif

