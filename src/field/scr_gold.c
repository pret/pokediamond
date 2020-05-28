//============================================================================================
/**
 * @file	scr_gold.c
 * @bfief	スクリプトコマンド：お金関連
 * @author	Tomomichi Ohta
 * @date	06.06.26
 */
//============================================================================================
//============================================================================================
//
//	お金関連
//
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

#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"
#include "ev_win.h"

#include "scr_gold.h"


//============================================================================================
//
//	コマンド
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * お金を加える
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddGold(VM_MACHINE * core)
{
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u32 gold;
	
	gold = VMGetU32(core);

	Mystatus_AddGold( my, gold);
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * お金を引く
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSubGold(VM_MACHINE * core)
{
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u32 gold;
	
	gold = VMGetU32(core);

	Mystatus_SubGold( my, gold);
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * お金を引く(ワーク対応型。扱える額に限度があるので注意）
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSubMyGold( VM_MACHINE * core )
{
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u32 gold;
	
	gold = VMGetWorkValue(core);

	Mystatus_SubGold( my, gold);
	return 0;
};


//--------------------------------------------------------------------------------------------
/**
 * 金額を調べる
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCompGold(VM_MACHINE * core)	
{
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u16 * work;
	u32 gold,my_gold;

	work  = VMGetWork(core);

	gold = VMGetU32(core);
	my_gold = MyStatus_GetGold( my);

	if(my_gold < gold){
		*work = FALSE;
	}else{
		*work = TRUE;
	}

	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * 金額を調べる(ワーク対応型。扱える額に限度があるので注意）
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCompMyGold( VM_MACHINE * core )
{
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u16 * work;
	u32 gold,my_gold;

	work  = VMGetWork(core);
	gold	= VMGetWorkValue( core );
	my_gold = MyStatus_GetGold( my);

	if(my_gold < gold){
		*work = FALSE;
	}else{
		*work = TRUE;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 所持金ウィンドウ表示
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGoldWinWrite(VM_MACHINE * core)	
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 x = VMGetWorkValue(core);
	u16 z = VMGetWorkValue(core);

	GF_BGL_BMPWIN** pMsgWinDat;
	pMsgWinDat = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_GOLDWINDAT );
	*pMsgWinDat = EvWin_GoldWinPut( core->fsys, x, z );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * 所持金ウィンドウ削除
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGoldWinDel(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	GF_BGL_BMPWIN** pMsgWinDat = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_GOLDWINDAT );
	EvWin_GoldWinDel( *pMsgWinDat );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * 所持金ウィンドウ再表示
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGoldWrite(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	GF_BGL_BMPWIN** pMsgWinDat = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_GOLDWINDAT );
	EvWin_GoldWrite( core->fsys, *pMsgWinDat );
	return 0;
};

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
