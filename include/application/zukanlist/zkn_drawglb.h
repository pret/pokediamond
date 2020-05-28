//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_drawglb.h
 *	@brief		図鑑描画グローバルデータ
 *	@author		tomoya takahashi
 *	@data		2006.01.19
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_DRAWGLB_H__
#define __ZKN_DRAWGLB_H__

#include "include/application/zukanlist/zkn_defain.h"


// 描画関係
#include "include/gflib/bg_system.h"
#include "include/system/clact_util.h"
#include "include/system/softsprite.h"
#include "include/system/brightness.h"
#include "include/system/swsprite.h"
#include "include/system/arc_tool.h"
#include "include/system/arc_util.h"
#include "include/application/zukanlist/zkn_fontoam.h"
#include "include/application/zukanlist/zkn_cursor.h"


#undef GLOBAL
#ifdef	__ZKN_DRAWGLB_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	3Dポケモングラフィックデータ	
//=====================================
#define ZKN_DRAWGLB_POKEGRA_NUM		(4)		// すがた画面で４つ必要

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	座標自動動作ワーク
//=====================================
typedef struct {
	int x;
	int y;
	int s_x;
	int s_y;
	int dis_x;
	int dis_y;
	int count;
	int count_max;
} ZKN_UTIL_MOVE_WORK;





//-------------------------------------
//	ポケモンリスト画面と図鑑データ画面で共通に使用する
//	グラフィックデータ構造体
//=====================================
typedef struct {
	// ポケモンリスト、図鑑データ画面
	// リストOAMデータ
	CLACT_WORK_PTR pokelist_tbl;	// テーブル部分
	CLACT_WORK_PTR pokelist_icon;	// アイコン
	ZKN_FONTOAM_DATA* p_pokename;	// 名前OAM	
	CLACT_U_RES_OBJ_PTR pokelist_res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// リソースオブジェ数

	VecFx32		matrix;				// 全体を動かせる座標

	int mons_no;		// 現在設定されているモンスターナンバー（全国）
	u32 zkn_mode;
} ZKN_POKELIST_DATA_OAM_DATA;


//-------------------------------------
//	フェードインアウトブレンドシステム
//=====================================
enum{
	ZKN_UTIL_FADE_MAIN,
	ZKN_UTIL_FADE_SUB,
};
typedef struct {
	int disp_flag;		// メインサブ
	
	u32	plane1;			// 第１対称面
	u32	plane2;			// 第２対称面	無条件でBDは加えられます
	int	brightness_s;	// ブライトネス開始
	int brightness_dis;	// ブライトネス終了
	int alpha_s;		// 開始α値
	int alpha_dis;		// 終了までの値
	int count_max;		// 最大カウント数
	int count;			// 現在カウント値
} ZKN_UTIL_FADE_SYS;

//-------------------------------------
//	カーソルオブジェクト
//=====================================
typedef struct {
	CLACT_WORK_PTR cursor[ ZKN_CURROS_MAT_RECT_NUM ];	// カーソル
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// リソースオブジェ
	int x;	// Ｘ座標
	int y;	// Ｙ座標
	int size_x;	// Ｘサイズ
	int size_y;	// Ｙサイズ

	BOOL anm_stop;	// アニメストップフラグ
	int anm_count;	// アニメカウント
} ZKN_UTIL_CURSOR_OBJ;

//-------------------------------------
//	カーソルオブジェクト　座標変更動作アニメワーク
//=====================================
typedef struct {
	ZKN_UTIL_CURSOR_OBJ* p_cursor;		// カーソルオブジェクト
	ZKN_UTIL_MOVE_WORK mat_move;		// 座標動作用
	ZKN_UTIL_MOVE_WORK size_move;		// サイズ動作用

	int ta_x;		// 今のターゲットｘ座標
	int ta_y;		// 今のターゲットｙ座標
	int ta_size_x;	// 今のターゲットｘサイズ
	int ta_size_y;	// 今のターゲットｙサイズ

	BOOL move_stop;	// 動作ストップ
} ZKN_UTIL_CURSOR_OBJ_MOVE;


//-------------------------------------
//	図鑑描画グローバルデータ
//
//	全体で使用するもの　
//	複数アプリケーション間で共有したいリソースデータ
//	などを格納
//=====================================
typedef struct {
	// BGL
	GF_BGL_INI*	p_bg;					// ｂｇ管理
	GF_BGL_BMPWIN bmp_mfont;			// メイン画面フォント描画用
	
	// OAM
	CLACT_U_EASYRENDER_DATA	oam_rend;	// oamレンダラーデータ
	CLACT_SET_PTR			clact_set;	// セルアクターセット
	CLACT_U_RES_MANAGER_PTR	res_manager[ ZKN_CLACT_RES_MANAGER_NUM ];	// リソースマネージャ

	// FONTOAM
	ZKN_FONTOAM_SYS_PTR fontoam_sys;
	
	// 3Dポケモン
	SOFT_SPRITE_MANAGER* soft_sprite_man;	// ソフトウェアスプライトマネージャ
	SOFT_SPRITE*		 soft_sprite[ ZKN_DRAWGLB_POKEGRA_NUM ];	// 選択中のポケモンのソフトウェアスプライト

	// ソフトウェアスプライト
	SWSP_SYS_PTR	swsp_sys;

	// fadeシステム
	ZKN_UTIL_FADE_SYS	fade;
	ZKN_UTIL_FADE_SYS	fade_sub;

//	ポケモンリスト画面と図鑑データ画面で共通に使用する
//	グラフィックデータ構造体
	ZKN_POKELIST_DATA_OAM_DATA pokelist_data_draw;

	// 図鑑カーソル描画データ
	ZKN_UTIL_CURSOR_OBJ cursor;
	ZKN_UTIL_CURSOR_OBJ_MOVE cursor_move;	// 座標変更動作ワーク
	TCB_PTR	cursor_anm_tcb;		// アニメ
	TCB_PTR cursor_move_tcb;	// 座標変更動作

	// グラフィックデータアーカイブハンドル
	ARCHANDLE* p_graphic_arc_handl;
} ZKN_GLB_DRAWDATA;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_GlbDrawDataInit( ZKN_GLB_DRAWDATA* p_draw, int heap );
GLOBAL void ZKN_GlbDrawDataDelete( ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void ZKN_GlbDrawDataMain( ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void ZKN_GlbDrawDataVBlank( ZKN_GLB_DRAWDATA* p_draw );

void ZKN_GlbPokemonGraphicSet( ZKN_GLB_DRAWDATA* p_draw, int mons_no, int sex, int dir, int col, u8 form_no, u32 rnd, int x, int y );
GLOBAL void ZKN_GlbPokemonGraphicSetMatrix( ZKN_GLB_DRAWDATA* p_draw, int x, int y );
GLOBAL void ZKN_GlbPokemonGraphicGetMatrix( ZKN_GLB_DRAWDATA* p_draw, int* x, int* y );
GLOBAL SOFT_SPRITE* ZKN_GlbPokemonGraphicGet( const ZKN_GLB_DRAWDATA* cp_draw );
GLOBAL void ZKN_GlbPokemonGraphicDrawFlagSet( const ZKN_GLB_DRAWDATA* cp_draw, BOOL flag );
GLOBAL void ZKN_GLB_SpritePokeGraPalFade( const ZKN_GLB_DRAWDATA* p_draw, ZKN_UTIL_FADE_SYS* p_fade );

GLOBAL void ZKN_GlbPokemonGraphicSet_Idx( ZKN_GLB_DRAWDATA* p_draw, int mons_no, int sex, int dir, int col, u8 form_no, u32 rnd, int x, int y, int idx );
GLOBAL void ZKN_GlbPokemonGraphicSetMatrix_Idx( ZKN_GLB_DRAWDATA* p_draw, int x, int y, int idx );
GLOBAL void ZKN_GlbPokemonGraphicGetMatrix_Idx( ZKN_GLB_DRAWDATA* p_draw, int* x, int* y, int idx );
GLOBAL SOFT_SPRITE* ZKN_GlbPokemonGraphicGet_Idx( const ZKN_GLB_DRAWDATA* cp_draw, int idx );
GLOBAL void ZKN_GlbPokemonGraphicDrawFlagSet_Idx( const ZKN_GLB_DRAWDATA* cp_draw, BOOL flag, int idx );
GLOBAL void ZKN_GLB_SpritePokeGraPalFade_Idx( const ZKN_GLB_DRAWDATA* p_draw, ZKN_UTIL_FADE_SYS* p_fade, int idx );


GLOBAL CLACT_WORK_PTR ZKN_GlbPokeNameTblClactGet( const ZKN_GLB_DRAWDATA* p_draw );
GLOBAL CLACT_WORK_PTR ZKN_GlbPokeNameIconClactGet( const ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void ZKN_GlbPokeNameTblSet( ZKN_GLB_DRAWDATA* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, int char_size, int mons_no, u32 zkn_mode );
GLOBAL ZKN_FONTOAM_DATA* ZKN_GlbPokeNameTblGet( const ZKN_GLB_DRAWDATA* p_draw );
GLOBAL CLACT_U_RES_OBJ_PTR ZKN_GlbPokeNameTblResObjGet( const ZKN_GLB_DRAWDATA* p_draw, int res_type );
GLOBAL void ZKN_GlbPokeNameTblObjModeSet( const ZKN_GLB_DRAWDATA* p_draw, GXOamMode mode );
GLOBAL void ZKN_GlbPokeNameTblBGPriSet( const ZKN_GLB_DRAWDATA* p_draw, int pri );
GLOBAL void ZKN_GlbPokeNameTblDrawFlagSet( const ZKN_GLB_DRAWDATA* p_draw, BOOL flag );

// 戦闘後図鑑画面用の関数
GLOBAL void ZKN_GlbPokeNameTblSet_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, ZKN_FONTOAM_INIT* p_fontoam_init, int char_size, int mons_no, u32 zkn_mode );
GLOBAL void ZKN_GlbPokeNameTblResLoad_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap );
GLOBAL void ZKN_GlbPokeNameTblResRelease_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_U_RES_MANAGER_PTR* pp_res_manager );
GLOBAL void ZKN_GlbPokeNameTblActAdd_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, CLACT_SET_PTR clact_set, CLACT_U_RES_MANAGER_PTR* pp_res_manager, int heap, int bg_pri );
GLOBAL void ZKN_GlbPokeNameTblActDelete_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data );
GLOBAL void ZKN_GlbPokeNameTblDrawFlagSet_Minute( ZKN_POKELIST_DATA_OAM_DATA* p_data, BOOL flag );
 

GLOBAL void ZKN_GLB_ChangeFadeRequest( ZKN_UTIL_FADE_SYS* p_fade, u8 sync, int brightness_s, int brightness_e, int s_alpha, int e_alpha, BRIGHT_PLANEMASK plane1, BRIGHT_PLANEMASK plane2, int disp_flag );
GLOBAL BOOL ZKN_GLB_ChangeFadeMain( ZKN_UTIL_FADE_SYS* p_fade );
GLOBAL int ZKN_GLB_GetFadeAlpha( ZKN_UTIL_FADE_SYS* p_fade );
GLOBAL int ZKN_GLB_GetFadeBrightness( ZKN_UTIL_FADE_SYS* p_fade );
GLOBAL BOOL ZKN_GLB_ChangeFadeEndCheck( ZKN_UTIL_FADE_SYS* p_fade );



GLOBAL void ZKN_UTIL_CursorSetMatrixCursorSys( const ZKN_CURSOR* cp_cursor, ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void ZKN_UTIL_CursorSetMatrix( ZKN_GLB_DRAWDATA* p_draw, int def_x, int def_y, int size_x, int size_y );
GLOBAL void ZKN_UTIL_CursorSetDrawFlag( ZKN_UTIL_CURSOR_OBJ* p_obj, int flag );
GLOBAL BOOL ZKN_UTIL_CursorGetDrawFlag( ZKN_UTIL_CURSOR_OBJ* p_obj );
GLOBAL void ZKN_UTIL_CursorSetAnimeStopFlag( ZKN_UTIL_CURSOR_OBJ* p_obj, BOOL anm );
GLOBAL void ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( const ZKN_CURSOR* cp_cursor, ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void ZKN_UTIL_CursorSetMatrixNotAnm( ZKN_GLB_DRAWDATA* p_draw, int def_x, int def_y, int size_x, int size_y );


GLOBAL void ZKN_UTIL_MoveReq( ZKN_UTIL_MOVE_WORK* p_work, int s_x, int e_x, int s_y, int e_y, int count_max );
GLOBAL BOOL ZKN_UTIL_MoveMain( ZKN_UTIL_MOVE_WORK* p_work );

// アーカイブハンドルを使用した読み込み
// 読み込み処理高速化のため
GLOBAL ARCHANDLE* ZKN_GLBDATA_ArcHandlGet( ZKN_GLB_DRAWDATA* p_draw );
GLOBAL void* ZKN_GLBDATA_Arc_Load(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, u32 heapID);
GLOBAL u32 ZKN_GLBDATA_BgCharSet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID);
GLOBAL void ZKN_GLBDATA_PalSet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, PALTYPE palType, u32 offs, u32 transSize, u32 heapID );
GLOBAL void* ZKN_GLBDATA_CharDataGet( ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, NNSG2dCharacterData** charData, u32 heapID );
GLOBAL void* ZKN_GLBDATA_PalDataGet( ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, NNSG2dPaletteData** palData, u32 heapID );
GLOBAL void* ZKN_GLBDATA_ScrnDataGet(ZKN_GLB_DRAWDATA* p_draw, u32 dataIdx, BOOL compressedFlag, NNSG2dScreenData** scrnData, u32 heapID);


#undef	GLOBAL
#endif		// __ZKN_DRAWGLB_H__

