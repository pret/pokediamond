//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_encount_draw.h
 *	@brief		エンカウントデータ描画システム
 *	@author		tomoya takahashi
 *	@data		2006.02.09
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_ENCOUNT_DRAW_H__
#define __ZKN_ENCOUNT_DRAW_H__

#undef GLOBAL
#ifdef	__ZKN_ENCOUNT_DRAW_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//Tが斜め

enum{
	ZKN_ENCOUNT_DRAW_MUDDY_NONE,
	ZKN_ENCOUNT_DRAW_MUDDY_NORMAL,
	ZKN_ENCOUNT_DRAW_MUDDY_U,		// 上下左右
	ZKN_ENCOUNT_DRAW_MUDDY_D,
	ZKN_ENCOUNT_DRAW_MUDDY_L,
	ZKN_ENCOUNT_DRAW_MUDDY_R,
	ZKN_ENCOUNT_DRAW_MUDDY_UD,
	ZKN_ENCOUNT_DRAW_MUDDY_UL,
	ZKN_ENCOUNT_DRAW_MUDDY_UR,
	ZKN_ENCOUNT_DRAW_MUDDY_DL,
	ZKN_ENCOUNT_DRAW_MUDDY_DR,
	ZKN_ENCOUNT_DRAW_MUDDY_LR,
	ZKN_ENCOUNT_DRAW_MUDDY_UDL,
	ZKN_ENCOUNT_DRAW_MUDDY_UDR,
	ZKN_ENCOUNT_DRAW_MUDDY_ULR,
	ZKN_ENCOUNT_DRAW_MUDDY_DLR,
	ZKN_ENCOUNT_DRAW_MUDDY_UDLR,
	ZKN_ENCOUNT_DRAW_MUDDY_TUL,		// 斜め追加
	ZKN_ENCOUNT_DRAW_MUDDY_TUR,
	ZKN_ENCOUNT_DRAW_MUDDY_TDL,
	ZKN_ENCOUNT_DRAW_MUDDY_TDR,
	ZKN_ENCOUNT_DRAW_MUDDY_TULTUR,
	ZKN_ENCOUNT_DRAW_MUDDY_TULTDL,
	ZKN_ENCOUNT_DRAW_MUDDY_TULTDR,
	ZKN_ENCOUNT_DRAW_MUDDY_TURTDL,
	ZKN_ENCOUNT_DRAW_MUDDY_TURTDR,
	ZKN_ENCOUNT_DRAW_MUDDY_TDLTDR,
	ZKN_ENCOUNT_DRAW_MUDDY_TULTURTDL,
	ZKN_ENCOUNT_DRAW_MUDDY_TULTURTDR,
	ZKN_ENCOUNT_DRAW_MUDDY_TULTDLTDR,
	ZKN_ENCOUNT_DRAW_MUDDY_TURTDLTDR,
	ZKN_ENCOUNT_DRAW_MUDDY_TULTURTDLTDR,
	ZKN_ENCOUNT_DRAW_MUDDY_UTDLTDR,	// 上下左右1＆斜め2
	ZKN_ENCOUNT_DRAW_MUDDY_DTULTUR,	
	ZKN_ENCOUNT_DRAW_MUDDY_LTURTDR,	
	ZKN_ENCOUNT_DRAW_MUDDY_RTULTDL,	
	ZKN_ENCOUNT_DRAW_MUDDY_ULTDR,	// 上下左右2＆斜め1
	ZKN_ENCOUNT_DRAW_MUDDY_URTDL,
	ZKN_ENCOUNT_DRAW_MUDDY_DLTUR,
	ZKN_ENCOUNT_DRAW_MUDDY_DRTUL,
	ZKN_ENCOUNT_DRAW_MUDDY_UTDL,	// 上下左右1＆斜め1
	ZKN_ENCOUNT_DRAW_MUDDY_UTDR,
	ZKN_ENCOUNT_DRAW_MUDDY_DTUL,
	ZKN_ENCOUNT_DRAW_MUDDY_DTUR,
	ZKN_ENCOUNT_DRAW_MUDDY_LTUR,
	ZKN_ENCOUNT_DRAW_MUDDY_LTDR,
	ZKN_ENCOUNT_DRAW_MUDDY_RTUL,
	ZKN_ENCOUNT_DRAW_MUDDY_RTDL,
	ZKN_ENCOUNT_DRAW_MUDDY_CHIPNUM,
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_ENCOUNTDRAW_PrintChar( GF_BGL_BMPWIN * win, u8* char_buff, u16 char_sizex, u16 char_sizey, u8 grid_size, u8* p_buff, u8 size_x, u8 size_y, u16 win_x, u16 win_y );
GLOBAL void ZKN_ENCOUNTDRAW_MakeMuddyData( u8* p_buff, u8 size_x, u8 size_y );


#undef	GLOBAL
#endif		// __ZKN_ENCOUNT_DRAW_H__

