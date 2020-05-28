//============================================================================================
/**
 * @file	pms_input_view.c
 * @bfief	簡易会話入力画面
 * @author	taya
 * @date	06.01.24
 */
//============================================================================================
#include "common.h"
#include "gflib\tcb.h"
#include "gflib\bg_system.h"
#include "gflib\clact.h"
#include "system\clact_util.h"
#include "system\render_oam.h"
#include "system\brightness.h"
#include "system\arc_util.h"
#include "system\wipe.h"

#include "pms_input_prv.h"
#include "pms_input_view.h"
#include "pmsi.naix"

//==============================================================================================
//==============================================================================================


//==============================================================================================
//==============================================================================================
enum {
	STORE_COMMAND_MAX = 4,		///< 並列実行可能なコマンド総数

	FADE_FRAMES = 5,

};



//------------------------------------------------------
/**
 *  描画メインワーク
 */
//------------------------------------------------------
struct _PMS_INPUT_VIEW {
	TCB_PTR     mainTask;
	TCB_PTR     vintrTask;

	TCB_PTR     cmdTask[ STORE_COMMAND_MAX ];

	const PMS_INPUT_WORK*	main_wk;
	const PMS_INPUT_DATA*	data_wk;

	GF_BGL_INI*					bgl;
	CLACT_SET_PTR				actsys;
	CLACT_U_EASYRENDER_DATA		renddata;

	// メインとサブで２つずつ
	NNSG2dImageProxy			obj_image_proxy[2];
	NNSG2dImagePaletteProxy		obj_pltt_proxy[2];
	NNSG2dCellDataBank*			cellbank[2];
	NNSG2dCellAnimBankData*		anmbank[2];
	void*						cell_load_ptr[2];
	void*						anm_load_ptr[2];

	PMSIV_EDIT*			edit_wk;
	PMSIV_BUTTON*		button_wk;
	PMSIV_CATEGORY*		category_wk;
	PMSIV_WORDWIN*		wordwin_wk;
	PMSIV_SUB*			sub_wk;
};

//------------------------------------------------------
/**
 *  描画コマンドワーク
 */
//------------------------------------------------------
typedef struct {
	PMS_INPUT_VIEW*        vwk;
	const PMS_INPUT_WORK*  mwk;
	const PMS_INPUT_DATA*  dwk;

	u32   command_no;
	int   store_pos;
	int   seq;


}COMMAND_WORK;


//==============================================================
// Prototype
//==============================================================
static void PMSIView_MainTask( TCB_PTR tcb, void* wk_adrs );
static void PMSIView_VintrTask( TCB_PTR tcb, void* wk_adrs );
static void DeleteCommand( COMMAND_WORK* cwk );
static void Cmd_Init( TCB_PTR tcb, void* wk_adrs );
static void setup_obj_graphic( COMMAND_WORK* cwk );
static void Cmd_Quit( TCB_PTR tcb, void* wk_adrs );
static void setup_bg_params( COMMAND_WORK* cwk );
static void Cmd_FadeIn( TCB_PTR tcb, void* wk_adrs );
static void Cmd_UpdateEditArea( TCB_PTR tcb, void* wk_adrs );
static void Cmd_EditAreaToButton( TCB_PTR tcb, void* wk_adrs );
static void Cmd_ButtonToEditArea( TCB_PTR tcb, void* wk_adrs );
static void Cmd_EditAreaToCategory( TCB_PTR tcb, void* wk_adrs );
static void Cmd_ChangeCategoryModeDisable( TCB_PTR tcb, void* wk_adrs );
static void Cmd_ChangeCategoryModeEnable( TCB_PTR tcb, void* wk_adrs );
static void Cmd_CategoryToEditAra( TCB_PTR tcb, void* wk_adrs );
static void Cmd_CategoryToWordWin( TCB_PTR tcb, void* wk_adrs );
static void Cmd_WordWinToCategory( TCB_PTR tcb, void* wk_adrs );
static void Cmd_WordWinToEditArea( TCB_PTR tcb, void* wk_adrs );
static void Cmd_WordWinToButton( TCB_PTR tcb, void* wk_adrs );
static void Cmd_MoveEditAreaCursor( TCB_PTR tcb, void* wk_adrs );
static void Cmd_MoveButtonCursor( TCB_PTR tcb, void* wk_adrs );
static void Cmd_MoveCategoryCursor( TCB_PTR tcb, void* wk_adrs );
static void Cmd_MoveWordWinCursor( TCB_PTR tcb, void* wk_adrs  );
static void Cmd_ScrollWordWin( TCB_PTR tcb, void* wk_adrs  );
static void Cmd_DispMessageDefault( TCB_PTR tcb, void* wk_adrs );
static void Cmd_DispMessageOK( TCB_PTR tcb, void* wk_adrs );
static void Cmd_DispMessageCancel( TCB_PTR tcb, void* wk_adrs );
static void Cmd_DispMessageWarn( TCB_PTR tcb, void* wk_adrs );
static void Cmd_MoveMenuCursor( TCB_PTR tcb, void* wk_adrs );
static void Cmd_EraseMenu( TCB_PTR tcb, void* wk_adrs );
static void Cmd_ButtonUpHold(TCB_PTR tcb, void* wk_adrs);
static void Cmd_ButtonDownHold(TCB_PTR tcb, void* wk_adrs);
static void Cmd_ButtonUpRelease(TCB_PTR tcb, void* wk_adrs);
static void Cmd_ButtonDownRelease(TCB_PTR tcb, void* wk_adrs);



//------------------------------------------------------------------
/**
 * 
 *
 * @param   main_wk		
 * @param   data_wk		
 *
 * @retval  PMS_INPUT_VIEW*		
 */
//------------------------------------------------------------------
PMS_INPUT_VIEW*  PMSIView_Create(const PMS_INPUT_WORK* main_wk, const PMS_INPUT_DATA* data_wk)
{
	PMS_INPUT_VIEW*  vwk = sys_AllocMemory( HEAPID_PMS_INPUT_VIEW, sizeof(PMS_INPUT_VIEW) );

	if( vwk )
	{
		int i;

		sys_VBlankFuncChange( NULL, NULL );
		sys_HBlankIntrStop();

		vwk->main_wk = main_wk;
		vwk->data_wk = data_wk;

		NNS_G2dInitOamManagerModule();
		REND_OAMInit( 0, 128, 0, 32, 0, 128, 0, 32, HEAPID_PMS_INPUT_VIEW );
		vwk->actsys = CLACT_U_SetEasyInit( 128, &vwk->renddata, HEAPID_PMS_INPUT_VIEW );

		vwk->bgl = GF_BGL_BglIniAlloc( HEAPID_PMS_INPUT_VIEW );

		vwk->mainTask = TCB_Add( PMSIView_MainTask, vwk, TASKPRI_VIEW_MAIN );
		vwk->vintrTask = PMSIView_AddVTask( PMSIView_VintrTask, vwk, VTASKPRI_MAIN );
		for(i=0; i<STORE_COMMAND_MAX; i++)
		{
			vwk->cmdTask[i] = NULL;
		}

	}

	return vwk;
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   vwk		
 *
 */
//------------------------------------------------------------------
void PMSIView_Delete( PMS_INPUT_VIEW* vwk )
{
	if( vwk )
	{
		int i;

		sys_VBlankFuncChange(NULL, NULL);

		for(i=0; i<STORE_COMMAND_MAX; i++)
		{
			if( vwk->cmdTask[i] )
			{
				TCB_Delete( vwk->cmdTask[i] );
			}
		}

		TCB_Delete( vwk->mainTask );
		TCB_Delete( vwk->vintrTask );

		REND_OAM_Delete();
		CLACT_DestSet( vwk->actsys );

		sys_FreeMemoryEz( vwk->bgl );
		sys_FreeMemoryEz( vwk );
	}
}

//==============================================================================================
//==============================================================================================


//------------------------------------------------------------------
/**
 * V Blank 動作タスクをセットする
 *
 * @param   func		
 * @param   wk		
 * @param   pri		
 *
 * @retval  TCB_PTR		
 */
//------------------------------------------------------------------
TCB_PTR PMSIView_AddVTask( TCB_FUNC func, void* wk, int pri )
{
#ifdef PMSI_FPS_60
	return VIntrTCB_Add( func, wk, pri );
#else
	return VWaitTCB_Add( func, wk, pri );
#endif
}


//------------------------------------------------------------------
/**
 * メインタスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void PMSIView_MainTask( TCB_PTR tcb, void* wk_adrs )
{
	// 3D 関連の処理が無いのでなんにもしてない…
}

//------------------------------------------------------------------
/**
 * V Blank タスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void PMSIView_VintrTask( TCB_PTR tcb, void* wk_adrs )
{
	PMS_INPUT_VIEW* vwk = wk_adrs;

	CLACT_Draw( vwk->actsys );
	REND_OAMTrans();		// レンダラ共有OAMマネージャVram転送
	OS_SetIrqCheckFlag( OS_IE_V_BLANK );
}

//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * コマンド登録
 *
 * @param   vwk		
 * @param   cmd		
 *
 */
//------------------------------------------------------------------
void PMSIView_SetCommand( PMS_INPUT_VIEW* vwk, int cmd )
{
	static const TCB_FUNC  func_tbl[] = {
		Cmd_Init,
		Cmd_Quit,
		Cmd_FadeIn,

		Cmd_UpdateEditArea,
		Cmd_EditAreaToButton,
		Cmd_ButtonToEditArea,
		Cmd_EditAreaToCategory,
		Cmd_CategoryToEditAra,
		Cmd_CategoryToWordWin,
		Cmd_WordWinToCategory,
		Cmd_WordWinToEditArea,
		Cmd_WordWinToButton,

		Cmd_MoveEditAreaCursor,
		Cmd_MoveButtonCursor,
		Cmd_MoveCategoryCursor,
		Cmd_MoveWordWinCursor,
		Cmd_ScrollWordWin,

		Cmd_DispMessageDefault,
		Cmd_DispMessageOK,
		Cmd_DispMessageCancel,
		Cmd_DispMessageWarn,
		Cmd_MoveMenuCursor,
		Cmd_EraseMenu,

		Cmd_ChangeCategoryModeDisable,
		Cmd_ChangeCategoryModeEnable,

		Cmd_ButtonUpHold,
		Cmd_ButtonDownHold,
		Cmd_ButtonUpRelease,
		Cmd_ButtonDownRelease,


	};



	if( cmd < NELEMS(func_tbl) )
	{
		COMMAND_WORK* cwk = sys_AllocMemory( HEAPID_PMS_INPUT_VIEW, sizeof(COMMAND_WORK) );

		if( cwk )
		{
			int i;

			cwk->seq = 0;
			cwk->command_no = cmd;
			cwk->vwk = vwk;
			cwk->mwk = vwk->main_wk;
			cwk->dwk = vwk->data_wk;

			for(i=0; i<STORE_COMMAND_MAX; i++)
			{
				if( vwk->cmdTask[i] == NULL )
				{
					cwk->store_pos = i;
					vwk->cmdTask[i] = TCB_Add( func_tbl[cmd], cwk, TASKPRI_VIEW_COMMAND );
					break;
				}
			}
		}
	}
	else
	{
		GF_ASSERT_MSG(0, "cmd=%d", cmd);
	}

}
//------------------------------------------------------------------
/**
 * コマンド終了待ち（全てのコマンドが終了するのを待つ）
 *
 * @param   vwk		描画メインワーク
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL PMSIView_WaitCommandAll( PMS_INPUT_VIEW* vwk )
{
	int i;

	for(i=0; i<STORE_COMMAND_MAX; i++)
	{
		if( vwk->cmdTask[i] != NULL )
		{
			return FALSE;
		}
	}

	return TRUE;
}
//------------------------------------------------------------------
/**
 * コマンド終了待ち（指定ナンバーのコマンドが終了するのを待つ）
 *
 * @param   vwk		描画メインワーク
 * @param   cmd		コマンドナンバー
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL PMSIView_WaitCommand( PMS_INPUT_VIEW* vwk, int cmd )
{
	int i;

	for(i=0; i<STORE_COMMAND_MAX; i++)
	{
		if( vwk->cmdTask[i] != NULL )
		{
			COMMAND_WORK* cwk = TCB_GetWork( vwk->cmdTask[i] );
			if( cwk->command_no == cmd )
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}
//------------------------------------------------------------------
/**
 * コマンド自殺
 *
 * @param   cwk		
 *
 */
//------------------------------------------------------------------
static void DeleteCommand( COMMAND_WORK* cwk )
{
	TCB_Delete( cwk->vwk->cmdTask[ cwk->store_pos ] );
	cwk->vwk->cmdTask[ cwk->store_pos ] = NULL;
	sys_FreeMemoryEz( cwk );
}


//==============================================================================================
//==============================================================================================

//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：画面構築
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_Init( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* cwk = wk_adrs;

	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane( 0 );
	GXS_SetVisiblePlane( 0 );

	GX_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_1D_64K );
	GXS_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_1D_32K );

	setup_bg_params( cwk );
	setup_obj_graphic( cwk );

	cwk->vwk->edit_wk = PMSIV_EDIT_Create( cwk->vwk, cwk->mwk, cwk->dwk );
	PMSIV_EDIT_SetupGraphicDatas( cwk->vwk->edit_wk );

	cwk->vwk->button_wk = PMSIV_BUTTON_Create( cwk->vwk, cwk->mwk, cwk->dwk );
	PMSIV_BUTTON_SetupGraphicDatas( cwk->vwk->button_wk );

	cwk->vwk->category_wk = PMSIV_CATEGORY_Create( cwk->vwk, cwk->mwk, cwk->dwk );
	PMSIV_CATEGORY_SetupGraphicDatas( cwk->vwk->category_wk );

	cwk->vwk->wordwin_wk = PMSIV_WORDWIN_Create( cwk->vwk, cwk->mwk, cwk->dwk );
	PMSIV_WORDWIN_SetupGraphicDatas( cwk->vwk->wordwin_wk );

	cwk->vwk->sub_wk = PMSIV_SUB_Create( cwk->vwk, cwk->mwk, cwk->dwk );
	PMSIV_SUB_SetupGraphicDatas( cwk->vwk->sub_wk );

	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GX_DispOn();


	DeleteCommand(cwk);
}
//------------------------------------------------------------------
/**
 * OBJグラフィックデータ転送
 *
 * @param   cwk		
 *
 */
//------------------------------------------------------------------
static void setup_obj_graphic( COMMAND_WORK* cwk )
{
	PMS_INPUT_VIEW* vwk = cwk->vwk;

	NNS_G2dInitImagePaletteProxy( &(vwk->obj_pltt_proxy[PMSIV_LCD_MAIN]) );
	NNS_G2dInitImagePaletteProxy( &(vwk->obj_pltt_proxy[PMSIV_LCD_SUB]) );

	NNS_G2dInitImageProxy( &(vwk->obj_image_proxy[PMSIV_LCD_MAIN]) );
	NNS_G2dInitImageProxy( &(vwk->obj_image_proxy[PMSIV_LCD_SUB]) );

	ArcUtil_CharSysLoad(ARC_PMSI_GRAPHIC, NARC_pmsi_obj_main_lz_ncgr, TRUE, CHAR_MAP_1D, 0,
					NNS_G2D_VRAM_TYPE_2DMAIN, 0, HEAPID_PMS_INPUT_VIEW, &(vwk->obj_image_proxy[PMSIV_LCD_MAIN]) );

	ArcUtil_PalSysLoad(ARC_PMSI_GRAPHIC, NARC_pmsi_obj_main_nclr, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 
			HEAPID_PMS_INPUT_VIEW, &(vwk->obj_pltt_proxy[PMSIV_LCD_MAIN]));


	vwk->cell_load_ptr[PMSIV_LCD_MAIN] = ArcUtil_CellBankDataGet(ARC_PMSI_GRAPHIC, NARC_pmsi_obj_main_lz_ncer, TRUE,
				&(vwk->cellbank[PMSIV_LCD_MAIN]), HEAPID_PMS_INPUT_VIEW );

	vwk->anm_load_ptr[PMSIV_LCD_MAIN] = ArcUtil_AnimBankDataGet(ARC_PMSI_GRAPHIC, NARC_pmsi_obj_main_lz_nanr, TRUE,
				&(vwk->anmbank[PMSIV_LCD_MAIN]), HEAPID_PMS_INPUT_VIEW );

	vwk->cell_load_ptr[PMSIV_LCD_SUB] = NULL;
	vwk->anm_load_ptr[PMSIV_LCD_SUB] = NULL;
}


//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：描画終了
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_Quit( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* cwk = wk_adrs;
	PMS_INPUT_VIEW* vwk = cwk->vwk;

	switch( cwk->seq ){
	case 0:
		WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, FADE_FRAMES, 1, 
			HEAPID_PMS_INPUT_VIEW );
		cwk->seq++;
		break;

	case 1:
		if( WIPE_SYS_EndCheck() )
		{
			int i;

			PMSIV_EDIT_Delete( cwk->vwk->edit_wk );
			PMSIV_BUTTON_Delete( cwk->vwk->button_wk );
			PMSIV_CATEGORY_Delete( cwk->vwk->category_wk );
			PMSIV_WORDWIN_Delete( cwk->vwk->wordwin_wk );
			PMSIV_SUB_Delete( cwk->vwk->sub_wk );

			for(i=0; i<2; i++)
			{
				if( vwk->cell_load_ptr[i] != NULL )
				{
					sys_FreeMemoryEz( vwk->cell_load_ptr[i] );
				}
				if( vwk->anm_load_ptr[i] != NULL )
				{
					sys_FreeMemoryEz( vwk->anm_load_ptr[i] );
				}
			}

			GF_BGL_BGControlExit( vwk->bgl, FRM_MAIN_EDITAREA );
			GF_BGL_BGControlExit( vwk->bgl, FRM_MAIN_CATEGORY );
			GF_BGL_BGControlExit( vwk->bgl, FRM_MAIN_WORDWIN );
			GF_BGL_BGControlExit( vwk->bgl, FRM_MAIN_BUTTON );
			GF_BGL_BGControlExit( vwk->bgl, FRM_SUB_BG );


			DeleteCommand(cwk);
		}
		break;
	}
}


//--------------------------------------------------------------
/**
 * BG システム設定
 *
 * @param   cwk		
 */
//--------------------------------------------------------------
static void setup_bg_params( COMMAND_WORK* cwk )
{
	static const GF_BGL_DISPVRAM bank_data = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
	};
	static const GF_BGL_SYS_HEADER sys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
	};

	// BG0 MAIN
	static const GF_BGL_BGCNT_HEADER header_main0 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xd800, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 0, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	// BG1 MAIN
	static const GF_BGL_BGCNT_HEADER header_main1 = {
		0, 0, 0x1000, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x10000,
		GX_BG_EXTPLTT_01, 1, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	// BG2 MAIN
	static const GF_BGL_BGCNT_HEADER header_main2 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x18000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	// BG3 MAIN
	static const GF_BGL_BGCNT_HEADER header_main3 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x08000,
		GX_BG_EXTPLTT_01, 3, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	// BG0 SUB
	static const GF_BGL_BGCNT_HEADER header_sub0 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 0, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	PMS_INPUT_VIEW* vwk = cwk->vwk;


	GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
	GX_SetGraphicsMode( GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_3D);

	GF_Disp_SetBank( &bank_data );
	GF_BGL_InitBG( &sys_data );


	GF_BGL_BGControlSet( vwk->bgl, FRM_MAIN_EDITAREA,  &header_main0, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( vwk->bgl, FRM_MAIN_CATEGORY,  &header_main1, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( vwk->bgl, FRM_MAIN_WORDWIN,   &header_main2, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( vwk->bgl, FRM_MAIN_BUTTON,    &header_main3, GF_BGL_MODE_TEXT );

	GF_BGL_BGControlSet( vwk->bgl, FRM_SUB_BG, &header_sub0, GF_BGL_MODE_TEXT );
}


//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：フェードイン
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_FadeIn( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* cwk = wk_adrs;
	PMS_INPUT_VIEW* vwk = cwk->vwk;

	switch( cwk->seq ){
	case 0:
		WIPE_SYS_Start(WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, FADE_FRAMES, 1, 
			HEAPID_PMS_INPUT_VIEW );

		cwk->seq++;
		break;

	case 1:
		if( WIPE_SYS_EndCheck() )
		{
			cwk->seq++;
		}
		break;

	default:
		DeleteCommand(cwk);
		break;
	}
}

//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：編集エリア更新
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_UpdateEditArea( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_EDIT_UpdateEditArea( vwk->edit_wk );
	PMSIV_EDIT_MoveCursor( vwk->edit_wk, PMSI_GetEditAreaCursorPos( wk->mwk ) );

	DeleteCommand( wk );
}

//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：編集エリアからコマンドボタンへ
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_EditAreaToButton( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_EDIT_VisibleCursor( vwk->edit_wk, FALSE );
	PMSIV_EDIT_StopArrow( vwk->edit_wk );

	PMSIV_BUTTON_VisibleCursor( vwk->button_wk, TRUE );
	PMSIV_BUTTON_MoveCursor( vwk->button_wk, PMSI_GetButtonCursorPos(vwk->main_wk) );

	DeleteCommand( wk );
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：コマンドボタンから編集エリアへ
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_ButtonToEditArea( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_BUTTON_VisibleCursor( vwk->button_wk, FALSE );
	PMSIV_EDIT_ActiveArrow( vwk->edit_wk );
	PMSIV_EDIT_VisibleCursor( vwk->edit_wk, TRUE );

	DeleteCommand( wk );
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：編集エリアからカテゴリ選択へ
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_EditAreaToCategory( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	switch( wk->seq ){
	case 0:
		PMSIV_EDIT_StopCursor( vwk->edit_wk );
		PMSIV_EDIT_StopArrow( vwk->edit_wk );
		PMSIV_CATEGORY_StartEnableBG( vwk->category_wk );
		wk->seq++;
		break;

	case 1:
		if( PMSIV_CATEGORY_WaitEnableBG( vwk->category_wk ) )
		{
			PMSIV_BUTTON_Hide( vwk->button_wk );
			PMSIV_CATEGORY_MoveCursor( vwk->category_wk, PMSI_GetCategoryCursorPos(vwk->main_wk) );
			PMSIV_CATEGORY_VisibleCursor( vwk->category_wk, TRUE );
			DeleteCommand( wk );
		}
		break;
	}
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：カテゴリモード切替え（編集エリア・コマンドボタン選択動作中）
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_ChangeCategoryModeDisable( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	switch( wk->seq ){
	case 0:
		PMSIV_SUB_ChangeCategoryButton( vwk->sub_wk );
		wk->seq++;
		break;

	case 1:
		PMSIV_CATEGORY_StartModeChange( vwk->category_wk );
		wk->seq++;
		break;

	case 2:
		if(	PMSIV_CATEGORY_WaitModeChange( vwk->category_wk ) 
		&&	PMSIV_SUB_WaitChangeCategoryButton( vwk->sub_wk )
		)
		{
			PMSIV_CATEGORY_ChangeModeBG( vwk->category_wk );
			DeleteCommand( wk );
		}
		break;
	}
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：カテゴリモード切替え（カテゴリ選択動作中）
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_ChangeCategoryModeEnable( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	switch( wk->seq ){
	case 0:
		PMSIV_SUB_ChangeCategoryButton( vwk->sub_wk );
		wk->seq++;
		break;

	case 1:
		PMSIV_CATEGORY_VisibleCursor( vwk->category_wk, FALSE );
		PMSIV_CATEGORY_StartModeChange( vwk->category_wk );
		wk->seq++;
		break;

	case 2:
		if( PMSIV_CATEGORY_WaitModeChange( vwk->category_wk ) )
		{
			PMSIV_CATEGORY_ChangeModeBG( vwk->category_wk );
			wk->seq++;
		}
		break;

	case 3:
		if( PMSIV_SUB_WaitChangeCategoryButton( vwk->sub_wk ) )
		{
			PMSIV_CATEGORY_MoveCursor( vwk->category_wk, PMSI_GetCategoryCursorPos(vwk->main_wk) );
			PMSIV_CATEGORY_VisibleCursor( vwk->category_wk, TRUE );
			DeleteCommand( wk );
		}
		break;
	}
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：カテゴリ選択から編集エリアへ
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_CategoryToEditAra( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	switch( wk->seq ){
	case 0:
		PMSIV_BUTTON_Appear( vwk->button_wk );
		PMSIV_CATEGORY_VisibleCursor( vwk->category_wk, FALSE );
		PMSIV_CATEGORY_StartDisableBG( vwk->category_wk );
		wk->seq++;
		break;

	case 1:
		if( PMSIV_CATEGORY_WaitDisableBG( vwk->category_wk ) )
		{
			PMSIV_EDIT_ActiveArrow( vwk->edit_wk );
			PMSIV_EDIT_ActiveCursor( vwk->edit_wk );
			DeleteCommand( wk );
		}
		break;
	}
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：カテゴリ選択から単語選択へ
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_CategoryToWordWin( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	switch( wk->seq ){
	case 0:
		PMSIV_WORDWIN_SetupWord( vwk->wordwin_wk );
		PMSIV_CATEGORY_VisibleCursor( vwk->category_wk, FALSE );
		PMSIV_CATEGORY_StartFadeOut( vwk->category_wk );
		wk->seq++;
		break;

	case 1:
		if( PMSIV_CATEGORY_WaitFadeOut( vwk->category_wk ) )
		{
			PMSIV_WORDWIN_StartFadeIn( vwk->wordwin_wk );
			wk->seq++;
		}
		break;

	case 2:
		if( PMSIV_WORDWIN_WaitFadeIn( vwk->wordwin_wk ) )
		{
			PMSIV_WORDWIN_MoveCursor( vwk->wordwin_wk, PMSI_GetWordWinCursorPos(vwk->main_wk) );
			PMSIV_WORDWIN_VisibleCursor( vwk->wordwin_wk, TRUE );
			PMSIV_SUB_VisibleArrowButton( vwk->sub_wk, TRUE );
			DeleteCommand( wk );
		}
		break;
	}
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：単語選択からカテゴリ選択へ
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_WordWinToCategory( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	switch( wk->seq ){
	case 0:
		PMSIV_SUB_ChangeCategoryButton( vwk->sub_wk );
		wk->seq++;
		break;

	case 1:
		PMSIV_WORDWIN_VisibleCursor( vwk->wordwin_wk, FALSE );
		PMSIV_SUB_VisibleArrowButton( vwk->sub_wk, FALSE );
		PMSIV_WORDWIN_StartFadeOut( vwk->wordwin_wk );
		wk->seq++;
		break;

	case 2:
		if( PMSIV_WORDWIN_WaitFadeOut( vwk->wordwin_wk ) )
		{
			PMSIV_CATEGORY_ChangeModeBG( vwk->category_wk );
			wk->seq++;
		}
		break;

	case 3:
		PMSIV_CATEGORY_StartFadeIn( vwk->category_wk );
		wk->seq++;
		break;

	case 4:
		if( PMSIV_CATEGORY_WaitFadeIn( vwk->category_wk ) 
		&&	PMSIV_SUB_WaitChangeCategoryButton( vwk->sub_wk )
		)
		{
			PMSIV_CATEGORY_MoveCursor( vwk->category_wk, PMSI_GetCategoryCursorPos(vwk->main_wk) );
			PMSIV_CATEGORY_VisibleCursor( vwk->category_wk, TRUE );
			DeleteCommand( wk );
		}
		break;
	}
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：単語決定後、編集エリアへ
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_WordWinToEditArea( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	switch( wk->seq ){
	case 0:
		PMSIV_BUTTON_Appear( vwk->button_wk );
		PMSIV_WORDWIN_VisibleCursor( vwk->wordwin_wk, FALSE );
		PMSIV_SUB_VisibleArrowButton( vwk->sub_wk, FALSE );
		PMSIV_WORDWIN_StartFadeOut( vwk->wordwin_wk );
		wk->seq++;
		break;

	case 1:
		if( PMSIV_WORDWIN_WaitFadeOut( vwk->wordwin_wk ) )
		{
			PMSIV_CATEGORY_SetDisableBG( vwk->category_wk );
			PMSIV_CATEGORY_StartFadeIn( vwk->category_wk );
			wk->seq++;
		}
		break;

	case 2:
		if( PMSIV_CATEGORY_WaitFadeIn( vwk->category_wk ) )
		{
			PMSIV_CATEGORY_StartBrightDown( vwk->category_wk );
			wk->seq++;
		}
		break;

	case 3:
		if( PMSIV_CATEGORY_WaitBrightDown( vwk->category_wk ) )
		{
			PMSIV_EDIT_UpdateEditArea( vwk->edit_wk );
			PMSIV_EDIT_VisibleCursor( vwk->edit_wk, TRUE );
			PMSIV_EDIT_ActiveArrow( vwk->edit_wk );
			PMSIV_EDIT_ActiveCursor( vwk->edit_wk );
			DeleteCommand( wk );
		}
	}
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：単語決定後、コマンドボタンへ
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_WordWinToButton( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	switch( wk->seq ){
	case 0:
		PMSIV_BUTTON_Appear( vwk->button_wk );
		PMSIV_WORDWIN_VisibleCursor( vwk->wordwin_wk, FALSE );
		PMSIV_SUB_VisibleArrowButton( vwk->sub_wk, FALSE );
		PMSIV_WORDWIN_StartFadeOut( vwk->wordwin_wk );
		wk->seq++;
		break;

	case 1:
		if( PMSIV_WORDWIN_WaitFadeOut( vwk->wordwin_wk ) )
		{
			PMSIV_CATEGORY_SetDisableBG( vwk->category_wk );
			PMSIV_CATEGORY_StartFadeIn( vwk->category_wk );
			wk->seq++;
		}
		break;

	case 2:
		if( PMSIV_CATEGORY_WaitFadeIn( vwk->category_wk ) )
		{
			PMSIV_CATEGORY_StartBrightDown( vwk->category_wk );
			wk->seq++;
		}
		break;

	case 3:
		if( PMSIV_CATEGORY_WaitBrightDown( vwk->category_wk ) )
		{
			PMSIV_EDIT_UpdateEditArea( vwk->edit_wk );
			PMSIV_EDIT_VisibleCursor( vwk->edit_wk, FALSE );
			PMSIV_BUTTON_VisibleCursor( vwk->button_wk, TRUE );
			DeleteCommand( wk );
		}
	}
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：編集エリアのカーソル移動
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_MoveEditAreaCursor( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;


	PMSIV_EDIT_MoveCursor( vwk->edit_wk, PMSI_GetEditAreaCursorPos(vwk->main_wk) );
	DeleteCommand( wk );
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：ボタンカーソル移動
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_MoveButtonCursor( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_BUTTON_MoveCursor( vwk->button_wk, PMSI_GetButtonCursorPos(vwk->main_wk) );
	DeleteCommand( wk );
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：カテゴリカーソル移動
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_MoveCategoryCursor( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_CATEGORY_MoveCursor( vwk->category_wk, PMSI_GetCategoryCursorPos(vwk->main_wk) );
	DeleteCommand( wk );
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：単語ウィンドウカーソル移動
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_MoveWordWinCursor( TCB_PTR tcb, void* wk_adrs  )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_WORDWIN_MoveCursor( vwk->wordwin_wk, PMSI_GetWordWinCursorPos(vwk->main_wk) );
	DeleteCommand( wk );
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：単語ウィンドウスクロール
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_ScrollWordWin( TCB_PTR tcb, void* wk_adrs  )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	switch( wk->seq ){
	case 0:
		PMSIV_WORDWIN_StartScroll( vwk->wordwin_wk, PMSI_GetWordWinScrollVector(vwk->main_wk) );
		wk->seq++;
		break;

	case 1:
		if( PMSIV_WORDWIN_WaitScroll( vwk->wordwin_wk ) )
		{
			PMSIV_SUB_VisibleArrowButton( vwk->sub_wk, TRUE );
			DeleteCommand( wk );
		}
		break;
	}
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：初期状態メッセージ表示
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_DispMessageDefault( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_EDIT_SetSystemMessage( vwk->edit_wk, PMSIV_MSG_GUIDANCE );

	DeleteCommand( wk );
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：これでいいですか？メッセージ表示
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_DispMessageOK( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_EDIT_SetSystemMessage( vwk->edit_wk, PMSIV_MSG_CONFIRM_DECIDE );
	PMSIV_EDIT_DispYesNoWin( vwk->edit_wk, PMSI_GetMenuCursorPos(wk->mwk) );

	if( PMSIV_BUTTON_GetCursorVisibleFlag( vwk->button_wk ) )
	{
		PMSIV_BUTTON_StopCursor( vwk->button_wk );
	}
	else
	{
		PMSIV_EDIT_StopCursor( vwk->edit_wk );
	}

	DeleteCommand( wk );
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：やめますか？メッセージ表示
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_DispMessageCancel( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_EDIT_SetSystemMessage( vwk->edit_wk, PMSIV_MSG_CONFIRM_CANCEL );
	PMSIV_EDIT_DispYesNoWin( vwk->edit_wk, PMSI_GetMenuCursorPos(wk->mwk) );

	if( PMSIV_BUTTON_GetCursorVisibleFlag( vwk->button_wk ) )
	{
		PMSIV_BUTTON_StopCursor( vwk->button_wk );
	}
	else
	{
		PMSIV_EDIT_StopCursor( vwk->edit_wk );
	}

	DeleteCommand( wk );
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：何かことばを入れてください！メッセージ表示
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_DispMessageWarn( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_EDIT_SetSystemMessage( vwk->edit_wk, PMSIV_MSG_WARN_INPUT );
	DeleteCommand( wk );
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：はい／いいえカーソル移動
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_MoveMenuCursor( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_EDIT_MoveYesNoCursor( vwk->edit_wk, PMSI_GetMenuCursorPos(wk->mwk) );
	DeleteCommand( wk );
}
//----------------------------------------------------------------------------------------------
/**
 * 描画コマンド：メニュー表示消去
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//----------------------------------------------------------------------------------------------
static void Cmd_EraseMenu( TCB_PTR tcb, void* wk_adrs )
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_EDIT_SetSystemMessage( vwk->edit_wk, PMSIV_MSG_GUIDANCE );
	PMSIV_EDIT_EraseYesNoWin( vwk->edit_wk );

	if( PMSIV_BUTTON_GetCursorVisibleFlag( vwk->button_wk ) )
	{
		PMSIV_BUTTON_ActiveCursor( vwk->button_wk );
	}
	else
	{
		PMSIV_EDIT_ActiveCursor( vwk->edit_wk );
	}

	DeleteCommand( wk );
}

//------------------------------------------------------------------
/**
 * 描画コマンド：三角ボタン（上）押した状態に
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void Cmd_ButtonUpHold(TCB_PTR tcb, void* wk_adrs)
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_SUB_ChangeArrowButton( vwk->sub_wk, SUB_BUTTON_UP, SUB_BUTTON_STATE_HOLD );

	DeleteCommand( wk );
}
//------------------------------------------------------------------
/**
 * 描画コマンド：三角ボタン（下）押した状態に
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void Cmd_ButtonDownHold(TCB_PTR tcb, void* wk_adrs)
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_SUB_ChangeArrowButton( vwk->sub_wk, SUB_BUTTON_DOWN, SUB_BUTTON_STATE_HOLD );

	DeleteCommand( wk );
}
//------------------------------------------------------------------
/**
 * 描画コマンド：三角ボタン（上）離した状態に
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void Cmd_ButtonUpRelease(TCB_PTR tcb, void* wk_adrs)
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_SUB_ChangeArrowButton( vwk->sub_wk, SUB_BUTTON_UP, SUB_BUTTON_STATE_RELEASE );

	DeleteCommand( wk );
}
//------------------------------------------------------------------
/**
 * 描画コマンド：三角ボタン（下）離した状態に
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void Cmd_ButtonDownRelease(TCB_PTR tcb, void* wk_adrs)
{
	COMMAND_WORK* wk = wk_adrs;
	PMS_INPUT_VIEW* vwk = wk->vwk;

	PMSIV_SUB_ChangeArrowButton( vwk->sub_wk, SUB_BUTTON_DOWN, SUB_BUTTON_STATE_RELEASE );

	DeleteCommand( wk );
}



//==============================================================================================
// コントロールモジュールへの情報提供
//==============================================================================================
//------------------------------------------------------------------
/**
 * 文章モード時の、単語入力欄がいくつあるか取得
 * （文章解析を描画側で行っているため）
 *
 * @param   wk		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 PMSIView_GetSentenceEditPosMax( PMS_INPUT_VIEW* wk )
{
	return PMSIV_EDIT_GetWordPosMax( wk->edit_wk );
}







//==============================================================================================
// 下請けモジュールへの情報提供
//==============================================================================================

GF_BGL_INI* PMSIView_GetBGL( PMS_INPUT_VIEW* vwk )
{
	return vwk->bgl;
}

CLACT_SET_PTR  PMSIView_GetActSys( PMS_INPUT_VIEW* vwk )
{
	return vwk->actsys;
}

NNSG2dImageProxy* PMSIView_GetObjImageProxy( PMS_INPUT_VIEW* vwk, int lcd )
{
	return &(vwk->obj_image_proxy[lcd]);
}
NNSG2dImagePaletteProxy* PMSIView_GetObjPaletteProxy( PMS_INPUT_VIEW* vwk, int lcd )
{
	return &(vwk->obj_pltt_proxy[lcd]);
}

void PMSIView_SetupDefaultActHeader( PMS_INPUT_VIEW* vwk, CLACT_HEADER* header, u32 lcd, u32 bgpri )
{
	header->pImageProxy   = &vwk->obj_image_proxy[lcd];
	header->pPaletteProxy = &vwk->obj_pltt_proxy[lcd];
	header->pCellBank     = vwk->cellbank[lcd];
	header->pAnimBank     = vwk->anmbank[lcd];
	header->priority      = bgpri;

	header->pCharData = NULL;
	header->pMCBank = NULL;
	header->pMCABank = NULL;
	header->flag = FALSE;
}

CLACT_WORK_PTR PMSIView_AddActor( PMS_INPUT_VIEW* vwk, CLACT_HEADER* header, u32 x, u32 y, u32 actpri, int drawArea )
{
	CLACT_ADD_SIMPLE  add;
	CLACT_WORK_PTR    act;
	OSIntrMode        oldIntr;

	add.ClActSet = vwk->actsys;
	add.ClActHeader = header;
	add.mat.x = x * FX32_ONE;
	add.mat.y = y * FX32_ONE;
	add.mat.z = 0;
	add.pri = actpri;
	add.DrawArea = drawArea;
	add.heap = HEAPID_PMS_INPUT_VIEW;

	oldIntr = OS_DisableInterrupts();
	act = CLACT_AddSimple( &add );
	OS_RestoreInterrupts( oldIntr );

	if( act )
	{
		CLACT_SetAnmFlag( act, TRUE );
		CLACT_SetAnmFrame( act, PMSI_ANM_SPEED );
	}
	return act;
}


