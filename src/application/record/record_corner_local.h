//=============================================================================
/**
 * @file	record_corner_local.h
 * @brief	お絵かきボード用構造体定義（内部参照用)
 *          
 * @author	Akito Mori
 * @date    	2006.02.14
 */
//=============================================================================


#ifndef __RECORD_CORNER_LOCAL_H__
#define __RECORD_CORNER_LOCAL_H__
// 機能ボタン用定義
#define FUNCBUTTON_NUM	( 7 ) 		// 機能ボタンの数
#define START_WORDPANEL ( 0 )		// 最初の文字入力パネルの番号（０＝ひらがな）

// 接続人数MAXは５人
#define RECORD_CORNER_MEMBER_MAX	( 5 )


// CLACTで定義しているセルが大きすぎてサブ画面に影響がでてしまうので離してみる
#define NAMEIN_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)

// CellActorに処理させるリソースマネージャの種類の数（＝マルチセル・マルチセルアニメは使用しない）
#define CLACT_RESOURCE_NUM		(  4 )
#define NAMEIN_OAM_NUM			( 14 )


// メッセージ表示後のWAIT
#define RECORD_CORNER_MESSAGE_END_WAIT	( 60 )


// 文字パネルの遷移用
enum{
	RECORD_MODE_INIT  = 0, 

	RECORD_MODE_NEWMEMBER,
	RECORD_MODE_NEWMEMBER_END,

	RECORD_MODE,

	RECORD_MODE_END_SELECT,
	RECORD_MODE_END_SELECT_WAIT,
	RECORD_MODE_END_SELECT_ANSWER_WAIT,
	RECORD_MODE_END_SELECT_ANSWER_OK,
	RECORD_MODE_END_SELECT_ANSWER_NG,
	
    RECORD_MODE_END_CHILD,
    RECORD_MODE_END_CHILD_WAIT,

	RECORD_MODE_END_SELECT_PARENT,
    RECORD_MODE_END_SELECT_PARENT_WAIT,

	RECORD_MODE_FORCE_END,
	RECORD_MODE_FORCE_END_MES_WAIT,
    RECORD_MODE_FORCE_END_WAIT,
    RECORD_MODE_FORCE_END_SYNCHRONIZE,

	RECORD_MODE_END_PARENT_ONLY,
	RECORD_MODE_END_PARENT_ONLY_WAIT,

	RECORD_MODE_LOGOUT_CHILD,
    RECORD_MODE_LOGOUT_CHILD_WAIT,
    RECORD_MODE_LOGOUT_CHILD_CLOSE,

	RECORD_MODE_START_SELECT,
	RECORD_MODE_START_SELECT_WAIT,

	RECORD_MODE_START_RECORD_COMMAND,
	RECORD_MODE_RECORD_SEND_DATA,

	RECORD_MODE_RECORD_MIX_DATA,

	RECORD_MODE_COMM_SAVE_START,
    RECORD_MODE_COMM_SAVE,
    RECORD_MODE_END_MES_WAIT,


    RECORD_MODE_MESSAGE_WAIT,
};


enum{
	RECORD_SYNCHRONIZE_END=201,
};

// 上下画面指定定義
#define RES_NUM	( 3 )
#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// 要は０と
#define SUB_LCD		( GF_BGL_SUB_DISP )		// １なんですが。
#define CHARA_RES	( 2 )

// BMPWIN指定
enum{
	BMP_NAME1_S_BG0,
	BMP_NAME2_S_BG0,
	BMP_NAME3_S_BG0,
	BMP_NAME4_S_BG0,
	BMP_NAME5_S_BG0,
	BMP_RECORD_MAX,
};


enum{
	RECORD_EXIST_NO=0,
	RECORD_EXIST_APPEAR_REQ,
	RECORD_EXIST_APPEAR,
	RECORD_EXIST_BYE_REQ,
};

#define RECORD_SEND_DATASIZE	( 3000 )

typedef struct{
	u8  data[RECORD_SEND_DATASIZE];		// レコード交換データ
	u32 _xor;							// データ整合性確認用XOR
	u32 seed;							// 親から来たこの数値を元に乱数を発生させてデータを入れ替える
}RECORD_DATA;


typedef struct{
	int sw;
	int seq;
	int wait;
	void *paldata;
	NNSG2dPaletteData *palbuf;
}VTRANS_PAL_WORK;

//============================================================================================
//	構造体定義
//============================================================================================

struct RECORD_WORK{
	GF_BGL_INI			*bgl;								// GF_BGL_INI
	BOOL				wipe_end;							// ワイプ処理待ち
	RECORD_INPUT_PARAM	*param;								// PROC起動時に貰うパラメータ
	VTRANS_PAL_WORK		palwork;							// パレットアニメ用ワーク
	TCB_PTR				trans_tcb;

	WORDSET			*WordSet;								// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER *MsgManager;							// 名前入力メッセージデータマネージャー
	STRBUF			*TrainerName[RECORD_CORNER_MEMBER_MAX];		// 名前
	STRBUF			*EndString;								// 文字列「やめる」
	STRBUF			*TalkString;							// 会話メッセージ用
	STRBUF			*TitleString;							// タイトルメッセージ用
	int				MsgIndex;								// 終了検出用ワーク

	CLACT_SET_PTR 			clactSet;								// セルアクターセット
	CLACT_U_EASYRENDER_DATA	renddata;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	resObjTbl[RES_NUM][CLACT_RESOURCE_NUM];// リソースオブジェテーブル
	CLACT_HEADER			clActHeader_m;							// セルアクターヘッダー
	CLACT_HEADER			clActHeader_s;							// セルアクターヘッダー
	CLACT_HEADER			clActHeader_friend;							// セルアクターヘッダー
	CLACT_WORK_PTR			MainActWork[NAMEIN_OAM_NUM];				// セルアクターワークポインタ配列
	CLACT_WORK_PTR			SubActWork[NAMEIN_OAM_NUM];				// セルアクターワークポインタ配列

	GF_BGL_BMPWIN 			TrainerNameWin[BMP_RECORD_MAX];			// お絵かき画面用BMPウインドウ
	GF_BGL_BMPWIN			MsgWin;									// 会話ウインドウ
	GF_BGL_BMPWIN			EndWin;									// やめる
	GF_BGL_BMPWIN			TitleWin;								// 「レコードコーナー　ぼしゅうちゅう！」など
	GF_BGL_BMPWIN			*YesNoWin[2];							// はい・いいえウインドウのポインタ
	BMPMENU_WORK			*YesNoMenuWork;

	void*					FieldObjCharaBuf[2];					// 人物OBJキャラファイルデータ
	NNSG2dCharacterData*	FieldObjCharaData[2];					// 人物OBJキャラデータの実ポインタ				
	void*					FieldObjPalBuf[2];						// 人物OBJパレットァイルデータ
	NNSG2dPaletteData*		FieldObjPalData[2];						// 人物OBJパレットファイルデータ


	int						seq;									// 現在の文字入力状態（入力OK/アニメ中）など
	int						nextseq;
	int						mode;									// 現在最前面の文字パネル
	int						wait;
	u8						ConnectCheck[8][2];
	MYSTATUS				*TrainerStatus[RECORD_CORNER_MEMBER_MAX][2];
	int						TrainerReq[RECORD_CORNER_MEMBER_MAX];

	int						saveseq_work;							// セーブシーケンス管理用ワーク

	u16						CursorPal;
	u16						*ObjPaletteTable;
	u8						brush_color;
	u8						brush;

	int						send_num;
	RECORD_DATA				send_data;
	RECORD_DATA				recv_data[RECORD_CORNER_MEMBER_MAX];
	int						recv_count;
	SAVEDATA *				savedata;
	int						banFlag;								// 操作禁止フラグ
	u8						record_execute;							// TRUE:レコード混ぜ中
	// ----親だけが必要なワーク


	volatile int			connectBackup;							// 接続人数監視用
	int						shareNum;
	int						beacon_flag;
	u32						ridatu_bit;								// 離脱しようとしている子のBit
	u8						status_end;								// TRUE:終了シーケンスへ移行
	s8						limit_mode;								// 接続制限状態
	u8						start_num;								// レコード混ぜ開始人数
	u8						record_send;							// TRUE:レコード送信した
	
	// 子機が必要なワーク
	s32 					err_num;								// 通信終了をみるためのワーク
	u16						oya_share_num;			// 親が持っているshareNumをもらう
	s16						ridatu_wait;			// 離脱用のウェイト

#ifdef PM_DEBUG
	int 					frame;									//
	int						framenum[9][2];							//
#endif
};


//--------------------------------------------------------------
//	
//--------------------------------------------------------------
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
}COMM_RECORD_END_CHILD_WORK;

enum{
	CREC_REQ_RIDATU_CHECK,		///<離脱確認
	CREC_REQ_RIDATU_EXE,		///<離脱実行
};



extern void CommCommandRecordInitialize(void* pWork);
extern void RecordCorner_MainSeqCheckChange( RECORD_WORK *wk, int seq, u8 id );
extern void RecordCorner_MainSeqForceChange( RECORD_WORK *wk, int seq, u8 id  );
extern void RecordCornerTitleChange( RECORD_WORK *wk );
extern int RecordCorner_MyStatusGetNum(void);

extern void MakeSendData(SAVEDATA * sv, RECORD_DATA * send_rec);
extern void MixReceiveData(SAVEDATA * sv, const RECORD_DATA * record);

#endif
