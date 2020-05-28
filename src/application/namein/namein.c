//============================================================================================
/**
 * @file	namein.c
 * @bfief	名前入力画面処理
 * @author	Akito Mori
 * @date	05.10.05
 */
//============================================================================================
#define USE_PARAM_STR		// NAMEIN_PARAMに u16 str[20]が必要な間有効にする

//#define DEBUG_OAM_POSPRINT	// 有効にするとタッチパネルの当たり領域を確認できる


#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/window.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_namein.h"
#include "msgdata/msg_fightmsg_dp.h"
#include "system/wipe.h"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/msg_ds_icon.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"
#include "poketool/poke_tool.h"
#include "poketool/monsno.h"
#include "poketool/pokeicon.h"
#include "poketool/boxdata.h"
#include "application/namein.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "msgdata/msg_opening_name.h"
#include "namein_snd_def.h"

// 有効にするとLCDを上下逆にしてタッチパネルで入力できるようになる
#define NAMEIN_MAINUSE_TOUCHPANEL

#define POKEICON_VRAM_OFFSET (22*32+31)
#define POKEICON_PAL_OFFSET	 ( 6 )

// CLACTで定義しているセルが大きすぎてサブ画面に影響がでてしまうので離してみる
#define NAMEIN_SUB_ACTOR_DISTANCE 	(256*FX32_ONE)


// 入力した文字列を表示する際の間隔
#define INPUT_WORD_SPACE (12)		

// 文字パネルの文字の間隔
#define WORDPANEL_WORD_SPACE (16)		

// 文字種類パネルがＯＮになるまでタッチが有効にならないようにするためのウェイト
#define TOUCH_START_WAIT	 ( 5 )

#include "namein.naix"			// グラフィックアーカイブ定義
#include "../../field/poketch/poketch_arc.h"

#ifdef DEBUG_OAM_POSPRINT

static CLACT_WORK_PTR	testclact[4];
static int              testclact_no = 0;

#endif

//============================================================================================
//	定数定義
//============================================================================================
enum {
	SEQ_IN = 0,
	SEQ_WAIT,
	SEQ_MAIN,
	SEQ_OUT,
};


typedef struct {
	int x;			// 現在位置
	int y;			//
	int oldx;		// 1STEP前の位置
	int oldy;		//
	int lastxarrow;	// 最後の移動方向

	int on;			// 表示ON・OFF
	int decide;		// 決定アニメ中？
}NAMEIN_CURSOR;

#define INPUT_SCREEN_MAX	( 5)	
#define INPUT_WORD_W		(13)
#define INPUT_WORD_H		( 6)
#define INPUT_WORD_WH		(INPUT_WORD_W*INPUT_WORD_H)
#define INPUT_WORD_MAX		(32)	//根拠は無い

// CellActorに処理させるリソースマネージャの種類の数（＝マルチセル・マルチセルアニメは使用しない）
#define CLACT_RESOURCE_NUM		(  4 )
#define NAMEIN_OAM_NUM			( 14 )
#define NAMELINE_OAM_NUM		( 12 )

// カーソルのCLACT_WORKナンバー
#define CLACT_CURSOR_NUM		(  8 )

// 文字パネルの転送量
#define WORDPANEL_TRANS_SIZE	( 32*14*2 )

// 文字パネルの位置定義
#define WORDPANEL_POS_REGX		(  -11 )
#define WORDPANEL_POS_REGY		(  -80 )
#define HIDDENPANEL_POS_REGX	(  238 )
#define DOWNPANEL_POS_REGY		( -196 )

#define WORDPANEL_IN_SPEED		( 24 )
#define WORDPANEL_OUT_SPEED		( 10 )

// 入力済み文字の下線OBJ
#define NAMELINE_POS_X			( 10*8   )
#define NAMELINE_POS_Y			(  4*8+5 )

// パソコン・自機・ポケモンアイコンOBJ位置
#define NAMEIN_MYICON_X			( 24 )
#define NAMEIN_MYICON_Y			( 16-8 )

// ポケモンの性別アイコンの位置
#define NAMEIN_SEXICON_Y		( NAMELINE_POS_Y - 12)

// 名前入力情報位置定義（あなたのなまえは？）
#define NAME_INFO_POSX			(  7 )
#define NAME_INFO_POSY			(  2 )
#define NAME_INFO_POSW			( 22 )
#define NAME_INFO_POSH			(  2 )
#define NAMEINFO_WIN_SIZE		( NAME_INFO_POSW*NAME_INFO_POSH )


// 名前入力結果表示位置定義
#define NAME_RESULT_POSX		( 10   )
#define NAME_RESULT_POSY		(  3   )
#define NAME_RESULT_POSW		( 9*2  )
#define NAME_RESULT_POSH		(  2   )
#define NAME_RESULT_WIN_SIZE	( NAME_RESULT_POSW*NAME_RESULT_POSH )

// 「グループ」文字列表示用定義
#define GROUP_TEXT_POSX			(  10+9 )
#define GROUP_TEXT_POSY			(  NAME_RESULT_POSY )
#define GROUP_TEXT_POSW			(  7  )
#define GROUP_TEXT_POSH			(  2  )
#define GROUP_TEXT_WIN_SIZE		( GROUP_TEXT_POSW*GROUP_TEXT_POSH )


#define FLD_MESFRAME_PAL     ( 10 )         //  メッセージウインドウパレット
#define FLD_MESFONT_PAL      ( 12 )         //  メッセージフォントパレット


// 会話ウインドウ位置定義(フィールドからのコピー)
#define	TALK_MSG_WIN_PX		(  2 )
#define	TALK_MSG_WIN_PY		( 19 )
#define	TALK_MSG_WIN_SX		( 27 )
#define	TALK_MSG_WIN_SY		(  4 )
#define	TALK_MSG_WIN_PAL	( FLD_MESFONT_PAL )

// BG2のグラフィックデータサイズと会話ウインドウキャラデータの開始位置
#define NAMEIN_BG2GRAPHIC_NUM	  ( 32*8 )
#define NAMEIN_BG2GRAPHIC_SIZE	  ( NAMEIN_BG2GRAPHIC_NUM*0x20 )
#define NAMEIN_TALKWIN_CGX_OFFSET ( NAMEIN_BG2GRAPHIC_NUM )



// 文字パネルの遷移用
enum{
	NAMEIN_MODE_REQ  = 0, 
	NAMEIN_MODE_SET,
	NAMEIN_MODE_ANIM,
	NAMEIN_MODE_ANIM_WAIT,
	NAMEIN_MODE,
	NAMEIN_MODE_BOXMSG,
	NAMEIN_MODE_BOXMSG_END,
	NAMEIN_MODE_BOXMSG_END_WAIT,
};

// 機能ボタン定義
enum{
	NAMEIN_MODE_HIRA = 0,
	NAMEIN_MODE_KANA,
	NAMEIN_MODE_ALPHA,
	NAMEIN_MODE_KIGOU,
	NAMEIN_MODE_NUMCODE,
};

// 上下画面指定定義
#define BOTH_LCD	( 2 )
#define MAIN_LCD	( GF_BGL_MAIN_DISP )	// 要は０と
#define SUB_LCD		( GF_BGL_SUB_DISP )		// １なんですが。

// タッチパネル情報を定義するときに使う
#define PANEL_X		( 28 )
#define PANEL_Y		( 88 )
#define PANEL_H		( 19 )


// BMPWIN指定
enum{
	BMP_WORDPANEL_BG0=0,
	BMP_WORDPANEL_BG1,
	BMP_TITLE_MES,
	BMP_RESULT_NAME,
	BMP_SUB_BUTTON1,
	BMP_SUB_BUTTON2,
	BMP_SUB_BUTTON3,
	BMP_SUB_STRING,
	BMP_GROUP_STRING,
	BMP_TALK_WIN,
	BMP_NAMEIN_MAX,
};

// 機能ボタン用定義
#define FUNCBUTTON_NUM	( 7 ) 		// 機能ボタンの数

// 各データ定義

#include "namein.dat"

//============================================================================================
//	構造体定義
//============================================================================================

struct NAMEIN_WORK{

	int    inputmode;										// 入力モード（0:主人公,1:ポケモン,2:ボックス
	int    inputinfo;										// 入力情報（男女、ポケモンNOなど
	int    inputform;										// 入近く情報（ポケモン形状）
	int    inputmax;										// 入力文字最大数
	int    inputsex;										// ポケモンの時は性別を表示する
	int    endmode;											// 1の時はポケモンをBOXに転送する旨のメッセージがでる
	CONFIG *config;

	NAMEIN_CURSOR 	Cursor;									// カーソル情報　X・Y・過去X・表示ON
	u16				CursorPal;
	u16 			wordmap[INPUT_WORD_H][INPUT_WORD_W];	// 文字盤マップ
	u16 			nowmap;									// 現在の文字マップ
	u16 			inputword[INPUT_WORD_MAX];				// 入力した文字列
	u16 			paramstr[INPUT_WORD_MAX];				// 引数文字列(呼び出し時に格納されていた文字列（比較に使用））
	u16				nowinput;								// 現在のカーソル位置
	u16				subtouchword[3];						// ３つの下ボタンに配置されている文字コード
	GF_BGL_INI		*bgl;
	BOOL			wipe_end;								// ワイプ処理終了検出フラグ

	WORDSET			*WordSet;								// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER *MsgManager;							// 名前入力メッセージデータマネージャー
	MSGDATA_MANAGER *MsgDefaultName;						// 自分の名前候補メッセージデータ
	MSGDATA_MANAGER *FightMsgManager;						// ポケモン捕獲の時のメッセージデータを戦闘から参照
	STRBUF			*TitleStr;								// 名前入力タイトル
	STRBUF			*ChangeWordStr;							// 「もじを かえる」
	STRBUF			*BoxMessage;							// 「ポケモンは○○に転送された」
	STRBUF			*GroupString;							// 「グループ」文字列

	CLACT_SET_PTR 			clactSet;								// セルアクターセット
	CLACT_U_EASYRENDER_DATA	renddata;								// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	resMan[CLACT_RESOURCE_NUM];				// リソースマネージャ
	CLACT_U_RES_OBJ_PTR 	resObjTbl[BOTH_LCD][CLACT_RESOURCE_NUM];// リソースオブジェテーブル
	CLACT_HEADER			clActHeader_m;							// セルアクターヘッダー
	CLACT_HEADER			clActHeader_s;							// セルアクターヘッダー
	CLACT_WORK_PTR			clActWork[NAMEIN_OAM_NUM];				// セルアクターワークポインタ配列
	CLACT_WORK_PTR			NameLineActWork[NAMELINE_OAM_NUM];		// 入力結果表示文字列の下アンダーライン
	CLACT_WORK_PTR			NameIconActWork[2];						// 入力画面説明アイコン（自機・パソコン／性別♂・♀）
	TCB_PTR					FuncButtonTask[FUNCBUTTON_NUM];

	GF_BGL_BMPWIN 			NameInWin[BMP_NAMEIN_MAX];				// 名前入力用BMPウインドウ
	int						msg_index;


	int						seq;									// 現在の文字入力状態（入力OK/アニメ中）など
	int						mode;									// 現在最前面の文字パネル

	int						front;									// 手前に来ているBG面
	VecFx32					panelpos[2];							// 移動する2つのBG面用座標ワーク(固定少数では使っていない）

	int						word;									

	int						old_subbutton;							// 前回の下画面ボタン情報
	int						subbutton_mode;
	int						subbutton_work;

	int						funcbutton[FUNCBUTTON_NUM];				// ボタン押し状態フラグ

	void*					BgCharaBuf;
	NNSG2dCharacterData*	BgCharaDat;

	void*					PokeIconBuf;							// ポケモンアイコンデータ
	NNSG2dCharacterData*	PokeIconCharaDat;						

	void*					PokeIconPalBuf;
	NNSG2dPaletteData*		PokeIconPalDat;
	
	u8						ObjTransWork[32*4*2];					//

	void					*dsicon_task;							//

	BOOL					TP_decide;

	int						wait;
#ifdef PM_DEBUG
	int 					frame;									//
	int						framenum[9][2];							//
#endif
};


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static PROC_RESULT NameInProc_Init( PROC * proc, int * seq );
static PROC_RESULT NameInProc_Main( PROC * proc, int * seq );
static PROC_RESULT NameInProc_End( PROC * proc, int * seq );

static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void BgExit( GF_BGL_INI * ini, GF_BGL_BMPWIN *win );
static void BgGraphicSet( NAMEIN_WORK * wk );
static void PanelFunc(GF_BGL_INI *bgl, GF_BGL_BMPWIN *win, int *seq, int mode, int *front, VecFx32 panelpos[], CLACT_WORK_PTR *clActWork, void *dakuten_Character);
static void InitWork(NAMEIN_WORK *wk, PROC * proc);
static void FrontBackBG_RegSet(GF_BGL_INI *bgl, int front, VecFx32 panelpos[]);
static void SetPanelFirstPos(VecFx32 panelpos[], int front);
static void InitCellActor(NAMEIN_WORK *wk);
static void SetCellActor(NAMEIN_WORK *wk);
static void char_pltt_manager_init(void);
static void BmpMessageSet(NAMEIN_WORK *wk, PROC* proc);
static void DebugOBJPOSGet(NAMEIN_WORK *wk);
static void ControlCursor(NAMEIN_WORK *wk);
static void CursorColTrans(u16 *CursorCol);
static void TouchFunc(NAMEIN_WORK *wk);
static void NameinWordPanelPrint(GF_BGL_BMPWIN *win, const u16 *str, int x,int y, int space, int sw, GF_PRINTCOLOR color, u8 *datkuten_Character);
static void ChangeSubPanelButtonWord(GF_BGL_BMPWIN *win, const u16 *tbl, u8 *TransWork, STRBUF *ChangeWordStr);
static void MakeWordMap(u16 map[][INPUT_WORD_W], const int no);
static void SubPanelButton_CharaChange(GF_BGL_BMPWIN *win, STRCODE *str,int pos,  u16 *words, u8 *TransWork, STRBUF *ChangeWordStr);
static int  DecideMainButton(NAMEIN_WORK *wk,u16 code, int pad);
static int  ConvertWord(int start, int num, int flag, int target, u16*str, int pos);
static int  RotateConvertWord(int start, int num, u16 *str, int pos);
static void InputResultUnderLineMove(CLACT_WORK_PTR *lineact,int pos, int max);
static void SetNameInWorkParameter(NAMEIN_WORK *wk, NAMEIN_PARAM *param);
static void WordPanelSetUp(GF_BGL_BMPWIN *win,u16 bgchara, int frame, GF_PRINTCOLOR color, u8 *dakuten_Character);
static void CursorAppearUpDate(NAMEIN_WORK *wk, int arrow);
static void FuncButtonAnimation(int funcbutton[], CLACT_WORK_PTR *ButtonAct, int frame);
static void FuncButtonTaskFunc( TCB_PTR tcb, void *work );
static void QuakeFrameTaskFunc( TCB_PTR tcb, void *work );
static void TransPokeIconCharaPal( NNSG2dCharacterData *chara, NNSG2dPaletteData* pal, int pokeno, int form );
static void Namein_LCDOnOff( int flag);
static void SetBoxMessage( NAMEIN_WORK *wk, PROC * proc );
static void NameinIconAdd(NAMEIN_WORK *wk, CLACT_ADD *add );
static void InputCancelFunc( NAMEIN_WORK *wk, NAMEIN_PARAM *param );
static void PrintTalkInfoStr( GF_BGL_BMPWIN *bmp, int inputmode, STRBUF *Title );
static void CursorAnimationControl( NAMEIN_WORK *wk );
static int  NameInputMainMode( NAMEIN_WORK *wk, int seq );
static int SpaceCheck( STRCODE *str );


static void *GF_STR_PrintCGXOnly(GF_BGL_BMPWIN * win, STRBUF *msg,u8 fnt_index, GF_PRINTCOLOR col);

#ifdef DEBUG_OAM_POSPRINT

static testclact_set( void );

#endif
//============================================================================================
//	グローバル変数
//============================================================================================
// プロセス定義データ
const PROC_DATA NameInProcData = {
	NameInProc_Init,
	NameInProc_Main,
	NameInProc_End,
	NO_OVERLAY_ID,
};


static NAMEIN_WORK *debug_namein;
//============================================================================================
//	プロセス関数
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：初期化
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT NameInProc_Init( PROC * proc, int * seq )
{
	NAMEIN_WORK * wk;

	switch(*seq){
	case 0:
		sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
		sys_HBlankIntrStop();	//HBlank割り込み停止

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane( 0 );
		GXS_SetVisiblePlane( 0 );

		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_NAMEIN, 0x20000+0x8000 );

		wk = PROC_AllocWork( proc, sizeof(NAMEIN_WORK), HEAPID_NAMEIN );
		memset( wk, 0, sizeof(NAMEIN_WORK) );
		wk->bgl = GF_BGL_BglIniAlloc( HEAPID_NAMEIN );
		
		// 文字列マネージャー生成
		wk->WordSet          = WORDSET_Create( HEAPID_NAMEIN );
		wk->MsgManager       = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_namein_dat, HEAPID_NAMEIN );
		wk->MsgDefaultName   = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_opening_name_dat, HEAPID_NAMEIN );
		wk->FightMsgManager  = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_fightmsg_dp_dat, HEAPID_NAMEIN );

		sys_KeyRepeatSpeedSet( 4, 8 );

		VramBankSet();
		
		// BGLレジスタ設定
		BgInit( wk->bgl );					

		// 輝度変更セット

//		ChangeBrightnessRequest(
//			8, 0, -16, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );

		
		// 引数を保存
		SetNameInWorkParameter(wk, (NAMEIN_PARAM*)PROC_GetParentWork(proc));

		//BGグラフィックセット
		BgGraphicSet( wk );

//		InitTPSystem();						// タッチパネルシステム初期化
//		InitTPNoBuff(4);
  
		// ボタン用フォントを読み込み
		FontProc_LoadFont( FONT_BUTTON, HEAPID_NAMEIN );
  	
 
		// VBlank関数セット
		sys_VBlankFuncChange( VBlankFunc, NULL );	
  
		// ワーク初期化
		InitWork(wk,proc);

		// システムフォント常駐
		FontProc_LoadBitData(FONT_SYSTEM,HEAPID_NAMEIN);

		// OBJキャラ、パレットマネージャー初期化
		char_pltt_manager_init();

		// CellActorシステム初期化
		InitCellActor(wk);
		
		// CellActro表示登録
		SetCellActor(wk);

		// BMPWIN登録・描画
		BmpMessageSet(wk,proc);


		// 下ボタンOBJフォント転送
		SubPanelButton_CharaChange(&wk->NameInWin[BMP_SUB_BUTTON1],
									wk->inputword,
									wk->nowinput,
									wk->subtouchword,
									wk->ObjTransWork,
									wk->ChangeWordStr);

		// サウンドデータロード(名前入力)(BGM引継ぎ)
		Snd_DataSetByScene( SND_SCENE_SUB_NAMEIN, 0, 0 );

		WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_NAMEIN );
		Namein_LCDOnOff( VISIBLE_ON );

#ifdef NAMEIN_MAINUSE_TOUCHPANEL
		{
			//画面反転	add by tetsu
			sys.disp3DSW = DISP_3D_TO_SUB;
			GF_Disp_DispSelect();
		}
#endif
		(*seq)++;
		break;
	case 1:
		wk = PROC_GetWork( proc );
		if(wk->inputmode==NAMEIN_POKEMON){
			// ポケモンアイコンデータをVRAMに転送
			TransPokeIconCharaPal(wk->PokeIconCharaDat, wk->PokeIconPalDat, wk->inputinfo, wk->inputform );
		}
		debug_namein = wk;

		wk->dsicon_task = MSG_DsIconFlashAdd( NULL, MSG_DSI_SUBDISP, TALK_MSG_WIN_PAL, HEAPID_NAMEIN );
		
		(*seq) = 0;
		return PROC_RES_FINISH;
		break;
	}
	return PROC_RES_CONTINUE;
}


//------------------------------------------------------------------
/**
 * ポケモンアイコンを転送する（ポケモンの名前の時だけ）
 *
 * @param   chara	キャラクターファイルアドレス
 * @param   pal		パレットファイルアドレス
 * @param   pokeno	ポケモンの開発NO
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TransPokeIconCharaPal( NNSG2dCharacterData *chara, NNSG2dPaletteData* pal, int pokeno, int form )
{
	u8 *pokepal;

	// キャラクター転送
	GX_LoadOBJ(chara->pRawData, POKEICON_VRAM_OFFSET*0x20, 0x20*4*4);

	// パレット転送
	pokepal = (u8*)pal->pRawData;
	GX_LoadOBJPltt((void*)(pokepal + PokeIconPalNumGet(pokeno, form, 0)*0x20), 
					POKEICON_PAL_OFFSET*0x20, 0x20);


}


//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：メイン
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------

static PROC_RESULT NameInProc_Main( PROC * proc, int * seq )
{
	NAMEIN_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_IN:
//		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) ){
		if( WIPE_SYS_EndCheck() ){
			*seq     = SEQ_WAIT;
			wk->wait = 0;
		}
		break;

	case SEQ_WAIT:
		wk->wait++;
		// カーソルアニメーション制御
		CursorAnimationControl( wk );
		// 機能ボタンのアニメ処理
		FuncButtonAnimation(wk->funcbutton, wk->clActWork, wk->mode);
		if(wk->wait > TOUCH_START_WAIT){
			*seq     = SEQ_MAIN;
			wk->wait = 0;
		}
		break;

	case SEQ_MAIN:
		// カーソル移動

		switch(wk->seq){
		case NAMEIN_MODE:

			// 通常入力制御
			if(!wk->Cursor.decide){
				// 入力アニメ中は動かせない
				*seq = NameInputMainMode(wk, *seq);
			}

			// カーソルアニメーション制御
			CursorAnimationControl( wk );

			break;
		case NAMEIN_MODE_BOXMSG:

			// ポケモンはボックスに格納されたよメッセージ
			SetBoxMessage( wk, proc );
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_TALK_WIN], 0x0f0f );
			BmpTalkWinWrite( &wk->NameInWin[BMP_TALK_WIN], WINDOW_TRANS_ON, NAMEIN_TALKWIN_CGX_OFFSET, FLD_MESFRAME_PAL );
			wk->msg_index = GF_STR_PrintSimple( &wk->NameInWin[BMP_TALK_WIN], FONT_TALK, wk->BoxMessage, 0, 0, 1, NULL );
			GF_BGL_BmpWinOn( &wk->NameInWin[BMP_TALK_WIN] );

			wk->seq = NAMEIN_MODE_BOXMSG_END;
			break;
		case NAMEIN_MODE_BOXMSG_END:
			// ボックス行きメッセージ表示待ち
			if(GF_MSG_PrintEndCheck( wk->msg_index )==0){
				Snd_SePlay( NAMEIN_SE_END );
				wk->funcbutton[6]++;
				wk->wait = 0 ;
				wk->seq = NAMEIN_MODE_BOXMSG_END_WAIT;
			}
			break;
		case NAMEIN_MODE_BOXMSG_END_WAIT:
			// ボックスメッセージ表示待ち
			wk->wait++;
			if(wk->wait>30){
				WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_NAMEIN );
				*seq = SEQ_OUT;
			}
			break;
		}

		// リクエスト毎に文字パネルを入れ替える
		PanelFunc(wk->bgl, &wk->NameInWin[BMP_WORDPANEL_BG0], &wk->seq, wk->mode, &wk->front, wk->panelpos, wk->clActWork, wk->BgCharaDat->pRawData);

		// 機能ボタンのアニメ処理
		FuncButtonAnimation(wk->funcbutton, wk->clActWork, wk->mode);

		CursorColTrans(&wk->CursorPal);

		break;

	case SEQ_OUT:
//		if( IsFinishedBrightnessChg(MASK_DOUBLE_DISPLAY) ){
		if( WIPE_SYS_EndCheck() ){
			return PROC_RES_FINISH;
		}
		break;
	}
	CLACT_Draw( wk->clactSet );									// セルアクター常駐関数

	return PROC_RES_CONTINUE;
}


//------------------------------------------------------------------
/**
 * @brief   名前入力通常時メイン制御
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int NameInputMainMode( NAMEIN_WORK *wk, int seq )
{
			ControlCursor(wk);		//		DebugOBJPOSGet(wk);
			//TouchFunc(wk);
			if( sys.trg & PAD_BUTTON_SELECT){
				// フレンドコード入力の時はパネル切り替えはできない
				if(wk->inputmode!=NAMEIN_FRIENDCODE){
					// パネル切り替え
					wk->seq = NAMEIN_MODE_REQ;
					wk->mode++;
					if(wk->mode>NAMEIN_MODE_KIGOU){
						wk->mode=NAMEIN_MODE_HIRA;
					}
					wk->funcbutton[wk->mode]++;
					MakeWordMap(wk->wordmap, wk->mode);		// 文字入力マップ差し替え
					Snd_SePlay( NAMEIN_SE_CHANGEPANEL );
				}
				wk->funcbutton[wk->mode]++;
				MakeWordMap(wk->wordmap, wk->mode);		// 文字入力マップ差し替え
				Snd_SePlay( NAMEIN_SE_CHANGEPANEL );
#ifdef NAMEIN_MAINUSE_TOUCHPANEL
			}else if( sys.trg & PAD_BUTTON_A){
				// 文字入力
				seq = DecideMainButton(wk,wk->wordmap[wk->Cursor.y][wk->Cursor.x], 1);

				// 入力後カーソルを表示する
				wk->Cursor.on = 1;
			}else if( wk->TP_decide == TRUE ){
				seq = DecideMainButton(wk,wk->wordmap[wk->Cursor.y][wk->Cursor.x], 0);

				// 入力後カーソルをＯＦＦする
				wk->Cursor.on = 0;
#else
			}else if( sys.trg & PAD_BUTTON_A){
#endif
			}else if( sys.trg & PAD_BUTTON_B ){
				// 文字消去
				seq = DecideMainButton(wk,NAMEIN_MODORU,1);

			}
			else if( sys.trg & PAD_BUTTON_R){
				seq = DecideMainButton( wk, NAMEIN_KOMOJI, 1 );
			}

	return seq;
}

#define DEFAULT_NAME_MAX		18

// ダイヤ・パールで変わる
#if (PM_VERSION==VERSION_DIAMOND)

#define MALE_NAME_START			( msg_opening_name_01 )
#define FEMALE_NAME_START		( msg_opening_name_19 )
#define RIVAL_NAME_NO			( msg_opening_rival_dia_01 )

#else

#define MALE_NAME_START			( msg_opening_name_45 )
#define FEMALE_NAME_START		( msg_opening_name_63 )
#define RIVAL_NAME_NO			( msg_opening_rival_pearl_01 )

#endif

//------------------------------------------------------------------
/**
 * @brief   入力無しで終了する時にキャンセル扱いにするか
 *			デフォルトネームを入れるか
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InputCancelFunc( NAMEIN_WORK *wk, NAMEIN_PARAM *param )
{
	// 自分の名前入力の時はキャンセルは無い
	if(wk->inputmode==NAMEIN_MYNAME){
		STRBUF *DefaultName;
		if(wk->inputinfo==PM_MALE){
			DefaultName = MSGMAN_AllocString( wk->MsgDefaultName, MALE_NAME_START+gf_rand()%DEFAULT_NAME_MAX );
		}else if(wk->inputinfo==PM_FEMALE){
			DefaultName = MSGMAN_AllocString( wk->MsgDefaultName, FEMALE_NAME_START+gf_rand()%DEFAULT_NAME_MAX );
		}
		STRBUF_Copy(param->strbuf, DefaultName);
		STRBUF_Delete(DefaultName);
#ifdef USE_PARAM_STR
		STRBUF_GetStringCode( param->strbuf, param->str, 10 );
#endif

	// ライバル名の時はキャンセルではなくデフォルトネームを入れる
	}else if(wk->inputmode==NAMEIN_RIVALNAME){
		STRBUF *rivalName;
		rivalName = MSGMAN_AllocString( wk->MsgDefaultName, RIVAL_NAME_NO );
		STRBUF_Copy(param->strbuf, rivalName);
		STRBUF_Delete(rivalName);
#ifdef USE_PARAM_STR
		STRBUF_GetStringCode( param->strbuf, param->str, 10 );
#endif

	}else{
		OS_Printf("入力はキャンセル\n");
		
		// キャンセル
		param->cancel = 1;
	}

}

//------------------------------------------------------------------
/**
 * @brief   入力文字列が全てスペースならキャンセル扱いにするチェック
 *
 * @param   str		
 *
 * @retval  int		全てスペースだったら1,違ったら0
 */
//------------------------------------------------------------------
static int SpaceCheck( STRCODE *str )
{
	int flag=1;
	int i;
	for(i=0;;i++){
		if(str[i]==EOM_){
			break;
		}
		if(str[i]!=spc_){
			flag = 0;
		}
	}
	
	return flag;
}

//--------------------------------------------------------------------------------------------
/**
 * プロセス関数：終了
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	処理状況
 */
//--------------------------------------------------------------------------------------------
static PROC_RESULT NameInProc_End( PROC * proc, int * seq )
{
	NAMEIN_WORK  *wk    = PROC_GetWork( proc );
	NAMEIN_PARAM *param = (NAMEIN_PARAM*)PROC_GetParentWork(proc);
	int i;

	// 入力文字列の最後にEOMを入れておく
	wk->inputword[wk->nowinput] = EOM_;

	// ポケモン名前入力の時のキャンセル判定のための準備
	if(wk->inputmode==NAMEIN_POKEMON){
		// wk->paramstrにデフォルトポケモン名をいれるか？
		STRCODE comparestr[MONS_NAME_SIZE+EOM_SIZE];
		POKEMON_PARAM *pp;

		OS_Printf("paramstr %02x, %02x, %02x, %02x, %02x, %02x,\n",
			wk->paramstr[0],wk->paramstr[1],wk->paramstr[2],wk->paramstr[3],wk->paramstr[4],wk->paramstr[5]
		);

		pp = PokemonParam_AllocWork(HEAPID_NAMEIN);
		PokeParaSet(pp,wk->inputinfo,5,10,10,10,10,10);
//		PokeParaGet(pp,ID_PARA_nickname, comparestr);
		sys_FreeMemoryEz(pp);

	}

	// キャンセルじゃないか？
	if(wk->nowinput==0 || (PM_strcmp( wk->inputword, wk->paramstr)==0) || SpaceCheck(wk->inputword)){

		InputCancelFunc( wk, param );

	}else{
		// 入力文字列を引数ワークに反映
		PM_strcpy(wk->paramstr,wk->inputword);
#ifdef USE_PARAM_STR
		PM_strcpy(param->str,wk->inputword);
#endif

		STRBUF_SetStringCode(param->strbuf,wk->inputword);
	}
	
	STRBUF_Delete(wk->GroupString);

	// 機能ボタン位置制御タスク解放
	for(i=0;i<FUNCBUTTON_NUM;i++){
		PMDS_taskDel(wk->FuncButtonTask[i]);
	}
	// セルアクターリソース解放

	// キャラ転送マネージャー破棄
	CLACT_U_CharManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES]);
	CLACT_U_CharManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES]);

	// パレット転送マネージャー破棄
	CLACT_U_PlttManagerDelete(wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES]);
	CLACT_U_PlttManagerDelete(wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES]);
		
	// キャラ・パレット・セル・セルアニメのリソースマネージャー破棄
	for(i=0;i<CLACT_RESOURCE_NUM;i++){
		CLACT_U_ResManagerDelete(wk->resMan[i]);
	}
	// セルアクターセット破棄
	CLACT_DestSet(wk->clactSet);

	//OAMレンダラー破棄
	REND_OAM_Delete();

	// BMPWIN用キャラデータ解放
	sys_FreeMemory( HEAPID_NAMEIN, wk->BgCharaBuf );

	// ポケモンアイコン解放
	if(wk->inputmode==NAMEIN_POKEMON){
		sys_FreeMemory( HEAPID_NAMEIN,wk->PokeIconBuf );
		sys_FreeMemory( HEAPID_NAMEIN,wk->PokeIconPalBuf );	
	}

	//会話ウインドウ用バッファ解放
	GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME3_S);

	DeleteCharManager();
	DeletePlttManager();

	// BMPウィンドウ開放
	BgExit(wk->bgl,wk->NameInWin);
	// BGL削除

	// 常駐システムフォント解放
	FontProc_UnloadBitData(FONT_SYSTEM);


	GX_SetVisibleWnd( GX_WNDMASK_NONE );	//ハードウェアウインドウ解除

	// ボタン用フォント解放
	FontProc_UnloadFont( FONT_BUTTON );

//	StopTP();							// タッチパネル終了

	//ポケモン転送文字列バッファが確保してあったら解放
	if(wk->BoxMessage){
		STRBUF_Delete(wk->BoxMessage);
	}

	// 「～のなまえは？」解放
	STRBUF_Delete(wk->TitleStr);
	//「かたちをかえる」解放
	STRBUF_Delete(wk->ChangeWordStr);

	// メッセージマネージャー・ワードセットマネージャー解放
	MSGMAN_Delete( wk->FightMsgManager );
	MSGMAN_Delete( wk->MsgDefaultName );
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );

	PROC_FreeWork( proc );				// ワーク開放

	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

	sys_DeleteHeap( HEAPID_NAMEIN );

#ifdef NAMEIN_MAINUSE_TOUCHPANEL
	{
		//画面反転	add by tetsu
		sys.disp3DSW = DISP_3D_TO_MAIN;
		GF_Disp_DispSelect();
	}
#endif
	return PROC_RES_FINISH;
}

//==============================================================================
/**
 * 名前入力に渡すパラメータを確保する（名前入力の結果も入るので、呼び出す側のHEAPIDが必要）
 *
 * @param   HeapId		呼び出す側のHEAPID
 * @param   mode		名前入力モード(NAMEIN_MYNAME,NAMEIN_BOX,NAMEIN_POKEMON)
 * @param   info		NAMEIN_MYNAMEの時は0=男1=女, NAMEIN_POKEMONの時は開発NO
 * @param   wordmax		入力文字最大数の指定
 *
 * @retval  NAMEIN_PARAM *		確保された名前入力パラメータのポインタ
 */
//==============================================================================
NAMEIN_PARAM *NameIn_ParamAllocMake(int HeapId, int mode, int info, int wordmax, CONFIG *config)
{
	NAMEIN_PARAM *param;
	
	
	param = (NAMEIN_PARAM*)sys_AllocMemory(HeapId, sizeof(NAMEIN_PARAM));

	param->mode    = mode;		// 入力モード（自分の名前、ポケモン、ボックス）
	param->info    = info;		// （男・女、ポケモンの開発NO)
	param->wordmax = wordmax;	// 入力文字最大数
	param->cancel  = 0;			// キャンセルフラグ
#ifdef USE_PARAM_STR
	param->str[0]  = EOM_;
#endif

	// 文字列最大長＋EOMで文字列バッファを作成
	param->strbuf = STRBUF_Create( wordmax+1, HeapId );


	// ポケモン捕獲の時にボックス転送が発生した時には使用されるメンバ
	param->get_msg_id  = 0;		// ポケモン捕獲メッセージID
	param->boxdata     = NULL;	// ポケモンボックスデータへのポインタ
	param->sex		   = 0;
	param->config      = config;
	param->form		   = 0;

	return param;
}

//==============================================================================
/**
 * 名前入力パラメータの解放（名前入力後にユーザーが名前取得したら解放してもらう）
 *
 * @param   param		
 *
 * @retval  none		
 */
//==============================================================================
void NameIn_ParamDelete(NAMEIN_PARAM *param)
{
	GF_ASSERT((param->strbuf)!=NULL);
	GF_ASSERT((param)!=NULL);
	
	STRBUF_Delete(param->strbuf);
	sys_FreeMemoryEz(param);
}

//--------------------------------------------------------------------------------------------
/**
 * VBlank関数
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VBlankFunc( void * work )
{
	// セルアクター
	// Vram転送マネージャー実行
	DoVramTransferManager();

	// レンダラ共有OAMマネージャVram転送
	REND_OAMTrans();	
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}

//==============================================================================
/**
 * 外部から名前入力初期化パラメーターをもらう
 *
 * @param   wk			名前入力ワークのポインタ
 * @param   mode		入力モード（namein.hのenum参照
 * @param   info		入力情報（男女・ポケモンＮＯなど
 * @param   wordmax		入力文字最大数
 *
 * @retval  none		
 */
//==============================================================================
static void SetNameInWorkParameter(NAMEIN_WORK *wk, NAMEIN_PARAM *param)
{
	wk->inputmode = param->mode;
	wk->inputinfo = param->info;
	wk->inputform = param->form;
	wk->inputmax  = param->wordmax;
	wk->inputsex  = param->sex;
	wk->config    = param->config;
}

//--------------------------------------------------------------------------------------------
/**
 * VRAM設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void VramBankSet(void)
{
	GF_BGL_DISPVRAM tbl = {
		GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット

		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット

		GX_VRAM_OBJ_128_B,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット

		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット

		GX_VRAM_TEX_NONE,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_NONE			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &tbl );
}

//--------------------------------------------------------------------------------------------
/**
 * BG設定
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgInit( GF_BGL_INI * ini )
{
	// BG SYSTEM
	{	
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	// 上画面文字版0
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );


	}

	// 上画面文字版1
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	// 背景
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

	// 会話ウインドウBG
//	{	
//		GF_BGL_BGCNT_HEADER TextBgCntDat = {
//			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
//			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
//			0, 0, 0, FALSE
//		};
//		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
//		GF_BGL_ScrClear( ini, GF_BGL_FRAME3_M );
//	}




	// BUTTON (CHAR)
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

	// BG (CHAR)
//	{	
//		GF_BGL_BGCNT_HEADER TextBgCntDat = {
//			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
//			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
//			1, 0, 0, FALSE
//		};
//		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
//	}

	Namein_LCDOnOff( VISIBLE_OFF );

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_NAMEIN );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_NAMEIN );

	// 上画面のハードウェアウインドウ0をＯＮに
	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_OBJ,1);
	G2_SetWndOutsidePlane(   GX_WND_PLANEMASK_BG0 
	                       | GX_WND_PLANEMASK_BG1 
	                       | GX_WND_PLANEMASK_BG2 
	                       | GX_WND_PLANEMASK_BG3 
	                       | GX_WND_PLANEMASK_OBJ,1);
	G2_SetWnd0Position(0, 0, 255, 64);


}


//------------------------------------------------------------------
/**
 * $brief   名前入力画面の表示ＯＮ・ＯＦＦ
 *
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Namein_LCDOnOff( int flag)
{
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG0, flag);
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG1, flag);
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG2, flag);
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_BG3, 0);
	GF_Disp_GX_VisibleControl( GX_BLEND_PLANEMASK_OBJ, flag);


    GF_Disp_GXS_VisibleControl( GX_BLEND_PLANEMASK_BG0,flag);
    GF_Disp_GXS_VisibleControl( GX_BLEND_PLANEMASK_BG1,0);
    GF_Disp_GXS_VisibleControl( GX_BLEND_PLANEMASK_OBJ,0);
	
}

//------------------------------------------------------------------
/**
 * 名前入力ワーク初期化
 *
 * @param   wk		NAMEIN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork(NAMEIN_WORK *wk, PROC * proc)
{
	NAMEIN_PARAM *param = (NAMEIN_PARAM*)PROC_GetParentWork(proc);
	wk->seq = NAMEIN_MODE;

	SetPanelFirstPos(wk->panelpos, 0);

	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME0_M+wk->front,       GF_BGL_SCROLL_X_SET, wk->panelpos[wk->front].x );
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME0_M+wk->front,       GF_BGL_SCROLL_Y_SET, wk->panelpos[wk->front].y );
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME0_M+((wk->front)^1), GF_BGL_SCROLL_X_SET, wk->panelpos[((wk->front)^1)].x );
	GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME0_M+((wk->front)^1), GF_BGL_SCROLL_Y_SET, wk->panelpos[((wk->front)^1)].y );

#ifdef PM_DEBUG
	{
		int i;
		for(i=0;i<9;i++){
			wk->framenum[i][0] = main_button_info[i][0];
			wk->framenum[i][1] = main_button_info[i][1];
		}
	}
#endif

	wk->paramstr[0] = EOM_;
	// パラメーターで貰っているSTRBUFの展開
	if(param->strbuf){
		STRBUF_GetStringCode(param->strbuf, wk->paramstr, INPUT_WORD_MAX);
	}

	MI_CpuFill16( wk->inputword, spc_,  INPUT_WORD_MAX*2 );


	// 「～のなまえは？」文字列展開
	if(wk->inputmode==NAMEIN_POKEMON){
		POKEMON_PARAM *pp;

		pp = PokemonParam_AllocWork(HEAPID_NAMEIN);
		PokeParaSet(pp,wk->inputinfo,5,10,10,10,10,10);
		WORDSET_RegisterPokeMonsName( wk->WordSet, 0, PPPPointerGet(pp) );
		sys_FreeMemoryEz(pp);
	}

	// 終了時にメッセージ表示を行うか（ポケモン捕獲時）
	if(param->get_msg_id!=0){
		wk->endmode       = 1;
		OS_Printf("BOXDATA Addr = %08x\n",param->boxdata);
	}

	// 「～のなまえは？」文字列取得(ポケモンの名前もここで展開される)
	wk->TitleStr      = MSGDAT_UTIL_AllocExpandString( wk->WordSet, wk->MsgManager, 
														NameinTitleStrTable[wk->inputmode], HEAPID_NAMEIN );
	
	// かたちをかえる
	wk->ChangeWordStr = MSGDAT_UTIL_AllocExpandString( wk->WordSet, wk->MsgManager, 
														NAMEIN_MSG_CHANGEWORD, HEAPID_NAMEIN );


	// 「グループ」
	wk->GroupString   = MSGMAN_AllocString( wk->MsgManager, NAMEIN_MSG_TITLEINFO7 );

	// NAMEIN_PARAM.strにデフォルト文字列入っていればカーソルの位置は0ではなくなる
	wk->nowinput       = PM_strlen( wk->paramstr ); 
	wk->Cursor.x       = 0;	// 初期位置を「あ」の位置に
	wk->Cursor.y       = 1;	
	wk->Cursor.oldx    = -1;
	wk->Cursor.oldy    = -1;
	wk->Cursor.on      = 0;	
	wk->Cursor.decide  = 0;	
	wk->old_subbutton  = RECT_HIT_NONE;							// 前回の下画面ボタン情報
	wk->subbutton_mode = 0;
	wk->subbutton_work = 0;
	wk->inputword[wk->inputmax] = EOM_;


	// 機能ボタン押し状態ワーク初期化
	{
		int i;
		for(i=0;i<FUNCBUTTON_NUM;i++){
			wk->funcbutton[i]	= 0;
		}

		// 文字入力ボタンの初期設定
		switch(wk->inputmode){
		case NAMEIN_POKEMON:
			wk->funcbutton[NAMEIN_MODE_KANA]    = 1;
			break;
		case NAMEIN_FRIENDCODE:
			wk->funcbutton[NAMEIN_MODE_KIGOU] = 1;
			break;
		default:
			wk->funcbutton[NAMEIN_MODE_HIRA]    = 1;
			break;
		}
	}
	
}

//------------------------------------------------------------------
/**
 * $brief   ポケモン捕獲でボックスに行くメッセージを出すための準備
 *
 * @param   wk		
 * @param   proc		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetBoxMessage( NAMEIN_WORK *wk, PROC * proc )
{
	STRBUF *name=NULL;

	NAMEIN_PARAM *param = (NAMEIN_PARAM*)PROC_GetParentWork(proc);


	// 戦闘からメッセージIDを貰っているならば
	if(param->get_msg_id!=0){
		int setbox,newbox;

		name = STRBUF_Create(200,HEAPID_NAMEIN);

		// ○○はボックス「？？？」に転送されました
		wk->BoxMessage = NULL;

		setbox = BOXDAT_GetCureentTrayNumber(param->boxdata);
		newbox = BOXDAT_GetEmptyTrayNumber(param->boxdata);
		
		// 転送先ボックス名設定
		WORDSET_RegisterBoxTrayName( wk->WordSet, 1, param->boxdata, setbox );


		// 現在転送先と、実際の転送先が違う場合は新しい転送先名も取得する
		if(setbox!=newbox){
			WORDSET_RegisterBoxTrayName( wk->WordSet, 2, param->boxdata, newbox );
			param->get_msg_id+=2;
		}else{
			WORDSET_RegisterBoxTrayName( wk->WordSet, 2, param->boxdata, setbox );
		}

		// 入力文字列を名前バッファに反映
		if(wk->nowinput==0 || SpaceCheck(wk->inputword)){
			// 名前を入力していないので、デフォルトネームを入れる
			POKEMON_PARAM	*poke = PokemonParam_AllocWork(HEAPID_NAMEIN);
			PokeParaSet( poke, wk->inputinfo,1,0,0,0,0,0);
			WORDSET_RegisterPokeMonsName( wk->WordSet,  0, PPPPointerGet(poke) );
			sys_FreeMemoryEz(poke);
		}else{
			// 名前を入力していた時
			wk->inputword[wk->nowinput] = EOM_;
			STRBUF_SetStringCode( name, wk->inputword );
			WORDSET_RegisterWord( wk->WordSet, 0, name, 0, 0, 0 );
		}
		wk->BoxMessage    = MSGDAT_UTIL_AllocExpandString( wk->WordSet, wk->FightMsgManager, param->get_msg_id, HEAPID_NAMEIN );
		wk->endmode       = 1;

		STRBUF_Delete(name);

	}
	
}

//--------------------------------------------------------------------------------------------
/**
 * BG解放
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgExit( GF_BGL_INI * ini, GF_BGL_BMPWIN *win )
{
	int i;
//	GF_Disp_GX_VisibleControl(
//		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 |
//		GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ, VISIBLE_OFF );
//	GF_Disp_GXS_VisibleControl(
//		GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_OBJ, VISIBLE_OFF );

	for(i=0;i<BMP_NAMEIN_MAX;i++){
		GF_BGL_BmpWinDel( &win[i] );
	}

//	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
//	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

	sys_FreeMemory( HEAPID_NAMEIN, ini );
}



//--------------------------------------------------------------------------------------------
/**
 * グラフィックデータセット
 *
 * @param	wk		ポケモンリスト画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BgGraphicSet( NAMEIN_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// 上下画面ＢＧパレット転送
	ArcUtil_PalSet(    ARC_NAMEIN_GRA,  NARC_namein_name_bg_NCLR, PALTYPE_MAIN_BG, 0, 16*3*2,  HEAPID_NAMEIN);
//	ArcUtil_PalSet(    ARC_NAMEIN_GRA,  NARC_namein_name_bg_NCLR, PALTYPE_SUB_BG,  0, 16*3*2,  HEAPID_NAMEIN);
	ArcUtil_PalSet(    ARC_POKETCH_IMG, NARC_poketch_before_nclr, PALTYPE_SUB_BG, 0, 16*2,  HEAPID_NAMEIN);
	
	// バックドロップパレットを０クリア
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, 0 );

	// 上画面BG2キャラ転送
	ArcUtil_BgCharSet( ARC_NAMEIN_GRA, NARC_namein_name_bg_m_lz_NCGR, bgl, GF_BGL_FRAME2_M, 0, NAMEIN_BG2GRAPHIC_SIZE, 1, HEAPID_NAMEIN);

	// 上画面BG2スクリーン転送
	ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_bg_m_lz_NSCR, bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_NAMEIN);


	// 上画面BG1キャラ転送
	ArcUtil_BgCharSet( ARC_NAMEIN_GRA, NARC_namein_name_bg_m_lz_NCGR, bgl, GF_BGL_FRAME1_M, 0, 32*8*0x20, 1, HEAPID_NAMEIN);
	// 上画面BG1スクリーン転送
	ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_screen1_lz_NSCR, bgl, GF_BGL_FRAME1_M, 0, WORDPANEL_TRANS_SIZE, 1, HEAPID_NAMEIN);
	// 上画面BG0スクリーン転送
	ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_screen2_lz_NSCR, bgl, GF_BGL_FRAME0_M, 0, WORDPANEL_TRANS_SIZE, 1, HEAPID_NAMEIN);
	
	// 会話ウインドウキャラデータ転送
//	TalkWinGraphicSet( wk->bgl, GF_BGL_FRAME3_M, NAMEIN_TALKWIN_CGX_OFFSET, FLD_MESFRAME_PAL, 0, HEAPID_NAMEIN );
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, TALK_MSG_WIN_PAL*32, HEAPID_NAMEIN );

	TalkWinGraphicSet( wk->bgl, GF_BGL_FRAME0_S, NAMEIN_TALKWIN_CGX_OFFSET, 
						FLD_MESFRAME_PAL, CONFIG_GetWindowType(wk->config), HEAPID_NAMEIN );
	TalkFontPaletteLoad( PALTYPE_SUB_BG, TALK_MSG_WIN_PAL*32, HEAPID_NAMEIN );

	// 下画面BG0キャラ転送
	// 下画面BG0スクリーン転送
//	ArcUtil_BgCharSet( ARC_NAMEIN_GRA, NARC_namein_name_bg_s_lz_NCGR, bgl, GF_BGL_FRAME0_S, 0, 32*2*0x20, 1, HEAPID_NAMEIN);
//	ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_bg_s_lz_NSCR, bgl, GF_BGL_FRAME0_S, 0, 32*24*2, 1, HEAPID_NAMEIN);

//	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_before_lz_ncgr, bgl, GF_BGL_FRAME0_S, 0, 0, 1, HEAPID_NAMEIN);
//	ArcUtil_ScrnSet(   ARC_POKETCH_IMG, NARC_poketch_before_lz_nscr, bgl, GF_BGL_FRAME0_S, 0, 0, 1, HEAPID_NAMEIN);


	// BMPWIN転送用キャラ用意(BgCharaBufは名前入力終了時に解放する必要あり）
	wk->BgCharaBuf = ArcUtil_CharDataGet( ARC_NAMEIN_GRA, NARC_namein_name_bg_prog_lz_NCGR, 1, &wk->BgCharaDat, HEAPID_NAMEIN );

}


//** CharManager PlttManager用 **//
#define NAMEIN_CHAR_CONT_NUM				(20)
#define NAMEIN_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define NAMEIN_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define NAMEIN_PLTT_CONT_NUM				(20)

//-------------------------------------
//
//	キャラクタマネージャー
//	パレットマネージャーの初期化
//
//=====================================
void char_pltt_manager_init(void)
{
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			NAMEIN_CHAR_CONT_NUM,
			NAMEIN_CHAR_VRAMTRANS_MAIN_SIZE,
			NAMEIN_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_NAMEIN
		};
		InitCharManager(&cm);
	}
	// パレットマネージャー初期化
	InitPlttManager(NAMEIN_PLTT_CONT_NUM, HEAPID_NAMEIN);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();
}


//------------------------------------------------------------------
/**
 * レーダー画面用セルアクター初期化
 *
 * @param   wk		レーダー構造体のポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitCellActor(NAMEIN_WORK *wk)
{
	int i;
	
	
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	// 共有OAMマネージャ作成
	// レンダラ用OAMマネージャ作成
	// ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			0, 128,		// メイン画面OAM管理領域
			0, 32,		// メイン画面アフィン管理領域
			0, 128,		// サブ画面OAM管理領域
			0, 32,		// サブ画面アフィン管理領域
			HEAPID_NAMEIN);
	
	
	
	// セルアクター初期化
	wk->clactSet = CLACT_U_SetEasyInit( 40+4, &wk->renddata, HEAPID_NAMEIN );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, NAMEIN_SUB_ACTOR_DISTANCE );

	
	//リソースマネージャー初期化
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//リソースマネージャー作成
		wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_NAMEIN);
	}


	//---------上画面用-------------------

	//chara読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_NAMEIN_GRA, NARC_namein_name_obj_m_lz_NCGR, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_NAMEIN);

	//pal読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_NCLR, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 9, HEAPID_NAMEIN);

	//cell読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_m_lz_NCER, 1, 0, CLACT_U_CELL_RES,HEAPID_NAMEIN);

	//同じ関数でanim読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_m_lz_NANR, 1, 0, CLACT_U_CELLANM_RES,HEAPID_NAMEIN);

	// ポケモンの名前入力の場合はアイコンデータを読み込む
	if(wk->inputmode==NAMEIN_POKEMON){
		wk->PokeIconBuf    = ArcUtil_CharDataGet( ARC_POKEICON, 
								PokeIconCgxArcIndexGetByMonsNumber( wk->inputinfo, 0, wk->inputform ), 
								0, 
								&wk->PokeIconCharaDat, HEAPID_NAMEIN );
		DC_FlushRange(wk->PokeIconCharaDat,0x20*4*4);

		wk->PokeIconPalBuf = ArcUtil_PalDataGet( ARC_POKEICON, PokeIconPalArcIndexGet(), &wk->PokeIconPalDat, HEAPID_NAMEIN );
		DC_FlushRange(wk->PokeIconPalDat,0x20*4);	
	}
//	ArcUtil_PalDataGet( u32 fileIdx, u32 dataIdx, NNSG2dPaletteData** palData, u32 heapID );

	//---------下画面用-------------------



	//chara読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_NAMEIN_GRA, NARC_namein_name_obj_s_lz_NCGR, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_NAMEIN);

	//pal読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_NCLR, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 3, HEAPID_NAMEIN);

	//cell読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_s_lz_NCER, 1, 1, CLACT_U_CELL_RES,HEAPID_NAMEIN);

	//同じ関数でanim読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_NAMEIN_GRA, NARC_namein_name_obj_s_lz_NANR, 1, 1, CLACT_U_CELLANM_RES,HEAPID_NAMEIN);

	// リソースマネージャーから転送

	// Chara転送
	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );

	// パレット転送
	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );

}

typedef struct{
	CLACT_WORK_PTR parent;
	CLACT_WORK_PTR child;
	int dx;
	int id;
}FUNC_BUTTON_TASK_WORK;


//------------------------------------------------------------------
/**
 * 機能ボタンがパネルフレームと同期するようにする処理
 *
 * @param   tcb		
 * @param   work	
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void FuncButtonTaskFunc( TCB_PTR tcb, void *work )
{
	const VecFx32 *pVex;
	VecFx32 cVex;
	FUNC_BUTTON_TASK_WORK *wk = (FUNC_BUTTON_TASK_WORK*)work;

	pVex   = CLACT_GetMatrix(wk->parent);
	cVex.x = pVex->x + wk->dx;
	cVex.y = FX32_ONE*main_button_info[wk->id][1];
	cVex.z = 0;
	CLACT_SetMatrix(wk->child, &cVex);
}



//------------------------------------------------------------------
/**
 * セルアクター登録
 *
 * @param   wk			NAMEIN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(NAMEIN_WORK *wk)
{
	int i;
	// セルアクターヘッダ作成
	CLACT_U_MakeHeader(&wk->clActHeader_m, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 1,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);

	CLACT_U_MakeHeader(&wk->clActHeader_s, 1, 1, 1, 1, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
	wk->resMan[CLACT_U_CHAR_RES],
	wk->resMan[CLACT_U_PLTT_RES],
	wk->resMan[CLACT_U_CELL_RES],
	wk->resMan[CLACT_U_CELLANM_RES],
	NULL,NULL);

	{
		//登録情報格納
		CLACT_ADD add;

		add.ClActSet	= wk->clactSet;
		add.ClActHeader	= &wk->clActHeader_m;

		add.mat.x		= FX32_CONST(32) ;
		add.mat.y		= FX32_CONST(96) ;		//画面は上下連続している（MAINが上、SUBが下）
		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 1;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_NAMEIN;

		//セルアクター表示開始

		// 上画面用
		for(i=0;i<9;i++){
			add.mat.x = FX32_ONE*main_button_info[i][0];
			add.mat.y = FX32_ONE*main_button_info[i][1];
			wk->clActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->clActWork[i],1);
			CLACT_AnmChg( wk->clActWork[i], main_button_info[i][2] );
			CLACT_DrawPriorityChg(wk->clActWork[i], main_button_info[i][3]);	// それぞれのアクターのプライオリティ設定
			
		}
		CLACT_SetDrawFlag( wk->clActWork[4], 0);
		CLACT_SetDrawFlag( wk->clActWork[8], 0);
		
		// 機能ボタンがパネルバーに同期して動く処理を登録
		for(i=0;i<7;i++){
			FUNC_BUTTON_TASK_WORK *twk;
			wk->FuncButtonTask[i] = PMDS_taskAdd(FuncButtonTaskFunc, 16, 5, HEAPID_NAMEIN);
			twk         = TCB_GetWork(wk->FuncButtonTask[i]);
			twk->parent = wk->clActWork[FUNCBUTTON_FRAME_ACTNO];
			twk->child  = wk->clActWork[i];
			twk->dx     = FX32_ONE*main_button_info[i][0];
			twk->id     = i;
		}

		//名前入力結果アンダーライン
		for(i=0;i<wk->inputmax;i++){
			add.mat.x = FX32_ONE*(NAMELINE_POS_X+i*12);
			add.mat.y = FX32_ONE*NAMELINE_POS_Y;
			wk->NameLineActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->NameLineActWork[i],1);
			CLACT_AnmChg( wk->NameLineActWork[i], 43 );
		}
		// １文字目のアンダーラインを上下に動かす
		InputResultUnderLineMove(wk->NameLineActWork, wk->nowinput, wk->inputmax);

		// 名前入力アイコン表示登録（モードによって切り替える）
		NameinIconAdd( wk, &add );
		
#ifdef DEBUG_OAM_POSPRINT
		// ポイント確認用
		for(i=0;i<4;i++){
			testclact[i] = CLACT_Add(&add);
			CLACT_AnmChg( testclact[i], 56+i );
		}

#endif


#ifndef NAMEIN_MAINUSE_TOUCHPANEL
		// 下画面用
		for(i=0;i<2;i++){
			add.ClActHeader	= &wk->clActHeader_s;
			add.mat.x = FX32_ONE*sub_button_info[i][0];
			add.mat.y = FX32_ONE*(sub_button_info[i][1]) + NAMEIN_SUB_ACTOR_DISTANCE;
			add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
			wk->clActWork[10+i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->clActWork[10+i],1);
			CLACT_AnmChg( wk->clActWork[10+i], sub_button_info[i][2] );
		}
#endif		
	}	
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ面ＯＮ
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);	//OBJ面ＯＮ
	
}

static void NameinIconAdd(NAMEIN_WORK *wk, CLACT_ADD *add )
{
		// 入力説明用アイコン（自機、性別、パソコン、ポケモンなど）
		add->mat.x = FX32_ONE*NAMEIN_MYICON_X;
		add->mat.y = FX32_ONE*NAMEIN_MYICON_Y;
		wk->NameIconActWork[0] = CLACT_Add(add);
		CLACT_SetAnmFlag(wk->NameIconActWork[0],1);
		switch(wk->inputmode){
		// 主人公
		case NAMEIN_MYNAME:
			if(wk->inputinfo==PM_MALE){
				CLACT_AnmChg( wk->NameIconActWork[0], 48 );	//男か女か
			}else{
				CLACT_AnmChg( wk->NameIconActWork[0], 49 );	//男か女か
			}
			break;
		// ライバル
		case NAMEIN_RIVALNAME:
			CLACT_AnmChg( wk->NameIconActWork[0], 51 );	
			break;
		// 石碑
		case NAMEIN_STONE:
			CLACT_AnmChg( wk->NameIconActWork[0], 55 );	
			break;
		// ランダムグループ
		case NAMEIN_RANDOMGROUP:
			CLACT_AnmChg( wk->NameIconActWork[0], 54 );	
			break;
		// ともだちコード
		case NAMEIN_FRIENDCODE:
		case NAMEIN_FRIENDNAME:
			CLACT_AnmChg( wk->NameIconActWork[0], 53 );	
			break;
		// パソコン
		case NAMEIN_BOX:
//			wk->NameIconActWork[0] = CLACT_Add(add);
			CLACT_AnmChg( wk->NameIconActWork[0], 47 );
			break;
		// ポケモンアイコン
		case NAMEIN_POKEMON:
			CLACT_AnmChg( wk->NameIconActWork[0], 50 );
			// 性別アイコン(性別無しでなければ）
			if(wk->inputsex!=PARA_UNK){
				add->mat.x = FX32_ONE*(NAMELINE_POS_X + wk->inputmax * 13);
				add->mat.y = FX32_ONE*NAMEIN_SEXICON_Y;
				wk->NameIconActWork[1] = CLACT_Add(add);
				if(wk->inputsex==PARA_MALE){
					CLACT_AnmChg( wk->NameIconActWork[1], 45 );	// ♂
				}else{
					CLACT_AnmChg( wk->NameIconActWork[1], 46 );	// ♀
				}
			}
			break;
		}

}


typedef struct{
	CLACT_WORK_PTR	frame;
	int				seq;
	int				dx;
	int				dy;
}QUAKE_FRAME_TASK_WORK;

static void QuakeFrameTaskFunc( TCB_PTR tcb, void *work )
{
	QUAKE_FRAME_TASK_WORK *wk = (QUAKE_FRAME_TASK_WORK *)work;
	VecFx32 tmp;
	tmp.y = wk->dy;
	tmp.z = 0;


	switch(wk->seq){
	case 0:
		tmp.x = wk->dx + 4*FX32_ONE;
		CLACT_SetMatrix(wk->frame, &tmp);
		
		break;
	case 2:
		tmp.x = wk->dx - 3*FX32_ONE;
		CLACT_SetMatrix(wk->frame, &tmp);
		break;
	case 4:
		tmp.x = wk->dx + 2*FX32_ONE;
		CLACT_SetMatrix(wk->frame, &tmp);
		break;
	case 6:
		tmp.x = wk->dx;
		CLACT_SetMatrix(wk->frame, &tmp);
		PMDS_taskDel(tcb);
		break;
	}
	wk->seq++;
}

//------------------------------------------------------------------
/**
 * 文字パネルをリクエストが来たら入れ替える
 *
 * @param   seq			遷移情報
 * @param   mode		文字入力モード（かな・カナ・ＡＢＣ・記号）
 * @param   front		前に来ているＢＧ面を保存しているワーク
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PanelFunc(GF_BGL_INI *bgl,GF_BGL_BMPWIN *win, int *seq, int mode, int *frontBG, VecFx32 panelpos[], CLACT_WORK_PTR *clActWork,void *dakuten)
{
	int front = *frontBG;
	int back  = front^1;
	int i;
	switch(*seq){

	case NAMEIN_MODE_REQ:
		{
			u16 bgcol = wordpanel_bg_col[mode]|(wordpanel_bg_col[mode]<<4);
			// 新しくやってくる文字パネル面を転送
			ArcUtil_ScrnSet( ARC_NAMEIN_GRA, NARC_namein_name_screen1_lz_NSCR+mode, bgl, GF_BGL_FRAME0_M+front, 0, WORDPANEL_TRANS_SIZE, 1, HEAPID_NAMEIN);
			SetPanelFirstPos(panelpos, front);

			WordPanelSetUp(&win[front],bgcol, mode, GF_PRINTCOLOR_MAKE(0xe,0xf,0/*wordpanel_bg_col[mode]*/),dakuten);

			(*seq)++;
		}
		break;
    	
	case NAMEIN_MODE_SET:
		// ２枚のBG面の初期座標をセット
		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+front, GF_BGL_SCROLL_X_SET, HIDDENPANEL_POS_REGX );
		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+front, GF_BGL_SCROLL_Y_SET, WORDPANEL_POS_REGY   );
		(*seq)++;
		break;
    	
	case NAMEIN_MODE_ANIM:
		// BG面を移動させる。
		// 定位置まできたらストップ（新パネル到着時はフレームが揺れる）
		
		
		panelpos[front].x-=WORDPANEL_IN_SPEED;
		if(panelpos[front].x < WORDPANEL_POS_REGX+10){		// フレームを揺らす
			QUAKE_FRAME_TASK_WORK *qtfw;
			TCB_PTR qt;
			
			qt          = PMDS_taskAdd(QuakeFrameTaskFunc, 16, 0, HEAPID_NAMEIN);
			qtfw        = TCB_GetWork(qt);
			qtfw->frame = clActWork[7];
			qtfw->seq   = 0;
			qtfw->dx    = CLACT_GetMatrix(clActWork[7])->x;
			qtfw->dy    = CLACT_GetMatrix(clActWork[7])->y;

			panelpos[front].x=WORDPANEL_POS_REGX;
			(*seq)++;
		}
		// 定位置まで来たらストップ
		panelpos[back].y-=WORDPANEL_OUT_SPEED;
		if(panelpos[back].y < DOWNPANEL_POS_REGY){
			panelpos[back].y=DOWNPANEL_POS_REGY;
		}


		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+front, GF_BGL_SCROLL_X_SET, panelpos[front].x );
		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+back,  GF_BGL_SCROLL_Y_SET, panelpos[back].y );

		break;
    	
    case NAMEIN_MODE_ANIM_WAIT:
		// 定位置まで来たらストップ
		panelpos[back].y-=WORDPANEL_OUT_SPEED;
		if(panelpos[back].y < DOWNPANEL_POS_REGY){
			panelpos[back].y=DOWNPANEL_POS_REGY;
		}


		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+front, GF_BGL_SCROLL_X_SET, panelpos[front].x );
		GF_BGL_ScrollSet( bgl, GF_BGL_FRAME0_M+back,  GF_BGL_SCROLL_Y_SET, panelpos[back].y );
		// 両方のBG面が移動終了したらシーケンス終了
		if(panelpos[front].x==WORDPANEL_POS_REGX && panelpos[back].y==DOWNPANEL_POS_REGY){
			(*seq)++;
			(*frontBG) ^=1;			//ＢＧ面の上下を入れ替える
			FrontBackBG_RegSet(bgl, *frontBG, panelpos);
			Snd_SePlay( SEQ_SE_DP_NAMEIN_01 );
		}
    	break;
	case NAMEIN_MODE:
		break;
    	

	}
}


//------------------------------------------------------------------
/**
 * @brief   会話ウインドウに描画を行う
 *
 * @param   bmp		
 * @param   inputmode		
 * @param   Title		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PrintTalkInfoStr( GF_BGL_BMPWIN *bmp, int inputmode, STRBUF *Title )
{

	BmpTalkWinWrite( bmp, WINDOW_TRANS_ON, NAMEIN_TALKWIN_CGX_OFFSET, FLD_MESFRAME_PAL );

	/* wk->msg_index = */ GF_STR_PrintSimple( bmp, FONT_TALK, Title, 0, 0, MSG_ALLPUT, NULL );
	
	GF_BGL_BmpWinOn( bmp );
}
//------------------------------------------------------------------
/**
 * 「～のなまえは？」文字列を描画する
 *
 * @param   bmp			文字列描画用BMPWIN構造体
 * @param   inputmode	入力モード（MYNAME,POKEMON,BOX)
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PrintTitleInfoStr(GF_BGL_BMPWIN *bmp, int inputmode, STRBUF *Title)
{
	int x = 16;

	int length = FontProc_GetPrintStrWidth( FONT_SYSTEM, Title, 0 );

	// 長い文字列は０から描画するが、短い文字列は少し右に動かす
	if(length>130){
		x = 0;
	}

	GF_BGL_BmpWinDataFill( bmp, 0x0101 );

	GF_STR_PrintColor(	bmp, FONT_SYSTEM, Title, x, 0, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);

	GF_BGL_BmpWinOn( bmp );

}

//------------------------------------------------------------------
/**
 * BMPWIN処理（文字パネルにフォント描画）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpMessageSet(NAMEIN_WORK *wk, PROC* proc)
{
	// BG0面用（文字パネル1用）BMPウインドウ確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_WORDPANEL_BG0], GF_BGL_FRAME0_M,
						WORDPANEL_WIN_POSX, WORDPANEL_WIN_POSY, WORDPANEL_WIN_W, WORDPANEL_WIN_H, 1,  WORDPANEL0_WIN_OFFSET);

	// BG1面用（文字パネル2用）BMPウインドウ確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_WORDPANEL_BG1], GF_BGL_FRAME1_M,
						WORDPANEL_WIN_POSX, WORDPANEL_WIN_POSY, WORDPANEL_WIN_W, WORDPANEL_WIN_H, 1,  WORDPANEL1_WIN_OFFSET);

	//最初に見えている面なので文字パネル描画と転送も行う
	// 文字パネル初期化・登録
	if(wk->inputmode==NAMEIN_POKEMON){
		ArcUtil_ScrnSet( ARC_NAMEIN_GRA, NARC_namein_name_screen1_lz_NSCR+1, wk->bgl, GF_BGL_FRAME1_M, 0, WORDPANEL_TRANS_SIZE, 1, HEAPID_NAMEIN);
		wk->mode = NAMEIN_MODE_KANA;
		MakeWordMap(wk->wordmap,1);			// カタカナ文字マップ展開
		WordPanelSetUp( &wk->NameInWin[BMP_WORDPANEL_BG1],0x0707, 1, 
						GF_PRINTCOLOR_MAKE(0xe,0xf,0/*wordpanel_bg_col[1]*/),wk->BgCharaDat->pRawData);
	}else if(wk->inputmode==NAMEIN_FRIENDCODE){
		ArcUtil_ScrnSet( ARC_NAMEIN_GRA, NARC_namein_name_screen1_lz_NSCR+3, wk->bgl, GF_BGL_FRAME1_M, 0, WORDPANEL_TRANS_SIZE, 1, HEAPID_NAMEIN);
		wk->mode = NAMEIN_MODE_NUMCODE;
		MakeWordMap(wk->wordmap,4);			// 数字のみ文字マップ展開
		WordPanelSetUp( &wk->NameInWin[BMP_WORDPANEL_BG1],0x0a0a, 4, 
						GF_PRINTCOLOR_MAKE(0xe,0xf,0/*wordpanel_bg_col[3]*/),wk->BgCharaDat->pRawData);
	}else{
		wk->mode = NAMEIN_MODE_HIRA;
		MakeWordMap(wk->wordmap,0);			// ひらがな文字マップ展開
		WordPanelSetUp( &wk->NameInWin[BMP_WORDPANEL_BG1],0x0404, 0, 
						GF_PRINTCOLOR_MAKE(0xe,0xf,0/*wordpanel_bg_col[0]*/),wk->BgCharaDat->pRawData);
	}




	// 画面上部メッセージ用BMPWIN確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_TITLE_MES], GF_BGL_FRAME2_M,
						NAME_INFO_POSX, NAME_INFO_POSY, NAME_INFO_POSW, NAME_INFO_POSH, 0,  NAMEINFO_WIN_OFFSET);



	{
		int w =  ( (wk->inputmax*12) /8 )+1;	// 12dot文字で必要なキャラ数の算出

		// 名前表示用BMPWIN確保
		GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_RESULT_NAME], GF_BGL_FRAME2_M,
							NAME_RESULT_POSX, NAME_RESULT_POSY, w, NAME_RESULT_POSH, 0,  NAMERESULT_WIN_OFFSET);
		GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );


		// 「グループ」文字列
		GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_GROUP_STRING], GF_BGL_FRAME2_M,
						NAME_RESULT_POSX+w-1, GROUP_TEXT_POSY, GROUP_TEXT_POSW, GROUP_TEXT_POSH, 0,  GROUP_TEXT_WIN_OFFSET);
		GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_GROUP_STRING], 0x0101 );
	}

	if(wk->inputmode==NAMEIN_RANDOMGROUP){
		PrintTitleInfoStr(&wk->NameInWin[BMP_GROUP_STRING], wk->inputmode, wk->GroupString );
		GF_BGL_BmpWinOn( &wk->NameInWin[BMP_GROUP_STRING] );
	}


	// BOX預け用に会話ウインドウ領域を確保する
	GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_TALK_WIN], GF_BGL_FRAME0_S,
						TALK_MSG_WIN_PX, TALK_MSG_WIN_PY, TALK_MSG_WIN_SX, TALK_MSG_WIN_SY, TALK_MSG_WIN_PAL, BOX_MESAGGE_WIN_OFFSET);
	GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_TALK_WIN], 0x0f0f );
	

	// 「～のなまえは？」文字列を表示
	PrintTalkInfoStr(&wk->NameInWin[BMP_TALK_WIN], wk->inputmode, wk->TitleStr);


	// NAMEIN_PARAMにデフォルト文字列が入っていたら反映させる
	{
		NAMEIN_PARAM* param = (NAMEIN_PARAM*)PROC_GetParentWork(proc);

		if(wk->paramstr[0]!= EOM_)
		{
			PM_strcpy(wk->inputword,wk->paramstr);
			NameinWordPanelPrint(&wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
									INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);		
		}
	}
	
	// 下画面ボタン用BMP確保
	{
		int i;
		// 「は　ば　ぱ」など
		for(i=0;i<3;i++){
			// どうせOBJVRAMに転送するので、BG面はどこでもいい
			GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_SUB_BUTTON1+i], GF_BGL_FRAME2_M,	0, 0, 2, 2, 0,  SUB_BUTTON_WORD_OFFSET);
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_SUB_BUTTON1+i], 0 );
		}

		// 「かたちをかえる」
		// どうせOBJVRAMに転送するので、BG面はどこでもいい
		GF_BGL_BmpWinAdd(wk->bgl, &wk->NameInWin[BMP_SUB_STRING], GF_BGL_FRAME2_M,	0, 0, 16, 2, 0,  SUB_BUTTON_STRING_OFFSET);
		GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_SUB_STRING], 0 );


	}
}	

//------------------------------------------------------------------
/**
 * Bg0面とBG1面のプライオリティがコロコロ変わるので関数化
 *
 * @param   front	どちらの面が上に来るか(0 or 1)
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void FrontBackBG_RegSet(GF_BGL_INI *bgl, int front, VecFx32 panelpos[])
{
	GF_BGL_PrioritySet( GF_BGL_FRAME0_M+front, 1 );
	GF_BGL_PrioritySet( GF_BGL_FRAME0_M+front^1, 2 );

}

//------------------------------------------------------------------
/**
 * 文字パネルの初期座標保存
 *
 * @param   panelpos[]		文字パネルの位置
 * @param   front				BG0面とBG1面のどちらが上か(0だとBG0が上)
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetPanelFirstPos(VecFx32 panelpos[], int front)
{
	panelpos[front].x   = HIDDENPANEL_POS_REGX;
    panelpos[front].y   = WORDPANEL_POS_REGY;
    panelpos[front^1].x = WORDPANEL_POS_REGX;
    panelpos[front^1].y = WORDPANEL_POS_REGY;
	
}

#ifdef PM_DEBUG
//------------------------------------------------------------------
/**
 * デバッグ表示用にOBJやBGを動かす
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DebugOBJPOSGet(NAMEIN_WORK *wk)
{
		if( sys.cont & PAD_KEY_UP){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][1]--;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
		}
		if( sys.cont & PAD_KEY_DOWN){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][1]++;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
			
		}
		if( sys.cont & PAD_KEY_LEFT){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][0]--;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
			
		}
		if( sys.cont & PAD_KEY_RIGHT){
			VecFx32 tmpVex;
			wk->framenum[wk->frame][0]++;
			tmpVex.x = FX32_ONE*wk->framenum[wk->frame][0];
			tmpVex.y = FX32_ONE*wk->framenum[wk->frame][1];
			CLACT_SetMatrix(wk->clActWork[wk->frame], &tmpVex);
			OS_Printf("frame %d x=%d, y=%d\n",wk->frame, wk->framenum[wk->frame][0],wk->framenum[wk->frame][1]);
		}

}

#endif



#define MOVE_UP 	1
#define MOVE_DOWN 	2
#define MOVE_LEFT 	3
#define MOVE_RIGHT 	4

static const arrowtbl[][2]={{0,0},{0,-1},{0,1},{-1,0},{1,0}};

static int AroundWork(int w, int min, int max)
{
	if(w>=max){
		w = min;
	}
	if(w<min){
		w = max-1;
	}
	return w;
}

//------------------------------------------------------------------
/**
 * カーソル移動部
 *
 * @param   wk		NAMEIN_WORK*
 * @param   arrow	移動方向フラグ
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void CursorMove(NAMEIN_WORK *wk, int arrow)
{
	int x,y;
	u16 old;
	
	if(arrow==0){
		return;
	}
	
	// 縦一列がSKIPの列だと、無限ループに入るので要修正（となりの列を検索するなど）
	old  = wk->wordmap[wk->Cursor.y][wk->Cursor.x];
	x    = AroundWork((wk->Cursor.x + arrowtbl[arrow][0]), 0, INPUT_WORD_W);
	y    = AroundWork((wk->Cursor.y + arrowtbl[arrow][1]), 0, INPUT_WORD_H);

	// X方向の移動（機能ボタン・スキップ列処理込み）
	while(wk->wordmap[y][x]==SKIP_ || (wk->wordmap[y][x]==old && wk->wordmap[y][x]>NAMEIN_BUTTON)){
//		OS_Printf(" %d, %d, \n",wk->wordmap[y][x], old, );

		if(wk->Cursor.oldy==0 && wk->wordmap[y][x]==SKIP_ && arrowtbl[arrow][1]!=0){	// ボタンの上にいて、下の行にSKIPが
			x += wk->Cursor.lastxarrow;													// あった場合の処理（最後の横移動を
			x = AroundWork(x, 0, INPUT_WORD_W);											// とっておいてその方向にずらす）
		}else{
			x += arrowtbl[arrow][0];													// 移動先がSKIP_だった場合は
			x = AroundWork(x, 0, INPUT_WORD_W);											// SKIP_じゃなくなるまで移動を繰り返す
			y += arrowtbl[arrow][1];
			y = AroundWork(y, 0, INPUT_WORD_H);
		}
	}
	
	// 最終移動先を格納
	wk->Cursor.x = x;	
	wk->Cursor.y = y;
}

//------------------------------------------------------------------
/**
 * カーソル移動処理
 *
 * @param   wk		NAMEIN_WORK*
 *
 * @retval  none	
 */
#ifdef NAMEIN_MAINUSE_TOUCHPANEL
static BOOL TouchPanelCheck( NAMEIN_WORK *wk );
#endif
//------------------------------------------------------------------
static void ControlCursor(NAMEIN_WORK *wk)
{
	int move  = 0;
	int arrow = 0;

	// キー入力に対して移動する４方向のうちの一つを決定
	if( sys.repeat & PAD_KEY_UP){
		Snd_SePlay(NAMEIN_SE_MOVE);
		CLACT_SetDrawFlag( wk->clActWork[8], 1);
		arrow = MOVE_UP;
		move++;
	}
	if( sys.repeat & PAD_KEY_DOWN){
		Snd_SePlay(NAMEIN_SE_MOVE);
		CLACT_SetDrawFlag( wk->clActWork[8], 1);
		arrow = MOVE_DOWN;
		move++;
	}
	if( sys.repeat & PAD_KEY_LEFT){
		Snd_SePlay(NAMEIN_SE_MOVE);
		CLACT_SetDrawFlag( wk->clActWork[8], 1);
		arrow = MOVE_LEFT;
		move++;
	}
	if( sys.repeat & PAD_KEY_RIGHT){
		Snd_SePlay(NAMEIN_SE_MOVE);
		CLACT_SetDrawFlag( wk->clActWork[8], 1);
		arrow = MOVE_RIGHT;
		move++;
	}
	
	// 終了ボタン位置へ
	if( sys.trg & PAD_BUTTON_START){
		Snd_SePlay(NAMEIN_SE_MOVE);
		CLACT_SetDrawFlag( wk->clActWork[8], 1);
		wk->Cursor.x = 12;
		wk->Cursor.y = 0;
		move++;
	}
#ifdef NAMEIN_MAINUSE_TOUCHPANEL
	{
		if( ( wk->TP_decide = TouchPanelCheck( wk ) ) == TRUE ){
			arrow = 0;
			move++;
		}
	}
#endif
	// 移動が発生したら変更
	if(move){
		CursorMove(wk,arrow);				// カーソルの移動先を決定する
		CursorAppearUpDate(wk,arrow);	// 移動の結果カーソルの形状がどのように変わるかを決定する
	}

}


//------------------------------------------------------------------
/**
 * 移動の結果カーソルの形状がどのように変わるかを決定する
 * 文字の上であれば、正方形のカーソル、ボタンの上であれば長方形のカーソル
 * 文字の更新が行われることで、サブ画面の中のフォントの更新も行われる
 *
 * @param   wk			NAMEIN_WORK*
 * @param   arrow		移動方向
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorAppearUpDate(NAMEIN_WORK *wk, int arrow)
{
	// カーソルが文字の列にいるか？
	if(wk->Cursor.y!=0){
		VecFx32 tmpVex;

		// 文字の列にいる
		if(wk->Cursor.oldy==0 && wk->Cursor.oldy != wk->Cursor.y){		// 直前にファンクションボタンの上にいたら
			CLACT_AnmChg( wk->clActWork[8], NAMEIN_CURSOR_ANM_START );	// 通常カーソルにアクター変更
		}
		tmpVex.x = FX32_ONE*(MAIN_CURSOR_POSX+wk->Cursor.x*16);
		tmpVex.y = FX32_ONE*(MAIN_CURSOR_POSY+(wk->Cursor.y-1)*PANEL_H);
		CLACT_SetMatrix(wk->clActWork[CLACT_CURSOR_NUM], &tmpVex);
	}else{
		VecFx32 tmpVex;

		// ボタンの列にいる
		int func_type = wk->wordmap[wk->Cursor.y][wk->Cursor.x]-NAMEIN_HIRA;
		tmpVex.x = FX32_ONE*func_button_pos_tbl[func_type];
		tmpVex.y = FX32_ONE*FUNC_BUTTON_POS_Y;
		CLACT_AnmChg( wk->clActWork[8], func_button_appear[func_type] );// ボタンに対応したカーソルに変更
		CLACT_SetMatrix(wk->clActWork[CLACT_CURSOR_NUM], &tmpVex);

		
	}
	wk->CursorPal = 180;							// 移動したらカーソルのパレットは赤い状態に戻す
	CLACT_AnmFrameSet( wk->clActWork[8], 0 );		// 移動したらカーソルのアニメは最初のフレームに戻す


	wk->Cursor.oldx       = wk->Cursor.x;
	wk->Cursor.oldy       = wk->Cursor.y;
	if(arrowtbl[arrow][0]!=0){
		wk->Cursor.lastxarrow = arrowtbl[arrow][0];
	}

}

//------------------------------------------------------------------
/**
 * アニメーションにあわせて下画面のボタンBGのスクリーンを書き換える
 *
 * @param   mode		
 * @param   work		
 * @param   bgl		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SubButtonBGFunc(int *mode, int *work, GF_BGL_INI *bgl)
{

	switch(*work){
	case 1:	case 5:
	// 下画面BG0スクリーン転送
		ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_bg_s2_lz_NSCR, bgl, GF_BGL_FRAME0_S, 0, 32*24*2, 1, HEAPID_NAMEIN);
		break;
	case 3:	
	// 下画面BG0スクリーン転送
		ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_bg_s3_lz_NSCR, bgl, GF_BGL_FRAME0_S, 0, 32*24*2, 1, HEAPID_NAMEIN);
		break;
	case 7:	
	// 下画面BG0スクリーン転送
		ArcUtil_ScrnSet(   ARC_NAMEIN_GRA, NARC_namein_name_bg_s_lz_NSCR, bgl, GF_BGL_FRAME0_S, 0, 32*24*2, 1, HEAPID_NAMEIN);
		break;
	}


	// 「押し」か「離し」の際にはworkを上げ下げする
	if(mode!=0){		// 
		if(*work > 9 ){	// 6以上にはならないように
			*work = 0;
			*mode  = 0;
		}
		*work += *mode;
	}
//	OS_Printf("mode = %d, work = %d\n",mode, *work);
}

//------------------------------------------------------------------
/**
 * タッチパネルで押したボタンがへこむ
 *
 * @param   wk		NAMEIN_WORKのポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void TouchFunc(NAMEIN_WORK *wk)
{
#ifndef NAMEIN_MAINUSE_TOUCHPANEL
	int button=-1,i;

	// 入力処理
	button=GF_TP_RectHitTrg( sub_button_hittbl );
	if(button != RECT_HIT_NONE && wk->subtouchword[button] != spc_){
//		DecideMainButton(wk,wk->subtouchword[button]);
		DecideMainButton(wk,NAMEIN_KOMOJI,1);				// 変換ボタンON
		CLACT_AnmChg( wk->clActWork[10], sub_button_info[0][2] );	// 下画面の文字をBGに合わせて上下に動かす
		CLACT_AnmChg( wk->clActWork[11], sub_button_info[1][2]+1 );	// 下画面の文字をBGに合わせて上下に動かす
		wk->subbutton_mode=1;
	}

	// 見た目の処理
//	button=GF_TP_RectHitCont( sub_button_hittbl );

	SubButtonBGFunc(&wk->subbutton_mode, &wk->subbutton_work, wk->bgl);
#endif
}


//------------------------------------------------------------------
/**
 * カーソルのパレット変更（点滅）
 *
 * @param   CursorCol	sinに渡すパラメータ（360まで）
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorColTrans(u16 *CursorCol)
{
	fx32  sin;
	GXRgb tmp;
	int   r,g,b;

	*CursorCol+=20;
	if(*CursorCol>360){
		*CursorCol = 0;
	}

	sin = Sin360R(*CursorCol);
	g   = 15 +( sin * 10 ) / FX32_ONE;
	tmp = GX_RGB(29,g,0);


	GX_LoadOBJPltt((u16*)&tmp, (16+13)*2, 2);
}



//------------------------------------------------------------------
/**
 * 文字パネルに均等な間隔に文字を配置する
 * プロポーショナルフォントなので横幅を確認しながら一文字ずつ配置する
 *
 * 「”」「゜」「[s]」に対応(CODEはDAKUTEN_,HANDAKUTEN_,SPACE_）
 * 横幅は12ドットずつ配置される事にする。
 *
 * @param   win		bmp
 * @param   str		文字列
 * @param   x		開始X（左上）
 * @param   y		開始Y（左上）
 * @param   sw		MSG_ALLPUTかMSG_NO_PUT
 * @param   color	5bitx3のカラー指定
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NameinWordPanelPrint(GF_BGL_BMPWIN *win, const u16 *str, int x,int y, int space, int sw, GF_PRINTCOLOR color, u8 *dakuten_Character)
{
	int i=0,w,dx;
	u16 word[2];
	STRBUF *strbuf_word;
	
	strbuf_word = STRBUF_Create( 2, HEAPID_NAMEIN );
	// 一文字ずつ取り出す
	while(str[i]!=EOM_){
		// 特殊文字だった場合の処理
		if(str[i]==DAKU_ || str[i]==HANDAKU_ || str[i]==SPACE_){
			u16 tmp = str[i] - NAMEIN_CODE;


			//12x12の特殊文字を描画
			GF_BGL_BmpWinPrint(	win, (void*)&dakuten_Character[tmp*8*8*4/2],
				0, 0, 12, 12,
				x+i*space, y+2, 12, 12 );

		}else{
		// 通常文字処理

			if(str[i]==SKIP_){		//スキップ記号は描画しない
				i++;
				continue;
			}
			word[0] = str[i];
			word[1] = EOM_;

			//フォントの横幅を取得し、12ドットずつ配置するときの差を算出して描画
			w=FontProc_GetStrWidth( FONT_SYSTEM, word, 0 );
			dx = x+i*space+((space-w)/2);
			STRBUF_SetStringCode( strbuf_word, word );
			GF_STR_PrintColor(	win, FONT_SYSTEM, strbuf_word, dx, y, sw, color,NULL);

		}
		i++;
	}	
	STRBUF_Delete( strbuf_word );
}


static const u8 StringCharacterOffsetTable[]={
	96,104,80,88
};


static void *GF_STR_PrintCGXOnly(GF_BGL_BMPWIN * win, STRBUF *msg, u8 fnt_index,const   GF_PRINTCOLOR col)
{

	GF_STR_PrintColor(	win, fnt_index, msg, 0, 0, MSG_NO_PUT, col,NULL);

	return win->chrbuf;
}

//------------------------------------------------------------------
/**
 * 下画面のボタンに書かれている文字キャラクターを転送
 *
 * @param   win		文字を展開するBMPWIN構造体のポインタ
 * @param   tbl		「はばぱ」などの変換後も文字も入ったテーブルのポインタ。無い時はNULL
 * @param   code	変換候補の無い文字はここに入れる。tblがあるときは0
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ChangeSubPanelButtonWord(GF_BGL_BMPWIN *win, const u16 *tbl, u8 *TransWork, STRBUF *ChangeWordStr)
{
	u16  word[SUB_BUTTON_STRING_MAX+1],i,n;
	void *objcharaadr;
	STRBUF *strbuf_word;

	GF_BGL_BmpWinDataFill( &win[3], 0 );
	
	// 「かたちをかえる」描画
	objcharaadr=GF_STR_PrintCGXOnly(&win[3], ChangeWordStr, FONT_BUTTON, GF_PRINTCOLOR_MAKE(0xd,0x0e,0xf));

	// BMP処理で描画したバッファをOBJに転送して反映させる
	DC_FlushRange(objcharaadr,0x20*4*16);	
	for(i=0;i<4;i++){						
		FONTOAM_BmpCutOamSize( &win[3], 4, 2, 4*i, 0,  (char*)TransWork);
		DC_FlushRange(TransWork,0x20*4*2);	
		GXS_LoadOBJ(TransWork, StringCharacterOffsetTable[i]*0x20, 0x20*4*2);
	}


	// STRBUF作成
	strbuf_word = STRBUF_Create(SUB_BUTTON_STRING_MAX+1, HEAPID_NAMEIN);
	
	// BMPWINで文字キャラクタを作成した後、OBJVRAMに転送する処理を３回繰り返す
	for(i=0;i<3;i++){
		word[0] = tbl[i];
		word[1] = EOM_;
		GF_BGL_BmpWinDataFill( &win[i], 0 );

		// STRBUFに変換、BMP処理でキャラクター描画
		STRBUF_SetStringCode( strbuf_word, word );
		objcharaadr=GF_STR_PrintCGXOnly(&win[i], strbuf_word, FONT_BUTTON, GF_PRINTCOLOR_MAKE(0xd,0x0e,0xf));

		// BMP処理で描画したバッファをOBJに転送して反映させる
		DC_FlushRange(objcharaadr,0x20*4);	
		GXS_LoadOBJ(objcharaadr, obj_word_offset[i]*0x20, 0x20*4);

	}

	STRBUF_Delete(strbuf_word);
}

//------------------------------------------------------------------
/**
 * カーソルが移動した時に、下画面ボタンの中の文字を書き換える
 *
 * @param   win		GF_BGL_BMPWIN*
 * @param   code	文字コード
 * @param   words	NAMEIN_WORK.subtouchword
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SubPanelButton_CharaChange(GF_BGL_BMPWIN *win, STRCODE *str,int pos, u16 *words, u8 *TransWork, STRBUF *ChangeWordStr)
{
	int i,r;
	const u16 *tbl = NULL;
	STRCODE code;

	if(pos==0){
		code = SPACE_;
	}else{
		code = str[pos-1];
	}

	// 特殊文字・ボタンのコードは全て空白文字として表示
	switch(code){
	case DAKU_			:	case HANDAKU_		:	case SPACE_			:	case SKIP_			:
	case NAMEIN_HIRA	:	case NAMEIN_KANA	:	case NAMEIN_ALPHA	:	case NAMEIN_KIGOU	:
	case NAMEIN_KOMOJI	:	case NAMEIN_MODORU	:	case NAMEIN_OWARI	:
		code = spc_;
	break;
	}
	
	for(i=0;i<3;i++){		// 一旦初期化
		words[i] = spc_;
	}
	words[0] = code;		// 元コード代入

	if(code!=spc_){	
		// 変換テーブルを検索して濁音・半濁音・小文字を持つ文字を探す
		for(i=0;i<sizeof(convert_tbl)/(3*2);i++){
			// 変換前の文字
			if(convert_tbl[i][0]==code){
				for(r=0;r<3;r++){
					words[r] =  convert_tbl[i][r];	// 見つかったらテーブルをコピー
				}
				break;
			}
			// 変換後の小文字（小文字も直接入力できるようになったので）
			if(convert_tbl[i][2]==code){
				for(r=0;r<3;r++){
					words[r] =  convert_tbl[i][r];	// 見つかったらテーブルをコピー
				}
				break;
			}
		}
	}

	// WINBMP上で処理、OBJVRAMに転送
	ChangeSubPanelButtonWord(win, words, TransWork, ChangeWordStr);
}



//------------------------------------------------------------------
/**
 * 現在入力文字パネルマップを作成する
 *
 * @param   map[][INPUT_WORD_W]		書き込む文字マップワーク
 * @param   no						文字パネル番号(0-3)
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void MakeWordMap(u16 map[][INPUT_WORD_W], const int no)
{
	int i,j;
	
	//画面最上段のボタン配置設定
	for(i=0;i<INPUT_WORD_W;i++){
		map[0][i] = str_func_b[no][i];
	}
	
	for(j=0;j<INPUT_WORD_H-1;j++){
		for(i=0;i<INPUT_WORD_W;i++){
			map[1+j][i] = str_nametbl[no][j][i];
		}
	}
}

//------------------------------------------------------------------
/**
 * 文字入力決定
 *
 * @param   wk		NAMEIN_WORK*
 * @param   code	文字コード(ボタン・特殊文字も含む)
 *
 * @retval  int		通常はSEQ_MAIN。終了時はSEQ_OUT
 */
//------------------------------------------------------------------
static int DecideMainButton(NAMEIN_WORK *wk,u16 code, int pad)
{
	// 特殊文字・ボタンのコードは全て空白文字として表示
	if(code==SPACE_ || code == SKIP_){
		code = spc_;
	}

	// フレンドコード入力の時の制限
	if(wk->inputmode==NAMEIN_FRIENDCODE){
		if(code==NAMEIN_HIRA || code==NAMEIN_KANA || code==NAMEIN_ALPHA || code==NAMEIN_KIGOU ){
			code = spc_;
		}
	}

	switch(code){
	// 濁音 
	case DAKU_			:	
		if(ConvertWord(DAKU_WORD_START,DAKU_WORD_NUM,1,DAKU_,wk->inputword,wk->nowinput)){
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );
			NameinWordPanelPrint(&wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
									INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);
			Snd_SePlay(NAMEIN_SE_DECIDE);
		}
		break;
	// 半濁音
	case HANDAKU_		:	
		if(ConvertWord(HANDAKU_WORD_START,HANDAKU_WORD_NUM,2,HANDAKU_,wk->inputword,wk->nowinput)){
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );
			NameinWordPanelPrint(&wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
									INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);
			Snd_SePlay(NAMEIN_SE_DECIDE);
		}
		break;
	// 小文字
	case NAMEIN_KOMOJI	:
		if(RotateConvertWord(BIGSMALL_WORD_START,HANDAKU_WORD_NUM,wk->inputword,wk->nowinput)){
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );
			NameinWordPanelPrint(&wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
									INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);
			wk->funcbutton[4]++;
			Snd_SePlay(NAMEIN_SE_DECIDE);
		}
		break;

	// 文字パネル切り替えボタン
	case NAMEIN_HIRA	:	case NAMEIN_KANA	:	case NAMEIN_ALPHA	:	case NAMEIN_KIGOU	:
		// パネル切り替え
		if(wk->mode!=code-NAMEIN_HIRA){
			wk->seq  = NAMEIN_MODE_REQ;
			wk->mode = code-NAMEIN_HIRA;
			MakeWordMap(wk->wordmap, wk->mode);		// 文字入力マップ差し替え
			wk->funcbutton[code-NAMEIN_HIRA]++;
			Snd_SePlay( NAMEIN_SE_CHANGEPANEL );
			CLACT_SetDrawFlag( wk->clActWork[8], pad);
		}
		break;

	// 1文字戻る
	case NAMEIN_MODORU	:
		if(wk->nowinput!=0){
			wk->inputword[wk->nowinput-1] = EOM_;
			wk->nowinput--;
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );
			if(wk->nowinput==0){
				// 0文字だと文字プリントが成立しないので
				GF_BGL_BmpWinOn( &wk->NameInWin[BMP_RESULT_NAME] );
			}else{
				NameinWordPanelPrint(&wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
										INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);
			}
			SubPanelButton_CharaChange(&wk->NameInWin[BMP_SUB_BUTTON1],
										wk->inputword,
										wk->nowinput,
										wk->subtouchword,
										wk->ObjTransWork,
										wk->ChangeWordStr);
			InputResultUnderLineMove(wk->NameLineActWork,wk->nowinput, wk->inputmax);
			wk->funcbutton[5]++;
			Snd_SePlay(NAMEIN_SE_BS);
			CLACT_SetDrawFlag( wk->clActWork[8], pad);
		}
		break;
	// 名前入力終了
	case NAMEIN_OWARI	:		
		// ナビゲーションアイコンアニメ終了
//		MSG_DsIconFlashReq( wk->dsicon_task, MSG_DSI_REQ_FREE );

		// こっちの方がすぐ消えるので安全
		MSG_DsIconFlashDelete( wk->dsicon_task );
		CLACT_SetDrawFlag( wk->clActWork[8], pad);

		// 入力終了
		if(wk->endmode==0){
			Snd_SePlay( NAMEIN_SE_END );
			wk->funcbutton[6]++;
			WIPE_SYS_Start(WIPE_PATTERN_FSAM, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_NAMEIN );
			return SEQ_OUT;
		}else{
			wk->seq = NAMEIN_MODE_BOXMSG;
		}
	break;

	// 通常の文字入力
	default:
		if(wk->mode==NAMEIN_MODE_NUMCODE && code==spc_){
			return SEQ_MAIN;
		}

		if(wk->nowinput!=wk->inputmax){				//Maxまで行ってなかったら入力
			wk->inputword[wk->nowinput] = code;
			GF_BGL_BmpWinDataFill( &wk->NameInWin[BMP_RESULT_NAME], 0x0101 );
			NameinWordPanelPrint( &wk->NameInWin[BMP_RESULT_NAME], wk->inputword, 0,0, 
									INPUT_WORD_SPACE, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0xe,0xf,1),NULL);
			wk->nowinput++;
			InputResultUnderLineMove(wk->NameLineActWork,wk->nowinput, wk->inputmax);
			Snd_SePlay(NAMEIN_SE_DECIDE);

				// 半透明にして赤い丸のアニメに切り替える
				CLACT_SetDrawFlag( wk->clActWork[8], 1);
				CLACT_ObjModeSet( wk->clActWork[8], GX_OAM_MODE_XLU );
				G2_SetBlendAlpha( 0,GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2,8,8 );
				CLACT_AnmChg( wk->clActWork[8], 60);
				wk->Cursor.decide = 1;
			
			SubPanelButton_CharaChange(&wk->NameInWin[BMP_SUB_BUTTON1],
										wk->inputword,
										wk->nowinput,
										wk->subtouchword,
										wk->ObjTransWork,
										wk->ChangeWordStr);

		}
	}	
	
	return SEQ_MAIN;
}

//------------------------------------------------------------------
/**
 * 小文字・濁点・半濁点が並んでいるテーブルに順次入れ替えた文字を返す
 * 「あ」なら「ぁ→あ」、「は」なら「ば→ぱ→は」
 * @param   tbl		
 * @param   pos		
 *
 * @retval  u16		
 */
//------------------------------------------------------------------
static u16 GetConvertWord(const u16 *tbl, int pos)
{

	do{
		pos = AroundWork(++pos,0,3);
//		OS_Printf("pos = %d, code = %d",pos,tbl[pos]);
	}while(tbl[pos]==spc_);
	
//	OS_Printf("last --- pos = %d, code = %d",pos,tbl[pos]);
	return tbl[pos];
}

//------------------------------------------------------------------
/**
 * 「かたちをかえる」ボタン処理
 *
 * @param   start	convert_tblを検索開始する位置
 * @param   num		convert_tblを検索終了する位置
 * @param   str		文字列バッファ
 * @param   pos		現在のカーソル
 *
 * @retval  int		0なら失敗	1なら成功（strは書き換わっている)
 */
//------------------------------------------------------------------
static int RotateConvertWord(int start, int num, u16 *str, int pos)
{
	int i,r;
	u16 code,w;
	if(pos==0){
		return 0;
	}

	code = str[pos-1];

	for(i=start;i<num;i++){
		for(r=0;r<3;r++){
			if(convert_tbl[i][r]==code && code!=spc_){
				str[pos-1] = GetConvertWord(convert_tbl[i],r);
				return 1;
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------
/**
 * 入力済み文字変換処理
 *
 * @param   start	convert_tblの検索開始位置
 * @param   num		convert_tblの検索終了位置
 * @param   target	convert_tblの０文字目と比較するのは１番目か２番目か（1or2)
 * @param   flag	DAKU_,HANDAKU_,NAMEIN_KOMOJIのどれか
 * @param   str		入力済み文字列
 * @param   pos		現在入力待ちの場所
 *
 * @retval  int		0=変換無し	1=変換あり
 */
//------------------------------------------------------------------
static int ConvertWord(int start, int num, int target, int flag, u16 *str, int pos)
{
	int i;
	u16 code;

	// 1文字も入力していない場合は変換は発生しない
	if(pos==0 || str[pos-1]==spc_){
		return 0;
	}	

	// 元の文字を変換する
	code=str[pos-1];
	for(i=start;i<num;i++){
		if(convert_tbl[i][0]==code){
			str[pos-1]=convert_tbl[i][target];
			return 1;
		}
	}

	// 変換済みの文字を元に戻す
	for(i=start;i<num;i++){
		if(convert_tbl[i][target]==code){
			str[pos-1]=convert_tbl[i][0];
			return 1;
		}
	}

	//特殊処理「ば→ぱ」「づ→っ」など

	switch(flag){
	case DAKU_:
		for(i=0;i<NELEMS(extra_daku_tbl);i++){
			if(extra_daku_tbl[i][0]==code){
				str[pos-1] = extra_daku_tbl[i][1];
				return 1;
			}
		}
		break;
	case HANDAKU_:
		for(i=0;i<NELEMS(extra_handaku_tbl);i++){
			if(extra_handaku_tbl[i][0]==code){
				str[pos-1] = extra_handaku_tbl[i][1];
				return 1;
			}
		}
		break;
	case NAMEIN_KOMOJI:
		if(code==du_){
			str[pos-1] = ttu_;
			return 1;
		}
		if(code==DU_){
			str[pos-1] = TTU_;
			return 1;
		}
		break;
	}	

	// 変換文字ではなかった
	return 0;
}


//------------------------------------------------------------------
/**
 * 入力済み文字列の下のアンダーラインを動かす指定を行う
 *
 * @param   lineact		アンダーラインのセルアクターのポインタ
 * @param   pos			位置
 * @param   max			文字最大数
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InputResultUnderLineMove(CLACT_WORK_PTR *lineact,int pos, int max)
{
	int i;
	for(i=0;i<max;i++){
		CLACT_AnmChg( lineact[i], 43 );		// 全てアンダーラインが動かない状態にクリア
	}
	if(pos!=max){
		CLACT_AnmChg( lineact[pos], 44 );	// 指定の文字を上下に動かす
	}
}


#define PLATE_CHARA_OFFSET1	( 12 )
#define PLATE_CHARA_OFFSET2	( 16 )
#define PLATE_H_CHARASIZE	(  8 )	// 文字パネル内のBMP書き込み部分キャラ縦幅

static const u8 plate_num[]={2,2,3,2,2};
static const u8 plate_table[][3]={
	{8*8,17*8,0,},
	{8*8,17*8,0,},
	{5*8,12*8,18*8,},
	{8*8,17*8,0,},
	{8*8,17*8,0,},

};
static const u8 plate_chara_no[][5]={
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
};

static const u8 plate_chara_pos[5]={
	0,1,2,3,3
};

static const u8 plate_wall_col[]={3,6,0xc,9,9};

//------------------------------------------------------------------
/**
 * 文字パネルの文字配置・枠描画などを行う
 *
 * @param   win			GF_BGL_WINBMP*
 * @param   bgchara		文字パネルの背景キャラ
 * @param   frame		０～３の文字パネル番号
 * @param   color		GF_PRINTCOLOR
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void WordPanelSetUp(GF_BGL_BMPWIN *win,u16 bgchara, int frame, GF_PRINTCOLOR color, u8* dakuten_Character )
{
	int i,r,h;

	// それぞれの文字パネルの背景色でクリア
	GF_BGL_BmpWinDataFill( win, bgchara );

	// 文字パネル内の仕切りを描画
//	for(r=0;r<plate_num[frame];r++){
//		for(i=0;i<PLATE_H_CHARASIZE;i++){
//			GF_BGL_BmpWinPrint(	win, (void*)&dakuten_Character[(plate_chara_no[frame][r]+plate_chara_pos[frame])*8*8/2],
//				0, 0, 8, 8,
//				plate_table[frame][r], 8*i, 8, 8 );
//		}
//	}

	// 文字パネルに市松模様を描く
	for(i=0;i<6;i++){
		GF_BGL_BmpWinFill( win, plate_wall_col[frame], 16+32*i, 0,  16,   PANEL_H );		
		GF_BGL_BmpWinFill( win, plate_wall_col[frame], 16+32*i, 19*2, 16, PANEL_H );		
		GF_BGL_BmpWinFill( win, plate_wall_col[frame], 16+32*i, 19*4, 16, PANEL_H );		
	}
	for(i=0;i<7;i++){
		GF_BGL_BmpWinFill( win, plate_wall_col[frame], 32*i, 19,   16, PANEL_H );		
		GF_BGL_BmpWinFill( win, plate_wall_col[frame], 32*i, 19*3, 16, PANEL_H );		
	}

	// 描画
	for(i=0;i<5;i++){
		NameinWordPanelPrint(win,str_nametbl[frame][i],0,i*PANEL_H+4,
								WORDPANEL_WORD_SPACE, MSG_NO_PUT,color,dakuten_Character);
	}
	// 転送
	GF_BGL_BmpWinOn( win );

}

//------------------------------------------------------------------
/**
 * 機能ボタン（かな・カナ・ABC・きごう／小文字／もどるおわる）のアニメ処理
 *
 * @param   funcbutton[]	ボタン押し状態フラグ列
 * @param   ButtonAct		CLACT_WORK_PTR
 * @param   frame			現在の文字パネル番号
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FuncButtonAnimation(int funcbutton[], CLACT_WORK_PTR *ButtonAct, int frame)
{
	int i,r;
	// かな カナ ABC きごう ボタン
	for(i=0;i<4;i++){
		if(funcbutton[i]){
			for(r=0;r<4;r++){
				CLACT_AnmChg( ButtonAct[r], main_button_info[r][2] );
			}
			CLACT_AnmChg( ButtonAct[i], main_button_info[i][2]-3 );
			break;
		}
	}

	// 小文字化ボタン（かな カナ ABCによってセルアニメが違う）
//	if(funcbutton[4]){
//		CLACT_AnmChg( ButtonAct[4], main_button_info[4][2] + frame);	// 「記号」の小文字化ボタンは存在しない
//	}

	// もどる おわるボタン
	for(i=5;i<7;i++){
		if(funcbutton[i]){
			CLACT_AnmChg( ButtonAct[i], main_button_info[i][2]+1);
		}
	}
	
	// アニメが反映されたらクリア
	for(i=0;i<7;i++){
		funcbutton[i] = 0;
	}

}


//------------------------------------------------------------------
/**
 * @brief   カーソルアニメーション制御
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorAnimationControl( NAMEIN_WORK *wk )
{
	// カーソルがアニメ終了状態になっている場合は通常カーソルに変化させる
	if(!CLACT_AnmActiveCheck( wk->clActWork[8] )){
		if(wk->nowinput==wk->inputmax){			// 文字入力マックスまできたら「終わり」ボタンへ
			wk->Cursor.x = 12;
			wk->Cursor.y = 0;
			CLACT_AnmChg( wk->clActWork[8], NAMEIN_CURSOR_ANM_START);
			OS_Printf("書き換えた\n");
		}else{
			CLACT_AnmChg( wk->clActWork[8], NAMEIN_CURSOR_ANM_START);
		}

		// 表示ＯＮならカーソル形状を戻す・表示ＯＦＦならカーソルを隠す
		if(wk->Cursor.on==0){
			CLACT_SetDrawFlag( wk->clActWork[8], 0);
		}else{
			CursorAppearUpDate(wk,0);		// 移動の結果カーソルの形状がどのように変わるかを決定する
		}
		wk->Cursor.decide = 0;

		// 半透明ＯＢＪを解除
		CLACT_ObjModeSet( wk->clActWork[8], GX_OAM_MODE_NORMAL );
	}

}

#ifdef NAMEIN_MAINUSE_TOUCHPANEL
//------------------------------------------------------------------
/**
 * タッチパネル判定処理
 *
 * @param   wk
 * @return  
 */
//------------------------------------------------------------------
//データ設定構造体（国バイナリデータ）
typedef struct NM_TP_DATA_tag
{
	u8 x;
	u8 y;
	u16 type:2;
	u8	cx:5;
	u8	cy:5;
}NM_TP_DATA;

enum {
	CTYPE_S1 = 0,		// かたなか・ひらがな・ＡＢＣ・きごう
	CTYPE_S2 = 1,		// もどる・おわり
	CTYPE_WD = 2,		// 文字
};


static const NM_TP_DATA TouchPanelDataTable[] = {
	{ MAIN_BUTTON1_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S1, 0,0},
	{ MAIN_BUTTON2_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S1, 1,0},	
	{ MAIN_BUTTON3_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S1, 3,0},
	{ MAIN_BUTTON4_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S1, 4,0},	
	{ MAIN_BUTTON6_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S2, 8,0},
	{ MAIN_BUTTON7_POSX+21,MAIN_BUTTON_POSY-8,CTYPE_S2,11,0},

	{PANEL_X+  0, PANEL_Y+ 0,CTYPE_WD, 0,1},{PANEL_X+ 16, PANEL_Y+ 0,CTYPE_WD, 1,1},{PANEL_X+ 32, PANEL_Y+ 0,CTYPE_WD, 2,1},
	{PANEL_X+ 48, PANEL_Y+ 0,CTYPE_WD, 3,1},{PANEL_X+ 64, PANEL_Y+ 0,CTYPE_WD, 4,1},
	{PANEL_X+ 80, PANEL_Y+ 0,CTYPE_WD, 5,1},{PANEL_X+ 96, PANEL_Y+ 0,CTYPE_WD, 6,1},{PANEL_X+112, PANEL_Y+ 0,CTYPE_WD, 7,1},
	{PANEL_X+128, PANEL_Y+ 0,CTYPE_WD, 8,1},{PANEL_X+144, PANEL_Y+ 0,CTYPE_WD, 9,1},
	{PANEL_X+160, PANEL_Y+ 0,CTYPE_WD,10,1},{PANEL_X+176, PANEL_Y+ 0,CTYPE_WD,11,1},{PANEL_X+192, PANEL_Y+ 0,CTYPE_WD,12,1},

	{PANEL_X+  0, PANEL_Y+PANEL_H,CTYPE_WD, 0,2},{PANEL_X+ 16, PANEL_Y+PANEL_H,CTYPE_WD, 1,2},{PANEL_X+ 32, PANEL_Y+PANEL_H,CTYPE_WD, 2,2},
	{PANEL_X+ 48, PANEL_Y+PANEL_H,CTYPE_WD, 3,2},{PANEL_X+ 64, PANEL_Y+PANEL_H,CTYPE_WD, 4,2},
	{PANEL_X+ 80, PANEL_Y+PANEL_H,CTYPE_WD, 5,2},{PANEL_X+ 96, PANEL_Y+PANEL_H,CTYPE_WD, 6,2},{PANEL_X+112, PANEL_Y+PANEL_H,CTYPE_WD, 7,2},
	{PANEL_X+128, PANEL_Y+PANEL_H,CTYPE_WD, 8,2},{PANEL_X+144, PANEL_Y+PANEL_H,CTYPE_WD, 9,2},
	{PANEL_X+160, PANEL_Y+PANEL_H,CTYPE_WD,10,2},{PANEL_X+176, PANEL_Y+PANEL_H,CTYPE_WD,11,2},{PANEL_X+192, PANEL_Y+PANEL_H,CTYPE_WD,12,2},

	{PANEL_X+  0, PANEL_Y+PANEL_H*2,CTYPE_WD, 0,3},{PANEL_X+ 16, PANEL_Y+PANEL_H*2,CTYPE_WD, 1,3},{PANEL_X+ 32, PANEL_Y+PANEL_H*2,CTYPE_WD, 2,3},
	{PANEL_X+ 48, PANEL_Y+PANEL_H*2,CTYPE_WD, 3,3},{PANEL_X+ 64, PANEL_Y+PANEL_H*2,CTYPE_WD, 4,3},
	{PANEL_X+ 80, PANEL_Y+PANEL_H*2,CTYPE_WD, 5,3},{PANEL_X+ 96, PANEL_Y+PANEL_H*2,CTYPE_WD, 6,3},{PANEL_X+112, PANEL_Y+PANEL_H*2,CTYPE_WD, 7,3},
	{PANEL_X+128, PANEL_Y+PANEL_H*2,CTYPE_WD, 8,3},{PANEL_X+144, PANEL_Y+PANEL_H*2,CTYPE_WD, 9,3},
	{PANEL_X+160, PANEL_Y+PANEL_H*2,CTYPE_WD,10,3},{PANEL_X+176, PANEL_Y+PANEL_H*2,CTYPE_WD,11,3},{PANEL_X+192, PANEL_Y+PANEL_H*2,CTYPE_WD,12,3},

	{PANEL_X+  0, PANEL_Y+PANEL_H*3,CTYPE_WD, 0,4},{PANEL_X+ 16, PANEL_Y+PANEL_H*3,CTYPE_WD, 1,4},{PANEL_X+ 32, PANEL_Y+PANEL_H*3,CTYPE_WD, 2,4},
	{PANEL_X+ 48, PANEL_Y+PANEL_H*3,CTYPE_WD, 3,4},{PANEL_X+ 64, PANEL_Y+PANEL_H*3,CTYPE_WD, 4,4},
	{PANEL_X+ 80, PANEL_Y+PANEL_H*3,CTYPE_WD, 5,4},{PANEL_X+ 96, PANEL_Y+PANEL_H*3,CTYPE_WD, 6,4},{PANEL_X+112, PANEL_Y+PANEL_H*3,CTYPE_WD, 7,4},
	{PANEL_X+128, PANEL_Y+PANEL_H*3,CTYPE_WD, 8,4},{PANEL_X+144, PANEL_Y+PANEL_H*3,CTYPE_WD, 9,4},
	{PANEL_X+160, PANEL_Y+PANEL_H*3,CTYPE_WD,10,4},{PANEL_X+176, PANEL_Y+PANEL_H*3,CTYPE_WD,11,4},{PANEL_X+192, PANEL_Y+PANEL_H*3,CTYPE_WD,12,4},

	{PANEL_X+  0, PANEL_Y+PANEL_H*4,CTYPE_WD, 0,5},{PANEL_X+ 16, PANEL_Y+PANEL_H*4,CTYPE_WD, 1,5},{PANEL_X+ 32, PANEL_Y+PANEL_H*4,CTYPE_WD, 2,5},
	{PANEL_X+ 48, PANEL_Y+PANEL_H*4,CTYPE_WD, 3,5},{PANEL_X+ 64, PANEL_Y+PANEL_H*4,CTYPE_WD, 4,5},
	{PANEL_X+ 80, PANEL_Y+PANEL_H*4,CTYPE_WD, 5,5},{PANEL_X+ 96, PANEL_Y+PANEL_H*4,CTYPE_WD, 6,5},{PANEL_X+112, PANEL_Y+PANEL_H*4,CTYPE_WD, 7,5},
	{PANEL_X+128, PANEL_Y+PANEL_H*4,CTYPE_WD, 8,5},{PANEL_X+144, PANEL_Y+PANEL_H*4,CTYPE_WD, 9,5},
	{PANEL_X+160, PANEL_Y+PANEL_H*4,CTYPE_WD,10,5},{PANEL_X+176, PANEL_Y+PANEL_H*4,CTYPE_WD,11,5},{PANEL_X+192, PANEL_Y+PANEL_H*4,CTYPE_WD,12,5},
};

#define TP_DATATBL_MAX ( NELEMS( TouchPanelDataTable ) )

//------------------------------------------------------------------
/**
 * @brief   文字盤に対応したタッチ判定ルーチン
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL TouchPanelCheck( NAMEIN_WORK *wk )
{
	int	i,start=0;
	u8	x,y,start_x,start_y,size_x,size_y;

	// フレンドコード入力の時は文字盤切り替えボタンを無効にする
	if(wk->inputmode==NAMEIN_FRIENDCODE){
		start = 4;
	}

	if( sys.tp_trg ){

		//割り込みで値が変わらないように
		x = sys.tp_x;
		y = sys.tp_y;

		for(i=start;i<TP_DATATBL_MAX;i++){
			start_x = TouchPanelDataTable[i].x;
			start_y = TouchPanelDataTable[i].y;

			// ボタン幅を取得
			switch( TouchPanelDataTable[i].type ){

			case CTYPE_S1:
				size_x = 24-1;
				size_y = 22;
				break;
			case CTYPE_S2:
				size_x = 32;
				size_y = 22;
				break;
			case CTYPE_WD:
				size_x = 16;
				size_y = PANEL_H;
				break;
			}
			
			// 当たり判定
			if((x >= start_x)&&(y >= start_y)&&(x <= (start_x+size_x))&&(y <= (start_y+size_y))){
				wk->Cursor.x = TouchPanelDataTable[i].cx;
				wk->Cursor.y = TouchPanelDataTable[i].cy;
				return TRUE;
			}
		}
	}
	return FALSE;
}

#ifdef DEBUG_OAM_POSPRINT
//------------------------------------------------------------------
/**
 * @brief   座標確認用ＯＡＭの表示
 *
 * @param   none		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static testclact_set( void )
{
	VecFx32 tmpVex;
	int start_x,start_y,size_x,size_y;

	switch( TouchPanelDataTable[testclact_no].type ){

	case CTYPE_S1:
		size_x = 24-1;
		size_y = 22;
		break;
	case CTYPE_S2:
		size_x = 32;
		size_y = 22;
		break;
	case CTYPE_WD:
		size_x = 16;
		size_y = PANEL_H;
		break;
	}


	tmpVex.x = FX32_ONE*(TouchPanelDataTable[testclact_no].x);
	tmpVex.y = FX32_ONE*(TouchPanelDataTable[testclact_no].y);
	CLACT_SetMatrix(testclact[0], &tmpVex);

	tmpVex.x = FX32_ONE*(TouchPanelDataTable[testclact_no].x+size_x);
	tmpVex.y = FX32_ONE*TouchPanelDataTable[testclact_no].y;
	CLACT_SetMatrix(testclact[1], &tmpVex);

	tmpVex.x = FX32_ONE*TouchPanelDataTable[testclact_no].x;
	tmpVex.y = FX32_ONE*(TouchPanelDataTable[testclact_no].y+size_y);
	CLACT_SetMatrix(testclact[2], &tmpVex);

	tmpVex.x = FX32_ONE*(TouchPanelDataTable[testclact_no].x+size_x);
	tmpVex.y = FX32_ONE*(TouchPanelDataTable[testclact_no].y+size_y);
	CLACT_SetMatrix(testclact[3], &tmpVex);


}
#endif



#endif

