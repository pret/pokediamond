//============================================================================================
/**
 * @file	scr_n_park.h
 * @bfief	スクリプトコマンド：自然公園関連
 * @author	Tomomichi Ohta
 * @date	06.06.26
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
#include "ev_win.h"

#include "include/application/imageClip/imc_sys.h"	//ImageClipProcData
#include "include/application/imageClip/imc_preview.h"	//ImageClipProcData

#include "scr_n_park.h"

//-----------------------------------------------------------------------------
/**
 *	自然公園歩数カウントクリア
 */
//-----------------------------------------------------------------------------
BOOL EvCmdNaturalParkWalkCountClear(VM_MACHINE * core)
{
	SysWork_ParkWalkCountClear(SaveData_GetEventWork(core->fsys->savedata));
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	自然公園歩数チェック
 */
//-----------------------------------------------------------------------------
BOOL EvCmdNaturalParkWalkCountGet(VM_MACHINE * core)
{
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = SysWork_ParkWalkCountGet(SaveData_GetEventWork(core->fsys->savedata));
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	自然公園歩数チェック
 */
//-----------------------------------------------------------------------------
static const u16 NaturalParkItemTbl[6][10]={
	{
		IMC_ACCE_WATA00, IMC_ACCE_WATA05, IMC_ACCE_HANE03, IMC_ACCE_STONE05, IMC_ACCE_LEAF00,
		IMC_ACCE_UROKO01, IMC_ACCE_HANE_GROUP01, IMA_ACCE_MUSHROOM00, IMC_ACCE_UROKO04, IMC_ACCE_KIRIKABU00
	},
	{
		IMC_ACCE_WATA02, IMC_ACCE_HANE01, IMC_ACCE_HANE02, IMC_ACCE_HANE_GROUP00,IMC_ACCE_UROKO05,
		IMC_ACCE_WATA00, IMC_ACCE_HANE_TABA01, IMC_ACCE_TUME00, IMC_ACCE_LEAF02, IMC_ACCE_UROKO03
	},
	{
		IMC_ACCE_STONE02, IMC_ACCE_STONE03, IMC_ACCE_WATA03, IMC_ACCE_STONE05, IMC_ACCE_HANE_TABA00,
		IMC_ACCE_TUME01, IMC_ACCE_UROKO05, IMC_ACCE_STONE00, IMC_ACCE_UROKO02, IMA_ACCE_MUSHROOM01
	},
	{
		IMC_ACCE_UROKO00, IMC_ACCE_HANE00, IMC_ACCE_HANE03, IMC_ACCE_UROKO01, IMA_ACCE_MUSHROOM00,
		IMC_ACCE_STONE03, IMC_ACCE_HANE_GROUP01, IMC_ACCE_HANE_GROUP00, IMC_ACCE_LEAF01, IMC_ACCE_STONE00
	},
	{
		IMC_ACCE_WATA05, IMC_ACCE_WATA03, IMC_ACCE_LEAF00, IMC_ACCE_HANE01, IMC_ACCE_HANE02,
		IMC_ACCE_WATA01, IMC_ACCE_STONE01, IMC_ACCE_UROKO04, IMC_ACCE_HANE_TABA00, IMC_ACCE_UROKO03
	},
	{
		IMC_ACCE_UROKO00, IMC_ACCE_TUME01, IMC_ACCE_WATA02, IMC_ACCE_HANE02, IMC_ACCE_TUME00,
		IMC_ACCE_WATA04, IMC_ACCE_STONE02, IMC_ACCE_LEAF01, IMC_ACCE_UROKO02, IMC_ACCE_STONE04
	}
};

BOOL EvCmdNaturalParkAccessoryNoGet(VM_MACHINE * core)
{
	u8 i,j;
	u16 rnd;
	u16* ret_wk	= VMGetWork( core );
	u16 mon_no	= VMGetWorkValue( core );

	rnd = gf_rand() % 100;

	if(rnd < (15)) {
		i = 0;
	}else if(rnd < (15+15)) {
		i = 1;
	}else if(rnd < (15+15+15)) {
		i = 2;
	}else if(rnd < (15+15+15+15)) {
		i = 3;
	}else if(rnd < (15+15+15+15+10)) {
		i = 4;
	}else if(rnd < (15+15+15+15+10+10)) {
		i = 5;
	}else if(rnd < (15+15+15+15+10+10+8)) {
		i = 6;
	}else if(rnd < (15+15+15+15+10+10+8+5)) {
		i = 7;
	}else if(rnd < (15+15+15+15+10+10+8+5+5)) {
		i = 8;
	}else{
		i = 9;
	}

	switch(mon_no){
	case MONSNO_PIPPI:
	case MONSNO_ENEKO:
		j=0;
		break;
	case MONSNO_HUUSEN:
	case MONSNO_ATYAMO:
		j=1;
		break;
	case MONSNO_PATIRISSU:
	case MONSNO_KODAKKU:
		j=2;
		break;
	case MONSNO_KINOKOKO:
	case MONSNO_PURIN:
		j=3;
		break;
	case MONSNO_PIKATYUU:
		j=4;
		break;
	case MONSNO_MIMITTO:
	case MONSNO_KORAKKII:
		j=5;
		break;
	default:	//※念のためエラー処理
		j=0;
	}

	*ret_wk = NaturalParkItemTbl[j][i];

	return 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
