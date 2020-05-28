//============================================================================================
/**
 * @file	comm_fushigi_card.c
 * @bfief	ふしぎな　おくりもの カードの確認画面
 * @author	Satoshi Mitsuhara
 * @date	06.05.19
 *
 * $Id: comm_mystery_card.c,v 1.54 2006/08/07 11:48:10 mitsuhara Exp $
 */
//============================================================================================

// [Main]
// BG0	メッセージウィンドウ
// BG1	カード背景
// BG2	手前のメニュー
// BG3	一番後ろの格子模様

// [Sub]
// 格子模様のみ


#include "common.h"
#include "system/main.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/arc_util.h"
#include "system/msgdata_util.h"
#include "system/wipe.h"
#include "system/bmp_list.h"
#include "system/clact_tool.h"
#include "system/snd_tool.h"
#include "system/laster.h"

#include "savedata/fushigi_data.h"
#include "savedata/config.h"

#include "communication/communication.h"
#include "communication/comm_state.h"

#include "poketool/pokeicon.h"

#include "comm_mystery_state.h"
#include "comm_mystery_gift.h"
#include "comm_mystery_func.h"
#include "mysterylib.h"
#include "mystery.naix"

#include "msgdata/msg.naix"
#include "msgdata/msg_mystery.h"
//#include "nitrocrypto/crypto.h"

void STRBUF_SetStringCodeOrderLength( STRBUF* strbuf, const STRCODE* str, u32 len );

#define MYSTERYCARD_WIN_MAX	20

extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);
extern void MysteryCard_DisplayCardOnly(GF_BGL_INI *bgl, void *p, int heapid);


//============================================================================================
//	定数定義
//============================================================================================
#define MYSTERYCARD_HEADSIZE	0x20000

#define TWAKU_PALETTE_NUMBER	10
#define LATTICEBG_PALNO		11
#define OSUSOWAKE_PALNO		12
#define WAKU_PALETTE_NUMBER1	13
#define WAKU_PALETTE_NUMBER2	14
#define	FONT_PALNO_NORMAL	15	/* ノーマルパレット */
#define	MYSTERYCARD_BLACK	(GF_PRINTCOLOR_MAKE( 1, 2, 0))
#define	MYSTERYCARD_WHITE	(GF_PRINTCOLOR_MAKE(15, 2, 0))
#define	MYSTERYCARD_OWHITE	(GF_PRINTCOLOR_MAKE(14, 15, 0))

#define MYSTERYCARD_RED		(GF_PRINTCOLOR_MAKE( 3,  4, 0))
#define MYSTERYCARD_BLUE	(GF_PRINTCOLOR_MAKE( 5,  6, 0))

#define LATTICEBG_CHARBASE	(0)


#define MYSTERYCARD_FRAMECHR1	1
#define MYSTERYCARD_FRAMECHR2	(MYSTERYCARD_FRAMECHR1 + MENU_WIN_CGX_SIZ)
#define MYSTERYCARD_TFRAMECHR	(MYSTERYCARD_FRAMECHR2 + MENU_WIN_CGX_SIZ)
#define MYSTERYCARD_CHBASE	(MYSTERYCARD_TFRAMECHR + TALK_WIN_CGX_SIZ)

/* グラフィックスの表裏 */
#define MYSTERYCARD_FRONT	0
#define MYSTERYCARD_BACK	1
#define MYSTERYCARD_MENU	2
#define MYSTERYCARD_SEND	3
#define WHITE			1
#define BLACK			2

/* メニューウィンドウのデータがある場所 */
#define MYSTERYCARD_INDEX_MENU	7
#define MYSTERYCARD_MENU_BASE	640

/* エントリ数を表示しているウィンドウのインデックス */
#define MYSTERYCARD_ENTRY_COUNT	15
/* エントリーを表示しているウィンドウのインデックス */
#define MYSTERYCARD_ENTRY_LIST	16
/* 最後のメッセージウィンドウ */
#define MYSTERYCARD_INDEX_LASTWIN	17


/* おすそわけできる最大人数 */
#define MYSTERYCARD_OSUSOWAKE_MAX	4
/* おすそわけするメンバー名の表示幅 */
#define MYSTERYCARD_OSUSOWAKE_HEIGHT	24

/* 表示するポケモンのアイコン数 */



// ポケモンアイコンが始まるVRAM上でのオフセット
#define POKEICON_VRAM_OFFSET ( 0x64 )
#define POKEICON_TRANS_CHARA	(4*4)
#define POKEICON_TRANS_SIZE		(POKEICON_TRANS_CHARA*0x20)
// ポケモンアイコンのパレットを転送するオフセット
#define POKEICON_PAL_OFFSET				(  3 )

//** CharManager PlttManager用 **//
#define RECORD_CHAR_CONT_NUM				(20)
#define RECORD_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define RECORD_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define RECORD_PLTT_CONT_NUM				(20)


// カードをめくる動作用
typedef struct {
  u16 sbuff[2][HW_LCD_HEIGHT*4];
  LASTER_SYS_PTR laster_ptr;
  TCB_PTR tcb_ptr;
  fx32 speed, accel;
  BOOL do_run;
  BOOL mode;		// true: close   false: open
} CARDTURN;


typedef struct {
  int heapid;

  MYSTERYGIFT_WORK gwk;
  
  GF_BGL_INI *bgl;
  WORDSET *word;	       			// 単語モジュール制御ワークへのポインタ
  MSGDATA_MANAGER *msgman;	    		// MSGデータマネージャへのポインタ

  GF_BGL_BMPWIN	win[MYSTERYCARD_WIN_MAX];	// メッセージを表示するウィンドウ
  int chbase[MYSTERYCARD_WIN_MAX];

  int nowbase;
  void *tbl;

  FUSHIGI_DATA *fdata;				// ふしぎデータを読んだ場所
  SAVEDATA *sv;
  CONFIG *cfg;
  int win_type;
  LOAD_RESULT load_result;
  GIFT_CARD *card[GIFT_CARD_MAX];		// カードデータへのポインタ

  int disp_card;				// 表示対象になっているカード番号
  int disp_side;				// 表示している面

  BMPLIST_WORK *lw;				// メニュー
  BMP_MENULIST_DATA *bmd;

  GF_BGL_BMPWIN	msgwin;				// メッセージを表示するウィンドウ
  GF_BGL_BMPWIN	menuwin;			// メニューを表示するウィンドウ
  int menu_index;

  int entry;					// おすそわけに繋げてきた人の数
  u32 tranerid[MYSTERYCARD_OSUSOWAKE_MAX];	// 前回繋がっていたトレーナーＩＤ

  MYSTATUS *my[MYSTERYCARD_OSUSOWAKE_MAX+1];	// 前回繋がっていたトレーナーＩＤ
  int worder[MYSTERYCARD_OSUSOWAKE_MAX+1];

  int prev_connect;				// ついさっきまで繋げていた人数
  int sync_wait;
  void (*wait_end_func)(void *p);
  int write_index;
  
  int next_seq;

  // セルアクター関連
  CLACT_SET_PTR	clactSet;				// セルアクターセット 
  CLACT_U_EASYRENDER_DATA renddata;			// 簡易レンダーデータ
  CLACT_U_RES_MANAGER_PTR resMan[CLACT_U_RES_MAX];	// リソースマネージャ
  CLACT_U_RES_OBJ_PTR resObjTbl[CLACT_U_RES_MAX];	// リソースオブジェテーブル
  CLACT_HEADER clActHeaderMain;
  // ボタンアイコンの背景
  CLACT_WORK_PTR ibase[2];

  // ポケモンアイコンの表示
  CLACT_WORK_PTR pokeicon[3];

  //  CRYPTORC4Context rc4context;
  //  GIFT_BEACON_CRC gbc;				// ビーコンデータ
  GIFT_DATA comm_data;					// 暗号化されたデータ

  CARDTURN cturn;					// カードめくり用
  void (*func_hook)(void *);				// 外部ファンクション実行用

  int select_icon;
  void *time_icon;

  
} MYSTERYCARD_WORK;


enum {
  MYSTERYCARD_READ_SAVEDATA = 0,	/* セーブデータの読み込み */
  MYSTERYCARD_SEQ_INIT,			/* 初期化 */
  MYSTERYCARD_SEQ_CREATE_SCREEN,	/* 初期画面作成 */
  
  MYSTERYCARD_SEQ_MAIN,			/* メインループ */

  MYSTERYCARD_SEQ_CREATE_MENU,		/* メニューの作成 */
  MYSTERYCARD_SEQ_MENU,			/* メニューのメインループ */
  MYSTERYCARD_SEQ_MENU_TO_VIEWMODE,	/* カードの説明文を見るモードへ移行 */
  MYSTERYCARD_SEQ_MENU_TO_VIEWMODE2,
  MYSTERYCARD_SEQ_MENU_VIEWMODE,	/* カードの説明文を見るモード */
  MYSTERYCARD_SEQ_MENU_VIEWMODE2,
  MYSTERYCARD_SEQ_MENU_VIEWMODE3,
  MYSTERYCARD_SEQ_END_MENU,		/* メニューを終了してメインループへ */
  MYSTERYCARD_SEQ_REMOVE_MENU,		/* カードを消すメニューのメインループ */

  MYSTERYCARD_SEQ_SENDFIGT_YESNO,	/* おすわけしますか？　はい／いいえ */
  MYSTERYCARD_SEQ_COMM_YESNO,		/* ＤＳワイヤレス通信を開始しますか？　はい／いいえ */
  MYSTERYCARD_SEQ_MENU_TO_SENDGIFT,	/* おすそわけ画面へ行く準備 */
  MYSTERYCARD_SEQ_MENU_TO_SENDGIFT2,	/* おすそわけ画面へ行く準備 その２ */
  MYSTERYCARD_SEQ_MENU_TO_SENDGIFT3,	/* おすそわけ画面へ行く準備 その３ */
  MYSTERYCARD_SEQ_ENTRY_SENDGIFT,	/* おすそわけ画面 */

  MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END1,	/* おすそわけ画面終了 その１ */
  MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END2,	/* おすそわけ画面終了 その２ */

  MYSTERYCARD_SEQ_SEND_WAITSYNC,	/* タイミングをとってデータ送信 */
  MYSTERYCARD_SEQ_WAIT_ENDCOMM,		/* 通信ライブラリが終了するまで待つ */
  MYSTERYCARD_SEQ_SEND_SAVEDATA,	/* おすそわけ後のデータセーブ */
  MYSTERYCARD_SEQ_LAST_SAVE_WAIT,	/* 子機と同期が取れるまで待ってから最後のセーブ処理 */

  MYSTERYCARD_SEQ_SEND_FINISH,		/* 終了(電源OFF) */
  
  MYSTERYCARD_SEQ_TO_RETURN,		/* 前のメニューへ戻るための入り口 */
  MYSTERYCARD_SEQ_WAIT_FADE,		/* フェードが終了するまで待つ */

  MYSTERYCARD_SEQ_RETURN,		/* 前のメニュー画面へ戻る */
  MYSTERYCARD_SEQ_LOOP,			/* エラー時の無限ループ */

  MYSTERYCARD_SEQ_MAX
};


typedef struct {
  int id;
  u32 param;
} LISTDATA;



//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static int MysteryCardGoRemove(PROC *proc);
static int MysteryCardGoSendGift(PROC *proc);
static int MysteryCardRetMainMenu(PROC *proc);
static int MysteryCardRemove(PROC *proc);
static void MysteryCardRemoveMainMenu(MYSTERYCARD_WORK *wk);
static BOOL _nop(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardTitleWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardStatusWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardDateWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardTextWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardTransWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardMenu1Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardMenu2Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardMenu3Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static BOOL MysteryCardDrawEntry(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);
static int MysteryCardDispConnectChildStatus(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win);
static void MysteryCardDispConnectChildCount(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, int num);
static void CommMysteryCardExit(MYSTERYCARD_WORK *wk, int *seq, int next);
static int MysteryCardCreateWindow(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN	*win, int index, int base);
static void CreateCardGraphics(MYSTERYCARD_WORK *wk, int side);
static int MysteryCardNextCard(MYSTERYCARD_WORK *wk, int card, int add);
static void MysteryCardCreateMsgWindow(MYSTERYCARD_WORK *wk, int font, int side);

static int CommMysteryCard_CreateBeacon(MYSTERYCARD_WORK *wk);
//static void CommMysteryCard_CreateSendData(MYSTERYCARD_WORK *wk);

static void MysteryCard_DisplayPokemonIcon(MYSTERYCARD_WORK *wk);
static void RemoveCellActor(MYSTERYCARD_WORK *wk);
static int MysteryCardGetConnectCount(MYSTERYCARD_WORK *wk);

//============================================================================================
//	グローバル変数
//============================================================================================
typedef struct {
  int side;
  int sx, sy;
  int width, height;
  int font;
  int color;
  int background;
  
  u32 msgid;
  BOOL (*func)(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col);

  int ox, oy;
  
} MYSTERYCARD_MSGWIN_TABLE;

MYSTERYCARD_MSGWIN_TABLE MsgWin_Table[] = {
  /*  ------------------------------ 表面 ---------------------------- */
  /* ふしぎなカード */
  /*  0 */ { MYSTERYCARD_FRONT, 2,  2, 12,  2, FONT_TALK, MYSTERYCARD_BLACK, -1,	mystery_card_001,	_nop },
  /* もらったひづけ */
  /*  1 */ { MYSTERYCARD_FRONT, 6, 17, 11,  2, FONT_TALK, MYSTERYCARD_WHITE, -1,	mystery_card_005,	_nop },
  /* ポケモンセンターにいる\nはいたついんから　うけとってください　など */
  /*  2 */ { MYSTERYCARD_FRONT, 2,  9, 28,  4, FONT_TALK, MYSTERYCARD_BLACK, -1,	NULL,		MysteryCardStatusWin },
  /* カード名の表示 */
  /*  3 */ { MYSTERYCARD_FRONT, 2,  6, 28,  2, FONT_TALK, MYSTERYCARD_WHITE, -1,	NULL,		MysteryCardTitleWin },
  /* 日付 */
  /*  4 */ { MYSTERYCARD_FRONT,18, 17, 11,  2, FONT_TALK, MYSTERYCARD_BLACK, -1,	mystery_card_014,		MysteryCardDateWin },

  /*  ------------------------------ 裏面 ---------------------------- */
  /* カードの説明 */
  /*  5 */ { MYSTERYCARD_BACK , 2,  3, 28, 10, FONT_TALK, MYSTERYCARD_BLACK, -1,	NULL,		MysteryCardTextWin },
  /* くばれる回数とメッセージ表示 */
  /*  6 */ { MYSTERYCARD_BACK , 2, 14, 28,  4, FONT_TALK, MYSTERYCARD_BLACK, -1,	mystery_card_006,	MysteryCardTransWin },

  /*  ------------------------------ メニュー ---------------------------- */
  /*  7 */ { MYSTERYCARD_MENU , 2, 19, 27,  4, FONT_TALK, MYSTERYCARD_BLACK, 15,	mystery_card_001,	_nop },
  /*  8 */ { MYSTERYCARD_MENU ,18,  9, 12,  8, FONT_TALK, MYSTERYCARD_BLACK, FONT_HEADER_F_COLOR,	NULL,		MysteryCardMenu1Win },
  /*  9 */ { MYSTERYCARD_MENU ,24, 13,  6,  4, FONT_TALK, MYSTERYCARD_BLACK, FONT_HEADER_F_COLOR,	NULL,		MysteryCardMenu2Win },
  /* 10 */ { MYSTERYCARD_MENU ,24, 13,  6,  4, FONT_TALK, MYSTERYCARD_BLACK, FONT_HEADER_F_COLOR,	NULL,		MysteryCardMenu3Win },

  /*  ------------------------------ おすそわけ ---------------------------- */
  /* ともだちはいしん　うけつけちゅう */
  /* 11 */ { MYSTERYCARD_SEND,  1,  1, 25,  2, FONT_SYSTEM, MYSTERYCARD_OWHITE, -1,	mystery_osusowake_001, _nop, 7, 0},
  /* げんざいのエントリー */
  /* 12 */ { MYSTERYCARD_SEND, 23,  7,  9,  4, FONT_SYSTEM, MYSTERYCARD_OWHITE, -1,	mystery_osusowake_004, _nop, 2, 0 },
  /* くばる */
  /* 13 */ { MYSTERYCARD_SEND,  6, 20,  6,  2, FONT_SYSTEM, MYSTERYCARD_OWHITE, -1,	mystery_osusowake_006, _nop, 8, 1},
  /* やめる */
  /* 14 */ { MYSTERYCARD_SEND, 21, 20,  6,  2, FONT_SYSTEM, MYSTERYCARD_OWHITE, -1,	mystery_osusowake_007, _nop, 0, 1 },
  /* げんざいのエントリー(○／４) */
  /* 15 */ { MYSTERYCARD_SEND, 25, 12,  4,  2, FONT_TALK, MYSTERYCARD_BLACK, -1,	mystery_osusowake_005, MysteryCardDrawEntry },
  /* 実際にエントリしてる人を表示するウィンドウ */
  /* 16 */ { MYSTERYCARD_SEND,  2,  5, 19, 11, FONT_SYSTEM, MYSTERYCARD_BLACK, -1,	NULL,		     _nop },

  /* おすそわけ中＆電源をきってくださいウィンドウ */
  /* 17 */ { MYSTERYCARD_MENU , 2, 19, 27,  4, FONT_TALK, MYSTERYCARD_BLACK, 14,	mystery_osusowake_008, _nop },
  /* 18 */ { MYSTERYCARD_MENU , 2, 19, 27,  4, FONT_TALK, MYSTERYCARD_BLACK, 14,	mystery_osusowake_009, _nop },
};

/* メニュー用データ */
LISTDATA MysteryCard_Menu1Data[] = {
  { mystery_card_007, (u32)MYSTERYCARD_SEQ_MENU_TO_VIEWMODE },	// せつめいを　よむ
  { mystery_card_008, (u32)MysteryCardGoSendGift },		// おすそわけ
  { mystery_card_009, (u32)MysteryCardGoRemove },		// すてる
  { mystery_card_010, (u32)MYSTERYCARD_SEQ_END_MENU },		// やめる
};
/* カードを消す選択 */
LISTDATA MysteryCard_Menu2Data[] = {
  { mystery_drop_004, (u32)MysteryCardRemove },			// はい
  { mystery_drop_005, (u32)MysteryCardRetMainMenu },		// いいえ
};
/* おすそわけ選択 */
LISTDATA MysteryCard_Menu3Data[] = {
  { mystery_drop_004, (u32)MYSTERYCARD_SEQ_COMM_YESNO },	// はい
  { mystery_drop_005, (u32)MysteryCardRetMainMenu },		// いいえ
};
/* ＤＳワイヤレス通信をする？選択 */
LISTDATA MysteryCard_Menu4Data[] = {
  { mystery_drop_004, (u32)MYSTERYCARD_SEQ_MENU_TO_SENDGIFT },	// はい
  { mystery_drop_005, (u32)MysteryCardRetMainMenu },		// いいえ
};

/* 汎用メニュー構造体(中身を書き換えて再利用) */
static BMPLIST_HEADER MenuListHeader = {
  NULL,
  MysteryLib_MenuKeyMove,	 	/* カーソル移動ごとのコールバック関数 */
  NULL,				     	/* 一列表示ごとのコールバック関数 */
  NULL,					/* BMPウィンドウデータ */
  0,/* 後で埋める */			/* リスト項目数 */
  4,					/* 表示最大項目数 */
  0,					/* ラベル表示Ｘ座標 */
  12,					/* 項目表示Ｘ座標 */
  0,					/* カーソル表示Ｘ座標 */
  0,					/* 表示Ｙ座標 */
  FBMP_COL_BLACK,			/*文字色 */
  FBMP_COL_WHITE,			/*背景色 */
  FBMP_COL_BLK_SDW,			/*文字影色 */
  0,					/* 文字間隔Ｘ */
  16,					/* 文字間隔Ｙ */
  BMPLIST_LRKEY_SKIP,			/* ページスキップタイプ */
  FONT_SYSTEM, 				/* 文字指定(本来は u8 だけど、そんなに作らないと思うので) */
  0			  		/* ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF) */
};



//------------------------------------------------------------------
/**
 * @brief	セルアクターの初期化
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void InitCellActor(MYSTERYCARD_WORK *wk)
{
  RemoveCellActor(wk);
  MysteryLib_InitCPManager();
  MysteryLib_InitClactSystem();
  MysteryLib_InitClact(ARC_MYSTERY_GRA,
		       NARC_mystery_fusigi_panel_00_lz_ccgr,
		       NARC_mystery_fusigi_panel_nclr,
		       NARC_mystery_fusigi_panel_00_lz_ccer,
		       NARC_mystery_fusigi_panel_00_lz_canr,
		       GF_BGL_MAIN_DISP);
}


//------------------------------------------------------------------
/**
 * @brief	セルアクターの削除
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void RemoveCellActor(MYSTERYCARD_WORK *wk)
{
  if(wk->ibase[0])	CLACT_Delete(wk->ibase[0]);
  if(wk->ibase[1])	CLACT_Delete(wk->ibase[1]);
  wk->ibase[0] = wk->ibase[1] = NULL;
  if(wk->pokeicon[0])	CLACT_Delete(wk->pokeicon[0]);
  if(wk->pokeicon[1])	CLACT_Delete(wk->pokeicon[1]);
  if(wk->pokeicon[2])	CLACT_Delete(wk->pokeicon[2]);
  wk->pokeicon[0] = wk->pokeicon[1] = wk->pokeicon[2] = NULL;
  MysteryLib_RemoveClact();
}

//------------------------------------------------------------------
/**
 * @brief	選択／やめる土台オブジェクトの登録
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetBaseIcon(MYSTERYCARD_WORK *wk)
{
  wk->select_icon = 0;
  wk->ibase[0] = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->ibase[0],  72, 168, 1);
  CLACT_BGPriorityChg(wk->ibase[0], 2);
  wk->ibase[1] = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->ibase[1], 184, 168, 0);
  CLACT_BGPriorityChg(wk->ibase[1], 2);
}


//------------------------------------------------------------------
/**
 * @brief	ウィンドウが存在すればクリアする
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CMC_BmpMenuWinClear(GF_BGL_BMPWIN * win, u8 trans_sw)
{
  if(GF_BGL_BmpWinAddCheck(win) == TRUE)
    BmpMenuWinClear(win, trans_sw);
}
static void CMC_BmpTalkWinClear(GF_BGL_BMPWIN * win, u8 trans_sw)
{
  if(GF_BGL_BmpWinAddCheck(win) == TRUE)
    BmpTalkWinClear(win, trans_sw);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	メニューを登録する汎用関数
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateWindowMenuData(MYSTERYCARD_WORK *wk, LISTDATA *ld, int num, GF_BGL_BMPWIN *win)
{
  int i;
  BMPLIST_HEADER list_h;

  if(wk->bmd)	BMP_MENULIST_Delete(wk->bmd);
  if(wk->lw) 	BmpListExit(wk->lw, NULL, NULL);
  /* メニューの文字列を登録 */
  wk->bmd = BMP_MENULIST_Create(num,HEAPID_MYSTERYCARD);
  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYCARD);
  for(i = 0; i < num; i++)
    BMP_MENULIST_AddArchiveString(wk->bmd, wk->msgman, ld[i].id, ld[i].param);
  MSGMAN_Delete(wk->msgman);
  /* desc作成 → 変更 → 登録 */
  list_h = MenuListHeader;
  list_h.list = wk->bmd;
  list_h.count = num;
  list_h.win = win;
  wk->lw = BmpListSet( &list_h, 0, 0, HEAPID_MYSTERYCARD);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	指定のウィンドウに文字列を表示
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void DrawStringWindow(GF_BGL_BMPWIN *win, int msgid)
{
  STRBUF *msg;
  MSGDATA_MANAGER *msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYCARD);
  WORDSET *word = WORDSET_Create(HEAPID_MYSTERYCARD);

  GF_BGL_BmpWinDataFill(win, FontHeaderGet(FONT_TALK, FONT_HEADER_B_COLOR));
  msg = MSGDAT_UTIL_AllocExpandString(word, msgman, msgid, HEAPID_MYSTERYCARD);
  GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, MYSTERYCARD_BLACK, NULL);
  GF_BGL_BmpWinOn(win);

  STRBUF_Delete(msg);
  MSGMAN_Delete(msgman);
  WORDSET_Delete(word);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	おすそわけ画面の作成
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void MysteryCardCreateOsusowake(GF_BGL_INI *ini)
{
  // おすそわけ画面専用のフォントパレットを転送
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_font_00_nclr, PALTYPE_MAIN_BG, 16*2*FONT_PALNO_NORMAL, 16*2, HEAPID_MYSTERYCARD);

  // メイン画面ＢＧパレット転送
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_recep_nclr, PALTYPE_MAIN_BG, 16*2*OSUSOWAKE_PALNO, 16*2, HEAPID_MYSTERYCARD);
  // メイン画面BG1キャラ転送
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_recep_00_lz_ccgr, ini,
		    GF_BGL_FRAME1_M, 0, 6*16*0x20, 1, HEAPID_MYSTERYCARD);
  // メイン画面スクリーン１
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_recep_00_lz_cscr, ini,
		  GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_MYSTERYCARD);
  GF_BGL_ScrPalChange(ini, GF_BGL_FRAME1_M, 0, 0, 32, 24, OSUSOWAKE_PALNO);
  GF_BGL_LoadScreenReq(ini, GF_BGL_FRAME1_M);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	おすそわけする処理へ移行
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardGoSendGift(PROC *proc)
{
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);
  MysteryCardRemoveMainMenu(wk);

  DrawStringWindow(&wk->msgwin, mystery_card_011);
  MysteryCardCreateWindow(wk, &wk->menuwin, MYSTERYCARD_INDEX_MENU+3, wk->menu_index);
  return MYSTERYCARD_SEQ_SENDFIGT_YESNO;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	カードをすてる処理に移行
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardGoRemove(PROC *proc)
{
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);
  MysteryCardRemoveMainMenu(wk);

  if(FUSHIGIDATA_GetCardLinkDeli(wk->fdata, wk->disp_card+1) == TRUE)
    /* おくりもの　を　うけとってませんが\nこの　カードを　すてますか？ */
    DrawStringWindow(&wk->msgwin, mystery_drop_002);
  else
    /* この　カードを　すてますか？ */
    DrawStringWindow(&wk->msgwin, mystery_drop_001);

  MysteryCardCreateWindow(wk, &wk->menuwin, MYSTERYCARD_INDEX_MENU+2, wk->menu_index);
  return MYSTERYCARD_SEQ_REMOVE_MENU;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	カードを捨てる処理
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardRemove(PROC *proc)
{
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);

  /* カードを捨ててます…の処理 */
  MysteryCardRemoveMainMenu(wk);
  DrawStringWindow(&wk->msgwin, mystery_drop_003);
  /* タイムアイコン表示スタート */
  wk->time_icon = TimeWaitIconAdd(&wk->msgwin, MYSTERYCARD_TFRAMECHR);

#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("捨てるカード %d\n", wk->disp_card);
#endif
  /* カードの抹消処理 */
  FUSHIGIDATA_RemoveCardData(wk->fdata, wk->disp_card);
  SaveData_Save(wk->sv);

  /* タイムアイコンを消す */
  TimeWaitIconDel(wk->time_icon);
  
  /* カードが残っていればメイン処理へ
     残っていなければ「ふしぎな　おくりもの」のメニューまで戻る */
  if(FUSHIGIDATA_IsExistsCardAll(wk->fdata) == FALSE)
    return MYSTERYCARD_SEQ_TO_RETURN;
  
  /* カードが残っているので、次のカードを探して表示 */
  wk->disp_card = MysteryCardNextCard(wk, wk->disp_card,  1);

  OS_TPrintf("次に表示するカード %d\n", wk->disp_card);

  DrawStringWindow(&wk->msgwin, mystery_card_001);
  MysteryCardCreateWindow(wk, &wk->menuwin, MYSTERYCARD_INDEX_MENU+1, wk->menu_index);

  MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);

  return MYSTERYCARD_SEQ_MENU;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	メインメニューに戻る
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardRetMainMenu(PROC *proc)
{
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);
  MysteryCardRemoveMainMenu(wk);
  DrawStringWindow(&wk->msgwin, mystery_card_001);
  MysteryCardCreateWindow(wk, &wk->menuwin, MYSTERYCARD_INDEX_MENU+1, wk->menu_index);
  return MYSTERYCARD_SEQ_MENU;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	メニューを消す
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void MysteryCardRemoveMainMenu(MYSTERYCARD_WORK *wk)
{
  BMP_MENULIST_Delete(wk->bmd); wk->bmd = NULL;
  BmpListExit(wk->lw, NULL, NULL); wk->lw = NULL;
  CMC_BmpMenuWinClear(&wk->menuwin, WINDOW_TRANS_ON);
  GF_BGL_BmpWinOff(&wk->menuwin); GF_BGL_BmpWinDel(&wk->menuwin);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	何もしない
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL _nop(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col){ return TRUE; }

//--------------------------------------------------------------------------------------------
/**
 * @brief	カードのタイトル表示
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardTitleWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  STRBUF *msg;

  msg = STRBUF_Create( GIFT_DATA_CARD_TITLE_MAX+1, wk->heapid );
  STRBUF_SetStringCodeOrderLength(msg, wk->card[wk->disp_card]->beacon.event_name, GIFT_DATA_CARD_TITLE_MAX);
  GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, col, NULL);
  STRBUF_Delete(msg);
  return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	カードの状態を表示
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardStatusWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  STRBUF * msg;
  GIFT_CARD *card = wk->card[wk->disp_card];
  int msgid;


  //  card->gift_type = MYSTERYGIFT_TYPE_NONE;
  
  //  if(card->gift_type == MYSTERYGIFT_TYPE_NONE){
  if(card->beacon.delivery_flag == FALSE){
    /* カード情報のみで配達員のデータがない場合 */
    msgid = mystery_card_004;
  } else {
    if(wk->fdata == NULL || FUSHIGIDATA_GetCardLinkDeli(wk->fdata, wk->disp_card+1) == TRUE)
      /* 配達員情報があって、まだユーザーが受け取ってない場合 */
      msgid = mystery_card_002;
    else
      /* 配達員から受け取っていた場合のメッセージ */
      msgid = mystery_card_003;
  }

  msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, msgid, wk->heapid);
  GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, col, NULL);
  STRBUF_Delete(msg);
  return TRUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	日付を表示
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardDateWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  RTCDate date;

  RTC_ConvertDayToDate(&date, wk->card[wk->disp_card]->recv_date);
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_Printf("pokemon_icon = %d, %d, %d\n",
	    wk->card[wk->disp_card]->pokemon_icon[0],
	    wk->card[wk->disp_card]->pokemon_icon[1],
	    wk->card[wk->disp_card]->pokemon_icon[2]);
  OS_Printf("今までに配布した回数 = %d\n", wk->card[wk->disp_card]->re_dealed_count);
  OS_Printf("%04d/%02d/%02d [ %d ]\n", date.year, date.month, date.day, wk->card[wk->disp_card]->recv_date);
#endif  

  // 文字列をセットだけして後はメッセージに任せる
  WORDSET_RegisterNumber(wk->word, 0, date.year+2000, 4, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  WORDSET_RegisterNumber(wk->word, 1, date.month,     2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  WORDSET_RegisterNumber(wk->word, 2, date.day,       2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  return TRUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	カードの説明文を表示
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardTextWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  STRBUF * msg;

  msg = STRBUF_Create( GIFT_DATA_CARD_TEXT_MAX+1, HEAPID_MYSTERYCARD );
  STRBUF_SetStringCodeOrderLength(msg, wk->card[wk->disp_card]->event_text, GIFT_DATA_CARD_TEXT_MAX);
  GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, col, NULL);
  STRBUF_Delete(msg);
  return FALSE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	配布できる回数を表示する
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardTransWin(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
#if 0	// 無限回数表示テスト
  wk->card[wk->disp_card]->re_deal_count = 255;
#endif

  if(wk->card[wk->disp_card]->re_deal_count == 255){
    // 無限回数の配布
    STRBUF * msg;
    msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, mystery_card_016, HEAPID_MYSTERYCARD);
    GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, col, NULL);
    STRBUF_Delete(msg);
    return FALSE;
  } else if(wk->card[wk->disp_card]->re_deal_count){
    // 指定回数の配布
    WORDSET_RegisterNumber(wk->word, 0,
			   wk->card[wk->disp_card]->re_deal_count,
			   3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
    return TRUE;
  } else {
    // 再配布できないので表示しない
    return FALSE;
  }
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	メニュー１を作成
 *		メインメニュー
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardMenu1Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  LISTDATA ld[4];
  MYSTERYCARD_MSGWIN_TABLE *tbl;
  int index = 0;

  // おすそわけが出来ない場合は「おすそわけ」メニューを表示しない
  ld[index++] = MysteryCard_Menu1Data[0];
  if(wk->card[wk->disp_card]->re_deal_count)
    ld[index++] = MysteryCard_Menu1Data[1];
  // 配達人から受け取っていない場合は「すてる」メニューを表示しない
  if(FUSHIGIDATA_GetCardLinkDeli(wk->fdata, wk->disp_card+1) == FALSE)
    ld[index++] = MysteryCard_Menu1Data[2];
  ld[index++] = MysteryCard_Menu1Data[3];
  // ウィンドウのサイズにあわせてメニューを作り直し
  tbl = wk->tbl;
  GF_BGL_BmpWinOff(win);  GF_BGL_BmpWinDel(win);
  GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME2_M,
		   tbl->sx, tbl->sy + (4 - index) * 2, tbl->width, tbl->height - (4 - index) * 2,
		   FONT_PALNO_NORMAL, wk->nowbase);
  // メニュー登録
  CreateWindowMenuData(wk, ld, index, win);

  return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	メニュー２を作成
 *		カードをすてますか？　はい／いいえ
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardMenu2Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  CreateWindowMenuData(wk, MysteryCard_Menu2Data, 2, win);
  return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	メニュー３を作成
 *		おすそわけをしますか？　はい／いいえ
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardMenu3Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  CreateWindowMenuData(wk, MysteryCard_Menu3Data, 2, win);
  return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	メニュー４を作成
 *		ＤＳワイヤレスつうしんを\nかいし　します　はい／いいえ
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardMenu4Win(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  DrawStringWindow(&wk->msgwin, mystery_01_003);
  CreateWindowMenuData(wk, MysteryCard_Menu4Data, 2, win);
  return TRUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	現在のエントリを表示
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static BOOL MysteryCardDrawEntry(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, GF_PRINTCOLOR col)
{
  WORDSET_RegisterNumber(wk->word, 0, 0/*wk->entry*/, 1, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
  return TRUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	フェード処理
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void RequestFade(MYSTERYCARD_WORK *wk, int type, int next_seq, int *seq)
{
  WIPE_SYS_Start(WIPE_PATTERN_WMS, type, type, WIPE_FADE_BLACK,WIPE_DEF_DIV,WIPE_DEF_SYNC,HEAPID_MYSTERYCARD);
  if(seq)
    *seq = MYSTERYCARD_SEQ_WAIT_FADE;
  wk->next_seq = next_seq;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	必要なスクリーンの作成
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void MysteryCardCreateMsgWindow(MYSTERYCARD_WORK *wk, int font, int side)
{
  int i, chbase;
  STRBUF * msg;
  GF_PRINTCOLOR col;
  MYSTERYCARD_MSGWIN_TABLE *tbl = MsgWin_Table;
  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, wk->heapid);
  wk->word = WORDSET_Create(wk->heapid);

  wk->disp_side = side;

  CreateCardGraphics(wk, side);

  /* まずは別サイドのウィンドウを抹消 */
  for(i = 0; i < sizeof(MsgWin_Table) / sizeof(MYSTERYCARD_MSGWIN_TABLE); i++){
    if(tbl[i].side != side && tbl[i].side != MYSTERYCARD_MENU){
      if(wk->win[i].ini){
	GF_BGL_BmpWinOff(&wk->win[i]);
	GF_BGL_BmpWinDel(&wk->win[i]);
      }
    }
  }
  chbase = MYSTERYCARD_CHBASE;
  /* 新たにウィンドウを作り直す */
  for(i = 0; i < sizeof(MsgWin_Table) / sizeof(MYSTERYCARD_MSGWIN_TABLE); i++){
    if(tbl[i].side == side){
      if(wk->win[i].ini == NULL){
	// ウィンドウを作って…
	wk->chbase[i] = chbase;
	GF_BGL_BmpWinAdd(wk->bgl, &wk->win[i], GF_BGL_FRAME0_M,
			 tbl[i].sx, tbl[i].sy, tbl[i].width, tbl[i].height,
			 FONT_PALNO_NORMAL, chbase);
      }
      // ウィンドウをクリアして…
      GF_BGL_BmpWinDataFill(&wk->win[i], FontHeaderGet(tbl[i].font, tbl[i].background));
      col = tbl[i].color;
      // 外部ファンクションを呼び出して…
      if(tbl[i].func(wk, &wk->win[i], col) == TRUE){
	// メッセージがあれば表示する
	if(tbl[i].msgid){
	  msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, tbl[i].msgid, wk->heapid);
	  GF_STR_PrintColor(&wk->win[i], tbl[i].font, msg, tbl[i].ox, tbl[i].oy, MSG_NO_PUT, col, NULL);
	  STRBUF_Delete(msg);
	}
      }
      /* 最後にウィンドウ表示 */
      GF_BGL_BmpWinOn(&wk->win[i]);
      chbase += tbl[i].width * tbl[i].height;
    }
  }
  MSGMAN_Delete(wk->msgman);
  WORDSET_Delete(wk->word);

  /* ポケモンのアイコンを表示 */
  if(side == MYSTERYCARD_FRONT)
    MysteryCard_DisplayPokemonIcon(wk);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	新しいメニューウィンドウを開く
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardCreateWindow(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN	*win, int index, int base)
{
  STRBUF * msg;
  GF_PRINTCOLOR col;
  MYSTERYCARD_MSGWIN_TABLE *tbl = MsgWin_Table + index;
#if 0
  OS_Printf("%d, %d, %d, %d, %d, %d\n", tbl->sx, tbl->sy, tbl->width, tbl->height, index,base);
#endif
  if(win->ini == NULL){
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME2_M,
		     tbl->sx, tbl->sy, tbl->width, tbl->height,
		     FONT_PALNO_NORMAL, base);
  }
  GF_BGL_BmpWinDataFill(win, tbl->background);
  if(tbl->msgid){
    wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYCARD);
    wk->word = WORDSET_Create(HEAPID_MYSTERYCARD);
  }
  // 外部ファンクションを呼び出す
  wk->nowbase = base;
  wk->tbl = tbl;
  tbl->func(wk, win, MYSTERYCARD_BLACK);
  // メッセージがあれば表示して…
  if(tbl->msgid){
    msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, tbl->msgid, HEAPID_MYSTERYCARD);
    GF_STR_PrintColor(win, tbl->font, msg, 0, 0, MSG_NO_PUT, tbl->color, NULL);
    STRBUF_Delete(msg);
    MSGMAN_Delete(wk->msgman);
    WORDSET_Delete(wk->word);
  }
  if(win == &wk->msgwin){	// ごめんなさいコード
    BmpTalkWinWrite(win, WINDOW_TRANS_ON, MYSTERYCARD_TFRAMECHR, TWAKU_PALETTE_NUMBER);
  } else {
    BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYCARD_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  }

  return base + tbl->width * tbl->height;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	次のカードを検索する
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardNextCard(MYSTERYCARD_WORK *wk, int card, int add)
{
  int orgcard = card;

  while(1){
    card += add;
    if(card == GIFT_CARD_MAX)	card = 0;
    if(card == -1)		card = GIFT_CARD_MAX - 1;
    if(orgcard == card)
      break;
    if(FUSHIGIDATA_IsExistsCard(wk->fdata, card))
      break;
  }
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("次のカードスロットは %d 番です\n", card);
#endif
  return card;
}

static void CMC_ArcUtil_ScrnSet(MYSTERYCARD_WORK *wk, u32 dataIdx, u32 frm, u32 transSize)
{
  // ArcUtil_ScrnSetだと非垂直期間中にVRAM転送されてしまうので、修正
  NNSG2dScreenData* scrnData;
  void *arcData = ArcUtil_Load(ARC_MYSTERY_GRA, dataIdx, 1, wk->heapid, ALLOC_BOTTOM);
  NNS_G2dGetUnpackedScreenData( arcData, &scrnData );
  GF_BGL_ScreenBufSet(wk->bgl, frm, scrnData->rawData, transSize);
  sys_FreeMemoryEz( arcData );
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	指定番号のスクリーンを転送
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateCardGraphics(MYSTERYCARD_WORK *wk, int side)
{
  // メイン画面ＢＧパレット転送
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_card_nclr, PALTYPE_MAIN_BG, 0, 16*16, wk->heapid);
  // メイン画面BG1キャラ転送
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_card_lz_cngr, wk->bgl, GF_BGL_FRAME1_M, 0, 24*16*0x20, 1, wk->heapid);

  switch(side){
  case MYSTERYCARD_FRONT:
    // メイン画面BG1スクリーン転送
    ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_card01_lz_cscr, wk->bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, wk->heapid);
    break;
  case MYSTERYCARD_BACK:
    // メイン画面BG1スクリーン転送
    ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_card02_lz_cscr, wk->bgl, GF_BGL_FRAME1_M, 0, 32*24*2, 1, wk->heapid);
    break;
  }

  // メイン画面ＢＧパレット転送
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_nclr, PALTYPE_MAIN_BG, 16*2*LATTICEBG_PALNO, 16*2, wk->heapid);
  // メイン画面BG2キャラ転送
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_ccgr, wk->bgl,
		    GF_BGL_FRAME3_M, LATTICEBG_CHARBASE * 1/*0x20*/, 1*16*0x20, 1, wk->heapid);
  // メイン画面スクリーン１
  CMC_ArcUtil_ScrnSet(wk, NARC_mystery_fusigi_bg_00_lz_cscr, GF_BGL_FRAME3_M, 32*24*2);
  GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME3_M, 0, 0, 32, 24, LATTICEBG_PALNO);
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME3_M);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	メニュー選択＆実行
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void DoMenuMain(PROC *proc, int *seq, int (*cfunc)(PROC *))
{
  u32 ret;
  int ret_seq;
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);
  static int (*func)(PROC *);
  
  ret = BmpListMain(wk->lw);
  switch(ret){
  case BMPLIST_NULL:	/* 何も選択されていない */
    break;
  case BMPLIST_CANCEL:	/* キャンセルされた */
    Snd_SePlay(SEQ_SE_DP_SELECT);
    if(cfunc){
      ret_seq = cfunc(proc);
      if(ret_seq != -1)
	*seq = ret_seq;
    }
    break;
  default:		/* 何かが決定された */
    Snd_SePlay(SEQ_SE_DP_SELECT);
    if(ret){
      if(ret < MYSTERYCARD_SEQ_MAX){
	*seq = ret;
      } else {
	func = (static int (*)(PROC *))ret;
	ret_seq = func(proc);
	if(ret_seq != -1)
	  *seq = ret_seq;
      }
    }
    break;
  }
}


//------------------------------------------------------------------
/**
 * @brief	ポケモンのアイコンを表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryCard_DisplayPokemonIcon(MYSTERYCARD_WORK *wk)
{
  int px, no, pokeno;
  u8 *buf;
  NNSG2dCharacterData *chara;

  if(wk->pokeicon[0] == NULL && wk->pokeicon[1] == NULL && wk->pokeicon[2] == NULL){
  
    if(MysteryLib_isInitClact() == TRUE)
      RemoveCellActor(wk);
    MysteryLib_InitCPManager();
    MysteryLib_InitClactSystem();
    MysteryLib_InitClact(ARC_MYSTERY_GRA,
			 NARC_mystery_gba_box_oam_lz_cngr,
			 NARC_mystery_gba_box_oam_nclr,
			 NARC_mystery_gba_box_oam_lz_ccer,
			 NARC_mystery_gba_box_oam_lz_canr,
			 GF_BGL_MAIN_DISP);
    // ポケモンアイコン用パレットを一気に読み込んでVRAM転送する
    ArcUtil_PalSet(ARC_POKEICON, PokeIconPalArcIndexGet(), PALTYPE_MAIN_OBJ, POKEICON_PAL_OFFSET*0x20,
		   0, wk->heapid);
  }

  pokeno = 1;
  px = 178;
  for(no = 0; no < MYSTERYGIFT_POKEICON; no++, px += 25){
    pokeno = wk->card[wk->disp_card]->pokemon_icon[no];
    if(pokeno == 0){
      if(wk->pokeicon[no])
	CLACT_SetDrawFlag(wk->pokeicon[no], 0);
      continue;
    }

    wk->pokeicon[no] = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->pokeicon[no], px, 16, 10+no);
    
    buf = ArcUtil_CharDataGet(ARC_POKEICON, 
			      PokeIconCgxArcIndexGetByMonsNumber(pokeno, 0, 0), 0, &chara, wk->heapid);
    DC_FlushRange(chara->pRawData, POKEICON_TRANS_SIZE);

    // キャラクター転送
    GX_LoadOBJ(chara->pRawData, (POKEICON_VRAM_OFFSET+no*POKEICON_TRANS_CHARA)*0x20, POKEICON_TRANS_SIZE);
    // パレット設定
    CLACT_PaletteNoChg(wk->pokeicon[no],  PokeIconPalNumGet(pokeno, 0, 0)+POKEICON_PAL_OFFSET );
    sys_FreeMemoryEz(buf);
  }
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	ふしぎなカード：初期化
 * @param	proc	プロセスへのポインタ
 * @param	seq		シーケンス用ワークへのポインタ
 * @return	PROC_RES_CONTINUE	動作継続中
 * @return	PROC_RES_FINISH		動作終了
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT MysteryCardProc_Init(PROC * proc, int * seq)
{
  MYSTERYCARD_WORK *wk;

  /* ワークエリアはTITLE_STARTMENUの上に作成する(抹消の順番は問題ないはず) */
  sys_CreateHeap( HEAPID_BASE_APP, HEAPID_MYSTERYCARD, MYSTERYCARD_HEADSIZE);
  wk = PROC_AllocWork(proc, sizeof(MYSTERYCARD_WORK), HEAPID_MYSTERYCARD);
  /* 初期化不良が怖いのでワークはゼロクリア */
  memset(wk, 0, sizeof(MYSTERYCARD_WORK));
  
  /* 各種変数の初期化 */
  wk->bgl = GF_BGL_BglIniAlloc(HEAPID_MYSTERYCARD);
  wk->heapid = HEAPID_MYSTERYCARD;

  /* 画面の初期設定 */
  WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
  WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

  /* 変数初期化 */
  wk->disp_card = GIFT_CARD_MAX - 1;
  wk->write_index = 1;
  // ライブラリ初期化
  MysteryLib_Init(HEAPID_MYSTERYCARD);

  sys_CreateHeap( HEAPID_BASE_SYSTEM, HEAPID_COMMICON, 0x300 );
  return PROC_RES_FINISH;
}


#define CARDHEIGHT		168
#define SPEED			0.025
//------------------------------------------------------------------
/**
 * @brief	カード回転時のVBLANK処理
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryCard_VBlankTcb(TCB_PTR tcb, void* p_work)
{
  CARDTURN *ct = (CARDTURN *)p_work;
  LASTER_DmaStop();
  LASTER_DmaSet(LASTER_GetReadBuff(ct->laster_ptr), (void *)REG_BG0HOFS_ADDR, sizeof(u32)*2, LASTER_DMA_TYPE32);
}

//------------------------------------------------------------------
/**
 * @brief	カード回転初期化
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryCard_InitTurn(MYSTERYCARD_WORK *wk, BOOL mode, fx32 default_speed, fx32 accel_speed)
{
  CARDTURN *ct = &wk->cturn;

  ct->mode = mode;
  ct->speed = default_speed;
  ct->accel = accel_speed;

  if(ct->laster_ptr == NULL)
    ct->laster_ptr = LASTER_Init(HEAPID_MYSTERYCARD, ct->sbuff[0], ct->sbuff[1]);
  if(ct->tcb_ptr == NULL)
    ct->tcb_ptr = VIntrTCB_Add(MysteryCard_VBlankTcb, ct, 1024);
  ct->do_run = TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	カード回転処理の最終後始末
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryCard_FinishTurn(MYSTERYCARD_WORK *wk)
{
  CARDTURN *ct = &wk->cturn;
  if(ct->laster_ptr)
    LASTER_Delete(ct->laster_ptr);
  if(ct->tcb_ptr)
    TCB_Delete(ct->tcb_ptr);
  ct->laster_ptr = NULL;
  ct->tcb_ptr = NULL;
  LASTER_DmaStop();
}

//------------------------------------------------------------------
/**
 * @brief	カード回転処理
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define CHANGE(y, v)		(0 - (y) + (v))
static BOOL MysteryCard_TurnMainProc(MYSTERYCARD_WORK *wk)
{
  int i, reg;
  u16 *buf;
  CARDTURN *ct = &wk->cturn;
  fx32 line = (CARDHEIGHT/2) * FX32_ONE;

  // 前回ですでに処理は終了している
  if(ct->do_run == FALSE)	return TRUE;

  // 先に終了判定を行って、最後の１フレームを作成する
  if(ct->mode == TRUE){
    // 閉じる際の終了判定
    ct->speed += ct->accel;
    ct->accel += ct->accel;
    if(ct->speed / FX32_ONE > 1000){
      ct->do_run = FALSE;
      line = CARDHEIGHT;
      ct->speed = 0;
      ct->accel = 0;
    }
  } else {
    // 開く際の終了判定
    ct->speed -= ct->accel;
    ct->accel /= 2;
    if(ct->accel < FX32_ONE/4/*4*/){
      ct->do_run = FALSE;
      ct->speed = 1*FX32_ONE;
      ct->accel = 0;
    }
  }
  // 各ラインのスクロール値計算
  buf = LASTER_GetWriteBuff(ct->laster_ptr);
  for(i = CARDHEIGHT/2; i < CARDHEIGHT; i++){
    reg = line / FX32_ONE;
    if(reg < 0)			reg = 0;
    if(reg > CARDHEIGHT)	reg = CARDHEIGHT;

    buf[i * 4 + 1] =		buf[i * 4 + 3] =		CHANGE(i, reg);
    buf[(CARDHEIGHT - i) * 4 + 1] =	buf[(CARDHEIGHT - i) * 4 + 3] =	CHANGE(CARDHEIGHT - i, CARDHEIGHT - reg);
    
    line += ct->speed;
  }
  DC_FlushRange(buf, sizeof(u16) * HW_LCD_HEIGHT*4);
  // 準備が終わったバッファへ切り替え
  LASTER_VBlank(ct->laster_ptr);

  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	セーブシーケンス
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SaveSequence(void *p)
{
  int ret;
  MYSTERYCARD_WORK *wk = (MYSTERYCARD_WORK *)p;
  ret = MysteryLib_SaveDSCard();
  if(ret == SAVE_RESULT_OK || ret == SAVE_RESULT_NG){
    Snd_SePlay(SEQ_SE_DP_SAVE);
    //    OS_TPrintf("分割セーブが終了しました\n");
    wk->func_hook = NULL;
  }
}

//------------------------------------------------------------------
/**
 * @brief	セーブシーケンス開始
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void MysteryCard_StartSaveSeq(MYSTERYCARD_WORK *wk)
{
  /* 配布した回数をカウントアップ(これ、使うのかな…？) */
  if(wk->card[wk->disp_card]->re_dealed_count != 255)
    wk->card[wk->disp_card]->re_dealed_count++;
  /* 配布回数を－１する(ただし255ならば無制限配布) */
  if(wk->card[wk->disp_card]->re_deal_count != 255)
    wk->card[wk->disp_card]->re_deal_count--;
  // セーブシーケンスを登録
  MysteryLib_InitSaveDSCard(wk->sv);
  wk->func_hook = SaveSequence;
#if 0
  /* データセーブ */
  SaveData_Save(wk->sv);
#endif
}


//------------------------------------------------------------------
/**
 * @brief	カーソル移動処理
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SelectCursor(MYSTERYCARD_WORK *wk, int connect, int *seq)
{
  int mark;
  int select = wk->select_icon;

  // 左右移動
  if(sys.trg & PAD_KEY_RIGHT && wk->select_icon != 1)
    wk->select_icon = 1;
  if(sys.trg & PAD_KEY_LEFT && wk->select_icon != 0)
    wk->select_icon = 0;
  // カーソル反映
  if(select != wk->select_icon){
    CLACT_AnmChg(wk->ibase[0], wk->select_icon == 0 ? 1 : 0);
    CLACT_AnmChg(wk->ibase[1], wk->select_icon == 0 ? 0 : 1);
  }

  // 処理の選択
  mark = 0;
  if(sys.trg & PAD_BUTTON_CANCEL)
    mark = 2;
  else if((sys.trg & PAD_BUTTON_DECIDE) && connect && wk->select_icon == 0)
    mark = 1;
  else if((sys.trg & PAD_BUTTON_DECIDE) && wk->select_icon == 1)
    mark = 2;
  else if((sys.trg & PAD_BUTTON_DECIDE) && connect == 0)
    mark = 3;

  // 処理実行
  if(mark == 1){
    Snd_SePlay(SEQ_SE_DP_SELECT);
    // データの送信開始
    CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE);
    wk->sync_wait = 1;
    *seq = MYSTERYCARD_SEQ_SEND_WAITSYNC;
    MysteryCardCreateWindow(wk, &wk->msgwin, MYSTERYCARD_INDEX_LASTWIN, MYSTERYCARD_MENU_BASE);
    wk->time_icon = TimeWaitIconAdd(&wk->msgwin, MYSTERYCARD_TFRAMECHR);
  }
  if(mark == 2){
    Snd_SePlay(SEQ_SE_DP_SELECT);
    // 通信を終了させる
    // ※通信が終了したら次のシーケンスへ移行
    CommMysteryCardExit(wk,  seq, MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END1);
  }
  if(mark == 3){
    Snd_SePlay(SEQ_SE_DP_SELECT);
  }
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	ふしぎなカード：メイン
 * @param	proc	プロセスへのポインタ
 * @param	seq		シーケンス用ワークへのポインタ
 * @return	PROC_RES_CONTINUE	動作継続中
 * @return	PROC_RES_FINISH		動作終了
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT MysteryCardProc_Main(PROC * proc, int * seq)
{
  int new_card, v1, v2, connect_ds;
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);

  switch(*seq){
  case MYSTERYCARD_READ_SAVEDATA:
    wk->sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
    wk->fdata = SaveData_GetFushigiData(wk->sv);
    wk->cfg = SaveData_GetConfig(wk->sv);
    wk->win_type = CONFIG_GetWindowType(wk->cfg);

    wk->card[0] = FUSHIGIDATA_GetCardData(wk->fdata, 0);
    wk->card[1] = FUSHIGIDATA_GetCardData(wk->fdata, 1);
    wk->card[2] = FUSHIGIDATA_GetCardData(wk->fdata, 2);
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_Printf("0:%08X  1:%08X  2:%08X\n", wk->card[0], wk->card[1], wk->card[2]);
#endif
    wk->disp_card = MysteryCardNextCard(wk, wk->disp_card, 1);
    *seq = MYSTERYCARD_SEQ_INIT;
    break;
    
  case MYSTERYCARD_SEQ_INIT:
    CommMysteryFunc_VramBankSet();
    CommMysteryFunc_BgInit(wk->bgl);
    *seq = MYSTERYCARD_SEQ_CREATE_SCREEN;
    break;

  case MYSTERYCARD_SEQ_CREATE_SCREEN:
    /* 画面作成 */
    MSG_PrintInit();
    /* スクリーン転送 */
    CreateCardGraphics(wk, MYSTERYCARD_FRONT);
    /* メッセージのフォントカラーを設定 */
    SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_NORMAL * 32, HEAPID_MYSTERYCARD);
    /*ウィンドウ枠キャラ、パレットをセット */
    MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, MYSTERYCARD_FRAMECHR1, WAKU_PALETTE_NUMBER1, 0, HEAPID_MYSTERYCARD);
    MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, MYSTERYCARD_FRAMECHR2, WAKU_PALETTE_NUMBER2, 1, HEAPID_MYSTERYCARD);
    TalkWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, MYSTERYCARD_TFRAMECHR, TWAKU_PALETTE_NUMBER, wk->win_type, HEAPID_MYSTERYCARD);

    MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);
    /* フェードイン */
    RequestFade(wk, WIPE_TYPE_FADEIN, MYSTERYCARD_SEQ_MAIN, seq);

    break;

  case MYSTERYCARD_SEQ_MAIN:
    new_card = wk->disp_card;
    /* カード入れ替え */
    if(sys.trg & PAD_KEY_UP){
      new_card = MysteryCardNextCard(wk, wk->disp_card, -1);
    } else if(sys.trg & PAD_KEY_DOWN){
      new_card = MysteryCardNextCard(wk, wk->disp_card,  1);
    }
    /* 戻るボタンチェック */
    else if(sys.trg & PAD_BUTTON_CANCEL){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      RequestFade(wk, WIPE_TYPE_FADEOUT, MYSTERYCARD_SEQ_RETURN, seq);
    }
    /* Ａボタンでメニューが開く */
    else if(sys.trg & PAD_BUTTON_DECIDE){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      *seq = MYSTERYCARD_SEQ_CREATE_MENU;
    }

    /* 変更があったらカード表示 */
    if(wk->disp_card != new_card){
      Snd_SePlay(SEQ_SE_DP_CARD2);
#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("カード変更だよ! %d -> %d\n", wk->disp_card, new_card);
#endif
      wk->disp_card = new_card;
      MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);
    }

    break;


  // ↓この間はメニューの制御 ----------------------------

    
  case MYSTERYCARD_SEQ_CREATE_MENU:
    /* メニューを開く */
    wk->menu_index = MysteryCardCreateWindow(wk, &wk->msgwin, MYSTERYCARD_INDEX_MENU, MYSTERYCARD_MENU_BASE);
    MysteryCardCreateWindow(wk, &wk->menuwin, MYSTERYCARD_INDEX_MENU+1, wk->menu_index);
    *seq = MYSTERYCARD_SEQ_MENU;
    break;

  case MYSTERYCARD_SEQ_MENU:
    /* メニュー画面 */
    DoMenuMain(proc, seq, NULL);
    if(sys.trg & PAD_BUTTON_CANCEL){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      *seq = MYSTERYCARD_SEQ_END_MENU;
    }
    break;

  case MYSTERYCARD_SEQ_MENU_TO_VIEWMODE:
    /* カードの説明文を見るモードへ移行 */
    Snd_SePlay(SEQ_SE_DP_CARD2);
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
    CMC_BmpTalkWinClear(&wk->msgwin,  WINDOW_TRANS_ON);
    CMC_BmpMenuWinClear(&wk->menuwin, WINDOW_TRANS_ON);
    // カードを閉じる
    MysteryCard_InitTurn(wk, TRUE,     1*FX32_ONE, SPEED*FX32_ONE);
    *seq = MYSTERYCARD_SEQ_MENU_TO_VIEWMODE2;
    break;
    
  case MYSTERYCARD_SEQ_MENU_TO_VIEWMODE2:
    if(MysteryCard_TurnMainProc(wk)){
      // 裏面を描画
      MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_BACK);
      // カードを開く
      MysteryCard_InitTurn(wk, FALSE, 1800*FX32_ONE,   900*FX32_ONE);
      *seq = MYSTERYCARD_SEQ_MENU_VIEWMODE;
    }
    break;

  case MYSTERYCARD_SEQ_MENU_VIEWMODE:
    MysteryCard_TurnMainProc(wk);
    /* カードの説明文を見るモード */
    if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL)){
      Snd_SePlay(SEQ_SE_DP_CARD2);
      //      Snd_SePlay(SEQ_SE_DP_SELECT);
      // カードを閉じる
      MysteryCard_InitTurn(wk, TRUE,     1*FX32_ONE, SPEED*FX32_ONE);
      *seq = MYSTERYCARD_SEQ_MENU_VIEWMODE2;
    }
    break;

  case MYSTERYCARD_SEQ_MENU_VIEWMODE2:
    if(MysteryCard_TurnMainProc(wk)){
      // 表面を描画
      MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);
      // カードを開く
      MysteryCard_InitTurn(wk, FALSE, 1800*FX32_ONE,   900*FX32_ONE);
      GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
      *seq = MYSTERYCARD_SEQ_MENU_VIEWMODE3;
    }
    break;
  case MYSTERYCARD_SEQ_MENU_VIEWMODE3:
    if(MysteryCard_TurnMainProc(wk)){
      // メニューを描画
      BmpTalkWinWrite(&wk->msgwin,  WINDOW_TRANS_ON, MYSTERYCARD_TFRAMECHR, TWAKU_PALETTE_NUMBER);
      BmpMenuWinWrite(&wk->menuwin, WINDOW_TRANS_ON, MYSTERYCARD_FRAMECHR2, WAKU_PALETTE_NUMBER2);
      GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
      MysteryCard_FinishTurn(wk);
      *seq = MYSTERYCARD_SEQ_MENU;
    }
    break;

  case MYSTERYCARD_SEQ_END_MENU:
    /* メニューを消す */
    MysteryCardRemoveMainMenu(wk);
    /* メッセージウィンドウを消す */
    CMC_BmpTalkWinClear(&wk->msgwin, WINDOW_TRANS_ON);
    GF_BGL_BmpWinOff(&wk->msgwin);  GF_BGL_BmpWinDel(&wk->msgwin);
    *seq = MYSTERYCARD_SEQ_MAIN;
    break;

  case MYSTERYCARD_SEQ_REMOVE_MENU:
    /* カードを消す選択メニュー */
    DoMenuMain(proc, seq, MysteryCardRetMainMenu);
    break;


  case MYSTERYCARD_SEQ_SENDFIGT_YESNO:
    /* おすそわけをしますか？ はい／いいえ */
    /* カードを消す選択メニュー */
    DoMenuMain(proc, seq, MysteryCardRetMainMenu);
    break;

  case MYSTERYCARD_SEQ_COMM_YESNO:
    /* 「ＤＳワイヤレスつうしんを　かいし　します」 */
    MysteryCardMenu4Win(wk, &wk->menuwin, MYSTERYCARD_BLACK);
    *seq = MYSTERYCARD_SEQ_SENDFIGT_YESNO;
    break;


    
  case MYSTERYCARD_SEQ_MENU_TO_SENDGIFT:
    /* おすそわけ画面へいくためのフェードアウト */
    RequestFade(wk, WIPE_TYPE_FADEOUT, MYSTERYCARD_SEQ_MENU_TO_SENDGIFT2, seq);
    break;

  case MYSTERYCARD_SEQ_MENU_TO_SENDGIFT2:
    /* おすそわけ画面へ行く準備 */
    /* メニューを消す */
    MysteryCardRemoveMainMenu(wk);
    /* メッセージウィンドウを消す */
    CMC_BmpTalkWinClear(&wk->msgwin, WINDOW_TRANS_ON);
    GF_BGL_BmpWinOff(&wk->msgwin);  GF_BGL_BmpWinDel(&wk->msgwin);
    MysteryCardCreateMsgWindow(wk, FONT_SYSTEM, MYSTERYCARD_SEND);
    /* おすそわけ画面の作成 */
    MysteryCardCreateOsusowake(wk->bgl);
    /* オブジェクト周りの初期化 */
    InitCellActor(wk);
    SetBaseIcon(wk);
    *seq = MYSTERYCARD_SEQ_MENU_TO_SENDGIFT3;
    break;

  case MYSTERYCARD_SEQ_MENU_TO_SENDGIFT3:
    // 親として通信開始
    CommMysteryCard_CreateBeacon(wk);
    WirelessIconEasy();		// 通信アイコン表示
    RequestFade(wk, WIPE_TYPE_FADEIN, MYSTERYCARD_SEQ_ENTRY_SENDGIFT, seq);
    break;

  case MYSTERYCARD_SEQ_ENTRY_SENDGIFT:
    /* おすそわけのエントリ中画面 */
    connect_ds = 0;
    if(CommIsConnect(COMM_PARENT_ID)){
      CommMPSetBeaconTempData(&wk->gwk.gift_data.beacon);
      // つながっている子機を表示
      connect_ds = MysteryCardDispConnectChildStatus(wk, &wk->win[MYSTERYCARD_ENTRY_LIST]);
      if(connect_ds == 0 && wk->prev_connect){
	// 誰も居なくなって、先ほどまで繋がっていたらウィンドウをクリア
	GF_BGL_BmpWinDataFill(&wk->win[MYSTERYCARD_ENTRY_LIST], 0);
	GF_BGL_BmpWinOn(&wk->win[MYSTERYCARD_ENTRY_LIST]);
	wk->prev_connect = 0;
      }
      MysteryCardDispConnectChildCount(wk, &wk->win[MYSTERYCARD_ENTRY_COUNT], connect_ds);
      wk->prev_connect = connect_ds;
    }
    /* カーソル移動で選択 */
    SelectCursor(wk, connect_ds, seq);
    break;

  case MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END1:
    // フェードアウト開始
    RequestFade(wk, WIPE_TYPE_FADEOUT, MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END2, seq);
    break;

  case MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END2:

    RemoveCellActor(wk);
    CMC_BmpTalkWinClear(&wk->msgwin,  WINDOW_TRANS_ON);
    CMC_BmpMenuWinClear(&wk->menuwin, WINDOW_TRANS_ON);
    
    // 画面を書き換えてフェードイン
    MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);
    /* メッセージのフォントカラーを設定 */
    SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_NORMAL * 32, HEAPID_MYSTERYCARD);
    RequestFade(wk, WIPE_TYPE_FADEIN, MYSTERYCARD_SEQ_CREATE_MENU, seq);
    break;

    
  case MYSTERYCARD_SEQ_WAIT_ENDCOMM:
    if(CommStateIsInitialize() == FALSE)
      *seq = wk->next_seq;
    break;
    
  case MYSTERYCARD_SEQ_SEND_WAITSYNC:
    if(--wk->sync_wait == 0){
      /* おすそわけ中 */
      MysteryLib_CreateCryptoData(&wk->gwk.gift_data, &wk->comm_data, wk->heapid);
      CommMysterySendGiftDataParent((const void *)&wk->comm_data, sizeof(GIFT_DATA));
      /* 非同期セーブ開始 */
      MysteryCard_StartSaveSeq(wk);
      *seq = MYSTERYCARD_SEQ_SEND_SAVEDATA;
    }
    break;
    
  case MYSTERYCARD_SEQ_SEND_SAVEDATA:
    // 最後の１セクタ以外がセーブできたら子機と同期を取る
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_LAST){
      CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE2);
      *seq = MYSTERYCARD_SEQ_LAST_SAVE_WAIT;
    }
    break;

  case MYSTERYCARD_SEQ_LAST_SAVE_WAIT:
    // 繋がっている子機全てからの返事を待つ
    if(MysteryCardGetConnectCount(wk) == 0 || CommIsTimingSync(MYSTERYGIFT_SYNC_CODE2) == TRUE){
      MysteryLib_DoLastSave();
      /* おしまいメッセージを出して終了 */
      MysteryCardCreateWindow(wk, &wk->msgwin, MYSTERYCARD_INDEX_LASTWIN+1, MYSTERYCARD_MENU_BASE);
      TimeWaitIconDel(wk->time_icon);
      CommMysteryCardExit(wk, seq, MYSTERYCARD_SEQ_SEND_FINISH);
    }
    break;
    
  case MYSTERYCARD_SEQ_SEND_FINISH:
    // おすそわけ終了、ボタンをまってメニュー画面へ
    if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL))
      *seq = MYSTERYCARD_SEQ_ENTRY_SENDGIFT_END1;
    break;


    
    // ↑この間はメニューの制御 ----------------------------

  case MYSTERYCARD_SEQ_TO_RETURN:
    // 処理を抜けて前のメニューに帰る時の入り口
    RequestFade(wk, WIPE_TYPE_FADEOUT, MYSTERYCARD_SEQ_RETURN, seq);
    break;

  case MYSTERYCARD_SEQ_WAIT_FADE:
    /* フェード終了まで待つ */
    if(WIPE_SYS_EndCheck()){
      *seq = wk->next_seq;
    }
    break;

    case MYSTERYCARD_SEQ_RETURN:	/* 前のメニュー画面へ戻る */
      RemoveCellActor(wk);
      MysteryCard_FinishTurn(wk);
      return PROC_RES_FINISH;
      break;
    
    case MYSTERYCARD_SEQ_LOOP:
      /* エラー時の無限ループ */
      break;
  }

  // アイコンを表示するために必要な駆動処理
  if(wk->clactSet!=NULL)
    CLACT_Draw( wk->clactSet );

  MysteryLib_DoClact();

  // 常時ではないけれど実行した関数はここで実行
  if(wk->func_hook)
    wk->func_hook(wk);
  
  return PROC_RES_CONTINUE;
}


// ------------------------------ ここから ----------------------------
// 通信関連のプログラムを後半にまとめます

//--------------------------------------------------------------------------------------------
/**
 * @brief	ビーコンデータを作成して親として通信を開始
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommMysteryCard_CreateBeacon(MYSTERYCARD_WORK *wk)
{
  /* セーブデータからビーコン情報を作成 */
  GIFT_CARD *gd = wk->card[wk->disp_card];
  memcpy(&wk->gwk.gift_data.data, gd, sizeof(GIFT_DATA));
  memcpy(&wk->gwk.gift_data.beacon, &gd->beacon, sizeof(GIFT_BEACON));
  // 孫配布される側は、さらに孫配布する事はできません(仕様)
  wk->gwk.gift_data.data.card.re_deal_count = 0;
  wk->gwk.gift_data.beacon.re_deal_flag = FALSE;
  // 孫配布である「印」を追加
  wk->gwk.gift_data.beacon.groundchild_flag = TRUE;

  CommMysteryStateEnterGiftParent(&wk->gwk, wk->sv, COMM_MODE_MYSTERY);
  
  return NULL;
}


// ４つの配列の中から一番小さな要素を返す
// ※ワークを破壊的に扱います※
static int getmin(int *p)
{
  int *v = p;
  int val = *p;
  int index = 0;
  if(p[1] < val)	val = p[1], index = 1, v = &p[1];
  if(p[2] < val)	val = p[2], index = 2, v = &p[2];
  if(p[3] < val)	val = p[3], index = 3, v = &p[3];
  *v = 32767*32767;
  return index + 1;
}


//------------------------------------------------------------------
/**
 * @brief	繋がっている人数を返す
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int MysteryCardGetConnectCount(MYSTERYCARD_WORK *wk)
{
  int i, max;
  MYSTATUS *my;

  max = 0;
  for(i = 1; i < MYSTERYCARD_OSUSOWAKE_MAX + 1; i++){
    if(CommInfoGetMyStatus(i))
      max++;
  }
  return max;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	繋がっている子機情報を表示
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int MysteryCardDispConnectChildStatus(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win)
{
  int i, max, y, redraw;
  u32 id;
  MYSTATUS *my;
  STRBUF *msg;
  WORDSET *word;
  MSGDATA_MANAGER *msgman;
  int copy[MYSTERYCARD_OSUSOWAKE_MAX];
  int order[MYSTERYCARD_OSUSOWAKE_MAX];

  // 前回と繋がっている人が違うか調べる
  max = 0;
  redraw = 0;
  for(i = 1; i < MYSTERYCARD_OSUSOWAKE_MAX + 1; i++){
    my = CommInfoGetMyStatus(i);
    if(my == NULL){
      if(wk->my[i])	redraw++;
      wk->my[i] = NULL;
      wk->worder[i] = 32767*32767;
    } else if(wk->my[i] != my){
      redraw++;
      max++;
      wk->my[i] = my;
      wk->worder[i] = wk->write_index++;
    } else {
      max++;
    }
  }

  // 再表示の必要がなければこの先の処理をしない
  if(redraw == 0)
    return max;

  // 表示順番を確定する
  copy[0] = wk->worder[1], copy[1] = wk->worder[2], copy[2] = wk->worder[3], copy[3] = wk->worder[4];
  order[0] = getmin(copy);
  order[1] = getmin(copy);
  order[2] = getmin(copy);
  order[3] = getmin(copy);

  // 再描画が必要ならば描きなおす
  word = WORDSET_Create(HEAPID_MYSTERYCARD);
  msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYCARD);
  y = 0;
  // ウィンドウを消して…
  GF_BGL_BmpWinDataFill(win, 0);
  for(i = 0; i < max; i++){
    my = CommInfoGetMyStatus(order[i]);
    if(my){
      // トレーナー名を表示
      WORDSET_RegisterPlayerName(word, 0, my);
      msg = MSGDAT_UTIL_AllocExpandString(word, msgman, mystery_osusowake_002, HEAPID_MYSTERYCARD);
      if(MyStatus_GetMySex(my) == PM_MALE)
	GF_STR_PrintColor(win, FONT_SYSTEM, msg, 0, y, MSG_NO_PUT, MYSTERYCARD_BLUE, NULL);
      else
	GF_STR_PrintColor(win, FONT_SYSTEM, msg, 0, y, MSG_NO_PUT, MYSTERYCARD_RED, NULL);

      STRBUF_Delete(msg);
      // ＩＤを表示
      WORDSET_RegisterNumber(word, 0,
			     MyStatus_GetID(my) & 0xFFFF,
			     5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
      msg = MSGDAT_UTIL_AllocExpandString(word, msgman, mystery_osusowake_003, HEAPID_MYSTERYCARD);
      GF_STR_PrintColor(win, FONT_SYSTEM, msg, 80, y, MSG_NO_PUT, MYSTERYCARD_OWHITE, NULL);
      STRBUF_Delete(msg);
      y += MYSTERYCARD_OSUSOWAKE_HEIGHT;
    }
  }
  if(max)	GF_BGL_BmpWinOn(win);
  MSGMAN_Delete(msgman);
  WORDSET_Delete(word);
  return max;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	繋がっている人数を表示
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void MysteryCardDispConnectChildCount(MYSTERYCARD_WORK *wk, GF_BGL_BMPWIN *win, int num)
{
  STRBUF * msg;

  wk->entry = num;
  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYCARD);
  wk->word = WORDSET_Create(HEAPID_MYSTERYCARD);

  GF_BGL_BmpWinDataFill(win, 0);
  WORDSET_RegisterNumber(wk->word, 0, wk->entry, 1, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
  msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, mystery_osusowake_005, HEAPID_MYSTERYCARD);
  GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, MSG_NO_PUT, MYSTERYCARD_BLACK, NULL);
  GF_BGL_BmpWinOn(win);
  
  STRBUF_Delete(msg);
  MSGMAN_Delete(wk->msgman);
  WORDSET_Delete(wk->word);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	通信を終了させる
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CommMysteryCardExit(MYSTERYCARD_WORK *wk, int *seq, int next)
{
  CommMysteryExitGift();
  WirelessIconEasyEnd(); // 通信アイコン削除
  wk->next_seq = next;
  *seq = MYSTERYCARD_SEQ_WAIT_ENDCOMM;
}

// ------------------------------ ここまで ----------------------------

#define CHECK_OVERLAY
#ifdef CHECK_OVERLAY
FS_EXTERN_OVERLAY(startmenu);
#endif


extern const PROC_DATA MysteryGiftProcData;
static PROC_RESULT MysteryCardProc_End(PROC * proc, int * seq)
{
  int i;
  MYSTERYCARD_WORK *wk = PROC_GetWork(proc);

  for(i = 0; i < sizeof(MsgWin_Table) / sizeof(MYSTERYCARD_MSGWIN_TABLE); i++){
    if(wk->win[i].ini){
      GF_BGL_BmpWinOff(&wk->win[i]);
      GF_BGL_BmpWinDel(&wk->win[i]);
    }
  }
  if(wk->msgwin.ini) { GF_BGL_BmpWinOff(&wk->msgwin);  GF_BGL_BmpWinDel(&wk->msgwin);  }
  if(wk->menuwin.ini){ GF_BGL_BmpWinOff(&wk->menuwin); GF_BGL_BmpWinDel(&wk->menuwin); }

  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME2_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME3_M);
  sys_FreeMemoryEz(wk->bgl);
#ifdef CHECK_OVERLAY
  Main_SetNextProc( FS_OVERLAY_ID(startmenu), &MysteryGiftProcData);
#else
  Main_SetNextProc( NO_OVERLAY_ID, &MysteryGiftProcData);
#endif

  sys_DeleteHeap(HEAPID_COMMICON);
  PROC_FreeWork(proc);
  sys_DeleteHeap(HEAPID_MYSTERYCARD);
  
  return PROC_RES_FINISH;
}

const PROC_DATA MysteryCardProcData = {
  MysteryCardProc_Init,
  MysteryCardProc_Main,
  MysteryCardProc_End,
  NO_OVERLAY_ID,
};
  


//------------------------------------------------------------------
/**
 * @brief	カードを受け取った後に表示する関数
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void MysteryCard_DisplayCardOnly(GF_BGL_INI *bgl, void *p, int heapid)
{
  MYSTERYCARD_WORK *wk;

  CommMysteryFunc_BgInit(bgl);

  // カード表示に必要なワークエリアの設定
  wk = sys_AllocMemoryLo(heapid, sizeof(MYSTERYCARD_WORK));
  memset(wk, 0, sizeof(MYSTERYCARD_WORK));
  wk->bgl = bgl;
  wk->heapid = heapid;

  /* メッセージのフォントカラーを設定 */
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_NORMAL * 32, wk->heapid);
  
  wk->card[0] = (GIFT_CARD *)p;
  wk->disp_card = 0;

  MysteryCardCreateMsgWindow(wk, FONT_TALK, MYSTERYCARD_FRONT);
  sys_FreeMemoryEz(wk);
}


/*  */
