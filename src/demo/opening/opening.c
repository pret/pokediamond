//==============================================================================================
/**
 * @file	opneing.c
 * @brief	オープニング
 * @author	Satoshi Nohara
 * @date	2005.12.08
 */
//==============================================================================================
#include "system/main.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/brightness.h"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/snd_tool.h"
#include "system/savedata.h"
#include "system/pmfprint.h"

#include "field/game_init.h"
#include "msgdata\msg.naix"							//NARC_msg_??_dat
#include "msgdata\msg_opening.h"					//msg_??

#include "opening.naix"
#include "opening_sys.h"
#include "opening_obj.h"
#include "opening_bmp.h"

#include "application/namein.h"						//NameInProcData

#include "gflib/strbuf_family.h"

#include "field/union_beacon_tool.h"				//UnionView_GetTrainerType


//==============================================================================================
//
//	デバック
//
//==============================================================================================


//==============================================================================================
//
//	extern宣言
//
//==============================================================================================


//==============================================================================================
//
//	定義
//
//==============================================================================================
//シーケンス定義
enum {
	SEQ_WELCOME_PM_WORLD,				//オーキド博士「ようこそ！」
	SEQ_KEY_GUIDE,						//操作説明
	SEQ_GAME_GUIDE,						//ゲーム説明
	SEQ_SEX_CHOICE,						//性別選択
	SEQ_NAME_INPUT,						//名前入力
	SEQ_RIVAL_NAME,						//ライバル名前入力
	SEQ_ID_CHOICE,						//ID選択
	SEQ_TO_ADVENTURE,					//冒険へ
	SEQ_EXIT,
};

#define OPENING_FADE_SYNC		(8)		//フェードsync数

#define OPENING_MSG_BUF_SIZE	(800)//(1024)	//メッセージサイズ
#define OPENING_MENU_BUF_SIZE	(64)	//メニューサイズ

//メッセージ表示位置
enum{
	OP_OOKIDO_X		= 0, 
	OP_OOKIDO_Y		= 0,
	OP_KEY_GUIDE_X	= 60, 
	OP_KEY_GUIDE_Y	= 8,
	OP_GAME_GUIDE_X = 8, 
	OP_GAME_GUIDE_Y = 48,
};

//オーキドOBJスクロール
#define OP_OOKIDO_SCR_SPD		(2)		//スクロールスピード
#define OP_OOKIDO_SCR_END		(140 * FX32_ONE)
//#define OP_OOKIDO_SCR_END_2		(90 * FX32_ONE)
#define OP_OOKIDO_SCR_END_2		(86 * FX32_ONE)	//opening_obj.cのデータと合わせる

//主人公BGスクロール
#define OP_HERO_SCR_START		(-140)//(-120)	//スクロール終了
#define OP_HERO_SCR_SPD			(4)		//スクロールインスピード
#define OP_HERO_SCR_SPD2		(2)		//スクロール中心スピード
#define OP_HERO_SCR_END			(-70)	//スクロール終了

#define AFF_SCALE_END			(0x700)	//(0x200)	//縮小値

//名前入力モード
enum{
	OP_NAMEIN_MODE_HERO = 0,
	OP_NAMEIN_MODE_RIVAL,
};

//パレット本数
#define OP_DEMO_PAL				(4)		

//カーソルを動かすまでのウェイト
#define OP_YESNO_WAIT			(3)


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================

static void SetVramBank(void);
static void SetBgHeader( GF_BGL_INI * ini );
static void SetBgGraphic_Sub2( OPENING_WORK * wk, u32 frm  );
static void SetBgGraphic_Sub4( OPENING_WORK * wk, u32 frm  );
static void SetBgGraphic_Sub5( OPENING_WORK * wk, u32 frm  );
static void SetBgGraphic_Sub6( OPENING_WORK * wk, u32 frm, int no );
static void SetBgGraphic_Sub7( OPENING_WORK * wk, u32 frm );
static void SetBgGraphic_Sub8( OPENING_WORK * wk, u32 frm );
static void SetBgGraphic_Sub9( OPENING_WORK * wk, u32 frm );
static void BgExit( GF_BGL_INI * ini );

static void SetPalette_Sub2(void);
static void SetPalette_Sub4(void);
static void SetPalette_Sub5(void);
static void SetPalette_Sub6(void);
static void SetPalette_Sub7(void);

static void VBlankFunc( void * work );
static int KeyCheck( int trg );
static void NextSeq( OPENING_WORK* wk, int* seq, int next );

static void OpeningAff( OPENING_WORK *wk );
static void OpeningAffReset(void);

//シーケンス
static BOOL Seq_WelcomePMWorld( OPENING_WORK* wk );
static BOOL Seq_KeyGuide( OPENING_WORK* wk );
static BOOL Seq_GameGuide( OPENING_WORK* wk );
static BOOL Seq_SexChoice( OPENING_WORK* wk );
static BOOL Seq_NameIn( OPENING_WORK* wk );
static BOOL Seq_RivalNameIn( OPENING_WORK* wk );
static BOOL Seq_IdChoice( OPENING_WORK* wk );
static BOOL Seq_ToAdventure( OPENING_WORK* wk );

//名前入力
static void OpeningNameInCall( OPENING_WORK* wk, u32 mode );
static void OpeningNameInMainTCB( TCB_PTR tcb, void* work );
static void OpeningRecover( OPENING_WORK* wk, u32 mode );

//共通初期化、終了
static void opening_init_sub();
static void opening_init_sub2( OPENING_WORK* wk );
static void opening_end_sub( OPENING_WORK* wk );

static void opening_talk_win_put( OPENING_WORK* wk );
static void opening_hero_fade_in( OPENING_WORK* wk );
static void opening_hero_fade_out( OPENING_WORK* wk );


//==============================================================================================
//
//	関数
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	プロセス関数：初期化
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	"処理状況"
 */
//--------------------------------------------------------------
PROC_RESULT OpeningProc_Init( PROC * proc, int * seq )
{
	int i;
	OPENING_WORK * wk;

	//PLAYER_BGMでタイトル、オープニングを鳴らすようにする
	Snd_DataSetByScene( SND_SCENE_OPENING, SEQ_OPENING, 1 );	//オープニング曲再生

	opening_init_sub();

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_OPENING, 0x20000 );

	wk = PROC_AllocWork( proc, sizeof(OPENING_WORK), HEAPID_OPENING );
	memset( wk, 0, sizeof(OPENING_WORK) );
	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_OPENING );

	opening_init_sub2(wk);

	//男女主人公BGは消しておく
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );

	(*seq) = SEQ_WELCOME_PM_WORLD;

	wk->proc	= proc;
	wk->sv		= ((MAINWORK *)PROC_GetParentWork(wk->proc))->savedata;
	wk->config	= SaveData_GetConfig( wk->sv );	//コンフィグポインタを取得

	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
/**
 * @brief	プロセス関数：メイン
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	"処理状況"
 */
//--------------------------------------------------------------
PROC_RESULT OpeningProc_Main( PROC * proc, int * seq )
{
	OPENING_WORK * wk  = PROC_GetWork( proc );

	//名前入力監視
	if( wk->tcb != NULL ){
		return PROC_RES_CONTINUE;
	}

	switch( *seq ){

	//オーキド博士「ようこそ！」
	case SEQ_WELCOME_PM_WORLD:
		if( Seq_WelcomePMWorld(wk) == TRUE ){
			NextSeq( wk, seq, wk->ret_work );
			wk->ret_work = 0;	//クリア
		}
		break;

	//操作説明
	case SEQ_KEY_GUIDE:
		if( Seq_KeyGuide(wk) == TRUE ){
			NextSeq( wk, seq, SEQ_WELCOME_PM_WORLD );
		}
		break;

	//ゲーム説明
	case SEQ_GAME_GUIDE:				
		if( Seq_GameGuide(wk) == TRUE ){
			NextSeq( wk, seq, SEQ_WELCOME_PM_WORLD );
		}
		break;

	//性別選択
	case SEQ_SEX_CHOICE:		
		if( Seq_SexChoice(wk) == TRUE ){
			NextSeq( wk, seq, SEQ_NAME_INPUT );
		}
		break;

	//名前入力
	case SEQ_NAME_INPUT:			
		if( Seq_NameIn(wk) == TRUE ){
			NextSeq( wk, seq, wk->ret_work );
			wk->ret_work = 0;	//クリア
		}
		break;

	//ライバル名前入力
	case SEQ_RIVAL_NAME:			
		if( Seq_RivalNameIn(wk) == TRUE ){
			NextSeq( wk, seq, wk->ret_work );
			wk->ret_work = 0;	//クリア
		}
		break;

	//ID選択
	case SEQ_ID_CHOICE:			
		if( Seq_IdChoice(wk) == TRUE ){
			NextSeq( wk, seq, SEQ_TO_ADVENTURE );
		}
		break;

	//冒険へ
	case SEQ_TO_ADVENTURE:		
		if( Seq_ToAdventure(wk) == TRUE ){
			NextSeq( wk, seq, SEQ_EXIT );
		}
		break;

	case SEQ_EXIT:
		//if( IsFinishedBrightnessChg( MASK_DOUBLE_DISPLAY ) == TRUE ){
		//if( WIPE_SYS_EndCheck() == TRUE ){
			return PROC_RES_FINISH;
		//}
		break;
	}

	CLACT_Draw( wk->ObjWork.ClactSet );			//セルアクター常駐関数

	return PROC_RES_CONTINUE;
}

//--------------------------------------------------------------
/**
 * @brief	プロセス関数：終了
 *
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 *
 * @return	"処理状況"
 */
//--------------------------------------------------------------
PROC_RESULT OpeningProc_End( PROC * proc, int * seq )
{
	int i;
	OPENING_WORK * wk = PROC_GetWork( proc );

	opening_end_sub( wk );

	PROC_FreeWork( proc );					//ワーク開放

	sys_VBlankFuncChange( NULL, NULL );		//VBlankセット
	sys_DeleteHeap( HEAPID_OPENING );

	Main_SetNextProc(NO_OVERLAY_ID, &FirstGameProcData);
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
/**
 * @brief	VRAM設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetVramBank(void)
{
	GF_BGL_DISPVRAM tbl = {
		//GX_VRAM_BG_64_E,				//メイン2DエンジンのBG
		GX_VRAM_BG_128_A,				//メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			//メイン2DエンジンのBG拡張パレット

		GX_VRAM_SUB_BG_128_C,			//サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		//サブ2DエンジンのBG拡張パレット

		GX_VRAM_OBJ_128_B,				//メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		//メイン2DエンジンのOBJ拡張パレット

		GX_VRAM_SUB_OBJ_16_I,			//サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	//サブ2DエンジンのOBJ拡張パレット

		GX_VRAM_TEX_NONE,				//テクスチャイメージスロット
		GX_VRAM_TEXPLTT_NONE			//テクスチャパレットスロット
	};
	GF_Disp_SetBank( &tbl );
}

//--------------------------------------------------------------
/**
 * @brief	BG設定
 *
 * @param	init	BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgHeader( GF_BGL_INI * ini )
{
	{	//BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_1, GX_BGMODE_1, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	{	//オーキド
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
	}

	{	//BG(フォント)
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, OP_FRM_FONT, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, OP_FRM_FONT );
	}

	{	//上画面背景
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

	{	//男女主人公(256色、拡大縮小)
		GF_BGL_BGCNT_HEADER AffineBgCntDat = {
			0, 0, 0x400, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_256,
			GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &AffineBgCntDat, GF_BGL_MODE_AFFINE );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME3_M );
	}

	{	//下画面背景
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_S );
	}
}

//--------------------------------------------------------------
/**
 * @brief	グラフィックデータセット：男女主人公
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub2( OPENING_WORK * wk, u32 frm  )
{
	u8 sex;

	//256色、拡大縮小
	SetPalette_Sub2();

//	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_character_NCGR, 
//						wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, HEAPID_OPENING );

	sex=(wk->sex == PM_MALE) ? NARC_opening_op_character01_NSCR : NARC_opening_op_character02_NSCR;
	ArcUtil_ScrnSet( ARC_OPENING_GRA, sex, wk->bgl, GF_BGL_FRAME3_M, 0, 0, 0, HEAPID_OPENING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	グラフィックデータセット：上画面背景
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub4( OPENING_WORK * wk, u32 frm  )
{
	SetPalette_Sub4();

	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_demo_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	ArcUtil_ScrnSet( ARC_OPENING_GRA, NARC_opening_op_demo01_NSCR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	グラフィックデータセット：下画面背景
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub5( OPENING_WORK * wk, u32 frm  )
{
	SetPalette_Sub5();

	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_demo_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );
	ArcUtil_ScrnSet( ARC_OPENING_GRA, NARC_opening_op_demo02_NSCR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	グラフィックデータセット：上画面操作説明
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub6( OPENING_WORK * wk, u32 frm, int no )
{
	int scrn;

	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_tutorial_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	switch( no ){
	case 0:
	case 3:
		scrn = NARC_opening_op_tutorial0_NSCR;
		break;
	case 1:
		scrn = NARC_opening_op_tutorial1_NSCR;
		break;
	case 2:
		scrn = NARC_opening_op_tutorial2_NSCR;
		break;
	};

	ArcUtil_ScrnSet( ARC_OPENING_GRA, scrn,	wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	グラフィックデータセット：下画面操作説明
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub7( OPENING_WORK * wk, u32 frm )
{
	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_tutorial_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	ArcUtil_ScrnSet( ARC_OPENING_GRA, NARC_opening_op_tutorial3_NSCR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	グラフィックデータセット：上画面ゲーム説明
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub8( OPENING_WORK * wk, u32 frm )
{
	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_tutorial_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	ArcUtil_ScrnSet( ARC_OPENING_GRA, NARC_opening_op_tutorial4_NSCR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	グラフィックデータセット：下画面ゲーム説明
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetBgGraphic_Sub9( OPENING_WORK * wk, u32 frm )
{
	ArcUtil_BgCharSet( ARC_OPENING_GRA, NARC_opening_op_tutorial_NCGR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	ArcUtil_ScrnSet( ARC_OPENING_GRA, NARC_opening_op_tutorial5_NSCR, 
						wk->bgl, frm, 0, 0, 0, HEAPID_OPENING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BG解放
 *
 * @param	ini		BGLデータ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void BgExit( GF_BGL_INI * ini )
{
	//メイン画面の各面の表示コントロール(表示OFF)
	GF_Disp_GX_VisibleControl(	GX_PLANEMASK_BG0 | 
								GX_PLANEMASK_BG1 | 
								GX_PLANEMASK_BG2 |
								GX_PLANEMASK_BG3 | 
								GX_PLANEMASK_OBJ, 
								VISIBLE_OFF );

	//サブ画面の各面の表示コントロール(表示OFF)
	GF_Disp_GXS_VisibleControl(	GX_PLANEMASK_BG0 | 
								GX_PLANEMASK_BG1 | 
								GX_PLANEMASK_OBJ, 
								VISIBLE_OFF );

	//GF_BGL_BGControlSetで取得したメモリを開放
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );
	GF_BGL_BGControlExit( ini, OP_FRM_FONT );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_S );

	sys_FreeMemoryEz( ini );
}

//--------------------------------------------------------------
/**
 * @brief	男女主人公パレット設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetPalette_Sub2(void)
{
	void *buf;
	NNSG2dPaletteData *dat;

	if( PM_VERSION == VERSION_DIAMOND ){
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_d_NCLR, &dat,HEAPID_OPENING);
	}else{
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_p_NCLR, &dat,HEAPID_OPENING);
	}

	{
		u16 * adr;
		adr = dat->pRawData;

		DC_FlushRange( dat->pRawData, (16*2)*4 );
		//転送するパレットアドレス、セットするパレットRAMオフセット、転送サイズ
		GX_LoadBGPltt( dat->pRawData, 0, (16*2)*4 );			//メイン
		sys_FreeMemoryEz(buf);
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	上画面背景パレット設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetPalette_Sub4(void)
{
	void *buf;
	NNSG2dPaletteData *dat;

	//バージョンでパレット変更
	if( PM_VERSION == VERSION_DIAMOND ){
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_d_NCLR, &dat,HEAPID_OPENING);
	}else{
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_p_NCLR, &dat,HEAPID_OPENING);
	}
		
	DC_FlushRange( dat->pRawData, (16*2) );
	GX_LoadBGPltt( dat->pRawData, 0, (16*2) );		//メイン
	sys_FreeMemoryEz(buf);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	下画面背景パレット設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetPalette_Sub5(void)
{
	void *buf;
	NNSG2dPaletteData *dat;

	if( PM_VERSION == VERSION_DIAMOND ){
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_d_NCLR, &dat,HEAPID_OPENING);
	}else{
		buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_demo_p_NCLR, &dat,HEAPID_OPENING);
	}
		
	DC_FlushRange( dat->pRawData, (16*2) );
	GXS_LoadBGPltt( dat->pRawData, 0, (16*2) );		//サブ
	sys_FreeMemoryEz(buf);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	上画面操作説明パレット設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetPalette_Sub6(void)
{
	void *buf;
	NNSG2dPaletteData *dat;

	buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_tutorial_NCLR, &dat,HEAPID_OPENING);
		
	DC_FlushRange( dat->pRawData, (16*2) );
	GX_LoadBGPltt( dat->pRawData, 0, (16*2*2) );		//メイン
	sys_FreeMemoryEz(buf);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	下画面操作説明パレット設定
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void SetPalette_Sub7(void)
{
	void *buf;
	NNSG2dPaletteData *dat;

	buf = ArcUtil_PalDataGet(ARC_OPENING_GRA, NARC_opening_op_tutorial_NCLR, &dat,HEAPID_OPENING);
		
	DC_FlushRange( dat->pRawData, (16*2) );
	GXS_LoadBGPltt( dat->pRawData, 0, (16*2*2) );		//サブ
	sys_FreeMemoryEz(buf);

	return;
}

//--------------------------------------------------------------
/**
 * @brief	VBlank関数
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void VBlankFunc( void * work )
{
	OPENING_WORK* wk = work;

	//パレット転送
	if( wk->pfd != NULL ){
		PaletteFadeTrans( wk->pfd );
	}

	//セルアクター
	//Vram転送マネージャー実行
	DoVramTransferManager();

	//レンダラ共有OAMマネージャVram転送
	REND_OAMTrans();	
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}

//--------------------------------------------------------------
/**
 * @brief	キーチェック
 *
 * @param	キー
 *
 * @return	none
 */
//--------------------------------------------------------------
static int KeyCheck( int trg )
{
	return (sys.trg & trg);
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス変更
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void NextSeq( OPENING_WORK* wk, int* seq, int next )
{
	wk->count	= 0;
	wk->sub_seq = 0;
	*seq		= next;
	return;
}

static const fx32 aff_speed[] =
{
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 6),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 5),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
	2 << (FX32_SHIFT - 4),
};

//--------------------------------------------------------------
/**
 * @brief	縮小
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void OpeningAff( OPENING_WORK *wk )
{
	MtxFx22 mtx;
    fx32 rScale_x,rScale_y;

	//元の大きさ
	//wk->ScaleX = 1 << FX32_SHIFT;
	//wk->ScaleY = 1 << FX32_SHIFT;
	
	//拡大
	//wk->ScaleX += 2 << (FX32_SHIFT - 6);
	//wk->ScaleY += 2 << (FX32_SHIFT - 6);
	
	//縮小
#if 1
	//スムーズに縮小
	wk->ScaleX -= 1 << (FX32_SHIFT - 6);
	wk->ScaleY -= 1 << (FX32_SHIFT - 6);
	//wk->ScaleX -= 2 << (FX32_SHIFT - 6);	//早くなる
	//wk->ScaleY -= 2 << (FX32_SHIFT - 6);
	//wk->ScaleX -= 1 << (FX32_SHIFT - 2);	//早くなる
	//wk->ScaleY -= 1 << (FX32_SHIFT - 2);
	//wk->ScaleX -= 1 << (FX32_SHIFT - 8);	//遅くなる
	//wk->ScaleY -= 1 << (FX32_SHIFT - 8);
#else
	//段階的に縮小
	//wk->ScaleX -= aff_speed[wk->count];
	//wk->ScaleY -= aff_speed[wk->count];
	wk->ScaleX -= aff_speed[wk->count/10];
	wk->ScaleY -= aff_speed[wk->count/10];
#endif

	rScale_x = FX_Inv(wk->ScaleX);
	rScale_y = FX_Inv(wk->ScaleY);
    mtx._00 = rScale_x;
    mtx._01 = 0;
    mtx._10 = 0;
    mtx._11 = rScale_y;

    SVC_WaitVBlankIntr();			//Waiting the end of VBlank interrup
	//G2S_SetBG3Affine( &mtx,		//a matrix for rotation and scaling
	G2_SetBG3Affine( &mtx,			//a matrix for rotation and scaling
						128, 96,	//the center of rotation
						0, 0);		//the reference point before rotation and scaling applied

	//OS_Printf( "scalex = %d\n", wk->ScaleX );
	//OS_Printf( "scaley = %d\n", wk->ScaleY );
	return ;
}

//--------------------------------------------------------------
/**
 * @brief	拡大縮小リセット
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void OpeningAffReset(void)
{
	MtxFx22 mtx;
    fx32 rScale_x,rScale_y;
	
	rScale_x = FX_Inv((1 << FX32_SHIFT));
	rScale_y = FX_Inv((1 << FX32_SHIFT));

    mtx._00 = rScale_x;
    mtx._01 = 0;
    mtx._10 = 0;
    mtx._11 = rScale_y;

    SVC_WaitVBlankIntr();			//Waiting the end of VBlank interrup
	G2_SetBG3Affine( &mtx,			//a matrix for rotation and scaling
						128, 96,	//the center of rotation
						0, 0 );		//the reference point before rotation and scaling applied
	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス：オーキド博士「ようこそ！」
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	"TRUE = 次へ、FALSE = 継続"
 */
//--------------------------------------------------------------
static BOOL Seq_WelcomePMWorld( OPENING_WORK* wk )
{
	u16 msg_id;
	u32 ret;
	VecFx32 vec;

	switch( wk->sub_seq ){

	//オーキドデータセット
	case 0:
		//初期座標に戻す
		OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_HAKASE );	//オーキド
		OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_RIVAL );		//ライバル
		OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_KAGE );		//影

		//上画面背景
		SetBgGraphic_Sub4( wk, GF_BGL_FRAME2_M );
	
		//下画面背景
		SetBgGraphic_Sub5( wk, GF_BGL_FRAME2_S );

		OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//オーキド
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//ライバル
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//影

		wk->sub_seq++;
		break;

	//ブラックイン
	case 1:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );
					//WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC*3, HEAPID_OPENING );

		wk->count = 15;
		wk->sub_seq++;
		break;
		
	//フェード終了待ち
	case 2:
		if( WIPE_SYS_EndCheck() == TRUE ){

			wk->count--;
			if( wk->count == 0 ){

				//会話ウィンドウ表示
				opening_talk_win_put( wk );

				//会話ウィンドウにオーキドメッセージをセット
				//「よくきてくれたね！」
				msg_id = (wk->cancel == 0) ? msg_opening_01 : msg_opening_20;
				//msg_id = (wk->cancel == 0) ? msg_opening_07 : msg_opening_07;
				wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );
				GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
				wk->cancel = 0;
				wk->sub_seq++;
			}
		}
		break;

	//オーキドの説明
	case 3:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}
		wk->sub_seq++;
		break;

	case 4:
		vec = OpeningClactMove( &wk->ObjWork, OP_OBJ_HAKASE, OP_OOKIDO_SCR_SPD );	//オーキド
		OpeningClactMove( &wk->ObjWork, OP_OBJ_KAGE, OP_OOKIDO_SCR_SPD );			//影
		//OS_Printf( "vec.x = %d\n", vec.x );

		//スクロール終了チェック
		if( vec.x >= OP_OOKIDO_SCR_END ){
			//OS_Printf( "終了vec.x = %d\n", vec.x );
			wk->sub_seq++;
		}
		break;

	case 5:
		//メニューウィンドウ
		OpeningWriteMenuWin( wk->bgl, &wk->bmpwin[BMPWIN_MENU_1] );
		
		OpeningInitMenu( wk, &wk->bmpwin[BMPWIN_MENU_1], 3 );
		OpeningSetMenuData( wk, 0, SEQ_SEX_CHOICE, msg_opening_09 );
		OpeningSetMenuData( wk, 1, SEQ_KEY_GUIDE, msg_opening_07 );
		OpeningSetMenuData( wk, 2, SEQ_GAME_GUIDE, msg_opening_08 );
		wk->mw = BmpMenuAddEx( &wk->MenuH, 8, 0, 0, HEAPID_OPENING, PAD_BUTTON_B );
		wk->count = OP_YESNO_WAIT;

		wk->sub_seq++;
		break;

	//選択待ち
	case 6:
		//ウェイト
		if( wk->count != 0 ){
			wk->count--;
			break;
		}

		wk->ret_work = BmpMenuMain( wk->mw );
		if( wk->ret_work == BMPMENU_CANCEL ){
			wk->ret_work = SEQ_SEX_CHOICE;
		}

		switch( wk->ret_work ){
		case BMPMENU_NULL:
			break;
		default:
			BmpMenuExit( wk->mw, NULL );
			BmpMenuWinClear( wk->MenuH.win, WINDOW_TRANS_ON );
			wk->sub_seq++;
			break;
		};
		break;

	//ブラックアウト
	case 7:
		//「だいじょうぶ」を選んだ時
		if( wk->ret_work == SEQ_SEX_CHOICE ){
			return TRUE;
		}

		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//フェード終了待ち
	case 8:
		if( WIPE_SYS_EndCheck() == TRUE ){
			return TRUE;
		}
		break;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス：操作説明
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	"TRUE = 次へ、FALSE = 継続"
 */
//--------------------------------------------------------------
static BOOL Seq_KeyGuide( OPENING_WORK* wk )
{
	switch( wk->sub_seq ){

	//操作説明データセット
	case 0:
		//会話ウィンドウを消す
		BmpTalkWinClear( &wk->bmpwin[BMPWIN_OOKIDO], WINDOW_TRANS_ON );

		OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//オーキド
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//ライバル
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//影

		SetPalette_Sub6();
		SetPalette_Sub7();

		SetBgGraphic_Sub6( wk, GF_BGL_FRAME2_M, 0 );
		SetBgGraphic_Sub7( wk, GF_BGL_FRAME2_S );

		//「いろいろな」
		OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_operation_01, 
							OP_KEY_GUIDE_X, OP_KEY_GUIDE_Y, MSG_NO_PUT,
							FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );
		wk->sub_seq++;
		break;

	//ブラックイン
	case 1:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//フェード終了待ち
	case 2:
		if( WIPE_SYS_EndCheck() == TRUE ){
			wk->sub_seq++;
		}
		break;

	//操作説明画面1
	case 3:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			SetBgGraphic_Sub6( wk, GF_BGL_FRAME2_M, 1 );

			//「じょうげさゆうに」
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_operation_02, 
							OP_KEY_GUIDE_X, OP_KEY_GUIDE_Y, MSG_NO_PUT, 
							FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//操作説明画面2
	case 4:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			SetBgGraphic_Sub6( wk, GF_BGL_FRAME2_M, 2 );

			//「メニューを」
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_operation_03, 
								OP_KEY_GUIDE_X, OP_KEY_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//操作説明画面3
	case 5:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			SetBgGraphic_Sub6( wk, GF_BGL_FRAME2_M, 3 );

			//「したのがめんは」
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_operation_04, 
								OP_KEY_GUIDE_X, OP_KEY_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_WHITE,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//操作説明画面4
	case 6:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){
			wk->sub_seq++;
		}
		break;

	//ブラックアウト
	case 7:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//フェード終了待ち
	case 8:
		if( WIPE_SYS_EndCheck() == TRUE ){
			GF_BGL_BmpWinOff( &wk->bmpwin[BMPWIN_GUIDE] );
			wk->cancel = 1;
			return TRUE;
		}
		break;
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス：ゲーム説明
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	"TRUE = 次へ、FALSE = 継続"
 */
//--------------------------------------------------------------
static BOOL Seq_GameGuide( OPENING_WORK* wk )
{
	switch( wk->sub_seq ){

	//ゲーム説明データセット
	case 0:
		//会話ウィンドウを消す
		BmpTalkWinClear( &wk->bmpwin[BMPWIN_OOKIDO], WINDOW_TRANS_ON );

		OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//オーキド
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//ライバル
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//影

		SetPalette_Sub6();
		SetPalette_Sub7();

		SetBgGraphic_Sub8( wk, GF_BGL_FRAME2_M );
		SetBgGraphic_Sub9( wk, GF_BGL_FRAME2_S );

		//「これからはじまる」
		OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_01, 
							OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
							FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

		wk->sub_seq++;
		break;

	//ブラックイン
	case 1:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//フェード終了待ち
	case 2:
		if( WIPE_SYS_EndCheck() == TRUE ){
			wk->sub_seq++;
		}
		break;

	//ゲーム説明画面1
	case 3:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			//「まちやみち」
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_02, 
								OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//ゲーム説明画面2
	case 4:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			//「そしてこまっている」
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_03, 
								OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//ゲーム説明画面3
	case 5:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			//「ときにしょうぶを」
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_04, 
								OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//ゲーム説明画面4
	case 6:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			//「ぼうけんを」
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_05, 
								OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//ゲーム説明画面5
	case 7:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){

			//「それが」
			OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_GUIDE], msg_guide_06, 
								OP_GAME_GUIDE_X, OP_GAME_GUIDE_Y, MSG_NO_PUT, 
								FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_NULL, FONT_SYSTEM );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_GUIDE] );

			wk->sub_seq++;
		}
		break;

	//ゲーム説明画面6
	case 8:
		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){
			wk->sub_seq++;
		}
		break;

	//ブラックアウト
	case 9:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//フェード終了待ち
	case 10:
		if( WIPE_SYS_EndCheck() == TRUE ){
			GF_BGL_BmpWinOff( &wk->bmpwin[BMPWIN_GUIDE] );
			wk->cancel = 1;
			return TRUE;
		}
		break;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス：性別選択
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	"TRUE = 次へ、FALSE = 継続"
 */
//--------------------------------------------------------------
static BOOL Seq_SexChoice( OPENING_WORK* wk )
{
	u16 col;
	u16 msg_id;
	VecFx32 vec;

	switch( wk->sub_seq ){

	//性別選択データセット
	case 0:
		wk->sex = PM_MALE;

		//男女主人公(256色、拡大縮小)
		SetBgGraphic_Sub2( wk, GF_BGL_FRAME3_M );

		//会話ウィンドウ表示
		//opening_talk_win_put( wk );
		//GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );

		//主人公スクロールイン開始位置セット
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, OP_HERO_SCR_START );

		wk->sub_seq++;
		break;

	case 1:
		vec = OpeningClactMove( &wk->ObjWork, OP_OBJ_HAKASE, -(OP_OOKIDO_SCR_SPD) );//オーキド
		OpeningClactMove( &wk->ObjWork, OP_OBJ_KAGE, -(OP_OOKIDO_SCR_SPD) );		//影

		//スクロール終了チェック
		if( vec.x <= OP_OOKIDO_SCR_END_2 ){
			//初期座標に戻す
			OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_HAKASE );	//オーキド
			OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_KAGE );		//影
			wk->sub_seq++;
		}
		break;

	//フェード終了待ち
	case 2:
		msg_id = (wk->cancel == 0) ? msg_opening_02 : msg_opening_18;
		//msg_id = (wk->cancel == 0) ? msg_opening_07 : msg_opening_07;
		wk->cancel = 0;

		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );
		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );

		wk->sub_seq++;
		break;

	//オーキドの説明
	case 3:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
		PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 8, 16, col );

		wk->count = 10;
		wk->sub_seq++;
		break;

	//オーキドパレットアウト待ち
	case 4:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//オーキド
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//ライバル
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//影

			wk->count--;
			if( wk->count == 0 ){
				//男女主人公BG表示
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
				wk->sub_seq++;
			}
		}
		break;

	//主人公スクロールイン
	case 5:
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_INC, OP_HERO_SCR_SPD );

		//スクロール値Ｘ取得
		if( GF_BGL_ScrollGetX(wk->bgl, GF_BGL_FRAME3_M) < OP_HERO_SCR_END ){
			break;
		}

		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, OP_HERO_SCR_END );

		//メニューウィンドウ
		OpeningWriteMenuWin( wk->bgl, &wk->bmpwin[BMPWIN_MENU_2] );
		
		OpeningInitMenu( wk, &wk->bmpwin[BMPWIN_MENU_2], 2 );
		OpeningSetMenuData( wk, 0, PM_MALE, msg_opening_10 );
		OpeningSetMenuData( wk, 1, PM_FEMALE, msg_opening_11 );
		wk->mw = BmpMenuAddEx( &wk->MenuH, 8, 0, 0, HEAPID_OPENING, PAD_BUTTON_B );
		wk->count = OP_YESNO_WAIT;

		wk->sub_seq++;
		break;

	//性別選択処理
	case 6:
		//ウェイト
		if( wk->count != 0 ){
			wk->count--;
			break;
		}

		wk->ret_work = BmpMenuMain( wk->mw );

		switch( wk->ret_work ){
		case BMPMENU_NULL:
		case BMPMENU_CANCEL:
			//男女主人公(256色、拡大縮小)
			if( sys.trg == PAD_KEY_UP ){
				wk->sex = PM_MALE;
			}else if( sys.trg == PAD_KEY_DOWN ){
				wk->sex = PM_FEMALE;
			}
			SetBgGraphic_Sub2( wk, GF_BGL_FRAME3_M );
			break;
		default:
			wk->sex = wk->ret_work;
			BmpMenuExit( wk->mw, NULL );
			BmpMenuWinClear( wk->MenuH.win, WINDOW_TRANS_ON );
			wk->sub_seq++;
			break;
		};
		break;

	//右へ消える
	case 7:
		//主人公スクロールアウト
		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_DEC, OP_HERO_SCR_SPD );

		//スクロール値Ｘ取得
		if( GF_BGL_ScrollGetX(wk->bgl, GF_BGL_FRAME3_M) > OP_HERO_SCR_START ){
			break;
		}

		GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, OP_HERO_SCR_START );

		//男女主人公BG非表示
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );

		wk->count = 10;
		wk->sub_seq++;
		break;

	//間
	case 8:
		wk->count--;
		if( wk->count == 0 ){

			//オーキドフェードイン
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//オーキド
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//ライバル
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//影

			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 16, 0, col );
			wk->sub_seq++;
		}
		break;

	//オーキド表示
	case 9:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			//会話ウィンドウ表示
			opening_talk_win_put( wk );

			wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_opening_03, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );
			GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
			wk->sub_seq++;
		}
		break;

	//メッセージ表示
	case 10:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){
			wk->sub_seq++;
		}
		break;

	//ブラックアウト
	case 11:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

		wk->sub_seq++;
		break;

	//フェード終了待ち
	case 12:
		if( WIPE_SYS_EndCheck() == TRUE ){
			//会話ウィンドウを消す
			BmpTalkWinClear( &wk->bmpwin[BMPWIN_OOKIDO], WINDOW_TRANS_ON );
			return TRUE;
		}
		break;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス：名前入力
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	"TRUE = 次へ、FALSE = 継続"
 */
//--------------------------------------------------------------
static BOOL Seq_NameIn( OPENING_WORK* wk )
{
	u16 msg_id,col;

	switch( wk->sub_seq ){

	case 0:
		wk->sub_seq++;
		break;

	case 1:
		wk->sub_seq++;
		break;

	//名前入力呼び出し
	case 2:
		wk->tcb = NULL;
		OpeningNameInCall( wk, OP_NAMEIN_MODE_HERO );
		wk->sub_seq++;
		break;

	//名前入力終了待ち
	case 3:
		//名前入力監視
		if( wk->tcb != NULL ){
			break;
		}

		//会話ウィンドウ表示
		opening_talk_win_put( wk );

		//「○くんだね？」
		msg_id = (wk->sex == PM_MALE) ? msg_opening_16 : msg_opening_17;
		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );

		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
		wk->sub_seq++;
		break;

	//性別選択処理
	case 4:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		//メニューウィンドウ
		OpeningWriteMenuWin( wk->bgl, &wk->bmpwin[BMPWIN_YESNO] );
		OpeningInitMenu( wk, &wk->bmpwin[BMPWIN_YESNO], 2 );
		OpeningSetMenuData( wk, 0, SEQ_RIVAL_NAME, msg_opening_14 );
		OpeningSetMenuData( wk, 1, SEQ_SEX_CHOICE, msg_opening_15 );
		wk->mw = BmpMenuAddEx( &wk->MenuH, 8, 0, 0, HEAPID_OPENING, PAD_BUTTON_B );
		wk->count = OP_YESNO_WAIT;
		wk->sub_seq++;
		break;

	case 5:
		//ウェイト
		if( wk->count != 0 ){
			wk->count--;
			break;
		}

		wk->ret_work = BmpMenuMain( wk->mw );
		if( wk->ret_work == BMPMENU_CANCEL ){
			wk->ret_work = SEQ_SEX_CHOICE;
		}

		switch( wk->ret_work ){
		case BMPMENU_NULL:
			break;
		default:
			BmpMenuExit( wk->mw, NULL );
			BmpMenuWinClear( wk->MenuH.win, WINDOW_TRANS_ON );
			wk->sub_seq++;
			break;
		};
		break;

	//主人公BGフェードアウト
	case 6:
		opening_hero_fade_out( wk );
		wk->sub_seq++;
		break;

	case 7:
		if( PaletteFadeCheck(wk->pfd) == 0 ){
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );		//男女主人公BG非表示
			GF_BGL_ScrollSet( wk->bgl, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, 0 );

			wk->count = 15;
			wk->sub_seq++;
		}
		break;

	case 8:
		wk->count--;
		if( wk->count == 0 ){
			//オーキドフェードイン
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//オーキド
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//ライバル
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//影
			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 16, 0, col );
			wk->sub_seq++;
		}
		break;

	case 9:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			if( wk->ret_work == SEQ_SEX_CHOICE ){
				OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//オーキド
				OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//ライバル
				OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//影
				wk->cancel = 1;
			}else{

				MyStatus_SetMyName( SaveData_GetMyStatus(wk->sv), wk->str );//主人公の名前セット
				MyStatus_SetMySex( SaveData_GetMyStatus(wk->sv), wk->sex );	//主人公の性別セット

				//「いいなまえだな」
				msg_id = msg_opening_04;
				wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );

				GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
			}

			wk->sub_seq++;
		}
		break;

	case 10:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		return TRUE;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス：ライバル名前入力
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	"TRUE = 次へ、FALSE = 継続"
 */
//--------------------------------------------------------------
static BOOL Seq_RivalNameIn( OPENING_WORK* wk )
{
	VecFx32 vec;
	u16 msg_id,col;

	switch( wk->sub_seq ){

	case 0:
		//会話ウィンドウ表示
		opening_talk_win_put( wk );

		//「かれの　なまえを　おしえてくれないか？」
		msg_id = (wk->cancel ==0) ? msg_opening_21 : msg_opening_22;

		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );

		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );

		wk->sub_seq++;
		break;

	case 1:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		wk->count = 15;
		wk->sub_seq++;
		break;

	case 2:
		wk->count--;
		if( wk->count == 0 ){
			//オーキドフェードアウト
			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 8, 16, col );
			wk->sub_seq++;
		}
		break;

#if 0
	//オーキドフェードアウト後に、ライバル横からスライドイン
	case 3:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//オーキド
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_OFF );	//ライバル
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//影

			OpeningClactPosSet( &wk->ObjWork, OP_OBJ_RIVAL, 200, 30 );			//座標変更

			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 16, 0, col );
			wk->sub_seq++;
		}
		break;

	case 4:
		vec = OpeningClactMove( &wk->ObjWork, OP_OBJ_RIVAL, -(OP_OOKIDO_SCR_SPD) );	//ライバル
		//OpeningClactMove( &wk->ObjWork, OP_OBJ_KAGE, -(OP_OOKIDO_SCR_SPD) );		//影

		//スクロール終了チェック
		if( vec.x <= OP_OOKIDO_SCR_END_2 ){
			//初期座標に戻す
			OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_RIVAL );		//ライバル
			//OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_KAGE );	//影
			wk->sub_seq++;
		}
		break;
#else
	//オーキドフェードアウト後に、ライバル真ん中からフェードイン
	case 3:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//オーキド
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_OFF );	//ライバル
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//影

			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 16, 0, col );

			wk->count = 45;
			wk->sub_seq++;
		}
		break;

	case 4:
		if( PaletteFadeCheck(wk->pfd) == 0 ){
			wk->count--;
			if( wk->count == 0 ){
				wk->sub_seq++;
			}
		}
		break;
#endif

	case 5:
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
					WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );
		wk->sub_seq++;
		break;

	//フェードアウト終了待ち
	case 6:
		if( WIPE_SYS_EndCheck() == TRUE ){
			wk->sub_seq++;
		}
		break;

	//名前入力呼び出し
	case 7:
		wk->tcb = NULL;
		OpeningNameInCall( wk, OP_NAMEIN_MODE_RIVAL );
		wk->sub_seq++;
		break;

	//名前入力終了待ち
	case 8:
		//名前入力監視
		if( wk->tcb != NULL ){
			break;
		}

		//会話ウィンドウ表示
		opening_talk_win_put( wk );

		//「○と　いうのか　それで　あっているかな？」
		msg_id = msg_opening_23;
		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );

		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
		wk->sub_seq++;
		break;

	//「はい・いいえ」選択処理
	case 9:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		//メニューウィンドウ
		OpeningWriteMenuWin( wk->bgl, &wk->bmpwin[BMPWIN_YESNO] );

		OpeningInitMenu( wk, &wk->bmpwin[BMPWIN_YESNO], 2 );
		OpeningSetMenuData( wk, 0, SEQ_ID_CHOICE, msg_opening_14 );
		OpeningSetMenuData( wk, 1, SEQ_RIVAL_NAME, msg_opening_15 );
		wk->mw = BmpMenuAddEx( &wk->MenuH, 8, 0, 0, HEAPID_OPENING, PAD_BUTTON_B );
		wk->count = OP_YESNO_WAIT;
		wk->sub_seq++;
		break;

	case 10:
		//ウェイト
		if( wk->count != 0 ){
			wk->count--;
			break;
		}

		wk->ret_work = BmpMenuMain( wk->mw );
		if( wk->ret_work == BMPMENU_CANCEL ){
			wk->ret_work = SEQ_RIVAL_NAME;
		}

		switch( wk->ret_work ){
		case BMPMENU_NULL:
			break;
		default:
			BmpMenuExit( wk->mw, NULL );
			BmpMenuWinClear( wk->MenuH.win, WINDOW_TRANS_ON );
			wk->sub_seq++;
			break;
		};
		break;

	case 11:
		//ライバルフェードアウト
		col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
		PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 8, 16, col );
		wk->sub_seq++;
		break;

	case 12:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			//オーキドフェードイン
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//オーキド
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//ライバル
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//影

			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 16, 0, col );

			wk->sub_seq++;
		}
		break;

	case 13:
		if( PaletteFadeCheck(wk->pfd) == 0 ){

			if( wk->ret_work == SEQ_RIVAL_NAME ){
				wk->cancel = 1;
			}else{

				{
					/*******************/
					//MyStatus_SetMyName( my, wk->str );	//ライバルの名前セット
					/*******************/
				}

			}

			return TRUE;
		}
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス：ID選択
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	"TRUE = 次へ、FALSE = 継続"
 */
//--------------------------------------------------------------
static BOOL Seq_IdChoice( OPENING_WORK* wk )
{
	u16 msg_id;

	switch( wk->sub_seq ){

	//データセットなど
	case 0:
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_OFF );	//オーキド
		//OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_OFF );	//ライバル
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_OFF );		//影

#if 0
		//会話ウィンドウ表示
		opening_talk_win_put( wk );
		
		msg_id = (wk->cancel == 0) ? msg_opening_04 : msg_opening_05;
		wk->cancel = 0;

		//WORDSET_RegisterPlayerName( wk->wordset, 0, 
		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_id, 
		//wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_opening_07, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );
		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );
#endif

		wk->sub_seq++;
		break;

	//ブラックイン
	case 1:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		{
			//---------------------------------------------------------------
			//IDをシャッフルして選ぶ処理がないので仮だが、IDをセットしておく
			//---------------------------------------------------------------
			
			//選択結果から決定したトレーナータイプの番号そのものを算出する
			int view = UnionView_GetTrainerType( 0x1234, wk->sex, 0 );

			//MYSTATUSに自分の「見た目」を格納する
			MyStatus_SetTrainerView( SaveData_GetMyStatus(wk->sv), view );
		}

		wk->sub_seq++;
		break;

	case 2:
		//if( IsFinishedBrightnessChg( MASK_DOUBLE_DISPLAY ) == TRUE ){
		if( WIPE_SYS_EndCheck() == TRUE ){
			wk->count = 0;
			wk->sub_seq++;
		}
		return TRUE;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス：冒険へ
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	"TRUE = 次へ、FALSE = 継続"
 */
//--------------------------------------------------------------
static BOOL Seq_ToAdventure( OPENING_WORK* wk )
{
	u16 col;

	switch( wk->sub_seq ){

	//データセットなど
	case 0:
		//会話ウィンドウ表示
		opening_talk_win_put( wk );
		
		WORDSET_RegisterPlayerName( wk->wordset, 0, SaveData_GetMyStatus(wk->sv) );//主人公名セット
		wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_opening_06, 
		//wk->msg_index = OpeningWriteMsg( wk, &wk->bmpwin[BMPWIN_OOKIDO], msg_opening_07, 
										OP_OOKIDO_X, OP_OOKIDO_Y, CONFIG_GetMsgPrintSpeed(wk->config), 
										FBMP_COL_BLACK,FBMP_COL_BLK_SDW,FBMP_COL_WHITE, FONT_TALK );
		GF_BGL_BmpWinOn( &wk->bmpwin[BMPWIN_OOKIDO] );

		wk->sub_seq++;
		break;

	//オーキド会話終了待ち
	case 1:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( wk->msg_index ) == 1 ){
			break;
		}

		if( KeyCheck(PAD_BUTTON_A | PAD_BUTTON_B) ){
			//会話ウィンドウを消す
			BmpTalkWinClear( &wk->bmpwin[BMPWIN_OOKIDO], WINDOW_TRANS_ON );

			OpeningOffBmpWin( wk->bmpwin );		//BMPウィンドウオフ

			col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;
			PaletteFadeReq( wk->pfd, PF_BIT_MAIN_OBJ, 0xffff, 0, 8, 16, col );
			//ChangeBrightnessRequest(OPENING_FADE_SYNC, BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 
			//					PLANEMASK_ALL, MASK_DOUBLE_DISPLAY);
			wk->sub_seq++;
		}
		break;

	//オーキドフェードアウト
	case 2:
		if( PaletteFadeCheck(wk->pfd) == 0 ){
		//if( IsFinishedBrightnessChg( MASK_DOUBLE_DISPLAY ) == TRUE ){

			OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//オーキド
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//ライバル
			OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//影

			wk->count = 15;
			wk->sub_seq++;
		}
		break;

	case 3:
		wk->count--;
		if( wk->count == 0 ){

			//男女主人公(256色、拡大縮小)
			SetBgGraphic_Sub2( wk, GF_BGL_FRAME3_M );
			//男女主人公BG非表示
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );

			wk->sub_seq++;
		}
		break;

	case 4:
		wk->count++;
		if( wk->count >= 10 ){
			wk->count = 0;
			wk->sub_seq++;
		}
		break;

	case 5:
#if 1
		OpeningAff( wk );
#else
		wk->count++;
		if( (wk->count % 10) == 0 ){
			OpeningAff( wk );
		}
#endif
		if( wk->ScaleX < AFF_SCALE_END ){ 
			return TRUE;
		}
		break;
	};

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	名前入力画面呼び出しTCB
 *
 * @param	tcb			TCBシステムワーク
 * @param	work		ワークエリアポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
typedef struct{
	int seq_no;
	u32 mode;
	OPENING_WORK* op_work;
	NAMEIN_PARAM* NameInParam;
	CONFIG*       config;
	PROC* proc;
}OPENING_NAMEIN_WORK;

static void OpeningNameInCall( OPENING_WORK* wk, u32 mode )
{
	OPENING_NAMEIN_WORK* name_wk;

	name_wk = sys_AllocMemory( HEAPID_OPENING, sizeof(OPENING_NAMEIN_WORK) );
	if( name_wk == NULL ){
		GF_ASSERT( (0) && "メモリ確保失敗！" );
		return;
	}
	memset( name_wk, 0, sizeof(OPENING_NAMEIN_WORK) );
	name_wk->op_work = wk; 
	name_wk->mode	 = mode; 
	name_wk->config  = wk->config;

	wk->tcb	= TCB_Add( OpeningNameInMainTCB, name_wk, 0 );
	return;
}

static void OpeningNameInMainTCB(TCB_PTR tcb,void *work)
{
	OPENING_NAMEIN_WORK* wk = (OPENING_NAMEIN_WORK *)work;

	switch( wk->seq_no ){

	//フェードアウト
	case 0:
		wk->seq_no++;
		break;

	//フェード終了待ち
	case 1:
		//削除処理
		opening_end_sub( wk->op_work );

		//名前入力用引数ワーク作成
		if( wk->mode == OP_NAMEIN_MODE_HERO ){
			wk->NameInParam = NameIn_ParamAllocMake( HEAPID_OPENING, NAMEIN_MYNAME, 
														0, NAMEIN_PERSON_LENGTH, NULL );
			wk->NameInParam->info = wk->op_work->sex;	//男女
		}else{
			wk->NameInParam = NameIn_ParamAllocMake( HEAPID_OPENING, NAMEIN_RIVALNAME,
														0, NAMEIN_PERSON_LENGTH, NULL );
			wk->NameInParam->info = PM_MALE;			//男
		}

		wk->proc = PROC_Create( &NameInProcData, wk->NameInParam, HEAPID_OPENING );

		wk->seq_no++;
		break;

	//名前入力画面終了待ち
	case 2:
		if( ProcMain(wk->proc) == TRUE ){

			STRBUF_GetStringCode( wk->NameInParam->strbuf, wk->op_work->str, 
										(PERSON_NAME_SIZE + EOM_SIZE) );

			//復帰処理
			PROC_Delete( wk->proc );

			//画面再構築
			OpeningRecover( wk->op_work, wk->mode );

			//wordsetを確保してから呼ぶ
			if( wk->mode == OP_NAMEIN_MODE_HERO ){
				WORDSET_RegisterWord( wk->op_work->wordset, 0, wk->NameInParam->strbuf, 
										wk->op_work->sex, TRUE, PM_LANG );
			}else{
				WORDSET_RegisterWord( wk->op_work->wordset, 1, wk->NameInParam->strbuf, 
										PM_MALE, TRUE, PM_LANG );
			}

			NameIn_ParamDelete( wk->NameInParam );				//名前入力ワークを解放
		
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, 
						WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_OPENING );

			wk->seq_no++;
		}
		break;

	//フェードイン終了待ち
	case 3:
		if( WIPE_SYS_EndCheck() == TRUE ){
			wk->op_work->tcb = NULL;
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	画面再構築
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void OpeningRecover( OPENING_WORK* wk, u32 mode )
{
	int i;

	opening_init_sub();
	
	wk->bgl = GF_BGL_BglIniAlloc( HEAPID_OPENING );

	opening_init_sub2( wk );

	//男女主人公BG表示
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );

	OpeningClactVanish( &wk->ObjWork, OP_OBJ_HAKASE, OP_VANISH_ON );	//オーキド
	OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_ON );		//ライバル
	OpeningClactVanish( &wk->ObjWork, OP_OBJ_KAGE, OP_VANISH_ON );		//影

	//初期座標に戻す
	OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_HAKASE );	//オーキド
	OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_RIVAL );		//ライバル
	OpeningClactMoveInit( &wk->ObjWork, OP_OBJ_KAGE );		//影

	//上画面背景
	SetBgGraphic_Sub4( wk, GF_BGL_FRAME2_M );
	
	//下画面背景
	SetBgGraphic_Sub5( wk, GF_BGL_FRAME2_S );

	//モードにより分岐
	if( mode == OP_NAMEIN_MODE_HERO ){
		//男女主人公(256色、拡大縮小)
		SetBgGraphic_Sub2( wk, GF_BGL_FRAME3_M );
	}else{
		OpeningClactVanish( &wk->ObjWork, OP_OBJ_RIVAL, OP_VANISH_OFF );	//ライバル

		//男女主人公BGは消しておく
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	共通初期化1
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_init_sub()
{
	WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
	WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
  
	sys_VBlankFuncChange( NULL, NULL );			//VBlankセット
	sys_HBlankIntrSet( NULL,NULL );				//HBlankセット
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );
	//sys_KeyRepeatSpeedSet( 4, 8 );
	return;	
}

//--------------------------------------------------------------
/**
 * @brief	共通初期化2
 *
 * @param	wk		OPENING_WORK型のポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_init_sub2( OPENING_WORK* wk )
{
	int i;

	SetVramBank();

	SetBgHeader( wk->bgl );

	OpeningInitCellActor( &wk->ObjWork );
	OpeningSetActor( &wk->ObjWork, OP_OBJ_HAKASE, OP_OBJ_HAKASE, 0 );
	OpeningSetActor( &wk->ObjWork, OP_OBJ_RIVAL, OP_OBJ_RIVAL, 0 );
	OpeningSetActor( &wk->ObjWork, OP_OBJ_KAGE, OP_OBJ_HAKASE, 1 );	

	//メッセージデータマネージャー作成
	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, 
								NARC_msg_opening_dat, HEAPID_OPENING );

	wk->wordset = WORDSET_Create( HEAPID_OPENING );
	wk->msg_buf = STRBUF_Create( OPENING_MSG_BUF_SIZE, HEAPID_OPENING );
	wk->tmp_buf = STRBUF_Create( OPENING_MSG_BUF_SIZE, HEAPID_OPENING );

	//文字列バッファ作成
	for( i=0; i < OPENING_MENU_MAX ;i++ ){
		wk->menu_buf[i] = STRBUF_Create( OPENING_MENU_BUF_SIZE, HEAPID_OPENING );
	}

	//フォントパレット
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, OP_FONT_PAL * 32, HEAPID_OPENING );
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, OP_MSGFONT_PAL * 32, HEAPID_OPENING );

	//ビットマップ追加
	OpeningAddBmpWin( wk->bgl, wk->bmpwin );

	//パレットフェードシステムワーク作成
	wk->pfd = PaletteFadeInit( HEAPID_OPENING );

	//リクエストデータをmallocしてセット
	PaletteFadeWorkAllocSet( wk->pfd, FADE_MAIN_OBJ, FADE_PAL_ALL_SIZE, HEAPID_OPENING );
	PaletteFadeWorkAllocSet( wk->pfd, FADE_MAIN_BG, FADE_PAL_ONE_SIZE*OP_DEMO_PAL, HEAPID_OPENING );

	//オーキド
	PaletteWorkSet_Arc(
			wk->pfd, ARC_OPENING_GRA, NARC_opening_op_hakase_NCLR,
			HEAPID_OPENING, FADE_MAIN_OBJ, 16*2*16, 0 );

	//ライバル
	PaletteWorkSet_Arc(
			wk->pfd, ARC_OPENING_GRA, NARC_opening_op_rival_NCLR,
			HEAPID_OPENING, FADE_MAIN_OBJ, 16*1*16, 16*2 );

	//主人公BG
	if( PM_VERSION == VERSION_DIAMOND ){
		PaletteWorkSet_Arc(
				wk->pfd, ARC_OPENING_GRA, NARC_opening_op_demo_d_NCLR,
				HEAPID_OPENING, FADE_MAIN_BG, (16*2)*OP_DEMO_PAL, 0 );
	}else{
		PaletteWorkSet_Arc(
				wk->pfd, ARC_OPENING_GRA, NARC_opening_op_demo_p_NCLR,
				HEAPID_OPENING, FADE_MAIN_BG, (16*2)*OP_DEMO_PAL, 0 );
	}

	//sys_VBlankFuncChange( VBlankFunc, NULL );	//VBlankセット
	sys_VBlankFuncChange( VBlankFunc, (void*)wk );	//VBlankセット

	//初期化
	wk->ScaleX = 1 << FX32_SHIFT;
	wk->ScaleY = 1 << FX32_SHIFT;
	wk->cancel = 0;

	MsgPrintSkipFlagSet( MSG_SKIP_ON );	//スキップ有効

	return;
}

//--------------------------------------------------------------
/**
 * @brief	共通終了
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_end_sub( OPENING_WORK* wk )
{
	int i;

	// パレットフェード開放
	PaletteFadeWorkAllocFree( wk->pfd, FADE_MAIN_OBJ );
	PaletteFadeWorkAllocFree( wk->pfd, FADE_MAIN_BG );

	//パレットフェードシステム開放
	PaletteFadeFree( wk->pfd );
	wk->pfd = NULL;

	OpeningAffReset();						//拡大縮小リセット
	OpeningRereaseCellObject(&wk->ObjWork);	//2Dオブジェクト関連領域開放
	MSGMAN_Delete( wk->msgman );			//メッセージマネージャ開放
	WORDSET_Delete( wk->wordset );
	STRBUF_Delete( wk->msg_buf );			//メッセージバッファ開放
	STRBUF_Delete( wk->tmp_buf );			//メッセージバッファ開放

	for( i=0; i < OPENING_MENU_MAX ;i++ ){
		STRBUF_Delete( wk->menu_buf[i] );	//メニューバッファ開放
	}

	OpeningExitBmpWin( wk->bmpwin );		//BMPウィンドウ開放
	BgExit( wk->bgl );						//BGL削除
	return;
}

//--------------------------------------------------------------
/**
 * @brief	会話ウィンドウ表示
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_talk_win_put( OPENING_WORK* wk )
{
	OpeningTalkWinPut( &wk->bmpwin[BMPWIN_OOKIDO], CONFIG_GetWindowType(wk->config) );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[BMPWIN_OOKIDO], FBMP_COL_WHITE );	//塗りつぶし
	return;
}

//--------------------------------------------------------------
/**
 * @brief	主人公BGのフェードイン
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_hero_fade_in( OPENING_WORK* wk )
{
	u16 col;
	col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;

	PaletteFadeReq( wk->pfd, PF_BIT_MAIN_BG, 0x000c, 0, 16, 0, col );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	主人公BGのフェードアウト
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------
static void opening_hero_fade_out( OPENING_WORK* wk )
{
	u16 col;
	col = (PM_VERSION == VERSION_DIAMOND) ? 0x7356 : 0x573b;

	//PaletteFadeReq( wk->pfd, PF_BIT_MAIN_BG, 0x000c, 0, 0, 16, col );
	PaletteFadeReq( wk->pfd, PF_BIT_MAIN_BG, 0x000c, -2, 0, 16, col );
	return;
}

#if 0
		//ウィンドウにカーソル画像を描画
		//BmpWin_DrawCursorImage(GF_BGL_BMPWIN* win, u32 x, u32 y);
#endif


