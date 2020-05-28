//=============================================================================
/**
 * @file	wbtower_local.h
 * @brief	WIFIバトルタワー処理ヘッダファイル
 *          
 * @author	Akito Mori
 * @date    	2006.05.16
 */
//=============================================================================


#ifndef __WBTOWER_LOCAL_H__
#define __WBTOWER_LOCAL_H__

#include "communication/wm_icon.h"
#include "system/bmp_list.h"


// Proc_Mainシーケンス定義
enum {
	SEQ_INIT_DPW=0,
	SEQ_INIT,
	SEQ_FADEIN,
	SEQ_MAIN,
	SEQ_FADEOUT,
	SEQ_OUT,
};

// サブプロセス制御番号
enum{
	WBTOWER_ENTER=0,		// 接続画面
};

// サブプロセスに渡すモード（同じサブプロセスでも使い方が違う時があるため）
enum{
	MODE_DOWNLOAD=0,
	MODE_UPLOAD,
};

// CLACTで定義しているセルが大きすぎてサブ画面に影響がでてしまうので離してみる
#define WBTOWER_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)

// CellActorに処理させるリソースマネージャの種類の数（＝マルチセル・マルチセルアニメは使用しない）
#define CLACT_RESOURCE_NUM		(  4 )
#define NAMEIN_OAM_NUM			( 14 )

#define WBTOWER_MESFRAME_PAL	 ( 10 )
#define WBTOWER_MENUFRAME_PAL    ( 11 )
#define WBTOWER_MESFRAME_CHR	 (  1 )
#define WBTOWER_MENUFRAME_CHR 	 ( WBTOWER_MESFRAME_CHR + TALK_WIN_CGX_SIZ )
#define WBTOWER_TALKFONT_PAL	 ( 13 )

// 会話ウインドウ表示位置定義
#define TALK_WIN_X		(  2 )
#define TALK_WIN_Y		( 19 )
#define	TALK_WIN_SX		( 27 )
#define	TALK_WIN_SY		(  4 )


// 画面上部タイトルウインドウ表示位置定義
#define TITLE_TEXT_X	(  4 )
#define TITLE_TEXT_Y	(  1 )
#define TITLE_TEXT_SX	( 24 )
#define TITLE_TEXT_SY	(  2 )


// はい・いいえウインドウのY座標
#define	WBTOWER_YESNO_PY2	( 13 )		// 会話ウインドウが２行の時

// タイトル文字列バッファ長
#define TITLE_MESSAGE_BUF_NUM	( 20 * 2 )

// 会話ウインドウ文字列バッファ長
#define TALK_MESSAGE_BUF_NUM	( 90*2 )

// ランク・ルーム番号の文字列上限
#define NUMBER_BUF_NUM			( 4 )
#define RANK_BUF_NUM			( 3 )

// ランク数値の上限
#define WIFITOWER_RANK_MAX		( 10 )

// １秒待つ用の定義
#define WAIT_ONE_SECONDE_NUM	( 30 )

// 上下画面指定定義
#define RES_NUM		( 3 )
#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// 要は０と
#define SUB_LCD		( GF_BGL_SUB_DISP )		// １なんですが。
#define CHARA_RES	( 2 )

#define DWC_ERROR_BUF_NUM		(16*8*2)

//============================================================================================
//	構造体定義
//============================================================================================



struct WBTOWER_WORK{
	// 起動時に貰ってるもの
	WBTOWER_PARAM *param;								// 呼び出し時パラメータ
	GF_BGL_INI		*bgl;								// GF_BGL_INI
	
	
	// WIFIバトルタワーシステムに関わるもの
	int				seq;								// 現在の世界交換画面の状態
	int				nextseq;							// 現在のシーケンスが終了した際の遷移先

	int				sub_process;						// 世界交換サブプログラム制御ナンバー
	int				sub_nextprocess;					// 世界交換サブNEXT制御ナンバー
	int				sub_process_mode;					// その画面にきたモードは何か？

	int				subprocess_seq;						// サブプログラムシーケンスNO
	int				subprocess_nextseq;					// サブプログラムNEXTシーケンスNO


	void 			*heapPtr;							// NitroDWCに渡すヒープワークの解放用ポインタ
	NNSFndHeapHandle heapHandle;						// heapPtrを32バイトアライメントに合わせたポインタ
	DWCInetControl  stConnCtrl;							// DWC接続ワーク


	// 各画面をぬけても保存されてるもの
	int				Rank;
	int				NowRank;
	int				RoomNum;
	int				NowRoom;
	Dpw_Bt_Room 	roomBtData;							// ダウンロードしたデータを格納する
	Dpw_Bt_Player	BtPlayer;							// 勝ち抜いた自分のデータ

	u16				TitleCursorPos;						// タイトルメニューのカーソル位置
	u16				PartnerPageInfo;					// 左・右ページのどちらをみているか？
	u16				BoxTrayNo;							// 何番ボックスを見ているか？
	u16				BoxCursorPos;						// ボックス上でのカーソルの位置
	POKEMON_PASO_PARAM	*deposit_ppp;					// 一旦預ける指定になったポケモンのポインタ
	int				SearchResult;						// 検索の結果返ってきた数
	int				TouchTrainerPos;					// 検索結果の誰をタッチしたか


	// 描画まわりのワーク（主にBMP用の文字列周り）
	WORDSET			*WordSet;								// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER *MsgManager;							// 名前入力メッセージデータマネージャー
	MSGDATA_MANAGER *LobbyMsgManager;						// 名前入力メッセージデータマネージャー
	MSGDATA_MANAGER *SystemMsgManager;						// Wifiシステムメッセージデータ
	STRBUF			*TalkString;							// 会話メッセージ用
	STRBUF			*TitleString;							// タイトルメッセージ用
	STRBUF			*RoomString;							// 部屋番号選択用
	STRBUF			*RankString;							// ランク選択用
	STRBUF			*ErrorString;							// ランク選択用
	int				MsgIndex;								// 終了検出用ワーク


	// 描画周りのワーク（主にOAM)
	CLACT_SET_PTR 			clactSet;								// セルアクターセット
	CLACT_U_EASYRENDER_DATA	renddata;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	resObjTbl[RES_NUM][CLACT_RESOURCE_NUM]; // リソースオブジェテーブル
	CLACT_HEADER			clActHeader_main;						// セルアクターヘッダー
	CLACT_HEADER			clActHeader_sub;						// セルアクターヘッダー
	CLACT_HEADER			clActHeader_friend;						// セルアクターヘッダー
	CLACT_WORK_PTR			ArrowActWork[2];						// セルアクターワークポインタ配列

	// BMPWIN描画周り
	GF_BGL_BMPWIN			MsgWin;									// 会話ウインドウ
	GF_BGL_BMPWIN			RankWin;								// ランク指定用ウインドウ
	GF_BGL_BMPWIN			NumberWin;								// 部屋ナンバー指定用ウインドウ
	GF_BGL_BMPWIN			TitleWin;								// 「レコードコーナー　ぼしゅうちゅう！」など
	GF_BGL_BMPWIN			SubWin;									// 「レコードコーナー　ぼしゅうちゅう！」など
	GF_BGL_BMPWIN			MenuWin[3];								// メニュー用BMPWIN
	GF_BGL_BMPWIN			InfoWin[11];	


	BMPMENU_WORK			*YesNoMenuWork;
	void*					timeWaitWork;							// 会話ウインドウ横アイコンワーク

	int						ErrorRet;
	int						ErrorCode;
	int						ConnectErrorNo;

	int						wait;

};


//============================================================================================
// SE用定義
//============================================================================================
#define WBTOWER_MOVE_SE		(SEQ_SE_DP_SELECT)
#define WBTOWER_DECIDE_SE	(SEQ_SE_DP_SELECT)


//============================================================================================
// extern宣言
//============================================================================================
// worldtrade.c
extern void WBTower_MakeCLACT(CLACT_ADD *add, WBTOWER_WORK *wk, CLACT_HEADER *header, int param);
extern BMPMENU_WORK *WBTower_BmpWinYesNoMake( GF_BGL_INI *bgl, int y, int yesno_bmp_cgx );
extern void WBTower_SetNextSeq( WBTOWER_WORK *wk, int to_seq, int next_seq );
extern void WBTower_SetNextProcess( WBTOWER_WORK *wk, int next_process );
extern void WBTower_ActPos( CLACT_WORK_PTR act, int x, int y );
extern  int WBTower_WifiLinkLevel( void );
extern void WBTower_BmpWinPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int msgno, u16 dat );
extern void WBTower_SysPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color );
extern void WBTower_TalkPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color );

extern void WBTower_WifiIconAdd( WBTOWER_WORK *wk );
extern void WBTower_SubProcessChange( WBTOWER_WORK *wk, int subprccess, int mode );


// worldtrade_enter.c
extern int WBTower_EnterEnd( WBTOWER_WORK *wk, int seq);
extern int WBTower_EnterMain(WBTOWER_WORK *wk, int seq);
extern int WBTower_EnterInit(WBTOWER_WORK *wk, int seq);


// workdtrade_uploadf.c
extern int WBTower_Upload_Init(WBTOWER_WORK *wk, int seq);
extern int WBTower_Upload_Main(WBTOWER_WORK *wk, int seq);
extern int WBTower_Upload_End(WBTOWER_WORK *wk, int seq);


#endif /* __WBTOWER_LOCAL_H__ */