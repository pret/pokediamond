//==============================================================================================
/**
 * @file	syoujyou.c
 * @brief	表彰状（図鑑コンプリート）
 * @author	
 * @date	
 */
//==============================================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/arc_util.h"
#include "savedata/savedata_def.h"

#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/fontproc.h"
#include "msgdata/msg.naix"
#include "system/pm_str.h"
#include "system/wipe.h"
#include "system/snd_tool.h"
#include "system/wordset.h"
#include "system/main.h"

#include "demo\syoujyou.h"
#include "msgdata/msg_award.h"
#include "syoujyou.naix"

//================================================================
//================================================================
//
//
//		
//
//
//================================================================
//----------------------------------
//定数宣言
//----------------------------------
// ＰＲＯＣメインシーケンス
enum {
	SYOUJYOU_SEQ_INIT = 0,
	SYOUJYOU_SEQ_DISPON,
	SYOUJYOU_SEQ_WAIT,
	SYOUJYOU_SEQ_SCROLL,
	SYOUJYOU_SEQ_MAIN,
	SYOUJYOU_SEQ_EXIT,
};

//----------------------------------
//型宣言
//----------------------------------
///	制御用ワーク構造体
typedef struct SYOUJYOU_WORK_tag
{
	int					heapID; 
	int					type; 
	SAVEDATA*			savedata;
	MYSTATUS*			my;

	//ＢＧシステム関連
	GF_BGL_INI*			bgl;
	GF_BGL_BMPWIN		msgwin_m;
	GF_BGL_BMPWIN		msgwin_s;
	MSGDATA_MANAGER*	msgman;
	WORDSET*			wordset;

	//スクロール
	s16					scroll;
	int					wait;
}SYOUJYOU_WORK;

//----------------------------------
//外部関数定義
//----------------------------------
extern void	Main_SetNextProc(FSOverlayID ov_id, const PROC_DATA * proc_data);

//----------------------------------
//関数宣言
//----------------------------------
PROC_RESULT Syoujyou_Init( PROC * proc, int * seq );
PROC_RESULT Syoujyou_Main( PROC * proc, int * seq );
PROC_RESULT Syoujyou_Exit( PROC * proc, int * seq );

static void Syoujyou_VBlank( void* work );

static void Syoujyou_VramBankSet( SYOUJYOU_WORK* wk );
static void Syoujyou_VramBankRelease( SYOUJYOU_WORK* wk );
static void Syoujyou_MsgDataSet( SYOUJYOU_WORK* wk );
static void Syoujyou_MsgDataRelease( SYOUJYOU_WORK* wk );

static void Syoujyou_ScrollInit( SYOUJYOU_WORK* wk );
static void Syoujyou_ScrollSet( SYOUJYOU_WORK* wk );
static void Syoujyou_GraphicLoad( SYOUJYOU_WORK* wk );
static void Syoujyou_MsgPrint( SYOUJYOU_WORK* wk );

//----------------------------------
//マクロ宣言
//----------------------------------
#define KEYTRG( pattern )	( ( sys.trg & ( pattern ) ) == ( pattern ) )
#define KEYCNT( pattern )	( ( sys.cont & ( pattern ) ) == ( pattern ) )

#define FADE( pattern, col, heapID ) {						\
	WIPE_SYS_Start(	WIPE_PATTERN_WMS,pattern,pattern,col,	\
					WIPE_DEF_DIV,WIPE_DEF_SYNC,heapID);		\
}

#define FRAME_ON( frame )		{ GF_BGL_VisibleSet( frame, VISIBLE_ON ); }
#define FRAME_OFF( frame )		{ GF_BGL_VisibleSet( frame, VISIBLE_OFF ); }
#define FRAME_ALLOFF {				\
	FRAME_OFF( GF_BGL_FRAME0_M )	\
	FRAME_OFF( GF_BGL_FRAME1_M )	\
	FRAME_OFF( GF_BGL_FRAME2_M )	\
	FRAME_OFF( GF_BGL_FRAME3_M )	\
	FRAME_OFF( GF_BGL_FRAME0_S )	\
	FRAME_OFF( GF_BGL_FRAME1_S )	\
	FRAME_OFF( GF_BGL_FRAME2_S )	\
	FRAME_OFF( GF_BGL_FRAME3_S )	\
}

//ＢＧコントロール定数
#define SYOUJYOU_TEXT_M_FRAME	(GF_BGL_FRAME0_M)
#define SYOUJYOU_SYOU_M_FRAME	(GF_BGL_FRAME1_M)
#define SYOUJYOU_BACK_M_FRAME	(GF_BGL_FRAME3_M)

#define SYOUJYOU_TEXT_S_FRAME	(GF_BGL_FRAME0_S)
#define SYOUJYOU_SYOU_S_FRAME	(GF_BGL_FRAME1_S)
#define SYOUJYOU_BACK_S_FRAME	(GF_BGL_FRAME3_S)

//=================================================================================================
//
// ＰＲＯＣ定義テーブル
//
//=================================================================================================
const PROC_DATA SyoujyouProcData = {
	Syoujyou_Init,
	Syoujyou_Main,
	Syoujyou_Exit,
	NO_OVERLAY_ID
};

//================================================================
//----------------------------------
//ＰＲＯＣ初期化
//----------------------------------
PROC_RESULT Syoujyou_Init( PROC* proc, int* seq )
{
	SYOUJYOU_WORK* wk;
	int	heapID = HEAPID_SYOUJYOU;

	sys_CreateHeap( HEAPID_BASE_APP, heapID, 0x20000 );

	wk = PROC_AllocWork( proc, sizeof( SYOUJYOU_WORK ), heapID );
	memset( wk, 0, sizeof( SYOUJYOU_WORK ) );

	wk->heapID = heapID;
	{
		SYOUJYOU_INI* ini = (SYOUJYOU_INI*)PROC_GetParentWork( proc );

		wk->savedata	= ini->savedata;
		wk->type		= ini->type;
		wk->my			= SaveData_GetMyStatus(wk->savedata);
	}

	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrSet( NULL,NULL );		// HBlankセット

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane(0);
	GXS_SetVisiblePlane(0);
	sys_KeyRepeatSpeedSet(4,8);

	Syoujyou_VramBankSet( wk );
	Syoujyou_MsgDataSet( wk );
	sys_VBlankFuncChange( Syoujyou_VBlank, (void*)wk );

	GF_Disp_DispOn();

	return	PROC_RES_FINISH;
}

//----------------------------------
//ＰＲＯＣメイン
//----------------------------------
PROC_RESULT Syoujyou_Main( PROC* proc, int* seq )
{
	SYOUJYOU_WORK* wk = PROC_GetWork( proc );
	PROC_RESULT result = PROC_RES_CONTINUE;

	switch( *seq ){
	// 画面初期化
	case SYOUJYOU_SEQ_INIT:

		Syoujyou_ScrollInit( wk );
		Syoujyou_GraphicLoad( wk );
		Syoujyou_MsgPrint( wk );

		FRAME_ON( SYOUJYOU_TEXT_M_FRAME );
		FRAME_ON( SYOUJYOU_SYOU_M_FRAME );
		FRAME_ON( SYOUJYOU_BACK_M_FRAME );
		FRAME_ON( SYOUJYOU_TEXT_S_FRAME );
		FRAME_ON( SYOUJYOU_SYOU_S_FRAME );
		FRAME_ON( SYOUJYOU_BACK_S_FRAME );
		FADE( WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, wk->heapID )
		*seq = SYOUJYOU_SEQ_DISPON;
		break;

	// ディスプレイ反映
	case SYOUJYOU_SEQ_DISPON:
		if(WIPE_SYS_EndCheck() == TRUE){
			wk->wait = 0;
			*seq = SYOUJYOU_SEQ_WAIT;
		}
		break;
	
	// 開始ウェイト
	case SYOUJYOU_SEQ_WAIT:
		if( wk->wait < 60 ){
			wk->wait++;
		} else {
			*seq = SYOUJYOU_SEQ_SCROLL;
		}
		break;
	
	// 開始ウェイト
	case SYOUJYOU_SEQ_SCROLL:
		if( ( wk->scroll > -8*24 )){
			wk->scroll -= 4;
			Syoujyou_ScrollSet( wk );
		} else {
			wk->scroll = -8*24;
			Syoujyou_ScrollSet( wk );
			*seq = SYOUJYOU_SEQ_MAIN;
		}
		break;
	
	// メインループ
	case SYOUJYOU_SEQ_MAIN:
		if( (KEYTRG( PAD_BUTTON_A ))||(KEYTRG( PAD_BUTTON_B ))||( sys.tp_trg ) ){
			FADE( WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, wk->heapID )
			*seq = SYOUJYOU_SEQ_EXIT;
		}
#if 0
		if( KEYCNT( PAD_KEY_UP ) && ( wk->scroll < 0 )){
			wk->scroll += 4;
			Syoujyou_ScrollSet( wk );
		}
		if( KEYCNT( PAD_KEY_DOWN ) && ( wk->scroll > -8*24 )){
			wk->scroll -= 4;
			Syoujyou_ScrollSet( wk );
		}
#endif
		break;

	// 終了
	case SYOUJYOU_SEQ_EXIT:
		if(WIPE_SYS_EndCheck() == TRUE){
			result = PROC_RES_FINISH;
		}
		break;
	}
	return result;
}

//----------------------------------
//ＰＲＯＣ終了
//----------------------------------
PROC_RESULT Syoujyou_Exit( PROC* proc, int* seq )
{
	SYOUJYOU_WORK* wk = PROC_GetWork( proc );
	int heapID = wk->heapID;

	Syoujyou_MsgDataRelease( wk );
	Syoujyou_VramBankRelease( wk );
	sys_VBlankFuncChange( NULL, NULL );

	PROC_FreeWork( proc );
	sys_DeleteHeap( heapID );

	return	PROC_RES_FINISH;
}


//----------------------------------
//ＶＢＬＡＮＫ関数
//----------------------------------
static void Syoujyou_VBlank( void* work )
{
	SYOUJYOU_WORK* wk = work;

	GF_BGL_VBlankFunc(wk->bgl);
}


//----------------------------------
//ＶＲＡＭ設定
//----------------------------------
#define PALSIZE			( 2*16 )

// パレット設定(メインサブ画面共通)
#define SYOUJYOU_BACKPLT_NUM	( 0 )			//背景
#define SYOUJYOU_SYOUPLT_NUM	( 1 )			//賞状
#define SYOUJYOU_TEXTPLT_NUM	( 2 )			//メッセージ

#define BGCONTSET( frame, scr, cgx, scrsiz, bufsiz ){					\
	header.screenBase		= scr;										\
	header.charBase			= cgx;										\
	header.scrbufferSiz		= bufsiz;									\
	header.screenSize		= scrsiz;									\
	GF_BGL_BGControlSet( wk->bgl, frame, &header, GF_BGL_MODE_TEXT );	\
	GF_BGL_ScrClear( wk->bgl, frame );									\
}

static void Syoujyou_VramBankSet( SYOUJYOU_WORK* wk )
{
	{ //ＶＲＡＭ設定
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
			GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG(メインと共通)
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
			GX_VRAM_OBJ_NONE,				// メイン2DエンジンのOBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
			GX_VRAM_SUB_OBJ_NONE,			// サブ2DエンジンのOBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
			GX_VRAM_TEX_NONE,				// テクスチャイメージスロット
			GX_VRAM_TEXPLTT_NONE			// テクスチャパレットスロット
		};
		GF_Disp_SetBank( &vramSetTable );
	}

	{ //ＢＧライブラリ用メモリ確保
		wk->bgl = GF_BGL_BglIniAlloc(wk->heapID);
	}

	{ // ＢＧシステム設定
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_2D
		};	
		GF_BGL_InitBG( &BGsys_data );
	}
	{ // ＢＧシステム設定
		GF_BGL_BGCNT_HEADER header = {	0, 0, 0, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
										0, 0, GX_BG_EXTPLTT_01, 0, 0, 0, FALSE };
		// メインＢＧシステム設定
		// テキストＢＧ設定(BG0)
		BGCONTSET(	SYOUJYOU_TEXT_M_FRAME, GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x10000, 
					GF_BGL_SCRSIZ_256x512, 0x1000 )
		// 賞状ＢＧ設定(BG1)
		BGCONTSET(	SYOUJYOU_SYOU_M_FRAME, GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x08000,
					GF_BGL_SCRSIZ_256x512, 0x1000 )
		// 背景ＢＧ設定(BG3)
		BGCONTSET(	SYOUJYOU_BACK_M_FRAME, GX_BG_SCRBASE_0x2000, GX_BG_CHARBASE_0x04000,
					GF_BGL_SCRSIZ_256x256, 0x0800 )

		// サブＢＧシステム設定
		// テキストＢＧ設定(BG0)
		BGCONTSET(	SYOUJYOU_TEXT_S_FRAME, GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x10000,
					GF_BGL_SCRSIZ_256x512, 0x1000 )
		// 賞状ＢＧ設定(BG1)
		BGCONTSET(	SYOUJYOU_SYOU_S_FRAME, GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x08000,
					GF_BGL_SCRSIZ_256x512, 0x1000 )
		// 背景ＢＧ設定(BG3)
		BGCONTSET(	SYOUJYOU_BACK_S_FRAME, GX_BG_SCRBASE_0x2000, GX_BG_CHARBASE_0x04000,
					GF_BGL_SCRSIZ_256x256, 0x800 )
	}
	FRAME_ALLOFF
}

static void Syoujyou_VramBankRelease( SYOUJYOU_WORK* wk )
{
	FRAME_ALLOFF

	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_TEXT_M_FRAME );
	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_SYOU_M_FRAME );
	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_BACK_M_FRAME );
	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_TEXT_S_FRAME );
	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_SYOU_S_FRAME );
	GF_BGL_BGControlExit( wk->bgl, SYOUJYOU_BACK_S_FRAME );

	sys_FreeMemoryEz( wk->bgl );
}


//----------------------------------
//メッセージ設定
//----------------------------------
#define	SYOUJYOU_TEXT_WIN_PX		(0)
#define	SYOUJYOU_TEXT_WIN_PY		(0)
#define	SYOUJYOU_TEXT_WIN_SX		(32)
#define	SYOUJYOU_TEXT_WIN_SY		(24)
#define	SYOUJYOU_TEXT_WIN_PAL		( SYOUJYOU_TEXTPLT_NUM )
#define	SYOUJYOU_TEXT_WIN_CGX		(1)

#define DOTSIZE						(8)

static void Syoujyou_MsgDataSet( SYOUJYOU_WORK* wk )
{
	BMPWIN_DAT text_windata = { 0,SYOUJYOU_TEXT_WIN_PX,SYOUJYOU_TEXT_WIN_PY,
		SYOUJYOU_TEXT_WIN_SX,SYOUJYOU_TEXT_WIN_SY,SYOUJYOU_TEXT_WIN_PAL,SYOUJYOU_TEXT_WIN_CGX };

	MSG_PrintInit();											//メッセージ表示システム初期化
	wk->msgman = MSGMAN_Create									//メッセージデータ読み込み
		( MSGMAN_TYPE_DIRECT, ARC_MSG,NARC_msg_award_dat, wk->heapID );
	wk->wordset = WORDSET_Create( wk->heapID );					//ワードセット作成

	text_windata.frm_num = SYOUJYOU_TEXT_M_FRAME;
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->msgwin_m, &text_windata );	//ビットマップ作成
	GF_BGL_BmpWinFill(&wk->msgwin_m,FBMP_COL_NULL,0,0,			//ビットマップ初期クリア
			SYOUJYOU_TEXT_WIN_SX * DOTSIZE, SYOUJYOU_TEXT_WIN_SY * DOTSIZE );
	text_windata.frm_num = SYOUJYOU_TEXT_S_FRAME;
	GF_BGL_BmpWinAddEx( wk->bgl, &wk->msgwin_s, &text_windata );	//ビットマップ作成
	GF_BGL_BmpWinFill(&wk->msgwin_s,FBMP_COL_NULL,0,0,			//ビットマップ初期クリア
			SYOUJYOU_TEXT_WIN_SX * DOTSIZE, SYOUJYOU_TEXT_WIN_SY * DOTSIZE );
}

static void Syoujyou_MsgDataRelease( SYOUJYOU_WORK* wk )
{
	GF_BGL_BmpWinDel( &wk->msgwin_s );	//ビットマップ破棄
	GF_BGL_BmpWinDel( &wk->msgwin_m );	//ビットマップ破棄

	WORDSET_Delete( wk->wordset );		//ワードセット破棄
	MSGMAN_Delete(wk->msgman);			//メッセージデータ破棄
}


//----------------------------------
//スクロール設定
//----------------------------------
#define SUBBG_OFFS ( 8*24 )
static void Syoujyou_ScrollInit( SYOUJYOU_WORK* wk )
{
	wk->scroll = 0;
	Syoujyou_ScrollSet( wk );
}

static void Syoujyou_ScrollSet( SYOUJYOU_WORK* wk )
{
	GF_BGL_ScrollSet( wk->bgl, SYOUJYOU_SYOU_M_FRAME, GF_BGL_SCROLL_Y_SET, wk->scroll );
	GF_BGL_ScrollSet( wk->bgl, SYOUJYOU_SYOU_S_FRAME, GF_BGL_SCROLL_Y_SET, wk->scroll+SUBBG_OFFS );
	GF_BGL_ScrollSet( wk->bgl, SYOUJYOU_TEXT_M_FRAME, GF_BGL_SCROLL_Y_SET, wk->scroll );
	GF_BGL_ScrollSet( wk->bgl, SYOUJYOU_TEXT_S_FRAME, GF_BGL_SCROLL_Y_SET, wk->scroll+SUBBG_OFFS );
}


//----------------------------------
//グラフィック読み込み
//----------------------------------
static void Syoujyou_GraphicLoad( SYOUJYOU_WORK* wk )
{
	int back_scrID, back_cgxID, back_palID;
	int syou_scrID, syou_cgxID, syou_palID;

	if( wk->type == SYOUJYOU_TYPE_SINOU ){
	//シンオウ
		back_scrID = NARC_syoujyou_syoujyou_s_bg_NSCR;
		back_cgxID = NARC_syoujyou_syoujyou_s_bg_NCGR; 
		back_palID = NARC_syoujyou_syoujyou_s_bg_NCLR;
		syou_scrID = NARC_syoujyou_dp_syoujyou_s_NSCR;
		syou_cgxID = NARC_syoujyou_dp_syoujyou_s_NCGR;
		syou_palID = NARC_syoujyou_dp_syoujyou_s_NCLR;
	} else {
		//全国
		back_scrID = NARC_syoujyou_syoujyou_z_bg_NSCR;
		back_cgxID = NARC_syoujyou_syoujyou_z_bg_NCGR; 
		back_palID = NARC_syoujyou_syoujyou_z_bg_NCLR;
		syou_scrID = NARC_syoujyou_dp_syoujyou_z_NSCR;
		syou_cgxID = NARC_syoujyou_dp_syoujyou_z_NCGR;
		syou_palID = NARC_syoujyou_dp_syoujyou_z_NCLR;
	}
	//背景
	ArcUtil_ScrnSet(	ARC_SYOUJYOU, back_scrID, wk->bgl, 
						SYOUJYOU_BACK_M_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_BgCharSet(	ARC_SYOUJYOU, back_cgxID, wk->bgl, 
						SYOUJYOU_BACK_M_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_PalSet(		ARC_SYOUJYOU, back_palID, PALTYPE_MAIN_BG, 
						SYOUJYOU_BACKPLT_NUM * PALSIZE, PALSIZE, wk->heapID );
	ArcUtil_ScrnSet(	ARC_SYOUJYOU, back_scrID, wk->bgl, 
						SYOUJYOU_BACK_S_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_BgCharSet(	ARC_SYOUJYOU, back_cgxID, wk->bgl, 
						SYOUJYOU_BACK_S_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_PalSet(		ARC_SYOUJYOU, back_palID, PALTYPE_SUB_BG, 
						SYOUJYOU_BACKPLT_NUM * PALSIZE, PALSIZE, wk->heapID );
	//賞状
	ArcUtil_ScrnSet(	ARC_SYOUJYOU, syou_scrID, wk->bgl, 
						SYOUJYOU_SYOU_M_FRAME, 0, 0, 0, wk->heapID );
	GF_BGL_ScrPalChange( wk->bgl, SYOUJYOU_SYOU_M_FRAME, 0, 0, 32, 24, SYOUJYOU_SYOUPLT_NUM );
	GF_BGL_LoadScreenReq( wk->bgl, SYOUJYOU_SYOU_M_FRAME );
	ArcUtil_BgCharSet(	ARC_SYOUJYOU, syou_cgxID, wk->bgl, 
						SYOUJYOU_SYOU_M_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_PalSet(		ARC_SYOUJYOU, syou_palID, PALTYPE_MAIN_BG, 
						SYOUJYOU_SYOUPLT_NUM * PALSIZE, PALSIZE, wk->heapID );
	ArcUtil_ScrnSet(	ARC_SYOUJYOU, syou_scrID, wk->bgl, 
						SYOUJYOU_SYOU_S_FRAME, 0, 0, 0, wk->heapID );
	GF_BGL_ScrPalChange( wk->bgl, SYOUJYOU_SYOU_S_FRAME, 0, 0, 32, 24, SYOUJYOU_SYOUPLT_NUM );
	GF_BGL_LoadScreenReq( wk->bgl, SYOUJYOU_SYOU_S_FRAME );
	ArcUtil_BgCharSet(	ARC_SYOUJYOU, syou_cgxID, wk->bgl, 
						SYOUJYOU_SYOU_S_FRAME, 0, 0, 0, wk->heapID );
	ArcUtil_PalSet(		ARC_SYOUJYOU, syou_palID, PALTYPE_SUB_BG, 
						SYOUJYOU_SYOUPLT_NUM * PALSIZE, PALSIZE, wk->heapID );
	//テキスト（NULLキャラ設定）
	GF_BGL_ClearCharSet( SYOUJYOU_TEXT_M_FRAME, 32, 0, wk->heapID );
	GF_BGL_ClearCharSet( SYOUJYOU_TEXT_S_FRAME, 32, 0, wk->heapID );
	//フォントパレット読み込み（システム）
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, SYOUJYOU_TEXTPLT_NUM * PALSIZE, wk->heapID );
	SystemFontPaletteLoad( PALTYPE_SUB_BG, SYOUJYOU_TEXTPLT_NUM * PALSIZE, wk->heapID );
}


//----------------------------------
//メッセージ表示
//----------------------------------
#define SYOUJYOU_STRBUF_SIZE		(0x200)	//メッセージバッファサイズ

static void Syoujyou_MsgPrint( SYOUJYOU_WORK* wk )
{
	STRBUF* msg_str = STRBUF_Create( SYOUJYOU_STRBUF_SIZE, wk->heapID );
	{//名前の表示
		STRBUF* msg_tmp = STRBUF_Create( SYOUJYOU_STRBUF_SIZE, wk->heapID );

		MSGMAN_GetString( wk->msgman, msg_l02r0301_award_01, msg_tmp );
		WORDSET_RegisterPlayerName( wk->wordset, 0, wk->my );
		WORDSET_ExpandStr( wk->wordset, msg_str, msg_tmp );
		GF_STR_PrintColor(	&wk->msgwin_m, FONT_SYSTEM, msg_str, 48, 32, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
		GF_STR_PrintColor(	&wk->msgwin_s, FONT_SYSTEM, msg_str, 48, 32, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
		STRBUF_Delete( msg_tmp );
	}
	{//本文の表示
		int		msgID;
	
		if( wk->type == SYOUJYOU_TYPE_SINOU ){
			msgID = msg_l02r0301_award_02;
		} else {
			msgID = msg_l02r0301_award_03;
		}
		MSGMAN_GetString( wk->msgman, msgID, msg_str );
		GF_STR_PrintColor(	&wk->msgwin_m, FONT_SYSTEM, msg_str, 64, 64, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
		GF_STR_PrintColor(	&wk->msgwin_s, FONT_SYSTEM, msg_str, 64, 64, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
	}
	{
		MSGMAN_GetString( wk->msgman, msg_l02r0301_award_04, msg_str );
		GF_STR_PrintColor(	&wk->msgwin_m, FONT_SYSTEM, msg_str, 138, 144, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
		GF_STR_PrintColor(	&wk->msgwin_s, FONT_SYSTEM, msg_str, 138, 144, MSG_ALLPUT, 
							GF_PRINTCOLOR_MAKE(1, 2, 0), NULL );
	}
	STRBUF_Delete( msg_str );
}



