//============================================================================================
/**
 * @file	scr_item.c
 * @bfief	スクリプトコマンド：グッズ（グッズ、タマ、トラップ等）
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

#include "itemtool/myitem.h"		//MyItem_AddItem
#include "itemtool/item.h"			//ItemParamGet

#include "underground/ug_manager.h"

#include "battle/attr_def.h"
#include "zonedata.h"

#include "d_print.h"

#include "ev_pokemon.h"				//EvPoke_Add
#include "situation_local.h"

#include "scr_goods.h"


//============================================================================================
//
//	コマンド
//
//============================================================================================




//============================================================================================
//
//	グッズ関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * グッズを加える(PC)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddGoods(VM_MACHINE * core)		
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	UNDERGROUNDDATA* pUGData;
	u16 goods_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	pUGData = SaveData_GetUnderGroundData(sv);

	*ret_wk = UnderGroundAddGoodsPCItem(pUGData,goods_no);
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * グッズを減らす(PC)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSubGoods(VM_MACHINE * core)					
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 goods_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

//	*ret_wk = MyGoods_SubGoods( SaveData_GetMyGoods(fsys->savedata), goods_no, num, HEAPID_FIELD );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * グッズを加えられるかのチェック(PC)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddGoodsChk(VM_MACHINE * core)	
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	UNDERGROUNDDATA* pUGData;
	u16 goods_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	pUGData = SaveData_GetUnderGroundData(sv);

	*ret_wk = UnderGroundAddChkGoodsPCItem(pUGData,goods_no);
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * バッグのグッズチェック(PC)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCheckGoods(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 goods_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

//	*ret_wk = MyGoods_CheckGoods( SaveData_GetMyGoods(fsys->savedata), item_no, num, HEAPID_WORLD );
	return 0;
};

//============================================================================================
//
//	罠関連
//
//============================================================================================

BOOL EvCmdAddTrap(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	UNDERGROUNDDATA* pUGData;
	u16 trap_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	pUGData = SaveData_GetUnderGroundData(sv);

	*ret_wk = UnderGroundAddTrapBagItem(pUGData,trap_no);
	return 0;
};

BOOL EvCmdSubTrap(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 trap_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

//	*ret_wk = MyGoods_SubGoods( SaveData_GetMyGoods(fsys->savedata), goods_no, num, HEAPID_FIELD );
	return 0;
};

BOOL EvCmdAddTrapChk(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 trap_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

//	*ret_wk = MyGoods_AddCheck( SaveData_GetMyGoods(fsys->savedata), goods_no, num, HEAPID_FIELD );
	return 0;
};

BOOL EvCmdCheckTrap(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 trap_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

//	*ret_wk = MyGoods_CheckGoods( SaveData_GetMyGoods(fsys->savedata), item_no, num, HEAPID_WORLD );
	return 0;
};

//============================================================================================
//
//	お宝関連
//
//============================================================================================

BOOL EvCmdAddTreasure(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	UNDERGROUNDDATA* pUGData;
	u16 treasure_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	pUGData = SaveData_GetUnderGroundData(sv);

//	*ret_wk = UnderGroundAddGoodsBagItem(pUGData,trap_no);
	return 0;
};


BOOL EvCmdSubTreasure(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 treasure_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

//	*ret_wk = MyGoods_SubGoods( SaveData_GetMyGoods(fsys->savedata), goods_no, num, HEAPID_FIELD );
	return 0;
};

BOOL EvCmdAddTreasureChk(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 treasure_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

//	*ret_wk = MyGoods_AddCheck( SaveData_GetMyGoods(fsys->savedata), goods_no, num, HEAPID_FIELD );
	return 0;
};

BOOL EvCmdCheckTreasure(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 treasure_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

//	*ret_wk = MyGoods_CheckGoods( SaveData_GetMyGoods(fsys->savedata), item_no, num, HEAPID_WORLD );
	return 0;
};

//============================================================================================
//
//	タマ関連
//
//============================================================================================
BOOL EvCmdAddTama(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	UNDERGROUNDDATA* pUGData;
	u16 tama_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	pUGData = SaveData_GetUnderGroundData(sv);

	*ret_wk = UnderGroundAddStoneBagItem(pUGData,tama_no,num);
	return 0;

};

BOOL EvCmdSubTama(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 tama_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

//	*ret_wk = MyGoods_SubGoods( SaveData_GetMyGoods(fsys->savedata), goods_no, num, HEAPID_FIELD );
	return 0;
};

BOOL EvCmdAddTamaChk(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 tama_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

//	*ret_wk = MyGoods_AddCheck( SaveData_GetMyGoods(fsys->savedata), goods_no, num, HEAPID_FIELD );
	return 0;
};

BOOL EvCmdCheckTama(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 tama_no		= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

//	*ret_wk = MyGoods_CheckGoods( SaveData_GetMyGoods(fsys->savedata), item_no, num, HEAPID_WORLD );
	return 0;
};

//============================================================================================
//============================================================================================
