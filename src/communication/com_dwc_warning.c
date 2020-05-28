//==============================================================================================
/**
 * @file	com_dwc_warning.c
 * @brief	ＤＷＣライブラリ警告画面
 * @author	
 * @date	
 */
//==============================================================================================
#include "common.h"

#include "system/procsys.h"
#include "system/arc_util.h"

#include "system/lib_pack.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "system/fontproc.h"
#include "msgdata/msg.naix"
#include "system/pm_str.h"
#include "system/wipe.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/palanm.h"
#include "system/wordset.h"
#include "system/pmfprint.h"
#include "system/main.h"
#include "system/brightness.h"

#include "msgdata/msg_wifi_system.h"

extern void sleepFunc(void);
//================================================================
//
//
//		
//
//
//================================================================
//ＢＧコントロール定数
#define SVERR_TEXT_FRAME	(GF_BGL_FRAME0_M)

#define SVERR_NULL_PALETTE	( 0x6c21 )		//ＢＧバックグラウンドパレット

#define	SVERR_TEXT_PALNUM	(1)
#define SVERR_NWIN_CGXNUM	(512 - MENU_WIN_CGX_SIZ)
#define SVERR_NWIN_PALNUM	(2)

#define SVERR_STRBUF_SIZE	(0x180)	//メッセージバッファサイズ
// メッセージウィンドウ
#define	SVERR_WIN_PX		(3)
#define	SVERR_WIN_PY		(3)
#define	SVERR_WIN_SX		(26)
#define	SVERR_WIN_SY		(18)
#define	SVERR_WIN_PAL		(SVERR_TEXT_PALNUM)
#define	SVERR_WIN_CGX		(SVERR_NWIN_CGXNUM-(SVERR_WIN_SX*SVERR_WIN_SY))

//================================================================
//================================================================
static const GF_BGL_DISPVRAM vramSetTable = {
	GX_VRAM_BG_256_AB,				// メイン2DエンジンのBG
	GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
	GX_VRAM_SUB_BG_NONE,			// サブ2DエンジンのBG
	GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
	GX_VRAM_OBJ_NONE,				// メイン2DエンジンのOBJ
	GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
	GX_VRAM_SUB_OBJ_NONE,			// サブ2DエンジンのOBJ
	GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
	GX_VRAM_TEX_NONE,				// テクスチャイメージスロット
	GX_VRAM_TEXPLTT_NONE			// テクスチャパレットスロット
};

static const GF_BGL_SYS_HEADER BGsys_data = {
	GX_DISPMODE_GRAPHICS,
	GX_BGMODE_0, GX_BGMODE_0,
	GX_BG0_AS_2D
};
static const GF_BGL_BGCNT_HEADER hd0 = {
	0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
	GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x18000, GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
};
static const BMPWIN_DAT windata = {
	SVERR_TEXT_FRAME,			//ウインドウ使用フレーム
	SVERR_WIN_PX,SVERR_WIN_PY,	//ウインドウ領域の左上XY座標
	SVERR_WIN_SX,SVERR_WIN_SY,	//ウインドウ領域のXYサイズ
	SVERR_WIN_PAL,				//ウインドウ領域のパレットナンバー 
	SVERR_WIN_CGX,				//ウインドウキャラ領域の開始キャラクタナンバー
};

//=================================================================================================
//
// 一括コール
//
//=================================================================================================
void DWClibWarningCall( int heapID, int error_msg_id )
{
	GF_BGL_INI*			bgl;
	GF_BGL_BMPWIN		msgwin;
	MSGDATA_MANAGER*	msgman;
	STRBUF*				msgstr;
	int msgID;

	msgID = dwc_message_0001;

	WIPE_SetBrightness( WIPE_DISP_MAIN,WIPE_FADE_BLACK );
	WIPE_SetBrightness( WIPE_DISP_SUB,WIPE_FADE_BLACK );

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrSet( NULL,NULL );		// HBlankセット

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );
	sys_KeyRepeatSpeedSet( 4, 8 );
	sys.disp3DSW = DISP_3D_TO_MAIN;
	GF_Disp_DispSelect();
	G2_BlendNone();
	G2S_BlendNone();
	GX_SetVisibleWnd( GX_WNDMASK_NONE ); 
	GXS_SetVisibleWnd( GX_WNDMASK_NONE ); 

	GF_Disp_SetBank( &vramSetTable );		//ＶＲＡＭ設定
	bgl = GF_BGL_BglIniAlloc( heapID );		//ＢＧライブラリ用メモリ確保
	GF_BGL_InitBG( &BGsys_data );			// ＢＧシステム設定
	GF_BGL_BGControlSet( bgl, SVERR_TEXT_FRAME, &hd0, GF_BGL_MODE_TEXT );// メインＢＧシステム設定
	GF_BGL_ScrClear( bgl, SVERR_TEXT_FRAME );	
	//メッセージウインドウキャラ＆パレット読み込み
	MenuWinGraphicSet( bgl, SVERR_TEXT_FRAME, SVERR_NWIN_CGXNUM, SVERR_NWIN_PALNUM, 0, heapID );
	//フォントパレット読み込み（システム）
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, SVERR_TEXT_PALNUM * (2*16), heapID );

	GF_BGL_ClearCharSet( SVERR_TEXT_FRAME, 32, 0, heapID );
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_M, SVERR_NULL_PALETTE );	//背景色初期化
	GF_BGL_BackGroundColorSet( GF_BGL_FRAME0_S, SVERR_NULL_PALETTE );	//背景色初期化
	//メッセージデータ読み込み
	msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wifi_system_dat, heapID );
	msgstr = STRBUF_Create( SVERR_STRBUF_SIZE, heapID);
	MSG_PrintInit();//メッセージ表示システム初期化
		
	GF_BGL_BmpWinAddEx( bgl, &msgwin,&windata );//ビットマップ作成
	GF_BGL_BmpWinFill( &msgwin, FBMP_COL_WHITE, 0, 0, SVERR_WIN_SX*8, SVERR_WIN_SY*8 );
	BmpMenuWinWrite( &msgwin, WINDOW_TRANS_ON, SVERR_NWIN_CGXNUM, SVERR_NWIN_PALNUM );
	
	MSGMAN_GetString( msgman, msgID, msgstr );	//文字列の取得
	GF_STR_PrintSimple(	&msgwin, FONT_SYSTEM, msgstr, 0, 0, 0, NULL );//文字列の表示
	STRBUF_Delete( msgstr );

	GF_Disp_DispOn();
	WIPE_ResetBrightness( WIPE_DISP_MAIN );
	WIPE_ResetBrightness( WIPE_DISP_SUB );
	SetBrightness( BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );

	while( 1 ){
		int	keyData = PAD_Read();

		sleepFunc();
		if( keyData & PAD_BUTTON_A ){
			break;
		}
		OS_WaitIrq(TRUE, OS_IE_V_BLANK); 	// Ｖブランク待ち
	}

	GF_BGL_BmpWinDel(&msgwin);
	MSGMAN_Delete( msgman );//メッセージデータ破棄

	GF_BGL_VisibleSet( GF_BGL_FRAME0_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME3_M, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME0_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME1_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME2_S, VISIBLE_OFF );
	GF_BGL_VisibleSet( GF_BGL_FRAME3_S, VISIBLE_OFF );
	GF_BGL_BGControlExit( bgl, SVERR_TEXT_FRAME );
	sys_FreeMemoryEz( bgl );
}



