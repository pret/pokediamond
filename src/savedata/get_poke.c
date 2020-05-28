//============================================================================================
/**
 * @file	get_poke.c
 * @brief	ポケモン入手時のセーブデータ処理
 * @author	taya
 * @date	2006.07.26
 */
//============================================================================================
#include "common.h"
#include "system\gamedata.h"
#include "savedata\savedata.h"
#include "poketool\poke_tool.h"

#include "savedata\zukanwork.h"
#include "field\poketch_data.h"

#include "savedata\get_poke.h"
#include "savedata/record.h"


//------------------------------------------------------------------
/**
 * 図鑑の手に入れたフラグ、ポケッチのポケモンヒストリーなど、
 * ポケモン入手時に必要なセーブデータ関連処理をまとめて呼び出す
 *
 * @param   sv		セーブデータポインタ
 * @param   pp		ポケモンパラメータ
 */
//------------------------------------------------------------------
void SaveData_GetPokeRegister( SAVEDATA* sv, const POKEMON_PARAM* pp )
{
	if( PokeParaGet((POKEMON_PARAM*)pp, ID_PARA_tamago_flag, NULL) == FALSE )
	{
		ZUKAN_WORK * zw = SaveData_GetZukanWork(sv);
		RECORD_Score_AddZukanScore( SaveData_GetRecord(sv), zw,
				PokeParaGet((POKEMON_PARAM*)pp, ID_PARA_monsno, NULL) );
		ZukanWork_SetPokeGet( zw, (POKEMON_PARAM*)pp );
		PoketchData_PokeHistory_Add( SaveData_GetPoketchData(sv), (const POKEMON_PASO_PARAM*)pp );
	}
}

