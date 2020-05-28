//============================================================================================
/**
 * @file	scr_dprint.c
 * @bfief	スクリプトコマンド：デバッグ表示関連
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

#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "vm.h"
#include "scrcmd.h"
#include "script.h"
#include "scr_tool.h"
#include "ev_win.h"
#include "ev_time.h"

#include "battle/attr_def.h"
#include "zonedata.h"

#include "itemtool/myitem.h"		//MyItem_AddItem
#include "itemtool/item.h"			//ItemParamGet

//#include "d_print.h" //060727 常駐領域確保の為、ノーマル版は無効へ

#include "scr_dprint.h"

//============================================================================================
//
//	コマンド
//
//============================================================================================

//-----------------------------------------------------------------------------
/**
 *	デバッグ専用命令　ワークの中身
 */
//-----------------------------------------------------------------------------
BOOL EvCmdDebugPrintWork(VM_MACHINE * core)
{
#ifdef	USE_DEBUG_SCRIPT_PRINT
	DebugScriptPrintWork(core);
#else
	GF_ASSERT(0);
#endif
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	デバッグ専用命令　フラグの値を表示
 */
//-----------------------------------------------------------------------------
BOOL EvCmdDebugPrintFlag(VM_MACHINE * core)
{
#ifdef	USE_DEBUG_SCRIPT_PRINT
	DebugScriptPrintFlag(core);
#else
	GF_ASSERT(0);
#endif
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	デバッグ専用命令(常駐領域版。いつでも使用OK）　ワークの中身
 */
//-----------------------------------------------------------------------------
BOOL EvCmdDebugPrintWorkStationed(VM_MACHINE * core)
{
#ifdef	PM_DEBUG
	u16 wk_val = (*((core)->PC)) + ((*(((core)->PC)+1)) << 8);
	u16 i,ct;

	u16* wk	= VMGetWork( core );

	OS_Printf( "dec[%6d] hex[%04x]  ",*wk,*wk );

	if(wk_val == 0x8000){
		OS_Printf("SCWK_PARAM0 ");
	}else if(wk_val == 0x8001){
		OS_Printf("SCWK_PARAM1 ");
	}else if(wk_val == 0x8002){
		OS_Printf("SCWK_PARAM2 ");
	}else if(wk_val == 0x8003){
		OS_Printf("SCWK_PARAM3 ");
	}else if(wk_val == 0x8004){
		OS_Printf("SCWK_TEMP0 ");
	}else if(wk_val == 0x8005){
		OS_Printf("SCWK_TEMP1 ");
	}else if(wk_val == 0x8006){
		OS_Printf("SCWK_TEMP2 ");
	}else if(wk_val == 0x8004){
		OS_Printf("SCWK_TEMP7 ");
	}else if(wk_val == 0x800c){
		OS_Printf("SCWK_ANSWER ");
	}else if((wk_val >= 0x4000)&&(wk_val < (0x4000+32))){
		OS_Printf("LOCALWORK%d ",(wk_val-0x4000));
	}else{
		OS_Printf("0x%4x ",wk_val);
	}

	OS_Printf("\n");
#endif

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	デバッグ専用命令(常駐領域版。いつでも使用OK）　フラグの中身
 */
//-----------------------------------------------------------------------------
BOOL EvCmdDebugPrintFlagStationed(VM_MACHINE * core)
{
#ifdef	PM_DEBUG
	u16 flag_val = (*((core)->PC)) + ((*(((core)->PC)+1)) << 8);

	FIELDSYS_WORK* fsys = core->fsys;
	u16	flag = VMGetU16( core );

	if( CheckEventFlag( fsys, flag ) == 0){
		OS_Printf( "[off]	");
	}else{
		OS_Printf( "[on]	");
	}

	OS_Printf("0x%4x ",flag);

	OS_Printf("\n");
#endif
	return 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
