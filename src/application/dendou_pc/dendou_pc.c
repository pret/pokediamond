//============================================================================================
/**
 * @file	dendou_pc.c
 * @bfief	殿堂入りパソコン画面
 * @author	taya GAME FREAK inc.
 *
 * @date	2006.04.21
 */
//============================================================================================
#include "common.h"
#include "gflib\strbuf.h"
#include "system\buflen.h"

#include "application\dendou_pc.h"
#include "dendou_pc_common.h"

//--------------------------------------------------------------
/**
 *	定数
 */
//--------------------------------------------------------------
enum {
	HEAPSIZE_SYS  = 0x4000,
	HEAPSIZE_VIEW = 0x1c000,
};

//--------------------------------------------------------------
/**
 *	システムワーク
 */
//--------------------------------------------------------------
struct  _DENDOU_PC_WORK {
	DENDOU_PC_VIEWPARAM		vpara;
	DENDOU_PC_VIEW*			vwk;
	DENDOU_SAVEDATA*		saveData;
	int   recordMax;
	int   recordPos;

	BOOL	waitViewCommand;

};

//==============================================================
// Prototype
//==============================================================
static void set_view_command( DENDOU_PC_WORK* wk, int cmd );
static BOOL change_record_prev( DENDOU_PC_WORK* wk );
static BOOL change_record_next( DENDOU_PC_WORK* wk );
static void setup_view_param( DENDOU_PC_VIEWPARAM* vpara, DENDOU_SAVEDATA* saveData );
static void cleanup_view_param( DENDOU_PC_VIEWPARAM* vpara );
static void update_view_param( DENDOU_PC_VIEWPARAM* vpara, DENDOU_SAVEDATA* saveData, int recordPos );


//------------------------------------------------------------------
/**
 * PROC初期化
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT DendouPc_PROC_Init( PROC * proc, int * seq )
{
	DENDOU_PC_WORK* wk;

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_DENDOU_PC, HEAPSIZE_SYS );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_DENDOU_PC_VIEW, HEAPSIZE_VIEW );

	wk = PROC_AllocWork( proc, sizeof(DENDOU_PC_WORK), HEAPID_DENDOU_PC );
	if( wk )
	{
		wk->saveData = PROC_GetParentWork( proc );
		wk->recordPos = 0;
		wk->recordMax = DendouData_GetRecordCount( wk->saveData );

		setup_view_param( &(wk->vpara), wk->saveData );

		wk->vwk = DendouPCView_CreateWork( wk, &(wk->vpara) );
		wk->waitViewCommand = DendouPCView_StartCommand( wk->vwk, VCMD_INIT );
	}

	return PROC_RES_FINISH;
}
//------------------------------------------------------------------
/**
 * PROC終了
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT DendouPc_PROC_Quit( PROC * proc, int * seq )
{
	DENDOU_PC_WORK* wk = PROC_GetWork( proc );

	DendouPCView_DeleteWork( wk->vwk );
	cleanup_view_param( &(wk->vpara) );

	PROC_FreeWork( proc );

	sys_DeleteHeap( HEAPID_DENDOU_PC_VIEW );
	sys_DeleteHeap( HEAPID_DENDOU_PC );

	return PROC_RES_FINISH;
}


//------------------------------------------------------------------
/**
 * PROCメイン
 *
 * @param   proc		
 * @param   seq		
 *
 * @retval  PROC_RESULT		
 */
//------------------------------------------------------------------
PROC_RESULT DendouPc_PROC_Main( PROC * proc, int * seq )
{
	DENDOU_PC_WORK* wk = PROC_GetWork( proc );

	if( wk->waitViewCommand )
	{
		if( DendouPCView_WaitCommand(wk->vwk) == FALSE )
		{
			return PROC_RES_CONTINUE;
		}
		wk->waitViewCommand = FALSE;
	}


	switch( *seq ){
	case 0:
		if( sys.trg & PAD_BUTTON_B )
		{
			set_view_command( wk, VCMD_QUIT );
			(*seq)++;
			break;
		}
		if( sys.trg & PAD_BUTTON_A )
		{
			wk->vpara.paramMode ^= 1;
			set_view_command( wk, VCMD_CHANGE_PARAMMODE );
			break;
		}
		if( sys.trg & PAD_KEY_LEFT )
		{
			if( change_record_prev( wk ) )
			{
				set_view_command( wk, VCMD_CHANGE_RECORD );
			}
			break;
		}
		if( sys.trg & PAD_KEY_RIGHT )
		{
			if( change_record_next( wk ) )
			{
				set_view_command( wk, VCMD_CHANGE_RECORD );
			}
			break;
		}
		if( sys.trg & PAD_KEY_UP )
		{
			if( --(wk->vpara.pokePos) < 0 )
			{
				if( change_record_prev( wk ) )
				{
					wk->vpara.pokePos = wk->vpara.pokeCount - 1;
					set_view_command( wk, VCMD_CHANGE_RECORD );
				}
			}
			else
			{

				set_view_command( wk, VCMD_CHANGE_POKE );
			}
			break;
		}
		if( sys.trg & PAD_KEY_DOWN )
		{
			if( ++(wk->vpara.pokePos) >= wk->vpara.pokeCount )
			{
				if( change_record_next( wk ) )
				{
					set_view_command( wk, VCMD_CHANGE_RECORD );
				}
			}
			else
			{
				set_view_command( wk, VCMD_CHANGE_POKE );
			}
			break;
		}
		break;

	case 1:
		return PROC_RES_FINISH;
	}
	return PROC_RES_CONTINUE;
}


static void set_view_command( DENDOU_PC_WORK* wk, int cmd )
{
	wk->waitViewCommand = DendouPCView_StartCommand( wk->vwk, cmd );
}

static BOOL change_record_prev( DENDOU_PC_WORK* wk )
{
	if( ++(wk->recordPos) >= wk->recordMax )
	{
		wk->recordPos = 0;
	}

	update_view_param( &(wk->vpara), wk->saveData, wk->recordPos );

	return TRUE;
}
static BOOL change_record_next( DENDOU_PC_WORK* wk )
{

	if( --(wk->recordPos) < 0 )
	{
		wk->recordPos = wk->recordMax - 1;
	}

	update_view_param( &(wk->vpara), wk->saveData, wk->recordPos );

	return TRUE;
}



//======================================================================================
//======================================================================================

static void setup_view_param( DENDOU_PC_VIEWPARAM* vpara, DENDOU_SAVEDATA* saveData )
{
	int i;

	for(i=0; i<TEMOTI_POKEMAX; i++)
	{
		vpara->pokemon[i].nickname = STRBUF_Create( BUFLEN_POKEMON_NAME, HEAPID_DENDOU_PC );
		vpara->pokemon[i].oyaname  = STRBUF_Create( BUFLEN_PERSON_NAME, HEAPID_DENDOU_PC );
	}

	vpara->paramMode = PARAM_NORMAL;

	update_view_param( vpara, saveData, 0 );
}

static void cleanup_view_param( DENDOU_PC_VIEWPARAM* vpara )
{
	int i;

	for(i=0; i<TEMOTI_POKEMAX; i++)
	{
		STRBUF_Delete( vpara->pokemon[i].nickname );
		STRBUF_Delete( vpara->pokemon[i].oyaname );
	}
}

static void update_view_param( DENDOU_PC_VIEWPARAM* vpara, DENDOU_SAVEDATA* saveData, int recordPos )
{
	int i;

	OS_TPrintf("!! recPos:%d\n", recordPos);

	vpara->times = DendouData_GetRecordNumber( saveData, recordPos );
	vpara->pokeCount = DendouData_GetPokemonCount( saveData, recordPos );
	DendouData_GetDate( saveData, recordPos, &(vpara->date) );

	for(i=0; i<vpara->pokeCount; i++)
	{
		DendouData_GetPokemonData( saveData, recordPos, i, &(vpara->pokemon[i]) );
	}

	vpara->pokePos = 0;
}

