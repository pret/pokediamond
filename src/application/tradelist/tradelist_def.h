//============================================================================================
/**
 * @file	tradelist_def.h
 * @bfief	ポケモン交換リスト画面用ヘッダ
 * @author	Akito Mori
 * @date	05.12.08
 */
//============================================================================================

#ifndef __TRADELIST_DEF_H__
#define __TRADELIST_DEF_H__

#include "savedata/wifilist.h"
#include "savedata/sp_ribbon.h"
#include "system/bmp_list.h"
#include "savedata/perapvoice.h"
#include "application/tradelist.h"
#include "application/p_status.h"
//---------------------------------------------------------------
//--BMPWIN用定義-------------------------------------------------
//---------------------------------------------------------------

#define TRADELIST_WIN_OFFSET	( 1 )		// BGVRAMのスタートからここまではウインドウ枠用に空けておく



// 上の画面のトレーナー名
#define TRADELIST_MYNAME_X			(  2  )
#define TRADELIST_FRIENDNAME_X		(  20 )
#define TRADELIST_NAME_Y			(   1 )
#define TRADELIST_NAME_W			(  10 )
#define TRADELIST_NAME_H			(   2 )
#define MAIN_MYNAMEBMP_OFFSET   	( TRADELIST_WIN_OFFSET )
#define MAIN_FRIENDNAMEBMP_OFFSET	( MAIN_MYNAMEBMP_OFFSET + ( TRADELIST_NAME_W * TRADELIST_NAME_H))

//上の画面の「おわり」
#define TRADELIST_ENDSTR_X		(  26 )
#define TRADELIST_ENDSTR_Y		(  21 )
#define TRADELIST_ENDSTR_W		(   5 )
#define TRADELIST_ENDSTR_H		(   2 )
#define MAIN_ENDSTRBMP_OFFSET   ( MAIN_FRIENDNAMEBMP_OFFSET + ( TRADELIST_NAME_W * TRADELIST_NAME_H))


// ポケモンの名前(12個分）
#define TRADELIST_POKENAME_X	(  0 )
#define TRADELIST_POKENAME_Y	(  7 )
#define TRADELIST_POKENAME_W	(  8 )
#define TRADELIST_POKENAME_H	(  2 )
#define TRADELIST_POKENAME_OFSX	(  8 )
#define TRADELIST_POKENAME_OFSY	(  5 )
#define MAIN_POKENAME_OFFSET	( MAIN_ENDSTRBMP_OFFSET    + (TRADELIST_ENDSTR_W*TRADELIST_ENDSTR_H))

#define TRADE_EX_MYPOKENAME_X 	(  4 )
#define TRADE_EX_MYPOKENAME_Y	( 10 )
#define TRADE_EX_F_POKENAME_X 	( 20 )
#define TRADE_EX_F_POKENAME_Y   ( 10 )



// 上の画面のメッセージウインドウ１（１列版）
#define TRADELIST_TALKWIN1_X	(   2 )
#define TRADELIST_TALKWIN1_Y	(  21 )
#define TRADELIST_TALKWIN1_W	(  20 )
#define TRADELIST_TALKWIN1_H	(   2 )
#define MAIN_TALKWIN1_OFFSET    (   1 )

// 上の画面のメッセージウインドウ2（2列版・短い）
#define TRADELIST_TALKWIN2_X	(   2 )
#define TRADELIST_TALKWIN2_Y	(  19 )
#define TRADELIST_TALKWIN2_W	(  14 )
#define TRADELIST_TALKWIN2_H	(   4 )
#define MAIN_TALKWIN2_OFFSET    ( TRADELIST_TALKWIN1_W * TRADELIST_TALKWIN1_H )

// 上の画面のメッセージウインドウ3（2列版・長い）
#define TRADELIST_TALKWIN3_X	(   2 )
#define TRADELIST_TALKWIN3_Y	(  19 )
#define TRADELIST_TALKWIN3_W	(  27 )
#define TRADELIST_TALKWIN3_H	(   4 )
#define MAIN_TALKWIN3_OFFSET    ( TRADELIST_TALKWIN2_W * TRADELIST_TALKWIN2_H )

// 上の画面の選択ウインドウ1( ３列版）
#define TRADELIST_SELECT1_X		(  20 )
#define TRADELIST_SELECT1_Y		(  17 )
#define TRADELIST_SELECT1_W		(  11 )
#define TRADELIST_SELECT1_H		(   6 )
#define MAIN_SELECT1_OFFSET     ( MAIN_TALKWIN3_OFFSET + (TRADELIST_TALKWIN3_W*TRADELIST_TALKWIN3_H ))

// 上の画面の選択ウインドウ2( 2列版）
#define TRADELIST_SELECT2_X		(  20 )
#define TRADELIST_SELECT2_Y		(  19 )
#define TRADELIST_SELECT2_W		(  11 )
#define TRADELIST_SELECT2_H		(   4 )
#define MAIN_SELECT2_OFFSET   	( MAIN_SELECT1_OFFSET + (TRADELIST_SELECT1_W*TRADELIST_SELECT1_H))


// 上の画面のはい・いいえウインドウ
#define MAIN_YESNO_OFFSET	  	( MAIN_SELECT2_OFFSET + (TRADELIST_SELECT2_W*TRADELIST_SELECT2_H))


// 下の画面のポケモンの名前
#define SUB_MYPOKENAME_X		(  4 )
#define SUB_FRIENDPOKENAME_X	(  4+16 )
#define SUB_POKENAME_Y			(  1 )
#define SUB_POKENAME_W			(  9 )
#define SUB_POKENAME_H			(  2 )
#define SUB_MYPOKEBMP_OFFSET 		( 1 )
#define SUB_FRIENDPOKEBMP_OFFSET	( SUB_MYPOKEBMP_OFFSET + ( SUB_POKENAME_W * SUB_POKENAME_H))


// 下の画面のレベル表示
#define SUB_MYPOKELEVEL_X		(  4 )
#define SUB_FRIENDPOKELEVEL_X	(  4+16 )
#define SUB_POKELEVEL_Y			(  3 )
#define SUB_POKELEVEL_W			(  8 )
#define SUB_POKELEVEL_H			(  2 )
#define SUB_MYPOKELVBMP_OFFSET 		( SUB_FRIENDPOKEBMP_OFFSET + ( SUB_POKENAME_W * SUB_POKENAME_H))
#define SUB_FRIENDPOKELVBMP_OFFSET	( SUB_MYPOKELVBMP_OFFSET   + ( SUB_POKELEVEL_W * SUB_POKELEVEL_H))

// 下の画面の文字列「もちもの」
#define SUB_MOTIMONOSTR_L_X		(  2 )
#define SUB_MOTIMONOSTR_R_X		(  2+16 )
#define SUB_MOTIMONOSTR_Y		( 19 )
#define SUB_MOTIMONOSTR_W		(  7 )
#define SUB_MOTIMONOSTR_H		(  2 )
#define SUB_MYMOTIMONOSTRBMP_OFFSET 	( SUB_FRIENDPOKELVBMP_OFFSET  + ( SUB_POKELEVEL_W * SUB_POKELEVEL_H))
#define SUB_FRIENDMOTIMONOSTRBMP_OFFSET	( SUB_MYMOTIMONOSTRBMP_OFFSET + ( SUB_MOTIMONOSTR_W * SUB_MOTIMONOSTR_H))

// 下の画面のアイテム名
#define SUB_MYITEM_X			(  2 )
#define SUB_FRIENDITEM_X		(  2+16 )
#define SUB_ITEM_Y				( 21 )
#define SUB_ITEM_W				( 12 )
#define SUB_ITEM_H				(  2 )
#define SUB_MYITEMBMP_OFFSET 		( SUB_FRIENDMOTIMONOSTRBMP_OFFSET + ( SUB_MOTIMONOSTR_W * SUB_MOTIMONOSTR_H))
#define SUB_FRIENDITEMBMP_OFFSET	( SUB_MYITEMBMP_OFFSET + ( SUB_ITEM_W * SUB_ITEM_H))



// 上画面用会話ウインドウ枠・メニュー枠のキャラ転送先定義
#define MENUWIN_FRAME_OFFSET	(512 - MENU_WIN_CGX_SIZ)
#define TALKWIN_FRAME_OFFSET	(512 - (MENU_WIN_CGX_SIZ+TALK_WIN_CGX_SIZ) )

//-----------------------------------------
// 文字列表示用定義
//-----------------------------------------
enum{
	LEFT_PRINT   = 0,
	CENTER_PRINT,
};


#define INPUT_SCREEN_MAX	( 5)	
#define INPUT_WORD_W		(17)
#define INPUT_WORD_H		( 5)
#define INPUT_WORD_WH		(INPUT_WORD_W*INPUT_WORD_H)
#define INPUT_WORD_MAX		(32)	//根拠は無い

// CellActorに処理させるリソースマネージャの種類の数（＝マルチセル・マルチセルアニメは使用しない）
#define CLACT_RESOURCE_NUM		(  4 )
#define NAMEIN_OAM_NUM			( 14 )
#define NAMELINE_OAM_NUM		( 10 )

// カーソルのCLACT_WORKナンバー
#define CLACT_CURSOR_NUM		(  8 )

// 文字パネルの転送量
#define WORDPANEL_TRANS_SIZE	( 32*13*2 )

// 文字パネルの位置定義
#define WORDPANEL_POS_REGX		(  -11 )
#define WORDPANEL_POS_REGY		(  -80 )
#define HIDDENPANEL_POS_REGX	(  234 )
#define DOWNPANEL_POS_REGY		( -196 )

#define WORDPANEL_IN_SPEED		( 24 )
#define WORDPANEL_OUT_SPEED		( 10 )

// 入力済み文字の下線OBJ
#define NAMELINE_POS_X			( 10*8   )
#define NAMELINE_POS_Y			(  6*8+5 )

// パソコン・自機・ポケモンアイコンOBJ位置
#define NAMEIN_MYICON_X			( 24 )
#define NAMEIN_MYICON_Y			( 16 )

// ポケモンの性別アイコンの位置
#define NAMEIN_SEXICON_Y		( NAMELINE_POS_Y - 12)

// 名前入力情報位置定義（あなたのなまえは？）
#define NAME_INFO_POSX			(  8 )
#define NAME_INFO_POSY			(  2 )
#define NAME_INFO_POSW			( 18 )
#define NAME_INFO_POSH			(  2 )
#define NAMEINFO_WIN_SIZE		( NAME_INFO_POSW*NAME_INFO_POSH )


// 名前入力結果表示位置定義
#define NAME_RESULT_POSX		( 10   )
#define NAME_RESULT_POSY		(  5   )
#define NAME_RESULT_POSW		( 9*2  )
#define NAME_RESULT_POSH		(  2   )


#define TALK_FONT_PAL			( 13   )

// 文字パネルの遷移用
enum{
	NAMEIN_MODE_REQ  = 0, 
	NAMEIN_MODE_SET,
	NAMEIN_MODE_ANIM,
	NAMEIN_MODE_ANIM_WAIT,
	NAMEIN_MODE,
};

// 機能ボタン定義
enum{
	NAMEIN_MODE_HIRA = 0,
	NAMEIN_MODE_KANA,
	NAMEIN_MODE_ALPHA,
	NAMEIN_MODE_KIGOU,
};

// 上下画面指定定義
#define BOTH_LCD	( 2 )
#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// 要は０と
#define SUB_LCD		( GF_BGL_SUB_DISP )		// １なんですが。


// 表示されるポケモンの最大数
#define TRADELIST_POKE_MAX	( 12 )

// 「おわる」を示すカーソルの位置番号
#define CURSOR_END_POS		( 12 )


// BMPWIN指定
enum{

	// ---メイン画面--
	BMP_M_MYNAME_WIN=0,			// 自分の名前
	BMP_M_FRIENDNAME_WIN,		// 相手の名前
	BMP_M_TRADEMES_WIN,			// 会話ウインドウ
	BMP_M_TRADECENTER_WIN1,		// 中央ウインドウ
	BMP_M_SELECT_WIN,			// 選択ウインドウ
	BMP_M_YESNO_WIN,			// ＹＥＳＮＯウインドウ
	BMP_M_ENDSTR_WIN,			// 「おわり」
	BMP_M_MYPOKENAME0_WIN,		// 自分の手持ちポケモンの名前
	BMP_M_MYPOKENAME1_WIN,
	BMP_M_MYPOKENAME2_WIN,
	BMP_M_MYPOKENAME3_WIN,
	BMP_M_MYPOKENAME4_WIN,
	BMP_M_MYPOKENAME5_WIN,
	BMP_M_FRIENDPOKENAME0_WIN,	// 相手の手持ちポケモンの名前
	BMP_M_FRIENDPOKENAME1_WIN,
	BMP_M_FRIENDPOKENAME2_WIN,
	BMP_M_FRIENDPOKENAME3_WIN,
	BMP_M_FRIENDPOKENAME4_WIN,
	BMP_M_FRIENDPOKENAME5_WIN,

	BMP_M_EX_MYPOKENAME_WIN,
	BMP_M_EX_F_POKENAME_WIN,

	BMP_M_MES1_WIN,				// 1行で表示される会話ウインドウ
	BMP_M_MES2_WIN,				// 2行だが、右側にはメニューが表示されるところまでしかないウインドウ
	BMP_M_MES3_WIN,				// フルで２行会話表示するウインドウ
	BMP_M_SELECT1_WIN,			// 「ようすをみる」「こうかんする」「やめる」ウインドウ
	BMP_M_SELECT2_WIN,			// 「ようすをみる」「やめる」ウインドウ

	// ---サブ画面--
	BMP_S_MYPOKENAME_WIN,		// 自分のポケモンの名前+性別アイコン
	BMP_S_FRIENDPOKENAME_WIN,
	BMP_S_MYPOKELEVEL_WIN,		// ポケモンのレベル
	BMP_S_FRIENDPOKELEVEL_WIN,
	BMP_S_MOTIMONO0_WIN,		// 「もちもの」
	BMP_S_MOTIMONO1_WIN,
	BMP_S_MYITEM_WIN,			// アイテム名
	BMP_S_FRIENDITEM_WIN,
	BMP_TRADELIST_MAX,
};

// 機能ボタン用定義
#define FUNCBUTTON_NUM	( 7 ) 		// 機能ボタンの数
#define START_WORDPANEL ( 0 )		// 最初の文字入力パネルの番号（０＝ひらがな）

// CT_DECIDE用コマンド
#define DECIDE_COMMAND_END		1
#define DECIDE_COMMAND_NEXT		2
#define DECIDE_COMMAND_YES		3
#define DECIDE_COMMAND_NO		4




//============================================================================================
//	構造体定義
//============================================================================================

// カーソル用構造体
typedef struct {
	int x;			// 現在位置
	int y;			//
	int oldx;		// 1STEP前の位置
	int oldy;		//
	int lastxarrow;	// 最後の移動方向

	int on;			// 表示ON・OFF
}TRADELIST_CURSOR;

// てもちポケモン表示用構造体
typedef struct{
	u16  exist;		// モンスター番号
	u16  item;		// 所持アイテム
	u8   monsball;	// 捕獲ボール
	u8   tamago;	// タマゴフラグ
	u8   form;		// フォルムデータ
	u16  sex;		// 性別
	u16  reverse;   // 反転フラグ
	int  customball;	// ボールカスタマイズ
}POKE_INFO;

struct TRADELIST_WORK{

	FIELDSYS_WORK		*fsys;
	SAVEDATA			*savedata;
	TRADELIST_PARAM		*param;

	PSTATUS_DATA	 	statusParam;						// スタータス呼び出し用パラメータ
	int					status_side;						// 自分の相手のどっちのステータスを呼んだか(0:1)
	PROC				*subproc;							// スタータス呼び出し用サブプロセスデータ

	int					subseqflag;
	int					tradeseq;
	int					exchangeseq;
	int					exchange_work;
	int					exchange_finish;
	int					exchange_friend_count;
	int					result;								// 交換結果は？（tradelist.hの定義を入れる）

	int					end_flag[2];
	int					fail_reason;
	BOOL				wipe_end;

	TRADELIST_CURSOR 	Cursor;								// カーソル情報　X・Y・過去X・表示ON
	int				cursor_pos[2];
	u16				CursorPal;
	u16 			wordmap[INPUT_WORD_H][INPUT_WORD_W];	// 文字盤マップ
	u16 			nowmap;									// 現在の文字マップ
	u16				nowinput;								// 現在のカーソル位置
	int				inputmode;
	u16				subtouchword[3];						// ３つの下ボタンに配置されている文字コード
	u32				CommWork[2];
	u32				CommSeq[2][3];

	int				MyPokeNum;								// 自分の手持ちポケモンの数
	int				FriendPokeNum;							// 相手の手持ちポケモンの数

	GF_BGL_INI		*bgl;

	WORDSET			*PokeNameWordSet;								// メッセージ展開用ワークマネージャー
	WORDSET			*WindowStrWordSet;								// メッセージ展開用ワークマネージャー
	WORDSET			*SubLcdWordSet;								// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER *MsgManager;							// メッセージデータマネージャー
//	STRBUF			*TitleStr;								// 名前入力タイトル
	STRBUF			*WindowPrintStr;						// ポケモンをえらんでください等
	STRBUF			*MyName;
	STRBUF			*MotimonoStr;							// 「もちもの」文字列


	CLACT_SET_PTR 			clactSet;								// セルアクターセット
	CLACT_U_EASYRENDER_DATA	renddata;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	resObjTbl[BOTH_LCD][CLACT_RESOURCE_NUM];// リソースオブジェテーブル
	CLACT_HEADER			clActHeader_m;							// セルアクターヘッダー
	CLACT_HEADER			clActHeader_s;							// セルアクターヘッダー
	CLACT_WORK_PTR			clActWork[NAMEIN_OAM_NUM];				// セルアクターワークポインタ配列
	CLACT_WORK_PTR			PokeIconActWork[TRADELIST_POKE_MAX];
	CLACT_WORK_PTR			PokeItemActWork[TRADELIST_POKE_MAX];
	CLACT_WORK_PTR			PokeCBallActWork[TRADELIST_POKE_MAX];
	CLACT_WORK_PTR			SubLCDIconActWork[6];
	CLACT_WORK_PTR			ExchangeArrow;							// 交換しますか？の時に表示

	TCB_PTR					FuncButtonTask[FUNCBUTTON_NUM];

	GF_BGL_BMPWIN 			TradeListWin[BMP_TRADELIST_MAX];		// 交換画面用BMPウインドウ
	BMPMENU_WORK 			*YesNoMenu;
	BMPMENU_DATA			*BmpMenuList;
	BMPMENU_WORK 			*BmpMenuWork;

	int						yesnoseq;
	

	int						seq;									// 現在の文字入力状態（入力OK/アニメ中）など
	int						mode;									// 現在最前面の文字パネル

	int						front;									// 手前に来ているBG面
	VecFx32					panelpos[2];							// 移動する2つのBG面用座標ワーク(固定少数では使っていない）

	int						word;									
//	int						existtbl[13];							///< 実際にﾎﾟｹﾓﾝがいるかどうかのﾌﾗｸﾞ
//	int						item[TRADELIST_POKE_MAX];				///< 持っているアイテム
//	int						monsball[TRADELIST_POKE_MAX];			///< つかまえたモンスターボール
//	int						monssex[TRADELIST_POKE_MAX];			///< ポケモンの性別
//	int						tamagotbl[TRADELIST_POKE_MAX];			///< タマゴかどうか
	POKE_INFO				pokeInfo[TRADELIST_POKE_MAX+1];			///< カーソル位置に対応したポケモンの情報 (「おわり」」も含まれている）

	int						old_subbutton;							// 前回の下画面ボタン情報
	int						subbutton_mode;
	int						subbutton_work;

	int						funcbutton[FUNCBUTTON_NUM];				// ボタン押し状態フラグ

	void*					BgCharaBuf;
	NNSG2dCharacterData*	BgCharaDat;

	void*					PokeIconBuf[TRADELIST_POKE_MAX];		// ポケモンアイコンデータ
	NNSG2dCharacterData*	PokeIconCharaDat[TRADELIST_POKE_MAX];					

	u8						PokeGra[2][0x20*10*10];					// ポケモングラフィックデータ
	SOFT_SPRITE_ARC 		PokeGraSsa[2];							// ポケモングラフィクデータアーカイブ情報
	int						vblankreq;
	
	u8						ObjTransWork[32*4*2];					//

	int 					(*func)(TRADELIST_WORK *wk);

	POKEPARTY				*MyPokeParty;
	POKEPARTY				*FriendPokeParty;
	PERAPVOICE				*perap;

	FRIEND_LIST				*friendlist;
	FRIEND_LIST				SendList;

	int						saveseq;
	int						savewait;
	int						sub_bg2_scroll;							// BG3スクロール用の変数
	int						animcount;
	int						savePreWait;
	VecFx32					myanimpos[2];
	VecFx32					f_animpos[2];
	

	u8						recv_buf[2][POKEPARTY_SEND_ONCE_SIZE];
	u8						perap_buf[2][PERAPVOICE_DATA_LENGTH];

    // 友達登録用
    int friendNetID[WIFILIST_FRIEND_MAX]; //フレンド登録するnetID
    int addFriendNo;  // 現在登録中の人
    int erasePos;  //消す予定の人
    WORDSET			*friendWordSet;			
    MSGDATA_MANAGER *friendMsgManager;			
    BMPLIST_DATA*   menulist;
    BMPLIST_WORK* lw;		// BMPメニューワーク
	GF_BGL_BMPWIN			listWin;	// 削除リストウインドウ
    WIFI_LIST* pWifiList;
	int tradeNum;
  
	int	commSaveSeq;		// 通信セーブ用ワーク

	int posBackup;			// 通信コマンドのコマンドのバックアップデータ
	int commandBackup;		// 通信コマンドの位置データのバックアップデータ

	void *timeWaitWork;		// 時間アイコン用タスクワーク

	int	 timeOutFlag;		// タイムアウト処理を行うかフラグ
	int  timeOutWait;		// タイムアウトカウンタ

#ifdef PM_DEBUG
	int 					frame;									//
	int						framenum[9][2];							//
#endif
};



//============================================================================================
//	プロトタイプ宣言
//============================================================================================
extern void TradeListCommSendPokeData(int netID, POKEPARTY *party, int no);
extern void TradeListCommSend(int netID, int command, int pos);
extern void TradeListCommDiffSend( TRADELIST_WORK *wk, int command, int pos);

#endif
