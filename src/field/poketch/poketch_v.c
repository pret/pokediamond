//============================================================================================
/**
 * @file	poketch_v.c
 * @bfief	ポケッチ（メイン）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "tcb.h"
#include "system\lib_pack.h"
#include "system\snd_tool.h"

#include "field\poketch.h"
#include "poketch_prv.h"
#include "poketch_main.h"
#include "poketch_view.h"


//====================================================
// consts
//====================================================
#define CMD_STORE_MAX		(8)		// 並列動作する最大コマンド数

// キャラファイルの配置
enum {
	CHARNO_EFF_CLOSE1 = 0x95,
	CHARNO_EFF_CLOSE2,
	CHARNO_EFF_CLOSE3,
	CHARNO_EFF_CLOSE_END,
	CHARNO_EFF_OPEN1,
	CHARNO_EFF_OPEN2,
	CHARNO_EFF_OPEN3,



	CHARNO_BUTTON_FREETOP = 0x48,
	CHARNO_BUTTON_PRESSTOP = 0x4c,
	CHARNO_BUTTON_HOLDTOP = 0x50,

	CHARNO_LAMP_ON_TOP = 0x8a,
	CHARNO_LAMP_OFF_TOP = 0x8d,

};

// スクリーン配置
enum {
	SCRN_BUTTON_XPOS = 27,
	SCRN_BUTTON_YPOS = 11,
	SCRN_BUTTON_WIDTH = 4,
	SCRN_BUTTON_HEIGHT = 11,

	SCRN_LAMP_XPOS = 28,
	SCRN_LAMP_YPOS = 3,
	SCRN_LAMP_WIDTH = 3,
	SCRN_LAMP_HEIGHT = 3,

	SCRN_LAMP_SIZE = SCRN_LAMP_WIDTH * SCRN_LAMP_HEIGHT,
};

#define SCRN_BUTTON_SIZE	(SCRN_BUTTON_WIDTH * SCRN_BUTTON_HEIGHT)
#define BOARD_CHARDATA_WIDTH		(21)




//====================================================
// 
//====================================================
typedef struct {
	BOOL				enable;
	PACTSYS*			actsys;
	PACT_CLANM_PACK		clpack;
	PACT*				act[2];
}SKIPNUM_WORK;


//====================================================
// work main
//====================================================
struct _POKETCH_VIEW_WORK {
	const POKETCH_MAIN_VPARAM	*vpara;
	POKETCH_CMD_STORE			cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	u16   scrn_button_free[ SCRN_BUTTON_SIZE ];
	u16   scrn_button_press[ SCRN_BUTTON_SIZE ];
	u16   scrn_button_hold[ SCRN_BUTTON_SIZE ];


	NNSG2dOamManagerInstance   oamm_body;
	NNSG2dOamManagerInstance*  oamm;

	PACTSYS*    actsys;
	TCB_PTR		vwait_task;

	SKIPNUM_WORK		skip_num;

	GF_BGL_INI*   bgl;
	CONTACT_WORK* cwk;

	u16    app_palette[16*2*POKETCH_COLOR_TYPE_MAX];
	u16    work_palette[16];
};

//====================================================
// work command
//====================================================
typedef struct {
	u16  timer;
	u16  line;
}CMDWORK_EFFECT;

//====================================================
// BG 配置
//====================================================
#define  BOARD_CHARBASE	(GX_BG_CHARBASE_0x04000)
#define  BOARD_CHAROFS	(64)
#define  BOARD_SCRBASE	(GX_BG_SCRBASE_0x6000)
#define  BOARD_PALNO	(15)

#define  EFFECT_CHARBASE	(GX_BG_CHARBASE_0x04000)
#define  EFFECT_CHAROFS	(BOARD_CHAROFS)
#define  EFFECT_SCRBASE	(GX_BG_SCRBASE_0x6800)
#define  EFFECT_PALNO	(15)


//==============================================================
// Prototype
//==============================================================
static void PoketchViewItask(TCB_PTR tcb, void* wk_adrs );
static void LoadAppPalette( POKETCH_VIEW_WORK* vwk );
static void MakeButtonScrn( u16 *buf, u32 charno_top );
static void DeleteCommand(POKETCH_CMD_WORK *cwk);
static void CmdInit(TCB_PTR tcb, void *wk_adrs);
static void CmdEffOpen(TCB_PTR tcb, void *wk_adrs);
static void CmdEffClose(TCB_PTR tcb, void *wk_adrs);
static void CmdEffOpen2(TCB_PTR tcb, void *wk_adrs);
static void CmdEffClose2(TCB_PTR tcb, void *wk_adrs);
static void CmdButtonLock(TCB_PTR tcb, void *wk_adrs);
static void CmdButtonFree(TCB_PTR tcb, void *wk_adrs);
static void CmdButtonPush(TCB_PTR tcb, void *wk_adrs);
static void CmdSkipNumDisp(TCB_PTR tcb, void* wk_adrs );
static void CmdSkipNumUpdate(TCB_PTR tcb, void* wk_adrs );
static void CmdSkipNumEnd(TCB_PTR tcb, void* wk_adrs );
static void SkipNumActor_InitWork( SKIPNUM_WORK* skipNumWork, PACTSYS* actsys );
static void SkipNumActor_Setup( POKETCH_VIEW_WORK* vwk, SKIPNUM_WORK* skipNumWork );
static void SkipNumActor_LoadPalette( POKETCH_VIEW_WORK* vwk, u32 palno );
static void SkipNumActor_Update( SKIPNUM_WORK* skipNumWork, const POKETCH_MAIN_VPARAM* vpara );
static void SkipNumActor_Delete( SKIPNUM_WORK* skipNumWork );
static void CmdSleep( TCB_PTR tcb, void* wk_adrs );
static void CmdWake( TCB_PTR tcb, void* wk_adrs );
static void CmdQuit( TCB_PTR tcb, void *wk_adrs );

extern struct _POKETCH_WORK* GetPoketchMainWorkPtr(void);

extern TCB_PTR VWaitTCB_Add( TCB_FUNC func, void* work, u32 pri );
extern void VWaitTCB_Delete( TCB_PTR func );

//------------------------------------------------------------------
/**
 * ワーク領域の確保
 *
 * @param   wk_ptr		ワーク領域アドレスを保存するポインタ変数のアドレス
 * @param   vpara		描画用パラメータ（書き換え不可）
 *
 * @retval  BOOL		TRUEで成功／FALSEで失敗
 */
//------------------------------------------------------------------
BOOL  Poketch_MAIN_SetViewWork(POKETCH_VIEW_WORK** wk_ptr, const POKETCH_MAIN_VPARAM *vpara, NNSG2dOamManagerInstance* oamm, CONTACT_WORK* cwk )
{
	*wk_ptr = sys_AllocMemory(POKETCH_MAIN_VIEW_HEAPID, sizeof(POKETCH_VIEW_WORK));

	if(*wk_ptr != NULL)
	{
		POKETCH_VIEW_WORK* vwk = *wk_ptr;

		vwk->oamm = oamm;
		NNS_G2dResetOamManagerBuffer( vwk->oamm );
		vwk->actsys = PACT_SysCreate( vwk->oamm, POKETCH_MAIN_VIEW_HEAPID );
		if(vwk->actsys == NULL)
		{
			sys_FreeMemoryEz( *wk_ptr );
			*wk_ptr = NULL;
			return FALSE;
		}

		vwk->vpara = vpara;
		vwk->bgl = GF_BGL_BglIniAlloc( POKETCH_MAIN_VIEW_HEAPID );
		vwk->cwk = cwk;

		LoadAppPalette( vwk );

		SkipNumActor_InitWork(&vwk->skip_num, vwk->actsys);

		PoketchViewTool_CmdStoreInit( (*wk_ptr)->cmd_store,  CMD_STORE_MAX);

		MakeButtonScrn( (*wk_ptr)->scrn_button_free, BOARD_CHAROFS+CHARNO_BUTTON_FREETOP );
		MakeButtonScrn( (*wk_ptr)->scrn_button_press, BOARD_CHAROFS+CHARNO_BUTTON_PRESSTOP );
		MakeButtonScrn( (*wk_ptr)->scrn_button_hold, BOARD_CHAROFS+CHARNO_BUTTON_HOLDTOP );

		vwk->vwait_task = VWaitTCB_Add( PoketchViewItask, vwk, 0 );

		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * VBlank中に呼び出されるタスク
 *
 * @param   itask		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void PoketchViewItask(TCB_PTR tcb, void* wk_adrs )
{
	POKETCH_VIEW_WORK* vwk = (POKETCH_VIEW_WORK*)wk_adrs;

	PACT_SysMain( vwk->actsys );
}


//------------------------------------------------------------------
/**
 * 各アプリから呼ばれてアクターシステムポインタを返す
 *
 * @retval  NNSG2dOamManagerInstance*		
 */
//------------------------------------------------------------------
PACTSYS*  PoketchGetActSys( void )
{
	POKETCH_VIEW_WORK *wk = PoketchGetMainViewWork();
	return wk->actsys;
}

//------------------------------------------------------------------
/**
 * 各アプリから呼ばれてアクターシステムポインタを返す
 *
 * @retval  NNSG2dOamManagerInstance*		
 */
//------------------------------------------------------------------
GF_BGL_INI*  PoketchView_GetAppBglWork( void )
{
	POKETCH_VIEW_WORK *wk = PoketchGetMainViewWork();
	return wk->bgl;
}


//------------------------------------------------------------------
/**
 * アプリパレットデータをワークにロードしておく
 *
 * @param   vwk		
 *
 */
//------------------------------------------------------------------
static void LoadAppPalette( POKETCH_VIEW_WORK* vwk )
{
	NNSG2dPaletteData* pal;
	void* load_ptr;

	load_ptr = ArcUtil_PalDataGet( ARC_POKETCH_IMG, NARC_poketch_app_nclr, &pal, POKETCH_MAIN_VIEW_HEAPID );
	if( load_ptr )
	{
		MI_CpuCopy32( pal->pRawData, vwk->app_palette, POKETCH_COLOR_TYPE_MAX*0x40 );
		DC_FlushRange( vwk->app_palette, POKETCH_COLOR_TYPE_MAX*0x40 );
		sys_FreeMemoryEz( load_ptr );
	}
}

//------------------------------------------------------------------
/**
 * BG, OBJ の両VRAMに基本カラーデータを転送する
 *
 * @param   bg_palno		BG転送パレット位置ナンバー(0～16)
 * @param   obj_palno		OBJ転送パレット位置ナンバー(0～16)
 *
 */
//------------------------------------------------------------------
void PoketchView_SetBaseColorPalette( u32 bg_palno, u32 obj_palno )
{
	POKETCH_VIEW_WORK *vwk = PoketchGetMainViewWork();
	POKETCH_DATA*  savedata = PoketchGetSaveData(vwk->cwk);
	u32 color_type = PoketchData_GetColorType(savedata);

	GXS_LoadBGPltt( &vwk->app_palette[ color_type*32 ], bg_palno*0x20, 0x20 );
	GXS_LoadOBJPltt( &vwk->app_palette[ color_type*32 ], obj_palno, 0x20 );
}

//------------------------------------------------------------------
/**
 * BG, OBJ の両VRAMに高輝度カラーデータを転送する
 *
 * @param   bg_palno		BG転送パレット位置ナンバー(0～16)
 * @param   obj_palno		OBJ転送パレット位置ナンバー(0～16)
 *
 */
//------------------------------------------------------------------
void PoketchView_SetHighColorPalette( u32 bg_palno, u32 obj_palno )
{
	POKETCH_VIEW_WORK *vwk = PoketchGetMainViewWork();
	POKETCH_DATA*  savedata = PoketchGetSaveData(vwk->cwk);
	u32 color_type = PoketchData_GetColorType(savedata);

	GXS_LoadBGPltt( &vwk->app_palette[ color_type*32 + 16 ], 0, 0x20 );
	GXS_LoadOBJPltt( &vwk->app_palette[ color_type*32 + 16 ], 0, 0x20 );
}

//------------------------------------------------------------------
/**
 * 基本カラーデータを指定バッファにコピー（16色分）
 *
 * @param   dst		
 *
 */
//------------------------------------------------------------------
void PoketchView_GetColorPalette( u16* dst )
{
	POKETCH_VIEW_WORK *vwk = PoketchGetMainViewWork();
	POKETCH_DATA*  savedata = PoketchGetSaveData(vwk->cwk);
	u32 color_type = PoketchData_GetColorType(savedata);

	MI_CpuCopy16( &vwk->app_palette[ color_type*32 ], dst, 0x20 );
}

//------------------------------------------------------------------
/**
 * カラーパレットナンバーを変更する
 *
 * @param   num		
 *
 */
//------------------------------------------------------------------
void PoketchView_SetColorPaletteNumber( u32 num )
{
	POKETCH_VIEW_WORK *vwk = PoketchGetMainViewWork();
	POKETCH_DATA*  savedata = PoketchGetSaveData(vwk->cwk);

	PoketchData_SetColorType( savedata, num );
}

//------------------------------------------------------------------
/**
 * ワーク領域の開放
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void Poketch_MAIN_DeleteViewWork( POKETCH_VIEW_WORK *wk )
{
	if( wk )
	{
		SkipNumActor_Delete( &(wk->skip_num) );

		if( wk->actsys )
		{
			PACT_SysDelete( wk->actsys );
		}
		if( wk->bgl )
		{
			sys_FreeMemoryEz( wk->bgl );
		}
		if( wk->vwait_task )
		{
			TCB_Delete( wk->vwait_task );
		}

		sys_FreeMemoryEz( wk );
	}
}

//------------------------------------------------------------------
/**
 * ボタンスクリーンデータをバッファに作成
 *
 * @param   buf				バッファアドレス
 * @param   charno_top		基点となるキャラナンバー
 * @param   width			ボタン幅（キャラ単位）
 * @param   height			ボタン高さ（キャラ単位）
 *
 */
//------------------------------------------------------------------
static void MakeButtonScrn( u16 *buf, u32 charno_top )
{
	static const u16 charno_ofs[SCRN_BUTTON_WIDTH*SCRN_BUTTON_HEIGHT] = {
		(BOARD_CHARDATA_WIDTH*0),(BOARD_CHARDATA_WIDTH*0)+1,(BOARD_CHARDATA_WIDTH*0)+2,(BOARD_CHARDATA_WIDTH*0)+3,
		(BOARD_CHARDATA_WIDTH*1),(BOARD_CHARDATA_WIDTH*1)+1,(BOARD_CHARDATA_WIDTH*1)+2,(BOARD_CHARDATA_WIDTH*1)+3,
		(BOARD_CHARDATA_WIDTH*2),(BOARD_CHARDATA_WIDTH*2)+1,(BOARD_CHARDATA_WIDTH*2)+2,(BOARD_CHARDATA_WIDTH*2)+3,
		(BOARD_CHARDATA_WIDTH*2),(BOARD_CHARDATA_WIDTH*2)+1,(BOARD_CHARDATA_WIDTH*2)+2,(BOARD_CHARDATA_WIDTH*2)+3,
		(BOARD_CHARDATA_WIDTH*2),(BOARD_CHARDATA_WIDTH*2)+1,(BOARD_CHARDATA_WIDTH*2)+2,(BOARD_CHARDATA_WIDTH*2)+3,
		(BOARD_CHARDATA_WIDTH*2),(BOARD_CHARDATA_WIDTH*2)+1,(BOARD_CHARDATA_WIDTH*2)+2,(BOARD_CHARDATA_WIDTH*2)+3,
		(BOARD_CHARDATA_WIDTH*2),(BOARD_CHARDATA_WIDTH*2)+1,(BOARD_CHARDATA_WIDTH*2)+2,(BOARD_CHARDATA_WIDTH*2)+3,
		(BOARD_CHARDATA_WIDTH*2),(BOARD_CHARDATA_WIDTH*2)+1,(BOARD_CHARDATA_WIDTH*2)+2,(BOARD_CHARDATA_WIDTH*2)+3,
		(BOARD_CHARDATA_WIDTH*2),(BOARD_CHARDATA_WIDTH*2)+1,(BOARD_CHARDATA_WIDTH*2)+2,(BOARD_CHARDATA_WIDTH*2)+3,
		(BOARD_CHARDATA_WIDTH*3),(BOARD_CHARDATA_WIDTH*3)+1,(BOARD_CHARDATA_WIDTH*3)+2,(BOARD_CHARDATA_WIDTH*3)+3,
		(BOARD_CHARDATA_WIDTH*4),(BOARD_CHARDATA_WIDTH*4)+1,(BOARD_CHARDATA_WIDTH*4)+2,(BOARD_CHARDATA_WIDTH*4)+3,
	};
	int i;

	for(i=0; i<NELEMS(charno_ofs); i++)
	{
		buf[i] = (BOARD_PALNO<<12) | (charno_top + charno_ofs[i]);
	}
}



//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------

static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_MAIN_INIT,		CmdInit,		0 },
	{ CMD_MAIN_FIRSTOPEN,	CmdEffOpen,		sizeof(CMDWORK_EFFECT) },
	{ CMD_MAIN_EFFOPEN,		CmdEffOpen,		sizeof(CMDWORK_EFFECT) },
	{ CMD_MAIN_EFFOPEN2,	CmdEffOpen2,	sizeof(CMDWORK_EFFECT) }, 
	{ CMD_MAIN_EFFCLOSE,	CmdEffClose,	sizeof(CMDWORK_EFFECT) },
	{ CMD_MAIN_EFFCLOSE2,	CmdEffClose2,	sizeof(CMDWORK_EFFECT) }, 
	{ CMD_MAIN_BUTTONLOCK,	CmdButtonLock,	0 },
	{ CMD_MAIN_BUTTONFREE,	CmdButtonFree,	0 },
	{ CMD_MAIN_BUTTONPUSH,	CmdButtonPush,	0 },
	{ CMD_MAIN_SKIPNUM_DISP,CmdSkipNumDisp, 0 },
	{ CMD_MAIN_SKIPNUM_UPDATE,CmdSkipNumUpdate, 0 },
	{ CMD_MAIN_SKIPNUM_END,	CmdSkipNumEnd, 0 },
	{ CMD_MAIN_SLEEP,		CmdSleep,		0 },
	{ CMD_MAIN_WAKE,		CmdWake,		0 },
	{ CMD_MAIN_QUIT,		CmdQuit,	0 },
	{ CMD_NULL, NULL, 0 },		// CMD_NULL で終端とみなす
};

//------------------------------------------------------------------
/**
 * 描画コマンドのセット
 *
 * @param   cmd		コマンド
 *
 */
//------------------------------------------------------------------
void Poketch_MAIN_SetCommand(POKETCH_VIEW_WORK *wk, u32 cmd)
{
	PoketchViewTool_SetCommand(CmdTbl, cmd, wk, wk->vpara, wk->cmd_store, POKETCH_GRAPHIC_TASKPRI, POKETCH_MAIN_VIEW_HEAPID);
}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（単発）
 *
 * @param   cmd			コマンド
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Poketch_MAIN_WaitCommand(POKETCH_VIEW_WORK *wk, u32 cmd)
{
	return PoketchViewTool_WaitCommand(wk->cmd_store, cmd);
}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（全部）
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Poketch_MAIN_WaitCommandAll(POKETCH_VIEW_WORK *wk)
{
	return PoketchViewTool_WaitCommandAll(wk->cmd_store);
}

//------------------------------------------------------------------
/**
 * コマンド削除（コマンドタスクからのみ呼ばれる）
 *
 * @param   cwk		コマンドワーク
 *
 */
//------------------------------------------------------------------
static void DeleteCommand(POKETCH_CMD_WORK *cwk)
{
	POKETCH_VIEW_WORK *wk = PoketchViewTool_GetViewWork(cwk);
	PoketchViewTool_DelCommand( wk->cmd_store, cwk );
}

//------------------------------------------------------------------
/**
 * コマンド：画面初期構築
 *
 * @param   tcb			TCBポインタ
 * @param   wk_adrs		ワーク領域
 *
 */
//------------------------------------------------------------------
static void CmdInit(TCB_PTR tcb, void *wk_adrs)
{
	static const GF_BGL_BGCNT_HEADER header0 = {
		0, 0, 0x824, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		BOARD_SCRBASE, BOARD_CHARBASE,
		GX_BG_EXTPLTT_01, 0, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	static const GF_BGL_BGCNT_HEADER header1 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		EFFECT_SCRBASE, EFFECT_CHARBASE,
		GX_BG_EXTPLTT_01, 1, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	POKETCH_VIEW_WORK* vwk = PoketchViewTool_GetViewWork(wk_adrs);


// BG 設定
	GXS_SetGraphicsMode(GX_BGMODE_0);

	GX_SetBankForSubBG(GX_VRAM_SUB_BG_32_H);
	GX_SetBankForSubOBJ(GX_VRAM_SUB_OBJ_16_I);
	GXS_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_1D_32K );

// グラフィックロード（BG0  キャラはBG1と共有）
	GF_Disp_GXS_VisibleControlInit();
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_BGL_BGControlSet( vwk->bgl, GF_BGL_FRAME0_S, &header0, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( vwk->bgl, GF_BGL_FRAME1_S, &header1, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet(ARC_POKETCH_IMG, NARC_poketch_board_ncgr, vwk->bgl, GF_BGL_FRAME0_S,
		BOARD_CHAROFS, 0, TRUE, POKETCH_MAIN_VIEW_HEAPID);
	ArcUtil_ScrnSet(ARC_POKETCH_IMG, NARC_poketch_board_nscr, vwk->bgl, GF_BGL_FRAME0_S,
		0, 0, TRUE, POKETCH_MAIN_VIEW_HEAPID);
//	ArcUtil_PalSet(ARC_POKETCH_IMG, NARC_poketch_board_nclr, PALTYPE_SUB_BG,
//		BOARD_PALNO*0x20, 0x20, POKETCH_MAIN_VIEW_HEAPID);
	ArcUtil_PalSetEx(ARC_POKETCH_IMG, NARC_poketch_board_nclr, PALTYPE_SUB_BG,
		PoketchGetBoardType(vwk->cwk)*0x20, BOARD_PALNO*0x20, 0x20, POKETCH_MAIN_VIEW_HEAPID);

// BG1 スクリーンセット
	GF_BGL_ScrFill( vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS + CHARNO_EFF_CLOSE_END,
		0, 0, 32, 24, BOARD_PALNO );
	GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME1_S );

// パレットロード（BG0, 1 共有）

// Visible Plane 設定
	GXS_SetVisiblePlane(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_OBJ);
	GXS_SetVisibleWnd(GX_WNDMASK_NONE);

	DeleteCommand(wk_adrs);
}

//------------------------------------------------------------------
/**
 * コマンド：ブラックアウト状態からアプリ画面を開く演出
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdEffOpen(TCB_PTR tcb, void *wk_adrs)
{
	enum {
		EFF_INTERVAL = 0,		// 更新間隔（フレーム）
		LINE_OPEN_SPEED = 12,	// ラインが開く速度（本数単位）
		LINE_PER_CHAR = 4,		// １キャラあたり何ラインか
		LINE_MAX = POKETCH_MONITOR_SCRN_HEIGHT * LINE_PER_CHAR / 2,		// ライン最大数
	};

	CMDWORK_EFFECT *wk;
	POKETCH_VIEW_WORK* vwk;
	u32 seq;


	wk = PoketchViewTool_GetCmdWork(wk_adrs);
	vwk =  PoketchViewTool_GetViewWork(wk_adrs);
	seq = PoketchViewTool_GetSeq(wk_adrs);

	switch(seq){
	case 0:
		wk->timer = 0;
		wk->line = 0;
		PoketchViewTool_FwdSeq( wk_adrs );
		/* fallthru */
	case 1:
		if( ++(wk->timer) > EFF_INTERVAL )
		{
			u32  open_char, mid_line, scrn_xorg;

			wk->timer = 0;
			wk->line += LINE_OPEN_SPEED;
			if(wk->line > LINE_MAX)
			{
				wk->line = LINE_MAX;
			}

			open_char = wk->line / LINE_PER_CHAR;
			mid_line = wk->line % LINE_PER_CHAR;

			scrn_xorg = POKETCH_MONITOR_SCRN_YORG + (POKETCH_MONITOR_SCRN_HEIGHT / 2) - open_char;

			GF_BGL_ScrFill(
				vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS, POKETCH_MONITOR_SCRN_XORG, scrn_xorg,
				POKETCH_MONITOR_SCRN_WIDTH, open_char * 2, EFFECT_PALNO );

			if(mid_line)
			{
				GF_BGL_ScrFill(
					vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS + CHARNO_EFF_CLOSE_END + mid_line,
					POKETCH_MONITOR_SCRN_XORG, scrn_xorg - 1,
					POKETCH_MONITOR_SCRN_WIDTH, 1, EFFECT_PALNO );

				GF_BGL_ScrFill(
					vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS + CHARNO_EFF_CLOSE_END - mid_line,
					POKETCH_MONITOR_SCRN_XORG, scrn_xorg + open_char * 2,
					POKETCH_MONITOR_SCRN_WIDTH, 1, EFFECT_PALNO );
			}

			GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME1_S );

			if(wk->line == LINE_MAX)
			{
				PoketchViewTool_FwdSeq(wk_adrs);
			}

		}
		break;
	case 2:
		DeleteCommand( wk_adrs );
	}
}

//------------------------------------------------------------------
/**
 * コマンド：アプリ画面を閉じる演出
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdEffClose(TCB_PTR tcb, void *wk_adrs)
{
	enum {
		EFF_INTERVAL = 0,		// 更新間隔（フレーム）
		LINE_OPEN_SPEED = 8,	// ラインが開く速度（本数単位）
		LINE_PER_CHAR = 4,		// １キャラあたり何ラインか
		LINE_MAX = POKETCH_MONITOR_SCRN_HEIGHT * LINE_PER_CHAR / 2,		// ライン最大数
	};

	CMDWORK_EFFECT *wk;
	POKETCH_VIEW_WORK* vwk;
	u32 seq;

	wk = PoketchViewTool_GetCmdWork(wk_adrs);
	vwk =  PoketchViewTool_GetViewWork(wk_adrs);
	seq = PoketchViewTool_GetSeq(wk_adrs);

	switch(seq){
	case 0:
		wk->timer = 0;
		wk->line = 0;
		PoketchViewTool_FwdSeq( wk_adrs );
		/* fallthru */
	case 1:
		if( ++(wk->timer) > EFF_INTERVAL )
		{
			u32  close_char, mid_line, bottom_scrn_yorg;

			wk->timer = 0;
			wk->line += LINE_OPEN_SPEED;
			if(wk->line > LINE_MAX)
			{
				wk->line = LINE_MAX;
			}

			close_char = wk->line / LINE_PER_CHAR;
			mid_line = wk->line % LINE_PER_CHAR;

			bottom_scrn_yorg = POKETCH_MONITOR_SCRN_YORG + POKETCH_MONITOR_SCRN_HEIGHT - close_char;

			GF_BGL_ScrFill(
				vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS + CHARNO_EFF_CLOSE_END,
				POKETCH_MONITOR_SCRN_XORG, POKETCH_MONITOR_SCRN_YORG,
				POKETCH_MONITOR_SCRN_WIDTH, close_char, EFFECT_PALNO );

			GF_BGL_ScrFill(
				vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS + CHARNO_EFF_CLOSE_END,
				POKETCH_MONITOR_SCRN_XORG, bottom_scrn_yorg,
				POKETCH_MONITOR_SCRN_WIDTH, close_char, EFFECT_PALNO );

			if(mid_line)
			{
				mid_line--;

				GF_BGL_ScrFill(
					vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS + CHARNO_EFF_OPEN3 - mid_line,
					POKETCH_MONITOR_SCRN_XORG, 0,
					POKETCH_MONITOR_SCRN_WIDTH, 1, EFFECT_PALNO );

				GF_BGL_ScrFill(
					vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS + CHARNO_EFF_CLOSE1 + mid_line,
					POKETCH_MONITOR_SCRN_XORG, bottom_scrn_yorg - 1,
					POKETCH_MONITOR_SCRN_WIDTH, 1, EFFECT_PALNO );
			}

			GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME1_S );

			if(wk->line == LINE_MAX)
			{
				PoketchViewTool_FwdSeq(wk_adrs);
			}

		}
		break;
	case 2:
		DeleteCommand( wk_adrs );
	}
}

//------------------------------------------------------------------
/**
 * 
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdEffOpen2(TCB_PTR tcb, void *wk_adrs)
{
	CMDWORK_EFFECT *wk;
	POKETCH_VIEW_WORK* vwk;
	u32 seq;

	wk = PoketchViewTool_GetCmdWork(wk_adrs);
	vwk =  PoketchViewTool_GetViewWork(wk_adrs);
	seq = PoketchViewTool_GetSeq(wk_adrs);

	if(seq < 4)
	{
		GF_BGL_ScrFill(
			vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS + CHARNO_EFF_CLOSE_END - seq - 1,
			POKETCH_MONITOR_SCRN_XORG, POKETCH_MONITOR_SCRN_YORG,
			POKETCH_MONITOR_SCRN_WIDTH, POKETCH_MONITOR_SCRN_HEIGHT, EFFECT_PALNO );

		GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME1_S );

		PoketchViewTool_FwdSeq( wk_adrs );
	}
	else
	{
		DeleteCommand( wk_adrs );
	}
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdEffClose2(TCB_PTR tcb, void *wk_adrs)
{
	CMDWORK_EFFECT *wk;
	POKETCH_VIEW_WORK* vwk;
	u32 seq;

	wk = PoketchViewTool_GetCmdWork(wk_adrs);
	vwk =  PoketchViewTool_GetViewWork(wk_adrs);
	seq = PoketchViewTool_GetSeq(wk_adrs);

	if(seq < 4)
	{
		GF_BGL_ScrFill(
			vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS + CHARNO_EFF_OPEN3 - seq,
			POKETCH_MONITOR_SCRN_XORG, POKETCH_MONITOR_SCRN_YORG,
			POKETCH_MONITOR_SCRN_WIDTH, POKETCH_MONITOR_SCRN_HEIGHT, EFFECT_PALNO );

		GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME1_S );

		PoketchViewTool_FwdSeq( wk_adrs );
	}
	else
	{
		DeleteCommand( wk_adrs );
	}
}

//------------------------------------------------------------------
/**
 * コマンド：ボタンロック状態へ変更
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdButtonLock(TCB_PTR tcb, void *wk_adrs)
{
	POKETCH_VIEW_WORK* vwk = PoketchViewTool_GetViewWork(wk_adrs);

	GF_BGL_ScrWrite( vwk->bgl, GF_BGL_FRAME0_S, vwk->scrn_button_press, 
			SCRN_BUTTON_XPOS, SCRN_BUTTON_YPOS, SCRN_BUTTON_WIDTH, SCRN_BUTTON_HEIGHT );
	GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME0_S );

	Snd_SePlay( POKETCH_SE_BUTTON_ROCK );

	DeleteCommand( wk_adrs );
}
//------------------------------------------------------------------
/**
 * コマンド：ボタン離し状態へ変更
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdButtonFree(TCB_PTR tcb, void *wk_adrs)
{
	POKETCH_VIEW_WORK* vwk = PoketchViewTool_GetViewWork(wk_adrs);

	GF_BGL_ScrWrite( vwk->bgl, GF_BGL_FRAME0_S, vwk->scrn_button_free, 
			SCRN_BUTTON_XPOS, SCRN_BUTTON_YPOS, SCRN_BUTTON_WIDTH, SCRN_BUTTON_HEIGHT );
	GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME0_S );

	DeleteCommand( wk_adrs );
}
//------------------------------------------------------------------
/**
 * コマンド：ボタン押し込み状態へ変更
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdButtonPush(TCB_PTR tcb, void *wk_adrs)
{
	POKETCH_VIEW_WORK* vwk = PoketchViewTool_GetViewWork(wk_adrs);

	GF_BGL_ScrWrite( vwk->bgl, GF_BGL_FRAME0_S, vwk->scrn_button_hold, 
			SCRN_BUTTON_XPOS, SCRN_BUTTON_YPOS, SCRN_BUTTON_WIDTH, SCRN_BUTTON_HEIGHT );
	GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME0_S );

	Snd_SePlay( POKETCH_SE_BUTTON_PUSH );

	DeleteCommand( wk_adrs );
}
//------------------------------------------------------------------
/**
 * コマンド：アプリ連打切り替え時のアプリナンバー表示開始
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdSkipNumDisp(TCB_PTR tcb, void* wk_adrs )
{
	POKETCH_VIEW_WORK* vwk = PoketchViewTool_GetViewWork(wk_adrs);

	SkipNumActor_Setup(vwk, &vwk->skip_num);
	SkipNumActor_Update(&vwk->skip_num, vwk->vpara);
	DeleteCommand( wk_adrs );
}
//------------------------------------------------------------------
/**
 * コマンド：アプリ連打切り替え時のアプリナンバー表示更新
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdSkipNumUpdate(TCB_PTR tcb, void* wk_adrs )
{
	POKETCH_VIEW_WORK* vwk = PoketchViewTool_GetViewWork(wk_adrs);

	SkipNumActor_Update(&vwk->skip_num, vwk->vpara);
	DeleteCommand( wk_adrs );
}

//------------------------------------------------------------------
/**
 * コマンド：アプリ連打切り替え時のアプリナンバー表示終了
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdSkipNumEnd(TCB_PTR tcb, void* wk_adrs )
{
	POKETCH_VIEW_WORK* vwk = PoketchViewTool_GetViewWork(wk_adrs);

	SkipNumActor_Delete(&vwk->skip_num);
	DeleteCommand( wk_adrs );
}



static void SkipNumActor_InitWork( SKIPNUM_WORK* skipNumWork, PACTSYS* actsys )
{
	skipNumWork->enable = FALSE;
	skipNumWork->actsys = actsys;
}

static void SkipNumActor_Setup( POKETCH_VIEW_WORK* vwk, SKIPNUM_WORK* skipNumWork )
{
	enum {
		SKIPNUMACTOR_PALNO = 15,
	};

	if( PACT_TOOL_LoadCellDatas(&skipNumWork->clpack, ARC_POKETCH_IMG,
				NARC_poketch_numobj_ncer, NARC_poketch_numobj_nanr, POKETCH_MAIN_VIEW_HEAPID ) )
	{
		static const PACT_ADD_PARAM param = {
			{  FX32INT(176), FX32INT(40) },
//			{  FX32INT(120), FX32INT(60) },
			0, 0, BGPRI0, 0, FALSE,
		};

		ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_numobj_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_MAIN_VIEW_HEAPID);
		ArcUtil_PalSet(ARC_POKETCH_IMG, NARC_poketch_app_nclr, PALTYPE_SUB_OBJ, 0, 0x60, POKETCH_MAIN_VIEW_HEAPID);
		SkipNumActor_LoadPalette( vwk, SKIPNUMACTOR_PALNO );

		skipNumWork->act[0] = PACT_Add(skipNumWork->actsys, &param, &skipNumWork->clpack);
		if( skipNumWork->act[0] == NULL ){
			return;
		}
		skipNumWork->act[1] = PACT_Add(skipNumWork->actsys, &param, &skipNumWork->clpack);
		if( skipNumWork->act[1] == NULL )
		{
			PACT_Del(skipNumWork->actsys, skipNumWork->act[0]);
			return;
		}
		PACT_MovePos(skipNumWork->act[1], 16*FX32_ONE, 0 );
		PACT_SetPalOffset(skipNumWork->act[0], SKIPNUMACTOR_PALNO);
		PACT_SetPalOffset(skipNumWork->act[1], SKIPNUMACTOR_PALNO);
		skipNumWork->enable = TRUE;
	}
}

static void SkipNumActor_LoadPalette( POKETCH_VIEW_WORK* vwk, u32 palno )
{
	#define swap(a,b)	{ u16 tmp=(a); (a)=(b); (b)=tmp; }

	POKETCH_DATA*  savedata = PoketchGetSaveData(vwk->cwk);
	u32 color_type = PoketchData_GetColorType(savedata);

	GXS_LoadBGPltt( &vwk->app_palette[ color_type*32 + POKETCH_DEFAULTCOLOR_L4_POS], 
						BOARD_PALNO*0x20 + POKETCH_DEFAULTCOLOR_L4_POS*sizeof(u16), sizeof(u16) );

	PoketchView_GetColorPalette( vwk->work_palette );

	swap(vwk->work_palette[POKETCH_DEFAULTCOLOR_L4_POS], vwk->work_palette[POKETCH_DEFAULTCOLOR_L1_POS]);
	swap(vwk->work_palette[POKETCH_DEFAULTCOLOR_L3_POS], vwk->work_palette[POKETCH_DEFAULTCOLOR_L2_POS]);

	DC_FlushRange( vwk->work_palette, sizeof(vwk->work_palette) );
	GXS_LoadOBJPltt( vwk->work_palette, palno*0x20, sizeof(vwk->work_palette) );

}

static void SkipNumActor_Update( SKIPNUM_WORK* skipNumWork, const POKETCH_MAIN_VPARAM* vpara )
{
	if( skipNumWork->enable )
	{
		u32 u, l;

		CP_SetDiv32_32( (vpara->app_pos+1), 10 );
		u = CP_GetDivResult32();
		l = CP_GetDivRemainder32();
		PACT_ChangeAnmSeq( skipNumWork->act[0], u );
		PACT_ChangeAnmSeq( skipNumWork->act[1], l );
	}
}

static void SkipNumActor_Delete( SKIPNUM_WORK* skipNumWork )
{
	if( skipNumWork->enable )
	{
		PACT_Del( skipNumWork->actsys, skipNumWork->act[0] );
		PACT_Del( skipNumWork->actsys, skipNumWork->act[1] );
		PACT_TOOL_UnloadCellDatas(&skipNumWork->clpack);
		skipNumWork->enable = FALSE;
	}
}



//------------------------------------------------------------------
/**
 * コマンド：スリープモードへ
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdSleep( TCB_PTR tcb, void* wk_adrs )
{
	u32 seq;
	CMDWORK_EFFECT *wk;
	POKETCH_VIEW_WORK* vwk = PoketchViewTool_GetViewWork(wk_adrs);

	wk = PoketchViewTool_GetCmdWork(wk_adrs);
	seq = PoketchViewTool_GetSeq(wk_adrs);

	switch( seq ){
	case 0:
		G2S_SetBlendAlpha(
			GX_BLEND_PLANEMASK_BG1,
			GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ,
			0x1a, 0x06
		);

		GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME0_S );

		/* fallthru */
	case 1:
	case 2:
	case 3:
		GF_BGL_ScrFill( vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS + CHARNO_EFF_OPEN3 - seq,
							POKETCH_MONITOR_SCRN_XORG, POKETCH_MONITOR_SCRN_YORG,
							POKETCH_MONITOR_SCRN_WIDTH, POKETCH_MONITOR_SCRN_HEIGHT, EFFECT_PALNO );

		GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME1_S );

		if( seq == 3 ){
			DeleteCommand( wk_adrs );
		}else{
			PoketchViewTool_FwdSeq( wk_adrs );
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * コマンド：スリープモード解除
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdWake( TCB_PTR tcb, void* wk_adrs )
{
	POKETCH_VIEW_WORK* vwk = PoketchViewTool_GetViewWork(wk_adrs);

	GF_BGL_ScrFill( vwk->bgl, GF_BGL_FRAME1_S, EFFECT_CHAROFS,
						POKETCH_MONITOR_SCRN_XORG, POKETCH_MONITOR_SCRN_YORG,
						POKETCH_MONITOR_SCRN_WIDTH, POKETCH_MONITOR_SCRN_HEIGHT, EFFECT_PALNO );


	GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME0_S );
	GF_BGL_LoadScreenReq( vwk->bgl, GF_BGL_FRAME1_S );

	G2S_SetBlendAlpha(
		0, 0, 0x1f, 0x00
	);

	DeleteCommand( wk_adrs );
}


//------------------------------------------------------------------
/**
 * コマンド：画面構築に使ったリソースの全解放
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdQuit( TCB_PTR tcb, void *wk_adrs )
{
	POKETCH_VIEW_WORK* vwk = PoketchViewTool_GetViewWork(wk_adrs);

	GF_BGL_BGControlExit( vwk->bgl, GF_BGL_FRAME0_S );
	GF_BGL_BGControlExit( vwk->bgl, GF_BGL_FRAME1_S );
	DeleteCommand( wk_adrs );
}
