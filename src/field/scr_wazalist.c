//============================================================================================
/**
 * @file	scr_wazalist.c
 * @bfief	�X�N���v�g�R�}���h�F�킴�I����ʊ֘A
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
//	�R�}���h
//
//============================================================================================



//--------------------------------------------------------------------------------------------
/**
 * @brief	�Z�Y��֘A�F���X�g�\��
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 * @return	1		�X�N���v�g���烁�C������ɖ߂�
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
 * @brief	�Z�Y��֘A�F���X�g�\��
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 * @return	1		�X�N���v�g���烁�C������ɖ߂�
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
	if (*ret_wk == 4) {			//4==�L�����Z��
		*ret_wk = 0xff;
	}
	sys_FreeMemoryEz(*buf);
	*buf = NULL;

	return 0;
}

//============================================================================================
//
//				�킴�����^�v���o���֘A
//
//============================================================================================
#define LV_WAZA_OBOE_END	( LEVELUPWAZA_OBOE_END )	// �I�[�R�[�h

//-----------------------------------------------------------------------------
/**
 *	�|�P�����ɋ�������킴�����擾
 */
//-----------------------------------------------------------------------------
BOOL EvCmdOshieWazaCount(VM_MACHINE * core)
{
#if 0			/*�d�l�ύX�ɂ�薢����*/
	POKEMON_PARAM * pp;
	u16* waza_dat;
	u16* ret_wk	= VMGetWork( core );
	u16 tno		= VMGetWorkValue( core );

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	waza_dat = sys_AllocMemory(HEAPID_EVENT, (1+1) * 2 );		//(�P���̃��U�{�I�[�R�[�h)��16bit
	*(waza_dat+0) = WAZANO_HANERU;
	*(waza_dat+1) = LV_WAZA_OBOE_END;

	*ret_wk = WazaOshie_WazaTableChack(waza_dat);
	sys_FreeMemoryEz( waza_dat );
#endif
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	�|�P�������v���o����킴�����擾
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
 *	�킴�����I����ʁ@����/�v���o�����ʕ���
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
 *	�킴�����I����ʌĂяo��
 */
//-----------------------------------------------------------------------------
BOOL EvCmdOshieWazaListSetProc(VM_MACHINE * core)
{
#if 0			/*�d�l�ύX�ɂ�薢����*/
	POKEMON_PARAM * pp;
	u16		tno	= VMGetWorkValue(core);
	u16*	waza_dat;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	waza_dat = sys_AllocMemory(HEAPID_EVENT, (1+1) * 2 );		//(�P���̃��U�{�I�[�R�[�h)��16bit
	*(waza_dat+0) = WAZANO_HANERU;
	*(waza_dat+1) = LV_WAZA_OBOE_END;

	WazaListSetProcCommon( core, WAZAOSHIE_MODE_TEACH, pp, waza_dat );

#endif
	return 1;
}


//-----------------------------------------------------------------------------
/**
 *	�킴�v���o���I����ʌĂяo��
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
 *	1�݂̂̂킴�����I����ʌĂяo��
 */
//-----------------------------------------------------------------------------
BOOL EvCmdNormalWazaListSetProc(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16		tno	= VMGetWorkValue(core);
	u16		wazano	= VMGetWorkValue(core);
	u16*	waza_dat;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	waza_dat = sys_AllocMemory( HEAPID_EVENT, (1+1) * 2 );		//16bit * (�e�[�u��1���{�I�[�R�[�h�j

	*(waza_dat+0) = wazano;
	*(waza_dat+1) = LV_WAZA_OBOE_END;

	WazaListSetProcCommon( core, WAZAOSHIE_MODE_TEACH, pp, waza_dat );

	return 1;
}

//-----------------------------------------------------------------------------
/**
 *	�킴�����I����ʌ��ʎ��o��
 */
//-----------------------------------------------------------------------------
BOOL EvCmdOshieWazaListGetResult(VM_MACHINE * core)
{
#if 0			/*�d�l�ύX�ɂ�薢����*/
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
 *	�킴�v���o���I����ʌ��ʎ��o��
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
 *	1�݂̂̂킴�����I����ʌ��ʎ��o��
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
