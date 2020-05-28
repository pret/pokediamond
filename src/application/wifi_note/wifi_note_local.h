//=============================================================================
/**
 * @file	wifi_note_local.h
 * @brief	WIFI手帳ローカル定義
 * @author	k.ohno
 * @date    2006.4.5
 */
//=============================================================================


#ifndef __WIFI_NOTE_LOCAL_H__
#define __WIFI_NOTE_LOCAL_H__

#include "savedata/wifilist.h"
#include "communication/communication.h"

#define WIFINOTE_MEMBER_MAX  (WIFILIST_FRIEND_MAX)
#define WIFINOTE_DISP_MEMBER_MAX  (8)

// 機能ボタン用定義
#define FUNCBUTTON_NUM	( 7 ) 		// 機能ボタンの数
#define START_WORDPANEL ( 0 )		// 最初の文字入力パネルの番号（０＝ひらがな）

// CLACTで定義しているセルが大きすぎてサブ画面に影響がでてしまうので離してみる
#define NAMEIN_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)

// CellActorに処理させるリソースマネージャの種類の数（＝マルチセル・マルチセルアニメは使用しない）
#define CLACT_RESOURCE_NUM		(  4 )
#define _OAM_NUM			( 10 )  // ８体のトレーナー＋左右矢印
#define _LEFT_ARROW       (8)
#define _RIGHT_ARROW       (9)
#define _UNION_CREATURE  (1)
#define _LIST_ARROW  (0)


#define FRIENDCODE_MAXLEN     (12)

// メッセージ表示後のWAIT
#define WIFINOTE_CORNER_MESSAGE_END_WAIT	( 60 )


// 文字パネルの遷移用
enum{
  WIFINOTE_MODE_INIT  = 0, 
  WIFINOTE_MODE,
  WIFINOTE_MODE_FRIENDLIST_INIT,
  WIFINOTE_MODE_FRIENDLIST,
  WIFINOTE_MODE_PERSONAL_MENU,
  WIFINOTE_MODE_PERSONAL_MENU_WAIT,
  WIFINOTE_MODE_MAIN_MENU,
  WIFINOTE_MODE_CODEINPUT_INIT,
  WIFINOTE_MODE_CODEINPUT_INIT_WAIT,
  WIFINOTE_MODE_CODEINPUT_LOOP,
  WIFINOTE_MODE_CODEINPUT_LOOPNEXT,
  WIFINOTE_MODE_CODEINPUT_LOOP2,
  WIFINOTE_MODE_CODEINPUT_END_WAIT,
  WIFINOTE_MODE_CODEINPUT_YESNO,
  WIFINOTE_MODE_CODEINPUT_YESNO_WAIT,
  WIFINOTE_MODE_FRIENDCODE_DIFFER,
  WIFINOTE_MODE_FRIENDCODE_DIFFER_WAIT,
  WIFINOTE_MODE_END_WAIT,
  WIFINOTE_MODE_MYCODE_DISP_INIT,
  WIFINOTE_MODE_MYCODE_DISP,
  WIFINOTE_MODE_INFO_INIT,
  WIFINOTE_MODE_INFO_DISP,
  WIFINOTE_MODE_INFO_END,
  WIFINOTE_MODE_RENAME_INIT,   // なまえをかえる
  WIFINOTE_MODE_RENAME_OPEN_WINDOW,
  WIFINOTE_MODE_RENAME_WAIT,
  WIFINOTE_MODE_RENAME_ENTRY,
  WIFINOTE_MODE_DELETE_INIT,   // 消す
  WIFINOTE_MODE_DELETE_YESNO,
  WIFINOTE_MODE_DELETE_CHECK,
  WIFINOTE_MODE_CODE_INIT,
};


enum{
	WIFINOTE_SYNCHRONIZE_END=201,
};

// 上下画面指定定義
#define BOTH_LCD	( 2 )

// BMPWIN指定
enum{
	BMP_NAME1_S_BG0,
	BMP_NAME2_S_BG0,
	BMP_NAME3_S_BG0,
	BMP_NAME4_S_BG0,
	BMP_NAME5_S_BG0,
	BMP_WIFINOTE_MAX,
};


#define WIFINOTE_SEND_DATASIZE	( 3000 )

typedef struct{
	u8  data[WIFINOTE_SEND_DATASIZE];		// レコード交換データ
	u32 _xor;							// データ整合性確認用XOR
	u32 seed;							// 親から来たこの数値を元に乱数を発生させてデータを入れ替える
}WIFINOTE_DATA;

//============================================================================================
//	構造体定義
//============================================================================================

struct _WIFINOTE_WORK{
	NAMEIN_PARAM*		nameinParam;
	GF_BGL_INI		*bgl;									// GF_BGL_INI
    SAVEDATA*  pSaveData;
	WORDSET			*WordSet;								// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER *MsgManager;							// 名前入力メッセージデータマネージャー
	BMPLIST_DATA*   menulist;
    u8              index2No[WIFINOTE_MEMBER_MAX];     // wifilistを引き出す為の番号
    STRBUF			*TrainerName[WIFINOTE_MEMBER_MAX];		// 名前
    STRBUF*         pExpStrBuf;
	STRBUF			*TalkString;							// 会話メッセージ用
	STRBUF			*TitleString;							// タイトルメッセージ用
	STRBUF			*MenuString[4];							// メニューメッセージ用
    STRBUF*         pTempTrainerName;        // 入力登録時の一時バッファ
    STRBUF*       pTempFriendCode;        // 入力登録時の一時バッファ

  SOFT_SPRITE_MANAGER* spriteManager;
  SOFT_SPRITE*			sprite;
  
	int				MsgIndex;								// 終了検出用ワーク
    BMPMENU_WORK* pYesNoWork;

	CLACT_SET_PTR 			clactSet;								// セルアクターセット
	CLACT_U_EASYRENDER_DATA	renddata;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	resObjTbl[BOTH_LCD][CLACT_RESOURCE_NUM];// リソースオブジェテーブル
	CLACT_HEADER			clActHeader_m;							// セルアクターヘッダー
	CLACT_HEADER			clActHeader_s;							// セルアクターヘッダー
	CLACT_WORK_PTR			MainActWork[_OAM_NUM];				// セルアクターワークポインタ配列
//	CLACT_WORK_PTR			SubActWork[_OAM_NUM];				// セルアクターワークポインタ配列

	GF_BGL_BMPWIN 			TrainerNameWin[WIFINOTE_DISP_MEMBER_MAX];			// お絵かき画面用BMPウインドウ
	GF_BGL_BMPWIN			MsgWin;									// 会話ウインドウ
    GF_BGL_BMPWIN           MenuWin[4];
	GF_BGL_BMPWIN			ListWin;									// やめる
	GF_BGL_BMPWIN			TitleWin;								// 「レコードコーナー　ぼしゅうちゅう！」など
    BMPLIST_WORK* lw;		// BMPメニューワーク
	u16						*ObjPaletteTable;
	int						seq;									// 現在の文字入力状態（入力OK/アニメ中）など
	int						nextseq;
	int						mode;									// 現在最前面の文字パネル
	int						wait;
    MYSTATUS                *pMyStatus;
	u16						CursorPal;
	u8						brush_color;
	u8						brush;
    u8     mainCur;
    u8     horizontalCur;
    u8     verticalCur;
    u8     subCur;
  u8 friendTrg;
  
  PROC*		subProc;

  int checkFriend[COMM_MACHINE_MAX];
  int indexFriend[COMM_MACHINE_MAX];
  int addFriendNo;

  u16 pos_bak;

};


// SE用定義
#define WIFINOTE_MOVE_SE		(SEQ_SE_DP_SELECT)
#define WIFINOTE_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define WIFINOTE_BS_SE		(SEQ_SE_DP_SELECT)


#endif  //__WIFI_NOTE_LOCAL_H__

