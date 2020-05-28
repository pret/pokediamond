//============================================================================================
/**
 * @file	box_common.h
 * @brief	ボックス操作画面共有ヘッダ
 * @author	taya
 * @date	2005.09.05
 */
//============================================================================================
#ifndef __BOX_COMMON_H__
#define __BOX_COMMON_H__

#include "gflib\msg_print.h"	// STRCODEのため
#include "gflib\strbuf.h"
#include "system\wordset.h"
#include "system\msgdata.h"
#include "system\buflen.h"
#include "itemtool\item.h"
#include "msgdata\msg_boxmes.h"
#include "poketool\boxdata.h"
#include "poketool\pokeparty.h"

#include "application\box.h"

#include "box_sound_def.h"

//----------------------------------------------------------------------
/**
 *  描画コマンド
 */
//----------------------------------------------------------------------
enum {
	CMD_INIT,
	CMD_NORMAL_IN,			///< 画面構築後のフェードインエフェクト（フィールドから入る）
	CMD_FADEIN,				///< 多画面から復帰する時のフェードイン
	CMD_FADEOUT,			///< 他画面以降前のフェードアウト

	CMD_TRAY_CHANGE,		///< ボックストレイ切り替え
	CMD_CURSOR_MOVE,		///< カーソル移動
	CMD_STATUS_UPDATE,		///< ステータス表示ポケモンの切り替え
	CMD_STATUS_MARK_UPDATE,	///< ステータス表示ポケモンのマーキング表示のみ更新
	CMD_STATUS_CLEAR,		///< ステータス表示部をクリア

	CMD_POKE_CATCH,			///< ポケモンつかむ
	CMD_POKE_PUT,			///< ポケモンおく
	CMD_POKE_CHANGE,		///< ポケモンいれかえる
	CMD_AZUKERU_CATCHPOKE,	///< ポケモンあずける（つかんでるポケモン）
	CMD_AZUKERU_POINTPOKE,	///< ポケモンあずける（指しているポケモン）
	CMD_NIGASU_CATCHPOKE,	///< ポケモンにがす（つかんでるポケモン）
	CMD_NIGASU_TRAYPOKE,	///< ポケモンにがす（ボックストレイのポケモン）
	CMD_NIGASU_PARTYPOKE,	///< ポケモンにがす（手持ちのポケモン）
	CMD_ITEMINFO_DISP,		///< アイテム説明の表示
	CMD_ITEMINFO_CLEAR,		///< アイテム説明の消去
	CMD_ITEM_WITHDRAW,		///< アイテム「あずかる」
	CMD_ITEM_SET,			///< アイテム「もたせる」（つかんでいるアイテムをもたせる）
	CMD_ITEM_SWAP,			///< アイテム「とりかえる」
	CMD_ITEM_POKE_UPDATE,	///< アイテム所持状況に応じてポケモン半透明表示切り替え
	CMD_ITEMICON_RESTORE,	///< アイテムアイコンをバッグに戻すエフェクト

	CMD_MSG_DISP,			///< メッセージのみ
	CMD_MENU_DISP,			///< メッセージ＆メニュー
	CMD_MSG_CLEAR,			///< メッセージ＆メニュークリア
	CMD_MENU_CLEAR,			///< メニューのみクリア

	CMD_MENUCURSOR_UPDATE,	///< メニューカーソル位置更新
	CMD_MENUMARK_UPDATE,	///< メニューマーク状態更新（マーキングメニューのみ）
	CMD_JUMPWIN_DISP,
	CMD_JUMPWIN_UPDATE,
	CMD_JUMPWIN_CLEAR,

	CMD_WALLPAPER_CHANGE,	///< カレント壁紙変更
	CMD_BUTTON_PUSH_ACTION,	///< 指カーソルが直下のボタンを押すような動作
	CMD_PARTYTRAY_OPEN,		///< 手持ちトレイ開く
	CMD_PARTYTRAY_CLOSE,	///< 手持ちトレイ閉じる

	CMD_PARTYICON_CLOSEUP,	///< 手持ちトレイのアイコン空き詰め（掴んだ後・逃がした後）
	CMD_PARTYLASTICON_CLOSEUP,	///< 手持ちトレイのアイコン空き詰め（置いた後）
	CMD_ICON_LIMITMODE_UPDATE,	///< アイコンの絞り込みモード表示更新

	CMD_SUBLCD_MODECHANGE,
	CMD_SUBLCD_MOVEICON,
	CMD_SUBLCD_MARKICON_UPDATE,	///< 絞り込みアイコンの表示更新

	CMD_CHANGE_EXPERTMODE,		///< 慣れてる人モードの切り替え
	CMD_START_AREASELECT,		///< ポケモンアイコンの範囲選択開始
	CMD_END_AREASELECT,			///< ポケモンアイコンの範囲選択終了
	CMD_UPDATE_AREASELECT,		///< ポケモンアイコンの範囲選択更新
	CMD_CATCH_AREASELECT_POKE,	///< 範囲選択中のポケモンアイコンを掴む

	CMD_SWITCH_COMPARE_SIDE,			///< つよさくらべの更新するサイドを変更
	CMD_SWITCH_COMPARE_SIDE_BY_BUTTON,	///< つよさくらべの更新するサイドを変更（ボタン押下エフェクトを伴う）
	CMD_CHANGE_COMPARE_PAGE,

	CMD_BOXCLOSE,
};

//----------------------------------------------------------------------
/**
 *  タスクプライオリティ
 */
//----------------------------------------------------------------------
enum BOXTASK{
	TASKPRI_VIEW_COMMAND_SUB,
	TASKPRI_VIEW_COMMAND,
	TASKPRI_VIEW_TRANS,
};

enum BOX_VTASK {
	TASKPRI_V_SUB,
	TASKPRI_V_MAIN,
};

//----------------------------------------------------------------------
/**
 *  メニューＩＤ
 */
//----------------------------------------------------------------------
typedef enum {
	BOXMENU_TRAY_JUMP,		///< ボックスの切り替え
	BOXMENU_TRAY_WALLPAPER,	///< 壁紙変更
	BOXMENU_TRAY_NAME,		///< ボックス名変更
	BOXMENU_TRAYMENU_QUIT,	///< トレイメニュー「やめる」
	BOXMENU_WP_CATEGORY1,	///< 壁紙カテゴリ１
	BOXMENU_WP_CATEGORY2,	///< 壁紙カテゴリ２
	BOXMENU_WP_CATEGORY3,	///< 壁紙カテゴリ３
	BOXMENU_WP_CATEGORY4,	///< 壁紙カテゴリ４
	BOXMENU_WP_CATEGORY_EX1,///< 壁紙カテゴリ隠し１
	BOXMENU_WP_CATEGORY_EX2,///< 壁紙カテゴリ隠し２
	BOXMENU_WP_NAME1_1,		///< 壁紙名１-１
	BOXMENU_WP_NAME1_2,		///< 壁紙名１-２
	BOXMENU_WP_NAME1_3,		///< 壁紙名１-３
	BOXMENU_WP_NAME1_4,		///< 壁紙名１-４
	BOXMENU_WP_NAME2_1,		///< 壁紙名２-１
	BOXMENU_WP_NAME2_2,		///< 壁紙名２-２
	BOXMENU_WP_NAME2_3,		///< 壁紙名２-３
	BOXMENU_WP_NAME2_4,		///< 壁紙名２-４
	BOXMENU_WP_NAME3_1,		///< 壁紙名３-１
	BOXMENU_WP_NAME3_2,		///< 壁紙名３-２
	BOXMENU_WP_NAME3_3,		///< 壁紙名３-３
	BOXMENU_WP_NAME3_4,		///< 壁紙名３-４
	BOXMENU_WP_NAME4_1,		///< 壁紙名４-１
	BOXMENU_WP_NAME4_2,		///< 壁紙名４-２
	BOXMENU_WP_NAME4_3,		///< 壁紙名４-３
	BOXMENU_WP_NAME4_4,		///< 壁紙名４-４
	BOXMENU_WP_NAME_EX_1,	///< 壁紙名隠し１
	BOXMENU_WP_NAME_EX_2,	///< 壁紙名隠し２
	BOXMENU_WP_NAME_EX_3,	///< 壁紙名隠し３
	BOXMENU_WP_NAME_EX_4,	///< 壁紙名隠し４
	BOXMENU_WP_NAME_EX_5,	///< 壁紙名隠し５
	BOXMENU_WP_NAME_EX_6,	///< 壁紙名隠し６
	BOXMENU_WP_NAME_EX_7,	///< 壁紙名隠し７
	BOXMENU_WP_NAME_EX_8,	///< 壁紙名隠し８
	BOXMENU_POKE_TUKAMU,	///< ポケモン「つかむ」
	BOXMENU_POKE_OKU,		///< ポケモン「ここにおく」
	BOXMENU_POKE_IREKAERU,	///< ポケモン「いれかえる」
	BOXMENU_POKE_YOUSU,		///< ポケモン「ようすをみる」
	BOXMENU_POKE_TURETEIKU,	///< ポケモン「つれていく」
	BOXMENU_POKE_AZUKERU,	///< ポケモン「あずける」
	BOXMENU_POKE_MOTIMONO,	///< ポケモン「もちもの」
	BOXMENU_POKE_MARKING,	///< ポケモン「マーキング」
	BOXMENU_POKE_NIGASU,	///< ポケモン「にがす」
	BOXMENU_POKEMENU_QUIT,	///< ポケモンメニュー「やめる」
	BOXMENU_MARKING_DECIDE,	///< マーキング「けってい」
	BOXMENU_MARKING_CANCEL,	///< マーキング「やめる」（キャンセル）
	BOXMENU_ITEM_SET,		///< アイテム「もたせる」
	BOXMENU_ITEM_WITHDRAW,	///< アイテム「あずかる」
	BOXMENU_ITEM_INFO,		///< アイテム「せつめい」
	BOXMENU_ITEM_SWAP,		///< アイテム「とりかえる」
	BOXMENU_ITEM_TO_BAG,	///< アイテム「バッグへ」
	BOXMENU_ITEM_QUIT,		///< アイテム「やめる」
	BOXMENU_COMPARE_HOLD_LEFT,	///< つよさくらべ「ひだりにこてい」
	BOXMENU_COMPARE_HOLD_RIGHT,	///< つよさくらべ「みぎにこてい」
	BOXMENU_YES,			///< はい
	BOXMENU_NO,				///< いいえ

	BOXMENU_MARK1,
	BOXMENU_MARK2,
	BOXMENU_MARK3,
	BOXMENU_MARK4,
	BOXMENU_MARK5,
	BOXMENU_MARK6,
}BOX_MENU_ID;


enum {
	BOX_MARK_MAX = 6,	// BOXMENU_MARK1～6と数を合わせる
};

//----------------------------------------------------------------------
/**
 *  メインワーク型定義
 */
//----------------------------------------------------------------------
typedef struct _BOXAPP_WORK  BOXAPP_WORK;

//----------------------------------------------------------------------
/**
 *  描画ワーク型定義
 */
//----------------------------------------------------------------------
typedef struct _BOXAPP_VIEW_WORK  BOXAPP_VIEW_WORK;

//----------------------------------------------------------------------
/**
 *  カーソル移動エリア
 */
//----------------------------------------------------------------------
enum CURSOR_AREA {
	CURSOR_AREA_TRAY,			///< トレイ
	CURSOR_AREA_PARTY,			///< 手持ちウィンドウ
	CURSOR_AREA_TRAY_TAB,		///< トレイのタブ
	CURSOR_AREA_PARTY_BUTTON,	///< 『てもちポケモン』のボタン
	CURSOR_AREA_EXIT_BUTTON,	///< 『とじる』ボタン
};

//----------------------------------------------------------------------
/**
 *  絞り込みモードアイコンID
 */
//----------------------------------------------------------------------
enum {
	LIMITMODE_ICON_ALLOFF,
	LIMITMODE_ICON_ITEM,
	LIMITMODE_ICON_MARK1,
	LIMITMODE_ICON_MARK2,
	LIMITMODE_ICON_MARK3,
	LIMITMODE_ICON_MARK4,
	LIMITMODE_ICON_MARK5,
	LIMITMODE_ICON_MARK6,

	LIMITMODE_ICON_MAX,
};

//----------------------------------------------------------------------
/**
 *  絞り込みモードビットフラグ
 */
//----------------------------------------------------------------------
enum {
	LIMITMODE_BIT_OFF = 0x0000,
	LIMITMODE_BIT_ITEM = 0x0001,
	LIMITMODE_BIT_MARK1 = 0x0002,
	LIMITMODE_BIT_MARK2 = 0x0004,
	LIMITMODE_BIT_MARK3 = 0x0008,
	LIMITMODE_BIT_MARK4 = 0x0010,
	LIMITMODE_BIT_MARK5 = 0x0020,
	LIMITMODE_BIT_MARK6 = 0x0040,
};

//----------------------------------------------------------------------
/**
 *  ポケモンつかみ状態
 */
//----------------------------------------------------------------------
enum {
	CURSOR_CATCH_NONE = 0x01,		///< つかんでいない
	CURSOR_CATCH_SINGLE = 0x02,		///< 単体でつかんでいる
	CURSOR_CATCH_AREA_POINT = 0x04,	///< 範囲選択でつかんでいて、ポケモンがカーソルの直下にある状態
	CURSOR_CATCH_AREA_FREE = 0x08,	///< 範囲選択でつかんでいて、ポケモンがカーソルの直下にない状態

	CURSOR_CATCH_AREA_MASK = (CURSOR_CATCH_AREA_POINT | CURSOR_CATCH_AREA_FREE),
	CUROSR_CATCH_STATUS_HOLD_MASK = (CURSOR_CATCH_SINGLE | CURSOR_CATCH_AREA_POINT ),
	
	
};

//----------------------------------------------------------------------
/**
 *  サブLCD表示状態
 */
//----------------------------------------------------------------------
typedef enum {
	SUBLCD_STATE_NORMAL,	// 通常時
	SUBLCD_STATE_TRAY,		// トレイ選択
	SUBLCD_STATE_MARK,		// マーク選択
}DISP_STATE;

//----------------------------------------------------------------------
/**
 *  そのた定数
 */
//----------------------------------------------------------------------
enum {
	TRAY_XPOS_MAX = BOX_MAX_COLUMN-1,
	TRAY_YPOS_MAX = BOX_MAX_RAW-1,

	CURSOR_PARTYTRAY_CLOSEBUTTON_POS = TEMOTI_POKEMAX,
};

//----------------------------------------------------------------------
/**
 *  ステータス表示するためのポケモンデータ
 */
//----------------------------------------------------------------------
typedef struct {
	void*	poke_data;
	u16		monsno;
	u16		itemno;
	u16		zukan_no;
	u8		level;
	u8		mark;
	u8		type1;	// タイプってのは「みず」とか「はがね」とか。
	u8		type2;	// アイコン表示するので文字列は不要。
	u8		sex;
	u8		tamago_flag;
	u8		update_flag;

	STRBUF*	nickname;
	STRBUF*	monsname;
	STRBUF*	itemname;
	STRBUF*	character;
	STRBUF*	ability;

}BOXAPP_STATUS_POKE;


//----------------------------------------------------------------------
/**
 *  強さ比べ用ポケモンデータ
 */
//----------------------------------------------------------------------
enum {
	BOXAPP_COMPARE_SIDE_LEFT,
	BOXAPP_COMPARE_SIDE_RIGHT,
};
enum {
	BOXAPP_COMPARE_PAGE_STATUS,
	BOXAPP_COMPARE_PAGE_CONDITION,
	BOXAPP_COMPARE_PAGE_SKILL,

	BOXAPP_COMPARE_PAGE_MAX,
};

typedef struct {
	void*	poke_data;
	u16		monsno;
	u8		tamago_flag;
	u8		form_number;

	// この並びは変えちゃダメ
	u16		level;
	u16		hp_max;
	u16		attack;
	u16		defence;
	u16		sp_attack;
	u16		sp_defence;
	u16		agility;

	u16		style;
	u16		beauty;
	u16		cute;
	u16		clever;
	u16		strong;

	u16		skill[4];

	STRBUF*	nickname;
	STRBUF*	character;

}BOXAPP_COMPARE_POKE_STATUS;

typedef struct {
	u8		updateSide;
	u8		page;
	u8		updateSideFlag[2];
	BOOL	pageButtonPushFlag;

	BOXAPP_COMPARE_POKE_STATUS      status[2];

}BOXAPP_COMPARE;

//----------------------------------------------------------------------
/**
 *  カーソル状態データ
 */
//----------------------------------------------------------------------
typedef struct {
	void*	point_poke;			///< 指しているポケモン

	u8   area;					///< ボックストレイ、手持ちトレイ、とじるボタン等
	s8   tray_xpos;				///< ボックストレイ内でのＸ位置
	s8   tray_ypos;				///< ボックストレイ内でのＹ位置
	s8   tray_pos;				///< ボックストレイ内でのデータ位置

	s8   partytray_pos;			///< 手持ちトレイ内でのデータ位置
	s8   partytray_prev_area;	///< 手持ちトレイ内へ以降するまえの area 

	u8  poke_point_flag;		///< ポケモンを指しているフラグ
	u8  poke_catch_flag;		///< ポケモンを掴んでいるフラグ

}BOXAPP_CURSOR;

//----------------------------------------------------------------------
/**
 *  つかんでるポケモンのデータ
 */
//----------------------------------------------------------------------
typedef struct {
	POKEMON_PASO_PARAM*		ppp;	///< 掴み中ポケデータ
	u8			areaStartX;			///< 範囲選択開始Ｘ座標（トレイ内位置）
	u8			areaStartY;			///< 範囲選択開始Ｙ座標（トレイ内位置）
	u8			areaEndX;			///< 範囲選択終了Ｘ座標（トレイ内位置）
	u8			areaEndY;			///< 範囲選択終了Ｙ座標（トレイ内位置）

	u8			areaPokeCount;
	u8			areaTopPos;
	u8			areaSpaceCatchFlag;			///< 範囲選択時、空白位置を掴んだ
	u8			fromPartyFlag;				///< 手持ちにいたポケモンを掴んだ
	s8			areaPokePos[BOX_MAX_POS];	///< トレイ内のどの位置から取得したポケモンか持っておく

}BOXAPP_CATCH_POKE;


//----------------------------------------------------------------------
/**
 *  表示中のトレイデータ
 */
//----------------------------------------------------------------------
typedef struct {
	u8			number;		///< 表示中トレイナンバー
	u8			wallPaper;	///< その壁紙ナンバー
	STRBUF*		name;
}BOXAPP_TRAY;

//----------------------------------------------------------------------
/**
 * メニュー情報データ
 */
//----------------------------------------------------------------------
#define BOXAPP_MENU_ELEMS_MAX	(8)
typedef struct {
	BOX_MENU_ID	id[ BOXAPP_MENU_ELEMS_MAX ];
	u8			pos;		///< 選択しているメニュー位置
	u8			cnt;		///< 登録されているメニュー数
	u8			mark;		///< マーキング状態
	u8			type;		///< 表示タイプ（現在未使用）
}BOXAPP_MENU;

//----------------------------------------------------------------------
/**
 *  ボックス選択ウィンドウデータ
 */
//----------------------------------------------------------------------
typedef struct {
	u32		center_trayno;		///< 中心のトレイナンバー
}BOXAPP_JUMPWIN;

//----------------------------------------------------------------------
/**
 *  サブLCD表示データ
 */
//----------------------------------------------------------------------
typedef struct {
	u8		state;				///< 表示状態
	u8      limit_pos;			///< 絞りこみモードアイコン位置
	u8		pos;				///< トレイモードアイコン位置
	s16		move;				///< 移動量
}BOXAPP_SUBLCD;

//----------------------------------------------------------------------
/**
 *  ボックスシステムデータ
 */
//----------------------------------------------------------------------
typedef struct {
	u8		boxMode;			///< ボックス動作モード（あずける・つれていく・せいり・どうぐ）
	u8		expertModeFlag;		///< 慣れてる人モードフラグ
	u16		limitModeBitFlag;	///< 絞り込みモードビットフラグ
}BOXAPP_SYSTEM;


//----------------------------------------------------------------------
/**
 *  ボックス描画用パラメータ
 *
 *  ※これらを box.c が操作し、boxv.c 以下の描画関数群は参照のみ行う。
 */
//----------------------------------------------------------------------
typedef struct {
	const BOX_DATA*			boxData;
	const POKEPARTY*		partyData;
	BOXAPP_CURSOR			cursor;
	BOXAPP_CATCH_POKE		catchPoke;
	BOXAPP_TRAY				tray;
	BOXAPP_SYSTEM			system;
	BOXAPP_STATUS_POKE		statusPoke;
	BOXAPP_MENU				menu;
	BOXAPP_JUMPWIN			jumpWin;
	BOXAPP_SUBLCD			subLCD;
	BOXAPP_COMPARE			compare;
	u32						message_id;
	u16						azukeruTrayNumber;
	u16						catch_item;
}BOXAPP_VPARAM;



extern BOOL BoxAppView_Init( BOXAPP_VIEW_WORK** vwk, const BOXAPP_VPARAM* vpara, const BOXAPP_WORK* mainwk );
extern void BoxAppView_SetCommand( BOXAPP_VIEW_WORK* vwk,  u32 cmd );
extern BOOL BoxAppView_WaitCommand( BOXAPP_VIEW_WORK* vwk, u32 cmd );
extern BOOL BoxAppView_WaitCommandAll( BOXAPP_VIEW_WORK* vwk );
extern void BoxAppView_Main( BOXAPP_VIEW_WORK* wk );
extern void BoxAppView_End( BOXAPP_VIEW_WORK* wk );

/*===================================================================================*/
/*  描画パラメータ関連                                                               */
/*===================================================================================*/
extern MSGDATA_MANAGER* BoxApp_GetMsgManager( const BOXAPP_WORK* wk );
extern const WORDSET* BoxApp_GetWordSet( const BOXAPP_WORK* wk );
extern u32 BoxAppVPara_GetBoxMode( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorArea( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorTrayPosX( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorTrayPosY( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorTrayPos( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorPartyPos( const BOXAPP_VPARAM* vpara );
extern BOOL BoxAppVPara_GetCursorPointPokeFlag( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCursorCatchPokeFlag(const BOXAPP_VPARAM* vpara );
extern BOOL BoxAppVPara_GetCursorCatchPokeFromPartyFlag( const BOXAPP_VPARAM* vpara );
extern BOOL BoxAppVPara_GetCursorStatusEnableFlag(const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetTrayBoxNumber( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetMessageID( const BOXAPP_VPARAM* vpara );
extern POKEMON_PASO_PARAM* BoxAppVPara_GetStatusPokePara( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetStatusPokeItemNumber( const BOXAPP_VPARAM* vpara );
extern const BOXAPP_STATUS_POKE* BoxAppVpara_GetStatusPokeData( const BOXAPP_VPARAM* vpara );
extern const BOXAPP_TRAY* BoxAppVpara_GetTrayData( const BOXAPP_VPARAM* vpara );
extern const BOX_DATA* BoxAppVPara_GetBoxData( const BOXAPP_VPARAM* vpara );
extern s32 BoxAppVPara_GetSubLCDMove( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetSubLCDPos( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetSubLCDLimitPos( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetJumpWinCenterTrayNumber( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetLimitModeBitFlag( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetStatusPokeMarkBit( const BOXAPP_VPARAM* vpara );
extern BOOL BoxAppVPara_GetExpertModeFlag( const  BOXAPP_VPARAM* vpara );
extern void BoxAppVPara_GetAreaSelectParam( const BOXAPP_VPARAM* vpara, u32* left, u32* right, u32* top, u32* bottom );
extern BOOL BoxAppVPara_CheckAreaSelectSinglePoke( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetAreaSelectCursorTopPos( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetAreaSelectIconOfsPos( const BOXAPP_VPARAM* vpara, u32 idx );
extern BOOL BoxAppVPara_GetAreaSelectCatchSpaceFlag( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCatchItemNumber( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetInfoItemNumber( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetCompareUpdateSide( const BOXAPP_VPARAM* vpara );
extern u32 BoxAppVPara_GetComparePage( const BOXAPP_VPARAM* vpara );
extern const BOXAPP_COMPARE_POKE_STATUS* BoxAppVPara_GetCompareStatus( const BOXAPP_VPARAM* vpara, int side );
extern BOOL BoxAppVPara_GetCompareUpdatedSideFlag( const BOXAPP_VPARAM* vpara, int side );
extern BOOL BoxAppVPara_GetComparePageButtonPushFlag( const BOXAPP_VPARAM* vpara );
extern int BoxApp_GetTalkWinType( const BOXAPP_WORK* wk );
extern BOOL BoxAppVPara_GetStatusPokeTamagoFlag( const BOXAPP_VPARAM* vpara );


/*===================================================================================*/
/*  ポケモンを逃がす時のワザチェック関連                                             */
/*===================================================================================*/
extern BOOL BoxApp_ReleaseWazaCheckDone( const BOXAPP_WORK* mainWk );
extern BOOL BoxApp_ReleaseWazaCheckOK( const BOXAPP_WORK* mainWk );

#endif
