//============================================================================================
/**
 * @file	numfont.h
 * @brief	数字フォント
 * @author	taya
 * @date	2005.09.30
 */
//============================================================================================
#ifndef __NUMFONT_H__
#define __NUMFONT_H__

#include  "system\pm_str.h"

//------------------------------------------------------
/**
 *	数字フォント実体構造体の型宣言（内容は非公開）
 */
//------------------------------------------------------
typedef   struct _NUMFONT    NUMFONT;

//------------------------------------------------------
/**
 *	数値描画モード
 */
//------------------------------------------------------
typedef enum {
	NUMFONT_MODE_LEFT = NUM_MODE_LEFT,		///< 左詰
	NUMFONT_MODE_SPACE = NUM_MODE_SPACE,	///< 右詰、足りない部分はスペース埋め
	NUMFONT_MODE_ZERO = NUM_MODE_ZERO,		///< 右詰、足りない部分はゼロ埋め
}NUMFONT_DRAW_MODE;

//------------------------------------------------------
/**
 *	記号種類
 */
//------------------------------------------------------
typedef enum {
	NUMFONT_MARK_SLASH,
	NUMFONT_MARK_LV,
	NUMFONT_MARK_NO,
	NUMFONT_MARK_ID,
	NUMFONT_MARK_MALE_LV,		// ♂記号とLVの混合（戦闘ゲージ専用）
	NUMFONT_MARK_FEMALE_LV,		// ♀記号とLVの混合（戦闘ゲージ専用）
	NUMFONT_MARK_BATTLE_LV,		// 最後にドットがつかないLV（戦闘ゲージ専用）
}NUMFONT_MARK;

//------------------------------------------------------
/**
 *	文字幅・高さ（定数）
 */
//------------------------------------------------------
enum {
	NUMFONT_NUM_WIDTH = 8,		///< 数字１桁分の幅
	NUMFONT_MARK_WIDTH = 16,	///< 記号１つ分の幅
	NUMFONT_HEIGHT = 8,			///< 高さ
};

//------------------------------------------------------------------
/**
 * 数字フォント作成
 *
 * @param   colLetter	文字色番号
 * @param   colShadow	影色番号
 * @param   colBack		背景色番号
 * @param   heapID		ヒープＩＤ
 *
 * @retval  NUMFONT*	数字フォント実体へのポインタ（内容は非公開）
 */
//------------------------------------------------------------------
extern NUMFONT*  NUMFONT_Create( u32 colLetter, u32 colShadow, u32 colBack, u32 heapID );


//------------------------------------------------------------------
/**
 * 数字フォント破棄
 *
 * @param   numfont		数字フォントポインタ
 *
 */
//------------------------------------------------------------------
extern void NUMFONT_Delete( NUMFONT* numfont );

//------------------------------------------------------------------
/**
 * 記号描画
 *
 * @param   numfont		数字フォントポインタ
 * @param   mark		記号種類
 * @param   win			描画先ウィンドウ
 * @param   x			描画先Ｘ座標（ドット）
 * @param   y			描画先Ｙ座標（ドット）
 *
 */
//------------------------------------------------------------------
extern void NUMFONT_WriteMark( NUMFONT* numfont, NUMFONT_MARK mark, GF_BGL_BMPWIN* win, u32 x, u32 y );

//------------------------------------------------------------------
/**
 * 数値描画
 *
 * @param   numfont		数字フォントポインタ
 * @param   num			数値
 * @param   keta		最大桁数
 * @param   mode		数値描画モード
 * @param   win			描画先ウィンドウ
 * @param   x			描画先Ｘ座標（ドット）
 * @param   y			描画先Ｙ座標（ドット）
 *
 */
//------------------------------------------------------------------
extern void NUMFONT_WriteNumber( NUMFONT* numfont, s32 num, u32 keta, NUMFONT_DRAW_MODE mode, GF_BGL_BMPWIN* win, u32 x, u32 y );

//------------------------------------------------------------------
/**
 * 記号・数値を並べて描画
 *
 * @param   numfont		数字フォントポインタ
 * @param   mark		記号種類
 * @param   num			数値
 * @param   keta		最大桁数
 * @param   mode		数値描画モード
 * @param   win			描画先ウィンドウ
 * @param   x			描画先Ｘ座標（ドット）
 * @param   y			描画先Ｙ座標（ドット）
 *
 */
//------------------------------------------------------------------
extern void NUMFONT_WriteSet( NUMFONT* numfont, NUMFONT_MARK mark, s32 num, u32 keta, NUMFONT_DRAW_MODE mode, GF_BGL_BMPWIN* win, u32 x, u32 y );

//------------------------------------------------------------------
/**
 * 数値描画(指定バッファに対してキャラクタデータのみ書き込み)
 *
 * @param   numfont		数字フォントポインタ
 * @param   num			数値
 * @param   keta		最大桁数
 * @param   mode		描画方式
 * @param   buf			描画先バッファ
 *
 */
//------------------------------------------------------------------
extern void NUMFONT_WriteNumberCGXOnly( NUMFONT* numfont, s32 num, u32 keta, 
	NUMFONT_DRAW_MODE mode, void *buf);

//--------------------------------------------------------------
/**
 * @brief   記号描画(指定バッファに対してキャラクタデータのみ書き込み)
 *
 * @param   numfont		数字フォントポインタ
 * @param   mark		記号タイプ
 * @param   buf			展開バッファ先へのポインタ
 *
 * @retval  
 *
 * bufは 「(NUMFONT_MARK_WIDTH / 8) * (NUMFONT_HEIGHT / 8) * 32」 のサイズが必要です。
 */
//--------------------------------------------------------------
extern void NUMFONT_WriteMarkCGXOnly( NUMFONT* numfont, NUMFONT_MARK mark, void *buf);

#endif
