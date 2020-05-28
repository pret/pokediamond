//============================================================================================
/**
 * @file	field_battle.h
 * @brief	
 * @date	2006.04.29
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================
#ifndef	__FIELD_BATTLE_H__
#define	__FIELD_BATTLE_H__

#include "field_common.h"
#include "battle/battle_common.h"

//============================================================================================
//	きっとbattle_param.hができて独立するはずだがそれまでここに間借りする
//============================================================================================
extern BATTLE_PARAM * BattleParam_Create(int heapID, u32 fight_type);			//実体はfield_battle.c
extern BATTLE_PARAM * BattleParam_CreateForSafari(int heapID, int ball_num);	//実体はfield_battle.c
extern BATTLE_PARAM * BattleParam_CreateForPokePark(int heapID, int ball_num);	//実体はfield_battle.c
extern BATTLE_PARAM * BattleParam_CreateForGetDemo(int heapID, const FIELDSYS_WORK * fsys);	
extern void BattleParam_Delete(BATTLE_PARAM * bp);
extern void BattleParam_AddPokemon(BATTLE_PARAM * bp, POKEMON_PARAM * pp, int client_no);
extern void BattleParam_SetPokeParty(BATTLE_PARAM * bp, const POKEPARTY * party, int client_no);
extern void BattleParam_SetMyStatus(BATTLE_PARAM * bp, const MYSTATUS * my, int client_no);
extern void BattleParam_SetPokeVoice(BATTLE_PARAM * bp, const PERAPVOICE * pv, int client_no);
extern void BattleParam_SetFisingParam(BATTLE_PARAM * bp);

extern BOOL BattleParam_IsWinResult(u32 result);
extern BOOL BattleParam_IsSeacretPokeRetry(u32 result);
extern BOOL BattleParam_IsHaifuPokeRetry(u32 result);

//============================================================================================
//	フィールドシステム依存のBATTLE_PARAM操作
//============================================================================================
extern void BattleParam_UpdateGameData(const BATTLE_PARAM * bp, FIELDSYS_WORK * fsys);
extern void BattleParam_UpdateGameDataOfVirtualBattle(const BATTLE_PARAM * bp, FIELDSYS_WORK * fsys);
extern void BattleParam_SetParamByGameDataCore(BATTLE_PARAM * bp, const FIELDSYS_WORK * fsys);
extern void BattleParam_SetParamByGameData(BATTLE_PARAM * bp, const FIELDSYS_WORK * fsys);
extern void BattleParam_SetParamByWiFiGameData(BATTLE_PARAM * bp, const FIELDSYS_WORK * fsys, int lvLimit);
extern void BattleParam_SetTemotiListParamGameData(BATTLE_PARAM * bp, const FIELDSYS_WORK * fsys,const u8* temotiList);
extern void BattleParam_SetCommBattle(BATTLE_PARAM* bp, const FIELDSYS_WORK* fsys, const POKEPARTY* party, const u8* setlist);


#endif	/* __FIELD_BATTLE_H__ */

