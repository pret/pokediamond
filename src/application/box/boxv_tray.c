//============================================================================================
/**
 * @file	boxv_tray.c
 * @brief	ボックス操作画面　描画下請け（トレイ関連）
 * @author	taya
 * @date	2005.09.09
 */
//============================================================================================
#include  "common.h"
#include  "system\arc_util.h"
#include  "system\fontproc.h"
#include  "system\brightness.h"
#include  "poketool\pokeicon.h"

#include  "box_arc.h"
#include  "box_view.h"
#include  "box_common.h"

#define TRAY_CHAR_WIDTH		(21)		///< トレイ１枚の横キャラ数
#define TRAY_CHAR_HEIGHT	(20)		///< トレイ１枚の縦キャラ数
#define TRAY_WRITE_XPOS		(11)		///< トレイ描画開始Ｘ座標（初期位置）
#define TRAY_WRITE_YPOS		(0)			///< トレイ描画開始Ｙ座標（初期位置）
#define TRAY_WRITE_X_SPACE	(2)			///< トレイ描画Ｘ間隔（キャラ単位）
#define TRAY_WRITE_Y_SPACE	(4)

#define TRAY_CHAR_SIZE		(TRAY_CHAR_WIDTH*TRAY_CHAR_HEIGHT)
#define TRAY_WRITE_DIFF		(TRAY_CHAR_WIDTH + TRAY_WRITE_X_SPACE)

#define TRAY_SCROLL_LEN		(TRAY_WRITE_DIFF*8)			///< スクロール量（ドット）
#define TRAY_SCROLL_WAIT	BOX_TIMER(15)				///< スクロール時間（フレーム）
#define TRAY_FX_SHIFT		(8)
#define TRAY_FX_MASK		(0x1ff)

#define TRAY_NCG_WIDTH		(21)
#define TRAY_NCG_TAB_HEIGHT	(4)
#define TRAYNAME_WRITE_CENTER_X		(84)	// ボックス名はNCGデータに直接描く
#define TRAYNAME_WRITE_YPOS			(13)	/// [[[海外版は調整の必要あるかも]]]
#define TRAYNAME_FONTTYPE	(FONT_SYSTEM)

#define ICON_VISIBLE_MIN	(72)
#define ICON_VISIBLE_MAX	(256+16)

#define TRAY_BG_HOFS_MASK	(REG_G2_BG3HOFS_OFFSET_MASK)	// 0x1ff です

#define WPCHANGE_FADE_TIME	(15)	// 輝度変更は30fps固定にしているのでBOX_TIMERマクロを使わない

#define TRAY_SPACE_CHARNO	(0)

//--------------------------------------------------------------
/**
 * 壁紙画像のアーカイブインデックステーブル
 */
//--------------------------------------------------------------
static const struct {
	u8  nscr;
	u8  ncgr;
	u8  nclr;
}WallPaperArcID[] = {

	{ NARC_box_wp01_lz_nscr, NARC_box_wp01_lz_ncgr, NARC_box_wp01_nclr },
	{ NARC_box_wp02_lz_nscr, NARC_box_wp02_lz_ncgr, NARC_box_wp02_nclr },
	{ NARC_box_wp03_lz_nscr, NARC_box_wp03_lz_ncgr, NARC_box_wp03_nclr },
	{ NARC_box_wp04_lz_nscr, NARC_box_wp04_lz_ncgr, NARC_box_wp04_nclr },
	{ NARC_box_wp05_lz_nscr, NARC_box_wp05_lz_ncgr, NARC_box_wp05_nclr },
	{ NARC_box_wp06_lz_nscr, NARC_box_wp06_lz_ncgr, NARC_box_wp06_nclr },
	{ NARC_box_wp07_lz_nscr, NARC_box_wp07_lz_ncgr, NARC_box_wp07_nclr },
	{ NARC_box_wp08_lz_nscr, NARC_box_wp08_lz_ncgr, NARC_box_wp08_nclr },
	{ NARC_box_wp09_lz_nscr, NARC_box_wp09_lz_ncgr, NARC_box_wp09_nclr },
	{ NARC_box_wp10_lz_nscr, NARC_box_wp10_lz_ncgr, NARC_box_wp10_nclr },
	{ NARC_box_wp11_lz_nscr, NARC_box_wp11_lz_ncgr, NARC_box_wp11_nclr },
	{ NARC_box_wp12_lz_nscr, NARC_box_wp12_lz_ncgr, NARC_box_wp12_nclr },
	{ NARC_box_wp13_lz_nscr, NARC_box_wp13_lz_ncgr, NARC_box_wp13_nclr },
	{ NARC_box_wp14_lz_nscr, NARC_box_wp14_lz_ncgr, NARC_box_wp14_nclr },
	{ NARC_box_wp15_lz_nscr, NARC_box_wp15_lz_ncgr, NARC_box_wp15_nclr },
	{ NARC_box_wp16_lz_nscr, NARC_box_wp16_lz_ncgr, NARC_box_wp16_nclr },

	{ NARC_box_wpex01_lz_nscr, NARC_box_wpex01_lz_ncgr, NARC_box_wpex01_nclr },
	{ NARC_box_wpex02_lz_nscr, NARC_box_wpex02_lz_ncgr, NARC_box_wpex02_nclr },
	{ NARC_box_wpex03_lz_nscr, NARC_box_wpex03_lz_ncgr, NARC_box_wpex03_nclr },
	{ NARC_box_wpex04_lz_nscr, NARC_box_wpex04_lz_ncgr, NARC_box_wpex04_nclr },
	{ NARC_box_wpex05_lz_nscr, NARC_box_wpex05_lz_ncgr, NARC_box_wpex05_nclr },
	{ NARC_box_wpex06_lz_nscr, NARC_box_wpex06_lz_ncgr, NARC_box_wpex06_nclr },
	{ NARC_box_wpex07_lz_nscr, NARC_box_wpex07_lz_ncgr, NARC_box_wpex07_nclr },
	{ NARC_box_wpex08_lz_nscr, NARC_box_wpex08_lz_ncgr, NARC_box_wpex08_nclr },

};

//--------------------------------------------------------------
/**
 * パレット転送オフセット
 */
//--------------------------------------------------------------
static const u16 PalettePosTbl[] = {
	PAL_MAIN_WALLPAPER_A,
	PAL_MAIN_WALLPAPER_B,
};


//==============================================================
// Prototype
//==============================================================
static void GetTrayGraphicTransPos( const TRAY_VIEW_WORK* wk, int vector, u32* charPos, u32* scrnPos, u32* palPos );
static void LoadWallPaperPalette( TRAY_VIEW_WORK* wk, const BOXAPP_TRAY* trayParam, int pos, BOOL transFlag );
static void LoadWallPaperCgx( TRAY_VIEW_WORK* wk, const BOXAPP_TRAY* trayParam, int ofs );
static void LoadWallPaperScreen( TRAY_VIEW_WORK* wk, const BOXAPP_TRAY* trayParam, u32 scrnPos, u32 charOfs, u32 palPos );
static void TrayScrollTask( TCB_PTR tcb, void* wk_adrs );
static void TrayScrollVintrTask( TCB_PTR tcb, void* wk_adrs );
static void SetScrollIconPos( TRAY_VIEW_WORK* wk, fx32 scrollValue, s32 xofs );
static void AddScrollIconPos( TRAY_VIEW_WORK* wk, fx32 scrollValue );
static void AddScrollLineIcon( TRAY_VIEW_WORK* wk, BOX_ICON_WORK* iconwk, int xpos, int column );
static void DelScrollLineIcon( TRAY_VIEW_WORK* wk, BOX_ICON_WORK* iconwk, int column );
static void ReadIconCharData( TRAY_VIEW_WORK* wk, u32 trayno );
static void SetupWallPaperBrightChangeTask( TRAY_VIEW_WORK* wk, int start, int end, u32 transOffs );
static void WallPaperBrightChangeTask( TCB_PTR tcb, void* wk_adrs );
static void WallPaperBrightWorkFreeCallback( void* wk_adrs );
static void WallPaperGraphicTransTask( TCB_PTR tcb, void* wk_adrs );
static void SetupWallPaperGraphicTransTask( TRAY_VIEW_WORK* wk );
static u32 GetIconActorPri( u32 pos );
static void AddTrayIcon( TRAY_VIEW_WORK* wk, BOX_ICON_SYS* iconSys, u32 box, u32 vramPos, s32 xofs, BOX_ICON_WORK* icon );
static void IconScrollOut( TRAY_VIEW_WORK* wk, BOX_ICON_WORK* icon, u32 vcnt );
static void IconScrollIn( TRAY_VIEW_WORK* wk, BOX_ICON_WORK* icon, u32 vcnt );
static void IconScrollEnd( TRAY_VIEW_WORK* wk, BOX_ICON_WORK* icon );
static void TrayScrnWrite( u16* dst, const u16* src, u32 xpos, u32 charOfs, u32 palPos );


//==============================================================================================================
// メインモジュールから呼ばれる初期化・終了関連
//==============================================================================================================

//------------------------------------------------------------------
/**
 * 初期化
 *
 * @param   wk			
 * @param   vpara		
 * @param   bgl			
 * @param   actsys		
 *
 * @retval  BOOL		TRUEで成功
 */
//------------------------------------------------------------------
BOOL BoxAppView_TrayInit( TRAY_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys )
{
	extern void GF_BGL_GGFLG_Set(void);
	wk->trayNum = vpara->tray.number;
	wk->scrnPos = TRAY_WRITE_XPOS;
	wk->imgPos = 0;


	wk->scrollXofs = BoxAppView_GetTrayScrollOfs( vwk );
	wk->iconVisibleXmin = ICON_VISIBLE_MIN + wk->scrollXofs;
	wk->iconVisibleXmax = ICON_VISIBLE_MAX + wk->scrollXofs;

	wk->iconSys = BoxAppView_GetIconSysWork( vwk );
	BoxAppView_IconWorkInit( wk->iconSys, wk->icon[0], BOX_MAX_POS );
	BoxAppView_IconWorkInit( wk->iconSys, wk->icon[1], BOX_MAX_POS );

	wk->bgl = bgl;
	wk->vpara = vpara;
	wk->vwk = vwk;

	return TRUE;
}

//------------------------------------------------------------------
/**
 * 終了
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_TrayQuit( TRAY_VIEW_WORK* wk )
{
	BoxAppView_IconWorkQuit( wk->iconSys, wk->icon[0], BOX_MAX_POS );
	BoxAppView_IconWorkQuit( wk->iconSys, wk->icon[1], BOX_MAX_POS );
}


//==============================================================================================================
// メインモジュールから呼ばれるコマンド処理関数群
//==============================================================================================================

//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_TraySetup( TRAY_VIEW_WORK* wk )
{
	wk->scrollSetPos = GF_BGL_ScrollGetX(wk->bgl, FRM_MAIN_TRAY);
	wk->scrollSetPos -= wk->scrollXofs;
	wk->scrollSetPos &= TRAY_BG_HOFS_MASK;
	GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_TRAY, GF_BGL_SCROLL_X_SET, wk->scrollSetPos );

	GF_BGL_ScrFill( wk->bgl, FRM_MAIN_TRAY, 0x0018, 0, 0, 64, 32, PAL_MAIN_WALLPAPER_A );
}


//------------------------------------------------------------------
/**
 * 壁紙グラフィック転送位置を取得
 *
 * @param   wk			[in]  トレイ描画ワーク
 * @param   vector		[in]  転送方向（0:現在表示 1:右隣 -1:左隣）
 * @param   charPos		[out] キャラ転送位置（バンク先頭からキャラ単位オフセット）
 * @param   scrnPos		[out] スクリーン書き出し開始Ｘ座標
 * @param   palPos		[out] パレット転送先（0～F）
 *
 */
//------------------------------------------------------------------
static void GetTrayGraphicTransPos( const TRAY_VIEW_WORK* wk, int vector, u32* charPos, u32* scrnPos, u32* palPos )
{
	if( vector != 0 )
	{
		*charPos = (wk->imgPos^1) * TRAY_CHAR_SIZE;
		*scrnPos = (wk->scrnPos + (vector * TRAY_WRITE_DIFF)) & 63;
		*palPos = PalettePosTbl[ wk->imgPos^1 ];
	}
	else
	{
		*charPos = wk->imgPos * TRAY_CHAR_SIZE;
		*scrnPos = wk->scrnPos;
		*palPos = PalettePosTbl[ wk->imgPos ];;
	}
}

//------------------------------------------------------------------------------
/**
 * トレイ壁紙グラフィックのVRAM転送
 *
 * @param   wk				トレイ描画ワーク
 * @param   trayParam		壁紙ナンバー
 * @param   pos				転送位置（0:現在表示 1:右隣 -1:左隣）
 * @param   completeFlag	TRUEだとﾊﾟﾚｯﾄﾃﾞｰﾀのVRAM転送，アイコン作成まで行う。FALSEだと両方やらない
 *
 */
//------------------------------------------------------------------------------
void BoxAppView_TrayWrite( TRAY_VIEW_WORK* wk, const BOXAPP_TRAY* trayParam, int pos, BOOL completeFlag )
{
	u32 charOfs, scrnPos, palPos;

	GetTrayGraphicTransPos( wk, pos, &charOfs, &scrnPos, &palPos );

	LoadWallPaperPalette( wk, trayParam, palPos, completeFlag );
	LoadWallPaperCgx( wk, trayParam, charOfs );
	LoadWallPaperScreen( wk, trayParam, scrnPos, charOfs, palPos );

	if( completeFlag )
	{
		// 表示中トレイには普通に全描画する
		if( pos == 0 )
		{
			AddTrayIcon( wk, wk->iconSys, trayParam->number, wk->imgPos, pos*TRAY_SCROLL_LEN, wk->icon[wk->imgPos] );
		}
	}
}

//------------------------------------------------------------------
/**
 * 壁紙ﾊﾟﾚｯﾄﾃﾞｰﾀを読み込み、フェード用の加工をしてワークに保存。必要あればVram転送も行う
 *
 * @param   wk				ワークポインタ
 * @param   trayParam		トレイパラメータ
 * @param   pos				転送先パレットナンバ
 * @param   transFlag		転送フラグ
 */
//------------------------------------------------------------------
static void LoadWallPaperPalette( TRAY_VIEW_WORK* wk, const BOXAPP_TRAY* trayParam, int pos, BOOL transFlag )
{
	NNSG2dPaletteData* palData;
	void* loadPtr;

	// パレットデータは転送後、フェードに必要なデータを作成して保存しておく
	loadPtr = ArcUtil_PalDataGet(ARC_BOX_GRA, WallPaperArcID[trayParam->wallPaper].nclr, &palData, HEAPID_BOX_VIEW);
	if(loadPtr)
	{
		int i;
		fx32  step;

		if( transFlag )
		{
			DC_FlushRange( palData->pRawData, 0x20 );
			GX_LoadBGPltt( palData->pRawData, pos*0x20, 0x20);
		}

		for(i=0, step=0; i<TRAY_WALLPAPER_FADE_STEPS; i++)
		{
			BoxAppView_PalFade( palData->pRawData, wk->wallpaperFadePalette[i], 16, 0x7fff, (step>>FX32_SHIFT) );
			step += ( (16<<FX32_SHIFT) / TRAY_WALLPAPER_FADE_STEPS );
		}
		BoxAppView_PalFade( palData->pRawData, wk->wallpaperFadePalette[i], 16, 0x7fff, 16 );
		DC_FlushRange( wk->wallpaperFadePalette, sizeof(wk->wallpaperFadePalette) );

		sys_FreeMemoryEz(loadPtr);
	}
}
//------------------------------------------------------------------
/**
 * 壁紙cgxデータを読み込み、転送
 *
 * @param   wk		
 * @param   trayParam		
 * @param   pos		
 *
 */
//------------------------------------------------------------------
static void LoadWallPaperCgx( TRAY_VIEW_WORK* wk, const BOXAPP_TRAY* trayParam, int ofs )
{
	void* loadPtr;
	// キャラデータは読み込んだあとBitmapWin機能を使ってトレイ名を描きこみ、それを転送する
	loadPtr = ArcUtil_Load(ARC_BOX_GRA, WallPaperArcID[trayParam->wallPaper].ncgr, TRUE, HEAPID_BOX_VIEW, ALLOC_BOTTOM);
	if( loadPtr != NULL ){
		NNSG2dCharacterData* charData;

		if( NNS_G2dGetUnpackedBGCharacterData( loadPtr, &charData ) )
		{
			GF_BGL_BMPWIN* win;

			win = GF_BGL_BmpWinAllocGet(HEAPID_BOX_VIEW, 1);
			if( win )
			{
				u32 xpos, strwidth;

				win->ini = wk->bgl;
				win->sizx = TRAY_NCG_WIDTH;
				win->sizy = TRAY_NCG_TAB_HEIGHT;
				win->chrbuf = charData->pRawData;

				strwidth = FontProc_GetPrintStrWidth( TRAYNAME_FONTTYPE, trayParam->name, 0 );
				xpos = TRAYNAME_WRITE_CENTER_X - ( strwidth / 2 );

				GF_STR_PrintColor( win, FONT_SYSTEM, trayParam->name, xpos, TRAYNAME_WRITE_YPOS, MSG_NO_PUT,
						GF_PRINTCOLOR_MAKE(2,1,0), NULL );

				sys_FreeMemoryEz( win );
			}
			GF_BGL_LoadCharacter(wk->bgl, FRM_MAIN_TRAY, charData->pRawData, charData->szByte, ofs);
		}
		sys_FreeMemoryEz( loadPtr );
	}
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 * @param   trayParam		
 * @param   scrnPos		
 * @param   charOfs		
 * @param   palPos		
 *
 */
//------------------------------------------------------------------
static void LoadWallPaperScreen( TRAY_VIEW_WORK* wk, const BOXAPP_TRAY* trayParam, u32 scrnPos, u32 charOfs, u32 palPos )
{
	void* scrnSrc;

	// スクリーンデータは読み込んだ後、キャラ＆パレット位置に応じて書き換えて転送
	scrnSrc = ArcUtil_Load(ARC_BOX_GRA, WallPaperArcID[trayParam->wallPaper].nscr, TRUE, HEAPID_BOX_VIEW, ALLOC_BOTTOM);
	if( scrnSrc )
	{
		u16 *scrnDst;
		NNSG2dScreenData* scrnData;

		NNS_G2dGetUnpackedScreenData( scrnSrc, &scrnData );
		scrnDst = GF_BGL_ScreenAdrsGet( wk->bgl, FRM_MAIN_TRAY );

		if(scrnDst)
		{
			TrayScrnWrite( scrnDst, (const u16*)(scrnData->rawData), scrnPos, charOfs, palPos );
		}
		sys_FreeMemoryEz(scrnSrc);

		GF_BGL_LoadScreen( wk->bgl, FRM_MAIN_TRAY, scrnDst, 0x1000, 0 );
	}

}

//------------------------------------------------------------------------------
/**
 * トレイスクロール開始
 *
 * @param   wk			トレイ描画ワーク
 * @param   direction	方向（1:右へ -1:左へ）
 *
 */
//------------------------------------------------------------------------------
void BoxAppView_TrayScrollSet( TRAY_VIEW_WORK* wk, const BOXAPP_TRAY* trayParam, int direction )
{
	wk->scrollPos = (GF_BGL_ScrollGetX(wk->bgl, FRM_MAIN_TRAY) & TRAY_BG_HOFS_MASK) << FX32_SHIFT;;
	wk->scrollEndPos = wk->scrollPos + ((TRAY_SCROLL_LEN * direction) << FX32_SHIFT);
	wk->scrollValue = (wk->scrollEndPos - wk->scrollPos) / TRAY_SCROLL_WAIT;
	wk->scrollEndPos >>= FX32_SHIFT;
	wk->scrollEndPos &= TRAY_BG_HOFS_MASK;
	wk->scrollWait = TRAY_SCROLL_WAIT;
	wk->scrollOutIcon = wk->imgPos;


	// スクロールした後は画像転送位置が変わる
	wk->scrnPos += (TRAY_WRITE_DIFF * direction);
	wk->scrnPos &= 63;
	wk->imgPos ^= 1;

	{
		ReadIconCharData( wk, trayParam->number );
		SetScrollIconPos( wk, wk->scrollValue, direction * TRAY_SCROLL_LEN );
		wk->scrollInTrayNumber = trayParam->number;
		wk->scrollInIconVramPos = wk->imgPos;
	}

	wk->scrollIconVcnt = 1;
	wk->scrollEndFlag = FALSE;


	TCB_Add( TrayScrollTask, wk, TASKPRI_VIEW_COMMAND_SUB );
	BoxAppView_VTaskAdd( TrayScrollVintrTask, wk, TASKPRI_V_MAIN );
}
//------------------------------------------------------------------------------
/**
 * トレイスクロール終了待ち
 *
 * @param   wk			トレイ描画ワーク
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------------------
BOOL BoxAppView_TrayScrollWait( TRAY_VIEW_WORK* wk )
{
	return wk->scrollEndFlag;
}

//------------------------------------------------------------------
/**
 * トレイスクロールメインタスク
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void TrayScrollTask( TCB_PTR tcb, void* wk_adrs )
{
	TRAY_VIEW_WORK* wk = (TRAY_VIEW_WORK*)wk_adrs;

	if( wk->scrollWait )
	{
		if( wk->scrollIconVcnt == 2 )
		{
			AddScrollIconPos( wk, wk->scrollValue );
			wk->scrollIconVcnt = 0;
		}
		return;
	}
	wk->scrollSetPos = wk->scrollEndPos;
	wk->trayNum = BoxAppVPara_GetTrayBoxNumber( wk->vpara );
	TCB_Delete( tcb );
	wk->scrollEndFlag = TRUE;

}

//------------------------------------------------------------------
/**
 * トレイスクロールVBlankタスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void TrayScrollVintrTask( TCB_PTR tcb, void* wk_adrs )
{
	TRAY_VIEW_WORK* wk = (TRAY_VIEW_WORK*)wk_adrs;
	u32 out, in;

	out = wk->scrollOutIcon;
	in = out ^ 1;

	if( wk->scrollWait )
	{
		if( wk->scrollIconVcnt < 2 )
		{
			IconScrollOut( wk, wk->icon[out], wk->scrollIconVcnt );
			IconScrollIn( wk, wk->icon[in], wk->scrollIconVcnt );
			wk->scrollIconVcnt++;

			wk->scrollSetPos = (wk->scrollPos >> FX32_SHIFT) & TRAY_BG_HOFS_MASK;
			wk->scrollPos += wk->scrollValue;
			GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_TRAY, GF_BGL_SCROLL_X_SET, wk->scrollSetPos );

			wk->scrollWait--;
		}
	}
	else
	{
		GF_BGL_ScrollSet( wk->bgl, FRM_MAIN_TRAY, GF_BGL_SCROLL_X_SET, wk->scrollEndPos );
		IconScrollEnd( wk, wk->icon[in] );
		TCB_Delete( tcb );
	}
}


//------------------------------------------------------------------
/**
 * スクロールするアイコンの位置のみ計算してワークに保存
 *
 * @param   wk			ワークポインタ
 * @param   xofs		描画Ｘ座標オフセット
 *
 */
//------------------------------------------------------------------
static void SetScrollIconPos( TRAY_VIEW_WORK* wk, fx32 scrollValue, s32 xofs )
{
	int x, intX;

	for( x = 0; x < BOX_MAX_COLUMN; x++ )
	{
		wk->scrollOutIconXpos[0][x] = (ICON_TRAY_XORG + wk->scrollXofs + ICON_TRAY_XSPC * x) * FX32_ONE;
		wk->scrollOutIconXpos[1][x] = wk->scrollOutIconXpos[0][x] - scrollValue;

		wk->scrollInIconXpos[0][x] = (ICON_TRAY_XORG + wk->scrollXofs + ICON_TRAY_XSPC * x + xofs) * FX32_ONE;
		wk->scrollInIconXpos[1][x] = wk->scrollInIconXpos[0][x] - scrollValue;

		intX = wk->scrollInIconXpos[1][x] >> FX32_SHIFT;
		if(intX > wk->iconVisibleXmin && intX < wk->iconVisibleXmax)
		{
			int in = wk->scrollOutIcon ^ 1;
			AddScrollLineIcon( wk, wk->icon[in], intX, x );
		}
	}
}

static void AddScrollIconPos( TRAY_VIEW_WORK* wk, fx32 scrollValue )
{
	int x, intX, in, out;

	out = wk->scrollOutIcon;
	in = out ^ 1;

	for( x = 0; x < BOX_MAX_COLUMN; x++ )
	{
		// 前フレームで表示範囲外に消えているアイコンは削除
		intX = wk->scrollOutIconXpos[1][x] >> FX32_SHIFT;
		if(intX <= wk->iconVisibleXmin || intX >= wk->iconVisibleXmax)
		{
			DelScrollLineIcon( wk, wk->icon[out], x );
		}

		wk->scrollOutIconXpos[0][x] = wk->scrollOutIconXpos[1][x] - scrollValue;
		wk->scrollOutIconXpos[1][x] = wk->scrollOutIconXpos[0][x] - scrollValue;

		wk->scrollInIconXpos[0][x] = wk->scrollInIconXpos[1][x] - scrollValue;
		wk->scrollInIconXpos[1][x] = wk->scrollInIconXpos[0][x] - scrollValue;

		intX = wk->scrollInIconXpos[1][x] >> FX32_SHIFT;
		if(intX > wk->iconVisibleXmin && intX < wk->iconVisibleXmax)
		{
			AddScrollLineIcon( wk, wk->icon[in], intX, x );
		}
	}
}


static void AddScrollLineIcon( TRAY_VIEW_WORK* wk, BOX_ICON_WORK* iconwk, int xpos, int column )
{
	const BOX_DATA* boxData;
	POKEMON_PASO_PARAM* ppp;
	int y, pos;
	u32 charno;

	boxData = BoxAppVPara_GetBoxData( wk->vpara );
	charno = (OBJCHAR_TRAY_ICON_POS + (wk->scrollInIconVramPos * OBJCHAR_TRAY_ICON_HALF_SIZE)) + column * BOXICON_CHAR_SIZE;
	iconwk += column;
	pos = column;

	for( y = 0; y < BOX_MAX_RAW; y++)
	{
		if( iconwk->act == NULL )
		{
			ppp = BOXDAT_GetPokeDataAddress( boxData, wk->scrollInTrayNumber, pos );
			if( PokePasoParaGet(ppp, ID_PARA_poke_exist, NULL) )
			{
				BoxAppView_IconAddCharSet( wk->iconSys, ppp, wk->iconMonsNo[pos], wk->iconArcIdx[pos], wk->iconCharBuf[pos],
						xpos,
						ICON_TRAY_YORG + ICON_TRAY_YSPC * y,
						BGPRI_TRAY_ICON, GetIconActorPri(pos), charno, 
						iconwk
				);
			}
		}
		charno += (BOX_MAX_COLUMN*BOXICON_CHAR_SIZE);
		iconwk += BOX_MAX_COLUMN;
		pos += BOX_MAX_COLUMN;
	}
}

static void DelScrollLineIcon( TRAY_VIEW_WORK* wk, BOX_ICON_WORK* iconwk, int column )
{
	int y;

	iconwk += column;

	for( y = 0; y < BOX_MAX_RAW; y++)
	{
		if(iconwk->act != NULL)
		{
			CLACT_Delete( iconwk->act );
			iconwk->act = NULL;
		}
		iconwk += BOX_MAX_COLUMN;
	}

}

static void ReadIconCharData( TRAY_VIEW_WORK* wk, u32 trayno )
{
	const BOX_DATA* boxData;
	POKEMON_PASO_PARAM* ppp;
	u32 pos, monsno;

	boxData = BoxAppVPara_GetBoxData( wk->vpara );

	for( pos = 0; pos < BOX_MAX_POS; pos++ )
	{
		ppp = BOXDAT_GetPokeDataAddress( boxData, trayno, pos );
		monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
		if( monsno )
		{
			wk->iconMonsNo[pos] = monsno;
			wk->iconArcIdx[pos] = PokeIconCgxArcIndexGet( ppp );
			BoxAppView_IconCharDataLoad( wk->iconSys, wk->iconCharBuf[pos], wk->iconArcIdx[pos], BOXICON_CHARBUF_SIZE );
		}
	} 
}



//--------------------------------------
/**
 * 壁紙輝度変更タスク用ワーク
 */
//--------------------------------------
typedef struct {
	TRAY_VIEW_WORK*  parent;
	s16              step;
	s16              end;
	s16              add;
	s16              wait;
	u32              offs;
}WALLPAPER_BRIGHTCHANGE_WORK;

enum {
	WALLPAPER_BRIGHTCHANGE_STEP_WAIT = 2,	// １ステップごとにこれだけウェイト入れる
};


static void SetupWallPaperBrightChangeTask( TRAY_VIEW_WORK* wk, int start, int end, u32 transOffs )
{
	WALLPAPER_BRIGHTCHANGE_WORK*  twk;

	wk->wp_taskFlag = FALSE;
	twk = sys_AllocMemory(HEAPID_BOX_VIEW, sizeof(WALLPAPER_BRIGHTCHANGE_WORK));
	if( twk )
	{
		twk->parent = wk;
		twk->step = start;
		twk->end = end;
		twk->offs = transOffs;
		twk->wait = WALLPAPER_BRIGHTCHANGE_STEP_WAIT;
		twk->add = ( end > start )? 1 : -1;

		if( BoxAppView_VTaskAdd( WallPaperBrightChangeTask, twk, TASKPRI_V_SUB ) != NULL )
		{
			wk->wp_taskFlag = TRUE;
		}
		else
		{
			sys_FreeMemoryEz(twk);
		}
	}
}

static void WallPaperBrightChangeTask( TCB_PTR tcb, void* wk_adrs )
{
	WALLPAPER_BRIGHTCHANGE_WORK* wk = wk_adrs;

	if( wk->wait )
	{
		wk->wait--;
	}
	else
	{
		if( wk->step != wk->end )
		{
			wk->step += wk->add;
			GX_LoadBGPltt( wk->parent->wallpaperFadePalette[wk->step], wk->offs, 0x20 );
			wk->wait = WALLPAPER_BRIGHTCHANGE_STEP_WAIT;
		}
		else
		{
			BoxAppView_IrqMemoryFreeReq( wk, WallPaperBrightWorkFreeCallback, wk->parent );
			TCB_Delete(tcb);
		}
	}

}


static void WallPaperBrightWorkFreeCallback( void* wk_adrs )
{
	TRAY_VIEW_WORK* wk = wk_adrs;
	wk->wp_taskFlag = FALSE;
}


static int TSEQ=0;


static void WallPaperGraphicTransTask( TCB_PTR tcb, void* wk_adrs )
{
	static u32 charOfs=0, scrnPos=0, palPos=0;
	static const BOXAPP_TRAY* trayParam = NULL;
	TRAY_VIEW_WORK* wk = wk_adrs;

	switch( TSEQ ){
	case 0:
		GetTrayGraphicTransPos( wk, 0, &charOfs, &scrnPos, &palPos );
		trayParam = BoxAppVpara_GetTrayData( wk->vpara );

		LoadWallPaperPalette( wk, trayParam, palPos, FALSE );
		TSEQ++;
		break;

	case 1:
		LoadWallPaperScreen( wk, trayParam, scrnPos, charOfs, palPos );
		LoadWallPaperCgx( wk, trayParam, charOfs );
		TSEQ++;
		break;

	case 2:
		wk->wp_taskFlag = FALSE;
		TSEQ = 0;
		TCB_Delete( tcb );
		break;
	}
}

static void SetupWallPaperGraphicTransTask( TRAY_VIEW_WORK* wk )
{
	wk->wp_taskFlag = ( VWaitTCB_Add( WallPaperGraphicTransTask, wk, 0 ) != NULL );
	if( wk->wp_taskFlag )
	{
		TSEQ = 0;
	}
}


//------------------------------------------------------------------------------
/**
 * 壁紙変更開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------------------
void BoxAppView_TrayChangeWallPaperStart( TRAY_VIEW_WORK* wk )
{
	wk->wpseq = 0;
	SetupWallPaperBrightChangeTask(wk, 0, TRAY_WALLPAPER_FADE_STEPS, PalettePosTbl[wk->imgPos]*0x20);
}
//------------------------------------------------------------------------------
/**
 * 壁紙変更終了待ち
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------------------
BOOL BoxAppView_TrayChangeWallPaperWait( TRAY_VIEW_WORK* wk )
{
	switch( wk->wpseq ){
	case 0:
		if( wk->wp_taskFlag == FALSE )
		{
			wk->wpseq++;
		}
		break;

	case 1:
		// ↓壁紙書き込みをいっぺんにやると、パシることがある。
		//   Pal,Cgx,Scrn の３要素に分割して処理を行った方が良いかも？？
		SetupWallPaperGraphicTransTask( wk );
//		BoxAppView_TrayWrite( wk, BoxAppVpara_GetTrayData( wk->vpara ), 0, FALSE );
		wk->wpseq++;
		break;

	case 2:
		if( wk->wp_taskFlag == FALSE )
		{
			wk->wpseq++;
		}
		break;

	case 3:
		SetupWallPaperBrightChangeTask(wk, TRAY_WALLPAPER_FADE_STEPS, 0, PalettePosTbl[wk->imgPos]*0x20);
		wk->wpseq++;
		break;

	case 4:
		if( wk->wp_taskFlag == FALSE )
		{
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//------------------------------------------------------------------------------
/**
 * カレントディレクトリの指定位置アイコンデータをバッファに移動させる
 *
 * @param   wk		ワークポインタ
 * @param   pos		ボックス内の位置
 * @param   charpos	新しいキャラデータ転送先（領域先頭からのキャラ単位オフセット）／マイナスならそのままにする
 * @param   dst		アイコンデータ移動先
 *
 */
//------------------------------------------------------------------------------
void BoxAppView_TrayMoveIconData( TRAY_VIEW_WORK* wk, u32 pos, s32 charpos, BOX_ICON_WORK* dst )
{
	BoxAppView_IconWorkCopy( &wk->icon[wk->imgPos][pos], dst, 1 );
	BoxAppView_Icon_ResetImageBank( wk->iconSys, dst, charpos );
	BoxAppView_IconWorkInit( wk->iconSys, &wk->icon[wk->imgPos][pos], 1 );
}

//------------------------------------------------------------------------------
/**
 * アイコンデータをカレントの指定位置バッファに移動させる
 *
 * @param   wk		
 * @param   pos		
 * @param   dst		
 *
 */
//------------------------------------------------------------------------------
void BoxAppView_TrayPutIconData( TRAY_VIEW_WORK* wk, u32 pos, const BOX_ICON_WORK* srcIcon )
{
	u32 charpos;
	BOX_ICON_WORK* dstIcon;

	charpos = OBJCHAR_TRAY_ICON_POS + (wk->imgPos * OBJCHAR_TRAY_ICON_HALF_SIZE) + (BOXICON_CHAR_SIZE * pos);
	dstIcon = &wk->icon[wk->imgPos][pos];
	BoxAppView_IconWorkCopy( srcIcon, dstIcon, 1 );
	BoxAppView_IconAreaSelectPalSet( wk->iconSys, dstIcon, FALSE );
	BoxAppView_Icon_ResetImageBank( wk->iconSys, dstIcon, charpos );
	BoxAppView_ChangeDrawPriority( dstIcon->act, GetIconActorPri(pos) );
}
//------------------------------------------------------------------------------
/**
 * カレント指定位置のアイコンデータポインタを返す
 *
 * @param   wk		
 * @param   pos		
 * @param   dst		
 *
 */
//------------------------------------------------------------------------------
BOX_ICON_WORK* BoxAppView_TrayGetIconData( TRAY_VIEW_WORK* wk, u32 pos )
{
	return &wk->icon[wk->imgPos][pos];
}

//------------------------------------------------------------------------------
/**
 * 現在のカレントボックスデータを見て新しく追加されたポケモンのアイコンを作る
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------------------
void BoxAppView_TrayUpdateIcon( TRAY_VIEW_WORK* wk )
{
	int i, current;
	POKEMON_PASO_PARAM* ppp;

	current = BOXDAT_GetCureentTrayNumber( wk->vpara->boxData );

	for(i=0; i<BOX_MAX_POS; i++)
	{
		ppp = BOXDAT_GetPokeDataAddress( wk->vpara->boxData, current, i );
		if( PokePasoParaGet( ppp, ID_PARA_poke_exist, NULL ) )
		{
			if(wk->icon[wk->imgPos][i].act == NULL)
			{
				int x, y, charpos;

				y = i / BOX_MAX_COLUMN;
				x = i % BOX_MAX_COLUMN;
				charpos = (OBJCHAR_TRAY_ICON_POS + (wk->imgPos * OBJCHAR_TRAY_ICON_HALF_SIZE))
						+ (BOXICON_CHAR_SIZE*i);

				BoxAppView_IconAdd( wk->iconSys, ppp,
						ICON_TRAY_XORG + wk->scrollXofs + ICON_TRAY_XSPC * x,
						ICON_TRAY_YORG + ICON_TRAY_YSPC * y,
						BGPRI_TRAY_ICON, GetIconActorPri(i), charpos, 
						&(wk->icon[wk->imgPos][i])
				);
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * トレイ内の位置からアイコンアクターのプライオリティを返す
 *
 * @param   pos		トレイ内位置
 *
 * @retval  u32		アクタープライオリティ
 */
//------------------------------------------------------------------
static u32 GetIconActorPri( u32 pos )
{
	static const u16 pri[BOX_MAX_POS] = {
		 5, 4, 3, 2, 1, 0,
		11,10, 9, 8, 7, 6,
		17,16,15,14,13,12,
		23,22,21,20,19,18,
		29,28,27,26,25,24,
	};

	return ACTPRI_TRAY_ICON_MIN + pri[pos];
}
//------------------------------------------------------------------------------
/**
 * 指定ボックスアイコン全描画
 *
 * @param   wk			ワークポインタ
 * @param   iconSys		アイコンシステムポインタ
 * @param   box			ボックスナンバー
 * @param   vramPos		ncgデータの転送先VRAM（0 or 1）
 * @param   xofs		描画Ｘ座標オフセット
 * @param   icon		アイコン作成先ワークポインタ（１ボックス分以上の配列！）
 *
 */
//------------------------------------------------------------------------------
static void AddTrayIcon( TRAY_VIEW_WORK* wk, BOX_ICON_SYS* iconSys, u32 box, u32 vramPos, s32 xofs, BOX_ICON_WORK* icon )
{
	POKEMON_PASO_PARAM* ppp;
	u32 monsno, x, y, pos, charpos;
	u64 timePara, timeIcon;

	charpos = (OBJCHAR_TRAY_ICON_POS + (vramPos * OBJCHAR_TRAY_ICON_HALF_SIZE));
	pos = 0;

	for( y = 0; y < BOX_MAX_RAW; y++ )
	{
		for( x = 0; x < BOX_MAX_COLUMN; x++ )
		{
			ppp = BOXDAT_GetPokeDataAddress( iconSys->vpara->boxData, box, pos );
			monsno = PokePasoParaGet( (POKEMON_PASO_PARAM*)ppp, ID_PARA_monsno, NULL );
			if( monsno != 0 )
			{
				BoxAppView_IconAdd( iconSys, ppp,
						ICON_TRAY_XORG + wk->scrollXofs + ICON_TRAY_XSPC * x + xofs,
						ICON_TRAY_YORG + ICON_TRAY_YSPC * y,
						BGPRI_TRAY_ICON, GetIconActorPri(pos), charpos, 
						icon
				);
			}
			icon++;
			pos++;
			charpos += BOXICON_CHAR_SIZE;
		}
	}
}


//------------------------------------------------------------------
/**
 * アイコンスクロール処理（画面から出て行く）
 *
 * @param   val			スクロール移動量
 * @param   icon		アイコンワーク
 *
 */
//------------------------------------------------------------------
static void IconScrollOut( TRAY_VIEW_WORK* wk, BOX_ICON_WORK* icon, u32 vcnt )
{
	VecFx32 vector;
	int x, y;

	for( y = 0; y < BOX_MAX_RAW; y++ )
	{
		for(x = 0; x < BOX_MAX_COLUMN; x++)
		{
			if( icon->act != NULL )
			{
				vector = *(CLACT_GetMatrix(icon->act));
				vector.x = wk->scrollOutIconXpos[vcnt][x];
				CLACT_SetMatrix(icon->act, &vector);
			}
			icon++;
		}
	}
}
//------------------------------------------------------------------
/**
 * アイコンスクロール処理（画面に入ってくる）
 *
 * @param   val			スクロール移動量
 * @param   icon		アイコンワーク
 *
 */
//------------------------------------------------------------------
static void IconScrollIn( TRAY_VIEW_WORK* wk, BOX_ICON_WORK* icon, u32 vcnt )
{
	VecFx32 vector;
	int x, y;

	for( y = 0; y < BOX_MAX_RAW; y++ )
	{
		for(x = 0; x < BOX_MAX_COLUMN; x++)
		{
			if( icon->act != NULL )
			{
				vector = *(CLACT_GetMatrix(icon->act));
				vector.x = wk->scrollInIconXpos[vcnt][x];
				CLACT_SetMatrix(icon->act, &vector);
			}
			icon++;
		}
	}
}
//------------------------------------------------------------------
/**
 * アイコンスクロール後の位置に整列
 *
 * @param   icon		アイコンワーク
 *
 */
//------------------------------------------------------------------
static void IconScrollEnd( TRAY_VIEW_WORK* wk, BOX_ICON_WORK* icon )
{
	VecFx32 vector;
	int x, y, i;

	vector.z = 0;
	for(y = 0; y < BOX_MAX_RAW; y++)
	{
		vector.y = (ICON_TRAY_YORG + y * ICON_TRAY_YSPC) * FX32_ONE;

		for(x = 0; x < BOX_MAX_COLUMN; x++)
		{
			vector.x = (ICON_TRAY_XORG + wk->scrollXofs + x * ICON_TRAY_XSPC) * FX32_ONE;
			if( icon->act != NULL )
			{
				CLACT_SetMatrix(icon->act, &vector);
			}
			icon++;
		}
		
	}
}
//------------------------------------------------------------------
/**
 * 指定壁紙スクリーン描画
 *
 * @param   dst			描画先スクリーンバッファ
 * @param   src			描画元スクリーンデータ
 * @param   xpos		書き出し開始Ｘ
 * @param   charOfs		キャラナンバー先頭
 * @param   palPos		パレットナンバー
 *
 */
//------------------------------------------------------------------
static void TrayScrnWrite( u16* dst, const u16* src, u32 xpos, u32 charOfs, u32 palPos )
{
	enum {
		SCRN_BANK_ELEMS = 1024,	// １バンク1024キャラ分なので
		SCRN_LINE_ELEMS = 32,
	};
	u32 x, y;
	u16* dst_row;
	u16 scrn;

	if( xpos >= 32 )
	{
		dst += SCRN_BANK_ELEMS;
	}

	for(x = 0; x < TRAY_CHAR_WIDTH; x++)
	{
		dst_row = dst + ((SCRN_LINE_ELEMS*TRAY_WRITE_YPOS) + (xpos&31));
		for(y = 0; y < TRAY_CHAR_HEIGHT; y++)
		{
			scrn = src[ y * TRAY_CHAR_WIDTH + x ];
			scrn =		( ( GX_SCRFMT_TEXT_CHARNAME_MASK & scrn) + charOfs )
					|	( (GX_SCRFMT_TEXT_HF_MASK|GX_SCRFMT_TEXT_VF_MASK) & scrn )
					|	( palPos << GX_SCRFMT_TEXT_COLORPLTT_SHIFT );
			*dst_row = scrn;
			dst_row += SCRN_LINE_ELEMS;
		}
		for(y=0; y<TRAY_WRITE_Y_SPACE; y++)
		{
			*dst_row = ( palPos << GX_SCRFMT_TEXT_COLORPLTT_SHIFT ) | (charOfs + TRAY_SPACE_CHARNO);
			dst_row += SCRN_LINE_ELEMS;
		}

		xpos = (xpos + 1) & 63;
		if( xpos == 0 ){ dst -= SCRN_BANK_ELEMS; }
		if( xpos == 32){ dst += SCRN_BANK_ELEMS; }
	}

	for(x = 0; x < TRAY_WRITE_X_SPACE; x++)
	{
		dst_row = dst + ((SCRN_LINE_ELEMS*TRAY_WRITE_YPOS) + (xpos&31));
		for(y = 0; y < (TRAY_CHAR_HEIGHT+TRAY_WRITE_Y_SPACE); y++)
		{
			*dst_row = ( palPos << GX_SCRFMT_TEXT_COLORPLTT_SHIFT ) | (charOfs + TRAY_SPACE_CHARNO);
			dst_row += SCRN_LINE_ELEMS;
		}
		xpos = (xpos + 1) & 63;
		if( xpos == 0 ){ dst -= SCRN_BANK_ELEMS; }
		if( xpos == 32){ dst += SCRN_BANK_ELEMS; }
	}
}


//------------------------------------------------------------------------------
/**
 * 指定位置のアイコン逃がす処理開始
 *
 * @param   wk			トレイ描画ワーク
 * @param   pos			アイコン位置
 *
 */
//------------------------------------------------------------------------------
void BoxAppView_TrayIconReleaseStart( TRAY_VIEW_WORK* wk, u32 pos )
{
	wk->icon_release_pos = pos;
	wk->mvseq = 0;

	BoxAppView_IconAnmStart( wk->iconSys, &(wk->icon[wk->imgPos][pos]), ICON_ANM_RELEASE );
}
//------------------------------------------------------------------------------
/**
 * 指定位置のアイコン逃がす処理終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------------------
BOOL BoxAppView_TrayIconReleaseWait( TRAY_VIEW_WORK* wk )
{
	BOX_ICON_WORK*  icon = &(wk->icon[wk->imgPos][wk->icon_release_pos]);

	switch( wk->mvseq ){
	case 0:
		if( BoxAppView_IconAnmWait( wk->iconSys, icon ) )
		{
			const BOXAPP_WORK* mainWk = BoxAppView_GetMainWork( wk->vwk );

			if( BoxApp_ReleaseWazaCheckDone( mainWk ) )
			{
				if( BoxApp_ReleaseWazaCheckOK( mainWk ) )
				{
					BoxAppView_IconWorkQuit( wk->iconSys, icon, 1 );
					return TRUE;
				}
				else
				{
					BoxAppView_IconAnmStart( wk->iconSys, icon, ICON_ANM_COMEBACK );
					wk->mvseq++;
				}
			}
		}
		break;

	case 1:
		if( BoxAppView_IconAnmWait( wk->iconSys, icon ) )
		{
			return TRUE;
		}
		break;
	}
	return FALSE;
}


//------------------------------------------------------------------
/**
 * アイコンを絞り込みモード表示に対応
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_TrayIconLimitModeSet( TRAY_VIEW_WORK* wk )
{
	u32 limitBit;
	int i;

	limitBit = BoxAppVPara_GetLimitModeBitFlag( wk->vpara );

	for(i=0; i<BOX_MAX_POS; i++)
	{
		if( wk->icon[wk->imgPos][i].act != NULL )
		{
			BoxAppView_IconLimitModeSet( wk->iconSys, &(wk->icon[wk->imgPos][i]), limitBit );
		}
	}
}
//------------------------------------------------------------------
/**
 * アイコンのアイテム情報を更新
 *
 * @param   wk			ワークポインタ
 * @param   pos			アイコン位置
 * @param   itemNumber	アイテムナンバー
 *
 */
//------------------------------------------------------------------
void BoxAppView_TrayIconUpdateItem( TRAY_VIEW_WORK* wk, u32 pos, u32 itemNumber )
{
	if( wk->icon[wk->imgPos][pos].act != NULL )
	{
		BoxAppView_IconItemNumberSet( wk->iconSys, &(wk->icon[wk->imgPos][pos]), itemNumber );
		BoxAppView_IconLimitModeSet(wk->iconSys, &(wk->icon[wk->imgPos][pos]), BoxAppVPara_GetLimitModeBitFlag(wk->vpara));
	}
}


//------------------------------------------------------------------
/**
 * ポイントしているアイコンマーキングビットフラグ（内部ステータス）を書き換え
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_TrayIconMarkUpdate( TRAY_VIEW_WORK* wk )
{
	u32 pos, markBit;

	pos = BoxAppVPara_GetCursorTrayPos( wk->vpara );
	markBit = BoxAppVPara_GetStatusPokeMarkBit( wk->vpara );

	if( wk->icon[wk->imgPos][pos].act != NULL )
	{
		BoxAppView_IconMarkBitSet( wk->iconSys, &(wk->icon[wk->imgPos][pos]), markBit );
	}
}



//------------------------------------------------------------------
/**
 * 範囲選択の対象になっているアイコンをカラー変更
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_TrayIconAleaSelectUpdate( TRAY_VIEW_WORK* wk )
{
	u32 left, right, top, bottom, x, y, p;

	BoxAppVPara_GetAreaSelectParam(wk->vpara, &left, &right, &top, &bottom);

	p = 0;
	for(y=0; y<BOX_MAX_RAW; y++)
	{
		for(x=0; x<BOX_MAX_COLUMN; x++)
		{
			if( wk->icon[wk->imgPos][p].act != NULL )
			{
				if( ((u32)(x-left) <= (u32)(right - left))
				&	((u32)(y-top) <= (u32)(bottom - top))
				){
					BoxAppView_IconAreaSelectPalSet( wk->iconSys, &(wk->icon[wk->imgPos][p]), TRUE );
				}
				else
				{
					BoxAppView_IconAreaSelectPalSet( wk->iconSys, &(wk->icon[wk->imgPos][p]), FALSE );
				}
			}
			p++;
		}
	}
}
void BoxAppView_TrayIconAleaSelectQuit( TRAY_VIEW_WORK* wk )
{
	int i;

	for(i=0; i<BOX_MAX_POS; i++)
	{
		if( wk->icon[wk->imgPos][i].act != NULL )
		{
			BoxAppView_IconAreaSelectPalSet( wk->iconSys, &(wk->icon[wk->imgPos][i]), FALSE );
		}
	}
}



