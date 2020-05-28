//============================================================================================
/**
 * @file	scr_kaseki.c
 * @bfief	�X�N���v�g�R�}���h�F�J�Z�L�֘A
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

#include "d_print.h"
#include "sodateya.h"

#include "ev_pokemon.h"				//EvPoke_Add

#include "scr_kaseki.h"

//============================================================================================
//
//	�R�}���h
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/*
 *	���Ε���
 */
//--------------------------------------------------------------------------------------------
#define KASEKI_MAX		(7)				//���΂̎��

// �Ђ݂̃R�n�N	->	�v�e��
// �����̃J�Z�L		->	�I���i�C�g
// ������̃J�Z�L	->	�J�u�g
// �˂����̃J�Z�L	->	�����[��
// �c���̃J�Z�L		->	�A�m�v�X
// ���ẴJ�Z�L		->	�^�e�g�v�X
// �������̃J�Z�L	->	�Y�K�C�f�X

const u16 kaseki_fukugen_tbl[KASEKI_MAX][2]=
{
 { ITEM_HIMITUNOKOHAKU	,	MONSNO_PUTERA		},
 { ITEM_KAINOKASEKI		,	MONSNO_OMUNAITO		},
 { ITEM_KOURANOKASEKI	,	MONSNO_KABUTO		},
 { ITEM_NEKKONOKASEKI	,	MONSNO_RIRIIRA		},
 { ITEM_TUMENOKASEKI	,	MONSNO_ANOPUSU		},
 { ITEM_TATENOKASEKI	,	MONSNO_TATETOPUSU	},		
 { ITEM_ZUGAINOKASEKI	,	MONSNO_PATIKI		},
};

//--------------------------------------------------------------------------------------------
/**
 *	���΂������邩�̃`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdKasekiCount(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u8 i;
	u16	ans,no;
	u16* ret_wk			= VMGetWork( core );

	for(i=0,no=0;i<KASEKI_MAX;i++){
		no += MyItem_GetItemNum( SaveData_GetMyItem(fsys->savedata), kaseki_fukugen_tbl[i][0], HEAPID_FIELD );
	}

	*ret_wk = no;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	�A�C�e���i���΁j�ԍ����A�����X�^�[�ԍ��֕ϊ�(0:���΂ł͂Ȃ��Ƃ��͂O�j
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdItemNoToMonsNo(VM_MACHINE * core)
{
	u16 i;
	u16* ret_wk	= VMGetWork( core );
	u16 itemno	= VMGetWorkValue(core);

	*ret_wk = 0;
	for(i=0;i<KASEKI_MAX;i++){
		if(kaseki_fukugen_tbl[i][0] == itemno) {
			*ret_wk = kaseki_fukugen_tbl[i][1];
			break;
		}
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	�莝����xxx�Ԗڂ̉��΂������ăA�C�e���ԍ��ɂ��ĕԂ�(0:�ŏ���1��)
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdKasekiItemNo(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u8 i;
	u16	ans,no;
	u16* ret_wk_i			= VMGetWork( core );
	u16* ret_wk_m			= VMGetWork( core );
	u16 tno			= VMGetWorkValue( core );

	*ret_wk_i = 0;
	*ret_wk_m = 0;

	for(i=0,no=0;i<KASEKI_MAX;i++){
		no += MyItem_GetItemNum( SaveData_GetMyItem(fsys->savedata), kaseki_fukugen_tbl[i][0], HEAPID_FIELD );	//�����Ă鐔��
		if(no >= tno){
			*ret_wk_i = kaseki_fukugen_tbl[i][0];
			*ret_wk_m = i;
			break;
		}
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//���g�p
BOOL EvCmdItemListSetProc(VM_MACHINE * core)
{
	return 0;
}

BOOL EvCmdItemListGetResult(VM_MACHINE * core)
{
	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
