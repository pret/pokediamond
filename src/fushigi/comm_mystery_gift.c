//============================================================================================
/**
 * @file	comm_mystery_figt.c
 * @bfief	ふしぎな　おくりもの
 * @author	Satoshi Mitsuhara
 * @date	06.05.08
 *
 * $Id: comm_mystery_gift.c,v 1.97 2006/08/12 06:29:26 mitsuhara Exp $
 */
//============================================================================================
#include "system/main.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/arc_util.h"
#include "system/msgdata_util.h"
#include "system/snd_tool.h"
#include "system/pm_rtc.h"

#include "demo/title.h"
#include "mystery.naix"
#include "msgdata/msg.naix"
#include "msgdata/msg_mystery.h"
#include "msgdata/msg_wifi_system.h"

#include "communication/communication.h"
#include "communication/comm_state.h"
#include "../communication/wh.h"

#include "savedata/fushigi_data.h"
#include "savedata/system_data.h"
#include "savedata/config.h"

#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"

#include "comm_mystery_func.h"
#include "comm_mystery_state.h"
#include "comm_mystery_gift.h"
#include "agbdownload.h"
#include "beacondownload.h"

#include "mysterylib.h"

// 親のテスト実装
//#define PARENT_TEST


extern void STRBUF_GetStringCode( const STRBUF* strbuf, STRCODE* ary, u32 arysize );
extern void STRBUF_SetStringCodeOrderLength( STRBUF* strbuf, const STRCODE* str, u32 len );
extern FUSHIGI_DATA * SaveData_GetFushigiData(SAVEDATA * sv);
extern void MysteryCard_DisplayCardOnly(GF_BGL_INI *bgl, void *, int heapid);

// ※参考ファイル
//  src/field/comm_command_field.h       通信コマンドのコマンドラベル
//  src/field/comm_command_field.c       通信コマンドのコールバック関数テーブル
//  src/field/comm_field_state.c         通信に関連する流れの制御  
//  src/field/comm_direct_counter.c      ポケモンセンター２Fのカウンターで必要なメニューとその流れ

//============================================================================================
//	定数定義
//============================================================================================

enum {
  MYSTERYGIFT_SEQ_INIT = 0,		/* 画面関係の初期化 */
  MYSTERYGIFT_SEQ_CREATE_SCREEN,	/* 画面作成 */
  MYSTERYGIFT_SEQ_WAIT_FADE,		/* フェードを待つ処理 */
  MYSTERYGIFT_SEQ_MAIN,			/* MAIN PROC */
  
  MYSTERYGIFT_SEQ_RECV,			/* 「おくりものを　うけとる」 */
  MYSTERYGIFT_SEQ_DIRECT_YESNO,		/* ダイレクトで送る「はい／いいえ」 */

  MYSTERYGIFT_SEQ_RECV_BEACON,		/* ビーコン情報を受け取る */

  /* DS親機からのダウンロードシーケンス */
  MYSTERYGIFT_SEQ_START_CHILD,		/* 子機として通信開始 */
  MYSTERYGIFT_SEQ_RECV_YESNO_CHILD,	/* 子機：見つけたデータを受け取るか？ */
  MYSTERYGIFT_SEQ_REQEST_CHILD,		/* 子機：親に対して接続要求を出した／親待ち */
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD1,	/* 子機：親機からデータが受信されるまで待つ */
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD2,	/* 子機：受信されたデータの暗号化を解く */
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD3,	/* 子機：同期セーブ終了待ち */
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD30,
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD31,
  MYSTERYGIFT_SEQ_RECV_WAIT_CHILD4,
  MYSTERYGIFT_SEQ_SEND_RECV_REFUSAL,	/* 子機：申し込みが拒否された場合 */
  MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT,/* 子機：キャンセル処理準備 */
  MYSTERYGIFT_SEQ_SEND_RECV_CANCEL,	/* 子機：キャンセル処理 */

  /* AGBカセットからのダウンロードシーケンス */
  MYSTERYGIFT_SEQ_AGB_START_CHILD,	/* 子機として通信開始 */
  MYSTERYGIFT_SEQ_AGB_RECV_YESNO_CHILD,	/* 子機：見つけたデータを受け取るか？ */
  MYSTERYGIFT_SEQ_AGB_RECV_CHECK_CHILD,	/* 子機：受け取れるかチェック */
  MYSTERYGIFT_SEQ_AGB_REQEST_CHILD,	/* 子機：親に対して接続要求を出した／親待ち */
  MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD,	/* 子機：親機からデータが受信されるまで待つ */
  MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD2,	/* 子機：同期セーブ終了待ち */
  MYSTERYGIFT_SEQ_AGB_SEND_RECV_FLAG_CHILD,/* 子機：データを受け取った旨を親機に送信 */
  MYSTERYGIFT_SEQ_AGB_SEND_RECV_FLAG_CHILD2,
  
  /* WiFiからの取得シーケンス */
  MYSTERYGIFT_WIFI_DOWNLOAD_MAIN,	/* WiFi通信 */
  
  /* ビーコン取得シーケンス */
  MYSTERYGIFT_BEACON_SEQ_INIT,		/* ビーコン取得初期化 */
  MYSTERYGIFT_BEACON_SEQ_WAIT,		/* ビーコン取得　何もしない */
  MYSTERYGIFT_BEACON_SEQ_TIMER,		/* ビーコン取得中 */

  MYSTERYGIFT_BEACON_DOWNLOAD_YESNO,	/* ビーコンダウンロード中 */
  MYSTERYGIFT_BEACON_DOWNLOAD_WAIT_TITLE,	/* event_nameが送られてくるのを待つ */
  MYSTERYGIFT_BEACON_DOWNLOAD,		/* ビーコンダウンロード中 */
  MYSTERYGIFT_BEACON_DOWNLOAD_WAITSAVE,	/* セーブ終了を待って次の処理へ */
  MYSTERYGIFT_BEACON_DOWNLOAD_CANCEL,	/* キャンセル処理 */
  
  /* ビーコンダウンロードシーケンス */
  BEACON_STATE_INIT1,			// 初期状態(通信ライブラリ準備)
  BEACON_STATE_INIT2,			// 初期状態
  BEACON_STATE_START,			// 開始直後
  BEACON_STATE_SCANNING,		// スキャン中
  BEACON_STATE_DOWNLOAD,		// 親機発見して、ダウンロード中
  BEACON_STATE_COMPLETE,		// ダウンロード完了
  BEACON_STATE_CANCELING,		// キャンセル処理中
  BEACON_STATE_FINISH,			// ダウンロード終了
  BEACON_STATE_SUCCESS,			// ダウンロード成功
  BEACON_STATE_CRCERROR,		// ダウンロードＣＲＣエラー	
  BEACON_STATE_CANCEL,			// キャンセル終了
  BEACON_STATE_ERROR,				// エラー

  MYSTERYGIFT_ERROR_FULL,		// 配達員またはカードが一杯で受け取れない
  MYSTERYGIFT_SEQ_DISP_MSG,
  MYSTERYGIFT_SEQ_RETURN_TOPMENU,
  MYSTERYGIFT_SEQ_GROUNDCHILD_CHECK,	// 孫配布チェック
  
  MYSTERYGIFT_SEQ_RETURN,		/* タイトルのメニューに戻る */
  MYSTERYGIFT_SEQ_GO_LOOKCARD,		/* カードを見るへ飛ぶ */

  MYSTERYGIFT_SEQ_LOOP,			/* 無限ループ */
  MYSTERYGIFT_SEQ_DISP_CARD,		/* カード情報を表示する */
  MYSTERYGIFT_SEQ_FADEOUT_RESET,	/* フェードアウト→リセット */
  
#ifdef PARENT_TEST
  /* 以下、デバッグ用 */
  MYSTERYGIFT_SEQ_START_PARENT,		/* 親機：通信開始 */
  MYSTERYGIFT_SEQ_SYNC_CHILD_TIMING,	/* 親機：子機との同期を待つ */
  MYSTERYGIFT_SEQ_SYNC_CHILD_PARENT,	/* 親機：子機とのタイミングあわせ */
  MYSTERYGIFT_SEQ_SENDDATA_PARENT,	/* 親機：データ送信開始 */
#endif	// PARENT_TEST

  MYSTERYGIFT_SEQ_MAX
};



typedef struct {
  int id;
  u32 param;
} LISTDATA;


#define MYSTERYGIFT_FRAMECHR1	1
#define MYSTERYGIFT_FRAMECHR2	(MYSTERYGIFT_FRAMECHR1 + TALK_WIN_CGX_SIZ)
#define MYSTERYGIFT_WINDOWCHR	(MYSTERYGIFT_FRAMECHR2 + MENU_WIN_CGX_SIZ)
#define MYSTERYGIFT_TOPMENUCHR	(MYSTERYGIFT_WINDOWCHR + 26 * 6)
#define MYSTERYGIFT_COMMTYPECHR	(MYSTERYGIFT_TOPMENUCHR + 16 * 6)
#define MYSTERYGIFT_COMMDIRCHR	(MYSTERYGIFT_COMMTYPECHR + 17 * 8)
#define MYSTERYGIFT_UPWINCHR	(MYSTERYGIFT_COMMDIRCHR + 6 * 4)

#define	FONT_PALNO_NORMAL	0	/* ノーマルパレット */
#define	FONT_PALNO_SELECT	1	/* 選択時パレット */
#define WAKU_PALETTE_NUMBER1	2
#define WAKU_PALETTE_NUMBER2	3
#define	MYSTERYGIFT_BLACK	(GF_PRINTCOLOR_MAKE(1, 2, 15))
#define	MYSTERYGIFT_WHITE	(GF_PRINTCOLOR_MAKE(15, 2, 0))

//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static int CommParentStart(PROC *proc);
static int CommChildStart(PROC *proc);
static int CommChildRecvStart(PROC *proc);
static int CommWiFiChildStart(PROC *proc);
static int CommBeaconChildStart(PROC *proc);

static int CommDirectMenuNo(PROC *proc);
static int CommDirectCommMenuNo(PROC *proc);
static int CommDirectMenuYesNo(PROC *proc);
static int CommWiFiMenuYesNo(PROC *proc);
static int CommBeaconMenuYesNo(PROC *proc);
static int CommChildRecvBeaconStart(PROC *proc);
static int CommChildRecvBeaconCancel(PROC *proc);

static int CommTypeMenuRetire(PROC *proc);

static int TopMainMenuRecvGift(PROC *proc);
static int TopMainMenuLookCard(PROC *proc);
static int TopMainMenuRetire(PROC *proc);
static void CreateWindowMenuData(PROC *proc, LISTDATA *ld, int num, GF_BGL_BMPWIN *win, u32 msg);
static void CreateMenuWindow(PROC *proc, int base, u32 msg);

static void DisplaySequence(PROC *proc, GF_BGL_BMPWIN *win, u32 msgid);

static void MysteryGift_BeaconCancel(void);
static void MysteryGiftBeaconProc_Main(MYSTERYGIFT_WORK *wk);
static void MysteryGift_BeaconMainLoop(MYSTERYGIFT_WORK *wk);
static int MysteryGif_DisplayMessage(PROC *proc, GF_BGL_BMPWIN *win, int msgid, int seq);


//============================================================================================
//	グローバル変数
//============================================================================================
static PROC *MysteryProc;

/* トップメインメニュー用データ */
LISTDATA TopMainMenu_MenuData1[] = {
  { mystery_menu_001, (u32)TopMainMenuRecvGift },
  { mystery_menu_002, (u32)TopMainMenuLookCard },
  { mystery_menu_003, (u32)TopMainMenuRetire },
};

/* 通信方式選択メニュー用データ */
LISTDATA CommTypeMenu_MenuData[] = {
  { mystery_menu_004, (u32)CommDirectMenuYesNo },
  { mystery_menu_009, (u32)CommBeaconMenuYesNo },
  { mystery_menu_005, (u32)CommWiFiMenuYesNo },
  { mystery_menu_006, (u32)CommTypeMenuRetire },
};

/* 通信方式で「ダイレクト」を選択した時の確認メニュー */
LISTDATA CommDirectYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommChildStart },
#ifndef PARENT_TEST
  { mystery_menu_008, (u32)CommDirectMenuNo },
#else
  // デバッグ用では親機として起動する
  { mystery_menu_008, (u32)CommParentStart },
#endif
};

/* ダイレクト通信時に接続しますか「はい／いいえ」メニュー */
LISTDATA CommDirectCommYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommChildRecvStart },
  { mystery_menu_008, (u32)CommDirectCommMenuNo },
};



/* 通信方式で「WiFiつうしん」を選択した時の確認メニュー */
LISTDATA CommWiFiYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommWiFiChildStart },
  { mystery_menu_008, (u32)CommDirectMenuNo },
};
/* WiFi通信に接続しますか「はい／いいえ」メニュー */
LISTDATA CommWiFiCommYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommChildRecvStart },
  { mystery_menu_008, (u32)NULL },
};



/* 通信方式で「ブロードキャスト」を選択した時の確認メニュー */
LISTDATA CommBeaconYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommBeaconChildStart },
  { mystery_menu_008, (u32)CommDirectMenuNo },
};
/* ブロードキャスト通信時に見つけたデータを受信するか「はい／いいえ」メニュー */
LISTDATA CommBeaconCommYesNoMenu_MenuData[] = {
  { mystery_menu_007, (u32)CommChildRecvBeaconStart },
  { mystery_menu_008, (u32)CommChildRecvBeaconCancel },
};





/* 汎用メニュー構造体(中身を書き換えて再利用) */
static BMPLIST_HEADER MenuListHeader = {
  NULL,
  MysteryLib_MenuKeyMove,	 	/* カーソル移動ごとのコールバック関数 */
  NULL,				     	/* 一列表示ごとのコールバック関数 */
  NULL,					/* BMPウィンドウデータ */
  0,/* 後で埋める */			/* リスト項目数 */
  3,					/* 表示最大項目数 */
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



#define debug_printf	OS_TPrintf
static int s_state;
static int progress_time;
static void *buffer;


#ifdef PARENT_TEST
//--------------------------------------------------------------------------------------------
/**
 * @brief	通信データのでっちあげ関数
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
#include "gflib/fntsys.h"
#include "msgdata/msg_debug_mitsuhara.h"
static GIFT_COMM_PACK decchi_giftdata;
static GIFT_COMM_PACK *DecchiCreateGiftData(MYSTERYGIFT_WORK *wk)
{
  int i;
  
  GIFT_COMM_PACK *gd = &decchi_giftdata;
  // 良い子は真似しちゃダメです！
  static STRCODE title[] = { hu_, si_, gi_, na_, o_, ku_, ri_, mo_, no_, TE_, SU_, TO_, de_, su_, CR_,
			     D__, S__, spc_, BA_, bou_, ZI_, YYO_, N_, EOM_, 0 };
  static STRCODE etext[] = { hu_, na_, tu_, ki_, ba_, ni_, spc_, hu_, ru_, bi_, ta_, ka_, i_, zu_, wo_, CR_,
			     mo_, ttu_, te_, i_, ku_, to_, CR_,
			     sa_, i_, ha_, te_, no_, ko_, to_, u_, ni_, spc_, i_, ke_, ru_, zo_, gyoe_, CR_,
			     ya_, se_, i_, no_, MI_, YYU_, U_, ni_, spc_, a_, i_, ni_, i_, ko_, u_, gyoe_,  EOM_, 0 };
  static u8 pokedata[] = {
    0xA6, 0x8A, 0x4E, 0x79, 0x00, 0x00, 0x6F, 0xFD, 0x0F, 0x80, 0xCC, 0x00, 0xE1, 0x4C, 0xEA, 0x2D,
    0x94, 0x1D, 0x47, 0x82, 0xF0, 0xAE, 0x93, 0xCE, 0x7F, 0x0A, 0xE7, 0xA3, 0x67, 0xD3, 0x98, 0x2F,
    0x2B, 0x8A, 0xD9, 0x46, 0xF9, 0xE9, 0xE5, 0x53, 0xC6, 0x18, 0x72, 0xB7, 0x2C, 0x7D, 0x3B, 0x86,
    0x9D, 0x85, 0x49, 0xC1, 0xB6, 0x97, 0xBA, 0x86, 0x2E, 0xA8, 0x19, 0x01, 0x20, 0x07, 0x9D, 0x0B,
    0xFA, 0xFF, 0x89, 0x74, 0xED, 0x8C, 0x68, 0x00, 0xF7, 0x54, 0xB9, 0x92, 0xB3, 0xCF, 0xC4, 0xB8,
    0xA6, 0x84, 0x0A, 0xF3, 0x8C, 0xE3, 0x56, 0x3A, 0x03, 0xB0, 0x08, 0x03, 0x75, 0x49, 0x80, 0x19,
    0x00, 0x85, 0xEE, 0xBF, 0x3F, 0x99, 0x84, 0x21, 0xFD, 0x34, 0x71, 0x40, 0x7D, 0x11, 0x75, 0x07,
    0xA3, 0xCB, 0xAA, 0xDB, 0x1E, 0x60, 0x03, 0xEB, 0x7C, 0xE1, 0x8D, 0x23, 0x60, 0xEE, 0xAD, 0x2E,
    0xA9, 0xEC, 0xBE, 0x26, 0xA1, 0xE5, 0x78, 0x4C, 0x13, 0xF7, 0x29, 0x73, 0xBA, 0x77, 0x92, 0xCB,
    0x58, 0x20, 0x2A, 0x89, 0x06, 0xBB, 0x19, 0x60, 0xA5, 0xDF, 0xE4, 0xD5, 0x6D, 0xFE, 0xDF, 0x0B,
    0xA2, 0x0B, 0x3B, 0xC7, 0xC2, 0xBF, 0xC7, 0x17, 0xC6, 0x5F, 0xB7, 0x4B, 0xD0, 0x38, 0x52, 0x35,
    0xD1, 0xB4, 0x8D, 0x81, 0x60, 0x83, 0x4E, 0x07, 0x82, 0x66, 0x68, 0x1A, 0x8C, 0xF8, 0x38, 0xD8,
    0x70, 0xAF, 0xA3, 0x65, 0x4B, 0xC8, 0x64, 0x6C, 0x0F, 0x6B, 0xE4, 0x85, 0xA0, 0x68, 0xE1, 0x6B,
    0xBA, 0x26, 0x8C, 0x66, 0x7D, 0x34, 0xCA, 0x89, 0x7C, 0xC8, 0x14, 0xDA, 0x71, 0xF8, 0x8C, 0xB3,
    0x44, 0x9F, 0x9E, 0xF1, 0x90, 0x20, 0x51, 0x90, 0xBF, 0xA8, 0x42, 0x5A,
  };
  
  // 文字列をとってくるために初期化
  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYGIFT);
  wk->word = WORDSET_Create(HEAPID_MYSTERYGIFT);

  MI_CpuClear8(gd, sizeof(GIFT_COMM_PACK));
  // ポケモンデータをコピー(PokemonParam)
  for(i = 0; i < sizeof(pokedata); i++)
    gd->data.deli.data.pokemon.data[i] = pokedata[i];

  // それ以外のデータセット
  memcpy(gd->beacon.event_name, title, GIFT_DATA_CARD_TITLE_MAX*2);
  
  gd->beacon.version = (1 << VERSION_DIAMOND) | (1 << VERSION_PEARL) | (1 << VERSION_DP_NEXT);// 対象バージョン
  gd->beacon.only_one_flag = 0;			// １度だけ配信フラグ
  gd->beacon.access_point = 0;			// アクセスポイント(未使用)
  gd->beacon.have_card = 1;			// カード情報を含んでいるか
  gd->beacon.delivery_flag = 1;			// 配達員から受け取るものを含んでいるか

  // カード情報のでっちあげ
  gd->data.card.re_deal_count = 128; 		// 再配布の回数(0～254、255は無制限)
  gd->data.card.pokemon_icon[0] = 1;		// ポケモンアイコン３つ分
  gd->data.card.pokemon_icon[1] = 151;		// ポケモンアイコン３つ分
  gd->data.card.pokemon_icon[2] = 250;		// ポケモンアイコン３つ分

  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_POKEMON;	// ポケモン
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_POKEEGG;	// タマゴ
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_ITEM;	// どうぐ
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_RULE;	// ルール
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_GOODS;	// グッズ
  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_ACCESSORY;	// アクセサリ
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_RANGEREGG;	// マナフィーのタマゴ
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_MEMBERSCARD;	// メンバーズカード
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_LETTER;	// オーキドのてがみ
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_WHISTLE;	// てんかいのふえ
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_POKETCH;	// ポケッチ
  //  gd->data.deli.gift_type = MYSTERYGIFT_TYPE_CLEAR;	// ふしぎ領域の強制クリア


  gd->beacon.event_id = gd->data.deli.gift_type + 100;	// イベントＩＤ

  // たまご属性だったらタマゴ設定
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_POKEEGG){
    u8 tamago = 1;
    POKEMON_PARAM *pp = (POKEMON_PARAM *)gd->data.deli.data.pokemon.data;
    PokeParaPut(pp, ID_PARA_tamago_flag, &tamago);
  }

  // アイテム属性
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_ITEM){
    gd->data.deli.data.item.itemNo = 80;
  }

  // レギュレーション
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_RULE){
    REGULATION _dummycup = {
      {EOM_}, // gmmからとってくる
      80,//レベルの合計８０まで
      3,//３匹
      30,//ポケモンのレベル３０まで
      -20,//身長制限２．０ｍいか
      -20,// 体重制限２０ｋｇいか
      0,// 進化ポケモン参加できない
      0,// 特別なポケモン参加できない
      0,// 同じポケモン参加できない
      0,// 同じ道具持たせられない
      0,// 固定ダメージ技が必ず失敗
    };
    MSGDATA_MANAGER* msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_mitsuhara_dat, HEAPID_MYSTERYGIFT);
    STRBUF* pStr = MSGMAN_AllocString( msgman, msg_regulation_dummy );
    //    gd.gift_type = MYSTERYGIFT_TYPE_RULE;
    Regulation_SetCupName(&_dummycup,pStr);
    MI_CpuCopy8(&_dummycup, &gd->data.deli.data, sizeof(REGULATION));
    MSGMAN_Delete(msgman);
    STRBUF_Delete(pStr);
  }

  // グッズ
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_GOODS){
    gd->data.deli.data.goods.goodsNo = 33;
  }

  // アクセサリ
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_ACCESSORY){
    gd->data.deli.data.accessory.accType = MYSTERYGIFT_ACCTYPE_SEAL;
    gd->data.deli.data.accessory.accNo = 79;//爆発シール
  }

  // ポケッチ
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_POKETCH){
    gd->data.deli.data.poketch.id = 1; //POKETCH_APPID_STOPWATCH
  }

  // ふしぎ領域の強制クリア
  if(gd->data.deli.gift_type == MYSTERYGIFT_TYPE_CLEAR){
    gd->beacon.version  = 0xFFFFFFFF;
    gd->beacon.event_id = 0xFFFF;
  }


  
  // 出来上がったビーコンデータを本体にもコピーしておく(再配布用)
  memcpy(&gd->data.card.beacon, &gd->beacon, sizeof(GIFT_BEACON));

  // イベント名のコピー
  memcpy(gd->data.card.event_text, etext, GIFT_DATA_CARD_TEXT_MAX*2);
  // 後始末
  MSGMAN_Delete(wk->msgman);
  WORDSET_Delete(wk->word);

#ifdef DEBUG_ONLY_FOR_mituhara
  // デバッガでバイナリを出力させてAGB-ROMを作るためのアドレス表示
  OS_TPrintf("でっちあげデータ：0x%08X - 0x%08X\n", &decchi_giftdata, (u32)&decchi_giftdata + sizeof(GIFT_COMM_PACK));
  OS_TPrintf("                  %dbytes\n", sizeof(GIFT_COMM_PACK));
#endif
  
  return gd;
}
#endif	// PARENT_TEST

//------------------------------------------------------------------
/**
 * @brief	タイムアイコンのON/OFF
 * @param	flag: TRUE 表示　FALSE 非表示
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetTimeWaitIcon(MYSTERYGIFT_WORK *wk, int flag)
{
  if(flag == TRUE){
    if(wk->time_icon == NULL){
      wk->time_icon = TimeWaitIconAdd(&wk->msgwin, MYSTERYGIFT_FRAMECHR1);
#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("--- タイムアイコン: ON\n");
#endif
    }
  } else {
    if(wk->time_icon){
      TimeWaitIconDel(wk->time_icon);
#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("--- タイムアイコン: OFF\n");
#endif
    }
    wk->time_icon = NULL;
  }
}
void SetTimeWaitIconEx(MYSTERYGIFT_WORK *wk, int flag)
{
  SetTimeWaitIcon(wk, flag);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	このメニュー画面の最終後始末
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void TopMainMenuFinish(PROC *proc)
{
  int i;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  MysteryLib_RemoveClact();

  
  if(wk->bmd)		BMP_MENULIST_Delete(wk->bmd);
  if(wk->lw)		BmpListExit(wk->lw, NULL, NULL);
  GF_BGL_BmpWinOff(&wk->msgwin); GF_BGL_BmpWinDel(&wk->msgwin);
  if(GF_BGL_BmpWinAddCheck(&wk->upwin)){
    GF_BGL_BmpWinOff(&wk->upwin); GF_BGL_BmpWinDel(&wk->upwin);
  }
  for(i = 0; i < MYSTERYGIFT_WIN_MAX; i++){
    if(wk->selwin[i].ini){
      GF_BGL_BmpWinOff(&wk->selwin[i]);
      GF_BGL_BmpWinDel(&wk->selwin[i]);
    }
  }
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_M);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME0_S);
  GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_S);
  sys_FreeMemoryEz(wk->bgl);
}

// *******************************************************************************************


//** CharManager PlttManager用 **//
#define RECORD_CHAR_CONT_NUM				(20)
#define RECORD_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define RECORD_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define RECORD_PLTT_CONT_NUM				(20)


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
 * @brief	セルアクターの初期化
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void InitCellActor(MYSTERYGIFT_WORK *wk)
{
  MysteryLib_InitCPManager();
  MysteryLib_InitClactSystem();
  MysteryLib_InitClact(ARC_MYSTERY_GRA,
		       NARC_mystery_fusigi_cur_00_lz_ccgr,
		       NARC_mystery_fusigi_cur_nclr,
		       NARC_mystery_fusigi_cur_00_lz_ccer,
		       NARC_mystery_fusigi_cur_00_lz_canr,
		       GF_BGL_MAIN_DISP);
}


//------------------------------------------------------------------
/**
 * @brief	選択／やめる土台オブジェクトの登録
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void SetBaseIcon(MYSTERYGIFT_WORK *wk, int anum)
{
  if(anum != -1){
    wk->arrow = MysteryLib_MakeCLACT(GF_BGL_MAIN_DISP, wk->arrow, HW_LCD_WIDTH/2, 100, anum);
  } else {
    CLACT_SetDrawFlag(wk->arrow, 0);
  }
}



// *******************************************************************************************


#ifdef PARENT_TEST
//--------------------------------------------------------------------------------------------
/**
 * @brief	親機として通信開始
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommParentStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  SAVEDATA *sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;

  // 送るデータのでっちあげ
  GIFT_COMM_PACK *gd = DecchiCreateGiftData(wk);
  // MYSTERYGIFT_WORKへデータをセット
  memcpy(&wk->gift_data, gd, sizeof(GIFT_COMM_PACK));
  
  CommMysteryStateEnterGiftParent(wk, sv, COMM_MODE_MYSTERY);
#ifdef DEBUG_ONLY_FOR_mituhara
  OS_Printf("親として通信開始\n");
#endif
  return MYSTERYGIFT_SEQ_START_PARENT;
}
#endif	// PARENT_TEST


// *******************************************************************************************


//------------------------------------------------------------------
/**
 * @brief	ウィンドウが存在すればクリアする
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CMG_BmpMenuWinClear(GF_BGL_BMPWIN * win, u8 trans_sw)
{
  if(GF_BGL_BmpWinAddCheck(win) == TRUE)
    BmpMenuWinClear(win, trans_sw);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	子機として通信開始
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommChildStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  
  if(wk->comm_type != MYSTERYCOMM_TYPE_AGBCARTRIDGE){
    /* 「おくりもの　を　さがしています\nしばらく　おまち　ください……」 */
    DisplaySequence(proc, &wk->msgwin, mystery_01_004);
  }
  /* 「はい／いいえ」のメニューウィンドウはいったん消す */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_Printf("子として通信開始\n");
#endif
  if(wk->comm_type != MYSTERYCOMM_TYPE_AGBCARTRIDGE){
    CommMysteryStateEnterGiftChild(wk, COMM_MODE_MYSTERY);
    // タイムアウト時間を設定
    wk->timeout = MYSTERYGIFT_TIMEOUT;
    // 通信アイコン表示
    WirelessIconEasy();
    // タイムアイコン表示
    SetTimeWaitIcon(wk, TRUE);
    return MYSTERYGIFT_SEQ_START_CHILD;
  } else {
    OS_TPrintf("AGBカートリッジからの転送 \n");
    return MYSTERYGIFT_SEQ_AGB_START_CHILD;
  }
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	おくりものを受信すると確定した時の動作(子機)
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommChildRecvStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  // ダイレクト通信の場合はここでバージョン違いをチェック
  if(wk->gift_error == COMMMYSTERYFUNC_ERROR_VERSION)
    return MYSTERYGIFT_ERROR_FULL;
  
  // ホントに受け取れるかチェックを行う
  if(wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLGIFT ||	/* 配達員が一杯 */
     wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLCARD ||	/* カードが一杯 */
     wk->gift_error == COMMMYSTERYFUNC_ERROR_HAVE)		/* 一度しか受け取れない */
    return MYSTERYGIFT_ERROR_FULL;

  // 孫配布の場合はホントに受け取るの？チェックを行う
  if(wk->gift_error == COMMMYSTERYFUNC_ERROR_GROUNDCHILD){
    /* mituhara; */
    return MYSTERYGIFT_ERROR_FULL;
  }

  if(wk->comm_type == MYSTERYCOMM_TYPE_DIRECT){
    CommMysteryStateConnectGiftChild(wk->connectIndex);
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_Printf("親に対して接続要求を出しました\n");
#endif  
  }
  // 「もうしこみを　しました\nしばらく　おまちください…」
  DisplaySequence(proc, &wk->msgwin, mystery_01_007);
  /* 「はい／いいえ」のメニューウィンドウはいったん消す */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);

  // 受け取りオブジェクトの表示(Wi-Fiの場合は瞬間的にしか表示されないので、そもそも表示しない)
  if(wk->comm_type == MYSTERYCOMM_TYPE_DIRECT){
    SetBaseIcon(wk, 0);
    SetTimeWaitIcon(wk, TRUE);
  }

  // 受け取り方法が微妙に変わるため、シーケンス分岐
  if(wk->comm_type == MYSTERYCOMM_TYPE_DIRECT){
    CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE);
    return MYSTERYGIFT_SEQ_REQEST_CHILD;
  } else {
    return MYSTERYGIFT_SEQ_AGB_RECV_CHECK_CHILD;
  }
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	セーブデータをセーブ構造体にセット
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static GIFT_DELIVERY *CommSetSaveData(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  GIFT_DATA *gdata = &wk->gift_data.data;
  GIFT_BEACON *beacon = &wk->gift_data.beacon;
  GIFT_COMM_PACK *gcp;

  switch(wk->comm_type){
  case MYSTERYCOMM_TYPE_DIRECT:
    memcpy(gdata, CommGetMysteryGiftRecvBuff(0, NULL, 0), sizeof(GIFT_DATA));
    /* 受信したデータの暗号をdecode */
    MysteryLib_DecodeCryptoData(&wk->gift_data, &wk->gift_data.data, HEAPID_MYSTERYGIFT);
    break;
  case MYSTERYCOMM_TYPE_BEACON:
    gcp = (GIFT_COMM_PACK *)wk->recvbuf;
    memcpy(gdata, &gcp->data, sizeof(GIFT_DATA));
#if 0
    memcpy(beacon, &gcp->data.card.beacon, sizeof(GIFT_BEACON));
#else
    memcpy(beacon, &gcp->beacon, sizeof(GIFT_BEACON));
#endif
    break;
  }
  return &gdata->deli;
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
  MYSTERYGIFT_WORK *wk = (MYSTERYGIFT_WORK *)p;
  if(wk->save_cancel == TRUE){
    // セーブがキャンセルされた
    wk->func_hook = NULL;
  }
  ret = MysteryLib_SaveDSCard();
  if(ret == SAVE_RESULT_OK || ret == SAVE_RESULT_NG){
    Snd_SePlay(SEQ_SE_DP_SAVE);
    //    OS_TPrintf("分割セーブが終了しました\n");
    wk->func_hook = NULL;
  }
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	届いたデータをセーブ領域へ登録する
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CommChildSaveRecvData(PROC *proc)
{
  int type, ret;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  GIFT_BEACON *beacon = &wk->gift_data.beacon;
  GIFT_DATA *gdata = &wk->gift_data.data;
  SAVEDATA *sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
  FUSHIGI_DATA *fdata;

#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("カード情報:\t%d\n", beacon->have_card);
  OS_TPrintf("ポケモンアイコン:\t%3d : %3d : %3d\n",
	     gdata->card.pokemon_icon[0], gdata->card.pokemon_icon[1], gdata->card.pokemon_icon[2]);
#endif
  
  if(beacon->have_card == 0){
    type = MYSTERYGIFT_DELIVERY;
  } else {
    RTCDate date;
    type = MYSTERYGIFT_CARD;
    /* 再配布した回数をリセット */
    gdata->card.re_dealed_count = 0;	//gdata->card.re_deal_count;
    /* もしも再配布可能フラグが寝ていたら回数をリセット */
    if(beacon->re_deal_flag == FALSE)
      gdata->card.re_deal_count = 0;
    /* セーブする日付を入れる */
    GF_RTC_GetDate(&date);
    gdata->card.recv_date = RTC_ConvertDateToDay(&date);
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_Printf("%4d年%2d月%2d日 -> %08X\n", date.year, date.month, date.day, gdata->card.recv_date);
#endif
  }

  // ふしぎデータのポインタを得る
  fdata = SaveData_GetFushigiData(sv);
  // イベント番号フラグを立てる
  FUSHIGIDATA_SetEventRecvFlag(fdata, beacon->event_id);
  // セーブエリアにデータをセット
  if(type == MYSTERYGIFT_DELIVERY){
    ret = FUSHIGIDATA_SetDeliData(fdata, (const void *)gdata, 0);
  } else {
    ret = FUSHIGIDATA_SetCardData(fdata, (const void *)gdata);
  }
  // セーブシーケンスを登録
  MysteryLib_InitSaveDSCard(sv);
  wk->save_cancel = FALSE;
  wk->func_hook = SaveSequence;
}




//--------------------------------------------------------------------------------------------
// ↓ダイレクト通信で「はい／いいえ」を選択するウィンドウ

//--------------------------------------------------------------------------------------------
/**
 * @brief	ダイレクト通信中に見つかった親と接続するか「はい／いいえ」
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateDirectCommYesNoMenu(PROC *proc, int flag)
{
  int msg;
  GF_BGL_BMPWIN *win;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  if(flag == 0)	msg = mystery_01_005;
  else		msg = -1;
  
  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO];
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 23, 10, 6, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_COMMDIRCHR);
  CreateWindowMenuData(proc, CommDirectCommYesNoMenu_MenuData, NELEMS(CommDirectCommYesNoMenu_MenuData), win, msg);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
}



//--------------------------------------------------------------------------------------------
// ↓通信方法でダイレクト通信を選択した際の確認ウィンドウ

//--------------------------------------------------------------------------------------------
/**
 * @brief	ダイレクト通信しますか？で「いいえ」を選択
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommDirectMenuNo(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  /* 今のメニューウィンドウを表示させない */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
  CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
  if(wk->comm_type == MYSTERYCOMM_TYPE_DIRECT){
    SetTimeWaitIcon(wk, FALSE);	// タイムアイコン消去
  }

  WirelessIconEasyEnd();
  return TopMainMenuRecvGift(proc);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	ダイレクト通信しますか？「はい／いいえ」
 * @param	NONE
 * @return	次のシーケンス番号
 */
//--------------------------------------------------------------------------------------------
static int CommDirectMenuYesNo(PROC *proc)
{
  GF_BGL_BMPWIN *win;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  if(wk->comm_type != MYSTERYCOMM_TYPE_AGBCARTRIDGE)
    wk->comm_type = MYSTERYCOMM_TYPE_DIRECT;
  /* 今のメニューウィンドウを表示させない */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_TYPE], WINDOW_TRANS_ON);
  /* メニューをすげかえる */
  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO];
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 23, 10, 6, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_COMMDIRCHR);
  CreateWindowMenuData(proc, CommDirectYesNoMenu_MenuData, NELEMS(CommDirectYesNoMenu_MenuData), win, mystery_01_003);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  
  return MYSTERYGIFT_SEQ_DIRECT_YESNO;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	WiFiダウンロード通信しますか？「はい／いいえ」
 * @param	NONE
 * @return	次のシーケンス番号
 */
//--------------------------------------------------------------------------------------------
static int CommWiFiMenuYesNo(PROC *proc)
{
  GF_BGL_BMPWIN *win;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  wk->comm_type = MYSTERYCOMM_TYPE_WIFI;
  /* 今のメニューウィンドウを表示させない */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_TYPE], WINDOW_TRANS_ON);
  /* メニューをすげかえる */
  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO];
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 23, 10, 6, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_COMMDIRCHR);
  CreateWindowMenuData(proc, CommWiFiYesNoMenu_MenuData, NELEMS(CommWiFiYesNoMenu_MenuData), win, mystery_wifi_001);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  
  return MYSTERYGIFT_SEQ_DIRECT_YESNO;
}





//--------------------------------------------------------------------------------------------
/**
 * @brief	ブロードキャスト通信しますか？「はい／いいえ」
 * @param	NONE
 * @return	次のシーケンス番号
 */
//--------------------------------------------------------------------------------------------
static int CommBeaconMenuYesNo(PROC *proc)
{
  GF_BGL_BMPWIN *win;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  wk->comm_type = MYSTERYCOMM_TYPE_BEACON;
  /* 今のメニューウィンドウを表示させない */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_TYPE], WINDOW_TRANS_ON);
  /* メニューをすげかえる */
  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO];
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 23, 10, 6, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_COMMDIRCHR);
  CreateWindowMenuData(proc, CommBeaconYesNoMenu_MenuData, NELEMS(CommBeaconYesNoMenu_MenuData), win, mystery_broadcast_001);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  
  return MYSTERYGIFT_SEQ_DIRECT_YESNO;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	ブロードキャスト通信時に見つけたデータを受信するか「はい／いいえ」メニュー
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateBeaconCommYesNoMenu(PROC *proc)
{
  GF_BGL_BMPWIN *win;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO];
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 23, 10, 6, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_COMMDIRCHR);
  CreateWindowMenuData(proc, CommBeaconCommYesNoMenu_MenuData, NELEMS(CommBeaconCommYesNoMenu_MenuData), win, mystery_01_005);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	みつかったデータをじゅしんしますかで「いいえ」
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommDirectCommMenuNo(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  /* 今のメニューウィンドウを表示させない */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
  CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
  WirelessIconEasyEnd();
  /* ダイレクト通信の場合は通信回路を切る */
  if(wk->comm_type == MYSTERYCOMM_TYPE_DIRECT){
    CommMysteryExitGift();
  }
  return TopMainMenuRecvGift(proc);
}


//------------------------------------------------------------------
/**
 * @brief	ブロードキャスト通信開始
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int CommBeaconChildStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  
  /* 「おくりもの　を　さがしています
     　しばらく　おまち　ください……」 */
  DisplaySequence(proc, &wk->msgwin, mystery_01_004);
  /* 「はい／いいえ」のメニューウィンドウはいったん消す */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
  // タイムアイコン表示
  SetTimeWaitIcon(wk, TRUE);
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("ビーコン情報を取得する\n");
#endif
  s_state = BEACON_STATE_INIT1;
  return MYSTERYGIFT_BEACON_DOWNLOAD_WAIT_TITLE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	おくりものをビーコンから受信すると確定した時の動作
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static int CommChildRecvBeaconStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  OS_TPrintf("エラー番号は %d\n", wk->gift_error);

  
  // ホントに受け取れるかチェックを行う
  if(wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLGIFT ||	/* 配達員が一杯 */
     wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLCARD ||	/* カードが一杯 */
     wk->gift_error == COMMMYSTERYFUNC_ERROR_HAVE)		/* 一度しか受け取れない */
    return MYSTERYGIFT_ERROR_FULL;

  /* 「はい／いいえ」のメニューウィンドウはいったん消す */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);

  // 受け取りオブジェクトの表示
  SetBaseIcon(wk, 1);

  /* おくりもの　を　じゅしんちゅう　です\nでんげんを　きらないで　ください…… */
  DisplaySequence(proc, &wk->msgwin, mystery_01_008);
  return MYSTERYGIFT_BEACON_DOWNLOAD;
}


//------------------------------------------------------------------
/**
 * @brief	おくりものを受け取らないと確定したとき
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int CommChildRecvBeaconCancel(PROC *proc)
{
  if(s_state == BEACON_STATE_SCANNING || s_state == BEACON_STATE_DOWNLOAD || s_state == BEACON_STATE_ERROR){
    if(bsdown_end()){
      s_state = BEACON_STATE_CANCELING;	
    }
  }
  return MYSTERYGIFT_BEACON_DOWNLOAD_CANCEL;
}




//--------------------------------------------------------------------------------------------


//------------------------------------------------------------------
/**
 * @brief	WiFiつうしん通信開始
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int CommWiFiChildStart(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  
  /* 「おくりもの　を　さがしています
     　しばらく　おまち　ください……」 */
  DisplaySequence(proc, &wk->msgwin, mystery_01_004);
  SetTimeWaitIcon(wk, TRUE);
  /* 「はい／いいえ」のメニューウィンドウはいったん消す */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
  // タイムアイコン表示
  SetTimeWaitIcon(wk, TRUE);
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("WiFi通信を開始します\n");
#endif

  wk->wifi_dl_seq = WIFI_MYSTERYGIFT_BASE;
  wk->wifi_check_func = NULL;
  return MYSTERYGIFT_WIFI_DOWNLOAD_MAIN;
}






//--------------------------------------------------------------------------------------------
// ↓通信方法選択メニューの処理

//--------------------------------------------------------------------------------------------
/**
 * @brief	通信方式選択メニューで「もどる」を選択
 * @param	NONE
 * @return	次のシーケンス番号
 */
//--------------------------------------------------------------------------------------------
static int CommTypeMenuRetire(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  /* 今のメニューウィンドウを表示させない */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_TYPE], WINDOW_TRANS_ON);
  /* メインメニューを表示 */
  CreateMenuWindow(proc, MYSTERYGIFT_TOPMENUCHR, mystery_01_001);
  return MYSTERYGIFT_SEQ_MAIN;
}



//--------------------------------------------------------------------------------------------
// ↓トップメインメニューの処理

//--------------------------------------------------------------------------------------------
/**
 * @brief	一番最初の選択画面で「おくりものを　うけとる」を選択
 * @param	NONE
 * @return	次のシーケンス番号
 */
//--------------------------------------------------------------------------------------------
static int TopMainMenuRecvGift(PROC *proc)
{
  GF_BGL_BMPWIN *win;
  SYSTEMDATA *sysdata;
  //  LISTDATA ld[4];
  //  int width, max = 0;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  FUSHIGI_DATA *fdata = SaveData_GetFushigiData(wk->sv);

  /* ビーコン取得処理を停止 */
  if(wk->beacon_seq == MYSTERYGIFT_BEACON_SEQ_TIMER){
    wk->beacon_wait = 1;
    MysteryGiftBeaconProc_Main(wk);
  }
  
  /* 今のメニューウィンドウを表示させない */
  CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_MAIN], WINDOW_TRANS_ON);
  /* メニューをすげかえる */
  win = &wk->selwin[MYSTERYGIFT_WIN_COMM_TYPE];
#if 0
  // 状態によってメニューの項目と大きさを変化させるタイプ(変わらなくなった…)
  width = 16;
  // 最初のメニューは必須
  ld[max++] = CommTypeMenu_MenuData[0];
  // ふしぎなおくりものが開いたらフルオープンとなりました
  ld[max++] = CommTypeMenu_MenuData[1];
  ld[max++] = CommTypeMenu_MenuData[2];

  // 最後も必須
  ld[max++] = CommTypeMenu_MenuData[3];
#endif
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 15, 9, 16, 8,
		     FONT_PALNO_NORMAL, MYSTERYGIFT_COMMTYPECHR);
  CreateWindowMenuData(proc, CommTypeMenu_MenuData, 4, win, mystery_01_002);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  
  return MYSTERYGIFT_SEQ_RECV;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	一番最初の選択画面で「カードを　みる」を選択
 * @param	NONE
 * @return	次のシーケンス番号
 */
//--------------------------------------------------------------------------------------------
static int TopMainMenuLookCard(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  /* ビーコン取得処理を停止 */
  if(wk->beacon_seq == MYSTERYGIFT_BEACON_SEQ_TIMER){
    wk->beacon_wait = 1;
    MysteryGiftBeaconProc_Main(wk);
  }
  /* MYSTERYGIFT_SEQ_WAIT_FADE → MYSTERYGIFT_SEQ_WAIT_RETURN */
  MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, MYSTERYGIFT_SEQ_GO_LOOKCARD, wk->seq, MYSTERYGIFT_SEQ_WAIT_FADE);
  return -1;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	一番最初の選択画面で「やめる」を選択
 * @param	NONE
 * @return	次のシーケンス番号
 */
//--------------------------------------------------------------------------------------------
static int TopMainMenuRetire(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  /* ビーコン取得中であれば終了させる */
  if(wk->beacon_seq == MYSTERYGIFT_BEACON_SEQ_TIMER)
    wk->beacon_wait = 1;

  /* MYSTERYGIFT_SEQ_WAIT_FADE → MYSTERYGIFT_SEQ_WAIT_RETURN */
  MysteryLib_ChangeFadeType(1);
  MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, MYSTERYGIFT_SEQ_RETURN, wk->seq, MYSTERYGIFT_SEQ_WAIT_FADE);
  return -1;
}


//--------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------
/**
 * @brief	BG初期化
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInitSub(GF_BGL_INI *ini, int frame, u32 scrbase, u32 scrchar)
{
  GF_BGL_BGCNT_HEADER MBg_Data = {
    0, 0, 0x800, 0,
    GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
    GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000,
    GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
  };
  MBg_Data.screenBase = scrbase / 0x0800;
  MBg_Data.charBase = scrchar / 0x4000;
  GF_BGL_BGControlSet(ini, frame, &MBg_Data, GF_BGL_MODE_TEXT );
  GF_BGL_ScrClear(ini, frame);
}
static void BgInit( GF_BGL_INI * ini )
{
  /* BG SYSTEM */
  GF_BGL_SYS_HEADER BGsys_data = { GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D };
  GF_BGL_InitBG( &BGsys_data );
  BgInitSub(ini, GF_BGL_FRAME0_M, 0xF000, 0x0000); /* MAIN DISP BG0 */
  BgInitSub(ini, GF_BGL_FRAME1_M, 0xF800, 0x8000); /* MAIN DISP BG1 */
  BgInitSub(ini, GF_BGL_FRAME0_S, 0x3800, 0x0000); /* SUB DISP BG0 */
  BgInitSub(ini, GF_BGL_FRAME1_S, 0x7800, 0x4000); /* SUB DISP BG1 */
}


//------------------------------------------------------------------
/**
 * @brief	背景グラフィックスの登録
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CreateBgScreenSub(GF_BGL_INI * ini)
{
  // サブ画面ＢＧパレット転送
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_nclr, PALTYPE_SUB_BG, 16*2*8, 16*2, HEAPID_MYSTERYGIFT);
  // サブ画面BG1キャラ転送
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_ccgr, ini,
		    GF_BGL_FRAME1_S, 0, 10*16*0x20, 1, HEAPID_MYSTERYGIFT);
  // サブ画面スクリーン１
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_cscr, ini,
		  GF_BGL_FRAME1_S, 0, 32*24*2, 1, HEAPID_MYSTERYGIFT);
  GF_BGL_ScrPalChange(ini, GF_BGL_FRAME1_S, 0, 0, 32, 24, 8);
  GF_BGL_LoadScreenReq(ini, GF_BGL_FRAME1_S);
}

static void CreateBgScreen(GF_BGL_INI * ini)
{
  // メイン画面ＢＧパレット転送
  ArcUtil_PalSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_nclr, PALTYPE_MAIN_BG, 16*2*8, 16*2, HEAPID_MYSTERYGIFT);
  // メイン画面BG1キャラ転送
  ArcUtil_BgCharSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_ccgr, ini,
		    GF_BGL_FRAME1_M, 0, 10*16*0x20, 1, HEAPID_MYSTERYGIFT);
  // メイン画面スクリーン１
  ArcUtil_ScrnSet(ARC_MYSTERY_GRA, NARC_mystery_fusigi_bg_00_lz_cscr, ini,
		  GF_BGL_FRAME1_M, 0, 32*24*2, 1, HEAPID_MYSTERYGIFT);
  GF_BGL_ScrPalChange(ini, GF_BGL_FRAME1_M, 0, 0, 32, 24, 8);
  GF_BGL_LoadScreenReq(ini, GF_BGL_FRAME1_M);

  // ↓↓画面の格子模様
  CreateBgScreenSub(ini);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	メニューを登録する汎用関数
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateWindowMenuData(PROC *proc, LISTDATA *ld, int num, GF_BGL_BMPWIN *win, u32 msg)
{
  int i;
  BMPLIST_HEADER list_h;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  if(wk->bmd)	BMP_MENULIST_Delete(wk->bmd);
  /* メニューの文字列を登録 */
  wk->bmd = BMP_MENULIST_Create(num,HEAPID_MYSTERYGIFT);
  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYGIFT);
  for(i = 0; i < num; i++)
    BMP_MENULIST_AddArchiveString(wk->bmd, wk->msgman, ld[i].id, ld[i].param);
  MSGMAN_Delete(wk->msgman);
  /* desc作成 → 変更 → 登録 */
  list_h = MenuListHeader;
  list_h.list = wk->bmd;
  list_h.count = list_h.line = num;
  list_h.win = win;
  if(wk->lw) 	BmpListExit(wk->lw, NULL, NULL);
  wk->lw = BmpListSet( &list_h, 0, 0, HEAPID_MYSTERYGIFT);
  /* メッセージウィンドウにメッセージ表示 */
  if(msg != -1)
    DisplaySequence(proc, &wk->msgwin, msg);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	メニューを表示する
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
static void CreateMenuWindow(PROC *proc, int base, u32 msg)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  GF_BGL_BMPWIN *win;
  LISTDATA ld[4];
  int i, index = 0;
  FUSHIGI_DATA *fdata = SaveData_GetFushigiData(wk->sv);
  win = &wk->selwin[MYSTERYGIFT_WIN_MAIN];
  // 必要なメニューのみをコピー
  ld[index++] = TopMainMenu_MenuData1[0];
  if(FUSHIGIDATA_IsExistsCardAll(fdata))
    ld[index++] = TopMainMenu_MenuData1[1];
  ld[index++] = TopMainMenu_MenuData1[2];
  // ウィンドウ登録
  if(win->ini == NULL)
    GF_BGL_BmpWinAdd(wk->bgl, win, GF_BGL_FRAME0_M, 8,  7, 16, index*2, FONT_PALNO_NORMAL, base);
  // メニュー作成
  CreateWindowMenuData(proc, ld, index, win, msg);
  // ウィンドウ表示
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	ウィンドウへメッセージの表示
 * @param	proc	プロセスへのポインタ
 * @param	msgid	メッセージのID
 */
//--------------------------------------------------------------------------------------------
static void DisplaySequence(PROC *proc, GF_BGL_BMPWIN *win, u32 msgid)
{
  STRBUF * msg;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  wk->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYGIFT);
  wk->word = WORDSET_Create(HEAPID_MYSTERYGIFT);

  /*ウィンドウ枠内を塗りつぶす(透明色) */
  GF_BGL_BmpWinDataFill(win, FontHeaderGet(FONT_TALK, FONT_HEADER_B_COLOR));
  if(wk->msg)
    msg = wk->msg;
  else
    msg = MSGDAT_UTIL_AllocExpandString(wk->word, wk->msgman, msgid, HEAPID_MYSTERYGIFT);

  wk->m_id = GF_STR_PrintColor(win, FONT_TALK, msg, 0, 0, wk->msg_wait, MYSTERYGIFT_BLACK, NULL);
  if(wk->msg == NULL)
    STRBUF_Delete(msg);
  /*ウィンドウ枠描画(会話用ウィンドウを使用) */
  BmpTalkWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR1, WAKU_PALETTE_NUMBER1);
  MSGMAN_Delete(wk->msgman);
  WORDSET_Delete(wk->word);
  wk->msg_wait = MSG_NO_PUT;
}
static void DisplaySequenceDirect(PROC *proc, GF_BGL_BMPWIN *win, STRCODE *msgcode)
{
  STRBUF *msg;

  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  msg = STRBUF_Create( GIFT_DATA_CARD_TITLE_MAX+1, HEAPID_MYSTERYGIFT );
  STRBUF_SetStringCodeOrderLength(msg, msgcode, GIFT_DATA_CARD_TITLE_MAX);
  GF_BGL_BmpWinDataFill(win, FontHeaderGet(FONT_SYSTEM, FONT_HEADER_B_COLOR));
  GF_STR_PrintColor(win, FONT_SYSTEM, msg, 0, 0, MSG_NO_PUT, MYSTERYGIFT_BLACK, NULL);
  BmpMenuWinWrite(win, WINDOW_TRANS_ON, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  STRBUF_Delete(msg);
}
static BOOL DisplaySequenceEndCheck(PROC *proc)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  if(GF_MSG_PrintEndCheck(wk->m_id) == 0)
      return TRUE;
  return FALSE;
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
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
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
      func = (static int (*)(PROC *))ret;
      ret_seq = func(proc);
      if(ret_seq != -1)
	*seq = ret_seq;
    }
    break;
  }
}


//--------------------------------------------------------------------------------------------
// 以下、組み合わせしなおした関数をおく予定


//------------------------------------------------------------------
/**
 * @brief	グラフィックスデータ初期化
 */
//------------------------------------------------------------------
static BOOL MysteryGift_InitGraphicsData(PROC *proc, MYSTERYGIFT_WORK *wk)
{
  int type;

  MSG_PrintInit();
  /* メッセージのフォントカラーを設定 */
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_NORMAL * 32, HEAPID_MYSTERYGIFT);
  SystemFontPaletteLoad( PALTYPE_MAIN_BG, FONT_PALNO_SELECT * 32, HEAPID_MYSTERYGIFT);
  /*ウィンドウ枠キャラ、パレットをセット */
  type = CONFIG_GetWindowType(wk->cfg);
  TalkWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, MYSTERYGIFT_FRAMECHR1, WAKU_PALETTE_NUMBER1, type, HEAPID_MYSTERYGIFT);
  MenuWinGraphicSet(wk->bgl, GF_BGL_FRAME0_M, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2, 1, HEAPID_MYSTERYGIFT);
  /* 超ごめんなさいコード(パレット０カラー０の色をでっちあげ) */
  *((u16 *)HW_BG_PLTT) = RGB(12, 12, 31);
  /* ↓メッセージを表示するウィンドウ */
  if(!GF_BGL_BmpWinAddCheck(&wk->msgwin))
    GF_BGL_BmpWinAdd(wk->bgl, &wk->msgwin, GF_BGL_FRAME0_M, 2, 19, 27, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_WINDOWCHR);
  DisplaySequence(proc, &wk->msgwin, mystery_01_001); /* 「ふしぎな　おくりもの　へ　ようこそ！」 */
  /* メニューを表示するウィンドウ 「ふしぎな　おくりもの　へ　ようこそ！」 */
  CreateMenuWindow(proc, MYSTERYGIFT_TOPMENUCHR, mystery_01_001);
  CreateBgScreen(wk->bgl);
  return TRUE;
}


//------------------------------------------------------------------
/**
 * @brief	WiFiダウンロードメイン処理
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
extern int WifiMysteryGift_Main(PROC *proc, int *seq);
static void WiFi_MysteryGitft_Main(PROC *proc, int *seq)
{
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  switch(WifiMysteryGift_Main(proc, &wk->wifi_dl_seq)){
  case ND_RESULT_EXECUTE:		// 実行中
    break;
  case ND_RESULT_COMPLETE:		// 正常ダウンロード終了
    memcpy(&wk->gift_data, wk->filebuffer, sizeof(GIFT_COMM_PACK));
    SetTimeWaitIcon(wk, FALSE);
    wk->from_seq = MYSTERYGIFT_WIFI_DOWNLOAD_MAIN;
    *seq = MYSTERYGIFT_SEQ_AGB_START_CHILD;
    /* シーケンス変更 */
    break;
  case ND_RESULT_NOT_FOUND_FILES:	// ファイルが見つからなかった
  case ND_RESULT_DOWNLOAD_CANCEL:	// ユーザーからキャンセルされた
    SetTimeWaitIcon(wk, FALSE);
    *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT;
    break;
  case ND_RESULT_DOWNLOAD_ERROR:	// なんらかのエラーが起きた
    GF_BGL_BmpWinOff(&wk->wifiwin);
    GF_BGL_BmpWinDel(&wk->wifiwin);
    GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME0_M);
    /* メインメニューを表示 */
    Snd_SePlay(SEQ_SE_DP_SELECT);
    CreateMenuWindow(proc, MYSTERYGIFT_TOPMENUCHR, mystery_01_001);
    *seq = MYSTERYGIFT_SEQ_MAIN;
    break;
  }
}

//------------------------------------------------------------------
/**
 * @brief	Wi-Fiで通信へ復帰不可能なエラーが起きた場合の処理
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
void WifiMysteryGift_ErrorDisp(MYSTERYGIFT_WORK *wk)
{
  WORDSET *word;
  MYSTERY_WIN mw;
  int msg;

  if(wk->wifi_errmsg != -1)	msg = dwc_error_0001 + wk->wifi_errmsg;
  else				msg = dwc_error_0012;

  // OBJ画面は非表示
  GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
  // スクリーンをクリアして…
  GF_BGL_ScrClear(wk->bgl, GF_BGL_FRAME0_M);
  // エラー番号をwordへセットして
  word = WORDSET_Create(HEAPID_MYSTERYGIFT);
  WORDSET_RegisterNumber(word, 0, wk->wifi_errcode, 5, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
  // ウィンドウを作って表示
  MysteryLib_WinInit1(&mw, &wk->wifiwin, FONT_PALNO_SELECT, NARC_msg_wifi_system_dat, MYSTERYGIFT_FRAMECHR2, WAKU_PALETTE_NUMBER2);
  MysteryLib_WinInit2(&mw, 24, 16, 100);
  MysteryLib_WinInit3(&mw, MYSTERYLIB_WINTYPE_NORMAL, FONT_TALK);
  mw.word = word;
  MysteryLib_CreateWin(wk->bgl, &mw, 4, 4, msg);
  WORDSET_Delete(word);
}


//------------------------------------------------------------------
/**
 * @brief	配達員またはカードが一杯でおくりものを受け取れない
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static int MysteryGift_FullError(PROC *proc)
{
  int msg;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  if(wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLGIFT)		msg = mystery_err_001;
  else if(wk->gift_error == COMMMYSTERYFUNC_ERROR_FULLCARD)	msg = mystery_err_005;
  else if(wk->gift_error == COMMMYSTERYFUNC_ERROR_HAVE)		msg = mystery_err_002;
  else if(wk->gift_error == COMMMYSTERYFUNC_ERROR_VERSION)	msg = mystery_err_007;
  else if(wk->gift_error == COMMMYSTERYFUNC_ERROR_GROUNDCHILD){
    msg = mystery_01_010;
    return MysteryGif_DisplayMessage(proc, &wk->msgwin, msg, MYSTERYGIFT_SEQ_GROUNDCHILD_CHECK);
  }
  
  return MysteryGif_DisplayMessage(proc, &wk->msgwin, msg, MYSTERYGIFT_SEQ_RETURN_TOPMENU);
}


//------------------------------------------------------------------
/**
 * @brief	行更新付きメッセージの表示処理
 * @param	NONE
 * @return	NONE
 * ※予め wk->msg_next_seq に終了後のシーケンスを入れておく事
*/
//------------------------------------------------------------------
static int MysteryGif_DisplayMessage(PROC *proc, GF_BGL_BMPWIN *win, int msgid, int next_seq)
{
  WORDSET *word;
  MSGDATA_MANAGER *msgman;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  if(win && msgid){
    // 表示が終了するまでmsgバッファを保障せねばならない
    msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_mystery_dat, HEAPID_MYSTERYGIFT);
    word = WORDSET_Create(HEAPID_MYSTERYGIFT);
    wk->msg = MSGDAT_UTIL_AllocExpandString(word, msgman, msgid, HEAPID_MYSTERYGIFT);
    wk->msg_wait = 1;
    // 表示
    DisplaySequence(proc, win, msgid);
    wk->msg_next_seq = next_seq;
    // 使わなくなったバッファは開放
    WORDSET_Delete(word);
    MSGMAN_Delete(msgman);

  } else {
    if(GF_MSG_PrintEndCheck(wk->m_id) == 0){
      // 表示が終わったら開放
      STRBUF_Delete(wk->msg);
      wk->msg = NULL;
      wk->msg_wait = 0;
      return wk->msg_next_seq;
    }
  }
  return MYSTERYGIFT_SEQ_DISP_MSG;
}


//------------------------------------------------------------------
/**
 * @brief	エラーが起きた際に通信を切る処理
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
static void CommDisconnect(MYSTERYGIFT_WORK *wk)
{
  switch(wk->comm_type){
  case MYSTERYCOMM_TYPE_NULL:
    break;
  case MYSTERYCOMM_TYPE_DIRECT:		// ダイレクト通信
    CommMysteryExitGift();
    WirelessIconEasyEnd(); // 通信アイコン削除
    break;
  case MYSTERYCOMM_TYPE_AGBCARTRIDGE:	// ＡＧＢのカートリッジからダウンロード
    break;
  case MYSTERYCOMM_TYPE_BEACON:		// ビーコンからダウンロード
    break;
  case MYSTERYCOMM_TYPE_WIFI:		// Wi-Fiからのダウンロード
    break;
  }
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
static PROC_RESULT MysteryGiftProc_Init(PROC * proc, int * seq)
{
  MYSTERYGIFT_WORK *wk;

#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("sizeof(GIFT_BEACON)     = %3d\n", sizeof(GIFT_BEACON));
  //  OS_TPrintf("sizeof(GIFT_BEACON_CRC) = %3d\n", sizeof(GIFT_BEACON_CRC));
  OS_TPrintf("sizeof(POKEMON_PARAM)   = %3d\n", PokemonParam_GetWorkSize());
  OS_TPrintf("sizeof(GIFT_PRESENT)    = %3d\n", sizeof(GIFT_PRESENT));
#endif
  
  MysteryGiftSetProcp(proc);
  /* ワークエリアはTITLE_STARTMENUの上に作成する(抹消の順番は問題ないはず) */
  sys_CreateHeap( HEAPID_BASE_APP, HEAPID_MYSTERYGIFT, 0x30000);
  wk = PROC_AllocWork(proc, sizeof(MYSTERYGIFT_WORK), HEAPID_MYSTERYGIFT);
  /* 初期化不良が怖いのでワークはゼロクリア */
  memset(wk, 0, sizeof(MYSTERYGIFT_WORK));
  
  /* 各種変数の初期化 */
  wk->bgl = GF_BGL_BglIniAlloc(HEAPID_MYSTERYGIFT);
  GF_Disp_GX_VisibleControlInit();
  GF_Disp_GXS_VisibleControlInit();
  CommMysteryFunc_VramBankSet();
  BgInit(wk->bgl);

  /* 画面の初期設定 */
  WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
  WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

  /* サウンドデータロード */
  Snd_DataSetByScene( SND_SCENE_HUSIGI, SEQ_PRESENT, 1 );

  /* AGBからのダウンロードかどうかのフラグを設定 */
  if(GetAgbCartridgeDataSize()){
    wk->comm_type = MYSTERYCOMM_TYPE_AGBCARTRIDGE;
    sys_InitAgbCasetteVer(CasetteVersion);
    MysteryLib_SetAgbCartridgeIntr(TRUE);	/* AGBカートリッジの抜け検出ON */
  }
  /* ビーコン取得シーケンス初期化 */
  wk->beacon_seq = MYSTERYGIFT_BEACON_SEQ_WAIT;
  wk->sv = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
  wk->cfg = SaveData_GetConfig(wk->sv);

  wk->msg_wait = MSG_NO_PUT;

#if 0//def DEBUG_ONLY_FOR_mituhara
  {
    POKEMON_PARAM *pp = PokeParty_GetMemberPointer(SaveData_GetTemotiPokemon(wk->sv), 0);
    u32 adrs = (u32)pp + PokemonParam_GetWorkSize();
    OS_TPrintf("POKEMON_PARAM: %08X - %08X\n", pp, adrs);
  }
#endif
  sys_CreateHeap( HEAPID_BASE_SYSTEM, HEAPID_COMMICON, 0x300 );
  
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
static PROC_RESULT MysteryGiftProc_Main(PROC * proc, int * seq)
{
  u32 ret, value;
  GIFT_DELIVERY *deli;
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);

  CTRDG_IsExisting();

  //  OS_TPrintf("seq = %d\n", *seq);
  
  // ビーコン取得シーケンス
  if(wk->beacon_seq != MYSTERYGIFT_BEACON_SEQ_WAIT)
    MysteryGiftBeaconProc_Main(wk);
  
  switch(*seq){
  case MYSTERYGIFT_SEQ_INIT:
    /* ライブラリ初期化 */
    MysteryLib_Init(HEAPID_MYSTERYGIFT);
    wk->seq = seq;
    *seq = MYSTERYGIFT_SEQ_CREATE_SCREEN;
    break;

  case   MYSTERYGIFT_SEQ_CREATE_SCREEN:
    /* 画面作成 */
    MysteryGift_InitGraphicsData(proc, wk);
    InitCellActor(wk);
    /* フェードイン */
    MysteryLib_RequestFade(WIPE_TYPE_FADEIN, MYSTERYGIFT_SEQ_MAIN, seq, MYSTERYGIFT_SEQ_WAIT_FADE);
#if 0
    // ビーコンは拾わなくても良くなりました
    wk->beacon_seq = MYSTERYGIFT_BEACON_SEQ_INIT;
#endif
    break;

  case MYSTERYGIFT_SEQ_WAIT_FADE:
    // フェードが終了するまで待って次のシーケンスへ
    MysteryLib_FadeEndCheck(seq);
    break;

  case MYSTERYGIFT_SEQ_MAIN:
    /* トップメニューのメインループ */
    DoMenuMain(proc, seq, TopMainMenuRetire);
    break;

  case MYSTERYGIFT_SEQ_RECV:
    /* 通信方式を決定するウィンドウのメインループ */
    DoMenuMain(proc, seq, CommTypeMenuRetire);
    break;

  case MYSTERYGIFT_SEQ_DIRECT_YESNO:
    /* ダイレクトで送る「はい／いいえ」のメインループ */
    DoMenuMain(proc, seq, CommDirectMenuNo);
    break;



//--------------------------------------------------------------------------------------------

    // WiFiダウンロードの処理

  case MYSTERYGIFT_WIFI_DOWNLOAD_MAIN:
    WiFi_MysteryGitft_Main(proc, seq);
    break;


//--------------------------------------------------------------------------------------------

    // ビーコンダウンロードの処理

  case MYSTERYGIFT_BEACON_DOWNLOAD_WAIT_TITLE:
    // event_nameが送られてくるのを待つ
    MysteryGift_BeaconMainLoop(wk);
    // ビーコン情報を拾ったら以下の処理へ進む。ダウンロード処理自体は続けて行われる
    // 暗号化に伴い、全てのデータをダウンロードしてから処理するように変更
    if(s_state == BEACON_STATE_SUCCESS){
      // タイムアイコン消去
      SetTimeWaitIcon(wk, FALSE);
      // ビーコン情報を本来のワークエリアにコピー保存
      CommSetSaveData(proc);

      // 受け取ったビーコン情報のエラーを調べておく
      wk->gift_error = CommMysteryFunc_CheckGetGift(wk->sv, &wk->gift_data);
      // 受け取り許可のＲＯＭバージョンと異なっていたら受け取れない
      if(wk->gift_error == COMMMYSTERYFUNC_ERROR_VERSION){
	SetTimeWaitIcon(wk, FALSE);	// 	タイムアイコンを消去
	*seq = MYSTERYGIFT_ERROR_FULL;
      } else {

	if(!GF_BGL_BmpWinAddCheck(&wk->upwin))
	  GF_BGL_BmpWinAdd(wk->bgl, &wk->upwin, GF_BGL_FRAME0_M, 3, 2, 26, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_UPWINCHR);

	// ここで受信したタイトルを表示
	DisplaySequenceDirect(proc, &wk->upwin, bsdown_c_fileheader());
	DisplaySequence(proc, &wk->msgwin, mystery_01_005);
	/* 「はい／いいえ」メニューの作成 */
	CreateBeaconCommYesNoMenu(proc);
	*seq = MYSTERYGIFT_BEACON_DOWNLOAD_YESNO;
      }
    }
    // キャンセル処理
    if(s_state == BEACON_STATE_CANCEL || s_state == BEACON_STATE_CRCERROR){
      MysteryGift_BeaconCancel();
      *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT;
    }
    break;

  case MYSTERYGIFT_BEACON_DOWNLOAD_YESNO:
    // 「おくりものを　じゅしんしますか」「はい／いいえ」
    DoMenuMain(proc, seq, CommChildRecvBeaconCancel);
    MysteryGift_BeaconMainLoop(wk);
    break;

  case MYSTERYGIFT_BEACON_DOWNLOAD:
    // ダウンロードはすでに終わっている
    // ここで下画面の更新(受け取りアニメーション追加)
    //    SetBaseIcon(wk, -1);
    deli = CommSetSaveData(proc);
    MysteryLib_InitGift(wk->bgl, deli);
    SetTimeWaitIcon(wk, TRUE);
    /* ここでセーブしてみよう */
    CommChildSaveRecvData(proc);
    *seq = MYSTERYGIFT_BEACON_DOWNLOAD_WAITSAVE;
    break;

  case MYSTERYGIFT_BEACON_DOWNLOAD_WAITSAVE:
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_LAST)
      MysteryLib_DoLastSave();
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_OK){
      SetTimeWaitIcon(wk, FALSE);
      SetBaseIcon(wk, -1);
      Snd_SePlay( SEQ_SE_DP_UG_020 );
      /* おくりものを　うけとりました！\nフレンドリィ　ショップ　で\nはいたついん　から　うけとってね！ */
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_01_009, MYSTERYGIFT_SEQ_LOOP);

    } else if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_NG){
      SetBaseIcon(wk, -1);
      /* セーブエラーの時の処理 */
      wk->gift_data.beacon.have_card = 0;	// カード画面は表示しない
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_err_006, MYSTERYGIFT_SEQ_LOOP);
    }
    break;

    
  case MYSTERYGIFT_BEACON_DOWNLOAD_CANCEL:
    // キャンセル処理が終了するまで待ちます
    MysteryGift_BeaconMainLoop(wk);
    if(s_state == BEACON_STATE_CANCEL || s_state == BEACON_STATE_SUCCESS || s_state == BEACON_STATE_CRCERROR){
      if(s_state == BEACON_STATE_CANCEL)
	MysteryGift_BeaconCancel();
      // キャンセル処理終了
      *seq = CommDirectCommMenuNo(proc);
    }
    break;


//--------------------------------------------------------------------------------------------


#ifdef PARENT_TEST
    // あくまでもテスト用の親機です。
    // 通信をスタートさせるときはＡボタンを押してください
    // Ｂボタンを押せば何台繋がっているか知ることができます
  case MYSTERYGIFT_SEQ_START_PARENT:
    // 親機として通信開始
    if(CommIsConnect(COMM_PARENT_ID)){
      CommMPSetBeaconTempData(&wk->gift_data.beacon);
      if(sys.trg & PAD_BUTTON_CANCEL){
	Snd_SePlay(SEQ_SE_DP_SELECT);
#ifdef DEBUG_ONLY_FOR_mituhara
	OS_Printf("繋がっている子の数: %d\n", CommMysteryGetCommChild());
#endif
      }
      if(sys.trg & PAD_BUTTON_DECIDE){
	Snd_SePlay(SEQ_SE_DP_SELECT);
	//	wk->sync_wait = 1;
	CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE);
	*seq = MYSTERYGIFT_SEQ_SYNC_CHILD_TIMING;
#ifdef DEBUG_ONLY_FOR_mituhara
	OS_Printf("送信開始\n");
#endif
      }
    }
    break;

  case MYSTERYGIFT_SEQ_SYNC_CHILD_TIMING:
    if(CommIsTimingSync(MYSTERYGIFT_SYNC_CODE) == TRUE){
      *seq = MYSTERYGIFT_SEQ_SYNC_CHILD_PARENT;
    }
    break;
    
  case MYSTERYGIFT_SEQ_SYNC_CHILD_PARENT:
    //    if(--wk->sync_wait == 0){
      /* ここでデータの送信を開始(wk->gift_dataにデータを受ける) */
      MysteryLib_CreateCryptoData(&wk->gift_data, &wk->comm_data, HEAPID_MYSTERYGIFT);
      CommMysterySendGiftDataParent((const void *)&wk->comm_data, sizeof(GIFT_DATA));
      *seq = MYSTERYGIFT_SEQ_SENDDATA_PARENT;
      //    }
    break;

  case MYSTERYGIFT_SEQ_SENDDATA_PARENT:
    if(CommMysteryGiftGetRecvCheck() == TRUE){
      CommMysteryExitGift();
#ifdef DEBUG_ONLY_FOR_mituhara
      OS_Printf("通信が正常に終了しました！\n");
#endif
      *seq = MYSTERYGIFT_SEQ_LOOP;
    }
    
    break;

#endif	// PARENT_TEST



//--------------------------------------------------------------------------------------------


    


  case MYSTERYGIFT_SEQ_START_CHILD:
    //    WirelessIconEasy_SetLevel(WM_LINK_LEVEL_3 - WM_GetLinkLevel());
    /* 子機として通信開始 */
    if((wk->connectIndex = CommMysteryCheckParentBeacon(wk)) != -1){
      SetTimeWaitIcon(wk, FALSE);	// タイムアイコン消去
      // ビーコンのエラーチェックのみ行う
      // 子機の場合は、受け取りバージョンが違っていたらエラーを表示するようにした
      wk->gift_error = CommMysteryFunc_CheckGetGift(wk->sv, &wk->gift_data);
      // ビーコン内に埋め込まれているタイトルを表示する
      if(!GF_BGL_BmpWinAddCheck(&wk->upwin))
	GF_BGL_BmpWinAdd(wk->bgl, &wk->upwin, GF_BGL_FRAME0_M, 3, 2, 26, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_UPWINCHR);
      DisplaySequenceDirect(proc, &wk->upwin, wk->gift_data.beacon.event_name);
      DisplaySequence(proc, &wk->msgwin, mystery_01_005);
      /* 「はい／いいえ」メニューの作成 */
      CreateDirectCommYesNoMenu(proc, 0);
      *seq = MYSTERYGIFT_SEQ_RECV_YESNO_CHILD;
    }
    /* キャンセル処理 */
    if((sys.trg & PAD_BUTTON_CANCEL) || (--wk->timeout == 0)){
      SetTimeWaitIcon(wk, FALSE);	// タイムアイコン消去
      CommMysteryExitGift();
      WirelessIconEasyEnd();		// 通信アイコン削除
      *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT;
    }
    break;

  case MYSTERYGIFT_SEQ_RECV_YESNO_CHILD:
    /* 「この　おくりもの　を　じゅしん　しますか？」の「はい／いいえ」選択 */
#if 0
    DoMenuMain(proc, seq, CommDirectMenuNo);
#else
    DoMenuMain(proc, seq, CommDirectCommMenuNo);
#endif
    break;

  case MYSTERYGIFT_SEQ_REQEST_CHILD:
    /* 親機からの送信待ち */
    value = CommGetCurrentID();
    if(value != COMM_PARENT_ID && CommIsConnect(value)){
      if(CommIsTimingSync(MYSTERYGIFT_SYNC_CODE) == TRUE){
	SetTimeWaitIcon(wk, FALSE);
	CommStateSetErrorCheck(TRUE,TRUE);
	/* おくりもの　を　じゅしんちゅう　です
	   でんげんを　きらないで　ください…… */
	DisplaySequence(proc, &wk->msgwin, mystery_01_008);
#if 0//def DEBUG_ONLY_FOR_mituhara
	OS_Printf("親機から送信が開始されました！\n");
#endif
	SetBaseIcon(wk, 1);
	SetTimeWaitIcon(wk, TRUE);
	wk->timeout = 60*10;
	*seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD1;
      }
    } else if(value != COMM_PARENT_ID && CommIsConnect(value) == 0){
      /* 親との通信がとまってしまったら「もうしこみ拒否」とみなす */
      CommMysteryExitGift();
      WirelessIconEasyEnd(); // 通信アイコン削除
      SetBaseIcon(wk, -1);
      SetTimeWaitIcon(wk, FALSE);
      *seq = MYSTERYGIFT_SEQ_SEND_RECV_REFUSAL;
      break;
    }
    /* キャンセル処理 */
    if((sys.trg & PAD_BUTTON_CANCEL) || (--wk->timeout == 0)){
      CommMysteryExitGift();
      WirelessIconEasyEnd(); // 通信アイコン削除
      SetBaseIcon(wk, -1);
      SetTimeWaitIcon(wk, FALSE);
      *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT;
    }
    break;

  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD1:
    /* 親機からデータ送信が終了するまで待つ */
    if(CommMysteryCheckRecvData()){
      *seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD2;
    }
    /* キャンセル処理 */
    value = CommGetCurrentID();
    if((sys.trg & PAD_BUTTON_CANCEL) || (--wk->timeout == 0) || (value != COMM_PARENT_ID && CommIsConnect(value) == 0)){
      SetTimeWaitIcon(wk, FALSE);
      CommMysteryExitGift();
      WirelessIconEasyEnd(); // 通信アイコン削除
      *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT;
    }

    break;

  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD2:
#if 0//def DEBUG_ONLY_FOR_mituhara
    OS_Printf("受け取り確認ができました！\n");
#endif
    // ここで下画面の更新(受け取りアニメーション追加)
    deli = CommSetSaveData(proc);
    MysteryLib_InitGift(wk->bgl, deli);
    CommStateSetErrorCheck(FALSE,FALSE);
    /* ここでセーブしてみよう */
    CommChildSaveRecvData(proc);
    *seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD3;
    break;

  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD3:
    // もしも親機との通信が切れたらセーブ失敗
    value = CommGetCurrentID();
    if(value != COMM_PARENT_ID && CommIsConnect(value) == 0){
      CommMysteryExitGift();
      // 通信切断
      wk->save_cancel = TRUE;
      MysteryLib_CancelSaveDSCard();
      SetTimeWaitIcon(wk, FALSE);
      WirelessIconEasyEnd(); // 通信アイコン削除
      SetBaseIcon(wk, -1);
      *seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD31;
      break;
    }
    // セーブ完了待ち
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_LAST){
      // 親機と同期を取る
      CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE2);
      *seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD30;
      wk->sync_wait = 120;	// タイムアウト用カウンタ

    } else if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_NG){
      /* セーブエラーの時の処理 */
      MysteryLib_CancelSaveDSCard();
      wk->gift_data.beacon.have_card = 0;	// カード画面は表示しない
      SetTimeWaitIcon(wk, FALSE);
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_err_006, MYSTERYGIFT_SEQ_LOOP);
    }
    break;

  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD30:
    // 親機から返事が戻ってきたらセーブ成功
    if(CommIsTimingSync(MYSTERYGIFT_SYNC_CODE2) == TRUE){
      // 最後のセーブを行う
      MysteryLib_DoLastSave();
      wk->sync_wait = 10;
      *seq = MYSTERYGIFT_SEQ_RECV_WAIT_CHILD4;
    } else if(--wk->sync_wait == 0){
      /* セーブエラーの時の処理 */
      MysteryLib_CancelSaveDSCard();
      wk->gift_data.beacon.have_card = 0;	// カード画面は表示しない
      SetTimeWaitIcon(wk, FALSE);
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_err_006, MYSTERYGIFT_SEQ_LOOP);
    }
    break;
    
  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD31:
#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_TPrintf("セーブ失敗\n");
#endif
      //      DisplaySequence(proc, &wk->msgwin, mystery_err_008);
      // 上のウィンドウを消す
      CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
      wk->gift_data.beacon.have_card = 0;
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_err_008, MYSTERYGIFT_SEQ_LOOP);
    break;

  case MYSTERYGIFT_SEQ_RECV_WAIT_CHILD4:
    if(--wk->sync_wait == 0){ // || CommMysteryGiftGetRecvCheck() == TRUE){
      // 通信切断
      SetTimeWaitIcon(wk, FALSE);
      CommMysteryExitGift();
      WirelessIconEasyEnd(); // 通信アイコン削除
      Snd_SePlay( SEQ_SE_DP_UG_020 );
      SetBaseIcon(wk, -1);
#if 0//def DEBUG_ONLY_FOR_mituhara
      OS_Printf("完全終了\n");
#endif
      /* おくりものを　うけとりました！\nフレンドリィ　ショップ　で\nはいたついん　から　うけとってね！ */
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_01_009, MYSTERYGIFT_SEQ_LOOP);
    }
    break;

  case MYSTERYGIFT_SEQ_SEND_RECV_REFUSAL:
    /* 申し込みが拒否された場合の処理 */
    Snd_SePlay(SEQ_SE_DP_SELECT);
    // 「もうしこみ　が　きょひ　されました」
    DisplaySequence(proc, &wk->msgwin, mystery_err_004);
    // 上のウィンドウを消す
    CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
    *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL;
    break;
    
    break;
  case MYSTERYGIFT_SEQ_SEND_RECV_CANCEL_INIT:
    // 	タイムアイコンを消去
    SetTimeWaitIcon(wk, FALSE);
    /* キャンセル処理の準備 */
    Snd_SePlay(SEQ_SE_DP_SELECT);
    // 「おくりもの　が\nみつかりません　でした」
    DisplaySequence(proc, &wk->msgwin, mystery_err_003);
    // 上のウィンドウを消す
    CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
    *seq = MYSTERYGIFT_SEQ_SEND_RECV_CANCEL;
    break;
  case MYSTERYGIFT_SEQ_SEND_RECV_CANCEL:

    OS_TPrintf("キャンセル処理\n");

    /* ユーザーによるキャンセル */
    if(sys.trg){
      /* メインメニューを表示 */
      Snd_SePlay(SEQ_SE_DP_SELECT);
      CreateMenuWindow(proc, MYSTERYGIFT_TOPMENUCHR, mystery_01_001);
      *seq = MYSTERYGIFT_SEQ_MAIN;
    }
    break;

    

//--------------------------------------------------------------------------------------------
//	ＡＧＢカートリッジからのデータ転送

  case MYSTERYGIFT_SEQ_AGB_START_CHILD:
    /* ビーコン情報をメモリへコピーしてメニューを表示 */
    if(wk->from_seq != MYSTERYGIFT_WIFI_DOWNLOAD_MAIN)
      ReadAgbCartridgeData(&wk->gift_data, sizeof(GIFT_COMM_PACK));

#if 0
    // 強制抹消テスト
    wk->gift_data.beacon.version  = 0xFFFFFFFF;
    wk->gift_data.beacon.event_id = 0xFFFF;
#endif

    // 主にスロット系のエラーチェック
    wk->gift_error = CommMysteryFunc_CheckGetGift(wk->sv, &wk->gift_data);
    
    // 受け取り許可のＲＯＭバージョンと異なっていたら受け取れない
    if(wk->gift_error == COMMMYSTERYFUNC_ERROR_VERSION){
      SetTimeWaitIcon(wk, FALSE);	// 	タイムアイコンを消去
      *seq = MYSTERYGIFT_ERROR_FULL;
    } else {
      if(!GF_BGL_BmpWinAddCheck(&wk->upwin))
	GF_BGL_BmpWinAdd(wk->bgl, &wk->upwin, GF_BGL_FRAME0_M, 3, 2, 26, 4, FONT_PALNO_NORMAL, MYSTERYGIFT_UPWINCHR);
      DisplaySequenceDirect(proc, &wk->upwin, wk->gift_data.beacon.event_name);
      DisplaySequence(proc, &wk->msgwin, mystery_01_005);
      /* 「はい／いいえ」メニューの作成 */
      CreateDirectCommYesNoMenu(proc, 0);
      *seq = MYSTERYGIFT_SEQ_AGB_RECV_YESNO_CHILD;
    }
    break;

  case MYSTERYGIFT_SEQ_AGB_RECV_YESNO_CHILD:
    /* 「この　おくりもの　を　じゅしん　しますか？」の「はい／いいえ」選択 */
    DoMenuMain(proc, seq, CommDirectCommMenuNo);
    break;

  case MYSTERYGIFT_SEQ_AGB_RECV_CHECK_CHILD:
    /* 受信できるかどうかのチェック */
    *seq = MYSTERYGIFT_SEQ_AGB_REQEST_CHILD;
    break;
    
  case MYSTERYGIFT_SEQ_AGB_REQEST_CHILD:
    // ここで下画面の更新(受け取りアニメーション追加)
    deli = CommSetSaveData(proc);
    MysteryLib_InitGift(wk->bgl, deli);
    /* おくりもの　を　じゅしんちゅう　です
       でんげんを　きらないで　ください…… */
    DisplaySequence(proc, &wk->msgwin, mystery_01_008);
    SetBaseIcon(wk, 1);
    SetTimeWaitIcon(wk, TRUE);
    wk->sync_wait = 60;
    *seq = MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD;
    break;

  case MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD:
    /* 親機からデータ送信が終了するまで待つ */
    if(--wk->sync_wait == 0){
      /* ここでセーブしてみよう */
      CommChildSaveRecvData(proc);
      *seq = MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD2;
    }
    break;
  case MYSTERYGIFT_SEQ_AGB_RECV_WAIT_CHILD2:
    // セーブ完了待ち
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_LAST)
      MysteryLib_DoLastSave();
    if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_OK){
      wk->sync_wait = 1;
      SetTimeWaitIcon(wk, FALSE);
      SetBaseIcon(wk, -1);
      Snd_SePlay( SEQ_SE_DP_UG_020 );
      /* おくりものを　うけとりました！\nフレンドリィ　ショップ　で\nはいたついん　から　うけとってね！ */
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_01_009, MYSTERYGIFT_SEQ_AGB_SEND_RECV_FLAG_CHILD);
    } else if(MysteryLib_GetSaveStatus() == MYSTERYLIB_SEQ_SAVE_NG){
      /* セーブエラーの時の処理 */
      SetBaseIcon(wk, -1);
      wk->gift_data.beacon.have_card = 0;	// カード画面は表示しない
      *seq = MysteryGif_DisplayMessage(proc, &wk->msgwin, mystery_err_006, MYSTERYGIFT_SEQ_LOOP);
    }
    break;

  case MYSTERYGIFT_SEQ_AGB_SEND_RECV_FLAG_CHILD:
    if(--wk->sync_wait == 0){
      wk->sync_wait = 256*256;
      *seq = MYSTERYGIFT_SEQ_LOOP;
    }      
    break;


//--------------------------------------------------------------------------------------------

  case MYSTERYGIFT_ERROR_FULL:
    // 通信を切る処理(ただし孫配布チェックの場合は切らない)
    if(wk->gift_error != COMMMYSTERYFUNC_ERROR_GROUNDCHILD)
      CommDisconnect(wk);

    // 配達員またはカードが一杯で受け取れない
    *seq = MysteryGift_FullError(proc);
    // はい／いいえのメニューを消す
    CMG_BmpMenuWinClear(&wk->selwin[MYSTERYGIFT_WIN_COMM_DIRECT_YESNO], WINDOW_TRANS_ON);
    break;

  case MYSTERYGIFT_SEQ_DISP_MSG:
    // メッセージが表示し終わるまでループ
    *seq = MysteryGif_DisplayMessage(proc, NULL, NULL, *seq);
    break;

  case MYSTERYGIFT_SEQ_RETURN_TOPMENU:
    if(sys.trg){
      /* 上のメニューウィンドウを消す */
      CMG_BmpMenuWinClear(&wk->upwin, WINDOW_TRANS_ON);
      *seq = CommTypeMenuRetire(proc);
    }
    break;

  case MYSTERYGIFT_SEQ_GROUNDCHILD_CHECK:
    OS_TPrintf("孫配布チェック\n");
    /* 「はい／いいえ」メニューの作成 */
    CreateDirectCommYesNoMenu(proc, 1);
    *seq = MYSTERYGIFT_SEQ_RECV_YESNO_CHILD;
    wk->gift_error = COMMMYSTERYFUNC_ERROR_NONE;
    break;

    
//--------------------------------------------------------------------------------------------
    
  case MYSTERYGIFT_SEQ_RETURN:
    /* タイトルのメニューに戻る */
    TopMainMenuFinish(proc);
    wk->to_seq = 0;
    return PROC_RES_FINISH;
    break;

  case MYSTERYGIFT_SEQ_GO_LOOKCARD:
    /* カード画面へ行く */
    TopMainMenuFinish(proc);
    wk->to_seq = 1;
    return PROC_RES_FINISH;
    break;
    

  case MYSTERYGIFT_SEQ_LOOP:
    /* 電源をＯＦＦにする／カード情報があれば表示する */
    if(sys.trg){
      Snd_SePlay(SEQ_SE_DP_SELECT);
      if(wk->gift_data.beacon.have_card == 1){
	MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, MYSTERYGIFT_SEQ_DISP_CARD, wk->seq, MYSTERYGIFT_SEQ_WAIT_FADE);
      } else {
	MysteryLib_ChangeFadeType(1);
	MysteryLib_RequestFade(WIPE_TYPE_FADEOUT, MYSTERYGIFT_SEQ_FADEOUT_RESET, wk->seq, MYSTERYGIFT_SEQ_WAIT_FADE);
      }	
    }
    break;

  case MYSTERYGIFT_SEQ_DISP_CARD:
    // 下画面は格子模様を復活
    CreateBgScreenSub(wk->bgl);
    GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
    GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
    // 上画面はカード情報の表示
    MysteryCard_DisplayCardOnly(wk->bgl, &wk->gift_data.data.card, HEAPID_MYSTERYGIFT);
    MysteryLib_RequestFade(WIPE_TYPE_FADEIN, MYSTERYGIFT_SEQ_LOOP, wk->seq, MYSTERYGIFT_SEQ_WAIT_FADE);
    wk->gift_data.beacon.have_card = 0;
    break;

  case MYSTERYGIFT_SEQ_FADEOUT_RESET:
    OS_ResetSystem(0);
    break;
  }

  // 常時ではないけれど実行した関数はここで実行
  if(wk->func_hook)
    wk->func_hook(wk);

  
  // アイコンを表示するために必要な駆動処理
  MysteryLib_DoClact();

  return PROC_RES_CONTINUE;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	セーブデータのポインタを返す
 * @param	NONE
 * @return	SAVEDATA	セーブデータへのポインタ
 */
//--------------------------------------------------------------------------------------------
PROC *MyseryGiftGetProcp(void)
{
  return MysteryProc;
}
void MysteryGiftSetProcp(PROC *proc)
{
  MysteryProc = proc;
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
extern const PROC_DATA MysteryCardProcData;
#define CHECK_OVERLAY
static PROC_RESULT MysteryGiftProc_End(PROC * proc, int * seq)
{
  FS_EXTERN_OVERLAY( title );
#ifdef CHECK_OVERLAY
  FS_EXTERN_OVERLAY( startmenu );
#endif
  MYSTERYGIFT_WORK *wk = PROC_GetWork(proc);
  if(wk->to_seq == 0){
    Main_SetNextProc( FS_OVERLAY_ID(title), &TitleProcData);
  } else if(wk->to_seq == 1){
#ifdef CHECK_OVERLAY
    Main_SetNextProc( FS_OVERLAY_ID(startmenu), &MysteryCardProcData);
#else
    Main_SetNextProc( NO_OVERLAY_ID, &MysteryCardProcData);
#endif
  }
  sys_DeleteHeap(HEAPID_COMMICON);
  PROC_FreeWork(proc);
  sys_DeleteHeap(HEAPID_MYSTERYGIFT);
  if(wk->comm_type == MYSTERYCOMM_TYPE_AGBCARTRIDGE)
    sys_InitAgbCasetteVer(0);
  MysteryLib_SetAgbCartridgeIntr(FALSE);	/* AGBカートリッジの抜け検出OFF */

  return PROC_RES_FINISH;
}


//--------------------------------------------------------------------------------------------


//------------------------------------------------------------------
/**
 * @brief	ビーコン取得シーケンス
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
#define BEACON_GATHER_TIME	(2*60)			// ビーコン情報を集める時間
static void MysteryGiftBeaconProc_Main(MYSTERYGIFT_WORK *wk)
{
  int flag;

  switch(wk->beacon_seq){
  case MYSTERYGIFT_BEACON_SEQ_WAIT:	// 何もしない
    break;

  case MYSTERYGIFT_BEACON_SEQ_INIT:
    // * パーティーゲーム検索の通信処理開始（子機状態のみ）
    CommStateEnterPartyGameScanChild(wk->sv);
    wk->beacon_wait = BEACON_GATHER_TIME;
    wk->beacon_seq = MYSTERYGIFT_BEACON_SEQ_TIMER;
    break;

  case MYSTERYGIFT_BEACON_SEQ_TIMER:
    // ビーコン収集中
    flag = CommStateGetPartyGameBit();

#if 0//def DEBUG_ONLY_FOR_mituhara
    // デバッグ中
    if(sys.trg & PAD_BUTTON_L)	flag |= PARTYGAME_MYSTERY_BCON;
#endif

    if(flag & PARTYGAME_MYSTERY_BCON)	wk->found_beacon = TRUE;

    if(--wk->beacon_wait == 0){
      // パーティーゲームサーチの終了処理
      CommStateExitPartyGameScan();
      wk->beacon_seq = MYSTERYGIFT_BEACON_SEQ_WAIT;
    }
    break;
  }
}


//------------------------------------------------------------------
/**
 * @brief	ビーコンダウンロード
 *		※任天堂吉原様のmain.cをここに移植
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
// bsdownから返ってくるコールバックを処理する。
static void MysteryGift_BSCallBack( int code )
{
  switch( code ){
  case BSDOWNCALLBACK_STARTSCAN:	// スキャン開始時
    s_state = BEACON_STATE_SCANNING;
    break;
  case BSDOWNCALLBACK_START:		// 親機をみつけたとき
    s_state = BEACON_STATE_DOWNLOAD;
    break;
  case BSDOWNCALLBACK_SUCCESS:		// データを完全に受け取ったとき
    s_state = BEACON_STATE_COMPLETE;
    break;
  case BSDOWNCALLBACK_FINISH:		// 無線の終了処理
    if( s_state == BEACON_STATE_COMPLETE ){
      s_state = BEACON_STATE_FINISH;
    }	else {
      s_state = BEACON_STATE_CANCEL;				
    }
    break;
  case BSDOWNCALLBACK_ERROR:		// エラー発生時
    s_state = BEACON_STATE_ERROR;
    break;
  }
}


static void MysteryGift_BeaconCancel(void)
{
  OS_TPrintf("イクニューモン開放\n");
  CommVRAMDFinalize();
  sys_FreeMemoryEz(buffer);
  WirelessIconEasyEnd(); // 通信アイコン削除
  buffer = NULL;
}

static void MysteryGift_BeaconMainLoop(MYSTERYGIFT_WORK *wk)
{
  if( s_state == BEACON_STATE_FINISH ){
    MysteryGift_BeaconCancel();

    // ダウンロード完了待ち。ＣＲＣが正しいかチェック
    // コールバックでなく、ここでチェックするのは、割り込みにルーチンに重い処理をいれたくないため
    if( bsdown_c_checkcrc() ) {
      s_state = BEACON_STATE_SUCCESS;
    } else {
      s_state = BEACON_STATE_CRCERROR;
    }
  }

  if(s_state == BEACON_STATE_INIT1 || s_state == BEACON_STATE_INIT2 || s_state == BEACON_STATE_START ||
     s_state == BEACON_STATE_SCANNING || s_state == BEACON_STATE_DOWNLOAD || s_state == BEACON_STATE_CANCELING)
    WirelessIconEasy_SetLevel(WM_LINK_LEVEL_3 - WM_GetLinkLevel());
  
  //  OS_TPrintf("s_state = %d\n", s_state - BEACON_STATE_INIT1);
  
  switch( s_state ){
  case BEACON_STATE_INIT1:				// 初期状態(通信ライブラリ初期化)
    CommVRAMDInitialize();
    s_state = BEACON_STATE_INIT2;
    break;			
  case BEACON_STATE_INIT2:				// 初期状態
    if(CommIsVRAMDInitialize() == TRUE){
      progress_time = 0;
      buffer = sys_AllocMemory(HEAPID_MYSTERYGIFT, bsdown_c_worksize());
      bsdown_c_init( &(wk->recvbuf[0]), MysteryGift_BSCallBack, buffer );
      s_state = BEACON_STATE_START;
      WirelessIconEasy();	// 通信アイコン表示(アンテナ立たないT-T)
      debug_printf("PRESS A TO START\n");
    }
    break;
  case BEACON_STATE_START:				// 初期状態
    debug_printf("INITIALIZING...\n");
    break;
  case BEACON_STATE_SCANNING:			// スキャン中
    debug_printf("SEARCHING......\n");
    //    debug_printf("PRESS START TO RESTART\n");
    break;
  case BEACON_STATE_DOWNLOAD:			// 親機発見して、ダウンロード中
    debug_printf("packets %d / %d\t", bsdown_c_received(), bsdown_c_total());
    progress_time++;
    debug_printf("time    %d : %d\n", (progress_time / 60) / 60, (progress_time / 60) % 60 );
    break;				
  case BEACON_STATE_COMPLETE:			// ダウンロード完了
    debug_printf("Finishing( size = %d byte )\n", bsdown_c_size());
    debug_printf("time    %d : %d\n", (progress_time / 60) / 60, (progress_time / 60) % 60 );				
    break;
  case BEACON_STATE_CANCELING:		// キャンセル処理中
    debug_printf("CANCELING......\n");    //    s_state = BEACON_STATE_FINISH;	// 失敗して終了させる
    break;
  case BEACON_STATE_SUCCESS:			// ダウンロード終了
    //    debug_printf("Complete( size = %d byte )\n", bsdown_c_size());
    //    debug_printf("time    %d : %d\n", (progress_time / 60) / 60, (progress_time / 60) % 60 );				
    //    debug_printf("PRESS START TO RESTART\n");				
    break;
  case BEACON_STATE_CANCEL:			// キャンセル終了
    //    debug_printf("PRESS START TO RESTART\n");
    return;
    break;			
  case BEACON_STATE_ERROR:				// エラー	
    debug_printf("error......\n");
    break;
  case BEACON_STATE_CRCERROR:
    debug_printf("crc error.\n");
    //    debug_printf("PRESS START TO RESTART\n");
    break;
  }
		
  if(sys.trg & PAD_BUTTON_CANCEL){
    Snd_SePlay(SEQ_SE_DP_SELECT);
    // リセット処理
    switch( s_state ){
    case BEACON_STATE_SCANNING:			// スキャン中
    case BEACON_STATE_DOWNLOAD:			// 親機発見して、ダウンロード中
    case BEACON_STATE_ERROR:				// エラー

      OS_TPrintf("キャンセル依頼\n");
      if( bsdown_end() ){
	s_state = BEACON_STATE_CANCELING;	
      }					
      break;
				
    case BEACON_STATE_SUCCESS:			// ダウンロード終了
    case BEACON_STATE_CANCEL:			// キャンセル終了
    case BEACON_STATE_CRCERROR:		// ＣＲＣエラー
      return;
    default:
      break;
    }				
  }
}


//------------------------------------------------------------------
///	プロセスデータ
//------------------------------------------------------------------
const PROC_DATA MysteryGiftProcData = {
  MysteryGiftProc_Init,
  MysteryGiftProc_Main,
  MysteryGiftProc_End,
  NO_OVERLAY_ID,
};
  
/*  */
