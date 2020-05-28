//============================================================================================
/**
 * @file	pmsiv_sub.c
 * @bfief	簡易会話入力画面（描画下請け：サブ画面）
 * @author	taya
 * @date	06.02.10
 */
//============================================================================================
#include "common.h"
#include "gflib\heapsys.h"
#include "gflib\strbuf.h"
#include "system\arc_util.h"
#include "system\window.h"
#include "system\pms_word.h"
#include "system\winframe.naix"
#include "system\msgdata.h"
#include "msgdata\msg_pms_input.h"
#include "msgdata\msg.naix"


#include "pms_input_prv.h"
#include "pms_input_view.h"


//======================================================================

enum {


	GROUP_WIN_XPOS = 4,
	GROUP_WIN_YPOS = 5,
	GROUP_WIN_PALNO = 0,

	INITIAL_WIN_XPOS = 19,
	INITIAL_WIN_YPOS = 5,
	INITIAL_WIN_PALNO = 1,

	BUTTON_WIN_WIDTH = 9,
	BUTTON_WIN_HEIGHT = 5,
	BUTTON_WIN_CHARSIZE = BUTTON_WIN_WIDTH*BUTTON_WIN_HEIGHT,

	PUSH_BUTTON_WRITE_OX = 5,
	PUSH_BUTTON_WRITE_OY = 5,
	RELEASE_BUTTON_WRITE_OX = 4,
	RELEASE_BUTTON_WRITE_OY = 4,

	WIN_COL_PUSH_GROUND = 0x0a,
	WIN_COL_RELEASE_GROUND = 0x09,
	WIN_COL1 = 0x01,
	WIN_COL2 = 0x02,
	WIN_COL3 = 0x03,

};

enum {
	SCREEN_PATTERN_PUSH_GROUP,
	SCREEN_PATTERN_PUSH_INITIAL,
};

enum {
	ANM_MODEBUTTON_OFF,
	ANM_MODEBUTTON_ON,
	ANM_MODEBUTTON_PUSH,
};


enum {
	MODEBUTTON_SCRN_SIZE = MODEBUTTON_SCRN_WIDTH * MODEBUTTON_SCRN_HEIGHT,

	SCRN_ID_GROUP_OFF = 0,
	SCRN_ID_GROUP_PUSH1,
	SCRN_ID_GROUP_PUSH2,
	SCRN_ID_GROUP_ON,
	SCRN_ID_INITIAL_OFF,
	SCRN_ID_INITIAL_PUSH1,
	SCRN_ID_INITIAL_PUSH2,
	SCRN_ID_INITIAL_ON,
	SCRN_ID_MAX,

};


enum {
	ACTANM_ARROW_UP_STOP,
	ACTANM_ARROW_UP_HOLD,
	ACTANM_ARROW_DOWN_STOP,
	ACTANM_ARROW_DOWN_HOLD,
};


//======================================================================


//======================================================================
typedef struct {
	void*					cellLoadPtr;
	NNSG2dCellDataBank*		cellData;
	void*					animLoadPtr;
	NNSG2dAnimBankData*		animData;
}CELL_ANIM_PACK;


//--------------------------------------------------------------
/**
 *	
 */
//--------------------------------------------------------------
struct _PMSIV_SUB {
	PMS_INPUT_VIEW*        vwk;
	const PMS_INPUT_WORK*  mwk;
	const PMS_INPUT_DATA*  dwk;

	GF_BGL_INI*        bgl;

	CLACT_SET_PTR      actsys;
	CLACT_WORK_PTR     up_button;
	CLACT_WORK_PTR     down_button;
	CELL_ANIM_PACK     clpack;

	u16   button_scrn[SCRN_ID_MAX][MODEBUTTON_SCRN_SIZE];

	TCB_PTR       changeButtonTask;

};


//==============================================================
// Prototype
//==============================================================
static void load_scrn_datas( PMSIV_SUB* wk );
static void setup_cgx_datas( PMSIV_SUB* wk );
static void print_mode_name( GF_BGL_BMPWIN* win, GF_BGL_INI* bgl, const STRBUF* str, int yofs );
static void setup_actors( PMSIV_SUB* wk );
static void cleanup_actors( PMSIV_SUB* wk );
static void load_clpack( CELL_ANIM_PACK* clpack, u32 arcID, u32 cellDatID, u32 animDatID );
static void unload_clpack( CELL_ANIM_PACK* clpack );
static void ChangeButtonTask( TCB_PTR tcb, void* wk_adrs );


 static CLACT_WORK_PTR add_actor(
	PMSIV_SUB* wk, NNSG2dImageProxy* imgProxy, NNSG2dImagePaletteProxy* palProxy,
	CELL_ANIM_PACK* clpack, int xpos, int ypos, int bgpri, int actpri );



//------------------------------------------------------------------
/**
 * 
 *
 * @param   vwk		
 * @param   mwk		
 * @param   dwk		
 *
 * @retval  PMSIV_SUB*		
 */
//------------------------------------------------------------------
PMSIV_SUB*  PMSIV_SUB_Create( PMS_INPUT_VIEW* vwk, const PMS_INPUT_WORK* mwk, const PMS_INPUT_DATA* dwk )
{
	PMSIV_SUB*  wk = sys_AllocMemory( HEAPID_PMS_INPUT_VIEW, sizeof(PMSIV_SUB) );

	wk->vwk = vwk;
	wk->mwk = mwk;
	wk->dwk = dwk;
	wk->bgl = PMSIView_GetBGL(vwk);
	wk->actsys = PMSIView_GetActSys(vwk);

	wk->up_button = NULL;
	wk->down_button = NULL;
	wk->changeButtonTask = NULL;

	return wk;
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_SUB_Delete( PMSIV_SUB* wk )
{
	cleanup_actors( wk );

	sys_FreeMemoryEz( wk );
}



//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_SUB_SetupGraphicDatas( PMSIV_SUB* wk )
{
	ArcUtil_PalSet( ARC_PMSI_GRAPHIC, NARC_pmsi_bg_sub_nclr, PALTYPE_SUB_BG, 0, 0x40, HEAPID_PMS_INPUT_VIEW );
	ArcUtil_ScrnSet( ARC_PMSI_GRAPHIC, NARC_pmsi_bg_sub_lz_nscr, wk->bgl, FRM_SUB_BG, 0, 0, TRUE, HEAPID_PMS_INPUT_VIEW );


	load_scrn_datas( wk );
	setup_cgx_datas( wk );

	if( PMSI_GetCategoryMode( wk->mwk ) == CATEGORY_MODE_GROUP )
	{
		GF_BGL_ScrWriteExpand( wk->bgl, FRM_SUB_BG, BUTTON_GROUP_SCRN_XPOS, BUTTON_GROUP_SCRN_YPOS,
					MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT, wk->button_scrn[SCRN_ID_GROUP_ON],
					0, 0, MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT );

		GF_BGL_ScrWriteExpand( wk->bgl, FRM_SUB_BG, BUTTON_INITIAL_SCRN_XPOS, BUTTON_INITIAL_SCRN_YPOS,
					MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT, wk->button_scrn[SCRN_ID_INITIAL_OFF],
					0, 0, MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT );
	}
	else
	{
		GF_BGL_ScrWriteExpand( wk->bgl, FRM_SUB_BG, BUTTON_GROUP_SCRN_XPOS, BUTTON_GROUP_SCRN_YPOS,
					MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT, wk->button_scrn[SCRN_ID_GROUP_OFF],
					0, 0, MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT );

		GF_BGL_ScrWriteExpand( wk->bgl, FRM_SUB_BG, BUTTON_INITIAL_SCRN_XPOS, BUTTON_INITIAL_SCRN_YPOS,
					MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT, wk->button_scrn[SCRN_ID_INITIAL_ON],
					0, 0, MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT );

	}

	setup_actors( wk );

	GF_BGL_LoadScreenReq( wk->bgl, FRM_SUB_BG );

}
static void load_scrn_datas( PMSIV_SUB* wk )
{
	static const u16 dat_id[] = {
		NARC_pmsi_bg_sub_a1_lz_nscr,
		NARC_pmsi_bg_sub_a2_lz_nscr,
		NARC_pmsi_bg_sub_a3_lz_nscr,
		NARC_pmsi_bg_sub_a4_lz_nscr,
		NARC_pmsi_bg_sub_b1_lz_nscr,
		NARC_pmsi_bg_sub_b2_lz_nscr,
		NARC_pmsi_bg_sub_b3_lz_nscr,
		NARC_pmsi_bg_sub_b4_lz_nscr,
	};
	int i;
	void* loadPtr;
	NNSG2dScreenData* scrnData;

	for(i=0; i<NELEMS(dat_id); i++)
	{
		loadPtr = ArcUtil_ScrnDataGet(ARC_PMSI_GRAPHIC, dat_id[i], TRUE, &scrnData, HEAPID_PMS_INPUT_VIEW);
		if( loadPtr )
		{
			MI_CpuCopy16( scrnData->rawData, wk->button_scrn[i], MODEBUTTON_SCRN_SIZE*2 );
			DC_FlushRange( wk->button_scrn[i], MODEBUTTON_SCRN_SIZE*2 );
			sys_FreeMemoryEz( loadPtr );
		}
	}
}

static void setup_cgx_datas( PMSIV_SUB* wk )
{
	enum {
		CGX_WIDTH  = 11,
		CGX_HEIGHT = 57,
	};

	STRBUF* str_group;
	STRBUF* str_initial;
	void* loadPtr;
	NNSG2dCharacterData* charData;

	FontProc_LoadFont( FONT_BUTTON, HEAPID_BASE_SYSTEM );
	str_group = MSGDAT_GetStrDirectAlloc(ARC_MSG, NARC_msg_pms_input_dat, str_group_mode, HEAPID_PMS_INPUT_VIEW );
	str_initial = MSGDAT_GetStrDirectAlloc(ARC_MSG, NARC_msg_pms_input_dat, str_initial_mode, HEAPID_PMS_INPUT_VIEW );


	loadPtr = ArcUtil_CharDataGet(ARC_PMSI_GRAPHIC, NARC_pmsi_bg_sub_lz_ncgr, TRUE, &charData, HEAPID_PMS_INPUT_VIEW);
	if(loadPtr)
	{
		GF_BGL_BMPWIN   win;
		int i;

		GF_BGL_BmpWinInit(&win);
		win.ini = wk->bgl;
		win.sizx = CGX_WIDTH;
		win.sizy = CGX_HEIGHT;
		win.bitmode = GF_BGL_BMPWIN_BITMODE_4;
		win.chrbuf = charData->pRawData;
		print_mode_name( &win, wk->bgl, str_group,   0 );

		win.chrbuf = (u8*)(charData->pRawData) + ((CGX_WIDTH * (MODEBUTTON_SCRN_HEIGHT*4))*0x20);
		print_mode_name( &win, wk->bgl, str_initial, 0 );

		DC_FlushRange( charData->pRawData, charData->szByte );
		GF_BGL_LoadCharacter(wk->bgl, FRM_SUB_BG, charData->pRawData, charData->szByte, 0);

		sys_FreeMemoryEz(loadPtr);
	}

	STRBUF_Delete(str_initial);
	STRBUF_Delete(str_group);
	FontProc_UnloadFont( FONT_BUTTON );
}

static void print_mode_name( GF_BGL_BMPWIN* win, GF_BGL_INI* bgl, const STRBUF* str, int yofs )
{
	enum {
		COL_1 = 0x01,
		COL_2 = 0x02,
		COL_3 = 0x03,

		WRITE_X_ORG = 10,
		WRITE_Y_ORG = 22,
		WRITE_Y_DIFF = 56,
	};

	static const struct {
		s16				xofs;
		s16				yofs;
	}writeParam[] = {
		{ WRITE_X_ORG,  WRITE_Y_ORG },
		{ WRITE_X_ORG, (WRITE_Y_ORG + WRITE_Y_DIFF*1)-1 },
		{ WRITE_X_ORG, (WRITE_Y_ORG + WRITE_Y_DIFF*2)-2 },
		{ WRITE_X_ORG, (WRITE_Y_ORG + WRITE_Y_DIFF*3)-1 },
	};
	int i, y;

	for(i=0; i<NELEMS(writeParam); i++)
	{
		y = writeParam[i].yofs + yofs;
		GF_STR_PrintColor( win, FONT_BUTTON, str, writeParam[i].xofs, y,
							MSG_NO_PUT, GF_PRINTCOLOR_MAKE(COL_1,COL_2,COL_3), NULL );
	}
}


//==============================================================================================
//==============================================================================================

static void setup_actors( PMSIV_SUB* wk )
{
	NNSG2dImagePaletteProxy	palProxy;
	NNSG2dImageProxy		imgProxy;

	NNS_G2dInitImagePaletteProxy( &palProxy );
	NNS_G2dInitImageProxy( &imgProxy );
	ArcUtil_PalSysLoad( ARC_PMSI_GRAPHIC, NARC_pmsi_obj_sub_nclr, NNS_G2D_VRAM_TYPE_2DSUB, 0, HEAPID_PMS_INPUT_VIEW, &palProxy );
	ArcUtil_CharSysLoad( ARC_PMSI_GRAPHIC, NARC_pmsi_obj_sub_lz_ncgr, TRUE, CHAR_MAP_1D, 0, NNS_G2D_VRAM_TYPE_2DSUB, 0, 
							HEAPID_PMS_INPUT_VIEW, &imgProxy );

	load_clpack( &(wk->clpack), ARC_PMSI_GRAPHIC, NARC_pmsi_obj_sub_lz_ncer, NARC_pmsi_obj_sub_lz_nanr );

	wk->up_button = add_actor(wk, &imgProxy, &palProxy, &wk->clpack, BUTTON_UP_XPOS, BUTTON_UP_YPOS, 0, 0);
	CLACT_AnmChg( wk->up_button, ACTANM_ARROW_UP_STOP );
	CLACT_SetDrawFlag( wk->up_button, FALSE );

	wk->down_button = add_actor(wk, &imgProxy, &palProxy, &wk->clpack, BUTTON_DOWN_XPOS, BUTTON_DOWN_YPOS, 0, 0);
	CLACT_AnmChg( wk->down_button, ACTANM_ARROW_DOWN_STOP );
	CLACT_SetDrawFlag( wk->down_button, FALSE );

}

static void cleanup_actors( PMSIV_SUB* wk )
{
	if( wk->up_button )
	{
		CLACT_Delete( wk->up_button );
	}
	if( wk->down_button )
	{
		CLACT_Delete( wk->down_button );
	}

	unload_clpack(&wk->clpack);
}




static void load_clpack( CELL_ANIM_PACK* clpack, u32 arcID, u32 cellDatID, u32 animDatID )
{
	clpack->cellLoadPtr = ArcUtil_CellBankDataGet(arcID, cellDatID, TRUE, &(clpack->cellData), HEAPID_PMS_INPUT_VIEW);
	clpack->animLoadPtr = ArcUtil_AnimBankDataGet(arcID, animDatID, TRUE, &(clpack->animData), HEAPID_PMS_INPUT_VIEW);
}
static void unload_clpack( CELL_ANIM_PACK* clpack )
{
	sys_FreeMemoryEz( clpack->cellLoadPtr );
	sys_FreeMemoryEz( clpack->animLoadPtr );
}


 static CLACT_WORK_PTR add_actor(
	PMSIV_SUB* wk, NNSG2dImageProxy* imgProxy, NNSG2dImagePaletteProxy* palProxy,
	CELL_ANIM_PACK* clpack, int xpos, int ypos, int bgpri, int actpri )
{
	CLACT_HEADER  header;
	CLACT_ADD_SIMPLE  add;
	CLACT_WORK_PTR   act;

	header.pImageProxy = imgProxy;
	header.pPaletteProxy = palProxy;
	header.pCellBank     = clpack->cellData;
	header.pAnimBank     = clpack->animData;
	header.priority      = bgpri;
	header.pCharData = NULL;
	header.pMCBank = NULL;
	header.pMCABank = NULL;
	header.flag = FALSE;

	add.ClActSet = wk->actsys;
	add.ClActHeader = &header;
	add.mat.x = xpos * FX32_ONE;
	add.mat.y = (ypos+192) * FX32_ONE;
	add.mat.z = 0;
	add.pri = actpri;
	add.DrawArea = NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap = HEAPID_PMS_INPUT_VIEW;

	act = CLACT_AddSimple(&add);
	if( act )
	{
		CLACT_SetAnmFlag( act, TRUE );
		CLACT_SetAnmFrame( act, PMSI_ANM_SPEED );
	}
	return act;
}

//==============================================================================================
//==============================================================================================

typedef struct {
	PMSIV_SUB*  wk;
	int seq;
	u16 timer;

	u16 on_scrnID;
	u16 on_scrnID_end;
	u16 on_scrn_x;
	u16 on_scrn_y;

	u16 off_scrnID;
	u16 off_scrn_x;
	u16 off_scrn_y;

}CHANGE_BUTTON_WORK;

//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void PMSIV_SUB_ChangeCategoryButton( PMSIV_SUB* wk )
{
	CHANGE_BUTTON_WORK* twk = sys_AllocMemory(HEAPID_PMS_INPUT_VIEW, sizeof(CHANGE_BUTTON_WORK));

	if( twk )
	{
		static const struct {
			u16 on_id_start;
			u16 on_id_end;
			u16 on_x;
			u16 on_y;
			u16 off_id;
			u16 off_x;
			u16 off_y;
		}TaskParam[] = {
			{
				SCRN_ID_GROUP_PUSH1, SCRN_ID_GROUP_ON, BUTTON_GROUP_SCRN_XPOS, BUTTON_GROUP_SCRN_YPOS,
				SCRN_ID_INITIAL_OFF, BUTTON_INITIAL_SCRN_XPOS, BUTTON_INITIAL_SCRN_YPOS
			},{
				SCRN_ID_INITIAL_PUSH1, SCRN_ID_INITIAL_ON, BUTTON_INITIAL_SCRN_XPOS, BUTTON_INITIAL_SCRN_YPOS,
				SCRN_ID_GROUP_OFF, BUTTON_GROUP_SCRN_XPOS, BUTTON_GROUP_SCRN_YPOS
			}
		};

		int mode = PMSI_GetCategoryMode( wk->mwk );

		twk->wk = wk;
		twk->seq = 0;
		twk->timer = 0;

		twk->on_scrnID		= TaskParam[mode].on_id_start;
		twk->on_scrnID_end	= TaskParam[mode].on_id_end;
		twk->on_scrn_x		= TaskParam[mode].on_x;
		twk->on_scrn_y		= TaskParam[mode].on_y;
		twk->off_scrnID		= TaskParam[mode].off_id;
		twk->off_scrn_x		= TaskParam[mode].off_x;
		twk->off_scrn_y		= TaskParam[mode].off_y;

		wk->changeButtonTask = TCB_Add( ChangeButtonTask, twk, TASKPRI_VIEW_COMMAND );

	}
	else
	{
		wk->changeButtonTask = NULL;
	}
}

BOOL PMSIV_SUB_WaitChangeCategoryButton( PMSIV_SUB* wk )
{
	return (wk->changeButtonTask == NULL);
}


static void ChangeButtonTask( TCB_PTR tcb, void* wk_adrs )
{
	enum {
		ANM_WAIT1 = 2,
		ANM_WAIT2 = 4,
	};

	CHANGE_BUTTON_WORK* twk = wk_adrs;

	switch( twk->seq ){
	case 0:
		GF_BGL_ScrWriteExpand(twk->wk->bgl, FRM_SUB_BG, twk->on_scrn_x, twk->on_scrn_y,
						MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT, twk->wk->button_scrn[twk->on_scrnID],
						0, 0, MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT );

		GF_BGL_ScrWriteExpand(twk->wk->bgl, FRM_SUB_BG, twk->off_scrn_x, twk->off_scrn_y,
						MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT, twk->wk->button_scrn[twk->off_scrnID],
						0, 0, MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT );

		GF_BGL_LoadScreenReq( twk->wk->bgl, FRM_SUB_BG );
		twk->on_scrnID++;
		twk->seq++;
		break;

	case 1:
		if( ++(twk->timer) >= ANM_WAIT1 )
		{
			GF_BGL_ScrWriteExpand(twk->wk->bgl, FRM_SUB_BG, twk->on_scrn_x, twk->on_scrn_y,
						MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT, twk->wk->button_scrn[twk->on_scrnID],
						0, 0, MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT );

			GF_BGL_LoadScreenReq( twk->wk->bgl, FRM_SUB_BG );
			twk->timer = 0;
			twk->on_scrnID++;
			twk->seq++;
		}
		break;

	case 2:
		if( ++(twk->timer) >= ANM_WAIT2 )
		{
			GF_BGL_ScrWriteExpand(twk->wk->bgl, FRM_SUB_BG, twk->on_scrn_x, twk->on_scrn_y,
						MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT, twk->wk->button_scrn[twk->on_scrnID],
						0, 0, MODEBUTTON_SCRN_WIDTH, MODEBUTTON_SCRN_HEIGHT );

			GF_BGL_LoadScreenReq( twk->wk->bgl, FRM_SUB_BG );
			twk->seq++;
		}
		break;

	case 3:
		twk->wk->changeButtonTask = NULL;
		sys_FreeMemoryEz(wk_adrs);
		TCB_Delete(tcb);
	}
}




//------------------------------------------------------------------
/**
 * 矢印ボタン描画オン／オフ
 *
 * @param   wk		
 * @param   flag		
 *
 */
//------------------------------------------------------------------
void PMSIV_SUB_VisibleArrowButton( PMSIV_SUB* wk, BOOL flag )
{
	if( flag )
	{
		CLACT_SetDrawFlag( wk->up_button, PMSI_GetWordWinUpArrowVisibleFlag(wk->mwk) );
		CLACT_SetDrawFlag( wk->down_button, PMSI_GetWordWinDownArrowVisibleFlag(wk->mwk) );
	}
	else
	{
		CLACT_SetDrawFlag( wk->up_button, FALSE );
		CLACT_SetDrawFlag( wk->down_button, FALSE );
	}
}

//------------------------------------------------------------------
/**
 * 矢印ボタン状態切り替え
 *
 * @param   wk		
 * @param   pos		
 * @param   state		
 *
 */
//------------------------------------------------------------------
void PMSIV_SUB_ChangeArrowButton( PMSIV_SUB* wk, int pos, int state )
{
	switch(pos){
	case SUB_BUTTON_UP:
		switch( state ){
		case SUB_BUTTON_STATE_HOLD:
			CLACT_AnmChg( wk->up_button, ACTANM_ARROW_UP_HOLD );
			break;
		case SUB_BUTTON_STATE_RELEASE:
			CLACT_AnmChg( wk->up_button, ACTANM_ARROW_UP_STOP );
			break;
		}
		break;

	case SUB_BUTTON_DOWN:
		switch( state ){
		case SUB_BUTTON_STATE_HOLD:
			CLACT_AnmChg( wk->down_button, ACTANM_ARROW_DOWN_HOLD );
			break;
		case SUB_BUTTON_STATE_RELEASE:
			CLACT_AnmChg( wk->down_button, ACTANM_ARROW_DOWN_STOP );
			break;
		}
		break;
	}
}

