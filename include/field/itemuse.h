//============================================================================================
/**
 * @file	itemuse.h
 * @brief	フィールドアイテム使用処理
 * @author	Hiroyuki Nakamura
 * @date	05.12.12
 */
//============================================================================================
#ifndef ITEMUSE_H
#define ITEMUSE_H
#undef GLOBAL
#ifdef ITEMUSE_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif



#include "../../src/field/player.h"


//============================================================================================
//	定数定義
//============================================================================================
// アイテム使用ワーク
typedef struct {
	GMEVENT_CONTROL * event;	// イベント
	u16	item;					// アイテム番号
	u8	use_poke;				// 使用するポケモン
}ITEMUSE_WORK;

// アイテム使用チェックワーク
typedef struct {
	int	zone_id;	// ゾーンID
	BOOL Companion;	//　連れ歩き状態か？
	int PlayerForm;	//　自機の形状（自転車に乗っているかとか）
	u16 FrontAttr;	//　自機前方アトリビュート
	u16 NowAttr;	//　自機現在アトリビュート
	u16 SeedInfo;	//使用可能なアイテム情報（きのみ関連）
	PLAYER_STATE_PTR player;	//自機情報参照ポインタ
	FIELDSYS_WORK * fsys;
}ITEMCHECK_WORK;

typedef u32 (*ITEMCHECK_FUNC)(const ITEMCHECK_WORK*);	// アイテム使用チェック関数

typedef void (*ITEMUSE_FUNC)(ITEMUSE_WORK*, const ITEMCHECK_WORK *);	// アイテム使用関数

// アイテム使用関数取得パラメータ
enum {
	ITEMUSE_PRM_USEFUNC = 0,	// バッグからの使用関数
	ITEMUSE_PRM_CNVFUNC,		// 便利ボタンからの使用関数
	ITEMUSE_PRM_CHECKFUNC		// チェック関数
};

// アイテム使用チェックの戻り値
enum {
	ITEMCHECK_TRUE = 0,				// 使用可能

	ITEMCHECK_ERR_CYCLE_OFF,		// 自転車を降りれない
	ITEMCHECK_ERR_COMPANION,		// 使用不可・連れ歩き

	ITEMCHECK_FALSE = 0xffffffff	// 使用不可・博士の言葉
};



//============================================================================================
//	プロトタイプ宣言
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 使用関数取得
 *
 * @param	prm		取得パラメータ
 * @param	id		関数ID
 *
 * @return	使用関数
 */
//--------------------------------------------------------------------------------------------
GLOBAL u32 ItemUse_FuncGet( u16 prm, u16 id );

//--------------------------------------------------------------------------------------------
/**
 * 使用チェックワーク作成
 *
 * @param	fsys	フィールドワーク
 * @param	id		チェックワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void ItemUse_CheckWorkMake( FIELDSYS_WORK * fsys, ITEMCHECK_WORK * icwk );


GLOBAL BOOL ItemUse_KinomiTypeCheck( const ITEMCHECK_WORK * icwk );

GLOBAL BOOL FieldConvButtonEventInit( FIELDSYS_WORK * repw );


#undef GLOBAL
#endif	/* ITEMUSE_H */
