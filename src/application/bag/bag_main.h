//============================================================================================
/**
 * @file	bag_main.h
 * @brief	バッグ画面処理
 * @author	Hiroyuki Nakamura
 * @date	06.04.17
 */
//============================================================================================
#ifndef BAG_MAIN_H
#define BAG_MAIN_H
#undef GLOBAL
#ifdef BAG_MAIN_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


#include "itemtool/myitem.h"

//============================================================================================
//	定数定義
//============================================================================================
#define	BAG_LARGE_POKE_MAX		( BAG_NORMAL_ITEM_MAX )		// 最大サイズのポケット

#define	P_ICON_SIZ_X	( 10 )		// ポケットアイコンのXサイズ
#define	P_ICON_SIZ_Y	( 10 )		// ポケットアイコンのYサイズ
#define	P_ICON_DEF_PX	( 6 )		// ポケットアイコンの表示X座標
#define	P_ICON_DEF_SX	( 90 )		// ポケットアイコンの表示領域のXサイズ


// ウィンドウインデックス
enum {
	WIN_LIST = 0,
	WIN_INFO,
	WIN_POCKET,
	WIN_MENU_INFO,
	WIN_MENU_INFO2,
	WIN_P_ICON,
	WIN_TALK,

	WIN_SALE_NUM,
	WIN_GOLD,
	WIN_SUB,

	WIN_PORUTO,

	WIN_MAX
};


enum {
	ADD_WIN_MENU = 0,

	ADD_WIN_MAX
};

// メニュー項目
enum {
	BAG_MENU_TSUKAU = 0,	// つかう
	BAG_MENU_ORIRU,			// おりる
	BAG_MENU_MIRU,			// みる
	BAG_MENU_UMERU,			// うめる
	BAG_MENU_HIRAKU,		// ひらく
	BAG_MENU_SUTERU,		// すてる
	BAG_MENU_TOUROKU,		// とうろく
	BAG_MENU_KAIZYO,		// かいじょ
	BAG_MENU_MOTASERU,		// もたせる
	BAG_MENU_TAGUWOMIRU,	// タグをみる
	BAG_MENU_KETTEI,		// けってい
	BAG_MENU_YAMERU,		// やめる

	BAG_MENU_MAX
};

// セルアクター管理番号
enum {
	ACT_BAG = 0,
	ACT_POKE_CURSOR,
	ACT_POKE_ARROW_LEFT,
	ACT_POKE_ARROW_RIGHT,
	ACT_LIST_SEL_CURSOR,
	ACT_LIST_SEL_CHANGE,

	ACT_BUTTON_ANM,
	ACT_ITEMICON,

	ACT_NUM_ARROW_UP,
	ACT_NUM_ARROW_DOWN,

	ACT_TYPE,
	ACT_KIND,

	BAG_ACT_MAX
};


// ページ切り替え用ワーク
typedef struct {
	u8	next;			// 次のページ
	u8	move;			// 移動方向

	u8	cur_seq;		// ポケットカーソル移動シーケンス
	u8	cur_cnt;		// ポケットカーソル移動カウンタ

	u8	tp_seq;			// タッチパネル処理シーケンス
	u8	tp_cnt;			// タッチパネル処理カウンタ
	u8	tp_button;		// ボタン番号
	u8	tp_chg:4;		// 違うボタンが押されたか
	u8	tp_push:3;		// タッチパネルに触れているか
	u8	tp_mode:1;		// タッチパネルでの変更かどうか
}PAGE_CHG_WORK;



// バッグで参照するデータ
typedef struct {
	MINEITEM * item;	// 参照するアイテムデータ
	u16	cur;			// カーソル位置
	u16	scr;			// スクロールカウンタ
//	u16	pos;			// 現在値 ( cur + scr )
	u8	type;			// ポケットタイプ
	u8	max;			// アイテム最大数
}POCKET_DATA;

struct _BAG_DATA {
	SAVEDATA * sv;		// セーブデータ

	POCKET_DATA	p_data[BAG_POKE_MAX];	// ポケットごとのデータ
	u8	p_now;							// 現在のポケット
	u8	mode;							// バッグ画面の役割
	u16	ret_item;						// 選択アイテム
	u16	ret_mode;						// 終了モード

	void * bag_cursor;		// カーソル位置の外部記憶領域

	void * icwk;			// アイテム使用チェックワーク

	u8	use_poke;			// アイテムを使用したポケモン

	u8	fnote_sale_cnt;		// 冒険ノート用売った個数

	u16	cycle_flg:1;		// 自転車フラグ ( 0=off, 1=on )
	u16	map_mode:15;		// マップモード
};

typedef struct {
	u8	req;
	u8	mv;
	u8	next;
	u8	cnt;
	fx32 tbl[8];	// ページカーソル移動テーブル
}POCKET_CURSOR_MOVE;

typedef struct {
	GF_BGL_INI * bgl;						// BGLデータ

	GF_BGL_BMPWIN	win[WIN_MAX];			// BMPウィンドウデータ（通常）
	GF_BGL_BMPWIN	add_win[ADD_WIN_MAX];	// BMPウィンドウデータ（追加）

	BAG_DATA * dat;							// バッグデータ

	MYITEM * myitem;		// 手持ちアイテムデータ
	MYSTATUS * myst;		// プレーヤーデータ
	CONFIG * cfg;			// コンフィグデータ

	ARCHANDLE * gra_h;		// グラフィックのアーカイブハンドル

	CATS_SYS_PTR	csp;
	CATS_RES_PTR	crp;
	CATS_ACT_PTR	cap[BAG_ACT_MAX];

	NUMFONT * num_font;			// 8x8フォント
	MSGDATA_MANAGER * msg_man;	// メッセージデータマネージャ
	WORDSET * wset;				// 単語セット

	MSGDATA_MANAGER * item_man;	// メッセージデータマネージャ
	MSGDATA_MANAGER * waza_man;	// メッセージデータマネージャ

	STRBUF * menu_str[BAG_MENU_MAX];	// メニュー項目
	BMP_MENULIST_DATA * md;				// BMPメニューデータ
	BMPMENU_WORK * mw;					// BMPメニューワーク

	BMPLIST_WORK * lw;			// BMPリストデータ
	BMP_MENULIST_DATA * ld;		// BMPリストデータ
	STRBUF * itemname[BAG_LARGE_POKE_MAX];					// アイテム名展開場所

	STRBUF * expb;			// メッセージ展開場所

	STRBUF * num_str1;		// 個数表示・"x"
	STRBUF * num_str2;		// 個数表示・個数

	STRBUF * pocket_name[BAG_POKE_MAX];	// ポケット名展開場所ポインタ
	u8	p_max;				// ポケット数

	u8	sex;				// 性別

	u8	midx;				// メッセージインデックス

	u8	p_icon_gx;			// ページ０のアイコンのX座標
	u8	p_icon_sx;			// アイコンの間隔

	PAGE_CHG_WORK	page_work;
	fx32 p_mv_tbl[8];		// ページカーソル移動テーブル

	POCKET_CURSOR_MOVE	pcmv;
	u8	p_next;

	u8	info_put;			// アイテム情報セット

	u8	irekae_flg;
	u8	irekae_pos;
	u32	irekae_param;

	u8	arrow_mv;
	u8	arrow_cnt;

	u8	se_type;		// リスト選択時のSE

	u8	sub_seq;		// サブシーケンス
	u32	use_func;		// バッグ内使用関数

	s16	sel_num;		// 個数選択：選択数
	u16	sel_max;		// 個数選択：最大数
	u32	sel_price;		// 選択されたアイテムの値段

	u8	enter_anm_flg;	// サブ画面決定ボタンアニメ
	u8	enter_anm_cnt;	// サブ画面決定ボタンカウント

	u8	wheel_flg;
//	s16	wheel_pos;
	s32	wheel_pos;
	s16	wheel_mv;
	s16	wheel_rot;
	s16	wheel_start;
	u16	backup_tpx;
	u16	backup_tpy;

}BAG_WORK;

typedef int (*pBagFunc)(BAG_WORK *);	// 関数ポインタ型


#define	POS_GET_ID		( 0 )		// アイテム番号
#define	POS_GET_NUM		( 1 )		// 所持数


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 現在のポケットの指定位置のアイテムを取得
 *
 * @param	wk		バッグ画面のワーク
 * @param	pos		位置
 * @param	id		取得ID
 *
 * @return	指定位置のアイテム
 *
 * @li	id = POS_GET_ID : アイテム番号
 * @li	id = POS_GET_NUM : 所持数
 */
//--------------------------------------------------------------------------------------------
extern u16 Bag_PosItemGet( BAG_WORK * wk, u16 pos, u16 id );


extern const u32 Bag_MenuParamGet( u32 menu_num );



#undef GLOBAL
#endif	/* BAG_MAIN_H */
