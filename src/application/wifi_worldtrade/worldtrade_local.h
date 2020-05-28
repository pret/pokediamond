//=============================================================================
/**
 * @file	worldtrade_local.h
 * @brief	世界交換画面ヘッダファイル
 *          
 * @author	Akito Mori
 * @date    	2006.04.16
 */
//=============================================================================


#ifndef __WORLDTRADE_LOCAL_H__
#define __WORLDTRADE_LOCAL_H__

#include "system/bmp_list.h"
#include "communication/wm_icon.h"
#include "savedata/zukanwork.h"
#include "savedata/wifilist.h"
#include "savedata/wifihistory.h"
#include "application/p_status.h"
#include "demo/demo_trade.h"
#include "battle/shinka.h"

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
	WORLDTRADE_ENTER=0,		// 接続画面
	WORLDTRADE_TITLE,		// タイトル・メニュー
	WORLDTRADE_MYPOKE,		// ようすをみる
	WORLDTRADE_PARTNER,		// あいてのポケモンのようすをみる
	WORLDTRADE_SEARCH,		// ポケモンを検索する
	WORLDTRADE_MYBOX,		// 自分のボックス
	WORLDTRADE_DEPOSIT,		// ほしいポケモンの条件
	WORLDTRADE_UPLOAD,		// ポケモンデータをアップロード
	WORLDTRADE_STATUS,		// ポケモンステータス呼び出し
	WORLDTRADE_DEMO,		// ポケモンステータス呼び出し
};

// サブプロセスに渡すモード（同じサブプロセスでも使い方が違う時があるため）
enum{
	// worldtrade_title.c
	MODE_OPENING=0,				// 初めてきたとき
	MODE_CONTINUE,				// 継続するためにきた
	MODE_NOT_END,				// 一回やめるを選んだが、やめなかった

	// worldtrade_mypoke.c
	MODE_VIEW,					// 預けたポケモンのようすをみる
	MODE_DEPOSIT,				// 検索したポケモンと交換するときにみる

	// worldtrade_box.c
	MODE_DEPOSIT_SELECT,		// 自分からポケモンを預けるとき
	MODE_EXCHANGE_SELECT,		// 検索したポケモンと交換するポケモンを選ぶ
	
	// worldtrade_upload.c
	MODE_UPLOAD,				// ポケモンを預ける画面に行く
	MODE_DOWNLOAD,				// ポケモンを引き取る
	MODE_EXCHANGE,				// ポケモンを交換する
	MODE_DOWNLOAD_EX,
	MODE_SERVER_CHECK,	// ポケモンが交換されているか確認する→メニューへ
//	MODE_SERVER_CHECK,	// ポケモンが交換されているか確認する→ようすをみるへ
	MODE_POKEMON_EVO_SAVE,		// 交換ポケモンが進化した後のセーブ処理

};

// CLACTで定義しているセルが大きすぎてサブ画面に影響がでてしまうので離してみる
#define NAMEIN_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)

// CellActorに処理させるリソースマネージャの種類の数（＝マルチセル・マルチセルアニメは使用しない）
#define CLACT_RESOURCE_NUM		(  4 )
#define NAMEIN_OAM_NUM			( 14 )

#define WORLDTRADE_MESFRAME_PAL	 ( 10 )
#define WORLDTRADE_MENUFRAME_PAL ( 11 )
#define WORLDTRADE_MESFRAME_CHR	 (  1 )
#define WORLDTRADE_MENUFRAME_CHR ( WORLDTRADE_MESFRAME_CHR + TALK_WIN_CGX_SIZ )
#define WORLDTRADE_TALKFONT_PAL	 ( 13 )

// 会話ウインドウ表示位置定義
#define TALK_WIN_X		(  2 )
#define TALK_WIN_Y		( 19 )
#define	TALK_WIN_SX		( 27 )
#define	TALK_WIN_SY		(  4 )


// １行メッセージウインドウ表示位置定義
#define LINE_TEXT_X		(  2 )
#define LINE_TEXT_Y		( 21 )
#define	LINE_TEXT_SX	( 27 )
#define	LINE_TEXT_SY	(  2 )


// 画面上部タイトルウインドウ表示位置定義
#define TITLE_TEXT_X	(  1 )
#define TITLE_TEXT_Y	(  1 )
#define TITLE_TEXT_SX	( 28 )
#define TITLE_TEXT_SY	(  2 )

#define HEAD_LIST_X		( 15 )
#define HEAD_LIST_Y		(  5 )
#define HEAD_LIST_SX	(  4 )
#define HEAD_LIST_SY	( 13 )

#define NAME_LIST_X		( 21 )
#define NAME_LIST_Y		(  5 )
#define NAME_LIST_SX	( 10 )
#define NAME_LIST_SY	( 13 )


// 選択リストの位置・幅定義(_deposit.c _search.c)
// 頭文字
#define SELECT_MENU1_X	(  15 )
#define SELECT_MENU1_Y 	(   5 )
#define SELECT_MENU1_SX	(   4 )
#define SELECT_MENU1_SY	(  13 )

// ポケモン名
#define SELECT_MENU2_X	(  21 )
#define SELECT_MENU2_Y 	(   5 )
#define SELECT_MENU2_SX	(  10 )
#define SELECT_MENU2_SY	(  13 )

// 性別
#define SELECT_MENU3_X	(  21 )
#define SELECT_MENU3_Y 	(  10 )
#define SELECT_MENU3_SX	(  10 )
#define SELECT_MENU3_SY	(   8 )

// 欲しいレベル
#define SELECT_MENU4_X	(  15 )
#define SELECT_MENU4_Y 	(   5 )
#define SELECT_MENU4_SX	(  16 )
#define SELECT_MENU4_SY	(  13 )


// はい・いいえウインドウのY座標
#define	WORLDTRADE_YESNO_PY2	( 13 )		// 会話ウインドウが２行の時
#define	WORLDTRADE_YESNO_PY1	( 15 )		// 会話ウインドウが１行の時

// タイトル文字列バッファ長
#define TITLE_MESSAGE_BUF_NUM	( 20 * 2 )

// 会話ウインドウ文字列バッファ長
#define TALK_MESSAGE_BUF_NUM	( 90*2 )

#define DWC_ERROR_BUF_NUM		(16*8*2)

// ボックストレい名
#define BOX_TRAY_NAME_BUF_NUM	( 9*2 )

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

// １画面のボックスの中のポケモンの数
#define BOX_POKE_NUM		( 30 )

// ポケモンアイコンのパレットを転送するオフセット
#define POKEICON_PAL_OFFSET				(  3 )

// 選択できないポケモンアイコンのパレット
#define POKEICON_NOTSELECT_PAL_OFFSET	(  6 )

// ポケモンアイコンが始まるVRAM上でのオフセット
#define POKEICON_VRAM_OFFSET ( 12 )

// ５０音順のポケモンの頭文字の数（アカサタナハマヤラワ）
#define HEADWORD_NUM		( 10 )

// アイテム・メールアイコンのセルアニメ番号
#define CELL_ITEMICON_NO	( 40 )
#define CELL_MAILICON_NO	( 41 )
#define CELL_CBALLICON_NO	( 42 )

// ボックス横の矢印
#define CELL_BOXARROW_NO	( 38 )


// ポケモン検索
#define SEARCH_POKE_MAX		(  7 )

#define SUB_OBJ_NUM			(  8 )

// 1秒待つ
#define WAIT_ONE_SECONDE_NUM	( 30 )

// ワイプのスピード
#define WORLDTRADE_WIPE_SPPED	( 6 )

// サーバー確認ができるようになるまでの秒数（６０秒）
#define SEVER_RETRY_WAIT		( 60*30 )


//============================================================================================
//	構造体定義
//============================================================================================

// ポケモンを預ける際の情報
typedef struct{

	// ポケモンの種族名を格納するテーブル（2重にALLOCする）
	STRBUF **pokename;

	// ポケモン預け・検索共用
	u16		headwordPos;		// 選択頭カーソル位置
	u16		headwordListPos;	// 選択リスト位置
	u16		namePos;			// 名前選択カーソル位置
	u16		nameListPos;		// 名前選択リスト位置
	int		sexPos;				// 性別カーソル位置
	int		levelPos;			// レベルカーソル位置

	u8		*sinouTable;		// シンオウ図鑑データ（数値は開発NO）
	u16		*nameSortTable;		// ポケモン名ソートテーブル読み込みポインタ
	int		nameSortNum;		// 頭文字
	int		sex_selection;		// 選択したポケモンの性別分布率


	// ポケモン検索画面用
	int		cursorSide;			// 
	int		leftCursorPos;
	int		rightCursorPos;

}DEPOSIT_WORK;

typedef struct{
	Dpw_Tr_PokemonDataSimple	info[BOX_POKE_NUM];
}BOX_RESEARCH;

// 一度交換したポケモンが進化した時のために、2回目の書き込み位置を保存しておく構造体
typedef struct{
	int boxno;
	int pos;
}EVOLUTION_POKEMON_INFO;

#define NAME_HEAD_MAX	( 10 )	// [アカサタナハマヤラワ]の数は１０個

typedef struct{
	u16 head_list,head_pos;

	u16 name_list[NAME_HEAD_MAX];
	u16 name_pos[NAME_HEAD_MAX];
}SELECT_LIST_POS;

struct WORLDTRADE_WORK{
	// 起動時に貰ってるもの
	WORLDTRADE_PARAM *param;							// 呼び出し時パラメータ
	GF_BGL_INI		*bgl;								// GF_BGL_INI
	WIFI_LIST		*wifilist;							// wifi接続データ・友達データ
	
	
	// 世界交換システムに関わるもの
	int				seq;								// 現在の世界交換画面の状態
	int				nextseq;							// 現在のシーケンスが終了した際の遷移先

	int				sub_process;						// 世界交換サブプログラム制御ナンバー
	int				sub_nextprocess;					// 世界交換サブNEXT制御ナンバー
	int				sub_returnprocess;					// nextプロセスを呼んで終了した時の戻りプロセス
	int				old_sub_process;					// 一つ前のサブプロセスを保存しておく
	int				sub_process_mode;					// その画面にきたモードは何か？
	int				error_mes_no;

	int				subprocess_seq;						// サブプログラムシーケンスNO
	int				subprocess_nextseq;					// サブプログラムNEXTシーケンスNO

	u16				OpeningFlag;						// 世界交換タイトルを見たか？
	u16				DepositFlag;						// ポケモンを既にサーバーに預けているか？（1:預けている）
	u16				ExchangeFlag;						// 預けたポケモンが交換されていた
	u16				serverWaitTime;						// サーバーにアクセスできないようにさせるタイマー

	int				ConnectErrorNo;						// DWC・またはサーバーからのエラー
	int				ErrorRet;
	int				ErrorCode;

	void 			*heapPtr;							// NitroDWCに渡すヒープワークの解放用ポインタ
	NNSFndHeapHandle heapHandle;						// heapPtrを32バイトアライメントに合わせたポインタ
	DWCInetControl   stConnCtrl;							// DWC接続ワーク

	PROC			*proc;								// スタータス呼び出し用サブプロセスデータ
	PSTATUS_DATA	 statusParam;						// スタータス呼び出し用パラメータ
	DEMO_TRADE_PARAM tradeDemoParam;					// 交換デモパラメータ
	SHINKA_WORK		 *shinkaWork;						// 通信進化デモ用ワーク
	int				 subprocflag;						// ステータスや交換デモを呼び出すためのフラグ
	u16				listpos;				
	u16				dummy;

	// 各画面をぬけても保存されてるもの
	u16				TitleCursorPos;						// タイトルメニューのカーソル位置
	u16				PartnerPageInfo;					// 左・右ページのどちらをみているか？
	u16				BoxTrayNo;							// 何番ボックスを見ているか？
	u16				BoxCursorPos;						// ボックス上でのカーソルの位置
	POKEMON_PASO_PARAM	*deposit_ppp;					// 一旦預ける指定になったポケモンのポインタ
	int				SearchResult;						// 検索の結果返ってきた数
	int				TouchTrainerPos;					// 検索結果の誰をタッチしたか
	MYSTATUS		*partnerStatus;						// 交換デモようにでっちあげるMYSTATUS;
	EVOLUTION_POKEMON_INFO EvoPokeInfo;


	Dpw_Tr_Data		UploadPokemonData;					// 送信データ
	Dpw_Tr_Data		DownloadPokemonData[SEARCH_POKE_MAX];// 検索結果データ
	Dpw_Tr_Data		ExchangePokemonData;				// 交換結果データ
	Dpw_Tr_PokemonDataSimple Post;
	Dpw_Tr_PokemonSearchData Want;
	Dpw_Tr_PokemonSearchData Search;
	Dpw_Tr_PokemonSearchData SearchBackup;				// 同じ検索はできないようにするために



	// 描画まわりのワーク（主にBMP用の文字列周り）
	WORDSET			*WordSet;								// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER *MsgManager;							// 名前入力メッセージデータマネージャー
	MSGDATA_MANAGER *MonsNameManager;						// ポケモン名メッセージデータマネージャー
	MSGDATA_MANAGER *LobbyMsgManager;						// 名前入力メッセージデータマネージャー
	MSGDATA_MANAGER *SystemMsgManager;						// Wifiシステムメッセージデータ
	STRBUF			*BoxTrayNameString;						// ボックストレイ名
	STRBUF			*EndString;								// 文字列「やめる」
	STRBUF			*TalkString;							// 会話メッセージ用
	STRBUF			*TitleString;							// タイトルメッセージ用
	STRBUF			*InfoString[10];						// タイトルメッセージ用
	STRBUF			*ErrorString;
	int				MsgIndex;								// 終了検出用ワーク


	// 描画周りのワーク（主にOAM)
	CLACT_SET_PTR 			clactSet;								// セルアクターセット
	CLACT_U_EASYRENDER_DATA	renddata;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	resObjTbl[RES_NUM][CLACT_RESOURCE_NUM];// リソースオブジェテーブル
	CLACT_HEADER			clActHeader_main;							// セルアクターヘッダー
	CLACT_HEADER			clActHeader_sub;							// セルアクターヘッダー
	CLACT_HEADER			clActHeader_friend;						// セルアクターヘッダー
	CLACT_WORK_PTR			CursorActWork;							// セルアクターワークポインタ配列
	CLACT_WORK_PTR			FingerActWork;							// セルアクターワークポインタ配列
	CLACT_WORK_PTR			PokeIconActWork[BOX_POKE_NUM];			// ポケモンアイコンアクター
	CLACT_WORK_PTR			ItemIconActWork[BOX_POKE_NUM];			// アイテムアイコンアクター
	CLACT_WORK_PTR			CBallActWork[6];						// カスタムボールアイコンアクター
	CLACT_WORK_PTR			PokemonActWork;				// セルアクターワークポインタ配列
	CLACT_WORK_PTR			SubActWork[SUB_OBJ_NUM];				// サブ画面用ＯＢＪポインタ
	CLACT_WORK_PTR			BoxArrowActWork[2];						// ボックス名の横にある矢印

	// BMPWIN描画周り
	GF_BGL_BMPWIN			MsgWin;									// 会話ウインドウ
	GF_BGL_BMPWIN			NumberWin;								// やめる
	GF_BGL_BMPWIN			TitleWin;								// 「レコードコーナー　ぼしゅうちゅう！」など
	GF_BGL_BMPWIN			SubWin;									// 「レコードコーナー　ぼしゅうちゅう！」など
	GF_BGL_BMPWIN			MenuWin[3];								// メニュー用BMPWIN
	GF_BGL_BMPWIN			InfoWin[11];	
	GF_BGL_BMPWIN			TalkWin;


	BMP_MENULIST_DATA		*BmpMenuList;
	BMPMENU_WORK			*YesNoMenuWork;
	BMPMENU_WORK 			*BmpMenuWork;
	BMPLIST_WORK 			*BmpListWork;
	void*					timeWaitWork;							// 会話ウインドウ横アイコンワーク

	int						wait;



	// 画面毎に使うことがあるワーク
	DEPOSIT_WORK			*dw;


	// worldtrade_upload.c用ワーク
	u16						saveNextSeq1st;						// セーブの前半終了時に飛ぶシーケンス
	u16						saveNextSeq2nd;						// セーブの後半終了時に飛ぶシーケンス

	// worldtrade_sublcd.c用ワーク
	TCB_PTR					demotask;							// 主人公デモ用タスクポインタ
	u16						demo_end;							// デモ終了フラグ
	u16						SubLcdTouchOK;						// 人物OBJがでてきてから触れるようになるフラグ
	void*					FieldObjCharaBuf;					// 人物OBJキャラファイルデータ
	NNSG2dCharacterData*	FieldObjCharaData;					// 人物OBJキャラデータの実ポインタ				
	void*					FieldObjPalBuf;						// 人物OBJパレットァイルデータ
	NNSG2dPaletteData*		FieldObjPalData;					// 人物OBJパレットファイルデータ

	// worldtrade_demo.c用ワーク
	POKEMON_PARAM *demoPokePara;


	// worldtrade_box.c用ワーク
	BOX_RESEARCH			*boxWork;
	u16						boxPokeNum;								// ボックスにいるポケモンの総数
	u16						boxSearchFlag;							// ボックスの総数を取得するためのフラグ
	u32	sub_out_flg;		// 下画面フェードコントロール
	
	void *boxicon;
	void (*vfunc)(void *);

	// worldtrade_deposit.c worldtrade_search.cで兼用
	SELECT_LIST_POS			selectListPos;
	
#ifdef PM_DEBUG
	int 					frame;									//
	int						framenum[9][2];							//
#endif
};


//============================================================================================
// SE用定義
//============================================================================================
#define WORLDTRADE_MOVE_SE		(SEQ_SE_DP_SELECT)
#define WORLDTRADE_DECIDE_SE	(SEQ_SE_DP_SELECT)


//============================================================================================
//	デバッグ用
//============================================================================================
//#define	GTS_FADE_OSP	// フェード場所表示用定義


//============================================================================================
// extern宣言
//============================================================================================
// worldtrade.c
extern void WorldTrade_MakeCLACT(CLACT_ADD *add, WORLDTRADE_WORK *wk, CLACT_HEADER *header, int param);
extern BMPMENU_WORK *WorldTrade_BmpWinYesNoMake( GF_BGL_INI *bgl, int y, int yesno_bmp_cgx );
extern void WorldTrade_SetNextSeq( WORLDTRADE_WORK *wk, int to_seq, int next_seq );
extern void WorldTrade_SetNextProcess( WORLDTRADE_WORK *wk, int next_process );
extern void WorldTrade_ActPos( CLACT_WORK_PTR act, int x, int y );
extern  int WorldTrade_WifiLinkLevel( void );
extern void WorldTrade_BmpWinPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int msgno, u16 dat );
extern void WorldTrade_SysPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color );
extern void WorldTrade_TalkPrint( GF_BGL_BMPWIN *win, STRBUF *strbuf, int x, int y, int flag, GF_PRINTCOLOR color );

extern void WorldTrade_WifiIconAdd( WORLDTRADE_WORK *wk );
extern void Enter_MessagePrint( WORLDTRADE_WORK *wk, MSGDATA_MANAGER *msgman, int msgno, int wait, u16 dat );
extern void WorldTrade_SubProcessChange( WORLDTRADE_WORK *wk, int subprccess, int mode );
extern WINTYPE WorldTrade_GetMesWinType( WORLDTRADE_WORK *wk );
extern int WorldTrade_GetTalkSpeed( WORLDTRADE_WORK *wk );
extern void FreeFieldObjData( WORLDTRADE_WORK *wk );
extern void WorldTrade_BoxPokeNumGetStart( WORLDTRADE_WORK *wk );
extern void WorldTrade_SubProcessUpdate( WORLDTRADE_WORK *wk );
extern void WorldTrade_TimeIconAdd( WORLDTRADE_WORK *wk );
extern void WorldTrade_TimeIconDel( WORLDTRADE_WORK *wk );


// worldtrade_sublcd.c
extern void WorldTrade_HeroDemo( WORLDTRADE_WORK *wk, int sex );
extern int  WorldTrade_SubLcdObjHitCheck( int max );
void WorldTrade_SubLcdMatchObjAppear( WORLDTRADE_WORK *wk, int num, int flag );
extern void WorldTrade_SubLcdMatchObjHide( WORLDTRADE_WORK *wk );
extern void WorldTrade_SubLcdActorAdd( WORLDTRADE_WORK *wk, int sex );
extern void WorldTrade_ReturnHeroDemo( WORLDTRADE_WORK *wk, int sex );


// worldtrade_enter.c
extern int  WorldTrade_Enter_End( WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_Enter_Main(WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_Enter_Init(WORLDTRADE_WORK *wk, int seq);

// worldtrade_title.c
extern int  WorldTrade_Title_End( WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_Title_Main(WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_Title_Init(WORLDTRADE_WORK *wk, int seq);
extern void WorldTrade_SubLcdBgGraphicSet( WORLDTRADE_WORK *wk );



// worldtrade_mypoke.c
extern int  WorldTrade_MyPoke_Init(WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_MyPoke_Main(WORLDTRADE_WORK *wk, int seq);
extern int  WorldTrade_MyPoke_End(WORLDTRADE_WORK *wk, int seq);
extern void WorldTrade_PokeInfoPrint( 	MSGDATA_MANAGER *MsgManager,
							MSGDATA_MANAGER *MonsNameManager, 	
							WORDSET *WordSet, 
							GF_BGL_BMPWIN win[], 	
							POKEMON_PASO_PARAM *ppp,
							Dpw_Tr_PokemonDataSimple *post );
extern void WorldTrade_PokeInfoPrint2( MSGDATA_MANAGER *MsgManager, GF_BGL_BMPWIN win[], STRCODE *name );
extern void WorldTrade_TransPokeGraphic( POKEMON_PARAM *pp );


// worldtrade_partner.c
extern int WorldTrade_Partner_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Partner_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Partner_End(WORLDTRADE_WORK *wk, int seq);

// worldtrade_search.c
extern int WorldTrade_Search_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Search_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Search_End(WORLDTRADE_WORK *wk, int seq);

// worldtrade_box.c
extern int WorldTrade_Box_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Box_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Box_End(WORLDTRADE_WORK *wk, int seq);
extern POKEMON_PASO_PARAM *WorldTrade_GetPokePtr( POKEPARTY *party, BOX_DATA *box,  int  tray, int pos );
extern int WorldTrade_GetPPorPPP( int tray );
extern BOOL WorldTrade_PokemonMailCheck( POKEMON_PARAM *pp );

// workdtrade_deposit.c
extern int WorldTrade_Deposit_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Deposit_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Deposit_End(WORLDTRADE_WORK *wk, int seq);
extern void WodrldTrade_PokeWantPrint( MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager,
		WORDSET *WordSet, GF_BGL_BMPWIN win[], int monsno, int sex, int level );
extern void WodrldTrade_MyPokeWantPrint( MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager,
	WORDSET *WordSet, GF_BGL_BMPWIN win[], int monsno, int sex, int level );

extern BMPLIST_WORK *WorldTrade_WordheadBmpListMake( WORLDTRADE_WORK *wk, BMP_MENULIST_DATA **menulist, 
													GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager );
extern BMPLIST_WORK *WorldTrade_PokeNameListMake( WORLDTRADE_WORK *wk, BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, 
			MSGDATA_MANAGER *MsgManager, MSGDATA_MANAGER *MonsNameManager, DEPOSIT_WORK* dw, ZUKAN_WORK *zukan);
extern BMPLIST_WORK *WorldTrade_SexSelectListMake( BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager  );
extern BMPLIST_WORK *WorldTrade_LevelListMake(BMP_MENULIST_DATA **menulist, GF_BGL_BMPWIN *win, MSGDATA_MANAGER *MsgManager  );
extern const int WorldTrade_WantLevelTable[];
extern const int WorldTrade_SexStringTable[];
extern u16* WorldTrade_ZukanSortDataGet( int heap, int idx, int* p_arry_num );

void WorldTrade_PokeNamePrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *nameman, int monsno, int flag, int y, GF_PRINTCOLOR color );
void WorldTrade_SexPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int sex, int flag, int y, int printflag, GF_PRINTCOLOR color );
void WorldTrade_WantLevelPrint( GF_BGL_BMPWIN *win, MSGDATA_MANAGER *msgman, int level, int flag, int y, GF_PRINTCOLOR color );
extern void WorldTrade_PostPokemonBaseDataMake( Dpw_Tr_Data *dtd, WORLDTRADE_WORK *wk );
extern int WorldTrade_SexSelectionCheck( Dpw_Tr_PokemonSearchData *dtp, int sex_selection );
extern int WorldTrade_LevelTermGet( int min, int max );
extern void WorldTrade_LevelMinMaxSet( Dpw_Tr_PokemonSearchData *dtps, int index );
extern u8 *WorldTrade_SinouZukanDataGet( int heap  );
extern u32 WorldTrade_BmpListMain( BMPLIST_WORK * lw, u16 *posbackup );
extern void WorldTrade_SelectListPosInit( SELECT_LIST_POS *slp);
extern void WorldTrade_SelectNameListBackup( SELECT_LIST_POS *slp, int head, int list, int pos );


// workdtrade_uploade.c
extern int WorldTrade_Upload_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Upload_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Upload_End(WORLDTRADE_WORK *wk, int seq);

// workdtrade_status.c
extern int WorldTrade_Status_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Status_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Status_End(WORLDTRADE_WORK *wk, int seq);

// workdtrade_demo.c
extern int WorldTrade_Demo_Init(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Demo_Main(WORLDTRADE_WORK *wk, int seq);
extern int WorldTrade_Demo_End(WORLDTRADE_WORK *wk, int seq);


#endif
