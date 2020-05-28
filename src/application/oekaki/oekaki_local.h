//=============================================================================
/**
 * @file	oekaki_local.h
 * @brief	お絵かきボード用構造体定義（内部参照用)
 *          
 * @author	Akito Mori
 * @date    	2006.02.14
 */
//=============================================================================



#ifndef __OEKAKI_LOCAL_H__
#define __OEKAKI_LOCAL_H__

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
#define OEKAKI_BOARD_W	 	( 30 )
#define OEKAKI_BOARD_H	 	( 15 )
#define OEKAKI_GRAPHI_SIZE  ( OEKAKI_BOARD_W*OEKAKI_BOARD_H*32 )

// ボタンセルアクターのペン先定義が始まる番号
#define CELL_BRUSH_NO		( 9 )


// ブラシの大きさ
#define SMALL_BRUSH			( 0 )
#define MIDDLE_BRUSH		( 1 )
#define BIG_BRUSH			( 2 )


// お絵かき禁止フラグ
#define OEKAKI_BAN_NONE		( 0 )
#define OEKAKI_BAN_OFF		( 1 )
#define OEKAKI_BAN_ON		( 2 )

// メインシーケンスの遷移
enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_LEAVE,
	SEQ_OUT,
};

// サブシーケンスの遷移用
enum{
	OEKAKI_MODE_INIT  = 0, 

	OEKAKI_MODE_NEWMEMBER,
	OEKAKI_MODE_NEWMEMBER_WAIT,
	OEKAKI_MODE_NEWMEMBER_END,

	OEKAKI_MODE,

	OEKAKI_MODE_END_SELECT,
	OEKAKI_MODE_END_SELECT_WAIT,
	OEKAKI_MODE_END_SELECT_ANSWER_WAIT,
	OEKAKI_MODE_END_SELECT_ANSWER_OK,
	OEKAKI_MODE_END_SELECT_ANSWER_NG,

    OEKAKI_MODE_END_CHILD,
    OEKAKI_MODE_END_CHILD_WAIT,
    OEKAKI_MODE_END_CHILD_WAIT2,

	OEKAKI_MODE_END_SELECT_PARENT,
    OEKAKI_MODE_END_SELECT_PARENT_WAIT,

	OEKAKI_MODE_FORCE_END,
    OEKAKI_MODE_FORCE_END_WAIT,
    OEKAKI_MODE_FORCE_END_SYNCHRONIZE,
	OEKAKI_MODE_FORCE_END_WAIT_NOP,

	OEKAKI_MODE_END_PARENT_ONLY,
	OEKAKI_MODE_END_PARENT_ONLY_WAIT,

	OEKAKI_MODE_LOGOUT_CHILD,
    OEKAKI_MODE_LOGOUT_CHILD_WAIT,
    OEKAKI_MODE_LOGOUT_CHILD_CLOSE,
    
};


enum{
	OEKAKI_SYNCHRONIZE_END=200,
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
	u8 x[4];	// 最大４回分のタッチ座標
	u8 y[4];	// 
	u8 color:3;	// 選択中のカラー
	u8 size:3;	// サンプリング成功個数
	u8 brush:2; // 選択中のペン先
	u8 banFlag;  // 操作禁止フラグ(親機からのみ送信）
}TOUCH_INFO;

typedef struct{
	u8   x,y;
	u16  size;
}OLD_TOUCH_INFO;

typedef struct{
	u8  chara[1000];
	u32 _xor;
	u8  no;
	u8  dummy[3];
}OEKAKIG_SPLIT_DATA;

//============================================================================================
//	構造体定義
//============================================================================================

struct OEKAKI_WORK{
	GF_BGL_INI		*bgl;
	BOOL			wipe_end;
	OEKAKI_PARAM	*param;

	WORDSET			*WordSet;								// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER *MsgManager;							// 名前入力メッセージデータマネージャー
	STRBUF			*TrainerName[OEKAKI_MEMBER_MAX];		// 名前
	STRBUF			*EndString;								// 文字列「やめる」
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
	CLACT_WORK_PTR			ButtonActWork[12];						// ボタンアクターポインタ

	GF_BGL_BMPWIN 			TrainerNameWin[BMP_OEKAKI_MAX];			// お絵かき画面用BMPウインドウ
	GF_BGL_BMPWIN			OekakiBoard;
	GF_BGL_BMPWIN			MsgWin;									// 会話ウインドウ
	GF_BGL_BMPWIN			EndWin;									// やめる
	GF_BGL_BMPWIN			*YesNoWin[2];								// はい・いいえウインドウのポインタ

	int						proc_seq;								// MainProcのシーケンスを監視するためだけにある
																	// （サブシーケンスは書き換えない）
	int						seq;									// 現在のサブシーケンス状態
	int						next_seq;								// 次のシーケンスは何か？
	int						mode;									// 現在最前面の文字パネル
	int						wait;
	int						connectBackup;							// 直前の接続人数
	int						shareNum;								// 画像送信済みの人数
	int						shareBit;								// 画像送信済みの人数(ビット)
	int						newMemberId;							// 乱入してきた人のID
	
	u8						ConnectCheck[8][2];
	MYSTATUS				*TrainerStatus[8][2];

	u8						SendBoardGraphic[0x4000];
	u16						CursorPal;
	u8						brush_color;
	u8						brush;

	TOUCH_INFO				MyTouchResult;							// 自分のサンプリング結果（これは送信するだけ
	TOUCH_INFO				AllTouchResult[OEKAKI_MEMBER_MAX];		// 通信で取得したサンプリング結果（このデータで描画する
	OLD_TOUCH_INFO			OldTouch[OEKAKI_MEMBER_MAX];			// 前回からのポイント履歴

	u8						*lz_buf;								// 圧縮画像格納領域
	int						send_num;
	u8						canvas_buf[OEKAKI_GRAPHI_SIZE];
	OEKAKIG_SPLIT_DATA		send_buf;
	OEKAKIG_SPLIT_DATA		split_temp[OEKAKI_MEMBER_MAX];

	s32 					err_num;								// 通信終了をみるためのワーク
	u32						ridatu_bit;								// 離脱しようとしている子のBit
	u16						oya_share_num;			// 親が持っているshareNumをもらう
	s16						ridatu_wait;			// 離脱用のウェイト
	u8						status_end;								// TRUE:終了シーケンスへ移行

	// ----親だけが必要なワーク

	TOUCH_INFO				ParentTouchResult[5];
	TOUCH_SW_SYS			*TouchSubWindowSys;
	int						banFlag;
	int						yesno_flag;								// 現在「はい・いいえ」画面を呼び出し中
	int						firstChild;								// 一番最初にやってきたときに子機から乱入宣言されても無視
	int						ireagalJoin;							//お絵かき終了時に乱入されたか
	int						bookJoin;								//乱入予約フラグ
	int						joinBit;								//乱入者ビット
#ifdef PM_DEBUG
	int 					frame;									//
	int						framenum[9][2];							//
#endif
};

//--------------------------------------------------------------
/**
 * @brief   この構造体の中身を替えたら、必ず通信関数テーブルで
 *          CommRecordCornerEndChildを使用している箇所の送受信サイズを変更すること！！
 *			ファイル：comm_command_record.c, comm_command_oekaki.c, comm_command_field.c
 */
//--------------------------------------------------------------
typedef struct{
	u8 ridatu_id;			///<離脱者のID
	u8 oya_share_num;		///<親の持つshareNum
	u8 request;				///<命令コード
	u8 ridatu_kyoka;		///<TRUE:離脱OK、FALSE:離脱NG
}COMM_OEKAKI_END_CHILD_WORK;

enum{
	COEC_REQ_RIDATU_CHECK,		///<離脱確認
	COEC_REQ_RIDATU_EXE,		///<離脱実行
};


extern void OekakiBoardCommSendPokeData(int netID, POKEPARTY *party, int no);
extern void OekakiBoardCommSend(int netID, int command, int pos);
extern void OekakiBoard_MainSeqCheckChange( OEKAKI_WORK *wk, int seq, u8 id );
extern void OekakiBoard_MainSeqForceChange( OEKAKI_WORK *wk, int seq, u8 id  );
extern int OekakiBoard_MyStatusGetNum(void);


#endif
