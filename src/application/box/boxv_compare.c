//============================================================================================
/**
 * @file	boxv_compare.c
 * @brief	ボックス操作画面　描画下請け（つよさくらべモード関連）
 * @author	taya
 * @date	2006.03.28
 */
//============================================================================================
#include  "common.h"
#include  "gflib\calctool.h"
#include  "gflib\strbuf.h"
#include  "system\fontproc.h"
#include  "system\arc_util.h"
#include  "system\clact_util.h"
#include  "system\render_oam.h"
#include  "poketool\pokeicon.h"
#include  "msgdata\msg.naix"

#include  "box_arc.h"
#include  "box_view.h"
#include  "box_common.h"


//------------------------------------------------------
/**
 *  BitmapWindow Parameters
 */
//------------------------------------------------------
enum {
	WINID_NAME_LEFT,
	WINID_NAME_RIGHT,
	WINID_TITLE,

	WINID_STATUS_LEFT,
	WINID_STATUS_RIGHT,
	WINID_SKILL_LEFT,
	WINID_SKILL_RIGHT,


	WINID_MAX,
};

enum {
	BMPWIN_NAME_HEIGHT = 2,
	BMPWIN_NAME_WIDTH  = 9,
	BMPWIN_NAME_CHARSIZE = BMPWIN_NAME_HEIGHT*BMPWIN_NAME_WIDTH,
	BMPWIN_TITLE_WIDTH = 6,
	BMPWIN_TITLE_HEIGHT = 16,
	BMPWIN_TITLE_CHARSIZE = BMPWIN_TITLE_WIDTH*BMPWIN_TITLE_HEIGHT,

	BMPWIN_STATUS_WIDTH  = 9,
	BMPWIN_STATUS_HEIGHT = 16,
	BMPWIN_STATUS_CHARSIZE = BMPWIN_STATUS_WIDTH*BMPWIN_STATUS_HEIGHT,
	BMPWIN_SKILL_WIDTH = 11,
	BMPWIN_SKILL_HEIGHT = 12,
	BMPWIN_SKILL_CHARSIZE = BMPWIN_SKILL_WIDTH*BMPWIN_SKILL_HEIGHT,


	BMPWIN_CHAROFS_TOP = 1,
	BMPWIN_NAME_LEFT_CHARPOS  = BMPWIN_CHAROFS_TOP,
	BMPWIN_NAME_RIGHT_CHARPOS = BMPWIN_NAME_LEFT_CHARPOS + BMPWIN_NAME_CHARSIZE,
	BMPWIN_TITLE_CHARPOS      = BMPWIN_NAME_RIGHT_CHARPOS + BMPWIN_NAME_CHARSIZE,
	BMPWIN_FIX_CHARPOS_END    = BMPWIN_TITLE_CHARPOS + BMPWIN_TITLE_CHARSIZE,

	BMPWIN_STATUS_LEFT_CHARPOS  = BMPWIN_FIX_CHARPOS_END,
	BMPWIN_STATUS_RIGHT_CHARPOS = BMPWIN_STATUS_LEFT_CHARPOS + BMPWIN_STATUS_CHARSIZE,

	BMPWIN_SKILL_LEFT_CHARPOS   = BMPWIN_FIX_CHARPOS_END,
	BMPWIN_SKILL_RIGHT_CHARPOS  = BMPWIN_SKILL_LEFT_CHARPOS + BMPWIN_SKILL_CHARSIZE,


	BMPWIN_NAME_LEFT_X = 3,
	BMPWIN_NAME_LEFT_Y = 1,
	BMPWIN_NAME_RIGHT_X = 20,
	BMPWIN_NAME_RIGHT_Y = 1,

	BMPWIN_TITLE_X = 13,
	BMPWIN_TITLE_Y = 4,

	BMPWIN_STATUS_LEFT_X = 3,
	BMPWIN_STATUS_LEFT_Y = 4,
	BMPWIN_STATUS_RIGHT_X = 20,
	BMPWIN_STATUS_RIGHT_Y = 4,

	BMPWIN_SKILL_LEFT_X = 1,
	BMPWIN_SKILL_LEFT_Y = 4,
	BMPWIN_SKILL_RIGHT_X = 20,
	BMPWIN_SKILL_RIGHT_Y = 4,


	BMPWIN_TITLE_COL_LETTER = 0x0f,
	BMPWIN_COL_LETTER = 0x0f,
	BMPWIN_COL_SHADOW = 0x0e,
	BMPWIN_COL_GROUND = 0x00,

	BMPWIN_TITLE_STR_OY = 0,
	BMPWIN_TITLE_STR_HEIGHT = 16,

	BMPWIN_STATUS_STR_OY = 0,
	BMPWIN_STATUS_STR_HEIGHT = 16,

	BMPWIN_SKILL_STR_OY = 4,
	BMPWIN_SKILL_STR_HEIGHT = 24,

/*
	名前				18*2=36
	ステータス			144*2=288
	ステータスタイトル	128
	ワザ				132*2=264
	ワザタイトル		16
*/

};

//------------------------------------------------------
/**
 *  Actor Animation
 */
//------------------------------------------------------
enum {
	ANM_SIDEBUTTON_FREE,
	ANM_SIDEBUTTON_HOLD,
	ANM_SIDEBUTTON_PUSH,
	ANM_PAGEBUTTON_FREE,
	ANM_PAGEBUTTON_PUSH,
	ANM_CONDITION_POINT_L,
	ANM_CONDITION_POINT_R,
};


//------------------------------------------------------
/**
 *  
 */
//------------------------------------------------------
struct _COMPARE_VIEW_WORK {
	BOOL					enableFlag;

	BOXAPP_VIEW_WORK*		vwk;
	const BOXAPP_VPARAM*	vpara;
	GF_BGL_INI*				bgl;
	CLACT_SET_PTR			actsys;
	BOX_ICON_SYS*			iconsys;

	u32						pokeActCharPos[2];
	CLACT_WORK_PTR			actPoke[2];
	CLACT_WORK_PTR			actButton[2];
	CLACT_WORK_PTR			actButtonPage;
	CLACT_WORK_PTR			actConditionPoint[2][5];
	void*					cellBuf;
	NNSG2dCellDataBank*		cellData;
	void*					animBuf;
	NNSG2dAnimBankData*		animData;

	MSGDATA_MANAGER*		msgman;
	MSGDATA_MANAGER*		msgman_wazaname;
	STRBUF*					strbuf;

	GF_BGL_BMPWIN			bmpwin[ WINID_MAX ];

	u8						iconCharBuf[BOXICON_CHARBUF_SIZE];

	NNSG2dScreenData*		arrowScrnDataL;
	NNSG2dScreenData*		arrowScrnDataR;
	void*					arrowScrnLoadPtrL;
	void*					arrowScrnLoadPtrR;

	int						prev_page;
	int						page_seq;

	TCB_PTR					pageButtonCtrlTask;
};

//==============================================================
// Prototype
//==============================================================
static void UpdateArrowBgScreen( COMPARE_VIEW_WORK* wk );
static void EnableBackgroundBG( COMPARE_VIEW_WORK* wk );
static void InitBmpWin( COMPARE_VIEW_WORK* wk );
static void QuitBmpWin( COMPARE_VIEW_WORK* wk );
static void CreatePageBmpWin( COMPARE_VIEW_WORK* wk );
static void DeletePageBmpWin( COMPARE_VIEW_WORK* wk, int page );
static void CreateBmpWinForStatusPage( COMPARE_VIEW_WORK* wk );
static void DeleteBmpWinForStatusPage( COMPARE_VIEW_WORK* wk );
static void UpdateConditionPointActors( COMPARE_VIEW_WORK* wk, int side );
static void HideConditionPointActors( COMPARE_VIEW_WORK* wk, int side );
static void CreateBmpWinForSkillPage( COMPARE_VIEW_WORK* wk );
static void DeleteBmpWinForSkillPage( COMPARE_VIEW_WORK* wk );
static inline u32 CalcCenteringXpos(GF_BGL_BMPWIN* win, u32 fontID, const STRBUF* str);
static void BmpWinTitleWriteCgx( COMPARE_VIEW_WORK* wk );
static void BmpWinTitleClearCgx( COMPARE_VIEW_WORK* wk );
static void UpdateBmpWinForStatusPage( COMPARE_VIEW_WORK* wk, int side );
static void UpdateBmpWinForSkillPage( COMPARE_VIEW_WORK* wk, int side );
static void SetupActors( COMPARE_VIEW_WORK* wk );
static void SetupPokeIconActors( COMPARE_VIEW_WORK* wk, u32 charpos );
static void CleanupActors( COMPARE_VIEW_WORK* wk );
static void UpdatePokeIcon( COMPARE_VIEW_WORK* wk );
static void UpdateBmpWinPokeName( COMPARE_VIEW_WORK* wk, int side );
static void PageButtonCtrlTask(TCB_PTR tcb, void* wk_adrs);






//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk_ptr_adrs		
 * @param   vwk		
 * @param   vpara		
 * @param   bgl		
 * @param   actsys		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL BoxAppView_CompareInit( COMPARE_VIEW_WORK** wk_ptr_adrs, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys, MSGDATA_MANAGER* msgman )
{
	if( BoxAppVPara_GetBoxMode(vpara) != BOX_MODE_COMPARE )
	{
		*wk_ptr_adrs = NULL;
		return TRUE;
	}
	else
	{
		COMPARE_VIEW_WORK*  wk = sys_AllocMemory(HEAPID_BOX_VIEW, sizeof(COMPARE_VIEW_WORK));

		if( wk )
		{
			wk->vwk = vwk;
			wk->vpara = vpara;
			wk->bgl = bgl;
			wk->actsys = actsys;
			wk->iconsys = BoxAppView_GetIconSysWork( vwk );

			wk->arrowScrnLoadPtrL = ArcUtil_ScrnDataGet(ARC_BOX_GRA, NARC_box_bg1_compare_L_lz_nscr, TRUE, &(wk->arrowScrnDataL), HEAPID_BOX_VIEW );
			wk->arrowScrnLoadPtrR = ArcUtil_ScrnDataGet(ARC_BOX_GRA, NARC_box_bg1_compare_R_lz_nscr, TRUE, &(wk->arrowScrnDataR), HEAPID_BOX_VIEW );

			wk->msgman = msgman; 
			wk->msgman_wazaname = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wazaname_dat, HEAPID_BOX_VIEW );
			wk->strbuf = STRBUF_Create( 32, HEAPID_BOX_VIEW );

			wk->pageButtonCtrlTask = NULL;


			*wk_ptr_adrs = wk;
			return TRUE;
		}

		return FALSE;
	}
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CompareQuit( COMPARE_VIEW_WORK* wk )
{
	if( wk )
	{
		sys_FreeMemoryEz( wk->arrowScrnLoadPtrL );
		sys_FreeMemoryEz( wk->arrowScrnLoadPtrR );
		MSGMAN_Delete(wk->msgman_wazaname);
		CleanupActors(wk);
		QuitBmpWin(wk);
		STRBUF_Delete( wk->strbuf );
		sys_FreeMemoryEz( wk );
	}
}






//------------------------------------------------------------------
/**
 * 画面構築
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_SetupCompare( COMPARE_VIEW_WORK* wk )
{
	if( wk )
	{
		UpdateArrowBgScreen( wk );

		ArcUtil_BgCharSet( ARC_BOX_GRA, NARC_box_compare_bg_sub_lz_ncgr, wk->bgl, FRM_SUB_COMPARE_PAGE1, 0, 0, TRUE, HEAPID_BOX_VIEW);
		ArcUtil_ScrnSet(ARC_BOX_GRA, NARC_box_compare_bg_sub_page1_lz_nscr, wk->bgl, FRM_SUB_COMPARE_PAGE1, 0, 0, TRUE, HEAPID_BOX_VIEW);
		ArcUtil_ScrnSet(ARC_BOX_GRA, NARC_box_compare_bg_sub_page2_lz_nscr, wk->bgl, FRM_SUB_COMPARE_PAGE2, 0, 0, TRUE, HEAPID_BOX_VIEW);
		ArcUtil_ScrnSet(ARC_BOX_GRA, NARC_box_compare_bg_sub_page3_lz_nscr, wk->bgl, FRM_SUB_COMPARE_PAGE3, 0, 0, TRUE, HEAPID_BOX_VIEW);
		ArcUtil_PalSet(ARC_BOX_GRA, NARC_box_compare_bg_nclr, PALTYPE_SUB_BG, 0, 0x20*4, HEAPID_BOX_VIEW);
		ArcUtil_PalSet(ARC_POKEICON, PokeIconPalArcIndexGet(), PALTYPE_SUB_OBJ, OBJPAL_COMPARE_POKEICON1*0x20,  4*0x20, HEAPID_BOX_VIEW );

		GF_BGL_ClearCharSet( FRM_SUB_COMPARE_BMPWIN, 0x20, 0, HEAPID_BOX_VIEW );
		GF_BGL_ScrFill( wk->bgl, FRM_SUB_COMPARE_BMPWIN, 0x0000, 0, 0, 32, 32, GF_BGL_SCRWRT_PALIN );

		EnableBackgroundBG( wk );
		InitBmpWin( wk );
		wk->prev_page = BoxAppVPara_GetComparePage(wk->vpara);

		GF_BGL_LoadScreenReq( wk->bgl, FRM_SUB_COMPARE_BMPWIN );

		SetupActors(wk);
	}
}


//------------------------------------------------------------------
/**
 * サイド変更
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_Compare_SwitchSide( COMPARE_VIEW_WORK* wk, BOOL buttonAnmFlag )
{
	if( wk )
	{
		int side = BoxAppVPara_GetCompareUpdateSide(wk->vpara);

		if( buttonAnmFlag )
		{
			CLACT_AnmChg( wk->actButton[side^1], ANM_SIDEBUTTON_PUSH );
			CLACT_AnmChg( wk->actButton[side], ANM_SIDEBUTTON_FREE );
		}
		else
		{
			CLACT_AnmChg( wk->actButton[side^1], ANM_SIDEBUTTON_HOLD );
			CLACT_AnmChg( wk->actButton[side], ANM_SIDEBUTTON_FREE );
		}

		UpdateArrowBgScreen( wk );
	}
}


//------------------------------------------------------------------
/**
 * カーソルが指しているポケモンのパラメータ更新開始
 *
 * @param   wk		
 */
//------------------------------------------------------------------
void BoxAppView_Compare_StartUpdate( COMPARE_VIEW_WORK* wk )
{
	UpdatePokeIcon( wk );

	if( wk )
	{
		int side = BoxAppVPara_GetCompareUpdateSide(wk->vpara);

		UpdateBmpWinPokeName( wk, side );


		switch( BoxAppVPara_GetComparePage(wk->vpara) ){
		case BOXAPP_COMPARE_PAGE_STATUS:
			UpdateBmpWinForStatusPage( wk, side );
			break;
		case BOXAPP_COMPARE_PAGE_CONDITION:
			UpdateConditionPointActors( wk, side );
			break;
		case BOXAPP_COMPARE_PAGE_SKILL:
			UpdateBmpWinForSkillPage( wk, side );
			break;
		}
	}
}
//------------------------------------------------------------------
/**
 * カーソルが指しているポケモンのパラメータ更新終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL BoxAppView_Compare_WaitUpdate( COMPARE_VIEW_WORK* wk )
{
	return TRUE;
}



//------------------------------------------------------------------
/**
 * ページ切り替え
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_Compare_ChangePage( COMPARE_VIEW_WORK* wk )
{
	if( wk )
	{
		wk->page_seq = 0;
		DeletePageBmpWin( wk, wk->prev_page );
		GF_BGL_LoadScreenReq( wk->bgl, FRM_SUB_COMPARE_BMPWIN );
	}
}
//------------------------------------------------------------------
/**
 * ページ切り替えの終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_Compare_WaitChangePage( COMPARE_VIEW_WORK* wk )
{
	if( wk )
	{
		switch( wk->page_seq ){
		case 0:
			EnableBackgroundBG( wk );
			wk->page_seq++;
			break;

		case 1:
			BmpWinTitleWriteCgx( wk );
			CreatePageBmpWin( wk );
			GF_BGL_LoadScreenReq( wk->bgl, FRM_SUB_COMPARE_BMPWIN );
			wk->page_seq++;
			break;

		case 2:
			return TRUE;
		}
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}



//==============================================================================================
//==============================================================================================

static void UpdateArrowBgScreen( COMPARE_VIEW_WORK* wk )
{
	NNSG2dScreenData* scrn = (BoxAppVPara_GetCompareUpdateSide(wk->vpara) == BOXAPP_COMPARE_SIDE_LEFT)? wk->arrowScrnDataL : wk->arrowScrnDataR;

	GF_BGL_ScrWriteExpand(wk->bgl, FRM_MAIN_STATUS,  0, 0, 6, 32, scrn->rawData,  0, 0, 32, 32);
	GF_BGL_ScrWriteExpand(wk->bgl, FRM_MAIN_STATUS, 26, 0, 6, 32, scrn->rawData, 26, 0, 32, 32);

	GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_STATUS );
}


static void EnableBackgroundBG( COMPARE_VIEW_WORK* wk )
{
	switch( BoxAppVPara_GetComparePage(wk->vpara) ){
	case BOXAPP_COMPARE_PAGE_STATUS:
		GF_BGL_VisibleSet( FRM_SUB_COMPARE_PAGE1, TRUE );
		GF_BGL_VisibleSet( FRM_SUB_COMPARE_PAGE2, FALSE );
		GF_BGL_VisibleSet( FRM_SUB_COMPARE_PAGE3, FALSE );
		break;
	case BOXAPP_COMPARE_PAGE_CONDITION:
		GF_BGL_VisibleSet( FRM_SUB_COMPARE_PAGE2, TRUE );
		GF_BGL_VisibleSet( FRM_SUB_COMPARE_PAGE1, FALSE );
		GF_BGL_VisibleSet( FRM_SUB_COMPARE_PAGE3, FALSE );
		break;
	case BOXAPP_COMPARE_PAGE_SKILL:
		GF_BGL_VisibleSet( FRM_SUB_COMPARE_PAGE3, TRUE );
		GF_BGL_VisibleSet( FRM_SUB_COMPARE_PAGE1, FALSE );
		GF_BGL_VisibleSet( FRM_SUB_COMPARE_PAGE2, FALSE );
		break;
	}
}


static void InitBmpWin( COMPARE_VIEW_WORK* wk )
{
	static const BMPWIN_DAT  windat[] = {
		{
			FRM_SUB_COMPARE_BMPWIN,
			BMPWIN_NAME_LEFT_X, BMPWIN_NAME_RIGHT_Y, BMPWIN_NAME_WIDTH, BMPWIN_NAME_HEIGHT,
			PAL_SUB_COMPARE_LEFT, BMPWIN_NAME_LEFT_CHARPOS
		},{
			FRM_SUB_COMPARE_BMPWIN,
			BMPWIN_NAME_RIGHT_X, BMPWIN_NAME_RIGHT_Y, BMPWIN_NAME_WIDTH, BMPWIN_NAME_HEIGHT,
			PAL_SUB_COMPARE_RIGHT, BMPWIN_NAME_RIGHT_CHARPOS
		},{
			FRM_SUB_COMPARE_BMPWIN,
			BMPWIN_TITLE_X, BMPWIN_TITLE_Y, BMPWIN_TITLE_WIDTH, BMPWIN_TITLE_HEIGHT,
			PAL_SUB_COMPARE_LEFT, BMPWIN_TITLE_CHARPOS
		}
	};

	int i;

	// chrbuf == NULL をウィンドウ未作成であるフラグとして使う
	for(i=0; i<WINID_MAX; i++)
	{
		wk->bmpwin[i].chrbuf = NULL;
	}

	for(i=0; i<NELEMS(windat); i++)
	{
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->bmpwin[WINID_NAME_LEFT+i], &windat[i] );
		GF_BGL_BmpWinMakeScrn( &wk->bmpwin[WINID_NAME_LEFT+i] );
	}

	BmpWinTitleWriteCgx(wk);
	GF_BGL_BmpWinDataFill( &wk->bmpwin[WINID_NAME_LEFT], BMPWIN_COL_GROUND );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[WINID_NAME_RIGHT], BMPWIN_COL_GROUND );

	for(i=0; i<NELEMS(windat); i++)
	{
		GF_BGL_BmpWinCgxOn(&wk->bmpwin[WINID_NAME_LEFT+i]);
	}

	CreatePageBmpWin( wk );
}

static void QuitBmpWin( COMPARE_VIEW_WORK* wk )
{
	int i;

	for(i=0; i<WINID_MAX; i++)
	{
		if( wk->bmpwin[i].chrbuf )
		{
			GF_BGL_BmpWinDel( &(wk->bmpwin[i]) );
		}
	}
}


static void CreatePageBmpWin( COMPARE_VIEW_WORK* wk )
{
	int page = BoxAppVPara_GetComparePage(wk->vpara);

	switch(BoxAppVPara_GetComparePage(wk->vpara)){
	case BOXAPP_COMPARE_PAGE_STATUS:
		CreateBmpWinForStatusPage( wk );
		UpdateBmpWinForStatusPage( wk, BOXAPP_COMPARE_SIDE_LEFT );
		UpdateBmpWinForStatusPage( wk, BOXAPP_COMPARE_SIDE_RIGHT );
		break;

	case BOXAPP_COMPARE_PAGE_CONDITION:
		UpdateConditionPointActors( wk, BOXAPP_COMPARE_SIDE_LEFT );
		UpdateConditionPointActors( wk, BOXAPP_COMPARE_SIDE_RIGHT );
		break;

	case BOXAPP_COMPARE_PAGE_SKILL:
		CreateBmpWinForSkillPage( wk );
		UpdateBmpWinForSkillPage( wk, BOXAPP_COMPARE_SIDE_LEFT );
		UpdateBmpWinForSkillPage( wk, BOXAPP_COMPARE_SIDE_RIGHT );
		break;
	}
	wk->prev_page = page;
}

static void DeletePageBmpWin( COMPARE_VIEW_WORK* wk, int page )
{
	switch(page){
	case BOXAPP_COMPARE_PAGE_STATUS:
		DeleteBmpWinForStatusPage( wk );
		BmpWinTitleClearCgx( wk );
		break;

	case BOXAPP_COMPARE_PAGE_CONDITION:
		HideConditionPointActors( wk, BOXAPP_COMPARE_SIDE_LEFT );
		HideConditionPointActors( wk, BOXAPP_COMPARE_SIDE_RIGHT );
		break;

	case BOXAPP_COMPARE_PAGE_SKILL:
		DeleteBmpWinForSkillPage( wk );
		BmpWinTitleClearCgx( wk );
		break;
	}
}


static void CreateBmpWinForStatusPage( COMPARE_VIEW_WORK* wk )
{
	static const BMPWIN_DAT  windat[] = {
		{
			FRM_SUB_COMPARE_BMPWIN,
			BMPWIN_STATUS_LEFT_X, BMPWIN_STATUS_RIGHT_Y, BMPWIN_STATUS_WIDTH, BMPWIN_STATUS_HEIGHT,
			PAL_SUB_COMPARE_LEFT, BMPWIN_STATUS_LEFT_CHARPOS
		},{
			FRM_SUB_COMPARE_BMPWIN,
			BMPWIN_STATUS_RIGHT_X, BMPWIN_STATUS_RIGHT_Y, BMPWIN_STATUS_WIDTH, BMPWIN_STATUS_HEIGHT,
			PAL_SUB_COMPARE_RIGHT, BMPWIN_STATUS_RIGHT_CHARPOS
		}
	};

	int i;

	for(i=0; i<NELEMS(windat); i++)
	{
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->bmpwin[WINID_STATUS_LEFT+i], &windat[i] );
		GF_BGL_BmpWinMakeScrn( &wk->bmpwin[WINID_STATUS_LEFT+i] );
		GF_BGL_BmpWinDataFill( &wk->bmpwin[WINID_STATUS_LEFT+i], BMPWIN_COL_GROUND );
	}
}
static void DeleteBmpWinForStatusPage( COMPARE_VIEW_WORK* wk )
{
	int i;

	for(i=WINID_STATUS_LEFT; i<=WINID_STATUS_RIGHT; i++)
	{
		if( wk->bmpwin[i].chrbuf )
		{
			GF_BGL_BmpWinClearScrn(&(wk->bmpwin[i]));
			GF_BGL_BmpWinDel(&(wk->bmpwin[i]));
			wk->bmpwin[i].chrbuf = NULL;
		}
	}
}

static void UpdateConditionPointActors( COMPARE_VIEW_WORK* wk, int side )
{
	enum {
		POINT_CENTER_X = 128,
		POINT_CENTER_Y = 100 + SUBSURFACE_YOFS,

		POINT_STYLE_X  = 128,
		POINT_STYLE_Y  =  54 + SUBSURFACE_YOFS,
		POINT_BEAUTY_X = 172,
		POINT_BEAUTY_Y =  86 + SUBSURFACE_YOFS,
		POINT_CUTE_X   = 155,
		POINT_CUTE_Y   = 136 + SUBSURFACE_YOFS,
		POINT_CLEVER_X = 100,
		POINT_CLEVER_Y = 136 + SUBSURFACE_YOFS,
		POINT_STRONG_X =  84,
		POINT_STRONG_Y =  86 + SUBSURFACE_YOFS,
	};

	#define ORGPOS_X(tx)	((POINT_CENTER_X<<FX32_SHIFT)+(((((tx)-POINT_CENTER_X)<<FX32_SHIFT)*10)/100))
	#define ORGPOS_Y(ty)	((POINT_CENTER_Y<<FX32_SHIFT)+(((((ty)-POINT_CENTER_Y)<<FX32_SHIFT)*10)/100))

	static const struct {
		fx32   org_x;
		fx32   org_y;
		fx32   top_x;
		fx32   top_y;
	}posTbl[] = {
		{ ORGPOS_X(POINT_STYLE_X),  ORGPOS_Y(POINT_STYLE_Y),  POINT_STYLE_X<<FX32_SHIFT,  POINT_STYLE_Y<<FX32_SHIFT  },
		{ ORGPOS_X(POINT_BEAUTY_X), ORGPOS_Y(POINT_BEAUTY_Y), POINT_BEAUTY_X<<FX32_SHIFT, POINT_BEAUTY_Y<<FX32_SHIFT },
		{ ORGPOS_X(POINT_CUTE_X)  , ORGPOS_Y(POINT_CUTE_Y),   POINT_CUTE_X<<FX32_SHIFT,   POINT_CUTE_Y<<FX32_SHIFT   },
		{ ORGPOS_X(POINT_CLEVER_X), ORGPOS_Y(POINT_CLEVER_Y), POINT_CLEVER_X<<FX32_SHIFT, POINT_CLEVER_Y<<FX32_SHIFT },
		{ ORGPOS_X(POINT_STRONG_X), ORGPOS_Y(POINT_STRONG_Y), POINT_STRONG_X<<FX32_SHIFT, POINT_STRONG_Y<<FX32_SHIFT },

	};

	const BOXAPP_COMPARE_POKE_STATUS* status;
	BOOL  pointPokeFlag, updateSideFlag, notEmptyFlag;

	status = BoxAppVPara_GetCompareStatus(wk->vpara, side);

	pointPokeFlag = BoxAppVPara_GetCursorPointPokeFlag(wk->vpara);
	updateSideFlag = (BoxAppVPara_GetCompareUpdateSide(wk->vpara) == side);
	notEmptyFlag = BoxAppVPara_GetCompareUpdatedSideFlag(wk->vpara, side);

	if(	(((pointPokeFlag==TRUE) && (updateSideFlag==TRUE) ) || ((updateSideFlag==FALSE) && (notEmptyFlag==TRUE)))
	&&	( status->tamago_flag == FALSE )
	){
		int i;
		VecFx32  mtx;
		const u16 *val = &status->style;

		mtx.z = 0;
		for(i=0; i<5; i++)
		{
			mtx.x = posTbl[i].org_x + (((posTbl[i].top_x-posTbl[i].org_x) / 256) * (int)(*val));
			mtx.y = posTbl[i].org_y + (((posTbl[i].top_y-posTbl[i].org_y) / 256) * (int)(*val));
			CLACT_SetMatrix( wk->actConditionPoint[side][i], &mtx );
			BoxAppView_ChangeDrawPriority( wk->actConditionPoint[side][i], 0 );
			BoxAppView_ChangeDrawPriority( wk->actConditionPoint[side^1][i], 1 );
			CLACT_SetDrawFlag( wk->actConditionPoint[side][i], TRUE );
			val++;
		}
	}
	else
	{
		HideConditionPointActors( wk, side );
	}

	#undef ORGPOS_X
	#undef ORGPOS_Y

}


static void HideConditionPointActors( COMPARE_VIEW_WORK* wk, int side )
{
	int i;

	for(i=0; i<5; i++)
	{
		CLACT_SetDrawFlag( wk->actConditionPoint[side][i], FALSE );
	}
}







static void CreateBmpWinForSkillPage( COMPARE_VIEW_WORK* wk )
{
	static const BMPWIN_DAT  windat[] = {
		{
			FRM_SUB_COMPARE_BMPWIN,
			BMPWIN_SKILL_LEFT_X, BMPWIN_SKILL_RIGHT_Y, BMPWIN_SKILL_WIDTH, BMPWIN_SKILL_HEIGHT,
			PAL_SUB_COMPARE_LEFT, BMPWIN_SKILL_LEFT_CHARPOS
		},{
			FRM_SUB_COMPARE_BMPWIN,
			BMPWIN_SKILL_RIGHT_X, BMPWIN_SKILL_RIGHT_Y, BMPWIN_SKILL_WIDTH, BMPWIN_SKILL_HEIGHT,
			PAL_SUB_COMPARE_RIGHT, BMPWIN_SKILL_RIGHT_CHARPOS
		}
	};

	int i;

	for(i=0; i<NELEMS(windat); i++)
	{
		GF_BGL_BmpWinAddEx( wk->bgl, &wk->bmpwin[WINID_SKILL_LEFT+i], &windat[i] );
		GF_BGL_BmpWinMakeScrn( &wk->bmpwin[WINID_SKILL_LEFT+i] );
		GF_BGL_BmpWinDataFill( &wk->bmpwin[WINID_SKILL_LEFT+i], BMPWIN_COL_GROUND );
	}
}
static void DeleteBmpWinForSkillPage( COMPARE_VIEW_WORK* wk )
{
	int i;

	for(i=WINID_SKILL_LEFT; i<=WINID_SKILL_RIGHT; i++)
	{
		if( wk->bmpwin[i].chrbuf )
		{
			GF_BGL_BmpWinClearScrn(&(wk->bmpwin[i]));
			GF_BGL_BmpWinDel(&(wk->bmpwin[i]));
			wk->bmpwin[i].chrbuf = NULL;
		}
	}
}



static inline u32 CalcCenteringXpos(GF_BGL_BMPWIN* win, u32 fontID, const STRBUF* str)
{
	return ((win->sizx * 8) - FontProc_GetPrintStrWidth(fontID, str, 0)) / 2;
}

static void BmpWinTitleWriteCgx( COMPARE_VIEW_WORK* wk )
{
	static const u16 strid_status[] = {
		msg_boxmes_02_01, msg_boxmes_02_02, msg_boxmes_02_03, msg_boxmes_02_04, msg_boxmes_02_05,
		msg_boxmes_02_06, msg_boxmes_02_07, msg_boxmes_02_08,
	};

	GF_BGL_BMPWIN* win = &wk->bmpwin[WINID_TITLE];
	int i;

	GF_BGL_BmpWinDataFill( win, BMPWIN_COL_GROUND );

	switch(BoxAppVPara_GetComparePage(wk->vpara)){
	case BOXAPP_COMPARE_PAGE_STATUS:
		for(i=0; i<NELEMS(strid_status); i++)
		{
			MSGMAN_GetString( wk->msgman, strid_status[i], wk->strbuf );
			GF_STR_PrintColor( win, FONT_SYSTEM, wk->strbuf, CalcCenteringXpos(win,FONT_SYSTEM,wk->strbuf),
				BMPWIN_TITLE_STR_OY+BMPWIN_TITLE_STR_HEIGHT*i,
				MSG_NO_PUT, GF_PRINTCOLOR_MAKE(BMPWIN_TITLE_COL_LETTER,BMPWIN_COL_SHADOW,BMPWIN_COL_GROUND), NULL);

		}
		break;
	case BOXAPP_COMPARE_PAGE_SKILL:
		MSGMAN_GetString( wk->msgman, msg_boxmes_02_09, wk->strbuf );
		GF_STR_PrintColor( win, FONT_SYSTEM, wk->strbuf, CalcCenteringXpos(win,FONT_SYSTEM,wk->strbuf), BMPWIN_TITLE_STR_OY,
				MSG_NO_PUT, GF_PRINTCOLOR_MAKE(BMPWIN_TITLE_COL_LETTER,BMPWIN_COL_SHADOW,BMPWIN_COL_GROUND), NULL);
		break;

	}

	GF_BGL_BmpWinCgxOn( win );
}

static void BmpWinTitleClearCgx( COMPARE_VIEW_WORK* wk )
{
	GF_BGL_BMPWIN* win = &wk->bmpwin[WINID_TITLE];
	GF_BGL_BmpWinDataFill( win, BMPWIN_COL_GROUND );
	GF_BGL_BmpWinCgxOn( win );
}



static void UpdateBmpWinForStatusPage( COMPARE_VIEW_WORK* wk, int side )
{
	GF_BGL_BMPWIN* stwin;
	const BOXAPP_COMPARE_POKE_STATUS* status;
	BOOL  pointPokeFlag, updateSideFlag, notEmptyFlag;

	stwin = &(wk->bmpwin[WINID_STATUS_LEFT + side]);
	status = BoxAppVPara_GetCompareStatus(wk->vpara, side);

	pointPokeFlag = BoxAppVPara_GetCursorPointPokeFlag(wk->vpara);
	updateSideFlag = (BoxAppVPara_GetCompareUpdateSide(wk->vpara) == side);
	notEmptyFlag = BoxAppVPara_GetCompareUpdatedSideFlag(wk->vpara, side);

	GF_BGL_BmpWinDataFill( stwin, BMPWIN_COL_GROUND );

	if(	((pointPokeFlag==TRUE) && (updateSideFlag==TRUE) )
	||	((updateSideFlag==FALSE) && (notEmptyFlag==TRUE))
	){
		int i;

		if( status->tamago_flag == FALSE )
		{
			const u16* val = &status->level;

			GF_STR_PrintColor(stwin, FONT_SYSTEM, status->character, CalcCenteringXpos(stwin,FONT_SYSTEM,status->character), 0,
				MSG_NO_PUT, GF_PRINTCOLOR_MAKE(BMPWIN_COL_LETTER,BMPWIN_COL_SHADOW,BMPWIN_COL_GROUND), NULL);

			for(i=0; i<7; i++)
			{
				STRBUF_SetNumber( wk->strbuf, val[i], 3, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT );
				GF_STR_PrintColor(stwin, FONT_SYSTEM, wk->strbuf,
					CalcCenteringXpos(stwin,FONT_SYSTEM,wk->strbuf), (1+i)*BMPWIN_STATUS_STR_HEIGHT,
					MSG_NO_PUT, GF_PRINTCOLOR_MAKE(BMPWIN_COL_LETTER,BMPWIN_COL_SHADOW,BMPWIN_COL_GROUND), NULL);

			}
		}
		else
		{
			MSGMAN_GetString( wk->msgman, msg_boxmes_02_10, wk->strbuf );
			for(i=0; i<8; i++)
			{
				GF_STR_PrintColor(stwin, FONT_SYSTEM, wk->strbuf,
					CalcCenteringXpos(stwin,FONT_SYSTEM,wk->strbuf), i*BMPWIN_STATUS_STR_HEIGHT,
					MSG_NO_PUT, GF_PRINTCOLOR_MAKE(BMPWIN_COL_LETTER,BMPWIN_COL_SHADOW,BMPWIN_COL_GROUND), NULL);
			}
		}
	}

	GF_BGL_BmpWinCgxOn( stwin );
}

static void UpdateBmpWinForSkillPage( COMPARE_VIEW_WORK* wk, int side )
{
	GF_BGL_BMPWIN* win;
	const BOXAPP_COMPARE_POKE_STATUS* status;
	BOOL  pointPokeFlag, updateSideFlag, notEmptyFlag;

	win = &(wk->bmpwin[WINID_SKILL_LEFT + side]);
	status = BoxAppVPara_GetCompareStatus(wk->vpara, side);

	pointPokeFlag = BoxAppVPara_GetCursorPointPokeFlag(wk->vpara);
	updateSideFlag = (BoxAppVPara_GetCompareUpdateSide(wk->vpara) == side);
	notEmptyFlag = BoxAppVPara_GetCompareUpdatedSideFlag(wk->vpara, side);


	GF_BGL_BmpWinDataFill( win, BMPWIN_COL_GROUND );

	if(	((pointPokeFlag==TRUE) && (updateSideFlag==TRUE) )
	||	((updateSideFlag==FALSE) && (notEmptyFlag==TRUE))
	){
		int i;

		if( status->tamago_flag == FALSE )
		{
			for(i=0; i<4; i++)
			{
				if( status->skill[i] )
				{
					MSGMAN_GetString( wk->msgman_wazaname, status->skill[i], wk->strbuf );

					GF_STR_PrintColor(win, FONT_SYSTEM, wk->strbuf, CalcCenteringXpos(win,FONT_SYSTEM, wk->strbuf), BMPWIN_SKILL_STR_OY+BMPWIN_SKILL_STR_HEIGHT*i,
						MSG_NO_PUT, GF_PRINTCOLOR_MAKE(BMPWIN_COL_LETTER,BMPWIN_COL_SHADOW,BMPWIN_COL_GROUND), NULL);
				}
			}
		}
		else
		{
			MSGMAN_GetString( wk->msgman, msg_boxmes_02_10, wk->strbuf );
			for(i=0; i<4; i++)
			{
				GF_STR_PrintColor(win, FONT_SYSTEM, wk->strbuf, CalcCenteringXpos(win,FONT_SYSTEM, wk->strbuf), BMPWIN_SKILL_STR_OY+BMPWIN_SKILL_STR_HEIGHT*i,
					MSG_NO_PUT, GF_PRINTCOLOR_MAKE(BMPWIN_COL_LETTER,BMPWIN_COL_SHADOW,BMPWIN_COL_GROUND), NULL);
			}
		}
	}

	GF_BGL_BmpWinCgxOn( win );

}

//==============================================================================================
//==============================================================================================


static void SetupActors( COMPARE_VIEW_WORK* wk )
{
	enum {
		OBJ_TRANSPOS = 0 * 0x20,
	};

	static const struct  {
		s16 x;
		s16 y;
	}button_pos[] = {
		{ 0,   SUBSURFACE_YOFS+184 },
		{ 256, SUBSURFACE_YOFS+184 },
	};

	NNSG2dImageProxy imgProxy;
	CLACT_HEADER  header;
	u32  charpos, i, j;


	wk->cellBuf = ArcUtil_CellBankDataGet(ARC_BOX_GRA, NARC_box_compare_button_lz_ncer, TRUE, &(wk->cellData), HEAPID_BOX_VIEW );
	wk->animBuf = ArcUtil_AnimBankDataGet(ARC_BOX_GRA, NARC_box_compare_button_lz_nanr, TRUE, &(wk->animData), HEAPID_BOX_VIEW );
	ArcUtil_PalSet(ARC_BOX_GRA, NARC_box_compare_button_nclr, PALTYPE_SUB_OBJ, 0, 0x20*3, HEAPID_BOX_VIEW);

	NNS_G2dInitImageProxy( &imgProxy );
	charpos = ArcUtil_CharSysLoad(ARC_BOX_GRA, NARC_box_compare_button_lz_ncgr, TRUE, CHAR_MAP_1D, 0, NNS_G2D_VRAM_TYPE_2DSUB,
					OBJ_TRANSPOS, HEAPID_BOX_VIEW, &imgProxy);

	BoxAppView_SetActHeader( &header, &imgProxy, BoxAppView_GetObjPlttProxy( wk->vwk ),
			wk->cellData, wk->animData, 1 );

	for(i=0; i<2; i++)
	{
		wk->actButton[i] = BoxAppView_AddActor( wk->actsys, &header, button_pos[i].x, button_pos[i].y, 0, NNS_G2D_VRAM_TYPE_2DSUB );
		CLACT_PaletteNoChg( wk->actButton[i], i );
		CLACT_AnmChg( wk->actButton[i], ANM_SIDEBUTTON_FREE );

		for(j=0; j<5; j++)
		{
			wk->actConditionPoint[i][j] = BoxAppView_AddActor( wk->actsys, &header, 0, 0, 0, NNS_G2D_VRAM_TYPE_2DSUB );
			CLACT_AnmChg( wk->actConditionPoint[i][j], ANM_CONDITION_POINT_L+i );
			CLACT_PaletteNoChg( wk->actConditionPoint[i][j], i );
			CLACT_SetDrawFlag( wk->actConditionPoint[i][j], FALSE );
		}

	}
	CLACT_SetFlip( wk->actButton[BOXAPP_COMPARE_SIDE_RIGHT], CLACT_FLIP_H );

	wk->actButtonPage = BoxAppView_AddActor( wk->actsys, &header, 128, 176+SUBSURFACE_YOFS, 0, NNS_G2D_VRAM_TYPE_2DSUB );
	CLACT_AnmChg( wk->actButtonPage, ANM_PAGEBUTTON_FREE );
	CLACT_PaletteNoChg( wk->actButtonPage, 2 );

	wk->pageButtonCtrlTask = TCB_Add(PageButtonCtrlTask, wk, TASKPRI_VIEW_COMMAND);

	SetupPokeIconActors( wk, charpos );
}

static void SetupPokeIconActors( COMPARE_VIEW_WORK* wk, u32 charpos )
{
	static const struct  {
		s16 x;
		s16 y;
	}pokeicon_pos[] = {
		{ 112, SUBSURFACE_YOFS+10 },
		{ 144, SUBSURFACE_YOFS+10 },
	};

	NNSG2dImageProxy imgProxy;
	CLACT_HEADER  header;
	int i;

	BoxAppView_SetActHeader( &header, &imgProxy, BoxAppView_GetObjPlttProxy( wk->vwk ),
			BoxAppView_IconSys_GetCellBank(wk->iconsys), BoxAppView_IconSys_GetAnimBank(wk->iconsys), 1 );

	for(i=0; i<2; i++)
	{
		wk->pokeActCharPos[i] = charpos+(i*BOXICON_CHAR_SIZE*0x20);
		NNS_G2dInitImageProxy( &imgProxy );
		NNS_G2dSetImageLocation(&imgProxy, NNS_G2D_VRAM_TYPE_2DSUB, wk->pokeActCharPos[i]);
		imgProxy.attr.mappingType = GXS_GetOBJVRamModeChar();
		wk->actPoke[i] = BoxAppView_AddActor( wk->actsys, &header, pokeicon_pos[i].x, pokeicon_pos[i].y, 1-i, NNS_G2D_VRAM_TYPE_2DSUB );
		CLACT_SetDrawFlag( wk->actPoke[i], FALSE );
	}




}


static void CleanupActors( COMPARE_VIEW_WORK* wk )
{
	int i, j;

	if( wk->pageButtonCtrlTask )
	{
		TCB_Delete( wk->pageButtonCtrlTask );
	}

	for(i=0; i<2; i++)
	{
		CLACT_Delete( wk->actPoke[i] );
		CLACT_Delete( wk->actButton[i] );

		for(j=0; j<5; j++)
		{
			CLACT_Delete( wk->actConditionPoint[i][j] );
		}
	}

	CLACT_Delete( wk->actButtonPage );

	sys_FreeMemoryEz( wk->cellBuf );
	sys_FreeMemoryEz( wk->animBuf );
}



static void UpdatePokeIcon( COMPARE_VIEW_WORK* wk )
{
	int side = BoxAppVPara_GetCompareUpdateSide(wk->vpara);
	const BOXAPP_COMPARE_POKE_STATUS* status = BoxAppVPara_GetCompareStatus(wk->vpara,side);
	CLACT_WORK_PTR act = wk->actPoke[side];
	POKEMON_PASO_PARAM* ppp = (POKEMON_PASO_PARAM*)(status->poke_data);
	NNSG2dCharacterData* charData;

	if( BoxAppVPara_GetCursorPointPokeFlag(wk->vpara) )
	{
		u32 palNo = OBJPAL_COMPARE_POKEICON1 + PokeIconPalNumGet( status->monsno, status->form_number, status->tamago_flag );

		BoxAppView_IconCharDataLoad(wk->iconsys, wk->iconCharBuf, PokeIconCgxArcIndexGet(ppp), sizeof(wk->iconCharBuf));
		NNS_G2dGetUnpackedCharacterData( wk->iconCharBuf, &charData );
		DC_FlushRange( charData->pRawData, BOXICON_CHAR_SIZE*0x20 );
		GXS_LoadOBJ( charData->pRawData, wk->pokeActCharPos[side], BOXICON_CHAR_SIZE*0x20 );
		CLACT_PaletteNoChg( act, palNo );
		CLACT_SetDrawFlag( act, TRUE );
	}
	else
	{
		CLACT_SetDrawFlag( act, FALSE );
	}
}

static void UpdateBmpWinPokeName( COMPARE_VIEW_WORK* wk, int side )
{
	GF_BGL_BMPWIN* namewin;

	side = BoxAppVPara_GetCompareUpdateSide(wk->vpara);
	namewin = &(wk->bmpwin[WINID_NAME_LEFT + side]);

	GF_BGL_BmpWinDataFill( namewin, BMPWIN_COL_GROUND );

	if( BoxAppVPara_GetCursorPointPokeFlag(wk->vpara) )
	{
		const BOXAPP_COMPARE_POKE_STATUS* status = BoxAppVPara_GetCompareStatus(wk->vpara, side);

		GF_STR_PrintColor(namewin, FONT_SYSTEM, status->nickname, CalcCenteringXpos(namewin,FONT_SYSTEM,status->nickname), 0,
			MSG_NO_PUT, GF_PRINTCOLOR_MAKE(BMPWIN_COL_LETTER,BMPWIN_COL_SHADOW,BMPWIN_COL_GROUND), NULL);
	}
	GF_BGL_BmpWinCgxOn( namewin );
}



//==============================================================================================
//==============================================================================================

static void PageButtonCtrlTask(TCB_PTR tcb, void* wk_adrs)
{
	COMPARE_VIEW_WORK* wk = wk_adrs;
	BOOL pushFlag = BoxAppVPara_GetComparePageButtonPushFlag(wk->vpara);

	if( CLACT_AnmGet(wk->actButtonPage) == ANM_PAGEBUTTON_FREE )
	{
		if(pushFlag)
		{
			CLACT_AnmChg(wk->actButtonPage, ANM_PAGEBUTTON_PUSH );
		}
	}
	else
	{
		if(pushFlag==FALSE)
		{
			CLACT_AnmChg(wk->actButtonPage, ANM_PAGEBUTTON_FREE );
		}
	}
}

