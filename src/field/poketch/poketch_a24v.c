//============================================================================================
/**
 * @file	poketch_a24v.c
 * @bfief	�|�P�b�`�i�A�v��No24:�J���[�`�F���W���[�j�@�`��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a24.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

//==============================================================
// Work
//==============================================================
struct _POKETCH_A24_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              act_bar;
	PACT_CLANM_PACK    clpack;

};



//====================================================
// bg map
//====================================================
#define TEST_PALNO	(0)

//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara );
static void cleanup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdUpdateBarPos(TCB_PTR tcb, void *wk_ptr);




//------------------------------------------------------------------
/**
 * ���[�N�m��
 *
 * @param   wk_ptr		�m�ۂ������[�N�A�h���X��ۑ�����|�C���^�̃A�h���X
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A24_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();

		wk->actsys = PoketchGetActSys();

		setup_actors( wk, vpara );

		*wk_ptr = wk;
		return TRUE;
	}

	return FALSE;
}
static void setup_actors( VIEWWORK* wk, const VIEWPARAM* vpara )
{
	static const PACT_ADD_PARAM actparam = {
		{  FX32INT(BAR_XORG), FX32INT(BAR_YPOS) },
		0, 0, BGPRI2, 0, FALSE,
	};

	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_changer_obj_lz_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

	PACT_TOOL_LoadCellDatas(&wk->clpack, ARC_POKETCH_IMG,
				NARC_poketch_changer_lz_ncer, NARC_poketch_changer_lz_nanr, POKETCH_APP_VIEW_HEAPID );

	wk->act_bar = PACT_Add( wk->actsys, &actparam, &wk->clpack );
	PACT_SetPos(wk->act_bar, (BAR_XORG+(BAR_MOVE_DIFF*vpara->bar_pos))<<FX32_SHIFT, (BAR_YPOS<<FX32_SHIFT));
}

static void cleanup_actors( VIEWWORK* wk )
{
	int i;

	if( wk->act_bar )
	{
		PACT_Del( wk->actsys, wk->act_bar );
	}

	PACT_TOOL_UnloadCellDatas(&wk->clpack);
}



//------------------------------------------------------------------
/**
 * ���[�N�폜
 *
 * @param   wk		�m�ۂ������[�N�A�h���X
 *
 */
//------------------------------------------------------------------
void Poketch_A24_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		cleanup_actors(wk);
		sys_FreeMemoryEz( wk );
	}
}

//------------------------------------------------------------------
/**
 * @brief	�R�}���h�e�[�u��
 */
//------------------------------------------------------------------
static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT, CmdInit, 0 },
	{ CMD_QUIT, CmdQuit, 0 },
	{ CMD_UPDATE_BARPOS, CmdUpdateBarPos },
	{ 0, NULL, 0 },
};


//------------------------------------------------------------------
/**
 * �`��R�}���h�̃Z�b�g
 *
 * @param   cmd		�R�}���h
 * @param   view_wk_adrs	���[�N�̈�A�h���X
 *
 */
//------------------------------------------------------------------
void Poketch_A24_SetViewCommand(VIEWWORK* wk, u32 cmd)
{
	PoketchViewTool_SetCommand(CmdTbl, cmd, wk, wk->vpara, wk->cmd_store, POKETCH_GRAPHIC_TASKPRI, POKETCH_APP_VIEW_HEAPID);
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�̏I���҂��i�P���j
 *
 * @param   cmd			�R�}���h
 *
 * @retval  BOOL		TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL Poketch_A24_WaitViewCommand(VIEWWORK* wk, u32 cmd)
{
	return PoketchViewTool_WaitCommand(wk->cmd_store, cmd);
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�̏I���҂��i�S���j
 *
 * @retval  BOOL		TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL Poketch_A24_WaitViewCommandAll(VIEWWORK* wk)
{
	return PoketchViewTool_WaitCommandAll(wk->cmd_store);
}



//------------------------------------------------------------------
/**
 * �R�}���h�폜
 *
 * @param   cwk		�R�}���h���[�N
 *
 */
//------------------------------------------------------------------
static void DeleteCommand(POKETCH_CMD_WORK* cwk)
{
	VIEWWORK *wk = PoketchViewTool_GetViewWork(cwk);
	PoketchViewTool_DelCommand( wk->cmd_store, cwk );
}

//------------------------------------------------------------------
/**
 * �R�}���h�F��ʍ\�z
 *
 * @param   tcb			TCB�|�C���^
 * @param   wk_ptr		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void CmdInit(TCB_PTR tcb, void *wk_ptr)
{
	static const GF_BGL_BGCNT_HEADER header = {
		0, 0, 0x800, 0,		// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	GXSDispCnt dispcnt;
	VIEWWORK* vwk;
	const VIEWPARAM* vpara;
	void* load_p;
	NNSG2dPaletteData* pal;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	vpara = PoketchViewTool_GetViewParam( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_changer_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_changer_lz_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette(0,0);

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2);

	DeleteCommand( wk_ptr );

}

//------------------------------------------------------------------
/**
 * �R�}���h�F�I������
 *
 * @param   tcb			TCB�|�C���^
 * @param   wk_ptr		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void CmdQuit(TCB_PTR tcb, void *wk_ptr)
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_ptr );
}

//------------------------------------------------------------------
/**
 * �R�}���h�F�o�[�ʒu�X�V
 *
 * @param   tcb			TCB�|�C���^
 * @param   wk_ptr		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void CmdUpdateBarPos(TCB_PTR tcb, void *wk_ptr)
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	PoketchSePlay(POKETCH_SE_CHANGER_CHANGE);

	PoketchView_SetBaseColorPalette(0,0);
	PACT_SetPos(vwk->act_bar, (BAR_XORG+(BAR_MOVE_DIFF*vpara->bar_pos))<<FX32_SHIFT, (BAR_YPOS<<FX32_SHIFT));
	DeleteCommand( wk_ptr );
}





