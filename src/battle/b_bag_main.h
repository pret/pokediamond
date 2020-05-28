//============================================================================================
/**
 * @file	b_plist_main.h
 * @brief	戦闘用バッグ画面
 * @author	Hiroyuki Nakamura
 * @date	05.02.10
 */
//============================================================================================
#ifndef B_BAG_MAIN_H
#define B_BAG_MAIN_H
#undef GLOBAL
#ifdef B_BAG_MAIN_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif

#include "itemtool/myitem.h"
#include "finger_cursor.h"

//============================================================================================
//	定数定義
//============================================================================================
// パレット定義
#define	BBAG_PAL_BTN_FONT	( 0 )		///< パレット00：ボタンフォントで使用してます
//#define	BPL_PAL_SYS_WIN	( 12 )		///< パレット12：システムウィンドウ
#define	BBAG_PAL_SYS_FONT	( 4 )		///< パレット13：システムフォント
#define	BBAG_PAL_TALK_WIN	( 14 )		///< パレット14：会話ウィンドウ
#define	BBAG_PAL_TALK_FONT	( 15 )		///< パレット15：会話フォント

// BMPウィンドウインデックス
// ページ１
enum {
	WIN_P1_HP = 0,		// 「HP/PPかいふく」
	WIN_P1_ZYOUTAI,		// 「じょうたいかいふく」
	WIN_P1_BALL,		// 「ボール」
	WIN_P1_BATTLE,		// 「せんとうよう」
	WIN_P1_LASTITEM,	// 「さいごにつかったどうぐ」
	WIN_P1_MAX
};

// ページ２
enum {
	WIN_P2_NAME1 = 0,	// 道具名１
	WIN_P2_NUM1,		// 道具数１
	WIN_P2_NAME2,		// 道具名２
	WIN_P2_NUM2,		// 道具数２
	WIN_P2_NAME3,		// 道具名３
	WIN_P2_NUM3,		// 道具数３
	WIN_P2_NAME4,		// 道具名４
	WIN_P2_NUM4,		// 道具数４
	WIN_P2_NAME5,		// 道具名５
	WIN_P2_NUM5,		// 道具数５
	WIN_P2_NAME6,		// 道具名６
	WIN_P2_NUM6,		// 道具数６

	WIN_P2_NAME1_S,		// 道具名１（スワップ用）
	WIN_P2_NUM1_S,		// 道具数１（スワップ用）
	WIN_P2_NAME2_S,		// 道具名２（スワップ用）
	WIN_P2_NUM2_S,		// 道具数２（スワップ用）
	WIN_P2_NAME3_S,		// 道具名３（スワップ用）
	WIN_P2_NUM3_S,		// 道具数３（スワップ用）
	WIN_P2_NAME4_S,		// 道具名４（スワップ用）
	WIN_P2_NUM4_S,		// 道具数４（スワップ用）
	WIN_P2_NAME5_S,		// 道具名５（スワップ用）
	WIN_P2_NUM5_S,		// 道具数５（スワップ用）
	WIN_P2_NAME6_S,		// 道具名６（スワップ用）
	WIN_P2_NUM6_S,		// 道具数６（スワップ用）

	WIN_P2_POCKET,		// ポケット名
	WIN_P2_PAGENUM,		// ページ数（アイテム数）

	WIN_P2_MAX
};

// ページ３
enum {
	WIN_P3_NAME = 0,	// 道具名
	WIN_P3_NUM,			// 個数
	WIN_P3_INFO,		// 説明
	WIN_P3_USE,			// 「つかう」
	WIN_P3_MAX
};

// ページID
enum {
	BBAG_PAGE_POCKET = 0,	// ポケット選択ページ
	BBAG_PAGE_MAIN,			// アイテム選択ページ
	BBAG_PAGE_ITEM			// アイテム使用ページ
};

// ページ１の選択ID
enum {
	BBAG_P1_LASTITEM = BBAG_POKE_MAX,	// 最後に使用した道具
	BBAG_P1_RETURN						// 戻る
};

// セルアクターのID
enum {
	BBAG_CA_ITEM1 = 0,
	BBAG_CA_ITEM2,
	BBAG_CA_ITEM3,
	BBAG_CA_ITEM4,
	BBAG_CA_ITEM5,
	BBAG_CA_ITEM6,
//	BBAG_CA_GETDEMO,

	BBAG_CA_MAX
};

#define	BBAG_POCKET_IN_MAX		( 36 )		// 各ポケットに入る数


#define	BBAG_BANM_MAX_N	( 3 )		// ボタンアニメパターン数（通常）
#define	BBAG_BANM_MAX_E	( 4 )		// ボタンアニメパターン数（押せないボタンあり）
// ポケットボタンサイズ
#define	BBAG_BSX_POCKET	( 16 )
#define	BBAG_BSY_POCKET	( 9 )
// 使用ボタンサイズ
#define	BBAG_BSX_USE	( 26 )
#define	BBAG_BSY_USE	( 5 )
// 戻るボタンサイズ
#define	BBAG_BSX_RET	( 5 )
#define	BBAG_BSY_RET	( 5 )
// アイテムボタンサイズ
#define	BBAG_BSX_ITEM	( 16 )
#define	BBAG_BSY_ITEM	( 6 )
// 前のページへボタンサイズ
#define	BBAG_BSX_UP		( 5 )
#define	BBAG_BSY_UP		( 5 )
// 次のページへボタンサイズ
#define	BBAG_BSX_DOWN	( 5 )
#define	BBAG_BSY_DOWN	( 5 )
// ポケットボタンのアイコンサイズ
#define	BBAG_BSX_ICON	( 4 )
#define	BBAG_BSY_ICON	( 4 )

typedef struct {
	BBAG_DATA * dat;		// 外部参照データ

	GF_BGL_INI * bgl;		// BGデータ

	PALETTE_FADE_PTR pfd;	// パレットフェードデータ

	NUMFONT * nfnt;				// 8x8フォント
	MSGDATA_MANAGER * mman;		// メッセージデータマネージャ
	WORDSET * wset;				// 単語セット
	STRBUF * msg_buf;			// メッセージ用バッファ

	GF_BGL_BMPWIN	talk_win;	// BMPウィンドウデータ（通常）
	GF_BGL_BMPWIN * add_win;	// BMPウィンドウデータ（追加）
	u8	bmp_add_max;			// 追加したBMPの数
	u8	p2_swap;				// ページ２のスワップ描画フラグ
	u8	midx;					// メッセージインデックス

	BAPP_CURSOR_MVWK * cmv_wk;	// カーソル制御ワーク

	FINGER_PTR	finger;			// 捕獲デモ用指カーソル

	MINEITEM	pocket[5][BBAG_POCKET_IN_MAX];	// ポケットデータ

	CATS_RES_PTR	crp;				// リソース管理
	CATS_ACT_PTR	cap[BBAG_CA_MAX];	// OAMのCAP

	// ボタンアニメスクリーンデータ
	u16	btn_pocket[BBAG_BANM_MAX_N][BBAG_BSX_POCKET*BBAG_BSY_POCKET];	// ポケットボタン
	u16	btn_use[BBAG_BANM_MAX_E][BBAG_BSX_USE*BBAG_BSY_USE];			// 使用ボタン
	u16	btn_ret[BBAG_BANM_MAX_N][BBAG_BSX_RET*BBAG_BSY_RET];			// 戻るボタン
	u16	btn_item[BBAG_BANM_MAX_E][BBAG_BSX_ITEM*BBAG_BSY_ITEM];			// アイテム
	u16	btn_up[BBAG_BANM_MAX_E][BBAG_BSX_UP*BBAG_BSY_UP];				// 前のページへ
	u16	btn_down[BBAG_BANM_MAX_E][BBAG_BSX_DOWN*BBAG_BSY_DOWN];			// 次のページへ

	u16	btn_icon_hp[BBAG_BANM_MAX_N][BBAG_BSX_ICON*BBAG_BSY_ICON];
	u16	btn_icon_st[BBAG_BANM_MAX_N][BBAG_BSX_ICON*BBAG_BSY_ICON];
	u16	btn_icon_ball[BBAG_BANM_MAX_N][BBAG_BSX_ICON*BBAG_BSY_ICON];
	u16	btn_icon_batl[BBAG_BANM_MAX_N][BBAG_BSX_ICON*BBAG_BSY_ICON];

	u8	btn_seq;
	u8	btn_cnt;
	u8	btn_id;
	u8	btn_flg:4;
	u8	btn_mode:4;
	u8	btn_win[8];

	u8	seq;			// メインシーケンス
	u8	ret_seq;		// 復帰シーケンス
	u8	page;			// ページID
	u8	poke_id;		// ポケットID

	s8	page_mv;		// アイテム選択ページの移動方向

	u8	item_max[5];	// アイテム数
	u8	scr_max[5];		// アイテムスクロールカウンタ最大値

	u8	get_seq;		// 捕獲デモシーケンス
	u8	get_cnt;		// 捕獲デモカウンタ
//	u8	get_anm;		// 捕獲デモカーソルアニメフラグ

}BBAG_WORK;





int BattleBag_SelMonsNoGet( BBAG_WORK * wk );



#undef GLOBAL
#endif	// B_BAG_MAIN_H
