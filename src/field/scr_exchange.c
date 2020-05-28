//============================================================================================
/**
 * @file	scr_exchange.c
 * @bfief	スクリプトコマンド：景品交換所
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

#include "vm.h"
#include "scrcmd.h"
#include "script.h"
#include "scr_tool.h"
#include "ev_win.h"
#include "ev_time.h"

#include "zonedata.h"

#include "itemtool/myitem.h"		//MyItem_AddItem
#include "itemtool/item.h"			//ItemParamGet

#include "d_print.h"


#include "scr_exchange.h"

//============================================================================================
//
//	コマンド
//
//============================================================================================



//--------------------------------------------------------------------------------------------
/**
 * コインと交換できるアイテムのデータを返す
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetCoinGift( VM_MACHINE * core )
{
	u16	item_idx = VMGetWorkValue(core);	//アイテムindex
	u16* ret_item = VMGetWork(core);
	u16* ret_bp = VMGetWork(core);

	static const u16 coingift_list[][2] = {
		{ ITEM_SIRUKUNOSUKAAHU,1000 },
		{ ITEM_KOUKAKURENZU,1000 },
		{ ITEM_FOOKASURENZU,1000 },
		{ ITEM_METORONOOMU,1000 },

		{ ITEM_WAZAMASIN90,2000 },
		{ ITEM_WAZAMASIN58,2000 },
		{ ITEM_WAZAMASIN75,4000 },
		{ ITEM_WAZAMASIN32,4000 },
		{ ITEM_WAZAMASIN44,6000 },
		{ ITEM_WAZAMASIN89,6000 },
		{ ITEM_WAZAMASIN10,6000 },
		{ ITEM_WAZAMASIN27,8000 },
		{ ITEM_WAZAMASIN21,8000 },
		{ ITEM_WAZAMASIN35,10000 },
		{ ITEM_WAZAMASIN24,10000 },
		{ ITEM_WAZAMASIN13,10000 },
		{ ITEM_WAZAMASIN29,10000 },
		{ ITEM_WAZAMASIN74,15000 },
		{ ITEM_WAZAMASIN68,20000 },
	};

	*ret_item = coingift_list[item_idx][0];
	*ret_bp = coingift_list[item_idx][1];

	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
