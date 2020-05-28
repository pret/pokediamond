//============================================================================================
/**
 * @file	fld_menu.h
 * @brief	フィールドメニュー処理用ヘッダ
 * @author	Hiroyuki Nakamura
 */
//============================================================================================
#ifndef FLD_MENU_H
#define FLD_MENU_H

#include "field/itemuse.h"
#include "field/field_skill.h"
#include "field_skill_local.h"

#undef GLOBAL
#ifdef FLD_MENU_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================
#define	FIELD_MENU_MAX		( 7 )					// 項目最大数
#define	FLDMENU_CLACT_MAX	( FIELD_MENU_MAX + 1 )	// セルアクター最大数（項目＋カーソル）

#define FLD_MENU_VANISH_ZUKAN	( 0x00000001 )		// 図鑑を隠す
#define FLD_MENU_VANISH_PLIST	( 0x00000002 )		// ポケモンリストを隠す
#define FLD_MENU_VANISH_BAG		( 0x00000004 )		// バッグを隠す
#define FLD_MENU_VANISH_TRCARD	( 0x00000008 )		// トレーナーカードを隠す
#define FLD_MENU_VANISH_REPORT	( 0x00000010 )		// レポートを隠す
#define FLD_MENU_VANISH_CONFIG	( 0x00000020 )		// 設定を隠す
#define FLD_MENU_VANISH_CLOSE	( 0x00000040 )		// 「閉じる」を隠す
#define FLD_MENU_VANISH_CHAT	( 0x00000080 )		// チャットを隠す
#define FLD_MENU_VANISH_RETIRE	( 0x00000100 )		// リタイアを隠す


// フィールドメニューワーク
typedef struct {
	GF_BGL_BMPWIN	win;		// BMPウィンドウ（メニュー）
	GF_BGL_BMPWIN	ball_win;	// BMPウィンドウ（ボール数）

	BMPMENU_WORK * mw;
	BMP_MENULIST_DATA * ld;	// BMPリストデータ
	u16	pos;				// メニュー位置
	u16	seq;				// シーケンス
	u32	ret;				// 戻り値

	u8	list[ FIELD_MENU_MAX ];		// メニューリスト

	FIELD_CLACT	fcat;		// セルアクター設定データ
	CATS_ACT_PTR	cap[FLDMENU_CLACT_MAX];
	u32	clact_max;			// セルアクター登録数

	u32	ev_flg;				// メニュー制御フラグ
	u32	union_flg;			// ユニオンルームフラグ

	GMEVENT_FUNC	app_func;

	ITEMCHECK_WORK	item_check;		// アイテム使用チェックワーク
	SKILLCHECK_WORK	skill_check;	// 技使用チェックワーク

	void * app_wk;			// 汎用ワークポインタ
	void * tmp_wk;			// 汎用ワークポインタ２（各画面を行き来する場合に使用）
}FLD_MENU;

// フィールドメニューシーケンス
enum {
	FLD_MENU_SEQ_INIT = 0,		// 初期化
	FLD_MENU_SEQ_SELECT,		// メニュー選択

	FLD_MENU_SEQ_APP_CALL,		// アプリ呼び出し
	FLD_MENU_SEQ_APP_WAIT,		// アプリ終了待ち

	FLD_MENU_SEQ_REPORT_CALL,
	FLD_MENU_SEQ_REPORT_WAIT,

	FLD_MENU_SEQ_SHINKA_INIT,	// 進化画面呼び出し
	FLD_MENU_SEQ_SHINKA_MAIN,	// 進化画面待ち

	FLD_MENU_SEQ_BLACK_IN_END,
	FLD_MENU_SEQ_BLACK_IN_END_WAIT,

	FLD_MENU_SEQ_BLACK_IN_EVCHG,
	FLD_MENU_SEQ_BLACK_IN_EVCHG_WAIT,

	FLD_MENU_SEQ_AGAIN,
	FLD_MENU_SEQ_END,
	FLD_MENU_SEQ_WAIT_BLACK_IN,
	FLD_MENU_SEQ_END_NOMENU,
};


// メール画面のモード
#define	FM_MAIL_MODE_VIEW		( 3 )		// メールを見る
#define	FM_MAIL_MODE_READ		( 2 )		// メールを読む
#define	FM_MAIL_MODE_MAKE_LIST	( 0 )		// メールを持たせる（ポケモンリストから）
#define	FM_MAIL_MODE_MAKE_BAG	( 1 )		// メールを持たせる（バッグから）


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
GLOBAL void FieldMenuInit( struct _FIELDSYS_WORK * repw );
GLOBAL void FieldMenuInitUnion( struct _FIELDSYS_WORK * repw );
GLOBAL void FieldMenuInitVS( FIELDSYS_WORK * repw );
GLOBAL void FieldMenuEvChg( FIELDSYS_WORK * repw );
GLOBAL void FieldMenuEvChgUnion( FIELDSYS_WORK * repw );

GLOBAL void FldMenu_AppWaitFuncSet( FLD_MENU * wk, void * func );

GLOBAL BOOL FldMenu_PokeListEnd( GMEVENT_CONTROL * event );

GLOBAL void * FieldMenu_MailWorkMake( u16 item, u8 mode, u8 poke_pos );

GLOBAL BOOL FldMenu_MailEnd( GMEVENT_CONTROL * event );
GLOBAL BOOL FldMenu_TownMapEnd( GMEVENT_CONTROL * event );
GLOBAL BOOL FldMenu_FantasyNoteEnd( GMEVENT_CONTROL * event );
GLOBAL BOOL FldMenu_PorutoCaseEnd( GMEVENT_CONTROL * event );
GLOBAL BOOL FldMenu_FriendBookEnd( GMEVENT_CONTROL * event );
GLOBAL BOOL FldMenu_SorawotobuEnd( GMEVENT_CONTROL * event );

//==============================================================================
//	データ
//==============================================================================
GLOBAL const u8 PST_PageTbl_Normal[];


#undef GLOBAL
#endif	/* FLD_MENU_H */
