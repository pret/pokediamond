//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		touchpanel_draw.h
 *@brief	タッチパネル情報を表示する
 *@author	tomoya takahashi
 *@data		2005.03.29
 *
 *	gflib/touchpanel_systemから移植
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#ifndef __TOUCHPANEL_DRAW_H__
#define	__TOUCHPANEL_DRAW_H__

#undef	GLOBAL
#ifdef	__TOUCHPANEL_DRAW_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------
#define		TP_WIN_CGX		( 1024 )		// ウィンドウ設定の値

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
/// ブラシデータ構造体
typedef struct
{
	u16* pCharData;			// ブラシデータ			
				
	u16 SizeX;				// サイズX
	u16 SizeY;				// サイズY
} TP_BRUSH_DATA;


//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
/// タッチペン情報を渡して描画するシステム
GLOBAL void DrawTPInit( GF_BGL_INI* bgl, int gf_bgl_frame, u32 width, u32 height, u32 x, u32 y, const u16* p_pltt, int heap );	// 描画設定関数
GLOBAL void DrawTPDelete(GF_BGL_INI* bgl, u16 pltt );							// 描画システム破棄関数
GLOBAL void DrawTPChgPltt( int gf_bgl_frame, const u16* p_pltt );									// パレットを変える
GLOBAL void DrawTP(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA brush_data, u16 check_num );	// サイズのTPデータを描画する
GLOBAL void DrawTPInOut(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
						 u16 check_num, TP_PICTURE_DATA* pData );						// 内外判定をする描画
GLOBAL u32 DrawTPSync(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA brush_data, u16 check_num, u16 sync, u32* p_count );
GLOBAL void DrawTPLine(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA brush_data, u16 check_num );			// 線を描画
GLOBAL void DrawTPLineInOut(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
							 u16 check_num, TP_PICTURE_DATA* pData );					// 内外判定をする描画
GLOBAL void DrawTPPoint(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA brush_data );						// 点を描画
GLOBAL void DrawTPClean(GF_BGL_INI* bgl, u16 pltt_num );						// クリア
GLOBAL void DrawTPPaste( GF_BGL_INI* bgl );								// 実際に画面に描画(上の関数を使用した跡に
																// 行う必要がある)
GLOBAL void DrawTPOldMatDest( void );							// 保存している１つ前の座用を破棄する
																// 新しく線を描くときに使用する
GLOBAL void MakeTPBrush( TP_BRUSH_DATA* p_brush, u16 pltt, u16 size_x, u16 size_y, int heap );			// ブラシデータを作成
GLOBAL void MakeTPGraphicBrush( TP_BRUSH_DATA* p_brush, const u16* p_char, u16 size_x, u16 size_y, int heap );	// 絵のブラシデータを作成
GLOBAL void DestTPBrush( TP_BRUSH_DATA* p_brush );		// ブラシデータを破棄


//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------

#undef	GLOBAL
#endif

