//******************************************************************************
/**
 * 
 * @file	slot.c
 * @brief	ミニゲーム　スロット
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#define SLOT_LOCAL
#include "common.h"
#include "system\wipe.h"
#include "slot_local.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	struct
//==============================================================================
typedef struct _TAG_SLOTPROC SLOTPROC;

//--------------------------------------------------------------
///	SLOTPROC構造体
//--------------------------------------------------------------
typedef struct _TAG_SLOTPROC
{
	SLOT_PARAM *param;
	SLOTMAIN *main;
};

#define SLOTPROC_SIZE (sizeof(SLOTPROC))

//==============================================================================
//	プロトタイプ
//==============================================================================
static void slot_SlotParamReflect( SLOTPROC *slotproc, SLOTMAIN *main );

static SLOTMAIN * slot_MainWorkInit( SLOT_PARAM *param );
static void slot_MainWorkDelete( SLOTMAIN *main );

static void slotDraw_Init( SLOTMAIN *main );
static void slotDraw_Delete( SLOTMAIN *main );

static void slotDraw_VramBankSet( void );
static void slotDraw_BGLSet( GF_BGL_INI *ini );
static void slotDraw_BGLDelete( GF_BGL_INI *ini );
static void slotDraw_WindowInit( void );

static void slotBG_Init( SLOTMAIN *main );

static void slotCharPalM_Init( void );
static void slotCharPalM_Delete( void );

static void slotClAct_Init( SLOTMAIN *main );
static void slotClAct_Delete( SLOTMAIN *main );
static void slotClAct_VramInit( SLOTMAIN *main );
static void slotClAct_VramDelete( SLOTMAIN *main );

static void slotEoa_Init( SLOTMAIN *main );
static void slotEoa_Delete( SLOTMAIN *main );

static int slotBGM_ChangeCheck( SLOTMAIN *main );
static void slotBGM_Init( SLOTMAIN *main );
static void slotBGM_Delete( SLOTMAIN *main );
static void slotBGM_Tcb( TCB_PTR tcb, void *wk );

static void slot_VBlankFunc( void *work );

static void slotArc_HandleOpen( SLOTMAIN *main );
static void slotArc_HandleClose( SLOTMAIN *main );

static const BMPWIN_DAT DATA_SlotBmpWinList[SLOTWIN_MAX];

#ifdef DEBUG_SLOT_PARAM_INIT
static SLOT_PARAM DEBUG_SlotParam;
static int DEBUG_SlotCoin;
#endif

//==============================================================================
//	スロット	プロセス
//==============================================================================
//--------------------------------------------------------------
/**
 * スロットプロセス　初期化
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 * @retval	PROC_RESULT	PROC_RESULT
 */
//--------------------------------------------------------------
PROC_RESULT SlotProc_Init( PROC *proc, int *seq )
{
	SLOTPROC *slotproc;
	SLOTMAIN *main;
	SLOT_PARAM *param;
    
	sys_VBlankFuncChange( NULL, NULL );
	sys_HBlankIntrStop();
	
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_SLOT, SLOT_HEAPSIZE );
	
	slotproc = PROC_AllocWork( proc, SLOTPROC_SIZE, HEAPID_SLOT );
	memset( slotproc, 0, SLOTPROC_SIZE );
	
	param = PROC_GetParentWork( proc );
	
#ifdef DEBUG_SLOT_PARAM_INIT
	if( param == NULL ){
		
		DEBUG_SlotCoin = 1000;
		DEBUG_SlotParam.coin = &DEBUG_SlotCoin;
		DEBUG_SlotParam.hard = SLOT_HARD_5;
		DEBUG_SlotParam.record = NULL;
		DEBUG_SlotParam.r_count = 0;
		
		param = &DEBUG_SlotParam;
	}
	
	slotproc->param = param;
	main = slot_MainWorkInit( slotproc->param );
	slotproc->main = main;
#else
	slotproc->param = param;
	main = slot_MainWorkInit( slotproc->param );
	slotproc->main = main;
#endif
	
	slotArc_HandleOpen( main );
	
	slotEoa_Init( main );
	slotDraw_Init( main );
	slotBG_Init( main );
	SlotTalkWinFont_Init( main );
	slotCharPalM_Init();
	slotClAct_Init( main );
	
	SlotMain_GameInit( main );
	
	SlotSubEoa_ReelPatternInit( main );
	SlotSubEoa_CreditFontInit( main );
	SlotSubEoa_PayOutFontInit( main );
	
	Snd_DataSetByScene( SND_SCENE_SUB_SLOT, 0, 0 );	// サウンドデータロード(スロット)(BGM引継ぎ)
	slotBGM_Init( main );
	
	WIPE_SYS_Start( WIPE_PATTERN_WMS,
		WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 8, 1, HEAPID_SLOT );	
	
	return( PROC_RES_FINISH );
}

//--------------------------------------------------------------
/**
 * スロットプロセス　メイン
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 * @retval	PROC_RESULT	PROC_RESULT
 */
//--------------------------------------------------------------
PROC_RESULT SlotProc_Main( PROC *proc, int *seq )
{
	SLOTPROC *slotproc = PROC_GetWork( proc );
	SLOTMAIN *main = slotproc->main;
	
	switch( *seq ){
	case 0:
		if( WIPE_SYS_EndCheck() ){
			(*seq)++;
		}
		break;
	case 1:
		if( SlotMain_Game(main) == TRUE ){
			(*seq)++;
			WIPE_SYS_Start( WIPE_PATTERN_FSAM,
				WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 8, 1, HEAPID_SLOT );
			
			SlotBGM_Play( main, BGM_NORMAL );
		}
		break;
	case 2:
		if( WIPE_SYS_EndCheck() == 0 ){
			break;
		}
		
		(*seq)++;
	case 3:
		if( slotBGM_ChangeCheck(main) == FALSE ){
			return( PROC_RES_FINISH );
		}
	}
	
	EOA_SysDraw( main->eoa_sys );
	ClActSetDataDraw( main->clactset );
	
	return( PROC_RES_CONTINUE );
}

//--------------------------------------------------------------
/**
 * スロットプロセス　終了
 * @param	proc	プロセスデータ
 * @param	seq		シーケンス
 * @retval	PROC_RESULT	PROC_RESULT
 */
//--------------------------------------------------------------
PROC_RESULT SlotProc_End( PROC *proc, int *seq )
{
	SLOTPROC *slotproc = PROC_GetWork( proc );
	SLOTMAIN *main = slotproc->main;
	
	sys_VBlankFuncChange( NULL, NULL );
	
	slot_SlotParamReflect( slotproc, main );
	
	slotEoa_Delete( main );
	slotDraw_Delete( main );
	SlotTalkWinFont_Delete( main );
	
	SlotMain_GameDelete( main );
	slotBGM_Delete( main );
	
	slotArc_HandleClose( main );
	slot_MainWorkDelete( main );
	PROC_FreeWork( proc );
	sys_DeleteHeap( HEAPID_SLOT );
	
	return( PROC_RES_FINISH );
}

//--------------------------------------------------------------
/**
 * 終了時のSLOT_PARAM反映
 * @param	slotproc	SLOTPROC
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_SlotParamReflect( SLOTPROC *slotproc, SLOTMAIN *main )
{
	u32 credit = main->credit;
	if( credit > SLOT_COIN_MAX ){ credit = SLOT_COIN_MAX; }
	(*slotproc->param->coin) = credit;
	slotproc->param->r_count = main->bonus_continue_count_max;
	
	if( slotproc->param->record != NULL ){
		RECORD_Add( slotproc->param->record, RECID_SLOT_FEAVER, main->bonus_hit_count );	
	}
}

//==============================================================================
//	スロット　メインワーク
//==============================================================================
//--------------------------------------------------------------
/**
 * SLOTMAIN初期化
 * @param	slotparam	SLOT_PARAM
 * @retval	SLOTPROC	SLOTPROC *
 */
//--------------------------------------------------------------
static SLOTMAIN * slot_MainWorkInit( SLOT_PARAM *param )
{
	SLOTMAIN *main = Slot_AllocMemory( SLOTMAIN_SIZE );
	
	main->credit = *(param->coin);
	main->hard = param->hard;
	main->win_type = param->win_type;
	return( main );
}

//--------------------------------------------------------------
/**
 * SLOTMAIN削除
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_MainWorkDelete( SLOTMAIN *main )
{
	sys_FreeMemoryEz( main );
}

//==============================================================================
//	描画
//==============================================================================
//--------------------------------------------------------------
/**
 * 描画初期化
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_Init( SLOTMAIN *main )
{
	main->bgl = GF_BGL_BglIniAlloc( HEAPID_SLOT );
	
	slotDraw_VramBankSet();
	slotDraw_BGLSet( main->bgl );
	slotDraw_WindowInit();
	
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	
	G2_SetBG0Priority( 0 );
	G2_SetBG1Priority( 1 );
	G2_SetBG2Priority( 2 );
	G2_SetBG3Priority( 3 );
	G2S_SetBG0Priority( 0 );
	G2S_SetBG1Priority( 1 );
	G2S_SetBG2Priority( 2 );
	G2S_SetBG3Priority( 3 );
	
	G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_OBJ, 8, 9 );
	
	sys_VBlankFuncChange( slot_VBlankFunc, main );
}

//--------------------------------------------------------------
/**
 * 描画削除
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_Delete( SLOTMAIN *main )
{
	slotDraw_BGLDelete( main->bgl );
	slotClAct_Delete( main );
	slotCharPalM_Delete();
}

//--------------------------------------------------------------
/**
 * VRAM BANK割り当て
 * @param	nothing
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_VramBankSet( void )
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

//--------------------------------------------------------------
/**
 * BG初期化　
 * @param	bgl		GF_BGL_INI
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_BGLSet( GF_BGL_INI *ini )
{
	GX_SetDispSelect( GX_DISP_SELECT_MAIN_SUB );
	
	{	//BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}
	
	{	//上画面　会話ウィンドウ
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
			0, 0, 0, FALSE
		};
		
		GF_BGL_BGControlSet( ini, BGFRAME_KAIWA, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, BGFRAME_KAIWA );
		GF_BGL_ClearCharSet( BGFRAME_KAIWA, 32, 0, HEAPID_SLOT );
	}
	
	{	//スロット台
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
			1, 0, 0, FALSE
		};
		
		GF_BGL_BGControlSet( ini, BGFRAME_SLOT, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, BGFRAME_SLOT );
	}
	
	{	//スロット影
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000, GX_BG_EXTPLTT_01,
			2, 0, 0, FALSE
		};
		
		GF_BGL_BGControlSet( ini, BGFRAME_SLOT_SHADOW, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, BGFRAME_SLOT_SHADOW );
	}
	
	{	//下画面背景
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1800, GX_BG_CHARBASE_0x20000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		
		GF_BGL_BGControlSet( ini, BGFRAME_BGSUB, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, BGFRAME_BGSUB );
	}
	
#ifdef DEBUG_ON_SLOT
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat = {
			0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x2000, GX_BG_CHARBASE_0x2c000, GX_BG_EXTPLTT_01,
			3, 0, 0, FALSE
		};
		
		GF_BGL_BGControlSet( ini, BGFRAME_SUB_DEBUG, &TextBgCntDat, GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear( ini, BGFRAME_SUB_DEBUG );
	}
#endif
}

//--------------------------------------------------------------
/**
 * BG削除
 * @param	bgl		GF_BGL_INI
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_BGLDelete( GF_BGL_INI *ini )
{
	GF_BGL_BGControlExit( ini, BGFRAME_KAIWA );
	GF_BGL_BGControlExit( ini, BGFRAME_SLOT );
	GF_BGL_BGControlExit( ini, BGFRAME_SLOT_SHADOW );
	GF_BGL_BGControlExit( ini, BGFRAME_BGSUB );
	
#ifdef DEBUG_ON_SLOT
	GF_BGL_BGControlExit( ini, BGFRAME_SUB_DEBUG );
#endif
	
	sys_FreeMemoryEz( ini );
}

//--------------------------------------------------------------
/**
 * ウィンドウ初期化
 * @param	nothing
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotDraw_WindowInit( void )
{
	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	
	G2_SetWnd0InsidePlane(
			GX_WND_PLANEMASK_BG0 |
			GX_WND_PLANEMASK_BG1 |
			GX_WND_PLANEMASK_BG2 |
			GX_WND_PLANEMASK_BG3 |
			GX_WND_PLANEMASK_OBJ,
			TRUE );
	
	G2_SetWndOutsidePlane(
			GX_WND_PLANEMASK_BG0 |
			GX_WND_PLANEMASK_BG1 |
			GX_WND_PLANEMASK_BG2 |
			GX_WND_PLANEMASK_BG3 |
			GX_WND_PLANEMASK_OBJ,
			TRUE );
			
	G2_SetWnd0Position( 0, 0, 255, 255 );
}

//==============================================================================
//	スロット BG
//==============================================================================
//--------------------------------------------------------------
/**
 * BG初期化
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotBG_Init( SLOTMAIN *main )
{
	//スロットBGパレット
	void *buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_NCLR, FALSE );
	NNS_G2dGetUnpackedPaletteData( buf, &main->bg_pPltt );
	GF_BGL_PaletteSet( BGFRAME_SLOT, main->bg_pPltt->pRawData, 
		BGF_SLOT_PLTT_SIZE, BGF_SLOT_PLTT_OFFSET );
	sys_FreeMemoryEz( buf );
	
	//スロット台
	buf = SlotArc_DataLoad( main, NARC_slot_slot_machine_NCGR, FALSE );
	NNS_G2dGetUnpackedCharacterData( buf, &main->bg_pChar );
	GF_BGL_LoadCharacter( main->bgl, BGFRAME_SLOT,
		main->bg_pChar->pRawData, main->bg_pChar->szByte, BGF_SLOT_CHAR_OFFSET );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_machine_NSCR, FALSE );
	NNS_G2dGetUnpackedScreenData( buf, &main->bg_pScr );
	GF_BGL_ScreenBufSet( main->bgl, BGFRAME_SLOT,
		(void*)main->bg_pScr->rawData, main->bg_pScr->szByte );
	GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SLOT );
	sys_FreeMemoryEz( buf );
	
	//影
	buf = SlotArc_DataLoad( main, NARC_slot_slot_bg_shadow_NCGR, FALSE );
	NNS_G2dGetUnpackedCharacterData( buf, &main->bg_pChar );
	GF_BGL_LoadCharacter( main->bgl, BGFRAME_SLOT_SHADOW,
		main->bg_pChar->pRawData, main->bg_pChar->szByte, BGF_SLOT_CHAR_OFFSET );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_bg_shadow_NSCR, FALSE );
	NNS_G2dGetUnpackedScreenData( buf, &main->bg_pScr );
	GF_BGL_ScreenBufSet( main->bgl, BGFRAME_SLOT_SHADOW,
		(void*)main->bg_pScr->rawData, main->bg_pScr->szByte );
	GF_BGL_LoadScreenReq( main->bgl, BGFRAME_SLOT_SHADOW );
	sys_FreeMemoryEz( buf );
	
	//下画面
	buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_NCLR, FALSE );
	NNS_G2dGetUnpackedPaletteData( buf, &main->bg_pPltt );
	GF_BGL_PaletteSet( BGFRAME_BGSUB, main->bg_pPltt->pRawData, 
		BGF_SLOT_PLTT_SIZE, BGF_SLOT_PLTT_OFFSET );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_NCGR, FALSE );
	NNS_G2dGetUnpackedCharacterData( buf, &main->bg_pChar );
	GF_BGL_LoadCharacter( main->bgl, BGFRAME_BGSUB,
		main->bg_pChar->pRawData, main->bg_pChar->szByte, 0 );
	sys_FreeMemoryEz( buf );
	
	buf = SlotArc_DataLoad( main, NARC_slot_slot_mount_NSCR, FALSE );
	NNS_G2dGetUnpackedScreenData( buf, &main->bg_pScr );
	GF_BGL_ScreenBufSet( main->bgl, BGFRAME_BGSUB,
		(void*)main->bg_pScr->rawData, main->bg_pScr->szByte );
	GF_BGL_LoadScreenReq( main->bgl, BGFRAME_BGSUB );
	sys_FreeMemoryEz( buf );
	
	//下画面　デバッグ
#ifdef DEBUG_ON_SLOT
	main->bg_pPltt = GF_BGL_NTRCHR_PalLoad( buf, HEAPID_SLOT, "data/nfont.NCLR" );
	GF_BGL_PaletteSet( BGFRAME_SUB_DEBUG, main->bg_pPltt->pRawData, 32, BGF_SLOT_PANO_FONT*32 );
	sys_FreeMemoryEz( buf );
	GF_BGL_NTRCHR_CharLoad( main->bgl, BGFRAME_SUB_DEBUG, "data/nfont.NCGR", 0 );
#endif
}

//==============================================================================
//	スロット　フォント
//==============================================================================
//--------------------------------------------------------------
/**
 * フォント 初期化
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotTalkWinFont_Init( SLOTMAIN *main )
{
	int i;
	MSGWORK *msg = &main->msgwork;
	
	MenuWinGraphicSet( main->bgl, BGFRAME_KAIWA,
		BGF_SLOT_CHAR_NO_WIN, BGF_SLOT_PANO_FONT, 0, HEAPID_SLOT );
	
	TalkWinGraphicSet(
		main->bgl, BGFRAME_KAIWA, BGF_SLOT_CHAR_NO_TALK,
		BGF_SLOT_PANO_TALK, main->win_type, HEAPID_SLOT );
	
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, BGF_SLOT_PANO_FONT*32, HEAPID_SLOT );
	
	msg->msgman = MSGMAN_Create(
			MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_slot_dat, HEAPID_SLOT );
	
	msg->wordset = WORDSET_Create( HEAPID_SLOT );
	
	for( i = 0; i < SLOTWIN_MAX; i++ ){
		GF_BGL_BmpWinAddEx( main->bgl, &msg->bmpwin[i], &DATA_SlotBmpWinList[i] );
	}
	
	msg->strbuf = STRBUF_Create( STR_BUF_SIZE, HEAPID_SLOT );
}

//--------------------------------------------------------------
/**
 * フォント削除
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotTalkWinFont_Delete( SLOTMAIN *main )
{
	int i;
	MSGWORK *msg = &main->msgwork;
	
	for( i = 0; i < SLOTWIN_MAX; i++ ){
		GF_BGL_BmpWinOff( &msg->bmpwin[i] );
		GF_BGL_BmpWinDel( &msg->bmpwin[i] );
	}
	
	MSGMAN_Delete( msg->msgman );
	WORDSET_Delete( msg->wordset );
	STRBUF_Delete( msg->strbuf );
}

//--------------------------------------------------------------
/**
 * 会話ウィンドウ表示
 * @param	main	SLOTMAIN
 * @param	msgno	メッセージデータNo
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotTalkWin_Write( SLOTMAIN *main, u32 msgno )
{
	MSGWORK *msg = &main->msgwork;
	
	BmpTalkWinWrite( &msg->bmpwin[SLOTWIN_TALK],
			WINDOW_TRANS_OFF, BGF_SLOT_CHAR_NO_TALK, BGF_SLOT_PANO_TALK );
	
	GF_BGL_BmpWinDataFill( &msg->bmpwin[SLOTWIN_TALK], FBMP_COL_WHITE );
	
	MSGMAN_GetString( msg->msgman, msgno, msg->strbuf );
	GF_STR_PrintSimple( &msg->bmpwin[SLOTWIN_TALK],
			FONT_TALK, msg->strbuf, 0, 0, MSG_NO_PUT, NULL );
	
	GF_BGL_BmpWinOnVReq( &msg->bmpwin[SLOTWIN_TALK] );	
}

//--------------------------------------------------------------
/**
 * 会話ウィンドウクリア
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotTalkWin_Clear( SLOTMAIN *main )
{
	MSGWORK *msg = &main->msgwork;
	
	BmpTalkWinClear( &msg->bmpwin[SLOTWIN_TALK], WINDOW_TRANS_OFF );
	GF_BGL_BmpWinDataFill( &msg->bmpwin[SLOTWIN_TALK], FBMP_COL_NULL );
	GF_BGL_BmpWinOnVReq( &msg->bmpwin[SLOTWIN_TALK] );	
}

//==============================================================================
//	スロット　キャラ、パレットマネージャ
//==============================================================================
//--------------------------------------------------------------
/**
 * キャラ、パレットマネージャ初期化
 * @param	nothing
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotCharPalM_Init( void )
{
	CHAR_MANAGER_MAKE cm = {
		CHAR_MANAGER_MAX,CHAR_VRAMTRANS_M_SIZE,CHAR_VRAMTRANS_S_SIZE,HEAPID_SLOT};
	
//	InitCharManager( &cm );
	InitCharManagerReg( &cm, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_128K );
	InitPlttManager( PLTT_MANAGER_MAX, HEAPID_SLOT );
	
	CharLoadStartAll();
	PlttLoadStartAll();
}

//--------------------------------------------------------------
/**
 * キャラ、パレットマネージャ削除
 * @param	nothing
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotCharPalM_Delete( void )
{
	DeleteCharManager();
	DeletePlttManager();
}

//==============================================================================
//	スロット　セルアクター
//==============================================================================
//--------------------------------------------------------------
/**
 * セルアクター　初期化
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotClAct_Init( SLOTMAIN *main )
{
	//OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();
	
	//共有OAMマネージャ作成
	//レンダラ用OAMマネージャ作成
	//ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			0, 128,		// メイン画面OAM管理領域
			0, 32,		// メイン画面アフィン管理領域
			0, 128,		// サブ画面OAM管理領域
			0, 32,		// サブ画面アフィン管理領域
			HEAPID_SLOT );
	
	main->clactset = ClActSetDataInit( HEAPID_SLOT, SLOT_CLACT_MAX, SLOT_CLACT_TRANS_MAX,
		SLOT_CHAR_MAX, SLOT_PLTT_MAX, SLOT_CELL_MAX, SLOT_ANM_MAX,
		SLOT_CHARID_MAX, SLOT_PLTTID_MAX, SLOT_CELLID_MAX, SLOT_ANMID_MAX );
	
	slotClAct_VramInit( main );
}

//--------------------------------------------------------------
/**
 * セルアクター　削除
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotClAct_Delete( SLOTMAIN *main )
{
	slotClAct_VramDelete( main );
	ClActSetDataDelete( main->clactset );
	REND_OAM_Delete();
}

//--------------------------------------------------------------
/**
 * セルアクターVRAM初期化
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotClAct_VramInit( SLOTMAIN *main )
{
	ClActCharAdd( main->clactset, G2D_2DMAIN,
		main->arc_handle, NARC_slot_slotreel_NCGR, SLOT_CHARID_REEL );
	ClActCharAdd( main->clactset, G2D_2DMAIN,
		main->arc_handle, NARC_slot_credit_font_NCGR, SLOT_CHARID_CREDITFONT );
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_slot_bonus_NCGR, SLOT_CHARID_BONUSFONT );
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_slot_get_NCGR, SLOT_CHARID_GETFONT );
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_bonus_get_font_NCGR, SLOT_CHARID_BONUSGETFONT );
	ClActCharAdd( main->clactset, G2D_2DSUB,
		main->arc_handle, NARC_slot_moon_font_NCGR, SLOT_CHARID_MOONFONT );
	
	ClActPlttAdd( main->clactset, G2D_2DMAX,	//ビッグヒット、下画面利用
			main->arc_handle, NARC_slot_slotreel_NCLR, SLOT_PLTTID_REEL );
	ClActPlttAdd( main->clactset, G2D_2DMAIN,
			main->arc_handle, NARC_slot_credit_font_NCLR, SLOT_PLTTID_CREDITFONT );
	ClActPlttAdd( main->clactset, G2D_2DSUB,
			main->arc_handle, NARC_slot_bonus_get_font_NCLR, SLOT_PLTTID_BONUSFONT );
	ClActPlttAdd( main->clactset, G2D_2DSUB,
			main->arc_handle, NARC_slot_moon_font_NCLR, SLOT_PLTTID_MOONFONT );
	
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_slotreel_NCER, SLOT_CELLID_REEL );
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_credit_font_NCER, SLOT_CELLID_CREDITFONT );
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_slot_bonus_NCER, SLOT_CELLID_BONUSFONT );
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_slot_get_NCER, SLOT_CELLID_GETFONT );
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_bonus_get_font_NCER, SLOT_CELLID_BONUSGETFONT );
	ClActCellAdd( main->clactset,
			main->arc_handle, NARC_slot_moon_font_NCER, SLOT_CELLID_MOONFONT );
	
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_slotreel_NANR, SLOT_ANMID_REEL );
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_credit_font_NANR, SLOT_ANMID_CREDITFONT );
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_slot_bonus_NANR, SLOT_ANMID_BONUSFONT );
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_slot_get_NANR, SLOT_ANMID_GETFONT );
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_bonus_get_font_NANR, SLOT_ANMID_BONUSGETFONT );
	ClActAnmAdd( main->clactset,
			main->arc_handle, NARC_slot_moon_font_NANR, SLOT_ANMID_MOONFONT );
	
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_REEL );
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_CREDITFONT );
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_BONUSFONT );
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_GETFONT );
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_BONUSGETFONT );
	ClActCharVramAreaSet( main->clactset, SLOT_CHARID_MOONFONT );
	ClActCharResDelete( main->clactset, SLOT_CHARID_REEL );
	ClActCharResDelete( main->clactset, SLOT_CHARID_CREDITFONT );
	ClActCharResDelete( main->clactset, SLOT_CHARID_BONUSFONT );
	ClActCharResDelete( main->clactset, SLOT_CHARID_GETFONT );
	ClActCharResDelete( main->clactset, SLOT_CHARID_BONUSGETFONT );
	ClActCharResDelete( main->clactset, SLOT_CHARID_MOONFONT );
	
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_REEL );
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_CREDITFONT );
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_BONUSFONT );
	ClActPlttVramAreaSet( main->clactset, SLOT_PLTTID_MOONFONT );
	ClActPlttResDelete( main->clactset, SLOT_PLTTID_REEL );
	ClActPlttResDelete( main->clactset, SLOT_PLTTID_CREDITFONT );
	ClActPlttResDelete( main->clactset, SLOT_PLTTID_BONUSFONT );
	ClActPlttResDelete( main->clactset, SLOT_PLTTID_MOONFONT );
}

//--------------------------------------------------------------
/**
 * セルアクターVRAM削除
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotClAct_VramDelete( SLOTMAIN *main )
{
}

//==============================================================================
//	スロット EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA初期化
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotEoa_Init( SLOTMAIN *main )
{
	main->eoa_sys = EOA_SysInit( HEAPID_SLOT, SLOT_EOA_MAX );
}

//--------------------------------------------------------------
/**
 * EOA削除
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotEoa_Delete( SLOTMAIN *main )
{
	EOA_SysDeleteAll( main->eoa_sys );
}

//==============================================================================
//	BGM
//==============================================================================
//--------------------------------------------------------------
/**
 * 指定BGM再生
 * @param	main	SLOTMAIN
 * @param	type	BGMTYPE
 * @retval	nothing
 */
//--------------------------------------------------------------
void SlotBGM_Play( SLOTMAIN *main, BGMTYPE type )
{
	SLOTBGM *bgm = &main->bgm;
	
	if( bgm->now_play == type || bgm->next_play == type ){
		return;
	}
	
	bgm->next_play = type;
	bgm->seq_no = 1;
	bgm->chg_flag = TRUE;
}

//--------------------------------------------------------------
/**
 * BGM再生チェック
 * @param	main	SLOTMAIN
 * @retval	int		TRUE=BGM切り替え中
 */
//--------------------------------------------------------------
static int slotBGM_ChangeCheck( SLOTMAIN *main )
{
	SLOTBGM *bgm = &main->bgm;
	return( bgm->chg_flag );
}

//--------------------------------------------------------------
/**
 * BGM管理初期化
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotBGM_Init( SLOTMAIN *main )
{
	SLOTBGM *bgm = &main->bgm;
	
	bgm->now_play = BGM_NORMAL;
	bgm->next_play = BGM_MAX;
	bgm->tcb = TCB_Add( slotBGM_Tcb, main, TCBPRI_BGM );
}

//--------------------------------------------------------------
/**
 * BGM管理削除
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotBGM_Delete( SLOTMAIN *main )
{
	TCB_Delete( main->bgm.tcb );
}

//--------------------------------------------------------------
/**
 * BGM管理
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotBGM_Tcb( TCB_PTR tcb, void *wk )
{
	SLOTMAIN *main = wk;
	SLOTBGM *bgm = &main->bgm;
	
	switch( bgm->seq_no ){
	case 0:
		break;
	case 1:
		switch( bgm->now_play ){
		case BGM_NORMAL: Snd_PlayerPause( PLAYER_FIELD, TRUE ); break;
		case BGM_HIT: Snd_BgmStop( SEQ_SLOT_ATARI, 0 ); break;
		case BGM_BIGHIT: Snd_BgmStop( SEQ_SLOT_OOATARI, 0 ); break;
		}
		
		bgm->seq_no++;
		break;
	case 2:
		switch( bgm->next_play ){
		case BGM_NORMAL: Snd_PlayerPause( PLAYER_FIELD, FALSE ); break;
		case BGM_HIT: Snd_BgmPlayBasicData( SEQ_SLOT_ATARI ); break;
		case BGM_BIGHIT: Snd_BgmPlayBasicData( SEQ_SLOT_OOATARI ); break;
		}
		
		bgm->now_play = bgm->next_play;
		bgm->next_play = BGM_MAX;
		bgm->chg_flag = FALSE;
		bgm->seq_no = 0;
	}
}

//==============================================================================
//	スロット　Vブランク
//==============================================================================
//--------------------------------------------------------------
/**
 * スロットVBlank処理
 * @param	work	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slot_VBlankFunc( void *work )
{
	SLOTMAIN *main = work;
	
	//セルアクターVram転送マネージャー実行
	DoVramTransferManager();
	
	//レンダラ共有OAMマネージャVram転送
	REND_OAMTrans();
	
	//BG転送
	GF_BGL_VBlankFunc( main->bgl );
}

//==============================================================================
//	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * メモリ確保
 * @param	size	確保サイズ
 * @retval	void*	確保した領域
 */
//--------------------------------------------------------------
void * Slot_AllocMemory( u32 size )
{
	void *alloc = sys_AllocMemory( HEAPID_SLOT, size );
	GF_ASSERT( alloc != NULL && "Slot_AllocMemory() alloc error" );
	memset( alloc, 0, size );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * メモリ確保　後ろ
 * @param	size	確保サイズ
 * @retval	void*	確保した領域
 */
//--------------------------------------------------------------
void * Slot_AllocMemoryLo( u32 size )
{
	void *alloc = sys_AllocMemoryLo( HEAPID_SLOT, size );
	GF_ASSERT( alloc != NULL && "Slot_AllocMemory() alloc error" );
	memset( alloc, 0, size );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * アーカイブオープン
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotArc_HandleOpen( SLOTMAIN *main )
{
	main->arc_handle = ArchiveDataHandleOpen( ARC_SLOT, HEAPID_SLOT );
}

//--------------------------------------------------------------
/**
 * アーカイブクローズ
 * @param	main	SLOTMAIN
 * @retval	nothing
 */
//--------------------------------------------------------------
static void slotArc_HandleClose( SLOTMAIN *main )
{
	ArchiveDataHandleClose( main->arc_handle );
}

//--------------------------------------------------------------
/**
 * アーカイブデータロード
 * @param	main	SLOTMAIN
 * @param	id		データインデックス
 * @param	fb		TRUE=前 FALSE=後ろから領域取得
 * @retval	void*	ロードしたデータ
 */
//--------------------------------------------------------------
void * SlotArc_DataLoad( SLOTMAIN *main, u32 id, int fb )
{
	void *buf;
	u32 size = ArchiveDataSizeGetByHandle( main->arc_handle, id );
	
	if( fb == TRUE ){
		buf = sys_AllocMemory( HEAPID_SLOT, size );
	}else{
		buf = sys_AllocMemoryLo( HEAPID_SLOT, size );
	}
	
	GF_ASSERT( buf != NULL && "slotArc_DataLoad() alloc error" );
	ArchiveDataLoadByHandle( main->arc_handle, id, buf );
	return( buf );
}

//==============================================================================
//	msg data
//==============================================================================
//--------------------------------------------------------------
///	ビットマップウィンドウ
//--------------------------------------------------------------
static const BMPWIN_DAT DATA_SlotBmpWinList[SLOTWIN_MAX] =
{
	{ //SLOTWIN_TALK
		BGFRAME_KAIWA, 2, 19, 26, 4,
		BGF_SLOT_PANO_FONT, BGF_SLOT_CHAR_NO_TALK+TALK_WIN_CGX_SIZ,
	},
};
