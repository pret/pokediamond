//============================================================================================
/**
 * @file	scr_pokepark.c
 * @brief	スクリプトコマンド：ポケパーク関連
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
///	ポケパーク用コマンド：開始・終了制御
//-----------------------------------------------------------------------------
BOOL EvCmdPokeParkControl(VM_MACHINE * core)
{
	EVENTWORK * ev = SaveData_GetEventWork(core->fsys->savedata);
	u16 mode = VMGetWorkValue(core);
	if (mode == POKEPARK_MODE_START) {
		SysFlag_PokeParkSet(ev);
		PokeParkSys_Init(core->fsys);	//エンカウント設定とか、時間カウント開始とか
	} else if (mode == POKEPARK_MODE_END) {
		SysFlag_PokeParkReset(ev);
		PokeParkSys_Finish(core->fsys); //時間カウントストップとか
	} else {
		GF_ASSERT(0);
	}
	return 0;
}

//-----------------------------------------------------------------------------
///	ポケパーク用コマンド：預けたポケモンを数える
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
///	ポケパーク用コマンド：預けたポケモンをボックスに転送
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
		//一体ずつボックスへ移動
		POKEPARKDATA_CopyPokemonParam(ppd, i, pp);
		TrainerMemoSetPP(pp, my, TRMEMO_POKEPARK_PLACESET, 0, HEAPID_EVENT);
		result = BOXDAT_PutPokemon(box, PPPPointerGet(pp));
		GF_ASSERT(result);
		SaveData_GetPokeRegister( core->fsys->savedata, pp );
	}
	sys_FreeMemoryEz(pp);
	POKEPARKDATA_PreInit(ppd);	//ポケパークデータ全消去
	return 0;
}

//-----------------------------------------------------------------------------
///	ポケパーク用コマンド：スコア取得
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

