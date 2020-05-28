//============================================================================================
/**
 * @file	poketch_a17v.c
 * @bfief	�|�P�b�`�i�A�v��No17:�R�C���g�X�j�@�`��
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a17.h"


static fx32  CoinSpeed = 0;
static fx32  Gravity = 0;

#define DEFAULT_COIN_SPEED 	(-43008)
#define DEFAULT_GRAVITY		(2816)

#define COIN_REFRECT_SPEED_BORDER		(-2*FX32_ONE)

//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(4)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)


enum {
	ANMSEQ_ROLL,		///< ��]
	ANMSEQ_FACE,		///< �Î~�i�\�j
	ANMSEQ_BOTTOM,		///< �Î~�i���j
};

//==============================================================
// Work
//==============================================================
struct _POKETCH_A17_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	PACTSYS*           actsys;
	PACT*              act_coin;
	PACT_CLANM_PACK    clpack_coin;

	fx32    coin_ypos;
	fx32    coin_speed;

	BOOL    toss_stop_flag;
};



//====================================================
// bg map
//====================================================
#define TEST_PALNO	(0)

//==============================================================
// Prototype
//==============================================================
static void setup_actors( VIEWWORK* wk );
static void cleanup_actors( VIEWWORK* wk );
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdToss(TCB_PTR tcb, void* wk_ptr );




//------------------------------------------------------------------
/**
 * ���[�N�m��
 *
 * @param   wk_ptr		�m�ۂ������[�N�A�h���X��ۑ�����|�C���^�̃A�h���X
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A17_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();

		setup_actors( wk );

		CoinSpeed = DEFAULT_COIN_SPEED;
		Gravity = DEFAULT_GRAVITY;


		*wk_ptr = wk;
		return TRUE;
	}

	return FALSE;
}

static void setup_actors( VIEWWORK* wk )
{
	static const PACT_ADD_PARAM  actparam_coin = {
		{  FX32INT(COIN_DEFAULT_X), FX32INT(COIN_DEFAULT_Y) },
		ANMSEQ_FACE, 0, BGPRI2, 0, FALSE,
	};

	ArcUtil_ObjCharSet(ARC_POKETCH_IMG, NARC_poketch_coin_obj_ncgr, OBJTYPE_SUB, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

	PACT_TOOL_LoadCellDatas(&wk->clpack_coin, ARC_POKETCH_IMG,
				NARC_poketch_coin_ncer, NARC_poketch_coin_nanr, POKETCH_APP_VIEW_HEAPID );

	wk->act_coin = PACT_Add( wk->actsys, &actparam_coin, &wk->clpack_coin );

	if( wk->vpara->result == 0 )
	{
		PACT_ChangeAnmSeq( wk->act_coin, ANMSEQ_BOTTOM );
	}
}

static void cleanup_actors( VIEWWORK* wk )
{
	PACT_Del( wk->actsys, wk->act_coin );
	PACT_TOOL_UnloadCellDatas( &(wk->clpack_coin ) );
}




//------------------------------------------------------------------
/**
 * ���[�N�폜
 *
 * @param   wk		�m�ۂ������[�N�A�h���X
 *
 */
//------------------------------------------------------------------
void Poketch_A17_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		cleanup_actors( wk );
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
	{ CMD_TOSS, CmdToss, 0 },
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
void Poketch_A17_SetViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A17_WaitViewCommand(VIEWWORK* wk, u32 cmd)
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
BOOL Poketch_A17_WaitViewCommandAll(VIEWWORK* wk)
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
	void* load_p;
	NNSG2dPaletteData* pal;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_coin_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	ArcUtil_ScrnSet( ARC_POKETCH_IMG, NARC_poketch_coin_nscr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
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

	switch( PoketchViewTool_GetSeq( wk_ptr ) ){
	case 0:
		vwk->toss_stop_flag = TRUE;
		PoketchViewTool_FwdSeq( wk_ptr );
		/* fallthru */
	case 1:
		if( Poketch_A17_WaitViewCommand( vwk, CMD_TOSS ) )
		{
			GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
			DeleteCommand( wk_ptr );
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * �R�}���h�F�R�C���g�X����J�n
 *
 * @param   tcb		
 * @param   wk_ptr		
 *
 */
//------------------------------------------------------------------
static void CmdToss(TCB_PTR tcb, void* wk_ptr )
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	switch( PoketchViewTool_GetSeq( wk_ptr ) ){
	case 0:
		PoketchSePlay(POKETCH_SE_COINTOSS_START);
		PACT_ChangeAnmSeq( vwk->act_coin, ANMSEQ_ROLL );
		vwk->coin_ypos = COIN_DEFAULT_Y << FX32_SHIFT;
		vwk->coin_speed = CoinSpeed;
		vwk->toss_stop_flag = FALSE;
		PoketchViewTool_FwdSeq (wk_ptr );
		/* fallthru */
	case 1:
		if( vwk->toss_stop_flag )
		{
			DeleteCommand( wk_ptr );
			return;
		}
		vwk->coin_ypos += vwk->coin_speed;

		vwk->coin_speed += Gravity;
		if( vwk->coin_speed > 0 && vwk->coin_ypos >= (COIN_DEFAULT_Y << FX32_SHIFT) )
		{
			vwk->coin_speed = -( (vwk->coin_speed*56) / 100 );

			if( vwk->coin_speed < COIN_REFRECT_SPEED_BORDER )
			{
				PoketchSePlay(POKETCH_SE_COINTOSS_BOUND);
				vwk->coin_ypos = COIN_DEFAULT_Y << FX32_SHIFT;
			}
			else
			{
				PoketchSePlay(POKETCH_SE_COINTOSS_BOUND);

				PACT_ChangeAnmSeq( vwk->act_coin, (vpara->result)? ANMSEQ_FACE : ANMSEQ_BOTTOM );

				vwk->coin_ypos = COIN_DEFAULT_Y << FX32_SHIFT;
				PoketchViewTool_FwdSeq (wk_ptr );
			}
		}
		PACT_SetPos( vwk->act_coin, (COIN_DEFAULT_X << FX32_SHIFT), vwk->coin_ypos );
		break;

	case 2:
		DeleteCommand( wk_ptr );
	}
}


#ifdef PM_DEBUG
void PA17DEBUG_AddCoinSpeed( fx32 add )
{
	CoinSpeed += add;
	if( CoinSpeed >= 0 )
	{
		CoinSpeed -= add;
	}
}
void PA17DEBUG_AddGravity( fx32 add )
{
	Gravity += add;
	if( Gravity <= 0 )
	{
		Gravity -= add;
	}
}
#endif


