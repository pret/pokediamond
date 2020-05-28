//============================================================================================
/**
 * @file	scr_coin.c
 * @bfief	�X�N���v�g�R�}���h�F�R�C���֘A
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

#include "savedata/coin.h"				//�R�C���������֐��p

#include "scr_coin.h"

//============================================================================================
//
//	�R�}���h
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �����R�C���E�B���h�E�\��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCoinWinWrite(VM_MACHINE * core)	
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 x = VMGetWorkValue(core);
	u16 z = VMGetWorkValue(core);

	GF_BGL_BMPWIN** pMsgWinDat;
	pMsgWinDat = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_COINWINDAT );
	*pMsgWinDat = EvWin_CoinWinPut( core->fsys, x, z );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����R�C���E�B���h�E�폜
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCoinWinDel(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	GF_BGL_BMPWIN** pMsgWinDat = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_COINWINDAT );
	EvWin_CoinWinDel(* pMsgWinDat );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����R�C���ĕ\��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCoinWrite(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	GF_BGL_BMPWIN** pMsgWinDat = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_COINWINDAT );
	EvWin_CoinWrite( core->fsys, *pMsgWinDat );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����R�C�������擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCheckCoin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	COIN * coin = SaveData_GetMyCoin(sv);
	u16 * work;

	work  = VMGetWork(core);
	*work = (u16)COIN_GetValue(coin);

	return	0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����R�C����������
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddCoin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	COIN * coin = SaveData_GetMyCoin(sv);
	u16 value;
	
	value = VMGetWorkValue(core);
	COIN_Add(coin, value);

	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * �����R�C�������炷
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSubCoin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	COIN * coin = SaveData_GetMyCoin(sv);
	u16 value;
	
	value = VMGetWorkValue(core);
	COIN_Sub(coin, value);

	return	0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����R�C�������炷(wk��p�Łj
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSubWkCoin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	COIN * coin = SaveData_GetMyCoin(sv);
	u16* c_wk			= VMGetWork(core);
	u16 value;
	
	value = *c_wk;

	COIN_Sub(coin, value);

	return	0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����R�C�������擾(�����Ă��邩�ǂ�����Ԃ��i_COMP_GOLD��COIN�Łj
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCompCoin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	SAVEDATA * sv = fsys->savedata;
	COIN * coin_t = SaveData_GetMyCoin(sv);
	u32 coin,my_coin;
	u16* ret_wk			= VMGetWork( core );
	coin = VMGetU32(core);

	my_coin = COIN_GetValue(coin_t);

	if(my_coin < coin){
		*ret_wk = FALSE;
	}else{
		*ret_wk = TRUE;
	}

	return	0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����R�C�������擾(�����Ă��邩�ǂ�����Ԃ�WK��p�i_COMP_GOLD��COIN�Łj
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCompWkCoin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	SAVEDATA * sv = fsys->savedata;
	COIN * coin_t = SaveData_GetMyCoin(sv);
	u16* ret_wk			= VMGetWork( core );
	u16* c_wk			= VMGetWork(core);
	u32 coin,my_coin;
	coin = *c_wk;

	my_coin = COIN_GetValue(coin_t);

	if(my_coin < coin){
		*ret_wk = FALSE;
	}else{
		*ret_wk = TRUE;
	}

	return	0;
}


//--------------------------------------------------------------------------------------------
/**
 * �������������邩�`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdAddCoinChk(VM_MACHINE * core)	
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;
	COIN * coin = SaveData_GetMyCoin(sv);
	u16* ret_wk			= VMGetWork( core );
	u16 value = VMGetWorkValue(core);

	*ret_wk = COIN_AddCheck(coin, value);
	return 0;
};

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
