//============================================================================================
/**
 * @file	scr_pokepark.c
 * @brief	�X�N���v�g�R�}���h�F�|�P�p�[�N�֘A
 * @author	tamada GAME FREAK inc.
 * @date	2006.06.07
 */
//
//============================================================================================

#include "common.h"
#include "script.h"
#include "fieldsys.h"
#include "field_subproc.h"
#include "savedata/get_poke.h"

#include "scrcmd_def.h"
#include "scr_pokepark.h"

#include "savedata/pokepark_data.h"

#include "sysflag.h"

#include "pokepark_sys.h"
#include "poketool/poke_memo.h"

//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
///	�|�P�p�[�N�p�R�}���h�F�J�n�E�I������
//-----------------------------------------------------------------------------
BOOL EvCmdPokeParkControl(VM_MACHINE * core)
{
	EVENTWORK * ev = SaveData_GetEventWork(core->fsys->savedata);
	u16 mode = VMGetWorkValue(core);
	if (mode == POKEPARK_MODE_START) {
		SysFlag_PokeParkSet(ev);
		PokeParkSys_Init(core->fsys);	//�G���J�E���g�ݒ�Ƃ��A���ԃJ�E���g�J�n�Ƃ�
	} else if (mode == POKEPARK_MODE_END) {
		SysFlag_PokeParkReset(ev);
		PokeParkSys_Finish(core->fsys); //���ԃJ�E���g�X�g�b�v�Ƃ�
	} else {
		GF_ASSERT(0);
	}
	return 0;
}

//-----------------------------------------------------------------------------
///	�|�P�p�[�N�p�R�}���h�F�a�����|�P�����𐔂���
//-----------------------------------------------------------------------------
BOOL EvCmdPokeParkDepositCount(VM_MACHINE * core)
{
	POKEPARK_DATA * ppd = SaveData_GetPokeParkData(core->fsys->savedata);
	POKEMON_PARAM * pp = PokemonParam_AllocWork(HEAPID_EVENT);
	u16 * ret_wk = VMGetWork(core);
	if (POKEPARKDATA_CountPokemon(ppd) == POKEPARK_MONS_MAX) {
		*ret_wk = 1;
	} else {
		*ret_wk = 0;
	}
	sys_FreeMemoryEz(pp);
	return 0;
}

//-----------------------------------------------------------------------------
///	�|�P�p�[�N�p�R�}���h�F�a�����|�P�������{�b�N�X�ɓ]��
//-----------------------------------------------------------------------------
BOOL EvCmdPokeParkTransMons(VM_MACHINE * core)
{
	POKEPARK_DATA * ppd = SaveData_GetPokeParkData(core->fsys->savedata);
	BOX_DATA * box = SaveData_GetBoxData(core->fsys->savedata);
	POKEMON_PARAM * pp = PokemonParam_AllocWork(HEAPID_EVENT);
	MYSTATUS * my = SaveData_GetMyStatus(core->fsys->savedata);
	ZUKAN_WORK * zw = SaveData_GetZukanWork(core->fsys->savedata);
	BOOL result;
	int i;
	for (i = 0; i < POKEPARK_MONS_MAX; i++) {
		//��̂��{�b�N�X�ֈړ�
		POKEPARKDATA_CopyPokemonParam(ppd, i, pp);
		TrainerMemoSetPP(pp, my, TRMEMO_POKEPARK_PLACESET, 0, HEAPID_EVENT);
		result = BOXDAT_PutPokemon(box, PPPPointerGet(pp));
		GF_ASSERT(result);
		SaveData_GetPokeRegister( core->fsys->savedata, pp );
	}
	sys_FreeMemoryEz(pp);
	POKEPARKDATA_PreInit(ppd);	//�|�P�p�[�N�f�[�^�S����
	return 0;
}

//-----------------------------------------------------------------------------
///	�|�P�p�[�N�p�R�}���h�F�X�R�A�擾
//-----------------------------------------------------------------------------
BOOL EvCmdPokeParkGetScore(VM_MACHINE * core)
{
	u16 score_id = VMGetWorkValue(core);
	u16 * ret_wk = VMGetWork(core);
	switch (score_id) {
	case POKEPARK_SCORE_CAPTURE:
		*ret_wk = PokeParkSys_GetCaptureScore(core->fsys);
		break;
	case POKEPARK_SCORE_TIME:
		*ret_wk = PokeParkSys_GetTimeScore(core->fsys);
		break;
	case POKEPARK_SCORE_TYPE:
		*ret_wk = PokeParkSys_GetTypeScore(core->fsys);
		break;
	case POKEPARK_SCORE_TOTAL:
		*ret_wk = PokeParkSys_GetCaptureScore(core->fsys)
			+ PokeParkSys_GetTypeScore(core->fsys)
			+ PokeParkSys_GetTimeScore(core->fsys);
		break;
	}
	return 0;
}

