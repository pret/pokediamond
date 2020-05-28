//=============================================================================
/**
 * @file	wifi_note_local.h
 * @brief	WIFI手帳ローカル定義
 * @author	k.ohno
 * @date    2006.4.5
 */
//=============================================================================


#ifndef __WIFI_P2PMATCH_LOCAL_H__
#define __WIFI_P2PMATCH_LOCAL_H__

#include "savedata/wifilist.h"

#define WIFIP2PMATCH_MEMBER_MAX  (WIFILIST_FRIEND_MAX)
#define WIFIP2PMATCH_DISP_MEMBER_MAX  (5)

// 機能ボタン用定義
#define FUNCBUTTON_NUM	( 7 ) 		// 機能ボタンの数
#define START_WORDPANEL ( 0 )		// 最初の文字入力パネルの番号（０＝ひらがな）

// CLACTで定義しているセルが大きすぎてサブ画面に影響がでてしまうので離してみる
#define NAMEIN_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)

// CellActorに処理させるリソースマネージャの種類の数（＝マルチセル・マルチセルアニメは使用しない）
#define CLACT_RESOURCE_NUM		(  4 )
#define _OAM_NUM			( 5 )

#define FRIENDCODE_MAXLEN     (12)

// メッセージ表示後のWAIT
#define WIFIP2PMATCH_CORNER_MESSAGE_END_WAIT	( 60 )


// 文字パネルの遷移用
enum{
  WIFIP2PMATCH_MODE_INIT  = 0,
  WIFIP2PMATCH_NORMALCONNECT_YESNO,
  WIFIP2PMATCH_NORMALCONNECT_WAIT,
  WIFIP2PMATCH_DIFFER_MACHINE_INIT,
  WIFIP2PMATCH_DIFFER_MACHINE_NEXT,
  WIFIP2PMATCH_DIFFER_MACHINE_ONEMORE,
  WIFIP2PMATCH_FIRST_YESNO,
  WIFIP2PMATCH_POWEROFF_INIT,
  WIFIP2PMATCH_POWEROFF_YESNO,
  WIFIP2PMATCH_POWEROFF_WAIT,
  WIFIP2PMATCH_RETRY_INIT,        //10
  WIFIP2PMATCH_RETRY_YESNO,
  WIFIP2PMATCH_RETRY_WAIT,
  WIFIP2PMATCH_RETRY,
  WIFIP2PMATCH_CONNECTING_INIT,
  WIFIP2PMATCH_CONNECTING,
  WIFIP2PMATCH_FIRST_ENDMSG,
  WIFIP2PMATCH_FIRST_ENDMSG_WAIT,
  WIFIP2PMATCH_FRIENDLIST_INIT,
  WIFIP2PMATCH_MODE_FRIENDLIST,
  WIFIP2PMATCH_VCHATWIN_WAIT,           //20
  WIFIP2PMATCH_MODE_VCT_CONNECT_INIT2,
  WIFIP2PMATCH_MODE_VCT_CONNECT_INIT,
  WIFIP2PMATCH_MODE_VCT_CONNECT_WAIT,
  WIFIP2PMATCH_MODE_VCT_CONNECT,
  WIFIP2PMATCH_MODE_VCT_CONNECTEND_YESNO,
  WIFIP2PMATCH_MODE_VCT_CONNECTEND_WAIT,
  WIFIP2PMATCH_MODE_VCT_DISCONNECT,
  WIFIP2PMATCH_MODE_BATTLE_DISCONNECT,
  WIFIP2PMATCH_MODE_DISCONNECT,
  WIFIP2PMATCH_MODE_BATTLE_CONNECT_INIT,  //30
  WIFIP2PMATCH_MODE_BATTLE_CONNECT_WAIT,
  WIFIP2PMATCH_MODE_BATTLE_CONNECT,
  WIFIP2PMATCH_MODE_MAIN_MENU,
  WIFIP2PMATCH_MODE_END_WAIT,
  WIFIP2PMATCH_MODE_CHECK_AND_END,
  WIFIP2PMATCH_MODE_SELECT_INIT,
  WIFIP2PMATCH_MODE_SELECT_WAIT,
  WIFIP2PMATCH_MODE_SUBBATTLE_WAIT,
  WIFIP2PMATCH_MODE_SELECT_REL_INIT,
  WIFIP2PMATCH_MODE_SELECT_REL_YESNO,       //40
  WIFIP2PMATCH_MODE_SELECT_REL_WAIT,
  WIFIP2PMATCH_MODE_MATCH_INIT,
  WIFIP2PMATCH_MODE_MATCH_WAIT,
  WIFIP2PMATCH_MODE_MATCH_LOOP,
  WIFIP2PMATCH_MODE_BCANCEL_YESNO,
  WIFIP2PMATCH_MODE_BCANCEL_WAIT,
  WIFIP2PMATCH_MODE_CALL_INIT,
  WIFIP2PMATCH_MODE_CALL_YESNO,
  WIFIP2PMATCH_MODE_CALL_SEND,
  WIFIP2PMATCH_MODE_CALL_CHECK,             //50
  WIFIP2PMATCH_MODE_MYSTATUS_WAIT,
  WIFIP2PMATCH_MODE_CALL_WAIT,
  WIFIP2PMATCH_MODE_PERSONAL_INIT,
  WIFIP2PMATCH_MODE_PERSONAL_WAIT,
  WIFIP2PMATCH_MODE_PERSONAL_END,
  WIFIP2PMATCH_MODE_EXIT_YESNO,
  WIFIP2PMATCH_MODE_EXIT_WAIT,
  WIFIP2PMATCH_MODE_EXITING,
  WIFIP2PMATCH_MODE_EXIT_END,
  WIFIP2PMATCH_NEXTBATTLE_YESNO,         //60
  WIFIP2PMATCH_NEXTBATTLE_WAIT,
  WIFIP2PMATCH_MODE_VCHAT_NEGO,
  WIFIP2PMATCH_MODE_VCHAT_NEGO_WAIT,
  WIFIP2PMATCH_RECONECTING_WAIT,
  WIFIP2PMATCH_MODE_BCANCEL_YESNO_VCT,
  WIFIP2PMATCH_MODE_BCANCEL_WAIT_VCT,
};


enum{
	WIFIP2PMATCH_SYNCHRONIZE_END=201,
};

// 上下画面指定定義
#define BOTH_LCD	( 2 )
#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// 要は０と
#define SUB_LCD		( GF_BGL_SUB_DISP )		// １なんですが。

// BMPWIN指定
enum{
	BMP_NAME1_S_BG0,
	BMP_NAME2_S_BG0,
	BMP_NAME3_S_BG0,
	BMP_NAME4_S_BG0,
	BMP_NAME5_S_BG0,
	BMP_WIFIP2PMATCH_MAX,
};


//---------------WIFISTATUSデータ

typedef enum{
  WIFI_STATUS_NONE,   // 何も無い
  WIFI_STATUS_VCT,      // VCT中
  WIFI_STATUS_SBATTLE50,      // シングル対戦中
  WIFI_STATUS_SBATTLE100,      // シングル対戦中
  WIFI_STATUS_SBATTLE_FREE,      // シングル対戦中
  WIFI_STATUS_DBATTLE50,      // ダブル対戦中
  WIFI_STATUS_DBATTLE100,      // ダブル対戦中
  WIFI_STATUS_DBATTLE_FREE,      // ダブル対戦中
  WIFI_STATUS_TRADE,          // 交換中
  WIFI_STATUS_SBATTLE50_WAIT,   // シングルLv50対戦募集中
  WIFI_STATUS_SBATTLE100_WAIT,   // シングルLv100対戦募集中
  WIFI_STATUS_SBATTLE_FREE_WAIT,   // シングルLv100対戦募集中
  WIFI_STATUS_DBATTLE50_WAIT,   // ダブルLv50対戦募集中
  WIFI_STATUS_DBATTLE100_WAIT,   // ダブルLv100対戦募集中
  WIFI_STATUS_DBATTLE_FREE_WAIT,   // ダブルLv100対戦募集中
  WIFI_STATUS_TRADE_WAIT,    // 交換募集中
  WIFI_STATUS_LOGIN_WAIT,    // 待機中　ログイン直後はこれ
  WIFI_STATUS_UNKNOWN,   // 新たに作ったらこの番号以上になる
};

typedef enum{
  _REGULATION_BATTLE_TOWER     // バトルタワー対戦方式
};


//トータル189バイト送信できるがとりあえず下位プログラムは範囲分だけ送る
#define _POKEMON_NUM   (6)


typedef struct{
  u16 pokemonType[_POKEMON_NUM];
  u16 hasItemType[_POKEMON_NUM];
  u8 version;
  u8 regionCode;
  u8 pokemonZukan;
  u8 status;
  u8 regulation;
  u8 trainer_view;
  u8 sex;
  u8 nation;
  u8 area;
  u8 vchat;
  u8 vchat_org;
} _WIFI_MACH_STATUS;

#define _WIFI_STATUS_MAX_SIZE  (sizeof(_WIFI_MACH_STATUS))

//============================================================================================
//	構造体定義
//============================================================================================

typedef struct {
  _WIFI_MACH_STATUS myMatchStatus;   // 自分のマッチング状態データ
  _WIFI_MACH_STATUS friendMatchStatus[WIFIP2PMATCH_MEMBER_MAX]; // 相手のマッチング状態データ
} TEST_MATCH_WORK;


struct _WIFIP2PMATCH_WORK{
  WIFI_LIST* pList;
  TEST_MATCH_WORK* pMatch;
  int friendMatchReadCount;
  u8 index2No[WIFIP2PMATCH_MEMBER_MAX];
  int matchStatusBackup[WIFIP2PMATCH_MEMBER_MAX];
  NAMEIN_PARAM*		nameinParam;
  BMPLIST_DATA*   menulist;
  BMPLIST_WORK* lw;		// BMPメニューワーク
  BMPLIST_DATA*   submenulist;
  BMPLIST_WORK* sublw;		// BMPメニューワーク
  GF_BGL_INI		*bgl;									// GF_BGL_INI
  SAVEDATA*  pSaveData;
  WORDSET			*WordSet;								// メッセージ展開用ワークマネージャー
  MSGDATA_MANAGER *MsgManager;							// 名前入力メッセージデータマネージャー
  MSGDATA_MANAGER *SysMsgManager;  //
  STRBUF			*TrainerName[WIFIP2PMATCH_MEMBER_MAX];		// 名前
  STRBUF			*MsgString;								// メッセージ
  STRBUF*         pExpStrBuf;
  STRBUF			*TalkString;							// 会話メッセージ用
  STRBUF			*TitleString;							// タイトルメッセージ用
  STRBUF			*MenuString[4];							// メニューメッセージ用
  STRBUF*         pTemp;        // 入力登録時の一時バッファ
  
  int				MsgIndex;								// 終了検出用ワーク
  BMPMENU_WORK* pYesNoWork;
  void* timeWaitWork;
  CLACT_SET_PTR 			clactSet;								// セルアクターセット
  CLACT_U_EASYRENDER_DATA	renddata;								// 簡易レンダーデータ
  CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// リソースマネージャ
  CLACT_U_RES_OBJ_PTR 	resObjTbl[BOTH_LCD][CLACT_RESOURCE_NUM];// リソースオブジェテーブル
  CLACT_HEADER			clActHeader_m;							// セルアクターヘッダー
  CLACT_HEADER			clActHeader_s;							// セルアクターヘッダー
  CLACT_WORK_PTR			MainActWork[_OAM_NUM];				// セルアクターワークポインタ配列
	//CLACT_WORK_PTR			SubActWork[_OAM_NUM];				// セルアクターワークポインタ配列

  GF_BGL_BMPWIN			MsgWin;									// 会話ウインドウ
  //   GF_BGL_BMPWIN           MenuWin[4];
  GF_BGL_BMPWIN			MyInfoWin;									// やめる
  GF_BGL_BMPWIN			TitleWin;								// 「レコードコーナー　ぼしゅうちゅう！」など
  GF_BGL_BMPWIN			SysMsgWin;								// 「レコードコーナー　ぼしゅうちゅう！」など
  GF_BGL_BMPWIN			ListWin;									// やめる
  GF_BGL_BMPWIN			SubListWin;									// やめる
  GF_BGL_BMPWIN			MyWin;									// やめる

  int localTime;
  int seq;									// 現在の文字入力状態（入力OK/アニメ中）など
  int       endSeq;
  int						nextseq;
  int initSeq;
  int						mode;									// 現在最前面の文字パネル
  int						timer;
  MYSTATUS                *pMyStatus;
  u8     mainCur;
  u8     subCur;
  BOOL bInitMessage;
  PROC*		subProc;
  int preConnect;
  u16 battleCur;
  u16 singleCur[2];
  u16 bSingle;
  u16 keepStatus;
  u16 keepVChat;
  u16 friendNo;
  BOOL bRetryBattle;
};




#endif  //__WIFI_P2PMATCH_LOCAL_H__

