//============================================================================================
/**
 * @file	startmenu.c	
 * @bfief	タイトルメニュー
 * @author	Satoshi Mitsuhara
 * @date	06.04.11
 *
 * $Id: startmenu.c,v 1.71 2006/08/10 08:57:27 mitsuhara Exp $
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/main.h"
#include "system/wipe.h"
#include "system/wordset.h"
#include "system/msgdata_util.h"
#include "system/arc_util.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/snd_play.h"
#include "system/render_oam.h"

#include "gflib/bg_system.h"
#include "gflib/rebooter.h"

#include "savedata/savedata.h"
#include "savedata/zukanwork.h"
#include "savedata/playtime.h"
#include "savedata/fushigi_data.h"
#include "savedata/system_data.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_startmenu.h"
#include "msgdata/msg_bconfind.h"

#include "communication/comm_state.h"

#include "../fushigi/agbpoke_access.h"
#include "../fushigi/mysterylib.h"
#include "../fushigi/agbdownload.h"
#include "../fushigi/mystery.naix"

#include "msgdata/msg_wifi_system.h"
#include "wifi/dwc_rap.h"

/*
 * ※必ず表示されるメニュー
 *
 *	つづきからはじめる
 *	さいしょからはじめる
 *	WiFiせってい
 *
 * ※カートリッジが刺さっていると表示されるメニュー
 *
 *	なんとかとからつれてくる(ルビー/サファイア/...)
 *
 * ※条件によって表示されるメニュー
 *
 *	ポケモンレンジャーとせつぞく
 *	Wiiとのせつぞく
 *
 * ※メニューから選択した後に接続するもの
 *
 *	ダイレクトせつぞく
 *	WiFiせつぞく
 *	ビーコンせつぞく
 *
 */
/*
  タイトルメニューの最初の時点でお願いしたい事があります。
  WIFIの初期化関数なのですが、この関数の戻り値が
  DWC_INIT_RESULT_DESTROY_OTHER_SETTING　の場合に、
  メッセージを出していただきたいのです。
  ちなみにこのエラーはDS本体の通信情報が壊れた場合に出ます。

  #include "msgdata/msg_wifi_system.h"
  #include "wifi/dwc_rap.h"

  ret = mydwc_init(HEAPID_BASE_APP);
  if(ret == DWC_INIT_RESULT_DESTROY_OTHER_SETTING){
    message (  dwc_message_0001 );
  }

  PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL で本物のタイトルへ移動

  こういった流れになります。
*/

//
// BG0 - メニュー表示画面
// BG1 - ビーコンを拾った際に表示されるメニュー(一時的表示のみ)
// BG2 - 通信アイコン(BG0と一緒にスクロール)
//

#define WIICLIENT_FILE		"data/eoo.dat"

#define STARTMENU_FCHR1		1			// 通常フレーム
#define STARTMENU_FCOL1		2
#define STARTMENU_FCHR2		(STARTMENU_FCHR1 + 9)	// 選択時フレーム
#define STARTMENU_FCOL2		3


#define STARTMENU_WCHR		(STARTMENU_FCHR2 + 9)
#define STARTMENU_WCOL_SELECT	0
#define STARTMENU_WCOL_NORMAL	1

#define STARTMENU_WICON_PAL	4

#define STARTMENU_NOSELECT	-1

#define STARTMENU_FIRSTGAME_SELECT	0x80

#define RGB(r, g, b)	(((b)&31)<<10|((g)&31)<<5|((r)&31))

enum {
  // メインシーケンス
  STARTMENU_SEQ_INIT,
  STARTMENU_SEQ_CHECK_SYSTEM,		// 各種システムチェック
  STARTMENU_SEQ_DISP_ERROR,
  STARTMENU_SEQ_HARDINIT,
  STARTMENU_SEQ_CREATE_SCREEN,		// スクリーン作成(基本形)
  STARTMENU_SEQ_MAIN,
  STARTMENU_SEQ_SELECT_FIRSTGAME,

  STARTMENU_SEQ_SELECT_MENU,		// メニューが選択された後の処理

  STARTMENU_SEQ_FADE_WAIT,
  STARTMENU_SEQ_FINISH,			// 何もせず抜ける

  // ビーコン取得シーケンス
  STARTMENU_BEACON_SEQ_INIT,		// 初期化
  STARTMENU_BEACON_SEQ_INIT2,		// 初期化
  STARTMENU_BEACON_SEQ_WAIT,		// メイン処理が良いというまで待つ
  STARTMENU_BEACON_SEQ_TIMER,		// 実際のビーコン収集処理
  STARTMENU_BEACON_SEQ_CANCEL,		// 強制キャンセルモード

  // ビーコン取得時のメッセージ表示
  BEACON_MSGSEQ_NOP,			// 何もしない
  BEACON_MSGSEQ_INIT,			// 初期化
  BEACON_MSGSEQ_INIT_DISP,		// スクリーン初期化
  BEACON_MSGSEQ_INIT_MAIN,		// キー入力待ち
  BEACON_MSGSEQ_INIT_FINISH,		// 終了
  BEACON_MSGSEQ_FADE_WAIT,		// フェード待ち
  
  STARTMENU_SEQ_MAX
};


typedef struct _STARTMENU_DATA {
  int mark;
  int height;
  int msgid;
  // 表示時に呼び出されるファンクション
  BOOL (*func)(void */* STARTMENU_WORK */, int, MYSTERY_WIN *, int);
} STARTMENU_DATA;


static BOOL StartMenuAgbPokemon(void *, int, MYSTERY_WIN *, int);
static BOOL StartMenuCheckMystery(void *, int, MYSTERY_WIN *, int);
static BOOL StartMenuCheckRanger(void *, int, MYSTERY_WIN *, int);
static BOOL StartMenuCheckWii(void *, int, MYSTERY_WIN *, int);
static BOOL StartMenuSetWifi(void *, int, MYSTERY_WIN *, int);
static BOOL StartMenuContinue(void *, int, MYSTERY_WIN *, int);

enum {
  SEL_CANCEL = 0,
  SEL_CONTINUE,
  SEL_FIRSTGAME,
  SEL_MYSTERY,
  SEL_RANGER,
  SEL_AGBPOKEMON,
  SEL_WII,
  SEL_WIFI,
  SEL_MAX
};

enum {
  STARTMENU_DWC_ERROR = 0,		// DS本体の通信情報が壊れている
  STARTMENU_ERROR_MAX
};

typedef struct {
  int sx, sy, width, height;
  u32 arc, msgid;
  void (*func)(void */*STARTMENU_WORK* */);
} ERRORTABLE;

// ２つセットのエラー表示メッセージ
static ERRORTABLE ErrorMsgTable[] = {
  { 5, 5, 22, 14, NARC_msg_wifi_system_dat, dwc_message_0001, NULL/*DispErrorDwc*/ },
};


STARTMENU_DATA StartMenuWinTable[] = {
  // つづきから はじめる
  { SEL_CONTINUE,   10, mes_startmenu_01,	StartMenuContinue },
  // さいしょから　はじめる
  { SEL_FIRSTGAME,   2, mes_startmenu_02,	NULL },
  // ふしぎな　おくりもの
  { SEL_MYSTERY,     2, mes_startmenu_03,	StartMenuCheckMystery },
  // ポケモンレンジャーとの　せつぞく
  { SEL_RANGER,      2, mes_startmenu_04, 	StartMenuCheckRanger },
  // ×××から　つれてくる
  { SEL_AGBPOKEMON,  2, NULL, 			StartMenuAgbPokemon },
  // Wiiと　せつぞく
  { SEL_WII,         2, mes_startmenu_11, 	StartMenuCheckWii },
  // Wi-Fiせってい
  { SEL_WIFI,        2, mes_startmenu_12, 	StartMenuSetWifi },
};


static u32 StartMenuContinueTable[] = {
  mes_startmenu_01,			// つづきから　はじめる
  mes_startmenu_13,			// しゅじんこう
  mes_startmenu_14,			// プレイじかん
  mes_startmenu_16,			// もっているバッジ
  mes_startmenu_15,			// ポケモンずかん
};

// ビーコンを拾ったときのメッセージデータ
typedef struct {
  int sx, sy;
  int width, height;
  int msg;
} BEACON_MSG_TABLE;
BEACON_MSG_TABLE BeaconMsgTable[] = {
  { 4, 2, 24, 20, bcon_002 },		// ふしぎなおくりものを発見。メニューで選んでね
  { 4, 4, 24, 16, bcon_004 },		// ふしぎなおくりものを発見。でもまだダメ
  { 4, 1, 24, 22, bcon_001 },		// レンジャーを発見。メニューで選んでね
  { 4, 3, 24, 18, bcon_003 },		// レンジャーを発見。でもまだダメ
  // ↓これだけメニュー選択時メッセージ
  { 2, 1, 28, 22, bcon_006 },		// さいしょからはじめてもセーブできんよ？
};



// メニューの最大数
#define MENU_WIN_MAX	(sizeof(StartMenuWinTable) / sizeof(STARTMENU_DATA))

// ビーコン情報を集める時間
#define BEACON_GATHER_TIME	(2*60)

#define SetSeq(w, n)	(w = n)


typedef struct {
  GF_BGL_INI *bgl;
  SAVEDATA *sv;
  ZUKAN_WORK *zw;
  MYSTATUS *mst;
  PLAYTIME *ptime;
  FUSHIGI_DATA *fdata;				// ふしぎデータを読んだ場所

  // メインシーケンス関係

  int jiffy;
  int next_seq;
  int chrbase;			       	// ウィンドウのキャラクタベース

  int agbpokemon;     			// 刺さっているAGBカセットのタイプ(CASTYPE_xxx)
  int agbpokemoncheck;
  int pokemonranger;			// ポケモンレンジャーを発見した
  int wii;				// Wiiのビーコンを発見した
  int mystery;				// ふしぎな　おくりものビーコン

  int menu_flag;			// 各種ビーコンメニューを表示したか？(PARTYGAME_xxx)
  int new_menu_flag;
  
  
  int beacon_status;
  int beacon_disp_status;
  int redrawflag;
  
  int zukangetflag;			// ずかんを持っているならTRUE
  int badgecount;			// もっているバッチの数


  int cursor;				// 現在のカーソル位置

  int select;				// 選択された項目(-1ならば何も選択していない)
  
  GF_BGL_BMPWIN mwin[MENU_WIN_MAX];
  int menuflag[MENU_WIN_MAX];		// 表示されていたらTRUE(default = FALSE)
  int iconflag[MENU_WIN_MAX];		// ワイヤレスアイコンがある時にTRUE

  fx32 scrolly;				// 現在のスクロール値
  fx32 target;				// 目的座標

  // ビーコン取得関係
  int beacon_seq;
  int beacon_wait;
  int beacon_msg_seq;			// ビーコン取得時に表示するメッセージシーケンス
  int beacon_msg_wait;
  int beacon_key_wait;
  int beacon_result;
  GF_BGL_BMPWIN beacon_win;
  
  int pass_start_menu;			// TRUEならばスタートメニューを表示させない
  int req_popup;

  // エラー情報
  BOOL errorflag[STARTMENU_ERROR_MAX];
  GF_BGL_BMPWIN ewin;
  
  // カーソルアクター
  CLACT_WORK_PTR clcursor[2];		// 0 = ↑　1 = ↓

  int anim_index;
} STARTMENU_WORK;






//============================================================================================
//	外部関数定義
//============================================================================================
extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);
extern int CommPlayerNowFlagDataArraySize(void);
extern int MyStatus_GetWorkSize(void);
extern void CreateIndexData(int heapid);

//============================================================================================
//	定数定義
//============================================================================================


//------------------------------------------------------------------
/**
 * @brief	システムエラーチェック
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int StartMenuCheckSystem(STARTMENU_WORK *wk)
{
  int max, ret;
  
  max = 0;
#if 0  //mainで呼びますので、ここは消します
  // DS本体の通信情報が壊れていないかチェックする
  ret = mydwc_init(HEAPID_BASE_APP);
#if 0	// デバッグ用ですよ
  ret = DWC_INIT_RESULT_DESTROY_OTHER_SETTING;
#endif
  if(ret == DWC_INIT_RESULT_DESTROY_OTHER_SETTING){
    wk->errorflag[STARTMENU_DWC_ERROR] = TRUE;
    max++;
  }
#endif
  return max;
}


//------------------------------------------------------------------
/**
 * @brief	エラー情報を表示する
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL StartMenuDisplayError(STARTMENU_WORK *wk)
{
  int i;
  ERRORTABLE *et;
  MYSTERY_WIN mw;

  // エラー表示ウィンドウが初期化されているかどうかで判断を行おうかな
  if(GF_BGL_BmpWinAddCheck(&wk->ewin) == FALSE){
    for(i = 0; i < STARTMENU_ERROR_MAX; i++){
      if(wk->errorflag[i] == TRUE){
	wk->errorflag[i] = FALSE;
	et = &ErrorMsgTable[i];
	//ここでエラー表示を行う
	MysteryLib_WinInit1(&mw, &wk->ewin, STARTMENU_WCOL_SELECT, et->arc, STARTMENU_FCHR1, STARTMENU_FCOL1);
	MysteryLib_WinInit2(&mw, et->width, et->height, /*et->msgid,*/ STARTMENU_WCHR);
	MysteryLib_CreateWin(wk->bgl, &mw, et->sx, et->sy, et->msgid);
	return TRUE;
      }
    }
  } else {
    // エラーウィンドウの表示中
    if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      BmpMenuWinClear(&wk->ewin, WINDOW_TRANS_ON);
      GF_BGL_BmpWinDel(&wk->ewin);
    }
    return TRUE;
  }



  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	ＡＧＢカセットが刺さっているか初期化する
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void AgbCartridgeInit(STARTMENU_WORK *wk)
{
  int pmv;
  int flag = agbpoke_init(NULL);

  wk->agbpokemon = FALSE;
  
  // AGBポケモンが刺さっていなければ何もしない
  if(flag != AGBPOKE_ERROR_OK)
    return;

  // システムへカセットタイプを通知する
  pmv = 0;	// unknown
  switch(agbpoke_getPokemonType()){
  case CASTYPE_RUBY:	pmv = VERSION_RUBY;	break;
  case CASTYPE_SAPPHIRE:pmv = VERSION_SAPPHIRE; break;
  case CASTYPE_GREEN:	pmv = VERSION_GREEN;	break;
  case CASTYPE_RED:	pmv = VERSION_RED;	break;
  case CASTYPE_EMERALD:	pmv = VERSION_EMERALD;	break;
  }
  sys_InitAgbCasetteVer(pmv);
#ifdef DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("AGBカセットバージョン: %d\n", pmv);
#endif

#ifndef DEBUG_ONLY_FOR_mituhara
  // DP側の全国ずかんモードがONになっていなければポケモンカセットのメニューは表示されない
  if(ZukanWork_GetZenkokuZukanFlag(wk->zw) == FALSE)
    return;
#endif

  // DPと同じ言語でなければメニューは表示しない
  if(agbpoke_getPokemonLanguage() != CasetteLanguage)
    return;

  // ポケモンのタイプを設定する
  wk->agbpokemon = agbpoke_getPokemonType() + 1;

#if 0
  // RTC付きのカートリッジで、RTCの電池が切れたものは常にOS_IE_CARTRIDGE割り込みが
  // 掛かってしまうため、タイトル画面ではカートリッジ抜け判定をしない
  // ただし「×××から　つれてくる」を選択した時に停止するようにする
  // 2006.08.10(※マスターアップ当日)

  /* AGBカートリッジの抜け検出ON */
  MysteryLib_SetAgbCartridgeIntr(TRUE);
#else
  /* スリープ時のカートリッジ抜けを有効にするための関数呼び出し */
  MysteryLib_SetAgbCartridgeIntr2();
#endif
}


//------------------------------------------------------------------
/**
 * @brief	ビーコン取得プロセス
 * 		※threadになってるわけではありません
 */
//------------------------------------------------------------------
static void StartMenuBeacon_Proc(STARTMENU_WORK *wk)
{
  int flag;

  switch(wk->beacon_seq){
  case STARTMENU_BEACON_SEQ_WAIT:
    // 外部からシーケンスを変更されない限り動かない
    break;

  case STARTMENU_BEACON_SEQ_INIT:
    wk->beacon_seq = STARTMENU_BEACON_SEQ_INIT2;
    break;
  case STARTMENU_BEACON_SEQ_INIT2:
    // * パーティーゲーム検索の通信処理開始（子機状態のみ）
    CommStateEnterPartyGameScanChild(wk->sv);
    wk->beacon_wait = BEACON_GATHER_TIME;
    wk->beacon_seq = STARTMENU_BEACON_SEQ_TIMER;
    wk->beacon_status = 0;
    // すでに「ふしぎな　おくりもの」メニューが表示されていたらポップアップはしない
    if(FUSHIGIDATA_IsFushigiMenu(wk->fdata) == TRUE){
      wk->beacon_status |= PARTYGAME_MYSTERY_BCON;
      wk->beacon_disp_status |= PARTYGAME_MYSTERY_BCON;
    }
    
    break;

  case STARTMENU_BEACON_SEQ_TIMER:
    // すでにポップアップ予約中
    if(wk->beacon_msg_wait)	break;
    // ビーコン収集中
    flag = CommStateGetPartyGameBit();

#ifdef DEBUG_ONLY_FOR_mituhara
    // デバッグ中
#if 1
    if(sys.trg & PAD_BUTTON_L)	flag |= PARTYGAME_RANGER_BCON;
    if(sys.trg & PAD_BUTTON_R)	flag |= PARTYGAME_WII_BCON;
    if(sys.trg & PAD_BUTTON_Y)	flag |= PARTYGAME_MYSTERY_BCON;
#else
    flag |= PARTYGAME_RANGER_BCON;
    flag |= PARTYGAME_WII_BCON;
    flag |= PARTYGAME_MYSTERY_BCON;
#endif
#endif
    
    // 前回まで表示していないビットのみ立てる
    flag = ~wk->beacon_status & flag;
    // 何かのビーコンを拾っていて、割り込みメッセージ表示中でなくて、すでに予約済みでなくて、まだ表示してない場合
    if(flag && wk->beacon_msg_seq == BEACON_MSGSEQ_NOP && wk->beacon_msg_wait == 0 && wk->beacon_status != flag){
      wk->redrawflag = TRUE;
      if(flag & PARTYGAME_MYSTERY_BCON)	wk->mystery = TRUE,		flag = PARTYGAME_MYSTERY_BCON;
      if(flag & PARTYGAME_RANGER_BCON)	wk->pokemonranger = TRUE,	flag = PARTYGAME_RANGER_BCON;
      if(flag & PARTYGAME_WII_BCON)	wk->wii = TRUE,			flag = PARTYGAME_WII_BCON;
      // ふしぎビーコンとレンジャービーコンの場合は割り込みメッセージ表示
      if(flag & (PARTYGAME_MYSTERY_BCON|PARTYGAME_RANGER_BCON))
	wk->req_popup = TRUE;
      // ここでようやく表示済みフラグの更新
      wk->beacon_status |= flag;
    }
    if(--wk->beacon_wait == 0){
      // パーティーゲームサーチの終了処理
      CommStateExitPartyGameScan();
      wk->beacon_seq = STARTMENU_BEACON_SEQ_WAIT;
    }
    break;

  case STARTMENU_BEACON_SEQ_CANCEL:
    // 強制終了処理(ゲームが開始されたとか)
    CommStateExitPartyGameScan();
    wk->beacon_seq = STARTMENU_BEACON_SEQ_WAIT;
    break;
  }
}


//------------------------------------------------------------------
/**
 * @brief	ビーコンを取得した際に表示する画面
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL BeaconMessage_Proc(STARTMENU_WORK *wk)
{
  MYSTERY_WIN mw;
  BEACON_MSG_TABLE *tbl;
  int msg, status;

  switch(wk->beacon_msg_seq){
  case BEACON_MSGSEQ_NOP:
    if(wk->beacon_msg_wait == 0)	return FALSE;
    // ビーコンを拾ってから数フレーム後に発動
    if(--wk->beacon_msg_wait == 0)
      wk->beacon_msg_seq = BEACON_MSGSEQ_INIT;
    return TRUE;
    break;

  case BEACON_MSGSEQ_INIT:
    // 初期化
    MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME1_M, STARTMENU_FCHR1, STARTMENU_FCOL1, 0, HEAPID_STARTMENU);
    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME1_M);
    *((u16 *)HW_BG_PLTT + 33) = RGB(26, 26, 26);
    wk->beacon_msg_seq = BEACON_MSGSEQ_INIT_DISP;
    break;

  case BEACON_MSGSEQ_INIT_DISP:
    // スクリーン初期化
    MysteryLib_WinInit1(&mw, &wk->beacon_win, STARTMENU_WCOL_SELECT, NARC_msg_bconfind_dat, STARTMENU_FCHR1, STARTMENU_FCOL1);

    // １度表示したメニューは表示しないために表示したフラグを覚えておく
    status = wk->beacon_status & ~wk->beacon_disp_status;

    if(status & PARTYGAME_MYSTERY_BCON){
      if(wk->menu_flag & PARTYGAME_MYSTERY_BCON)	tbl = &BeaconMsgTable[0];	// ふしぎ追加
      else						tbl = &BeaconMsgTable[1];	// 追加できなかった
    } else if(status & PARTYGAME_RANGER_BCON){
      if(wk->menu_flag & PARTYGAME_RANGER_BCON)		tbl = &BeaconMsgTable[2];	// レンジャー追加
      else						tbl = &BeaconMsgTable[3];	// 追加できなかった
    } else if(status & STARTMENU_FIRSTGAME_SELECT){
      tbl = &BeaconMsgTable[4];	// さいしょからはじめるをえらんだ時のメッセージ
      status = 0;	// 何度でも表示させたいので覚えさせない
    }
    wk->beacon_disp_status |= status;

    MysteryLib_WinInit2(&mw, tbl->width, tbl->height, STARTMENU_WCHR);
    mw.screen = GF_BGL_FRAME1_M;
    MysteryLib_CreateWin(wk->bgl, &mw, tbl->sx, tbl->sy, tbl->msg);

    GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME1_M,
			GF_BGL_BmpWinGet_PosX(mw.win),  GF_BGL_BmpWinGet_PosY(mw.win),
			GF_BGL_BmpWinGet_SizeX(mw.win), GF_BGL_BmpWinGet_SizeY(mw.win),
			STARTMENU_WCOL_SELECT);
    
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_OFF);
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_OFF);
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_ON);
    wk->beacon_key_wait = 30;
    wk->beacon_msg_seq = BEACON_MSGSEQ_INIT_MAIN;
    break;

  case BEACON_MSGSEQ_INIT_MAIN:
    // キー入力待ち
    if(wk->beacon_key_wait){
      wk->beacon_key_wait--;
    } else {
      if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
	GF_BGL_BmpWinDel(&wk->beacon_win);
	wk->beacon_msg_seq = BEACON_MSGSEQ_INIT_FINISH;
	wk->beacon_result = sys.trg;
	Snd_SePlay(SEQ_SE_DP_SELECT);
      }
    }
    break;

  case BEACON_MSGSEQ_INIT_FINISH:
    // 終了
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_ON);
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_ON);
    GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);
    wk->beacon_msg_seq = BEACON_MSGSEQ_NOP;
    break;
  }
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	毎フレーム行う処理
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
// 条件分岐しないABS
#define ABS(x)		(((x) ^ ((x)>>31)) - ((x)>>31))
#define SCROLL_MAX_SPEED	(12 * FX32_ONE)
static void StartMenuProc(STARTMENU_WORK *wk)
{
  fx32 speed;

  // スクロール処理
  if(wk->scrolly != wk->target){
    speed = (wk->target - wk->scrolly) / 4;
    if(ABS(speed) > SCROLL_MAX_SPEED){
      if(speed > 0)	speed =  SCROLL_MAX_SPEED;
      else		speed = -SCROLL_MAX_SPEED;
    }
    wk->scrolly += speed;

    if(ABS(wk->target - wk->scrolly) < FX32_ONE/8)
      wk->scrolly = wk->target;

    GF_BGL_ScrollReq(wk->bgl, GF_BGL_FRAME0_M, GF_BGL_SCROLL_Y_SET, wk->scrolly / FX32_ONE);
    GF_BGL_ScrollReq(wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_SET, wk->scrolly / FX32_ONE);
  } 
}

//------------------------------------------------------------------
/**
 * @brief	スクリーン初期化
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void InitStartMenuScreen(STARTMENU_WORK *wk)
{
  GF_BGL_DISPVRAM tbl = {
    GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
    GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
    GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
    GX_VRAM_SUB_BGEXTPLTT_NONE,			// サブ2DエンジンのBG拡張パレット
    GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
    GX_VRAM_OBJEXTPLTT_NONE,			// メイン2DエンジンのOBJ拡張パレット
    GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
    GX_VRAM_SUB_OBJEXTPLTT_NONE,		// サブ2DエンジンのOBJ拡張パレット
    GX_VRAM_TEX_0_B,				// テクスチャイメージスロット
    GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
  };
  GF_BGL_SYS_HEADER BGsys_data = { GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D };

  GF_Disp_SetBank( &tbl );

  /* BG SYSTEM */
  GF_BGL_InitBG( &BGsys_data );
  /* メニューを表示するBG */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME0_M, GF_BGL_SCRSIZ_256x512, 0xF000, 0x0000); /* MAIN DISP BG0 */
  G2_SetBG0Priority(2);
  GF_BGL_ClearCharSet(GF_BGL_FRAME0_M, 32, 0, HEAPID_STARTMENU);
  /* ビーコン取得時に表示するメッセージBG */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME1_M, GF_BGL_SCRSIZ_256x256, 0xD800, 0x8000); /* MAIN DISP BG1 */
  G2_SetBG1Priority(1);
  GF_BGL_ClearCharSet(GF_BGL_FRAME1_M, 32, 0, HEAPID_STARTMENU);
  /* 通信アイコンを表示するBG画面 */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME2_M, GF_BGL_SCRSIZ_256x512, 0xE000, 0x0000); /* MAIN DISP BG2 */
  G2_SetBG2Priority(0);
  GF_BGL_ClearCharSet(GF_BGL_FRAME2_M, 32, 0, HEAPID_STARTMENU);

  MSG_PrintInit();

  /* メッセージのフォントカラーを設定 */
  SystemFontPaletteLoad(PALTYPE_MAIN_BG, STARTMENU_WCOL_NORMAL * 32, HEAPID_STARTMENU);
  SystemFontPaletteLoad(PALTYPE_MAIN_BG, STARTMENU_WCOL_SELECT * 32, HEAPID_STARTMENU);
  *((u16 *)HW_BG_PLTT +  0) = RGB( 0,  0,  0);

  *((u16 *)HW_BG_PLTT + 31) = RGB(26, 26, 26);	// ウィンドウの背景
  //ウィンドウ枠キャラ、パレットをセット
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, STARTMENU_FCHR1, STARTMENU_FCOL1, 0, HEAPID_STARTMENU);
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, STARTMENU_FCHR2, STARTMENU_FCOL2, 1, HEAPID_STARTMENU);
  // 選択してないウィンドウの白ライン
  *((u16 *)HW_BG_PLTT + 33) = RGB(26, 26, 26);

}


//------------------------------------------------------------------
/**
 * @brief	スクロールカーソルの表示準備
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void StartMenuInitClact(STARTMENU_WORK *wk)
{
  MysteryLib_InitCPManager();
  MysteryLib_InitClactSystem();
  MysteryLib_InitClact(ARC_MYSTERY_GRA,
		       NARC_mystery_title_cursor_lz_cngr,
		       NARC_mystery_title_cursol_nclr,
		       NARC_mystery_title_cursor_lz_ccer,
		       NARC_mystery_title_cursor_lz_canr,
		       GF_BGL_MAIN_DISP);
  wk->clcursor[0] = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->clcursor[0],  HW_LCD_WIDTH/2, 8, 0);
  CLACT_SetDrawFlag(wk->clcursor[0], 0);
  wk->clcursor[1] = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->clcursor[1],  HW_LCD_WIDTH/2, HW_LCD_HEIGHT - 8, 1);
  CLACT_SetDrawFlag(wk->clcursor[1], 0);
}


//------------------------------------------------------------------
/**
 * @brief	通信アイコンのグラフィックス準備
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define WIRELESS_CHR_BASE		0x0380
static void WirelessIconInit(STARTMENU_WORK *wk)
{
  // メイン画面ＢＧパレット転送
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_wicon_nclr, PALTYPE_MAIN_BG, STARTMENU_WICON_PAL*32, 32*1, HEAPID_STARTMENU);
  // メイン画面BG1キャラ転送
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_wicon_ncgr, wk->bgl,
		    GF_BGL_FRAME2_M, WIRELESS_CHR_BASE, 2*32*0x20, 0, HEAPID_STARTMENU);
}


//------------------------------------------------------------------
/**
 * @brief	指定座標に通信アイコンを表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define WIRELESS_ICON_BASE		((STARTMENU_WICON_PAL << 12) + WIRELESS_CHR_BASE + 0)
static void SetWirelessIcon(STARTMENU_WORK *wk, int sx, int sy, int flag)
{
  u16 *scrn = (u16 *)GF_BGL_ScreenAdrsGet(wk->bgl, GF_BGL_FRAME2_M);
  int base = WIRELESS_ICON_BASE;

  if(flag == 2)	base = WIRELESS_ICON_BASE + 2;
  
  scrn[sy * 32 + sx + 0] = base + 0;
  scrn[sy * 32 + sx + 1] = base + 1;
  sy++;
  scrn[sy * 32 + sx + 0] = base + 8;
  scrn[sy * 32 + sx + 1] = base + 9;
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME2_M);
}
static void ClrWirelessIcon(STARTMENU_WORK *wk, int sx, int sy)
{
  u16 *scrn = (u16 *)GF_BGL_ScreenAdrsGet(wk->bgl, GF_BGL_FRAME2_M);
  scrn[sy * 32 + sx + 0] = WIRELESS_ICON_BASE + 4;
  scrn[sy * 32 + sx + 1] = WIRELESS_ICON_BASE + 4;
  sy++;
  scrn[sy * 32 + sx + 0] = WIRELESS_ICON_BASE + 4;
  scrn[sy * 32 + sx + 1] = WIRELESS_ICON_BASE + 4;
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME2_M);
}


//------------------------------------------------------------------
/**
 * @brief	つづきからはじめるの内容表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define STARTMENU_MARGIN_L	32
#define	STARTMENU_BLUE		(GF_PRINTCOLOR_MAKE(7, 8, 15))
#define	STARTMENU_RED		(GF_PRINTCOLOR_MAKE(3, 4, 15))

static void StartMenuContinueSub1(GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, WORDSET *word, GF_PRINTCOLOR color, u32 msgid, int y)
{
  int width, wsize;
  STRBUF * msg;

  msg = MSGDAT_UTIL_AllocExpandString(word, msgman, msgid, HEAPID_STARTMENU);
  width = FontProc_GetPrintStrWidth(FONT_SYSTEM, msg,	FontHeaderGet(FONT_SYSTEM, FONT_HEADER_SPACE_X));
  wsize = GF_BGL_BmpWinGet_SizeX(win) * 8 - (width + STARTMENU_MARGIN_L);
  GF_STR_PrintColor(win, FONT_SYSTEM, msg, wsize, y, MSG_NO_PUT, color, NULL);
  STRBUF_Delete(msg);
}
static void StartMenuContinueSub2(WORDSET *word, int value)
{
  int keta, type;
  if (value >= 100) { 	keta = 3; 	type = NUMBER_DISPTYPE_LEFT;  }
  else if (value >= 10) {	keta = 3;	type = NUMBER_DISPTYPE_SPACE; }
  else {			keta = 3 - 1;	type = NUMBER_DISPTYPE_SPACE; }
  WORDSET_RegisterNumber(word, 0, value, keta, type, NUMBER_CODETYPE_DEFAULT);
}

static BOOL StartMenuContinue(void *p, int index, MYSTERY_WIN *mw, int y)
{
  int i, width, wsize;
  STRBUF * msg;
  WORDSET *word;
  MSGDATA_MANAGER *msgman;
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;
  GF_PRINTCOLOR color;

  msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_startmenu_dat, HEAPID_STARTMENU);
  word = WORDSET_Create(HEAPID_STARTMENU);

  // 女性(FEMALE)なら赤、それ以外(MALE, NEUTRAL)ならば青
  if(MyStatus_GetMySex(wk->mst) == PM_FEMALE)	color = STARTMENU_RED;
  else						color = STARTMENU_BLUE;
  
  // さいしょの１行を表示
  MysteryLib_CreateWin(wk->bgl, mw, 3, y, StartMenuWinTable[index].msgid);
  // ２行目以降を表示
  for(i = 1; i < sizeof(StartMenuContinueTable) / sizeof(u32); i++){
    // ずかんを持っていなかったら、そもそも項目を表示しない
    if(i == 4 && wk->zukangetflag == FALSE) continue;
    // それ以外は普通に表示して良い
    msg = MSGDAT_UTIL_AllocExpandString(word, msgman, StartMenuContinueTable[i], HEAPID_STARTMENU);
    GF_STR_PrintColor(mw->win, FONT_SYSTEM, msg, STARTMENU_MARGIN_L, i*16, MSG_NO_PUT, color, NULL);
    STRBUF_Delete(msg);
  }
  
  // 主人公の情報表示
  WORDSET_RegisterPlayerName(word, 0, wk->mst);
  StartMenuContinueSub1(mw->win, msgman, word, color, mes_startmenu_17, 16*1);
  // プレイ時間を表示
  StartMenuContinueSub2(word, PLAYTIME_GetHour(wk->ptime));
  WORDSET_RegisterNumber(word, 1, PLAYTIME_GetMinute(wk->ptime), 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  StartMenuContinueSub1(mw->win, msgman, word, color, mes_startmenu_18, 16*2);
  // もっているバッチ
  WORDSET_RegisterNumber(word, 0, wk->badgecount, 1, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
  StartMenuContinueSub1(mw->win, msgman, word, color, mes_startmenu_20, 16*3);
  // ポケモンずかん表示
  if(wk->zukangetflag){
    StartMenuContinueSub2(word, ZukanWork_GetZukanPokeSeeCount(wk->zw));
    StartMenuContinueSub1(mw->win, msgman, word, color, mes_startmenu_19, 16*4);
  }
  // まとめて表示
  BmpMenuWinWrite(mw->win, WINDOW_TRANS_ON, mw->fchr, mw->fcol);
  // 描いたよフラグをON
  wk->menuflag[index] = StartMenuWinTable[index].mark;

  WORDSET_Delete(word);
  MSGMAN_Delete(msgman);

  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	ＡＧＢポケモンの有無を調べてメニュー表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL StartMenuAgbPokemon(void *p, int index, MYSTERY_WIN *mw, int y)
{
  int msg;
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;

  // AGBカートリッジの存在は別のタイミングで行っています
  if(wk->agbpokemon == FALSE)	return FALSE;

  // 文字列を選択
  switch(wk->agbpokemon - 1){
  case CASTYPE_RUBY:	msg = mes_startmenu_05; break;
  case CASTYPE_SAPPHIRE:msg = mes_startmenu_06; break;
  case CASTYPE_GREEN:	msg = mes_startmenu_07; break;
  case CASTYPE_RED:	msg = mes_startmenu_08; break;
  case CASTYPE_EMERALD:	msg = mes_startmenu_09; break;
  }    
  // メニュー表示
  MysteryLib_CreateWin(wk->bgl, mw, 3, y, msg);
  ClrWirelessIcon(wk, 26, y);
  wk->menuflag[index] = StartMenuWinTable[index].mark;

  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	ふしぎな　おくりものを表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL StartMenuCheckMystery(void *p, int index, MYSTERY_WIN *mw, int y)
{
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;

  // ふしぎな　おくりものを強制的にONにする場合の処理
  if(wk->mystery == FALSE){
    // すでにふしぎな　おくりものは表示可能？
    if(FUSHIGIDATA_IsFushigiMenu(wk->fdata) == TRUE)
      wk->mystery = TRUE;
    // ゲーム中のあいことばが成立している？
    if(SYSTEMDATA_GetWifiMPOpenFlag(SaveData_GetSystemData(wk->sv)) == TRUE)
      wk->mystery = TRUE;
    // AGBでの配布用カセットが刺さってる？
    if(GetAgbCartridgeDataSize()){
      wk->mystery = TRUE;
      MysteryLib_SetAgbCartridgeIntr(TRUE);	/* AGBカートリッジの抜け検出ON */
    }
  }

  // ふしぎな　おくりものを強制的にOFFにする場合の処理
  if(wk->mystery == TRUE){
    // ずかんを持っていなければ強制的にOFFする
    if(wk->zukangetflag == FALSE)
      wk->mystery = FALSE;
  }

  // 実際のチェックはStartMenuBeacon_Procで行っています
  if(wk->mystery == TRUE){
    // メニュー表示
    MysteryLib_CreateWin(wk->bgl, mw, 3, y, StartMenuWinTable[index].msgid);
#if 0
    SetWirelessIcon(wk, 26, y, 1);
    wk->iconflag[index] = 1;
#else
    ClrWirelessIcon(wk, 26, y);
#endif
    wk->menuflag[index] = StartMenuWinTable[index].mark;
    wk->menu_flag |= PARTYGAME_MYSTERY_BCON;
    FUSHIGIDATA_SetFushigiMenu(wk->fdata);
    return TRUE;
  }

  return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	ポケモンレンジャーとの接続を表示
 * @param	NONE
 * @return	NONE
*/
//------------------------------------------------------------------
static BOOL StartMenuCheckRanger(void *p, int index, MYSTERY_WIN *mw, int y)
{
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;
  // 実際のチェックはStartMenuBeacon_Procで行っています

  if(wk->pokemonranger == TRUE && wk->zukangetflag == TRUE){
    // メニュー表示
    MysteryLib_CreateWin(wk->bgl, mw, 3, y, StartMenuWinTable[index].msgid);
    SetWirelessIcon(wk, 26, y, 1);
    wk->iconflag[index] = 1;
    wk->menuflag[index] = StartMenuWinTable[index].mark;
    wk->menu_flag |= PARTYGAME_RANGER_BCON;
    return TRUE;
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	Wiiのメニューを表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL StartMenuCheckWii(void *p, int index, MYSTERY_WIN *mw, int y)
{
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;
  // 実際のチェックはStartMenuBeacon_Procで行っています

  if(wk->wii == TRUE){
    // メニュー表示
    MysteryLib_CreateWin(wk->bgl, mw, 3, y, StartMenuWinTable[index].msgid);
    wk->iconflag[index] = 1;
    SetWirelessIcon(wk, 26, y, 1);
    wk->menuflag[index] = StartMenuWinTable[index].mark;
    return TRUE;
  }
  return FALSE;
}


//------------------------------------------------------------------
/**
 * @brief	Wi-Fi設定
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL StartMenuSetWifi(void *p, int index, MYSTERY_WIN *mw, int y)
{
  STARTMENU_WORK *wk = (STARTMENU_WORK *)p;
  // メニュー表示
  MysteryLib_CreateWin(wk->bgl, mw, 3, y, StartMenuWinTable[index].msgid);
  wk->iconflag[index] = 2;
  SetWirelessIcon(wk, 26, y, 2);
  wk->menuflag[index] = StartMenuWinTable[index].mark;
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	メニュー作成
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL CreateStartMenu(STARTMENU_WORK *wk)
{
  STARTMENU_DATA *smd;
  MYSTERY_WIN mw;
  int i, y, ret;

  ret = FALSE;
  y = 1;
  wk->chrbase = STARTMENU_WCHR;
  for(i = 0; i < MENU_WIN_MAX; i++){
    smd = &StartMenuWinTable[i];

    MysteryLib_WinInit1(&mw, &wk->mwin[i], STARTMENU_WCOL_NORMAL, NARC_msg_startmenu_dat, STARTMENU_FCHR1, STARTMENU_FCOL1);
    MysteryLib_WinInit2(&mw, 26, smd->height,/* NULL,*/ wk->chrbase);
    if(smd->func){
      // func内部で表示
      if(wk->menuflag[i]){
	GF_BGL_BmpWinSet_PosX(mw.win, 3);
	GF_BGL_BmpWinSet_PosY(mw.win, y);
	BmpMenuWinWrite(mw.win, WINDOW_TRANS_ON, mw.fchr, mw.fcol);
	if(wk->iconflag[i])	SetWirelessIcon(wk, 26, y, wk->iconflag[i]);
	else			ClrWirelessIcon(wk, 26, y);
	y += smd->height + 2;
	ret = TRUE;
      } else if(smd->func(wk, i, &mw, y) == TRUE){
	y += smd->height + 2;
	ret = TRUE;
      }
    } else {
      // 通常表示
      MysteryLib_CreateWin(wk->bgl, &mw, 3, y, smd->msgid);
      wk->menuflag[i] = smd->mark;
      y += smd->height + 2;
    }
    wk->chrbase += 26 * smd->height;
  }
  return ret;
}


//------------------------------------------------------------------
/**
 * @brief	ウィンドウの枠(フレーム)を再表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void RedrawWindowFrame(STARTMENU_WORK *wk, int select)
{
  int i;
  for(i = 0; i < sizeof(StartMenuWinTable) / sizeof(STARTMENU_DATA); i++){
    if(GF_BGL_BmpWinAddCheck(&wk->mwin[i]) == FALSE)	continue;

    if(i == select){
      BmpMenuWinWrite(&wk->mwin[i], WINDOW_TRANS_OFF, STARTMENU_FCHR2, STARTMENU_FCOL2);
      GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME0_M,
			  GF_BGL_BmpWinGet_PosX(&wk->mwin[i]),  GF_BGL_BmpWinGet_PosY(&wk->mwin[i]),
			  GF_BGL_BmpWinGet_SizeX(&wk->mwin[i]), GF_BGL_BmpWinGet_SizeY(&wk->mwin[i]),
			  STARTMENU_WCOL_SELECT);
    } else {
      BmpMenuWinWrite(&wk->mwin[i], WINDOW_TRANS_OFF, STARTMENU_FCHR1, STARTMENU_FCOL1);
      GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME0_M,
			  GF_BGL_BmpWinGet_PosX(&wk->mwin[i]),  GF_BGL_BmpWinGet_PosY(&wk->mwin[i]),
			  GF_BGL_BmpWinGet_SizeX(&wk->mwin[i]), GF_BGL_BmpWinGet_SizeY(&wk->mwin[i]),
			  STARTMENU_WCOL_NORMAL);
    }
  }
  // スクリーンの全体を再転送
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME0_M);
}


//------------------------------------------------------------------
/**
 * @brief	次のカーソル位置を検索する
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void NextCursorPosition(STARTMENU_WORK *wk, int offset)
{
  int now = wk->cursor;

  while(1){
    now += offset;
    // オーバーフロー検査
    if(now == -1)		now = 0;
    if(now == MENU_WIN_MAX)	now = MENU_WIN_MAX - 1;
    // 動ける場所がなければ動かない
    if(now == wk->cursor)
      break;
    // 動ける場所が見つかったら決定
    if(wk->menuflag[now]){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      break;
    }
  }

  wk->cursor = now;
}


//------------------------------------------------------------------
/**
 * @brief	カーソルが画面内に入るようにスクロール登録
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetCursorScroll(STARTMENU_WORK *wk)
{
  int cursory, height, basey;

  // ドット換算のカーソル位置を算出
  cursory = (GF_BGL_BmpWinGet_PosY(&wk->mwin[wk->cursor] ) - 1) * 8;
  height = (GF_BGL_BmpWinGet_SizeY(&wk->mwin[wk->cursor] ) + 2) * 8;

  // 現在のスクロール値(目的座標)
  basey = wk->target / FX32_ONE;

  // 画面の中に入っているか調査する

  // 画面の上にはみ出てるので下にスクロールセット
  if(basey > cursory){
    wk->target = cursory * FX32_ONE;
  }
  // 画面の下にはみ出ているので上にスクロールセット
  if(basey + HW_LCD_HEIGHT <= cursory){
    wk->target = ((cursory + height) - HW_LCD_HEIGHT) * FX32_ONE;
  }
}


//------------------------------------------------------------------
/**
 * @brief	上下カーソルの表示／非表示処理
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetCursorVisible(STARTMENU_WORK *wk)
{
  int i, du, dd;
  int cursory, height, basey;

  du = dd = FALSE;

  // 現在のスクロール値(目的座標)
  basey = wk->target / FX32_ONE;

  for(i = 0; i < MENU_WIN_MAX; i++){
    if(GF_BGL_BmpWinAddCheck(&wk->mwin[i]) == FALSE)
      continue;

    // ドット換算のカーソル位置を算出
    cursory = (GF_BGL_BmpWinGet_PosY(&wk->mwin[i] ) - 1) * 8;
    height = (GF_BGL_BmpWinGet_SizeY(&wk->mwin[i] ) + 2) * 8;

    // 上のはみ出しチェック
    if(basey > cursory)
      du = TRUE;
    // 下のはみ出しチェック
    if(basey + HW_LCD_HEIGHT <= cursory)
      dd = TRUE;
  }

  CLACT_SetDrawFlag(wk->clcursor[0], du);
  CLACT_SetDrawFlag(wk->clcursor[1], dd);

}


//------------------------------------------------------------------
/**
 * @brief	処理の終了 メモリ開放など
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void StartMenuFinish(PROC *proc)
{
  int i;
  STARTMENU_WORK *wk = PROC_GetWork(proc);

  // アクター関連の開放
  if(wk->clcursor[0] || wk->clcursor[1]){
    CLACT_Delete(wk->clcursor[0]);
    CLACT_Delete(wk->clcursor[1]);
    MysteryLib_RemoveClact();
  }
  
  // ウィンドウ開放
  for(i = 0; i < MENU_WIN_MAX; i++){
    if(wk->mwin[i].ini){
      GF_BGL_BmpWinOff(&wk->mwin[i]);
      GF_BGL_BmpWinDel(&wk->mwin[i]);
    }
  }
  // BGL開放
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME2_M);
  sys_FreeMemoryEz(wk->bgl);
  sys_VBlankFuncChange(NULL, NULL);
}


//------------------------------------------------------------------
/**
 * @brief	選択ウィンドウのパレットアニメ
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
u16 animtable[] = {
  RGB( 1, 28, 20),  RGB( 3, 28, 20),  RGB( 5, 28, 20),  RGB( 7, 28, 20),
  RGB( 9, 28, 20),  RGB(11, 28, 20),  RGB(13, 28, 20),  RGB(15, 28, 20),
  RGB(17, 28, 20),  RGB(19, 28, 20),  RGB(21, 28, 20),  RGB(23, 28, 20),
  RGB(25, 28, 20),  RGB(27, 28, 20),  RGB(29, 28, 20),  RGB(31, 28, 20),
  RGB(29, 28, 20),  RGB(27, 28, 20),  RGB(25, 28, 20),  RGB(23, 28, 20),
  RGB(21, 28, 20),  RGB(19, 28, 20),  RGB(17, 28, 20),  RGB(15, 28, 20),
  RGB(13, 28, 20),  RGB(11, 28, 20),  RGB( 9, 28, 20),  RGB( 7, 28, 20),
  RGB( 5, 28, 20),  RGB( 3, 28, 20),
  0,
};
static void SelectPalAnim(STARTMENU_WORK *wk)
{
  u16 *col = (u16 *)0x0500006C;
  if(animtable[wk->anim_index] == 0)
    wk->anim_index = 0;
  *col = animtable[wk->anim_index++];
}

static void VBlankFunc(void *work)
{
  // セルアクターVram転送マネージャー実行
  DoVramTransferManager();
  // レンダラ共有OAMマネージャVram転送
  REND_OAMTrans();	
  GF_BGL_VBlankFunc( (GF_BGL_INI*)work );
  OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	タイトルプロセス：初期化
 * @param	proc	プロセスへのポインタ
 * @param	seq		シーケンス用ワークへのポインタ
 * @return	PROC_RES_CONTINUE	動作継続中
 * @return	PROC_RES_FINISH		動作終了
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT StartMenuProc_Init(PROC * proc, int * seq)
{
  STARTMENU_WORK *wk;

  sys_CreateHeap( HEAPID_BASE_APP, HEAPID_STARTMENU, 0x40000);
  //  sys_PrintHeapFreeSize(HEAPID_STARTMENU);
  wk = PROC_AllocWork(proc, sizeof(STARTMENU_WORK), HEAPID_STARTMENU);
  // 初期化不良が怖いのでワークはゼロクリア
  memset(wk, 0, sizeof(STARTMENU_WORK));

  /* 各種変数の初期化 */
  wk->bgl = GF_BGL_BglIniAlloc(HEAPID_STARTMENU);

  /* 画面の初期設定 */
  WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
  WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

  /* 変数初期化 */
  wk->sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
  wk->fdata = SaveData_GetFushigiData(wk->sv);
  //  wk->cursor = 0;
  wk->scrolly = FX32_ONE * 0;
  wk->target  = FX32_ONE * 0;

  wk->mst = SaveData_GetMyStatus(wk->sv);
  wk->zw = SaveData_GetZukanWork(wk->sv);
  wk->ptime = SaveData_GetPlayTime(wk->sv);

  wk->zukangetflag = ZukanWork_GetZukanGetFlag(wk->zw);
  wk->badgecount = MyStatus_GetBadgeCount(wk->mst);
  wk->beacon_msg_seq = BEACON_MSGSEQ_NOP;
  
  // ライブラリ初期化
  MysteryLib_Init(HEAPID_STARTMENU);

  // セーブデータが無ければスタートメニュー自体を表示させない
  if(!SaveData_GetExistFlag(wk->sv)){
    wk->pass_start_menu = TRUE;
  }

  Snd_BgmChannelSetAndReverbSet( 0 );	// 使用可能チャンネル操作、リバーブ設定(クリア)
  Snd_SceneSet( SND_SCENE_DUMMY );		// 次のシーンが必ず読み込まれるようにしておく！

#ifdef DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("sizeof(POKEMON_PARAM) = %d\n", PokemonParam_GetWorkSize());
  OS_TPrintf("sizeof(_SEND_FLAG) = %d\n", CommPlayerNowFlagDataArraySize());
  OS_TPrintf("sizeof(MYSTATUS) = %d\n", MyStatus_GetWorkSize());
#endif

#ifdef CREATE_INDEX
  CreateIndexData(HEAPID_STARTMENU);
#endif

  
  return PROC_RES_FINISH;
}



//--------------------------------------------------------------------------------------------
/**
 * @brief	タイトルプロセス：メイン
 * @param	proc	プロセスへのポインタ
 * @param	seq		シーケンス用ワークへのポインタ
 * @return	PROC_RES_CONTINUE	動作継続中
 * @return	PROC_RES_FINISH		動作終了
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT StartMenuProc_Main(PROC * proc, int * seq)
{
  int ret;
  STARTMENU_WORK *wk = PROC_GetWork(proc);
  wk->jiffy++;
  CTRDG_IsExisting();

  // ビーコン受信時のメッセージ表示シーケンス
  if(BeaconMessage_Proc(wk) == TRUE){
    StartMenuBeacon_Proc(wk);
    StartMenuProc(wk);
    return PROC_RES_CONTINUE;
  }

  // 選択されているウィンドウをパレットアニメーション
  SelectPalAnim(wk);

  switch(*seq){
  case STARTMENU_SEQ_INIT:
    // ＢＧ関係の必要最低限の初期化
    InitStartMenuScreen(wk);
    SetSeq(*seq, STARTMENU_SEQ_CHECK_SYSTEM);
    break;

  case STARTMENU_SEQ_CHECK_SYSTEM:
    // 各種システムのチェック(一気にチェック、順次表示)
    if(StartMenuCheckSystem(wk) == 0){
      SetSeq(*seq, STARTMENU_SEQ_HARDINIT);
    } else {
      MysteryLib_RequestFade(WIPE_TYPE_FADEIN, STARTMENU_SEQ_DISP_ERROR, seq, STARTMENU_SEQ_FADE_WAIT);
      *((u16 *)HW_BG_PLTT +  0) = RGB(12, 12, 31);
    }
    break;

  case STARTMENU_SEQ_DISP_ERROR:
    // エラーがあったので詳細を表示しまくり
    if(StartMenuDisplayError(wk) == FALSE)
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, STARTMENU_SEQ_HARDINIT, seq, STARTMENU_SEQ_FADE_WAIT);
    break;
    
  case STARTMENU_SEQ_HARDINIT:
    wk->beacon_seq = STARTMENU_BEACON_SEQ_WAIT;
    // セーブデータがなければゲームの最初から始める
    if(wk->pass_start_menu == TRUE){
      wk->select = SEL_FIRSTGAME;
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, STARTMENU_SEQ_SELECT_MENU, seq, STARTMENU_SEQ_FADE_WAIT);
    } else {
      // AGBカートリッジの初期化をして次のシーケンスへ
      AgbCartridgeInit(wk);
      SetSeq(*seq, STARTMENU_SEQ_CREATE_SCREEN);
    }
    break;

  case STARTMENU_SEQ_CREATE_SCREEN:
    // カーソルオブジェクトの読み込み
    StartMenuInitClact(wk);
    // ワイヤレスアイコンの読み込み
    WirelessIconInit(wk);
    sys_VBlankFuncChange(VBlankFunc, wk->bgl);

    // スクリーン作成(基本形)
    CreateStartMenu(wk);
    RedrawWindowFrame(wk, wk->cursor);
    MysteryLib_RequestFade(WIPE_TYPE_FADEIN, STARTMENU_SEQ_MAIN, seq, STARTMENU_SEQ_FADE_WAIT);
    *((u16 *)HW_BG_PLTT +  0) = RGB(12, 12, 31);
    // ビーコンの収集を開始する
    wk->beacon_seq = STARTMENU_BEACON_SEQ_INIT;
    break;

  case STARTMENU_SEQ_MAIN:
    // 決定ボタン / キャンセルボタン
    if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL)){
      if(sys.trg & PAD_BUTTON_DECIDE){
	Snd_SePlay(SEQ_SE_DP_SELECT);
	wk->select = wk->menuflag[wk->cursor];

	// AGBカセットから連れてくるを選んだ際の停止判定処理
	if(wk->select == SEL_AGBPOKEMON){
	  if(CTRDG_IsPulledOut() == TRUE)
	    CTRDG_TerminateForPulledOut();
	}
	
      } else {
	Snd_SePlay(SEQ_SE_DP_SELECT);
	wk->select = SEL_CANCEL;
	MysteryLib_ChangeFadeType(1);
      }
      if(wk->select == SEL_FIRSTGAME){
	// さいしょからはじめるを選択した場合には警告画面を表示する
	wk->beacon_status |= STARTMENU_FIRSTGAME_SELECT;
	wk->beacon_msg_wait = 1;
	SetSeq(*seq, STARTMENU_SEQ_SELECT_FIRSTGAME);
      } else {
	if(wk->select == SEL_WII)
	  MysteryLib_ChangeFadeType(1);
	MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, STARTMENU_SEQ_SELECT_MENU, seq, STARTMENU_SEQ_FADE_WAIT);
      }

      // ビーコン収集中だったら強制終了処理へ
      if(wk->beacon_seq == STARTMENU_BEACON_SEQ_TIMER)
	wk->beacon_seq = STARTMENU_BEACON_SEQ_CANCEL;
      break;
    }
    
    // 再描画の必要があれば再描画する
    if(wk->redrawflag == TRUE){
      CreateStartMenu(wk);
      wk->redrawflag = FALSE;
      break;
    }

    // カーソル移動
    if(sys.trg & PAD_KEY_UP)
      NextCursorPosition(wk, -1);
    if(sys.trg & PAD_KEY_DOWN)
      NextCursorPosition(wk,  1);
    // スクリーン書き換え
    RedrawWindowFrame(wk, wk->cursor);
    // スクロール処理
    SetCursorScroll(wk);
    // 上下カーソルの表示処理
    SetCursorVisible(wk);

    // リスクエストが出ていればポップアップメニューの登録
    if(*seq == STARTMENU_SEQ_MAIN && wk->req_popup == TRUE){
      wk->req_popup = FALSE;
      wk->beacon_msg_wait = 1;
    }
    
    break;

  case STARTMENU_SEQ_SELECT_FIRSTGAME:
    // さいしょからはじめるを選んだ時は警告を表示
    if(wk->beacon_msg_seq == BEACON_MSGSEQ_NOP){
      if(wk->beacon_result & PAD_BUTTON_CANCEL){
	SetSeq(*seq, STARTMENU_SEQ_MAIN);
      } else {
	MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, STARTMENU_SEQ_SELECT_MENU, seq, STARTMENU_SEQ_FADE_WAIT);
      }
    }
    break;

    
  case STARTMENU_SEQ_SELECT_MENU:
    // メモリ群を開放
    StartMenuFinish(proc);
    return PROC_RES_FINISH;
    break;

    
  case STARTMENU_SEQ_FADE_WAIT:
    // フェードが終了するまで待って次のシーケンスへ
    MysteryLib_FadeEndCheck(seq);
    break;

  case STARTMENU_SEQ_FINISH:
    return PROC_RES_FINISH;
    break;
  }

  StartMenuBeacon_Proc(wk);
  StartMenuProc(wk);
  MysteryLib_DoClact();
  
  return PROC_RES_CONTINUE;
}



//------------------------------------------------------------------
/**
 * @brief	選択されたメニューによって処理分岐
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#include "system/gamestart.h"
#include "demo/title.h"
FS_EXTERN_OVERLAY( title );
#define CHECK_OVERLAY
#ifdef CHECK_OVERLAY
FS_EXTERN_OVERLAY( startmenu );
#endif
extern const PROC_DATA MysteryGiftProcData;
extern const PROC_DATA AgbCartridgeProcData;
extern const PROC_DATA PokemonRangerProcData;
extern const PROC_DATA StartMenuWifiProcData;

static void StartMenuSetNextProc(STARTMENU_WORK *wk)
{
  switch(wk->select){
  case SEL_CONTINUE:	// つづきから　はじめる
    Main_SetNextProc(OVERLAY_ID_GAMESTART, &ContinueGameStartProcData);
    break;
  case SEL_FIRSTGAME:	// さいしょから　はじめる
    Main_SetNextProc(OVERLAY_ID_GAMESTART, &NewGameStartProcData);
    break;
  case SEL_MYSTERY:	// ふしぎな　おくりもの
#ifdef CHECK_OVERLAY
    Main_SetNextProc(FS_OVERLAY_ID(startmenu), &MysteryGiftProcData);
#else
    Main_SetNextProc(NO_OVERLAY_ID, &MysteryGiftProcData);
#endif
    break;
  case SEL_AGBPOKEMON:	// ×××から　つれてくる
#ifdef CHECK_OVERLAY
    Main_SetNextProc(FS_OVERLAY_ID(startmenu), &AgbCartridgeProcData);
#else
    Main_SetNextProc(NO_OVERLAY_ID, &AgbCartridgeProcData);
#endif
    break;
  case SEL_RANGER:	// ポケモンレンジャーとの　せつぞく
#ifdef CHECK_OVERLAY
    Main_SetNextProc(FS_OVERLAY_ID(startmenu), &PokemonRangerProcData);
#else
    Main_SetNextProc(OVERLAY_ID_GAMESTART, &PokemonRangerProcData);
#endif
    break;
  case SEL_WII:		// Wiiと　せつぞく
    rebooter(WIICLIENT_FILE);
    break;  case SEL_WIFI:	// Wi-Fiせってい
    Snd_Stop();
    Main_SetNextProc(NO_OVERLAY_ID, &StartMenuWifiProcData);
    break;
  case SEL_CANCEL:	// キャンセル
    Main_SetNextProc( FS_OVERLAY_ID(title), &TitleProcData);
    break;
  }
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	タイトルプロセス：終了
 * @param	proc	プロセスへのポインタ
 * @param	seq		シーケンス用ワークへのポインタ
 * @return	PROC_RES_CONTINUE	動作継続中
 * @return	PROC_RES_FINISH		動作終了
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT StartMenuProc_End(PROC * proc, int * seq)
{
  STARTMENU_WORK *wk = PROC_GetWork(proc);

  StartMenuSetNextProc(wk);

  PROC_FreeWork(proc);
  sys_DeleteHeap(HEAPID_STARTMENU);

  /* AGBカートリッジの抜け検出OFF */
  MysteryLib_SetAgbCartridgeIntr(FALSE);

  return PROC_RES_FINISH;
}


//--------------------------------------------------------------------------------------------
// この定義はsrc/demo/title.cから参照されます
//--------------------------------------------------------------------------------------------
//FS_EXTERN_OVERLAY(startmenu);
const PROC_DATA StartMenuProcData = {
  StartMenuProc_Init,
  StartMenuProc_Main,
  StartMenuProc_End,
  NO_OVERLAY_ID,
};



/*  */
