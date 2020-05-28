//============================================================================================
/**
 * @file	poketch_a04v.c
 * @bfief	�|�P�b�`�i�A�v��No04�F�A�i���O���v�j�@�`��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a04.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(8)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

//==============================================================
// actor
//==============================================================
enum {
	ACT_HOUR_HAND,
	ACT_MINUTE_HAND,
	ACT_MAX,
};

enum {
	ACTANM_MINUTE_HAND_START = 0,
	ACTANM_HOUR_HAND_START = 60,
};

enum {
	ACT_HOUR_HAND_X = 116,
	ACT_HOUR_HAND_Y = 100,
	ACT_MINUTE_HAND_X = 116,
	ACT_MINUTE_HAND_Y = 100,
};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A04_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	TCB_PTR            maintask;
	PACT_CLANM_PACK    clpack;
	PACTSYS*           actsys;
	PACT*              act[ ACT_MAX ];
};



//====================================================
// bg map
//====================================================
#define USE_PALNO	(0)

//==============================================================
// Prototype
//==============================================================
static void PoketchA04ViewMain(TCB_PTR tcb, void *wk_adrs );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdTimeUpdate( TCB_PTR tcb, void* wk_adrs );
static void CmdBackLightUpdate(TCB_PTR tcb, void* wk_adrs );
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void UpdateWatchHandObj( VIEWWORK* vwk );
static BOOL SetupObj( VIEWWORK* vwk );
static void DeleteObj( VIEWWORK* vwk );




//------------------------------------------------------------------
/**
 * ���[�N�m��
 *
 * @param   wk_ptr		�m�ۂ������[�N�A�h���X��ۑ�����|�C���^�̃A�h���X
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A04_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		NNSG2dScreenData* scrnDat;
		void* buf;

		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();

		if( SetupObj( wk ) == FALSE )
		{
			sys_FreeMemoryEz( wk );
			return FALSE;
		}


		wk->maintask = TCB_Add( PoketchA04ViewMain, wk, POKETCH_APP_GRAPHIC_TASKPRI );

		*wk_ptr = wk;
		return TRUE;
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * ���[�N�폜
 *
 * @param   wk		�m�ۂ������[�N�A�h���X
 *
 */
//------------------------------------------------------------------
void Poketch_A04_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		DeleteObj( wk );

		if( wk->maintask )
		{
			TCB_Delete( wk->maintask );
		}

		sys_FreeMemoryEz( wk );
	}
}

//------------------------------------------------------------------
/**
 * ���C���^�X�N
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void PoketchA04ViewMain(TCB_PTR tcb, void *wk_adrs )
{
//	VIEWWORK *vwk = (VIEWWORK*)wk_adrs;
//	PACT_SysMain( vwk->actsys );
}

//------------------------------------------------------------------
/**
 * @brief	�R�}���h�e�[�u��
 */
//------------------------------------------------------------------
static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT,   CmdInit,   0 },
	{ CMD_TIME_UPDATE, CmdTimeUpdate, 0 },
	{ CMD_BACKLIGHT_UPDATE, CmdBackLightUpdate, 0 },
	{ CMD_QUIT,   CmdQuit,   0 },
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
void Poketch_A04_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A04_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A04_WaitViewCommandAll(VIEWWORK* wk)
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

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	// �L�����̓f�W�^�����v�Ƌ��L
	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_dwatch_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
//	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, 0, 0, 0, 32, 24, USE_PALNO );
//void ArcUtil_ScrnSet(u32 fileIdx, u32 dataIdx, GF_BGL_INI* bgl, u32 frm, u32 offs, u32 transSize, BOOL compressedFlag, u32 heapID)
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_awatch_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	PoketchView_SetBaseColorPalette(0,0);

	UpdateWatchHandObj( vwk );

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2| GX_PLANEMASK_OBJ);

	DeleteCommand( wk_ptr );

}
//------------------------------------------------------------------
/**
 * �R�}���h�F���ԍX�V
 *
 * @param   tcb			TCB�|�C���^
 * @param   wk_ptr		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void CmdTimeUpdate( TCB_PTR tcb, void* wk_adrs )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	UpdateWatchHandObj( vwk );
	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );
}
//------------------------------------------------------------------
/**
 * �R�}���h�F�o�b�N���C�g�X�V
 *
 * @param   tcb			TCB�|�C���^
 * @param   wk_ptr		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void CmdBackLightUpdate(TCB_PTR tcb, void* wk_adrs )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_adrs );
	if( vwk->vpara->backlight )
	{
		PoketchView_SetHighColorPalette(0,0);
	}
	else
	{
		PoketchView_SetBaseColorPalette(0,0);
	}
	DeleteCommand( wk_adrs );
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
 * �����X�N���[�����X�V
 *
 * @param   vwk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void UpdateWatchHandObj( VIEWWORK* vwk )
{
	u32 anmseq;

	CP_SetDiv32_32( vwk->vpara->time.hour, 10 );

	// �Z�j�͂P���Ԃ��Ƃ�30�x�{�Q�����ƂɂP�x�i��
	anmseq = ACTANM_HOUR_HAND_START +
			((vwk->vpara->time.hour % 12) * 30) + 
			(vwk->vpara->time.minute / 2);

	PACT_ChangeAnmSeq( vwk->act[ACT_HOUR_HAND], anmseq );

	// ���j�͂P�����ƂɂU�x�i��
	anmseq = ACTANM_MINUTE_HAND_START + vwk->vpara->time.minute;
	PACT_ChangeAnmSeq( vwk->act[ACT_MINUTE_HAND], anmseq );
}


//------------------------------------------------------------------
/**
 * �A�N�^�[�Z�b�g�A�b�v
 *
 * @param   vwk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static BOOL SetupObj( VIEWWORK* vwk )
{
	static const PACT_ADD_PARAM param[] = {
{		{  FX32INT(ACT_HOUR_HAND_X), FX32INT(ACT_HOUR_HAND_Y) },
			ACTANM_HOUR_HAND_START, 0, BGPRI2, 0, TRUE,
		},{
			{  FX32INT(ACT_MINUTE_HAND_X), FX32INT(ACT_MINUTE_HAND_Y) },
			ACTANM_MINUTE_HAND_START, 0, BGPRI2, 0, TRUE,
		},
	};

	ArcUtil_ObjCharSet( ARC_POKETCH_IMG, NARC_poketch_awatch_obj_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID );

	if( PACT_TOOL_LoadCellDatas( &vwk->clpack, ARC_POKETCH_IMG,
			NARC_poketch_awatch_ncer, NARC_poketch_awatch_nanr, POKETCH_APP_VIEW_HEAPID )
	)
	{
		int i;
		for(i = 0; i < ACT_MAX; i++)
		{
			vwk->act[i] = PACT_Add( vwk->actsys, &param[i], &vwk->clpack );
		}
		return TRUE;
	}
	return FALSE;

}
//------------------------------------------------------------------
/**
 * �A�N�^�[�S�폜
 *
 * @param   vwk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
static void DeleteObj( VIEWWORK* vwk )
{
	int i;

	PACT_TOOL_UnloadCellDatas( &(vwk->clpack) );
	for( i = 0; i < ACT_MAX; i++ )
	{
		PACT_Del( vwk->actsys, vwk->act[i] );
	}
}

