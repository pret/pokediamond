//============================================================================================
/**
 * @file	pokeparty.h
 * @brief	ポケモンパーティ操作
 * @author	tamada	GAME FREAK Inc.
 * @date	2005.10.13
 *
 * ポケモンパーティーとは自分や対戦相手の手持ちなど、複数のポケモンをひとかたまりとして
 * 扱いたい場合に使用する。
 * 手持ちにポケモンを加えたり、あるいは手持ちから外したり、位置を入れ替えたりなどの操作は
 * POKEPARTYを対象として行う。
 */
//============================================================================================

#ifndef	__POKEPARTY_H__
#define	__POKEPARTY_H__

#include "system/savedata_def.h"	//SAVEDATA参照のため
#include "poketool/poke_tool.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @param	ポケモンパーティ型定義
 */
//----------------------------------------------------------
typedef struct _POKEPARTY POKEPARTY;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	セーブデータシステムが依存する関数
//----------------------------------------------------------
extern int PokeParty_GetWorkSize(void);
extern POKEPARTY * PokeParty_AllocPartyWork(u32 heapID);
extern void PokeParty_InitWork(POKEPARTY * party);

//----------------------------------------------------------
//	POKEPARTY操作のための関数
//----------------------------------------------------------
extern void PokeParty_Init(POKEPARTY * party, int max);
extern POKEMON_PARAM * PokeParty_GetMemberPointer(const POKEPARTY * party, int pos);
extern BOOL PokeParty_Add(POKEPARTY * party, POKEMON_PARAM * poke);
extern BOOL PokeParty_Delete(POKEPARTY * party, int pos);
BOOL PokeParty_ExchangePosition(POKEPARTY * party, int pos1, int pos2);
extern void PokeParty_Copy(const POKEPARTY * src, POKEPARTY * dst);
extern BOOL PokeParty_PokemonCheck(const POKEPARTY * ppt, int mons_no);
extern int PokeParty_GetPokeCount(const POKEPARTY* party);
extern void PokeParty_SetMemberData( POKEPARTY* party, int pos, POKEMON_PARAM* pp );

extern void Debug_PokeParty_MakeParty(POKEPARTY * party);
//----------------------------------------------------------
//	セーブデータ取得のための関数
//----------------------------------------------------------
extern POKEPARTY * SaveData_GetTemotiPokemon(SAVEDATA * sv);

#ifdef CREATE_INDEX
extern void *Index_Get_PokeCount_Offset(POKEPARTY *pt);
#endif

#endif	/* __POKEPARTY_H__ */

