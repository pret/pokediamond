//============================================================================================
/**
 * @file	scr_item.c
 * @bfief	�X�N���v�g�R�}���h�F�A�C�e���֘A
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

#include "battle/attr_def.h"
#include "zonedata.h"

#include "d_print.h"

#include "ev_pokemon.h"				//EvPoke_Add
#include "situation_local.h"

#include "scr_item.h"


//============================================================================================
//
//	�R�}���h
//
//============================================================================================


//============================================================================================
//
//	�A�C�e���֘A
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e����������
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddItem(VM_MACHINE * core)		
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 item_no			= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = MyItem_AddItem( SaveData_GetMyItem(fsys->savedata), item_no, num, HEAPID_FIELD );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e�������炷
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSubItem(VM_MACHINE * core)			
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 item_no			= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = MyItem_SubItem( SaveData_GetMyItem(fsys->savedata), item_no, num, HEAPID_FIELD );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * �A�C�e�����������邩�`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddItemChk(VM_MACHINE * core)	
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 item_no			= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = MyItem_AddCheck( SaveData_GetMyItem(fsys->savedata), item_no, num, HEAPID_FIELD );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * �o�b�O�̃A�C�e���`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCheckItem(VM_MACHINE * core)			
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 item_no			= VMGetWorkValue(core);
	u16 num				= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	//060526 HEAPID_FIELD �� HEAPID_WORLD�ɕύX FLAG_CHANGE_LABEL�Ŏg�p���邽�߁I
	*ret_wk = MyItem_CheckItem( SaveData_GetMyItem(fsys->savedata), item_no, num, HEAPID_WORLD );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * �Z�}�V���̃A�C�e���i���o�[���`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdWazaMachineItemNoCheck( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 itemno			= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = WazaMachineItemNoCheck( itemno );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�b�g�i���o�[�擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdGetPocketNo(VM_MACHINE * core)		
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 itemno			= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = (u16)ItemParamGet( itemno, ITEM_PRM_POCKET, HEAPID_WORLD );
	return 0;
};

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------


//���g�p
BOOL EvCmdAddPCBoxItem( VM_MACHINE * core )
{

	return 0;
}

BOOL EvCmdCheckPCBoxItem( VM_MACHINE * core )
{

	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
