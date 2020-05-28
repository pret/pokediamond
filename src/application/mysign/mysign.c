//============================================================================================
/**
 * @file	mysign.c
 * @bfief	マイサイン作成処理
 * @author	Akito Mori
 * @date	05.10.05
 */
//============================================================================================

#include "common.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/pm_str.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_oekaki.h"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/msg_print.h"
#include "gflib/touchpanel.h"
#include "poketool/monsno.h"
#include "application/mysign.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "msgdata/msg_opening_name.h"
#include "field/fld_bmp.h"
#include "system/fontoam.h"
#include "savedata/savedata.h"
#include "savedata/trainercard_data.h"
#include "savedata/record.h"
#include "savedata/config.h"


#include "mysign_local.h"



//#include "msgdata/msg.naix"
#include "msgdata/msg_ev_win.h"

// SE用定義
#define OEKAKI_MOVE_SE		(SEQ_SE_DP_SELECT)
#define OEKAKI_DECIDE_SE	(SEQ_SE_DP_SELECT)
#define OEKAKI_BS_SE		(SEQ_SE_DP_SELECT)
// Snd_SePlay( SEQ_SE_DP_KYU01 );

#define BUTTON_NUM			( 1 )

#include "mysign.naix"			// グラフィックアーカイブ定義
//============================================================================================
//	定数定義
//============================================================================================
enum {
	SEQ_IN = 0,
	SEQ_MAIN,
	SEQ_OUT,
};



//============================================================================================
//	プロトタイプ宣言
//============================================================================================

/*** 関数プロトタイプ ***/
static void VBlankFunc( void * work );
static void VramBankSet(void);
static void BgInit( GF_BGL_INI * ini );
static void InitWork( MYSIGN_WORK *wk );
static void FreeWork( MYSIGN_WORK *wk );
static void BgExit( GF_BGL_INI * ini );
static void BgGraphicSet( MYSIGN_WORK * wk );
static void char_pltt_manager_init(void);
static void InitCellActor(MYSIGN_WORK *wk);
static void SetCellActor(MYSIGN_WORK *wk);
static void BmpWinInit(MYSIGN_WORK *wk, PROC* proc);
static void BmpTouchYesnoWin_Init( GF_BGL_INI *ini, GF_BGL_BMPWIN  **yeswin, GF_BGL_BMPWIN  **nowin, int heap  );
static void BmpTouchYesnoWin_End( GF_BGL_BMPWIN  *yeswin, GF_BGL_BMPWIN  *nowin );
static void BmpWinDelete( MYSIGN_WORK *wk );
static void ControlCursor(MYSIGN_WORK *wk);
static void CursorAppearUpDate(MYSIGN_WORK *wk, int arrow);
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y );
static void NormalTouchFunc(MYSIGN_WORK *wk);
static int  EndTouchFunc( GF_BGL_BMPWIN *TalkWin, GF_BGL_BMPWIN *Yes, GF_BGL_BMPWIN *No );
static int Oekaki_MainNormal( MYSIGN_WORK *wk, int seq );
static void EndSequenceCommonFunc( MYSIGN_WORK *wk );
static int Oekaki_EndSelectPutString( MYSIGN_WORK *wk, int seq );
static int Oekaki_EndSelectWait( MYSIGN_WORK *wk, int seq );
static int 	Oekaki_EndChild( MYSIGN_WORK *wk, int seq );
static int 	Oekaki_EndChildWait( MYSIGN_WORK *wk, int seq );
static int 	Oekaki_EndChildWait2( MYSIGN_WORK *wk, int seq );
static int Oekaki_ReWrite( MYSIGN_WORK *wk, int seq );
static int Oekaki_ReWriteWait( MYSIGN_WORK *wk, int seq );
static int Oekaki_EndParentOnly( MYSIGN_WORK *wk, int seq );
static int Oekaki_EndParentOnlyWait( MYSIGN_WORK *wk, int seq );
static void DrawPoint_to_Line( 	GF_BGL_BMPWIN *win, 	const u8 *brush, 	int px, int py, int *sx, int *sy, 	int count, int flag );
static void Stock_OldTouch( TOUCH_INFO *all, OLD_TOUCH_INFO *stock );
static void DrawBrushLine( GF_BGL_BMPWIN *win, TOUCH_INFO *all, OLD_TOUCH_INFO *old, int draw );
static void MoveCommCursor( MYSIGN_WORK *wk );
static void DebugTouchDataTrans( MYSIGN_WORK *wk );
static void CursorColTrans(u16 *CursorCol);
static void NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, MYSIGN_WORK *wk );
static void LineDataSendRecv( MYSIGN_WORK *wk );
static void EndMessagePrint( MYSIGN_WORK *wk, int msgno );
static int EndMessageWait( int msg_index );
static void EndMessageWindowOff( MYSIGN_WORK *wk );
static int Oekaki_LogoutChildMes( MYSIGN_WORK *wk, int seq );
static int Oekaki_LogoutChildClose( MYSIGN_WORK *wk, int seq );
static int Oekaki_LogoutChildMesWait( MYSIGN_WORK *wk, int seq );
static void PalButtonAppearChange( CLACT_WORK_PTR *act, int no);
static void EndButtonAppearChange( CLACT_WORK_PTR *act, BOOL flag );
static int Oekaki_ReWriteSelect( MYSIGN_WORK *wk, int seq );
static void TouchYesNoStart( GF_BGL_INI *bgl, TOUCH_SW_SYS* touch_sub_window_sys );
static void Output_SignData( u8 *des, u8 *src );
static void *PrintCGXOnly(GF_BGL_BMPWIN * win, STRBUF *msg, int y, u8 fnt_index,const   GF_PRINTCOLOR col);
static void BrushCanvas( MYSIGN_WORK *wk);
static void PlayScruchSe( SCRUCH_INFO *scruchInfo );
static void _BmpWinPrint_Rap(
			GF_BGL_BMPWIN * win, void * src,
			int src_x, int src_y, int src_dx, int src_dy,
			int win_x, int win_y, int win_dx, int win_dy );




static int (*FuncTable[])(MYSIGN_WORK *wk, int seq)={
	NULL,							// MYSIGN_MODE_INIT  = 0, 
	Oekaki_MainNormal,              // MYSIGN_MODE,
	Oekaki_EndSelectPutString,      // MYSIGN_MODE_END_SELECT,
	Oekaki_EndSelectWait,			// MYSIGN_MODE_END_SELECT_WAIT,
	Oekaki_ReWrite,					// MYSIGN_MODE_REWRITE_
	Oekaki_ReWriteWait,				// MYSIGN_MODE_REWRITE_WAIT
	Oekaki_ReWriteSelect,			// MYSIGN_MODE_REWRITE_SELECT
};



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
PROC_RESULT MySignProc_Init( PROC * proc, int * seq )
{
	MYSIGN_WORK * wk;

	switch(*seq){
	case 0:
		WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );
		
		sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
		sys_HBlankIntrStop();	//HBlank割り込み停止

		GF_Disp_GX_VisibleControlInit();
		GF_Disp_GXS_VisibleControlInit();
		GX_SetVisiblePlane( 0 );
		GXS_SetVisiblePlane( 0 );

		sys_CreateHeap( HEAPID_BASE_APP, HEAPID_OEKAKI, 0x40000 );

		wk = PROC_AllocWork( proc, sizeof(MYSIGN_WORK), HEAPID_OEKAKI );
		memset( wk, 0, sizeof(MYSIGN_WORK) );
		wk->bgl = GF_BGL_BglIniAlloc( HEAPID_OEKAKI );
		
		// 文字列マネージャー生成
		wk->WordSet    = WORDSET_Create( HEAPID_OEKAKI );
		wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_oekaki_dat, HEAPID_OEKAKI );

		sys_KeyRepeatSpeedSet( 4, 8 );

		// VRAM バンク設定
		VramBankSet();
		
		// BGLレジスタ設定
		BgInit( wk->bgl );					

///		WIPE_ResetBrightness( WIPE_DISP_MAIN );	<<20060715 del
///		WIPE_ResetBrightness( WIPE_DISP_SUB );	<<20060715 del
		
		// 輝度変更セット
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_OEKAKI );
		

		// パラメータ取得
		{
			SAVEDATA *sv = (SAVEDATA*)PROC_GetParentWork(proc);
			// サイン書き出しバッファポインタ取得
			wk->SignBuf = (u8*)TRCSave_GetSighnDataPtr(TRCSave_GetSaveDataPtr(sv));

			// レコードデータポインタ取得
			wk->record  = (RECORD *)SaveData_GetRecord((SAVEDATA*)PROC_GetParentWork(proc));
			wk->config  = (CONFIG *)SaveData_GetConfig((SAVEDATA*)PROC_GetParentWork(proc));
		}

		//BGグラフィックセット
		BgGraphicSet( wk );

		InitTPSystem();						// タッチパネルシステム初期化
		InitTPNoBuff(1);
  
		// VBlank関数セット
		sys_VBlankFuncChange( VBlankFunc, wk->bgl );	
  
		// ボタン用フォントを読み込み
		FontProc_LoadFont( FONT_BUTTON, HEAPID_OEKAKI );


		// ワーク初期化
		InitWork( wk );

		// OBJキャラ、パレットマネージャー初期化
		char_pltt_manager_init();

		// CellActorシステム初期化
		InitCellActor(wk);
		
		// CellActro表示登録
		SetCellActor(wk);

		// BMPWIN登録・描画
		BmpWinInit(wk,proc);

		// サウンドデータロード(サイン入力)(BGM引継ぎ)
		Snd_DataSetByScene( SND_SCENE_SUB_TRCARD, 0, 0 );
	
		// 画面出力を上下入れ替える
		GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);

		(*seq)++;
		break;
	case 1:
		wk = PROC_GetWork( proc );
		(*seq) = SEQ_IN;
		return PROC_RES_FINISH;
		break;
	}
	return PROC_RES_CONTINUE;
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

PROC_RESULT MySignProc_Main( PROC * proc, int * seq )
{
	MYSIGN_WORK * wk  = PROC_GetWork( proc );

	switch( *seq ){
	case SEQ_IN:
		if( WIPE_SYS_EndCheck() ){
			// ワイプ処理待ち
			*seq = SEQ_MAIN;
		}
		break;

	case SEQ_MAIN:
		// カーソル移動

		// シーケンス毎の動作
		if(FuncTable[wk->seq]!=NULL){
			*seq = (*FuncTable[wk->seq])( wk, *seq );
		}

		CursorColTrans(&wk->CursorPal);

		break;

	case SEQ_OUT:
		if( WIPE_SYS_EndCheck() ){
			return PROC_RES_FINISH;
		}
		break;
	}
	CLACT_Draw( wk->clactSet );									// セルアクター常駐関数

	return PROC_RES_CONTINUE;
}

#define DEFAULT_NAME_MAX		18

// ダイヤ・パールで変わるんだろう
#define MALE_NAME_START			0
#define FEMALE_NAME_START		18

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
PROC_RESULT MySignProc_End( PROC * proc, int * seq )
{
	MYSIGN_WORK  *wk    = PROC_GetWork( proc );
	int i;

	// サインをセーブデータに書き出し
	Output_SignData( wk->SignBuf, wk->OekakiBoard.chrbuf );

	// Vblank期間中のBG転送終了
	sys_VBlankFuncChange( NULL, NULL);

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

	// リソース解放
	DeleteCharManager();
	DeletePlttManager();

	// BMPウィンドウ開放
	BmpWinDelete( wk );

	// ボタン用フォント解放
	FontProc_UnloadFont( FONT_BUTTON );

	// BGL削除
	BgExit( wk->bgl );

	// タッチパネルシステム終了
	StopTP();							


	// メッセージマネージャー・ワードセットマネージャー解放
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );

	// ワーク解放
	FreeWork( wk );

	PROC_FreeWork( proc );				// PROCワーク開放

	// 入れ替わっていた上下画面出力を元に戻す
	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);

	sys_VBlankFuncChange( NULL, NULL );		// VBlankセット

	sys_DeleteHeap( HEAPID_OEKAKI );

	return PROC_RES_FINISH;
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
	
	GF_BGL_VBlankFunc( (GF_BGL_INI*)work );
	
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
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

	// メイン画面文字版0
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );


	}

	// メイン画面ラクガキ面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
	}

	// メイン画面背景
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
//		GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
	}

#if 0
	// 背景 (CHAR)
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}
#endif

	// サブ画面テキスト面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, GF_BGL_FRAME0_S );
	}

	// サブ画面背景面
	{	
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_S, &TextBgCntDat, GF_BGL_MODE_TEXT );
	}

	GF_BGL_ClearCharSet( GF_BGL_FRAME0_M, 32, 0, HEAPID_OEKAKI );
	GF_BGL_ClearCharSet( GF_BGL_FRAME0_S, 32, 0, HEAPID_OEKAKI );

}


#define TALK_MESSAGE_BUF_NUM	( 40*2 )
#define END_MESSAGE_BUF_NUM		( 10*2 )
#define  TITLE_MESSAGE_BUF_NUM	( 20*2 )

//------------------------------------------------------------------
/**
 * お絵かきワーク初期化
 *
 * @param   wk		MYSIGN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void InitWork( MYSIGN_WORK *wk )
{
	int i;

	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		wk->TrainerName[i] = STRBUF_Create( PERSON_NAME_SIZE+EOM_SIZE, HEAPID_OEKAKI );
		wk->AllTouchResult[i].size = 0;
		wk->OldTouch[i].size = 0;

	}
	// 「やめる」文字列バッファ作成
	wk->EndString   = STRBUF_Create( END_MESSAGE_BUF_NUM,   HEAPID_OEKAKI );
	wk->TitleString = STRBUF_Create( TITLE_MESSAGE_BUF_NUM, HEAPID_OEKAKI );
	wk->TalkString  = STRBUF_Create( TALK_MESSAGE_BUF_NUM,  HEAPID_OEKAKI );

	// ブラシ初期化
	wk->brush_color  = 0;
	

	wk->seq = MYSIGN_MODE;
	
	// 「やめる」取得
	MSGMAN_GetString( wk->MsgManager, msg_oekaki_13, wk->EndString );

	// トレーナーサインを書こう
	MSGMAN_GetString( wk->MsgManager, msg_oekaki_10, wk->TitleString );

	// 下画面ウインドウシステム初期化
	wk->TouchSubWindowSys = TOUCH_SW_AllocWork( HEAPID_OEKAKI );

	MI_CpuClearFast( &wk->scruchInfo, sizeof(SCRUCH_INFO));
}

//------------------------------------------------------------------
/**
 * $brief   ワーク解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void FreeWork( MYSIGN_WORK *wk )
{
	int i;

	TOUCH_SW_FreeWork( wk->TouchSubWindowSys );


	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		STRBUF_Delete( wk->TrainerName[i] );
	}
	STRBUF_Delete( wk->TalkString ); 
	STRBUF_Delete( wk->TitleString  ); 
	STRBUF_Delete( wk->EndString  ); 

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
static void BgExit( GF_BGL_INI * ini )
{

	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME3_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( ini, GF_BGL_FRAME0_M );

	sys_FreeMemoryEz( ini );
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
static void BgGraphicSet( MYSIGN_WORK * wk )
{
	GF_BGL_INI *bgl = wk->bgl;

	// 上下画面ＢＧパレット転送
	ArcUtil_PalSet(    ARC_MYSIGN_GRA, NARC_mysign_mysign_m_nclr, PALTYPE_MAIN_BG, 0, 16*2*3,  HEAPID_OEKAKI);
	ArcUtil_PalSet(    ARC_MYSIGN_GRA, NARC_mysign_mysign_s_nclr, PALTYPE_SUB_BG,  0, 16*2*2,  HEAPID_OEKAKI);
	
	// 会話フォントパレット転送
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, 13*0x20, HEAPID_OEKAKI );
	TalkFontPaletteLoad( PALTYPE_SUB_BG,  13*0x20, HEAPID_OEKAKI );


	// ０キャラ目をクリアする
	GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, HEAPID_OEKAKI );

	// メイン画面BG2キャラ転送
	ArcUtil_BgCharSet( ARC_MYSIGN_GRA, NARC_mysign_mainbg_lz_ncgr, bgl, GF_BGL_FRAME2_M, 0, 32*8*0x20, 1, HEAPID_OEKAKI);

	// メイン画面BG2スクリーン転送
	ArcUtil_ScrnSet(   ARC_MYSIGN_GRA, NARC_mysign_mainbg_lz_nscr, bgl, GF_BGL_FRAME2_M, 0, 32*24*2, 1, HEAPID_OEKAKI);



	// サブ画面BG1キャラ転送
	ArcUtil_BgCharSet( ARC_MYSIGN_GRA, NARC_mysign_subbg_lz_ncgr, bgl, GF_BGL_FRAME1_S, 0, 32*8*0x20, 1, HEAPID_OEKAKI);

	// サブ画面BG1スクリーン転送
	ArcUtil_ScrnSet(   ARC_MYSIGN_GRA, NARC_mysign_subbg_lz_nscr, bgl, GF_BGL_FRAME1_S, 0, 32*24*2, 1, HEAPID_OEKAKI);

	// サブ画面会話ウインドウグラフィック転送
	TalkWinGraphicSet(
				bgl, GF_BGL_FRAME0_M, 1, FLD_MESFRAME_PAL,  CONFIG_GetWindowType(wk->config), HEAPID_OEKAKI );

	MenuWinGraphicSet(
				bgl, GF_BGL_FRAME0_M, 1+TALK_WIN_CGX_SIZ, FLD_MENUFRAME_PAL, 0, HEAPID_OEKAKI );

}


//** CharManager PlttManager用 **//
#define OEKAKI_CHAR_CONT_NUM				(20)
#define OEKAKI_CHAR_VRAMTRANS_MAIN_SIZE		(2048)
#define OEKAKI_CHAR_VRAMTRANS_SUB_SIZE		(2048)
#define OEKAKI_PLTT_CONT_NUM				(20)

//-------------------------------------
//
//	キャラクタマネージャー
//	パレットマネージャーの初期化
//
//=====================================
static void char_pltt_manager_init(void)
{
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			OEKAKI_CHAR_CONT_NUM,
			OEKAKI_CHAR_VRAMTRANS_MAIN_SIZE,
			OEKAKI_CHAR_VRAMTRANS_SUB_SIZE,
			HEAPID_OEKAKI
		};
		InitCharManager(&cm);
	}
	// パレットマネージャー初期化
	InitPlttManager(OEKAKI_PLTT_CONT_NUM, HEAPID_OEKAKI);

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
static void InitCellActor(MYSIGN_WORK *wk)
{
	int i;
	
	
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	// 共有OAMマネージャ作成
	// レンダラ用OAMマネージャ作成
	// ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			0, 126,		// メイン画面OAM管理領域
			0, 32,		// メイン画面アフィン管理領域
			0, 126,		// サブ画面OAM管理領域
			0, 32,		// サブ画面アフィン管理領域
			HEAPID_OEKAKI);
	
	
	
	// セルアクター初期化
	wk->clactSet = CLACT_U_SetEasyInit( 50, &wk->renddata, HEAPID_OEKAKI );
	
	CLACT_U_SetSubSurfaceMatrix( &wk->renddata, 0, NAMEIN_SUB_ACTOR_DISTANCE );

	
	//リソースマネージャー初期化
	for(i=0;i<CLACT_RESOURCE_NUM;i++){		//リソースマネージャー作成
		wk->resMan[i] = CLACT_U_ResManagerInit(2, i, HEAPID_OEKAKI);
	}


	//---------上画面用-------------------

	//chara読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_ncgr, 1, 0, NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_OEKAKI);

	//pal読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_MYSIGN_GRA, NARC_mysign_mysign_m_obj_nclr, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 3, HEAPID_OEKAKI);

	//cell読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_ncer, 1, 0, CLACT_U_CELL_RES,HEAPID_OEKAKI);

	//同じ関数でanim読み込み
	wk->resObjTbl[MAIN_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_nanr, 1, 0, CLACT_U_CELLANM_RES,HEAPID_OEKAKI);


	//---------下画面用-------------------



	//chara読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] = CLACT_U_ResManagerResAddArcChar(wk->resMan[CLACT_U_CHAR_RES], 
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_ncgr, 1, 1, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_OEKAKI);

	//pal読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] = CLACT_U_ResManagerResAddArcPltt(wk->resMan[CLACT_U_PLTT_RES],
							ARC_MYSIGN_GRA, NARC_mysign_mysign_m_obj_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DSUB, 3, HEAPID_OEKAKI);

	//cell読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELL_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELL_RES],
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_ncer, 1, 1, CLACT_U_CELL_RES,HEAPID_OEKAKI);

	//同じ関数でanim読み込み
	wk->resObjTbl[SUB_LCD][CLACT_U_CELLANM_RES] = CLACT_U_ResManagerResAddArcKindCell(wk->resMan[CLACT_U_CELLANM_RES],
							ARC_MYSIGN_GRA, NARC_mysign_obj_lz_nanr, 1, 1, CLACT_U_CELLANM_RES,HEAPID_OEKAKI);

	// リソースマネージャーから転送

	// Chara転送
	CLACT_U_CharManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_CHAR_RES] );
	CLACT_U_CharManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_CHAR_RES] );

	// パレット転送
	CLACT_U_PlttManagerSet( wk->resObjTbl[MAIN_LCD][CLACT_U_PLTT_RES] );
	CLACT_U_PlttManagerSet( wk->resObjTbl[SUB_LCD][CLACT_U_PLTT_RES] );

}

#define TRAINER_NAME_POS_X		( 24 )
#define TRAINER_NAME_POS_Y		( 32 )
#define TRAINER_NAME_POS_SPAN	( 32 )

static const u16 pal_button_oam_table[BUTTON_NUM][3]={
	{48+12*8*2-2*8, 171+4, 0},
//	{48       , 171+4, 5},
//	{48+12*8*1, 171+4, 7},
};

//------------------------------------------------------------------
/**
 * セルアクター登録
 *
 * @param   wk			MYSIGN_WORK*
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCellActor(MYSIGN_WORK *wk)
{
	int i;
	// セルアクターヘッダ作成
	CLACT_U_MakeHeader(&wk->clActHeader_m, 0, 0, 0, 0, CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
	0, 0,
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

		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 1;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_OEKAKI;

		//セルアクター表示開始

		// メイン画面用(矢印の登録）
#if 0
		for(i=0;i<5;i++){
			add.ClActHeader	= &wk->clActHeader_s;
			add.mat.x = FX32_ONE * (  TRAINER_NAME_POS_X + i * 40);
			add.mat.y = FX32_ONE * ( TRAINER_NAME_POS_Y + TRAINER_NAME_POS_SPAN );
			add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
			wk->MainActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->MainActWork[i],1);
			CLACT_AnmChg( wk->MainActWork[i], i );
			CLACT_SetDrawFlag( wk->MainActWork[i], 0 );

		}
#endif
		

		// メイン画面パレット・「やめる」ボタンの登録
		for(i=0;i<BUTTON_NUM;i++){
			add.ClActHeader	= &wk->clActHeader_s;
			add.mat.x = FX32_ONE * (  pal_button_oam_table[i][0]);
			add.mat.y = FX32_ONE * ( pal_button_oam_table[i][1] );
			wk->ButtonActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->ButtonActWork[i],1);
			CLACT_AnmChg( wk->ButtonActWork[i], pal_button_oam_table[i][2] );
			CLACT_PaletteNoChg( wk->ButtonActWork[i], 0 );
			if(i==0){
				CLACT_BGPriorityChg( wk->ButtonActWork[i], 2 );
			}

//			CLACT_SetDrawFlag( wk->ButtonActWork[i], 0 );
		}

#if 0
		// サブ画面用(矢印の登録）
		for(i=0;i<5;i++){
			add.mat.x = FX32_ONE *   TRAINER_NAME_POS_X;
			add.mat.y = FX32_ONE * ( TRAINER_NAME_POS_Y + TRAINER_NAME_POS_SPAN*i ) + NAMEIN_SUB_ACTOR_DISTANCE;
			wk->SubActWork[i] = CLACT_Add(&add);
			CLACT_SetAnmFlag(wk->SubActWork[i],1);
			CLACT_AnmChg( wk->SubActWork[i], i );
			CLACT_DrawPriorityChg(wk->SubActWork[i], 1);	// それぞれのアクターのプライオリティ設定
			CLACT_SetDrawFlag( wk->SubActWork[i], 0 );
			
		}
#endif		
	}	
	GF_Disp_GX_VisibleControl(  GX_PLANEMASK_OBJ, VISIBLE_ON );	//メイン画面OBJ面ＯＮ
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );	//サブ画面OBJ面ＯＮ
	
}


//------------------------------------------------------------------
/**
 * @brief   ＯＡＭ用にBmpWinのメモリにのみ文字列を描画する
 *
 * @param   win			BMPWIN
 * @param   msg			STRBUF
 * @param   y			BMP内の描画開始Ｙ座標
 * @param   fnt_index	フォンオ指定
 * @param   col			カラー指定
 *
 * @retval  void *		描画してメモリのトップ
 */
//------------------------------------------------------------------
static void *PrintCGXOnly(GF_BGL_BMPWIN * win, STRBUF *msg, int y, u8 fnt_index,const   GF_PRINTCOLOR col)
{
	int x,length;

	length = FontProc_GetPrintStrWidth( FONT_BUTTON, msg, 0 );
	x      = ((win->sizx*8)-length)/2;

	GF_STR_PrintColor(	win, fnt_index, msg, x, y, MSG_NO_PUT, col,NULL);

	return win->chrbuf;
}


// おえかきボードBMP（下画面）
#define OEKAKI_BOARD_POSX	 ( 4 )
#define OEKAKI_BOARD_POSY	 ( 9 )


// 名前表示BMP（上画面）
#define OEKAKI_NAME_BMP_W	 ( 10 )
#define OEKAKI_NAME_BMP_H	 (  2 )
#define OEKAKI_NAME_BMP_SIZE (OEKAKI_NAME_BMP_W * OEKAKI_NAME_BMP_H)

#define END_BMP_OFFSET		 (1+OEKAKI_BOARD_W*OEKAKI_BOARD_H)
#define TITLE_BMP_OFFSET     (END_BMP_OFFSET + OEKAKI_END_BMP_W*OEKAKI_END_BMP_H)

// 「やめる」文字列BMP（下画面）
#define OEKAKI_END_BMP_X	( 26 )
#define OEKAKI_END_BMP_Y	( 21 )
#define OEKAKI_END_BMP_W	( 8  )
#define OEKAKI_END_BMP_H	( 2  )

// 「トレーナーサインをかこう！」
#define TITLE_BMP_X			(  2 )
#define TITLE_BMP_Y			(  2 )
#define TITLE_BMP_W			( 28 )
#define TITLE_BMP_H			(  2 )

// 会話ウインドウ表示位置定義
#define OEKAKI_TALK_X		(  2 )
#define OEKAKI_TALK_Y		(  1 )

#define OBJ_VRAM_WORD_OFFSET		( 0 )
#define OBJ_VRAM_WORD_TRANS_SIZE	( 0x20*4*2 )
//------------------------------------------------------------------
/**
 * BMPWIN処理（文字パネルにフォント描画）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinInit( MYSIGN_WORK *wk, PROC* proc )
{
	// ---------- メイン画面 ------------------

	// BG0面BMP（会話ウインドウ）ウインドウ確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->MsgWin, GF_BGL_FRAME0_M,
		OEKAKI_TALK_X, OEKAKI_TALK_Y, FLD_MSG_WIN_SX, FLD_MSG_WIN_SY, 13,  1 + TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ );
	GF_BGL_BmpWinDataFill( &wk->MsgWin, 0x0f0f );

	// BG1面用BMP（お絵かき画像）ウインドウ確保
	GF_BGL_BmpWinAdd(wk->bgl, &wk->OekakiBoard, GF_BGL_FRAME1_M,
		OEKAKI_BOARD_POSX, OEKAKI_BOARD_POSY, OEKAKI_BOARD_W, OEKAKI_BOARD_H, 1,  1 );
	GF_BGL_BmpWinDataFill( &wk->OekakiBoard, 0x0202 );

	// BG1面BMP（やめる）ウインドウ確保・描画
	GF_BGL_BmpWinAdd(wk->bgl, &wk->EndWin, GF_BGL_FRAME1_M,
	OEKAKI_END_BMP_X, OEKAKI_END_BMP_Y, OEKAKI_END_BMP_W, OEKAKI_END_BMP_H, 2,  1+OEKAKI_BOARD_W*OEKAKI_BOARD_H );

	GF_BGL_BmpWinDataFill( &wk->EndWin, 0x0000 );
//	GF_STR_PrintColor( &wk->EndWin, FONT_BUTTON, wk->EndString, 0, 0, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0x1,0x2,0x3),NULL);

	{
		void *objcharaadr;
		int  i;
		objcharaadr = PrintCGXOnly(&wk->EndWin, wk->EndString, 1, FONT_BUTTON, GF_PRINTCOLOR_MAKE(0xe,7,2));

		// BMP処理で描画したバッファをOBJに転送して反映させる
		DC_FlushRange(objcharaadr,0x20*8*2);	
		for(i=0;i<2;i++){						
			FONTOAM_BmpCutOamSize( &wk->EndWin, 4, 2, 4*i, 0,  (char*)wk->TransWork);
			DC_FlushRange(wk->TransWork,OBJ_VRAM_WORD_TRANS_SIZE);	
			GX_LoadOBJ(wk->TransWork, OBJ_VRAM_WORD_OFFSET+i*OBJ_VRAM_WORD_TRANS_SIZE, OBJ_VRAM_WORD_TRANS_SIZE);
		}
	}


	// BG1面BMP（トレーナーサインを書こう！）ウインドウ確保・描画
	GF_BGL_BmpWinAdd(wk->bgl, &wk->TitleWin, GF_BGL_FRAME1_M,
	TITLE_BMP_X, TITLE_BMP_Y, TITLE_BMP_W, TITLE_BMP_H, 13,  TITLE_BMP_OFFSET );

	{
		int length = FontProc_GetPrintStrWidth( FONT_TALK, wk->TitleString, 0 );
		int x      = (TITLE_BMP_W*8-length)/2;

		GF_BGL_BmpWinDataFill( &wk->TitleWin, 0x0000 );
		GF_STR_PrintColor( &wk->TitleWin, FONT_TALK, wk->TitleString, x, 0, MSG_ALLPUT, GF_PRINTCOLOR_MAKE(0x1,0x2,0x0),NULL);
	}

	// ----------- サブ画面名前表示BMP確保 ------------------
	{
		int i;
		for(i=0;i<OEKAKI_MEMBER_MAX;i++){
			GF_BGL_BmpWinAdd(wk->bgl, &wk->TrainerNameWin[i], GF_BGL_FRAME0_S,	
				TRAINER_NAME_POS_X/8+2, TRAINER_NAME_POS_Y/8+i*4-1, 10, 2, 13,  1+i*OEKAKI_NAME_BMP_SIZE);
			GF_BGL_BmpWinDataFill( &wk->TrainerNameWin[i], 0 );
		}

		//最初に見えている面なので文字パネル描画と転送も行う
		NameCheckPrint( wk->TrainerNameWin, 0, GF_PRINTCOLOR_MAKE(0xe,0xd,0xf), wk );
	}

}	

// はい・いいえBMP（下画面）
#define YESNO_WIN_FRAME_CHAR	( 1 + TALK_WIN_CGX_SIZ )
#define YESNO_CHARA_OFFSET	(1 + TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ + FLD_MSG_WIN_SX*FLD_MSG_WIN_SY)
#define YESNO_WINDOW_X		( 22   )
#define YESNO_WINDOW_Y1		(  7   )
#define YESNO_WINDOW_Y2		(  7+6 )
#define YESNO_CHARA_W		( 8 )
#define YESNO_CHARA_H		( 4 )

static const BMPWIN_DAT TouchYesNoBmpDat[2]={
	{
		GF_BGL_FRAME0_M, YESNO_WINDOW_X, YESNO_WINDOW_Y1,
		YESNO_CHARA_W, YESNO_CHARA_H, 13, YESNO_CHARA_OFFSET
	},
	{
		GF_BGL_FRAME0_M, YESNO_WINDOW_X, YESNO_WINDOW_Y2,
		YESNO_CHARA_W, YESNO_CHARA_H, 13, YESNO_CHARA_OFFSET+YESNO_CHARA_W*YESNO_CHARA_H
		
	}
};




//------------------------------------------------------------------
/**
 * $brief   下画面（タッチ用）はい・いいえウインドウ表示
 *
 * @param   ini		
 * @param   yeswin		
 * @param   nowin		
 * @param   heap		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpTouchYesnoWin_Init( GF_BGL_INI *ini, GF_BGL_BMPWIN  **yeswin, GF_BGL_BMPWIN  **nowin, int heap  )
{
	MSGDATA_MANAGER * man;
	STRBUF *yes,*no;
	int yespos, nopos;

	// はい・いいえ文字列取得
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_ev_win_dat, heap );
	yes = MSGMAN_AllocString( man, msg_ev_win_046 );
	no  = MSGMAN_AllocString( man, msg_ev_win_047 );
	MSGMAN_Delete( man );

	// BMPWIN確保(Alloc)
	*yeswin = GF_BGL_BmpWinAllocGet( heap, 1 );
	*nowin  = GF_BGL_BmpWinAllocGet( heap, 1 );
	
	GF_BGL_BmpWinAddEx( ini, *yeswin, &TouchYesNoBmpDat[0] );
	GF_BGL_BmpWinAddEx( ini, *nowin, &TouchYesNoBmpDat[1] );

	// Window枠描画
	BmpMenuWinWrite( *yeswin, WINDOW_TRANS_OFF, YESNO_WIN_FRAME_CHAR, FLD_MENUFRAME_PAL );
	BmpMenuWinWrite( *nowin, WINDOW_TRANS_OFF, YESNO_WIN_FRAME_CHAR, FLD_MENUFRAME_PAL );

	// BMPキャラ塗りつぶし
	GF_BGL_BmpWinDataFill( *yeswin, 0x0f0f );
	GF_BGL_BmpWinDataFill( *nowin,  0x0f0f );

	// はい・いいえセンタリング位置取得
	yespos = FontProc_GetPrintStrWidth( FONT_TALK, yes, 0 );
    nopos  = FontProc_GetPrintStrWidth( FONT_TALK,  no, 0 );
	yespos = (YESNO_CHARA_W*8/2) - yespos/2;
	nopos =  (YESNO_CHARA_W*8/2) - nopos/2;
	
	// はい・いいえ描画
	
	GF_STR_PrintSimple( *yeswin, FONT_TALK,  yes,  yespos, 2*8-12/2, MSG_ALLPUT, NULL);
	GF_STR_PrintSimple( *nowin,  FONT_TALK,   no,  nopos,  2*8-12/2, MSG_ALLPUT, NULL);

	// はい・いいえ文字列解放
	STRBUF_Delete(yes);
	STRBUF_Delete(no);
}

//------------------------------------------------------------------
/**
 * $brief   下画面（タッチ用）はい・いいえウインドウ削除
 *
 * @param   yeswin		
 * @param   nowin		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpTouchYesnoWin_End( GF_BGL_BMPWIN  *yeswin, GF_BGL_BMPWIN  *nowin )
{
	// BMPWIN表示OFF
	GF_BGL_BmpWinOff( yeswin );
	GF_BGL_BmpWinOff( nowin  );

	// Window枠消去
	BmpMenuWinClear( yeswin, WINDOW_TRANS_ON );
	BmpMenuWinClear( nowin,  WINDOW_TRANS_ON );

	// BMPWIN解放
	GF_BGL_BmpWinFree( yeswin,1 );
	GF_BGL_BmpWinFree( nowin,1 );
}

//------------------------------------------------------------------
/**
 * $brief   確保したBMPWINを解放
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void BmpWinDelete( MYSIGN_WORK *wk )
{
	int i;
	
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		GF_BGL_BmpWinDel( &wk->TrainerNameWin[i] );
	}
	GF_BGL_BmpWinDel( &wk->TitleWin );
	GF_BGL_BmpWinDel( &wk->EndWin );
	GF_BGL_BmpWinDel( &wk->OekakiBoard );
	GF_BGL_BmpWinDel( &wk->MsgWin );


}



//------------------------------------------------------------------
/**
 * カーソル移動処理
 *
 * @param   wk		MYSIGN_WORK*
 *
 * @retval  none	
 */
//------------------------------------------------------------------
static void ControlCursor(MYSIGN_WORK *wk)
{
	int move  = 0;
	int arrow = 0;


	// 移動が発生したら変更
	if(move){
		CursorAppearUpDate(wk,arrow);		// 移動の結果カーソルの形状がどのように変わるかを決定する
	}

}


//------------------------------------------------------------------
/**
 * 移動の結果カーソルの形状がどのように変わるかを決定する
 * 文字の上であれば、正方形のカーソル、ボタンの上であれば長方形のカーソル
 * 文字の更新が行われることで、サブ画面の中のフォントの更新も行われる
 *
 * @param   wk			MYSIGN_WORK*
 * @param   arrow		移動方向
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CursorAppearUpDate(MYSIGN_WORK *wk, int arrow)
{
	VecFx32 tmpVex;

//	tmpVex.x = FX32_ONE*(MAIN_CURSOR_POSX+wk->Cursor.x*12);
//	tmpVex.y = FX32_ONE*(MAIN_CURSOR_POSY+(wk->Cursor.y-1)*16);
//	CLACT_SetMatrix(wk->clActWork[CLACT_CURSOR_NUM], &tmpVex);


}




//------------------------------------------------------------------
/**
 * $brief   カーソル位置を変更する
 *
 * @param   act		アクターのポインタ
 * @param   x		
 * @param   y		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void SetCursor_Pos( CLACT_WORK_PTR act, int x, int y )
{
	VecFx32 mat;

	mat.x = FX32_CONST( x + 8 );
	mat.y = FX32_CONST( y - 10 );
	mat.z = 0;
	CLACT_SetMatrix( act, &mat);

}


#define PAL_BUTTON_X	(  0  )
#define PAL_BUTTON_Y	( 150 )
#define PAL_BUTTON_W	( 12*8 )
#define PAL_BUTTON_H	( 5*8 )
#define PAL_BUTTON_RECT ( 12*8 -1 )
#define END_BUTTON_RECT ( 8*8 -1 )

#define PAL_BUTTON0_X	( PAL_BUTTON_X+PAL_BUTTON_W*0 )
#define PAL_BUTTON1_X	( PAL_BUTTON_X+PAL_BUTTON_W*1 )
#define END_BUTTON_X	( PAL_BUTTON_X+PAL_BUTTON_W*2 )


static const RECT_HIT_TBL sub_button_hittbl[]={
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,END_BUTTON_X,END_BUTTON_X+END_BUTTON_RECT},
{RECT_HIT_END,0,0,0},		// 終了データ
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON0_X,PAL_BUTTON0_X+PAL_BUTTON_RECT},
{PAL_BUTTON_Y,PAL_BUTTON_Y+PAL_BUTTON_H-1,PAL_BUTTON1_X,PAL_BUTTON1_X+PAL_BUTTON_RECT},
};

#define DRAW_AREA_X	(  8*OEKAKI_BOARD_POSX  )
#define DRAW_AREA_Y	(  8*OEKAKI_BOARD_POSY  )
#define DRAW_AREA_W	( OEKAKI_BOARD_W*8 )
#define DRAW_AREA_H	( OEKAKI_BOARD_H*8)

static const RECT_HIT_TBL sub_canvas_touchtbl[]={
	{DRAW_AREA_Y,DRAW_AREA_Y+DRAW_AREA_H,DRAW_AREA_X,DRAW_AREA_X+DRAW_AREA_W},
{RECT_HIT_END,0,0,0},		// 終了データ
};


// 下画面用はい・いいえ処理のタッチ判定テーブル
static const RECT_HIT_TBL end_button_touchtbl[]={
	{ YESNO_WINDOW_Y1*8, (YESNO_WINDOW_Y1+YESNO_CHARA_H)*8, YESNO_WINDOW_X*8, (YESNO_WINDOW_X+YESNO_CHARA_W)*8,},
	{ YESNO_WINDOW_Y2*8, YESNO_WINDOW_Y2*8+YESNO_CHARA_H*8, YESNO_WINDOW_X*8, (YESNO_WINDOW_X+YESNO_CHARA_W)*8,},
	{RECT_HIT_END,0,0,0},		// 終了データ
};



//------------------------------------------------------------------
/**
 * タッチパネルで押したボタンがへこむ
 *
 * @param   wk		MYSIGN_WORKのポインタ
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NormalTouchFunc(MYSIGN_WORK *wk)
{
	int button=-1,touch;

	// 入力処理

	// ブラシ切り替え
	button=GF_TP_RectHitTrg( sub_button_hittbl );
	if( button != RECT_HIT_NONE ){
		if(button==0){
			// 「やめる」を押したらウインドウ描画開始
			if(wk->seq==MYSIGN_MODE){
				EndMessagePrint( wk, msg_oekaki_11 );
				wk->seq = MYSIGN_MODE_END_SELECT;
				EndButtonAppearChange( wk->ButtonActWork, TRUE );
				Snd_SePlay( SEQ_SE_DP_DECIDE );
			}
		}else{
			// 終了ボタンじゃない場合は、色変更
			wk->brush_color = button;
			PalButtonAppearChange( wk->ButtonActWork, button);
		}
	}

	// カーソル位置変更
	touch = GF_TP_RectHitCont( sub_canvas_touchtbl );

//	CLACT_SetDrawFlag( wk->MainActWork[0], 0 );
	if(touch!=RECT_HIT_NONE){
		// 自分のカーソルはタッチパネルの座標を反映させる
//		SetCursor_Pos( wk->MainActWork[0], sys.tp_x, sys.tp_y );
		BrushCanvas(wk);
	}

	// サンプリング情報を取得して格納
	{
		TP_ONE_DATA	tpData;
		int i;
		if(MainTP( &tpData, TP_BUFFERING_JUST, 1 )==TP_OK){
			for(i=0;i<tpData.Size;i++){
				wk->MyTouchResult.x[i] = tpData.TPDataTbl[i].x;
				wk->MyTouchResult.y[i] = tpData.TPDataTbl[i].y;
			}
			wk->MyTouchResult.size  = tpData.Size;
			wk->MyTouchResult.brush = wk->brush_color;
		}
	}


	// 見た目の処理
//	button=GF_TP_RectHitCont( sub_button_hittbl );


}


//------------------------------------------------------------------
/**
 * $brief   パレットとやめるボタンのセルアクター制御
 *
 * @param   act		アクターのポインタ
 * @param   button		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PalButtonAppearChange( CLACT_WORK_PTR *act, int no )
{
	int i;
	
	for(i=0;i<BUTTON_NUM;i++){
		// 押されたボタンはへこむ。ほかのボタンは戻る
		if(i==no){
			CLACT_AnmChg( act[i], pal_button_oam_table[i][2]+1 );
		}else{
			CLACT_AnmChg( act[i], pal_button_oam_table[i][2] );
		}
	}
}

//------------------------------------------------------------------
/**
 * $brief   やめるボタンのオン・オフ
 *
 * @param   act		アクターのポインタ
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndButtonAppearChange( CLACT_WORK_PTR *act, BOOL flag )
{
	if(flag==TRUE){
		CLACT_AnmChg( act[0], pal_button_oam_table[0][2]+1 );
	}else{
		CLACT_AnmChg( act[0], pal_button_oam_table[0][2] );
	}
}

//------------------------------------------------------------------
/**
 * $brief   おえかき終了のはい・いいえウインドウタッチ処理
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static int  EndTouchFunc( GF_BGL_BMPWIN *TalkWin, GF_BGL_BMPWIN *Yes, GF_BGL_BMPWIN *No )
{
	int button;
	int result = 0;
	
	// はい・いいえテスト
	button=GF_TP_RectHitTrg( end_button_touchtbl );
	if( button != RECT_HIT_NONE ){
			// ウインドウクリア
		BmpTalkWinClear( TalkWin, WINDOW_TRANS_ON );
		BmpTouchYesnoWin_End( Yes, No   );
		if(button==0){
			result = 1;
		}else{
			result = 2;
		}
	}
	
	return result;
}
//------------------------------------------------------------------
/**
 * $brief   お絵かきボード通常処理
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_MainNormal( MYSIGN_WORK *wk, int seq )
{
	NormalTouchFunc(wk);			//  タッチパネル処理

	NameCheckPrint( wk->TrainerNameWin, 0, GF_PRINTCOLOR_MAKE(0xe,0xc,0xf),wk);

	
	LineDataSendRecv( wk );

	MoveCommCursor( wk );
	DrawBrushLine( &wk->OekakiBoard, wk->AllTouchResult, wk->OldTouch, 1 );

	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   終了選択処理の共通処理関数(後ろで描画等）
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndSequenceCommonFunc( MYSIGN_WORK *wk )
{
	ControlCursor(wk);		//	DebugOBJPOSGet(wk);
	MoveCommCursor( wk );
	DrawBrushLine( &wk->OekakiBoard, wk->AllTouchResult, wk->OldTouch, 0 );
	
}

//------------------------------------------------------------------
/**
 * $brief   YESNOウインドウシステムスタート
 *
 * @param   bgl		
 * @param   touch_sub_window_sys		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static void TouchYesNoStart( GF_BGL_INI *bgl, TOUCH_SW_SYS* touch_sub_window_sys )
{
	TOUCH_SW_PARAM param;

	// YES NO ウィンドウボタンの表示
	param.p_bgl		= bgl;
	param.bg_frame	= GF_BGL_FRAME0_M;
	param.char_offs	= YESNO_CHARA_OFFSET+YESNO_CHARA_W*YESNO_CHARA_H;
	param.pltt_offs = 8;
	param.x			= 25;
	param.y			= 6;

	TOUCH_SW_Init( touch_sub_window_sys, &param );

}


//------------------------------------------------------------------
/**
 * $brief   お絵かきボード「やめる」を選択した時
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndSelectPutString( MYSIGN_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		TOUCH_SW_PARAM param;

		// YES NO ウィンドウボタンの表示
		TouchYesNoStart( wk->bgl, wk->TouchSubWindowSys );
	
		wk->seq = MYSIGN_MODE_END_SELECT_WAIT;
	}
	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;
}

//------------------------------------------------------------------
/**
 * $brief   「やめますか？」はい・いいえ選択待ち
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_EndSelectWait( MYSIGN_WORK *wk, int seq )
{
	int result;
	result = TOUCH_SW_Main( wk->TouchSubWindowSys );
	switch(result){				//やめますか？
	case TOUCH_SW_RET_YES:						//はい
		// スコア加算
		RECORD_Score_Add( wk->record, SCORE_ID_WRITE_SIGN );
		
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		TOUCH_SW_Reset( wk->TouchSubWindowSys );
		WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 16, 1, HEAPID_OEKAKI );
		return SEQ_OUT;
		break;
	case TOUCH_SW_RET_NO:						//いいえ
		wk->seq = MYSIGN_MODE_REWRITE;
		EndButtonAppearChange( wk->ButtonActWork, FALSE );
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		TOUCH_SW_Reset( wk->TouchSubWindowSys );
		break;
	}

	// 誤送信を防ぐ
	wk->MyTouchResult.size = 0;

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理

	return seq;
}




//------------------------------------------------------------------
/**
 * $brief   
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_ReWriteSelect( MYSIGN_WORK *wk, int seq )
{
	int result = TOUCH_SW_Main( wk->TouchSubWindowSys );
	switch(result){				//かきなおしますか？
	case TOUCH_SW_RET_YES:						//はい
		
		wk->seq = MYSIGN_MODE;
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		TOUCH_SW_Reset( wk->TouchSubWindowSys );

		GF_BGL_BmpWinDataFill( &wk->OekakiBoard, 0x0202 );
		GF_BGL_BmpWinOn( &wk->OekakiBoard );

		break;
	case TOUCH_SW_RET_NO:						//いいえ
		wk->seq = MYSIGN_MODE;
		BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_OFF );
		TOUCH_SW_Reset( wk->TouchSubWindowSys );
		break;
	}

	return seq;
}


//------------------------------------------------------------------
/**
 * $brief   「やめない」にした時、ボードのクリアを入れるか？
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_ReWrite( MYSIGN_WORK *wk, int seq )
{
	EndMessagePrint( wk, msg_oekaki_12 );		// かきなおしますか？
	wk->seq = MYSIGN_MODE_REWRITE_WAIT;

	EndSequenceCommonFunc( wk );				//終了選択時の共通処理
	return seq;

}

//------------------------------------------------------------------
/**
 * $brief   親機が終わりと言ったので終わる
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int Oekaki_ReWriteWait( MYSIGN_WORK *wk, int seq )
{
	if( EndMessageWait( wk->MsgIndex ) ){
		wk->seq = MYSIGN_MODE_REWRITE_SELECT;
		TouchYesNoStart( wk->bgl, wk->TouchSubWindowSys );
//		return SEQ_OUT;
	}

	EndSequenceCommonFunc( wk );		//終了選択時の共通処理
	return seq;

}









//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//11520
//---------------------------------------------------------
// ブラシパターン
//---------------------------------------------------------

// どうしてもパレットデータを3bitに縮めてしまいたいので、透明色を8にして
// 色指定自体は0-7に当てている。0は透明色だがBD面を黒にして黒く見えるようにしている

// BMPデータは最低横8dot分必要なので、4x4のドットデータを作りたい時は
// ２バイトごとに参照されないデータがもう２バイト必要
static const u8 oekaki_brush[2][8][16]={
	{/*  0  */              /*  1  */               /*  2  */              /*  3  */
//	{0x00,0x00, 0x00,0x00,  0x11,0x01,  0x00,0x00,  0x11,0x01, 0x00,0x00,  0x11,0x01,0x00,0x00,},
//	{0x00,0x00, 0x00,0x00,  0x00,0x00,  0x00,0x00,  0x00,0x00, 0x00,0x00,  0x00,0x00,0x00,0x00,},

	{0x00,0x00, 0x00,0x00,  0x10,0x01,  0x00,0x00,  0x10,0x01, 0x00,0x00,  0x00,0x00,0x00,0x00,},
	{0x00,0x00, 0x00,0x00,  0x00,0x00,  0x00,0x00,  0x00,0x00, 0x00,0x00,  0x00,0x00,0x00,0x00,},


	},                                                                     
	{                                                                      
	{0x00,0x00, 0x11,0x11,  0x10,0x01,  0x10,0x11,  0x10,0x01, 0x11,0x11,  0x00,0x00,},
	{0x00,0x00, 0x22,0x22,  0x20,0x02,  0x22,0x22,  0x20,0x02, 0x22,0x22,  0x00,0x00,},
	},
};

/*


















*/



//==============================================================================
/**
 * @brief   描画開始位置がマイナス方向にあっても描画できるBmpWinPrintラッパー
 * @retval  none		
 */
//==============================================================================
static void _BmpWinPrint_Rap(
			GF_BGL_BMPWIN * win, void * src,
			int src_x, int src_y, int src_dx, int src_dy,
			int win_x, int win_y, int win_dx, int win_dy )
{
	if(win_x < 0){
		int diff;
		diff = win_x*-1;
		if(diff>win_dx){
			diff = win_dx;
		}
		win_x   = 0;
		src_x  += diff;
		src_dx -= diff;
		win_dx -= diff;
	}

	if(win_y < 0){
		int diff;
		diff = win_y*-1;
		if(diff>win_dy){
			diff = win_dy;
		}
		win_y   = 0;
		src_y  += diff;
		src_dy -= diff;
		win_dy -= diff;
	}

	GF_BGL_BmpWinPrint( win, src,	src_x, src_y, src_dx, src_dy, win_x, win_y, win_dx, win_dy );
}


//------------------------------------------------------------------
/**
 * $brief   ライン描画
 *
 * @param   win		
 * @param   brush		
 * @param   px		
 * @param   py		
 * @param   sx		
 * @param   sy		
 * @param   count		
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DrawPoint_to_Line( 
	GF_BGL_BMPWIN *win, 
	const u8 *brush, 
	int px, int py, int *sx, int *sy, 
	int count, int flag )
{
	int dx, dy, s, step;
	int x1 = *sx;
	int y1 = *sy;
	int x2 = px;
	int y2 = py;

	// 初回は原点保存のみ
	if(count==0 && flag == 0){
		*sx = px;		*sy = py;
		return;
	}
	

	dx = MATH_IAbs(x2 - x1);  dy = MATH_IAbs(y2 - y1);
	if (dx > dy) {
		if (x1 > x2) {
			step = (y1 > y2) ? 1 : -1;
			s = x1;  x1 = x2;  x2 = s;  y1 = y2;
		} else step = (y1 < y2) ? 1: -1;

//		GF_BGL_BmpWinPrint( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		_BmpWinPrint_Rap( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		s = dx >> 1;
		while (++x1 <= x2) {
			if ((s -= dy) < 0) {
				s += dx;  y1 += step;
			};
//		GF_BGL_BmpWinPrint( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		_BmpWinPrint_Rap( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		}
	} else {
		if (y1 > y2) {
			step = (x1 > x2) ? 1 : -1;
			s = y1;  y1 = y2;  y2 = s;  x1 = x2;
		} else step = (x1 < x2) ? 1 : -1;
//		GF_BGL_BmpWinPrint( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		_BmpWinPrint_Rap( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		s = dy >> 1;
		while (++y1 <= y2) {
			if ((s -= dx) < 0) {
				s += dy;  x1 += step;
			}
//			GF_BGL_BmpWinPrint( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
			_BmpWinPrint_Rap( win, (void*)brush,	0, 0, 4, 4, x1, y1, 4, 4 );
		}
	}
	
	
	*sx = px;			*sy = py;

}

static void Stock_OldTouch( TOUCH_INFO *all, OLD_TOUCH_INFO *stock )
{
	int i;
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		stock[i].size = all[i].size;
		if(all[i].size!=0){
			stock[i].x = all[i].x[all[i].size-1];
			stock[i].y = all[i].y[all[i].size-1];
		}
	}
}



static int debug_count;
//------------------------------------------------------------------
/**
 * $brief  通信で受信したタッチパネルの結果データを下に描画する
 *
 * @param   win		
 * @param   all		
 * @param   draw	メモリ上で行ったCGX変更を転送するか？(0:しない	1:する）
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void DrawBrushLine( GF_BGL_BMPWIN *win, TOUCH_INFO *all, OLD_TOUCH_INFO *old, int draw )
{
	int px,py,i,r,flag=0, sx, sy;

//	OS_Printf("id0=%d,id1=%d,id2=%d,id3=%d,id4=%d\n",all[0].size,all[1].size,all[2].size,all[3].size,all[4].size);

	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		if(all[i].size!=0){
			if(old[i].size){
				sx = old[i].x-OEKAKI_BOARD_POSX*8;
				sy = old[i].y-OEKAKI_BOARD_POSY*8;
			}
			for(r=0;r<all[i].size;r++){
				px = all[i].x[r] - OEKAKI_BOARD_POSX*8;
				py = all[i].y[r] - OEKAKI_BOARD_POSY*8;
				

				// BG1面用BMP（お絵かき画像）ウインドウ確保
				DrawPoint_to_Line(win, oekaki_brush[0][all[i].brush], px, py, &sx, &sy, r, old[i].size);
//				DrawPoint_to_Line(win, oekaki_brush[0][all[i].brush], -1, -1, &sx, &sy, r, old[i].size);
				flag = 1;
			}
			
		}
	}
	if(flag && draw){
		
//		OS_Printf("write board %d times\n",debug_count++);
		GF_BGL_BmpWinOn( win );
	}
	
	// 今回の最終座標のバックアップを取る   
    Stock_OldTouch(all, old);
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		all[i].size = 0;		// 一度描画したら座標情報は捨てる
	}
	
}

//------------------------------------------------------------------
/**
 * $brief   通信データからカーソル位置を移動させる
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void MoveCommCursor( MYSIGN_WORK *wk )
{
	int i;
	// 描画用ペン先情報ワークにも直接反映させる
	TOUCH_INFO *all = wk->AllTouchResult;


	// 座標データが入っている時はカーソル座標を反映させる

//	SetCursor_Pos( wk->MainActWork[i], all[0].x[all[0].size-1],  all[0].y[all[0].size-1]);

	
	
}
//------------------------------------------------------------------
/**
 * $brief   デバッグ用に自分で取得した情報を受信バッファにコピーする
 *
 * @param   wk		
 *
 * @retval  static		
 */
//------------------------------------------------------------------
static void DebugTouchDataTrans( MYSIGN_WORK *wk )
{
	wk->AllTouchResult[0] = wk->MyTouchResult;
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


	GX_LoadOBJPltt((u16*)&tmp, ( 12 )*2, 2);
}


//------------------------------------------------------------------
/**
 * $brief   オンライン状況を確認して上画面に名前を表示する
 *
 * @param   win		
 * @param   frame		
 * @param   color		
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void NameCheckPrint( GF_BGL_BMPWIN *win, int frame, GF_PRINTCOLOR color, MYSIGN_WORK *wk )
{
	int i,id;

	return ;

	// それぞれの文字パネルの背景色でクリア
	for(i=0;i<5;i++){
		GF_BGL_BmpWinFill( &win[i], 0, 0, 0, OEKAKI_NAME_BMP_W*8, OEKAKI_NAME_BMP_H*8 );
	}

	// 描画
	for(i=0;i<OEKAKI_MEMBER_MAX;i++){
		GF_STR_PrintColor(	&win[i], FONT_TALK, wk->TrainerName[i], 0, 0, MSG_NO_PUT, 
										GF_PRINTCOLOR_MAKE(FBMP_COL_RED,FBMP_COL_RED_SDW,15),NULL);
		GF_BGL_BmpWinOn( &win[i] );
	}

}









#define PLATE_CHARA_OFFSET1	( 12 )
#define PLATE_CHARA_OFFSET2	( 16 )

static const u8 plate_num[4]={2,2,3,2};
static const u8 plate_table[4][3]={
	{8*8,17*8,0,},
	{8*8,17*8,0,},
	{5*8,12*8,18*8,},
	{8*8,17*8,0,},

};
static const u8 plate_chara_no[][5]={
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
	{PLATE_CHARA_OFFSET1,PLATE_CHARA_OFFSET1,},
};



//------------------------------------------------------------------
/**
 * $brief   タッチパネル情報の送受信を行う
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void LineDataSendRecv( MYSIGN_WORK *wk )
{

	wk->AllTouchResult[0] = wk->MyTouchResult;

}



//------------------------------------------------------------------
/**
 * $brief   会話ウインドウ表示
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndMessagePrint( MYSIGN_WORK *wk, int msgno )
{
	// 文字列取得
	STRBUF *tempbuf;
	
	tempbuf = STRBUF_Create(TALK_MESSAGE_BUF_NUM,HEAPID_OEKAKI);
	MSGMAN_GetString(  wk->MsgManager, msgno, tempbuf );
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, tempbuf );
	STRBUF_Delete(tempbuf);

	// 会話ウインドウ枠描画
	GF_BGL_BmpWinDataFill( &wk->MsgWin,  0x0f0f );
	BmpTalkWinWrite( &wk->MsgWin, WINDOW_TRANS_ON, 1, FLD_MESFRAME_PAL );

	// 文字列描画開始
	wk->MsgIndex = GF_STR_PrintSimple( &wk->MsgWin, FONT_TALK, wk->TalkString, 0, 0, 
										CONFIG_GetMsgPrintSpeed(wk->config), NULL);


}

//------------------------------------------------------------------
/**
 * $brief   会話表示ウインドウ終了待ち
 *
 * @param   msg_index		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int EndMessageWait( int msg_index )
{
	if(GF_MSG_PrintEndCheck( msg_index )==0){
		
		return 1;
	}
	return 0;
}


//------------------------------------------------------------------
/**
 * $brief   
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void EndMessageWindowOff( MYSIGN_WORK *wk )
{
	BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
}



//------------------------------------------------------------------
/**
 * $brief   サインデータを書き込む（16色データを1bitに縮めて書き込み)
 *
 * @param   des		
 * @param   src		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void Output_SignData( u8 *des, u8 *src )
{
	int i,s,count=0;
	
	
	s=0;
	*des = 0;
	for(i=0;i<OEKAKI_GRAPHI_SIZE;i++){
		int w;

		// 下位データを1bitに
		w = src[i]&0x0f;
		if(w==1){
			*des |= (1<<s);
		}
		s++;

		// 上位データを1bitに
		w = src[i]>>4;
		if(w==1){
			*des |= (1<<s);
		}
		s++;

		// 8bitになったら書き出し
		if(s==8){
			count++;
			des++;
			*des=0;
			s=0;
		}
		
		if( count>= OEKAKI_GRAPHI_SIZE ){
			GF_ASSERT(0 && "圧縮データが領域を超えた");
		}

	}
}


#define MIN_SCRUCH	(3)
#define MAX_SCRUCH	(40)

//--------------------------------------------------------------------------------------------
/**
 * バッジ磨き
 *
 * @param	wk		画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BrushCanvas( MYSIGN_WORK *wk)
{
	BOOL scruch;
	int sub;
	scruch = FALSE;
	//保持座標とタッチ座標の差分を取る
	if( (sys.tp_x!=0xffff)&&(sys.tp_y!=0xffff) && (wk->BeforeX!=0xffff)&&(wk->BeforeY!=0xffff) ){	//値有効か？

		//差分が規定値以上の場合は磨いたことにする
		if ( wk->BeforeX > sys.tp_x ){		//前回のほうが値が大きいか？
			sub = wk->BeforeX - sys.tp_x;
			wk->scruchInfo.DirX = -1;
		}else{
			sub = sys.tp_x - wk->BeforeX;
			wk->scruchInfo.DirX = 1;
		}
		if ( (sub>=MIN_SCRUCH)&&(sub<=MAX_SCRUCH) ){
			if ( wk->BeforeY > sys.tp_y ){	//前回のほうが値が大きいか？
				sub = wk->BeforeY - sys.tp_y;
				wk->scruchInfo.DirY = -1;
			}else{
				sub = sys.tp_y - wk->BeforeY;
				wk->scruchInfo.DirY = 1;
			}
			if (sub<=MAX_SCRUCH){
				scruch = TRUE;			//こすった
				PlayScruchSe( &wk->scruchInfo );
//				Snd_SePlay( SEQ_SE_DP_KYU01 );
			}else{
//				ClearScruchSndNow(&wk->ScruchSnd);
			}
		}else if (sub<=MAX_SCRUCH){
			if ( wk->BeforeY > sys.tp_y ){		//前回のほうが値が大きいか？
				sub = wk->BeforeY - sys.tp_y;
				wk->scruchInfo.DirY = -1;
			}else{
				sub = sys.tp_y - wk->BeforeY;
				wk->scruchInfo.DirY = 1;
			}
			if ((sub>=MIN_SCRUCH)&&(sub<=MAX_SCRUCH)){
				scruch = TRUE;		//こすった
				PlayScruchSe( &wk->scruchInfo );
//				Snd_SePlay( SEQ_SE_DP_KYU01 );
			}else{
//				ClearScruchSndNow(&wk->ScruchSnd);
			}
		}

	}
		//保持座標更新
	wk->BeforeX = sys.tp_x;
	wk->BeforeY = sys.tp_y;
}


//------------------------------------------------------------------
/**
 * @brief   方向を変えたのであれば、効果音を「キュッ」と鳴らす
 *
 * @param   scruchInfo		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void PlayScruchSe( SCRUCH_INFO *scruchInfo )
{
	//初回判定
	if ((scruchInfo->OldDirX == 0)&&(scruchInfo->OldDirY == 0)){
		OS_Printf("初回\n");//初回音
		if(!Snd_SePlayCheck( SEQ_SE_DP_KYU01 )){
			Snd_SePlay( SEQ_SE_DP_KYU01 );
		}
	}
	//前回の方向と今回の方向を比較
	if ((scruchInfo->OldDirX*scruchInfo->DirX<0) ||
			(scruchInfo->OldDirY*scruchInfo->DirY<0)){
//		OS_Printf("切り替え\n");//方向が変わったので音を切り替える
		if(!Snd_SePlayCheck( SEQ_SE_DP_KYU01 )){
			Snd_SePlay( SEQ_SE_DP_KYU01 );
		}
	}

	scruchInfo->OldDirX = scruchInfo->DirX;
	scruchInfo->OldDirY = scruchInfo->DirY;
	scruchInfo->DirX = 0;
	scruchInfo->DirY = 0;
}
