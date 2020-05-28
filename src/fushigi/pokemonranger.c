//============================================================================================
/**
 * @file	pokemonranger.c	
 * @bfief	ポケモンレンジャーとの接続画面/たまご転送
 * @author	Satoshi Mitsuhara
 * @date	06.04.27
 *
 * $Id: pokemonranger.c,v 1.21 2006/08/01 14:41:26 mitsuhara Exp $
 */
//============================================================================================

// BG0		メニューやメッセージ表示
// BG1		格子模様の背景

#include "common.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/arc_util.h"
#include "system/wipe.h"
#include "system/render_oam.h"
#include "system/pm_rtc.h"
#include "system/snd_tool.h"
#include "system/window.h"
#include "system/msgdata_util.h"

#include "savedata/zukanwork.h"
#include "savedata/config.h"
#include "savedata/savedata.h"
#include "savedata/fushigi_data.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_startmenu.h"
#include "msgdata/msg_bconfind.h"
#include "msgdata/msg_mystery.h"
#include "strbuf_family.h"	//for STRBUF_SetStringCode 今だけ

#include "demo/title.h"
#include "field/field.h"

#include "system/main.h"
#include "system/brightness.h"

#include "communication/communication.h"
#include "communication/comm_system.h"
#include "communication/comm_mp.h"
#include "communication/mpconnect.h"
#include "communication/mpdata.h"

#include "system/startmenu.h"
#include "poketool/monsno.h"

#include "mysterylib.h"
#include "mystery.naix"


#include "pokemonrangerdata.h"

//============================================================================================
/**
 * ↓ポケモンレンジャーとの接続画面用ワーク定義↓
 */
//============================================================================================

#define POKEMONRANGER_WCOL_NORMAL	0
#define POKEMONRANGER_FCOL		1
#define POKEMONRANGER_TWCOL		2

#define POKEMONRANGER_FCHR		1			// 通常フレーム
#define POKEMONRANGER_TWCHR		(POKEMONRANGER_FCHR + MENU_WIN_CGX_SIZ)
#define POKEMONRANGER_WCHR		(POKEMONRANGER_TWCHR + TALK_WIN_CGX_SIZ)



typedef struct {
  int heapid;
  GF_BGL_INI * bgl;
  SAVEDATA *sv;
  ZUKAN_WORK *zw;
  MYSTATUS *mst;
  CONFIG *cfg;

  GF_BGL_BMPWIN	ewin;
  GF_BGL_BMPWIN	twin;		// TalkWin用のビットマップ管理構造体
  GF_BGL_BMPWIN	swin;		// ステータス表示用ビットマップ管理構造体

  MYSTERY_WIN talkwin;		// TalkWint登録用
  MYSTERY_WIN titlewin;		// タイトル表示ウィンドウ
  MYSTERY_WIN statwin;		// ステータス表示用ウィンドウ

  int chrbase;
  int commvramload;		// イクニューモンが存在する時にTRUE

  
  int beacon_seq;		// ビーコン取得シーケンス
  int beacon_ret;		// 上記のリターン値
  
  int beacon_check_time;	// ビーコンをチェックする時間
  int doproc;			// true = MpProc駆動
  int seq;			// 駆動シーケンス
  int mp_time_out;		// タイムアウトまでのカウント
  int connect_num;		// コネクション番号
  int disable;			// true = 通信中断要求フラグ
  u8 mp_buf[12*1024];		// MP通信駆動用ワークエリア(実際には約10KB必要)
  PROC *proc;			// proc

  //  MYSTERY_CLACT act;
  CLACT_WORK_PTR arrow;
  
  FUSHIGI_DATA *fdata;		// セーブ用のふしぎデータをロードした場所
  LOAD_RESULT result;		// 上記データのロード状況

  int warning_msg;		// 警告画面時のメッセージID

  GIFT_CARD gc;			// カードを表示するために必要

  void *time_icon;		// タイムアイコン用
  
} POKEMONRANGER_WORK;


// CheckPokemonRangerBeacon関数が返す値
enum {
  POKEMONRANGER_RET_NONE,	// 何もイベントは無い
  POKEMONRANGER_RET_FOUNDRANGER,// レンジャーを見つけた！
  POKEMONRANGER_RET_DISCONNECT,	// 通信が切れた
  POKEMONRANGER_RET_TIMEOUT,	// タイムアウト
  POKEMONRANGER_RET_SUCCESS,	// たまご通信成功
  POKEMONRANGER_RET_CANCEL,	// ユーザーからのキャンセル
  POKEMONRANGER_RET_MAX
};

#define POKEMONRANGER_CHECK_BEACON_TIME		(60)


#if 0
char *vtable[] = {
  "POKEMONRANGER_COMM_INIT",
  "POKEMONRANGER_COMM_IDLE",
  "POKEMONRANGER_COMM_CHECK_PARENT_INIT",
  "POKEMONRANGER_COMM_CHECK_PARENT",
  "POKEMONRANGER_COMM_CONNECT_WAIT_PARENT",
  "POKEMONRANGER_COMM_CREATE_SCREEN",
  "POKEMONRANGER_COMM_WAIT_FADE_CREATE_SCREEN",
  "POKEMONRANGER_COMM_CONNECT_WAIT2_PARENT",
  "POKEMONRANGER_COMM_SELECT_WAIT_PARENT",
  "POKEMONRANGER_COMM_FIND_PARENT",
  "POKEMONRANGER_COMM_SEND_USERDATA_WAIT",
  "POKEMONRANGER_COMM_RECV_PARENT_INIT",
  "POKEMONRANGER_COMM_RECV_PARENT",
  "POKEMONRANGER_COMM_RECV_SUCCESS",
  "POKEMONRANGER_COMM_SAVE_WAIT",
  "POKEMONRANGER_COMM_SAVE_DUMMY_WAIT",
  "POKEMONRANGER_COMM_SAVE_SYNC",
  "POKEMONRANGER_COMM_SAVE_SYNC_WAIT",
  "POKEMONRANGER_COMM_SAVE_SYNC_END",
  "POKEMONRANGER_COMM_RECV_END_WAIT",
  "POKEMONRANGER_COMM_RECV_END",
  "POKEMONRANGER_COMM_NOTFIND_PARENT",
  "POKEMONRANGER_COMM_DISCONNECT_PARENT",
  "POKEMONRANGER_COMM_TIMEOUT",
  "POKEMONRANGER_COMM_CANSEL",
  "POKEMONRANGER_COMM_STOP",
  "POKEMONRANGER_COMM_RETURN_TITLE",
  "POKEMONRANGER_COMM_LOOP",
  "POKEMONRANGER_COMM_RESET",
};
#endif


enum {
    POKEMONRANGER_COMM_INIT,			// モード開始直後のフェード待ち
    POKEMONRANGER_COMM_IDLE,			// 通信ライブラリの準備待ち
    POKEMONRANGER_COMM_CHECK_PARENT_INIT,	// レンジャー（親機）を探すための初期化
    POKEMONRANGER_COMM_CHECK_PARENT,		// レンジャー（親機）を探す
    POKEMONRANGER_COMM_CONNECT_WAIT_PARENT,	// レンジャー（親機）の接続可能を待ち接続を要求
    POKEMONRANGER_COMM_CREATE_SCREEN,		// 新規追加　画面を作る
    POKEMONRANGER_COMM_WAIT_FADE_CREATE_SCREEN,	// 新規追加　フェードが終了するのを待つ
    POKEMONRANGER_COMM_CONNECT_WAIT2_PARENT,	// レンジャー（親機）の接続待ち
    POKEMONRANGER_COMM_SELECT_WAIT_PARENT,	// レンジャー（親機）とデータ通信するかどうかの選択
    POKEMONRANGER_COMM_FIND_PARENT,		// レンジャー（親機）に接続中 ユーザーデータ送信中
    POKEMONRANGER_COMM_SEND_USERDATA_WAIT,	// レンジャー（親機）へのユーザーデータ送信終了待ち
    POKEMONRANGER_COMM_RECV_PARENT_INIT,	// レンジャー（親機）から受信するための初期化
    POKEMONRANGER_COMM_RECV_PARENT,		// レンジャー（親機）から受信中
    POKEMONRANGER_COMM_RECV_SUCCESS,		// レンジャー（親機）からの受信成功 タマゴ情報セーブ開始
    POKEMONRANGER_COMM_SAVE_WAIT,		// タマゴ情報セーブ中
    POKEMONRANGER_COMM_SAVE_DUMMY_WAIT,		// レンジャー（親機）に同期待ち中前のダミー待ち
    POKEMONRANGER_COMM_SAVE_SYNC,		// タマゴ情報セーブ終了 レンジャー（親機）に同期待ちリクエスト
    POKEMONRANGER_COMM_SAVE_SYNC_WAIT,		// レンジャー（親機）に同期待ち中    
    POKEMONRANGER_COMM_SAVE_SYNC_END,
    POKEMONRANGER_COMM_RECV_END_WAIT,
    POKEMONRANGER_COMM_RECV_END,		// レンジャー（親機）からの受信／タマゴ情報セーブ終了
    POKEMONRANGER_COMM_NOTFIND_PARENT,		// レンジャー（親機）が見つからなかった／接続できなかった
    POKEMONRANGER_COMM_DISCONNECT_PARENT,	// レンジャー（親機）との接続解除
    POKEMONRANGER_COMM_TIMEOUT,			// レンジャーとの通信がタイムアウトした
    POKEMONRANGER_COMM_CANSEL,			// レンジャーとの通信をキャンセル
    POKEMONRANGER_COMM_STOP,			// レンジャーとの全ての通信終了
    POKEMONRANGER_COMM_RETURN_TITLE,		// 通信を終了させてタイトルへ戻る
    POKEMONRANGER_COMM_LOOP,			// 何もしない
    POKEMONRANGER_COMM_RESET,			// リセット処理

    POKEMONRANGER_COMM_END

} POKEMONRANGER_COMM;


enum {
  // メインシーケンス
  POKEMONRANGER_SEQ_INIT,			// 一番最初の初期設定
  POKEMONRANGER_SEQ_DISP_ERROR,			// 起動にエラーがあれば表示して終了
  POKEMONRANGER_SEQ_INIT_SCREEN,		// 最初の画面を表示
  POKEMONRANGER_SEQ_FULL_WARNING,		// 警告画面表示

  POKEMONRANGER_SEQ_MAIN,
  POKEMONRANGER_SEQ_DISP_CARD_INIT,
  POKEMONRANGER_SEQ_DISP_CARD,


  // ビーコン検索シーケンス
  POKEMONRANGER_SEQ_BEACON_INIT,		// 転送に必要なデータの初期化
  POKEMONRANGER_SEQ_BEACON_FIND,		// ビーコンを探して接続
  POKEMONRANGER_SEQ_BEACON_WAIT,		// 何もしない
  POKEMONRANGER_SEQ_BEACON_MAIN,		// データの受信その他処理


  POKEMONRANGER_SEQ_RESET,			// ソフトウェアリセット
  POKEMONRANGER_SEQ_FINISH,			// 終了してタイトル画面へ戻る
  POKEMONRANGER_SEQ_FADE_WAIT,
  
  POKEMONRANGER_SEQ_END
} POKEMONRANGER_SEQ;


#define POKEMONDP_CONNECT_ID		21
#define POKEMONRANGER_CONNECT_CH	1


#define POKEMONRANGER_FRAMECHR1	1
#define POKEMONRANGER_FRAMECHR2	(POKEMONRANGER_FRAMECHR1+9)
#define POKEMONRANGER_WINDOWCHR	(POKEMONRANGER_FRAMECHR2+9)
#define WAKU_PALETTE_NUMBER1	2
#define WAKU_PALETTE_NUMBER2	3
#define	FONT_PAL_NO_N		( 0 )	// ノーマルパレット
#define	FONT_PAL_NO_S		( 1 )	// 選択時パレット
#define	POKEMONRANGER_BLACK	(GF_PRINTCOLOR_MAKE(1, 2, 15))
#define	POKEMONRANGER_WHITE	(GF_PRINTCOLOR_MAKE(15, 2, 0))

#define RGB(r, g, b)	(((b)&31)<<10|((g)&31)<<5|((r)&31))


static void StartMenu_RangerScreenInit(PROC * proc);
static void PokemonRangerInitSubScreen(POKEMONRANGER_WORK *wk);
static void DisplaySequence(PROC *proc, u32 msgid);
static void PokemonRanger_ScreenFinish(PROC *proc);

extern int CheckPokemonRangerBeacon(POKEMONRANGER_WORK *wk);
extern int DisablePokemonRangerBeacon(POKEMONRANGER_WORK *wk);

extern void StartMenu_BgInit(PROC * proc);

extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);
extern void MysteryCard_DisplayCardOnly(GF_BGL_INI *bgl, void *, int heapid);



// ユーザー名
static u16 ModeDptestName[PERSON_NAME_SIZE+EOM_SIZE] = { 0 };
// ユーザーＩＤ
static u16 ModeDptestUserId[10] = { 0 };

// 受信データバッファ
static u8 ModeDptestRecvData[42] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, };

// MP通信用デスクリプタ
static MpInitDesc init_desc = {
  22, 1, OS_LANGUAGE_JAPANESE, POKEMONDP_CONNECT_ID, ModeDptestUserId, ModeDptestName,
};


//------------------------------------------------------------------
/**
 * @brief	セルアクター駆動用のVBlankFunc
 */
//------------------------------------------------------------------
static void VBlankFunc( void * work )
{
  // セルアクターVram転送マネージャー実行
  DoVramTransferManager();
  // レンダラ共有OAMマネージャVram転送
  REND_OAMTrans();	
  OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}

//------------------------------------------------------------------
/**
 * @brief	通信に必要なデータの初期化
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void PokemonRangerInitConnectData(POKEMONRANGER_WORK *wk)
{
  int i;
  u32 code;
  const STRCODE *datap;

  // ユーザー名をRANGER-CODEへ変換して格納
  datap = MyStatus_GetMyName( wk->mst );
  for(i = 0; i < PERSON_NAME_SIZE+EOM_SIZE; i++)
    ModeDptestName[i] = ConvDP2Ranger(datap[i]);

  // ユーザーIDを文字列へ変換して格納
  code = MyStatus_GetID_Low(wk->mst);
  ConvDPDec2RangerDec(&ModeDptestUserId[0], code);
  ModeDptestUserId[5] = ranger_EOM_;
}


//------------------------------------------------------------------
/**
 * @brief	ＢＧ初期化
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void PokemonRangerInitScreen(POKEMONRANGER_WORK *wk)
{
  int type;

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
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME0_M, GF_BGL_SCRSIZ_256x256, 0xF000, 0x0000); /* MAIN DISP BG0 */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME1_M, GF_BGL_SCRSIZ_256x256, 0xF800, 0x4000); /* MAIN DISP BG1 */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME0_S, GF_BGL_SCRSIZ_256x256, 0x7800, 0x0000); /* SUB DISP BG0 */
  MysteryLib_BgInitFrame(wk->bgl, GF_BGL_FRAME1_S, GF_BGL_SCRSIZ_256x256, 0x7000, 0x4000); /* SUB DISP BG1 */
  MSG_PrintInit();

  /* メッセージのフォントカラーを設定 */
  SystemFontPaletteLoad(PALTYPE_MAIN_BG, POKEMONRANGER_WCOL_NORMAL * 32, wk->heapid);

  //ウィンドウ枠キャラ、パレットをセット
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, POKEMONRANGER_FCHR,  POKEMONRANGER_FCOL,     0, wk->heapid);
  type = CONFIG_GetWindowType(wk->cfg);
  TalkWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, POKEMONRANGER_TWCHR, POKEMONRANGER_TWCOL, type, wk->heapid);

  // 格子模様を表示する
  // メイン画面ＢＧパレット転送
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_nclr, PALTYPE_MAIN_BG, 16*2*8, 16*2, wk->heapid);
  // メイン画面BG1キャラ転送
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_ccgr, wk->bgl,
		    GF_BGL_FRAME1_M, 0, 10*16*0x20, 1, wk->heapid);
  // メイン画面スクリーン１
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_cscr, wk->bgl,
		  GF_BGL_FRAME1_M, 0, 32*24*2, 1, wk->heapid);
  GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME1_M, 0, 0, 32, 24, 8);
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME1_M);
  // サブ画面の格子模様を表示
  PokemonRangerInitSubScreen(wk);
}


//------------------------------------------------------------------
/**
 * @brief	サブ画面の格子模様を表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void PokemonRangerInitSubScreen(POKEMONRANGER_WORK *wk)
{
  // サブ画面ＢＧパレット転送
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_nclr, PALTYPE_SUB_BG, 16*2*8, 16*2, wk->heapid);
  // サブ画面BG1キャラ転送
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_ccgr, wk->bgl,
		    GF_BGL_FRAME0_S, 0, 10*16*0x20, 1, wk->heapid);
  // サブ画面スクリーン０
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_cscr, wk->bgl,
		  GF_BGL_FRAME0_S, 0, 32*24*2, 1, wk->heapid);
  GF_BGL_ScrPalChange(wk->bgl, GF_BGL_FRAME0_S, 0, 0, 32, 24, 8);
  GF_BGL_LoadScreenReq(wk->bgl, GF_BGL_FRAME0_S);
}

//------------------------------------------------------------------
/**
 * @brief	ずかんを持ってない時のエラー表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static BOOL PokemonRangerNoHaveZukan(POKEMONRANGER_WORK *wk)
{
  MYSTERY_WIN mw;

  // エラー表示ウィンドウが初期化されているかどうかで判断を行おうかな
  if(GF_BGL_BmpWinAddCheck(&wk->ewin) == FALSE){
    MysteryLib_WinInit1(&mw, &wk->ewin, POKEMONRANGER_WCOL_NORMAL, NARC_msg_bconfind_dat, POKEMONRANGER_FCHR, POKEMONRANGER_FCOL);
    MysteryLib_WinInit2(&mw, 22, 16,wk->chrbase);
    MysteryLib_CreateWin(wk->bgl, &mw, 5, 4, bcon_003);
    return TRUE;
  } else {
    // エラーウィンドウの表示中
    if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
      BmpMenuWinClear(&wk->ewin, WINDOW_TRANS_ON);
      GF_BGL_BmpWinDel(&wk->ewin);
      return FALSE;
    }
  }
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	たまごの受信画面を作成
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void DisplayRangerStatus(POKEMONRANGER_WORK *wk);
static void PokemonRangerCreateScreen(POKEMONRANGER_WORK *wk)
{
  // 初期のメッセージ表示(会話ウィンドウを開く)
  MysteryLib_WinInit1(&wk->talkwin, &wk->twin,
		      POKEMONRANGER_WCOL_NORMAL, NARC_msg_mystery_dat, POKEMONRANGER_TWCHR, POKEMONRANGER_TWCOL);
  MysteryLib_WinInit2(&wk->talkwin, 27, 4, /*mystery_test_001,*/ wk->chrbase);
  MysteryLib_WinInit3(&wk->talkwin, MYSTERYLIB_WINTYPE_TALK, FONT_TALK);
  // 「ポケモンレンジャーからの　もうしこみを\nうけつけています」
  MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_005);
  wk->chrbase += MysteryLib_GetWindowChr(&wk->talkwin);

  // 画面上のタイトル表示
  MysteryLib_WinInit1(&wk->titlewin, &wk->ewin,
		      POKEMONRANGER_WCOL_NORMAL, NARC_msg_mystery_dat, POKEMONRANGER_FCHR, POKEMONRANGER_FCOL);
  MysteryLib_WinInit2(&wk->titlewin, 30, 4, /*mystery_01_012,*/ wk->chrbase);
  MysteryLib_WinInit3(&wk->titlewin, MYSTERYLIB_WINTYPE_NORMAL, FONT_TALK);
  MysteryLib_CreateWin(wk->bgl, &wk->titlewin, 1, 1, mystery_01_012);
  wk->chrbase += MysteryLib_GetWindowChr(&wk->titlewin);

  // アクター初期化
  MysteryLib_InitCPManager();
  MysteryLib_InitClactSystem();
  MysteryLib_InitClact(ARC_MYSTERY_GRA,
		       NARC_mystery_fusigi_cur_00_lz_ccgr,
		       NARC_mystery_fusigi_cur_nclr,
		       NARC_mystery_fusigi_cur_00_lz_ccer,
		       NARC_mystery_fusigi_cur_00_lz_canr,
		       GF_BGL_MAIN_DISP);
  // ↓アイコンを登録
  wk->arrow = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->arrow, HW_LCD_WIDTH/2, 76, 1);
  
  DisplayRangerStatus(wk);
}


//------------------------------------------------------------------
/**
 * @brief	レンジャーに送った情報をこちらにも表示
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void DisplayRangerStatus(POKEMONRANGER_WORK *wk)
{
  u32 high, low, width, wsize;
  u8 mac_addr[6];
  MpMACAddData mac_data;
  WORDSET *word;

  word = WORDSET_Create(wk->heapid);

  MysteryLib_WinInit1(&wk->statwin, &wk->swin,
		      POKEMONRANGER_WCOL_NORMAL, NARC_msg_mystery_dat, POKEMONRANGER_FCHR, POKEMONRANGER_FCOL);
  MysteryLib_WinInit2(&wk->statwin, 26, 4, wk->chrbase);
  MysteryLib_WinInit3(&wk->statwin, MYSTERYLIB_WINTYPE_NORMAL, FONT_TALK);
  //  wk->chrbase += MysteryLib_GetWindowChr(&wk->statwin);
  wk->statwin.word = word;

  // 名前を設定
  WORDSET_RegisterPlayerName(word, 0, wk->mst);
  // IDNo.を設定
  WORDSET_RegisterNumber(word, 1, MyStatus_GetID_Low(wk->mst), 5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  MysteryLib_CreateWin(wk->bgl, &wk->statwin, 3, 13, mystery_ranger_001);

  // 「もうしこみナンバー」表示
  wk->statwin.redrawflag = FALSE;
  MysteryLib_WinSetPos(&wk->statwin, 0, FontHeaderGet(FONT_SYSTEM, FONT_HEADER_SIZE_Y));
  MysteryLib_CreateWin(wk->bgl, &wk->statwin, -1, -1, mystery_ranger_003);
  // もうしこみナンバーを右詰で表示
  OS_GetMacAddress(mac_addr);
  mac_data = MpMACAddArrayToMACAddData(mac_addr);
  MpMACAddressToConnectCode(mac_data.u.data32, &high, &low);
  WORDSET_RegisterNumber(word, 0, high, 4, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  WORDSET_RegisterNumber(word, 1, low,  4, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  wk->statwin.rightflag = TRUE;
  MysteryLib_CreateWin(wk->bgl, &wk->statwin, -1, -1, mystery_ranger_004);
  
  WORDSET_Delete(word);
}


//------------------------------------------------------------------
/**
 * @brief	利用したメモリ等を開放
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void PokemonRangerFinish(PROC *proc)
{
  int i;
  POKEMONRANGER_WORK *wk = PROC_GetWork(proc);

  // セルアクターを削除
  MysteryLib_RemoveClact();
  
  // ウィンドウ開放
  if(GF_BGL_BmpWinAddCheck(&wk->ewin) == TRUE){
    GF_BGL_BmpWinOff(&wk->ewin); GF_BGL_BmpWinDel(&wk->ewin);
    GF_BGL_BmpWinOff(&wk->twin); GF_BGL_BmpWinDel(&wk->twin);
    GF_BGL_BmpWinOff(&wk->swin); GF_BGL_BmpWinDel(&wk->swin);
  }
  // BGL開放
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_S);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_S);
  sys_FreeMemoryEz(wk->bgl);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	シーケンス駆動に必要なワークエリア初期化
 * @param	wk	通信関係ワークへのポインタ
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT PokemonRangerProc_Init(PROC * proc, int * seq)
{
  POKEMONRANGER_WORK *wk;

  wk = MysteryLib_InitProc(proc, HEAPID_POKEMONRANGER, sizeof(POKEMONRANGER_WORK), 0x20000);
  // 各種変数の初期化
  wk->heapid = HEAPID_POKEMONRANGER;
  wk->bgl = GF_BGL_BglIniAlloc(wk->heapid);
  wk->sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
  wk->mst = SaveData_GetMyStatus(wk->sv);
  wk->zw = SaveData_GetZukanWork(wk->sv);
  wk->cfg = SaveData_GetConfig(wk->sv);
  // ライブラリ初期化
  MysteryLib_Init(wk->heapid);
  // ふしぎデータのポインタを得る
  wk->fdata = SaveData_GetFushigiData(wk->sv);
  
  // 変数初期化
  wk->beacon_seq = POKEMONRANGER_SEQ_BEACON_WAIT;
  wk->chrbase =POKEMONRANGER_WCHR;
  wk->beacon_check_time = 0;
  wk->seq = POKEMONRANGER_COMM_INIT;
  wk->doproc = FALSE;

  // 通信アイコンを表示するためのヒープ確保
  sys_CreateHeap( HEAPID_BASE_SYSTEM, HEAPID_COMMICON, 0x300 );
  
  /* サウンドデータロード */
  Snd_DataSetByScene( SND_SCENE_AGB, SEQ_PRESENT, 1 );

  return PROC_RES_FINISH;
}


//------------------------------------------------------------------
/**
 * @brief	プロセスのメイン処理
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static PROC_RESULT PokemonRangerProc_Main(PROC * proc, int * seq)
{
  POKEMONRANGER_WORK *wk = PROC_GetWork(proc);
  
  switch(*seq){
  case POKEMONRANGER_SEQ_INIT:
    PokemonRangerInitScreen(wk);
    // ずかんを持っていなければ警告を表示してタイトルへ戻る
    if(ZukanWork_GetZukanGetFlag(wk->zw) == FALSE)
      MysteryLib_RequestFade(WIPE_TYPE_FADEIN, POKEMONRANGER_SEQ_DISP_ERROR,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    else
      *seq = POKEMONRANGER_SEQ_INIT_SCREEN;
    break;

  case POKEMONRANGER_SEQ_DISP_ERROR:
    // 起動にエラーがあれば表示して終了
    if(PokemonRangerNoHaveZukan(wk) == FALSE){
      MysteryLib_ChangeFadeType(1);
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_FINISH, seq, POKEMONRANGER_SEQ_FADE_WAIT);
    }
    break;
    
  case POKEMONRANGER_SEQ_INIT_SCREEN:
    // 最初の画面を表示
    PokemonRangerCreateScreen(wk);

#if 0
    if(FUSHIGIDATA_CheckCardDataSpace(wk->fdata) == FALSE){
      // カード領域がいっぱいの場合は警告を表示して終了
      wk->talkwin.msgspd = 1;
      wk->warning_msg = MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_err_005);
      MysteryLib_RequestFade(WIPE_TYPE_FADEIN, POKEMONRANGER_SEQ_FULL_WARNING,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    } else
#endif
      if(FUSHIGIDATA_CheckDeliDataSpace(wk->fdata) == FALSE){
      // 配達員がいっぱいの場合は警告を表示して終了
      wk->talkwin.msgspd = 1;
      wk->warning_msg = MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_err_001);
      MysteryLib_RequestFade(WIPE_TYPE_FADEIN, POKEMONRANGER_SEQ_FULL_WARNING,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    } else {
      // ビーコン検索開始
      wk->beacon_seq = POKEMONRANGER_SEQ_BEACON_INIT;
      MysteryLib_RequestFade(WIPE_TYPE_FADEIN, POKEMONRANGER_SEQ_MAIN,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    }
    break;

  case POKEMONRANGER_SEQ_FULL_WARNING:
    // 警告画面表示
    if(GF_MSG_PrintEndCheck(wk->warning_msg) == 0 && sys.trg & PAD_BUTTON_DECIDE){
      MysteryLib_ChangeFadeType(1);
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_FINISH,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    }
    break;
    
  case POKEMONRANGER_SEQ_MAIN:
    // ここで通信のメイン処理を行う
    wk->beacon_ret = CheckPokemonRangerBeacon(wk);
    // 終了するか、キャンセルされるまで待つ
    if(wk->beacon_ret == POKEMONRANGER_RET_CANCEL){
      MysteryLib_ChangeFadeType(1);
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_FINISH,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    } else if(wk->beacon_ret == POKEMONRANGER_RET_SUCCESS){
#if 0
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_DISP_CARD_INIT, seq, POKEMONRANGER_SEQ_FADE_WAIT);
#else
      MysteryLib_ChangeFadeType(1);
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_FINISH,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
#endif
    }
    break;

  case POKEMONRANGER_SEQ_DISP_CARD_INIT:
    // 下画面は格子模様を復活
    PokemonRangerInitSubScreen(wk);
    GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
    // 上画面はカード情報の表示
    MysteryCard_DisplayCardOnly(wk->bgl, &wk->gc, HEAPID_POKEMONRANGER);
    MysteryLib_RequestFade(WIPE_TYPE_FADEIN, POKEMONRANGER_SEQ_DISP_CARD, seq, POKEMONRANGER_SEQ_FADE_WAIT);
    wk->gc.beacon.have_card = 0;
    break;

  case POKEMONRANGER_SEQ_DISP_CARD:
    if(sys.trg)
      MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, POKEMONRANGER_SEQ_RESET,  seq, POKEMONRANGER_SEQ_FADE_WAIT);
    break;

  case POKEMONRANGER_SEQ_RESET:
    // 改造対策等の事情によりソフトウェアリセット
    OS_ResetSystem(0); 
    break;

  case POKEMONRANGER_SEQ_FINISH:
    // 後始末してタイトルへ戻る
    PokemonRangerFinish(proc);
    return PROC_RES_FINISH;
    break;
    
  case POKEMONRANGER_SEQ_FADE_WAIT:
    // フェードが終了するまで待って次のシーケンスへ
    MysteryLib_FadeEndCheck(seq);
    break;
  }

  // アイコンを表示するために必要な駆動処理
  MysteryLib_DoClact();

  return PROC_RES_CONTINUE;
}
//#include "demo/title.h"
FS_EXTERN_OVERLAY( title );
static PROC_RESULT PokemonRangerProc_End(PROC * proc, int * seq)
{
  sys_DeleteHeap(HEAPID_COMMICON);
  Main_SetNextProc(FS_OVERLAY_ID(title), &TitleProcData);
  PROC_FreeWork(proc);
  sys_DeleteHeap(HEAPID_POKEMONRANGER);

  OS_TPrintf("終了しました\n");

  return PROC_RES_FINISH;
}


//------------------------------------------------------------------
/**
 * @brief	ポケモンレンジャーのセーブデータを作成
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CreatePokemonRangerSaveData(POKEMONRANGER_WORK *wk)
{
  RTCDate date;
  STRBUF * msg;
  WORDSET *word;
  MSGDATA_MANAGER *msgman;
#if 0
  GIFT_CARD *gc = sys_AllocMemory(wk->heapid, sizeof(GIFT_CARD));
#else
  GIFT_CARD *gc = &wk->gc;
#endif
  MI_CpuClear8(gc, sizeof(GIFT_CARD));

  msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, wk->heapid);
  word = WORDSET_Create(wk->heapid);

  // カードのデータを作成する
  gc->gift_type = MYSTERYGIFT_TYPE_RANGEREGG;	// おくりものタイプは「マナフィのたまご」
  
  // カードタイトルの設定
  msg = MSGDAT_UTIL_AllocExpandString(word, msgman, mystery_ranger_011, wk->heapid);
  STRBUF_GetStringCode((const STRBUF *)msg, gc->beacon.event_name, GIFT_DATA_CARD_TITLE_MAX);
  STRBUF_Delete(msg);

  gc->beacon.version = (			// 対象バージョン
			MysteryLib_GetCasetteCode(VERSION_DIAMOND) |
			MysteryLib_GetCasetteCode(VERSION_PEARL) |
			MysteryLib_GetCasetteCode(VERSION_DP_NEXT));
  gc->beacon.event_id = MYSTERYGIFT_MANAFIEGG;	// マナフィのたまごは１番
  gc->beacon.only_one_flag = 0;			// １度だけ配信フラグ(何度でも受け取れる)
  gc->beacon.access_point = 0;			// アクセスポイント(無効)
  gc->beacon.have_card = 1;			// カード情報を含んでいる
  gc->beacon.delivery_flag = 1;			// 配達員から受け取るものを含んでいる
  gc->beacon.groundchild_flag = 0;		// 孫配布ではない
  
  // イベントテキストの文字列の設定
  msg = MSGDAT_UTIL_AllocExpandString(word, msgman, mystery_ranger_010, wk->heapid);
  STRBUF_GetStringCode((const STRBUF *)msg, gc->event_text, GIFT_DATA_CARD_TEXT_MAX);
  STRBUF_Delete(msg);

  gc->re_deal_count = 0;			// 再配布の回数(再配布は出来ない)
  gc->pokemon_icon[0] = MONSNO_MANAFI;		// ポケモンアイコン(マナフィ)
  gc->pokemon_icon[1] = 0;			// ポケモンアイコン(なし)
  gc->pokemon_icon[2] = 0;			// ポケモンアイコン(なし)
  gc->re_dealed_count = 0;			// 配布した回数
  GF_RTC_GetDate(&date);
  gc->recv_date = RTC_ConvertDateToDay(&date);	// セーブする日付を入れる

  WORDSET_Delete(word);
  MSGMAN_Delete(msgman);
			
  // セーブ領域に登録(事前に空き領域をチェックしてるので絶対に大丈夫)
#if 0
  FUSHIGIDATA_SetCardData(wk->fdata, gc);
#else
  FUSHIGIDATA_SetDeliData(wk->fdata, &gc->gift_type, 0);
#endif
#if 1
  // ここで下画面の更新(受け取りアニメーション追加)
  GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
  MysteryLib_InitGift(wk->bgl, (GIFT_DELIVERY *)gc);
#endif
#if 0
  // 後始末
  sys_FreeMemoryEz(gc);
#endif
}


//------------------------------------------------------------------
/**
 * @brief	タイムアウト設定
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void PokemonRangerSetTimeOut(POKEMONRANGER_WORK *wk, int time)
{
  wk->mp_time_out = time;
}


//------------------------------------------------------------------
/**
 * @brief	タイムアウト、通信切断、キャンセル処理
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int PokemonRangerCheckConnect(POKEMONRANGER_WORK *wk, int *seq, int flag, u32 key)
{
  // タイムアウト処理
  if(--wk->mp_time_out == 0){
    MpRequestClose();
    *seq = POKEMONRANGER_COMM_TIMEOUT;
    return 0;
  }
  if(flag){
    // 通信切断チェック
    if(!MpIsConnect()){
      MpRequestClose();
      *seq = POKEMONRANGER_COMM_DISCONNECT_PARENT;
      return 0;
    }
  }
  // キャンセルチェック
  if(key && sys.trg & key){
    MpRequestClose();
    *seq = POKEMONRANGER_COMM_RETURN_TITLE;
    return 1;
  }
  return 0;
}



//--------------------------------------------------------------------------------------------
/**
 * ポケモンレンジャーとの通信シーケンス
 * ※この処理はsrc/system/startmenu.cから呼び出されます
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
int CheckPokemonRangerBeacon(POKEMONRANGER_WORK *wk)
{
  int num, v1;
  u16 *p1;
  int *seq = &wk->seq;

  // ライブラリの初期化が終了するまではMpProcを呼び出さない
  if(wk->doproc == TRUE){
    WirelessIconEasy_SetLevel(WM_LINK_LEVEL_3 - MpGetConnectLinkLevel());
    // メイン処理駆動
    MpProc();
    // 使用するポート番号設定
    MpSetChannel(POKEMONRANGER_CONNECT_CH);
  }

  //  MIT_PRINTF("seq = %d %s\n", *seq, vtable[*seq]);

  switch(*seq){
  case POKEMONRANGER_COMM_INIT:
    /// VRAMDにイクニューモンを入れる
    PokemonRangerInitConnectData(wk);
    CommVRAMDInitialize();
    wk->commvramload = TRUE;
    *seq = POKEMONRANGER_COMM_IDLE;
    break;

  case POKEMONRANGER_COMM_IDLE:
    /// VRAMDへイクニューモンが入るのを待つ
    if(CommIsVRAMDInitialize()){
      // 通信初期化
      MpInit(&init_desc, wk->mp_buf);
      // これ以降はMpProcを呼び出してOK
      wk->doproc = TRUE;
      // 通信アイコン表示
      WirelessIconEasy();
      *seq = POKEMONRANGER_COMM_CHECK_PARENT_INIT;
    }
    break;

  case POKEMONRANGER_COMM_CHECK_PARENT_INIT:
    // 子機として通信開始
    MpRequestScan();
    // タイムアウトは1600フレーム
    PokemonRangerSetTimeOut(wk, 1600);
    wk->time_icon = TimeWaitIconAdd(&wk->twin, POKEMONRANGER_TWCHR);
    *seq = POKEMONRANGER_COMM_CHECK_PARENT;
    break;

  case POKEMONRANGER_COMM_CHECK_PARENT:
    // 親機（レンジャー）発見待ち
    num = MpGetConnectListNum();
    if (num) {
      // ポケモンレンジャーを発見した！
      wk->connect_num = num - 1;
      // タイムアウト設定
      PokemonRangerSetTimeOut(wk, 1800);
      *seq = POKEMONRANGER_COMM_CONNECT_WAIT_PARENT;
    }
    // タイムアウト、通信切断、キャンセル処理
    PokemonRangerCheckConnect(wk, seq, 0, PAD_BUTTON_CANCEL);

    break;

    // ↓ここから接続処理
    
  case POKEMONRANGER_COMM_CONNECT_WAIT_PARENT:
    // 親機（レンジャー）の接続可能待ち
    if (MpGetConnectParentEnable(wk->connect_num)) {
      // 接続要求
      MpConnectParent(wk->connect_num);
      *seq = POKEMONRANGER_COMM_CONNECT_WAIT2_PARENT;
      wk->mp_time_out = 1800;
    }
    // タイムアウト、通信切断、キャンセル処理
    PokemonRangerCheckConnect(wk, seq, 0, PAD_BUTTON_CANCEL);
    break;

  case POKEMONRANGER_COMM_CONNECT_WAIT2_PARENT:
    // 親機（レンジャー）の接続待ち

    // タイムアウト、通信切断、キャンセル処理
    PokemonRangerCheckConnect(wk, seq, 0, PAD_BUTTON_CANCEL);

    // 接続できたらPOKEMONRANGER_COMM_SELECT_WAIT_PARENT
    if (MpIsConnect()) {
      *seq = POKEMONRANGER_COMM_SELECT_WAIT_PARENT;
    }    
    break;

  case POKEMONRANGER_COMM_SELECT_WAIT_PARENT:
    // レンジャー（親機）とデータ通信するかどうかの選択
    // ポケモンレンジャーへ接続をする
    MpSetSendRedy();
    *seq = POKEMONRANGER_COMM_FIND_PARENT;
    wk->mp_time_out = 1800;
    // タイムアウト、通信切断、キャンセル処理
    PokemonRangerCheckConnect(wk, seq, 1, PAD_BUTTON_CANCEL);
    break;

  case POKEMONRANGER_COMM_FIND_PARENT:
    // データ送信要求通信終了？
    if (MpIsSendDataEnd()) {
      // こちらのユーザーデータ送信
      MpSetSendUserData();
      *seq = POKEMONRANGER_COMM_SEND_USERDATA_WAIT;
      wk->mp_time_out = 3200;
      // 「ポケモンレンジャーの　がめんを\nタッチ　してください
      MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_test_006);
      // ↓アイコンを一時的に消す
      CLACT_SetDrawFlag(wk->arrow, 0);
      TimeWaitIconDel(wk->time_icon);
      Snd_SePlay(SEQ_SE_DP_SELECT);
      wk->time_icon = NULL;

      return POKEMONRANGER_RET_FOUNDRANGER;
    }    
    // タイムアウト、通信切断、キャンセル処理
    PokemonRangerCheckConnect(wk, seq, 1, PAD_BUTTON_CANCEL);
    break;


    // これ以降はメインシーケンスへ
    
  case POKEMONRANGER_COMM_SEND_USERDATA_WAIT:
    // 送信終了で今後はレンジャーからのデータを受け取る
    if (MpIsSendDataEnd()) {
      // 「ポケモンレンジャーの\nてんそうを　まっています」
      MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_006);
      // ↓アイコンを表示
      CLACT_SetDrawFlag(wk->arrow, 1);

      DisplayRangerStatus(wk);
      *seq = POKEMONRANGER_COMM_RECV_PARENT_INIT;
    }
    // タイムアウト、通信切断、キャンセル処理
    PokemonRangerCheckConnect(wk, seq, 1, PAD_BUTTON_CANCEL);
    break;
      
  case POKEMONRANGER_COMM_RECV_PARENT_INIT:
    // 親機（レンジャー）からのデータ受信開始
    MpSetRecvData(ModeDptestRecvData, 42, 1);
    *seq = POKEMONRANGER_COMM_RECV_PARENT;
    wk->mp_time_out = 3200;
    break;

  case POKEMONRANGER_COMM_RECV_PARENT:
    // データの受信終了まで待つ
    if (MpIsRecvDataEnd()) {
      *seq = POKEMONRANGER_COMM_RECV_SUCCESS;
      wk->mp_time_out = 60;
      // 「タマゴの　じゅしんに　せいこう　しました」
      MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_006);
    }
    // タイムアウト、通信切断、キャンセル処理
    PokemonRangerCheckConnect(wk, seq, 1, PAD_BUTTON_CANCEL);
    break;

  case POKEMONRANGER_COMM_RECV_SUCCESS:
    if(--wk->mp_time_out == 0){
      // セーブ開始
      // 「レポートを　かいています　しばらく　おまち　ください」
      MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_007);
      wk->time_icon = TimeWaitIconAdd(&wk->twin, POKEMONRANGER_TWCHR);

      // セーブデータを作成
      CreatePokemonRangerSaveData(wk);
      // セーブ処理開始
      MysteryLib_InitSaveDSCard(wk->sv);

      *seq = POKEMONRANGER_COMM_SAVE_WAIT;
    }
    break;

  case POKEMONRANGER_COMM_SAVE_WAIT:
    // セーブ終了待ち
    if(MysteryLib_SaveDSCard() == SAVE_RESULT_LAST){
      *seq = POKEMONRANGER_COMM_SAVE_DUMMY_WAIT;
      wk->mp_time_out = 6 + (OS_GetTickLo() % 54);
    }
    break;

  case POKEMONRANGER_COMM_SAVE_DUMMY_WAIT:
    // レンジャー（親機）に同期待ち中前のダミー待ち
    if (--wk->mp_time_out == 0) {
      *seq = POKEMONRANGER_COMM_SAVE_SYNC;
    }
    break;

  case POKEMONRANGER_COMM_SAVE_SYNC:
    // レンジャー（親機）に同期用データ送信開始
    // 同期のためにデータ送信
    MpSetRecvData(ModeDptestRecvData, 42, 2);
    *seq = POKEMONRANGER_COMM_SAVE_SYNC_WAIT;
    wk->mp_time_out = 1200;
    break;

  case POKEMONRANGER_COMM_SAVE_SYNC_WAIT:
    // データ送信終了で最後のセーブ
    if(MpIsRecvDataAcknowledge()) {
      // 最後の１セクタをセーブする
#if 0
      MysteryLib_SaveDSCard();
#else
      MysteryLib_DoLastSave();
#endif
      
      *seq = POKEMONRANGER_COMM_SAVE_SYNC_END;
      wk->mp_time_out = 800;
      break;
    }
    // 一定時間が経過しても通信が出来なかった
    if(--wk->mp_time_out == 0){
      MpRequestClose();
      *seq = POKEMONRANGER_COMM_TIMEOUT;
      wk->mp_time_out = 120;
    }
    // 接続が切れたら
    if (!MpIsConnect()) {
      MpRequestClose();
      *seq = POKEMONRANGER_COMM_DISCONNECT_PARENT;
      wk->mp_time_out = 120;
    }
    break;
      
  case POKEMONRANGER_COMM_SAVE_SYNC_END:
    // セーブの終了を確認しつつ、データ送信終了を待つ
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_NG){
      MpRequestClose();
      *seq = POKEMONRANGER_COMM_DISCONNECT_PARENT;
      wk->mp_time_out = 120;
    } else if(MysteryLib_GetSaveStatus() != MYSTERYLIB_SEQ_SAVE_OK){
      MysteryLib_SaveDSCard();
    } else {
      if(MpIsRecvDataEnd() || (!MpIsConnect())){
	*seq = POKEMONRANGER_COMM_RECV_END_WAIT;
	wk->mp_time_out = 1 /*120*/;
	MpRequestClose();
	break;
      }
    }
    // 一定時間が経過しても通信が出来なかった
    if(--wk->mp_time_out == 0){
      MpRequestClose();
      *seq = POKEMONRANGER_COMM_TIMEOUT;
      wk->mp_time_out = 10;
    }
      
  case POKEMONRANGER_COMM_RECV_END_WAIT:
    // レンジャー（親機）に同期待ち中
    if (--wk->mp_time_out == 0) {
      *seq = POKEMONRANGER_COMM_RECV_END;
      // 「てんそうが　しゅうりょう　しました\nＡボタンで　でんげんを　きります」
      MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_008);
      // ↓アイコンの表示を止める
      CLACT_SetDrawFlag(wk->arrow, 0);
      TimeWaitIconDel(wk->time_icon);
      Snd_SePlay(SEQ_SE_DP_SELECT);
      wk->time_icon = NULL;
    }
    break;
      
  case POKEMONRANGER_COMM_RECV_END:
    // レンジャー（親機）からの受信／タマゴ情報セーブ終了
    if (MpIsEnd()) {
      if(wk->commvramload == TRUE){
	CommVRAMDFinalize();
	WirelessIconEasyEnd(); // 通信アイコン削除
	wk->commvramload = FALSE;
      }
      if(sys.trg & PAD_BUTTON_DECIDE){
	*seq = POKEMONRANGER_COMM_LOOP;
	return POKEMONRANGER_RET_SUCCESS;
      }
    }
    break;

    
  case POKEMONRANGER_COMM_DISCONNECT_PARENT:
    // タイムアウトも通信切断も処理を同じにします
    *seq = POKEMONRANGER_COMM_TIMEOUT;
  case POKEMONRANGER_COMM_TIMEOUT:
    // レンジャーとの通信がタイムアウト
    // 「ポケモンレンジャーとの　つうしんが　せつだん　されました」
    MysteryLib_CreateWin(wk->bgl, &wk->talkwin, 2, 19, mystery_ranger_009);
    // ↓アイコンの表示を止める
    CLACT_SetDrawFlag(wk->arrow, 0);
    if(wk->time_icon)
      TimeWaitIconDel(wk->time_icon);
    wk->time_icon = NULL;
    *seq = POKEMONRANGER_COMM_RESET;
    break;

  case POKEMONRANGER_COMM_RESET:
    // 通信を終了させてリセット処理
    if (MpIsEnd()){
      if(wk->commvramload == TRUE){
	CommVRAMDFinalize();
	WirelessIconEasyEnd(); // 通信アイコン削除
	wk->commvramload = FALSE;
      }
      if(sys.trg & PAD_BUTTON_DECIDE){
	OS_ResetSystem(0); 
      }
    }      
    break;

  case POKEMONRANGER_COMM_RETURN_TITLE:
    // 通信を終了させてタイトルへ戻る
    if (MpIsEnd()){
      if(wk->commvramload == TRUE){
	CommVRAMDFinalize();
	WirelessIconEasyEnd(); // 通信アイコン削除
	wk->commvramload = FALSE;
	if(wk->time_icon)
	  TimeWaitIconDel(wk->time_icon);
	return POKEMONRANGER_RET_CANCEL;
      }
    }      
    break;

    
  case POKEMONRANGER_COMM_LOOP:
    break;
    
  }
  return POKEMONRANGER_RET_NONE;
}

#if 0
//--------------------------------------------------------------------------------------------
/**
 * ポケモンレンジャーとの通信シーケンスを終了させる
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
int DisablePokemonRangerBeacon(POKEMONRANGER_WORK *wk)
{
  if(wk->disable == TRUE){
    MpRequestClose();
    wk->disable = FALSE;
  } else {
    if (MpIsEnd()) {
      /// VRAMDのイクニューモンを捨てる
      CommVRAMDFinalize();
      wk->doproc = FALSE;
      WirelessIconEasyEnd(); // 通信アイコン削除
      return TRUE;
    }
  }
  return FALSE;
}
#endif

const PROC_DATA PokemonRangerProcData = {
  PokemonRangerProc_Init,
  PokemonRangerProc_Main,
  PokemonRangerProc_End,
  NO_OVERLAY_ID,
};



/*  */
