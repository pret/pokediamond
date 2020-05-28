//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_fontoam.h
 *	@brief		ふぉんとOAM作成システム
 *	@author		tomoya takahashi
 *	@data		2006.01.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_FONTOAM_H__
#define __ZKN_FONTOAM_H__

#include "include/gflib/bg_system.h"
#include "include/system/fontoam.h"
#include "include/gflib/char_manager.h"
#include "include/gflib/pltt_manager.h"

#undef GLOBAL
#ifdef	__ZKN_FONTOAM_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	図鑑フォントOAMデータ
//	
//=====================================
typedef struct {
	FONTOAM_OBJ_PTR p_fontoam;
	CHAR_MANAGER_ALLOCDATA char_data;
} ZKN_FONTOAM_DATA;

//-------------------------------------
//	
//	図鑑フォントOAMシステム
//	
//=====================================
typedef struct _ZKN_FONTOAM_SYS* ZKN_FONTOAM_SYS_PTR;
typedef const struct _ZKN_FONTOAM_SYS* CONST_ZKN_FONTOAM_SYS_PTR;

//-------------------------------------
//	
//	図鑑フォントOAMシステム初期化関数
//	
//=====================================
typedef struct {
	CLACT_SET_PTR clact_set;	// 使用するセルアクターセット
	GF_BGL_INI*		p_bg;		// bgシステム
	int work_num;		// 登録最大数
	int heap;			// ヒープ
} ZKN_FONTOAM_SYS_INIT;


//-------------------------------------
//	
//	フォントデータ登録構造体
//	
//=====================================
typedef struct {
	ZKN_FONTOAM_SYS_PTR zkn_fontoam;	// fontoamシステム
	const GF_BGL_BMPWIN*	p_bmp;		// ビットマップデータ
	const NNSG2dImagePaletteProxy* pltt;// セル参照先パレットプロクシ
	CONST_CLACT_WORK_PTR	parent;		// 親のアクター		いらないときNULL	（ボタンなど）
	int					x;				// 登録ｘ座標		親アクターがあるときは親からのオフセットｙ座標	(dot単位)
	int					y;				// 登録ｙ座標		親アクターがあるときは親からのオフセットｙ座標	(dot単位)
	int					bg_pri;			// bg優先順位
	int					soft_pri;		// ソフト優先順位
	int					draw_area;		// 表示先
	/*
		NNS_G2D_VRAM_TYPE_2DMAIN    ２ＤグラフィックスエンジンＡ用
		NNS_G2D_VRAM_TYPE_2DSUB     ２ＤグラフィックスエンジンＢ用*/
	int					heap;			// 使用するヒープ	
} ZKN_FONTOAM_INIT;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL ZKN_FONTOAM_SYS_PTR ZKN_FONTOAM_InitSys( const ZKN_FONTOAM_SYS_INIT* cp_init );
GLOBAL void ZKN_FONTOAM_DeleteSys( ZKN_FONTOAM_SYS_PTR fontoam_sys );

GLOBAL ZKN_FONTOAM_DATA* ZKN_FONTOAM_Make( const ZKN_FONTOAM_INIT* cp_init );
GLOBAL ZKN_FONTOAM_DATA* ZKN_FONTOAM_MakeCharOfs( const ZKN_FONTOAM_INIT* cp_init, int char_size );
GLOBAL void ZKN_FONTOAM_Delete( ZKN_FONTOAM_DATA* p_fontoam );
GLOBAL void ZKN_FONTOAM_DeleteAll( ZKN_FONTOAM_SYS_PTR fontoam_sys );

GLOBAL GF_BGL_BMPWIN* ZKN_FONTOAM_GetBmp( ZKN_FONTOAM_SYS_PTR fontoam_sys, int bmp_x, int bmp_y );
GLOBAL void ZKN_FONTOAM_DeleteBmp( GF_BGL_BMPWIN* win );
GLOBAL void ZKN_FONTOAM_PrintBmpStr( ZKN_FONTOAM_SYS_PTR fontoam_sys, GF_BGL_BMPWIN* win, u32 dataid, u32 msgid, int bmp_x, int bmp_y );
GLOBAL void ZKN_FONTOAM_PrintBmpStrBuf( ZKN_FONTOAM_SYS_PTR fontoam_sys, GF_BGL_BMPWIN* win, STRBUF* str, int bmp_x, int bmp_y );



#undef	GLOBAL
#endif		// __ZKN_FONTOAM_H__

