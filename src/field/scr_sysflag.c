//============================================================================================
/**
 * @file	scr_sysflag.c
 * @bfief	スクリプトコマンド：SYSFLAG操作関連
 * @author	Tomomichi Ohta
 * @date	06.06.30
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

#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

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
#include "situation_local.h"

#include "scr_sysflag.h"


//============================================================================================
//
//	コマンド
//
//============================================================================================


//============================================================================================
//
//	システムフラグのゲット、セット関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　図鑑入手済みか取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagZukanGet( VM_MACHINE * core )
{
	const ZUKAN_WORK* zw = SaveData_GetZukanWork( core->fsys->savedata );
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = ZukanWork_GetZukanGetFlag( zw );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　図鑑セット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagZukanSet( VM_MACHINE * core )
{
	ZUKAN_WORK* zw = SaveData_GetZukanWork( core->fsys->savedata );

	ZukanWork_SetZukanGetFlag( zw );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　シューズ入手済みか取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagShoesGet( VM_MACHINE * core )
{
	SITUATION *situ;
	PLAYER_SAVE_DATA *jikisave;
	u16* ret_wk	= VMGetWork( core );

	situ = SaveData_GetSituation( core->fsys->savedata );
	jikisave = Situation_GetPlayerSaveData( situ );
	*ret_wk = Player_SaveDataDashCheck( jikisave );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　シューズセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagShoesSet( VM_MACHINE * core )
{
	SITUATION *situ;
	PLAYER_SAVE_DATA *jikisave;

	situ = SaveData_GetSituation( core->fsys->savedata );
	jikisave = Situation_GetPlayerSaveData( situ );
	Player_SaveDataDashSet( jikisave, TRUE );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　バッジ入手済みか取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagBadgeGet( VM_MACHINE * core )
{
	u16 no		= VMGetWorkValue( core );		//バッジの種類
	u16* ret_wk	= VMGetWork( core );

	GF_ASSERT(no < 8)
	*ret_wk = MyStatus_GetBadgeFlag(SaveData_GetMyStatus(core->fsys->savedata), no);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　バッジセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagBadgeSet( VM_MACHINE * core )
{
	u16 no		= VMGetWorkValue( core );		//バッジの種類
	GF_ASSERT(no < 8)
	MyStatus_SetBadgeFlag(SaveData_GetMyStatus(core->fsys->savedata), no);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　バッグ入手済みか取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagBagGet( VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );
	*ret_wk = SysFlag_BagCheck( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　バッジ入手数取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
const u8 badge_num_tbl[8]={
 BADGE_ID_C03,
 BADGE_ID_C04,
 BADGE_ID_C07,
 BADGE_ID_C06,
 BADGE_ID_C05,
 BADGE_ID_C02,
 BADGE_ID_C09,
 BADGE_ID_C08
};

BOOL EvCmdSysFlagBadgeCount( VM_MACHINE * core )
{
	u16 i,ct;
	u16* ret_wk	= VMGetWork( core );

	for(i=0,ct=0;i<8;i++){
		if(MyStatus_GetBadgeFlag(SaveData_GetMyStatus(core->fsys->savedata), badge_num_tbl[i]) == 1){
			ct++;
		}
	}

	*ret_wk = ct;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　バッグセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagBagSet( VM_MACHINE * core )
{
	SysFlag_BagSet( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　連れ歩きフラグ取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagPairGet( VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );
	*ret_wk = SysFlag_PairCheck( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　連れ歩きフラグセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagPairSet( VM_MACHINE * core )
{
	SysFlag_PairSet( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　連れ歩きフラグリセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagPairReset( VM_MACHINE * core )
{
	SysFlag_PairReset( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　一歩動いたかフラグ取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagOneStepGet( VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );
	*ret_wk = SysFlag_OneStepCheck( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　一歩動いたかフラグセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagOneStepSet( VM_MACHINE * core )
{
	SysFlag_OneStepSet( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　一歩動いたかフラグリセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagOneStepReset( VM_MACHINE * core )
{
	SysFlag_OneStepReset( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　ゲームクリアフラグ取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagGameClearGet( VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );
	*ret_wk = SysFlag_GameClearCheck( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ　ゲームクリアフラグセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagGameClearSet( VM_MACHINE * core )
{
	// 使われてないらしいよ by Mori 2006/07/18
	SysFlag_GameClearSet( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムフラグ	かいりき操作
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagKairiki( VM_MACHINE * core )
{
	u8 mode;
	u16 * ret_wk;
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);

	mode = VMGetU8(core);
	switch (mode) {
	case FLAG_MODE_SET:
		SysFlag_KairikiSet(ev);
		break;
	case FLAG_MODE_RESET:
		SysFlag_KairikiReset(ev);
		break;
	case FLAG_MODE_GET:
		ret_wk = VMGetWork(core);
		*ret_wk = SysFlag_KairikiCheck(ev);
		break;
	default:
		GF_ASSERT_MSG(0, "FLAG MODE ERROR %d\n", mode);
	}
	
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	システムフラグ	フラッシュ操作
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagFlash(VM_MACHINE * core)
{
	u8 mode;
	u16 * ret_wk;
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);

	mode = VMGetU8(core);
	switch (mode) {
	case FLAG_MODE_SET:
		SysFlag_FlashSet(ev);
		break;
	case FLAG_MODE_RESET:
		SysFlag_FlashReset(ev);
		break;
	case FLAG_MODE_GET:
		ret_wk = VMGetWork(core);
		*ret_wk = SysFlag_FlashCheck(ev);
		break;
	default:
		GF_ASSERT_MSG(0, "FLAG MODE ERROR %d\n", mode);
	}
	
	return 0;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief	システムフラグ	きりばらい操作
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSysFlagKiribarai(VM_MACHINE * core)
{
	u8 mode;
	u16 * ret_wk;
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);

	mode = VMGetU8(core);
	switch (mode) {
	case FLAG_MODE_SET:
		SysFlag_KiribaraiSet(ev);
		break;
	case FLAG_MODE_RESET:
		SysFlag_KiribaraiReset(ev);
		break;
	case FLAG_MODE_GET:
		ret_wk = VMGetWork(core);
		*ret_wk = SysFlag_KiribaraiCheck(ev);
		break;
	default:
		GF_ASSERT_MSG(0, "FLAG MODE ERROR %d\n", mode);
	}
	
	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
