//============================================================================================
/**
 * @file	d_print.c
 * @bfief	デバッグ用ワーク＆フラグプリント関連
 * @bfief	※本来非常駐用だが、常駐想定での使用者が多いため玉田さん指示で常駐へ
 * @author	Tomomichi Ohta
 * @date	06.05.27
 */
//============================================================================================
#ifdef	PM_DEBUG

#include <nitro.h>
#include <nnsys.h>
#include "common.h"
#include "system/bmp_list.h"
#include "system/bmp_menu.h"
#include "fld_bmp.h"
#include "system/lib_pack.h"
#include "fntsys.h"
#include "system/fontproc.h"
#include "talk_msg.h"
#include "fieldsys.h"
#include "poketool/monsno.h"

#include "fieldsys.h"
#include "fieldmap.h"
#include "fld_bmp.h"
#include "talk_msg.h"
#include "fieldobj.h"
#include "fld_bgm.h"
#include "field_subproc.h"
#include "field/field.h"
#include "field/poketch_data.h"

#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"
#include "vm.h"
#include "scrcmd.h"
#include "script.h"
#include "scr_tool.h"
#include "scrcmd_def.h"
#include "ev_win.h"
#include "ev_time.h"
#include "guinness_win.h"
#include "..\fielddata\script\usescript.h"

#include  "d_print.h"


#ifdef	USE_DEBUG_SCRIPT_PRINT

#include "..\fielddata\script\savwtxt.dat"
#include "..\fielddata\script\savftxt.dat"

//-----------------------------------------------------------------------------
/**
 *	デバッグ専用命令　ワークの中身
 */
//-----------------------------------------------------------------------------
BOOL DebugScriptPrintWork(VM_MACHINE * core)
{
	u16 wk_val = (*((core)->PC)) + ((*(((core)->PC)+1)) << 8);

	u16* wk	= VMGetWork( core );
	u16 i,ct;

	OS_Printf( "dec[%6d] hex[%04x]  ",*wk,*wk );

	ct = (sizeof sawt/ sizeof sawt[0]);

	if(wk_val < 0x8000){
		for(i=0;i<ct;i++){
			if(wk_val == sawt[i].val){
				OS_Printf("%s ",sawt[i].wk_tbl);
				break;
			}
		}
	}else{
		if(wk_val == SCWK_PARAM0){ OS_Printf("SCWK_PARAM0"); }
		if(wk_val == SCWK_PARAM1){ OS_Printf("SCWK_PARAM1"); }
		if(wk_val == SCWK_PARAM2){ OS_Printf("SCWK_PARAM2"); }
		if(wk_val == SCWK_PARAM3){ OS_Printf("SCWK_PARAM3"); }
		if(wk_val == SCWK_TEMP0){ OS_Printf("SCWK_TEMP0"); }
		if(wk_val == SCWK_TEMP1){ OS_Printf("SCWK_TEMP1"); }
		if(wk_val == SCWK_TEMP2){ OS_Printf("SCWK_TEMP2"); }
		if(wk_val == SCWK_TEMP3){ OS_Printf("SCWK_TEMP3"); }
		if(wk_val == SCWK_ANSWER){ OS_Printf("SCWK_ANSWER"); }
	}

	OS_Printf("\n");

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	デバッグ専用命令　フラグの値を表示
 */
//-----------------------------------------------------------------------------
BOOL DebugScriptPrintFlag(VM_MACHINE * core)
{
	u16 flag_val = (*((core)->PC)) + ((*(((core)->PC)+1)) << 8);

	FIELDSYS_WORK* fsys = core->fsys;
	u16	flag = VMGetU16( core );
	u16 i,ct;

	if( CheckEventFlag( fsys, flag ) == 0){
		OS_Printf( "[off]	");
	}else{
		OS_Printf( "[on]	");
	}

	ct = (sizeof saft/ sizeof saft[0]);

	for(i=0;i<ct;i++){
		if(flag_val == saft[i].val){
			OS_Printf("%s",saft[i].flag_tbl);
			break;
		}

	}

	OS_Printf("\n");
	return 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#endif	//USE_DEBUG_SCRIPT_PRINT

#endif	//PM_DEBUG
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
