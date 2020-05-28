//============================================================================================
/**
 * @file	move_pokemon.h
 * @brief	ˆÚ“®ƒ|ƒPƒ‚ƒ“
 * @author	Saito GAME FREAK inc.
 * @date	2006.05.12
 */
//============================================================================================
#ifndef __MOVE_POKEMON_H__
#define __MOVE_POKEMON_H__

#include "savedata/savedata.h"
#include "savedata/encount.h"
extern void MP_JumpMovePokemonAll(ENC_SV_PTR inEncData);
extern void MP_JumpMovePokemon(ENC_SV_PTR inEncData, const u8 inTarget);
extern void MP_MovePokemonNeighboring(ENC_SV_PTR inEncData);
extern void MP_AddMovePoke(SAVEDATA *sv, const u8 inTargetPoke);
extern int MP_GetMovePokeZone(const u8 inIndex);
extern BOOL MP_CheckMovePoke(ENC_SV_PTR inEncData);
extern void MP_UpdatePlayerZoneHist(ENC_SV_PTR inEncData, const int inZone);
#ifdef PM_DEBUG
extern void MP_DebugUpdateData(	ENC_SV_PTR data, const u8 inTargetPoke, const u8  inZoneIdx);
#endif

#endif	//__MOVE_POKEMON_H__
