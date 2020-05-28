//============================================================================================
/**
 * @file	scr_wazalist.c
 * @bfief	スクリプトコマンド：わざ選択画面関連
 * @author	Tomomichi Ohta
 * @date	06.07.08
 */
//============================================================================================
#include "common.h"

#include <nitro/code16.h> 
#include "system/pm_str.h"
#include "system\msgdata.h"			//MSGMAN_GetString
#include "system/brightness.h"		//ChangeBrightnessRequest
#include "system\wordset.h"			//WordSet_RegistPlayerName
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/get_text.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/pms_data.h"
#include "system/wipe.h"
#include "system/placename.h"

#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "battle/wazano_def.h"

#include "poketool/boxdata.h"

#include "..\application\p_status\ribbon.h"

#include "vm.h"
#include "scrcmd.h"
#include "script.h"
#include "scr_tool.h"
#include "ev_win.h"
#include "ev_time.h"

#include "battle/attr_def.h"
#include "zonedata.h"

#include "d_print.h"

#include "ev_pokemon.h"				//EvPoke_Add
#include "poketool/poke_memo.h"

#include "scr_wazalist.h"

//============================================================================================
//============================================================================================
static void WazaListSetProcCommon(VM_MACHINE * core,u16 mode,POKEMON_PARAM * pp,u16* waza_dat);

//============================================================================================
//
//	コマンド
//
//============================================================================================



//--------------------------------------------------------------------------------------------
/**
 * @brief	技忘れ関連：リスト表示
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	1		スクリプトからメイン制御に戻る
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdWazaListSetProc( VM_MACHINE * core )
{
	u16		num	= VMGetWorkValue(core);
	void ** buf;
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	*buf = FieldWazaListEvent_SetProc(HEAPID_EVENT, core->fsys,num);

	VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	技忘れ関連：リスト表示
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	1		スクリプトからメイン制御に戻る
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdWazaListGetResult(VM_MACHINE * core)
{
	void ** buf;
	u16 * ret_wk;
	ret_wk = VMGetWork(core);
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	GF_ASSERT(*buf != 0);
	*ret_wk = FieldWazaListEvent_GetSelect(*buf);
	if (*ret_wk == 4) {			//4==キャンセル
		*ret_wk = 0xff;
	}
	sys_FreeMemoryEz(*buf);
	*buf = NULL;

	return 0;
}

//============================================================================================
//
//				わざ教え／思い出し関連
//
//============================================================================================
#define LV_WAZA_OBOE_END	( LEVELUPWAZA_OBOE_END )	// 終端コード

//-----------------------------------------------------------------------------
/**
 *	ポケモンに教えられるわざ個数を取得
 */
//-----------------------------------------------------------------------------
BOOL EvCmdOshieWazaCount(VM_MACHINE * core)
{
#if 0			/*仕様変更により未完成*/
	POKEMON_PARAM * pp;
	u16* waza_dat;
	u16* ret_wk	= VMGetWork( core );
	u16 tno		= VMGetWorkValue( core );

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	waza_dat = sys_AllocMemory(HEAPID_EVENT, (1+1) * 2 );		//(１個分のワザ＋終端コード)＊16bit
	*(waza_dat+0) = WAZANO_HANERU;
	*(waza_dat+1) = LV_WAZA_OBOE_END;

	*ret_wk = WazaOshie_WazaTableChack(waza_dat);
	sys_FreeMemoryEz( waza_dat );
#endif
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	ポケモンが思い出せるわざ個数を取得
 */
//-----------------------------------------------------------------------------
BOOL EvCmdRemaindWazaCount(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16* waza_dat;
	u16* ret_wk	= VMGetWork( core );
	u16 tno		= VMGetWorkValue( core );

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);
	waza_dat = RemaindWazaGet( pp, HEAPID_EVENT );
	*ret_wk = WazaOshie_WazaTableChack(waza_dat);
	sys_FreeMemoryEz( waza_dat );

	return 0;
}


//-----------------------------------------------------------------------------
/**
 *	わざ教え選択画面　教え/思い出し共通部分
 */
//-----------------------------------------------------------------------------
static void WazaListSetProcCommon(VM_MACHINE * core,u16 mode,POKEMON_PARAM * pp,u16* waza_dat)
{
	void** buf	= GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	WAZAOSHIE_DATA *dat;

	dat = WazaOshie_DataAlloc(HEAPID_EVENT);
	*buf = dat;

	dat->pp		= pp;
	dat->myst	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	dat->cfg	= SaveData_GetConfig( core->fsys->savedata );
	dat->waza_tbl = waza_dat;
	dat->mode	=  mode;

	WazaOshie_ProcSet(core->fsys,dat);

	VM_SetWait( core, EvCmdWaitSubProcEnd );

	sys_FreeMemoryEz( waza_dat );
}


//-----------------------------------------------------------------------------
/**
 *	わざ教え選択画面呼び出し
 */
//-----------------------------------------------------------------------------
BOOL EvCmdOshieWazaListSetProc(VM_MACHINE * core)
{
#if 0			/*仕様変更により未完成*/
	POKEMON_PARAM * pp;
	u16		tno	= VMGetWorkValue(core);
	u16*	waza_dat;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	waza_dat = sys_AllocMemory(HEAPID_EVENT, (1+1) * 2 );		//(１個分のワザ＋終端コード)＊16bit
	*(waza_dat+0) = WAZANO_HANERU;
	*(waza_dat+1) = LV_WAZA_OBOE_END;

	WazaListSetProcCommon( core, WAZAOSHIE_MODE_TEACH, pp, waza_dat );

#endif
	return 1;
}


//-----------------------------------------------------------------------------
/**
 *	わざ思い出し選択画面呼び出し
 */
//-----------------------------------------------------------------------------
BOOL EvCmdRemaindWazaListSetProc(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16		tno	= VMGetWorkValue(core);
	u16*	waza_dat;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	waza_dat = RemaindWazaGet( pp, HEAPID_EVENT );

	WazaListSetProcCommon( core, WAZAOSHIE_MODE_REMIND, pp, waza_dat );

	return 1;
}

//-----------------------------------------------------------------------------
/**
 *	1個のみのわざ教え選択画面呼び出し
 */
//-----------------------------------------------------------------------------
BOOL EvCmdNormalWazaListSetProc(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16		tno	= VMGetWorkValue(core);
	u16		wazano	= VMGetWorkValue(core);
	u16*	waza_dat;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	waza_dat = sys_AllocMemory( HEAPID_EVENT, (1+1) * 2 );		//16bit * (テーブル1個分＋終端コード）

	*(waza_dat+0) = wazano;
	*(waza_dat+1) = LV_WAZA_OBOE_END;

	WazaListSetProcCommon( core, WAZAOSHIE_MODE_TEACH, pp, waza_dat );

	return 1;
}

//-----------------------------------------------------------------------------
/**
 *	わざ教え選択画面結果取り出し
 */
//-----------------------------------------------------------------------------
BOOL EvCmdOshieWazaListGetResult(VM_MACHINE * core)
{
#if 0			/*仕様変更により未完成*/
	WAZAOSHIE_DATA *dat;
	u16* ret_wk	= VMGetWork( core );
	void** buf	= GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);

	dat = *buf;

	GF_ASSERT(*buf != 0);

	if((dat->ret) == WAZAOSHIE_RET_SET){
		*ret_wk = 0;
	}else{
		*ret_wk = 0xff;
	}

	WazaOshie_DataFree(dat);
#endif
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	わざ思い出し選択画面結果取り出し
 */
//-----------------------------------------------------------------------------
BOOL EvCmdRemaindWazaListGetResult(VM_MACHINE * core)
{
	WAZAOSHIE_DATA *dat;
	u16* ret_wk	= VMGetWork( core );
	void** buf	= GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);

	dat = *buf;

	GF_ASSERT(*buf != 0);

	if((dat->ret) == WAZAOSHIE_RET_SET){
		*ret_wk = 0;
	}else{
		*ret_wk = 0xff;
	}

	WazaOshie_DataFree(dat);

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	1個のみのわざ教え選択画面結果取り出し
 */
//-----------------------------------------------------------------------------
BOOL EvCmdNormalWazaListGetResult(VM_MACHINE * core)
{
	WAZAOSHIE_DATA *dat;
	u16* ret_wk	= VMGetWork( core );
	void** buf	= GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);

	dat = *buf;

	GF_ASSERT(*buf != 0);

	if((dat->ret) == WAZAOSHIE_RET_SET){
		*ret_wk = 0;
	}else{
		*ret_wk = 0xff;
	}

	WazaOshie_DataFree(dat);

	return 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
