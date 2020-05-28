//=============================================================================
/**
 * @file	mysign_local.h
 * @brief	サイン画面構造体定義（内部参照用)
 *          
 * @author	Akito Mori
 * @date    2006.04.11
 */
//=============================================================================



#ifndef __MYSIGN_LOCAL_H__
#define __MYSIGN_LOCAL_H__

#include "system/touch_subwindow.h"

// 機能ボタン用定義
#define FUNCBUTTON_NUM	( 7 ) 		// 機能ボタンの数
#define START_WORDPANEL ( 0 )		// 最初の文字入力パネルの番号（０＝ひらがな）

// 接続人数MAXは５人
#define OEKAKI_MEMBER_MAX	( 5 )


// CLACTで定義しているセルが大きすぎてサブ画面に影響がでてしまうので離してみる
#define NAMEIN_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)

// CellActorに処理させるリソースマネージャの種類の数（＝マルチセル・マルチセルアニメは使用しない）
#define CLACT_RESOURCE_NUM		(  4 )
#define NAMEIN_OAM_NUM			( 14 )


// メッセージ表示後のWAIT
#define OEKAKI_MESSAGE_END_WAIT	( 60 )


// お絵かきボードの幅・高さ
#define OEKAKI_BOARD_W	 	( 24 )
#define OEKAKI_BOARD_H	 	(  8 )
#define OEKAKI_GRAPHI_SIZE  ( OEKAKI_BOARD_W*OEKAKI_BOARD_H*32 )

// 文字パネルの遷移用
enum{
	MYSIGN_MODE_INIT  = 0, 
    MYSIGN_MODE,
	MYSIGN_MODE_END_SELECT,
	MYSIGN_MODE_END_SELECT_WAIT,
	MYSIGN_MODE_REWRITE,
    MYSIGN_MODE_REWRITE_WAIT,
	MYSIGN_MODE_REWRITE_SELECT,
   
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
	BMP_OEKAKI_MAX,
};

// タッチパネル情報構造体
// このデータが通信で送信されます
typedef struct{
	u8 x[8];	// 最大8回分のタッチ座標
	u8 y[8];	// 
	u8 brush:4;	// 選択中のブラシ
	u8 size:4;	// サンプリング成功個数
}TOUCH_INFO;

typedef struct{
	u8   x,y;
	u16  size;
}OLD_TOUCH_INFO;

typedef struct{
	s8 OldDirX;
	s8 OldDirY;
	s8 DirX;
	s8 DirY;
	u8 Snd;
}SCRUCH_INFO;


//============================================================================================
//	構造体定義
//============================================================================================

struct MYSIGN_WORK{
	GF_BGL_INI		*bgl;
	BOOL			wipe_end;
	RECORD			*record;
	CONFIG			*config;

	WORDSET			*WordSet;								// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER *MsgManager;							// 名前入力メッセージデータマネージャー
	STRBUF			*TrainerName[OEKAKI_MEMBER_MAX];		// 名前
	STRBUF			*EndString;								// 文字列「やめる」
	STRBUF			*TitleString;								// 文字列「やめる」
	STRBUF			*TalkString;							// 会話メッセージ用
	int				MsgIndex;								// 終了検出用ワーク

	CLACT_SET_PTR 			clactSet;								// セルアクターセット
	CLACT_U_EASYRENDER_DATA	renddata;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	resObjTbl[BOTH_LCD][CLACT_RESOURCE_NUM];// リソースオブジェテーブル
	CLACT_HEADER			clActHeader_m;							// セルアクターヘッダー
	CLACT_HEADER			clActHeader_s;							// セルアクターヘッダー
	CLACT_WORK_PTR			MainActWork[NAMEIN_OAM_NUM];				// セルアクターワークポインタ配列
	CLACT_WORK_PTR			SubActWork[NAMEIN_OAM_NUM];				// セルアクターワークポインタ配列
	CLACT_WORK_PTR			ButtonActWork[9];						// ボタンアクターポインタ

	GF_BGL_BMPWIN 			TrainerNameWin[BMP_OEKAKI_MAX];			// お絵かき画面用BMPウインドウ
	GF_BGL_BMPWIN			OekakiBoard;
	GF_BGL_BMPWIN			MsgWin;									// 会話ウインドウ
	GF_BGL_BMPWIN			EndWin;									// やめる
	GF_BGL_BMPWIN			TitleWin;								// 「トレーナーサインをかこう！」
	GF_BGL_BMPWIN			*YesNoWin[2];							// はい・いいえウインドウのポインタ

	int						seq;									// 現在の文字入力状態（入力OK/アニメ中）など
	int						mode;									// 現在最前面の文字パネル
	int						wait;

	u8						SendBoardGraphic[0x4000];
	u16						CursorPal;
	u8						brush_color;
	u8						brush;

	TOUCH_INFO				MyTouchResult;							// 自分のサンプリング結果（これは送信するだけ
	TOUCH_INFO				AllTouchResult[OEKAKI_MEMBER_MAX];		// 通信で取得したサンプリング結果（このデータで描画する
	OLD_TOUCH_INFO			OldTouch[OEKAKI_MEMBER_MAX];			// 前回からのポイント履歴

	u8						canvas_buf[OEKAKI_GRAPHI_SIZE];
	u8						*SignBuf;								// トレーナーカードのサイン領域を指すポインタ
	u8						TransWork[0x20*4*2];

	TOUCH_SW_SYS			*TouchSubWindowSys;
	SCRUCH_INFO				scruchInfo;								// こすり検出用ワーク
	int						BeforeX,BeforeY;

#ifdef PM_DEBUG
	int 					frame;									//
	int						framenum[9][2];							//
#endif
};


#endif