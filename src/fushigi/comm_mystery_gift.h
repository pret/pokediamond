//============================================================================================
/**
 * @file	comm_fushigi_present.h
 * @bfief	ふしぎな　おくりもの
 * @author	Satoshi Mitsuhara
 * @date	06.05.08
 *
 * $Id: comm_mystery_gift.h,v 1.25 2006/08/12 06:29:26 mitsuhara Exp $
 */
//============================================================================================
#ifndef __COMM_MYSTERY_GIFT_H__
#define __COMM_MYSTERY_GIFT_H__

#include "common.h"
#include "system/procsys.h"
#include "system/heapdefine.h"
#include "system/bmp_list.h"
#include "system/wordset.h"
#include "system/wipe.h"
#include "system/clact_tool.h"

#include "savedata/savedata_def.h"
#include "savedata/fushigi_data.h"



enum {
  MYSTERYGIFT_WIN_MAIN = 0,		/* メインメニュー選択ウィンドウ */
  MYSTERYGIFT_WIN_COMM_TYPE,		/* 通信方式選択ウィンドウ */
  MYSTERYGIFT_WIN_COMM_DIRECT_YESNO,	/* 通信方式でダイレクト通信を使いますか「はい／いいえ」ウィンドウ */
  MYSTERYGIFT_WIN_MAX
};

#define MYSTERYGIFT_TITLE_MAX		(36)
#define MYSTERYGIFT_EXPLANATION_MAX	(250)
// 親機と子機が同期をするための識別コード
#define MYSTERYGIFT_SYNC_CODE		(0xAB)
#define MYSTERYGIFT_SYNC_CODE2		(0x93)

// 通信をあきらめる時間
#define MYSTERYGIFT_TIMEOUT		(60*120)


//============================================================================================

// -- WiFiに関連した定数 --
#define FILE_NUM				10
enum {
  ND_RESULT_EXECUTE,		// 実行中
  ND_RESULT_COMPLETE,		// 正常ダウンロード終了
  ND_RESULT_NOT_FOUND_FILES,	// ファイルが見つからなかった
  ND_RESULT_DOWNLOAD_CANCEL,	// ユーザーからキャンセルされた
  ND_RESULT_DOWNLOAD_ERROR,	// なんらかのエラーが起きた
  ND_RESULT_MAX
};

#define WIFI_MYSTERYGIFT_BASE	0x1000
#define WIFI_MYSTERYFILE_SIZE	4096

//============================================================================================

// ふしぎなおくりもの専用ワーク定義
typedef struct {
  GF_BGL_INI *bgl;
  SAVEDATA *sv;
  CONFIG *cfg;
  WORDSET *word;	       			// 単語モジュール制御ワークへのポインタ
  MSGDATA_MANAGER *msgman;	    		// MSGデータマネージャへのポインタ
  STRBUF *msg;					// ２行以上あるメッセージの時のみ使用

  GF_BGL_BMPWIN	msgwin;				// メッセージを表示するウィンドウ
  GF_BGL_BMPWIN	selwin[MYSTERYGIFT_WIN_MAX];	// メニュー選択するウィンドウ
  GF_BGL_BMPWIN	upwin;				// 画面上のタイトルウィンドウ

  int msg_wait;					// メッセージ表示速度
  int m_id;
  int msg_seq;					// メッセージ表示中のシーケンス
  int msg_next_seq;				// メッセージを表示し終えたら進むべきシーケンス
  
  BMPLIST_WORK *lw;				// メニュー
  BMP_MENULIST_DATA *bmd;

  int gift_error;				// 受け取ったおくりもの(Beacon)に関するエラー情報
  
  int from_seq;
  int next_seq;					// フェードの次に行うシーケンス番号
  GIFT_COMM_PACK gift_data;			// 届いたおくりものデータの全体(ビーコン＋データ)
  int timeout;

  int connectIndex;
  int sync_wait;				// 同期情報通信時のタイミング待ち

  int to_seq;					// 行き先


  // セルアクター関連
  CLACT_SET_PTR	clactSet;				// セルアクターセット 
  CLACT_U_EASYRENDER_DATA renddata;			// 簡易レンダーデータ
  CLACT_U_RES_MANAGER_PTR resMan[CLACT_U_RES_MAX];	// リソースマネージャ
  CLACT_U_RES_OBJ_PTR resObjTbl[CLACT_U_RES_MAX];	// リソースオブジェテーブル
  CLACT_HEADER clActHeaderMain;
  // やじるしアイコン
  CLACT_WORK_PTR arrow;

  // AGBカートリッジからのダウンロードフラグ
  //  int agb_cartridge;

  // ビーコン取得シーケンス
  int beacon_seq;
  int beacon_wait;
  int found_beacon;

  u8 recvbuf[4*1024];
  int comm_type;

  // PROCの*seqをここに定義しておきます
  int *seq;

  // WiFiふしぎなおくりもの系
  int wifi_dl_seq;
  u8 *dwcWork;
  DWCInetControl stConnCtrl;
  BOOL callbackflag;
  int wifi_next_seq;
  int server_filenum;
  char filebuffer[WIFI_MYSTERYFILE_SIZE];
  int wifi_result;
  u32 recived,contentlen,percent;
  BOOL wifi_errflag;
  int wifi_errmsg;
  int wifi_errcode;
  int wifi_errtype;
  DWCErrorType wifi_cancel;
  BOOL (*wifi_check_func)(void);
  GF_BGL_BMPWIN	wifiwin;

  GIFT_DATA comm_data;					// 暗号化されたデータ

  void (*func_hook)(void *);
  int save_cancel;
  void *time_icon;
  
} MYSTERYGIFT_WORK;



enum {
  MYSTERYCOMM_TYPE_NULL,
  MYSTERYCOMM_TYPE_DIRECT,		// ダイレクト通信
  MYSTERYCOMM_TYPE_AGBCARTRIDGE,	// ＡＧＢのカートリッジからダウンロード
  MYSTERYCOMM_TYPE_BEACON,		// ビーコンからダウンロード
  MYSTERYCOMM_TYPE_WIFI,		// Wi-Fiからのダウンロード
  
  MYSTERYCOMM_TYPE_MAX
};



extern PROC *MyseryGiftGetProcp(void);
extern void MysteryGiftSetProcp(PROC *proc);
extern void WifiMysteryGift_ErrorDisp(MYSTERYGIFT_WORK *wk);
extern void SetTimeWaitIconEx(MYSTERYGIFT_WORK *wk, int flag);


#endif	// __COMM_MYSTERY_GIFT_H__
/*  */
