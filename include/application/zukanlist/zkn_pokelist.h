//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_pokelist.h
 *	@brief		ポケモンリスト
 *	@author		tomoya takahashi
 *	@data		2006.01.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_POKELIST_H__
#define __ZKN_POKELIST_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_POKELIST_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
// 動作タイミング定数
#define ZKN_POKELIST_MOVE_COUNT_UNIT	( 10 )	// 1 = 10の単位で計算
#define ZKN_POKELIST_MOVE_END_COUNT		( 64 * ZKN_POKELIST_MOVE_COUNT_UNIT )


// エフェクト用
// ポケリストテーブル位置
#define ZKN_POKELIST_TBL_MAT_Y	( 82 )
#define ZKN_POKELIST_TBL_MAT_X	( 170 )
// ポケモングラフィック
#define ZKN_POKELIST_POKEGRA_X				( 56 )	// ポケモン座標
#define ZKN_POKELIST_POKEGRA_Y				( 80 )	// ポケモン座標

//-------------------------------------
//	リストの進む方向
//=====================================
enum{
	ZKN_POKE_LIST_NO_MOVE,		// 動作なし
	ZKN_POKE_LIST_UP,			// 上に移動
	ZKN_POKE_LIST_DOWN,			// 下に移動
};

//-------------------------------------
//	フェードモード
//=====================================
enum{
	ZKN_POKELIST_BG_FADE_NORMAL,
	ZKN_POKELIST_BG_FADE_SHUTTER,
};

//-------------------------------------
//	ホイール動作ロックモード
//=====================================
enum{
	ZKN_POKELIST_WHEEL_LOCK_NONE,		// lockなし
	ZKN_POKELIST_WHEEL_LOCK_NORMAL,		// lockするしかしキー操作でホイールが動く
	ZKN_POKELIST_WHEEL_LOCK_ALL			// 完全にlockする
};



// ユーティリティ面シャッターフェードﾃﾞｰﾀ
#define ZKN_POKELIST_SCR_START_UP_CYSIZ		( 3 )
#define ZKN_POKELIST_SCR_START_DOWN_CYSIZ	( 14 )
#define ZKN_POKELIST_SCR_START_DOWN_YSIZ	( ZKN_POKELIST_SCR_START_DOWN_CYSIZ * 8 )
// BGShutterフェード面
#define ZKN_POKELIST_BGSHUTTER_FADE00_TOP_S		( 0 )
#define ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_S	( 0 )
#define ZKN_POKELIST_BGSHUTTER_FADE00_TOP_E		( ZKN_POKELIST_SCR_START_UP_CYSIZ )
#define ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_E	( ZKN_POKELIST_SCR_START_DOWN_CYSIZ )

#define ZKN_POKELIST_BGSHUTTER_FADE01_TOP_S		( 12 )
#define ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_S	( 20 )
#define ZKN_POKELIST_BGSHUTTER_FADE01_TOP_E		( ZKN_POKELIST_SCR_START_UP_CYSIZ )
#define ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_E	( ZKN_POKELIST_SCR_START_DOWN_CYSIZ )
#define ZKN_POKELIST_BGSHUTTER_FADE_FONTBG_LIMIT	( -48 )



//-------------------------------------
//	ポケモンリストグローバルデータ
//
//	サブ画面と共有するため公開
//=====================================
typedef struct {
	int*				p_event_key;		// イベントキー
	ZKN_GLB_DATA*		p_glb;				// グローバルデータ

	int move_way;				// 進んでいる方向
	int move_count;				// 動作カウント値

	int fade_mode;				// フェードモード
	BOOL fade_zukan_data;		// 図鑑データフェードモード
	BOOL fade_sort_data;		// ｿｰﾄ画面からフェードしてきた

	// 描画更新ONOFF
	BOOL move_draw;				// 通常TRUE　更新OFF　FALSE

	u32 sub_wheel_lock;			// サブ画面のホイールをlockする

	BOOL zukan_sort_end;		// SORTモード終了
	BOOL zukan_end;				// 図鑑終了
	BOOL zukan_see;				// 図鑑データを見る
	BOOL zukan_chg;				// 図鑑モード変更
	BOOL sort_chg;				// SORT画面へ変更
} ZKN_POKELIST_GLB_DATA;

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
GLOBAL void ZKN_PokeListAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
GLOBAL void ZKN_PokeListAplDelete( ZKN_APL_DATA* p_data );

GLOBAL BOOL ZKN_PokeList_SubEventSetOkCheck( const ZKN_POKELIST_GLB_DATA* cp_glb );

#undef	GLOBAL
#endif		// __ZKN_POKELIST_H__

