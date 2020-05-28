//===========================================================================
/**
 * @file	ev_pokemon.h
 * @brief	イベントソース：ポケモン関連
 * @author	tamada GAME FREAK Inc.
 * @date	2005.12.18
 */
//===========================================================================

#ifndef	__EV_POKEMON_H__
#define	__EV_POKEMON_H__

#include "field_common.h"
#include "poketool/pokeparty.h"
#include "poketool/poke_tool.h"
#include "system/placename.h"

extern BOOL EvPoke_Add(int heapID, SAVEDATA * sv, u16 monsno, u8 level,
		u16 itemno, int place_id, int ground_id);
extern BOOL EvPoke_AddTamago(int heapID, SAVEDATA * sv, u16 monsno,
		u8 eventflg, PLACENAME_TYPE type, int index);

extern BOOL EvPoke_EnableBattle(POKEMON_PARAM * pp);
extern int EvPoke_CountLivingPokemon(const POKEPARTY * party);
extern POKEMON_PARAM *EvPoke_GetLivingPokemonTop(const POKEPARTY * party);
extern POKEMON_PARAM * EvPoke_GetPokemonTop(const POKEPARTY * party);
extern BOOL EvPoke_Enable2vs2Battle(const POKEPARTY * party);
extern void EvPoke_ChangeWaza(POKEPARTY * party, int poke_pos, int waza_pos, u16 waza_no);
extern int EvPoke_CheckWaza(POKEPARTY * party, u16 waza_no);


//-------------------------------------------------------------
//-------------------------------------------------------------
extern void EvPoke_SetChampionRibbon(POKEPARTY * party);

//-------------------------------------------------------------
//-------------------------------------------------------------
typedef enum {
	FLD_POISON_NODAMAGE = 0,
	FLD_POISON_DAMAGE,
	FLD_POISON_DEAD,
}FLD_POISON_STAT;

extern FLD_POISON_STAT EvPoke_PoisonDamage(POKEPARTY * party, u16 placeID);
extern BOOL EvPoke_ApprovePoisonDead(POKEMON_PARAM * pp);

#endif	//	__EV_POKEMON_H__

